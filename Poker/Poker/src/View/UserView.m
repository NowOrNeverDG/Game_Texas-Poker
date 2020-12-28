//
//  UserView.m
//  Poker
//
//  Created by 丁戈 on 16/10/24.
//  Copyright © 2016年 丁戈. All rights reserved.
//

#import "UserView.h"
#import "Commons.h"
#import "UIViewExt.h"
#define 倒计时时间 1.0/450

@implementation UserView {
    UIProgressView *_protaitProgress;
    int _timerSecond;//定时器倒计时的秒数
}

-(instancetype)init {
    self = [super init];
    //设置玩家头像背景图片
    [self addSubview:self.potraitBGImgView];
   
    //设置头像
    [self addSubview:self.potrait];
    
    //设置用户昵称视图
    [self addSubview:self.username];
    
    //设置金币视图
    [self addSubview:self.chipLabel];
    
    [self addSubview:self.potraitCoverView];
    
    self.timer = [CADisplayLink displayLinkWithTarget:self selector:@selector(circleAnimationType)];
    self.timer.frameInterval = 1; //设置刷新60次响应一次
    [self.timer addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    return self;
}

-(void)setCoverImgZIndex:(BOOL)bIsCover {
    self.potraitCoverView.hidden = !bIsCover;
}

-(void)setIsSelf {
    self.potraitBGImgView.image = [UIImage imageNamed:@"背景框红.png"];
//    self.
}

//懒加载所带筹码视图
-(UILabel*)chipLabel {
    if (!_chipLabel) {
        self.chipLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, self.potrait.frame.size.width+7, 15)];
        self.chipLabel.backgroundColor = [UIColor blackColor];
        [self.chipLabel setTextColor:[UIColor whiteColor]];
        self.chipLabel.font = [UIFont systemFontOfSize:10];
        self.chipLabel.textAlignment = NSTextAlignmentCenter;
        self.chipLabel.lineBreakMode = NSLineBreakByCharWrapping;
        self.chipLabel.backgroundColor = [UIColor clearColor];
        self.chipLabel.top = self.potrait.bottom;
    }
    return _chipLabel;
}

//懒加载用户名视图
-(UILabel*)username {
    if (!_username) {
        self.username = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, self.potrait.frame.size.width+7,15)];
        self.username.backgroundColor = [UIColor blackColor];
        [self.username setTextColor:[UIColor whiteColor]];
        self.username.font = [UIFont systemFontOfSize:10];
        self.username.textAlignment = NSTextAlignmentCenter;
        self.username.backgroundColor = [UIColor clearColor];
        self.username.lineBreakMode = NSLineBreakByCharWrapping;
        self.username.bottom = self.potrait.top;
    }
    return _username;
}

//懒加载玩家头像
-(UIImageView*)potrait {
    if (!_potrait) {
        self.potrait = [[UIImageView alloc]initWithFrame:CGRectMake(3.5, 15, 50, 50)];
        self.potrait.image = [UIImage imageNamed:@"头像.png"];
        self.potrait.layer.cornerRadius = 3;
        self.potrait.layer.masksToBounds = YES;
    }
    return _potrait;
}



-(UIImageView*)potraitBGImgView {
    if (!_potraitBGImgView) {
        self.potraitBGImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"玩家头像遮罩.png"]];
        self.potraitBGImgView.frame = CGRectMake(0, 0, 57, 80);
    }
    return _potraitBGImgView;
}

-(UIImageView*)potraitCoverView {
    if (!_potraitCoverView) {
        self.potraitCoverView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"玩家头像遮罩.png"]];
        self.potraitCoverView.frame = CGRectMake(0, 0, 57, 80);
        self.potraitCoverView.hidden = YES;
    }
    return _potraitCoverView;
}



//懒加载转转
-(CAShapeLayer*)shapeLayer {
    if (!_shapeLayer) {
        //创建出CAShapeLayer
        self.shapeLayer = [CAShapeLayer layer];
        self.shapeLayer.frame = CGRectMake(0, 0, 57, 80);
        self.shapeLayer.position = self.potrait.center;
        self.shapeLayer.fillColor = [UIColor clearColor].CGColor;
        
        //设置线条的宽度和颜色
        self.shapeLayer.lineWidth = 2.0f;
        self.shapeLayer.strokeColor = [UIColor greenColor].CGColor;
        
        //设置stroke起始点
        
        
        //创建出圆形贝塞尔曲线
        UIBezierPath *circlePath = [UIBezierPath bezierPathWithRoundedRect:CGRectMake(0, 0, 57, 80) cornerRadius:3];
        //让贝塞尔曲线与CAShapeLayer产生联系
        self.shapeLayer.path = circlePath.CGPath;
    }
    return _shapeLayer;
}

#pragma mark - Timer
-(void)startCycle {//用定时器模拟数值输入的情况
    [self.layer addSublayer:self.shapeLayer];
    
    _shapeLayer.strokeStart = 0;
    _shapeLayer.strokeEnd = 1;
//    [_timer setFireDate:[NSDate distantPast]];
//    _timer = [NSTimer scheduledTimerWithTimeInterval:.1
//                                              target:self
//                                            selector:@selector(circleAnimationType)
//                                            userInfo:nil
//                                             repeats:YES];
}

- (void)circleAnimationType {//用定时器调用的方法
    if (_shapeLayer.strokeStart != 1) {
        _shapeLayer.strokeStart += 倒计时时间;
    }
}

-(void)endCycle {
    
    _shapeLayer.strokeStart = 1;
    _shapeLayer.strokeEnd = 0;
//    [_timer setFireDate:[NSDate distantFuture]];
}
@end
