-(void)setBottomButton{
    //进度条加注(自己玩家回合)、跟任何注(其他玩家回合)按钮
    _callButtonOther = [CallButtonOther buttonWithType:UIButtonTypeSystem];
    _callButtonOther.frame = CGRectMake(10, 340, 120, 33);
    _callButtonOther.layer.cornerRadius = 5;
    [_callButtonOther setBackgroundImage:[UIImage imageNamed:@"按钮22.png"] forState:UIControlStateNormal];
    _callButtonOther.layer.masksToBounds = YES;
    [_callButtonOther addTarget:self action:@selector(callButtonActionOther) forControlEvents:UIControlEventTouchUpInside];//跟注按钮的方法
    _callButtonOther.hidden = YES;
    
    UILabel *callButtonOtherLB = [[UILabel alloc] init];
    callButtonOtherLB.frame = CGRectMake(35, 0,85,30);
    callButtonOtherLB.text = @"Call any bet";
    callButtonOtherLB.font = [UIFont systemFontOfSize:13];
    callButtonOtherLB.lineBreakMode = NSLineBreakByCharWrapping;
    callButtonOtherLB.textAlignment = NSTextAlignmentCenter;
    callButtonOtherLB.textColor = [UIColor whiteColor];
    
    //弃牌 (自己玩家回合)
    _foldButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _foldButton.frame = CGRectMake(ksboundsWidth - 130, 340, 120, 33);
    [_foldButton setTitle:@"Fold" forState:UIControlStateNormal];
    [_foldButton setTintColor:[UIColor whiteColor]];
    [_foldButton setBackgroundImage:[UIImage imageNamed:@"按钮2.png"] forState:UIControlStateNormal];
    _foldButton.layer.cornerRadius = 5;
    _foldButton.layer.masksToBounds = YES;
    [_foldButton addTarget:self action:@selector(foldButtonAction) forControlEvents:UIControlEventTouchUpInside];//弃牌按钮的方法
    _foldButton.hidden = YES;
    
    //弃牌 (其他玩家回合)
    _foldButtonOther = [FoldButtonOther buttonWithType:UIButtonTypeSystem];
    _foldButtonOther.frame = CGRectMake(ksboundsWidth - 130, 340, 120, 33);
    [_foldButtonOther setBackgroundImage:[UIImage imageNamed:@"按钮22.png"] forState:UIControlStateNormal];
    _foldButtonOther.layer.cornerRadius = 5;
    _foldButtonOther.layer.masksToBounds = YES;
    [_foldButtonOther addTarget:self action:@selector(foldButtonActionOther) forControlEvents:UIControlEventTouchUpInside];//弃牌按钮的方法
    _foldButtonOther.hidden = YES;
    [self.view addSubview:_foldButtonOther];
    
    UILabel *foldButtonOtherLB = [[UILabel alloc] init];
    foldButtonOtherLB.frame = CGRectMake(35, 0,85,30);
    foldButtonOtherLB.text = @"Fold";
    foldButtonOtherLB.font = [UIFont systemFontOfSize:13];
    foldButtonOtherLB.lineBreakMode = NSLineBreakByCharWrapping;
    foldButtonOtherLB.textAlignment = NSTextAlignmentCenter;
    foldButtonOtherLB.textColor = [UIColor whiteColor];
    
    //让牌/跟200 (自己玩家回合）
    _checkButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _checkButton.frame = CGRectMake(ksboundsWidth - 260, 340, 120, 33);
    [_checkButton setTintColor:[UIColor whiteColor]];
    [_checkButton setBackgroundImage:[UIImage imageNamed:@"按钮2.png"] forState:UIControlStateNormal];
    _checkButton.layer.cornerRadius = 5;
    _checkButton.layer.masksToBounds = YES;
    [_checkButton addTarget:self action:@selector(checkButtonAction) forControlEvents:UIControlEventTouchUpInside];//弃牌按钮的方法
    _checkButton.hidden = YES;
    
    
    //总是让牌/自动跟200 (其他玩家回合)
    _checkButtonOther = [CheckButtonOther buttonWithType:UIButtonTypeCustom];
    _checkButtonOther.frame = CGRectMake(ksboundsWidth - 260, 340, 120, 33);
    [_checkButtonOther setBackgroundImage:[UIImage imageNamed:@"按钮22.png"] forState:UIControlStateNormal];
    _checkButtonOther.layer.cornerRadius = 5;
    _checkButtonOther.layer.masksToBounds = YES;
    [_checkButtonOther addTarget:self action:@selector(checkButtonActionOther) forControlEvents:UIControlEventTouchUpInside];
    _checkButtonOther.hidden = YES;
    
    [_checkButtonOther addSubview:_checkButtonOther.textLabel];
    _checkButtonOther.textLabel.frame = CGRectMake(35, 0,85,30);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [_checkButtonOther addSubview:_checkButtonOther.markInOtherView];
        [_callButtonOther addSubview:callButtonOtherLB];
        [_callButtonOther addSubview:_callButtonOther.markInOtherView];
        [_foldButtonOther addSubview:_foldButtonOther.markInOtherView];
        [_foldButtonOther addSubview:foldButtonOtherLB];
        [self.view addSubview:_checkButtonOther];
        [self.view addSubview:_checkButton];
        [self.view addSubview:_callButtonOther];
        [self.view addSubview:_foldButton];
    });
}

