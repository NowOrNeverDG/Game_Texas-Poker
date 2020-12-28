#import "TableData.h"
#import "ViewController.h"
#define BUFFER_SIZE 1024

//服务器发给玩家的消息：10~99
#define MsgFromServer_玩家上线 10
#define MsgFromServer_玩家下线 12
#define MsgFromServer_玩家上桌 20
#define MsgFromServer_玩家离桌 22

#define MsgFromServer_玩家弃牌 30
#define MsgFromServer_玩家让牌 32
#define MsgFromServer_玩家下注 36
#define MsgFromServer_玩家操作 39

#define MsgFromServer_添加玩家 50
#define MsgFromServer_等待荷官 52
#define MsgFromServer_开始比赛 53
#define MsgFromServer_结束比赛 56 //未进行到最后的比赛
#define MsgFromServer_比赛结果 57 //经分析后得到的结果
#define MsgFromServer_荷官发牌 58
#define MsgFromServer_玩家明牌 59

#define MsgFromServer_创建房间 60
#define MsgFromServer_关闭房间 62
#define MsgFromServer_房间开赛 66

#define MsgFromServer_组桌_组桌成功 70
#define MsgFromServer_组桌_无此房间 72
#define MsgFromServer_组桌_人数已满 74
#define MsgFromServer_组桌_筹码不足 76
#define MsgFromServer_组桌_已经上桌 78
#define MsgFromServer_开局_玩家过少 80


-(void)通知_收到服务器消息:(NSNotification*)NotificationParam {
    char* recvBuffer = (char*)[NotificationParam.object bytes];
    int iRecvLen = [NotificationParam.userInfo[@"RecvLen"] intValue];
    //分析收到的数据，并做相应处理
    int iMsgLen;
    while (iRecvLen > 0) {
        iMsgLen = ((Byte)recvBuffer[0]) * 256 + ((Byte)recvBuffer[1]);
        if (iMsgLen > (iRecvLen - 2)) {
            NSLog(@"警告：收到的数据格式有问题！！！");
            return;
        }
        
        recvBuffer += 2;
        switch (recvBuffer[0]) {
                
            case MsgFromServer_玩家上线: {}
            case MsgFromServer_玩家下线: {}
            case MsgFromServer_玩家上桌: { [self interfacePlayerSitAtTheTable:recvBuffer]; break; }
            case MsgFromServer_玩家离桌: { [self interfacePlayerLeavingTable:recvBuffer]; break; }
            
            case MsgFromServer_玩家弃牌: { [self interfaceOtherPlayerFold:recvBuffer]; break; }
            case MsgFromServer_玩家让牌: { [self interfaceOtherPlayerCheck:recvBuffer]; break; }
            case MsgFromServer_玩家下注: { [self interfaceAllPlayerPour:recvBuffer]; break; }
            case MsgFromServer_添加玩家: { [self interfaceAddOtherPlayer:recvBuffer]; break; }
            case MsgFromServer_等待荷官: { [self interfaceWaitingDealer:recvBuffer]; break;}
            case MsgFromServer_开始比赛: { [self interfaceStartGame:recvBuffer]; break; }
            case MsgFromServer_结束比赛: { [self interfaceEndGame:recvBuffer]; break; }
            case MsgFromServer_比赛结果: { [self interfaceGameResults:recvBuffer]; break; }
            case MsgFromServer_荷官发牌: { [self interfaceDealerDear:recvBuffer]; break; }
            case MsgFromServer_玩家明牌: { [self interfaceOpenPokerOfOtherPlayer:recvBuffer]; break; }
            
            case MsgFromServer_创建房间: {}
            case MsgFromServer_关闭房间: {}
            case MsgFromServer_房间开赛: {}
                
            case MsgFromServer_组桌_组桌成功: { NSLog(@"组桌成功"); break; }
            case MsgFromServer_组桌_无此房间: { NSLog(@"无此房间"); break; }
            case MsgFromServer_组桌_人数已满: { NSLog(@"人数已满"); break; }
            case MsgFromServer_组桌_筹码不足: { NSLog(@"筹码不足"); break; }
            case MsgFromServer_组桌_已经上桌: { NSLog(@"已经上线"); break; }
            case MsgFromServer_开局_玩家过少: { NSLog(@"玩家过少"); break; }
        }
        
        recvBuffer += iMsgLen;
        iRecvLen = iRecvLen - 2 - iMsgLen;
    }
}

