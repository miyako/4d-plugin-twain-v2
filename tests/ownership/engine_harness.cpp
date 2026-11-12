/*
 * Synthetic 4D engine boundary for ownership regressions.
 *
 * Compiles the real plugin entry point (4DPlugin-TWAIN.cpp, included below)
 * and links the real support/4DPlugin-JSON.cpp, capabilities.cpp,
 * twain_dsm.cpp, twain_jpg.cpp, twain_png.cpp, the built 4D Plugin API
 * classes and the unmodified 4DPluginAPI.c. Only gCall4D is replaced.
 * Every engine resource (Unistrings, pictures, objects/collections,
 * handles) is a real heap block tracked in a live set, so leaks are
 * detected exactly and a dispose of something the engine no longer owns
 * (double free) is reported by name instead of being freed a second time.
 *
 * No scanner is ever touched: TWAIN.framework is not linked. DSM_Entry is
 * a synthetic data source that lists two identities and transfers small
 * synthetic grayscale pages through the real memory-transfer loop, and the
 * DSM memory entry points (DSM::Alloc/Free/Lock/Unlock) are the harness's,
 * modelling the Windows TWAINDSM path (on macOS the plugin's own versions
 * are "return 0" stubs, so no page could ever reach TWAIN_SCAN's result
 * loop, which is platform-independent).
 *
 * Engine semantics modelled (per the SDK contract):
 *  - PA_CreateVariable(eVK_Unistring/eVK_Picture) allocates an empty value.
 *  - PA_Set*Variable is shallow; PA_GetStringVariable is borrowed.
 *  - PA_SetObjectProperty / PA_SetCollectionElement deep-copy strings and
 *    pictures and retain objects/collections; the caller still owns its
 *    variable.
 *  - PA_GetObjectProperty returns an owned copy (or a retained object/
 *    collection) that must be cleared; on error the result is not an
 *    engine value (poisoned here) and must be neither read nor cleared.
 *  - PA_ExecuteCommandByID returns an owned result, with the same rule on
 *    error.
 */

/* Resolved through -I <source-root>, so the same harness tests baseline and fixed trees. */
#include "4DPlugin-TWAIN.cpp"

#include "PrivateTypes.h"
#include "EntryPoints.h"

#include <map>
#include <set>
#include <string>
#include <vector>

extern "C" Call4DProcPtr gCall4D;

