![version](https://img.shields.io/badge/version-17%2B-3E8B93)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm%20|%20win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-twain-v2)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-twain-v2/total)

# 4d-plugin-twain-v2

The TWAIN plugin drives image scanners from 4D through the TWAIN protocol. On Windows it uses the TWAIN 2.x Data Source Manager ([twain-dsm](https://github.com/twain/twain-dsm)), which is linked into the plugin. On macOS it uses Apple's legacy `TWAIN.framework`. You can list the installed scanner drivers, read a scanner's current settings and the values it allows, and scan one or more pages. Each page comes back to 4D as a `Picture` encoded as JPEG or PNG.

> **This reference describes the plugin built from the patched source** (the "safe fixes" set on top of `miyako/4d-plugin-twain-v2` @ `b126412`). Wherever the behavior of an older binary differs, the difference is marked **Changed by the fix**. If you are running an unpatched build, see [Behavior of unpatched builds](#behavior-of-unpatched-builds).

| Command | Returns | Purpose |
|---|---|---|
| [`TWAIN Get devices`](#twain-get-devices) | `Collection` | Lists the TWAIN data sources (scanner drivers) installed on this machine |
| [`TWAIN Get default option`](#twain-get-default-option) | `Object` | Reads a scanner's current capability values and the values it allows |
| [`TWAIN Scan`](#twain-scan) | `Collection` | Scans and returns one `Picture` per page |

**Platforms:** Windows 64-bit (fully functional). macOS Intel / Apple Silicon (listing devices only, see below).

---

## Requirements & platform notes

- **Windows needs a 64-bit TWAIN driver.** 4D is a 64-bit application, so only 64-bit TWAIN data sources are visible to it. These are installed by the scanner vendor under `%SystemRoot%\twain_64`. Many scanners still ship 32-bit-only TWAIN drivers, and those never appear in [`TWAIN Get devices`](#twain-get-devices). WIA-only or "ISIS-only" drivers aren't TWAIN, so they aren't listed either.
- **On macOS, only [`TWAIN Get devices`](#twain-get-devices) works in this build.** The macOS code path relies on Apple's `TWAIN.framework` (TWAIN 1.9) and data sources in `/Library/Image Capture/TWAIN Data Sources`. The plugin's memory-handle helpers aren't implemented for macOS, so:
  - [`TWAIN Get default option`](#twain-get-default-option) returns empty `option`/`values` objects.
  - [`TWAIN Scan`](#twain-scan) returns an empty collection and applies no options.

  Check separately whether your macOS version still ships `TWAIN.framework` and whether your scanner vendor provides a macOS TWAIN data source at all.
- **No scanner dialog is shown.** The plugin always enables the scanner with its user interface hidden (`ShowUI = false`). Every setting comes from the scanner's current defaults plus whatever you pass in the [`TWAIN Scan`](#twain-scan) options object.
- **Failure is silent, not a 4D error.** No command raises a 4D error or sets `OK`. When something fails, you get an empty collection or empty objects (see [Error handling & troubleshooting](#error-handling--troubleshooting)). Always test `.length`.
- **One TWAIN call at a time per 4D application.** All three commands are declared thread-safe, so you can call them from preemptive processes and workers. They are serialized internally: if a TWAIN call is already running in another process, the new call returns an empty result **immediately** instead of waiting. **Changed by the fix**: previously, concurrent calls could interfere with each other or hang.
- **Calls block the calling process, but not 4D.** [`TWAIN Scan`](#twain-scan) can take many seconds (lamp warm-up, paper feed, encoding). While it runs, the calling process waits and other 4D processes keep running.
  - **On Windows**, the scan and option-reading run on a separate thread, and the 4D process yields while it waits.
  - **On macOS**, the work runs in the calling process with periodic yields.

  For a responsive UI, call the commands from a worker (`CALL WORKER`) and send the result back to the form.
- **Parameters:** every parameter in the syntax below is declared in the plugin's manifest. Pass all of them; there's no shorter form.

---

## TWAIN Get devices

### Syntax

```
TWAIN Get devices → Collection
```

| Parameter | Type | Description |
|---|---|---|
| Result | `Collection` | One object per installed TWAIN data source; empty if none were found or TWAIN could not be opened |

### Description

`TWAIN Get devices` opens the TWAIN Data Source Manager and enumerates every data source it knows about. It does not open the scanners themselves, so it is fast and doesn't wake the devices.

Each element of the result is an object:

| Property | Type | Description |
|---|---|---|
| `manufacturer` | `Text` | Driver's manufacturer name |
| `productFamily` | `Text` | Driver's product family |
| `productName` | `Text` | Driver's product name. **This is the value you pass as `scanner` to the other two commands.** |
| `protocolMajor` | `Integer` | TWAIN protocol major version the driver implements |
| `protocolMinor` | `Integer` | TWAIN protocol minor version |
| `supportedGroups` | `Integer` | TWAIN `DG_*`/`DF_*` bit flags the driver reports |
| `version` | `Object` | Driver version: `info` (`Text`), `majorNum`, `minorNum`, `language`, `country` (all `Integer`) |

The collection is empty in any of these cases:
- No TWAIN data source is installed for the platform and bitness.
- The Data Source Manager could not be opened.
- Another TWAIN call is in progress.

Driver names are copied as raw bytes. A driver that reports a non-ASCII name in a legacy code page (rather than UTF-8) may show up with garbled characters, and such a name may then fail to match in the other commands (see troubleshooting).

### Example

From the plugin's own test method (`TEST.4dm`):

```4d
$devices:=TWAIN Get devices 
```

List the installed scanners:

```4d
C_COLLECTION($devices)
C_OBJECT($device)

$devices:=TWAIN Get devices

If ($devices.length=0)
	ALERT("No 64-bit TWAIN scanner driver found.")
Else 
	For each ($device;$devices)
		ALERT($device.productName+" — "+$device.manufacturer)
	End for each 
End if 
```

Pick a scanner by name:

```4d
C_COLLECTION($devices;$found)
C_TEXT($scanner)

$devices:=TWAIN Get devices
$found:=$devices.query("productName = :1";"fi-7160")
If ($found.length>0)
	$scanner:=$found[0].productName
End if 
```

---

## TWAIN Get default option

### Syntax

```
TWAIN Get default option ( scanner ) → Object
```

| Parameter | Type | Description |
|---|---|---|
| `scanner` | `Text` | `productName` of a data source as returned by [`TWAIN Get devices`](#twain-get-devices). Pass `""` for the system default scanner. |
| Result | `Object` | `{ option : Object ; values : Object }`. Both are empty if the scanner could not be opened. |

### Description

`TWAIN Get default option` opens the scanner and asks it which capabilities it supports (`CAP_SUPPORTEDCAPS`). It then reads each supported capability. Nothing is scanned and no settings are changed.

**Scanner selection:** `scanner` is compared exactly (case- and byte-sensitive) with each driver's `productName`. If there's no exact match, including when you pass `""`, the TWAIN system default source is used instead. A misspelled name therefore silently reads the *default* scanner, not nothing.

The result has two properties, both keyed by TWAIN capability name (`"ICAP_PIXELTYPE"`, `"ICAP_XRESOLUTION"`, `"CAP_FEEDERENABLED"`, …):

**`option`**: the current value of each capability:

| Capability data type | Value in `option` |
|---|---|
| Enumerated constant the plugin knows (e.g. pixel type, units, transfer mechanism) | `Text`: the TWAIN constant name, e.g. `"TWPT_RGB"` |
| Integer | `Integer` |
| Fixed-point (`TW_FIX32`, e.g. resolution, brightness) in a single-value or enumeration container | `Real`, e.g. `300` |
| Value in a **range** container | `Integer`: the raw value. For fixed-point ranges this is the 16.16 fixed-point encoding, e.g. `19660800` for 300 dpi (= 300 × 65536). |
| Boolean | `Integer` `0`/`1` (but `True`/`False` inside a `values` list) |
| String (`TW_STR32`…`TW_STR255`) | `Text` |
| Frame (`TW_FRAME`) | `Text` such as `"0.0,0.0,8.32768,11.45875"` (top, left, right, bottom as whole.fraction) |

**`values`**: what each capability allows, as an object with:

| Property | Present when | Description |
|---|---|---|
| `itemType` | always | The TWAIN **container** type: `"TWON_ONEVALUE"`, `"TWON_ENUMERATION"`, `"TWON_RANGE"` or `"TWON_ARRAY"` |
| `values` | enumeration, array | `Collection` of allowed values, using the same encoding as `option` |
| `minValue`, `maxValue`, `stepSize`, `defaultValue` | range | `Integer`, raw (fixed-point ranges in 16.16 encoding, as above) |

Use `values` to find out what a given scanner accepts before you build a [`TWAIN Scan`](#twain-scan) options object.

**Changed by the fix:**
- The current value of enumeration capabilities used to be read from the wrong position, so it was frequently wrong.
- Boolean lists were read with the wrong item size.
- String lists could read past the end of the driver's data.

### Example

From the plugin's own test method (`TEST.4dm`):

```4d
$option:=TWAIN Get default option 
```

(The test method calls it without an argument. The command's syntax declares one `Text` parameter, so pass `""` explicitly for the default scanner.)

Read the current pixel type and the allowed choices:

```4d
C_OBJECT($defaults)
C_TEXT($current)
C_COLLECTION($choices)

$defaults:=TWAIN Get default option("")

If (OB Is defined($defaults.option;"ICAP_PIXELTYPE"))
	$current:=$defaults.option.ICAP_PIXELTYPE  // e.g. "TWPT_RGB"
	$choices:=$defaults.values.ICAP_PIXELTYPE.values  // e.g. ["TWPT_BW","TWPT_GRAY","TWPT_RGB"]
End if 
```

Convert a fixed-point resolution range to dpi:

```4d
C_OBJECT($defaults;$range)
C_REAL($minDpi;$maxDpi)

$defaults:=TWAIN Get default option("")
$range:=$defaults.values.ICAP_XRESOLUTION

If ($range#Null)
	If ($range.itemType="TWON_RANGE")
		$minDpi:=$range.minValue/65536
		$maxDpi:=$range.maxValue/65536
	End if 
End if 
```

---

## TWAIN Scan

### Syntax

```
TWAIN Scan ( scanner ; options ; format ) → Collection
```

| Parameter | Type | Description |
|---|---|---|
| `scanner` | `Text` | `productName` from [`TWAIN Get devices`](#twain-get-devices), or `""` for the system default scanner. Same matching rules as [`TWAIN Get default option`](#twain-get-default-option). |
| `options` | `Object` | Capability settings to apply before scanning, as `{ "CAPABILITY_NAME" : value ; … }`. Pass `New object` (or `Null`) to scan with the scanner's current settings. |
| `format` | `Integer` | `Scanner image type PNG` (`2`) for PNG; `Scanner image type JPEG` (`0`) or **any other value** for JPEG |
| Result | `Collection` | One `Picture` per scanned page, in transfer order; empty on failure, cancellation, timeout, or if another TWAIN call is in progress |

### Description

`TWAIN Scan` runs these steps:
1. Opens the scanner.
2. Applies each entry of `options`.
3. Enables the scanner without its dialog.
4. Waits up to **30 seconds** for the scanner to report that an image is ready.
5. Transfers every pending page using TWAIN *memory transfer*.
6. Encodes each page as JPEG or PNG.

**The options object.** The object is flat. Each key is a TWAIN capability name, and each value is one of:
- **a TWAIN constant name** as `Text`, for enumerated capabilities: `"ICAP_PIXELTYPE":"TWPT_GRAY"`, `"ICAP_XFERMECH":"TWSX_MEMORY"`, `"ICAP_UNITS":"TWUN_INCHES"`. The accepted names are listed in [Options reference](#options-reference).
- **a number**, for integer or fixed-point capabilities: `"ICAP_XRESOLUTION":300`, `"ICAP_BRIGHTNESS":-200`, `"CAP_XFERCOUNT":-1`.
- **a boolean** (or `0`/`1`), for boolean capabilities: `"CAP_FEEDERENABLED":True`.

How the options are applied:
- **Options are applied in alphabetical key order**, not in the order you write them. All `CAP_*` keys are applied before `ICAP_*` keys, `ICAP_BITDEPTH` before `ICAP_PIXELTYPE`, `ICAP_UNITS` before `ICAP_XRESOLUTION`, and so on. TWAIN drivers sometimes reset one capability when another changes (e.g. changing pixel type resets bit depth). If a setting doesn't stick, that ordering is the likely reason.
- **Each setting is sent as a single value.** Only numeric, fixed-point and boolean capabilities can be set. String and frame capabilities (`CAP_AUTHOR`, `ICAP_FRAMES`, …) are ignored.
- **Unknown keys are ignored.** That includes a misspelled capability name and the `option`/`values` wrapper keys returned by [`TWAIN Get default option`](#twain-get-default-option).
- **A misspelled constant name becomes `0`.** For example, `"ICAP_PIXELTYPE":"TWPT_RGBB"` sets pixel type 0 (`TWPT_BW`).
- **A rejected setting is silent.** If the driver refuses a value, the scan proceeds with whatever the driver kept.

**Changed by the fix:**
- On Windows, the options object used to be lost before it reached the scanner, so options had no effect at all.
- Enumeration and range capabilities used to be sent as malformed containers.

**Transfer and image formats.** Pages are transferred uncompressed (memory transfer) and encoded by the plugin:

| Scanner pixel type | JPEG | PNG |
|---|---|---|
| `TWPT_BW` (1 bit) | 8-bit grayscale | 1-bit grayscale |
| `TWPT_GRAY` 8-bit | 8-bit grayscale | 8-bit grayscale |
| `TWPT_GRAY` 16-bit | not usable (JPEG expects 8-bit samples) | 16-bit grayscale |
| `TWPT_RGB` 24-bit | 24-bit color | 24-bit color |
| `TWPT_RGB` 48-bit | not usable | 48-bit color |
| `TWPT_PALETTE`, `TWPT_CMY`, `TWPT_CMYK`, others | page skipped | page skipped |

- **JPEG** is written at quality 100, progressive, with the scan resolution stored as JFIF density. Pages taller or wider than 65,500 pixels are skipped (libjpeg's limit; relevant to long-document feeders at high resolution).
- **PNG** stores the resolution in a `pHYs` chunk.
- Because pages are transferred uncompressed, don't set `ICAP_COMPRESSION` to anything other than `"TWCP_NONE"`.
- **Changed by the fix:**
  - PNG used to return no pages at all.
  - Multi-page scans used to return only the last page.
  - Unsupported pixel types used to be passed to the JPEG encoder and could crash 4D.
  - Any encoder error used to crash 4D; now it skips the page.

**Memory transfer mode.** TWAIN expects an application to select memory transfer with `"ICAP_XFERMECH":"TWSX_MEMORY"`. The plugin doesn't set it for you. Many drivers transfer correctly without it, but if scans come back empty, add it to `options`.

**Multiple pages.** To scan a whole feeder, enable it and request all pages, e.g. `"CAP_FEEDERENABLED":True` and `"CAP_XFERCOUNT":-1`. All pages are held in memory until the command returns, so a long batch at high resolution can use a lot of memory.

**When nothing comes back.** The command returns an empty collection, or only the pages completed so far, if any of the following happens:
- The scanner doesn't become ready within 30 seconds.
- The driver reports a cancel or failure mid-transfer (paper jam, double feed).
- The scanner cannot be opened.

After such an abort the plugin resets the driver's pending transfers so the scanner can be used again. **Changed by the fix**: a mid-transfer cancel or failure used to hang the 4D process, and an aborted transfer could leave the driver open until 4D restarted.

### Example

From the plugin's own test method (`TEST.4dm`):

```4d
$images:=TWAIN Scan ("";$option;Scanner image type PNG)
```

Here `$option` is the whole result of [`TWAIN Get default option`](#twain-get-default-option). Its top-level keys are `option` and `values`, which aren't capability names, so no settings are applied and the scan uses the scanner's current settings. To re-apply the reported values explicitly, pass `$option.option` instead.

Scan one color page at 300 dpi and save it:

```4d
C_OBJECT($options)
C_COLLECTION($images)
C_PICTURE($page)

$options:=New object(\
"ICAP_XFERMECH";"TWSX_MEMORY";\
"ICAP_PIXELTYPE";"TWPT_RGB";\
"ICAP_XRESOLUTION";300;\
"ICAP_YRESOLUTION";300)

$images:=TWAIN Scan("";$options;Scanner image type JPEG)

If ($images.length>0)
	$page:=$images[0]
	WRITE PICTURE FILE(System folder(Desktop)+"scan.jpg";$page;".jpg")
End if 
```

Scan every page in the document feeder, both sides, in grayscale PNG:

```4d
C_OBJECT($options)
C_COLLECTION($images)
C_LONGINT($i)

$options:=New object(\
"ICAP_XFERMECH";"TWSX_MEMORY";\
"CAP_FEEDERENABLED";True;\
"CAP_DUPLEXENABLED";True;\
"CAP_XFERCOUNT";-1;\
"ICAP_PIXELTYPE";"TWPT_GRAY";\
"ICAP_XRESOLUTION";200;\
"ICAP_YRESOLUTION";200)

$images:=TWAIN Scan("fi-7160";$options;Scanner image type PNG)

For ($i;0;$images.length-1)
	WRITE PICTURE FILE(System folder(Desktop)+"page_"+String($i+1)+".png";$images[$i];".png")
End for 
```

Scan in a worker so the form stays responsive. This project method runs in the worker:

```4d
// SCAN_IN_WORKER ($scanner : Text; $window : Integer)
C_TEXT($1)
C_LONGINT($2)
C_COLLECTION($images)

$images:=TWAIN Scan($1;New object("ICAP_XFERMECH";"TWSX_MEMORY");Scanner image type JPEG)
CALL FORM($2;"SCAN_DONE";$images)
```

```4d
CALL WORKER("twain";"SCAN_IN_WORKER";"";Current form window)
```

(`SCAN_DONE` is your own form-side method that receives the collection.)

---

## Options reference

### Capability names

The plugin recognizes the following keys in the `options` object of [`TWAIN Scan`](#twain-scan). Which ones a given scanner supports, and with which values, depends on the driver: check with [`TWAIN Get default option`](#twain-get-default-option). Only capabilities whose values are numeric, fixed-point or boolean can actually be set (see [`TWAIN Scan`](#twain-scan)).

**Image (`ICAP_*`):**
`ICAP_AUTOBRIGHT` `ICAP_AUTODISCARDBLANKPAGES` `ICAP_AUTOMATICBORDERDETECTION` `ICAP_AUTOMATICCOLORENABLED` `ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE` `ICAP_AUTOMATICCROPUSESFRAME` `ICAP_AUTOMATICDESKEW` `ICAP_AUTOMATICLENGTHDETECTION` `ICAP_AUTOMATICROTATE` `ICAP_AUTOSIZE` `ICAP_BARCODEDETECTIONENABLED` `ICAP_BARCODEMAXRETRIES` `ICAP_BARCODEMAXSEARCHPRIORITIES` `ICAP_BARCODESEARCHMODE` `ICAP_BARCODESEARCHPRIORITIES` `ICAP_BARCODETIMEOUT` `ICAP_BITDEPTH` `ICAP_BITDEPTHREDUCTION` `ICAP_BITORDER` `ICAP_BITORDERCODES` `ICAP_BRIGHTNESS` `ICAP_CCITTKFACTOR` `ICAP_COLORMANAGEMENTENABLED` `ICAP_COMPRESSION` `ICAP_CONTRAST` `ICAP_CUSTHALFTONE` `ICAP_EXPOSURETIME` `ICAP_EXTIMAGEINFO` `ICAP_FEEDERTYPE` `ICAP_FILMTYPE` `ICAP_FILTER` `ICAP_FLASHUSED` `ICAP_FLASHUSED2` `ICAP_FLIPROTATION` `ICAP_FRAMES` `ICAP_GAMMA` `ICAP_HALFTONES` `ICAP_HIGHLIGHT` `ICAP_ICCPROFILE` `ICAP_IMAGEDATASET` `ICAP_IMAGEFILEFORMAT` `ICAP_IMAGEFILTER` `ICAP_IMAGEMERGE` `ICAP_IMAGEMERGEHEIGHTTHRESHOLD` `ICAP_JPEGPIXELTYPE` `ICAP_JPEGQUALITY` `ICAP_JPEGSUBSAMPLING` `ICAP_LAMPSTATE` `ICAP_LIGHTPATH` `ICAP_LIGHTSOURCE` `ICAP_MAXFRAMES` `ICAP_MINIMUMHEIGHT` `ICAP_MINIMUMWIDTH` `ICAP_MIRROR` `ICAP_NOISEFILTER` `ICAP_ORIENTATION` `ICAP_OVERSCAN` `ICAP_PATCHCODEDETECTIONENABLED` `ICAP_PATCHCODEMAXRETRIES` `ICAP_PATCHCODEMAXSEARCHPRIORITIES` `ICAP_PATCHCODESEARCHMODE` `ICAP_PATCHCODESEARCHPRIORITIES` `ICAP_PATCHCODETIMEOUT` `ICAP_PHYSICALHEIGHT` `ICAP_PHYSICALWIDTH` `ICAP_PIXELFLAVOR` `ICAP_PIXELFLAVORCODES` `ICAP_PIXELTYPE` `ICAP_PLANARCHUNKY` `ICAP_ROTATION` `ICAP_SHADOW` `ICAP_SUPPORTEDBARCODETYPES` `ICAP_SUPPORTEDEXTIMAGEINFO` `ICAP_SUPPORTEDPATCHCODETYPES` `ICAP_SUPPORTEDSIZES` `ICAP_THRESHOLD` `ICAP_TILES` `ICAP_TIMEFILL` `ICAP_UNDEFINEDIMAGESIZE` `ICAP_UNITS` `ICAP_XFERMECH` `ICAP_XNATIVERESOLUTION` `ICAP_XRESOLUTION` `ICAP_XSCALING` `ICAP_YNATIVERESOLUTION` `ICAP_YRESOLUTION` `ICAP_YSCALING` `ICAP_ZOOMFACTOR`

**General (`CAP_*`):**
`CAP_ALARMS` `CAP_ALARMVOLUME` `CAP_AUTHOR` `CAP_AUTOFEED` `CAP_AUTOMATICCAPTURE` `CAP_AUTOMATICSENSEMEDIUM` `CAP_AUTOSCAN` `CAP_BATTERYMINUTES` `CAP_BATTERYPERCENTAGE` `CAP_CAMERAENABLED` `CAP_CAMERAORDER` `CAP_CAMERAPREVIEWUI` `CAP_CAMERASIDE` `CAP_CAPTION` `CAP_CLEARBUFFERS` `CAP_CLEARPAGE` `CAP_CUSTOMDSDATA` `CAP_CUSTOMINTERFACEGUID` `CAP_DEVICEEVENT` `CAP_DEVICEONLINE` `CAP_DEVICETIMEDATE` `CAP_DOUBLEFEEDDETECTION` `CAP_DOUBLEFEEDDETECTIONLENGTH` `CAP_DOUBLEFEEDDETECTIONRESPONSE` `CAP_DOUBLEFEEDDETECTIONSENSITIVITY` `CAP_DUPLEX` `CAP_DUPLEXENABLED` `CAP_ENABLEDSUIONLY` `CAP_ENDORSER` `CAP_EXTENDEDCAPS` `CAP_FEEDERALIGNMENT` `CAP_FEEDERENABLED` `CAP_FEEDERLOADED` `CAP_FEEDERORDER` `CAP_FEEDERPOCKET` `CAP_FEEDERPREP` `CAP_FEEDPAGE` `CAP_INDICATORS` `CAP_INDICATORSMODE` `CAP_JOBCONTROL` `CAP_LANGUAGE` `CAP_MAXBATCHBUFFERS` `CAP_MICRENABLED` `CAP_PAPERDETECTABLE` `CAP_PAPERHANDLING` `CAP_POWERSAVETIME` `CAP_POWERSUPPLY` `CAP_PRINTER` `CAP_PRINTERCHARROTATION` `CAP_PRINTERENABLED` `CAP_PRINTERFONTSTYLE` `CAP_PRINTERINDEX` `CAP_PRINTERINDEXLEADCHAR` `CAP_PRINTERINDEXMAXVALUE` `CAP_PRINTERINDEXNUMDIGITS` `CAP_PRINTERINDEXSTEP` `CAP_PRINTERINDEXTRIGGER` `CAP_PRINTERMODE` `CAP_PRINTERSTRING` `CAP_PRINTERSTRINGPREVIEW` `CAP_PRINTERSUFFIX` `CAP_PRINTERVERTICALOFFSET` `CAP_REACQUIREALLOWED` `CAP_REWINDPAGE` `CAP_SEGMENTED` `CAP_SERIALNUMBER` `CAP_SUPPORTEDCAPS` `CAP_SUPPORTEDCAPSEXT` `CAP_SUPPORTEDCAPSSEGMENTUNIQUE` `CAP_SUPPORTEDDATS` `CAP_THUMBNAILSENABLED` `CAP_TIMEBEFOREFIRSTCAPTURE` `CAP_TIMEBETWEENCAPTURES` `CAP_TIMEDATE` `CAP_UICONTROLLABLE` `CAP_XFERCOUNT`

Read-only capabilities (e.g. `CAP_SUPPORTEDCAPS`, `CAP_FEEDERLOADED`, `ICAP_PHYSICALWIDTH`) are recognized but have no effect when set.

### Constant names

For these capabilities, you can pass a TWAIN constant name as `Text` instead of its number. Any other text is treated as `0`.

| Capability | Accepted constant names |
|---|---|
| `ICAP_PIXELTYPE` | `TWPT_BW` `TWPT_GRAY` `TWPT_RGB` `TWPT_PALETTE` `TWPT_CMY` `TWPT_CMYK` `TWPT_YUV` `TWPT_YUVK` `TWPT_CIEXYZ` |
| `ICAP_XFERMECH` | `TWSX_NATIVE` `TWSX_FILE` `TWSX_MEMORY` |
| `ICAP_UNITS` | `TWUN_INCHES` `TWUN_CENTIMETERS` `TWUN_PICAS` `TWUN_POINTS` `TWUN_TWIPS` `TWUN_PIXELS` |
| `ICAP_COMPRESSION` | `TWCP_NONE` `TWCP_PACKBITS` `TWCP_GROUP31D` `TWCP_GROUP31DEOL` `TWCP_GROUP32D` `TWCP_GROUP4` `TWCP_JPEG` `TWCP_LZW` `TWCP_JBIG` `TWCP_PNG` `TWCP_RLE4` `TWCP_RLE8` `TWCP_BITFIELDS` |
| `ICAP_SUPPORTEDSIZES` | `TWSS_NONE` `TWSS_A4` `TWSS_A5` `TWSS_A3` `TWSS_USLETTER` `TWSS_USLEGAL` `TWSS_JISB5` `TWSS_JISB4` `TWSS_BUSINESSCARD` … (all `TWSS_*` sizes from the TWAIN 2.x specification) |
| `ICAP_ORIENTATION` | `TWOR_ROT0` `TWOR_ROT90` `TWOR_ROT180` `TWOR_ROT270` `TWOR_PORTRAIT` `TWOR_LANDSCAPE` |
| `ICAP_PIXELFLAVOR` | `TWPF_CHOCOLATE` `TWPF_VANILLA` |
| `ICAP_BITDEPTHREDUCTION` | `TWBR_THRESHOLD` `TWBR_HALFTONE` `TWBR_CUSTHALFTONE` `TWBR_DIFFUSION` |
| `ICAP_BITORDER` | `TWBO_LSBFIRST` `TWBO_MSBFIRST` |
| `ICAP_PLANARCHUNKY` | `TWPC_CHUNKY` `TWPC_PLANAR` |
| `ICAP_LIGHTPATH` | `TWLP_REFLECTIVE` `TWLP_TRANSMISSIVE` |
| `ICAP_LIGHTSOURCE` | `TWLS_RED` `TWLS_GREEN` `TWLS_BLUE` `TWLS_NONE` `TWLS_WHITE` `TWLS_UV` `TWLS_IR` |
| `ICAP_FILTER` | `TWFT_RED` `TWFT_GREEN` `TWFT_BLUE` `TWFT_NONE` `TWFT_WHITE` `TWFT_CYAN` `TWFT_MAGENTA` `TWFT_YELLOW` `TWFT_BLACK` |
| `ICAP_IMAGEFILTER` | `TWIF_NONE` `TWIF_AUTO` `TWIF_LOWPASS` `TWIF_BANDPASS` `TWIF_HIGHPASS` `TWIF_TEXT` `TWIF_FINELINE` |
| `ICAP_NOISEFILTER` | `TWNF_NONE` `TWNF_AUTO` `TWNF_LONEPIXEL` `TWNF_MAJORITYRULE` |
| `ICAP_OVERSCAN` | `TWOV_NONE` `TWOV_AUTO` `TWOV_TOPBOTTOM` `TWOV_LEFTRIGHT` `TWOV_ALL` |
| `ICAP_AUTOSIZE` | `TWAS_NONE` `TWAS_AUTO` `TWAS_CURRENT` |
| `ICAP_AUTODISCARDBLANKPAGES` | `TWBP_DISABLE` `TWBP_AUTO` |
| `ICAP_FEEDERTYPE` | `TWFE_GENERAL` `TWFE_PHOTO` |
| `ICAP_FLIPROTATION` | `TWFR_BOOK` `TWFR_FANFOLD` |
| `ICAP_FLASHUSED2` | `TWFL_NONE` `TWFL_OFF` `TWFL_ON` `TWFL_AUTO` `TWFL_REDEYE` |
| `ICAP_ICCPROFILE` | `TWIC_NONE` `TWIC_LINK` `TWIC_EMBED` |
| `ICAP_IMAGEFILEFORMAT` | `TWFF_TIFF` `TWFF_PICT` `TWFF_BMP` `TWFF_XBM` `TWFF_JFIF` `TWFF_FPX` `TWFF_TIFFMULTI` `TWFF_PNG` `TWFF_SPIFF` `TWFF_EXIF` `TWFF_PDF` `TWFF_JP2` `TWFF_JPN` `TWFF_JPX` `TWFF_DEJAVU` `TWFF_PDFA` `TWFF_PDFA2` |
| `ICAP_IMAGEMERGE` | `TWIM_NONE` `TWIM_FRONTONTOP` `TWIM_FRONTONBOTTOM` `TWIM_FRONTONLEFT` `TWIM_FRONTONRIGHT` |
| `ICAP_JPEGQUALITY` | `TWJQ_UNKNOWN` `TWJQ_LOW` `TWJQ_MEDIUM` `TWJQ_HIGH` (or a number 0–100) |
| `ICAP_BARCODESEARCHMODE` | `TWBD_HORZ` `TWBD_VERT` `TWBD_HORZVERT` `TWBD_VERTHORZ` |
| `CAP_DUPLEX` | `TWDX_NONE` `TWDX_1PASSDUPLEX` `TWDX_2PASSDUPLEX` |
| `CAP_CAMERASIDE` | `TWCS_BOTH` `TWCS_TOP` `TWCS_BOTTOM` |
| `CAP_FEEDERALIGNMENT` | `TWFA_NONE` `TWFA_LEFT` `TWFA_CENTER` `TWFA_RIGHT` |
| `CAP_FEEDERORDER` | `TWFO_FIRSTPAGEFIRST` `TWFO_LASTPAGEFIRST` |
| `CAP_FEEDERPOCKET` | `TWFP_POCKETERROR` `TWFP_POCKET1` … `TWFP_POCKET16` |
| `CAP_SEGMENTED` | `TWSG_NONE` `TWSG_AUTO` `TWSG_MANUAL` |
| `CAP_CLEARBUFFERS` | `TWCB_AUTO` `TWCB_CLEAR` `TWCB_NOCLEAR` |
| `CAP_JOBCONTROL` | `TWJC_NONE` `TWJC_JSIC` `TWJC_JSIS` `TWJC_JSXC` `TWJC_JSXS` |
| `CAP_POWERSUPPLY` | `TWPS_EXTERNAL` `TWPS_BATTERY` |
| `CAP_PRINTER` | `TWPR_IMPRINTERTOPBEFORE` `TWPR_IMPRINTERTOPAFTER` `TWPR_IMPRINTERBOTTOMBEFORE` `TWPR_IMPRINTERBOTTOMAFTER` `TWPR_ENDORSERTOPBEFORE` `TWPR_ENDORSERTOPAFTER` `TWPR_ENDORSERBOTTOMBEFORE` `TWPR_ENDORSERBOTTOMAFTER` |
| `CAP_PRINTERMODE` | `TWPM_SINGLESTRING` `TWPM_MULTISTRING` `TWPM_COMPOUNDSTRING` |
| `CAP_ALARMS` | `TWAL_ALARM` `TWAL_FEEDERERROR` `TWAL_FEEDERWARNING` `TWAL_BARCODE` `TWAL_DOUBLEFEED` `TWAL_JAM` `TWAL_PATCHCODE` `TWAL_POWER` `TWAL_SKEW` |
| `CAP_DEVICEEVENT` | `TWDE_*` event names from the TWAIN specification |

The constant names for `ICAP_AUTOSIZE`, `ICAP_AUTODISCARDBLANKPAGES`, `ICAP_FEEDERTYPE`, `ICAP_ICCPROFILE`, `ICAP_IMAGEMERGE`, `CAP_CAMERASIDE`, `CAP_FEEDERPOCKET` and `CAP_SEGMENTED` (TWAIN 2.x additions) are only recognized in the Windows build.

---

## Error handling & troubleshooting

- **Empty collection from `TWAIN Get devices` on Windows.** No 64-bit TWAIN driver is installed. Install the vendor's 64-bit TWAIN driver; WIA, ISIS and 32-bit TWAIN drivers are invisible to 64-bit 4D.
- **Scanner name typo selects a different scanner.** `scanner` must equal `productName` exactly. Anything else, including `""`, falls back to the TWAIN default source. Build the name from [`TWAIN Get devices`](#twain-get-devices) instead of typing it.
- **Non-ASCII scanner names don't match.** If a driver reports its name in a legacy code page, the text you get back may not round-trip, and the command falls back to the default source. Pass `""` if that scanner is the default, or make it the default in the vendor's tools.
- **Empty result while another scan is running.** TWAIN calls are serialized per 4D application. A call made while another is in progress returns empty at once. Retry later, or funnel all scanning through a single worker.
- **`TWAIN Scan` returns an empty collection.** Check, in order:
  1. Is the scanner on, connected and loaded with paper?
  2. Does it become ready within 30 seconds? Long lamp warm-up can exceed this.
  3. Add `"ICAP_XFERMECH":"TWSX_MEMORY"`.
  4. Make sure `ICAP_COMPRESSION` is `"TWCP_NONE"`.
  5. Make sure the pixel type is BW, gray or RGB.
- **Some pages are missing.** A page is skipped (not returned) if its pixel type can't be encoded, if it is larger than 65,500 pixels in either direction for JPEG, or if the encoder fails. A 16-bit gray or 48-bit color page encoded as JPEG comes out unusable. Use PNG for those, or set `ICAP_BITDEPTH` to `8`.
- **A setting has no effect.** Settings are applied in alphabetical key order, and the driver may reset one capability when another changes. Driver rejections are silent. Verify with [`TWAIN Get default option`](#twain-get-default-option) which values the driver allows, and check spelling: an unknown key is ignored, and an unknown constant name becomes `0`.
- **Black-and-white pages are inverted.** For 1-bit pages, the JPEG encoder treats a set bit as black and the PNG encoder treats it as white. If pages come out inverted in one format, switch format or set `ICAP_PIXELFLAVOR` (`"TWPF_CHOCOLATE"` / `"TWPF_VANILLA"`).
- **Resolution looks like a huge number.** Values reported in a range container are raw 16.16 fixed-point integers. Divide by 65536 (e.g. `19660800` → 300 dpi). Values you *pass* in `options` are plain numbers (`300`).
- **Nothing works on macOS beyond listing devices.** This build doesn't implement the macOS memory-handle helpers, so options can't be read or set and no image can be transferred. See [Requirements & platform notes](#requirements--platform-notes).
- **Memory use on large batches.** All pages are kept in memory (raw scan plus encoded copies) until the command returns. For large feeder batches at high resolution, scan in smaller batches (`CAP_XFERCOUNT`) or at lower resolution.

---

## Behavior of unpatched builds

If you are running a binary built from `4d-plugin-twain-v2` @ `b126412` or earlier without the fixes, expect these differences:

- **On Windows**, the `options` object of [`TWAIN Scan`](#twain-scan) has no effect.
- `Scanner image type PNG` returns an empty collection.
- Multi-page scans return only the last page.
- A cancel, paper jam or driver error during transfer can hang the calling 4D process.
- An aborted transfer can leave the scanner unusable until 4D restarts.
- Concurrent TWAIN calls can interfere with each other or hang.
- **On macOS**, [`TWAIN Get default option`](#twain-get-default-option), and [`TWAIN Scan`](#twain-scan) with options, can crash 4D.
- Some pixel types and very large pages can crash 4D during JPEG encoding.

---

## Quick reference

```4d
C_COLLECTION($devices;$images)
C_OBJECT($defaults;$options)
C_TEXT($scanner)

$devices:=TWAIN Get devices
$scanner:=Choose($devices.length>0;$devices[0].productName;"")

$defaults:=TWAIN Get default option($scanner)
// $defaults.option.ICAP_PIXELTYPE     current value
// $defaults.values.ICAP_PIXELTYPE     allowed values

$options:=New object(\
"ICAP_XFERMECH";"TWSX_MEMORY";\
"ICAP_PIXELTYPE";"TWPT_RGB";\
"ICAP_XRESOLUTION";300;"ICAP_YRESOLUTION";300;\
"CAP_FEEDERENABLED";True;"CAP_XFERCOUNT";-1)

$images:=TWAIN Scan($scanner;$options;Scanner image type JPEG)  // or Scanner image type PNG
// $images[0], $images[1], … : Picture, one per page; empty collection on failure
```

---

## Building from source

[jsoncpp](https://github.com/open-source-parsers/jsoncpp) is built from source (git submodule `deps/jsoncpp`, pinned to `1.9.8`) so its headers and static libraries always match. Clone with submodules:

```sh
git clone --recurse-submodules https://github.com/miyako/4d-plugin-twain-v2.git
# or, in an existing clone
git submodule update --init
```

Both projects build jsoncpp automatically on first build if the library is missing (requires CMake):

- **macOS**: `./build-jsoncpp.sh` → `a/libjsoncpp.a` (universal arm64 + x86_64, static).
- **Windows**: `build-jsoncpp.bat [Release|Debug]` → `lib\windows64\jsoncpp.lib` (x64, `/MT`) or `lib\windows64\debug\jsoncpp.lib` (`/MTd`).

After updating the submodule, re-run the script (or delete the built library) to rebuild.
