
-(void)UpdateNickName {//更新用户昵称
    for (int i = 0; i < 6; i++ ) {
        if (1 == _tableData->_bDirtyNickName[i]) {
            _userView[i].username.text = [NSString stringWithUTF8String:_tableData->_csz玩家昵称[i]];
            _tableData->_bDirtyNickName[i] = 0;
        }
    }
}

-(void)UpdateChips {//更新筹码数
    for (int i = 0; i < 6; i++ ) {
        if (1 == _tableData->_bDirtyChips[i]) {
            NSString* strTmp = [NSString stringWithFormat:@"%d",_tableData->_i手上筹码数[i]];
            _userView[i].chipLabel.text =  [NSString stringWithFormat:@"%@",strTmp];
            _tableData->_bDirtyChips[i] = 0;
        }
    }
}

-(void)ShowUserView {//隐藏和显示UserView
    for (int i = 0; i < 6; i++ ) {
        if (1 == _tableData->_bDirtyUserView[i]) {
            _userView[i].hidden = NO;
        }
        
        else if (99 == _tableData->_bDirtyUserView[i]) {
            _userView[i].hidden = YES;
        }
        
        _tableData->_bDirtyUserView[i] = 0;
    }
}

-(void)UpdatePours {//更新注额
    for (int i = 0; i < 6; i++ ) {
        if (1 == _tableData->_bDirtyPour[i]) {
            if (0 == _tableData->_i下注筹码数[i]) {
                _pourView[i].hidden = YES;
            }else{
            NSString* strTmp = [NSString stringWithFormat:@"%d",_tableData->_i下注筹码数[i]];
            _pourView[i].pourLabel.text =  [NSString stringWithFormat:@"%@",strTmp];
            _pourView[i].hidden = NO;
            }
            _tableData->_bDirtyPour[i] = 0;
        }
    }
}

-(void)UpdatePools {//更新边池
    
    for (int i = 0; i < 6; i++ ) {
        if (1 == _tableData->_bDirtyPool[i]) {
                if (0 == _tableData->_i边池筹码数[i]) {
                    _poolView[i].hidden = YES;
                }else {
                    NSString* strTmp = [NSString stringWithFormat:@"%d",_tableData->_i边池筹码数[i]];
                    _poolView[i].poolLabel.text =  [NSString stringWithFormat:@"%@",strTmp];
                    _poolView[i].hidden = NO;
                }
            _tableData->_bDirtyPool[i] = 0;
        }
    }
}

-(void)updateOpenPoker {
    for (int i = 0; i < 6; i++) {
        if (i == _tableData->_i自身玩家编号 || _tableData->_s玩家状态[i] < WJZT_有效玩家) { continue; }
        
        //设置其他玩家的明牌牌型
        dispatch_async(dispatch_get_main_queue(), ^{
            [_privatePokerImgView[i][0] creatImageWithHS:_tableData->_s私牌HS[i][0] withDX:_tableData->_s私牌DX[i][0]];
            [_privatePokerImgView[i][1] creatImageWithHS:_tableData->_s私牌HS[i][1] withDX:_tableData->_s私牌DX[i][1]];
            
            [_privatePokerImgView[i][0] changeLastStateOfBigFrameInDealWithPlayerNo:i withPokerNo:0];
            [_privatePokerImgView[i][1] changeLastStateOfBigFrameInDealWithPlayerNo:i withPokerNo:1];
        });
    }
}

-(void)CleanAllPoker {
    for (int i = 0; i < 5; i++) {
        _commonPokerImgView[i].hidden = YES;
    }
    for (int i = 0; i < 6; i++) {
        _privatePokerImgView[i][0].hidden = YES;
        _privatePokerImgView[i][1].hidden = YES;
    }
    for (int i = 0; i < 6; i++) {
        [_privatePokerImgView[i][0] hiddenFloatBGview];
        [_privatePokerImgView[i][1] hiddenFloatBGview];
    }
    for (int i = 0; i < 5; i++) {
        [_commonPokerImgView[i] hiddenFloatBGview];
    }
    for (int i = 0; i < 6; i++) {
        [_userView[i] setCoverImgZIndex:NO];
        
    }
    
    
}
-(void)gatherPour {
    
    [self gatherPourToCenterAnimation];
    
    _tableData->fuck收注();
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self UpdatePours];
    });
}

