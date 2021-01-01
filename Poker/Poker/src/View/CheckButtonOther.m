//
//  CheckButtonOther.m
//  Poker
//
//  Created by 丁戈 on 2017/1/11.
//  Copyright © 2017年 丁戈. All rights reserved.
//

#import "CheckButtonOther.h"
#import "Commons.h"
@implementation CheckButtonOther

-(UILabel*)textLabel {
    if (!_textLabel) {
        self.textLabel = [[UILabel alloc] init];
        self.textLabel.text = @"Call Auto";
        self.textLabel.font = [UIFont systemFontOfSize:13];
        self.textLabel.lineBreakMode = NSLineBreakByCharWrapping;
        self.textLabel.textAlignment = NSTextAlignmentCenter;
        self.textLabel.textColor = [UIColor whiteColor];
    }
    return _textLabel;
}

-(UIImageView*)markInOtherView {
    if (!_markInOtherView) {
        self.markInOtherView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"选中.png"]];
        self.markInOtherView.frame = CGRectMake(10.3, 3, 22,22);
        self.markInOtherView.hidden = YES;
    }
    return _markInOtherView;
}
@end
