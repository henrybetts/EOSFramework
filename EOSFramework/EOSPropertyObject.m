//
//  EOSObject.m
//  EOSFramework
//
//  Created by Henry Betts on 23/09/2014.
//  Copyright (c) 2014 Henry Betts. All rights reserved.
//

#import <EOSFramework/EOSPropertyObject.h>
#import <EDSDK/EDSDK.h>
#import <EOSFramework/EOSError.h>

@implementation EOSPropertyObject

//@synthesize baseRef = _baseRef;

//BOOL getValueSize:dataType:forProperty:withParameter:error:
-(BOOL)getValueSize:(NSUInteger *)size dataType:(EdsDataType *)dataType forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError *__autoreleasing *)error{
    
    EdsUInt32 intSize = 0;
    
    EOSError errorCode = EdsGetPropertySize(_baseRef, property, (EdsUInt32)parameter, dataType, &intSize);
    
    *size = intSize;
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        
        return NO;
        
    }
    
    return YES;
    
}

//BOOL getValue:ofSize:forProperty:withParameter:error:
-(BOOL)getValue:(void *)value ofSize:(NSUInteger)size forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsGetPropertyData(_baseRef, property, (EdsInt32)parameter, (EdsUInt32)size, value);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }
    
    return YES;
    
}



//NSNumber* getNumberValueForProperty:withParameter:error:
-(NSNumber*)numberValueForProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError *__autoreleasing *)error{
    
    NSNumber* number;
    EdsUInt32 value;
    NSUInteger size;
    EdsDataType dataType;
    
    if ([self getValueSize:&size dataType:&dataType forProperty:property withParameter:parameter error:error]){
        
        if ([self getValue:&value ofSize:size forProperty:property withParameter:parameter error:error]){
    
            number = [NSNumber numberWithUnsignedInt:value];
            
        }
        
    }
    
    return number;
    
}

//NSNumber* getNumberValueForProperty:error:
-(NSNumber*)numberValueForProperty:(EOSProperty)property error:(NSError *__autoreleasing *)error{
    
    return [self numberValueForProperty:property withParameter:0 error:error];
    
}

//NSString* getStringValueForProperty:withParameter:error:
-(NSString*)stringValueForProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError *__autoreleasing *)error{
    
    NSString* string;
    NSUInteger size;
    EdsDataType dataType;
    
    //EdsSetPropertyEventHandler(_baseRef, kEdsPropertyEvent_PropertyChanged, propertyEventHandler2, NULL);
    
    if([self getValueSize:&size dataType:&dataType forProperty:property withParameter:parameter error:error]){
        
        EdsChar* c = malloc(size);
        
        if ([self getValue:c ofSize:size forProperty:property withParameter:parameter error:error]){
            
            string = [NSString stringWithUTF8String:c];
            
        }
    
    }
    
    return string;
    
}

//NSString* getStringValueForProperty:error:
-(NSString*)stringValueForProperty:(EOSProperty)property error:(NSError *__autoreleasing *)error{
    
    return [self stringValueForProperty:property withParameter:0 error:error];
    
}





//BOOL setValue:ofSize:forProperty:withParameter:error:
-(BOOL)setValue:(const void *)value ofSize:(NSUInteger)size forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError *__autoreleasing *)error{
    
    EOSError errorCode = EdsSetPropertyData(_baseRef, property, (EdsInt32)parameter, (EdsUInt32)size, value);
    
    if (errorCode != EOSError_OK){
        
        if (error)
            *error = EOSCreateError(errorCode);
        return NO;
        
    }

    return YES;
    
}

//BOOL setNumberValue:forProperty:withParameter:error:
-(BOOL)setNumberValue:(NSNumber *)value forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError *__autoreleasing *)error{
    
    UInt32 intValue = [value unsignedIntValue];
    
    return [self setValue:&intValue ofSize:sizeof(intValue) forProperty:property withParameter:parameter error:error];
    
}

//BOOL setNumberValue:forProperty:error:
-(BOOL)setNumberValue:(NSNumber *)value forProperty:(EOSProperty)property error:(NSError *__autoreleasing *)error{

    return [self setNumberValue:value forProperty:property withParameter:0 error:error];
    
}

//BOOL setStringValue:forProperty:withParameter:error:
-(BOOL)setStringValue:(NSString *)value forProperty:(EOSProperty)property withParameter:(NSUInteger)parameter error:(NSError *__autoreleasing *)error{
    
    const EdsChar* c = [value UTF8String];
    NSUInteger length = strlen(c) + 1; //include null terminator
    
    return [self setValue:c ofSize:length forProperty:property withParameter:parameter error:error];
    
}

//BOOL setStringValue:forProperty:error:
-(BOOL)setStringValue:(NSString *)value forProperty:(EOSProperty)property error:(NSError *__autoreleasing *)error{
    
    return [self setStringValue:value forProperty:property withParameter:0 error:error];
    
}

@end
