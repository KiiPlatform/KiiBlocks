//
//  KiiClause.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 7/23/12.
//  Copyright (c) 2012 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KiiGeoPoint.h"

@class KiiGeoPoint;
/**
 Build a query using one or more KiiClause methods
 */
@interface KiiClause : NSObject 

/** Create a KiiClause with the AND operator concatenating multiple KiiClause objects
 @param clause A nil-terminated list of KiiClause objects to concatenate
 */
+ (KiiClause*) and:(KiiClause*)clause, ...;

/** Create a KiiClause with the OR operator concatenating multiple KiiClause objects
 @param clause A nil-terminated list of KiiClause objects to concatenate
 */
+ (KiiClause*) or:(KiiClause*)clause, ...;

/** Create an expression of the form key = value
 @param key The key to compare
 @param value The value to compare
 */
+ (KiiClause*)equals:(NSString*)key value:(id)value; 

/** Create an expression of the form key > value
 @param key The key to compare
 @param value The value to compare
 */
+ (KiiClause*)greaterThan:(NSString*)key value:(id)value; 

/** Create an expression of the form key >= value
 @param key The key to compare
 @param value The value to compare
 */
+ (KiiClause*)greaterThanOrEqual:(NSString*)key value:(id)value; 

/** Create an expression of the form key < value
 @param key The key to compare
 @param value The value to compare
 */
+ (KiiClause*)lessThan:(NSString*)key value:(id)value; 

/** Create an expression of the form key <= value
 @param key The key to compare
 @param value The value to compare
 */
+ (KiiClause*)lessThanOrEqual:(NSString*)key value:(id)value; 

/** Create an expression of the form key in [ values[0], values[1], ... ]
 @param key The key to compare
 @param values The values to compare
 */
+ (KiiClause*)in:(NSString*)key value:(NSArray*)values; 

/** Create an expression of the form key != value
 @param key The key to compare
 @param value The value to compare
 */
+ (KiiClause*)notEquals:(NSString*)key value:(id)value; 

/** Create an expression of the form key STARTS WITH value
 @param key The key to compare
 @param value The value to check for
 */
+ (KiiClause*)startsWith:(NSString*)key value:(NSString*)value;

/** Create a KiiClause with the AND operator concatenating multiple KiiClause objects
 @param clauses An array KiiClause objects to concatenate
 @return KiiClause instance with concatenated AND operator,or nil if array contains any non KiiClause instance
 */
+(KiiClause*) andClauses:(NSArray*) clauses;

/** Create a KiiClause with the OR operator concatenating multiple KiiClause objects
 @param clauses An array KiiClause objects to concatenate
 
 @return KiiClause instance with concatenated OR operator,or nil if array contains any non KiiClause instance
 */
+(KiiClause*) orClauses:(NSArray*) clauses;

/**
  Create a clause of geo box. This clause inquires objects in the specified rectangle.
  Rectangle would be placed parallel to the equator with specified coordinates of the corner.
  Throws NSInvalidArgumentException when key is nil or empty, northEast or southWest is nil.
  @param key name of the key to inquire, which holds geo point.
  @param northEast north-west corner of the rectangle.
  @param southWest south-East corner of the rectangle.
  @return KiiClause instance.
 */
+(KiiClause*) geoBox:(NSString*)key northEast:(KiiGeoPoint*)ne southWest:(KiiGeoPoint*)sw;

/**
  Create a clause of geo distance. This clause inquires objects in
  the specified circle.
  Throws NSInvalidArgumentException when key is nil or empty, centor is nil or radius is out of range
  @param key name of the key to inquire, which holds geo point.
  @param center geo point which specify center of the circle.
  @param radius of the circle. unit is meter. value should be in range of ]0, 20000000]
  @param calculatedDistance used for retrieve distance from the center from the query result. If the specified value is null, query result will not contain the distance.
 Note: You can get the results in ascending order of distances from center. To do so, build the orderBy field  by "_calculated.{specified value of calculatedDistance}" and pass it in <[KiiQuery sortByAsc:]> Note that, descending order of distances is not supported. The unit of distance is meter.

    NSString* calculatedDistance = @"distanceFromCurrentLoc";
    KiiGeoPoint* currentLoc = ..; // current location
    KiiClause* geoDist = [KiiClause geoDistance:@"location" center:currentLoc radius:7 putDistanceInto:calculatedDistance];
    KiiQuery *query = [KiiQuery queryWithClause:geoDist];
    // Sort by distances by ascending order.(Optional, use only if you intend to retrieve the distances in a ascending order).
    NSString* orderByKey = [@"_calculated." stringByAppendingString:calculatedDistance];
    [query sortByAsc:orderByKey];
    NSMutableArray *allResults = [NSMutableArray array];
    KiiQuery *nextQuery;
    KiiBucket *bucket = [Kii bucketWithName:@"MyBucket"];
    KiiError *error = nil;
    NSArray *results = [bucket executeQuerySynchronous:query withError:&error andNext:&nextQuery];

    // add the results to our main array
    [allResults addObjectsFromArray:results];
    KiiObject* object = [allResults objectAtIndex:0];
    NSDictionary* cal = [object getObjectForKey:@"_calculated"];
    NSNumber* distanceInMeter = [cal objectForKey:calculatedDistance];


  @return KiiClause instance.
 */
+(KiiClause*) geoDistance:(NSString*)key center:(KiiGeoPoint*)center radius:(double)radius putDistanceInto:(NSString*) calculatedDistance;
@end
