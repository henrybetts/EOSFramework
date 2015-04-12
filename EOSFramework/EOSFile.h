//
//  EOSFile.h
//  EOSFramework
//
//  Created by Henry Betts on 25/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <Foundation/Foundation.h>
#import <EOSFramework/EOSObject.h>
#import <EOSFramework/EOSImage.h>


/*!
 @brief File attributes
 */
typedef NS_ENUM(NSUInteger, EOSFileAttribute){
    
    EOSFileAttribute_Normal     = kEdsFileAttribute_Normal,
    EOSFileAttribute_ReadOnly   = kEdsFileAttribute_ReadOnly,
    EOSFileAttribute_Hidden     = kEdsFileAttribute_Hidden,
    EOSFileAttribute_System     = kEdsFileAttribute_System,
    EOSFileAttribute_Archive    = kEdsFileAttribute_Archive
    
};

@protocol EOSDownloadDelegate;
@protocol EOSReadDataDelegate;


// Allowed keys in the options dictionary used when downloading a file

/*!
 @const EOSDownloadDirectoryURLKey
 @brief   Download directory URL.
 @discussion The value for this key should be an NSURL object referencing a writable directory. The downloaded file will be saved in that directory.
 */
FOUNDATION_EXPORT NSString *const EOSDownloadDirectoryURLKey;

/*!
 @const EOSSaveAsFilenameKey
 @brief   Save as filename.
 @discussion The value for this key should be an NSString object containing the name to be used for the downloaded file.
 */
FOUNDATION_EXPORT NSString *const EOSSaveAsFilenameKey;

/*!
 @const      EOSSavedFilenameKey
 @abstract   Saved filename.
 @discussion The value for this key will be an NSString object containing the actual name of the saved file. The options dictionary returned in the EOSDownloadDelegate methods will have this key.
 */
FOUNDATION_EXPORT NSString *const EOSSavedFilenameKey;


/*!
 @const      EOSOverwriteKey
 @abstract   Overwrite existing file?
 @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the downloaded file will overwrite an existing file with the same name and extension.
 */
FOUNDATION_EXPORT NSString *const EOSOverwriteKey;






/*!
 The EOSFileInfo class is used to store infomation about a file stored on a camera. Instances of this class will typically be created by the [EOSFile info:] method.
 */
@interface EOSFileInfo : NSObject

///-----------------
/// @name Properties
///-----------------

/*!
 @brief The size of the file, in bytes.
 @discussion If the file is a directory, this value will be 0.
 */
@property NSUInteger size;

/*!
 @brief Indicates whether the file is a directory.
 */
@property BOOL isDirectory;

/*!
 @brief The group ID of the file.
 @discussion The same group ID is assigned to files that belong to the same group, such as RAW+JPEG images or RAW+AVI images.
 */
@property NSUInteger groupID;

/*!
 @brief The name of the file.
 */
@property NSString* name;

/*!
 @brief The image format of the file.
 @discussion If the file is not an image, this value will be EOSImageType_Unknown.
 */
@property EOSImageFormat imageFormat;


/*
 Not in documentation
 */
//@property NSUInteger dateTime;



///---------------------
/// @name Initialization
///---------------------

/*!
 @brief Initializes a newly allocated EOSFileInfo instance with all of it's properties.
 @param size size
 @param isDirectory isDirectory
 @param groupID groupID
 @param name name
 @param imageFormat imageFormat
 @return The intialized EOSFileInfo instance.
 */
-(id)initWithSize:(NSUInteger)size isDirectory:(BOOL)isDirectory groupID:(NSUInteger)groupID name:(NSString*)name imageFormat:(EOSImageFormat)imageFormat;


/*!
 @brief Initializes a newly allocated EOSFileInfo instance with the properties of an EdsDirectoryItemInfo struct.
 @param fileInfo An EdsDirectoryItemInfo struct.
 @return The intialized EOSFileInfo object.
 */
-(id)initWithDirectoryItemInfo:(EdsDirectoryItemInfo)fileInfo;

@end














/*!
 The EOSFile class is used to represent a file that is stored on a camera.
 */
@interface EOSFile : EOSObject

///---------------------
/// @name Initialization
///---------------------

/*!
 @brief Initializes a newly allocated EOSFile instance with a reference to an EDSDK file object.
 @param fileRef The EDSDK file reference.
 @return The initialized EOSFile object.
*/
-(id)initWithDirectoryItemRef:(EdsDirectoryItemRef)fileRef;



///-------------------------------
/// @name Getting File Information
///-------------------------------

/*!
 @brief Gets information about the file.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return if successful, an EOSFileInfo object, otherwise nil
 */
-(EOSFileInfo*)info:(NSError* __autoreleasing*)error;



///-------------------------------------
/// @name Getting and Setting Attributes
///-------------------------------------

/*!
 @brief Gets the attribute of the file.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return If successful an EOSFileAttribute value, otherwise NSNotFound.
 */
