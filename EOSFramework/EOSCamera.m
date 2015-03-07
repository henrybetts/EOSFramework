//
//  EOSCamera.m
//  EOSFramework
//
//  Created by Henry Betts on 23/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <EOSFramework/EOSCamera.h>
#import <EOSFramework/EOSVolume.h>
#import <EOSFramework/EOSFile.h>
#import <EDSDK/EDSDK.h>
#import <EOSFramework/EOSError.h>

EdsError EDSCALLBACK EOSCameraPropertyEventHandler(EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam, EdsVoid* inContext){

    EOSCamera* camera = (__bridge EOSCamera *)(inContext);
    
    if (inEvent == kEdsPropertyEvent_PropertyChanged)
        [[camera delegate] camera:camera valueDidChangeForProperty:inPropertyID];
    
    else if (inEvent == kEdsPropertyEvent_PropertyDescChanged)
        [[camera delegate] camera:camera supportedValuesDidChangeForProperty:inPropertyID];
    
    return EDS_ERR_OK;
    
}

EdsError EDSCALLBACK EOSCameraStateEventHandler(EdsStateEvent inEvent, EdsUInt32 inEventData, EdsVoid *inContext){

    EOSCamera* camera = (__bridge EOSCamera *)(inContext);
    
    if (inEvent == kEdsStateEvent_Shutdown)
        [[camera delegate] cameraDidDisconnect:camera];
    
    else if (inEvent == kEdsStateEvent_WillSoonShutDown)
        [[camera delegate] camera:camera willShutdownAfterDelay:inEventData];
    
    return EDS_ERR_OK;
    
}

EdsError EDSCALLBACK EOSCameraObjectEventHandler(EdsObjectEvent inEvent, EdsBaseRef inRef, EdsVoid *inContext){
    
    EOSCamera* camera = (__bridge EOSCamera *)(inContext);
    
    if (inEvent == kEdsObjectEvent_DirItemCreated)
        [[camera delegate] camera:camera didCreateFile:[[EOSFile alloc] initWithDirectoryItemRef:inRef]];
    
    else if (inEvent == kEdsObjectEvent_DirItemRemoved)
        [[camera delegate] camera:camera didRemoveFile:[[EOSFile alloc] initWithDirectoryItemRef:inRef]];
    
    else if (inEvent == kEdsObjectEvent_VolumeInfoChanged)
        [[camera delegate] camera:camera didModifyVolume:[[EOSVolume alloc] initWithVolumeRef:inRef]];
    
    else if (inEvent == kEdsObjectEvent_VolumeUpdateItems)
        [[camera delegate] camera:camera didFormatVolume:[[EOSVolume alloc] initWithVolumeRef:inRef]];
    
    return EDS_ERR_OK;
    
}

@implementation EOSCamera
//@synthesize baseRef = _baseRef;

-(id)initWithCameraRef:(EdsCameraRef)cameraRef{

    self = [super initWithBaseRef:cameraRef];

    if (self){

        _isOpen = false;
        _state = EOSCameraState_Default;
        //_shutterButtonState = kEdsCameraCommand_ShutterButton_OFF;
        
        EdsDeviceInfo deviceInfo;
        
        if (EdsGetDeviceInfo(_baseRef, &deviceInfo) == EOSError_OK){
            
            _description = [NSString stringWithUTF8String:deviceInfo.szDeviceDescription];
            _port = [NSString stringWithUTF8String:deviceInfo.szPortName];
            
        }
        
        //seems to fix a problem whereby string properties cannot be accessed.
        [self setDelegate:nil];
        
    }
    
    return self;
    
}

-(id)delegate{
    
    return _delegate;
    
}

