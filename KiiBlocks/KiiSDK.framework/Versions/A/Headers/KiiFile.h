//
//  KiiFile.h
//  SampleApp
//
//  Created by Chris Beauchamp on 12/12/11.
//  Copyright (c) 2011 Kii Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FileHolder.h"

@class KiiQuery, KiiFileBucket, KiiFile, KiiACL,KiiUploader,KiiDownloader;

typedef void (^KiiFileProgressBlock)(KiiFile *file, double progress);
typedef void (^KiiFileBlock)(KiiFile *file, NSError *error);
typedef void (^KiiFileDownloadBlock)(KiiFile *file, NSString *toPath, NSError *error);
typedef void (^KiiFilePublishBlock)(KiiFile* file, NSString *toURL, NSError *error);

/** Contains single file and file system information and methods
 
 The file class allows an application to create a file object and upload it to the server. Once stored, the file can be moved to trash, permanently deleted, updated and downloaded. 
 
 There are also File System methods available which are called statically, and provide system functions such as retrieving and emptying the trash.
 */
@interface KiiFile : NSObject <FileHolder>


/** The bucket that contains this file */
@property (strong, readonly) KiiFileBucket *bucket;

/** The local path of a file to upload. This path is not saved to the server and only used for uploading new files or changing existing file bodies. */
@property (nonatomic, strong) NSString *localPath;

/** The data associated with this file */
@property (nonatomic, strong) NSData *data;

/** The remote ID of the file on the server */
@property (readonly) NSString *uuid;

/** The Content-Type of the file */
@property (nonatomic, strong) NSString *mimeType;

/** The title of the file on the server */
@property (nonatomic, strong) NSString *title;

/** The thumbnail associated with this file (for image objects) **/
@property (nonatomic, strong) UIImage *thumbnail;

/** The creation date of the file on the server */
@property (strong, readonly) NSDate *created;

/** The modified date of the file on the server */
@property (strong, readonly) NSDate *modified;

/** An optional application-specific UTF-8 encoded string. This field has a maximum size of 512 bytes */
@property (nonatomic, strong) NSString *optional;

/** The size of the file on the server */
@property (strong, readonly) NSNumber *fileSize;

/** A boolean value, TRUE if the file is in the trash, FALSE otherwise */
@property (readonly) BOOL trashed;

/** Get a specifically formatted string referencing the file. The file must exist in the cloud (have a valid UUID). */
@property (strong, readonly) NSString *objectURI;

/** Get the ACL handle for this file. Any <KiiACLEntry> objects added or revoked from this ACL object will be appended to/removed from the server on ACL save. */
@property (readonly) KiiACL *fileACL;

#pragma mark - single file methods

///---------------------------------------------------------------------------------------
/// @name Single File Handling
///---------------------------------------------------------------------------------------

/** Generates a KiiFile object based on an existing file URI

 @param uri A file-specific URI
 @return A new KiiFile object
 */
+ (KiiFile*) fileWithURI:(NSString*)uri;



/** Saves the file data to the server
 
 Saves the file data, overwriting the contents on the server with the local contents. This is a non-blocking method.
 
 Error code 403 indicates that the local file specified was unable to be uploaded. If you receive this error, the file metadata and object was created on the server, but the body was not uploaded.

 
     [f saveFileWithProgressBlock:^(KiiFile *file, double progress) {
         NSLog(@"Progress: %lf %@", progress, file);
     } 
     andCompletionBlock:^(KiiFile *file, NSError *error) {
         if(error == nil) {
            NSLog(@"File saved: %@", file);
         }
     }];

 @param progress The callback block to be called when progress is made on the request. See the example
 @param completion The callback block to be called when the request is completed. See the example
 @note This API save file metadata and file body if target local file or data exists, but save only file metadata if target local file or data does NOT exist.
*/
- (void) saveFileWithProgressBlock:(KiiFileProgressBlock)progress andCompletionBlock:(KiiFileBlock)completion;


/** Saves the file data to the server
 
 Saves the file data, overwriting the contents on the server with the local contents. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param progress The callback method to be called when progress is made on the request. The progress callback should have a method signature similar to:
 
     - (void) updateProgress:(KiiFile*)file withProgress:(NSNumber*)progress {   
         // progress is sent as a float [0, 1]
         float f = [progress floatValue];
         // update the UI
     }
     
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
     
     - (void) fileUpdated:(KiiFile*)file withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the file object
         }
         
         else {
             // there was a problem
         }
     }
 
 Error code 403 indicates that the local file specified was unable to be uploaded. If you receive this error, the file metadata and object was created on the server, but the body was not uploaded.
 @note This API save file metadata and file body if target local file or data exists, but save only file metadata if target local file or data does NOT exist.
 */
- (void) saveFile:(id)delegate withProgress:(SEL)progress andCallback:(SEL)callback;


/** Saves the file data
 
 Saves the file data, overwriting the contents on the server with the local contents. This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue. Error code 403 indicates that the local file specified was unable to be uploaded. If you receive this error, the file metadata and object was created on the server, but the body was not uploaded.
 @note This API save file metadata and file body if target local file or data exists, but save only file metadata if target local file or data does NOT exist.
 */
