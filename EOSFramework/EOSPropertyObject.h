//
//  EOSObject.h
//  EOSFramework
//
//  Created by Henry Betts on 23/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <Foundation/Foundation.h>
#import <EOSFramework/EOSObject.h>

/*!
 Properties of cameras and images to be used with the methods of EOSPropertyObject.
 */
typedef NS_ENUM(NSUInteger, EOSProperty){
    
    /*----------------------------------
    Camera Setting Properties
    ----------------------------------*/
    EOSProperty_Unknown                 = kEdsPropID_Unknown,
    
    /** A string representing the product name */
    EOSProperty_ProductName             = kEdsPropID_ProductName,
    
    /** A string indicating the product serial number. */
    EOSProperty_SerialNumber            = kEdsPropID_BodyIDEx,
    
    /** A string identifying the owner as registered on the camera. */
    EOSProperty_OwnerName               = kEdsPropID_OwnerName,
    
    /** A string identifying the manufacturer. */
    EOSProperty_MakerName               = kEdsPropID_MakerName,
    
    /** Not yet supported */
    EOSProperty_DateTime                = kEdsPropID_DateTime,
    
    /** A string identifying the camera's firmware version. */
    EOSProperty_FirmwareVersion         = kEdsPropID_FirmwareVersion,
    
    /**
     @brief An integer indicating the camera battery level.
     @discussion The battery level is represented by a percentage (0-100), or -1 if the camera is AC powered.
     */
    EOSProperty_BatteryLevel            = kEdsPropID_BatteryLevel,
    
    /** The level of degradation of the battery, represented by an EOSBateryQuality value. */
    EOSProperty_BatteryQuality          = kEdsPropID_BatteryQuality,
    
    /** */
    EOSProperty_Cfn                     = kEdsPropID_CFn,
    EOSProperty_SaveTo                  = kEdsPropID_SaveTo,
    
    /** A string representing the name of the current storage media */
    EOSProperty_CurrentStorage          = kEdsPropID_CurrentStorage,
    
    /** A string representing the name of the current folder (for saving images to). */
    EOSProperty_CurrentFolder           = kEdsPropID_CurrentFolder,
    
    /** */
    EOSProperty_MyMenu                  = kEdsPropID_MyMenu,
    EOSProperty_HDDirectoryStructure    = kEdsPropID_HDDirectoryStructure,

    
    /*----------------------------------
     Image Properties
     ----------------------------------*/
    
    /**
     @brief The image quality, represented by an unsigned integer code.
     @discussion The value for this property contains information about the image format, size and compression for both the main and secondary images. This information can be obtained using the EOSImageQualityFromCode function.
     */
    EOSProperty_ImageQuality        = kEdsPropID_ImageQuality,
    
    /** */
    EOSProperty_JPEGQuality         = kEdsPropID_JpegQuality,
    EOSProperty_Orientation         = kEdsPropID_Orientation,
    EOSProperty_ICCProfile          = kEdsPropID_ICCProfile,
    EOSProperty_FocusInfo           = kEdsPropID_FocusInfo,
    EOSProperty_DigitalExposure     = kEdsPropID_DigitalExposure,
    EOSProperty_WhiteBalance        = kEdsPropID_WhiteBalance,
    EOSProperty_ColorTemperature    = kEdsPropID_ColorTemperature,
    EOSProperty_WhiteBalanceShift   = kEdsPropID_WhiteBalanceShift,
    EOSProperty_Contrast            = kEdsPropID_Contrast,
    EOSProperty_ColorSaturation     = kEdsPropID_ColorSaturation,
    EOSProperty_ColorTone           = kEdsPropID_ColorTone,
    EOSProperty_Sharpness           = kEdsPropID_Sharpness,
    EOSProperty_ColorSpace          = kEdsPropID_ColorSpace,
    EOSProperty_ToneCurve           = kEdsPropID_ToneCurve,
    EOSProperty_PhotoEffect         = kEdsPropID_PhotoEffect,
    EOSProperty_FilterEffect        = kEdsPropID_FilterEffect,
    EOSProperty_ToningEffect        = kEdsPropID_ToningEffect,
    EOSProperty_ParameterSet        = kEdsPropID_ParameterSet,
    EOSProperty_ColorMatrix         = kEdsPropID_ColorMatrix,
    EOSProperty_PictureStyle        = kEdsPropID_PictureStyle,
    EOSProperty_PictureStyleDesc    = kEdsPropID_PictureStyleDesc,
    EOSProperty_PictureStyleCaption = kEdsPropID_PictureStyleCaption,

    
    /*----------------------------------
     Image Processing Properties
     ----------------------------------*/
    EOSProperty_Linear                      = kEdsPropID_Linear,
    EOSProperty_WhiteBalanceClickPosition   = kEdsPropID_ClickWBPoint,
    EOSProperty_WhiteBalanceCoeffs          = kEdsPropID_WBCoeffs,
    
    
    /*----------------------------------
     Image GPS Properties
     ----------------------------------*/
    
    EOSProperty_GPSVersionID    = kEdsPropID_GPSVersionID,
    EOSProperty_GPSLatitudeRef  = kEdsPropID_GPSLatitudeRef,
    EOSProperty_GPSLatitude     = kEdsPropID_GPSLatitude,
    EOSProperty_GPSLongitudeRef = kEdsPropID_GPSLongitudeRef,
    EOSProperty_GPSLongitude    = kEdsPropID_GPSLongitude,
    EOSProperty_GPSAltitudeRef  = kEdsPropID_GPSAltitudeRef,
    EOSProperty_GPSAltitude     = kEdsPropID_GPSAltitude,
    EOSProperty_GPSTimeStamp    = kEdsPropID_GPSTimeStamp,
    EOSProperty_GPSSatellites   = kEdsPropID_GPSSatellites,
    EOSProperty_GPSStatus       = kEdsPropID_GPSStatus,
    EOSProperty_GPSMapDatum     = kEdsPropID_GPSMapDatum,
    EOSProperty_GPSDateStamp    = kEdsPropID_GPSDateStamp,
    
    
    /*----------------------------------
     Property Mask
     ----------------------------------*/
    EOSProperty_AtCaptureFlag   = kEdsPropID_AtCapture_Flag,
    
    
    /*----------------------------------
     Capture Properties
     ----------------------------------*/
    
    /** The current shooting mode, represented by an EOSAEMode value. */
    EOSProperty_AEMode                  = kEdsPropID_AEMode,
    
    /** The current drive mode, represented by an EOSDriveMode value. */
    EOSProperty_DriveMode               = kEdsPropID_DriveMode,
    
    /** The ISO sensitivity, represented by an EOSISOSpeed value. */
    EOSProperty_ISOSpeed                = kEdsPropID_ISOSpeed,
    
    /** The metering mode, represented by an EOSMeteringMode value. */
    EOSProperty_MeteringMode            = kEdsPropID_MeteringMode,
    
    /** The auto-focus mode, represented by an EOSAFMode value. */
    EOSProperty_AFMode                  = kEdsPropID_AFMode,
    
    /** The aperture, represented by an EOSAperture value. */
    EOSProperty_Aperture                = kEdsPropID_Av,
    
    /** The shutter speed, represented by an EOSShutterSpeed value. */
    EOSProperty_ShutterSpeed            = kEdsPropID_Tv,
    
    /** The exposure compensation, represented by an EOSExposureCompensation value. */
    EOSProperty_ExposureCompensation    = kEdsPropID_ExposureCompensation,
    
    /** The flash compensation, represented by an EOSExposureCompensation value. */
    EOSProperty_FlashCompensation       = kEdsPropID_FlashCompensation,
    
    EOSProperty_FocalLength             = kEdsPropID_FocalLength,
    
    /** An unsigned integer, representing the number of shots available on a camera. */
    EOSProperty_AvailableShots          = kEdsPropID_AvailableShots,
    
    /** */
    EOSProperty_Bracket                 = kEdsPropID_Bracket,
    EOSProperty_WhiteBalanceBracket     = kEdsPropID_WhiteBalanceBracket,
    EOSProperty_LensName                = kEdsPropID_LensName,
    EOSProperty_AEBracket               = kEdsPropID_AEBracket,
    EOSProperty_FEBracket               = kEdsPropID_FEBracket,
    EOSProperty_ISOBracket              = kEdsPropID_ISOBracket,
    EOSProperty_NoiseReduction          = kEdsPropID_NoiseReduction,
    EOSProperty_FlashOn                 = kEdsPropID_FlashOn,
    EOSProperty_RedEye                  = kEdsPropID_RedEye,
    EOSProperty_FlashMode               = kEdsPropID_FlashMode,
    
    /** A boolean, indicating whether the lens is attached to the camera. */
    EOSProperty_isLensAttached          = kEdsPropID_LensStatus,
    
    /** A string identifying the photographer as registered on the camera. */
    EOSProperty_Artist                  = kEdsPropID_Artist,
    
    /** A string identifying the copyright information as registered on the camera. */
    EOSProperty_Copyright               = kEdsPropID_Copyright,
    
    /** */
    EOSProperty_DepthOfField            = kEdsPropID_DepthOfField,
    EOSProperty_EFCompensation          = kEdsPropID_EFCompensation,
    EOSProperty_AEModeSelect            = kEdsPropID_AEModeSelect
    
    
    /*----------------------------------
     EVF Properties - Not supported in 64bit SDK
     ----------------------------------*/
//#define kEdsPropID_Evf_OutputDevice        0x00000500
//#define kEdsPropID_Evf_Mode                0x00000501
//#define kEdsPropID_Evf_WhiteBalance        0x00000502
//#define kEdsPropID_Evf_ColorTemperature    0x00000503
//#define kEdsPropID_Evf_DepthOfFieldPreview 0x00000504
//    
//    // EVF IMAGE DATA Properties
//#define kEdsPropID_Evf_Zoom                0x00000507
//#define kEdsPropID_Evf_ZoomPosition        0x00000508
//#define kEdsPropID_Evf_FocusAid            0x00000509
//#define kEdsPropID_Evf_Histogram           0x0000050A
//#define kEdsPropID_Evf_ImagePosition       0x0000050B
//#define kEdsPropID_Evf_HistogramStatus     0x0000050C
//#define kEdsPropID_Evf_AFMode              0x0000050E
//    
//#define kEdsPropID_Record                  0x00000510
//    
//#define kEdsPropID_Evf_HistogramY          0x00000515
//#define kEdsPropID_Evf_HistogramR          0x00000516
//#define kEdsPropID_Evf_HistogramG          0x00000517
//#define kEdsPropID_Evf_HistogramB          0x00000518
//    
//#define kEdsPropID_Evf_CoordinateSystem    0x00000540
//#define kEdsPropID_Evf_ZoomRect            0x00000541
//#define kEdsPropID_Evf_ImageClipRect       0x00000545
    
};

