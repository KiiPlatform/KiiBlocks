//
//  KiiError.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 12/21/11.
//  Copyright (c) 2011 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Find error codes and messages that can be returned by Kii SDK
 
 <h3>Application Errors (1xx)</h3>
 - *101* - The application received invalid credentials and was not initialized
 - *102* - The application was not found on the server. Please ensure your app id and key were entered correctly.
 - *103* - The required operation is failed due to unexpected error. Should not thrown if using latest SDK.

 <h3>Connectivity Errors (2xx)</h3>
 - *201* - Unable to connect to the internet
 - *202* - Unable to parse server response
 - *203* - Unable to authorize request
 
 <h3>User API Errors (3xx)</h3>
 - *301* - Unable to retrieve valid access token
 - *302* - Unable to authenticate user
 - *303* - Unable to retrieve file list
 - *304* - Invalid password format. Password must be 4-50 printable ASCII characters.
 - *305* - Invalid email format. Email must be a valid address
 - *306* - Invalid user object. Please ensure the credentials were entered properly
 - *307* - Invalid username format. The username must be 3-64 alphanumeric characters - the first character must be a letter
 - *308* - Invalid phone format. The phone number must be numeric between 7 and 20 digits, and it can begin with '+'
 - *309* - Unable to verify account. Please ensure the verification code provided is correct
 - *310* - Invalid displayname format. The displayname length is 4-50 chars (not byte), and allow Multi-Byte input.
 - *311* - The user's email was unable to be updated on the server
 - *312* - The user's phone number was unable to be updated on the server
 - *313* - Invalid email address format or phone number format. A userIdentifier must be one of the two
 - *314* - The request could not be made - the key associated with the social network is invalid
 - *315* - Invalid country code.
 - *316* - Invalid local phone format. The phone number numerical and must be at least 7 digits
 - *317* - Invalid credentials, please check whether the credentials associated with social network is valid
 - *318* - Social network account has been already linked.
 - *319* - Social network account is not linked.
 
 <h3>File API Errors (4xx)</h3>
 - *401* - Unable to delete file from cloud
 - *402* - Unable to upload file to cloud
 - *403* - Unable to retrieve local file for uploading. May not exist, or may be a directory
 - *404* - Unable to shred file. Must be in the trash before it is permanently deleted
 - *405* - Unable to perform operation - a valid container must be set first
 
 <h3>Core Object Errors (5xx)</h3>
 - *501* - Invalid objects passed to method. Must be already saved on server
 - *502* - Unable to parse object. Must be JSON-encodable
 - *503* - Duplicate entry exists
 - *504* - Invalid remote path set for KiiFile. Must be of form: /root/path/subpath
 - *505* - Unable to delete object from cloud
 - *506* - Invalid KiiObject type - the type does not match the regex [A-Za-z]{1}[A-Za-z0-9-_]{4,49}
 - *507* - Unable to set an object as a child of itself
 - *508* - The key of the object being set is being used by the system. Please use a different key
 - *509* - The container you are trying to operate on does not exist
 - *510* - The object you are trying to operate on does not exist on the server
 - *511* - The URI provided is invalid
 - *512* - The object you are saving is older than what is on the server. Use one of the KiiObject#save:forced: methods to forcibly override data on the server
 - *513* - The group name provided is not valid. Ensure it is alphanumeric and more than 0 characters in length
 - *514* - At least one of the ACL entries saved to an object failed. Please note there may also have been one or more successful entries
 - *515* - Bucket parent(user/group) of the bucket does not exist in the cloud.

 <h3>Query Errors (6xx)</h3>
 - *601* - No more query results exist
 - *602* - Query limit set too high
 - *603* - Query clauses is empty. Make sure "OR" and/or "AND" clauses have at least one correct sub-clauses

 <h3>Push Notification Errors (7xx)</h3>
 - *701* - Push installation error. Installation already exist
 - *702* - Push subscription already exists
 - *703* - Push subscription does not exist
 - *704* - Topic already exists
 - *705* - Topic does not exist
 - *706* - Invalid push message data
 - *707* - APNS field is required
 - *708* - Push data is required
 - *709* - Device token is not set
 - *710* - Push installation does not exist
 - *711* - Topic ID is invalid. Topic ID must be alphanumeric character and between 1-64 length
 - *712* - GCM payload key contains google reserved words
 - *713* - Topic parent(user/group) does not exist in the cloud.

 <h3>Resumable Transfer Errors (8xx)</h3>
 - *801* - Resumable transfer object has already transferred completely
 - *802* - File has been modified during transfer
 - *803* - File path is invalid, can not get the file attribute
 - *804* - File does not exist
 - *805* - File path is a directory
 - *806* - File size is 0 byte
 - *807* - Invalid transfer state, transfer is already suspended
 - *808* - Invalid transfer state, transfer is already terminated
 - *809* - Transfer was suspended
 - *810* - Transfer was terminated
 - *811* - Transfer has already started
 - *812* - Object body integrity not assured. ClientHash must be same during transfer.
 - *813* - Object body range not satisfiable. Please try to transfer using another task.
 - *814* - File path is not writable.
 - *815* - Invalid destination file, file range is not assured
 - *816* - Unable to operate transfer manager. The transfer manager can not operate since current user is nil or different from the user who instantiate.
 */
