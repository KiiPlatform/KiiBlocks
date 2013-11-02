//
//  Kii.h
//  SampleApp
//
//  Created by Chris Beauchamp on 12/11/11.
//  Copyright (c) 2011 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "KiiBucket.h"
#import "KiiError.h"
#import "KiiObject.h"
#import "KiiUser.h"
#import "KiiGroup.h"
#import "KiiFile.h"
#import "KiiFileBucket.h"
#import "KiiUtilities.h"
#import "KiiRequest.h"
#import "KiiClause.h"
#import "KiiQuery.h"
#import "KiiAnyAuthenticatedUser.h"
#import "KiiAnonymousUser.h"
#import "KiiACL.h"
#import "KiiACLEntry.h"
#import "KiiSocialConnect.h"
#import "KiiPushInstallation.h"
#import "KiiTopic.h"
#import "KiiPushMessage.h"
#import "KiiAPNSFields.h"
#import "KiiGCMFields.h"
#import "KiiRTransfer.h"
#import "KiiUploader.h"
#import "KiiRTransferManager.h"
#import "KiiResumableTransfer.h"
#import "KiiRTransferInfo.h"
#import "KiiDownloader.h"
#import "KiiBaseBucket.h"
#import "KiiServerCodeEntry.h"
#import "KiiServerCodeEntryArgument.h"


@class KiiFile, KiiUser, KiiBucket, KiiGroup;

enum {
    kiiSiteUS,
    kiiSiteJP,
    kiiSiteCN
};
typedef NSUInteger KiiSite;


/** The main SDK class
 
 This class must be initialized on application launch using <beginWithID:andKey:>. This class also allows the application to make some high-level user calls and access some application-wide data at any time using static methods.
 */
@interface Kii : NSObject


/** Initialize the Kii SDK
 
 Defaults to the US deployment. Should reside in applicationDidFinishLaunching:withResult:
 @param appId The application ID found in your Kii developer console
 @param appKey The application key found in your Kii developer console
 */
+ (void) beginWithID:(NSString*)appId andKey:(NSString*)appKey;

/** Initialize the Kii SDK
 
 Should reside in applicationDidFinishLaunching:withResult:
 If Kii has provided a custom URL, use this initializer to set it
 @param appId The application ID found in your Kii developer console
 @param appKey The application key found in your Kii developer console
 @param kiiSite One of the enumerator constants kiiSiteUS (United States), kiiSiteJP (Japan) or kiiSiteCN (China), based on your desired location.
 */
+ (void) beginWithID:(NSString*)appId andKey:(NSString*)appKey andSite:(KiiSite)kiiSite;
+ (void) beginWithID:(NSString*)appId andKey:(NSString*)appKey andCustomURL:(NSString*)customURL;


/** Get or create a bucket at the application level
 
 @param bucketName The name of the bucket you'd like to use
 @return An instance of a working <KiiBucket>
 */
+ (KiiBucket*) bucketWithName:(NSString*)bucketName;


/** Get a Topic at the application level
 Creation of App-scope topic is only supported by REST API calls, iOS SDK only has ability to get the app-scope topic object.
 
 @param TopicName The name of the topic you'd like to use. It has to match the pattern ^[A-Za-z0-9_-]{1,64}$, that is letters, numbers, '-' and '_' and non-multibyte characters with a length between 1 and 64 characters.
 @return An instance of a working <KiiTopic>
 */
+ (KiiTopic*) topicWithName:(NSString*)topicName;

/** Kii SDK Build Number
 @return An NSString object representing the current build number of the SDK
 */
+ (NSString*) getBuildNumber;

/** Kii SDK Version Number
 @return An NSString object representing the current version number of the SDK
 */
+ (NSString*) getSDKVersion;


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

+ (void) setLogLevel:(int)level;

/** Enable Kii APNS with APNS environment setting.
 @param isDevelopmentMode YES if APNS development environment mode or NO for production mode.
 @param types of ui remote notification type.
 */
+(void)enableAPNSWithDevelopmentMode:(BOOL) isDevelopmentMode
               andNotificationTypes:(UIRemoteNotificationType) types;

/** Set APNS device token it is called on AppDelegate's didRegisterForRemoteNotificationsWithDeviceToken
@param deviceToken device token that is given by APNS server.
 */
+(void) setAPNSDeviceToken:(NSData*) deviceToken;

/** Create KiiServerCodeEntry instance with the given entry name.
 @param entryName a specific entry name for this server code. Can not be nil and valid entryName pattern is "[a-zA-Z][_a-zA-Z0-9]*$"
 @return KiiServerCodeEntry instance.
 @exception NSInvalidArgumentException Thrown if given entryName is not valid.
 @exception KiiIllegalStateException Thrown if no user has logged in.
 */
+(KiiServerCodeEntry*)serverCodeEntry:(NSString*) entryName;

/** Create KiiServerCodeEntry instance with the given entry name and version name.
 @param entryName a specific entry name for this server code. Can not be nil and valid entryName pattern is "[a-zA-Z][_a-zA-Z0-9]*$" .
 @param version a string that represent version of the server code, must not nil or empty.
 @return KiiServerCodeEntry instance.
 @exception NSInvalidArgumentException Thrown if given entryName is not valid or version is nil/empty.
 @exception NSInvalidArgumentException Thrown if given version is nil or empty.
 @exception KiiIllegalStateException Thrown if no user has logged in.
 */
+(KiiServerCodeEntry*)serverCodeEntry:(NSString*) entryName withVersion:(NSString*) version;

@property(assign) BOOL isDevelopmentMode;

@end