- (void) saveFileSynchronous:(NSError**)err; //



/** Saves the file metadata to the server
 
 Saves the file metadata, overwriting the contents on the server with the local contents. This is a non-blocking method.

    KiiFile *f = [bucket fileWithLocalPath:localPath];
    [f setTitle:@"my_title"];
    [f saveMetaDataWithBlock:^(KiiFile *file, NSError *error) {
        if(error == nil) {
            NSLog(@"Saved file: %@", file);
        }
    }];

 @param block The block to be called upon method completion. See example
*/
- (void) saveMetaDataWithBlock:(KiiFileBlock)block;

/** Saves the file metadata to the server
 
 Saves the file metadata, overwriting the contents on the server with the local contents. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param progress The callback method to be called when progress is made on the request. The progress callback should have a method signature similar to:
 
     - (void) updateProgress:(KiiFile*)file withProgress:(NSNumber*)progress {   
         // progress is sent as a float [0, 1]
         float f = [progress floatValue];
         // update the UI
     }
 
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) fileUpdated:(KiiFile*)file withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the file object
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) saveMetaData:(id)delegate withProgress:(SEL)progress andCallback:(SEL)callback;


/** Saves the file metadata
 
 Saves the file metadata, overwriting the contents on the server with the local contents. This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 */
- (void) saveMetaDataSynchronous:(NSError**)err; //


/** Refreshes the file metadata
 
 Updates the local KiiFile object with metadata from the server. This is a non-blocking method.
 
     [f getFileMetadataWithBlock:^(KiiFile *file, NSError *error) {
         if(error == nil) {
             NSLog(@"Retrieved file: %@", file);
         }
     }];
 
 @param block The block to be called upon method completion. See example
 */
- (void) getFileMetadataWithBlock:(KiiFileBlock)block;

/** Refreshes the file metadata
 
 Updates the local KiiFile object with metadata from the server. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) fileRefreshed:(KiiFile*)file withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // do something with the file object
        }
 
        else {
            // there was a problem
        }
    }

 */
- (void) getFileMetadata:(id)delegate withCallback:(SEL)callback; //


/** Refreshes the file metadata
 
 Updates the local KiiFile object with metadata from the server. This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 */
- (void) getFileMetadataSynchronous:(NSError**)err; //


/** Retrieves the file body from the server
 
 Updates the local KiiFile object with the file body from the server. If the toPath parameter is nil, the file body will be stored in the 'data' attribute. Otherwise, the body will be downloaded to the given file path. This is a non-blocking method.
 
    [f getFileBody:@"my/tmp/dir" withProgressBlock:^(KiiFile *file, double progress) {
        NSLog(@"Progress: %lf %@", progress, file);
    }
    andCompletionBlock:^(KiiFile *file, NSString *toPath, NSError *error) {
        if(error == nil) {
            NSLog(@"File saved: %@", file);
        }
    }];
 
 @param toPath The path of the file the body will be written to. If nil, the file body will be stored in the 'data' attribute.
 @param progress The callback block to be called when progress is made on the request. See the example
 @param completion The callback block to be called when the request is completed. See the example
*/
- (void) getFileBody:(NSString*)toPath withProgressBlock:(KiiFileProgressBlock)progress andCompletionBlock:(KiiFileDownloadBlock)complete;


/** Retrieves the file body from the server

 Updates the local KiiFile object with the file body from the server. If the toPath parameter is nil, the file body will be stored in the 'data' attribute. Otherwise, the body will be downloaded to the given file path. This is a non-blocking method.
 @param toPath The path of the file the body will be written to. If nil, the file body will be stored in the 'data' attribute.
 @param delegate The object to make any callback requests to
 @param progress The callback method to be called when progress is made on the request. The progress callback should have a method signature similar to:
 
    - (void) downloadProgress:(KiiFile*)file withProgress:(NSNumber*)progress {   
        // progress is sent as a float [0, 1]
        float f = [progress floatValue];
        // update the UI
    }
 
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) fileDownloaded:(KiiFile*)file toPath:(NSString*)toPath withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // do something with the new file path
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) getFileBody:(NSString*)toPath withDelegate:(id)delegate andProgress:(SEL)progress andCallback:(SEL)callback;


/** Retrieves the file body from the server
 
 Updates the local KiiFile object with the file body from the server. If the toPath parameter is nil, the file body will be stored in the 'data' attribute. Otherwise, the body will be downloaded to the given file path. This is a non-blocking method.
 @param toPath The path of the file the body will be written to. If nil, the file body will be stored in the 'data' attribute.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 */
- (void) getFileBodySynchronous:(NSString*)toPath withError:(NSError**)err;


/** Permanently deletes a trashed file.
 
 If the file is not in the trash, an error is returned and the file remains as active. This is a non-blocking method.
 
    [f shredFileWithBlock:^(KiiFile *file, NSError *error) {
        if(error == nil) {
            NSLog(@"File shredded: %@", file);
         }
     }];
 
 @param block The block to be called upon method completion. See example
 */
- (void) shredFileWithBlock:(KiiFileBlock)block;