-(void)interfacePlayerSitAtTheTable:(char*)cszRecvBuff {//玩家上桌
    //[协议号(1位A码)][玩家个数(1位A码)][玩家自己座位号(1位A码:0~5)]{[玩家座位号(1位A码:0~5)][昵称长度(1位A码)][昵称(UTF8)][筹码数(8位十六进制)]}
    dispatch_queue_t concurrentQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_sync(concurrentQueue, ^{
    _tableData->fuck初始化所有变量();
    
    _tableData->_i玩家数量 = cszRecvBuff[1];//获取本局玩家的总人数
    _tableData->_i自身玩家编号 = cszRecvBuff[2];
        
    int iCount = 3;//接受的数据进行到了第几位
    int iPlayerNo;
    int iPlayerNameLength;//获取字符串的长度    
    char cPlayerChips[9] = {0};
    
    for (int i = _tableData->_i玩家数量; i > 0; i--) {//取出玩家的名字和筹码数
        iPlayerNo = cszRecvBuff[iCount];
        iCount ++;//到达昵称长度位
        
        iPlayerNameLength = cszRecvBuff[iCount];
        strncpy(_tableData->_csz玩家昵称[iPlayerNo], cszRecvBuff+iCount+1, iPlayerNameLength);
        iCount += iPlayerNameLength+1;//到达携带筹码位第一位

        strncpy(cPlayerChips,cszRecvBuff+iCount,8);
        _tableData->_i手上筹码数[iPlayerNo] = (int)strtoul(cPlayerChips, 0, 0x10);
        iCount += 8;
        
        //对脏区赋值
        _tableData->_bDirtyNickName[iPlayerNo] = 1;
        _tableData->_bDirtyChips[iPlayerNo] = 1;
        _tableData->_bDirtyUserView[iPlayerNo] = 1; 
    }
 });
    //在主线程加载UI 给玩家视图赋值
    dispatch_async(dispatch_get_main_queue(), ^{
        [_userView[_tableData->_i自身玩家编号] setIsSelf];
        [self UpdateNickName];
        [self UpdateChips];
        [self ShowUserView];
    });
}

-(void)interfacePlayerLeavingTable:(char*)cszRecvBuff {//离桌
    
}

-(void)interfaceAddOtherPlayer:(char*)cszRecvBuff {//添加玩家
    //[协议号(1位ASCII码)][玩家坐位号(1位A码:0~5)][昵称长度(1位A码)][昵称(UTF8)][筹码数(8位十六进制)]
    dispatch_queue_t concurrentQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_sync(concurrentQueue, ^{

        _tableData->_i玩家数量++;//增加桌上人数
        int iPlayNo = cszRecvBuff[1];
        //获取玩家的昵称
        strncpy(_tableData->_csz玩家昵称[iPlayNo], cszRecvBuff+3, cszRecvBuff[2]);
        
        //获取玩家的筹码数
        char cPlayerChips[9] = {0};
        strncpy(cPlayerChips,cszRecvBuff+3+cszRecvBuff[2],8);
        _tableData->_i手上筹码数[iPlayNo] = (int)strtoul(cPlayerChips,0,0x10);

        //对脏区赋值
        _tableData->_bDirtyNickName[iPlayNo] = 1;
        _tableData->_bDirtyChips[iPlayNo] = 1;
        _tableData->_bDirtyUserView[iPlayNo] = 1;
    });

    //在主线程加载UI 给玩家视图赋值
    dispatch_async(dispatch_get_main_queue(), ^{
        [self UpdateNickName];
        [self UpdateChips];
        [self ShowUserView];
    });
}