-(void)setDelegate:(id)delegate{
    
    if (delegate != nil){
            
        //register for events
        
        //property value change event
        if ([delegate respondsToSelector:@selector(camera:valueDidChangeForProperty:)]){
            
            EdsSetPropertyEventHandler(_baseRef, kEdsPropertyEvent_PropertyChanged, EOSCameraPropertyEventHandler, (__bridge EdsVoid *)(self));
            
        }
        
        //property supported values change event
        if ([delegate respondsToSelector:@selector(camera:supportedValuesDidChangeForProperty:)]){
            
            EdsSetPropertyEventHandler(_baseRef, kEdsPropertyEvent_PropertyDescChanged, EOSCameraPropertyEventHandler, (__bridge EdsVoid *)(self));
            
        }
        
        //camera shutdown event
        if ([delegate respondsToSelector:@selector(cameraDidDisconnect:)]){

            EdsSetCameraStateEventHandler(_baseRef, kEdsStateEvent_Shutdown, EOSCameraStateEventHandler, (__bridge EdsVoid *)(self));
            
        }
        
        //camera will shutdown event
        if ([delegate respondsToSelector:@selector(camera:willShutdownAfterDelay:)]){
            
            EdsSetCameraStateEventHandler(_baseRef, kEdsStateEvent_WillSoonShutDown, EOSCameraStateEventHandler, (__bridge EdsVoid *)(self));
            
        }
        
        //file creation event
        if ([delegate respondsToSelector:@selector(camera:didCreateFile:)]){
            
            EdsSetObjectEventHandler(_baseRef, kEdsObjectEvent_DirItemCreated, EOSCameraObjectEventHandler, (__bridge EdsVoid *)(self));
            
        }
        
        //file removed event
        if ([delegate respondsToSelector:@selector(camera:didRemoveFile:)]){
            
            EdsSetObjectEventHandler(_baseRef, kEdsObjectEvent_DirItemRemoved, EOSCameraObjectEventHandler, (__bridge EdsVoid *)(self));
            
        }
        
        //volume info changed event
        if ([delegate respondsToSelector:@selector(camera:didModifyVolume:)]){
            
            EdsSetObjectEventHandler(_baseRef, kEdsObjectEvent_VolumeInfoChanged, EOSCameraObjectEventHandler, (__bridge EdsVoid *)(self));
            
        }
        
        //volume formatted event
        if ([delegate respondsToSelector:@selector(camera:didFormatVolume:)]){
            
            EdsSetObjectEventHandler(_baseRef, kEdsObjectEvent_VolumeUpdateItems, EOSCameraObjectEventHandler, (__bridge EdsVoid *)(self));
            
        }

        
    }else{
            
        //stop receiving events
        EdsSetPropertyEventHandler(_baseRef, kEdsPropertyEvent_PropertyChanged, NULL, NULL);
        EdsSetPropertyEventHandler(_baseRef, kEdsPropertyEvent_PropertyDescChanged, NULL, NULL);
        
        EdsSetCameraStateEventHandler(_baseRef, kEdsStateEvent_Shutdown, NULL, NULL);
        EdsSetCameraStateEventHandler(_baseRef, kEdsStateEvent_WillSoonShutDown, NULL, NULL);
        
        EdsSetObjectEventHandler(_baseRef, kEdsObjectEvent_DirItemCreated, NULL, NULL);
        EdsSetObjectEventHandler(_baseRef, kEdsObjectEvent_DirItemRemoved, NULL, NULL);
        EdsSetObjectEventHandler(_baseRef, kEdsObjectEvent_VolumeInfoChanged, NULL, NULL);
        
    }
    
    _delegate = delegate;
    
}




-(BOOL)openSession:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsOpenSession(_baseRef);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    _isOpen = YES;
    return YES;
    
}

-(BOOL)closeSession:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsCloseSession(_baseRef);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    _isOpen = NO;
    return YES;
    
}


-(NSArray*)supportedValuesForProperty:(EOSProperty)property error:(NSError *__autoreleasing *)error{
    
    EdsPropertyDesc propertyDesc;
    NSArray *array;
    
    EOSError errorCode = EdsGetPropertyDesc(_baseRef, property, &propertyDesc);
     
    if (errorCode == EOSError_OK){
        
        NSUInteger i, count = propertyDesc.numElements;
        NSMutableArray* mArray = [NSMutableArray arrayWithCapacity:count];
        
        for (i=0; i<count; i++){
            
            [mArray addObject:[NSNumber numberWithInteger:propertyDesc.propDesc[i]]];
            
        }
        
        array = [NSArray arrayWithArray:mArray];
        
    }else{
        
        if (error)
            *error = EOSCreateError(errorCode);
        
    }
    
    return array;
    
}

-(BOOL)sendCommand:(EOSCameraCommand)command withParameter:(NSInteger)parameter error:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsSendCommand(_baseRef, command, (EdsUInt32)parameter);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    return YES;
    
}

-(BOOL)sendCommand:(EOSCameraCommand)command error:(NSError *__autoreleasing *)error{
    
    return [self sendCommand:command withParameter:0 error:error];
    
}

-(BOOL)setState:(EOSCameraState)state error:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EOSError_OK;
    
    if (state != _state){
    
        EdsCameraStatusCommand command;
    
        switch (state){
            
            case EOSCameraState_Default:
                command = (_state == EOSCameraState_UILocked) ? kEdsCameraStatusCommand_UIUnLock : kEdsCameraStatusCommand_ExitDirectTransfer;
                break;
            
            case EOSCameraState_UILocked:
                command = kEdsCameraStatusCommand_UILock;
                break;
                
            case EOSCameraState_DirectTransfer:
                command = kEdsCameraStatusCommand_EnterDirectTransfer;
            
        }
    
        errorCode = EdsSendStatusCommand(_baseRef, command, 0);
        
    }else{
        
        errorCode = EOSError_InvalidFunctionCall;
        
    }
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    return YES;
    
}


-(NSNumber*)volumeCount:(NSError *__autoreleasing *)error{
    
    EdsUInt32 count;

    EOSError errorCode = EdsGetChildCount(_baseRef, &count);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return nil;
        
    }
    
    return [NSNumber numberWithUnsignedInteger:count];
    
}

-(EOSVolume*)volumeAtIndex:(NSUInteger)index error:(NSError *__autoreleasing *)error{
    
    EdsVolumeRef volumeRef;
    
    EOSError errorCode = EdsGetChildAtIndex(_baseRef, (int)index, &volumeRef);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return nil;
        
    }
    
    return [[EOSVolume alloc] initWithVolumeRef:volumeRef];
    
}

-(NSArray*)volumes{
    
    NSUInteger i, count = 0;
    NSNumber* countNumber = [self volumeCount:nil];
    if (countNumber != nil)
        count = [countNumber integerValue];
    
    NSMutableArray* array = [NSMutableArray arrayWithCapacity:count];
    EOSVolume* volume;
    
    for (i=0; i<count; i++){
        
        volume = [self volumeAtIndex:i error:nil];
        if (volume != nil)
            [array addObject:volume];
        
    }
    
    return [NSArray arrayWithArray:array];
    
}

@end
