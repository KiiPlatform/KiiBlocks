//
//  KiiUser.h
//  SampleApp
//
//  Created by Chris Beauchamp on 12/14/11.
//  Copyright (c) 2011 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiUser;
typedef void (^KiiUserBlock)(KiiUser *user, NSError *error);
typedef void (^KiiUserArrayBlock)(KiiUser *user, NSArray *results, NSError *error);
typedef void (^KiiErrorBlock)(NSError *error);


/** Contains user profile/account information and methods
 
 The user class allows an application to generate a user, register them with the server and log them in during subsequent sessions. Since KiiUser is similar to <KiiObject>, the application can also set key/value pairs to this user.
 */

@class KiiBucket, KiiFileBucket, KiiTopic;
@interface KiiUser : NSObject

/** The unique id of the KiiUser object, assigned by the server */
@property (readonly) NSString *uuid;

/** Username to use for authentication or for display. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_' and periods '.' */
@property (readonly) NSString *username;

/** Display name for this user. Cannot be used for logging a user in; is non-unique. */
@property (nonatomic, strong) NSString *displayName;

/** Email address to use for authentication or for display */
@property (readonly) NSString *email;

/** Phone number to use for authentication or for display */
@property (readonly) NSString *phoneNumber;

/** The country code associated with this user */
@property (nonatomic, strong) NSString *country;

/** Whether or not a user has validated their email address. This field is assigned by the server. */
@property (readonly) BOOL emailVerified;

/** Whether or not a user has validated their phone number. This field is assigned by the server. */
@property (readonly) BOOL phoneVerified;

/** The date the user was created on the server */
@property (strong, readonly) NSDate *created;

/** The date the user was last modified on the server */
@property (strong, readonly) NSDate *modified;

/** Get a specifically formatted string referencing the user. The user must exist in the cloud (have a valid UUID). */
@property (strong, readonly) NSString *objectURI;

/** The access token for the user - only available if the user is currently logged in. */
@property (strong, readonly) NSString *accessToken;


/** Create a user object to prepare for registration with credentials pre-filled
 Creates an pre-filled user object for manipulation. This user will not be authenticated until one of the authentication methods are called on it. Custom fields can be added to it before it is registered or authenticated.
 @param userUsername The user's desired username. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_', dashes '-' and periods '.'
 @param userPassword The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @return a working KiiUser object
 */
+ (KiiUser*) userWithUsername:(NSString*)userUsername
                  andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param phoneNumber The user's phone number
 @param userPassword The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @return a working KiiUser object
 */
+ (KiiUser*) userWithPhoneNumber:(NSString*)phoneNumber
                     andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param emailAddress The user's email address
 @param userPassword The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @return a working KiiUser object
 */
+ (KiiUser*) userWithEmailAddress:(NSString*)emailAddress
                      andPassword:(NSString*)userPassword;



/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param userUsername The user's desired username. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_', dashes '-' and periods '.'
 @param phoneNumber The user's phone number
 @param userPassword The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @return a working KiiUser object
 */
+ (KiiUser*) userWithUsername:(NSString*)username
               andPhoneNumber:(NSString*)phoneNumber
                  andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param userUsername The user's desired username. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_', dashes '-' and periods '.'
 @param emailAddress The user's email address
 @param userPassword The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @return a working KiiUser object
 */
+ (KiiUser*) userWithUsername:(NSString*)username
              andEmailAddress:(NSString*)emailAddress
                  andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param emailAddress The user's email address
 @param phoneNumber The user's phone number
 @param userPassword The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @return a working KiiUser object
 */
+ (KiiUser*) userWithEmailAddress:(NSString*)emailAddress
                   andPhoneNumber:(NSString*)phoneNumber
                      andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param userUsername The user's desired username. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_', dashes '-' and periods '.'
 @param emailAddress The user's email address
 @param phoneNumber The user's phone number
 @param userPassword The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @return a working KiiUser object
 */
