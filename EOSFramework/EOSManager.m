//
//  EOSManager.m
//  EOSFramework
//
//  Created by Henry Betts on 22/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <EOSFramework/EOSManager.h>
#import <EOSFramework/EOSError.h>
#import <EOSFramework/EOSCamera.h>

#import <EDSDK/EDSDK.h>
#import <EDSDK/EDSDKTypes.h>

EdsError EDSCALLBACK EOSManagerCameraAddedHandler(EdsVoid* inContext){
    
    EOSManager* manager = [EOSManager sharedManager];
    id delegate = [manager delegate];
    
    [delegate performSelector:@selector(cameraDidConnect)];
    
    return EDS_ERR_OK;
    
}

@implementation EOSManager

-(id)init{
    
    self = [super init];
    
    if (self){
        
        _isLoaded = false;
        _cameraList = [NSArray array];
        
    }
    
    return self;
    
}

+(EOSManager*)sharedManager{
    
    static dispatch_once_t pred = 0;
    __strong static id _sharedObject = nil;
    dispatch_once(&pred, ^{
        _sharedObject = [[self alloc] init];
    });
    return _sharedObject;
    
}

-(id)delegate{
    
    return _delegate;
    
}

-(void)setDelegate:(id)delegate{
    
    if (delegate != nil){
        
        if (_delegate == nil){
            
            //register for events
            EdsSetCameraAddedHandler(EOSManagerCameraAddedHandler, NULL);
            
        }
        
    }else{
        
        if (_delegate != nil){
            
            //stop receiving events
            EdsSetCameraAddedHandler(NULL, NULL);
            
        }
        
    }
    
    _delegate = delegate;
    
}

-(BOOL)load:(NSError *__autoreleasing *)error{
    

    EOSError errorCode = EdsInitializeSDK();
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    _isLoaded = YES;
    return YES;
    
}


-(BOOL)terminate:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsTerminateSDK();
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }

    _isLoaded = NO;
    return YES;
    
}



-(NSArray*)getCameras{

    EdsUInt32 i, count = 0;
    EdsCameraListRef cameraListRef = NULL;
    
    if (EdsGetCameraList(&cameraListRef) == EOSError_OK){
        
        EdsGetChildCount(cameraListRef, &count);
        //NSLog(@"count: %i", count);
        
    }
    
    NSMutableArray* newCameraList = [NSMutableArray arrayWithCapacity:count];
    
    EOSCamera* camera;
    EdsCameraRef cameraRef;
    
    for (i=0; i<count; i++){
        
        if (EdsGetChildAtIndex(cameraListRef, i, &cameraRef) == EOSError_OK){
            
            camera = [[EOSCamera alloc] initWithCameraRef:cameraRef];

            NSUInteger index = [_cameraList indexOfObject:camera];
            if (index == NSNotFound){
                //NSLog(@"Found new camera");
                [newCameraList addObject:camera];
                
            }else{
                //NSLog(@"Found existing camera");
                [newCameraList addObject:[_cameraList objectAtIndex:index]];
                
            }
            
        }
        
    }
    
    if (cameraListRef != NULL)
        EdsRelease(cameraListRef);
    
    _cameraList = [NSArray arrayWithArray:newCameraList];
    return _cameraList;

}

//-(NSArray*)getAddedCameras{
//    
//    NSArray* oldCameraList = [NSArray arrayWithArray:_cameraList];
//    NSArray* newCameraList = [self getCameras];
//    
//    NSMutableArray* addedCameras = [NSMutableArray array];
//    for (EOSCamera* camera in newCameraList){
//        
//        if (![oldCameraList containsObject:camera]){
//            
//            [addedCameras addObject:camera];
//            
//        }
//        
//    }
//    
//    return [NSArray arrayWithArray:addedCameras];
//    
//}
//
//-(NSArray*)getRemovedCameras{
//    
//    NSArray* oldCameraList = [NSArray arrayWithArray:_cameraList];
//    NSArray* newCameraList = [self getCameras];
//    
//    NSMutableArray* removedCameras = [NSMutableArray array];
//    for (EOSCamera* camera in oldCameraList){
//        
//        if (![newCameraList containsObject:camera]){
//            
//            [removedCameras addObject:camera];
//            
//        }
//        
//    }
//    
//    return [NSArray arrayWithArray:removedCameras];
//    
//}



@end
