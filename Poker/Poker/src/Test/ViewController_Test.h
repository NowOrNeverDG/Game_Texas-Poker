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

-(void)testFunc {
    return;
    
    //测试区：
    _iTmp = 0;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        UIButton *testFoldButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [testFoldButton setTitle:@"弃牌" forState:UIControlStateNormal];
        testFoldButton.frame =  CGRectMake(80, 10, 45, 45);
        testFoldButton.backgroundColor = [UIColor blackColor];
        [testFoldButton addTarget:self action:@selector(testFoldButton:) forControlEvents:UIControlEventTouchUpInside];
        
        UIButton *testAddButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [testAddButton setTitle:@"出百" forState:UIControlStateNormal];
        testAddButton.frame =  CGRectMake(130, 10, 45, 45);
        testAddButton.backgroundColor = [UIColor blackColor];
        [testAddButton addTarget:self action:@selector(testAddButton:) forControlEvents:UIControlEventTouchUpInside];
        
        UIButton *testCheckButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [testCheckButton setTitle:@"让牌" forState:UIControlStateNormal];
        testCheckButton.frame =  CGRectMake(180, 10, 45, 45);
        testCheckButton.backgroundColor = [UIColor blackColor];
        [testCheckButton addTarget:self action:@selector(testCheckButton:) forControlEvents:UIControlEventTouchUpInside];
        
        UIButton *testGatherButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [testGatherButton setTitle:@"赛果" forState:UIControlStateNormal];
        testGatherButton.frame =  CGRectMake(230, 10, 45, 45);
        testGatherButton.backgroundColor = [UIColor blackColor];
        [testGatherButton addTarget:self action:@selector(testGatherButton:) forControlEvents:UIControlEventTouchUpInside];
        
        UIButton *testOpenButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [testOpenButton setTitle:@"明牌" forState:UIControlStateNormal];
        testOpenButton.frame =  CGRectMake(280, 10, 45, 45);
        testOpenButton.backgroundColor = [UIColor blackColor];
        [testOpenButton addTarget:self action:@selector(testOpenPokerButton:) forControlEvents:UIControlEventTouchUpInside];
        
        [self.view addSubview:testCheckButton];
        [self.view addSubview:testFoldButton];
        [self.view addSubview:testAddButton];
        [self.view addSubview:testGatherButton];
        [self.view addSubview:testOpenButton];
    });
    
    dispatch_queue_t queue = dispatch_queue_create("socketQueue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_sync(queue, ^{
        
        char csz1[256] = { 0 };
        [self testWith:MsgFromServer_玩家上桌 csz:csz1];
        NSData *data1 = [NSData dataWithBytes:csz1 length:256];
        NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz1)];
        NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
        NSNotification *notification1 =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data1 userInfo:recvLenDic];
        [[NSNotificationCenter defaultCenter] postNotification:notification1];
        
        char csz2[32] = { 0 };
        [self testWith:MsgFromServer_添加玩家 csz:csz2];
        NSData *data2 = [NSData dataWithBytes:csz2 length:32];
        str = [NSString stringWithFormat:@"%lu",sizeof(csz2)];
        recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
        NSNotification *notification2 =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data2 userInfo:recvLenDic];
        [[NSNotificationCenter defaultCenter] postNotification:notification2];

        char csz3[256] = { 0 };
        [self testWith:MsgFromServer_开始比赛 csz:csz3];
        NSData *data3 = [NSData dataWithBytes:csz3 length:256];
        str = [NSString stringWithFormat:@"%lu",sizeof(csz3)];
        recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
        NSNotification *notification3 =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data3 userInfo:recvLenDic];
        [[NSNotificationCenter defaultCenter] postNotification:notification3];


    });
}

