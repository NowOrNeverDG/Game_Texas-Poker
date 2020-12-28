
-(void)gatherPourToCenterAnimation {
    int iCount = 0;
    for (int i = 0; i < 6; i++) {//六个人
        if (0 == _tableData->_i下注筹码数[i]) { continue; }
        iCount = i;
    }
    
    for (int i = 0; i < 6; i++) {
        if (0 == _tableData->_i下注筹码数[i]) { continue; }
        
        CABasicAnimation *resultAnima = [CABasicAnimation animationWithKeyPath:@"position"];
        resultAnima.delegate = self;
        resultAnima.duration = .5f;
        resultAnima.beginTime = CACurrentMediaTime();
        resultAnima.removedOnCompletion = YES;
        resultAnima.fromValue = [NSValue valueWithCGPoint:_movingChipStartOrigin[i]];
        resultAnima.toValue = [NSValue valueWithCGPoint:CGPointMake(ksboundsWidth/2, 160)];
        
        NSString *animValueStr = (iCount != i) ? @"gatherPoolAnima":@"gatherPoolLastAnima";
        [resultAnima setValue:animValueStr forKey:@"gatherPoolAnimation"];
        
        dispatch_async(dispatch_get_main_queue(), ^{
//            _movingChipView[i].hidden = NO;
            [_movingChipView[i].layer addAnimation:resultAnima forKey:@"gatherPoolAnimation"];
        });
    }
}

-(void)MatchResultAnimatonWithPoolNo:(int)iPoolNo {
    int iCount = 0;
    for (int i = 0; i < 6; i++) {//六个人
        if (_tableData->_iczMatchResult[iPoolNo][i] == 0) { continue; }
        iCount = i;
    }
        
    for (int i = 0; i < 6; i++) {//六个人
        if (_tableData->_iczMatchResult[iPoolNo][i] == 0) { continue; }
        
        [self UpdatefloatPokerWithIplayerPos:i];
        
        
        CABasicAnimation *resultAnima = [CABasicAnimation animationWithKeyPath:@"position"];
        resultAnima.delegate = self;
        resultAnima.duration = 1.8f;
        resultAnima.beginTime = CACurrentMediaTime();
        resultAnima.removedOnCompletion = YES;
        CGFloat x = _poolBGView.origin.x + _poolView[iPoolNo].center.x;
        CGFloat y = _poolBGView.origin.y + _poolView[iPoolNo].center.y;
        resultAnima.fromValue = [NSValue valueWithCGPoint:CGPointMake(x, y)];
        resultAnima.toValue = [NSValue valueWithCGPoint:_userView[i].center];
        NSString *animValueStr = (iCount != i) ? @"fenPoolAnimGroup":[NSString stringWithFormat:@"fenPoolAnimGroup%d",iPoolNo];
        [resultAnima setValue:animValueStr forKey:@"groupAnimation"];
        
        _tableData->_i手上筹码数[i] +=  _tableData->_iczMatchResult[iPoolNo][i];
        _tableData->_i边池筹码数[iPoolNo] = 0;
        _tableData->_bDirtyPool[iPoolNo] = 1;
        _tableData->_bDirtyChips[i] = 1;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [_movingChipView[i].layer addAnimation:resultAnima forKey:@"groupAnimation"];
//            _movingChipView[i].hidden = NO;

            [self UpdatePools];
            [self UpdateChips];
        });
    }
}

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag {
    if([[anim valueForKey:@"groupAnimation"] isEqualToString:@"fenPoolAnimGroup4"]) {
        [self hiddenFloatBGView];
        [self MatchResultAnimatonWithPoolNo:3];
        
    } else if ([[anim valueForKey:@"groupAnimation"] isEqualToString:@"fenPoolAnimGroup3"]) {
        [self hiddenFloatBGView];
        [self MatchResultAnimatonWithPoolNo:2];
        
    } else if ([[anim valueForKey:@"groupAnimation"] isEqualToString:@"fenPoolAnimGroup2"]) {
        [self hiddenFloatBGView];
        [self MatchResultAnimatonWithPoolNo:1];
        
    } else if ([[anim valueForKey:@"groupAnimation"] isEqualToString:@"fenPoolAnimGroup1"]) {
        [self hiddenFloatBGView];
        [self MatchResultAnimatonWithPoolNo:0];
    } else if ([[anim valueForKey:@"groupAnimation"] isEqualToString:@"fenPoolAnimGroup0"]) {
        [self hiddenFloatBGView];
        
    } else if ([[anim valueForKey:@"gatherPoolAnimation"] isEqualToString:@"gatherPoolLastAnima"]) {
//        for (int i = 0; i < 6; i++) {
//            _movingChipView[i].hidden = YES;
//        }
        [self setPoolFrame];
    }
}