+ (KiiUser*) userWithUsername:(NSString*)username
              andEmailAddress:(NSString*)emailAddress
               andPhoneNumber:(NSString*)phoneNumber
                  andPassword:(NSString*)userPassword;


/** Create a KiiUser that references an existing user
 
 @param uri A user-specific URI
 @return a working KiiUser
 */
+ (KiiUser*) userWithURI:(NSString*)uri;



/** Asynchronously authenticates a user with the server using local phone number, country code and password
 
 Authenticates a user with the server. This method is non blocking.
 
 Example:
        [KiiUser authenticateWithLocalPhoneNumber:@"9812345"
            andPassword:@"mypassword"
            andCountryCode:@"US"
            andBlock:^(KiiUser *user, NSError *error) {
                if(error == nil) {
                NSLog(@"Authenticated user: %@", user);
                }
 
        }];
 
 @param phoneNumber local phone number, it must be numeric and at least 7 digit
 @param password The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param countryCode 2 digits phone contry code, it must be capital letters
 @param block The block to be called upon method completion. See example
 */
+ (void) authenticateWithLocalPhoneNumber:(NSString*)phoneNumber
                              andPassword:(NSString*)password
                           andCountryCode:(NSString*)countryCode
                                 andBlock:(KiiUserBlock)block;

/** Synchronously authenticates a user with the server using local phone number, country code and password
 
 Authenticates a user with the server. This method is blocking.
 @param phoneNumber local phone number, it must be numeric and at least 7 digit
 @param password The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param countryCode 2 digits phone contry code, it must be capital letters
 @param error An NSError object, set to nil, to test for errors
 @return The KiiUser object that was authenticated. NULL if failed to authenticate
 */
+ (KiiUser*) authenticateWithLocalPhoneNumberSynchronous:(NSString*)phoneNumber
                                             andPassword:(NSString*)password
                                          andCountryCode:(NSString*)countryCode
                                                andError:(NSError**)error;
/** Asynchronously authenticates a user with the server using local phone number, country code and password
 
 Authenticates a user with the server. This method is non blocking.
 @param phoneNumber local phone number, it must be numeric and at least 7 digit
 @param password The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param countryCode 2 digits phone contry code, it must be capital letters
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) authenticationComplete:(KiiUser*)user withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
        // do something with the user
        }
 
        else {
        // there was a problem
        }
    }
 */
+ (void) authenticateWithLocalPhoneNumber:(NSString*)phoneNumber
                              andPassword:(NSString*)password
                           andCountryCode:(NSString*)countryCode
                              andDelegate:(id)delegate
                              andCallback:(SEL)callback;


/** Asynchronously authenticates a user with the server
 
 Authenticates a user with the server. This method is non-blocking.
 
     [KiiUser authenticate:@"myusername" withPassword:@"mypassword" andBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"Authenticated user: %@", user);
         }
     }];
 
 @param userIdentifier Can be a username or a verified phone number or a verified email address
 @param password The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param block The block to be called upon method completion. See example
 
 */
+ (void) authenticate:(NSString*)userIdentifier
         withPassword:(NSString*)password
             andBlock:(KiiUserBlock)block;

/** Asynchronously authenticates a user with the server
 
 Authenticates a user with the server. This method is non-blocking.
 @param userIdentifier Can be a username or a verified phone number or a verified email address
 @param password The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) authenticationComplete:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
+ (void) authenticate:(NSString*)userIdentifier
         withPassword:(NSString*)password
          andDelegate:(id)delegate
          andCallback:(SEL)callback;


/** Synchronously authenticates a user with the server
 
 Authenticates a user with the server. This method is blocking.
 @param userIdentifier Can be a username or a verified phone number or a verified email address
 @param password The user's password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param error An NSError object, set to nil, to test for errors
 @return The KiiUser object that was authenticated. NULL if failed to authenticate
 */
