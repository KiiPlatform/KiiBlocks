//
//  KiiBucket.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 5/12/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KiiPushSubscription.h"
#import "KiiBaseBucket.h"

@class KiiObject, KiiQuery, KiiUser, KiiBucket, KiiGroup, KiiACL,KiiRTransferManager;



typedef void (^KiiBucketBlock)(KiiBucket *bucket, NSError *error);
typedef void (^KiiQueryResultBlock)(KiiQuery *query, KiiBucket *bucket, NSArray *results, KiiQuery *nextQuery, NSError *error);

/** A reference to a bucket within an application, group or user's scope which contains KiiObjects */
@interface KiiBucket : KiiBaseBucket <KiiSubscribable>

/** Get the ACL handle for this bucket. Any <KiiACLEntry> objects added or revoked from this ACL object will be appended to/removed from the server on ACL save. */
@property (readonly) KiiACL *bucketACL;

/** Create a <KiiObject> within the current bucket, with type
 
 The object will not be created on the server until the <KiiObject> is explicitly saved. This method simply returns an empty working <KiiObject> with a specified type. The type allows for better indexing and improved query results. It is recommended to use this method - but for lazy creation, the <createObject> method is also available.
 @param objectType A string representing the desired object type
 @return An empty <KiiObject> with the specified type
 */
- (KiiObject*) createObjectWithType:(NSString*)objectType;


/** Create a <KiiObject> within the current bucket
 
 The object will not be created on the server until the <KiiObject> is explicitly saved. This method simply returns an empty working <KiiObject>.
 @return An empty <KiiObject> with the specified type
 */
- (KiiObject*) createObject;


/** Execute a query on the current bucket
 
 The query will be executed against the server, returning a result set. This is a blocking method

    KiiBucket *bucket = ...;
    KiiQuery *query = ...;

    // To recursively get all results in a query (from multiple pages)
    KiiQueryResultBlock __block __weak weakQueryBlock;
    KiiQueryResultBlock queryBlock = ^(KiiQuery *retQuery, KiiBucket *retBucket, NSArray *retResults, KiiQuery *retNextQuery, NSError *retError) {
        // We got some valid results
        if (retError == nil) {
            // Do something with the results
            [self handleResults:retResults];
        }

        // We have another query available (another page of results)
        if (retNextQuery != nil) {
            // Execute the next query
            [bucket executeQuery:retNextQuery withBlock:[weakQueryBlock copy]];
        }
    };
    weakQueryBlock = queryBlock;

    [bucket executeQuery:query withBlock:queryBlock];
 
 @param query The query to execute
 @param block The block to be called upon method completion. See example
*/
- (void) executeQuery:(KiiQuery*)query withBlock:(KiiQueryResultBlock)block;


/** Execute a query on the current bucket
 
 The query will be executed against the server, returning a result set. This is a blocking method
 @param query The query to execute
 @param error An NSError object, set to nil, to test for errors
 @param nextQuery A <KiiQuery> object representing the next set of results, if they couldn't all be returned in the current query
 @return An NSArray of objects returned by the query
    
    KiiBucket *bucket = ...;
    KiiQuery *query = ...;
    NSError *error = nil;
    KiiQuery *nextQuery = nil;
    NSMutableArray *allResults = [NSMutableArray array];

    do {
        if (nextQuery != nil) {
            // Set next query
            query = nextQuery;
        }
        // Do query
        NSArray *results = [bucket executeQuerySynchronous:query withError:&error andNext:&nextQuery];
        // Add results to the all results array
        [allResults addObjectsFromArray:results];
    } while (error == nil && nextQuery != nil);
 
    // Do something with the entire result set contained in allResults
    
 */
- (NSArray*) executeQuerySynchronous:(KiiQuery*)query withError:(NSError**)error andNext:(KiiQuery**)nextQuery;


/** Execute a query on the current bucket
 
 The query will be executed against the server, returning a result set. This is a non-blocking method
 @param query The query to execute
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void)queryFinished:(KiiQuery *)query onBucket:(KiiBucket *)bucket withResults:(NSArray *)results andNext:(KiiQuery *)nextQuery andError:(NSError *)error {
        // The request was successful
        if (error == nil) {
            // Do something with the results
            for (KiiObject *o in results) {
                // use this object
            }

            // Also check to see if there are more results
            if (nextQuery != nil) {
                // There are more results, query for them
                [bucket executeQuery:nextQuery withDelegate:self andCallback:@selector(queryFinished:onBucket:withResults:andNext:andError:)];
            }
        } else {
            // there was a problem
        }
    }
 
 */
- (void) executeQuery:(KiiQuery*)query withDelegate:(id)delegate andCallback:(SEL)callback;

/** Asynchronously deletes a bucket from the server.
 
 Delete a bucket from the server. This method is non-blocking.
 
     [b deleteWithBlock:^(KiiBucket *bucket, NSError *error) {
         if(error == nil) {
             NSLog(@"Bucket deleted!");
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) deleteWithBlock:(KiiBucketBlock)block;

/** Synchronously deletes a bucket from the server.
 
 Delete a bucket from the server. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) deleteSynchronous:(NSError**)error;


/** Asynchronously deletes a bucket from the server. 
 
 Delete a bucket from the server. This method is non-blocking.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) bucketDeleted:(KiiBucket*)bucket withError:(NSError*)error {
     
        // the request was successful
        if(error == nil) {
            // do something
        }
     
        else {
            // there was a problem
        }
     }
 
 */
- (void) delete:(id)delegate withCallback:(SEL)callback;

/** Get transfer manager object based on this bucket
@return A transfer manager object based on this file bucket. 
 */
-(KiiRTransferManager*) transferManager;
@end