/** Permanently deletes a trashed file.
 
 If the file is not in the trash, an error is returned and the file remains as active. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) fileShredded:(KiiFile*)file withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // mark the file as deleted on the UI
        }
 
        else {
            // there was a problem
        }
    }

 */
- (void) shredFile:(id)delegate withCallback:(SEL)callback;


/** Permanently deletes a trashed file.
 
 If the file is not in the trash, an error is returned and the file remains as active. This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 */
- (void) shredFileSynchronous:(NSError**)err;//




/** Moves the working file to the trash
 
 The file, once moved to trash, can be restored as long as the trash hasn't been emptied and the file hasn't been shredded since trashing the file. This is a non-blocking method.
 
     [f moveToTrashWithBlock:^(KiiFile *file, NSError *error) {
         if(error == nil) {
             NSLog(@"File shredded: %@", file);
         }
     }];
 
 @param block The block to be called upon method completion. See example
 */
- (void) moveToTrashWithBlock:(KiiFileBlock)block;

/** Moves the working file to the trash
 
 The file, once moved to trash, can be restored as long as the trash hasn't been emptied and the file hasn't been shredded since trashing the file. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) fileTrashed:(KiiFile*)file withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // mark the file as moved to trash on the UI
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) moveToTrash:(id)delegate withCallback:(SEL)callback;


/** Moves the working file to the trash
 
 The file, once moved to trash, can be restored as long as the trash hasn't been emptied and the file hasn't been shredded since trashing the file. This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 */
- (void) moveToTrashSynchronous:(NSError**)err; //



/** Restores the working file from the trash
 
 This is a non-blocking method.
 
     [f restoreFromTrashWithBlock:^(KiiFile *file, NSError *error) {
         if(error == nil) {
             NSLog(@"File restored: %@", file);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) restoreFromTrashWithBlock:(KiiFileBlock)block;

/** Restores the working file from the trash
 
 This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) fileRestored:(KiiFile*)file withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // mark the file as moved to trash on the UI
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) restoreFromTrash:(id)delegate withCallback:(SEL)callback; //


/** Restores the working file from the trash
 
 This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 */
- (void) restoreFromTrashSynchronous:(NSError**)err; //


/** Publishes the file body to a public, time sensitive URL
 
 The body that exists on the server will be published. The body will not be uploaded again when this method is called, it is simply making the body available via URL. The link will expire at the provided time and the link will become inaccessible. This is a non-blocking method.

 
     [f publish:expires withBlock:^(KiiFile *file, NSString *toURL, NSError *error) {
         if(error == nil) {
             NSLog(@"Published file %@ to URL: %@", file, toURL);
         }
     }];
 
 @param expiresAt The date at which the link should expire
 @param block The block to be called upon method completion. See example
*/
- (void) publish:(NSDate*)expiresAt withBlock:(KiiFilePublishBlock)block;

/** Publishes the file body to a public, time sensitive URL
 
 The body that exists on the server will be published. The body will not be uploaded again when this method is called, it is simply making the body available via URL. The link will expire at the provided time and the link will become inaccessible. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 @param expiresAt The date at which the link should expire
 
    - (void) filePublished:(KiiFile*)file toURL:(NSString*)url withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // utilize the url
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) publish:(id)delegate andCallback:(SEL)callback expiresAt:(NSDate*)expiresAt; //


/** Synchronously publishes the file body to a public, time sensitive URL
 
 The body that exists on the server will be published. The body will not be uploaded again when this method is called, it is simply making the body available via URL. The link will expire at the provided time and the link will become inaccessible. This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 @param expiresAt The date at which the link should expire
 @return A URL pointing to the public file. Note: this will be nil on failure.
 */
- (NSString*) publishSynchronous:(NSError**)err expiresAt:(NSDate*)expiresAt; //


/** Publishes the file body to a public, time sensitive URL
 
 The body that exists on the server will be published. The body will not be uploaded again when this method is called, it is simply making the body available via URL. The link will never expire. This is a non-blocking method.
 
     [f publishWithBlock:^(KiiFile *file, NSString *toURL, NSError *error) {
         if(error == nil) {
             NSLog(@"Published file %@ to URL: %@", file, toURL);
         }
     }];
 
 @param expiresAt The date at which the link should expire
 @param block The block to be called upon method completion. See example
 */
- (void) publishWithBlock:(KiiFilePublishBlock)block;

/** Publishes the file body to a public URL
 
 The body that exists on the server will be published. The body will not be uploaded again when this method is called, it is simply making the body available via URL. The link will never expire. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) filePublished:(KiiFile*)file toURL:(NSString*)url withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // utilize the url
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) publish:(id)delegate andCallback:(SEL)callback; //


/** Synchronously publishes the file body to a public, persistent URL
 
 The body that exists on the server will be published. The body will not be uploaded again when this method is called, it is simply making the body available via URL. The link will never expire. This is a blocking method.
 @param err An NSError object, passed by reference. If the error is nil, the request was successful. Otherwise, the error contains a description of the issue.
 @return A URL pointing to the public file. Note: this will be nil on failure.
 */
- (NSString*) publishSynchronous:(NSError**)err; //


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


