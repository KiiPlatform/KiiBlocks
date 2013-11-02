//
//  KiiAPNSFields.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 1/28/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
/** Class that encapsulate APNS message fields data structure
 */
@interface KiiAPNSFields : NSObject

/**String. Not required. encapsulation of loc-key key on APNS alert property*/
@property(nonatomic,strong) NSString* alertBody;	//String. Not required.

/**String. Not required. encapsulation of action-loc-key key on APNS alert property*/
@property(nonatomic,strong) NSString* alertActionLocKey;



/**String. Not required. encapsulation of loc-key key on APNS alert property*/
@property(nonatomic,strong) NSString* alertLocKey;	//String. Not required.

/**Array. Not required. encapsulation of loc-args key on APNS alert property*/
@property(nonatomic,strong) NSArray* alertLocArgs;	//JSON Array of values. Not required.

/**String. Not required. encapsulation of launch-image key on APNS alert property*/
@property(nonatomic,strong) NSString* alertLaunchImage;	//String. Not required.

/**String. Not required. encapsulation of sound key on APNS  property*/
@property(nonatomic,strong) NSString* sound;

/**Number. Not required. encapsulation of badge key on APNS  property*/
@property(nonatomic,strong) NSNumber* badge;


/** Define APNS specific metadata
 @param dict a Dictionary object contains one level json dictionary data
 */
-(void) setSpecificData:(NSDictionary*) dict;

/** generate output dictionary object
  @return dict a Dictionary object contains one level json dictionary data
 */
-(NSDictionary*) generateFields;

/** Field creation constructor, automatically set enabled = true to APNS Field
 */
+(KiiAPNSFields*) createFields;
@end
