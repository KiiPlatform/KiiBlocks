//
//  KiiRTransferManager.h
//  KiiSDK-Private
//
//  Created by Syah Riza on 3/26/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
@class KiiRTransferManager;
typedef void(^KiiRTransferManagerBlock)(KiiRTransferManager *transferManager,NSArray *uploadEntries, NSError *error);
@protocol KiiRTransfer;
@interface KiiRTransferManager : NSObject

/** Synchronously get upload entries. This is blocking method.
 This API returns uploader entries that status is ONGOING and SUSPENDED. (NOENTRY is not included)
 
 @param error An NSError object, set to nil, to test for errors
 @return NSArray Upload entries array that status is ONGOING and SUSPENDED.
 */
-(NSArray*) getUploadEntries:(NSError**) error;


/**Synchronously get download entries.This is blocking method.
 This API returns download entries that status is ONGOING and SUSPENDED. (NOENTRY is not included)
 
 @param error An NSError object, set to nil, to test for errors
 @return NSArray download entries array that status is ONGOING and SUSPENDED.
 */
-(NSArray*) getDownloadEntries:(NSError**) error;

@end