namespace {

typedef std::basic_string<PA_Unichar> u16;

struct Obj {
    int rc;
    bool coll;
    std::map<u16, PA_Variable> props;
    std::vector<PA_Variable> items;
};

/* data first: the SDK dereferences array handles directly (*(T**)handle). */
struct Handle { char *data; size_t size; };

std::set<void *> g_strings;
std::map<void *, std::vector<uint8_t> > g_pictures;
std::set<Obj *> g_objects;
std::set<void *> g_handles;
std::set<void *> g_dsm_mem;
std::vector<std::string> g_violations;

/* PA_GetObjectProperty for this key fails. */
std::string g_fail_key;
/* JSON Stringify (1217) / JSON Parse (1218) fail. */
bool g_fail_stringify = false;
bool g_fail_parse = false;
int g_poison_clears = 0;
int g_parse_calls = 0;
/* A failed call's result is not an engine value: these markers are never
   engine-owned, so clearing (or storing) one is counted, not freed. */
PA_Unichar kPoisonBuf[] = { 'B', 'A', 'D', '!', 0 };
PA_Unichar *const kPoison = kPoisonBuf;
char kPoisonObjBuf[16];
void *const kPoisonObj = kPoisonObjBuf;

PA_Variable undefined_var() { PA_Variable v; memset(&v, 0, sizeof(v)); v.fType = eVK_Undefined; return v; }

void poison_string(PA_Variable *out) {
    *out = undefined_var();
    out->fType = eVK_Unistring;
    out->uValue.fString.fString = kPoison;
    out->uValue.fString.fLength = 4;
}

void poison_object(PA_Variable *out) {
    *out = undefined_var();
    out->fType = eVK_Object;
    out->uValue.fObject = (PA_ObjectRef)kPoisonObj;
}

void violation(const std::string &what) {
    fprintf(stderr, "  ENGINE CONTRACT: %s\n", what.c_str());
    g_violations.push_back(what);
}

void poison_cleared() {
    g_poison_clears++;
    fprintf(stderr, "  cleared the result of a failed engine call\n");
}

[[noreturn]] void die(const char *msg) {
    fprintf(stderr, "HARNESS ERROR: %s\n", msg);
    fflush(stderr);
    abort();
}

std::string narrow(const u16 &s) { std::string r; for(PA_Unichar c : s) r.push_back((char)c); return r; }
u16 widen(const std::string &s) { u16 r; for(char c : s) r.push_back((PA_Unichar)(unsigned char)c); return r; }

PA_Unistring new_string(const PA_Unichar *src, size_t len) {
    PA_Unichar *buf = (PA_Unichar *)malloc((len + 1) * sizeof(PA_Unichar));
    if(len) memcpy(buf, src, len * sizeof(PA_Unichar));
    buf[len] = 0;
    g_strings.insert(buf);
    PA_Unistring s;
    s.fLength = (PA_long32)len;
    s.fString = buf;
    s.fReserved1 = 0;
    s.fReserved2 = 0;
    return s;
}

void free_string(PA_Unistring *s) {
    if(!s->fString) return;
    if(s->fString == kPoison) {
        poison_cleared();
    } else if(!g_strings.erase(s->fString)) {
        violation("double_dispose_string");
    } else {
        free(s->fString);
    }
    s->fString = 0;
    s->fLength = 0;
}

void *new_picture(const void *bytes, size_t len) {
    void *p = malloc(16);
    std::vector<uint8_t> &b = g_pictures[p];
    if(len) b.assign((const uint8_t *)bytes, (const uint8_t *)bytes + len);
    return p;
}

void free_picture(void *p) {
    if(!p) return;
    if(!g_pictures.erase(p)) { violation("double_dispose_picture"); return; }
    free(p);
}

Handle *new_handle(size_t size) {
    Handle *h = (Handle *)malloc(sizeof(Handle));
    h->size = size;
    h->data = (char *)calloc(1, size ? size : 1);
    g_handles.insert(h);
    return h;
}

void free_handle(Handle *h) {
    if(!h) return;
    if(!g_handles.erase(h)) { violation("double_dispose_handle"); return; }
    free(h->data);
    free(h);
}

Handle *live_handle(void *p) {
    if(!g_handles.count(p)) die("used an unknown handle");
    return (Handle *)p;
}

void release_object(Obj *o);

void clear_var(PA_Variable *v) {
    switch(v->fType) {
        case eVK_Unistring: free_string(&v->uValue.fString); break;
        case eVK_Picture: free_picture(v->uValue.fPicture); break;
        case eVK_Blob: free_handle((Handle *)v->uValue.fBlob.fHandle); break;
        case eVK_Object:
        case eVK_Collection: {
            void *p = v->fType == eVK_Object ? (void *)v->uValue.fObject : (void *)v->uValue.fCollection;
            if(p == kPoisonObj) poison_cleared();
            else if(p) release_object((Obj *)p);
            break;
        }
        default: break;
    }
    v->fType = eVK_Undefined;
}

Obj *live(void *p) {
    if(!g_objects.count((Obj *)p)) die("used a dead object/collection");
    return (Obj *)p;
}

PA_Variable copy_var(const PA_Variable &src) {
    PA_Variable dst = src;
    switch(src.fType) {
        case eVK_Unistring:
            if(src.uValue.fString.fString == kPoison) violation("stored_failed_result");
            dst.uValue.fString = new_string(src.uValue.fString.fString, src.uValue.fString.fLength);
            break;
        case eVK_Picture: {
            void *pic = src.uValue.fPicture; /* PA_Variable is packed: never bind to its members */
            auto it = g_pictures.find(pic);
            if(it == g_pictures.end()) die("stored a dead picture");
            std::vector<uint8_t> b = it->second;
            dst.uValue.fPicture = new_picture(b.data(), b.size());
            break;
        }
        case eVK_Object:
        case eVK_Collection: {
            void *p = src.fType == eVK_Object ? (void *)src.uValue.fObject : (void *)src.uValue.fCollection;
            /* Stored as-is (not retained), so it is also counted when the parent clears it. */
            if(p == kPoisonObj) violation("stored_failed_result");
            else if(p) live(p)->rc++;
            break;
        }
        default: break;
    }
    return dst;
}

Obj *new_object(bool coll = false) {
    Obj *o = new Obj();
    o->rc = 1;
    o->coll = coll;
    g_objects.insert(o);
    return o;
}

void release_object(Obj *o) {
    if(!g_objects.count(o)) { violation("double_release_object"); return; }
    if(--o->rc == 0) {
        for(auto &kv : o->props) clear_var(&kv.second);
        for(auto &v : o->items) clear_var(&v);
        g_objects.erase(o);
        delete o;
    }
}

u16 key_of(const PA_Unistring &k) { return u16(k.fString, k.fLength); }

PA_Variable object_result(Obj *o) {
    PA_Variable v = undefined_var();
    v.fType = o->coll ? eVK_Collection : eVK_Object;
    if(o->coll) v.uValue.fCollection = (PA_CollectionRef)o; else v.uValue.fObject = (PA_ObjectRef)o;
    return v;
}

void execute_command(EngineBlock *eb) {
    PA_Variable **params = (PA_Variable **)eb->fPtr1;
    PA_Variable *ret = (PA_Variable *)eb->fPtr2;
    switch(eb->fParam1) {
        case 1225: { /* OB Copy */
            Obj *src = live(params[0]->uValue.fObject);
            Obj *dst = new_object(false);
            for(auto &kv : src->props) dst->props[kv.first] = copy_var(kv.second);
            *ret = object_result(dst);
            break;
        }
        case 1217: { /* JSON Stringify */
            live(params[0]->uValue.fObject);
            if(g_fail_stringify) { poison_string(ret); eb->fError = -1; break; }
            u16 json = widen("{}");
            ret->fType = eVK_Unistring;
            ret->uValue.fString = new_string(json.c_str(), json.size());
            break;
        }
        case 1218: { /* JSON Parse(text; Is object) */
            g_parse_calls++;
            if(params[0]->fType != eVK_Unistring) die("JSON Parse without text");
            if(g_fail_parse) { poison_object(ret); eb->fError = -1; break; }
            Obj *o = new_object(false);
            PA_Variable src = undefined_var();
            src.fType = eVK_Unistring;
            src.uValue.fString = params[0]->uValue.fString;
            o->props[widen("json")] = copy_var(src);
            *ret = object_result(o);
            break;
        }
        case 1231: { /* OB Is defined */
            Obj *o = live(params[0]->uValue.fObject);
            ret->fType = eVK_Boolean;
            ret->uValue.fBoolean = o->props.count(key_of(params[1]->uValue.fString)) ? 1 : 0;
            break;
        }
        case 1471: *ret = object_result(new_object(false)); break; /* New Object */
        case 1472: *ret = object_result(new_object(true)); break; /* New Collection */
        default: {
            char msg[64];
            snprintf(msg, sizeof(msg), "unexpected PA_ExecuteCommandByID %d", (int)eb->fParam1);
            die(msg);
        }
    }
}

void engine(short selector, EngineBlock *eb) {
    switch(selector) {
        case EX_CREATE_UNISTRING: {
            const PA_Unichar *src = (const PA_Unichar *)eb->fHandle;
            size_t len = 0;
            while(src[len]) len++;
            eb->fUniString1 = new_string(src, len);
            break;
        }
        case EX_DISPOSE_UNISTRING:
            free_string(&eb->fUniString1);
            break;
        case EX_VARIABLE_TO_STRING: {
            PA_Variable *v = (PA_Variable *)eb->fHandle;
            if(v->fType == eVK_Unistring) eb->fUniString1 = v->uValue.fString; /* borrowed */
            break;
        }
        case EX_CREATE_PICTURE:
            eb->fPicture = new_picture(eb->fPtr1, (size_t)eb->fParam1);
            break;
        case EX_DISPOSE_PICTURE:
            free_picture(eb->fPicture);
            break;
        case EX_CLEAR_VARIABLE:
            clear_var((PA_Variable *)eb->fPtr1);
            break;
        case EX_GET_INFORMATION:
            eb->fParam2 = 0x00002000; /* 4D v20: PA_CreateObject uses New Object */
            break;
        case EX_YIELD_ABSOLUTE:
            break;
        case EX_SET_OBJ_VALUE: {
            Obj *o = live(eb->fPtr1);
            PA_Variable value = copy_var(*(PA_Variable *)eb->fPtr2);
            if(eb->fShort == eVK_Collection) {
                if(!o->coll) die("collection set on an object");
                size_t i = (size_t)eb->fLongint;
                while(o->items.size() <= i) o->items.push_back(undefined_var());
                clear_var(&o->items[i]);
                o->items[i] = value;
                break;
            }
            u16 k = key_of(eb->fUniString1);
            auto it = o->props.find(k);
            if(it != o->props.end()) clear_var(&it->second);
            o->props[k] = value;
            break;
        }
        case EX_GET_OBJ_VALUE: {
            Obj *o = live(eb->fPtr1);
            PA_Variable *out = (PA_Variable *)eb->fPtr2;
            if(eb->fShort == eVK_Collection) {
                size_t i = (size_t)eb->fLongint;
                *out = i < o->items.size() ? copy_var(o->items[i]) : undefined_var();
                break;
            }
            u16 k = key_of(eb->fUniString1);
            if(!g_fail_key.empty() && narrow(k) == g_fail_key) {
                auto it = o->props.find(k);
                if(it != o->props.end() && (it->second.fType == eVK_Object || it->second.fType == eVK_Collection))
                    poison_object(out);
                else
                    poison_string(out);
                eb->fError = -1;
                break;
            }
            auto it = o->props.find(k);
            *out = it == o->props.end() ? undefined_var() : copy_var(it->second);
            break;
        }
        case EX_EXECUTE_COMMAND_BY_ID:
            execute_command(eb);
            break;
        case EX_HANDLE_MANAGER: {
            switch(eb->fParam1) {
                case 1: eb->fHandle = (PA_Handle)new_handle((size_t)eb->fParam2); break;
                case 2: free_handle((Handle *)eb->fHandle); break;
                case 4: eb->fParam2 = (sLONG_PTR)live_handle(eb->fHandle)->size; break;
                case 5: eb->fParam3 = (sLONG_PTR)live_handle(eb->fHandle)->data; break;
                case 6: break;
                default: die("unexpected handle manager op");
            }
            break;
        }
        default: {
            char msg[64];
            snprintf(msg, sizeof(msg), "unmodelled engine selector %d", selector);
            die(msg);
        }
    }
}

/* ---------- synthetic TWAIN data source (no scanner, no TWAIN.framework) ---------- */

const char *const kSources[] = { "Synthetic Scanner A", "Synthetic Scanner B" };
const int kNumSources = 2;
const int kPageWidth = 16, kPageLength = 8;

struct Twain {
    int next_source;
    int dsm_open, ds_open, ds_enabled;
    int pages;        /* pages the source will transfer */
    int transferred;
} g_tw;

void fill_identity(TW_IDENTITY *id, int i) {
    memset(id, 0, sizeof(*id));
    id->Id = (decltype(id->Id))(intptr_t)(100 + i);
    id->Version.MajorNum = 1;
    id->Version.MinorNum = i;
    id->Version.Language = TWLG_ENGLISH;
    id->Version.Country = TWCY_USA;
    snprintf((char *)id->Version.Info, sizeof(id->Version.Info), "synthetic %d", i);
    id->ProtocolMajor = 2;
    id->ProtocolMinor = 3;
    id->SupportedGroups = DG_CONTROL | DG_IMAGE;
    snprintf((char *)id->Manufacturer, sizeof(id->Manufacturer), "Example Synthetic Devices");
    snprintf((char *)id->ProductFamily, sizeof(id->ProductFamily), "Synthetic");
    snprintf((char *)id->ProductName, sizeof(id->ProductName), "%s", kSources[i]);
}

TW_UINT16 synthetic_dsm(pTW_IDENTITY, pTW_IDENTITY, TW_UINT32 DG, TW_UINT16 DAT, TW_UINT16 MSG, TW_MEMREF pData) {
    if(DG == DG_CONTROL && DAT == DAT_PARENT) {
        if(MSG == MSG_OPENDSM) { g_tw.dsm_open++; return TWRC_SUCCESS; }
        if(MSG == MSG_CLOSEDSM) { g_tw.dsm_open--; return TWRC_SUCCESS; }
    }
    if(DG == DG_CONTROL && DAT == DAT_IDENTITY) {
        TW_IDENTITY *id = (TW_IDENTITY *)pData;
        switch(MSG) {
            case MSG_GETFIRST: g_tw.next_source = 0; /* fall through */
            case MSG_GETNEXT:
                if(g_tw.next_source >= kNumSources) return TWRC_ENDOFLIST;
                fill_identity(id, g_tw.next_source++);
                return TWRC_SUCCESS;
            case MSG_GETDEFAULT: fill_identity(id, 0); return TWRC_SUCCESS;
            case MSG_OPENDS: g_tw.ds_open++; return TWRC_SUCCESS;
            case MSG_CLOSEDS: g_tw.ds_open--; return TWRC_SUCCESS;
        }
    }
    if(DG == DG_CONTROL && DAT == DAT_CAPABILITY) return TWRC_FAILURE; /* no capabilities */
    if(DG == DG_CONTROL && DAT == DAT_STATUS) { memset(pData, 0, sizeof(TW_STATUS)); return TWRC_SUCCESS; }
    if(DG == DG_CONTROL && DAT == DAT_USERINTERFACE) {
        if(MSG == MSG_ENABLEDS) { g_tw.ds_enabled++; return TWRC_SUCCESS; }
        if(MSG == MSG_DISABLEDS) { g_tw.ds_enabled--; return TWRC_SUCCESS; }
    }
    if(DG == DG_CONTROL && DAT == DAT_EVENT && MSG == MSG_PROCESSEVENT) {
        ((TW_EVENT *)pData)->TWMessage = g_tw.pages ? MSG_XFERREADY : MSG_CLOSEDSREQ;
        return TWRC_DSEVENT;
    }
    if(DG == DG_IMAGE && DAT == DAT_IMAGEINFO && MSG == MSG_GET) {
        TW_IMAGEINFO *info = (TW_IMAGEINFO *)pData;
        info->XResolution.Whole = 72;
        info->YResolution.Whole = 72;
        info->ImageWidth = kPageWidth;
        info->ImageLength = kPageLength;
        info->SamplesPerPixel = 1;
        info->BitsPerSample[0] = 8;
        info->BitsPerPixel = 8;
        info->PixelType = TWPT_GRAY;
        info->Compression = TWCP_NONE;
        return TWRC_SUCCESS;
    }
    if(DG == DG_CONTROL && DAT == DAT_SETUPMEMXFER && MSG == MSG_GET) {
        TW_SETUPMEMXFER *s = (TW_SETUPMEMXFER *)pData;
        s->MinBufSize = s->MaxBufSize = s->Preferred = kPageWidth * kPageLength;
        return TWRC_SUCCESS;
    }
    if(DG == DG_IMAGE && DAT == DAT_IMAGEMEMXFER && MSG == MSG_GET) {
        TW_IMAGEMEMXFER *x = (TW_IMAGEMEMXFER *)pData;
        TW_UINT32 n = kPageWidth * kPageLength;
        if(!x->Memory.TheMem || x->Memory.Length < n) die("memory transfer without a buffer");
        uint8_t *p = (uint8_t *)x->Memory.TheMem;
        for(TW_UINT32 i = 0; i < n; i++) p[i] = (uint8_t)(i * 7 + g_tw.transferred * 31); /* synthetic gradient */
        x->Compression = TWCP_NONE;
        x->BytesPerRow = kPageWidth;
        x->Columns = kPageWidth;
        x->Rows = kPageLength;
        x->BytesWritten = n;
        return TWRC_XFERDONE;
    }
    if(DG == DG_CONTROL && DAT == DAT_PENDINGXFERS) {
        TW_PENDINGXFERS *px = (TW_PENDINGXFERS *)pData;
        if(MSG == MSG_ENDXFER) { g_tw.transferred++; g_tw.pages--; px->Count = (TW_UINT16)g_tw.pages; return TWRC_SUCCESS; }
        if(MSG == MSG_RESET) { g_tw.pages = 0; px->Count = 0; return TWRC_SUCCESS; }
    }
    return TWRC_FAILURE;
}

} // namespace

