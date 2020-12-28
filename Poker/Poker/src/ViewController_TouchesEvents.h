#pragma mark - Touches Events
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    //跟踪手指滑动覆盖视图
//    UITouch *touch1 = [touches anyObject];
//    CGPoint touchPoint1 = [touch1 locationInView:_progressView];
//    CGPoint touchPoint1Pre = [touch1 previousLocationInView:_progressView];
//    if ((touchPoint1.x >= 0 && touchPoint1.x <= _progressView.frame.size.width) && (touchPoint1.y >= 0 &&touchPoint1.y <= _progressView.frame.size.height) && _progressView.hidden == NO) {
//        if (touchPoint1Pre.x > touchPoint1.y) { _coverView.image = [UIImage imageNamed:@"加注1.png"]; }
//        
//        _coverView.image = [UIImage imageNamed:@"加注1.png"];
//        _coverView.image = [_coverView.image getSubImage:CGRectMake(0, 0, touchPoint1.x, 35)];
//        _coverView.frame = CGRectMake(-2, -2, touchPoint1.x, 34);
//        
//        int iPour = _tableData->_i手上筹码数[_tableData->_i自身玩家编号];
//        _moneyNumber = iPour- iPour*touchPoint1.x/_progressView.frame.size.width;
//        
//        [_OKLabel setText:[NSString stringWithFormat:@"%d",_moneyNumber]];
//        
//        //跟踪手指滑动筹码显示视图
//        UITouch *touch2 = [touches anyObject];
//        CGPoint touchPoint2 = [touch2 locationInView:_progressView];
//        _OKView.origin = CGPointMake(touchPoint2.x - 15, 290);
//    }
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    //跟踪手指滑动覆盖视图
//    UITouch *touch1 = [touches anyObject];
//    CGPoint touchPoint1 = [touch1 locationInView:_progressView];
//    CGPoint touchPoint1Pre = [touch1 previousLocationInView:_progressView];
//    
//    if (touchPoint1.x >= 0 && touchPoint1.x <= _progressView.frame.size.width && touchPoint1.y >= 0 &&touchPoint1.y <= _progressView.frame.size.height && _progressView.hidden == NO) {
//        if (touchPoint1Pre.x > touchPoint1.y) { _coverView.image = [UIImage imageNamed:@"加注1.png"]; }
//            
//        _coverView.image = [UIImage imageNamed:@"加注1.png"];
//        _coverView.image = [_coverView.image getSubImage:CGRectMake(0, 0, touchPoint1.x, 35)];
//        _coverView.frame = CGRectMake(-2, -2, touchPoint1.x, 34);
//        
//        int iPour = _tableData->_i手上筹码数[_tableData->_i自身玩家编号];
//        _moneyNumber = iPour- iPour*touchPoint1.x/_progressView.frame.size.width;
//        [_OKLabel setText:[NSString stringWithFormat:@"%d",_moneyNumber]];
//
//        //跟踪手指滑动筹码显示视图
//        UITouch *touch2 = [touches anyObject];
//        CGPoint touchPoint2 = [touch2 locationInView:_progressView];
//        _OKView.origin = CGPointMake(touchPoint2.x - 15, 290);
//    }
}

-(void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    
}
