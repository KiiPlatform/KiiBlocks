//
//  KiiServerCodeEntry.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 6/25/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>


@class KiiServerCodeExecResult,KiiServerCodeEntryArgument,KiiServerCodeEntry;
typedef void(^KiiServerCodeExecBlock) (KiiServerCodeEntry* entry,KiiServerCodeEntryArgument* argument, KiiServerCodeExecResult* result, NSError* error);

/** Class that represents a server side code entry in KiiCloud.
 */
@interface KiiServerCodeEntry : NSObject

/** Synchronously execute this server code entry.
 This is blocking method.
 @param argument  passed to the entry of script in the server.
 @param error An NSError object, set to nil, to test for errors.
 @return Result of execution includes NSData returned from specified server code entry in KiiCloud.
 */
-(KiiServerCodeExecResult*) executeSynchronous:(KiiServerCodeEntryArgument*) argument withError:(NSError**) error;

/** Asynchronously execute this server code entry using block.This is non-blocking method.
    [kiiCloudEntry execute:argument 
                withBlock :^(KiiServerCodeEntry* entry,KiiServerCodeEntryArgument* argument, KiiCloudClodeExecResult* result, NSError* error){
                if(error==nil){
                    NSLog(@"Code is executed successfully");
                }
    }];
 
 @param argument  passed to the entry of script in the cloud.
 @param block The block to be called upon method completion. See example.
 */
-(void) execute:(KiiServerCodeEntryArgument*) argument withBlock:(KiiServerCodeExecBlock) block;

/** Get the entryName of this server code entry
 @return name of this server code entry.
 */
-(NSString*) entryName;




@end
