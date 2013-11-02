//
//  KiiObject.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 1/5/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FileHolder.h"

@class KiiACL, KiiBucket, KiiACL, KiiObject,KiiUploader,KiiDownloader, KiiGeoPoint;
typedef void (^KiiObjectBlock)(KiiObject *object, NSError *error);


/** A server-compatible object for generic storage use cases */
@interface KiiObject : NSObject<FileHolder>

/** The unique id of the object, assigned by the server */
@property (readonly) NSString *uuid;

/** The date the object was created on the server */
@property (strong, readonly) NSDate *created;

/** The date the object was last modified on the server */
@property (strong, readonly) NSDate *modified;

/** Get a specifically formatted string referencing the object. The object must exist in the cloud (have a valid UUID). */
@property (strong, readonly) NSString *objectURI;

/** The application-defined class name of the object */
@property (strong, readonly) NSString *objectType;

/** Get the ACL handle for this file. Any <KiiACLEntry> objects added or revoked from this ACL object will be appended to/removed from the server on ACL save. */
@property (readonly) KiiACL *objectACL;

/** The bucket that owns this object */
@property (readonly) KiiBucket *bucket;


/** Create a KiiObject that references an existing object
 
 @param uri An object-specific URI
 @return a working KiiObject
 */
+ (KiiObject*) objectWithURI:(NSString*)uri;


/** Retrieves a readable class name for this object 
 
 If the object is user-defined, it will return the class name it was initialized with. If it is a Kii subclass, it will return a readable string value of that class.
 @return A string value of this object's class name
 */
//- (NSString*) getClassName;


/** Sets a key/value pair to a KiiObject
 
 If the key already exists, its value will be written over. If the object is of invalid type, it will return false and an NSError will be thrown (quietly). Accepted types are any JSON-encodable objects.
 ***NOTE: Before involving floating point value, please consider using integer instead. For example, use percentage, permil, ppm, etc.***
 The reason is:
 - Will dramatically improve the performance of bucket query.
 - Bucket query does not support the mixed result of integer and floating point.
 ex.) If you use same key for integer and floating point and inquire object with the
 integer value, objects which has folating point value with the key would not be evaluated
 in the query. (and vice versa)
 @param object The value to be set. Object must be of a JSON-encodable type (Ex: NSDictionary, NSArray, NSString, NSNumber, etc)
 @param key The key to set. The key must not be a system key (created, metadata, modified, type, uuid) or begin with an underscore (_)
 @return True if the object was set, false otherwise.
 */
- (BOOL) setObject:(id)object forKey:(NSString*)key;

/**
  Set GeoPoint to this object with the specified key.
  @param key name of the field.
  @param value GeoPoint to be tied to the specified key.
 */
- (BOOL) setGeoPoint:(KiiGeoPoint*)object forKey:(NSString*)key;


/** Checks to see if an object exists for a given key
 
 @param key The key to check for existence
 @return True if the object exists, false otherwise.
 */
- (BOOL) hasObject:(NSString*)key;


/** Removes a specific key/value pair from the object
 If the key exists, the key/value will be removed from the object. Please note that the object must be saved before the changes propogate to the server.
 @param key The key of the key/value pair that will be removed
 */
- (void) removeObjectForKey:(NSString*)key;


/** Gets the value associated with the given key
 
 @param key The key to retrieve
 @return An object if the key exists, null otherwise
 */
- (id) getObjectForKey:(NSString*)key;

/** Gets the GeoPoint associated with the given key
 
 @param key The key to retrieve
 @return An object if the key exists, null otherwise
 */
- (KiiGeoPoint*) getGeoPointForKey:(NSString*)key;


/** Asynchronously saves the latest object values to the server
 
 If the object does not yet exist, it will be created. If the object already exists, the fields that have changed locally will be updated accordingly. This is a non-blocking method.
 
     [obj saveWithBlock:^(KiiObject *object, NSError *error) {
         if(error == nil) {
             NSLog(@"Object saved: %@", object);
         }
     }];
 
 @param block The block to be called upon method completion. See example 
*/
- (void) saveWithBlock:(KiiObjectBlock)block;


/** Asynchronously saves the latest object values to the server 
 
 If the object does not yet exist, it will be created. If the object already exists, the fields that have changed locally will be updated accordingly. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) objectSaved:(KiiObject*)object withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the object
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) save:(id)delegate withCallback:(SEL)callback;


/** Synchronously saves the latest object values to the server 
 
 If the object does not yet exist, it will be created. If the object already exists, the fields that have changed locally will be updated accordingly. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) saveSynchronous:(NSError**)error;


/** Asynchronously saves the latest object values to the server
 
 If the object does not yet exist, it will be created. If the object already exists and forced is set to TRUE, all fields on the server will be replaced by the fields defined locally. Otherwise, only changed fields will be modified. This is a non-blocking method.
 
     [obj save:TRUE withBlock:^(KiiObject *object, NSError *error) {
         if(error == nil) {
             NSLog(@"Object saved: %@", object);
         }
     }];
 
 @param forced Set to TRUE if the local copy should overwrite the remote copy, even if the remote copy is newer. Set to FALSE otherwise.
 @param block The block to be called upon method completion. See example
*/
- (void) save:(BOOL)forced withBlock:(KiiObjectBlock)block;