-(void)setPoolFrame {
    
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self UpdatePools];
    });
    
    int iPoolCount = 0;
    for (int i = 0; i < 6; i++ ) {
        if (0 == _tableData->_i边池筹码数[i]) { continue; }
        iPoolCount++;
    }

    dispatch_async(dispatch_get_main_queue(), ^{
        
        self.poolBGView.size = CGSizeMake(iPoolCount*58, 15);
        self.poolBGView.center = CGPointMake(ksboundsWidth/2, 150);
    });
    
    int iPoolNo = 0;
    for (int i = 0; i < 6; i++ ) {
        if (0 == _tableData->_i边池筹码数[i]) { continue; }
        dispatch_async(dispatch_get_main_queue(), ^{
           _poolView[i].origin = CGPointMake(iPoolNo*58, 0);
        });
        iPoolNo++;
    }
}

-(void)switchButtonStatus {
    if (_tableData->_i当前玩家编号 == 88) {//本轮首次下注
        if (_tableData->_s玩家状态[_tableData->_i自身玩家编号] != WJZT_正常玩家) {
            return [self HiddenAllButtomButton];
        }
        
        if (_tableData->_i下一玩家编号 == _tableData->_i自身玩家编号) {//如果首次下注是本人
            return [self showMyselfButtomButton];
        } else {
            //如果首次下注是其他玩家
            return [self showOtherButtomButton];
        }
    }
    
     if ((_tableData->_i当前玩家编号 == _tableData->_i自身玩家编号) ||
        (_tableData->_s玩家状态[_tableData->_i自身玩家编号] != WJZT_正常玩家) ||
        (_tableData->_i下一玩家编号 == 88)) {
        return [self HiddenAllButtomButton];
    }
    
     if (_tableData->_i下一玩家编号 == _tableData->_i自身玩家编号) {
         //判断是否自动执行
         if (NO ==_callButtonOther.markInOtherView.hidden){
             _callButtonOther.markInOtherView.hidden = YES;
             if (_tableData->_i本轮最大注 <= _tableData->_i下注筹码数[_tableData->_i自身玩家编号] + _tableData->_i手上筹码数[_tableData->_i自身玩家编号]) {
                 _socketClient->fuck下注(_tableData->_i本轮最大注 - _tableData->_i下注筹码数[_tableData->_i自身玩家编号],_tableData->_i自身玩家编号); return;
             }
             _socketClient->fuck下注(_tableData->_i手上筹码数[_tableData->_i自身玩家编号],_tableData->_i自身玩家编号);
         } else if (NO ==_foldButtonOther.markInOtherView.hidden){
             _foldButtonOther.markInOtherView.hidden = YES;
             [self foldButtonAction]; return;
         } else if (NO ==_checkButtonOther.markInOtherView.hidden){
             _checkButtonOther.markInOtherView.hidden = YES;
             [self checkButtonAction]; return; }
         
         //显示Myself
          return [self showMyselfButtomButton];
     } else {
         if (_tableData->_i本轮最大注 > _tableData->_i下注筹码数[_tableData->_i自身玩家编号]) {
             //显示Other
             return [self showOtherButtomButton];
         }
     }
}