@interface KiiError : NSError

+ (NSError*) errorWithCode:(NSString*)code andMessage:(NSString*)message;

/* Application Errors (1xx) */

/* The application received invalid credentials and was not initialized. Make sure you have called [Kii begin...] with the proper app id and key before making any requests */
+ (NSError*) invalidApplication;

/* The application was not found on the server. Please ensure your app id and key were entered correctly. */
+ (NSError*) appNotFound;

/* The required operation is failed due to unexpected error. Should not thrown if using latest SDK. */
+ (NSError*) undefinedError;


/* Connectivity Errors (2xx) */

/* Unable to connect to the internet */
+ (NSError*) unableToConnectToInternet;

/* Unable to parse server response */
+ (NSError*) unableToParseResponse;

/* Unable to authorize request */
+ (NSError*) unauthorizedRequest;


/* User API Errors (3xx) */

/* Unable to retrieve valid access token */
+ (NSError*) invalidAccessToken;

/* Unable to authenticate user */
+ (NSError*) unableToAuthenticateUser;

/* Unable to retrieve file list */
+ (NSError*) unableToRetrieveUserFileList;

/* Invalid password format. Password must be 4-50 printable ASCII characters */
+ (NSError*) invalidPasswordFormat;

/* Invalid email format. Email must be a valid address */
+ (NSError*) invalidEmailFormat;

/* Invalid email address format or phone number format. A userIdentifier must be one of the two */
+ (NSError*) invalidUserIdentifier;

/* Invalid username format. The username must be 3-64 alphanumeric characters - the first character must be a letter. */
+ (NSError*) invalidUsername;

/* Invalid user object. Please ensure the credentials were entered properly */
+ (NSError*) invalidUserObject;

/* Invalid phone format. The phone number must be numeric between 7 and 20 digits, and it can begin with '+'. */
+ (NSError*) invalidPhoneFormat;

/* Invalid Country code. 2-letters country code, capital letters*/
+ (NSError*) invalidCountryCode;
/* Invalid local phone format. The phone number numerical and must be at least 7 digits*/
+ (NSError*) invalidLocalPhoneFormat;

/* Invalid verification code */
+ (NSError*) unableToVerifyUser;

/* Invalid displayname format. The displayname length is 4-50 chars (not byte), and allow Multi-Byte input. */
+ (NSError*) invalidDisplayName;

/* The user's email was unable to be updated on the server */
+ (NSError*) unableToUpdateEmail;

/* The user's phone number was unable to be updated on the server */
+ (NSError*) unableToUpdatePhoneNumber;

/* The request could not be made - the key associated with the social network is invalid. */
+ (NSError*) invalidSocialNetworkKey;

/* Invalid credentials, please check whether the credentials associated with social network is valid */
+ (NSError*) invalidCredentials;

/* Social network account has been already linked */
+ (NSError*) socialAccountAlreadyLinked;

/* Social network account has is not linked */
+ (NSError*) socialAccountNotLinked;

/* File API Errors (4xx) */

/* Unable to delete file from cloud */
+ (NSError*) unableToDeleteFile;

/* Unable to upload file to cloud */
+ (NSError*) unableToUploadFile;

/* Unable to retrieve local file for uploading. May not exist, or may be a directory. */
+ (NSError*) localFileInvalid;

/* Unable to shred file. Must be in the trash before it is permanently deleted. */
+ (NSError*) shreddedFileMustBeInTrash;

/* Unable to perform operation - a valid container must be set first. */
+ (NSError*) fileContainerNotSpecified;


/* Core Object Errors (5xx) */

