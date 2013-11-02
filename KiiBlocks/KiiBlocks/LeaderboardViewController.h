//
//  LeaderboardViewController.h
//  KiiBlocks
//
//  Created by Chris on 11/1/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import "KTTableViewController.h"

@interface LeaderboardViewController : KTTableViewController

// allow the user score to be set from outside this class
@property (nonatomic, assign) NSUInteger userScore;

@end