-(void)interfaceWaitingDealer:(char*)cszRecvBuff {
    //[协议号(1位ASCII码)]
    NSLog(@"等待荷官上线中...");
}

-(void)interfaceStartGame:(char*)cszRecvBuff {//开始比赛（前注、大盲注、小盲注信息）
    //[协议号(1位ASCII码)][庄家坐位号(1位A码)][小盲坐位号(1位A码)][大盲坐位号(1位A码)][大盲注(8位十六进制)][小盲注(8位十六进制)][前注(8位十六进制)]
    //[玩家数量(1位A码)]{[玩家坐位号(1位A码)][玩家当前筹码数(8位十六进制)][玩家当前当前下注数(8位十六进制)]}
    _maxPourBefore = 0;
    
    _tableData->fuck开始比赛清场();
    
    _tableData->_i庄家编号 = cszRecvBuff[1];//庄家的座位号
    _tableData->_i玩家数量 = cszRecvBuff[28];
    
    dispatch_queue_t concurrentQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_sync(concurrentQueue, ^{
        
        char cszTmp[9] ={0};
//        strncpy(cszTmp, cszRecvBuff+4, 8);
//        int ulBigblind = (int)strtoul(cszTmp, 0, 0x10);
        
        for (int i = 0 ; i < _tableData->_i玩家数量; i++) {
            int iPlayerNo = cszRecvBuff[29+(i*17)];
            
            _tableData->_s玩家状态[iPlayerNo] = WJZT_正常玩家;
            
            strncpy(cszTmp, cszRecvBuff+30+(i*17), 8);
            _tableData->_i手上筹码数[iPlayerNo] = (int)strtoul(cszTmp, 0, 0x10);
            
            strncpy(cszTmp, cszRecvBuff+38+(i*17), 8);
            _tableData->_i下注筹码数[iPlayerNo] = (int)strtoul(cszTmp, 0, 0x10);
            
            //获取当前最大注额
            if ( _tableData->_i本轮最大注 < _tableData->_i下注筹码数[iPlayerNo]) {
                _tableData->_i本轮最大注 = _tableData->_i下注筹码数[iPlayerNo];
            }
            
            //设置庄家标志
            if (iPlayerNo == _tableData->_i庄家编号) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    for (int i = 0;i < 6; i++) {
                        [_pourView[i] setBankerMark:NO];
                    }
                    
                    [_pourView[iPlayerNo] setBankerMark:YES];
                });
            }
        }
    });
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self UpdateChips];
        [self UpdatePours];
        [self UpdatePools];
        [self UpdateNickName];
        [self CleanAllPoker];
        
    });
}

