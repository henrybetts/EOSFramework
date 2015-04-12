//
//  EOSVolume.h
//  EOSFramework
//
//  Created by Henry Betts on 24/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <Foundation/Foundation.h>
#import <EOSFramework/EOSObject.h>

@class EOSFile;

/*!
 @brief Storage types
 */
typedef NS_ENUM(NSUInteger, EOSStorageType){
    
    EOSStorageType_None = kEdsStorageType_Non,
    EOSStorageType_CF   = kEdsStorageType_CF,
    EOSStorageType_SD   = kEdsStorageType_SD,
    EOSStorageType_HD   = kEdsStorageType_HD
    
};

/*!
 @brief Access types
 */
typedef NS_ENUM(NSUInteger, EOSAccess){
    
    EOSAccess_Read      = kEdsAccess_Read,
    EOSAccess_Write     = kEdsAccess_Write,
    EOSAccess_ReadWrite = kEdsAccess_ReadWrite,
    EOSAccess_Error     = kEdsAccess_Error
    
};







/*!
 The EOSVolumeInfo class is used to store infomation about a volume that is mounted on a camera. Instances of this class will typically be created by the [EOSVolume info:] method.
 */
@interface EOSVolumeInfo : NSObject

///-----------------
/// @name Properties
///-----------------

/*!
 The name of the volume
 */
@property NSString* name;

/*!
 The type of storage, as defined in EOSStorageType
 */
@property EOSStorageType storageType;

/*!
 The type of access, as defined in EOSAccess
 */
@property EOSAccess access;

/*!
 The total capacity of the volume, in bytes
 */
@property UInt64 capacity;

/*!
 The space available on the volume, in bytes
 */
@property UInt64 available;



///---------------------
/// @name Initialization
///---------------------

/**
 @brief Initializes a newly allocated EOSVolumeInfo instance with all of its properties.
 @param name name
 @param storageType storageType
 @param access access
 @param capacity capacity
 @param available available
 @return The intialized EOSVolumeInfo object.
 */
-(id)initWithName:(NSString*)name storageType:(EOSStorageType)storageType access:(EOSAccess)access capacity:(UInt64)capacity available:(UInt64)available;

/*!
 @brief Initializes a newly allocated EOSVolumeInfo instance with the properties of an EdsVolumeInfo struct.
 @param volumeInfo An EdsVolumeInfo struct.
 @return The intialized EOSFileInfo object.
 */
-(id)initWithVolumeInfo:(EdsVolumeInfo)volumeInfo;

@end







/*!
 The EOSVolume class is used to represent a volume that is mounted on a camera.
 */
@interface EOSVolume : EOSObject

///---------------------
/// @name Initialization
///---------------------

/*!
 @brief Initializes a newly allocated EOSVolume instance with a reference to an EDSDK volume object.
 @param volumeRef The EDSDK volume reference.
 @return The intialized EOSVolume object.
 */
-(id)initWithVolumeRef:(EdsVolumeRef)volumeRef;



///---------------------------------
/// @name Getting Volume Information
///---------------------------------

/*!
 @brief Gets information about the volume.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return If successful, a EOSVolumeInfo object, otherwise nil.
 */
-(EOSVolumeInfo*)info:(NSError* __autoreleasing*)error;



///--------------------
/// @name Getting Files
///--------------------

/*!
 @brief Gets the number of files that are in the root directory.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return If successful, the number of files, otherwise nil.
 */
-(NSNumber*)fileCount:(NSError* __autoreleasing*)error;

/*!
 @brief Gets the file that is in the root directory at the specified index.
 @discussion Use fileCount: to find the valid index range.
 @param index The index of the file to get.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return If successful, an EOSFile object representing the file, otherwise nil.
 */
-(EOSFile*)fileAtIndex:(NSUInteger)index error:(NSError* __autoreleasing *)error;

/*!
 @brief Gets all of the files that are in the root directory.
 @discussion If there is an error retrieving a file, the function will continue without adding it to the array. If you need to check for errors when reteiving each file, use fileAtIndex:error: instead.
 @return An array containing instances of EOSFile.
 */
-(NSArray*)files;


///----------------------------
/// @name Formatting the Volume
///----------------------------

/*!
 @brief Formats the volume
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)format:(NSError* __autoreleasing*)error;

@end