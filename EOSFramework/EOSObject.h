//
//  EOSObject.h
//  EOSFramework
//
//  Created by Henry Betts on 11/10/2014.
//  Copyright (c) 2014 Henry Betts.
//

#import <Foundation/Foundation.h>

#import <EDSDK/EDSDKTypes.h>

/*!
 EOSObject is the underlying class of all EOS objects such as EOSCamera, EOSImage, EOSFile and EOSVolume. It acts as a wrapper around an EDSDK object reference. See the Canon EDSDK documentation for more information about EDSDK objects.
 */

@interface EOSObject : NSObject{
    EdsBaseRef _baseRef;
}


/*!
 @brief The EDSDK object reference.
 */
@property EdsBaseRef baseRef;

/*!
 @brief Initializes a newly allocated EOSObject instance with an EDSDK object reference.
 @param baseRef The EDSDK object reference.
 @return The intialized EOSObject.
 */
-(id)initWithBaseRef:(EdsBaseRef)baseRef;

/*!
 @brief Indicates whether the reciever represents the same object as an EDSDK object reference.
 @param baseRef The EDSDK object reference.
 @return YES if the receiver represents the same object as the baseRef, otherwise NO.
 */
-(BOOL)isEqualToBaseRef:(EdsBaseRef)baseRef;

/*!
 @brief Indicates whether the reciever represents the same object as another EOSObject (or one of it's subclasses).
 @param object The object to be compared to the reciever.
 @return YES if the receiver and object represent the same object, otherwise NO.
 */
-(BOOL)isEqualToObject:(EOSObject*)object;


@end