typedef NS_ENUM(NSUInteger, EOSISOSpeed){
    
    EOSISOSpeed_Auto    = 0x00,
    EOSISOSpeed_6       = 0x28,
    EOSISOSpeed_12      = 0x30,
    EOSISOSpeed_25      = 0x38,
    EOSISOSpeed_50      = 0x40,
    EOSISOSpeed_100     = 0x48,
    EOSISOSpeed_125     = 0x4b,
    EOSISOSpeed_160     = 0x4d,
    EOSISOSpeed_200     = 0x50,
    EOSISOSpeed_250     = 0x53,
    EOSISOSpeed_320     = 0x55,
    EOSISOSpeed_400     = 0x58,
    EOSISOSpeed_500     = 0x5b,
    EOSISOSpeed_640     = 0x5d,
    EOSISOSpeed_800     = 0x60,
    EOSISOSpeed_1000    = 0x63,
    EOSISOSpeed_1250    = 0x65,
    EOSISOSpeed_1600    = 0x68,
    EOSISOSpeed_2000    = 0x6b,
    EOSISOSpeed_2500    = 0x6d,
    EOSISOSpeed_3200    = 0x70,
    EOSISOSpeed_4000    = 0x73,
    EOSISOSpeed_5000    = 0x75,
    EOSISOSpeed_6400    = 0x78,
    EOSISOSpeed_8000    = 0x7b,
    EOSISOSpeed_10000   = 0x7d,
    EOSISOSpeed_12800   = 0x80,
    EOSISOSpeed_16000   = 0x83,
    EOSISOSpeed_20000   = 0x85,
    EOSISOSpeed_25600   = 0x88,
    EOSISOSpeed_32000   = 0x8b,
    EOSISOSpeed_40000   = 0x8d,
    EOSISOSpeed_51200   = 0x90,
    EOSISOSpeed_102400  = 0x98,
    EOSISOSpeed_Unknown = 0xffffffff
    
};