+ (KiiUser*) authenticateSynchronous:(NSString*)userIdentifier
                        withPassword:(NSString*)password
                            andError:(NSError**)error;



/** Asynchronously authenticates a user with the server using a valid access token
 
 Authenticates a user with the server. This method is non-blocking.
 
    [KiiUser authenticateWithToken:@"my-user-token"
                          andBlock:^(KiiUser *user, NSError *error) {
        if(error == nil) {
            NSLog(@"Authenticated user: %@", user);
        }
     }];

 @param accessToken A valid access token associated with the desired user
 @param block The block to be called upon method completion. See example
*/
+ (void) authenticateWithToken:(NSString *)accessToken
                      andBlock:(KiiUserBlock)block;

/** Asynchronously authenticates a user with the server using a valid access token
 
 Authenticates a user with the server. This method is non-blocking.
 @param accessToken A valid access token associated with the desired user
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) authenticationComplete:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
     
         else {
             // there was a problem
         }
     }
 
 */
+ (void) authenticateWithToken:(NSString*)accessToken
                   andDelegate:(id)delegate
                   andCallback:(SEL)callback;


/** Synchronously authenticates a user with the server using a valid access token
 
 Authenticates a user with the server. This method is blocking.
 @param accessToken A valid access token associated with the desired user
 @param error An NSError object, set to nil, to test for errors
 @return The KiiUser object that was authenticated. NULL if failed to authenticate
 */
+ (KiiUser*) authenticateWithTokenSynchronous:(NSString*)accessToken
                                     andError:(NSError**)error;



/** Asynchronously registers a user object with the server
 
 Registers a user with the server. The user object must have an associated email/password combination. This method is non-blocking.
 
     [u performRegistrationWithBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"Registered user: %@", user);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) performRegistrationWithBlock:(KiiUserBlock)block;


/** Asynchronously registers a user object with the server
 
 Registers a user with the server. The user object must have an associated email/password combination. This method is non-blocking.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) registrationComplete:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
     
         else {
             // there was a problem
         }
     }
 
 */
- (void) performRegistration:(id)delegate withCallback:(SEL)callback;


/** Synchronously registers a user object with the server
 
 Registers a user with the server. The user object must have an associated email/password combination. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) performRegistrationSynchronous:(NSError**)error;



/** Asynchronously update a user's password on the server
 
 Update a user's password with the server. The fromPassword must be equal to the current password associated with the account in order to succeed. This method is non-blocking.
 
    [user updatePassword:@"current_password" 
                      to:@"new_password"
               withBlock:^(KiiUser *user, NSError *error) {
        if(error == nil) {
            NSLog(@"Updated user password: %@", user);
         }
     }];
 
 @param fromPassword The user's current password
 @param toPassword The user's desired password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param block The block to be called upon method completion. See example
*/
- (void) updatePassword:(NSString*)fromPassword
                     to:(NSString*)toPassword
              withBlock:(KiiUserBlock)block;

/** Asynchronously update a user's password on the server
 
 Update a user's password with the server. The fromPassword must be equal to the current password associated with the account in order to succeed. This method is non-blocking.
 @param fromPassword The user's current password
 @param toPassword The user's desired password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) passwordUpdateComplete:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) updatePassword:(NSString*)fromPassword
                     to:(NSString*)toPassword
           withDelegate:(id)delegate
            andCallback:(SEL)callback;


/** Synchronously update a user's password on the server
 
 Update a user's password with the server. The fromPassword must be equal to the current password associated with the account in order to succeed. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 @param fromPassword The user's current password
 @param toPassword The user's desired password. Password must be 4-50 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and &.
 */
- (void) updatePasswordSynchronous:(NSError**)error
                              from:(NSString*)fromPassword
                                to:(NSString*)toPassword;



