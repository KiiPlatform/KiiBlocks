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

#import "MyScene.h"

// define some class-wide attributes for our scene
#define COLUMNS     6
#define ROWS        7

@implementation MyScene

/*
 Create a block and add it to the scene with the specified position, size and color
 */
- (void) createBlock:(CGSize)size withPosition:(CGPoint)position andColor:(UIColor*)color
{
    // create a block to be affected by gravity
    SKSpriteNode *block = [SKSpriteNode spriteNodeWithColor:color size:size];
    
    // create a physics body for this block and set attributes for it
    block.physicsBody = [SKPhysicsBody bodyWithRectangleOfSize:CGSizeMake(size.width-2, size.height-2)];
    block.physicsBody.restitution = 0.f;
    block.physicsBody.allowsRotation = FALSE;
    
    // position the block within the scene
    block.position = position;
    
    // add the block to the scene
    [self addChild:block];

}

-(id)initWithSize:(CGSize)size {
    if (self = [super initWithSize:size]) {
        
        // The background color for our scene
        self.backgroundColor = [SKColor colorWithRed:0.15 green:0.15 blue:0.3 alpha:1.0];
        
        // set the gravity of our world
        self.physicsWorld.gravity = CGVectorMake(0, -1.f);

        
        // create the floor for our scene
        SKSpriteNode *floor = [SKSpriteNode spriteNodeWithColor:[UIColor blackColor] size:CGSizeMake(320, 40)];
        
        // set up its physics body and set attributes
        floor.physicsBody = [SKPhysicsBody bodyWithRectangleOfSize:floor.size];
        floor.physicsBody.restitution = 0.f;
        floor.physicsBody.dynamic = FALSE; // other objects react to it, but gravity doesn't affect it
        floor.position = CGPointMake(160, 20);
        
        // add the floor to our scene
        [self addChild:floor];
        
        
        // iterate through however many rows we want
        for(int row=0; row<ROWS; row++) {
            
            // and in each row, iterate through the number of columns we want
            for (int col=0; col<COLUMNS; col++) {
                
                // generate the width/height of the blocks based on the column count
                CGFloat dimension = 320 / COLUMNS;
                
                // generate the position of the block based on its row and column
                CGFloat xPosition = (dimension / 2) + col * dimension;
                CGFloat yPosition = 480 + ( (dimension/2) - row * dimension );
                
                // define a list of colors the blocks can potentially be
                NSArray *colors = @[[UIColor greenColor], [UIColor blueColor], [UIColor yellowColor]];
                
                // generate a random number within the range of our color list
                NSUInteger colorIndex = arc4random() % colors.count;
                
                // create the block with the specified size and position + the random color
                [self createBlock:CGSizeMake(dimension, dimension)
                     withPosition:CGPointMake(xPosition, yPosition)
                         andColor:[colors objectAtIndex:colorIndex]];
            }

        }
        

    }
    return self;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    /* Called when a touch begins */

}

-(void)update:(CFTimeInterval)currentTime {
    /* Called before each frame is rendered */
    
    // go through all the blocks in our scene
    for(SKNode *node in self.scene.children) {
        
        // and normalize the position so it falls exactly on a pixel
        node.position = CGPointMake(roundf(node.position.x), roundf(node.position.y));
    }
    
}

@end
