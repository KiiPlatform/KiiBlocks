//
//  KiiIllegalStateException.h
//  KiiSDK-Private
//
//  Created by Ryuji OCHI on 7/9/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Thrown when Kii cloud user state is not valid.
 */
@interface KiiIllegalStateException : NSException

/** Return name of this exception.
 This method always return "KiiIllegalStateException".
 @return A NSString object of "KiiIllegalStateException".
 */
- (NSString *)name;

@end