-(void)setTopMenu {
    //设置返回箭头
    UIButton* LeftArrowButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [LeftArrowButton setImage:[UIImage imageNamed:@"返回.png"] forState:UIControlStateNormal];
    LeftArrowButton.frame = CGRectMake(25, 10, 45, 45);
    [LeftArrowButton addTarget:self action:@selector(leftArrowAction) forControlEvents:UIControlEventTouchUpInside];
    
    //设置有菜单箭头
    UIButton *RightMenuButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [RightMenuButton setImage:[UIImage imageNamed:@"更多.png"] forState:UIControlStateNormal];
    RightMenuButton.frame = CGRectMake(600, 10, 45, 45);
    //[RightMenuButton addTarget:self action:@selector(OnTableAction) forControlEvents:UIControlEventTouchUpInside];
    [RightMenuButton addTarget:self action:@selector(rightArrowAction) forControlEvents:UIControlEventTouchUpInside];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.view addSubview:RightMenuButton];
        [self.view addSubview:LeftArrowButton];
    });
}

-(void)setAddPourSlider {
    
    //滑动条
    _addPourSlider = [[AddSlider alloc] init];
    [_addPourSlider addTarget:self action:@selector(mySliderChange:) forControlEvents:UIControlEventValueChanged];
    [_addPourSlider.confirmButton addTarget:self action:@selector(confirmButtonActon) forControlEvents:UIControlEventTouchUpInside];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.view insertSubview:_addPourSlider aboveSubview:_privatePokerImgView[3][0]];
    });

//    //设置跟注进度条
//    _progressView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"加注2.png"]];
//    _progressView.frame = CGRectMake(15, 340, 340, 35);
//    _progressView.hidden = YES;
//    [self.view addSubview:_progressView];
//    
//    //设置覆盖视图
//    _coverView = [[UIImageView alloc] initWithFrame:CGRectMake(0,0, 9.0/10.0*_progressView.frame.size.width+13, 35)];
//    _coverView.image = [UIImage imageNamed:@"加注1.png"];
//    [_progressView addSubview:_coverView];
//    
//    //筹码确定视图
//    _OKView = [[UIImageView alloc] initWithFrame:CGRectMake(-100, -100, 40, 40)];
//    _OKView.image = [UIImage imageNamed:@"加注_确定.png"];
//    _OKView.layer.cornerRadius = 5;
//    _OKView.layer.masksToBounds = YES;
//    _OKView.userInteractionEnabled = YES;
//    [self.view addSubview:_OKView];
//    
//    //筹码下注数量文本
//    _OKLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 40, 20)];
//    _OKLabel.font = [UIFont systemFontOfSize:10.0];
//    _OKLabel.textAlignment = NSTextAlignmentCenter;
//    _OKLabel.lineBreakMode = NSLineBreakByCharWrapping;
//    [_OKView addSubview:_OKLabel];
//    
//    //确定按钮
//    _OKButton = [UIButton buttonWithType:UIButtonTypeCustom];
//    _OKButton.frame = CGRectMake(0, 20, 40, 20);
//    [_OKButton setTitle:@"确定" forState:UIControlStateNormal];
//    _OKButton.titleLabel.font = [UIFont systemFontOfSize: 10.0];
//    [_OKButton setTitleColor:[UIColor blackColor]forState:UIControlStateNormal];
//    _OKButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentCenter;
//    [_OKButton addTarget:self action:@selector(tapOKButton) forControlEvents:UIControlEventTouchUpInside];
//    [_OKView addSubview:_OKButton];
    
}



    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
