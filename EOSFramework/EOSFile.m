//
//  EOSFile.m
//  EOSFramework
//
//  Created by Henry Betts on 25/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <EOSFramework/EOSFile.h>
#import <EDSDK/EDSDK.h>
#import <EOSFramework/EOSError.h>

NSString *const EOSDownloadDirectoryURL = @"EOSDownloadDirectoryURL";
NSString *const EOSSaveAsFilename = @"EOSSaveAsFilename";
NSString *const EOSSavedFilename = @"EOSSavedFilename";
NSString *const EOSOverwrite = @"EOSOverwrite";

//EDSCALLBACK EdsError downloadProgressCallback(EdsUInt32 inPercent, EdsVoid* inContext, EdsBool* outCancel){
//    
//    NSArray* array = (__bridge NSArray *)(inContext);
//    id target = [array firstObject];
//    SEL selector = @selector(didReceiveDownloadProgress:forFile:withOptions:contextInfo:);
//
//    NSInvocation* inv = [NSInvocation invocationWithMethodSignature:[target methodSignatureForSelector:selector]];
//    
//    [inv setTarget:target];
//    [inv setSelector:selector];
//    
//    [inv setArgument:&inPercent atIndex:2]; //progress
//    
//    EOSFile* file = [array objectAtIndex:1];
//    NSDictionary* options = [array objectAtIndex:2];
//    id contextInfo = [array count] > 3 ? [array objectAtIndex:3] : nil;
//    
//    [inv setArgument:&file atIndex:3];
//    [inv setArgument:&options atIndex:4];
//    [inv setArgument:&contextInfo atIndex:5];
//    
//    dispatch_async(dispatch_get_main_queue(), ^(void){
//        [inv invoke];
//    });
//    
//    return EDS_ERR_OK;
//    
//};

@implementation EOSFile

//@synthesize baseRef = _baseRef;

-(id)initWithDirectoryItemRef:(EdsDirectoryItemRef)fileRef{
    
    return [self initWithBaseRef:fileRef];
    
}

-(EOSFileInfo*)info:(NSError *__autoreleasing *)error{

    EdsDirectoryItemInfo directoryItemInfo;

    EOSError errorCode = EdsGetDirectoryItemInfo(_baseRef, &directoryItemInfo);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return nil;
        
    }
    
    return [[EOSFileInfo alloc] initWithDirectoryItemInfo:directoryItemInfo];
    
}

-(EOSFileAttribute)attribute:(NSError *__autoreleasing *)error{
    
    EdsFileAttributes attribute;
    
    EOSError errorCode = EdsGetAttribute(_baseRef, &attribute);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NSNotFound;
        
    }
    
    return (EOSFileAttribute)attribute;
    
}

-(BOOL)setAttribute:(EOSFileAttribute)attribute error:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsSetAttribute(_baseRef, (EdsFileAttributes)attribute);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    return YES;
    
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