typedef NS_ENUM(NSUInteger, EOSShutterSpeed){
    
    EOSShutterSpeed_Bulb = 0x0c,
    EOSShutterSpeed_30_Seconds = 0x10,
    EOSShutterSpeed_25_Seconds = 0x13,
    EOSShutterSpeed_20_Seconds = 0x14,
    EOSShutterSpeed_20_Seconds__1_3 = 0x15,
    EOSShutterSpeed_15_Seconds = 0x18,
    EOSShutterSpeed_13_Seconds = 0x1B,
    EOSShutterSpeed_10_Seconds = 0x1C,
    EOSShutterSpeed_10_Seconds__1_3 = 0x1D,
    EOSShutterSpeed_8_Seconds = 0x20,
    EOSShutterSpeed_6_Seconds__1_3 = 0x23,
    EOSShutterSpeed_6_Seconds = 0x24,
    EOSShutterSpeed_5_Seconds = 0x25,
    EOSShutterSpeed_4_Seconds = 0x28,
    EOSShutterSpeed_3_2_Seconds = 0x2B,
    EOSShutterSpeed_3_Seconds = 0x2C,
    EOSShutterSpeed_2_5_Seconds = 0x2D,
    EOSShutterSpeed_2_Seconds = 0x30,
    EOSShutterSpeed_1_6_Seconds = 0x33,
    EOSShutterSpeed_1_5_Seconds = 0x34,
    EOSShutterSpeed_1_3_Seconds = 0x35,
    EOSShutterSpeed_1_Second = 0x38,
    EOSShutterSpeed_0_8_Seconds = 0x3B,
    EOSShutterSpeed_0_7_Seconds = 0x3C,
    EOSShutterSpeed_0_6_Seconds = 0x3D,
    EOSShutterSpeed_0_5_Seconds = 0x40,
    EOSShutterSpeed_0_4_Seconds = 0x43,
    EOSShutterSpeed_0_3_Seconds = 0x44,
    EOSShutterSpeed_0_3_Seconds__1_3 = 0x45,
    EOSShutterSpeed_4 = 0x48,
    EOSShutterSpeed_5 = 0x4B,
    EOSShutterSpeed_6 = 0x4C,
    EOSShutterSpeed_6__1_3 = 0x4D,
    EOSShutterSpeed_8 = 0x50,
    EOSShutterSpeed_10__1_3 = 0x53,
    EOSShutterSpeed_10 = 0x54,
    EOSShutterSpeed_13 = 0x55,
    EOSShutterSpeed_15 = 0x58,
    EOSShutterSpeed_20__1_3 = 0x5B,
    EOSShutterSpeed_20 = 0x5C,
    EOSShutterSpeed_25 = 0x5D,
    EOSShutterSpeed_30 = 0x60,
    EOSShutterSpeed_40 = 0x63,
    EOSShutterSpeed_45 = 0x64,
    EOSShutterSpeed_50 = 0x65,
    EOSShutterSpeed_60 = 0x68,
    EOSShutterSpeed_80 = 0x6B,
    EOSShutterSpeed_90 = 0x6C,
    EOSShutterSpeed_100 = 0x6D,
    EOSShutterSpeed_125 = 0x70,
    EOSShutterSpeed_160 = 0x73,
    EOSShutterSpeed_180 = 0x74,
    EOSShutterSpeed_200 = 0x75,
    EOSShutterSpeed_250 = 0x78,
    EOSShutterSpeed_320 = 0x7B,
    EOSShutterSpeed_350 = 0x7C,
    EOSShutterSpeed_400 = 0x7D,
    EOSShutterSpeed_500 = 0x80,
    EOSShutterSpeed_640 = 0x83,
    EOSShutterSpeed_750 = 0x84,
    EOSShutterSpeed_800 = 0x85,
    EOSShutterSpeed_1000 = 0x88,
    EOSShutterSpeed_1250 = 0x8B,
    EOSShutterSpeed_1500 = 0x8C,
    EOSShutterSpeed_1600 = 0x8D,
    EOSShutterSpeed_2000 = 0x90,
    EOSShutterSpeed_2500 = 0x93,
    EOSShutterSpeed_3000 = 0x94,
    EOSShutterSpeed_3200 = 0x95,
    EOSShutterSpeed_4000 = 0x98,
    EOSShutterSpeed_5000 = 0x9B,
    EOSShutterSpeed_6000 = 0x9C,
    EOSShutterSpeed_6400 = 0x9D,
    EOSShutterSpeed_8000 = 0xA0,
    
    EOSShutterSpeed_Unknown = 0xffffffff
    
};