/** Asynchronously saves the latest object values to the server
 
 If the object does not yet exist, it will be created. If the object already exists and forced is set to TRUE, all fields on the server will be replaced by the fields defined locally. Otherwise, only changed fields will be modified. This is a non-blocking method.
 @param forced Set to TRUE if the local copy should overwrite the remote copy, even if the remote copy is newer. Set to FALSE otherwise.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) objectSaved:(KiiObject*)object withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // do something with the object
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) save:(BOOL)forced withDelegate:(id)delegate andCallback:(SEL)callback;


/** Synchronously saves the latest object values to the server
 
 If the object does not yet exist, it will be created. If the object already exists and forced is set to TRUE, all fields on the server will be replaced by the fields defined locally. Otherwise, only changed fields will be modified. This is a blocking method.
 @param forced Set to TRUE if the local copy should overwrite the remote copy, even if the remote copy is newer. Set to FALSE otherwise.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) saveSynchronous:(BOOL)forced withError:(NSError**)error;


/** Asynchronously saves the latest object values to the server
 
 If the object does not yet exist, it will be created. If the object already exists, all fields will be removed or changed to match the local values. This is a non-blocking method.
 
     [obj save:TRUE withBlock:^(KiiObject *object, NSError *error) {
         if(error == nil) {
             NSLog(@"Object saved: %@", object);
         }
     }];

 @param forced Set to TRUE if the local copy should overwrite the remote copy, even if the remote copy is newer. Set to FALSE otherwise.
 @param block The block to be called upon method completion. See example
*/
- (void) saveAllFields:(BOOL)forced withBlock:(KiiObjectBlock)block;


/** Asynchronously saves the latest object values to the server
 
 If the object does not yet exist, it will be created. If the object already exists, all fields will be removed or changed to match the local values. This is a non-blocking method.
 @param forced Set to TRUE if the local copy should overwrite the remote copy, even if the remote copy is newer. Set to FALSE otherwise.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
     
     - (void) objectSaved:(KiiObject*)object withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the object
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) saveAllFields:(BOOL)forced withDelegate:(id)delegate andCallback:(SEL)callback;


/** Synchronously saves the latest object values to the server
 
 If the object does not yet exist, it will be created. If the object already exists, all fields will be removed or changed to match the local values. This is a blocking method.
 @param forced Set to TRUE if the local copy should overwrite the remote copy, even if the remote copy is newer. Set to FALSE otherwise.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) saveAllFieldsSynchronous:(BOOL)forced withError:(NSError**)error;

/** Asynchronously updates the local object's data with the object data on the server
 
 The object must exist on the server. Local data will be overwritten.
     
     [obj refreshWithBlock:^(KiiObject *object, NSError *error) {
         if(error == nil) {
             NSLog(@"Object refreshed: %@", object);
         }
     }];
     
 @param block The block to be called upon method completion. See example
*/
- (void) refreshWithBlock:(KiiObjectBlock)block;

/** Asynchronously updates the local object's data with the object data on the server
 
 The object must exist on the server. Local data will be overwritten.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) objectRefreshed:(KiiObject*)object withError:(NSError*)error {
         
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


/** Synchronously updates the local object's data with the object data on the server
 
 The object must exist on the server. Local data will be overwritten. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) refreshSynchronous:(NSError**)error;

/** Asynchronously deletes an object from the server.
 
 Delete an object from the server. This method is non-blocking.
 
     [obj deleteWithBlock:^(KiiObject *object, NSError *error) {
         if(error == nil) {
             NSLog(@"Object deleted!");
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) deleteWithBlock:(KiiObjectBlock)block;


/** Asynchronously deletes an object from the server.
 
 Delete an object from the server. This method is non-blocking.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) objectDeleted:(KiiObject*)object withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the object
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) delete:(id)delegate withCallback:(SEL)callback;


/** Synchronously deletes an object from the server.
 
 Delete an object from the server. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) deleteSynchronous:(NSError**)error;

/** Synchronously deletes an object's body from the server.
 
 Delete an object's body from the server. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) deleteBodySynchronous:(NSError**)error;

/** Asynchronously deletes an object's body from the server.
 
 Delete an object's body from the server. This method is non-blocking.
 
     [obj deleteBodyWithBlock:^(KiiObject *object, NSError *error) {
         if(error == nil) {
            NSLog(@"Object's body deleted!");
         }
     }];
 
 @param block The block to be called upon method completion. See example
 */
- (void) deleteBodyWithBlock:(KiiObjectBlock)block;

/** Gets a dictionary value of the application-specific attributes of this object */
- (NSDictionary*) dictionaryValue;

/** Prints the contents of this object to log
 
 For developer purposes only, this method prints the object in a readable format to the log for testing.
 */
- (void) describe;

///---------------------------------------------------------------------------------------
/// @name Resumable Transfer Handling
///---------------------------------------------------------------------------------------

/**
 Get uploader. If there is no uploader in the app, it will be created new instance
 @param localPath Path that will be used by the uploader.
 @return A KiiUploader instance associated to this object
 */
-(KiiUploader*) uploader : (NSString*) localPath;

/**
 Get downloader. If there is no downloader in the app, it will be created new instance
 @param localPath Path that will be used by the downloader. If file exists, will be overwritten.
 @return A KiiDownloader instance associated to this object
 */
-(KiiDownloader*) downloader : (NSString*) localPath;
@end
