//
//  KiiTopic.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 1/24/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KiiPushSubscription.h"

@class  KiiUser, KiiBucket, KiiGroup, KiiACL,KiiTopic,KiiPushMessage;
typedef void (^KiiTopicBlock)(KiiTopic *topic, NSError *error);
/** Topic on Kii push notification service
 */
@interface KiiTopic : NSObject<KiiSubscribable>


/** Get the ACL handle for this topic. Any <KiiACLEntry> objects added or revoked from this ACL object will be appended to/removed from the server on ACL save. */
@property (readonly) KiiACL *topicACL;

/** Asynchronously saves the topic to the server
 
 If the topic does not yet exist, it will be created. If the topic already exists, an error (code 704) will be returned. This is a non-blocking method.
 
     [obj saveWithBlock:^(KiiTopic *topic, NSError *error) {
         if (error == nil) {
            NSLog(@"topic saved: %@", topic);
         }
     }];
 
 @param block The block to be called upon method completion. See example
 */
- (void) saveWithBlock:(KiiTopicBlock)block;


/** Asynchronously saves the latest topic values to the server
 
 If the topic does not yet exist, it will be created. If the topic already exists, an error (code 704) will be returned. This is a non-blocking method.
 @param delegate The topic to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) topicSaved:(KiiTopic*)topic withError:(NSError*)error {
        // check whether the request was successful
        if (error == nil) {
            // do something with the topic
        } else {
            // there was a problem
        }
    }
 
 */
- (void) save:(id)delegate withCallback:(SEL)callback;


/** Synchronously saves the latest topic values to the server
 
 If the topic does not yet exist, it will be created. If the topic already exists, an error (code 704) will be returned. This is a blocking method.
 @param error An NSError topic, set to nil, to test for errors
 */
- (void) saveSynchronous:(NSError**)error;


/** Asynchronously deletes the topic to the server
 
If the topic does not exist, an error (code 705) will be returned.  This is a non-blocking method.
 
    [obj deleteWithBlock:^(KiiTopic *topic, NSError *error) {
        if(error == nil) {
            NSLog(@"topic saved: %@", topic);
        }
    }];
 
 @param block The block to be called upon method completion. See example
 */
-(void) deleteWithBlock:(KiiTopicBlock) block;

/** Asynchronously deletes the latest topic values to the server
 
 If the topic does not exist, an error (code 705) will be returned. This is a non-blocking method.
 @param delegate The topic to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) topicDeleted:(KiiTopic*)topic withError:(NSError*)error {
         // check whether the request was successful
         if(error == nil) {
             // do something with the topic
         } else {
             // there was a problem
         }
     }
 
 */
-(void) delete:(id) delegate withCallback:(SEL) callback;


/** Synchronously deletes the latest topic values to the server
 
 If the topic does not exist, the there will be an error. This is a blocking method.
 @param error An NSError topic, set to nil, to test for errors
 */
-(void) deleteSynchronous:(NSError**) error;



/** Asynchronously send Kii explicit push notification to topic.
 This is a non-blocking method.
 If the topic does not exist, an error (code 705) will be returned.  
 If message has gcmFields defined, the data and specific data will be validated for GCM reserved keys, an error (code 712) will be returned if it contains any GCM reserved keys.

    [obj sendMessage:message withBlock:^(KiiTopic *topic, NSError *error) {
        if(error == nil) {
            NSLog(@"message sent: %@", topic);
        }
    }];
 
 @param block The block to be called upon method completion. See example
 */
-(void) sendMessage:(KiiPushMessage*) message withBlock:(KiiTopicBlock) compeletion;

/** Asynchronously send Kii explicit push notification to topic
 This is a non-blocking method.
 If the topic does not exist, an error (code 705) will be returned. 
 If message has gcmFields defined, the data and specific data will be validated for GCM reserved keys, an error (code 712) will be returned if it contains any GCM reserved keys.
 @param delegate The topic to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) messageSent:(KiiTopic*)topic withError:(NSError*)error {
        // check whether the request was successful
        if(error == nil) {
            // do something with the topic
        } else {
            // there was a problem
        }
    }
 
 */
-(void) sendMessage:(KiiPushMessage*) message withDelegate:(id) delegate andCallback:(SEL) callback;


/** Synchronously send Kii explicit push notification to topic.
 This is a blocking method.
 If the topic does not exist, an error (code 705) will be returned. 
 If message has gcmFields defined, the data and specific data will be validated for GCM reserved keys, an error (code 712) will be returned if it contains any GCM reserved keys.
  @param error An NSError topic, set to nil, to test for errors
 */
-(void) sendMessageSynchronous:(KiiPushMessage*) message withError:(NSError**) error;


@end
