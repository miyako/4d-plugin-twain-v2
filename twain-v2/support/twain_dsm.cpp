#include "twain_dsm.h"

void twain_get_option_value_name(TW_UINT16 cap, TW_INT32 item, Json::Value& value) {

	char str[CAP_VALUE_BUF_SIZE];
	memset(str, 0, sizeof(str));

	BOOL string_or_constant_value = TRUE;

	switch (cap)
	{
		//convert to constant
#if USE_TWAIN_DSM
	case ICAP_AUTOSIZE:
	{
		switch (item)
		{
		case TWAS_NONE:
			sprintf(str, "%s", "TWAS_NONE"); break;
		case TWAS_AUTO:
			sprintf(str, "%s", "TWAS_AUTO"); break;
		case TWAS_CURRENT:
			sprintf(str, "%s", "TWAS_CURRENT"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_AUTODISCARDBLANKPAGES:
	{
		switch (item)
		{
		case TWBP_DISABLE:
			sprintf(str, "%s", "TWBP_DISABLE"); break;
		case TWBP_AUTO:
			sprintf(str, "%s", "TWBP_AUTO"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_CAMERASIDE:
	{
		switch (item)
		{
		case TWCS_BOTH:
			sprintf(str, "%s", "TWCS_BOTH"); break;
		case TWCS_TOP:
			sprintf(str, "%s", "TWCS_TOP"); break;
		case TWCS_BOTTOM:
			sprintf(str, "%s", "TWCS_BOTTOM"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_FEEDERTYPE:
	{
		switch (item)
		{
		case TWFE_GENERAL:
			sprintf(str, "%s", "TWFE_GENERAL"); break;
		case TWFE_PHOTO:
			sprintf(str, "%s", "TWFE_PHOTO"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_FEEDERPOCKET:
	{
		switch (item)
		{
		case TWFP_POCKETERROR:
			sprintf(str, "%s", "TWFP_POCKETERROR"); break;
		case TWFP_POCKET1:
			sprintf(str, "%s", "TWFP_POCKET1"); break;
		case TWFP_POCKET2:
			sprintf(str, "%s", "TWFP_POCKET2"); break;
		case TWFP_POCKET3:
			sprintf(str, "%s", "TWFP_POCKET3"); break;
		case TWFP_POCKET4:
			sprintf(str, "%s", "TWFP_POCKET4"); break;
		case TWFP_POCKET5:
			sprintf(str, "%s", "TWFP_POCKET5"); break;
		case TWFP_POCKET6:
			sprintf(str, "%s", "TWFP_POCKET6"); break;
		case TWFP_POCKET7:
			sprintf(str, "%s", "TWFP_POCKET7"); break;
		case TWFP_POCKET8:
			sprintf(str, "%s", "TWFP_POCKET8"); break;
		case TWFP_POCKET9:
			sprintf(str, "%s", "TWFP_POCKET9"); break;
		case TWFP_POCKET10:
			sprintf(str, "%s", "TWFP_POCKET10"); break;
		case TWFP_POCKET11:
			sprintf(str, "%s", "TWFP_POCKET11"); break;
		case TWFP_POCKET12:
			sprintf(str, "%s", "TWFP_POCKET12"); break;
		case TWFP_POCKET13:
			sprintf(str, "%s", "TWFP_POCKET13"); break;
		case TWFP_POCKET14:
			sprintf(str, "%s", "TWFP_POCKET14"); break;
		case TWFP_POCKET15:
			sprintf(str, "%s", "TWFP_POCKET15"); break;
		case TWFP_POCKET16:
			sprintf(str, "%s", "TWFP_POCKET16"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_ICCPROFILE:
	{
		switch (item)
		{
		case TWIC_NONE:
			sprintf(str, "%s", "TWIC_NONE"); break;
		case TWIC_LINK:
			sprintf(str, "%s", "TWIC_LINK"); break;
		case TWIC_EMBED:
			sprintf(str, "%s", "TWIC_EMBED"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_IMAGEMERGE:
	{
		switch (item)
		{
		case TWIM_NONE:
			sprintf(str, "%s", "TWIM_NONE"); break;
		case TWIM_FRONTONTOP:
			sprintf(str, "%s", "TWIM_FRONTONTOP"); break;
		case TWIM_FRONTONBOTTOM:
			sprintf(str, "%s", "TWIM_FRONTONBOTTOM"); break;
		case TWIM_FRONTONLEFT:
			sprintf(str, "%s", "TWIM_FRONTONLEFT"); break;
		case TWIM_FRONTONRIGHT:
			sprintf(str, "%s", "TWIM_FRONTONRIGHT"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_SEGMENTED:
	{
		switch (item)
		{
		case TWSG_NONE:
			sprintf(str, "%s", "TWSG_NONE"); break;
		case TWSG_AUTO:
			sprintf(str, "%s", "TWSG_AUTO"); break;
		case TWSG_MANUAL:
			sprintf(str, "%s", "TWSG_MANUAL"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
#endif
	case CAP_ALARMS:
	{
		switch (item)
		{
		case TWAL_ALARM:
			sprintf(str, "%s", "TWAL_ALARM"); break;
		case TWAL_FEEDERERROR:
			sprintf(str, "%s", "TWAL_FEEDERERROR"); break;
		case TWAL_FEEDERWARNING:
			sprintf(str, "%s", "TWAL_FEEDERWARNING"); break;
		case TWAL_BARCODE:
			sprintf(str, "%s", "TWAL_BARCODE"); break;
		case TWAL_DOUBLEFEED:
			sprintf(str, "%s", "TWAL_DOUBLEFEED"); break;
		case TWAL_JAM:
			sprintf(str, "%s", "TWAL_JAM"); break;
		case TWAL_PATCHCODE:
			sprintf(str, "%s", "TWAL_PATCHCODE"); break;
		case TWAL_POWER:
			sprintf(str, "%s", "TWAL_POWER"); break;
		case TWAL_SKEW:
			sprintf(str, "%s", "TWAL_SKEW"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_COMPRESSION:
	{
		switch (item)
		{
		case TWCP_NONE:
			sprintf(str, "%s", "TWCP_NONE"); break;
		case TWCP_PACKBITS:
			sprintf(str, "%s", "TWCP_PACKBITS"); break;
		case TWCP_GROUP31D:
			sprintf(str, "%s", "TWCP_GROUP31D"); break;
		case TWCP_GROUP31DEOL:
			sprintf(str, "%s", "TWCP_GROUP31DEOL"); break;
		case TWCP_GROUP32D:
			sprintf(str, "%s", "TWCP_GROUP32D"); break;
		case TWCP_GROUP4:
			sprintf(str, "%s", "TWCP_GROUP4"); break;
		case TWCP_JPEG:
			sprintf(str, "%s", "TWCP_JPEG"); break;
		case TWCP_LZW:
			sprintf(str, "%s", "TWCP_LZW"); break;
		case TWCP_JBIG:
			sprintf(str, "%s", "TWCP_JBIG"); break;
		case TWCP_PNG:
			sprintf(str, "%s", "TWCP_PNG"); break;
		case TWCP_RLE4:
			sprintf(str, "%s", "TWCP_RLE4"); break;
		case TWCP_RLE8:
			sprintf(str, "%s", "TWCP_RLE8"); break;
		case TWCP_BITFIELDS:
			sprintf(str, "%s", "TWCP_BITFIELDS"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_BARCODESEARCHMODE:
	{
		switch (item)
		{
		case TWBD_HORZ:
			sprintf(str, "%s", "TWBD_HORZ"); break;
		case TWBD_VERT:
			sprintf(str, "%s", "TWBD_VERT"); break;
		case TWBD_HORZVERT:
			sprintf(str, "%s", "TWBD_HORZVERT"); break;
		case TWBD_VERTHORZ:
			sprintf(str, "%s", "TWBD_VERTHORZ"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_BITORDER:
	{
		switch (item)
		{
		case TWBO_LSBFIRST:
			sprintf(str, "%s", "TWBO_LSBFIRST"); break;
		case TWBO_MSBFIRST:
			sprintf(str, "%s", "TWBO_MSBFIRST"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_BITDEPTHREDUCTION:
	{
		switch (item)
		{
		case TWBR_THRESHOLD:
			sprintf(str, "%s", "TWBR_THRESHOLD"); break;
		case TWBR_HALFTONE:
			sprintf(str, "%s", "TWBR_HALFTONE"); break;
		case TWBR_CUSTHALFTONE:
			sprintf(str, "%s", "TWBR_CUSTHALFTONE"); break;
		case TWBR_DIFFUSION:
			sprintf(str, "%s", "TWBR_DIFFUSION"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_SUPPORTEDBARCODETYPES:
	case TWEI_BARCODETYPE:
	{
		switch (item)
		{
		case TWBT_3OF9:
			sprintf(str, "%s", "TWBT_3OF9"); break;
		case TWBT_2OF5INTERLEAVED:
			sprintf(str, "%s", "TWBT_2OF5INTERLEAVED"); break;
		case TWBT_2OF5NONINTERLEAVED:
			sprintf(str, "%s", "TWBT_2OF5NONINTERLEAVED"); break;
		case TWBT_CODE93:
			sprintf(str, "%s", "TWBT_CODE93"); break;
		case TWBT_CODE128:
			sprintf(str, "%s", "TWBT_CODE128"); break;
		case TWBT_UCC128:
			sprintf(str, "%s", "TWBT_UCC128"); break;
		case TWBT_CODABAR:
			sprintf(str, "%s", "TWBT_CODABAR"); break;
		case TWBT_UPCA:
			sprintf(str, "%s", "TWBT_UPCA"); break;
		case TWBT_UPCE:
			sprintf(str, "%s", "TWBT_UPCE"); break;
		case TWBT_EAN8:
			sprintf(str, "%s", "TWBT_EAN8"); break;
		case TWBT_EAN13:
			sprintf(str, "%s", "TWBT_EAN13"); break;
		case TWBT_POSTNET:
			sprintf(str, "%s", "TWBT_POSTNET"); break;
		case TWBT_PDF417:
			sprintf(str, "%s", "TWBT_PDF417"); break;
		case TWBT_2OF5INDUSTRIAL:
			sprintf(str, "%s", "TWBT_2OF5INDUSTRIAL"); break;
		case TWBT_2OF5MATRIX:
			sprintf(str, "%s", "TWBT_2OF5MATRIX"); break;
		case TWBT_2OF5DATALOGIC:
			sprintf(str, "%s", "TWBT_2OF5DATALOGIC"); break;
		case TWBT_2OF5IATA:
			sprintf(str, "%s", "TWBT_2OF5IATA"); break;
		case TWBT_3OF9FULLASCII:
			sprintf(str, "%s", "TWBT_3OF9FULLASCII"); break;
		case TWBT_CODABARWITHSTARTSTOP:
			sprintf(str, "%s", "TWBT_CODABARWITHSTARTSTOP"); break;
		case TWBT_MAXICODE:
			sprintf(str, "%s", "TWBT_MAXICODE"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_CLEARBUFFERS:
	{
		switch (item)
		{
		case TWCB_AUTO:
			sprintf(str, "%s", "TWCB_AUTO"); break;
		case TWCB_CLEAR:
			sprintf(str, "%s", "TWCB_CLEAR"); break;
		case TWCB_NOCLEAR:
			sprintf(str, "%s", "TWCB_NOCLEAR"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_DEVICEEVENT:
	{
		switch (item)
		{
		case TWDE_CUSTOMEVENTS:
			sprintf(str, "%s", "TWDE_CUSTOMEVENTS"); break;
		case TWDE_CHECKAUTOMATICCAPTURE:
			sprintf(str, "%s", "TWDE_CHECKAUTOMATICCAPTURE"); break;
		case TWDE_CHECKBATTERY:
			sprintf(str, "%s", "TWDE_CHECKBATTERY"); break;
		case TWDE_CHECKDEVICEONLINE:
			sprintf(str, "%s", "TWDE_CHECKDEVICEONLINE"); break;
		case TWDE_CHECKFLASH:
			sprintf(str, "%s", "TWDE_CHECKFLASH"); break;
		case TWDE_CHECKPOWERSUPPLY:
			sprintf(str, "%s", "TWDE_CHECKPOWERSUPPLY"); break;
		case TWDE_CHECKRESOLUTION:
			sprintf(str, "%s", "TWDE_CHECKRESOLUTION"); break;
		case TWDE_DEVICEADDED:
			sprintf(str, "%s", "TWDE_DEVICEADDED"); break;
		case TWDE_DEVICEOFFLINE:
			sprintf(str, "%s", "TWDE_DEVICEOFFLINE"); break;
		case TWDE_DEVICEREADY:
			sprintf(str, "%s", "TWDE_DEVICEREADY"); break;
		case TWDE_DEVICEREMOVED:
			sprintf(str, "%s", "TWDE_DEVICEREMOVED"); break;
		case TWDE_IMAGECAPTURED:
			sprintf(str, "%s", "TWDE_IMAGECAPTURED"); break;
		case TWDE_IMAGEDELETED:
			sprintf(str, "%s", "TWDE_IMAGEDELETED"); break;
		case TWDE_PAPERDOUBLEFEED:
			sprintf(str, "%s", "TWDE_PAPERDOUBLEFEED"); break;
		case TWDE_PAPERJAM:
			sprintf(str, "%s", "TWDE_PAPERJAM"); break;
		case TWDE_LAMPFAILURE:
			sprintf(str, "%s", "TWDE_LAMPFAILURE"); break;
		case TWDE_POWERSAVE:
			sprintf(str, "%s", "TWDE_POWERSAVE"); break;
		case TWDE_POWERSAVENOTIFY:
			sprintf(str, "%s", "TWDE_POWERSAVENOTIFY"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_DUPLEX:
	{
		switch (item)
		{
		case TWDX_NONE:
			sprintf(str, "%s", "TWDX_NONE"); break;
		case TWDX_1PASSDUPLEX:
			sprintf(str, "%s", "TWDX_1PASSDUPLEX"); break;
		case TWDX_2PASSDUPLEX:
			sprintf(str, "%s", "TWDX_2PASSDUPLEX"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_FEEDERALIGNMENT:
	{
		switch (item)
		{
		case TWFA_NONE:
			sprintf(str, "%s", "TWFA_NONE"); break;
		case TWFA_LEFT:
			sprintf(str, "%s", "TWFA_LEFT"); break;
		case TWFA_CENTER:
			sprintf(str, "%s", "TWFA_CENTER"); break;
		case TWFA_RIGHT:
			sprintf(str, "%s", "TWFA_RIGHT"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_IMAGEFILEFORMAT:
	{
		switch (item)
		{
		case TWFF_TIFF:
			sprintf(str, "%s", "TWFF_TIFF"); break;
		case TWFF_PICT:
			sprintf(str, "%s", "TWFF_PICT"); break;
		case TWFF_BMP:
			sprintf(str, "%s", "TWFF_BMP"); break;
		case TWFF_XBM:
			sprintf(str, "%s", "TWFF_XBM"); break;
		case TWFF_JFIF:
			sprintf(str, "%s", "TWFF_JFIF"); break;
		case TWFF_FPX:
			sprintf(str, "%s", "TWFF_FPX"); break;
		case TWFF_TIFFMULTI:
			sprintf(str, "%s", "TWFF_TIFFMULTI"); break;
		case TWFF_PNG:
			sprintf(str, "%s", "TWFF_PNG"); break;
		case TWFF_SPIFF:
			sprintf(str, "%s", "TWFF_SPIFF"); break;
		case TWFF_EXIF:
			sprintf(str, "%s", "TWFF_EXIF"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_FLASHUSED2:
	{
		switch (item)
		{
		case TWFL_NONE:
			sprintf(str, "%s", "TWFL_NONE"); break;
		case TWFL_OFF:
			sprintf(str, "%s", "TWFL_OFF"); break;
		case TWFL_ON:
			sprintf(str, "%s", "TWFL_ON"); break;
		case TWFL_AUTO:
			sprintf(str, "%s", "TWFL_AUTO"); break;
		case TWFL_REDEYE:
			sprintf(str, "%s", "TWFL_REDEYE"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_FEEDERORDER:
	{
		switch (item)
		{
		case TWFO_FIRSTPAGEFIRST:
			sprintf(str, "%s", "TWFO_FIRSTPAGEFIRST"); break;
		case TWFO_LASTPAGEFIRST:
			sprintf(str, "%s", "TWFO_LASTPAGEFIRST"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_FLIPROTATION:
	{
		switch (item)
		{
		case TWFR_BOOK:
			sprintf(str, "%s", "TWFR_BOOK"); break;
		case TWFR_FANFOLD:
			sprintf(str, "%s", "TWFR_FANFOLD"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_FILTER:
	{
		switch (item)
		{
		case TWFT_RED:
			sprintf(str, "%s", "TWFT_RED"); break;
		case TWFT_GREEN:
			sprintf(str, "%s", "TWFT_GREEN"); break;
		case TWFT_BLUE:
			sprintf(str, "%s", "TWFT_BLUE"); break;
		case TWFT_NONE:
			sprintf(str, "%s", "TWFT_NONE"); break;
		case TWFT_WHITE:
			sprintf(str, "%s", "TWFT_WHITE"); break;
		case TWFT_CYAN:
			sprintf(str, "%s", "TWFT_CYAN"); break;
		case TWFT_MAGENTA:
			sprintf(str, "%s", "TWFT_MAGENTA"); break;
		case TWFT_YELLOW:
			sprintf(str, "%s", "TWFT_YELLOW"); break;
		case TWFT_BLACK:
			sprintf(str, "%s", "TWFT_BLACK"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_IMAGEFILTER:
	{
		switch (item)
		{
		case TWIF_NONE:
			sprintf(str, "%s", "TWIF_NONE"); break;
		case TWIF_AUTO:
			sprintf(str, "%s", "TWIF_AUTO"); break;
		case TWIF_LOWPASS:
			sprintf(str, "%s", "TWIF_LOWPASS"); break;
		case TWIF_BANDPASS:
			sprintf(str, "%s", "TWIF_BANDPASS"); break;
		case TWIF_HIGHPASS:
			sprintf(str, "%s", "TWIF_HIGHPASS"); break;
			//				case TWIF_TEXT:
			//					sprintf(str, "%s", "TWIF_TEXT");break;
			//				case TWIF_FINELINE:
			//					sprintf(str, "%s", "TWIF_FINELINE");break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_JOBCONTROL:
	{
		switch (item)
		{
		case TWJC_NONE:
			sprintf(str, "%s", "TWJC_NONE"); break;
		case TWJC_JSIC:
			sprintf(str, "%s", "TWJC_JSIC"); break;
		case TWJC_JSIS:
			sprintf(str, "%s", "TWJC_JSIS"); break;
		case TWJC_JSXC:
			sprintf(str, "%s", "TWJC_JSXC"); break;
		case TWJC_JSXS:
			sprintf(str, "%s", "TWJC_JSXS"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_JPEGQUALITY:
	{
		switch (item)
		{
		case TWJQ_UNKNOWN:
			sprintf(str, "%s", "TWJQ_UNKNOWN"); break;
		case TWJQ_LOW:
			sprintf(str, "%s", "TWJQ_LOW"); break;
		case TWJQ_MEDIUM:
			sprintf(str, "%s", "TWJQ_MEDIUM"); break;
		case TWJQ_HIGH:
			sprintf(str, "%s", "TWJQ_HIGH"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_LIGHTPATH:
	{
		switch (item)
		{
		case TWLP_REFLECTIVE:
			sprintf(str, "%s", "TWLP_REFLECTIVE"); break;
		case TWLP_TRANSMISSIVE:
			sprintf(str, "%s", "TWLP_TRANSMISSIVE"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_LIGHTSOURCE:
	{
		switch (item)
		{
		case TWLS_RED:
			sprintf(str, "%s", "TWLS_RED"); break;
		case TWLS_GREEN:
			sprintf(str, "%s", "TWLS_GREEN"); break;
		case TWLS_BLUE:
			sprintf(str, "%s", "TWLS_BLUE"); break;
		case TWLS_NONE:
			sprintf(str, "%s", "TWLS_NONE"); break;
		case TWLS_WHITE:
			sprintf(str, "%s", "TWLS_WHITE"); break;
		case TWLS_UV:
			sprintf(str, "%s", "TWLS_UV"); break;
		case TWLS_IR:
			sprintf(str, "%s", "TWLS_IR"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_NOISEFILTER:
	{
		switch (item)
		{
		case TWNF_NONE:
			sprintf(str, "%s", "TWNF_NONE"); break;
		case TWNF_AUTO:
			sprintf(str, "%s", "TWNF_AUTO"); break;
		case TWNF_LONEPIXEL:
			sprintf(str, "%s", "TWNF_LONEPIXEL"); break;
		case TWNF_MAJORITYRULE:
			sprintf(str, "%s", "TWNF_MAJORITYRULE"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_ORIENTATION:
	{
		switch (item)
		{
		case TWOR_ROT0:
			sprintf(str, "%s", "TWOR_ROT0"); break;
		case TWOR_ROT90:
			sprintf(str, "%s", "TWOR_ROT90"); break;
		case TWOR_ROT180:
			sprintf(str, "%s", "TWOR_ROT180"); break;
		case TWOR_ROT270:
			sprintf(str, "%s", "TWOR_ROT270"); break;
			//				case TWOR_PORTRAIT:
			//					sprintf(str, "%s", "TWOR_PORTRAIT");break;
			//				case TWOR_LANDSCAPE:
			//					sprintf(str, "%s", "TWOR_LANDSCAPE");break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_OVERSCAN:
	{
		switch (item)
		{
		case TWOV_NONE:
			sprintf(str, "%s", "TWOV_NONE"); break;
		case TWOV_AUTO:
			sprintf(str, "%s", "TWOV_AUTO"); break;
		case TWOV_TOPBOTTOM:
			sprintf(str, "%s", "TWOV_TOPBOTTOM"); break;
		case TWOV_LEFTRIGHT:
			sprintf(str, "%s", "TWOV_LEFTRIGHT"); break;
		case TWOV_ALL:
			sprintf(str, "%s", "TWOV_ALL"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_PLANARCHUNKY:
	{
		switch (item)
		{
		case TWPC_CHUNKY:
			sprintf(str, "%s", "TWPC_CHUNKY"); break;
		case TWPC_PLANAR:
			sprintf(str, "%s", "TWPC_PLANAR"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_PIXELFLAVOR:
	{
		switch (item)
		{
		case TWPF_CHOCOLATE:
			sprintf(str, "%s", "TWPF_CHOCOLATE"); break;
		case TWPF_VANILLA:
			sprintf(str, "%s", "TWPF_VANILLA"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_PRINTERMODE:
	{
		switch (item)
		{
		case TWPM_SINGLESTRING:
			sprintf(str, "%s", "TWPM_SINGLESTRING"); break;
		case TWPM_MULTISTRING:
			sprintf(str, "%s", "TWPM_MULTISTRING"); break;
		case TWPM_COMPOUNDSTRING:
			sprintf(str, "%s", "TWPM_COMPOUNDSTRING"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_PRINTER:
	{
		switch (item)
		{
		case TWPR_IMPRINTERTOPBEFORE:
			sprintf(str, "%s", "TWPR_IMPRINTERTOPBEFORE"); break;
		case TWPR_IMPRINTERTOPAFTER:
			sprintf(str, "%s", "TWPR_IMPRINTERTOPAFTER"); break;
		case TWPR_IMPRINTERBOTTOMBEFORE:
			sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMBEFORE"); break;
		case TWPR_IMPRINTERBOTTOMAFTER:
			sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMAFTER"); break;
		case TWPR_ENDORSERTOPBEFORE:
			sprintf(str, "%s", "TWPR_ENDORSERTOPBEFORE"); break;
		case TWPR_ENDORSERTOPAFTER:
			sprintf(str, "%s", "TWPR_ENDORSERTOPAFTER"); break;
		case TWPR_ENDORSERBOTTOMBEFORE:
			sprintf(str, "%s", "TWPR_ENDORSERBOTTOMBEFORE"); break;
		case TWPR_ENDORSERBOTTOMAFTER:
			sprintf(str, "%s", "TWPR_ENDORSERBOTTOMAFTER"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case CAP_POWERSUPPLY:
	{
		switch (item)
		{
		case TWPS_EXTERNAL:
			sprintf(str, "%s", "TWPS_EXTERNAL"); break;
		case TWPS_BATTERY:
			sprintf(str, "%s", "TWPS_BATTERY"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_PIXELTYPE:
	{
		switch (item)
		{
		case TWPT_BW:
			sprintf(str, "%s", "TWPT_BW"); break;
		case TWPT_GRAY:
			sprintf(str, "%s", "TWPT_GRAY"); break;
		case TWPT_RGB:
			sprintf(str, "%s", "TWPT_RGB"); break;
		case TWPT_PALETTE:
			sprintf(str, "%s", "TWPT_PALETTE"); break;
		case TWPT_CMY:
			sprintf(str, "%s", "TWPT_CMY"); break;
		case TWPT_CMYK:
			sprintf(str, "%s", "TWPT_CMYK"); break;
		case TWPT_YUV:
			sprintf(str, "%s", "TWPT_YUV"); break;
		case TWPT_YUVK:
			sprintf(str, "%s", "TWPT_YUVK"); break;
		case TWPT_CIEXYZ:
			sprintf(str, "%s", "TWPT_CIEXYZ"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_SUPPORTEDSIZES:
	{
		switch (item)
		{
		case TWSS_NONE:
			sprintf(str, "%s", "TWSS_NONE"); break;
		case TWSS_A4LETTER:
			sprintf(str, "%s", "TWSS_A4LETTER"); break;
		case TWSS_B5LETTER:
			sprintf(str, "%s", "TWSS_B5LETTER"); break;
		case TWSS_USLETTER:
			sprintf(str, "%s", "TWSS_USLETTER"); break;
		case TWSS_USLEGAL:
			sprintf(str, "%s", "TWSS_USLEGAL"); break;
		case TWSS_A5:
			sprintf(str, "%s", "TWSS_A5"); break;
		case TWSS_B4:
			sprintf(str, "%s", "TWSS_B4"); break;
		case TWSS_B6:
			sprintf(str, "%s", "TWSS_B6"); break;
			//				case TWSS_B:
			//					sprintf(str, "%s", "TWSS_B");break;
		case TWSS_USLEDGER:
			sprintf(str, "%s", "TWSS_USLEDGER"); break;
		case TWSS_USEXECUTIVE:
			sprintf(str, "%s", "TWSS_USEXECUTIVE"); break;
		case TWSS_A3:
			sprintf(str, "%s", "TWSS_A3"); break;
		case TWSS_B3:
			sprintf(str, "%s", "TWSS_B3"); break;
		case TWSS_A6:
			sprintf(str, "%s", "TWSS_A6"); break;
		case TWSS_C4:
			sprintf(str, "%s", "TWSS_C4"); break;
		case TWSS_C5:
			sprintf(str, "%s", "TWSS_C5"); break;
		case TWSS_C6:
			sprintf(str, "%s", "TWSS_C6"); break;
		case TWSS_4A0:
			sprintf(str, "%s", "TWSS_4A0"); break;
		case TWSS_2A0:
			sprintf(str, "%s", "TWSS_2A0"); break;
		case TWSS_A0:
			sprintf(str, "%s", "TWSS_A0"); break;
		case TWSS_A1:
			sprintf(str, "%s", "TWSS_A1"); break;
		case TWSS_A2:
			sprintf(str, "%s", "TWSS_A2"); break;
			//				case TWSS_A4:
			//					sprintf(str, "%s", "TWSS_A4");break;
		case TWSS_A7:
			sprintf(str, "%s", "TWSS_A7"); break;
		case TWSS_A8:
			sprintf(str, "%s", "TWSS_A8"); break;
		case TWSS_A9:
			sprintf(str, "%s", "TWSS_A9"); break;
		case TWSS_A10:
			sprintf(str, "%s", "TWSS_A10"); break;
		case TWSS_ISOB0:
			sprintf(str, "%s", "TWSS_ISOB0"); break;
		case TWSS_ISOB1:
			sprintf(str, "%s", "TWSS_ISOB1"); break;
		case TWSS_ISOB2:
			sprintf(str, "%s", "TWSS_ISOB2"); break;
			//				case TWSS_ISOB3:
			//					sprintf(str, "%s", "TWSS_ISOB3");break;
			//				case TWSS_ISOB4:
			//					sprintf(str, "%s", "TWSS_ISOB4");break;
		case TWSS_ISOB5:
			sprintf(str, "%s", "TWSS_ISOB5"); break;
			//				case TWSS_ISOB6:
			//					sprintf(str, "%s", "TWSS_ISOB6");break;
		case TWSS_ISOB7:
			sprintf(str, "%s", "TWSS_ISOB7"); break;
		case TWSS_ISOB8:
			sprintf(str, "%s", "TWSS_ISOB8"); break;
		case TWSS_ISOB9:
			sprintf(str, "%s", "TWSS_ISOB9"); break;
		case TWSS_ISOB10:
			sprintf(str, "%s", "TWSS_ISOB10"); break;
		case TWSS_JISB0:
			sprintf(str, "%s", "TWSS_JISB0"); break;
		case TWSS_JISB1:
			sprintf(str, "%s", "TWSS_JISB1"); break;
		case TWSS_JISB2:
			sprintf(str, "%s", "TWSS_JISB2"); break;
		case TWSS_JISB3:
			sprintf(str, "%s", "TWSS_JISB3"); break;
		case TWSS_JISB4:
			sprintf(str, "%s", "TWSS_JISB4"); break;
			//				case TWSS_JISB5:
			//					sprintf(str, "%s", "TWSS_JISB5");break;
		case TWSS_JISB6:
			sprintf(str, "%s", "TWSS_JISB6"); break;
		case TWSS_JISB7:
			sprintf(str, "%s", "TWSS_JISB7"); break;
		case TWSS_JISB8:
			sprintf(str, "%s", "TWSS_JISB8"); break;
		case TWSS_JISB9:
			sprintf(str, "%s", "TWSS_JISB9"); break;
		case TWSS_JISB10:
			sprintf(str, "%s", "TWSS_JISB10"); break;
		case TWSS_C0:
			sprintf(str, "%s", "TWSS_C0"); break;
		case TWSS_C1:
			sprintf(str, "%s", "TWSS_C1"); break;
		case TWSS_C2:
			sprintf(str, "%s", "TWSS_C2"); break;
		case TWSS_C3:
			sprintf(str, "%s", "TWSS_C3"); break;
		case TWSS_C7:
			sprintf(str, "%s", "TWSS_C7"); break;
		case TWSS_C8:
			sprintf(str, "%s", "TWSS_C8"); break;
		case TWSS_C9:
			sprintf(str, "%s", "TWSS_C9"); break;
		case TWSS_C10:
			sprintf(str, "%s", "TWSS_C10"); break;
		case TWSS_USSTATEMENT:
			sprintf(str, "%s", "TWSS_USSTATEMENT"); break;
		case TWSS_BUSINESSCARD:
			sprintf(str, "%s", "TWSS_BUSINESSCARD"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_XFERMECH:
	{
		switch (item)
		{
		case TWSX_NATIVE:
			sprintf(str, "%s", "TWSX_NATIVE"); break;
		case TWSX_FILE:
			sprintf(str, "%s", "TWSX_FILE"); break;
		case TWSX_MEMORY:
			sprintf(str, "%s", "TWSX_MEMORY"); break;
		case TWSX_FILE2:
			sprintf(str, "%s", "TWSX_FILE2"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	case ICAP_UNITS:
	{
		switch (item)
		{
		case TWUN_INCHES:
			sprintf(str, "%s", "TWUN_INCHES"); break;
		case TWUN_CENTIMETERS:
			sprintf(str, "%s", "TWUN_CENTIMETERS"); break;
		case TWUN_PICAS:
			sprintf(str, "%s", "TWUN_PICAS"); break;
		case TWUN_POINTS:
			sprintf(str, "%s", "TWUN_POINTS"); break;
		case TWUN_TWIPS:
			sprintf(str, "%s", "TWUN_TWIPS"); break;
		case TWUN_PIXELS:
			sprintf(str, "%s", "TWUN_PIXELS"); break;
		default:
			string_or_constant_value = FALSE;
			break;
		}
	}
	break;
	default:
		string_or_constant_value = FALSE;
	break;
	}

	if (string_or_constant_value)
	{
		if (strlen(str))
		{
			value = str;
		}
		else
		{
			value = (Json::Int)item;
		}
	}else
	{
		value = (Json::Int)item;
	}
}

void twain_get_capability_option_name(TW_UINT16 cap, std::string &stringValue) {
    
    switch(cap)
    {
        case CAP_XFERCOUNT:
            stringValue = "CAP_XFERCOUNT";
            break;
        case ICAP_COMPRESSION:
            stringValue = "ICAP_COMPRESSION";
            break;
        case ICAP_PIXELTYPE:
            stringValue = "ICAP_PIXELTYPE";
            break;
        case ICAP_UNITS:
            stringValue = "ICAP_UNITS";
            break;
        case ICAP_XFERMECH:
            stringValue = "ICAP_XFERMECH";
            break;
        case CAP_AUTHOR:
            stringValue = "CAP_AUTHOR";
            break;
        case CAP_CAPTION:
            stringValue = "CAP_CAPTION";
            break;
        case CAP_FEEDERENABLED:
            stringValue = "CAP_FEEDERENABLED";
            break;
        case CAP_FEEDERLOADED:
            stringValue = "CAP_FEEDERLOADED";
            break;
        case CAP_TIMEDATE:
            stringValue = "CAP_TIMEDATE";
            break;
        case CAP_SUPPORTEDCAPS:
            stringValue = "CAP_SUPPORTEDCAPS";
            break;
        case CAP_EXTENDEDCAPS:
            stringValue = "CAP_EXTENDEDCAPS";
            break;
        case CAP_AUTOFEED:
            stringValue = "CAP_AUTOFEED";
            break;
        case CAP_CLEARPAGE:
            stringValue = "CAP_CLEARPAGE";
            break;
        case CAP_FEEDPAGE:
            stringValue = "CAP_FEEDPAGE";
            break;
        case CAP_REWINDPAGE:
            stringValue = "CAP_REWINDPAGE";
            break;
        case CAP_INDICATORS:
            stringValue = "CAP_INDICATORS";
            break;
        case CAP_SUPPORTEDCAPSEXT:
            stringValue = "CAP_SUPPORTEDCAPSEXT";
            break;
        case CAP_PAPERDETECTABLE:
            stringValue = "CAP_PAPERDETECTABLE";
            break;
        case CAP_UICONTROLLABLE:
            stringValue = "CAP_UICONTROLLABLE";
            break;
        case CAP_DEVICEONLINE:
            stringValue = "CAP_DEVICEONLINE";
            break;
        case CAP_AUTOSCAN:
            stringValue = "CAP_AUTOSCAN";
            break;
        case CAP_THUMBNAILSENABLED:
            stringValue = "CAP_THUMBNAILSENABLED";
            break;
        case CAP_DUPLEX:
            stringValue = "CAP_DUPLEX";
            break;
        case CAP_DUPLEXENABLED:
            stringValue = "CAP_DUPLEXENABLED";
            break;
        case CAP_ENABLEDSUIONLY:
            stringValue = "CAP_ENABLEDSUIONLY";
            break;
        case CAP_CUSTOMDSDATA:
            stringValue = "CAP_CUSTOMDSDATA";
            break;
        case CAP_ENDORSER:
            stringValue = "CAP_ENDORSER";
            break;
        case CAP_JOBCONTROL:
            stringValue = "CAP_JOBCONTROL";
            break;
        case CAP_ALARMS:
            stringValue = "CAP_ALARMS";
            break;
        case CAP_ALARMVOLUME:
            stringValue = "CAP_ALARMVOLUME";
            break;
        case CAP_AUTOMATICCAPTURE:
            stringValue = "CAP_AUTOMATICCAPTURE";
            break;
        case CAP_TIMEBEFOREFIRSTCAPTURE:
            stringValue = "CAP_TIMEBEFOREFIRSTCAPTURE";
            break;
        case CAP_TIMEBETWEENCAPTURES:
            stringValue = "CAP_TIMEBETWEENCAPTURES";
            break;
        case CAP_CLEARBUFFERS:
            stringValue = "CAP_CLEARBUFFERS";
            break;
        case CAP_MAXBATCHBUFFERS:
            stringValue = "CAP_MAXBATCHBUFFERS";
            break;
        case CAP_DEVICETIMEDATE:
            stringValue = "CAP_DEVICETIMEDATE";
            break;
        case CAP_POWERSUPPLY:
            stringValue = "CAP_POWERSUPPLY";
            break;
        case CAP_CAMERAPREVIEWUI:
            stringValue = "CAP_CAMERAPREVIEWUI";
            break;
        case CAP_DEVICEEVENT:
            stringValue = "CAP_DEVICEEVENT";
            break;
        case CAP_SERIALNUMBER:
            stringValue = "CAP_SERIALNUMBER";
            break;
        case CAP_PRINTER:
            stringValue = "CAP_PRINTER";
            break;
        case CAP_PRINTERENABLED:
            stringValue = "CAP_PRINTERENABLED";
            break;
        case CAP_PRINTERINDEX:
            stringValue = "CAP_PRINTERINDEX";
            break;
        case CAP_PRINTERMODE:
            stringValue = "CAP_PRINTERMODE";
            break;
        case CAP_PRINTERSTRING:
            stringValue = "CAP_PRINTERSTRING";
            break;
        case CAP_PRINTERSUFFIX:
            stringValue = "CAP_PRINTERSUFFIX";
            break;
        case CAP_LANGUAGE:
            stringValue = "CAP_LANGUAGE";
            break;
        case CAP_FEEDERALIGNMENT:
            stringValue = "CAP_FEEDERALIGNMENT";
            break;
        case CAP_FEEDERORDER:
            stringValue = "CAP_FEEDERORDER";
            break;
        case CAP_REACQUIREALLOWED:
            stringValue = "CAP_REACQUIREALLOWED";
            break;
        case CAP_BATTERYMINUTES:
            stringValue = "CAP_BATTERYMINUTES";
            break;
        case CAP_BATTERYPERCENTAGE:
            stringValue = "CAP_BATTERYPERCENTAGE";
            break;
            /* was missing */
#if USE_TWAIN_DSM
        case CAP_CAMERASIDE:
            stringValue = "CAP_CAMERASIDE";
            break;
        case CAP_SEGMENTED:
            stringValue = "CAP_SEGMENTED";
            break;
        case CAP_CAMERAENABLED:
            stringValue = "CAP_CAMERAENABLED";
            break;
        case CAP_CAMERAORDER:
            stringValue = "CAP_CAMERAORDER";
            break;
        case CAP_MICRENABLED:
            stringValue = "CAP_MICRENABLED";
            break;
        case CAP_FEEDERPREP:
            stringValue = "CAP_FEEDERPREP";
            break;
        case CAP_FEEDERPOCKET:
            stringValue = "CAP_FEEDERPOCKET";
            break;
        case CAP_AUTOMATICSENSEMEDIUM:
            stringValue = "CAP_AUTOMATICSENSEMEDIUM";
            break;
        case CAP_CUSTOMINTERFACEGUID:
            stringValue = "CAP_CUSTOMINTERFACEGUID";
            break;
        case CAP_SUPPORTEDCAPSSEGMENTUNIQUE:
            stringValue = "CAP_SUPPORTEDCAPSSEGMENTUNIQUE";
            break;
        case CAP_SUPPORTEDDATS:
            stringValue = "CAP_SUPPORTEDDATS";
            break;
        case CAP_DOUBLEFEEDDETECTION:
            stringValue = "CAP_DOUBLEFEEDDETECTION";
            break;
        case CAP_DOUBLEFEEDDETECTIONLENGTH:
            stringValue = "CAP_DOUBLEFEEDDETECTIONLENGTH";
            break;
        case CAP_DOUBLEFEEDDETECTIONSENSITIVITY:
            stringValue = "CAP_DOUBLEFEEDDETECTIONSENSITIVITY";
            break;
        case CAP_DOUBLEFEEDDETECTIONRESPONSE:
            stringValue = "CAP_DOUBLEFEEDDETECTIONRESPONSE";
            break;
        case CAP_PAPERHANDLING:
            stringValue = "CAP_PAPERHANDLING";
            break;
        case CAP_INDICATORSMODE:
            stringValue = "CAP_INDICATORSMODE";
            break;
        case CAP_PRINTERVERTICALOFFSET:
            stringValue = "CAP_PRINTERVERTICALOFFSET";
            break;
        case CAP_POWERSAVETIME:
            stringValue = "CAP_POWERSAVETIME";
            break;
        case CAP_PRINTERCHARROTATION:
            stringValue = "CAP_PRINTERCHARROTATION";
            break;
        case CAP_PRINTERFONTSTYLE:
            stringValue = "CAP_PRINTERFONTSTYLE";
            break;
        case CAP_PRINTERINDEXLEADCHAR:
            stringValue = "CAP_PRINTERINDEXLEADCHAR";
            break;
        case CAP_PRINTERINDEXMAXVALUE:
            stringValue = "CAP_PRINTERINDEXMAXVALUE";
            break;
        case CAP_PRINTERINDEXNUMDIGITS:
            stringValue = "CAP_PRINTERINDEXNUMDIGITS";
            break;
        case CAP_PRINTERINDEXSTEP:
            stringValue = "CAP_PRINTERINDEXSTEP";
            break;
        case CAP_PRINTERINDEXTRIGGER:
            stringValue = "CAP_PRINTERINDEXTRIGGER";
            break;
        case CAP_PRINTERSTRINGPREVIEW:
            stringValue = "CAP_PRINTERSTRINGPREVIEW";
            break;
#endif
        case ICAP_AUTOBRIGHT:
            stringValue = "ICAP_AUTOBRIGHT";
            break;
        case ICAP_BRIGHTNESS:
            stringValue = "ICAP_BRIGHTNESS";
            break;
        case ICAP_CONTRAST:
            stringValue = "ICAP_CONTRAST";
            break;
        case ICAP_CUSTHALFTONE:
            stringValue = "ICAP_CUSTHALFTONE";
            break;
        case ICAP_EXPOSURETIME:
            stringValue = "ICAP_EXPOSURETIME";
            break;
        case ICAP_FILTER:
            stringValue = "ICAP_FILTER";
            break;
        case ICAP_FLASHUSED:
            stringValue = "ICAP_FLASHUSED";
            break;
        case ICAP_GAMMA:
            stringValue = "ICAP_GAMMA";
            break;
        case ICAP_HALFTONES:
            stringValue = "ICAP_HALFTONES";
            break;
        case ICAP_HIGHLIGHT:
            stringValue = "ICAP_HIGHLIGHT";
            break;
        case ICAP_IMAGEFILEFORMAT:
            stringValue = "ICAP_IMAGEFILEFORMAT";
            break;
        case ICAP_LAMPSTATE:
            stringValue = "ICAP_LAMPSTATE";
            break;
        case ICAP_LIGHTSOURCE:
            stringValue = "ICAP_LIGHTSOURCE";
            break;
        case ICAP_ORIENTATION:
            stringValue = "ICAP_ORIENTATION";
            break;
        case ICAP_PHYSICALWIDTH:
            stringValue = "ICAP_PHYSICALWIDTH";
            break;
        case ICAP_PHYSICALHEIGHT:
            stringValue = "ICAP_PHYSICALHEIGHT";
            break;
        case ICAP_SHADOW:
            stringValue = "ICAP_SHADOW";
            break;
        case ICAP_FRAMES:
            stringValue = "ICAP_FRAMES";
            break;
        case ICAP_XNATIVERESOLUTION:
            stringValue = "ICAP_XNATIVERESOLUTION";
            break;
        case ICAP_YNATIVERESOLUTION:
            stringValue = "ICAP_YNATIVERESOLUTION";
            break;
        case ICAP_XRESOLUTION:
            stringValue = "ICAP_XRESOLUTION";
            break;
        case ICAP_YRESOLUTION:
            stringValue = "ICAP_YRESOLUTION";
            break;
        case ICAP_MAXFRAMES:
            stringValue = "ICAP_MAXFRAMES";
            break;
        case ICAP_TILES:
            stringValue = "ICAP_TILES";
            break;
        case ICAP_BITORDER:
            stringValue = "ICAP_BITORDER";
            break;
        case ICAP_CCITTKFACTOR:
            stringValue = "ICAP_CCITTKFACTOR";
            break;
        case ICAP_LIGHTPATH:
            stringValue = "ICAP_LIGHTPATH";
            break;
        case ICAP_PIXELFLAVOR:
            stringValue = "ICAP_PIXELFLAVOR";
            break;
        case ICAP_PLANARCHUNKY:
            stringValue = "ICAP_PLANARCHUNKY";
            break;
        case ICAP_ROTATION:
            stringValue = "ICAP_ROTATION";
            break;
        case ICAP_SUPPORTEDSIZES:
            stringValue = "ICAP_SUPPORTEDSIZES";
            break;
        case ICAP_THRESHOLD:
            stringValue = "ICAP_THRESHOLD";
            break;
        case ICAP_XSCALING:
            stringValue = "ICAP_XSCALING";
            break;
        case ICAP_YSCALING:
            stringValue = "ICAP_YSCALING";
            break;
        case ICAP_BITORDERCODES:
            stringValue = "ICAP_BITORDERCODES";
            break;
        case ICAP_PIXELFLAVORCODES:
            stringValue = "ICAP_PIXELFLAVORCODES";
            break;
        case ICAP_JPEGPIXELTYPE:
            stringValue = "ICAP_JPEGPIXELTYPE";
            break;
        case ICAP_TIMEFILL:
            stringValue = "ICAP_TIMEFILL";
            break;
        case ICAP_BITDEPTH:
            stringValue = "ICAP_BITDEPTH";
            break;
        case ICAP_BITDEPTHREDUCTION:
            stringValue = "ICAP_BITDEPTHREDUCTION";
            break;
        case ICAP_UNDEFINEDIMAGESIZE:
            stringValue = "ICAP_UNDEFINEDIMAGESIZE";
            break;
        case ICAP_IMAGEDATASET:
            stringValue = "ICAP_IMAGEDATASET";
            break;
        case ICAP_EXTIMAGEINFO:
            stringValue = "ICAP_EXTIMAGEINFO";
            break;
        case ICAP_MINIMUMHEIGHT:
            stringValue = "ICAP_MINIMUMHEIGHT";
            break;
        case ICAP_MINIMUMWIDTH:
            stringValue = "ICAP_MINIMUMWIDTH";
            break;
        case ICAP_FLIPROTATION:
            stringValue = "ICAP_FLIPROTATION";
            break;
        case ICAP_BARCODEDETECTIONENABLED:
            stringValue = "ICAP_BARCODEDETECTIONENABLED";
            break;
        case ICAP_SUPPORTEDBARCODETYPES:
            stringValue = "ICAP_SUPPORTEDBARCODETYPES";
            break;
        case ICAP_BARCODEMAXSEARCHPRIORITIES:
            stringValue = "ICAP_BARCODEMAXSEARCHPRIORITIES";
            break;
        case ICAP_BARCODESEARCHPRIORITIES:
            stringValue = "ICAP_BARCODESEARCHPRIORITIES";
            break;
        case ICAP_BARCODESEARCHMODE:
            stringValue = "ICAP_BARCODESEARCHMODE";
            break;
        case ICAP_BARCODEMAXRETRIES:
            stringValue = "ICAP_BARCODEMAXRETRIES";
            break;
        case ICAP_BARCODETIMEOUT:
            stringValue = "ICAP_BARCODETIMEOUT";
            break;
        case ICAP_ZOOMFACTOR:
            stringValue = "ICAP_ZOOMFACTOR";
            break;
        case ICAP_PATCHCODEDETECTIONENABLED:
            stringValue = "ICAP_PATCHCODEDETECTIONENABLED";
            break;
        case ICAP_SUPPORTEDPATCHCODETYPES:
            stringValue = "ICAP_SUPPORTEDPATCHCODETYPES";
            break;
        case ICAP_PATCHCODEMAXSEARCHPRIORITIES:
            stringValue = "ICAP_PATCHCODEMAXSEARCHPRIORITIES";
            break;
        case ICAP_PATCHCODESEARCHPRIORITIES:
            stringValue = "ICAP_PATCHCODESEARCHPRIORITIES";
            break;
        case ICAP_PATCHCODESEARCHMODE:
            stringValue = "ICAP_PATCHCODESEARCHMODE";
            break;
        case ICAP_PATCHCODEMAXRETRIES:
            stringValue = "ICAP_PATCHCODEMAXRETRIES";
            break;
        case ICAP_PATCHCODETIMEOUT:
            stringValue = "ICAP_PATCHCODETIMEOUT";
            break;
        case ICAP_FLASHUSED2:
            stringValue = "ICAP_FLASHUSED2";
            break;
        case ICAP_IMAGEFILTER:
            stringValue = "ICAP_IMAGEFILTER";
            break;
        case ICAP_NOISEFILTER:
            stringValue = "ICAP_NOISEFILTER";
            break;
        case ICAP_OVERSCAN:
            stringValue = "ICAP_OVERSCAN";
            break;
        case ICAP_AUTOMATICBORDERDETECTION:
            stringValue = "ICAP_AUTOMATICBORDERDETECTION";
            break;
        case ICAP_AUTOMATICDESKEW:
            stringValue = "ICAP_AUTOMATICDESKEW";
            break;
        case ICAP_AUTOMATICROTATE:
            stringValue = "ICAP_AUTOMATICROTATE";
            break;
        case ICAP_JPEGQUALITY:
            stringValue = "ICAP_JPEGQUALITY";
            break;
#if USE_TWAIN_DSM
        case ICAP_AUTODISCARDBLANKPAGES:
            stringValue = "ICAP_AUTODISCARDBLANKPAGES";
            break;
        case ICAP_FEEDERTYPE:
            stringValue = "ICAP_FEEDERTYPE";
            break;
        case ICAP_ICCPROFILE:
            stringValue = "ICAP_ICCPROFILE";
            break;
        case ICAP_AUTOSIZE:
            stringValue = "ICAP_AUTOSIZE";
            break;
        case ICAP_AUTOMATICCROPUSESFRAME:
            stringValue = "ICAP_AUTOMATICCROPUSESFRAME";
            break;
        case ICAP_AUTOMATICLENGTHDETECTION:
            stringValue = "ICAP_AUTOMATICLENGTHDETECTION";
            break;
        case ICAP_AUTOMATICCOLORENABLED:
            stringValue = "ICAP_AUTOMATICCOLORENABLED";
            break;
        case ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE:
            stringValue = "ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE";
            break;
        case ICAP_COLORMANAGEMENTENABLED:
            stringValue = "ICAP_COLORMANAGEMENTENABLED";
            break;
        case ICAP_IMAGEMERGE:
            stringValue = "ICAP_IMAGEMERGE";
            break;
        case ICAP_IMAGEMERGEHEIGHTTHRESHOLD:
            stringValue = "ICAP_IMAGEMERGEHEIGHTTHRESHOLD";
            break;
        case ICAP_SUPPORTEDEXTIMAGEINFO:
            stringValue = "ICAP_SUPPORTEDEXTIMAGEINFO";
            break;
        case ICAP_FILMTYPE:
            stringValue = "ICAP_FILMTYPE";
            break;
        case ICAP_MIRROR:
            stringValue = "ICAP_MIRROR";
            break;
        case ICAP_JPEGSUBSAMPLING:
            stringValue = "ICAP_JPEGSUBSAMPLING";
            break;
#endif
        default:
        {
            char buf[33];
#if VERSIONWIN
            stringValue = _itoa(cap, buf, 10);
#else
            snprintf(buf, 33, "%d", cap);
            stringValue = buf;
#endif
        }
            break;
    }
}

void twain_get_capability_value(TW_CAPABILITY *tw_capability, void *p, Json::Value& json_scanner_option) {
    
    TW_UINT16 cap = tw_capability->Cap;
    TW_UINT16 conType = tw_capability->ConType;
    
    pTW_ENUMERATION pENUMERATION = (pTW_ENUMERATION)p;
    pTW_ONEVALUE pONEVALUE = (pTW_ONEVALUE)p;
    pTW_RANGE pRANGE = (pTW_RANGE)p;
    
    char str[CAP_VALUE_BUF_SIZE];
    memset(str, 0, sizeof(str));
    
    BOOL string_or_constant_value = TRUE;
    
    TW_INT32 item = 0;
    
    switch(conType)
    {
        case TWON_ARRAY:
            
            break;
        case TWON_ENUMERATION:
            item = (pENUMERATION->ItemList[pENUMERATION->CurrentIndex]);
            break;
        case TWON_ONEVALUE:
            item = pONEVALUE->Item;
            break;
        case TWON_RANGE:
            item = pRANGE->CurrentValue;
            break;
    }
    
    switch(cap)
    {
            //convert to constant
#if USE_TWAIN_DSM
        case ICAP_AUTOSIZE:
        {
            switch(item)
            {
                case TWAS_NONE:
                    sprintf(str, "%s", "TWAS_NONE");break;
                case TWAS_AUTO:
                    sprintf(str, "%s", "TWAS_AUTO");break;
                case TWAS_CURRENT:
                    sprintf(str, "%s", "TWAS_CURRENT");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_AUTODISCARDBLANKPAGES:
        {
            switch(item)
            {
                case TWBP_DISABLE:
                    sprintf(str, "%s", "TWBP_DISABLE");break;
                case TWBP_AUTO:
                    sprintf(str, "%s", "TWBP_AUTO");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_CAMERASIDE:
        {
            switch(item)
            {
                case TWCS_BOTH:
                    sprintf(str, "%s", "TWCS_BOTH");break;
                case TWCS_TOP:
                    sprintf(str, "%s", "TWCS_TOP");break;
                case TWCS_BOTTOM:
                    sprintf(str, "%s", "TWCS_BOTTOM");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_FEEDERTYPE:
        {
            switch(item)
            {
                case TWFE_GENERAL:
                    sprintf(str, "%s", "TWFE_GENERAL");break;
                case TWFE_PHOTO:
                    sprintf(str, "%s", "TWFE_PHOTO");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_FEEDERPOCKET:
        {
            switch(item)
            {
                case TWFP_POCKETERROR:
                    sprintf(str, "%s", "TWFP_POCKETERROR");break;
                case TWFP_POCKET1:
                    sprintf(str, "%s", "TWFP_POCKET1");break;
                case TWFP_POCKET2:
                    sprintf(str, "%s", "TWFP_POCKET2");break;
                case TWFP_POCKET3:
                    sprintf(str, "%s", "TWFP_POCKET3");break;
                case TWFP_POCKET4:
                    sprintf(str, "%s", "TWFP_POCKET4");break;
                case TWFP_POCKET5:
                    sprintf(str, "%s", "TWFP_POCKET5");break;
                case TWFP_POCKET6:
                    sprintf(str, "%s", "TWFP_POCKET6");break;
                case TWFP_POCKET7:
                    sprintf(str, "%s", "TWFP_POCKET7");break;
                case TWFP_POCKET8:
                    sprintf(str, "%s", "TWFP_POCKET8");break;
                case TWFP_POCKET9:
                    sprintf(str, "%s", "TWFP_POCKET9");break;
                case TWFP_POCKET10:
                    sprintf(str, "%s", "TWFP_POCKET10");break;
                case TWFP_POCKET11:
                    sprintf(str, "%s", "TWFP_POCKET11");break;
                case TWFP_POCKET12:
                    sprintf(str, "%s", "TWFP_POCKET12");break;
                case TWFP_POCKET13:
                    sprintf(str, "%s", "TWFP_POCKET13");break;
                case TWFP_POCKET14:
                    sprintf(str, "%s", "TWFP_POCKET14");break;
                case TWFP_POCKET15:
                    sprintf(str, "%s", "TWFP_POCKET15");break;
                case TWFP_POCKET16:
                    sprintf(str, "%s", "TWFP_POCKET16");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_ICCPROFILE:
        {
            switch(item)
            {
                case TWIC_NONE:
                    sprintf(str, "%s", "TWIC_NONE");break;
                case TWIC_LINK:
                    sprintf(str, "%s", "TWIC_LINK");break;
                case TWIC_EMBED:
                    sprintf(str, "%s", "TWIC_EMBED");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_IMAGEMERGE:
        {
            switch(item)
            {
                case TWIM_NONE:
                    sprintf(str, "%s", "TWIM_NONE");break;
                case TWIM_FRONTONTOP:
                    sprintf(str, "%s", "TWIM_FRONTONTOP");break;
                case TWIM_FRONTONBOTTOM:
                    sprintf(str, "%s", "TWIM_FRONTONBOTTOM");break;
                case TWIM_FRONTONLEFT:
                    sprintf(str, "%s", "TWIM_FRONTONLEFT");break;
                case TWIM_FRONTONRIGHT:
                    sprintf(str, "%s", "TWIM_FRONTONRIGHT");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_SEGMENTED:
        {
            switch(item)
            {
                case TWSG_NONE:
                    sprintf(str, "%s", "TWSG_NONE");break;
                case TWSG_AUTO:
                    sprintf(str, "%s", "TWSG_AUTO");break;
                case TWSG_MANUAL:
                    sprintf(str, "%s", "TWSG_MANUAL");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
#endif
        case CAP_ALARMS:
        {
            switch(item)
            {
                case TWAL_ALARM:
                    sprintf(str, "%s", "TWAL_ALARM");break;
                case TWAL_FEEDERERROR:
                    sprintf(str, "%s", "TWAL_FEEDERERROR");break;
                case TWAL_FEEDERWARNING:
                    sprintf(str, "%s", "TWAL_FEEDERWARNING");break;
                case TWAL_BARCODE:
                    sprintf(str, "%s", "TWAL_BARCODE");break;
                case TWAL_DOUBLEFEED:
                    sprintf(str, "%s", "TWAL_DOUBLEFEED");break;
                case TWAL_JAM:
                    sprintf(str, "%s", "TWAL_JAM");break;
                case TWAL_PATCHCODE:
                    sprintf(str, "%s", "TWAL_PATCHCODE");break;
                case TWAL_POWER:
                    sprintf(str, "%s", "TWAL_POWER");break;
                case TWAL_SKEW:
                    sprintf(str, "%s", "TWAL_SKEW");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_COMPRESSION:
        {
            switch(item)
            {
                case TWCP_NONE:
                    sprintf(str, "%s", "TWCP_NONE");break;
                case TWCP_PACKBITS:
                    sprintf(str, "%s", "TWCP_PACKBITS");break;
                case TWCP_GROUP31D:
                    sprintf(str, "%s", "TWCP_GROUP31D");break;
                case TWCP_GROUP31DEOL:
                    sprintf(str, "%s", "TWCP_GROUP31DEOL");break;
                case TWCP_GROUP32D:
                    sprintf(str, "%s", "TWCP_GROUP32D");break;
                case TWCP_GROUP4:
                    sprintf(str, "%s", "TWCP_GROUP4");break;
                case TWCP_JPEG:
                    sprintf(str, "%s", "TWCP_JPEG");break;
                case TWCP_LZW:
                    sprintf(str, "%s", "TWCP_LZW");break;
                case TWCP_JBIG:
                    sprintf(str, "%s", "TWCP_JBIG");break;
                case TWCP_PNG:
                    sprintf(str, "%s", "TWCP_PNG");break;
                case TWCP_RLE4:
                    sprintf(str, "%s", "TWCP_RLE4");break;
                case TWCP_RLE8:
                    sprintf(str, "%s", "TWCP_RLE8");break;
                case TWCP_BITFIELDS:
                    sprintf(str, "%s", "TWCP_BITFIELDS");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_BARCODESEARCHMODE:
        {
            switch(item)
            {
                case TWBD_HORZ:
                    sprintf(str, "%s", "TWBD_HORZ");break;
                case TWBD_VERT:
                    sprintf(str, "%s", "TWBD_VERT");break;
                case TWBD_HORZVERT:
                    sprintf(str, "%s", "TWBD_HORZVERT");break;
                case TWBD_VERTHORZ:
                    sprintf(str, "%s", "TWBD_VERTHORZ");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_BITORDER:
        {
            switch(item)
            {
                case TWBO_LSBFIRST:
                    sprintf(str, "%s", "TWBO_LSBFIRST");break;
                case TWBO_MSBFIRST:
                    sprintf(str, "%s", "TWBO_MSBFIRST");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_BITDEPTHREDUCTION:
        {
            switch(item)
            {
                case TWBR_THRESHOLD:
                    sprintf(str, "%s", "TWBR_THRESHOLD");break;
                case TWBR_HALFTONE:
                    sprintf(str, "%s", "TWBR_HALFTONE");break;
                case TWBR_CUSTHALFTONE:
                    sprintf(str, "%s", "TWBR_CUSTHALFTONE");break;
                case TWBR_DIFFUSION:
                    sprintf(str, "%s", "TWBR_DIFFUSION");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_SUPPORTEDBARCODETYPES:
        case TWEI_BARCODETYPE:
        {
            switch(item)
            {
                case TWBT_3OF9:
                    sprintf(str, "%s", "TWBT_3OF9");break;
                case TWBT_2OF5INTERLEAVED:
                    sprintf(str, "%s", "TWBT_2OF5INTERLEAVED");break;
                case TWBT_2OF5NONINTERLEAVED:
                    sprintf(str, "%s", "TWBT_2OF5NONINTERLEAVED");break;
                case TWBT_CODE93:
                    sprintf(str, "%s", "TWBT_CODE93");break;
                case TWBT_CODE128:
                    sprintf(str, "%s", "TWBT_CODE128");break;
                case TWBT_UCC128:
                    sprintf(str, "%s", "TWBT_UCC128");break;
                case TWBT_CODABAR:
                    sprintf(str, "%s", "TWBT_CODABAR");break;
                case TWBT_UPCA:
                    sprintf(str, "%s", "TWBT_UPCA");break;
                case TWBT_UPCE:
                    sprintf(str, "%s", "TWBT_UPCE");break;
                case TWBT_EAN8:
                    sprintf(str, "%s", "TWBT_EAN8");break;
                case TWBT_EAN13:
                    sprintf(str, "%s", "TWBT_EAN13");break;
                case TWBT_POSTNET:
                    sprintf(str, "%s", "TWBT_POSTNET");break;
                case TWBT_PDF417:
                    sprintf(str, "%s", "TWBT_PDF417");break;
                case TWBT_2OF5INDUSTRIAL:
                    sprintf(str, "%s", "TWBT_2OF5INDUSTRIAL");break;
                case TWBT_2OF5MATRIX:
                    sprintf(str, "%s", "TWBT_2OF5MATRIX");break;
                case TWBT_2OF5DATALOGIC:
                    sprintf(str, "%s", "TWBT_2OF5DATALOGIC");break;
                case TWBT_2OF5IATA:
                    sprintf(str, "%s", "TWBT_2OF5IATA");break;
                case TWBT_3OF9FULLASCII:
                    sprintf(str, "%s", "TWBT_3OF9FULLASCII");break;
                case TWBT_CODABARWITHSTARTSTOP:
                    sprintf(str, "%s", "TWBT_CODABARWITHSTARTSTOP");break;
                case TWBT_MAXICODE:
                    sprintf(str, "%s", "TWBT_MAXICODE");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_CLEARBUFFERS:
        {
            switch(item)
            {
                case TWCB_AUTO:
                    sprintf(str, "%s", "TWCB_AUTO");break;
                case TWCB_CLEAR:
                    sprintf(str, "%s", "TWCB_CLEAR");break;
                case TWCB_NOCLEAR:
                    sprintf(str, "%s", "TWCB_NOCLEAR");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_DEVICEEVENT:
        {
            switch(item)
            {
                case TWDE_CUSTOMEVENTS:
                    sprintf(str, "%s", "TWDE_CUSTOMEVENTS");break;
                case TWDE_CHECKAUTOMATICCAPTURE:
                    sprintf(str, "%s", "TWDE_CHECKAUTOMATICCAPTURE");break;
                case TWDE_CHECKBATTERY:
                    sprintf(str, "%s", "TWDE_CHECKBATTERY");break;
                case TWDE_CHECKDEVICEONLINE:
                    sprintf(str, "%s", "TWDE_CHECKDEVICEONLINE");break;
                case TWDE_CHECKFLASH:
                    sprintf(str, "%s", "TWDE_CHECKFLASH");break;
                case TWDE_CHECKPOWERSUPPLY:
                    sprintf(str, "%s", "TWDE_CHECKPOWERSUPPLY");break;
                case TWDE_CHECKRESOLUTION:
                    sprintf(str, "%s", "TWDE_CHECKRESOLUTION");break;
                case TWDE_DEVICEADDED:
                    sprintf(str, "%s", "TWDE_DEVICEADDED");break;
                case TWDE_DEVICEOFFLINE:
                    sprintf(str, "%s", "TWDE_DEVICEOFFLINE");break;
                case TWDE_DEVICEREADY:
                    sprintf(str, "%s", "TWDE_DEVICEREADY");break;
                case TWDE_DEVICEREMOVED:
                    sprintf(str, "%s", "TWDE_DEVICEREMOVED");break;
                case TWDE_IMAGECAPTURED:
                    sprintf(str, "%s", "TWDE_IMAGECAPTURED");break;
                case TWDE_IMAGEDELETED:
                    sprintf(str, "%s", "TWDE_IMAGEDELETED");break;
                case TWDE_PAPERDOUBLEFEED:
                    sprintf(str, "%s", "TWDE_PAPERDOUBLEFEED");break;
                case TWDE_PAPERJAM:
                    sprintf(str, "%s", "TWDE_PAPERJAM");break;
                case TWDE_LAMPFAILURE:
                    sprintf(str, "%s", "TWDE_LAMPFAILURE");break;
                case TWDE_POWERSAVE:
                    sprintf(str, "%s", "TWDE_POWERSAVE");break;
                case TWDE_POWERSAVENOTIFY:
                    sprintf(str, "%s", "TWDE_POWERSAVENOTIFY");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_DUPLEX:
        {
            switch(item)
            {
                case TWDX_NONE:
                    sprintf(str, "%s", "TWDX_NONE");break;
                case TWDX_1PASSDUPLEX:
                    sprintf(str, "%s", "TWDX_1PASSDUPLEX");break;
                case TWDX_2PASSDUPLEX:
                    sprintf(str, "%s", "TWDX_2PASSDUPLEX");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_FEEDERALIGNMENT:
        {
            switch(item)
            {
                case TWFA_NONE:
                    sprintf(str, "%s", "TWFA_NONE");break;
                case TWFA_LEFT:
                    sprintf(str, "%s", "TWFA_LEFT");break;
                case TWFA_CENTER:
                    sprintf(str, "%s", "TWFA_CENTER");break;
                case TWFA_RIGHT:
                    sprintf(str, "%s", "TWFA_RIGHT");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_IMAGEFILEFORMAT:
        {
            switch(item)
            {
                case TWFF_TIFF:
                    sprintf(str, "%s", "TWFF_TIFF");break;
                case TWFF_PICT:
                    sprintf(str, "%s", "TWFF_PICT");break;
                case TWFF_BMP:
                    sprintf(str, "%s", "TWFF_BMP");break;
                case TWFF_XBM:
                    sprintf(str, "%s", "TWFF_XBM");break;
                case TWFF_JFIF:
                    sprintf(str, "%s", "TWFF_JFIF");break;
                case TWFF_FPX:
                    sprintf(str, "%s", "TWFF_FPX");break;
                case TWFF_TIFFMULTI:
                    sprintf(str, "%s", "TWFF_TIFFMULTI");break;
                case TWFF_PNG:
                    sprintf(str, "%s", "TWFF_PNG");break;
                case TWFF_SPIFF:
                    sprintf(str, "%s", "TWFF_SPIFF");break;
                case TWFF_EXIF:
                    sprintf(str, "%s", "TWFF_EXIF");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_FLASHUSED2:
        {
            switch(item)
            {
                case TWFL_NONE:
                    sprintf(str, "%s", "TWFL_NONE");break;
                case TWFL_OFF:
                    sprintf(str, "%s", "TWFL_OFF");break;
                case TWFL_ON:
                    sprintf(str, "%s", "TWFL_ON");break;
                case TWFL_AUTO:
                    sprintf(str, "%s", "TWFL_AUTO");break;
                case TWFL_REDEYE:
                    sprintf(str, "%s", "TWFL_REDEYE");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_FEEDERORDER:
        {
            switch(item)
            {
                case TWFO_FIRSTPAGEFIRST:
                    sprintf(str, "%s", "TWFO_FIRSTPAGEFIRST");break;
                case TWFO_LASTPAGEFIRST:
                    sprintf(str, "%s", "TWFO_LASTPAGEFIRST");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_FLIPROTATION:
        {
            switch(item)
            {
                case TWFR_BOOK:
                    sprintf(str, "%s", "TWFR_BOOK");break;
                case TWFR_FANFOLD:
                    sprintf(str, "%s", "TWFR_FANFOLD");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_FILTER:
        {
            switch(item)
            {
                case TWFT_RED:
                    sprintf(str, "%s", "TWFT_RED");break;
                case TWFT_GREEN:
                    sprintf(str, "%s", "TWFT_GREEN");break;
                case TWFT_BLUE:
                    sprintf(str, "%s", "TWFT_BLUE");break;
                case TWFT_NONE:
                    sprintf(str, "%s", "TWFT_NONE");break;
                case TWFT_WHITE:
                    sprintf(str, "%s", "TWFT_WHITE");break;
                case TWFT_CYAN:
                    sprintf(str, "%s", "TWFT_CYAN");break;
                case TWFT_MAGENTA:
                    sprintf(str, "%s", "TWFT_MAGENTA");break;
                case TWFT_YELLOW:
                    sprintf(str, "%s", "TWFT_YELLOW");break;
                case TWFT_BLACK:
                    sprintf(str, "%s", "TWFT_BLACK");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_IMAGEFILTER:
        {
            switch(item)
            {
                case TWIF_NONE:
                    sprintf(str, "%s", "TWIF_NONE");break;
                case TWIF_AUTO:
                    sprintf(str, "%s", "TWIF_AUTO");break;
                case TWIF_LOWPASS:
                    sprintf(str, "%s", "TWIF_LOWPASS");break;
                case TWIF_BANDPASS:
                    sprintf(str, "%s", "TWIF_BANDPASS");break;
                case TWIF_HIGHPASS:
                    sprintf(str, "%s", "TWIF_HIGHPASS");break;
                    //                case TWIF_TEXT:
                    //                    sprintf(str, "%s", "TWIF_TEXT");break;
                    //                case TWIF_FINELINE:
                    //                    sprintf(str, "%s", "TWIF_FINELINE");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_JOBCONTROL:
        {
            switch(item)
            {
                case TWJC_NONE:
                    sprintf(str, "%s", "TWJC_NONE");break;
                case TWJC_JSIC:
                    sprintf(str, "%s", "TWJC_JSIC");break;
                case TWJC_JSIS:
                    sprintf(str, "%s", "TWJC_JSIS");break;
                case TWJC_JSXC:
                    sprintf(str, "%s", "TWJC_JSXC");break;
                case TWJC_JSXS:
                    sprintf(str, "%s", "TWJC_JSXS");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_JPEGQUALITY:
        {
            switch(item)
            {
                case TWJQ_UNKNOWN:
                    sprintf(str, "%s", "TWJQ_UNKNOWN");break;
                case TWJQ_LOW:
                    sprintf(str, "%s", "TWJQ_LOW");break;
                case TWJQ_MEDIUM:
                    sprintf(str, "%s", "TWJQ_MEDIUM");break;
                case TWJQ_HIGH:
                    sprintf(str, "%s", "TWJQ_HIGH");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_LIGHTPATH:
        {
            switch(item)
            {
                case TWLP_REFLECTIVE:
                    sprintf(str, "%s", "TWLP_REFLECTIVE");break;
                case TWLP_TRANSMISSIVE:
                    sprintf(str, "%s", "TWLP_TRANSMISSIVE");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_LIGHTSOURCE:
        {
            switch(item)
            {
                case TWLS_RED:
                    sprintf(str, "%s", "TWLS_RED");break;
                case TWLS_GREEN:
                    sprintf(str, "%s", "TWLS_GREEN");break;
                case TWLS_BLUE:
                    sprintf(str, "%s", "TWLS_BLUE");break;
                case TWLS_NONE:
                    sprintf(str, "%s", "TWLS_NONE");break;
                case TWLS_WHITE:
                    sprintf(str, "%s", "TWLS_WHITE");break;
                case TWLS_UV:
                    sprintf(str, "%s", "TWLS_UV");break;
                case TWLS_IR:
                    sprintf(str, "%s", "TWLS_IR");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_NOISEFILTER:
        {
            switch(item)
            {
                case TWNF_NONE:
                    sprintf(str, "%s", "TWNF_NONE");break;
                case TWNF_AUTO:
                    sprintf(str, "%s", "TWNF_AUTO");break;
                case TWNF_LONEPIXEL:
                    sprintf(str, "%s", "TWNF_LONEPIXEL");break;
                case TWNF_MAJORITYRULE:
                    sprintf(str, "%s", "TWNF_MAJORITYRULE");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_ORIENTATION:
        {
            switch(item)
            {
                case TWOR_ROT0:
                    sprintf(str, "%s", "TWOR_ROT0");break;
                case TWOR_ROT90:
                    sprintf(str, "%s", "TWOR_ROT90");break;
                case TWOR_ROT180:
                    sprintf(str, "%s", "TWOR_ROT180");break;
                case TWOR_ROT270:
                    sprintf(str, "%s", "TWOR_ROT270");break;
                    //                case TWOR_PORTRAIT:
                    //                    sprintf(str, "%s", "TWOR_PORTRAIT");break;
                    //                case TWOR_LANDSCAPE:
                    //                    sprintf(str, "%s", "TWOR_LANDSCAPE");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_OVERSCAN:
        {
            switch(item)
            {
                case TWOV_NONE:
                    sprintf(str, "%s", "TWOV_NONE");break;
                case TWOV_AUTO:
                    sprintf(str, "%s", "TWOV_AUTO");break;
                case TWOV_TOPBOTTOM:
                    sprintf(str, "%s", "TWOV_TOPBOTTOM");break;
                case TWOV_LEFTRIGHT:
                    sprintf(str, "%s", "TWOV_LEFTRIGHT");break;
                case TWOV_ALL:
                    sprintf(str, "%s", "TWOV_ALL");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_PLANARCHUNKY:
        {
            switch(item)
            {
                case TWPC_CHUNKY:
                    sprintf(str, "%s", "TWPC_CHUNKY");break;
                case TWPC_PLANAR:
                    sprintf(str, "%s", "TWPC_PLANAR");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_PIXELFLAVOR:
        {
            switch(item)
            {
                case TWPF_CHOCOLATE:
                    sprintf(str, "%s", "TWPF_CHOCOLATE");break;
                case TWPF_VANILLA:
                    sprintf(str, "%s", "TWPF_VANILLA");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_PRINTERMODE:
        {
            switch(item)
            {
                case TWPM_SINGLESTRING:
                    sprintf(str, "%s", "TWPM_SINGLESTRING");break;
                case TWPM_MULTISTRING:
                    sprintf(str, "%s", "TWPM_MULTISTRING");break;
                case TWPM_COMPOUNDSTRING:
                    sprintf(str, "%s", "TWPM_COMPOUNDSTRING");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_PRINTER:
        {
            switch(item)
            {
                case TWPR_IMPRINTERTOPBEFORE:
                    sprintf(str, "%s", "TWPR_IMPRINTERTOPBEFORE");break;
                case TWPR_IMPRINTERTOPAFTER:
                    sprintf(str, "%s", "TWPR_IMPRINTERTOPAFTER");break;
                case TWPR_IMPRINTERBOTTOMBEFORE:
                    sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMBEFORE");break;
                case TWPR_IMPRINTERBOTTOMAFTER:
                    sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMAFTER");break;
                case TWPR_ENDORSERTOPBEFORE:
                    sprintf(str, "%s", "TWPR_ENDORSERTOPBEFORE");break;
                case TWPR_ENDORSERTOPAFTER:
                    sprintf(str, "%s", "TWPR_ENDORSERTOPAFTER");break;
                case TWPR_ENDORSERBOTTOMBEFORE:
                    sprintf(str, "%s", "TWPR_ENDORSERBOTTOMBEFORE");break;
                case TWPR_ENDORSERBOTTOMAFTER:
                    sprintf(str, "%s", "TWPR_ENDORSERBOTTOMAFTER");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case CAP_POWERSUPPLY:
        {
            switch(item)
            {
                case TWPS_EXTERNAL:
                    sprintf(str, "%s", "TWPS_EXTERNAL");break;
                case TWPS_BATTERY:
                    sprintf(str, "%s", "TWPS_BATTERY");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_PIXELTYPE:
        {
            switch(item)
            {
                case TWPT_BW:
                    sprintf(str, "%s", "TWPT_BW");break;
                case TWPT_GRAY:
                    sprintf(str, "%s", "TWPT_GRAY");break;
                case TWPT_RGB:
                    sprintf(str, "%s", "TWPT_RGB");break;
                case TWPT_PALETTE:
                    sprintf(str, "%s", "TWPT_PALETTE");break;
                case TWPT_CMY:
                    sprintf(str, "%s", "TWPT_CMY");break;
                case TWPT_CMYK:
                    sprintf(str, "%s", "TWPT_CMYK");break;
                case TWPT_YUV:
                    sprintf(str, "%s", "TWPT_YUV");break;
                case TWPT_YUVK:
                    sprintf(str, "%s", "TWPT_YUVK");break;
                case TWPT_CIEXYZ:
                    sprintf(str, "%s", "TWPT_CIEXYZ");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_SUPPORTEDSIZES:
        {
            switch(item)
            {
                case TWSS_NONE:
                    sprintf(str, "%s", "TWSS_NONE");break;
                case TWSS_A4LETTER:
                    sprintf(str, "%s", "TWSS_A4LETTER");break;
                case TWSS_B5LETTER:
                    sprintf(str, "%s", "TWSS_B5LETTER");break;
                case TWSS_USLETTER:
                    sprintf(str, "%s", "TWSS_USLETTER");break;
                case TWSS_USLEGAL:
                    sprintf(str, "%s", "TWSS_USLEGAL");break;
                case TWSS_A5:
                    sprintf(str, "%s", "TWSS_A5");break;
                case TWSS_B4:
                    sprintf(str, "%s", "TWSS_B4");break;
                case TWSS_B6:
                    sprintf(str, "%s", "TWSS_B6");break;
                    //                case TWSS_B:
                    //                    sprintf(str, "%s", "TWSS_B");break;
                case TWSS_USLEDGER:
                    sprintf(str, "%s", "TWSS_USLEDGER");break;
                case TWSS_USEXECUTIVE:
                    sprintf(str, "%s", "TWSS_USEXECUTIVE");break;
                case TWSS_A3:
                    sprintf(str, "%s", "TWSS_A3");break;
                case TWSS_B3:
                    sprintf(str, "%s", "TWSS_B3");break;
                case TWSS_A6:
                    sprintf(str, "%s", "TWSS_A6");break;
                case TWSS_C4:
                    sprintf(str, "%s", "TWSS_C4");break;
                case TWSS_C5:
                    sprintf(str, "%s", "TWSS_C5");break;
                case TWSS_C6:
                    sprintf(str, "%s", "TWSS_C6");break;
                case TWSS_4A0:
                    sprintf(str, "%s", "TWSS_4A0");break;
                case TWSS_2A0:
                    sprintf(str, "%s", "TWSS_2A0");break;
                case TWSS_A0:
                    sprintf(str, "%s", "TWSS_A0");break;
                case TWSS_A1:
                    sprintf(str, "%s", "TWSS_A1");break;
                case TWSS_A2:
                    sprintf(str, "%s", "TWSS_A2");break;
                    //                case TWSS_A4:
                    //                    sprintf(str, "%s", "TWSS_A4");break;
                case TWSS_A7:
                    sprintf(str, "%s", "TWSS_A7");break;
                case TWSS_A8:
                    sprintf(str, "%s", "TWSS_A8");break;
                case TWSS_A9:
                    sprintf(str, "%s", "TWSS_A9");break;
                case TWSS_A10:
                    sprintf(str, "%s", "TWSS_A10");break;
                case TWSS_ISOB0:
                    sprintf(str, "%s", "TWSS_ISOB0");break;
                case TWSS_ISOB1:
                    sprintf(str, "%s", "TWSS_ISOB1");break;
                case TWSS_ISOB2:
                    sprintf(str, "%s", "TWSS_ISOB2");break;
                    //                case TWSS_ISOB3:
                    //                    sprintf(str, "%s", "TWSS_ISOB3");break;
                    //                case TWSS_ISOB4:
                    //                    sprintf(str, "%s", "TWSS_ISOB4");break;
                case TWSS_ISOB5:
                    sprintf(str, "%s", "TWSS_ISOB5");break;
                    //                case TWSS_ISOB6:
                    //                    sprintf(str, "%s", "TWSS_ISOB6");break;
                case TWSS_ISOB7:
                    sprintf(str, "%s", "TWSS_ISOB7");break;
                case TWSS_ISOB8:
                    sprintf(str, "%s", "TWSS_ISOB8");break;
                case TWSS_ISOB9:
                    sprintf(str, "%s", "TWSS_ISOB9");break;
                case TWSS_ISOB10:
                    sprintf(str, "%s", "TWSS_ISOB10");break;
                case TWSS_JISB0:
                    sprintf(str, "%s", "TWSS_JISB0");break;
                case TWSS_JISB1:
                    sprintf(str, "%s", "TWSS_JISB1");break;
                case TWSS_JISB2:
                    sprintf(str, "%s", "TWSS_JISB2");break;
                case TWSS_JISB3:
                    sprintf(str, "%s", "TWSS_JISB3");break;
                case TWSS_JISB4:
                    sprintf(str, "%s", "TWSS_JISB4");break;
                    //                case TWSS_JISB5:
                    //                    sprintf(str, "%s", "TWSS_JISB5");break;
                case TWSS_JISB6:
                    sprintf(str, "%s", "TWSS_JISB6");break;
                case TWSS_JISB7:
                    sprintf(str, "%s", "TWSS_JISB7");break;
                case TWSS_JISB8:
                    sprintf(str, "%s", "TWSS_JISB8");break;
                case TWSS_JISB9:
                    sprintf(str, "%s", "TWSS_JISB9");break;
                case TWSS_JISB10:
                    sprintf(str, "%s", "TWSS_JISB10");break;
                case TWSS_C0:
                    sprintf(str, "%s", "TWSS_C0");break;
                case TWSS_C1:
                    sprintf(str, "%s", "TWSS_C1");break;
                case TWSS_C2:
                    sprintf(str, "%s", "TWSS_C2");break;
                case TWSS_C3:
                    sprintf(str, "%s", "TWSS_C3");break;
                case TWSS_C7:
                    sprintf(str, "%s", "TWSS_C7");break;
                case TWSS_C8:
                    sprintf(str, "%s", "TWSS_C8");break;
                case TWSS_C9:
                    sprintf(str, "%s", "TWSS_C9");break;
                case TWSS_C10:
                    sprintf(str, "%s", "TWSS_C10");break;
                case TWSS_USSTATEMENT:
                    sprintf(str, "%s", "TWSS_USSTATEMENT");break;
                case TWSS_BUSINESSCARD:
                    sprintf(str, "%s", "TWSS_BUSINESSCARD");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_XFERMECH:
        {
            switch(item)
            {
                case TWSX_NATIVE:
                    sprintf(str, "%s", "TWSX_NATIVE");break;
                case TWSX_FILE:
                    sprintf(str, "%s", "TWSX_FILE");break;
                case TWSX_MEMORY:
                    sprintf(str, "%s", "TWSX_MEMORY");break;
                case TWSX_FILE2:
                    sprintf(str, "%s", "TWSX_FILE2");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        case ICAP_UNITS:
        {
            switch(item)
            {
                case TWUN_INCHES:
                    sprintf(str, "%s", "TWUN_INCHES");break;
                case TWUN_CENTIMETERS:
                    sprintf(str, "%s", "TWUN_CENTIMETERS");break;
                case TWUN_PICAS:
                    sprintf(str, "%s", "TWUN_PICAS");break;
                case TWUN_POINTS:
                    sprintf(str, "%s", "TWUN_POINTS");break;
                case TWUN_TWIPS:
                    sprintf(str, "%s", "TWUN_TWIPS");break;
                case TWUN_PIXELS:
                    sprintf(str, "%s", "TWUN_PIXELS");break;
				default:
					string_or_constant_value = FALSE;
					break;
            }
        }
            break;
        default:
            string_or_constant_value = FALSE;
            break;
    }
 
    if(string_or_constant_value)
    {
		json_scanner_option = str;
    }
    else
    {
        //generic
        switch (conType)
        {
            case TWON_ARRAY:
                string_or_constant_value = FALSE;
                break;
            case TWON_ENUMERATION:
                switch (pENUMERATION->ItemType)
            {
                case TWTY_FIX32:
                {
                    string_or_constant_value = FALSE;
                    pTW_FIX32 pFix32 = &((pTW_FIX32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
					json_scanner_option = float(pFix32->Whole) + float(pFix32->Frac / 65536.0);
                }
                    break;
                case TWTY_FRAME:
                {
                    pTW_FRAME pframe = &((pTW_FRAME)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
                    sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
                            pframe->Top.Whole, pframe->Top.Frac,
                            pframe->Left.Whole, pframe->Left.Frac,
                            pframe->Right.Whole, pframe->Right.Frac,
                            pframe->Bottom.Whole, pframe->Bottom.Frac);
                }
                    break;
                case TWTY_INT8:
                case TWTY_INT16:
                case TWTY_INT32:
                {
                    string_or_constant_value = FALSE;
                    TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
					json_scanner_option = (Json::UInt)currentValue;
                }
                    break;
                case TWTY_UINT8:
                case TWTY_UINT16:
                case TWTY_UINT32:
                {
                    string_or_constant_value = FALSE;
                    TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
					json_scanner_option = (Json::UInt)currentValue;
                }
                    break;
                case TWTY_BOOL:
                {
                    string_or_constant_value = FALSE;
                    TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
					json_scanner_option = (BOOL)currentValue;
                }
                    break;
                case TWTY_STR32:
                {
                    pTW_STR32 pStr32 = &((pTW_STR32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
                    sprintf(str, "%s", pStr32);
					json_scanner_option = str;
                }
                    break;
                case TWTY_STR64:
                {
                    pTW_STR64 pStr64 = &((pTW_STR64)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
                    sprintf(str, "%s", pStr64);
					json_scanner_option = str;
                }
                    break;
                case TWTY_STR128:
                {
                    pTW_STR128 pStr128 = &((pTW_STR128)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
                    sprintf(str, "%s", pStr128);
					json_scanner_option = str;
                }
                    break;
                case TWTY_STR255:
                {
                    pTW_STR255 pStr255 = &((pTW_STR255)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
                    sprintf(str, "%s", pStr255);
					json_scanner_option = str;
                }
                    break;
                    //                    case TWTY_STR1024:
                    //                    case TWTY_UNI512:
                    //                        break;
                default:
                    break;
            }
                break;
            case TWON_ONEVALUE:
                switch (pONEVALUE->ItemType)
            {
                case TWTY_FIX32:
                {
                    string_or_constant_value = FALSE;
                    pTW_FIX32 pFix32 = (pTW_FIX32)&pONEVALUE->Item;
					json_scanner_option = float(pFix32->Whole) + float(pFix32->Frac / 65536.0);
                }
                    break;
                case TWTY_FRAME:
                {
                    pTW_FRAME pframe = (pTW_FRAME)&pONEVALUE->Item;
                    sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
                            pframe->Top.Whole, pframe->Top.Frac,
                            pframe->Left.Whole, pframe->Left.Frac,
                            pframe->Right.Whole, pframe->Right.Frac,
                            pframe->Bottom.Whole, pframe->Bottom.Frac);
                }
                    break;
                case TWTY_INT8:
                case TWTY_INT16:
                case TWTY_INT32:
                {
                    string_or_constant_value = FALSE;
                    TW_UINT32 currentValue = pONEVALUE->Item;
					json_scanner_option = (Json::UInt)currentValue;
                }
                    break;
                case TWTY_UINT8:
                case TWTY_UINT16:
                case TWTY_UINT32:
                {
                    string_or_constant_value = FALSE;
                    TW_UINT32 currentValue = pONEVALUE->Item;
					json_scanner_option = (Json::UInt)currentValue;
                }
                    break;
                case TWTY_BOOL:
                {
                    string_or_constant_value = FALSE;
                    TW_UINT32 currentValue = pONEVALUE->Item;
					json_scanner_option = (BOOL)currentValue;
                }
                    break;
                case TWTY_STR32:
                {
                    pTW_STR32 pStr32 = (pTW_STR32)&pONEVALUE->Item;
                    sprintf(str, "%s", pStr32);
					json_scanner_option = str;
                }
                    break;
                case TWTY_STR64:
                {
                    pTW_STR64 pStr64 = (pTW_STR64)&pONEVALUE->Item;
                    sprintf(str, "%s", pStr64);
					json_scanner_option = str;
                }
                    break;
                case TWTY_STR128:
                {
                    pTW_STR128 pStr128 = (pTW_STR128)&pONEVALUE->Item;
                    sprintf(str, "%s", pStr128);
					json_scanner_option = str;
                }
                    break;
                case TWTY_STR255:
                {
                    pTW_STR255 pStr255 = (pTW_STR255)&pONEVALUE->Item;
                    sprintf(str, "%s", pStr255);
					json_scanner_option = str;
                }
                    break;
                    //                    case TWTY_STR1024:
                    //                    case TWTY_UNI512:
                    //                        break;
                default:
                    break;
            }
                break;
            case TWON_RANGE:
                string_or_constant_value = FALSE;
                TW_UINT32 currentValue = pRANGE->CurrentValue;
				json_scanner_option = (Json::UInt)currentValue;
                break;
        }
    }
}

void twain_get_capability_param(TW_CAPABILITY *tw_capability, void *p, Json::Value& json_scanner_option) {
    
	TW_UINT16 cap = tw_capability->Cap;
	TW_UINT16 conType = tw_capability->ConType;

	pTW_ENUMERATION pENUMERATION = (pTW_ENUMERATION)p;
	pTW_ONEVALUE pONEVALUE = (pTW_ONEVALUE)p;
	pTW_RANGE pRANGE = (pTW_RANGE)p;
	pTW_ARRAY pARRAY = (pTW_ARRAY)p;

	char str[CAP_VALUE_BUF_SIZE];
	memset(str, 0, sizeof(str));

	switch (conType)
	{
	case TWON_ARRAY:
	{
		Json::Value json_scanner_option_values(Json::arrayValue);

		for (int i = 0; i < pARRAY->NumItems; ++i)
		{
			switch (pARRAY->ItemType)
			{
			case TWTY_FIX32:
			{
				pTW_FIX32 pFix32 = &((pTW_FIX32)(&pARRAY->ItemList))[i];
				json_scanner_option_values.append(float(pFix32->Whole) + float(pFix32->Frac / 65536.0));
			}
			break;
			case TWTY_FRAME:
			{
				pTW_FRAME pframe = &((pTW_FRAME)(&pARRAY->ItemList))[i];
				sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
					pframe->Top.Whole, pframe->Top.Frac,
					pframe->Left.Whole, pframe->Left.Frac,
					pframe->Right.Whole, pframe->Right.Frac,
					pframe->Bottom.Whole, pframe->Bottom.Frac);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_INT8:
			{
				TW_INT8 currentValue = ((pTW_INT8)(&pARRAY->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_INT16:
			{
				TW_INT16 currentValue = ((pTW_INT16)(&pARRAY->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_INT32:
			{
				TW_INT32 currentValue = ((pTW_INT32)(&pARRAY->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_UINT8:
			{
				TW_UINT8 currentValue = ((pTW_UINT8)(&pARRAY->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_UINT16:
			{
				TW_UINT16 currentValue = ((pTW_UINT16)(&pARRAY->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_UINT32:
			{
				TW_UINT32 currentValue = ((pTW_UINT32)(&pARRAY->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_BOOL:
			{
				TW_UINT32 currentValue = ((pTW_UINT32)(&pARRAY->ItemList))[i];
				if ((BOOL)currentValue) {
					json_scanner_option_values.append(true);
				}
				else {
					json_scanner_option_values.append(false);
				}
				
			}
			break;
			case TWTY_STR32:
			{
				pTW_STR32 pStr32 = &((pTW_STR32)(&pARRAY->ItemList))[i];
				sprintf(str, "%s", pStr32);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_STR64:
			{
				pTW_STR64 pStr64 = &((pTW_STR64)(&pARRAY->ItemList))[i];
				sprintf(str, "%s", pStr64);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_STR128:
			{
				pTW_STR128 pStr128 = &((pTW_STR128)(&pARRAY->ItemList))[i];
				sprintf(str, "%s", pStr128);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_STR255:
			{
				pTW_STR255 pStr255 = &((pTW_STR255)(&pARRAY->ItemList))[i];
				sprintf(str, "%s", pStr255);
				json_scanner_option_values.append(str);
			}
			break;
			//					case TWTY_STR1024:
			//					case TWTY_UNI512:
			//						break;
			default:
				break;
			}
		}
		json_scanner_option["values"] = json_scanner_option_values;
	}
	json_scanner_option["itemType"] = "TWON_ARRAY";
	break;
	case TWON_ENUMERATION:
	{
		Json::Value json_scanner_option_values(Json::arrayValue);

		for (int i = 0; i < pENUMERATION->NumItems; ++i)
		{
			switch (pENUMERATION->ItemType)
			{
			case TWTY_FIX32:
			{
				pTW_FIX32 pFix32 = &((pTW_FIX32)(&pENUMERATION->ItemList))[i];
				json_scanner_option_values.append(float(pFix32->Whole) + float(pFix32->Frac / 65536.0));
			}
			break;
			case TWTY_FRAME:
			{
				pTW_FRAME pframe = &((pTW_FRAME)(&pENUMERATION->ItemList))[i];
				sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
					pframe->Top.Whole, pframe->Top.Frac,
					pframe->Left.Whole, pframe->Left.Frac,
					pframe->Right.Whole, pframe->Right.Frac,
					pframe->Bottom.Whole, pframe->Bottom.Frac);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_INT8:
			{
				TW_INT8 currentValue = ((pTW_INT8)(&pENUMERATION->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_INT16:
			{
				TW_INT16 currentValue = ((pTW_INT16)(&pENUMERATION->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_INT32:
			{
				TW_INT32 currentValue = ((pTW_INT32)(&pENUMERATION->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_UINT8:
			{
				TW_UINT8 currentValue = ((pTW_UINT8)(&pENUMERATION->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_UINT16:
			{
				TW_UINT16 currentValue = ((pTW_UINT16)(&pENUMERATION->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_UINT32:
			{
				TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[i];
				Json::Value value(Json::nullValue);
				twain_get_option_value_name(cap, currentValue, value);
				json_scanner_option_values.append(value);
			}
			break;
			case TWTY_BOOL:
			{
				TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[i];
				if ((BOOL)currentValue) {
					json_scanner_option_values.append(true);
				}
				else {
					json_scanner_option_values.append(false);
				}

			}
			break;
			/* important to count the null byte */
			case TWTY_STR32:
			{
				pTW_STR32 pStr32 = &((pTW_STR32)(&pENUMERATION->ItemList))[i];
				pStr32 += (i * 33);
				sprintf(str, "%s", pStr32);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_STR64:
			{
				pTW_STR64 pStr64 = &((pTW_STR64)(&pENUMERATION->ItemList))[i];
				pStr64 += (i * 65);
				sprintf(str, "%s", pStr64);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_STR128:
			{
				pTW_STR128 pStr128 = &((pTW_STR128)(&pENUMERATION->ItemList))[i];
				pStr128 += (i * 129);
				sprintf(str, "%s", pStr128);
				json_scanner_option_values.append(str);
			}
			break;
			case TWTY_STR255:
			{
				pTW_STR255 pStr255 = &((pTW_STR255)(&pENUMERATION->ItemList))[i];
				pStr255 += (i * 256);
				sprintf(str, "%s", pStr255);
				json_scanner_option_values.append(str);
			}
			break;
			//					case TWTY_STR1024:
			//					case TWTY_UNI512:
			//						break;
			default:
				break;
			}
		}
		json_scanner_option["values"] = json_scanner_option_values;
	}
	json_scanner_option["itemType"] = "TWON_ENUMERATION";
	break;
	case TWON_ONEVALUE:
		json_scanner_option["itemType"] = "TWON_ONEVALUE";
		break;
	case TWON_RANGE:
		json_scanner_option["itemType"] = "TWON_RANGE";
		json_scanner_option["minValue"] = (Json::Int)pRANGE->MinValue;
		json_scanner_option["maxValue"] = (Json::Int)pRANGE->MaxValue;
		json_scanner_option["stepSize"] = (Json::Int)pRANGE->StepSize;
		json_scanner_option["defaultValue"] = (Json::Int)pRANGE->DefaultValue;
		break;
	}

}

void twain_get_option_value(TW_IDENTITY *tw_identity,
                            TW_IDENTITY *tw_source_identity,
                            TW_CAPABILITY *tw_capability,
                            void *_entrypoint,
                            Json::Value& json_scanner_options, Json::Value& json_scanner_option_values) {
  
#if USE_TWAIN_DSM
    TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
#else
    void *tw_entrypoint = 0;
#endif
    
    std::string optionName;
    twain_get_capability_option_name(tw_capability->Cap, optionName);
    
    tw_capability->ConType = TWON_ONEVALUE;
    tw_capability->hContainer = 0;

    if(TWRC_SUCCESS == DSM_Entry(
                                 tw_identity,
                                 tw_source_identity,
                                 DG_CONTROL,
                                 DAT_CAPABILITY,
                                 MSG_GET,
                                 (TW_MEMREF)tw_capability))
    {
		TW_MEMREF mem = DSM::Lock(tw_entrypoint, tw_capability->hContainer);

		twain_get_capability_value(tw_capability, mem, json_scanner_options[optionName]);
		twain_get_capability_param(tw_capability, mem, json_scanner_option_values[optionName]);

        DSM::Unlock(tw_entrypoint, tw_capability->hContainer);
        DSM::Free(tw_entrypoint, tw_capability->hContainer);
    }
        
  }

TW_INT16 twain_get_condition(TW_IDENTITY *tw_identity)
{
	TW_INT16 condition = 0;
	
	TW_STATUS status;
	memset(&status, 0, sizeof(TW_STATUS));
	
	if(TWRC_SUCCESS == DSM_Entry(
															 tw_identity,
															 0,
															 DG_CONTROL,
															 DAT_STATUS,
															 MSG_GET,
															 (TW_MEMREF)&status))
	{
		condition = status.ConditionCode;
	}
	return condition;
}

TW_UINT16 twain_dsm_open(TW_IDENTITY *tw_identity,
												 TW_USERINTERFACE *tw_userinterface,
												 void *tw_entrypoint,
												 HWND *tw_parent)
{
	TW_UINT16 tw_ret = DSM_Entry(
															 tw_identity,
															 0,
															 DG_CONTROL,
															 DAT_PARENT,
															 MSG_OPENDSM,
															 (TW_MEMREF)tw_parent);
	if(tw_ret == TWRC_SUCCESS)
	{
#if USE_TWAIN_DSM
		tw_userinterface->hParent = (*tw_parent);
		if((tw_identity->SupportedGroups & DF_DSM2) == DF_DSM2)
		{
			DSM_Entry(
								tw_identity,
								0,
								DG_CONTROL,
								DAT_ENTRYPOINT,
								MSG_GET,
								(TW_MEMREF)tw_entrypoint);
		}/* DF_DSM2 */
#endif
	}/* MSG_OPENDSM */
	
	return tw_ret;
}

TW_UINT16 twain_dsm_close(TW_IDENTITY *tw_identity,
												 HWND *tw_parent)
{
	TW_UINT16 tw_ret = DSM_Entry(
															 tw_identity,
															 0,
															 DG_CONTROL,
															 DAT_PARENT,
															 MSG_CLOSEDSM,
															 (TW_MEMREF)tw_parent);
	
	return tw_ret;
}

TW_UINT16 twain_source_open(TW_IDENTITY *tw_identity,
														TW_IDENTITY *tw_source_identity,
														C_TEXT& name)
{
	TW_UINT16 ret = twain_get_source(tw_identity, name, tw_source_identity);
	
	if(TWRC_SUCCESS == ret)
	{
		ret = DSM_Entry(
										tw_identity,
										0,
										DG_CONTROL,
										DAT_IDENTITY,
										MSG_OPENDS,
										(TW_MEMREF)tw_source_identity);
	}
	
	return ret;
}

TW_UINT16 twain_source_close(TW_IDENTITY *tw_identity,
														 TW_IDENTITY *tw_source_identity)
{
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														0,
														DG_CONTROL,
														DAT_IDENTITY,
														MSG_CLOSEDS,
														(TW_MEMREF)tw_source_identity);
	
	return ret;
}

TW_UINT16 twain_source_enable(TW_IDENTITY *tw_identity,
															TW_IDENTITY *tw_source_identity,
															TW_USERINTERFACE *tw_userinterface)
{
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														tw_source_identity,
														DG_CONTROL,
														DAT_USERINTERFACE,
														MSG_ENABLEDS,
														(TW_MEMREF)tw_userinterface);
	
	return ret;
}

TW_UINT16 twain_source_disable(TW_IDENTITY *tw_identity,
															 TW_IDENTITY *tw_source_identity,
															 TW_USERINTERFACE *tw_userinterface)
{
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														tw_source_identity,
														DG_CONTROL,
														DAT_USERINTERFACE,
														MSG_DISABLEDS,
														(TW_MEMREF)tw_userinterface);
	
	return ret;
}


TW_INT16 twain_get_default_source(TW_IDENTITY *tw_identity, TW_IDENTITY *tw_source_identity)
{
	memset(tw_source_identity, 0, sizeof(TW_IDENTITY));
	
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														0,
														DG_CONTROL,
														DAT_IDENTITY,
														MSG_GETDEFAULT,
														(TW_MEMREF)tw_source_identity);
	
	return ret;
}

void twain_configure(TW_IDENTITY *tw_identity,
										 TW_USERINTERFACE *tw_userinterface,
										 void *_entrypoint,
										 HWND *tw_parent,
										 TW_UINT16 majorNum, TW_UINT16 minorNum, TW_UINT16 language, TW_UINT16 country)
{
	/* init */
	memset(tw_identity, 0, sizeof(TW_IDENTITY));
	memset(tw_userinterface, 0, sizeof(TW_USERINTERFACE));
	
	tw_userinterface->ShowUI = false;
	tw_userinterface->ModalUI = false;
	
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	memset(tw_entrypoint, 0, sizeof(TW_ENTRYPOINT));
	tw_entrypoint->Size = sizeof(TW_ENTRYPOINT);
#endif
	
	*tw_parent = NULL;
	
	tw_identity->Version.Language = language;
	tw_identity->Version.Country = country;
	
	char _majorNum[3];
	sprintf(_majorNum, "%X", majorNum);
	char _minorNum[3];
	sprintf(_minorNum, "%X", minorNum);
	tw_identity->Id = 0;//always 0
	tw_identity->Version.MajorNum = atoi(_majorNum);
	tw_identity->Version.MinorNum = atoi(_minorNum);
	char _versionInfo[6];
	sprintf(_versionInfo, "%X.%X", majorNum, minorNum);
	SSTRCPY(tw_identity->Version.Info, sizeof(tw_identity->Version.Info), _versionInfo);
	
	//protocol
	tw_identity->ProtocolMajor = TWON_PROTOCOLMAJOR;
	tw_identity->ProtocolMinor = TWON_PROTOCOLMINOR;
	/*
	 note: TWAIN.framework on Mac is 1.9
	 TWAIN_32.DLL on Windows is 1.x and 32-bit only
	 TWAINDSM.DLL on Windows is 2.3 and 32-bit or 64-bit
	 TWAINDSM.DYLIB does not work on Mac (dlopen can't open .ds)
	 */
#if USE_TWAIN_DSM
	tw_identity->SupportedGroups = DF_APP2 | DG_IMAGE | DG_CONTROL;
#else
	tw_identity->SupportedGroups = DG_IMAGE | DG_CONTROL;
#endif
	
	SSTRCPY(tw_identity->Manufacturer, sizeof(tw_identity->Manufacturer), PRODUCT_VENDOR_NAME);
	SSTRCPY(tw_identity->ProductFamily, sizeof(tw_identity->ProductFamily), PRODUCT_FAMILY_NAME);
	SSTRCPY(tw_identity->ProductName, sizeof(tw_identity->ProductName), PRODUCT_NAME);
}

TW_INT16 twain_get_source(TW_IDENTITY *tw_identity, C_TEXT& name, TW_IDENTITY *tw_source_identity)
{
	TW_UINT16 ret = TWRC_FAILURE;
	
	CUTF8String _name;
	name.copyUTF8String(&_name);
	
	std::vector<TW_IDENTITY>sources;
	
	twain_get_sources_list(tw_identity, sources);
	
	for(std::vector<TW_IDENTITY>::iterator it = sources.begin(); it < sources.end(); it++)
	{
		TW_IDENTITY identity = *it;
		
		size_t len = strlen((char *)identity.ProductName);
		if(len == _name.length())
		{
			if(0 == strncmp((char *)identity.ProductName, (char *)_name.c_str(), len))
			{
				memcpy(tw_source_identity, &identity, sizeof(TW_IDENTITY));
				ret = TWRC_SUCCESS;
				break;
			}
		}
	}
	if(ret != TWRC_SUCCESS)
	{
		ret = twain_get_default_source(tw_identity, tw_source_identity);
	}
	
	return ret;
}

void twain_get_sources_list(TW_IDENTITY *tw_identity, std::vector<TW_IDENTITY>& sources)
{
	TW_INT16 condition = 0;
	
	TW_IDENTITY tw_source_identity;
	memset(&tw_source_identity, 0, sizeof(TW_IDENTITY));
	
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														0,
														DG_CONTROL,
														DAT_IDENTITY,
														MSG_GETFIRST,
														(TW_MEMREF)&tw_source_identity);
	switch (ret)
	{
		case TWRC_SUCCESS:
			sources.push_back(tw_source_identity);
			do
			{
				memset(&tw_source_identity, 0, sizeof(TW_IDENTITY));
				ret = DSM_Entry(
												tw_identity,
												0,
												DG_CONTROL,
												DAT_IDENTITY,
												MSG_GETNEXT,
												(TW_MEMREF)&tw_source_identity);
				switch (ret)
				{
					case TWRC_SUCCESS:
						sources.push_back(tw_source_identity);
						break;
					case TWRC_ENDOFLIST:
						//TWRC_ENDOFLIST
						break;
					case TWRC_FAILURE:
						condition = twain_get_condition(tw_identity);
						break;
					default:
						
						break;
				}
			}
			while (TWRC_SUCCESS == ret);
			break;
		case TWRC_ENDOFLIST:
			//TWRC_ENDOFLIST
			break;
		case TWRC_FAILURE:
			condition = twain_get_condition(tw_identity);
			break;
		default:
			
			break;
	}
}

TW_HANDLE DSM::Alloc(void *_entrypoint, TW_UINT32 size)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemAllocate)
	{
		return tw_entrypoint->DSM_MemAllocate(size);
	}
	return ::GlobalAlloc(GPTR, size);
#endif
	
	return 0;
}
void DSM::Free(void *_entrypoint, TW_HANDLE h)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemFree)
	{
		return tw_entrypoint->DSM_MemFree(h);
	}
	::GlobalFree(h);
#endif
	
	return;
}
TW_MEMREF DSM::Lock(void *_entrypoint, TW_HANDLE h)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemLock)
	{
		return tw_entrypoint->DSM_MemLock(h);
	}
	return ::GlobalLock(h);
#endif
	
	return 0;
}
void DSM::Unlock(void *_entrypoint, TW_HANDLE h)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemUnlock)
	{
		return tw_entrypoint->DSM_MemUnlock(h);
	}
	::GlobalUnlock(h);
#endif
	
	return;
}

TW_UINT16 twain_get_cap(JSONCPP_STRING& name) {

	TW_UINT16 cap = 0;

	if (name.compare("CAP_XFERCOUNT") == 0)
	{
		cap = CAP_XFERCOUNT; goto exit;
	}
	if (name.compare("ICAP_COMPRESSION") == 0)
	{
		cap = ICAP_COMPRESSION; goto exit;
	}
	if (name.compare("ICAP_PIXELTYPE") == 0)
	{
		cap = ICAP_PIXELTYPE; goto exit;
	}
	if (name.compare("ICAP_UNITS") == 0)
	{
		cap = ICAP_UNITS; goto exit;
	}
	if (name.compare("ICAP_XFERMECH") == 0)
	{
		cap = ICAP_XFERMECH; goto exit;
	}
	if (name.compare("CAP_AUTHOR") == 0)
	{
		cap = CAP_AUTHOR; goto exit;
	}
	if (name.compare("CAP_CAPTION") == 0)
	{
		cap = CAP_CAPTION; goto exit;
	}
	if (name.compare("CAP_FEEDERENABLED") == 0)
	{
		cap = CAP_FEEDERENABLED; goto exit;
	}
	if (name.compare("CAP_FEEDERLOADED") == 0)
	{
		cap = CAP_FEEDERLOADED; goto exit;
	}
	if (name.compare("CAP_TIMEDATE") == 0)
	{
		cap = CAP_TIMEDATE; goto exit;
	}
	if (name.compare("CAP_SUPPORTEDCAPS") == 0)
	{
		cap = CAP_SUPPORTEDCAPS; goto exit;
	}
	if (name.compare("CAP_EXTENDEDCAPS") == 0)
	{
		cap = CAP_EXTENDEDCAPS; goto exit;
	}
	if (name.compare("CAP_AUTOFEED") == 0)
	{
		cap = CAP_AUTOFEED; goto exit;
	}
	if (name.compare("CAP_CLEARPAGE") == 0)
	{
		cap = CAP_CLEARPAGE; goto exit;
	}
	if (name.compare("CAP_FEEDPAGE") == 0)
	{
		cap = CAP_FEEDPAGE; goto exit;
	}
	if (name.compare("CAP_REWINDPAGE") == 0)
	{
		cap = CAP_REWINDPAGE; goto exit;
	}
	if (name.compare("CAP_INDICATORS") == 0)
	{
		cap = CAP_INDICATORS; goto exit;
	}
	if (name.compare("CAP_SUPPORTEDCAPSEXT") == 0)
	{
		cap = CAP_SUPPORTEDCAPSEXT; goto exit;
	}
	if (name.compare("CAP_PAPERDETECTABLE") == 0)
	{
		cap = CAP_PAPERDETECTABLE; goto exit;
	}
	if (name.compare("CAP_UICONTROLLABLE") == 0)
	{
		cap = CAP_UICONTROLLABLE; goto exit;
	}
	if (name.compare("CAP_DEVICEONLINE") == 0)
	{
		cap = CAP_DEVICEONLINE; goto exit;
	}
	if (name.compare("CAP_AUTOSCAN") == 0)
	{
		cap = CAP_AUTOSCAN; goto exit;
	}
	if (name.compare("CAP_THUMBNAILSENABLED") == 0)
	{
		cap = CAP_THUMBNAILSENABLED; goto exit;
	}
	if (name.compare("CAP_DUPLEX") == 0)
	{
		cap = CAP_DUPLEX; goto exit;
	}
	if (name.compare("CAP_DUPLEXENABLED") == 0)
	{
		cap = CAP_DUPLEXENABLED; goto exit;
	}
	if (name.compare("CAP_ENABLEDSUIONLY") == 0)
	{
		cap = CAP_ENABLEDSUIONLY; goto exit;
	}
	if (name.compare("CAP_CUSTOMDSDATA") == 0)
	{
		cap = CAP_CUSTOMDSDATA; goto exit;
	}
	if (name.compare("CAP_ENDORSER") == 0)
	{
		cap = CAP_ENDORSER; goto exit;
	}
	if (name.compare("CAP_JOBCONTROL") == 0)
	{
		cap = CAP_JOBCONTROL; goto exit;
	}
	if (name.compare("CAP_ALARMS") == 0)
	{
		cap = CAP_ALARMS; goto exit;
	}
	if (name.compare("CAP_ALARMVOLUME") == 0)
	{
		cap = CAP_ALARMVOLUME; goto exit;
	}
	if (name.compare("CAP_AUTOMATICCAPTURE") == 0)
	{
		cap = CAP_AUTOMATICCAPTURE; goto exit;
	}
	if (name.compare("CAP_TIMEBEFOREFIRSTCAPTURE") == 0)
	{
		cap = CAP_TIMEBEFOREFIRSTCAPTURE; goto exit;
	}
	if (name.compare("CAP_TIMEBETWEENCAPTURES") == 0)
	{
		cap = CAP_TIMEBETWEENCAPTURES; goto exit;
	}
	if (name.compare("CAP_CLEARBUFFERS") == 0)
	{
		cap = CAP_CLEARBUFFERS; goto exit;
	}
	if (name.compare("CAP_MAXBATCHBUFFERS") == 0)
	{
		cap = CAP_MAXBATCHBUFFERS; goto exit;
	}
	if (name.compare("CAP_DEVICETIMEDATE") == 0)
	{
		cap = CAP_DEVICETIMEDATE; goto exit;
	}
	if (name.compare("CAP_POWERSUPPLY") == 0)
	{
		cap = CAP_POWERSUPPLY; goto exit;
	}
	if (name.compare("CAP_CAMERAPREVIEWUI") == 0)
	{
		cap = CAP_CAMERAPREVIEWUI; goto exit;
	}
	if (name.compare("CAP_DEVICEEVENT") == 0)
	{
		cap = CAP_DEVICEEVENT; goto exit;
	}
	if (name.compare("CAP_SERIALNUMBER") == 0)
	{
		cap = CAP_SERIALNUMBER; goto exit;
	}
	if (name.compare("CAP_PRINTER") == 0)
	{
		cap = CAP_PRINTER; goto exit;
	}
	if (name.compare("CAP_PRINTERENABLED") == 0)
	{
		cap = CAP_PRINTERENABLED; goto exit;
	}
	if (name.compare("CAP_PRINTERINDEX") == 0)
	{
		cap = CAP_PRINTERINDEX; goto exit;
	}
	if (name.compare("CAP_PRINTERMODE") == 0)
	{
		cap = CAP_PRINTERMODE; goto exit;
	}
	if (name.compare("CAP_PRINTERSTRING") == 0)
	{
		cap = CAP_PRINTERSTRING; goto exit;
	}
	if (name.compare("CAP_PRINTERSUFFIX") == 0)
	{
		cap = CAP_PRINTERSUFFIX; goto exit;
	}
	if (name.compare("CAP_LANGUAGE") == 0)
	{
		cap = CAP_LANGUAGE; goto exit;
	}
	if (name.compare("CAP_FEEDERALIGNMENT") == 0)
	{
		cap = CAP_FEEDERALIGNMENT; goto exit;
	}
	if (name.compare("CAP_FEEDERORDER") == 0)
	{
		cap = CAP_FEEDERORDER; goto exit;
	}
	if (name.compare("CAP_REACQUIREALLOWED") == 0)
	{
		cap = CAP_REACQUIREALLOWED; goto exit;
	}
	if (name.compare("CAP_BATTERYMINUTES") == 0)
	{
		cap = CAP_BATTERYMINUTES; goto exit;
	}
	if (name.compare("CAP_BATTERYPERCENTAGE") == 0)
	{
		cap = CAP_BATTERYPERCENTAGE; goto exit;
	}
#if USE_TWAIN_DSM
	if (name.compare("CAP_CAMERASIDE") == 0)
	{
		cap = CAP_CAMERASIDE; goto exit;
	}
	if (name.compare("CAP_SEGMENTED") == 0)
	{
		cap = CAP_SEGMENTED; goto exit;
	}
	if (name.compare("CAP_CAMERAENABLED") == 0)
	{
		cap = CAP_CAMERAENABLED; goto exit;
	}
	if (name.compare("CAP_CAMERAORDER") == 0)
	{
		cap = CAP_CAMERAORDER; goto exit;
	}
	if (name.compare("CAP_MICRENABLED") == 0)
	{
		cap = CAP_MICRENABLED; goto exit;
	}
	if (name.compare("CAP_FEEDERPREP") == 0)
	{
		cap = CAP_FEEDERPREP; goto exit;
	}
	if (name.compare("CAP_FEEDERPOCKET") == 0)
	{
		cap = CAP_FEEDERPOCKET; goto exit;
	}
	if (name.compare("CAP_AUTOMATICSENSEMEDIUM") == 0)
	{
		cap = CAP_AUTOMATICSENSEMEDIUM; goto exit;
	}
	if (name.compare("CAP_CUSTOMINTERFACEGUID") == 0)
	{
		cap = CAP_CUSTOMINTERFACEGUID; goto exit;
	}
	if (name.compare("CAP_SUPPORTEDCAPSSEGMENTUNIQUE") == 0)
	{
		cap = CAP_SUPPORTEDCAPSSEGMENTUNIQUE; goto exit;
	}
	if (name.compare("CAP_SUPPORTEDDATS") == 0)
	{
		cap = CAP_SUPPORTEDDATS; goto exit;
	}
	if (name.compare("CAP_DOUBLEFEEDDETECTION") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTION; goto exit;
	}
	if (name.compare("CAP_DOUBLEFEEDDETECTIONLENGTH") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTIONLENGTH; goto exit;
	}
	if (name.compare("CAP_DOUBLEFEEDDETECTIONSENSITIVITY") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTIONSENSITIVITY; goto exit;
	}
	if (name.compare("CAP_DOUBLEFEEDDETECTIONRESPONSE") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTIONRESPONSE; goto exit;
	}
	if (name.compare("CAP_PAPERHANDLING") == 0)
	{
		cap = CAP_PAPERHANDLING; goto exit;
	}
	if (name.compare("CAP_INDICATORSMODE") == 0)
	{
		cap = CAP_INDICATORSMODE; goto exit;
	}
	if (name.compare("CAP_PRINTERVERTICALOFFSET") == 0)
	{
		cap = CAP_PRINTERVERTICALOFFSET; goto exit;
	}
	if (name.compare("CAP_POWERSAVETIME") == 0)
	{
		cap = CAP_POWERSAVETIME; goto exit;
	}
	if (name.compare("CAP_PRINTERCHARROTATION") == 0)
	{
		cap = CAP_PRINTERCHARROTATION; goto exit;
	}
	if (name.compare("CAP_PRINTERFONTSTYLE") == 0)
	{
		cap = CAP_PRINTERFONTSTYLE; goto exit;
	}
	if (name.compare("CAP_PRINTERINDEXLEADCHAR") == 0)
	{
		cap = CAP_PRINTERINDEXLEADCHAR; goto exit;
	}
	if (name.compare("CAP_PRINTERINDEXMAXVALUE") == 0)
	{
		cap = CAP_PRINTERINDEXMAXVALUE; goto exit;
	}
	if (name.compare("CAP_PRINTERINDEXNUMDIGITS") == 0)
	{
		cap = CAP_PRINTERINDEXNUMDIGITS; goto exit;
	}
	if (name.compare("CAP_PRINTERINDEXSTEP") == 0)
	{
		cap = CAP_PRINTERINDEXSTEP; goto exit;
	}
	if (name.compare("CAP_PRINTERINDEXTRIGGER") == 0)
	{
		cap = CAP_PRINTERINDEXTRIGGER; goto exit;
	}
	if (name.compare("CAP_PRINTERSTRINGPREVIEW") == 0)
	{
		cap = CAP_PRINTERSTRINGPREVIEW; goto exit;
	}
	if (name.compare("ICAP_AUTODISCARDBLANKPAGES") == 0)
	{
		cap = ICAP_AUTODISCARDBLANKPAGES; goto exit;
	}
	if (name.compare("ICAP_FEEDERTYPE") == 0)
	{
		cap = ICAP_FEEDERTYPE; goto exit;
	}
	if (name.compare("ICAP_ICCPROFILE") == 0)
	{
		cap = ICAP_ICCPROFILE; goto exit;
	}
	if (name.compare("ICAP_AUTOSIZE") == 0)
	{
		cap = ICAP_AUTOSIZE; goto exit;
	}
	if (name.compare("ICAP_AUTOMATICCROPUSESFRAME") == 0)
	{
		cap = ICAP_AUTOMATICCROPUSESFRAME; goto exit;
	}
	if (name.compare("ICAP_AUTOMATICLENGTHDETECTION") == 0)
	{
		cap = ICAP_AUTOMATICLENGTHDETECTION; goto exit;
	}
	if (name.compare("ICAP_AUTOMATICCOLORENABLED") == 0)
	{
		cap = ICAP_AUTOMATICCOLORENABLED; goto exit;
	}
	if (name.compare("ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE") == 0)
	{
		cap = ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE; goto exit;
	}
	if (name.compare("ICAP_COLORMANAGEMENTENABLED") == 0)
	{
		cap = ICAP_COLORMANAGEMENTENABLED; goto exit;
	}
	if (name.compare("ICAP_IMAGEMERGE") == 0)
	{
		cap = ICAP_IMAGEMERGE; goto exit;
	}
	if (name.compare("ICAP_IMAGEMERGEHEIGHTTHRESHOLD") == 0)
	{
		cap = ICAP_IMAGEMERGEHEIGHTTHRESHOLD; goto exit;
	}
	if (name.compare("ICAP_SUPPORTEDEXTIMAGEINFO") == 0)
	{
		cap = ICAP_SUPPORTEDEXTIMAGEINFO; goto exit;
	}
	if (name.compare("ICAP_FILMTYPE") == 0)
	{
		cap = ICAP_FILMTYPE; goto exit;
	}
	if (name.compare("ICAP_MIRROR") == 0)
	{
		cap = ICAP_MIRROR; goto exit;
	}
	if (name.compare("ICAP_JPEGSUBSAMPLING") == 0)
	{
		cap = ICAP_JPEGSUBSAMPLING; goto exit;
	}
#endif
	if (name.compare("ICAP_AUTOBRIGHT") == 0)
	{
		cap = ICAP_AUTOBRIGHT; goto exit;
	}
	if (name.compare("ICAP_BRIGHTNESS") == 0)
	{
		cap = ICAP_BRIGHTNESS; goto exit;
	}
	if (name.compare("ICAP_CONTRAST") == 0)
	{
		cap = ICAP_CONTRAST; goto exit;
	}
	if (name.compare("ICAP_CUSTHALFTONE") == 0)
	{
		cap = ICAP_CUSTHALFTONE; goto exit;
	}
	if (name.compare("ICAP_EXPOSURETIME") == 0)
	{
		cap = ICAP_EXPOSURETIME; goto exit;
	}
	if (name.compare("ICAP_FILTER") == 0)
	{
		cap = ICAP_FILTER; goto exit;
	}
	if (name.compare("ICAP_FLASHUSED") == 0)
	{
		cap = ICAP_FLASHUSED; goto exit;
	}
	if (name.compare("ICAP_GAMMA") == 0)
	{
		cap = ICAP_GAMMA; goto exit;
	}
	if (name.compare("ICAP_HALFTONES") == 0)
	{
		cap = ICAP_HALFTONES; goto exit;
	}
	if (name.compare("ICAP_HIGHLIGHT") == 0)
	{
		cap = ICAP_HIGHLIGHT; goto exit;
	}
	if (name.compare("ICAP_IMAGEFILEFORMAT") == 0)
	{
		cap = ICAP_IMAGEFILEFORMAT; goto exit;
	}
	if (name.compare("ICAP_LAMPSTATE") == 0)
	{
		cap = ICAP_LAMPSTATE; goto exit;
	}
	if (name.compare("ICAP_LIGHTSOURCE") == 0)
	{
		cap = ICAP_LIGHTSOURCE; goto exit;
	}
	if (name.compare("ICAP_ORIENTATION") == 0)
	{
		cap = ICAP_ORIENTATION; goto exit;
	}
	if (name.compare("ICAP_PHYSICALWIDTH") == 0)
	{
		cap = ICAP_PHYSICALWIDTH; goto exit;
	}
	if (name.compare("ICAP_PHYSICALHEIGHT") == 0)
	{
		cap = ICAP_PHYSICALHEIGHT; goto exit;
	}
	if (name.compare("ICAP_SHADOW") == 0)
	{
		cap = ICAP_SHADOW; goto exit;
	}
	if (name.compare("ICAP_FRAMES") == 0)
	{
		cap = ICAP_FRAMES; goto exit;
	}
	if (name.compare("ICAP_XNATIVERESOLUTION") == 0)
	{
		cap = ICAP_XNATIVERESOLUTION; goto exit;
	}
	if (name.compare("ICAP_YNATIVERESOLUTION") == 0)
	{
		cap = ICAP_YNATIVERESOLUTION; goto exit;
	}
	if (name.compare("ICAP_XRESOLUTION") == 0)
	{
		cap = ICAP_XRESOLUTION; goto exit;
	}
	if (name.compare("ICAP_YRESOLUTION") == 0)
	{
		cap = ICAP_YRESOLUTION; goto exit;
	}
	if (name.compare("ICAP_MAXFRAMES") == 0)
	{
		cap = ICAP_MAXFRAMES; goto exit;
	}
	if (name.compare("ICAP_TILES") == 0)
	{
		cap = ICAP_TILES; goto exit;
	}
	if (name.compare("ICAP_BITORDER") == 0)
	{
		cap = ICAP_BITORDER; goto exit;
	}
	if (name.compare("ICAP_CCITTKFACTOR") == 0)
	{
		cap = ICAP_CCITTKFACTOR; goto exit;
	}
	if (name.compare("ICAP_LIGHTPATH") == 0)
	{
		cap = ICAP_LIGHTPATH; goto exit;
	}
	if (name.compare("ICAP_PIXELFLAVOR") == 0)
	{
		cap = ICAP_PIXELFLAVOR; goto exit;
	}
	if (name.compare("ICAP_PLANARCHUNKY") == 0)
	{
		cap = ICAP_PLANARCHUNKY; goto exit;
	}
	if (name.compare("ICAP_ROTATION") == 0)
	{
		cap = ICAP_ROTATION; goto exit;
	}
	if (name.compare("ICAP_SUPPORTEDSIZES") == 0)
	{
		cap = ICAP_SUPPORTEDSIZES; goto exit;
	}
	if (name.compare("ICAP_THRESHOLD") == 0)
	{
		cap = ICAP_THRESHOLD; goto exit;
	}
	if (name.compare("ICAP_XSCALING") == 0)
	{
		cap = ICAP_XSCALING; goto exit;
	}
	if (name.compare("ICAP_YSCALING") == 0)
	{
		cap = ICAP_YSCALING; goto exit;
	}
	if (name.compare("ICAP_BITORDERCODES") == 0)
	{
		cap = ICAP_BITORDERCODES; goto exit;
	}
	if (name.compare("ICAP_PIXELFLAVORCODES") == 0)
	{
		cap = ICAP_PIXELFLAVORCODES; goto exit;
	}
	if (name.compare("ICAP_JPEGPIXELTYPE") == 0)
	{
		cap = ICAP_JPEGPIXELTYPE; goto exit;
	}
	if (name.compare("ICAP_TIMEFILL") == 0)
	{
		cap = ICAP_TIMEFILL; goto exit;
	}
	if (name.compare("ICAP_BITDEPTH") == 0)
	{
		cap = ICAP_BITDEPTH; goto exit;
	}
	if (name.compare("ICAP_BITDEPTHREDUCTION") == 0)
	{
		cap = ICAP_BITDEPTHREDUCTION; goto exit;
	}
	if (name.compare("ICAP_UNDEFINEDIMAGESIZE") == 0)
	{
		cap = ICAP_UNDEFINEDIMAGESIZE; goto exit;
	}
	if (name.compare("ICAP_IMAGEDATASET") == 0)
	{
		cap = ICAP_IMAGEDATASET; goto exit;
	}
	if (name.compare("ICAP_EXTIMAGEINFO") == 0)
	{
		cap = ICAP_EXTIMAGEINFO; goto exit;
	}
	if (name.compare("ICAP_MINIMUMHEIGHT") == 0)
	{
		cap = ICAP_MINIMUMHEIGHT; goto exit;
	}
	if (name.compare("ICAP_MINIMUMWIDTH") == 0)
	{
		cap = ICAP_MINIMUMWIDTH; goto exit;
	}
	if (name.compare("ICAP_FLIPROTATION") == 0)
	{
		cap = ICAP_FLIPROTATION; goto exit;
	}
	if (name.compare("ICAP_BARCODEDETECTIONENABLED") == 0)
	{
		cap = ICAP_BARCODEDETECTIONENABLED; goto exit;
	}
	if (name.compare("ICAP_SUPPORTEDBARCODETYPES") == 0)
	{
		cap = ICAP_SUPPORTEDBARCODETYPES; goto exit;
	}
	if (name.compare("ICAP_BARCODEMAXSEARCHPRIORITIES") == 0)
	{
		cap = ICAP_BARCODEMAXSEARCHPRIORITIES; goto exit;
	}
	if (name.compare("ICAP_BARCODESEARCHPRIORITIES") == 0)
	{
		cap = ICAP_BARCODESEARCHPRIORITIES; goto exit;
	}
	if (name.compare("ICAP_BARCODESEARCHMODE") == 0)
	{
		cap = ICAP_BARCODESEARCHMODE; goto exit;
	}
	if (name.compare("ICAP_BARCODEMAXRETRIES") == 0)
	{
		cap = ICAP_BARCODEMAXRETRIES; goto exit;
	}
	if (name.compare("ICAP_BARCODETIMEOUT") == 0)
	{
		cap = ICAP_BARCODETIMEOUT; goto exit;
	}
	if (name.compare("ICAP_ZOOMFACTOR") == 0)
	{
		cap = ICAP_ZOOMFACTOR; goto exit;
	}
	if (name.compare("ICAP_PATCHCODEDETECTIONENABLED") == 0)
	{
		cap = ICAP_PATCHCODEDETECTIONENABLED; goto exit;
	}
	if (name.compare("ICAP_SUPPORTEDPATCHCODETYPES") == 0)
	{
		cap = ICAP_SUPPORTEDPATCHCODETYPES; goto exit;
	}
	if (name.compare("ICAP_PATCHCODEMAXSEARCHPRIORITIES") == 0)
	{
		cap = ICAP_PATCHCODEMAXSEARCHPRIORITIES; goto exit;
	}
	if (name.compare("ICAP_PATCHCODESEARCHPRIORITIES") == 0)
	{
		cap = ICAP_PATCHCODESEARCHPRIORITIES; goto exit;
	}
	if (name.compare("ICAP_PATCHCODESEARCHMODE") == 0)
	{
		cap = ICAP_PATCHCODESEARCHMODE; goto exit;
	}
	if (name.compare("ICAP_PATCHCODEMAXRETRIES") == 0)
	{
		cap = ICAP_PATCHCODEMAXRETRIES; goto exit;
	}
	if (name.compare("ICAP_PATCHCODETIMEOUT") == 0)
	{
		cap = ICAP_PATCHCODETIMEOUT; goto exit;
	}
	if (name.compare("ICAP_FLASHUSED2") == 0)
	{
		cap = ICAP_FLASHUSED2; goto exit;
	}
	if (name.compare("ICAP_IMAGEFILTER") == 0)
	{
		cap = ICAP_IMAGEFILTER; goto exit;
	}
	if (name.compare("ICAP_NOISEFILTER") == 0)
	{
		cap = ICAP_NOISEFILTER; goto exit;
	}
	if (name.compare("ICAP_OVERSCAN") == 0)
	{
		cap = ICAP_OVERSCAN; goto exit;
	}
	if (name.compare("ICAP_AUTOMATICBORDERDETECTION") == 0)
	{
		cap = ICAP_AUTOMATICBORDERDETECTION; goto exit;
	}
	if (name.compare("ICAP_AUTOMATICDESKEW") == 0)
	{
		cap = ICAP_AUTOMATICDESKEW; goto exit;
	}
	if (name.compare("ICAP_AUTOMATICROTATE") == 0)
	{
		cap = ICAP_AUTOMATICROTATE; goto exit;
	}
	if (name.compare("ICAP_JPEGQUALITY") == 0)
	{
		cap = ICAP_JPEGQUALITY; goto exit;
	}

exit:
	return cap;
}

int getSizeForItemType(TW_UINT16 itemType) {

	switch (itemType)
	{
	case TWTY_INT8:
		return sizeof(TW_INT8);
		break;
	case TWTY_INT16:
		return sizeof(TW_INT16);
		break;
	case TWTY_INT32:
		return sizeof(TW_INT32);
		break;
	case TWTY_UINT8:
		return sizeof(TW_UINT8);
		break;
	case TWTY_UINT16:
		return sizeof(TW_UINT16);
		break;
	case TWTY_UINT32:
		return sizeof(TW_UINT32);
		break;
	case TWTY_BOOL:
		return sizeof(TW_BOOL);
		break;
	case TWTY_FIX32:
		return sizeof(TW_FIX32);
		break;
	case TWTY_FRAME:
		return sizeof(TW_FRAME);
		break;
	case TWTY_STR32:
		return sizeof(TW_STR32);
		break;
	case TWTY_STR64:
		return sizeof(TW_STR64);
		break;
	case TWTY_STR128:
		return sizeof(TW_STR128);
		break;
	case TWTY_STR255:
		return sizeof(TW_STR255);
		break;
#if USE_TWAIN_DSM
	case TWTY_STR1024:
		return sizeof(TW_STR1024);
		break;
	case TWTY_UNI512:
		return sizeof(TW_UNI512);
		break;
	case TWTY_HANDLE:
		return sizeof(TW_HANDLE);
		break;
#endif
	default:
		break;
	}
	return 0;
}

int json_get_cap_constant(Json::Value& value, TW_UINT16 cap) {

	JSONCPP_STRING strValue;

	if (value.isString())
	{
		strValue = value.asString();
	}

	int v = 0;

	if (value.isInt())
	{
		v = value.asInt();
	}

	switch (cap)
	{
		//convert to constant
#if USE_TWAIN_DSM
	case ICAP_AUTOSIZE:
	{
		if (strValue.compare("TWAS_NONE") == 0)
		{
			v = TWAS_NONE; goto exit2;
		}
		if (strValue.compare("TWAS_AUTO") == 0)
		{
			v = TWAS_AUTO; goto exit2;
		}
		if (strValue.compare("TWAS_CURRENT") == 0)
		{
			v = TWAS_CURRENT; goto exit2;
		}

	}
	break;
	case ICAP_AUTODISCARDBLANKPAGES:
	{
		if (strValue.compare("TWBP_DISABLE") == 0)
		{
			v = TWBP_DISABLE; goto exit2;
		}
		if (strValue.compare("TWBP_AUTO") == 0)
		{
			v = TWBP_AUTO; goto exit2;
		}

	}
	break;
	case CAP_CAMERASIDE:
	{
		if (strValue.compare("TWCS_BOTH") == 0)
		{
			v = TWCS_BOTH; goto exit2;
		}
		if (strValue.compare("TWCS_TOP") == 0)
		{
			v = TWCS_TOP; goto exit2;
		}
		if (strValue.compare("TWCS_BOTTOM") == 0)
		{
			v = TWCS_BOTTOM; goto exit2;
		}

	}
	break;
	case ICAP_FEEDERTYPE:
	{
		if (strValue.compare("TWFE_GENERAL") == 0)
		{
			v = TWFE_GENERAL; goto exit2;
		}
		if (strValue.compare("TWFE_PHOTO") == 0)
		{
			v = TWFE_PHOTO; goto exit2;
		}

	}
	break;
	case CAP_FEEDERPOCKET:
	{
		if (strValue.compare("TWFP_POCKETERROR") == 0)
		{
			v = TWFP_POCKETERROR; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET1") == 0)
		{
			v = TWFP_POCKET1; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET2") == 0)
		{
			v = TWFP_POCKET2; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET3") == 0)
		{
			v = TWFP_POCKET3; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET4") == 0)
		{
			v = TWFP_POCKET4; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET5") == 0)
		{
			v = TWFP_POCKET5; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET6") == 0)
		{
			v = TWFP_POCKET6; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET7") == 0)
		{
			v = TWFP_POCKET7; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET8") == 0)
		{
			v = TWFP_POCKET8; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET9") == 0)
		{
			v = TWFP_POCKET9; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET10") == 0)
		{
			v = TWFP_POCKET10; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET11") == 0)
		{
			v = TWFP_POCKET11; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET12") == 0)
		{
			v = TWFP_POCKET12; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET13") == 0)
		{
			v = TWFP_POCKET13; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET14") == 0)
		{
			v = TWFP_POCKET14; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET15") == 0)
		{
			v = TWFP_POCKET15; goto exit2;
		}
		if (strValue.compare("TWFP_POCKET16") == 0)
		{
			v = TWFP_POCKET16; goto exit2;
		}

	}
	break;
	case ICAP_ICCPROFILE:
	{
		if (strValue.compare("TWIC_NONE") == 0)
		{
			v = TWIC_NONE; goto exit2;
		}
		if (strValue.compare("TWIC_LINK") == 0)
		{
			v = TWIC_LINK; goto exit2;
		}
		if (strValue.compare("TWIC_EMBED") == 0)
		{
			v = TWIC_EMBED; goto exit2;
		}

	}
	break;
	case ICAP_IMAGEMERGE:
	{
		if (strValue.compare("TWIM_NONE") == 0)
		{
			v = TWIM_NONE; goto exit2;
		}
		if (strValue.compare("TWIM_FRONTONTOP") == 0)
		{
			v = TWIM_FRONTONTOP; goto exit2;
		}
		if (strValue.compare("TWIM_FRONTONBOTTOM") == 0)
		{
			v = TWIM_FRONTONBOTTOM; goto exit2;
		}
		if (strValue.compare("TWIM_FRONTONLEFT") == 0)
		{
			v = TWIM_FRONTONLEFT; goto exit2;
		}
		if (strValue.compare("TWIM_FRONTONRIGHT") == 0)
		{
			v = TWIM_FRONTONRIGHT; goto exit2;
		}

	}
	break;
	case CAP_SEGMENTED:
	{
		if (strValue.compare("TWSG_NONE") == 0)
		{
			v = TWSG_NONE; goto exit2;
		}
		if (strValue.compare("TWSG_AUTO") == 0)
		{
			v = TWSG_AUTO; goto exit2;
		}
		if (strValue.compare("TWSG_MANUAL") == 0)
		{
			v = TWSG_MANUAL; goto exit2;
		}

	}
	break;
#endif
	case CAP_ALARMS:
	{
		if (strValue.compare("TWAL_ALARM") == 0)
		{
			v = TWAL_ALARM; goto exit2;
		}
		if (strValue.compare("TWAL_FEEDERERROR") == 0)
		{
			v = TWAL_FEEDERERROR; goto exit2;
		}
		if (strValue.compare("TWAL_FEEDERWARNING") == 0)
		{
			v = TWAL_FEEDERWARNING; goto exit2;
		}
		if (strValue.compare("TWAL_BARCODE") == 0)
		{
			v = TWAL_BARCODE; goto exit2;
		}
		if (strValue.compare("TWAL_DOUBLEFEED") == 0)
		{
			v = TWAL_DOUBLEFEED; goto exit2;
		}
		if (strValue.compare("TWAL_JAM") == 0)
		{
			v = TWAL_JAM; goto exit2;
		}
		if (strValue.compare("TWAL_PATCHCODE") == 0)
		{
			v = TWAL_PATCHCODE; goto exit2;
		}
		if (strValue.compare("TWAL_POWER") == 0)
		{
			v = TWAL_POWER; goto exit2;
		}
		if (strValue.compare("TWAL_SKEW") == 0)
		{
			v = TWAL_SKEW; goto exit2;
		}

	}
	break;
	case ICAP_COMPRESSION:
	{
		if (strValue.compare("TWCP_NONE") == 0)
		{
			v = TWCP_NONE; goto exit2;
		}
		if (strValue.compare("TWCP_PACKBITS") == 0)
		{
			v = TWCP_PACKBITS; goto exit2;
		}
		if (strValue.compare("TWCP_GROUP31D") == 0)
		{
			v = TWCP_GROUP31D; goto exit2;
		}
		if (strValue.compare("TWCP_GROUP31DEOL") == 0)
		{
			v = TWCP_GROUP31DEOL; goto exit2;
		}
		if (strValue.compare("TWCP_GROUP32D") == 0)
		{
			v = TWCP_GROUP32D; goto exit2;
		}
		if (strValue.compare("TWCP_GROUP4") == 0)
		{
			v = TWCP_GROUP4; goto exit2;
		}
		if (strValue.compare("TWCP_JPEG") == 0)
		{
			v = TWCP_JPEG; goto exit2;
		}
		if (strValue.compare("TWCP_LZW") == 0)
		{
			v = TWCP_LZW; goto exit2;
		}
		if (strValue.compare("TWCP_JBIG") == 0)
		{
			v = TWCP_JBIG; goto exit2;
		}
		if (strValue.compare("TWCP_PNG") == 0)
		{
			v = TWCP_PNG; goto exit2;
		}
		if (strValue.compare("TWCP_RLE4") == 0)
		{
			v = TWCP_RLE4; goto exit2;
		}
		if (strValue.compare("TWCP_RLE8") == 0)
		{
			v = TWCP_RLE8; goto exit2;
		}
		if (strValue.compare("TWCP_BITFIELDS") == 0)
		{
			v = TWCP_BITFIELDS; goto exit2;
		}

	}
	break;
	case ICAP_BARCODESEARCHMODE:
	{
		if (strValue.compare("TWBD_HORZ") == 0)
		{
			v = TWBD_HORZ; goto exit2;
		}
		if (strValue.compare("TWBD_VERT") == 0)
		{
			v = TWBD_VERT; goto exit2;
		}
		if (strValue.compare("TWBD_HORZVERT") == 0)
		{
			v = TWBD_HORZVERT; goto exit2;
		}
		if (strValue.compare("TWBD_VERTHORZ") == 0)
		{
			v = TWBD_VERTHORZ; goto exit2;
		}

	}
	break;
	case ICAP_BITORDER:
	{
		if (strValue.compare("TWBO_LSBFIRST") == 0)
		{
			v = TWBO_LSBFIRST; goto exit2;
		}
		if (strValue.compare("TWBO_MSBFIRST") == 0)
		{
			v = TWBO_MSBFIRST; goto exit2;
		}

	}
	break;
	case ICAP_BITDEPTHREDUCTION:
	{
		if (strValue.compare("TWBR_THRESHOLD") == 0)
		{
			v = TWBR_THRESHOLD; goto exit2;
		}
		if (strValue.compare("TWBR_HALFTONE") == 0)
		{
			v = TWBR_HALFTONE; goto exit2;
		}
		if (strValue.compare("TWBR_CUSTHALFTONE") == 0)
		{
			v = TWBR_CUSTHALFTONE; goto exit2;
		}
		if (strValue.compare("TWBR_DIFFUSION") == 0)
		{
			v = TWBR_DIFFUSION; goto exit2;
		}

	}
	break;
	case ICAP_SUPPORTEDBARCODETYPES:
	case TWEI_BARCODETYPE:
	{
		if (strValue.compare("TWBT_3OF9") == 0)
		{
			v = TWBT_3OF9; goto exit2;
		}
		if (strValue.compare("TWBT_2OF5INTERLEAVED") == 0)
		{
			v = TWBT_2OF5INTERLEAVED; goto exit2;
		}
		if (strValue.compare("TWBT_2OF5NONINTERLEAVED") == 0)
		{
			v = TWBT_2OF5NONINTERLEAVED; goto exit2;
		}
		if (strValue.compare("TWBT_CODE93") == 0)
		{
			v = TWBT_CODE93; goto exit2;
		}
		if (strValue.compare("TWBT_CODE128") == 0)
		{
			v = TWBT_CODE128; goto exit2;
		}
		if (strValue.compare("TWBT_UCC128") == 0)
		{
			v = TWBT_UCC128; goto exit2;
		}
		if (strValue.compare("TWBT_CODABAR") == 0)
		{
			v = TWBT_CODABAR; goto exit2;
		}
		if (strValue.compare("TWBT_UPCA") == 0)
		{
			v = TWBT_UPCA; goto exit2;
		}
		if (strValue.compare("TWBT_UPCE") == 0)
		{
			v = TWBT_UPCE; goto exit2;
		}
		if (strValue.compare("TWBT_EAN8") == 0)
		{
			v = TWBT_EAN8; goto exit2;
		}
		if (strValue.compare("TWBT_EAN13") == 0)
		{
			v = TWBT_EAN13; goto exit2;
		}
		if (strValue.compare("TWBT_POSTNET") == 0)
		{
			v = TWBT_POSTNET; goto exit2;
		}
		if (strValue.compare("TWBT_PDF417") == 0)
		{
			v = TWBT_PDF417; goto exit2;
		}
		if (strValue.compare("TWBT_2OF5INDUSTRIAL") == 0)
		{
			v = TWBT_2OF5INDUSTRIAL; goto exit2;
		}
		if (strValue.compare("TWBT_2OF5MATRIX") == 0)
		{
			v = TWBT_2OF5MATRIX; goto exit2;
		}
		if (strValue.compare("TWBT_2OF5DATALOGIC") == 0)
		{
			v = TWBT_2OF5DATALOGIC; goto exit2;
		}
		if (strValue.compare("TWBT_2OF5IATA") == 0)
		{
			v = TWBT_2OF5IATA; goto exit2;
		}
		if (strValue.compare("TWBT_3OF9FULLASCII") == 0)
		{
			v = TWBT_3OF9FULLASCII; goto exit2;
		}
		if (strValue.compare("TWBT_CODABARWITHSTARTSTOP") == 0)
		{
			v = TWBT_CODABARWITHSTARTSTOP; goto exit2;
		}
		if (strValue.compare("TWBT_MAXICODE") == 0)
		{
			v = TWBT_MAXICODE; goto exit2;
		}

	}
	break;
	case CAP_CLEARBUFFERS:
	{
		if (strValue.compare("TWCB_AUTO") == 0)
		{
			v = TWCB_AUTO; goto exit2;
		}
		if (strValue.compare("TWCB_CLEAR") == 0)
		{
			v = TWCB_CLEAR; goto exit2;
		}
		if (strValue.compare("TWCB_NOCLEAR") == 0)
		{
			v = TWCB_NOCLEAR; goto exit2;
		}

	}
	break;
	case CAP_DEVICEEVENT:
	{
		if (strValue.compare("TWDE_CUSTOMEVENTS") == 0)
		{
			v = TWDE_CUSTOMEVENTS; goto exit2;
		}
		if (strValue.compare("TWDE_CHECKAUTOMATICCAPTURE") == 0)
		{
			v = TWDE_CHECKAUTOMATICCAPTURE; goto exit2;
		}
		if (strValue.compare("TWDE_CHECKBATTERY") == 0)
		{
			v = TWDE_CHECKBATTERY; goto exit2;
		}
		if (strValue.compare("TWDE_CHECKDEVICEONLINE") == 0)
		{
			v = TWDE_CHECKDEVICEONLINE; goto exit2;
		}
		if (strValue.compare("TWDE_CHECKFLASH") == 0)
		{
			v = TWDE_CHECKFLASH; goto exit2;
		}
		if (strValue.compare("TWDE_CHECKPOWERSUPPLY") == 0)
		{
			v = TWDE_CHECKPOWERSUPPLY; goto exit2;
		}
		if (strValue.compare("TWDE_CHECKRESOLUTION") == 0)
		{
			v = TWDE_CHECKRESOLUTION; goto exit2;
		}
		if (strValue.compare("TWDE_DEVICEADDED") == 0)
		{
			v = TWDE_DEVICEADDED; goto exit2;
		}
		if (strValue.compare("TWDE_DEVICEOFFLINE") == 0)
		{
			v = TWDE_DEVICEOFFLINE; goto exit2;
		}
		if (strValue.compare("TWDE_DEVICEREADY") == 0)
		{
			v = TWDE_DEVICEREADY; goto exit2;
		}
		if (strValue.compare("TWDE_DEVICEREMOVED") == 0)
		{
			v = TWDE_DEVICEREMOVED; goto exit2;
		}
		if (strValue.compare("TWDE_IMAGECAPTURED") == 0)
		{
			v = TWDE_IMAGECAPTURED; goto exit2;
		}
		if (strValue.compare("TWDE_IMAGEDELETED") == 0)
		{
			v = TWDE_IMAGEDELETED; goto exit2;
		}
		if (strValue.compare("TWDE_PAPERDOUBLEFEED") == 0)
		{
			v = TWDE_PAPERDOUBLEFEED; goto exit2;
		}
		if (strValue.compare("TWDE_PAPERJAM") == 0)
		{
			v = TWDE_PAPERJAM; goto exit2;
		}
		if (strValue.compare("TWDE_LAMPFAILURE") == 0)
		{
			v = TWDE_LAMPFAILURE; goto exit2;
		}
		if (strValue.compare("TWDE_POWERSAVE") == 0)
		{
			v = TWDE_POWERSAVE; goto exit2;
		}
		if (strValue.compare("TWDE_POWERSAVENOTIFY") == 0)
		{
			v = TWDE_POWERSAVENOTIFY; goto exit2;
		}

	}
	break;
	case CAP_DUPLEX:
	{
		if (strValue.compare("TWDX_NONE") == 0)
		{
			v = TWDX_NONE; goto exit2;
		}
		if (strValue.compare("TWDX_1PASSDUPLEX") == 0)
		{
			v = TWDX_1PASSDUPLEX; goto exit2;
		}
		if (strValue.compare("TWDX_2PASSDUPLEX") == 0)
		{
			v = TWDX_2PASSDUPLEX; goto exit2;
		}

	}
	break;
	case CAP_FEEDERALIGNMENT:
	{
		if (strValue.compare("TWFA_NONE") == 0)
		{
			v = TWFA_NONE; goto exit2;
		}
		if (strValue.compare("TWFA_LEFT") == 0)
		{
			v = TWFA_LEFT; goto exit2;
		}
		if (strValue.compare("TWFA_CENTER") == 0)
		{
			v = TWFA_CENTER; goto exit2;
		}
		if (strValue.compare("TWFA_RIGHT") == 0)
		{
			v = TWFA_RIGHT; goto exit2;
		}

	}
	break;
	case ICAP_IMAGEFILEFORMAT:
	{
		if (strValue.compare("TWFF_TIFF") == 0)
		{
			v = TWFF_TIFF; goto exit2;
		}
		if (strValue.compare("TWFF_PICT") == 0)
		{
			v = TWFF_PICT; goto exit2;
		}
		if (strValue.compare("TWFF_BMP") == 0)
		{
			v = TWFF_BMP; goto exit2;
		}
		if (strValue.compare("TWFF_XBM") == 0)
		{
			v = TWFF_XBM; goto exit2;
		}
		if (strValue.compare("TWFF_JFIF") == 0)
		{
			v = TWFF_JFIF; goto exit2;
		}
		if (strValue.compare("TWFF_FPX") == 0)
		{
			v = TWFF_FPX; goto exit2;
		}
		if (strValue.compare("TWFF_TIFFMULTI") == 0)
		{
			v = TWFF_TIFFMULTI; goto exit2;
		}
		if (strValue.compare("TWFF_PNG") == 0)
		{
			v = TWFF_PNG; goto exit2;
		}
		if (strValue.compare("TWFF_SPIFF") == 0)
		{
			v = TWFF_SPIFF; goto exit2;
		}
		if (strValue.compare("TWFF_EXIF") == 0)
		{
			v = TWFF_EXIF; goto exit2;
		}
		if (strValue.compare("TWFF_PDF") == 0)
		{
			v = 10; goto exit2;
		}
		if (strValue.compare("TWFF_JP2") == 0)
		{
			v = 11; goto exit2;
		}
		if (strValue.compare("TWFF_JPN") == 0)
		{
			v = 12; goto exit2;
		}
		if (strValue.compare("TWFF_JPX") == 0)
		{
			v = 13; goto exit2;
		}
		if (strValue.compare("TWFF_DEJAVU") == 0)
		{
			v = 14; goto exit2;
		}
		if (strValue.compare("TWFF_PDFA") == 0)
		{
			v = 15; goto exit2;
		}
		if (strValue.compare("TWFF_PDFA2") == 0)
		{
			v = 16; goto exit2;
		}
	}
	break;
	case ICAP_FLASHUSED2:
	{
		if (strValue.compare("TWFL_NONE") == 0)
		{
			v = TWFL_NONE; goto exit2;
		}
		if (strValue.compare("TWFL_OFF") == 0)
		{
			v = TWFL_OFF; goto exit2;
		}
		if (strValue.compare("TWFL_ON") == 0)
		{
			v = TWFL_ON; goto exit2;
		}
		if (strValue.compare("TWFL_AUTO") == 0)
		{
			v = TWFL_AUTO; goto exit2;
		}
		if (strValue.compare("TWFL_REDEYE") == 0)
		{
			v = TWFL_REDEYE; goto exit2;
		}

	}
	break;
	case CAP_FEEDERORDER:
	{
		if (strValue.compare("TWFO_FIRSTPAGEFIRST") == 0)
		{
			v = TWFO_FIRSTPAGEFIRST; goto exit2;
		}
		if (strValue.compare("TWFO_LASTPAGEFIRST") == 0)
		{
			v = TWFO_LASTPAGEFIRST; goto exit2;
		}

	}
	break;
	case ICAP_FLIPROTATION:
	{
		if (strValue.compare("TWFR_BOOK") == 0)
		{
			v = TWFR_BOOK; goto exit2;
		}
		if (strValue.compare("TWFR_FANFOLD") == 0)
		{
			v = TWFR_FANFOLD; goto exit2;
		}

	}
	break;
	case ICAP_FILTER:
	{
		if (strValue.compare("TWFT_RED") == 0)
		{
			v = TWFT_RED; goto exit2;
		}
		if (strValue.compare("TWFT_GREEN") == 0)
		{
			v = TWFT_GREEN; goto exit2;
		}
		if (strValue.compare("TWFT_BLUE") == 0)
		{
			v = TWFT_BLUE; goto exit2;
		}
		if (strValue.compare("TWFT_NONE") == 0)
		{
			v = TWFT_NONE; goto exit2;
		}
		if (strValue.compare("TWFT_WHITE") == 0)
		{
			v = TWFT_WHITE; goto exit2;
		}
		if (strValue.compare("TWFT_CYAN") == 0)
		{
			v = TWFT_CYAN; goto exit2;
		}
		if (strValue.compare("TWFT_MAGENTA") == 0)
		{
			v = TWFT_MAGENTA; goto exit2;
		}
		if (strValue.compare("TWFT_YELLOW") == 0)
		{
			v = TWFT_YELLOW; goto exit2;
		}
		if (strValue.compare("TWFT_BLACK") == 0)
		{
			v = TWFT_BLACK; goto exit2;
		}

	}
	break;
	case ICAP_IMAGEFILTER:
	{
		if (strValue.compare("TWIF_NONE") == 0)
		{
			v = TWIF_NONE; goto exit2;
		}
		if (strValue.compare("TWIF_AUTO") == 0)
		{
			v = TWIF_AUTO; goto exit2;
		}
		if (strValue.compare("TWIF_LOWPASS") == 0)
		{
			v = TWIF_LOWPASS; goto exit2;
		}
		if (strValue.compare("TWIF_BANDPASS") == 0)
		{
			v = TWIF_BANDPASS; goto exit2;
		}
		if (strValue.compare("TWIF_HIGHPASS") == 0)
		{
			v = TWIF_HIGHPASS; goto exit2;
		}
		if (strValue.compare("TWIF_TEXT") == 0)
		{
			v = TWIF_TEXT; goto exit2;
		}
		if (strValue.compare("TWIF_FINELINE") == 0)
		{
			v = TWIF_FINELINE; goto exit2;
		}

	}
	break;
	case CAP_JOBCONTROL:
	{
		if (strValue.compare("TWJC_NONE") == 0)
		{
			v = TWJC_NONE; goto exit2;
		}
		if (strValue.compare("TWJC_JSIC") == 0)
		{
			v = TWJC_JSIC; goto exit2;
		}
		if (strValue.compare("TWJC_JSIS") == 0)
		{
			v = TWJC_JSIS; goto exit2;
		}
		if (strValue.compare("TWJC_JSXC") == 0)
		{
			v = TWJC_JSXC; goto exit2;
		}
		if (strValue.compare("TWJC_JSXS") == 0)
		{
			v = TWJC_JSXS; goto exit2;
		}

	}
	break;
	case ICAP_JPEGQUALITY:
	{
		if (strValue.compare("TWJQ_UNKNOWN") == 0)
		{
			v = TWJQ_UNKNOWN; goto exit2;
		}
		if (strValue.compare("TWJQ_LOW") == 0)
		{
			v = TWJQ_LOW; goto exit2;
		}
		if (strValue.compare("TWJQ_MEDIUM") == 0)
		{
			v = TWJQ_MEDIUM; goto exit2;
		}
		if (strValue.compare("TWJQ_HIGH") == 0)
		{
			v = TWJQ_HIGH; goto exit2;
		}

	}
	break;
	case ICAP_LIGHTPATH:
	{
		if (strValue.compare("TWLP_REFLECTIVE") == 0)
		{
			v = TWLP_REFLECTIVE; goto exit2;
		}
		if (strValue.compare("TWLP_TRANSMISSIVE") == 0)
		{
			v = TWLP_TRANSMISSIVE; goto exit2;
		}

	}
	break;
	case ICAP_LIGHTSOURCE:
	{
		if (strValue.compare("TWLS_RED") == 0)
		{
			v = TWLS_RED; goto exit2;
		}
		if (strValue.compare("TWLS_GREEN") == 0)
		{
			v = TWLS_GREEN; goto exit2;
		}
		if (strValue.compare("TWLS_BLUE") == 0)
		{
			v = TWLS_BLUE; goto exit2;
		}
		if (strValue.compare("TWLS_NONE") == 0)
		{
			v = TWLS_NONE; goto exit2;
		}
		if (strValue.compare("TWLS_WHITE") == 0)
		{
			v = TWLS_WHITE; goto exit2;
		}
		if (strValue.compare("TWLS_UV") == 0)
		{
			v = TWLS_UV; goto exit2;
		}
		if (strValue.compare("TWLS_IR") == 0)
		{
			v = TWLS_IR; goto exit2;
		}

	}
	break;
	case ICAP_NOISEFILTER:
	{
		if (strValue.compare("TWNF_NONE") == 0)
		{
			v = TWNF_NONE; goto exit2;
		}
		if (strValue.compare("TWNF_AUTO") == 0)
		{
			v = TWNF_AUTO; goto exit2;
		}
		if (strValue.compare("TWNF_LONEPIXEL") == 0)
		{
			v = TWNF_LONEPIXEL; goto exit2;
		}
		if (strValue.compare("TWNF_MAJORITYRULE") == 0)
		{
			v = TWNF_MAJORITYRULE; goto exit2;
		}

	}
	break;
	case ICAP_ORIENTATION:
	{
		if (strValue.compare("TWOR_ROT0") == 0)
		{
			v = TWOR_ROT0; goto exit2;
		}
		if (strValue.compare("TWOR_ROT90") == 0)
		{
			v = TWOR_ROT90; goto exit2;
		}
		if (strValue.compare("TWOR_ROT180") == 0)
		{
			v = TWOR_ROT180; goto exit2;
		}
		if (strValue.compare("TWOR_ROT270") == 0)
		{
			v = TWOR_ROT270; goto exit2;
		}
		if (strValue.compare("TWOR_PORTRAIT") == 0)
		{
			v = TWOR_PORTRAIT; goto exit2;
		}
		if (strValue.compare("TWOR_LANDSCAPE") == 0)
		{
			v = TWOR_LANDSCAPE; goto exit2;
		}

	}
	break;
	case ICAP_OVERSCAN:
	{
		if (strValue.compare("TWOV_NONE") == 0)
		{
			v = TWOV_NONE; goto exit2;
		}
		if (strValue.compare("TWOV_AUTO") == 0)
		{
			v = TWOV_AUTO; goto exit2;
		}
		if (strValue.compare("TWOV_TOPBOTTOM") == 0)
		{
			v = TWOV_TOPBOTTOM; goto exit2;
		}
		if (strValue.compare("TWOV_LEFTRIGHT") == 0)
		{
			v = TWOV_LEFTRIGHT; goto exit2;
		}
		if (strValue.compare("TWOV_ALL") == 0)
		{
			v = TWOV_ALL; goto exit2;
		}

	}
	break;
	case ICAP_PLANARCHUNKY:
	{
		if (strValue.compare("TWPC_CHUNKY") == 0)
		{
			v = TWPC_CHUNKY; goto exit2;
		}
		if (strValue.compare("TWPC_PLANAR") == 0)
		{
			v = TWPC_PLANAR; goto exit2;
		}

	}
	break;
	case ICAP_PIXELFLAVOR:
	{
		if (strValue.compare("TWPF_CHOCOLATE") == 0)
		{
			v = TWPF_CHOCOLATE; goto exit2;
		}
		if (strValue.compare("TWPF_VANILLA") == 0)
		{
			v = TWPF_VANILLA; goto exit2;
		}

	}
	break;
	case CAP_PRINTERMODE:
	{
		if (strValue.compare("TWPM_SINGLESTRING") == 0)
		{
			v = TWPM_SINGLESTRING; goto exit2;
		}
		if (strValue.compare("TWPM_MULTISTRING") == 0)
		{
			v = TWPM_MULTISTRING; goto exit2;
		}
		if (strValue.compare("TWPM_COMPOUNDSTRING") == 0)
		{
			v = TWPM_COMPOUNDSTRING; goto exit2;
		}

	}
	break;
	case CAP_PRINTER:
	{
		if (strValue.compare("TWPR_IMPRINTERTOPBEFORE") == 0)
		{
			v = TWPR_IMPRINTERTOPBEFORE; goto exit2;
		}
		if (strValue.compare("TWPR_IMPRINTERTOPAFTER") == 0)
		{
			v = TWPR_IMPRINTERTOPAFTER; goto exit2;
		}
		if (strValue.compare("TWPR_IMPRINTERBOTTOMBEFORE") == 0)
		{
			v = TWPR_IMPRINTERBOTTOMBEFORE; goto exit2;
		}
		if (strValue.compare("TWPR_IMPRINTERBOTTOMAFTER") == 0)
		{
			v = TWPR_IMPRINTERBOTTOMAFTER; goto exit2;
		}
		if (strValue.compare("TWPR_ENDORSERTOPBEFORE") == 0)
		{
			v = TWPR_ENDORSERTOPBEFORE; goto exit2;
		}
		if (strValue.compare("TWPR_ENDORSERTOPAFTER") == 0)
		{
			v = TWPR_ENDORSERTOPAFTER; goto exit2;
		}
		if (strValue.compare("TWPR_ENDORSERBOTTOMBEFORE") == 0)
		{
			v = TWPR_ENDORSERBOTTOMBEFORE; goto exit2;
		}
		if (strValue.compare("TWPR_ENDORSERBOTTOMAFTER") == 0)
		{
			v = TWPR_ENDORSERBOTTOMAFTER; goto exit2;
		}

	}
	break;
	case CAP_POWERSUPPLY:
	{
		if (strValue.compare("TWPS_EXTERNAL") == 0)
		{
			v = TWPS_EXTERNAL; goto exit2;
		}
		if (strValue.compare("TWPS_BATTERY") == 0)
		{
			v = TWPS_BATTERY; goto exit2;
		}

	}
	break;
	case ICAP_PIXELTYPE:
	{
		if (strValue.compare("TWPT_BW") == 0)
		{
			v = TWPT_BW; goto exit2;
		}
		if (strValue.compare("TWPT_GRAY") == 0)
		{
			v = TWPT_GRAY; goto exit2;
		}
		if (strValue.compare("TWPT_RGB") == 0)
		{
			v = TWPT_RGB; goto exit2;
		}
		if (strValue.compare("TWPT_PALETTE") == 0)
		{
			v = TWPT_PALETTE; goto exit2;
		}
		if (strValue.compare("TWPT_CMY") == 0)
		{
			v = TWPT_CMY; goto exit2;
		}
		if (strValue.compare("TWPT_CMYK") == 0)
		{
			v = TWPT_CMYK; goto exit2;
		}
		if (strValue.compare("TWPT_YUV") == 0)
		{
			v = TWPT_YUV; goto exit2;
		}
		if (strValue.compare("TWPT_YUVK") == 0)
		{
			v = TWPT_YUVK; goto exit2;
		}
		if (strValue.compare("TWPT_CIEXYZ") == 0)
		{
			v = TWPT_CIEXYZ; goto exit2;
		}

	}
	break;
	case ICAP_SUPPORTEDSIZES:
	{
		if (strValue.compare("TWSS_NONE") == 0)
		{
			v = TWSS_NONE; goto exit2;
		}
		if (strValue.compare("TWSS_A4") == 0)
		{
			v = TWSS_A4; goto exit2;
		}
		if (strValue.compare("TWSS_JISB5") == 0)
		{
			v = TWSS_JISB5; goto exit2;
		}
		if (strValue.compare("TWSS_USLETTER") == 0)
		{
			v = TWSS_USLETTER; goto exit2;
		}
		if (strValue.compare("TWSS_USLEGAL") == 0)
		{
			v = TWSS_USLEGAL; goto exit2;
		}
		if (strValue.compare("TWSS_A5") == 0)
		{
			v = TWSS_A5; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB4") == 0)
		{
			v = TWSS_ISOB4; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB6") == 0)
		{
			v = TWSS_ISOB6; goto exit2;
		}
		if (strValue.compare("TWSS_USLEDGER") == 0)
		{
			v = TWSS_USLEDGER; goto exit2;
		}
		if (strValue.compare("TWSS_USEXECUTIVE") == 0)
		{
			v = TWSS_USEXECUTIVE; goto exit2;
		}
		if (strValue.compare("TWSS_A3") == 0)
		{
			v = TWSS_A3; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB3") == 0)
		{
			v = TWSS_ISOB3; goto exit2;
		}
		if (strValue.compare("TWSS_A6") == 0)
		{
			v = TWSS_A6; goto exit2;
		}
		if (strValue.compare("TWSS_C4") == 0)
		{
			v = TWSS_C4; goto exit2;
		}
		if (strValue.compare("TWSS_C5") == 0)
		{
			v = TWSS_C5; goto exit2;
		}
		if (strValue.compare("TWSS_C6") == 0)
		{
			v = TWSS_C6; goto exit2;
		}
		if (strValue.compare("TWSS_4A0") == 0)
		{
			v = TWSS_4A0; goto exit2;
		}
		if (strValue.compare("TWSS_2A0") == 0)
		{
			v = TWSS_2A0; goto exit2;
		}
		if (strValue.compare("TWSS_A0") == 0)
		{
			v = TWSS_A0; goto exit2;
		}
		if (strValue.compare("TWSS_A1") == 0)
		{
			v = TWSS_A1; goto exit2;
		}
		if (strValue.compare("TWSS_A2") == 0)
		{
			v = TWSS_A2; goto exit2;
		}
		if (strValue.compare("TWSS_A7") == 0)
		{
			v = TWSS_A7; goto exit2;
		}
		if (strValue.compare("TWSS_A8") == 0)
		{
			v = TWSS_A8; goto exit2;
		}
		if (strValue.compare("TWSS_A9") == 0)
		{
			v = TWSS_A9; goto exit2;
		}
		if (strValue.compare("TWSS_A10") == 0)
		{
			v = TWSS_A10; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB0") == 0)
		{
			v = TWSS_ISOB0; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB1") == 0)
		{
			v = TWSS_ISOB1; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB2") == 0)
		{
			v = TWSS_ISOB2; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB5") == 0)
		{
			v = TWSS_ISOB5; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB7") == 0)
		{
			v = TWSS_ISOB7; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB8") == 0)
		{
			v = TWSS_ISOB8; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB9") == 0)
		{
			v = TWSS_ISOB9; goto exit2;
		}
		if (strValue.compare("TWSS_ISOB10") == 0)
		{
			v = TWSS_ISOB10; goto exit2;
		}
		if (strValue.compare("TWSS_JISB0") == 0)
		{
			v = TWSS_JISB0; goto exit2;
		}
		if (strValue.compare("TWSS_JISB1") == 0)
		{
			v = TWSS_JISB1; goto exit2;
		}
		if (strValue.compare("TWSS_JISB2") == 0)
		{
			v = TWSS_JISB2; goto exit2;
		}
		if (strValue.compare("TWSS_JISB3") == 0)
		{
			v = TWSS_JISB3; goto exit2;
		}
		if (strValue.compare("TWSS_JISB4") == 0)
		{
			v = TWSS_JISB4; goto exit2;
		}
		if (strValue.compare("TWSS_JISB6") == 0)
		{
			v = TWSS_JISB6; goto exit2;
		}
		if (strValue.compare("TWSS_JISB7") == 0)
		{
			v = TWSS_JISB7; goto exit2;
		}
		if (strValue.compare("TWSS_JISB8") == 0)
		{
			v = TWSS_JISB8; goto exit2;
		}
		if (strValue.compare("TWSS_JISB9") == 0)
		{
			v = TWSS_JISB9; goto exit2;
		}
		if (strValue.compare("TWSS_JISB10") == 0)
		{
			v = TWSS_JISB10; goto exit2;
		}
		if (strValue.compare("TWSS_C0") == 0)
		{
			v = TWSS_C0; goto exit2;
		}
		if (strValue.compare("TWSS_C1") == 0)
		{
			v = TWSS_C1; goto exit2;
		}
		if (strValue.compare("TWSS_C2") == 0)
		{
			v = TWSS_C2; goto exit2;
		}
		if (strValue.compare("TWSS_C3") == 0)
		{
			v = TWSS_C3; goto exit2;
		}
		if (strValue.compare("TWSS_C7") == 0)
		{
			v = TWSS_C7; goto exit2;
		}
		if (strValue.compare("TWSS_C8") == 0)
		{
			v = TWSS_C8; goto exit2;
		}
		if (strValue.compare("TWSS_C9") == 0)
		{
			v = TWSS_C9; goto exit2;
		}
		if (strValue.compare("TWSS_C10") == 0)
		{
			v = TWSS_C10; goto exit2;
		}
		if (strValue.compare("TWSS_USSTATEMENT") == 0)
		{
			v = TWSS_USSTATEMENT; goto exit2;
		}
		if (strValue.compare("TWSS_BUSINESSCARD") == 0)
		{
			v = TWSS_BUSINESSCARD; goto exit2;
		}

	}
	break;
	case ICAP_XFERMECH:
	{
		if (strValue.compare("TWSX_NATIVE") == 0)
		{
			v = TWSX_NATIVE; goto exit2;
		}
		if (strValue.compare("TWSX_FILE") == 0)
		{
			v = TWSX_FILE; goto exit2;
		}
		if (strValue.compare("TWSX_MEMORY") == 0)
		{
			v = TWSX_MEMORY; goto exit2;
		}

	}
	break;
	case ICAP_UNITS:
	{
		if (strValue.compare("TWUN_INCHES") == 0)
		{
			v = TWUN_INCHES; goto exit2;
		}
		if (strValue.compare("TWUN_CENTIMETERS") == 0)
		{
			v = TWUN_CENTIMETERS; goto exit2;
		}
		if (strValue.compare("TWUN_PICAS") == 0)
		{
			v = TWUN_PICAS; goto exit2;
		}
		if (strValue.compare("TWUN_POINTS") == 0)
		{
			v = TWUN_POINTS; goto exit2;
		}
		if (strValue.compare("TWUN_TWIPS") == 0)
		{
			v = TWUN_TWIPS; goto exit2;
		}
		if (strValue.compare("TWUN_PIXELS") == 0)
		{
			v = TWUN_PIXELS; goto exit2;
		}

	}
	break;
	}

	exit2:



	return v;
}
