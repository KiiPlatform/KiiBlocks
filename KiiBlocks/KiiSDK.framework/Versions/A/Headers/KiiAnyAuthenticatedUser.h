//
//  KiiAnyAuthenticatedUser.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 8/20/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Represent any authenticated user for setting the ACL of an object.
 This will include anyone using the application who has registered
 and authenticated in the current session.
 
 When retrieving ACL from an object, test for this class to
 determine the subject type. Example:
 
    if([acl.subject isKindOfClass:[KiiAnyAuthenticatedUser class]]) {
        // the ACL is set for any authenticated users
    }
 */
@interface KiiAnyAuthenticatedUser : NSObject

/**
 Represent any authenticated user when setting an ACL
 
    KiiACLEntry *entryAnon = [KiiACLEntry entryWithSubject:[KiiAnyAuthenticatedUser aclSubject] andAction:KiiACLFileActionRead];
    entry.grant = TRUE;
    [objACL putACLEntry:entryAnon];
 */
+ (KiiAnyAuthenticatedUser*) aclSubject;

@end