typedef NS_ENUM(NSUInteger, EOSAperture){
    
    EOSAperture_1 = 0x08,
    EOSAperture_1_1 = 0x0B,
    EOSAperture_1_2 = 0x0C,
    EOSAperture_1_2__1_3 = 0x0D,
    EOSAperture_1_4 = 0x10,
    EOSAperture_1_6 = 0x13,
    EOSAperture_1_8 = 0x14,
    EOSAperture_1_8__1_3 = 0x15,
    EOSAperture_2 = 0x18,
    EOSAperture_2_2 = 0x1B,
    EOSAperture_2_5 = 0x1C,
    EOSAperture_2_5__1_3 = 0x1D,
    EOSAperture_2_8 = 0x20,
    EOSAperture_3_2 = 0x23,
    EOSAperture_3_5 = 0x24,
    EOSAperture_3_5__1_3 = 0x25,
    EOSAperture_4 = 0x28,
    EOSAperture_4_5 = 0x2B,
    EOSAperture_4_5__1_3 = 0x2C,
    EOSAperture_5_0 = 0x2D,
    EOSAperture_5_6 = 0x30,
    EOSAperture_6_3 = 0x33,
    EOSAperture_6_7 = 0x34,
    EOSAperture_7_1 = 0x35,
    EOSAperture_8 = 0x38,
    EOSAperture_9 = 0x3B,
    EOSAperture_9_5 = 0x3C,
    EOSAperture_10 = 0x3D,
    EOSAperture_11 = 0x40,
    EOSAperture_13__1_3 = 0x43,
    EOSAperture_13 = 0x44,
    EOSAperture_14 = 0x45,
    EOSAperture_16 = 0x48,
    EOSAperture_18 = 0x4B,
    EOSAperture_19 = 0x4C,
    EOSAperture_20 = 0x4D,
    EOSAperture_22 = 0x50,
    EOSAperture_25 = 0x53,
    EOSAperture_27 = 0x54,
    EOSAperture_29 = 0x55,
    EOSAperture_32 = 0x58,
    EOSAperture_36 = 0x5B,
    EOSAperture_38 = 0x5C,
    EOSAperture_40 = 0x5D,
    EOSAperture_45 = 0x60,
    EOSAperture_51 = 0x63,
    EOSAperture_54 = 0x64,
    EOSAperture_57 = 0x65,
    EOSAperture_64 = 0x68,
    EOSAperture_72 = 0x6B,
    EOSAperture_76 = 0x6C,
    EOSAperture_80 = 0x6D,
    EOSAperture_91 = 0x70,

    EOSAperture_Unknown = 0xffffffff
    
};

