//
//  PourView.h
//  Poker
//
//  Created by 丁戈 on 2017/1/5.
//  Copyright © 2017年 丁戈. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PourView : UIImageView

@property(nonatomic,strong)UILabel *pourLabel;//玩家已下的注

-(void)setBankerMark:(BOOL)bIsBanker;
@end