-(void)downloadWithOptions:(NSDictionary *)options delegate:(id)delegate contextInfo:(id)contextInfo{
    
    //SEL didReceiveProgressSelector = @selector(didReceiveDownloadProgress:forFile:withOptions:contextInfo:);
    //BOOL delegateRespondsToProgress = [delegate respondsToSelector:didReceiveProgressSelector];
    
    //download in background thread
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        
        NSUInteger size = 0;
        EdsStreamRef stream = NULL;
        EOSError errorCode = EOSError_OK;
        NSDictionary* newOptions;
        NSError* error;
        
        
        //get info
        EOSFileInfo* info = [self info:&error];
        if (info == nil){
            
            errorCode = [error code];
            
        }
        
        if (errorCode == EOSError_OK){
            
            //get size
            size = [info size];
            
            
            
            //get download directory URL
            NSURL* downloadDirectoryURL = [options objectForKey:EOSDownloadDirectoryURL];
            
            //create directory if it doesn't exist
            if (![[NSFileManager defaultManager] fileExistsAtPath:[downloadDirectoryURL absoluteString]]){
                
                [[NSFileManager defaultManager] createDirectoryAtPath:[downloadDirectoryURL absoluteString] withIntermediateDirectories:NO attributes:nil error:nil];
                
            }
            
            
            //get target filename
            NSString* saveAsFilename = [options objectForKey:EOSSaveAsFilename];
            
            if (saveAsFilename == nil){
                saveAsFilename = [info name];
            }
            
            
            //update options to include savedFilename
            NSMutableDictionary* newOptionsM = [NSMutableDictionary dictionaryWithDictionary:options];
            [newOptionsM setObject:saveAsFilename forKey:EOSSavedFilename];
            newOptions = [NSDictionary dictionaryWithDictionary:newOptionsM];
            
            //full download URL
            NSURL* downloadURL = [NSURL URLWithString:saveAsFilename relativeToURL:downloadDirectoryURL];
            
            //disposition (overwrite or not)
            EdsFileCreateDisposition disposition = [[options objectForKey:EOSOverwrite] boolValue] == YES ? kEdsFileCreateDisposition_CreateAlways : kEdsFileCreateDisposition_CreateNew;
            
            
            
            //create file stream
            errorCode = EdsCreateFileStreamEx((__bridge CFURLRef)downloadURL, disposition, kEdsAccess_Write, &stream);
            
        }
        
        
//        if (errorCode == EOSError_OK){
//            
//            //setup progress update if necessary
//            if (delegateRespondsToProgress){
//                
//                //delegate followed by arguments for didReceiveDownloadProgress:forFile:withOptions:contextInfo: (except progress)
//                NSArray* callbackParams = [NSArray arrayWithObjects:
//                                           delegate,
//                                           self,
//                                           newOptions,
//                                           contextInfo,
//                                           nil];
//                
//
//                
//                errorCode = EdsSetProgressCallback(stream, downloadProgressCallback, kEdsProgressOption_Periodically, (__bridge EdsVoid *)(callbackParams));
//                
//            }
//            
//        }
        
        
        if (errorCode == EOSError_OK){
            
            //download
            errorCode = EdsDownload(_baseRef, (EdsUInt32)size, stream);
            
        }
        
        if (errorCode == EOSError_OK){
            
            //complete download
            errorCode = EdsDownloadComplete(_baseRef);
            
        }
        
        
        //release stream
        if (stream != NULL){
            
            EdsRelease(stream);
            stream = NULL;
            
        }
        
            
        error = EOSCreateError(errorCode);
        
        
        //prepare didDownloadFile:withOptions:contextInfo:error method

        SEL didDownloadSelector = @selector(didDownloadFile:withOptions:contextInfo:error:);
        NSInvocation* inv = [NSInvocation invocationWithMethodSignature:[delegate methodSignatureForSelector:didDownloadSelector]];
        
        [inv setTarget:delegate];
        [inv setSelector:didDownloadSelector];
        
        [inv setArgument:(__bridge void *)(self) atIndex:2]; //file
        [inv setArgument:&newOptions atIndex:3]; //options
        if (contextInfo)
            [inv setArgument:(__bridge void *)(contextInfo) atIndex:4]; //contextInfo
        [inv setArgument:&error atIndex:5]; //error
        
        //perform method on main thread
        [inv performSelectorOnMainThread:@selector(invoke) withObject:nil waitUntilDone:YES];
        
        
        
        
    });
    
}