typedef NS_ENUM(NSUInteger, EOSWhiteBalance){
    
    EOSWhiteBalance_Auto        = kEdsWhiteBalance_Auto,
    EOSWhiteBalance_Daylight    = kEdsWhiteBalance_Daylight,
    EOSWhiteBalance_Cloudy      = kEdsWhiteBalance_Cloudy,
    EOSWhiteBalance_Tungsten    = kEdsWhiteBalance_Tangsten,
    EOSWhiteBalance_Fluorescent = kEdsWhiteBalance_Fluorescent,
    EOSWhiteBalance_Flash       = kEdsWhiteBalance_Strobe,
    EOSWhiteBalance_Manual  = kEdsWhiteBalance_WhitePaper,
    EOSWhiteBalance_Shade       = kEdsWhiteBalance_Shade,
    EOSWhiteBalance_ColorTemp   = kEdsWhiteBalance_ColorTemp,
    EOSWhiteBalance_PC1         = kEdsWhiteBalance_PCSet1,
    EOSWhiteBalance_PC2         = kEdsWhiteBalance_PCSet2,
    EOSWhiteBalance_PC3         = kEdsWhiteBalance_PCSet3,
    EOSWhiteBalance_Manual2 = kEdsWhiteBalance_WhitePaper2,
    EOSWhiteBalance_Manual3 = kEdsWhiteBalance_WhitePaper3,
    EOSWhiteBalance_Manual4 = kEdsWhiteBalance_WhitePaper4,
    EOSWhiteBalance_Manual5 = kEdsWhiteBalance_WhitePaper5,
    EOSWhiteBalance_PC4         = kEdsWhiteBalance_PCSet4,
    EOSWhiteBalance_PC5         = kEdsWhiteBalance_PCSet5,
    EOSWhiteBalance_Click       = kEdsWhiteBalance_Click,
    EOSWhiteBalance_Pasted      = kEdsWhiteBalance_Pasted
    
};

