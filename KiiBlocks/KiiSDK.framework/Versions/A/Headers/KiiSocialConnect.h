//
//  KiiSocialConnect.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 7/3/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiSocialConnectNetwork;
@class KiiSCNFacebook;

typedef enum {
    kiiSCNFacebook,
    kiiSCNTwitter
} KiiSocialNetworkName;

/** An interface to link users to social networks
 
 The SDK currently support the following social networks (KiiSocialNetworkName constant):
  
 1. Facebook (kiiSCNFacebook)
 2. Twitter (kiiSCNTwitter)
 
 
*/
@interface KiiSocialConnect : NSObject;


/** Required method by KiiSocialNetwork
 
 This method must be placed in your AppDelegate file in order for the SNS to properly authenticate with KiiSocialConnect:

    // Pre iOS 4.2 support
    - (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
        return [KiiSocialConnect handleOpenURL:url];
    }
 
    // For iOS 4.2+ support
    - (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
                                           sourceApplication:(NSString *)sourceApplication 
                                                  annotation:(id)annotation {
        return [KiiSocialConnect handleOpenURL:url];
    }

 */
+ (BOOL) handleOpenURL:(NSURL*)url;


/** Set up a reference to one of the supported KiiSocialNetworks.
 
 The user will not be authenticated or linked to a <KiiUser>
 until one of those methods are called explicitly.
 @param network One of the supported KiiSocialNetworkName values.
 @param key The SDK key assigned by the social network provider. It should not be nil or empty.
 @param secret The SDK secret assigned by the social network provider. In case of Twitter, It should not be nil or empty.  
 @param options Extra options that can be passed to the SNS, this is not mandatory. Examples could be (Facebook) an NSDictionary of permissions to grant to the authenticated user. In case of twitter, options parameter will not be used, please set to nil.
 @exception NSInvalidParameterException will be thrown if key and/or secret is not valid (see description above).
 */
+ (void) setupNetwork:(KiiSocialNetworkName)network 
              withKey:(NSString*)key 
            andSecret:(NSString*)secret 
           andOptions:(NSDictionary*)options;


/** Log a user into the social network provided
 
 This will initiate the login process for the given network, which provides OAuth like Facebook/Twitter,
 will send the user to the Facebook/Twitter app for authentication. If the social network user has already linked with a KiiUser,
 that user will be used as signed user. Otherwise, KiiCloud creates a new user and link with the specified social network account.
 The network must already be set up via <setupNetwork:withKey:andSecret:andOptions:>
 @param network One of the supported KiiSocialNetworkName values
 @param options A dictionary of key/values to pass to KiiSocialConnect. Can be nil for Facebook but should not nil/empty for Twitter.
 
### Facebook
<table>
<thead>
<tr>
    <th>Key</th>
    <th>Value type</th>
    <th>Value</th>
    <th>Note</th>
</tr>
</thead>
<tbody>
<tr>
    <td>access_token</td>
    <td>NSString</td>
    <td>Access token of Facebook.</td>
    <td>If provided, KiiCloud uses this token while login using Facebook.</td>
</tr>
<tr>
    <td>access_token_expires</td>
    <td>NSDate</td>
    <td>Expire date of access token.</td>
    <td>Use for social network token validation.</td>
</tr>
<tr>
    <td>permissions</td>
    <td>NSDictionary</td>
    <td>Key-Value pairs of permissions defined by Facebook.</td>
    <td>Facebook : <a href="http://developers.facebook.com/docs/authentication/permissions">Facebook permissions</a>.</td>
</tr>
</tbody>
</table>

### Twitter
<table>
<thead>
<tr>
    <th>Key</th>
    <th>Value type</th>
    <th>Value</th>
    <th>Note</th>
</tr>
</thead>
<tbody>
<tr>
    <td>twitter_account</td>
    <td>ACAccount</td>
    <td>Twitter account that is obtained from account store.</td>
    <td>This is mandatory if "oauth_token" and "oauth_token_secret" are not provided.</td>
</tr>
<tr>
    <td>oauth_token</td>
    <td>NSString</td>
    <td>OAuth access token of twitter.</td>
    <td>This is mandatory if "twitter_account" is not provided.</td>
</tr>
<tr>
    <td>oauth_token_secret</td>
    <td>NSString</td>
    <td>OAuth access token secret of twitter.</td>
    <td>This is mandatory if "twitter_account" is not provided.</td>
</tr>
</tbody>
</table>

 @param delegate The object to make any callback requests to.
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) loggedIn:(KiiUser*)user usingNetwork:(KiiSocialNetworkName)network withError:(NSError*)error {
         
         // the process was successful - the user is now authenticated
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 @exception KiiIllegalStateException will be thrown if setupNetwork: is not called.
 @exception NSInvalidParameterException will be thrown if options is not valid (see description above).
 */
+ (void) logIn:(KiiSocialNetworkName)network usingOptions:(NSDictionary*)options withDelegate:(id)delegate andCallback:(SEL)callback;