-(void)testWith:(int)protocolNo csz:(char*)cszRTN {
    switch (protocolNo) {
        case MsgFromServer_玩家上桌:{
            char csz[] = "xx1xxxx丫000001400xx牛100001500xx王200001600xx张300001700xx赵400001800";
            int iLen = (int)strlen(csz);
            csz[0] = 0;
            csz[1] = iLen - 2;
            
            csz[2] = MsgFromServer_玩家上桌;
            csz[3] = 5;//玩家人数
            csz[4] = 3;//玩家自己的编号
            
            csz[5] = 0;//玩家编号0
            csz[6] = 4;
            csz[19] = 1;//玩家编号1
            csz[20] = 4;
            csz[33] = 2;//玩家编号2
            csz[34] = 4;
            csz[47] = 3;//玩家编号3
            csz[48] = 4;
            csz[61] = 4;//玩家编号4
            csz[62] = 4;
            memcpy(cszRTN, csz, iLen);
            break;
        }
        case MsgFromServer_添加玩家: {
            //#define MsgFromServer_添加玩家 50
            //[协议号(1位ASCII码)][玩家坐位号(1位A码:0~5)][昵称长度(1位A码)][昵称(UTF8)][筹码数(8位十六进制)]
            char csz[] = "xxxxx增500002000";
            int iLen = (int)strlen(csz);
            csz[0] = 0;
            csz[1] = iLen - 2;
            
            csz[2] = MsgFromServer_添加玩家;
            csz[3] = 5;
            csz[4] = 4;
            memcpy(cszRTN, csz, iLen);
            break;
        }
        case MsgFromServer_开始比赛: {
            //[协议号(1位ASCII码)][庄家坐位号(1位A码)][小盲坐位号(1位A码)][大盲坐位号(1位A码)][大盲注(8位十六进制)][小盲注(8位十六进制)][前注(8位十六进制)]
            //[玩家数量(1位A码)]{[玩家坐位号(1位A码)][玩家当前筹码数(8位十六进制)][玩家当前当前下注数(8位十六进制)]}
            //#define MsgFromServer_开始比赛 53
            char csz[] = "xxxxxx000002000000015000000100xx0000010000001300x0000010000001400x0000010000000900x0000010000001600x0000010000001000x0000010000000700";
            int iLen = (int)strlen(csz);
            csz[0] = 0;
            csz[1] = iLen - 2;
            
            csz[2] = MsgFromServer_开始比赛;
            csz[3] = 0;
            csz[4] = 1;
            csz[5] = 2;
            csz[30] = 6;
            csz[31] = 0;//1号玩家设置筹码和下注数
            csz[48] = 1;
            csz[65] = 2;
            csz[82] = 3;
            csz[99] = 4;
            csz[116] = 5;
            memcpy(cszRTN, csz, iLen);
            break;
        }

    }
    return;
}

-(void)leftArrowAction {
    //[协议号(1位A码)][坐位号(1位A码:0~5,公牌:88)][牌的编号(1位A码:0~1,公牌:0~4)][花色(1位A码:1~4)][大小(1位A码:1~13)][下注玩家的坐位号(1位A码:1~6,无下注时:88)]
    char csz_Deal[8] = {0};
    csz_Deal[0] = 0;
    csz_Deal[1] = sizeof(csz_Deal) - 2;
    csz_Deal[2] = MsgFromServer_荷官发牌;
    
    if (_iTmp <= 5) {
//        csz_Deal[3] = 88;
//        csz_Deal[4] = _iTmp;
        csz_Deal[3] = _iTmp;
        csz_Deal[4] = 0;
        csz_Deal[5] = 0;//花色
        csz_Deal[6] = 0;//大小
        csz_Deal[7] = 88;
    } else if (6 <= _iTmp &&  _iTmp < 11){
            csz_Deal[3] = _iTmp%6;
            csz_Deal[4] = 1;
            csz_Deal[5] = 0;//花色
            csz_Deal[6] = 0;//大小
            csz_Deal[7] = 88;
    } else if ( _iTmp == 11) {
        csz_Deal[3] = 5;
        csz_Deal[4] = 1;
        csz_Deal[5] = 0;//花色
        csz_Deal[6] = 0;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 12) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 0;
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 14;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 13) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 1;
        csz_Deal[5] = 4;//花色
        csz_Deal[6] = 14;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 14) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 2;
        csz_Deal[5] = 2;//花色
        csz_Deal[6] = 5;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 15) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 3;
        csz_Deal[5] = 4;//花色
        csz_Deal[6] = 9;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 16) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 4;
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 8;//大小
        csz_Deal[7] = 0;
    } 



    
    if (_iTmp == 3) {
        csz_Deal[5] = 1;//花色
        csz_Deal[6] = 14;//大小
    }
    if (_iTmp == 9) {
        csz_Deal[5] = 2;//花色
        csz_Deal[6] = 14;//大小
    }
    _iTmp++;
    
    NSData *data = [NSData dataWithBytes:csz_Deal length:16];
    NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz_Deal)];
    NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:recvLenDic];
    [[NSNotificationCenter defaultCenter] postNotification:notification];
}