-(void)interfaceDealerDear:(char*)cszRecvBuff {//荷官发牌:(每轮下注通知添加在最后)
    //[协议号(1位A码)][坐位号(1位A码:0~5,公牌:88)][牌的编号(1位A码:0~1,公牌:0~4)][花色(1位A码:1~4)][大小(1位A码:1~13)][下注玩家的坐位号(1位A码:1~6,无下注时:88)]
    //发其他玩家的私牌时，具体牌的信息为0
    _tableData->_i当前玩家编号 = 88;
    _tableData->_i下一玩家编号 = cszRecvBuff[5];
 
    int iPlayerNo = cszRecvBuff[1];
    int iPokerNo = cszRecvBuff[2];
    int iPokerHS = cszRecvBuff[3];
    int iPokerDX = cszRecvBuff[4];
 
    if (iPlayerNo != 88) {  //发的是私牌
        _tableData->_s私牌HS[iPlayerNo][iPokerNo] = cszRecvBuff[3];
        _tableData->_s私牌DX[iPlayerNo][iPokerNo] = cszRecvBuff[4];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [_privatePokerImgView[iPlayerNo][iPokerNo] creatImageWithHS:iPokerHS withDX:iPokerDX];
            _privatePokerImgView[iPlayerNo][iPokerNo].origin = CGPointMake(ksboundsWidth/2, 50);
            _privatePokerImgView[iPlayerNo][iPokerNo].hidden = NO;
            
            [UIView animateWithDuration:.5 animations:^{//发公共牌的动画
                if (iPlayerNo == _tableData->_i自身玩家编号) {
                    //记录公牌显示牌的类型 把类型显示在用户名上
                    NSString *pokerTypeStr = _tableData->fuck获取牌类型文本(_tableData->_i自身玩家编号);
                    _userView[_tableData->_i自身玩家编号].username.text = pokerTypeStr;

                    [_privatePokerImgView[iPlayerNo][iPokerNo] changeLastStateOfBigFrameInDealWithPlayerNo:iPlayerNo withPokerNo:iPokerNo];
                }else{
                    [_privatePokerImgView[iPlayerNo][iPokerNo] changeLastStateOfFrameInDealWithPlayerNo:iPlayerNo withPokerNo:iPokerNo];
                }
            }];
            
            //判断是否牌已经发完 可以开局 开始转转
            if (0 <= _tableData->_i下一玩家编号 && _tableData->_i下一玩家编号 <=5) {
                [_userView[_tableData->_i下一玩家编号] startCycle];
                [self switchButtonStatus];
            }
        });
    } else { //公牌

        _tableData->_s公牌HS[iPokerNo] = cszRecvBuff[3];
        _tableData->_s公牌DX[iPokerNo] = cszRecvBuff[4];
        _tableData->_i本轮最大注 = 0;
        _maxPourBefore = 0;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [_commonPokerImgView[iPokerNo] creatImageWithHS:cszRecvBuff[3] withDX:cszRecvBuff[4]];
            _commonPokerImgView[iPokerNo].origin = CGPointMake(ksboundsWidth/2, 50);
            _commonPokerImgView[iPokerNo].hidden = NO;
            [UIView animateWithDuration:.5 animations:^{//发公共牌的动画
                
                [_commonPokerImgView[iPokerNo] changeCommonPokerLastStateOfFrameWithPokerNo:iPokerNo];
            }];
        
            //记录公牌显示牌的类型 把类型显示在用户名上
            NSString *pokerTypeStr = _tableData->fuck获取牌类型文本(_tableData->_i自身玩家编号);
            _userView[_tableData->_i自身玩家编号].username.text = pokerTypeStr;

            //判断是否牌已经发完 可以开局 开始转转
            if (0 <= _tableData->_i下一玩家编号 && _tableData->_i下一玩家编号 <=5) {
                //还原昵称
                for (int i = 0; i < 6; i++) {
                    if (i == _tableData->_i自身玩家编号) { continue; }
                    _tableData->_bDirtyNickName[i] = 1;
                }
                [self UpdateNickName];
                
                [_userView[_tableData->_i下一玩家编号] startCycle];
                [self switchButtonStatus];
            }
        });
    }
}

-(void)interfaceOtherPlayerFold:(char*)cszRecvBuff {//其他玩家 弃牌操作
    //[协议号(1位A码)][弃牌玩家坐位号(1位A码:0~5)][下一操作玩家坐位号(1位A码,88为无下一位玩家)];
    _tableData->_s玩家状态[cszRecvBuff[1]] = WJZT_弃牌玩家;
   
    _tableData->_i当前玩家编号 = cszRecvBuff[1];
    _tableData->_i下一玩家编号 = cszRecvBuff[2];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [_userView[cszRecvBuff[1]] setCoverImgZIndex:YES];
        [_userView[cszRecvBuff[1]] endCycle];
        
        //显示弃牌，隐藏Poker
        _userView[cszRecvBuff[1]].username.text = @"弃牌";
        _privatePokerImgView[cszRecvBuff[1]][0].hidden = YES;
        _privatePokerImgView[cszRecvBuff[1]][1].hidden = YES;
        
        //判断是否收注
        if (cszRecvBuff[2] == 88) {
            [self gatherPour];
        }else{
            [_userView[cszRecvBuff[2]] startCycle];
        }
        
        [self switchButtonStatus];
    });
}