/** Link the currently logged in user with a social network
 
 This will initiate the login process for the given network, which for SSO-enabled services like Facebook/Twitter, will send the user to the Facebook/Twitter app for authentication. There must be a currently authenticated <KiiUser>. Otherwise, you can use the logIn: method to create and log in a <KiiUser> using Facebook/Twitter. The network must already be set up via <setupNetwork:withKey:andSecret:andOptions:>
 @param network One of the supported KiiSocialNetworkName values.
 @param options A dictionary of key/values to pass to KiiSocialConnect. Can be nil for Facebook but should not nil/empty for Twitter.

### Facebook
<table>
<thead>
<tr>
    <th>Key</th>
    <th>Value type</th>
    <th>Value</th>
    <th>Note</th>
</tr>
</thead>
<tbody>
<tr>
    <td>access_token</td>
    <td>NSString</td>
    <td>Access token of Facebook.</td>
    <td>If provided, KiiCloud uses this token while login using Facebook.</td>
</tr>
<tr>
    <td>access_token_expires</td>
    <td>NSDate</td>
    <td>Expire date of access token.</td>
    <td>Use for social network token validation.</td>
</tr>
<tr>
    <td>permissions</td>
    <td>NSDictionary</td>
    <td>Key-Value pairs of permissions defined by Facebook.</td>
    <td>Facebook : <a href="http://developers.facebook.com/docs/authentication/permissions">Facebook permissions</a>.</td>
</tr>
</tbody>
</table>

### Twitter
<table>
<thead>
<tr>
    <th>Key</th>
    <th>Value type</th>
    <th>Value</th>
    <th>Note</th>
</tr>
</thead>
<tbody>
<tr>
    <td>twitter_account</td>
    <td>ACAccount</td>
    <td>Twitter account that is obtained from account store.</td>
    <td>This is mandatory if "oauth_token" and "oauth_token_secret" are not provided.</td>
</tr>
<tr>
    <td>oauth_token</td>
    <td>NSString</td>
    <td>OAuth access token of twitter.</td>
    <td>This is mandatory if "twitter_account" is not provided.</td>
</tr>
<tr>
    <td>oauth_token_secret</td>
    <td>NSString</td>
    <td>OAuth access token secret of twitter.</td>
    <td>This is mandatory if "twitter_account" is not provided.</td>
</tr>
</tbody>
</table>

 @param delegate The object to make any callback requests to.
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userLinked:(KiiUser*)user withNetwork:(KiiSocialNetworkName)network andError:(NSError*)error {
         
         // the process was successful - the user is now linked to the network
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 @exception KiiIllegalStateException will be thrown if setupNetwork: is not called.
 @exception NSInvalidParameterException will be thrown if options is not valid (see description above).
 */
+ (void) linkCurrentUserWithNetwork:(KiiSocialNetworkName)network
                       usingOptions:(NSDictionary*)options
                       withDelegate:(id)delegate
                        andCallback:(SEL)callback;


/** Unlink the currently logged in user from the social network.
 
 The network must already be set up via <setupNetwork:withKey:andSecret:andOptions:>
 @param network One of the supported KiiSocialNetworkName values.
 @param delegate The object to make any callback requests to.
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userUnLinked:(KiiUser*)user fromNetwork:(KiiSocialNetworkName)network withError:(NSError*)error {
         
         // the process was successful - the user is no longer linked to the network
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 @exception KiiIllegalStateException will be thrown if setupNetwork: is not called.
 */
+ (void) unLinkCurrentUserWithNetwork:(KiiSocialNetworkName)network
                         withDelegate:(id)delegate
                          andCallback:(SEL)callback;



/** Retrieve the current user's access token from a social network
 
 The network must be set up and linked to the current user. It is recommended you save this to preferences for multi-session use.
 @param network One of the supported KiiSocialNetworkName values.
 @return An NSString representing the access token, nil if none available.
 @warning This method is deprecated. Use <[KiiSocialConnect getAccessTokenDictionaryForNetwork:]> instead.
 */
+ (NSString*) getAccessTokenForNetwork:(KiiSocialNetworkName)network __attribute__((deprecated("Use [KiiSocialConnect getAccessTokenDictionaryForNetwork:] instead.")));

/** Retrieve the current user's access token expiration date from a social network
 
 The network must be set up and linked to the current user. It is recommended you save this to preferences for multi-session use.
 @param network One of the supported KiiSocialNetworkName values.
 @return An NSDate representing the access token's expiration date, nil if none available.
 @warning This method is deprecated. Use <[KiiSocialConnect getAccessTokenDictionaryForNetwork:]> instead.
 */
+ (NSDate*) getAccessTokenExpiresForNetwork:(KiiSocialNetworkName)network __attribute__((deprecated("Use [KiiSocialConnect getAccessTokenDictionaryForNetwork:] instead.")));

/** Retrieve the current user's access token object by NSDictionary from a social network

 The network must be set up and linked to the current user. It is recommended you save this to preferences for multi-session use.
 Following parameters can be assigned to NSDictionary's key.<br><br>

### Facebook
- access_token
- access_token_expires

###Twitter
- oauth_token
- oauth_token_secret

 @param network One of the supported KiiSocialNetworkName values.
 @return An NSDictionary representing the access token's object.
 */
+ (NSDictionary *)getAccessTokenDictionaryForNetwork:(KiiSocialNetworkName)network;

@end