//-(void)playerOperation {
//    
//    _tableData->test();
//    
//    dispatch_async(dispatch_get_main_queue(), ^{
//        [self UpdateNickName];
//        [self UpdateChips];
//        [self ShowUserView];
//        [self UpdatePours];
//        [self UpdatePools];
//        
//        [_pourView[1] setBankerMark:YES];
//        
//        for (int i = 0; i < 6; i++) {
//            if (_tableData->_i自身玩家编号 == i) {
//                [_userView[i] setIsSelf];
//                [_userView[i] setPokersSize:YES];
//            }else{
//                [_userView[i] setPokersSize:NO];
//            }
//            _userView[i].firstPoker.image = [UIImage imageNamed:@"扑克背面.png"];
//            _userView[i].secondPoker.image = [UIImage imageNamed:@"方块_14.png"];
//        }
//        
//        for (int i = 0; i < 5; i++) {
//            _commonPokerImgView[i].hidden = NO;
//            _commonPokerImgView[i].image = [UIImage imageNamed:@"方块_14.png"];
//        }
//    });
//    return;
//}

-(void)rightArrowAction {
    _socketClient->fuck上桌();
}

-(void)testFoldButton:(UIButton*)foldButton {
    //[协议号(1位A码)][弃牌玩家坐位号(1位A码:0~5)][下一操作玩家坐位号(1位A码,88为无下一位玩家)];
    char csz_FoldOP[5] = { 0 };
    csz_FoldOP[0] = 0;
    csz_FoldOP[1] = sizeof(csz_FoldOP) - 2;
    csz_FoldOP[2] = MsgFromServer_玩家弃牌;
    csz_FoldOP[3] = _tableData->_i下一玩家编号;
    csz_FoldOP[4] = _tableData->_i下一玩家编号+1;
    if (csz_FoldOP[3] == 5) {
        csz_FoldOP[4] = 88; }
    NSData *data = [NSData dataWithBytes:csz_FoldOP length:5];
    NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz_FoldOP)];
    NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:recvLenDic];
    [[NSNotificationCenter defaultCenter] postNotification:notification];
    
}

-(void)testAddButton:(UIButton*)callButton {
    //[协议号(1位A码)][下注玩家坐位号(1位A码:0~5)][下注筹码数(8位十六进制)][下一操作玩家坐位号(1位A码,88为无下一位玩家)];
    char csz_CallOP[] = "xxxx00000100x";
    csz_CallOP[0] = 0;
    csz_CallOP[1] = sizeof(csz_CallOP) - 2;
    csz_CallOP[2] = MsgFromServer_玩家下注;
    csz_CallOP[3] = _tableData->_i下一玩家编号;
    csz_CallOP[12] = _tableData->_i下一玩家编号+1;
    NSData *data = [NSData dataWithBytes:csz_CallOP length:16];
    if (csz_CallOP[12] == 6) {
        csz_CallOP[12] = 88; }
    NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz_CallOP)];
    NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:recvLenDic];
    [[NSNotificationCenter defaultCenter] postNotification:notification];
}

-(void)testAllInButton:(UIButton*)AllInButton {
    //[协议号(1位A码)][下注玩家坐位号(1位A码:0~5)][下注筹码数(8位十六进制)][下一操作玩家坐位号(1位A码,88为无下一位玩家)];
//    char csz_CallOP[] = "xxxx00000100x";
//    csz_CallOP[0] = 0;
//    csz_CallOP[1] = sizeof(csz_CallOP) - 2;
//    csz_CallOP[2] = MsgFromServer_玩家下注;
//    csz_CallOP[3] = _tableData->_i下一玩家编号;
//    csz_CallOP[12] = _tableData->_i下一玩家编号+1;
//    NSData *data = [NSData dataWithBytes:csz_CallOP length:16];
//    if (csz_CallOP[4] == 5) { csz_CallOP[4] = 88; }
//    NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz_CallOP)];
//    NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
//    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:recvLenDic];
//    [[NSNotificationCenter defaultCenter] postNotification:notification];

}