/** Asynchronously reset a user's password on the server.
 
 Reset a user's password on the server. The user is determined by the specified email address that has already been associated with an account. Reset instructions will be sent to that email address. This method is non-blocking.

 
     [KiiUser resetPassword:@"myemail@address.com"
                  withBlock:^(NSError *error) {
         if(error == nil) {
             NSLog(@"Reset user password!");
         }
     }];

 @param userIdentifier The email address which the account is associated with.
 @param block The block to be called upon method completion. See example.
*/
+ (void) resetPassword:(NSString*)userIdentifier withBlock:(KiiErrorBlock)block;

/** Asynchronously reset a user's password on the server.
 
 Reset a user's password on the server. The user is determined by the specified email address that has already been associated with an account. Reset instructions will be sent to that email address. This method is non-blocking.
 @param userIdentifier The email address which the account is associated with.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) passwordResetComplete:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
+ (void) resetPassword:(NSString*)userIdentifier
          withDelegate:(id)delegate
           andCallback:(SEL)callback;


/** Synchronously reset a user's password on the server.
 
 Reset a user's password on the server.The user is determined by the specified email address that has already been associated with an account. Reset instructions will be sent to that email address. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 @param userIdentifier The email address which the account is associated with.
 */
+ (void) resetPasswordSynchronous:(NSError**)error
               withUserIdentifier:(NSString*)userIdentifier;


/** Asynchronously verify the current user's phone number
 
 This method is used to verify the phone number of the currently logged in user. This is a non-blocking method.

     [u verifyPhoneNumber:@"verification_code"
                withBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"Verification complete!");
         }
     }];

 @param code The code which verifies the currently logged in user
 @param block The block to be called upon method completion. See example
*/
- (void) verifyPhoneNumber:(NSString*)code withBlock:(KiiUserBlock)block;

/** Synchronously verify the current user's phone number
 
 This method is used to verify the phone number of the currently logged in user. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 @param code The code which verifies the currently logged in user
 */
// TODO - change method name to end with 'synchronous'
- (void) verifyPhoneNumber:(NSError**)error
                  withCode:(NSString*)code;


/** Asynchronously verify the current user's phone number
 
 This method is used to verify the phone number of the currently logged in user. This is a non-blocking method.
 @param code The code which verifies the currently logged in user
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) verificationComplete:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) verifyPhoneNumber:(NSString*)code
              withDelegate:(id)delegate
               andCallback:(SEL)callback;


/** Asynchronously resend the email verification
 
 This method is used to resend the email verification for the currently logged in user. This is a non-blocking method.
 
     [u resendEmailVerificationWithBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"Email verification resent!");
         }
     }];

 @param block The block to be called upon method completion. See example
*/
- (void) resendEmailVerificationWithBlock:(KiiUserBlock)block;

/** Synchronously resend the email verification
 
 This method will re-send the email verification to the currently logged in user. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) resendEmailVerificationSynchronous:(NSError**)error;


/** Asynchronously resend the email verification
 
 This method is used to resend the email verification for the currently logged in user. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) verificationCodeReSent:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) resendEmailVerification:(id)delegate
                     andCallback:(SEL)callback;




/** Asynchronously resend the phone number verification
 
 This method is used to re-send the SMS verification for the currently logged in user. This is a non-blocking method.
 
     [u resendPhoneNumberVerificationWithBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"SMS verification resent!");
         }
     }];
 
 @param block The block to be called upon method completion. See example
 */
- (void) resendPhoneNumberVerificationWithBlock:(KiiUserBlock)block;

/** Synchronously resend the phone number verification
 
 This method will re-send the SMS verification to the currently logged in user. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) resendPhoneNumberVerificationSynchronous:(NSError**)error;


/** Asynchronously resend the phone number verification
 
 This method is used to resend the phone number verification for the currently logged in user. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) verificationCodeReSent:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) resendPhoneNumberVerification:(id)delegate
                           andCallback:(SEL)callback;



/** Asynchronously gets a list of groups which the user is a member of
 
 This is a non-blocking method.
 
     [u memberOfGroupsWithBlock:^(KiiUser *user, NSArray *results, NSError *error) {
         if(error == nil) {
             NSLog(@"User %@ is member of groups: %@", user, results);
         }
     }];

 @param block The block to be called upon method completion. See example
*/
- (void) memberOfGroupsWithBlock:(KiiUserArrayBlock)block;

