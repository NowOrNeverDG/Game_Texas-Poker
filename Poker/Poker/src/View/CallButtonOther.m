//
//  CallButtonOther.m
//  Poker
//
//  Created by 丁戈 on 2017/1/12.
//  Copyright © 2017年 丁戈. All rights reserved.
//

#import "CallButtonOther.h"

@implementation CallButtonOther

-(UIImageView*)markInOtherView {
    if (!_markInOtherView) {
        self.markInOtherView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"选中.png"]];
        self.markInOtherView.frame = CGRectMake(10.3, 3, 22,22);
        self.markInOtherView.hidden = YES;
    }
    return _markInOtherView;
}

@end
