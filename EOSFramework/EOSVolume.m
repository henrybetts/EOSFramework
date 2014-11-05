//
//  EOSVolume.m
//  EOSFramework
//
//  Created by Henry Betts on 24/09/2014.
//  Copyright (c) 2014 Henry Betts. All rights reserved.
//

#import <EOSFramework/EOSVolume.h>
#import <EOSFramework/EOSFile.h>
#import <EDSDK/EDSDK.h>
#import <EOSFramework/EOSError.h>

@implementation EOSVolume

-(id)initWithVolumeRef:(EdsVolumeRef)volumeRef{
    
    return [self initWithBaseRef:volumeRef];
    
}


-(EOSVolumeInfo*)info:(NSError *__autoreleasing *)error{
    
    EdsVolumeInfo volumeInfo;
    
    EOSError errorCode = EdsGetVolumeInfo(_baseRef, &volumeInfo);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return nil;
        
    }
    
    return [[EOSVolumeInfo alloc] initWithVolumeInfo:volumeInfo];
    
}

-(NSNumber*)fileCount:(NSError *__autoreleasing *)error{
    
    EdsUInt32 count;
    
    EOSError errorCode = EdsGetChildCount(_baseRef, &count);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return nil;
        
    }
    
    return [NSNumber numberWithUnsignedInteger:count];
    
}

-(EOSFile*)fileAtIndex:(NSUInteger)index error:(NSError *__autoreleasing *)error{
    
    EdsDirectoryItemRef fileRef;
    
    EOSError errorCode = EdsGetChildAtIndex(_baseRef, (int)index, &fileRef);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return nil;
        
    }
    
    return [[EOSFile alloc] initWithDirectoryItemRef:fileRef];
    
}

-(NSArray*)files{
    
    NSUInteger i, count = 0;
    NSNumber* countNumber = [self fileCount:nil];
    if (countNumber != nil)
        count = [countNumber integerValue];
    
    NSMutableArray* array = [NSMutableArray arrayWithCapacity:count];
    EOSFile* file;
    
    for (i=0; i<count; i++){
        
        file = [self fileAtIndex:i error:nil];
        if (file != nil)
            [array addObject:file];
        
    }
    
    return [NSArray arrayWithArray:array];
    
    
}

-(BOOL)format:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsFormatVolume(_baseRef);
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    return YES;
    
}

@end




@implementation EOSVolumeInfo

-(id)initWithName:(NSString *)name storageType:(EOSStorageType)storageType access:(EOSAccess)access capacity:(UInt64)capacity available:(UInt64)available{
    
    self = [super init];
    if (self){
        
        _name = name;
        _storageType = storageType;
        _access = access;
        _capacity = capacity;
        _available = available;
        
    }
    
    return self;
    
}

-(id)initWithVolumeInfo:(EdsVolumeInfo)volumeInfo{
    
    UInt64 capacity = volumeInfo.maxCapacity;
    UInt64 available = volumeInfo.freeSpaceInBytes;
    
    return [self initWithName:[NSString stringWithUTF8String:volumeInfo.szVolumeLabel] storageType:volumeInfo.storageType access:(EOSAccess)volumeInfo.access capacity:capacity available:available];
    
}

@end