typedef NS_ENUM(NSUInteger, EOSExposureCompensation){
    
    EOSExposureCompensation_Plus_3 = 0x18,
    EOSExposureCompensation_Plus_2__2_3 = 0x15,
    EOSExposureCompensation_Plus_2__1_2 = 0x14,
    EOSExposureCompensation_Plus_2__1_3 = 0x13,
    EOSExposureCompensation_Plus_2 = 0x10,
    EOSExposureCompensation_Plus_1__2_3 = 0x0d,
    EOSExposureCompensation_Plus_1__1_2 = 0x0c,
    EOSExposureCompensation_Plus_1__1_3 = 0x0b,
    EOSExposureCompensation_Plus_1 = 0x08,
    EOSExposureCompensation_Plus_2_3 = 0x05,
    EOSExposureCompensation_Plus_1_2 = 0x04,
    EOSExposureCompensation_Plus_1_3 = 0x03,
    EOSExposureCompensation_Zero = 0x00,
    EOSExposureCompensation_Minus_1_3 = 0xfd,
    EOSExposureCompensation_Minus_1_2 = 0xfc,
    EOSExposureCompensation_Minus_2_3 = 0xfb,
    EOSExposureCompensation_Minus_1 = 0xf8,
    EOSExposureCompensation_Minus_1__1_3 = 0xf5,
    EOSExposureCompensation_Minus_1__1_2 = 0xf4,
    EOSExposureCompensation_Minus_1__2_3 = 0xf3,
    EOSExposureCompensation_Minus_2 = 0xf0,
    EOSExposureCompensation_Minus_2__1_3 = 0xed,
    EOSExposureCompensation_Minus_2__1_2 = 0xec,
    EOSExposureCompensation_Minus_2__2_3 = 0xeb,
    EOSExposureCompensation_Minus_3 = 0xe8,

    EOSExposureCompensation_Unknown = 0xffffffff
    
};



