//
//  KiiFileRequest.h
//  KiiSDK-Private
//
//  Created by rahman moshiur on 7/11/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import "KiiRequest.h"

@interface KiiFileRequest : KiiRequest

@property (nonatomic, assign) BOOL isFileUpload;
- (id) initWithPath:(NSString*)path;
@end
