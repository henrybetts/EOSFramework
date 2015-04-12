//
//  EOSError.h
//  EOSFramework
//
//  Created by Henry Betts on 23/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <Foundation/Foundation.h>
#import <EDSDK/EDSDKErrors.h>


/*!
 @brief The domain of all EOS related errors.
 @discussion The global method EOSCreateError will use this domain when creating NSError instances.
*/
FOUNDATION_EXPORT NSString *const EOSErrorDomain;

/*!
 @brief Types of EOS related errors.
 @discussion Each EOSError code can be categorized into one of the EOSErrorType values.
 */
typedef NS_ENUM(NSInteger, EOSErrorType){
    
    EOSErrorType_OK,
    EOSErrorType_Misc,
    EOSErrorType_File,
    EOSErrorType_Directory,
    EOSErrorType_Property,
    EOSErrorType_Function,
    EOSErrorType_Device,
    EOSErrorType_Stream,
    EOSErrorType_Comms,
    EOSErrorType_STI,
    EOSErrorType_Other,
    EOSErrorType_PTP,
    EOSErrorType_TakePicture
    
};

/*!
 EOSError codes
 */
typedef NS_ENUM(NSUInteger, EOSError){
    
    /*-----------------------------------------------------------------------
     ED-SDK Functin Success Code
     ------------------------------------------------------------------------*/
    EOSError_OK = EDS_ERR_OK,

    
    /*-----------------------------------------------------------------------
     ED-SDK Generic Error IDs
     ------------------------------------------------------------------------*/
    /* Miscellaneous errors */
    EOSError_Unimplemented              = EDS_ERR_UNIMPLEMENTED,
    EOSError_InternalError              = EDS_ERR_INTERNAL_ERROR,
    EOSError_MemoryAllocationFailed     = EDS_ERR_MEM_ALLOC_FAILED,
    EOSError_MemoryFreeFailed           = EDS_ERR_MEM_FREE_FAILED,
    EOSError_OperationCancelled         = EDS_ERR_OPERATION_CANCELLED,
    EOSError_IncompatibleVersion        = EDS_ERR_INCOMPATIBLE_VERSION,
    EOSError_NotSupported               = EDS_ERR_NOT_SUPPORTED,
    EOSError_UnexpectedException        = EDS_ERR_UNEXPECTED_EXCEPTION,
    EOSError_ProtectionViolation        = EDS_ERR_PROTECTION_VIOLATION,
    EOSError_MissingSubcomponent        = EDS_ERR_MISSING_SUBCOMPONENT,
    EOSError_SelectionUnavailable       = EDS_ERR_SELECTION_UNAVAILABLE,
    
    /* File errors */
    EOSError_File_IOError               = EDS_ERR_FILE_IO_ERROR,
    EOSError_File_TooManyOpen           = EDS_ERR_FILE_TOO_MANY_OPEN,
    EOSError_File_NotFound              = EDS_ERR_FILE_NOT_FOUND,
    EOSError_File_OpenError             = EDS_ERR_FILE_OPEN_ERROR,
    EOSError_File_CloseError            = EDS_ERR_FILE_CLOSE_ERROR,
    EOSError_File_SeekError             = EDS_ERR_FILE_SEEK_ERROR,
    EOSError_File_TellError             = EDS_ERR_FILE_TELL_ERROR,
    EOSError_File_ReadError             = EDS_ERR_FILE_READ_ERROR,
    EOSError_File_WriteError            = EDS_ERR_FILE_WRITE_ERROR,
    EOSError_File_PermissionError       = EDS_ERR_FILE_PERMISSION_ERROR,
    EOSError_File_DiskFull              = EDS_ERR_FILE_DISK_FULL_ERROR,
    EOSError_File_AlreadyExists         = EDS_ERR_FILE_ALREADY_EXISTS,
    EOSError_File_FormatUnrecognized    = EDS_ERR_FILE_FORMAT_UNRECOGNIZED,
    EOSError_File_DataCorrupt           = EDS_ERR_FILE_DATA_CORRUPT,
    EOSError_File_FileNamingError       = EDS_ERR_FILE_NAMING_NA,

    
    /* Directory errors */
    EOSError_Directory_NotFound         = EDS_ERR_DIR_NOT_FOUND,
    EOSError_Directory_IOError          = EDS_ERR_DIR_IO_ERROR,
    EOSError_Directory_ChildNotFound    = EDS_ERR_DIR_ENTRY_NOT_FOUND,
    EOSError_Directory_ContainsChild    = EDS_ERR_DIR_ENTRY_EXISTS,
    EOSError_Directory_Full             = EDS_ERR_DIR_NOT_EMPTY,

    
    /* Property errors */
    EOSError_Property_Unavailable       = EDS_ERR_PROPERTIES_UNAVAILABLE,
    EOSError_Property_Mismatch          = EDS_ERR_PROPERTIES_MISMATCH,
    EOSError_Property_NotLoaded         = EDS_ERR_PROPERTIES_NOT_LOADED,
    
    /* Function Parameter errors */
    EOSError_InvalidParameter           = EDS_ERR_INVALID_PARAMETER,
    EOSError_InvalidHandle              = EDS_ERR_INVALID_HANDLE,
    EOSError_InvalidPointer             = EDS_ERR_INVALID_POINTER,
    EOSError_InvalidIndex               = EDS_ERR_INVALID_INDEX,
    EOSError_InvalidLength              = EDS_ERR_INVALID_LENGTH,
    EOSError_InvalidFunctionPointer     = EDS_ERR_INVALID_FN_POINTER,
    EOSError_InvalidSortFunction        = EDS_ERR_INVALID_SORT_FN,
    
    /* Device errors */
    EOSError_Device_NotFound            = EDS_ERR_DEVICE_NOT_FOUND,
    EOSError_Device_Busy                = EDS_ERR_DEVICE_BUSY,
    EOSError_Device_Invalid             = EDS_ERR_DEVICE_INVALID,
    EOSError_Device_Emergency           = EDS_ERR_DEVICE_EMERGENCY,
    EOSError_Device_MemoryFull          = EDS_ERR_DEVICE_MEMORY_FULL,
    EOSError_Device_InternalError       = EDS_ERR_DEVICE_INTERNAL_ERROR,
    EOSError_Device_InvalidParameter    = EDS_ERR_DEVICE_INVALID_PARAMETER,
    EOSError_Device_NoDisk              = EDS_ERR_DEVICE_NO_DISK,
    EOSError_Device_DiskError           = EDS_ERR_DEVICE_DISK_ERROR,
    EOSError_Device_CFGateChanged       = EDS_ERR_DEVICE_CF_GATE_CHANGED,
    EOSError_Device_DialChanged         = EDS_ERR_DEVICE_DIAL_CHANGED,
    EOSError_Device_NotInstalled        = EDS_ERR_DEVICE_NOT_INSTALLED,
    EOSError_Device_StayAwake           = EDS_ERR_DEVICE_STAY_AWAKE,
    EOSError_Device_NotReleased         = EDS_ERR_DEVICE_NOT_RELEASED,
    
    /* Stream errors */
    EOSError_Stream_IOError             = EDS_ERR_STREAM_IO_ERROR,
    EOSError_Stream_NotOpen             = EDS_ERR_STREAM_NOT_OPEN,
    EOSError_Stream_AlreadyOpen         = EDS_ERR_STREAM_ALREADY_OPEN,
    EOSError_Stream_OpenError           = EDS_ERR_STREAM_OPEN_ERROR,
    EOSError_Stream_CloseError          = EDS_ERR_STREAM_CLOSE_ERROR,
    EOSError_Stream_SeekError           = EDS_ERR_STREAM_SEEK_ERROR,
    EOSError_Stream_TellError           = EDS_ERR_STREAM_TELL_ERROR,
    EOSError_Stream_ReadError           = EDS_ERR_STREAM_READ_ERROR,
    EOSError_Stream_WriteError          = EDS_ERR_STREAM_WRITE_ERROR,
    EOSError_Stream_PermissionError     = EDS_ERR_STREAM_PERMISSION_ERROR,
    EOSError_Stream_CouldNotBeginThread = EDS_ERR_STREAM_COULDNT_BEGIN_THREAD,
    EOSError_Stream_BadOptions          = EDS_ERR_STREAM_BAD_OPTIONS,
    EOSError_Stream_EndOfStream         = EDS_ERR_STREAM_END_OF_STREAM,
    
    /* Communications errors */
    EOSError_COMM_PortInUse             = EDS_ERR_COMM_PORT_IS_IN_USE,
    EOSError_COMM_Disconnected          = EDS_ERR_COMM_DISCONNECTED,
    EOSError_COMM_DeviceIncompatible    = EDS_ERR_COMM_DEVICE_INCOMPATIBLE,
    EOSError_COMM_BufferFull            = EDS_ERR_COMM_BUFFER_FULL,
    EOSError_COMM_USBError              = EDS_ERR_COMM_USB_BUS_ERR,
    
    /* Lock/Unlock */
    EOSError_Device_LockError           = EDS_ERR_USB_DEVICE_LOCK_ERROR,
    EOSError_Device_UnlockError         = EDS_ERR_USB_DEVICE_UNLOCK_ERROR,
    
    /* STI/WIA */
    EOSError_STI_Unknown                = EDS_ERR_STI_UNKNOWN_ERROR,
    EOSError_STI_InternalError          = EDS_ERR_STI_INTERNAL_ERROR,
    EOSError_STI_DeviceCreationError    = EDS_ERR_STI_DEVICE_CREATE_ERROR,
    EOSError_STI_DeviceReleaseError     = EDS_ERR_STI_DEVICE_RELEASE_ERROR,
    EOSError_STI_DeviceNotLaunched      = EDS_ERR_DEVICE_NOT_LAUNCHED,

    /* Other general errors */
    EOSError_EnumerationFailed          = EDS_ERR_ENUM_NA,
    EOSError_InvalidFunctionCall        = EDS_ERR_INVALID_FN_CALL,
    EOSError_HandleNotFound             = EDS_ERR_HANDLE_NOT_FOUND,
    EOSError_InvalidID                  = EDS_ERR_INVALID_ID,
    EOSError_Timeout                    = EDS_ERR_WAIT_TIMEOUT_ERROR,
    
    /* PTP */
    EOSError_PTP_SessionNotOpen                 = EDS_ERR_SESSION_NOT_OPEN,
    EOSError_PTP_InvalidTransactionID           = EDS_ERR_INVALID_TRANSACTIONID,
    EOSError_PTP_IncompleteTransfer             = EDS_ERR_INCOMPLETE_TRANSFER,
    EOSError_PTP_InvalidStorageID               = EDS_ERR_INVALID_STRAGEID,
    EOSError_PTP_UnsupportedProperty            = EDS_ERR_DEVICEPROP_NOT_SUPPORTED,
    EOSError_PTP_InvalidObjectFormatCode        = EDS_ERR_INVALID_OBJECTFORMATCODE,
    EOSError_PTP_SelfTestFailed                 = EDS_ERR_SELF_TEST_FAILED,
    EOSError_PTP_PartialDeletion                = EDS_ERR_PARTIAL_DELETION,
    EOSError_PTP_UnsupportedFormatSpecification = EDS_ERR_SPECIFICATION_BY_FORMAT_UNSUPPORTED,
    EOSError_PTP_InvalidObjectInfo              = EDS_ERR_NO_VALID_OBJECTINFO,
    EOSError_PTP_InvalidCodeFormat              = EDS_ERR_INVALID_CODE_FORMAT,
    EOSError_PTP_UnknownVendorCode              = EDS_ERR_UNKNOWN_VENDOR_CODE,
    EOSError_PTP_CaptureAlreadyTerminated       = EDS_ERR_CAPTURE_ALREADY_TERMINATED,
    EOSError_PTP_InvalidParentObject            = EDS_ERR_INVALID_PARENTOBJECT,
    EOSError_PTP_InvalidPropertyFormat          = EDS_ERR_INVALID_DEVICEPROP_FORMAT,
    EOSError_PTP_InvalidPropertyValue           = EDS_ERR_INVALID_DEVICEPROP_VALUE,
    EOSError_PTP_SessionAlreadyOpen             = EDS_ERR_SESSION_ALREADY_OPEN,
    EOSError_PTP_TransactionCancelled           = EDS_ERR_TRANSACTION_CANCELLED,
    EOSError_PTP_UnsupportedDestinationSpecification    = EDS_ERR_SPECIFICATION_OF_DESTINATION_UNSUPPORTED,
    EOSError_PTP_LegacyCamera                   = EDS_ERR_NOT_CAMERA_SUPPORT_SDK_VERSION,
    
    /* PTP Vendor */
    EOSError_PTP_UnknownCommand         = EDS_ERR_UNKNOWN_COMMAND,
    EOSError_PTP_OperationRefused       = EDS_ERR_OPERATION_REFUSED,
    EOSError_PTP_LensCoverClosed        = EDS_ERR_LENS_COVER_CLOSE,
    EOSError_PTP_LowBattery             = EDS_ERR_LOW_BATTERY,
    EOSError_PTP_ObjectNotReady         = EDS_ERR_OBJECT_NOTREADY,
    EOSError_PTP_CannotMakeObject       = EDS_ERR_CANNOT_MAKE_OBJECT,
    EOSError_PTP_MemoryStatusNotReady   = EDS_ERR_MEMORYSTATUS_NOTREADY,
    
    /* Take Picture errors */
    EOSError_TakePicture_AF             = EDS_ERR_TAKE_PICTURE_AF_NG,
    EOSError_TakePicture_Reserved       = EDS_ERR_TAKE_PICTURE_RESERVED,
    EOSError_TakePicture_MirrorUp       = EDS_ERR_TAKE_PICTURE_MIRROR_UP_NG,
    EOSError_TakePicture_SensorCleaning = EDS_ERR_TAKE_PICTURE_SENSOR_CLEANING_NG,
    EOSError_TakePicture_Silence        = EDS_ERR_TAKE_PICTURE_SILENCE_NG,
    EOSError_TakePicture_NoCard         = EDS_ERR_TAKE_PICTURE_NO_CARD_NG,
    EOSError_TakePicture_WriteError     = EDS_ERR_TAKE_PICTURE_CARD_NG,
    EOSError_TakePicture_CardProtected  = EDS_ERR_TAKE_PICTURE_CARD_PROTECT_NG,
    EOSError_TakePicture_MovieCrop      = EDS_ERR_TAKE_PICTURE_MOVIE_CROP_NG,
    EOSError_TakePicture_StrobeCharge   = EDS_ERR_TAKE_PICTURE_STROBO_CHARGE_NG,
    EOSError_TakePicture_NoLens         = EDS_ERR_TAKE_PICTURE_NO_LENS_NG,
    EOSError_TakePicture_SpecialMovieMode   = EDS_ERR_TAKE_PICTURE_SPECIAL_MOVIE_MODE_NG,
    EOSError_TakePicture_LVError        = EDS_ERR_TAKE_PICTURE_LV_REL_PROHIBIT_MODE_NG,
    
};

/*!
 @brief Gets the error type of an EOSError code.
 @param errorCode An EOSError code.
 @return The type of error, as defined by EOSErrorType.
 */
FOUNDATION_EXPORT EOSErrorType EOSErrorTypeFromCode(EOSError errorCode);

/*!
 @brief Uses an EOSError code to generate an informative NSError object.
 @discussion The NSError's userInfo property may contain values for NSLocalizedDescriptionKey, and NSLocalizedFailureReasonErrorKey.
 @param errorCode An EOSError code.
 @return the NSError object.
 */
FOUNDATION_EXPORT NSError* EOSCreateError(EOSError errorCode);
