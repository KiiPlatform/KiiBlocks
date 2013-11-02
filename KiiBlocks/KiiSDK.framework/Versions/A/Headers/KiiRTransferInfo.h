//
//  KiiRTransferInfo.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 3/21/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef enum {
    NOENTRY,
    ONGOING,
    SUSPENDED,
}KiiRTransferStatus;


/** Class that is encapsulated transfer information.
 <h3> Transfer info properties : </h3>
  - completedSizeInBytes
  - totalSizeInBytes
  - status (enum)
 
 <h3> enumeration value of "status" : </h3>
  - NOENTRY
  - ONGOING
  - SUSPENDED
 */
@interface KiiRTransferInfo : NSObject

/** Get a transfer completed size in bytes.
 @return NSUInteger completed size in bytes
 */
-(NSUInteger) completedSizeInBytes;

/** Get a transfer total size in bytes.
 @return NSUInteger total size in bytes.
 */
-(NSUInteger) totalSizeInBytes;

/** Get a transfer status.
 @return KiiRTransferStatus transfer status.
 */
-(KiiRTransferStatus) status;

@end
