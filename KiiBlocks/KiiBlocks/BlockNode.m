//
//  BlockNode.m
//  KiiBlocks
//
//  Created by Chris on 11/1/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import "BlockNode.h"

@implementation BlockNode


- (BlockNode*) initWithRow:(NSUInteger)row
                 andColumn:(NSUInteger)column
                 withColor:(UIColor*)color
                   andSize:(CGSize)size
{
    
    self = [super initWithColor:color size:size];
    
    if(self) {
        
        // store our parameters as class variables
        _row = row;
        _column = column;
        
        // create a physics body for this block and set attributes for it
        self.physicsBody = [SKPhysicsBody bodyWithRectangleOfSize:CGSizeMake(size.width-2, size.height-2)];
        self.physicsBody.restitution = 0.f;
        self.physicsBody.allowsRotation = FALSE;
        
        // generate the position of the block based on its row and column
        CGFloat xPosition = (size.width / 2) + _column * size.width;
        CGFloat yPosition = 480 + ( (size.height / 2) + _row * size.height );

        // position the block within the scene
        self.position = CGPointMake(xPosition, yPosition);
        
    }
    
    return self;
}

@end