/** Synchronously gets a list of groups which the user is a member of
 
 This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 @return An array of <KiiGroup> objects
 */
- (NSArray*) memberOfGroupsSynchronous:(NSError**)error;


/** Asynchronously gets a list of groups which the user is a member of
 
 This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userIsMember:(KiiUser*)user ofGroups:(NSArray*)groups withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             
             // do something with the user's groups
             for(KiiGroup *g in groups) {
                 // do something with the group
             }
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) memberOfGroups:(id)delegate andCallback:(SEL)callback;

/** Get or create a bucket at the user level
 
 @param bucketName The name of the bucket you'd like to use
 @return An instance of a working <KiiBucket>
 */
- (KiiBucket*) bucketWithName:(NSString*)bucketName;


/** Get or create a file bucket at the user level
 
 @param bucketName The name of the file bucket you'd like to use
 @return An instance of a working <KiiFileBucket>
 */
- (KiiFileBucket*) fileBucketWithName:(NSString*)bucketName;

/** Get or create a Push notification topic at the user level
 
 @param topicName The name of the topic you'd like to use. It has to match the pattern ^[A-Za-z0-9_-]{1,64}$, that is letters, numbers, '-' and '_' and non-multibyte characters with a length between 1 and 64 characters.
 @return An instance of a working <KiiTopic>
 */
- (KiiTopic*) topicWithName:(NSString*)topicName;


/** Asynchronously updates the local user's data with the user data on the server
 
 The user must exist on the server. Local data will be overwritten.
 
     [u refreshWithBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"User refreshed: %@", user);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) refreshWithBlock:(KiiUserBlock)block;

/** Asynchronously updates the local user's data with the user data on the server
 
 The user must exist on the server. Local data will be overwritten.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userRefreshed:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) refresh:(id)delegate withCallback:(SEL)callback;


/** Synchronously updates the local user's data with the user data on the server
 
 The user must exist on the server. Local data will be overwritten. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) refreshSynchronous:(NSError**)error;


/** Asynchronously saves the latest user values to the server
 
 The user must exist in order to make this method call. If the user does exist, the application-specific fields that have changed will be updated accordingly. This is a non-blocking method.
 
     [u saveWithBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"User saved: %@", user);
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) saveWithBlock:(KiiUserBlock)block;

/** Asynchronously saves the latest user values to the server
 
 The user must exist in order to make this method call. If the user does exist, the application-specific fields that have changed will be updated accordingly. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userSaved:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) save:(id)delegate withCallback:(SEL)callback;


/** Synchronously saves the latest user values to the server
 
 The user must exist in order to make this method call. If the user does exist, the application-specific fields that have changed will be updated accordingly. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) saveSynchronous:(NSError**)error;


/** Asynchronously deletes the user from the server
 
 The user must exist on the server for this method to execute properly. This is a non-blocking method.
 
     [u deleteWithBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"User deleted!");
         }
     }];
 
 @param block The block to be called upon method completion. See example
*/
- (void) deleteWithBlock:(KiiUserBlock)block;

/** Asynchronously deletes the user from the server
 
 The user must exist on the server for this method to execute properly. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userDeleted:(KiiUser*)user withError:(NSError*)error {
         
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


/** Synchronously deletes the user from the server
 
 The user must exist on the server for this method to execute properly. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) deleteSynchronous:(NSError**)error;


/** Prints the contents of this user to log
 
 For developer purposes only, this method prints the user in a readable format to the log for testing.
 */
- (void) describe;



