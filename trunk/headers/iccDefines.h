#ifndef _H_iccHeaderDefines_H_
#define _H_iccHeaderDefines_H_

ICC_LIB_NAMESPACE_START

/**
 *	Profile/Device Class Signature
 */
enum {
    iccInputClass                   = 0x73636E72L,  /* 'scnr' */
    iccDisplayClass                 = 0x6D6E7472L,  /* 'mntr' */
    iccOutputClass                  = 0x70727472L,  /* 'prtr' */
    iccLinkClass                    = 0x6C696E6BL,  /* 'link' */
    iccAbstractClass                = 0x61627374L,  /* 'abst' */
    iccColorSpaceClass              = 0x73706163L,  /* 'spac' */
    iccNamedColorClass              = 0x6e6d636cL,  /* 'nmcl' */
    iccMaxEnumClass                 = 0xFFFFFFFFL
};

/**
 *	Color Space Signature
 */
enum {
	iccXYZData                      = 0x58595A20L,  /* 'XYZ ' */
    iccLabData                      = 0x4C616220L,  /* 'Lab ' */
    iccLuvData                      = 0x4C757620L,  /* 'Luv ' */
    iccYCbCrData                    = 0x59436272L,  /* 'YCbr' */
    iccYxyData                      = 0x59787920L,  /* 'Yxy ' */
    iccRGBData                      = 0x52474220L,  /* 'RGB ' */
    iccGrayData                     = 0x47524159L,  /* 'GRAY' */
    iccHSVData                      = 0x48535620L,  /* 'HSV ' */
    iccHLSData                      = 0x484C5320L,  /* 'HLS ' */
    iccCMYKData                     = 0x434D594BL,  /* 'CMYK' */
    iccCMYData                      = 0x434D5920L,  /* 'CMY ' */
    icc1colorData                   = 0x31434C52L,  /* '1CLR' */
    icc2colorData                   = 0x32434C52L,  /* '2CLR' */
    icc3colorData                   = 0x33434C52L,  /* '3CLR' */
    icc4colorData                   = 0x34434C52L,  /* '4CLR' */
    icc5colorData                   = 0x35434C52L,  /* '5CLR' */
    icc6colorData                   = 0x36434C52L,  /* '6CLR' */
    icc7colorData                   = 0x37434C52L,  /* '7CLR' */
    icc8colorData                   = 0x38434C52L,  /* '8CLR' */
    icc9colorData                   = 0x39434C52L,  /* '9CLR' */
    icc10colorData                  = 0x41434C52L,  /* 'ACLR' */
    icc11colorData                  = 0x42434C52L,  /* 'BCLR' */
    icc12colorData                  = 0x43434C52L,  /* 'CCLR' */
    icc13colorData                  = 0x44434C52L,  /* 'DCLR' */
    icc14colorData                  = 0x45434C52L,  /* 'ECLR' */
    icc15colorData                  = 0x46434C52L,  /* 'FCLR' */
    icc16colorData                  = 0x47434C52L,  /* 'GCLR' */
};

/**
 *	Primary Platform Signature
 */
enum {
	iccApple						= 0x4150504C,	/* 'APPL' */
	iccMicrosoft					= 0x4D534654,	/* 'MSFT' */
	iccSiliconGraphics				= 0x53474920,	/* 'SGI ' */
	iccSun							= 0x53554E57,	/* 'SUNW' */
	iccTaligent						= 0x54474E54	/* 'TGNT' */
};

/**
 *	Rendering Intents
 */
enum {
	iccPerceptual					= 0,
	iccRelativeColorimetric			= 1,
	iccSaturation					= 2,
	iccAbsoluteColorimetric			= 3
};

/**
 *	Tag Signatures
 */
