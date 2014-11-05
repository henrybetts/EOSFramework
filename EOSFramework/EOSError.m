//
//  EOSError.m
//  EOSFramework
//
//  Created by Henry Betts on 23/09/2014.
//  Copyright (c) 2014 Henry Betts. All rights reserved.
//

#import "EOSError.h"

NSString *const EOSErrorDomain = @"com.EOSManager";

EOSErrorType EOSGetErrorType(EOSError errorCode){

    switch (errorCode) {
    
        /*-----------------------------------------------------------------------
         ED-SDK Functin Success Code
         ------------------------------------------------------------------------*/
        case EOSError_OK:
            return EOSErrorType_OK;
        
        
        /*-----------------------------------------------------------------------
         ED-SDK Generic Error IDs
         ------------------------------------------------------------------------*/
        /* Miscellaneous errors */
        case EOSError_Unimplemented:
        case EOSError_InternalError:
        case EOSError_MemoryAllocationFailed:
        case EOSError_MemoryFreeFailed:
        case EOSError_OperationCancelled:
        case EOSError_IncompatibleVersion:
        case EOSError_NotSupported:
        case EOSError_UnexpectedException:
        case EOSError_ProtectionViolation:
        case EOSError_MissingSubcomponent:
        case EOSError_SelectionUnavailable:
            return EOSErrorType_Misc;
        
        /* File errors */
        case EOSError_File_IOError:
        case EOSError_File_TooManyOpen:
        case EOSError_File_NotFound:
        case EOSError_File_OpenError:
        case EOSError_File_CloseError:
        case EOSError_File_SeekError:
        case EOSError_File_TellError:
        case EOSError_File_ReadError:
        case EOSError_File_WriteError:
        case EOSError_File_PermissionError:
        case EOSError_File_DiskFull:
        case EOSError_File_AlreadyExists:
        case EOSError_File_FormatUnrecognized:
        case EOSError_File_DataCorrupt:
        case EOSError_File_FileNamingError:
            return EOSErrorType_File;
        
        /* Directory errors */
        case EOSError_Directory_NotFound:
        case EOSError_Directory_IOError:
        case EOSError_Directory_ChildNotFound:
        case EOSError_Directory_ContainsChild:
        case EOSError_Directory_Full:
            return EOSErrorType_Directory;
        
        /* Property errors */
        case EOSError_Property_Unavailable:
        case EOSError_Property_Mismatch:
        case EOSError_Property_NotLoaded:
            return EOSErrorType_Property;
        
        /* Function Parameter errors */
        case EOSError_InvalidParameter:
        case EOSError_InvalidHandle:
        case EOSError_InvalidPointer:
        case EOSError_InvalidIndex:
        case EOSError_InvalidLength:
        case EOSError_InvalidFunctionPointer:
        case EOSError_InvalidSortFunction:
            return EOSErrorType_Function;
        
        /* Device errors */
        case EOSError_Device_NotFound:
        case EOSError_Device_Busy:
        case EOSError_Device_Invalid:
        case EOSError_Device_Emergency:
        case EOSError_Device_MemoryFull:
        case EOSError_Device_InternalError:
        case EOSError_Device_InvalidParameter:
        case EOSError_Device_NoDisk:
        case EOSError_Device_DiskError:
        case EOSError_Device_CFGateChanged:
        case EOSError_Device_DialChanged:
        case EOSError_Device_NotInstalled:
        case EOSError_Device_StayAwake:
        case EOSError_Device_NotReleased:
        case EOSError_Device_LockError:
        case EOSError_Device_UnlockError:
            return EOSErrorType_Device;
            
        /* Stream errors */
        case EOSError_Stream_IOError:
        case EOSError_Stream_NotOpen:
        case EOSError_Stream_AlreadyOpen:
        case EOSError_Stream_OpenError:
        case EOSError_Stream_CloseError:
        case EOSError_Stream_SeekError:
        case EOSError_Stream_TellError:
        case EOSError_Stream_ReadError:
        case EOSError_Stream_WriteError:
        case EOSError_Stream_PermissionError:
        case EOSError_Stream_CouldNotBeginThread:
        case EOSError_Stream_BadOptions:
        case EOSError_Stream_EndOfStream:
            return EOSErrorType_Stream;
        
        /* Communications errors */
        case EOSError_COMM_PortInUse:
        case EOSError_COMM_Disconnected:
        case EOSError_COMM_DeviceIncompatible:
        case EOSError_COMM_BufferFull:
        case EOSError_COMM_USBError:
            return EOSErrorType_Comms;
        
        
        /* STI/WIA */
        case EOSError_STI_Unknown:
        case EOSError_STI_InternalError:
        case EOSError_STI_DeviceCreationError:
        case EOSError_STI_DeviceReleaseError:
        case EOSError_STI_DeviceNotLaunched:
            return EOSErrorType_STI;
        
        /* Other general errors */
        /* EOSErrorType_Other is default */
//        case EOSError_EnumerationFailed:
//        case EOSError_InvalidFunctionCall:
//        case EOSError_HandleNotFound:
//        case EOSError_InvalidID:
//        case EOSError_Timeout:
        
        /* PTP */
        case EOSError_PTP_SessionNotOpen:
        case EOSError_PTP_InvalidTransactionID:
        case EOSError_PTP_IncompleteTransfer:
        case EOSError_PTP_InvalidStorageID:
        case EOSError_PTP_UnsupportedProperty:
        case EOSError_PTP_InvalidObjectFormatCode:
        case EOSError_PTP_SelfTestFailed:
        case EOSError_PTP_PartialDeletion:
        case EOSError_PTP_UnsupportedFormatSpecification:
        case EOSError_PTP_InvalidObjectInfo:
        case EOSError_PTP_InvalidCodeFormat:
        case EOSError_PTP_UnknownVendorCode:
        case EOSError_PTP_CaptureAlreadyTerminated:
        case EOSError_PTP_InvalidParentObject:
        case EOSError_PTP_InvalidPropertyFormat:
        case EOSError_PTP_InvalidPropertyValue:
        case EOSError_PTP_SessionAlreadyOpen:
        case EOSError_PTP_TransactionCancelled:
        case EOSError_PTP_UnsupportedDestinationSpecification:
        case EOSError_PTP_LegacyCamera:

        
        /* PTP Vendor */
        case EOSError_PTP_UnknownCommand:
        case EOSError_PTP_OperationRefused:
        case EOSError_PTP_LensCoverClosed:
        case EOSError_PTP_LowBattery:
        case EOSError_PTP_ObjectNotReady:
        case EOSError_PTP_CannotMakeObject:
        case EOSError_PTP_MemoryStatusNotReady:
            return EOSErrorType_PTP;
        
        /* Take Picture errors */
        case EOSError_TakePicture_AF:
        case EOSError_TakePicture_Reserved:
        case EOSError_TakePicture_MirrorUp:
        case EOSError_TakePicture_SensorCleaning:
        case EOSError_TakePicture_Silence:
        case EOSError_TakePicture_NoCard:
        case EOSError_TakePicture_WriteError:
        case EOSError_TakePicture_CardProtected:
        case EOSError_TakePicture_MovieCrop:
        case EOSError_TakePicture_StrobeCharge:
        case EOSError_TakePicture_NoLens:
        case EOSError_TakePicture_SpecialMovieMode:
        case EOSError_TakePicture_LVError:
            return EOSErrorType_TakePicture;
            
        default:
            return EOSErrorType_Other;
            
    }
    
}

