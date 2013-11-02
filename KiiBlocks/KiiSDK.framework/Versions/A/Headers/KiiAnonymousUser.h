//
//  KiiAnonymousUser.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 8/20/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Represent an anonymous user for setting the ACL of an object.
 This will include anyone using the application but have not 
 signed up or authenticated as registered user.
 
 When retrieving ACL from an object, test for this class to 
 determine the subject type. Example:
 
    if([acl.subject isKindOfClass:[KiiAnonymousUser class]]) {
        // the ACL is set for anonymous users
    }
 */
@interface KiiAnonymousUser : NSObject

/** 
 Represent an anonymous user when setting an ACL
 
    KiiACLEntry *entryAnon = [KiiACLEntry entryWithSubject:[KiiAnonymousUser aclSubject] andAction:KiiACLFileActionRead];
    entryAnon.grant = TRUE;
    [objACL putACLEntry:entryAnon];
 */
+ (KiiAnonymousUser*) aclSubject;

@end
