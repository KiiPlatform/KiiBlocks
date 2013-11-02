//
//  KiiGroup.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 5/12/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiUser, KiiBucket, KiiGroup,KiiTopic;

typedef void (^KiiGroupMemberBlock)(KiiGroup *group, NSArray *members, NSError *error);
typedef void (^KiiGroupOwnerBlock)(KiiGroup *group, KiiUser *owner, NSError *error);
typedef void (^KiiGroupBlock)(KiiGroup *group, NSError *error);


/** A reference to a group of users within the application */
@interface KiiGroup : NSObject 

/** The name of the group */
@property (readonly) NSString *name;

/** Get a specifically formatted string referencing the group. The group must exist in the cloud (have a valid UUID). */
@property (strong, readonly) NSString *objectURI;


/** Creates a reference to a group with the given name
 
 If the group already exists, it should be be 'refreshed' to fill the data from the server
 @param groupName An application-specific group name
 @return a working <KiiGroup>
 */
+ (KiiGroup*) groupWithName:(NSString*)groupName;


/** Creates a reference to a group with the given name with default members
 
 If the group already exists, it should be be 'refreshed' to fill the data from the server
 @param groupName An application-specific group name
 @param members An array of members to automatically add to the group upon creation
 @return a working <KiiGroup>
 */
+ (KiiGroup*) groupWithName:(NSString*)groupName andMembers:(NSArray*)members;


/** Creates a reference to a group with the given URI
 
 To utilize existing group data, the group should be be 'refreshed' to fill the data from the server
 @param groupURI An application-specific group URI
 @return a working <KiiGroup>
 */
+ (KiiGroup*) groupWithURI:(NSString*)groupURI;


/** Creates a reference to a bucket that is within the group's scope
 
 If the bucket exists, it should be 'refreshed' to pull the latest information from the server. Otherwise, the bucket must be written to or explicitly created on the server before it will persist.
 @param bucketName The name of the bucket you'd like to use
 @return An instance of a working <KiiBucket>
 */
- (KiiBucket*) bucketWithName:(NSString*)bucketName;

/** Get or create a Push notification topic at the group level
 
 @param topicName The name of the topic you'd like to use. It has to match the pattern ^[A-Za-z0-9_-]{1,64}$, that is letters, numbers, '-' and '_' and non-multibyte characters with a length between 1 and 64 characters.
 @return An instance of a working <KiiTopic>
 */
- (KiiTopic*) topicWithName:(NSString*)topicName;


/** Adds a user to the given group
 
 This method will NOT access the server immediately. You must call save to add the user on the server. This allows multiple users to be added before calling save.
 @param user The user that should be added to the group
 
 */
- (void) addUser:(KiiUser*)user;


/** Removes a user to the given group
 
 This method will NOT access the server immediately. You must call save to remove the user from the server. This allows multiple users to be removed before calling save.
 @param user The user that should be removed from the group
 
 */
- (void) removeUser:(KiiUser*)user;


/** Asynchronously gets a list of all current members in a group
 
 This method is non-blocking.
 
     [g getMemberListWithBlock:^(KiiGroup *group, NSArray *members, NSError *error) {
         if(error == nil) {
             NSLog(@"Got members: %@", members);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) getMemberListWithBlock:(KiiGroupMemberBlock)block;

/** Gets a list of all current members of a group
 
 Returns an array of <KiiUser> objects if successful. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 @return An NSArray of <KiiUser> objects
 */
- (NSArray*) getMemberListSynchronous:(NSError**)error;


/** Asynchronously gets a list of all current members in a group
 
 This method is non-blocking.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) gotMemberList:(NSArray*)members inGroup:(KiiGroup*)group withError:(NSError*)error {
     
         if(error == nil) {
             // successfully got the list, do something with it
             for(KiiUser *user in members) {
                 // do something with the user
             }
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) getMemberList:(id)delegate withCallback:(SEL)callback;


/** Asynchronously gets the owner of the associated group
 
 Receives a <KiiUser> object representing the group's owner. This is a non-blocking request.
 
     [g getOwnerWithBlock:^(KiiGroup *group, KiiUser *owner, NSError *error) {
         if(error == nil) {
             NSLog(@"Got owner: %@", owner);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) getOwnerWithBlock:(KiiGroupOwnerBlock)block;

/** Gets the owner of the associated group
 
 Returns a <KiiUser> object for this group's owner. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 @return A <KiiUser> object representing the current group's owner
 */
- (KiiUser*) getOwnerSynchronous:(NSError**)error;


