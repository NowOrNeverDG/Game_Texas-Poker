//load all view on screen
#import "ViewController.h"
#import "ViewController_SetViewPos.h"

#import "UIViewExt.h"

#import "Commons.h"
#import "UserView.h"
#import "PourView.h"
#import "PokerView.h"
#import "PoolView.h"

#import "AddSlider.h"
#import "CheckButtonOther.h"
#import "FoldButtonOther.h"
#import "CallButtonOther.h"

//按钮状态
enum enum_buttonStatus {
    hidden,
    otherPlayer,
    myself
};

@implementation ViewController {
    UIView* _VideoPlayerView;
    NSURL* _urlVideo;
    
    PoolView* _poolView[6];
    UserView* _userView[6];
    PourView* _pourView[6];
    
    PokerView* _commonPokerImgView[5];
    PokerView* _privatePokerImgView[6][2];
    
    int _moneyNumber;//活动条上选择的下注额
    AddSlider *_addPourSlider;//滑动条
    
    UIButton *_foldButton;
    UIButton *_checkButton;
    CallButtonOther *_callButtonOther;
    FoldButtonOther *_foldButtonOther;
    CheckButtonOther *_checkButtonOther;
    UIImageView *_tapMarkInOther;
    
    UIImageView* _movingChipView[6];
    CGPoint _movingChipStartOrigin[6];
    int _iButtonStatus;//按钮状态
    
    CAAnimationGroup *_groupAnimation[5];
    int _maxPourBefore;//切换checkButtonOther的点击状态
    int _iTmp;//全局暂时变量
}

- (void)viewDidLoad {
    [super viewDidLoad];

    _iButtonStatus = enum_buttonStatus::hidden;
    //创建Socket对象
    _socketClient = new CSocketClient();
    
    //创建桌数据对象
    _tableData = new CTableData();
    _tableData->fuck初始化所有变量();
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.view addSubview:self.poolBGView];
    });
}

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    //显示背景
    UIImageView *backgroundImgView = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"带桌背景.png"]];
    backgroundImgView.frame = self.view.bounds;
    [self.view addSubview:backgroundImgView];
    
    //创建各子视图
    [self setTopMenu];         //设置顶部的两个菜单
  //[self setVideoPlayer];     //设置播放器
    [self setAddPourSlider];   //设置跟注条
    [self setBottomButton];    //设置底部按钮
    
    for (int i = 0; i < 5; i++) {
        //创建5个边池的View
        _poolView[i] = [[PoolView alloc] init];
        switch (i) {
            case 0: {_poolView[i].frame = 零号边池的视图窗口; break;}
            case 1: {_poolView[i].frame = 一号边池的视图窗口; break;}
            case 2: {_poolView[i].frame = 二号边池的视图窗口; break;}
            case 3: {_poolView[i].frame = 三号边池的视图窗口; break;}
            case 4: {_poolView[i].frame = 四号边池的视图窗口; break;}
        }
        _poolView[i].hidden = YES;
        
        //创建6个公牌的View
        _commonPokerImgView[i] = [[PokerView alloc] init];
        _commonPokerImgView[i].size = CGSizeMake(42, 55);
        _commonPokerImgView[i].hidden = YES;
        
        [self.poolBGView addSubview:_poolView[i]];
        [self.view addSubview:_commonPokerImgView[i]];
        [_commonPokerImgView[i] addSubview:_commonPokerImgView[i].floatBGView];
    }
    
    //创建玩家及下注View
    for (int i = 0; i < 6; i++) {
        _userView[i] = [[UserView alloc] init];
        switch (i) {
            case 0: {_userView[i].frame = 零号玩家的视图窗口; break;}
            case 1: {_userView[i].frame = 一号玩家的视图窗口; break;}
            case 2: {_userView[i].frame = 二号玩家的视图窗口; break;}
            case 3: {_userView[i].frame = 三号玩家的视图窗口; break;}
            case 4: {_userView[i].frame = 四号玩家的视图窗口; break;}
            case 5: {_userView[i].frame = 五号玩家的视图窗口; break;}
        }
        _userView[i].hidden = YES;
        
        _pourView[i] = [[PourView alloc] init];
        switch (i) {
            case 0: {_pourView[i].frame = 零号注额的视图窗口; break;}
            case 1: {_pourView[i].frame = 一号注额的视图窗口; break;}
            case 2: {_pourView[i].frame = 二号注额的视图窗口; break;}
            case 3: {_pourView[i].frame = 三号注额的视图窗口; break;}
            case 4: {_pourView[i].frame = 四号注额的视图窗口; break;}
            case 5: {_pourView[i].frame = 五号注额的视图窗口; break;}
        }
        
        _pourView[i].hidden = YES;
        
        //创建6个私牌的View
        _privatePokerImgView[i][0] = [[PokerView alloc] init];
        _privatePokerImgView[i][1] = [[PokerView alloc] init];
        _privatePokerImgView[i][0].size = CGSizeMake(25, 33);
        _privatePokerImgView[i][1].size = CGSizeMake(25, 33);
        
        //创建移动筹码View
        _movingChipView[i] = [[UIImageView alloc] init];
        _movingChipView[i].frame = CGRectMake(-100, -100, 15, 15);
        _movingChipView[i].image = [UIImage imageNamed:@"筹码1.png"];
      //_movingChipView[i].hidden = YES;
        
        [self.view addSubview:_userView[i]];
        [self.view addSubview:_pourView[i]];
        [self.view addSubview:_privatePokerImgView[i][1]];
        [_privatePokerImgView[i][1] addSubview:_privatePokerImgView[i][1].floatBGView];
        [self.view addSubview:_privatePokerImgView[i][0]];
        [_privatePokerImgView[i][0] addSubview:_privatePokerImgView[i][0].floatBGView];
        [self.view addSubview:_movingChipView[i]];
    }

    _movingChipStartOrigin[0] = 零号注额筹码的位置;
    _movingChipStartOrigin[1] = 一号注额筹码的位置;
    _movingChipStartOrigin[2] = 二号注额筹码的位置;
    _movingChipStartOrigin[3] = 三号注额筹码的位置;
    _movingChipStartOrigin[4] = 四号注额筹码的位置;
    _movingChipStartOrigin[5] = 五号注额筹码的位置;
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    if (_socketClient->ConnectLocalHost() != 1){
        _socketClient->ConnectServers();
    }
    
    //建立通知链接
    //[[NSRunLoop currentRunLoop] addPort:self.notificationPort forMode:(__bridge NSString *)kCFRunLoopCommonModes];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(通知_收到服务器消息:) name:@"通知_收到服务器消息" object:nil];
    
    dispatch_queue_t concurrentQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_async(concurrentQueue, ^{ [self testFunc]; });
}

-(UIView*)poolBGView {
    if (!_poolBGView) {
        _poolBGView = [[UIView alloc] init];
        _poolBGView.center = CGPointMake(ksboundsWidth/2, 150);
    }
    return _poolBGView;
}

-(void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    delete _tableData;
    delete _socketClient;
}

#import "ViewController_TapEvents.h"
#import "ViewController_View.h"
#import "ViewController_TouchesEvents.h"
#import "ViewController_Player.h"
#import "ViewController_Test.h"
#import "ViewController_UpdateUI.h"
#import "ViewController_Anima.h"
#import "ViewController_Protocol.h"
@end
