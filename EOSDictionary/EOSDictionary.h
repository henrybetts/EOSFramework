//
//  EOSDefualtDictionary.h
//  EOSManager
//
//  Created by Henry Betts on 17/10/2014.
//  Copyright (c) 2014 Henry Betts. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EOSDictionary : NSObject

+(EOSDictionary*)defaultDictionary;

@property NSDictionary* aperture;
@property NSDictionary* shutterSpeed;
@property NSDictionary* iso;
@property NSDictionary* whiteBalance;
@property NSDictionary* exposureCompensation;

@property NSDictionary* imageQuality;

@property NSDictionary* driveMode;

@property NSDictionary* AEMode;

@property NSDictionary* imageSize;
@property NSDictionary* imageFormat;
@property NSDictionary* compressionQuality;

@property NSDictionary* batteryQuality;
@property NSDictionary* meteringMode;

@end