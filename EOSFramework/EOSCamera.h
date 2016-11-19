//
//  EOSCamera.h
//  EOSFramework
//
//  Created by Henry Betts on 23/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <EOSFramework/EOSPropertyObject.h>

NS_ASSUME_NONNULL_BEGIN

@class EOSVolume;
@class EOSFile;


/*!
 Camera commands
 */
typedef NS_ENUM(NSUInteger, EOSCameraCommand){
    
    /** Reqests the camera to shoot */
    EOSCommand_TakePicture          = kEdsCameraCommand_TakePicture,
    
    /** Requests to extend the time for the auto shut-off timer. */
    EOSCommand_ExtendShutDownTimer  = kEdsCameraCommand_ExtendShutDownTimer,
    
    /** Starts bulb shooting */
    EOSCommand_BulbStart            = kEdsCameraCommand_BulbStart,
    
    /** Ends bulb shooting */
    EOSCommand_BulbEnd              = kEdsCameraCommand_BulbEnd,
    
    /** Controls shutter button operations.
      
     This command should be used with one of the EOSShutterButtonState parameters. The command is supported by the EOS 50D or EOS 5D Mark II or later cameras.
     */
    EOSCommand_PressShutterButton   = kEdsCameraCommand_PressShutterButton,
    
    /**
     Only supported in live view, which is not supported in the 64bit SDK
     */
    //EOSCommand_DoEvfAf              = kEdsCameraCommand_DoEvfAf,
    //EOSCommand_DriveLens            = kEdsCameraCommand_DriveLensEvf,
    //EOSCommand_DoClickWBEvf         = kEdsCameraCommand_DriveLensEvf,
    
    /**
     Status Commands
     */
    
    /** Locks the camera's UI */
    EOSCommand_LockUI,
    
    /** Unlocks the camera's UI */
    EOSCommand_UnlockUI,
    
    /** Put the camera in direct transfer mode */
    EOSCommand_EnterDirectTransfer,
    
    /** Ends direct transfer mode */
    EOSCommand_ExitDirectTransfer
    
};


/*!
 Camera shutter button states
 */
typedef NS_ENUM(NSInteger, EOSShutterButtonState){
    
    EOSShutterButtonState_Off               = kEdsCameraCommand_ShutterButton_OFF,
    EOSShutterButtonState_Halfway           = kEdsCameraCommand_ShutterButton_Halfway,
    EOSShutterButtonState_Completely        = kEdsCameraCommand_ShutterButton_Completely,
    EOSShutterButtonState_Halfway_NonAF     = kEdsCameraCommand_ShutterButton_Halfway_NonAF,
    EOSShutterButtonState_Completely_NonAF  = kEdsCameraCommand_ShutterButton_Completely_NonAF
    
};

@protocol EOSCameraDelegate;

/*!
 EOSCamera is a class used to represent a camera. It is a subclass of EOSPropertyObject. Instances of this class will typically be created by the [EOSManager getCameras] method.
 */
@interface EOSCamera : EOSPropertyObject{
    id _delegate;
}

///-----------------
/// @name Properties
///-----------------

/*!
 @brief The camera's port name.
 @discussion This property is provided by the EDSDK and does not seem to represent a physical port. It appears to be the position of the camera in the camera list. Therefore, this value can change if cameras are disconnected, and should not be used as an indentifier.
 */
@property (readonly) NSString* port;

/*!
 @brief A description of the camera.
 @discussion This is typically the camera's model name. This property is the equivalent of calling description.
 */
@property (readonly) NSString* cameraDescription;


///---------------------
/// @name Initialization
///---------------------

/*!
 @brief Initializes a newly allocated EOSCamera instance with a reference to an EDSDK camera.
 @param cameraRef An EDSDK camera reference.
 @return The intialized EOSCamera object.
 */
-(id)initWithCameraRef:(EdsCameraRef)cameraRef;



///------------------------
/// @name Managing Sessions
///------------------------

/*!
 @brief Indicates whether the camera has an open session.
 */
@property (readonly) BOOL isOpen;

/*!
 @brief Opens a session with the camera.
 @discussion This must be performed before accessing properties or sending commands.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)openSession:(NSError* __autoreleasing*)error;


/*!
 @brief Closes the camera session.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)closeSession:(NSError* __autoreleasing*)error;



///-----------------------
/// @name Managing Volumes
///-----------------------

/*!
 @brief Gets the number of volumes that are mounted on the camera.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return If successful, the number of volumes, otherwise nil.
 */
-(nullable NSNumber*)volumeCount:(NSError* __autoreleasing*)error;

/*!
 @brief Gets the volume at the specified index.
 @discussion Use volumeCount:error: to find the valid index range.
 @param index The index of the volume to get.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return If successful, an EOSVolume object representing the volume, otherwise nil.
 */
-(nullable EOSVolume*)volumeAtIndex:(NSUInteger)index error:(NSError* __autoreleasing *)error;