extern "C" TW_UINT16 DSM_Entry(pTW_IDENTITY pOrigin, pTW_IDENTITY pDest, TW_UINT32 DG, TW_UINT16 DAT, TW_UINT16 MSG, TW_MEMREF pData) {
    return synthetic_dsm(pOrigin, pDest, DG, DAT, MSG, pData);
}

/* DSM memory (the TWAINDSM DSM_MemAllocate/Free/Lock/Unlock model). */
TW_HANDLE DSM::Alloc(void *, TW_UINT32 size) {
    void *p = calloc(1, size ? size : 1);
    g_dsm_mem.insert(p);
    return (TW_HANDLE)p;
}
void DSM::Free(void *, TW_HANDLE h) {
    if(!h) return;
    if(!g_dsm_mem.erase((void *)h)) { violation("double_free_dsm_memory"); return; }
    free((void *)h);
}
TW_MEMREF DSM::Lock(void *, TW_HANDLE h) {
    if(!g_dsm_mem.count((void *)h)) die("locked unknown DSM memory");
    return (TW_MEMREF)h;
}
void DSM::Unlock(void *, TW_HANDLE) {}

namespace {

/* ---------- test helpers ---------- */

PA_Unistring U(const char *ascii) {
    u16 s = widen(ascii);
    return new_string(s.c_str(), s.size());
}

void put(Obj *o, const char *key, PA_Variable v) {
    PA_Unistring k = U(key);
    PA_SetObjectProperty((PA_ObjectRef)o, &k, v);
    PA_DisposeUnistring(&k);
}

void put_text(Obj *o, const char *key, const char *value) {
    PA_Variable v = undefined_var();
    PA_Unistring u = U(value);
    PA_SetStringVariable(&v, &u);
    put(o, key, v);
    PA_ClearVariable(&v);
}

void put_bool(Obj *o, const char *key, bool b) {
    PA_Variable v = undefined_var();
    PA_SetBooleanVariable(&v, b);
    put(o, key, v);
}

Obj *put_object(Obj *o, const char *key, bool coll) {
    Obj *c = new_object(coll);
    PA_Variable v = object_result(c);
    put(o, key, v);
    PA_ClearVariable(&v);
    return c;
}

std::string text_of(Obj *o, const char *key) {
    auto it = o->props.find(widen(key));
    if(it == o->props.end() || it->second.fType != eVK_Unistring) return "<none>";
    return narrow(key_of(it->second.uValue.fString));
}

bool check(bool ok, const char *what) {
    if(!ok) fprintf(stderr, "  check failed: %s\n", what);
    return ok;
}

bool no_leaks() {
    bool ok = true;
    for(void *p : g_strings) {
        fprintf(stderr, "  LEAK: engine string \"%s\"\n", narrow(u16((PA_Unichar *)p)).c_str());
        ok = false;
    }
    if(!g_pictures.empty()) { fprintf(stderr, "  LEAK: %zu engine picture(s)\n", g_pictures.size()); ok = false; }
    if(!g_objects.empty()) { fprintf(stderr, "  LEAK: %zu engine object(s)/collection(s)\n", g_objects.size()); ok = false; }
    if(!g_handles.empty()) { fprintf(stderr, "  LEAK: %zu engine handle(s)\n", g_handles.size()); ok = false; }
    if(!g_dsm_mem.empty()) { fprintf(stderr, "  LEAK: %zu DSM memory block(s)\n", g_dsm_mem.size()); ok = false; }
    if(g_tw.dsm_open || g_tw.ds_open || g_tw.ds_enabled) { fprintf(stderr, "  TWAIN session left open\n"); ok = false; }
    if(g_poison_clears) { fprintf(stderr, "  %d failed result(s) cleared\n", g_poison_clears); ok = false; }
    if(!g_violations.empty()) ok = false;
    return ok;
}

/* Calls the real `TWAIN Get devices` command (selector 1). */
Obj *call_get_devices() {
    PA_CollectionRef result = NULL;
    PluginBlock pb;
    pb.fParameters = NULL;
    pb.fResult = &result;
    PluginMain(1, &pb);
    return (Obj *)result;
}

/* Calls the real `TWAIN Get default option` command (selector 2). */
Obj *call_get_default_option(const char *scanner) {
    PA_Unistring p1 = U(scanner);
    void *args[1] = { &p1 };
    PA_ObjectRef result = NULL;
    PluginBlock pb;
    pb.fParameters = args;
    pb.fResult = &result;
    PluginMain(2, &pb);
    PA_DisposeUnistring(&p1);
    return (Obj *)result;
}

/* Calls the real `TWAIN SCAN` command (selector 3) with a borrowed option object. */
Obj *call_scan(const char *scanner, Obj *option, PA_long32 format, int pages) {
    PA_Unistring p1 = U(scanner);
    PA_ObjectRef p2 = (PA_ObjectRef)option;
    PA_long32 p3 = format;
    void *args[3] = { &p1, &p2, &p3 };
    PA_CollectionRef result = NULL;
    PluginBlock pb;
    pb.fParameters = args;
    pb.fResult = &result;
    g_tw.pages = pages;
    g_tw.transferred = 0;
    PluginMain(3, &pb);
    PA_DisposeUnistring(&p1);
    return (Obj *)result;
}

bool is_jpeg(const std::vector<uint8_t> &b) { return b.size() > 4 && b[0] == 0xFF && b[1] == 0xD8 && b[b.size() - 2] == 0xFF && b[b.size() - 1] == 0xD9; }
bool is_png(const std::vector<uint8_t> &b) { return b.size() > 8 && !memcmp(b.data(), "\x89PNG\r\n\x1a\n", 8); }

bool pictures_ok(Obj *images, size_t n, bool (*kind)(const std::vector<uint8_t> &)) {
    if(!images || !g_objects.count(images) || !images->coll || images->items.size() != n) return false;
    for(auto &v : images->items) {
        if(v.fType != eVK_Picture) return false;
        void *pic = v.uValue.fPicture;
        auto it = g_pictures.find(pic);
        if(it == g_pictures.end() || !kind(it->second)) return false;
    }
    return true;
}

/* ---------- LIVE defects ---------- */

/* LIVE: TWAIN Get devices never cleared `d` after the deep-copying
   PA_SetCollectionElement, so every device object outlived the result. */
bool defect_live_get_devices_element_not_cleared() {
    Obj *devices = call_get_devices();
    bool ok = check(devices && devices->coll && devices->items.size() == 2, "two devices returned");
    if(ok) {
        Obj *d = (Obj *)devices->items[1].uValue.fObject;
        ok &= check(text_of(d, "productName") == "Synthetic Scanner B", "device B listed");
        ok &= check(d->rc == 1, "device owned by the collection only");
        auto v = d->props.find(widen("version"));
        ok &= check(v != d->props.end() && text_of((Obj *)v->second.uValue.fObject, "info") == "synthetic 1", "version object set");
    }
    if(devices) release_object(devices);
    ok &= check(g_objects.empty(), "no device object outlives the collection");
    return no_leaks() && ok;
}

/* LIVE: ob_set_s(obj, wchar_t*, char*) -- 4 calls per device in TWAIN Get
   devices -- shallow-set over PA_CreateVariable(eVK_Unistring). */
bool defect_live_ob_set_s_empty_owner_leaks() {
    Obj *o = new_object(false);
    ob_set_s((PA_ObjectRef)o, L"productName", "Synthetic Scanner A");
    bool ok = check(text_of(o, "productName") == "Synthetic Scanner A", "value set");
    release_object(o);
    return no_leaks() && ok;
}

/* LIVE: TWAIN SCAN never cleared the picture variable after the
   deep-copying PA_SetCollectionElement (one leaked picture per page). */
bool defect_live_scan_jpeg_pictures_not_cleared() {
    Obj *option = new_object(false);
    Obj *images = call_scan("Synthetic Scanner B", option, 1, 2);
    bool ok = check(pictures_ok(images, 2, is_jpeg), "two JPEG pages returned");
    ok &= check(g_objects.count(option) && option->rc == 1 && option->props.empty(), "caller's option untouched");
    if(images) release_object(images);
    release_object(option);
    return no_leaks() && ok;
}

bool defect_live_scan_png_picture_not_cleared() {
    Obj *images = call_scan("Synthetic Scanner A", NULL, 2, 1);
    bool ok = check(pictures_ok(images, 1, is_png), "one PNG page returned");
    if(images) release_object(images);
    return no_leaks() && ok;
}

/* HARDENING (LIVE): TWAIN Get default option stored the 1218 (JSON Parse)
   result without checking the error; a failed result must be neither
   stored nor cleared. */
bool hardening_live_default_option_parse_error_untouched() {
    g_fail_parse = true;
    Obj *option = call_get_default_option("Synthetic Scanner A");
    g_fail_parse = false;
    bool ok = check(g_parse_calls == 2, "both JSON Parse calls made");
    ok &= check(option && g_objects.count(option) && option->props.empty(), "nothing stored from a failed parse");
    if(option && g_objects.count(option)) release_object(option);
    return no_leaks() && ok;
}

/* HARDENING (LIVE, via TWAIN SCAN): ob_stringify read and cleared the 1217
   result without checking the error. */
bool hardening_live_ob_stringify_error_untouched() {
    Obj *option = new_object(false);
    put_bool(option, "duplex", true);
    g_fail_stringify = true;
    Obj *images = call_scan("Synthetic Scanner A", option, 1, 0);
    g_fail_stringify = false;
    CUTF8String json;
    g_fail_stringify = true;
    ob_stringify((PA_ObjectRef)option, &json);
    g_fail_stringify = false;
    bool ok = check(json.empty(), "failed stringify yields nothing");
    ok &= check(g_objects.count(option) && option->rc == 1 && option->props.size() == 1, "caller's option untouched");
    if(images) release_object(images);
    release_object(option);
    return no_leaks() && ok;
}

/* ---------- DORMANT defects (support/4DPlugin-JSON.cpp, built, no caller) ---------- */

bool defect_dormant_ob_get_a_result_not_cleared() {
    Obj *o = new_object(false);
    put_text(o, "s", "text");
    CUTF8String s;
    bool r = ob_get_a((PA_ObjectRef)o, L"s", &s);
    release_object(o);
    bool ok = check(r && s == (const uint8_t *)"text", "value read");
    return no_leaks() && ok;
}

bool defect_dormant_ob_get_b_wrong_kind_not_cleared() {
    Obj *o = new_object(false);
    put_text(o, "flag", "yes");
    bool b = ob_get_b((PA_ObjectRef)o, L"flag");
    release_object(o);
    bool ok = check(!b, "wrong kind yields false");
    return no_leaks() && ok;
}

bool defect_dormant_ob_get_n_wrong_kind_not_cleared() {
    Obj *o = new_object(false);
    put_text(o, "n", "1.5");
    double d = ob_get_n((PA_ObjectRef)o, L"n");
    release_object(o);
    bool ok = check(d == 0.0, "wrong kind yields 0");
    return no_leaks() && ok;
}

/* The retained object/collection reference was never released, so it
   outlived its owner. The returned ref is borrowed from the parent. */
bool defect_dormant_ob_get_o_c_reference_not_released() {
    Obj *o = new_object(false);
    Obj *child = put_object(o, "child", false);
    Obj *items = put_object(o, "items", true);
    PA_ObjectRef r1 = ob_get_o((PA_ObjectRef)o, L"child");
    PA_CollectionRef r2 = ob_get_c((PA_ObjectRef)o, L"items");
    bool ok = check(r1 == (PA_ObjectRef)child && r2 == (PA_CollectionRef)items, "references returned");
    ok &= check(child->rc == 1 && items->rc == 1, "returned references borrowed from the parent");
    release_object(o);
    return no_leaks() && ok;
}

/* ob_set_s(char*)/ob_set_a/ob_set_p overwrote the value allocated by
   PA_CreateVariable(eVK_Unistring/eVK_Picture). */
bool defect_dormant_ob_set_empty_owner_leaks() {
    Obj *o = new_object(false);
    ob_set_s((PA_ObjectRef)o, "k1", "v1");
    ob_set_a((PA_ObjectRef)o, L"k2", L"v2");
    CUTF16String v3 = widen("v3");
    ob_set_a((PA_ObjectRef)o, L"k3", &v3);
    PA_Picture pic = PA_CreatePicture((void *)"synthetic", 9);
    // ob_set_p consumes `pic` (shallow set, deep-copying set, then clear).
    ob_set_p((PA_ObjectRef)o, L"k4", pic);
    bool ok = check(o->props.size() == 4 && text_of(o, "k1") == "v1" && text_of(o, "k2") == "v2" && text_of(o, "k3") == "v3", "four properties set");
    release_object(o);
    return no_leaks() && ok;
}

/* HARDENING: on error PA_GetObjectProperty's result is not an engine value. */
bool hardening_dormant_ob_get_error_result_untouched() {
    Obj *o = new_object(false);
    put_text(o, "a", "x");
    put_object(o, "child", false);
    g_fail_key = "a";
    CUTF8String s;
    ob_get_a((PA_ObjectRef)o, L"a", &s);
    g_fail_key = "child";
    PA_ObjectRef r = ob_get_o((PA_ObjectRef)o, L"child");
    g_fail_key.clear();
    release_object(o);
    bool ok = check(s.empty() && r == NULL, "failed reads yield nothing");
    return no_leaks() && ok;
}

/* ---------- controls (pass on both trees) ---------- */

bool control_get_default_option() {
    Obj *option = call_get_default_option("Synthetic Scanner B");
    bool ok = check(g_parse_calls == 2, "both JSON Parse calls made");
    ok &= check(option && g_objects.count(option) && option->props.size() == 2, "option and values set");
    if(ok) {
        auto a = option->props.find(widen("option"));
        auto b = option->props.find(widen("values"));
        ok &= check(a != option->props.end() && b != option->props.end(), "keys");
        ok &= check(text_of((Obj *)a->second.uValue.fObject, "json") == "{}" && text_of((Obj *)b->second.uValue.fObject, "json") == "{}", "parsed from the synthetic source");
        ok &= check(((Obj *)a->second.uValue.fObject)->rc == 1, "parsed object owned by the result only");
    }
    if(option && g_objects.count(option)) release_object(option);
    return no_leaks() && ok;
}

bool control_scan_no_pages() {
    Obj *option = new_object(false);
    put_bool(option, "duplex", true);
    Obj *images = call_scan("Synthetic Scanner A", option, 1, 0);
    bool ok = check(images && images->coll && images->items.empty(), "empty result");
    ok &= check(g_objects.count(option) && option->rc == 1 && option->props.size() == 1, "caller's option untouched");
    if(images) release_object(images);
    release_object(option);
    return no_leaks() && ok;
}

bool control_ob_set_get_round_trip() {
    Obj *o = new_object(false);
    ob_set_n((PA_ObjectRef)o, L"n", 2.5);
    ob_set_b((PA_ObjectRef)o, L"b", true);
    ob_set_i((PA_ObjectRef)o, L"i", 7);
    ob_set_0((PA_ObjectRef)o, L"z");
    ob_set_o((PA_ObjectRef)o, L"o", PA_CreateObject());
    ob_set_c((PA_ObjectRef)o, L"c", PA_CreateCollection());
    bool ok = check(o->props.size() == 6, "six properties set");
    ok &= check(ob_is_defined((PA_ObjectRef)o, L"n") && !ob_is_defined((PA_ObjectRef)o, L"x"), "ob_is_defined");
    release_object(o);
    return no_leaks() && ok;
}

bool control_ob_stringify() {
    Obj *o = new_object(false);
    put_text(o, "a", "x");
    CUTF8String json;
    ob_stringify((PA_ObjectRef)o, &json);
    bool ok = check(json == (const uint8_t *)"{}", "stringified");
    ok &= check(o->rc == 1 && o->props.size() == 1, "object untouched");
    release_object(o);
    return no_leaks() && ok;
}

struct Test { const char *name; bool (*fn)(); };
const Test kTests[] = {
    { "defect_live_get_devices_element_not_cleared", defect_live_get_devices_element_not_cleared },
    { "defect_live_ob_set_s_empty_owner_leaks", defect_live_ob_set_s_empty_owner_leaks },
    { "defect_live_scan_jpeg_pictures_not_cleared", defect_live_scan_jpeg_pictures_not_cleared },
    { "defect_live_scan_png_picture_not_cleared", defect_live_scan_png_picture_not_cleared },
    { "hardening_live_default_option_parse_error_untouched", hardening_live_default_option_parse_error_untouched },
    { "hardening_live_ob_stringify_error_untouched", hardening_live_ob_stringify_error_untouched },
    { "defect_dormant_ob_get_a_result_not_cleared", defect_dormant_ob_get_a_result_not_cleared },
    { "defect_dormant_ob_get_b_wrong_kind_not_cleared", defect_dormant_ob_get_b_wrong_kind_not_cleared },
    { "defect_dormant_ob_get_n_wrong_kind_not_cleared", defect_dormant_ob_get_n_wrong_kind_not_cleared },
    { "defect_dormant_ob_get_o_c_reference_not_released", defect_dormant_ob_get_o_c_reference_not_released },
    { "defect_dormant_ob_set_empty_owner_leaks", defect_dormant_ob_set_empty_owner_leaks },
    { "hardening_dormant_ob_get_error_result_untouched", hardening_dormant_ob_get_error_result_untouched },
    { "control_get_default_option", control_get_default_option },
    { "control_scan_no_pages", control_scan_no_pages },
    { "control_ob_set_get_round_trip", control_ob_set_get_round_trip },
    { "control_ob_stringify", control_ob_stringify },
};

} // namespace

int main(int argc, char **argv) {
    gCall4D = engine;
    if(argc == 2 && !strcmp(argv[1], "--list")) {
        for(const Test &t : kTests) printf("%s\n", t.name);
        return 0;
    }
    if(argc != 2) { fprintf(stderr, "usage: %s --list | <test>\n", argv[0]); return 2; }
    for(const Test &t : kTests) {
        if(!strcmp(argv[1], t.name)) {
            bool ok = t.fn();
            printf("%s: %s\n", t.name, ok ? "PASS" : "FAIL");
            return ok ? 0 : 1;
        }
    }
    fprintf(stderr, "unknown test %s\n", argv[1]);
    return 2;
}