/** Sets a key/value pair to a KiiUser
 
 If the key already exists, its value will be written over. If the object is of invalid type, it will return false and an NSError will be thrown (quietly). Accepted types are any JSON-encodable objects.
 @param object The value to be set. Object must be of a JSON-encodable type (Ex: NSDictionary, NSArray, NSString, NSNumber, etc)
 @param key The key to set. The key must not be a system key (created, metadata, modified, type, uuid) or begin with an underscore (_)
 @return True if the object was set, false otherwise.
 */
- (BOOL) setObject:(id)object forKey:(NSString*)key;


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


/** Updates the user's email address on the server
 
 This is a non-blocking method.
 
     [u changeEmail:@"mynewemail@address.com" withBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"Email changed for user: %@", user);
         }
     }];
 
 @param newEmail The new email address to change to
 @param block The block to be called upon method completion. See example
*/
- (void) changeEmail:(NSString*)newEmail withBlock:(KiiUserBlock)block;

/** Updates the user's email address on the server
 
 This is a non-blocking method.
 @param newEmail The new email address to change to
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) emailChanged:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
 
     }
 **/
- (void) changeEmail:(NSString*)newEmail withDelegate:(id)delegate andCallback:(SEL)callback;


/** Updates the user's email address on the server
 
 This is a blocking method.
 @param newEmail The new email address to change to
 @param error An NSError object, set to nil, to test for errors
 **/
- (void) changeEmailSynchronous:(NSString*)newEmail withError:(NSError**)error;

/** Updates the user's phone number on the server
 
 This is a non-blocking method.
 
     [u changePhone:@"mynewphonenumber" withBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
             NSLog(@"Phone changed for user: %@", user);
         }
     }];
 
 @param newPhoneNumber The new phone number to change to
 @param block The block to be called upon method completion. See example
*/
- (void) changePhone:(NSString*)newPhoneNumber withBlock:(KiiUserBlock)block;

/** Updates the user's phone number on the server
 
 This is a non-blocking method.
 @param newPhoneNumber The new phone number to change to
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) phoneChanged:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
 
     }
 **/
- (void) changePhone:(NSString*)newPhoneNumber withDelegate:(id)delegate andCallback:(SEL)callback;


/** Updates the user's phone number on the server
 
 This is a blocking method.
 @param newPhoneNumber The new phone number to change to
 @param error An NSError object, set to nil, to test for errors
 **/
- (void) changePhoneSynchronous:(NSString*)newPhoneNumber withError:(NSError**)error;


/** Logs the currently logged-in user out of the KiiSDK */
+ (void) logOut;


/** Determines whether or not there is a KiiUser currently logged in
 @return TRUE if an authenticated user exists, FALSE otherwise
 */
+ (BOOL) loggedIn;


/** Get the currently logged-in user
 @return A KiiUser object representing the current user, nil if no user is logged-in
 */
+ (KiiUser*) currentUser;


//search functionality


/** Find user by username asynchronously using block
 This is a non-blocking method.
 
     [u findUserByUsername:@"user_to_found" withBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
         NSLog(@"Found user: %@", user);
         }
     }];
 
 @param username the username of user that want to be discovered
 @param block The block to be called upon method completion. See example
 */
+(void)  findUserByUsername:(NSString*) username withBlock:(KiiUserBlock) block;



/** Find user by user e mail address asynchronously using block
 This is a non-blocking method. This method can only get user that has verified email.
 
     [u findUserByEmail:@"email_to_found" withBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
         NSLog(@"Found user: %@", user);
         }
     }];
 
 @param email the email address of user that want to be discovered. User can only find specific user from email that has been verified.
 @param block The block to be called upon method completion. See example 
 */
+(void) findUserByEmail:(NSString*) emailAddress  withBlock:(KiiUserBlock) block;


