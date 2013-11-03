//
//  LeaderboardViewController.m
//  KiiBlocks
//
//  Created by Chris on 11/1/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import "LeaderboardViewController.h"

#import <KiiSDK/Kii.h>

@implementation LeaderboardViewController

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
    cell.detailTextLabel.text = [object getObjectForKey:@"username"];
    
    return cell;
}

// create a header view for our table to show the user's score and a done button
- (UIView*) tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    // create the main header view
    UIView *header = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 320, 100)];
    header.backgroundColor = [UIColor orangeColor];
    
    // add a 'done' button that will close the view controller
    UIButton *close = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [close setTitle:@"Done" forState:UIControlStateNormal];
    close.frame = CGRectMake(260, 20, 60, 40);
    [close addTarget:self action:@selector(closeView:) forControlEvents:UIControlEventTouchUpInside];
    [header addSubview:close];
    
    // add the user's score label to the header
    UILabel *scoreLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 60, 320, 40)];
    scoreLabel.backgroundColor = [UIColor clearColor];
    scoreLabel.font = [UIFont boldSystemFontOfSize:18.0f];
    scoreLabel.textColor = [UIColor whiteColor];
    scoreLabel.textAlignment = NSTextAlignmentCenter;
    scoreLabel.text = [NSString stringWithFormat:@"Your score: %d", _userScore];
    [header addSubview:scoreLabel];
    
    return header;
}

// set the header height - required by the uitableviewcontroller delegate
- (CGFloat) tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 100.0f;
}

@end