/* Invalid objects passed to method. Must be already saved on server. */
+ (NSError*) invalidObjects;

/* Unable to parse object. Must be JSON-encodable */
+ (NSError*) unableToParseObject;

/* Duplicate entry exists */
+ (NSError*) duplicateEntry;

/* Invalid remote path set for KiiFile. Must be of form:  /root/path/subpath    */
+ (NSError*) invalidRemotePath;

/* Unable to delete object from cloud */
+ (NSError*) unableToDeleteObject;

/* Invalid KiiObject - the class name contains one or more spaces */
+ (NSError*) invalidObjectType;

/* Unable to set an object as a child of itself */
+ (NSError*) unableToSetObjectToItself;

/* The key of the object being set is a preferred key, please try a different key */
+ (NSError*) invalidAttributeKey;

/* The container you are trying to operate on does not exist */
+ (NSError*) invalidContainer;

/* The object you are trying to operate on does not exist */
+ (NSError*) objectNotFound;

/* The URI provided is invalid */
+ (NSError*) invalidURI;

/* The group name provided is not valid. Ensure it is alphanumeric and more than 0 characters in length */
+ (NSError*) invalidGroupName;

/* At least one of the ACL entries saved to an object failed. Please note there may also have been one or more successful entries. */
+ (NSError*) partialACLFailure;

/* Bucket parent of the bucket(user/group) does not exist in the cloud. */
+ (NSError *)bucketParentNotExistInCloud;


/* Query Errors (6xx) */

/* No more query results exist */
+ (NSError*) noMoreResults;

/* Query limit set too high */
+ (NSError*) singleQueryLimitExceeded;

+ (NSError*) emptyQueryClauses;



/* Push Notification Errors (7xx) */

/*Push installation error. Installation already exist*/
+ (NSError*) installationAlreadyExist;

/* Push subscription already exist */
+ (NSError*) subscriptionAlreadyExist;

/*Push subscription does not exist*/
+ (NSError*) subscriptionNotExist;

/* Topic already exists */
+ (NSError*) topicAlreadyExist;

/* Topic does not exist */
+ (NSError*) topicNotExist;

/* invalid push message data */
+ (NSError*) invalidPushMessageData;

/* APNS field is required */
+ (NSError*) apnsFieldRequired;

/* Push data is required */
+ (NSError*) pushDataRequired;

/* Device token is not set*/
+ (NSError*) deviceTokenNotSet;

/* Installation does not exist*/
+ (NSError*) installationNotFound;

/* Topic ID is invalid. Topic ID must be alphanumeric character and between 1-64 length.*/
+ (NSError*) invalidTopicID;

/* GCM payload key contains google reserved words.*/
+ (NSError*) containsGCMReservedKey;

/* Topic parent(user/group) does not exist in the cloud.*/
+ (NSError*) topicParentNotExistInCloud;

/* Resumable Transfer Errors (8xx) */

/* Resumable transfer object has already transferred completely*/
+ (NSError*) transferAlreadyCompleted ;

/* File has been modified during transfer*/
+ (NSError*) fileModifiedDuringTransfer;

/* File path is invalid, can not get the file attribute*/
+ (NSError*) cannotGetFileAttribute;

/* File does not exist*/
+ (NSError*) fileNotExist;

/* File path is a directory*/
+ (NSError*) filePathIsDirectory;

/* File size is 0 byte*/
+ (NSError*) fileSizeIsZeroByte;

/* Transfer is already suspended*/
+ (NSError*) transferAlreadySuspended;

/* Transfer is already terminated*/
+ (NSError*) transferAlreadyTerminated;

/* Transfer was suspended*/
+ (NSError*) transferWasSuspended;

/* Transfer was terminated*/
+ (NSError*) transferWasTerminated;

/* Transfer has already started*/
+ (NSError*) transferAlreadyStarted;

/* Object body integrity not assured. ClientHash must be same during transfer. */
+ (NSError *)objectBodyIntegrityNotAssured;

/* Object body range not satisfiable. Please try to transfer using another task. */
+ (NSError *)objectBodyRangeNotSatisfiable;

/* File path is not writable */
+ (NSError *)filePathIsNotWritable;

/* Invalid destination file, file range is not assured */
+ (NSError*) fileRangeNotValid;

/* Unable to operate transfer manager. The transfer manager can not operate since current user is nil or different from the user who instantiate. */
+ (NSError *)unableToOperateTransferManager;

@end