NSError* EOSCreateError(EOSError errorCode){

    if (errorCode == EOSError_OK)
        return nil;
    
    NSString* title, *description;
    
    EOSErrorType errorType = EOSErrorTypeFromCode(errorCode);
    
    switch (errorType) {
            
        case EOSErrorType_Misc:
            title = @"Miscellaneous Error";
            break;
            
        case EOSErrorType_File:
            title = @"File Error";
            break;
            
        case EOSErrorType_Directory:
            title = @"Directory Error";
            break;
            
        case EOSErrorType_Property:
            title = @"Property Error";
            break;
            
        case EOSErrorType_Function:
            title = @"Function Error";
            break;
            
        case EOSErrorType_Device:
            title = @"Device Error";

            switch (errorCode){
                    
                case EOSError_Device_Busy:
                    description = @"The device is busy";
                    break;
                case EOSError_Device_CFGateChanged:
                    description = @"The CF gate has been changed";
                    break;
                case EOSError_Device_DialChanged:
                    description = @"The dial has been changed";
                    break;
                case EOSError_Device_DiskError:
                    description = @"Disk error";
                    break;
                case EOSError_Device_Emergency:
                    description = @"Device emergency";
                    break;
                case EOSError_Device_InternalError:
                    description = @"Internal device error";
                    break;
                case EOSError_Device_Invalid:
                    description = @"Invalid device";
                    break;
                case EOSError_Device_InvalidParameter:
                    description = @"Invalid parameters";
                    break;
                case EOSError_Device_LockError:
                    description = @"Failed to lock the UI";
                    break;
                case EOSError_Device_MemoryFull:
                    description = @"Device memory full";
                    break;
                case EOSError_Device_NoDisk:
                    description = @"No disk";
                    break;
                case EOSError_Device_NotFound:
                    description = @"Device not found";
                    break;
                case EOSError_Device_NotInstalled:
                    description = @"Device not installed";
                    break;
                case EOSError_Device_NotReleased:
                    description = @"Device not released";
                    break;
                case EOSError_Device_StayAwake:
                    description = @"Device connected in awake mode";
                    break;
                case EOSError_Device_UnlockError:
                    description = @"Failed to unlock the UI";
                    break;
                default:
                    break;
                    
            }
            
            break;
            
        case EOSErrorType_Stream:
            title = @"Stream Error";
            break;
            
        case EOSErrorType_Comms:
            title = @"Communications Error";
            break;

        case EOSErrorType_STI:
            title = @"STI Error";
            break;
            
        case EOSErrorType_PTP:
            title = @"PTP Error";
            break;
            
        case EOSErrorType_TakePicture:
            title = @"Take Picture Error";
            break;
            
        default:
            title = @"Error";
            break;
            
    }
    
            
    NSDictionary* userInfo = [NSDictionary dictionaryWithObjectsAndKeys:
                title, NSLocalizedDescriptionKey,
                description, NSLocalizedFailureReasonErrorKey,
                nil];
    
    return [NSError errorWithDomain:EOSErrorDomain code:errorCode userInfo:userInfo];
    
}