-(void)interfaceOtherPlayerCheck:(char*)cszRecvBuff {//让牌操作
    //[协议号(1位A码)][让牌玩家坐位号(1位A码:0~5)][下一操作玩家坐位号(1位A码,88为无下一位玩家)];
    _tableData->_i当前玩家编号 = cszRecvBuff[1];
    _tableData->_i下一玩家编号 = cszRecvBuff[2];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        //显示操作
        _userView[cszRecvBuff[1]].username.text = @"让牌";
        
        //判断是否收注
        [_userView[cszRecvBuff[1]] endCycle];
        
        if (cszRecvBuff[2] == 88) {
            [self gatherPour];
        }else{
            [_userView[cszRecvBuff[2]] startCycle];
        }
        
        [self switchButtonStatus];
    });
}

-(void)interfaceAllPlayerPour:(char*)cszRecvBuff {//所有玩家 下注\跟注\ALLIN操作
    //[协议号(1位A码)][下注玩家坐位号(1位A码:0~5)][下注筹码数(8位十六进制)][下一操作玩家坐位号(1位A码,88为无下一位玩家)];
    _tableData->_i当前玩家编号 = cszRecvBuff[1];
    _tableData->_i下一玩家编号 = cszRecvBuff[10];
        
    int iPlayerNo = cszRecvBuff[1];//当前下注的玩家
    
    //获取下注筹码数
    char cszPour[9] = {0};
    strncpy(cszPour, cszRecvBuff+2, 8);
    unsigned long ulPour = strtoul(cszPour, 0, 0x10);
    
    //更新筹码
    _tableData->_i手上筹码数[iPlayerNo] -= ulPour;
    _tableData->_i下注筹码数[iPlayerNo] += ulPour;
    
    //显示操作 更新本轮最大筹码数
    if (0 == _tableData->_i手上筹码数[iPlayerNo] ) {
        _tableData->_s玩家状态[iPlayerNo] = WJZT_本轮饿赢;
        dispatch_async(dispatch_get_main_queue(), ^{
            _userView[iPlayerNo].username.text = @"All In";
        });
        
    } else if (_tableData->_i本轮最大注 == _tableData->_i下注筹码数[iPlayerNo]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            _userView[iPlayerNo].username.text = @"跟注";
        });
        
    } else if (_tableData->_i本轮最大注 < _tableData->_i下注筹码数[iPlayerNo]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            _userView[iPlayerNo].username.text = @"加注";
        });
    }
    
    //更新最大注
    if (_tableData->_i下注筹码数[iPlayerNo] > _tableData->_i本轮最大注) {
        _tableData->_i本轮最大注 = _tableData->_i下注筹码数[iPlayerNo];
    }
    
    //更新脏区
    _tableData->_bDirtyPour[iPlayerNo] = 1;
    _tableData->_bDirtyChips[iPlayerNo] = 1;
    
    //更新其他玩家的UI
    dispatch_async(dispatch_get_main_queue(), ^{
        [self UpdatePours];
        [self UpdateChips];
   
        [_userView[cszRecvBuff[1]] endCycle];
        if (88 == cszRecvBuff[10]) {
            [self gatherPour];    
        }else {
            [_userView[cszRecvBuff[10]] startCycle];
        }
        
        [self switchButtonStatus];
    });
}