-(EOSFileAttribute)attribute:(NSError* __autoreleasing*)error;

/*!
 @brief Sets the attribute of the file.
 @param attribute The new attribute.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)setAttribute:(EOSFileAttribute)attribute error:(NSError* __autoreleasing*)error;



///--------------------
/// @name Getting Files
///--------------------

/*!
 @brief Gets the number of files that are directly contained within a directory.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return If successful, the number of children, otherwise nil.
 */
-(NSNumber*)fileCount:(NSError* __autoreleasing*)error;

/*!
 @brief Gets the file that is directly contained within a directory at the specified index.
 @discussion Use fileCount: to find the valid index range.
 @param index The index of the file to get
 @param error If unsuccessful, an instance of NSError describes the problem
 @return If successful, an EOSFile object representing the file, otherwise nil
 */
-(EOSFile*)fileAtIndex:(NSUInteger)index error:(NSError* __autoreleasing *)error;

/**
 @brief Gets all of the files that are directly contained within a directory.
 @discussion If there is an error retrieving a child, the function will continue without adding it to the array. If you need to check for errors when reteiving each file, use fileAtIndex:error: instead.
 @return an array containing instances of EOSFile.
 */
-(NSArray*)files;



///------------------
/// @name Downloading
///------------------

/*!
 @brief Downloads the file asynchronously.
 @discussion When the download is completed, the didDownloadFile:withOptions:contextInfo:error method of the delegate object is called. The content of the error returned should be examined to determine if the download completed successfully. See EOSDownloadDelegate for more information. The options dictionary may contain the keys; EOSDownloadDirectoryURLKey, EOSSaveAsFilenameKey and EOSOverwriteKey.
 @param options A dictionary of options.
 @param delegate The download delegate.
 @param contextInfo An object that will be passed to the delegate methods. Can be nil.
 */
-(void)downloadWithOptions:(NSDictionary*)options delegate:(id<EOSDownloadDelegate>)delegate contextInfo:(id)contextInfo;

/**
 @brief Reads the data from the file asynchronously.
 @discussion When reading the data has completed, the didReadData:fromFile:contextInfo:error: method of the delegate object is called. The content of error returned should be examined to determine if reading the data completed successfully. See EOSReadDataDelegate for more information.
 @param delegate The read data delegate.
 @param contextInfo An object that will be passed to the delegate methods. Can be nil.
*/
-(void)readDataWithDelegate:(id<EOSReadDataDelegate>)delegate contextInfo:(id)contextInfo;



///---------------
/// @name Removing
///---------------

/*!
 @brief Deletes the file.
 @discussion If the file is a directory, all of its content is deleted except protected files.
 @param error If unsuccessful, an instance of NSError will describe the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)remove:(NSError* __autoreleasing*)error;

@end



/*!
 The EOSDownloadDelegate protocol defines the methods implemented by the delegate used during the download of a file.
 */
@protocol EOSDownloadDelegate <NSObject>

@required

/*!
 @brief Invoked when the download is complete.
 @discussion The content of error returned should be examined to determine if the download completed successfully. The options dictionary will contain the additional key; EOSSavedFilenameKey.
 @param file The file that was downloaded.
 @param options The dictionary of download options.
 @param contextInfo The object that was passed to the download method.
 @param error If unsuccessful, an instance of NSError describes the problem.
 */
-(void)didDownloadFile:(EOSFile*)file withOptions:(NSDictionary*)options contextInfo:(id)contextInfo error:(NSError*)error;

@optional

/*!
 @brief Invoked when progress is recieved for the download of a file.
 @discussion The options dictionary will contain the additional key; EOSSavedFilenameKey.
 @param progress The download progress as a percentage.
 @param file The file that is being downloaded.
 @param options The dictionary of download options.
 @param contextInfo The object that was passed to the download method.
 */
-(void)didReceiveDownloadProgress:(NSUInteger)progress forFile:(EOSFile*)file withOptions:(NSDictionary*)options contextInfo:(id)contextInfo;


@end


/*!
 The EOSReadDataDelegate protocol defines the methods implemented by the delegate used during the reading of file data.
 */
@protocol EOSReadDataDelegate <NSObject>

@required

/*!
 @brief Invoked when the reading of file data is complete.
 @discussion The content of error returned should be examined to determine if the reading completed successfully.
 @param data The file data.
 @param file The file that was read.
 @param contextInfo The object that was passed to the readData method.
 @param error If unsuccessful, an instance of NSError describes the problem.
 */
-(void)didReadData:(NSData*)data forFile:(EOSFile*)file contextInfo:(id)contextInfo error:(NSError*)error;

@optional

/*!
 @brief Invoked when progress is recieved for the reading of file data.
 @param progress The read progress as a percentage.
 @param file The file that is being read.
 @param contextInfo The object that was passed to the readData method.
 */
-(void)didReceiveReadProgress:(NSUInteger)progress forFile:(EOSFile*)file contextInfo:(id)contextInfo;

@end
