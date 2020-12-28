//
//  Poker.m
//  Poker
//
//  Created by 丁戈 on 2016/12/13.
//  Copyright © 2016年 丁戈. All rights reserved.
//

#import "PokerView.h"
#import "Commons.h"
#import "ViewController_SetViewPos.h"

@implementation PokerView
-(NSString*)getPokerFileNameWithHS:(int)HS withDX:(int)DX {
    NSString *pokerFileName;
    //花色大小为0时 则发送卡牌背面视图
    if (DX == 0 || HS == 0) {
        return @"扑克背面.png";
    }
    if (DX == 14) { DX = 1; }
    //设置卡牌的花色
    switch (HS) {
        case 1:{ pokerFileName = [NSString stringWithFormat:@"黑桃_%d.png",DX];break; }
        case 2:{ pokerFileName = [NSString stringWithFormat:@"红桃_%d.png",DX];break; }
        case 3:{ pokerFileName = [NSString stringWithFormat:@"梅花_%d.png",DX];break; }
        case 4:{ pokerFileName = [NSString stringWithFormat:@"方块_%d.png",DX];break; }
    }
    return pokerFileName;
}

-(void)creatImageWithHS:(int)HS withDX:(int)DX {
    if (!_originImage) {
        _originImage = [[UIImage alloc] init];
    }
    self.image = [UIImage imageNamed:[self getPokerFileNameWithHS:HS withDX:DX]];
    _originImage = self.image;
}

//设置扑克的大小
-(void)changeLastStateOfFrameInDealWithPlayerNo:(int)iPlayerNo withPokerNo:(int)iPokerNo {
    if (0 == iPokerNo) {
        switch (iPlayerNo) {
            case 0: { self.frame = 零号一号私牌的视图窗口; break;}
            case 1: { self.frame = 一号一号私牌的视图窗口; break;}
            case 2: { self.frame = 二号一号私牌的视图窗口; break;}
            case 3: { self.frame = 三号一号私牌的视图窗口; break;}
            case 4: { self.frame = 四号一号私牌的视图窗口; break;}
            case 5: { self.frame = 五号一号私牌的视图窗口; break;}
        }
    } else {
        switch (iPlayerNo) {
            case 0: { self.frame = 零号二号私牌的视图窗口; break;}
            case 1: { self.frame = 一号二号私牌的视图窗口; break;}
            case 2: { self.frame = 二号二号私牌的视图窗口; break;}
            case 3: { self.frame = 三号二号私牌的视图窗口; break;}
            case 4: { self.frame = 四号二号私牌的视图窗口; break;}
            case 5: { self.frame = 五号二号私牌的视图窗口; break;}
        }
    }
}

-(void)changeLastStateOfBigFrameInDealWithPlayerNo:(int)iPlayerNo withPokerNo:(int)iPokerNo {
    if (iPokerNo == 0) {
        switch (iPlayerNo) {
            case 0: { self.frame = 零号一号私牌的大视图窗口; break;}
            case 1: { self.frame = 一号一号私牌的大视图窗口; break;}
            case 2: { self.frame = 二号一号私牌的大视图窗口; break;}
            case 3: { self.frame = 三号一号私牌的大视图窗口; break;}
            case 4: { self.frame = 四号一号私牌的大视图窗口; break;}
            case 5: { self.frame = 五号一号私牌的大视图窗口; break;}
        }
    } else {
        switch (iPlayerNo) {
            case 0: { self.frame = 零号二号私牌的大视图窗口; break;}
            case 1: { self.frame = 一号二号私牌的大视图窗口; break;}
            case 2: { self.frame = 二号二号私牌的大视图窗口; break;}
            case 3: { self.frame = 三号二号私牌的大视图窗口; break;}
            case 4: { self.frame = 四号二号私牌的大视图窗口; break;}
            case 5: { self.frame = 五号二号私牌的大视图窗口; break;}
        }
    }
}
    
-(void)changeCommonPokerLastStateOfFrameWithPokerNo:(int)iPokerNo {
    switch (iPokerNo) {
        case 第一张公牌的序号: {self.frame = 一号公牌的视图窗口; break;}
        case 第二张公牌的序号: {self.frame = 二号公牌的视图窗口; break;}
        case 第三张公牌的序号: {self.frame = 三号公牌的视图窗口; break;}
        case 第四张公牌的序号: {self.frame = 四号公牌的视图窗口; break;}
        case 第五张公牌的序号: {self.frame = 五号公牌的视图窗口; break;}
    }
}

-(void)showFloatBGview {
    self.size = CGSizeMake(45, 60);
    self.floatBGView.frame = self.bounds;
    self.image = _originImage;
    [self increasebrightness];
    
    self.floatBGView.hidden = NO;
}

-(void)hiddenFloatBGview {
    self.floatBGView.hidden = YES;
    
    self.image = _originImage;
    self.size = CGSizeMake(40, 55);
}

-(UIImageView*)floatBGView {
    if (!_floatBGView) {
        self.floatBGView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"比牌火焰.png"]];
        self.floatBGView.hidden = YES;
    }
    return _floatBGView;
}

-(void)decreasebrightness {
    CIContext *context = [CIContext contextWithOptions:nil];
    CIImage *superImage = [CIImage imageWithCGImage:self.image.CGImage];
    CIFilter *filter = [CIFilter filterWithName:@"CIPhotoEffectMono" keysAndValues:kCIInputImageKey, superImage, nil];
    [filter setDefaults];
    CIImage *outputImage = [filter outputImage];
    CGImageRef cgImage = [context createCGImage:outputImage fromRect:[outputImage extent]];//创建CGImage句柄
    UIImage *image = [UIImage imageWithCGImage:cgImage];
    self.image = image;
    CGImageRelease(cgImage);//释放CGImage句柄

}

-(void)increasebrightness {
    CIContext *context = [CIContext contextWithOptions:nil];
    CIImage *superImage = [CIImage imageWithCGImage:self.image.CGImage];
    CIFilter *lighten = [CIFilter filterWithName:@"CIColorControls"];
    [lighten setValue:superImage forKey:kCIInputImageKey];
    [lighten setValue:@(.5) forKey:@"inputBrightness"];
    [lighten setValue:@(2) forKey:@"inputSaturation"];
    [lighten setValue:@(2) forKey:@"inputContrast"];
    CIImage *result = [lighten valueForKey:kCIOutputImageKey];
    CGImageRef cgImage = [context createCGImage:result fromRect:[superImage extent]];
    self.image = [UIImage imageWithCGImage:cgImage];// 得到修改后的图片
    CGImageRelease(cgImage);// 释放对象
}
@end





