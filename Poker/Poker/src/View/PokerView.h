//
//  Poker.h
//  Poker
//
//  Created by 丁戈 on 2016/12/13.
//  Copyright © 2016年 丁戈. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Commons.h"
#import "UIViewExt.h"
@interface PokerView : UIImageView

@property(nonatomic,strong)UIImageView* floatBGView;
@property(nonatomic,strong)UIImage *originImage;
-(NSString*)getPokerFileNameWithHS:(int)HS withDX:(int)DX;
-(void)creatImageWithHS:(int)HS withDX:(int)DX;
-(void)changeLastStateOfFrameInDealWithPlayerNo:(int)iPlayer withPokerNo:(int)iPokerNo;
-(void)changeLastStateOfBigFrameInDealWithPlayerNo:(int)iPlayer withPokerNo:(int)iPokerNo;
-(void)changeCommonPokerLastStateOfFrameWithPokerNo:(int)iPokerNo;

-(void)showFloatBGview;
-(void)hiddenFloatBGview;

-(void)decreasebrightness;
@end
