//
//  KiiCloudEntryArgument.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 6/25/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
/** Class for argument passed to the KiiServerCodeEntry.
 This class can not be instantiated by using init method.
 Calling [[KiiServerCodeEntryArgument alloc] init] directly will throw NSInternalInconsistencyException.
 */
@interface KiiServerCodeEntryArgument : NSObject

/** Instantiate new argument passed to the KiiServerCodeEntry.
 @param NSDictionary instance to represent JSON object argument, can not be nil.
 @return KiiServerCodeEntryArgument instance.
 @exception NSInvalidArgumentException Thrown if objectArgument is not valid.
 */
+(KiiServerCodeEntryArgument*) argumentWithDictionary:(NSDictionary*) objectArgument;
@end