-(void)hiddenFloatBGView {
    for (int i = 0; i < 6; i++) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [_privatePokerImgView[i][0] hiddenFloatBGview];
            [_privatePokerImgView[i][1] hiddenFloatBGview];
        });
    }
    
    for (int i = 0; i < 5; i++) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [_commonPokerImgView[i] hiddenFloatBGview];
        });
    }
}

//-(void)dispensePoolsToWinner {
//    int winnerPos = 0;
//    for (int i = 0; i < 6; i++) {
//        if (_tableData->_s玩家状态[i] <= WJZT_正常玩家) { continue; }
//        winnerPos = i;
//    }
//    
//        CABasicAnimation *resultAnima = [CABasicAnimation animationWithKeyPath:@"position"];
//        resultAnima.delegate = self;
//        resultAnima.duration = 1.8f;
//        resultAnima.beginTime = CACurrentMediaTime();
//        resultAnima.removedOnCompletion = YES;
//        resultAnima.fromValue = [NSValue valueWithCGPoint:CGPointMake(58, 15)];
//        resultAnima.toValue = [NSValue valueWithCGPoint:_userView[winnerPos].center];
//        dispatch_async(dispatch_get_main_queue(), ^{
//            [_movingChipView[winnerPos].layer addAnimation:resultAnima forKey:@"groupAnimation"];
//            _movingChipView[winnerPos].hidden = NO;
//        });
//}
//-(void)showPourToPoolAnimation:(int)iPourPos {
//        CABasicAnimation *anima = [CABasicAnimation animationWithKeyPath:@"position"];
//        anima.delegate = self;
//        anima.fromValue = [NSValue valueWithCGPoint:CGPointMake(0, 0)];
//        anima.toValue = [NSValue valueWithCGPoint:CGPointMake(0, 100)];
//        anima.duration = 1.0f;
//        anima.removedOnCompletion= NO;
//        //[UIView setAnimationDidStopSelector:@selector(otherAnimation)];
//        //view.frame = CGRectMake(0, 100, 100, 100);
//        [view.layer addAnimation:anima forKey:@"positionAnimation"];
    
    //创建边池label
    //    __block UILabel *insideSidepotLB = (UILabel*)[self.view viewWithTag:6];
    //    if (insideSidepotLB == nil) {
    //        insideSidepotLB = [[UILabel alloc] initWithFrame:CGRectMake((6-100)*55,0,53,15)];
    //        //insideSidepotLB.backgroundColor = [UIColor redColor];
    //        insideSidepotLB.font = [UIFont systemFontOfSize:10];
    //        insideSidepotLB.textAlignment = NSTextAlignmentCenter;
    //
    //        __block UIImageView *sidepLabelImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"带筹码框.png"]];
    //        sidepLabelImgView.frame = insideSidepotLB.bounds;
    //        [insideSidepotLB addSubview: sidepLabelImgView];
    //    }
    
    //找到需要收注的玩家
    //    _userView = [self.view viewWithTag:[_PlayerNoArr[_igatherPourCount] intValue]];
    
    //设置移动筹码动画中的各点
    //__block CGFloat fMovedx = _sidepot.origin.x + insideSidepotLB.center.x;
    //__block CGFloat fMovedy = _sidepot.origin.y + insideSidepotLB.center.y;
    //__block CGFloat fWillMovex = _userView[_PlayerNoArr[_igatherPourCount] intValue].origin.x + _userView[_PlayerNoArr[_igatherPourCount] intValue].pourBGImgView.origin.x;
    //__block CGFloat fWillMovey = _userView[_PlayerNoArr[_igatherPourCount] intValue].origin.y + _userView[_PlayerNoArr[_igatherPourCount] intValue].pourBGImgView.origin.y;
    
    //    dispatch_async(dispatch_get_main_queue(), ^{
    
    
    //        _movingChipImgView.center = CGPointMake(fWillMovex, fWillMovey);
    //        [UIView animateWithDuration:1.2 animations:^{//发公共牌的时候，都会将注额收进奖池
    //
    //            _movingChipImgView.center = CGPointMake(fMovedx, fMovedy);
    //        }completion:^(BOOL finished) {
    //
    //            //创建label 并赋值
    //            [self.sidepot addSubview:insideSidepotLB];
    //            insideSidepotLB.text = [NSString stringWithFormat:@"%d",[insideSidepotLB.text intValue] + [_userView.forepour.text intValue]];
    //
    //            if(_igatherPourCount >= _iCount-1){
    //                [_movingChipImgView removeFromSuperview];
    //                return;
    //            }
    //            ++_igatherPourCount;
    //            [self gatherPourToSidepotAnimation];
    
    //        }];
    //    });
//}
