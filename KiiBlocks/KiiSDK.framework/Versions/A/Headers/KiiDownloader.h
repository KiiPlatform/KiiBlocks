//
//  KiiDownloader.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 4/30/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KiiRTransfer.h"
#import "KiiResumableTransfer.h"

/** Implementation of resumable transfer operation.
 This operation is only supported with localpath, if the KiiFile object that produce the downloader has NSData value, it will not be used.
 */
@interface KiiDownloader : KiiResumableTransfer<KiiRTransfer>

/** @name Get local file path */

/** Get local file path that is used by the downloader.
 @return A string value of local file path that is used by the downloader.
 */
-(NSString*) localPath;
@end