typedef NS_ENUM(NSUInteger, EOSDriveMode){
    
    EOSDriveMode_Single                             = 0x00000000,
    EOSDriveMode_Continuous                         = 0x00000001,
    EOSDriveMode_Video                              = 0x00000002,
    EOSDriveMode_NotUsed                            = 0x00000003,
    EOSDriveMode_Continuous_LowSpeed                = 0x00000004,
    EOSDriveMode_Continuous_HighSpeed               = 0x00000005,
    EOSDriveMode_SilentSingle                       = 0x00000006,
    EOSDriveMode_Timer_10Seconds_WithContinuousShots= 0x00000007,
    EOSDriveMode_Timer_10Seconds                    = 0x00000010,
    EOSDriveMode_Timer_2Seconds                     = 0x00000011
    
};

typedef NS_ENUM(NSUInteger, EOSAEMode){

    EOSAEMode_Program          = kEdsAEMode_Program,
    EOSAEMode_Tv               = kEdsAEMode_Tv,
    EOSAEMode_Av               = kEdsAEMode_Av,
    EOSAEMode_Manual           = kEdsAEMode_Manual,
    EOSAEMode_Bulb             = kEdsAEMode_Bulb,
    EOSAEMode_A_DEP            = kEdsAEMode_A_DEP,
    EOSAEMode_DEP              = kEdsAEMode_DEP,
    EOSAEMode_Custom           = kEdsAEMode_Custom,
    EOSAEMode_Lock             = kEdsAEMode_Lock,
    EOSAEMode_Green            = kEdsAEMode_Green,
    EOSAEMode_NightPortrait    = kEdsAEMode_NightPortrait,
    EOSAEMode_Sports           = kEdsAEMode_Sports,
    EOSAEMode_Portrait         = kEdsAEMode_Portrait,
    EOSAEMode_Landscape        = kEdsAEMode_Landscape,
    EOSAEMode_Closeup          = kEdsAEMode_Closeup,
    EOSAEMode_FlashOff         = kEdsAEMode_FlashOff,
    EOSAEMode_CreativeAuto     = kEdsAEMode_CreativeAuto,
    EOSAEMode_Movie             = kEdsAEMode_Movie,
    EOSAEMode_PhotoInMovie		= kEdsAEMode_PhotoInMovie,
    EOSAEMode_SceneIntelligentAuto	= kEdsAEMode_SceneIntelligentAuto,
    EOSAEMode_SCN              = kEdsAEMode_SCN,
    EOSAEMode_Unknown          = kEdsAEMode_Unknown

};

typedef NS_ENUM(NSUInteger, EOSBatteryQuality){
    
    EOSBatteryQuality_Full = 3,
    EOSBatteryQuality_High = 2,
    EOSBatteryQuality_Half = 1,
    EOSBatteryQuality_Low  = 0
    
};

typedef NS_ENUM(NSUInteger, EOSMeteringMode){
    
    EOSMeteringMode_Spot        = 1,
    EOSMeteringMode_Evaluative  = 3,
    EOSMeteringMode_Partial     = 4,
    EOSMeteringMode_CenterWeighted = 5,
    EOSMeteringMode_Unknown     = 0xFFFFFFFF
    
};

