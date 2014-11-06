//
//  EOSManager.h
//  EOSFramework
//
//  Created by Henry Betts on 22/09/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <Foundation/Foundation.h>

@class EOSCamera;

@protocol EOSManagerDelegate;


/*!
 The EOSManager class defines a singleton object used to manage the EOS framework.
 */
@interface EOSManager : NSObject{
    
    id _delegate;
    NSArray* _cameraList;
    
}


///---------------------
/// @name Initialization
///---------------------

/*!
 @brief Returns the singleton instance of EOSManager.
 @return The singleton instance of EOSManager.
 */
+(EOSManager*)sharedManager;



///-----------------------
/// @name Managing the SDK
///-----------------------

/*!
 @brief Indicates whether the EOS SDK is loaded (read only).
 */
@property (readonly) BOOL isLoaded;

/*!
 @brief Initializes the EOS SDK.
 @discussion This method must be called before performing any other EOS related functions, such as retrieving cameras or images. If successful, the isLoaded property will be changed to YES.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)load:(NSError* __autoreleasing *)error;

/*!
 @brief Terminates the EOS SDK.
 @discussion This method will deallocate all EOS related objects, and should be called once for each time the SDK is loaded. If successful, the isLoaded property will be changed to NO.
 @param error If unsuccessful, an instance of NSError describes the problem.
 @return YES if successful, otherwise NO.
 */
-(BOOL)terminate:(NSError* __autoreleasing *)error;



///----------------------------
/// @name Managing the delegate
///----------------------------

/*!
 @brief Sets the manager's delegate to a given object or removes an existing delegate.
 @param delegate The delegate for the manager. Pass nil to remove an existing delegate.
 @see EOSManagerDelegate
 */
-(void)setDelegate:(id<EOSManagerDelegate>)delegate;

/*!
 @brief Returns the manager's delegate.
 @return The manager's delegate, or nil if it doesn’t have a delegate.
 @see EOSManagerDelegate
 */
-(id<EOSManagerDelegate>)delegate;



///----------------------------
/// @name Getting Cameras
///----------------------------

/*!
 @brief Returns a list of the connected cameras.
 @discussion EOSManager ensures that there is never more than one instance of EOSCamera reprenting each device. Therefore this method will return the same EOSCamera instance for any camera that has already been retrieved.
 @return An array containing instances of EOSCamera.
 */
-(NSArray*)getCameras;



/**
 Gets the number of cameras that are connected
 @param error If unsuccessful, an instance of NSError describes the problem
 @return If successful, the number of cameras, otherwise nil
 */
//-(NSNumber*)getCameraCount:(NSError* __autoreleasing*)error;

/**
 Gets the camera at the specified index.
 
 Use getCameraCount:error: to find the valid index range.
 @param index The index of the camera to get
 @param error If unsuccessful, an instance of NSError describes the problem
 @param If successful, an EOSCamera object representing the camera, otherwise nil
 */
//-(EOSCamera*)getCameraAtIndex:(NSUInteger)index error:(NSError* __autoreleasing *)error;




//-(NSArray*)getAddedCameras;
//-(NSArray*)getRemovedCameras;

@end




/*!
 The EOSManagerDelegate protocol defines the methods implemented by the delegate of EOSManager.
 */
@protocol EOSManagerDelegate <NSObject>

@required

/*!
 @brief Invoked when a new camera becomes available.
 @discussion Use the EOSManager method getCameras to access the new camera.
 */
-(void)cameraDidConnect;

@end
