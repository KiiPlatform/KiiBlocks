//
//  KiiPushInstallation.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 1/21/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiPushInstallation;
/** Block type for Kii Push installation*/
typedef void (^KiiPushCallbackBlock)(KiiPushInstallation *installation, NSError *error);


/** Install APNS feature on user scope*/
@interface KiiPushInstallation : NSObject



/** Asynchronously install APNS feature.
Install APNS using deviceToken captured by Kii +(void) setAPNSDeviceToken. This method is non-blocking method.
 
    [KiiPushInstallation installWithBlock:^(KiiPushInstallation *installation, NSError *error) {
        // do something with the result
    }];
 
 @param completion Block for installation process
 */
+(void) installWithBlock:(KiiPushCallbackBlock) completion;

/** Asynchronously install APNS feature.
 Install asynchronously using delegate and callback. This method is non-blocking.
 
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
        - (void)installCompleted:(KiiPushInstallation *installation, NSError *error) {
            if (nil == error) {
                NSLog(@" Installation succeeded");
            }
        }
 */
+(void)install:(id) delegate withCallback:(SEL) callback;

/** Synchronously installs APNS feature.
  Install APNS using deviceToken captured by Kii +(void) setAPNSDeviceToken. This method is blocking method.

 @param error An NSError object, set to nil, to test for errors
 */
+(KiiPushInstallation*)installSynchronous:(NSError**) error;


/** Asynchronously uninstall APNs feature.
 Uninstall APNs using deviceToken captured by Kii +(void) setAPNSDeviceToken.
 This method is non-blocking method.

[KiiPushInstallation uninstallWithBlock:^(KiiPushInstallation *uninstallation, NSError *error) {
    // do something with the result
    if (error == nil) {
        NSLog(@" Uninstallation succeeded");
    }
}];

@param completion Block for uninstallation process
 */
+(void) uninstallWithBlock:(KiiPushCallbackBlock) completion;

/** Synchronously uninstall APNs feature.
 Uninstall APNs using deviceToken captured by Kii +(void) setAPNSDeviceToken.
 This method is blocking method.

 @param error An NSError object, set to nil, to test for errors
 */
+(KiiPushInstallation*)uninstallSynchronous:(NSError**) error;

@end
