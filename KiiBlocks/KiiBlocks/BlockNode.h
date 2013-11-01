//
//  BlockNode.h
//  KiiBlocks
//
//  Created by Chris on 11/1/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>

@interface BlockNode : SKSpriteNode

@property (nonatomic, assign) NSUInteger row;
@property (nonatomic, assign) NSUInteger column;

- (BlockNode*) initWithRow:(NSUInteger)row
                 andColumn:(NSUInteger)column
                 withColor:(UIColor*)color
                   andSize:(CGSize)size;

@end