/** Asynchronously gets the owner of the associated group
 
 Receives a <KiiUser> object representing the group's owner. This is a non-blocking request.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) gotOwner:(KiiUser*)owner inGroup:(KiiGroup*)group withError:(NSError*)error {
     
         if(error == nil) {
             // successfully got the owner, do something with it
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) getOwner:(id)delegate withCallback:(SEL)callback;

/** Returns the owner of this group if this group holds the information of owner.

 Group will holds the information of owner when "saving group on cloud" or "retrieving group info/owner from cloud".
 The cache will not be shared among the different instances of KiiGroup.

 @return A <KiiUser> object who owns this group, nil if this group doesn't hold the information of owner yet.
 @note This API will not access to server. To update the group owner information on cloud, please call KiiGroup refresh or getOwner methods.
 @warning This API does not return all the properties of the owner. To get all owner properties, KiiUser refresh is necessary.
 @see getOwnerSynchronous:
 @see getOwnerWithBlock:
 @see getOwner:withCallback:
 */
- (KiiUser *)getCachedOwner;

/** Asynchronously updates the local group's data with the group data on the server
 
 The group must exist on the server. Local data will be overwritten.
 
     [g refreshWithBlock:^(KiiGroup *group, NSError *error) {
         if(error == nil) {
             NSLog(@"Group refreshed: %@", group);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) refreshWithBlock:(KiiGroupBlock)block;

/** Synchronously updates the local object's data with the object data on the server
 
 The group must exist on the server. Local data will be overwritten. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) refreshSynchronous:(NSError**)error;


/** Asynchronously updates the local group's data with the group data on the server
 
 The group must exist on the server. Local data will be overwritten.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) groupRefreshed:(KiiGroup*)object withError:(NSError*)error {
     
        // the request was successful
        if(error == nil) {
            // do something with the object
        }
     
        else {
            // there was a problem
        }
     }
 
 */
- (void) refresh:(id)delegate withCallback:(SEL)callback;


/** Asynchronously saves the latest group information to the server
 
 If the group does not yet exist, it will be created. If the group already exists, the information that has changed will be updated accordingly. This is a non-blocking method.
 
     [g saveWithBlock:^(KiiGroup *group, NSError *error) {
         if(error == nil) {
             NSLog(@"Group saved: %@", group);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) saveWithBlock:(KiiGroupBlock)block;

/** Synchronously saves the latest group information to the server
 
 If the group does not yet exist, it will be created. If the group already exists, the information that has changed will be updated accordingly. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) saveSynchronous:(NSError**)error;


/** Asynchronously saves the latest group information to the server 
 
 If the group does not yet exist, it will be created. If the group already exists, the information that has changed will be updated accordingly. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) groupSaved:(KiiGroup*)group withError:(NSError*)error {
     
        // the request was successful
        if(error == nil) {
            // do something with the group
        }
     
        else {
            // there was a problem
        }
     }
 
 */
- (void) save:(id)delegate withCallback:(SEL)callback;


/** Asynchronously deletes a group from the server.
 
 Delete a group from the server. This method is non-blocking.
 
     [g deleteWithBlock:^(KiiGroup *group, NSError *error) {
         if(error == nil) {
             NSLog(@"Group deleted!");
         }
     }];

 @param block The block to be called upon method completion. See example
*/
- (void) deleteWithBlock:(KiiGroupBlock)block;

/** Synchronously deletes a group from the server.
 
 Delete a group from the server. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) deleteSynchronous:(NSError**)error;


/** Asynchronously deletes a group from the server.
 
 Delete a group from the server. This method is non-blocking.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) groupDeleted:(KiiGroup*)group withError:(NSError*)error {
     
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


/** Asynchronously updates the group name on the server
 
 This method is non-blocking.
 
     [g changeGroupName:@"new_group_name" withBlock:^(KiiGroup *group, NSError *error) {
         if(error == nil) {
             NSLog(@"Group name changed!");
         }
     }];
 
 @param groupName An NSString of the desired group name
 @param block The block to be called upon method completion. See example
*/
- (void) changeGroupName:(NSString*)groupName withBlock:(KiiGroupBlock)block;

/** Synchronously updates the group name on the server
 
 This method is blocking.
 @param groupName An NSString of the desired group name
 @param error An NSError object, set to nil, to test for errors
 */
- (void) changeGroupNameSynchronous:(NSString*)groupName withError:(NSError**)error;


/** Asynchronously updates the group name on the server
 
 This method is non-blocking.
 @param groupName An NSString of the desired group name
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) groupNameUpdated:(KiiGroup*)group withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) changeGroupName:(NSString*)groupName withDelegate:(id)delegate andCallback:(SEL)callback;




/** Prints the contents of this object to log
 
 For developer purposes only, this method prints the object in a readable format to the log for testing.
 */
- (void) describe;


@end
