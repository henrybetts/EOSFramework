//
//  EOSImage.m
//  EOSFramework
//
//  Created by Henry Betts on 25/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <EOSFramework/EOSImage.h>

EOSImageQuality EOSImageQualityFromCode(NSUInteger imageQualityCode){
    
    EOSImageQuality imageQuality;
    
    imageQuality.size = (imageQualityCode >> 24) & 255;
    imageQuality.format = (imageQualityCode >> 20) & 15;
    imageQuality.compressionQuality = (imageQualityCode >> 16) & 15;
    
    imageQuality.secondarySize = (imageQualityCode >> 8) & 255;
    imageQuality.secondaryFormat = (imageQualityCode >> 4) & 15;
    imageQuality.secondaryCompressionQuality = imageQualityCode & 15;
    
    return imageQuality;
    
}

@implementation EOSImage

-(id)initWithImageRef:(EdsImageRef)imageRef{
    
    return [super initWithBaseRef:imageRef];
    
}

@end