-(void)showMyselfButtomButton {
    _iButtonStatus = enum_buttonStatus::myself;
    
    _foldButton.hidden = NO;
    _checkButton.hidden = NO;
    _addPourSlider.hidden = NO;
    _addPourSlider.value = 1;
    
    if (_tableData->_i本轮最大注 == _tableData->_i下注筹码数[_tableData->_i自身玩家编号]) {
        [_checkButton setTitle:@"Check" forState:UIControlStateNormal];
    }else  if (_tableData->_i本轮最大注 > (_tableData->_i下注筹码数[_tableData->_i自身玩家编号] + _tableData->_i手上筹码数[_tableData->_i自身玩家编号])){
        [_checkButton setTitle:@"All In" forState:UIControlStateNormal];
        _addPourSlider.hidden = YES;
    } else {
        NSString *checkBtnText = [NSString stringWithFormat:@"Call %d",_tableData->_i本轮最大注 - _tableData->_i下注筹码数[_tableData->_i自身玩家编号]];
        [_checkButton setTitle:checkBtnText forState:UIControlStateNormal];
    }
    
    _callButtonOther.hidden = YES;
    _foldButtonOther.hidden = YES;
    _checkButtonOther.hidden = YES;
}

-(void)showOtherButtomButton {
    if (_tableData->_i本轮最大注 == _tableData->_i下注筹码数[_tableData->_i自身玩家编号]) {
        _checkButtonOther.textLabel.text = @"Check Auto";
    } else  if (_tableData->_i本轮最大注 > (_tableData->_i下注筹码数[_tableData->_i自身玩家编号] + _tableData->_i手上筹码数[_tableData->_i自身玩家编号])) {
        _checkButtonOther.textLabel.text = @"All In";
    } else {
        if (_tableData->_i本轮最大注 > _maxPourBefore) {
            _checkButtonOther.markInOtherView.hidden = YES;
            _maxPourBefore = _tableData->_i本轮最大注;
            
            NSString *checkBtnOtherText = [NSString stringWithFormat:@"Call %d",_tableData->_i本轮最大注 - _tableData->_i下注筹码数[_tableData->_i自身玩家编号]];
            _checkButtonOther.textLabel.text = checkBtnOtherText;
        }
    }
    
    if (_iButtonStatus == enum_buttonStatus::otherPlayer) { return; }
    _iButtonStatus = enum_buttonStatus::otherPlayer;
    
    _foldButtonOther.hidden = NO;
    _checkButtonOther.hidden = NO;
    _callButtonOther.hidden = NO;
    
    _foldButton.hidden = YES;
    _checkButton.hidden = YES;
    _addPourSlider.hidden = YES;
    _addPourSlider.confirmView.hidden = YES;
}

-(void)HiddenAllButtomButton {
    if (_iButtonStatus == enum_buttonStatus::hidden) { return; }
    _iButtonStatus = enum_buttonStatus::hidden;
    
    _foldButton.hidden = YES;
    _checkButton.hidden = YES;
    _foldButtonOther.hidden = YES;
    _checkButtonOther.hidden = YES;
    _callButtonOther.hidden = YES;
    
    _addPourSlider.hidden = YES;
    _addPourSlider.confirmView.hidden = YES;
}

-(void)UpdatefloatPokerWithIplayerPos:(int)iPlayerPos {
    for (int j = 0; j < 7; j++) {
        dispatch_async(dispatch_get_main_queue(), ^{
            if (_tableData->_b浮起牌序号[iPlayerPos][j] != 1) {
                if (j < 2){
                    [_privatePokerImgView[iPlayerPos][j] decreasebrightness];
                } else {
                    [_commonPokerImgView[j-2] decreasebrightness];
                }
            } else {
                if (j < 2){
                    [_privatePokerImgView[iPlayerPos][j] showFloatBGview];
                } else {
                    [_commonPokerImgView[j-2] showFloatBGview];
                }
            }
        });
    }
}

/*
 一轮下注第一个就是自身玩家：
 1.点击弃牌/ALLIN之后，按钮在永远不再显示；
 2.点击让牌/加注之后，按钮在本轮不显示；
 3.本轮中在此之后，如果有人的筹码比我多，（其他玩家状态）按钮继续显示，并且状态初始化（没有选中的标记）
 
 一轮下注第一个玩家非自身玩家：
 1.（其他玩家状态）按钮继续显示，并且状态初始化（没有选中的标记）;
 2.轮到自己下注时检查按钮状态，并根据按钮状态做相应操作；（此时相当于自己是第一个下注的玩家）
 3.
 
 
*/
