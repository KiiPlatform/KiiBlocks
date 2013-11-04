//
//  LeaderboardViewController.m
//  KiiBlocks
//
//  Created by Chris on 11/1/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import "LeaderboardViewController.h"

#import <KiiSDK/Kii.h>
#import "KiiToolkit.h"

@interface LeaderboardViewController() {
    UISegmentedControl *_segmentControl;
}

@end

@implementation LeaderboardViewController

- (void) getScores
{
    // TODO: double-check loading indicators for leaderboard
    KiiClause *clause = nil;
    
    if([KiiUser loggedIn] && _segmentControl.selectedSegmentIndex == 0) {
        clause = [KiiClause equals:@"user" value:[KiiUser currentUser]];
    }
    
    // create a query to retrieve the scores
    KiiQuery *query = [KiiQuery queryWithClause:clause];
    [query sortByDesc:@"score"];
    
    // set the query to the leaderboard view controller
    self.query = query;
    
    // pull the data from the server
    [self refreshQuery];
}

- (void) viewDidAppear:(BOOL)animated
{
    // tell the controller which bucket to retrieve the data from
    self.bucket = [Kii bucketWithName:@"scores"];

    [self getScores];
}

// called when the user clicks the 'done' button
- (void) closeView:(id)sender
{
    // closes the leaderboard
    [self dismissViewControllerAnimated:TRUE completion:nil];
}

// create a cell for our score KiiObject
- (UITableViewCell*) tableView:(UITableView *)tableView
              cellForKiiObject:(KiiObject*)object
                   atIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"MyCell";
    
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle
                                                   reuseIdentifier:identifier];
    
    // set the textlabels of the subtitled table view cell
    cell.textLabel.text = [[object getObjectForKey:@"score"] description];
    
    NSString *username = [object getObjectForKey:@"username"];
    NSString *timeAgo = [object.created timeAgo:FALSE];
    NSString *detail = [NSString stringWithFormat:@"%@ - %@", username, timeAgo];
    cell.detailTextLabel.text = detail;
    
    [object describe];
    
    return cell;
}

// create a header view for our table to show the user's score and a done button
- (UIView*) tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    // create the main header view
    UIView *header = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 320, 48.0f)];
    header.backgroundColor = [UIColor orangeColor];
    
    // add a 'done' button that will close the view controller
    UIButton *close = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [close setTitle:@"Done" forState:UIControlStateNormal];
    [close setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    close.frame = CGRectMake(260, 0, 60, 48.0f);
    [close addTarget:self action:@selector(closeView:) forControlEvents:UIControlEventTouchUpInside];
    [header addSubview:close];
    
    // add the user's score label to the header
    UILabel *scoreLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 320, 48.0f)];
    scoreLabel.backgroundColor = [UIColor clearColor];
    scoreLabel.font = [UIFont boldSystemFontOfSize:18.0f];
    scoreLabel.textColor = [UIColor whiteColor];
    scoreLabel.textAlignment = NSTextAlignmentCenter;
    scoreLabel.text = @"Leaderboard"; // [NSString stringWithFormat:@"Your score: %d", _userScore];
    [header addSubview:scoreLabel];
    
    if([KiiUser loggedIn] && _segmentControl == nil) {
        _segmentControl = [[UISegmentedControl alloc] initWithItems:@[@"My Scores", @"All Scores"]];
        _segmentControl.frame = CGRectMake(20, 58, 280, 30);
        _segmentControl.tintColor = [UIColor whiteColor];
        _segmentControl.selectedSegmentIndex = 0;
        [_segmentControl addTarget:self action:@selector(getScores) forControlEvents:UIControlEventValueChanged];
    }

    [header addSubview:_segmentControl];
    
    return header;
}

// set the header height - required by the uitableviewcontroller delegate
- (CGFloat) tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return (_segmentControl == nil) ? 48.0f : _segmentControl.frame.origin.y + _segmentControl.frame.size.height + 10.0f;
}


#pragma mark - KTTableViewDelegate
- (void) tableDidStartLoading
{
    [KTLoader showLoader:@"Loading leaderboard..."];
}

- (void) tableDidFinishLoading:(NSError*)error
{
    if(error == nil) {
        [KTLoader hideLoader];
    } else {
        [KTLoader showLoader:@"Error loading leaderboard"
                    animated:TRUE
               withIndicator:KTLoaderIndicatorError
             andHideInterval:KTLoaderDurationAuto];
    }
}


@end
