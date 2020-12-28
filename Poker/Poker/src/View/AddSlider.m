//
//  AddSlider.m
//  Poker
//
//  Created by 丁戈 on 2017/1/13.
//  Copyright © 2017年 丁戈. All rights reserved.
//

#import "AddSlider.h"

@implementation AddSlider
-(instancetype)init {
    self = [super init];
    if (self) {
        self.frame = CGRectMake(15, 300, 300, 115);
        [self setThumbImage:[UIImage imageNamed:@"筹码1.png"] forState:UIControlStateNormal];
        [self setThumbImage:[UIImage imageNamed:@"筹码1.png"] forState:UIControlStateHighlighted];
        self.value = 1;
        self.tintColor = [UIColor whiteColor];
        self.userInteractionEnabled = YES;
        self.hidden = YES;
        [self addSubview:self.confirmView];
    }
    return self;
}

-(UIView*)confirmView {
    if (!_confirmView) {
        _confirmView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 40, 40)];
        _confirmView.image = [UIImage imageNamed:@"加注_确定2.png"];
        _confirmView.layer.cornerRadius = 5;
        _confirmView.layer.masksToBounds = YES;
        _confirmView.userInteractionEnabled = YES;
        _confirmView.hidden = YES;
        [_confirmView addSubview:self.countLabel];
        [_confirmView addSubview:self.confirmButton];
    }
    return _confirmView;
}

-(UILabel*)countLabel {
    if (!_countLabel) {
        _countLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 40, 20)];
        _countLabel.font = [UIFont systemFontOfSize:10.0];
        _countLabel.textAlignment = NSTextAlignmentCenter;
        _countLabel.lineBreakMode = NSLineBreakByCharWrapping;
        _countLabel.textColor = [UIColor whiteColor];
    }
    return _countLabel;
}

-(UIButton*)confirmButton {
    if (!_confirmButton) {
        _confirmButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _confirmButton.frame = CGRectMake(0, 18, 40, 20);
        [_confirmButton setTitle:@"确定" forState:UIControlStateNormal];
        _confirmButton.titleLabel.font = [UIFont systemFontOfSize: 10.0];
        [_confirmButton setTitleColor:[UIColor whiteColor]forState:UIControlStateNormal];
        _confirmButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentCenter;
    }
    return _confirmButton;
}

@end