//-(void)readDataWithDelegate:(id)delegate contextInfo:(id)contextInfo{
//    
//    SEL didReceiveProgressSelector = @selector(didReceiveReadProgress:forFile:contextInfo:);
//    BOOL delegateRespondsToProgress = [delegate respondsToSelector:didReceiveProgressSelector];
//    
//    //download in background thread
//    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
//        
//        NSData* data;
//        EdsStreamRef stream = NULL;
//        void* ptr = NULL;
//        
//        NSUInteger size = 0;
//        EOSError errorCode = EOSError_OK;
//        NSError* error;
//        
//        //get info
//        EOSFileInfo* info = [self getInfo:&error];
//        if (info == nil)
//            errorCode = [error code];
//        
//        
//        
//        if (error == EOSError_OK){
//            
//            //get size
//            size = [info size];
//            
//            
//            //create memory stream
//            errorCode = EdsCreateMemoryStream((int)size, &stream);
//            
//        }
//        
////        if (errorCode == EOSError_OK){
////            
////            //setup progress update if necessary
////            if (delegateRespondsToProgress){
////                
////                NSArray* callbackParams = [NSArray arrayWithObjects:
////                                           self,
////                                           contextInfo,
////                                           nil];
////                
////                NSArray* callbackContext = [NSArray arrayWithObjects:
////                                            delegate,
////                                            NSStringFromSelector(didReceiveProgressSelector),
////                                            callbackParams,
////                                            nil];
////                
////                error = EdsSetProgressCallback(stream, downloadProgressCallback, kEdsProgressOption_Periodically, (__bridge EdsVoid *)(callbackContext));
////                
////            }
////            
////        }
//        
//        if (errorCode == EOSError_OK){
//            
//            //start download
//            errorCode = EdsDownload(_baseRef, (int)size, stream);
//            
//        }
//        
//        if (errorCode == EOSError_OK){
//            
//            //complete download
//            errorCode = EdsDownloadComplete(_baseRef);
//            
//        }
//        
//        if (errorCode == EOSError_OK){
//            
//            //get stream pointer
//            errorCode = EdsGetPointer(stream, &ptr);
//            
//        }
//        
//        if (errorCode == EOSError_OK){
//            
//            //init NSData
//            data = [NSData dataWithBytes:ptr length:size];
//            
//        }
//        
//        if (stream != NULL){
//            
//            EdsRelease(stream);
//            stream = NULL;
//            
//        }
//        
//        error = EOSCreateError(errorCode);
//        
//        //prepare didReadData:forFile:contextInfo:error:
//        SEL didReadSelector = @selector(didReadData:forFile:contextInfo:error:);
//        
//        NSInvocation* inv = [NSInvocation invocationWithMethodSignature:[delegate methodSignatureForSelector:didReadSelector]];
//        
//        [inv setTarget:delegate];
//        [inv setSelector:didReadSelector];
//        
//        [inv setArgument:&data atIndex:2];
//        [inv setArgument:(__bridge void *)(self) atIndex:3];
//        [inv setArgument:(__bridge void *)(contextInfo) atIndex:4];
//        [inv setArgument:&error atIndex:5];
//        
//            
//        //perform on main thread
//        dispatch_async(dispatch_get_main_queue(), ^(void){
//                
//            [inv invoke];
//                
//        });
//        
//    });
//    
//}




-(BOOL)remove:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsDeleteDirectoryItem(_baseRef);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    return YES;
    
}

@end








@implementation EOSFileInfo

-(id)initWithSize:(NSUInteger)size isDirectory:(BOOL)isDirectory groupID:(NSUInteger)groupID name:(NSString *)name imageFormat:(EOSImageFormat)imageFormat{
    
    self = [super init];
    if (self){
        
        _size = size;
        _isDirectory = isDirectory;
        _groupID = groupID;
        _name = name;
        _imageFormat = imageFormat;
        
    }
    
    return self;
    
}

-(id)initWithDirectoryItemInfo:(EdsDirectoryItemInfo)fileInfo{
    
    return [self initWithSize:fileInfo.size isDirectory:fileInfo.isFolder groupID:fileInfo.groupID name:[NSString stringWithUTF8String:fileInfo.szFileName] imageFormat:fileInfo.format];
    
}

@end