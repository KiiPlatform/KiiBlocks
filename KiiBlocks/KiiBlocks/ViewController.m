//
//
// Copyright 2013 Kii Corporation
// http://kii.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//

#import "ViewController.h"
#import "MyScene.h"
#import "KiiToolkit.h"

#import <KiiSDK/Kii.h>

#define KII_ACCESS_TOKEN    @"kii-token"

@interface ViewController() {
    BOOL _loaded;
}

@end

@implementation ViewController

// when the view controller appears (on launch)
- (void) viewDidAppear:(BOOL)animated
{
    // we only want to do auth logic if the app is just opened
    if(!_loaded) {

        // see if there's a stored user token
        NSString *token = [[NSUserDefaults standardUserDefaults] stringForKey:KII_ACCESS_TOKEN];
        
        // if we have a token
        if(token != nil) {
            
            // make sure it's valid, but do it in the background
            [KiiUser authenticateWithToken:token
                                  andBlock:^(KiiUser *user, NSError *error) {
                                      if(error == nil) {
                                          
                                          NSString *message = [NSString stringWithFormat:@"Welcome back %@", user.username];
                                          
                                          KTAlertBar *bar = (KTAlertBar*)[[KTAlert alloc] initWithType:KTAlertTypeBar
                                                                                            withMessage:message
                                                                                            andDuration:KTAlertDurationLong];

                                          [bar setBackgroundColors:[UIColor colorWithHex:@"009C00"], [UIColor colorWithHex:@"005404"], nil];
                                          [(KTAlert*)bar show];
                                          
                                      } else {
                                          
                                          NSString *message = @"Couldn't log in - won't post scores";
                                          [KTAlert showAlert:KTAlertTypeBar
                                                 withMessage:message
                                                 andDuration:KTAlertDurationLong];
                                          
                                      }
                                  }];
            
        }
        
        // don't have a token yet, get one
        else {
            
            // if not, show a login view
            KTLoginViewController *lvc = [[KTLoginViewController alloc] init];
            lvc.delegate = self;
            [self presentViewController:lvc animated:TRUE completion:nil];
        }

        // set the flag, indicating that we've tried login
        _loaded = TRUE;
    }
    

}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Configure the view.
    SKView * skView = (SKView *)self.view;
//    skView.showsFPS = YES;
//    skView.showsNodeCount = YES;
    
    // Create and configure the scene.
    MyScene * scene = [MyScene sceneWithSize:skView.bounds.size];
    scene.scaleMode = SKSceneScaleModeAspectFill;
    scene.parentViewController = self; // make this view controller accessible to our scene
    
    // Present the scene.
    [skView presentScene:scene];
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return UIInterfaceOrientationMaskAllButUpsideDown;
    } else {
        return UIInterfaceOrientationMaskAll;
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - KTLoginView delegate
- (void) didFinishAuthenticating:(KiiUser*)user
                       withError:(NSError*)error
{
    NSLog(@"Did finish authing: %@ with error: %@", user, error);
    if(error == nil) {
        NSLog(@"atoken: %@", user.accessToken);
        [[NSUserDefaults standardUserDefaults] setObject:user.accessToken forKey:KII_ACCESS_TOKEN];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

- (void) didFinishRegistering:(KiiUser*)user
                    withError:(NSError*)error
{
    NSLog(@"Did finish registering: %@ with error: %@", user, error);
    if(error == nil) {
        NSLog(@"rtoken: %@", user.accessToken);
        [[NSUserDefaults standardUserDefaults] setObject:user.accessToken forKey:KII_ACCESS_TOKEN];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}


@end
