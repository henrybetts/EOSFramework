//
//  EOSObject.m
//  EOSFramework
//
//  Created by Henry Betts on 11/10/2014.
//  Copyright (c) 2014 Henry Betts. All rights reserved.
//

#import <EOSFramework/EOSObject.h>
#import <EDSDK/EDSDK.h>

@implementation EOSObject

-(id)initWithBaseRef:(EdsBaseRef)baseRef{
    
    self = [super init];
    if (self){
        
        _baseRef = baseRef;
        
    }
    
    return self;
    
}

-(void)dealloc{

    //release the EdsBaseRef object
    EdsRelease(_baseRef);
    
}

-(BOOL)isEqualToBaseRef:(EdsBaseRef)baseRef{
    
    return baseRef == _baseRef;
    
}

-(BOOL)isEqualToObject:(EOSObject*)object{
    
    return [self isEqualToBaseRef:[object baseRef]];
    
}

-(BOOL)isEqual:(id)object{
    
    if ([object isKindOfClass:[self class]]){
        
        return [self isEqualToObject:object];
        
    }

    return NO;
    
}


@end