/** Find user by user phone asynchronously using block
 This is a non-blocking method.  This method can only get user that has verified phone number.
 
     [u findUserByPhone:@"phoneNumber_to_found" withBlock:^(KiiUser *user, NSError *error) {
         if(error == nil) {
         NSLog(@"Found user: %@", user);
         }
     }];
 

 
 @param phoneNumber the global phone number of user that want to be discovered. Do not pass local phone number, it is not supported. User can only find specific user from phone number that has been verified.
 @param block The block to be called upon method completion. See example
 */
+(void) findUserByPhone:(NSString*) phoneNumber  withBlock:(KiiUserBlock) block;

/** Find user by username asynchronously using delegate and callback
  This is a non-blocking method.
 @param username the username of user that want to be discovered 
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userFound:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
         // do something with the user
         }
         
         else {
         // there was a problem
         }
     
     }
 */
+(void) findUserByUsername:(NSString*) username withDelegate :(id) delegate andCallback:(SEL) callback;



/** Find user by user e mail address asynchronously using delegate and callback
 This is a non-blocking method. This method can only get user that has verified email.
 
 @param email the email address of user that want to be discovered. User can only find specific user from email that has been verified.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
     
     - (void) userFound:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
         // do something with the user
         }
         
         else {
         // there was a problem
         }
     
     }
 */
+(void)  findUserByEmail:(NSString*) emailAddress  withDelegate :(id) delegate andCallback:(SEL) callback;




/** Find user by user phone asynchronously using delegate and callback
 This is a non-blocking method.  This method can only get user that has verified phone number.
 @param phoneNumber the global phone number of user that want to be discovered. Do not pass local phone number, it is not supported. User can only find specific user from phone number that has been verified.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userFound:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
         // do something with the user
         }
         
         else {
         // there was a problem
         }
     
     }
 */
+(void)  findUserByPhone:(NSString*) phoneNumber  withDelegate :(id) delegate andCallback:(SEL) callback;



/** Find user by username synchronously
  This is a blocking method. 
 
 @param username the username of user that want to be discovered
 @param error An NSError object, set to nil, to test for errors
 */
+(KiiUser*) findUserByUsernameSynchronous:(NSString*) username withError:(NSError**) error;



/** Find user by user e mail address synchronously
 This is a blocking method. This method can only get user that has verified email.
 
 @param email the email address of user that want to be discovered. User can only find specific user from email that has been verified.
 @param error An NSError object, set to nil, to test for errors
 */
+(KiiUser*) findUserByEmailSynchronous:(NSString*) emailAddress withError:(NSError**) error;



/** Find user by user phone synchronously
 This is a blocking method. This method can only get user that has verified phone number.
 
 @param phoneNumber the global phone number of user that want to be discovered. Do not pass local phone number, it is not supported. User can only find specific user from phone number that has been verified.
 @param error An NSError object, set to nil, to test for errors
 */
+(KiiUser*) findUserByPhoneSynchronous:(NSString*) phoneNumber withError:(NSError**) error;



/** Asynchronously gets the groups owned by this user.
 Group in the returned array does not contain all the property of group. To get all the
 property from cloud, a <[KiiGroup refresh]> is necessary.
 This method is non-blocking.
 
 [u ownerOfGroupsWithBlock:^(KiiUser *user, NSArray *results, NSError *error) {
 if(error == nil) {
 NSLog(@"User %@ is owner of groups: %@", user, results);
 }
 }];

 
 @param block The block to be called upon method completion. See example.
 */
- (void) ownerOfGroupsWithBlock:(KiiUserArrayBlock)block;

/**
 Synchronously gets groups owned by this user. Group in
 the returned array does not contain all the property of group. To get all the
 property from cloud, a <[KiiGroup refresh]> is necessary.This method is blocking.
 @param error An NSError object, set to nil, to test for errors.
 @return An NSArray Array of groups owned by the user.
 */
- (NSArray*) ownerOfGroupsSynchronous:(NSError**)error;


@end
