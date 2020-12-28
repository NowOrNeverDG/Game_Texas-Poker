//
//  AddSlider.h
//  Poker
//
//  Created by 丁戈 on 2017/1/13.
//  Copyright © 2017年 丁戈. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AddSlider : UISlider
@property(nonatomic,strong)UIImageView* confirmView;
@property(nonatomic,strong)UIButton* confirmButton;
@property(nonatomic,strong)UILabel* countLabel;

@end
