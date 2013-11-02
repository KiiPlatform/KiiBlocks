//
//  KiiPushSubscription.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 1/21/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
@class KiiPushSubscription,KiiBucket;
@protocol KiiPrivateSubscribable,KiiSubscribable;

typedef void(^KiiSubscribableBlock)(id<KiiSubscribable> subscribable,BOOL result,NSError *error);
typedef void (^KiiPushSubscriptionBlock)(KiiPushSubscription *subscription,NSError *error);
@interface KiiPushSubscription : NSObject

/** Asynchronously subscribe a subscribable object using block.
 This is a non-blocking method.    
     [KiiPushSubscription subscribe:aBucket withBlock:^(KiiPushSubscription *subscription, NSError *error) {
         if (nil == error) {
             NSLog(@"Subscribed");
         }
     }];
     
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be subscribed.
 @param completion block to handle after process completed
 */
+(void) subscribe:(id<KiiSubscribable>) subscribable withBlock:(KiiPushSubscriptionBlock) completion;
/** Asynchronously subscribe a subscribable object using delegate and callback.
 This is a non-blocking method. 
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be subscribed.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void)bucketSubscribed:(KiiPushSubscription*)subscription withError:(NSError*)error {
        // check whether the request was successful
        if (error == nil) {
            // do something
        } else {
            // there was a problem
        }
    }
 
 */
+(void)subscribe:(id<KiiSubscribable>) subscribable withDelegate:(id) delegate andCallback:(SEL) callback;


/** Synchronously subscribe a subscribable object.
 This is a blocking method.
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be subscribed.
 @param error An NSError object, set to nil, to test for errors
 */
+(KiiPushSubscription*) subscribeSynchronous:(id<KiiSubscribable>) subscribable withError:(NSError**) error;

/** Asynchronously unsubscribe a subscribable object using block
 This is a non-blocking method.
    [KiiPushSubscription unsubscribe:aBucket withBlock:^(KiiPushSubscription *subscription, NSError *error) {
        if (nil == error) {
            NSLog(@"Unsubscribed");
        }
    }];
 
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be unsubscribed.
 @param completion block to handle after process completed
 */
+(void) unsubscribe:(id<KiiSubscribable>) subscribable withBlock:(KiiPushSubscriptionBlock) completion;


/** Asynchronously unsubscribe a subscribable object using delegate and callback
 This is a non-blocking method.
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be unsubscribed.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void)bucketUnsubscribed:(KiiPushSubscription*)subscription withError:(NSError*)error {
         // check whether the request was successful
         if (error == nil) {
             // do something
         } else {
             // there was a problem
         }
     }

 */
+(void) unsubscribe:(id<KiiSubscribable>) subscribable withDelegate:(id) delegate andCallback:(SEL) callback;

/** Synchronously unsubscribe a subscribable object.
 This is a blocking method.
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be unsubscribed.
 @param error An NSError object, set to nil, to test for errors
 */
+(KiiPushSubscription*) unsubscribeSynchronous:(id<KiiSubscribable>) subscribable withError:(NSError**) error;



/** Asynchronously check whether subscribable object is already subscribed or not using block.
 This is a non-blocking method. 
 
     [KiiPushSubscription checkSubscription:bucket withBlock:^(id<KiiSubscribable> subscribable, BOOL result, NSError *error) {
         if (result) {
          NSLog(@"subscribed");
         }
     }];
 
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be checked for subscription.
 @param completion block to handle after process completed
 */
+(void) checkSubscription:(id<KiiSubscribable>) subscribable withBlock:(KiiSubscribableBlock) completion;

/** Synchronously check whether subscribable object is already subscribed or not
 This is a blocking method.
 
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be checked for subscription.
 @param error An NSError object, set to nil, to test for errors.
 @return BOOL YES if the subscribable object is already subscribed, NO if there is no subscription or there is an error during the calls. 
 */
+(BOOL) checkSubscriptionSynchronous:(id<KiiSubscribable>) subscribable withError:(NSError**) error;

/** Asynchronously check whether subscribable object is already subscribed or not  using delegate and callback.
 This is a non-blocking method. 
 
 @param subscribable A subscribable object. Currently, <KiiBucket>, <KiiFileBucket> and <KiiTopic> can be checked for subscription.
 @param delegate The object to make any callback requests to.
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void)subscribableObject:(id<KiiSubscribable>) subscribable isSubscribed:(BOOL) isSubscribed withError:(NSError*)error {
         // check whether the request was successful
         if (error == nil) {
         // do something
         } else {
         // there was a problem
         }
     }
 
 */
+(void) checkSubscription:(id<KiiSubscribable>) subscribable withDelegate:(id) delegate andCallback:(SEL) callback;

@end

@protocol KiiSubscribable <NSObject>



@end
