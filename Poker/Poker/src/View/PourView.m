//
//  PourView.m
//  Poker
//
//  Created by 丁戈 on 2017/1/5.
//  Copyright © 2017年 丁戈. All rights reserved.
//

#import "PourView.h"
@implementation PourView {
    UIImageView* _pourBankerMarkImgView;
}

-(instancetype)init {
    self = [super init];

    self.image = [UIImage imageNamed:@"带筹码框.png"];
    
    //前面的注额文本
    self.pourLabel = [[UILabel alloc] initWithFrame:CGRectMake(15,2,32,12)];
    self.pourLabel.font = [UIFont systemFontOfSize:10];
    self.pourLabel.textColor = [UIColor whiteColor];
    self.pourLabel.textAlignment = NSTextAlignmentCenter;
    self.pourLabel.lineBreakMode = NSLineBreakByCharWrapping;
    [self addSubview:self.pourLabel];
    
    _pourBankerMarkImgView = [[UIImageView alloc] init];
    _pourBankerMarkImgView.frame = CGRectMake(0, 2, 15, 15);
    [self addSubview:_pourBankerMarkImgView];
    
    return self;
}

-(void)setBankerMark:(BOOL)bIsBanker {
    if (bIsBanker) {
        
        _pourBankerMarkImgView.image = [UIImage imageNamed:@"庄.png"];
        _pourBankerMarkImgView.frame = CGRectMake(0, 1, 14, 14);
    } else{
        _pourBankerMarkImgView.image = nil;
    }
}
@end
