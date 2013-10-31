//
//  MyScene.m
//  KiiBlocks
//
//  Created by Chris on 10/31/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import "MyScene.h"

@implementation MyScene

-(id)initWithSize:(CGSize)size {    
    if (self = [super initWithSize:size]) {
        
        // The background color for our scene
        self.backgroundColor = [SKColor colorWithRed:0.15 green:0.15 blue:0.3 alpha:1.0];
        
        // set the gravity of our world
        self.physicsWorld.gravity = CGVectorMake(0, -1.f);
        
        
        
        // create a block to be affected by gravity
        SKSpriteNode *block = [SKSpriteNode spriteNodeWithColor:[UIColor redColor] size:CGSizeMake(100, 100)];
        
        // create a physics body for this block and set attributes for it
        block.physicsBody = [SKPhysicsBody bodyWithRectangleOfSize:block.size];
        block.physicsBody.restitution = 0.f;
        
        // position the block within the scene
        block.position = CGPointMake(160, 480);
        
        // add the block to the scene
        [self addChild:block];
        
        
        
        // create the floor for our scene
        SKSpriteNode *floor = [SKSpriteNode spriteNodeWithColor:[UIColor greenColor] size:CGSizeMake(320, 40)];
        
        // set up its physics body and set attributes
        floor.physicsBody = [SKPhysicsBody bodyWithRectangleOfSize:floor.size];
        floor.physicsBody.restitution = 0.f;
        floor.physicsBody.dynamic = FALSE; // other objects react to it, but gravity doesn't affect it
        floor.position = CGPointMake(160, 20);
        
        [self addChild:floor];

    }
    return self;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    /* Called when a touch begins */

}

-(void)update:(CFTimeInterval)currentTime {
    /* Called before each frame is rendered */
}

@end
