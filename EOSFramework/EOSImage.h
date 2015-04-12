//
//  EOSImage.h
//  EOSFramework
//
//  Created by Henry Betts on 25/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <EOSFramework/EOSPropertyObject.h>

typedef NS_ENUM(NSUInteger, EOSImageSize){
    
    EOSImageSize_Large         = kEdsImageSize_Large,
    EOSImageSize_Middle        = kEdsImageSize_Middle,
    EOSImageSize_Small         = kEdsImageSize_Small,
    EOSImageSize_Middle1       = kEdsImageSize_Middle1,
    EOSImageSize_Middle2       = kEdsImageSize_Middle2,
    EOSImageSize_Small1        = kEdsImageSize_Small1,
    EOSImageSize_Small2        = kEdsImageSize_Small2,
    EOSImageSize_Small3        = kEdsImageSize_Small3,
    EOSImageSize_Unknown       = kEdsImageSize_Unknown
    
};


typedef NS_ENUM(NSUInteger, EOSImageFormat){
    
    EOSImageFormat_Unknown    = kEdsImageType_Unknown,
    EOSImageFormat_JPEG       = kEdsImageType_Jpeg,
    EOSImageFormat_CRW        = kEdsImageType_CRW,
    EOSImageFormat_RAW        = kEdsImageType_RAW,
    EOSImageFormat_CR2        = kEdsImageType_CR2
    
};



typedef NS_ENUM(NSUInteger, EOSCompressionQuality){
    
    EOSCompressionQuality_Normal     = kEdsCompressQuality_Normal,
    EOSCompressionQuality_Fine       = kEdsCompressQuality_Fine,
    EOSCompressionQuality_Lossless   = kEdsCompressQuality_Lossless,
    EOSCompressionQuality_SuperFine  = kEdsCompressQuality_SuperFine,
    EOSCompressionQuality_Unknown    = kEdsCompressQuality_Unknown
    
};

/*!
 @struct EOSImageQuality
 @brief Contains information regarding an image's size, format and compression.
 @discussion Use the function EOSImageQualityFromCode to generate this struct from a number value retrieved from a camera.
 */
typedef struct _EOSImageQuality {
    
    EOSImageSize size;
    EOSImageFormat format;
    EOSCompressionQuality compressionQuality;
    
    EOSImageSize secondarySize;
    EOSImageFormat secondaryFormat;
    EOSCompressionQuality secondaryCompressionQuality;
    
} EOSImageQuality;

/*!
 @function EOSImageQualityFromCode
 @brief Creates an EOSImageQuality struct using the data from an image quality code.
 @discussion The value for the property EOSProperty_ImageQuality is an unsigned integer, which contains several pieces of information about the quality of the image(s). This function extracts the information using bitmasks and repackages it into an easier to use structure.
 @param imageQualityCode An image quality code, typically retrieved from a camera.
 @return An EOSImageQuality struct.
 */
FOUNDATION_EXPORT EOSImageQuality EOSImageQualityFromCode(NSUInteger imageQualityCode);


/*!
 EOSImage is a class used to represent an image. It is a subclass of EOSPropertyObject.
 */
@interface EOSImage : EOSPropertyObject

/*!
 Initialize the class with a reference to an image
 @param imageRef An EdsImageRef object
 @return the newly intialized EOSImage
 */
-(id)initWithImageRef:(EdsImageRef)imageRef;

@end