enum {
	iccUnknownTag					= 0x00000000L,	/* Not defined */
	iccAToB0Tag						= 0x41324230L, 	/* 'A2B0' */
	iccAToB1Tag						= 0x41324231L,  /* 'A2B1' */
	iccAToB2Tag						= 0x41324232L,  /* 'A2B2' */
	iccBlueMatrixColumnTag			= 0x6258595AL,	/* 'bXYZ' */
	iccBlueTRCTag					= 0x62545243L,  /* 'bTRC' */
	iccBToA0Tag						= 0x42324130L,  /* 'B2A0' */
	iccBToA1Tag						= 0x42324131L,  /* 'B2A1' */
	iccBToA2Tag						= 0x42324132L,  /* 'B2A2' */
	iccCalibrationDateTimeTag		= 0x63616C74L,  /* 'calt' */
	iccCharTargetTag				= 0x74617267L,  /* 'targ' */
	iccChromaticAdaptationTag		= 0x63686164L,  /* 'chad' */
	iccChromaticityTag				= 0x6368726DL,  /* 'chrm' */
	iccColorantOrderTag				= 0x636C726FL,	/* 'clro' */
	iccColorantTableTag				= 0x636C7274L,	/* 'clrt' */
	iccCopyrightTag					= 0x63707274L,  /* 'cprt' */
	iccDeviceMfgDescTag				= 0x646D6E64L,  /* 'dmnd' */
	iccDeviceModelDescTag			= 0x646D6464L,  /* 'dmdd' */
	iccGamutTag						= 0x67616D74L,  /* 'gamt' */
	iccGrayTRCTag					= 0x6b545243L,  /* 'kTRC' */
	iccGreenMatrixColumnTag			= 0x6758595AL,  /* 'gXYZ' */
	iccGreenTRCTag					= 0x67545243L,  /* 'gTRC' */
	iccLuminanceTag					= 0x6C756d69L,  /* 'lumi' */
	iccMeasurementTag				= 0x6D656173L,  /* 'meas' */
	iccMediaBlackPointTag			= 0x626B7074L,  /* 'bkpt' */
	iccMediaWhitePointTag			= 0x77747074L,  /* 'wtpt' */
	iccNamedColor2Tag				= 0x6E636C32L, 	/* 'ncl2' */
	iccOutputResponseTag			= 0x72657370L, 	/* 'resp' */
	iccPreview0Tag					= 0x70726530L,  /* 'pre0' */
	iccPreview1Tag					= 0x70726531L,  /* 'pre1' */
	iccPreview2Tag					= 0x70726532L,  /* 'pre2' */
	iccProfileDescriptionTag		= 0x64657363L,  /* 'desc' */
	iccProfileSequenceDescTag		= 0x70736571L,  /* 'pseq' */
	iccRedMatrixColumnTag			= 0x7258595AL,  /* 'rXYZ' */
	iccRedTRCTag					= 0x72545243L,  /* 'rTRC' */
	iccTechnologyTag				= 0x74656368L,  /* 'tech' */
	iccViewingCondDescTag			= 0x76756564L,  /* 'vued' */
	iccViewingConditionsTag			= 0x76696577L	/* 'view' */
};

/**
 *	Tag Signatures
 */
enum {
	iccChromaticityType				= 0x6368726DL,  /* 'chrm' */
	iccColorantOrderType			= 0x636C726FL,  /* 'clro' */
	iccColorantTableType			= 0x636C7274L,  /* 'clrt' */
	iccCrdInfoType					= 0x63726469L,  /* 'crdi' */
	iccCurveType					= 0x63757276L,  /* 'curv' */
	iccDataType						= 0x64617461L,  /* 'data' */
	iccDateTimeType					= 0x6474696DL,  /* 'dtim' */
	iccDeviceSettingsType			= 0x64657673L,  /* 'devs' */
	iccLut16Type					= 0x6d667432L,  /* 'mft2' */
	iccLut8Type						= 0x6d667431L,  /* 'mft1' */
	iccLutAtoBType					= 0x6d414220L,  /* 'mAB ' */
	iccLutBtoAType					= 0x6d424120L,  /* 'mBA ' */
	iccMeasurementType				= 0x6D656173L,  /* 'meas' */
	iccMultiLocalizedUnicodeType	= 0x6D6C7563L,  /* 'mluc' */
	iccNamedColor2Type				= 0x6E636C32L,  /* 'ncl2' */
	iccParametricCurveType			= 0x70617261L,  /* 'para' */
	iccProfileSequenceDescType		= 0x70736571L,  /* 'pseq' */
	iccResponseCurveSet16Type		= 0x72637332L,  /* 'rcs2' */
	iccS15Fixed16ArrayType			= 0x73663332L,  /* 'sf32' */
	iccScreeningType				= 0x7363726EL,  /* 'scrn' */
	iccSignatureType				= 0x73696720L,  /* 'sig ' */
	iccTextType 					= 0x74657874L,  /* 'text' */
	iccTextDescriptionType			= 0x64657363L,  /* 'desc' */
	iccU16Fixed16ArrayType			= 0x75663332L,  /* 'uf32' */
	iccUcrBgType					= 0x62666420L,  /* 'bfd ' */
	iccUInt16ArrayType				= 0x75693136L,  /* 'ui16' */
	iccUInt32ArrayType				= 0x75693332L,  /* 'ui32' */
	iccUInt64ArrayType				= 0x75693634L,  /* 'ui64' */
	iccUInt8ArrayType				= 0x75693038L,  /* 'ui08' */
	iccViewingConditionsType		= 0x76696577L,  /* 'view' */
	iccXYZType						= 0x58595A20L,  /* 'XYZ ' */
	iccXYZArrayType					= 0x58595A20L,  /* 'XYZ ' */
	iccSigUnknownType				= 0x3f3f3f3fL,  /* '????' */
};

enum
{
	iccStandardIlluminant_Unknown	= 0L,
	iccStandardIlluminant_D50,
	iccStandardIlluminant_D65,
	iccStandardIlluminant_D93,
	iccStandardIlluminant_F2,
	iccStandardIlluminant_D55,
	iccStandardIlluminant_A,
	iccStandardIlluminant_E,
	iccStandardIlluminant_F8,
	iccStandardIlluminant_Max
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccHeaderDefines_H_