typedef NS_ENUM(NSUInteger, EOSAFMode){
    
    EOSAFMode_OneShot = 0,
    EOSAFMode_AIServo = 1,
    EOSAFMode_AIFocus = 2,
    EOSAFMode_Manual = 3,
    EOSAFMode_Unknown = 0xffffffff
    
};


/**
 EOSPropertyObject is the underlying class of EOSCamera and EOSImage. It provides methods for getting and setting properties. It is a subclass of EOSObject.
 */
@interface EOSPropertyObject : EOSObject


///-------------------------
/// @name Getting Properties
///-------------------------

/*!
 @brief Gets the numeric value of a property with a parameter.
 @param property The property.
 @param parameter A parameter for the property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return A numeric value if successful, otherwise nil.
 */
-(NSNumber*)numberValueForProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError* __autoreleasing*)error;

/*!
 @brief Gets the numeric value of a property.
 @param property The property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return A numeric value if successful, otherwise nil.
 */
-(NSNumber*)numberValueForProperty:(EOSProperty)property error:(NSError* __autoreleasing*)error;


/*!
 @brief Gets the string value of a property with a parameter.
 @param property The property.
 @param parameter A parameter for the property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return A string value if successful, otherwise nil.
 */
-(NSString*)stringValueForProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError* __autoreleasing*)error;


/*!
 @brief Gets the string value of a property.
 @param property The property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return A string value if successful, otherwise nil.
 */
-(NSString*)stringValueForProperty:(EOSProperty)property error:(NSError* __autoreleasing*)error;



///-------------------------
/// @name Setting Properties
///-------------------------

/*!
 @brief Sets the numeric value of a property with a parameter.
 @param value The numeric value to set.
 @param property The property.
 @param parameter A parameter for the property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)setNumberValue:(NSNumber*)value forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError* __autoreleasing*)error;


/*!
 @brief Sets the numeric value of a property.
 @param value The numeric value to set.
 @param property The property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)setNumberValue:(NSNumber*)value forProperty:(EOSProperty)property error:(NSError* __autoreleasing*)error;


/*!
 @brief Sets the string value of a property with a parameter.
 @param value The string value to set.
 @param property The property.
 @param parameter A parameter for the property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)setStringValue:(NSString*)value forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError* __autoreleasing*)error;

/*!
 @brief Sets the string value of a property.
 @param value The string value to set.
 @param property The property.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)setStringValue:(NSString *)value forProperty:(EOSProperty)property error:(NSError *__autoreleasing *)error;



///-----------------------
/// @name Advanced Methods
///-----------------------

/*!
 @brief Gets the size and data type of a property value.
 @param size The size of the property value in bytes.
 @param dataType The data type of the property value.
 @param property The property.
 @param parameter A parameter for the property (use 0 if not required).
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)getValueSize:(NSUInteger*)size dataType:(EdsDataType*)dataType forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError* __autoreleasing*)error;

/*!
 @brief Gets the value (of unknown type) of a property.
 @discussion See the EDSDK documentation for the type of value that will be returned.
 @warning Using this method is not recommended. Use getNumericValue:forProperty:error: or getStringValue:forProperty:error: instead.
 @param value The value that will be retrieved.
 @param size The amount of bytes to retreive.
 @param property The property of the value that is being retrieved.
 @param parameter A parameter for the property (use 0 if not required).
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)getValue:(void*)value ofSize:(NSUInteger)size forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError* __autoreleasing*)error;

/*!
 @brief Sets the value (of unknown type) of a property
 @discussion See the EDSDK documentation for the type of value that should be provided.
 @warning Using this method is not recommended. Use setNumericValue:forProperty:error: or setStringValue:forProperty:error: instead.
 @param value The new value to set.
 @param size The size of the value in bytes.
 @param property The property.
 @param parameter A parameter for the property (use 0 if not required).
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)setValue:(const void*)value ofSize:(NSUInteger)size forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError* __autoreleasing*)error;

@end