-(void)testCheckButton:(UIButton*)checkButton {
    //[协议号(1位A码)][让牌玩家坐位号(1位A码:0~5)][下一操作玩家坐位号(1位A码,88为无下一位玩家)];
    char csz_CheckOP[16] = { 0 };
    csz_CheckOP[0] = 0;
    csz_CheckOP[1] = sizeof(csz_CheckOP) - 2;
    csz_CheckOP[2] = MsgFromServer_玩家让牌;
    csz_CheckOP[3] = _tableData->_i下一玩家编号;
    csz_CheckOP[4] = _tableData->_i下一玩家编号+1;
    if (csz_CheckOP[3] == 5) { csz_CheckOP[4] = 88; }
    NSData *data = [NSData dataWithBytes:csz_CheckOP length:16];
    NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz_CheckOP)];
    NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:recvLenDic];
    [[NSNotificationCenter defaultCenter] postNotification:notification];
}

-(void)testGatherButton:(UIButton*)gatherPourButton {
    //[协议号(1位A码)][赢家人数(1位A码)]{[赢家坐位号(1位A码:0~5)][筹码数(8位十六进制)]}
    char csz_FinishOP[] = "xxxxx00005000x00003000";
    
    csz_FinishOP[0] = 0;
    csz_FinishOP[1] = sizeof(csz_FinishOP) - 2;
    csz_FinishOP[2] = MsgFromServer_比赛结果;
    csz_FinishOP[3] = 2;
    csz_FinishOP[4] = 3;
    csz_FinishOP[13] = 2;
    NSData *data = [NSData dataWithBytes:csz_FinishOP length:sizeof(csz_FinishOP)];
    NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz_FinishOP)];
    NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:recvLenDic];
    [[NSNotificationCenter defaultCenter] postNotification:notification];

//    //[协议号(1位A码)][赢家坐位号(1位A码:0~5)][筹码数(8位十六进制)]
//    char csz_CheckOP[] = "xx00000750";
//    csz_CheckOP[0] = MsgFromServer_结束比赛;
//    csz_CheckOP[1] = 5;
//    NSData *data = [NSData dataWithBytes:csz_CheckOP length:16];
//    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:nil];
//    [[NSNotificationCenter defaultCenter] postNotification:notification];
}

-(void)testOpenPokerButton:(UIButton*)openPokerButton {
    //[协议号(1位A码)][玩家人数(1位A码)]
    //{[玩家坐位号(1位A码:05)][花色(1位A码:14)][大小(1位A码:1~13)][花色(1位A码:14)][大小(1位A码:1~13)]}
    char csz_CheckOP[] = "xxxxxxxxxxxxxx";
    csz_CheckOP[0] = 0;
    csz_CheckOP[1] = sizeof(csz_CheckOP) - 2;
    csz_CheckOP[2] = MsgFromServer_玩家明牌;
    csz_CheckOP[3] = 2;
    csz_CheckOP[4] = 1;//玩家座位号
    csz_CheckOP[5] = 2;
    csz_CheckOP[6] = 6;
    csz_CheckOP[7] = 2;
    csz_CheckOP[8] = 7;
    csz_CheckOP[9] = 2;//玩家座位号
    csz_CheckOP[10] = 3;
    csz_CheckOP[11] = 7;
    csz_CheckOP[12] = 3;
    csz_CheckOP[13] = 8;
    NSData *data = [NSData dataWithBytes:csz_CheckOP length:sizeof(csz_CheckOP)];
    NSString *str = [NSString stringWithFormat:@"%lu",sizeof(csz_CheckOP)];
    NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:str,@"RecvLen",nil];
    NSNotification *notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data userInfo:recvLenDic];
    [[NSNotificationCenter defaultCenter] postNotification:notification];
}
