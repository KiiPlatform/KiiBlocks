//
//  GeoPoint.h
//  KiiSDK-Private
//
//  Created by rahman moshiur on 5/16/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KiiGeoPoint : NSObject

/** latitude of this point. */
@property (readonly) double latitude;
/** longitude of this point. */
@property (readonly) double longitude;
/**
 Create an instance of GeoPoint with the given latitude and longitude.
 throws NSInvalidArgumentException when the given lat/ lon is out of range.
 @param lat of the point in degrees. Valid if the value is greater than -90 degrees and less than +90 degrees.
 @param lon of the point in degrees. Valid if the value is greater than -180 degrees and less than +180 degrees.
 */
- (KiiGeoPoint*) initWithLatitude:(double)lat andLongitude:(double) lon;

/**
 Return true when both latitude and longitude of the specified object are equal to this one.
 @param other object that will be compared to this.
 @return true if the given object is equal to this, false otherwise.
 */
- (BOOL)isEqual: (id)other;
- (NSUInteger)hash;
@end