-(void)interfaceOpenPokerOfOtherPlayer:(char*)cszRecvBuff {//玩家明牌
    //[协议号(1位A码)][玩家人数(1位A码)]
    //{[玩家坐位号(1位A码:05)][花色(1位A码:14)][大小(1位A码:1~13)][花色(1位A码:14)][大小(1位A码:1~13)]}
    int iCount = 2;
    int iPlayerNo;
    for (int i = 0; i < cszRecvBuff[1]; i++) {
        iPlayerNo = cszRecvBuff[iCount];
        
        _tableData->_s私牌HS[iPlayerNo][0] = cszRecvBuff[iCount+1];
        _tableData->_s私牌DX[iPlayerNo][0] = cszRecvBuff[iCount+2];
        _tableData->_s私牌HS[iPlayerNo][1] = cszRecvBuff[iCount+3];
        _tableData->_s私牌DX[iPlayerNo][1] = cszRecvBuff[iCount+4];
        
        iCount += 5;
    }
    
    //更新其他玩家的牌型UI
    dispatch_async(dispatch_get_main_queue(), ^{
        [self updateOpenPoker];
    });
}

-(void)interfaceGameResults:(char*)cszRecvBuff {//比赛结果：需要比牌
    sleep(.6);//等待收注动画完成
    
    //[协议号(1位A码)][赢家人数(1位A码)]{[赢家坐位号(1位A码:0~5)][筹码数(8位十六进制)]}
    //计算输赢情况
    _tableData->fuck结束比赛();
    
    dispatch_async(dispatch_get_main_queue(), ^{
        for (int i = 0; i < 6; i++) {
            if (_tableData->_s玩家状态[i] <= WJZT_有效玩家) { continue; }
            _userView[i].username.text = _tableData->fuck获取牌类型文本(i);
        }
    });

    for (int i = 4; i >= 0; i--) {
        if (0 == _tableData->_i边池筹码数[i]) { continue; }
        
        [self MatchResultAnimatonWithPoolNo:i];
        return;
    }
}

-(void)interfaceEndGame:(char*)cszRecvBuff {//结束比赛:不需要比牌
    sleep(1);//等待收注动画完成
    //[协议号(1位A码)][赢家坐位号(1位A码:0~5)][筹码数(8位十六进制)]
    
    int iPlayerPos = cszRecvBuff[1];
    
    char cszChip[9] ={0};
    strncpy(cszChip, cszRecvBuff+2, 8);
    unsigned long ulChip = strtoul(cszChip, 0, 0x10);

    _tableData->_i手上筹码数[iPlayerPos] += ulChip;
    _tableData->_bDirtyChips[iPlayerPos] = 1;

    _tableData->_i边池筹码数[0] = 0;
    
    CABasicAnimation *resultAnima = [CABasicAnimation animationWithKeyPath:@"position"];
    resultAnima.delegate = self;
    resultAnima.duration = 1.8f;
    resultAnima.beginTime = CACurrentMediaTime();
    resultAnima.removedOnCompletion = YES;
    CGFloat x = _poolBGView.origin.x + _poolView[0].center.x;
    CGFloat y = _poolBGView.origin.y + _poolView[0].center.y;
    resultAnima.fromValue = [NSValue valueWithCGPoint:CGPointMake(x, y)];
    resultAnima.toValue = [NSValue valueWithCGPoint:_userView[iPlayerPos].center];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        _poolView[0].hidden = YES;
        [_movingChipView[iPlayerPos].layer addAnimation:resultAnima forKey:nil];
//        _movingChipView[iPlayerPos].hidden = NO;

        [self UpdateChips];
    });
}

//- (void)handleMachMessage:(void *)msg {
//
//    [self.notificationLock lock];
//    
//    while ([self.notifications count]) {
//        NSNotification *notification = [self.notifications objectAtIndex:0];
//        [self.notifications removeObjectAtIndex:0];
//        [self.notificationLock unlock];
//        [self 通知_收到服务器消息:notification];
//        [self.notificationLock lock];
//    };
//    
//    [self.notificationLock unlock];
//}
