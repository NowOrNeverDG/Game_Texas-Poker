//
//  PoolView.m
//  Poker
//
//  Created by 丁戈 on 2017/1/6.
//  Copyright © 2017年 丁戈. All rights reserved.
//

#import "PoolView.h"

@implementation PoolView

-(instancetype)init {
    self = [super init];
    
    self.image = [UIImage imageNamed:@"多筹码下注框.png"];
    
    
    //前面的注额文本
    self.poolLabel = [[UILabel alloc] initWithFrame:CGRectMake(14,2,42,12)];
    self.poolLabel.font = [UIFont systemFontOfSize:10];
    self.poolLabel.textColor = [UIColor whiteColor];
    self.poolLabel.textAlignment = NSTextAlignmentCenter;
    self.poolLabel.lineBreakMode = NSLineBreakByCharWrapping;
    [self addSubview:self.poolLabel];
    
    return self;
}

@end
