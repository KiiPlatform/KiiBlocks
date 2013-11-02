//
//  KiiACL.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 5/14/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiACLEntry, KiiACL;

typedef void (^KiiACLArrayBlock)(KiiACL *acl, NSArray *aclList, NSError *error);
typedef void (^KiiACLSaveBlock)(KiiACL *acl, NSArray *succeeded, NSArray *failed, NSError *error);

/** A reference to the ACL of a <KiiObject> or <KiiFile>
 
 A single KiiACL object can contain multiple <KiiACLEntry> objects, which grant/prevent access of the associated object to users and groups.
 */
@interface KiiACL : NSObject

/** Asynchronously gets the list of active ACLs associated with this object from the server
 
 This is a non-blocking method
 
     [a listACLEntriesWithBlock:^(KiiACL *acl, NSArray *aclList, NSError *error) {
         if(error == nil) {
             NSLog(@"Got acl entries: %@", aclList);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) listACLEntriesWithBlock:(KiiACLArrayBlock)block;

/** Get the list of active ACLs associated with this object from the server
 
 This is a blocking method
 @param error An NSError object, set to nil, to test for errors
 @return An array of <KiiACLEntry> objects
 */
- (NSArray*) listACLEntriesSynchronous:(NSError**)error; 


/** Asynchronously gets the list of active ACLs associated with this object from the server

 This is a non-blocking method
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) listRetrieved:(KiiACL*)forACL withResults:(NSArray*)aclList andError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the list
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) listACLEntries:(id)delegate withCallback:(SEL)callback; 


/** Add a <KiiACLEntry> to the local object, if not already present
 
 @param entry The <KiiACLEntry> to add
 @return TRUE if the entry was added, FALSE otherwise
 */
- (BOOL) putACLEntry:(KiiACLEntry*)entry;


/** Remove a <KiiACLEntry> from the local object
 
 @param entry The <KiiACLEntry> to remove
 @return TRUE if the entry was removed, FALSE otherwise
 */
- (BOOL) removeACLEntry:(KiiACLEntry*)entry; 


/** Asynchronously saves the list of ACLEntry objects associated with this ACL object to the server
 
 This is a non-blocking method
 
     [a listACLEntriesWithBlock:^(KiiACL *acl, NSArray *succeeded, NSArray *failed, NSError *error) {
         if(error == nil) {
             NSLog(@"ACL entries that were successfully saved: %@", succeeded);
             NSLog(@"ACL entries that were NOT saved: %@", failed);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) saveWithBlock:(KiiACLSaveBlock)block;


/** Save the list of ACLEntry objects associated with this ACL object to the server
 
 This is a blocking method
 @param error An NSError object, set to nil, to test for errors. If this error shows partial success, one or more of the ACL entries was unsuccessfully saved - check the succeeded/failed parameters.
 @param succeeded An NSArray object of <KiiACLEntry> objects that were successfully updated
 @param failed An NSArray object of <KiiACLEntry> objects that failed to update
 */
- (void) saveSynchronous:(NSError**)error
              didSucceed:(NSArray**)succeeded
                 didFail:(NSArray**)failed;


/** Asynchronously saves the list of ACLEntry objects associated with this ACL object to the server
 
 This is a non-blocking method
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) aclSaved:(KiiACL*)acl withError:(NSError*)error andSuccessfulEntries:(NSArray*)successful andFailedEntries:(NSArray*)failed {
     
         // the request was successful
         if(error == nil) {
             // do something with the list
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) save:(id)delegate withCallback:(SEL)callback;

@end