/*!
 @brief Gets all of the volumes that are mounted on the camera.
 @discussion If there is an error retrieving a volume, the function will continue without adding it to the array. If you need to check for errors when reteiving each volume, use volumeAtIndex:error: instead.
 @return An array containing instances of EOSVolume.
 */
-(NSArray<EOSVolume*>*)volumes;



///-------------------------------
/// @name Getting Supported Values
///-------------------------------

/*!
 @brief Gets a list of values that the camera supports in it's current mode, for a given property.
 @discussion Use this to find the supported values for a numeric type property, such as aperture, shutter speed, ISO etc. The list of supported values may change when the camera's mode is changed.
 @param property The property to get supported values for.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return If successful an array containing the supported values as NSNumbers, otherwise nil.
 */
-(nullable NSArray<NSNumber*>*)supportedValuesForProperty:(EOSProperty)property error:(NSError* __autoreleasing*)error;



///-----------------------
/// @name Sending Commands
///-----------------------

/*!
 @brief Sends a command with a parameter to the camera.
 @param command The command.
 @param parameter A parameter to send with the command.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)sendCommand:(EOSCameraCommand)command withParameter:(NSInteger)parameter error:(NSError* __autoreleasing*)error;

/*!
 @brief Sends a command to the camera.
 @param command The command.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)sendCommand:(EOSCameraCommand)command error:(NSError* __autoreleasing*)error;



///----------------------------
/// @name Managing the Delegate
///----------------------------

/*!
 @brief Returns the camera's delegate.
 @return The camera's delegate, or nil if it doesn’t have a delegate.
 @see EOSCameraDelegate
 */

-(nullable id<EOSCameraDelegate>)delegate;

/*!
 @brief Sets the camera's delegate to a given object or removes an existing delegate.
 @param delegate The delegate for the camera. Pass nil to remove an existing delegate.
 @see EOSCameraDelegate
 */
-(void)setDelegate:(nullable id<EOSCameraDelegate>)delegate;


/**
 Indicates whether the reciever represents the same camera as an EdsCameraRef object
 @param cameraRef The EdsCameraRef object to be compared with the reciever
 @return YES if the receiver and cameraRef represent the same camera, otherwise NO.
 */
//-(BOOL)isEqualToCameraRef:(EdsCameraRef)cameraRef;

/**
 Indicates whether the reciever represents the same camera as another EOSCamera object
 @param camera The EOSCamera object to be compared with the reciever
 @return YES if the receiver and camera represent the same camera, otherwise NO.
 */
//-(BOOL)isEqualToCamera:(EOSCamera*)camera;


//-(BOOL)isEqual:(id)object;

@end



/*!
 The EOSCameraDelegate protocol defines the optional methods implemented by the delegate of a camera.
 */
@protocol EOSCameraDelegate <NSObject>

@optional

/*!
 @brief Invoked when the value of a camera's property changes.
 @param camera The camera that sent the message.
 @param property The property that has changed.
 */
-(void)camera:(EOSCamera*)camera valueDidChangeForProperty:(EOSProperty)property;

/*!
 @brief Invoked when the supported values of a camera's property changes.
 @param camera The camera that sent the message.
 @param property The property that has changed.
 */
-(void)camera:(EOSCamera*)camera supportedValuesDidChangeForProperty:(EOSProperty)property;

/*!
 @brief Invoked when a file is created on a camera's volume.
 @param camera The camera that sent the message.
 @param file The file that was created.
 */
-(void)camera:(EOSCamera*)camera didCreateFile:(EOSFile*)file;

/*!
 @brief Invoked when a file is removed from a camera's volume.
 @param camera The camera that sent the message.
 @param file The file that was removed.
 */
-(void)camera:(EOSCamera*)camera didRemoveFile:(EOSFile*)file;

/*!
 @brief Invoked when the info of a camera's volume changes.
 @param camera The camera that sent the message.
 @param volume The volume that was modified.
 */
-(void)camera:(EOSCamera*)camera didModifyVolume:(EOSVolume*)volume;

/*!
 @brief Invoked when a camera's volume is formatted.
 @param camera The camera that sent the message.
 @param volume The volume that was formatted.
 */
-(void)camera:(EOSCamera*)camera didFormatVolume:(EOSVolume*)volume;

/*!
 Untested
 */
-(void)camera:(EOSCamera*)camera didRequestTransferOfFile:(EOSFile*)file;

/*!
 @brief Invoked when a camera is soon going to shutdown.
 @discussion The time at which the camera issues the notification is model dependent, which is why the delay parameter is provided. To cancel the shutdown, send the EOSCameraCommand_ExtendShutdownTimer command to the camera.
 @param camera The camera that is going to shutdown.
 @param delay The time in seconds until the camera shutsdown.
 */
-(void)camera:(EOSCamera*)camera willShutdownAfterDelay:(NSUInteger)delay;

/*!
 @brief Invoked when a camera is shutdown or disconnected.
 @param camera The camera that disconnected.
 */
-(void)cameraDidDisconnect:(EOSCamera*)camera;

@end

NS_ASSUME_NONNULL_END