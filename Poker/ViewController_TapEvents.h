#import <UIKit/UIKit.h>
#import "TableData.h"

-(void)OnTableAction { _socketClient->fuck上桌(); }

-(void)mySliderChange:(UISlider*)mySlider {//addPourSlider的滑动改变事件
    if (_addPourSlider.confirmView.hidden == YES) { _addPourSlider.confirmView.hidden = NO;        }
    
    int iMinPour = _tableData->_i本轮最大注 - _tableData->_i下注筹码数[_tableData->_i自身玩家编号];
    int iBasePour = _tableData->_i手上筹码数[_tableData->_i自身玩家编号] - iMinPour;
    
    _moneyNumber = iBasePour * (1-mySlider.value) + iMinPour;
    
//    if ((_tableData->_i下注筹码数[_tableData->_i自身玩家编号] + _tableData->_i手上筹码数[_tableData->_i自身玩家编号]) <= _tableData->_i本轮最大注) {
//        fPos = _tableData->_i手上筹码数[_tableData->_i自身玩家编号];
//    }else if (_tableData->_i下注筹码数[_tableData->_i自身玩家编号] < _tableData->_i本轮最大注 && _tableData->_i本轮最大注 < (_tableData->_i下注筹码数[_tableData->_i自身玩家编号] + _tableData->_i手上筹码数[_tableData->_i自身玩家编号])){
//        fPos = (_tableData->_i本轮最大注 - _tableData->_i下注筹码数[_tableData->_i自身玩家编号]) + (_tableData->_i手上筹码数[_tableData->_i自身玩家编号] - (_tableData->_i本轮最大注 - _tableData->_i下注筹码数[_tableData->_i自身玩家编号])) * (1-mySlider.value);
//        }else if (_tableData->_i本轮最大注 <= _tableData->_i下注筹码数[_tableData->_i自身玩家编号]) {
//            fPos = _tableData->_i手上筹码数[_tableData->_i自身玩家编号] * (1-mySlider.value);
//        }
    if (mySlider.value == 0){
        _addPourSlider.countLabel.text = @"All In";
    }else {
        _addPourSlider.countLabel.text = [NSString stringWithFormat:@"%d",_moneyNumber];
    }
    
    
    //根据Value设置ConfirmView的位置
    float numerator = mySlider.value - mySlider.minimumValue;
    float denominator = mySlider.maximumValue - mySlider.minimumValue;
    CGFloat x = numerator / denominator;
    _addPourSlider.confirmView.origin = CGPointMake(x * (mySlider.bounds.size.width - 15*2) - 10, _addPourSlider.confirmView.origin.y);
    
    _addPourSlider.confirmView.hidden = NO;
}

-(void)confirmButtonActon {//addPourSlider的滑动的确认按钮
    
    _socketClient->fuck下注(_moneyNumber,_tableData->_i自身玩家编号);
    NSLog(@"%@",[NSString stringWithFormat:@"下%d",_moneyNumber]);
}

-(void)foldButtonAction {
    _socketClient->fuck弃牌(_tableData->_i自身玩家编号);
}

-(void)checkButtonAction {
    if (_tableData->_i本轮最大注 <= _tableData->_i下注筹码数[_tableData->_i自身玩家编号]  ) {
        _socketClient->fuck让牌(_tableData->_i自身玩家编号);
    } else if (_tableData->_i下注筹码数[_tableData->_i自身玩家编号] < _tableData->_i本轮最大注 && _tableData->_i本轮最大注 < (_tableData->_i下注筹码数[_tableData->_i自身玩家编号] + _tableData->_i手上筹码数[_tableData->_i自身玩家编号])){
        _socketClient->fuck下注(_tableData->_i本轮最大注 - _tableData->_i下注筹码数[_tableData->_i自身玩家编号],_tableData->_i自身玩家编号);
    } else if ((_tableData->_i下注筹码数[_tableData->_i自身玩家编号] + _tableData->_i手上筹码数[_tableData->_i自身玩家编号]) <= _tableData->_i本轮最大注) {
        _socketClient->fuck下注(_tableData->_i手上筹码数[_tableData->_i自身玩家编号],_tableData->_i自身玩家编号);
    }
}

-(void)tapOKButton {//加注(其他玩家时间)、进度条(本玩家时间)按钮
    
}

//跟注(本玩家时间)、跟任何注(其他玩家时间)按钮
-(void)callButtonActionOther {
    _callButtonOther.markInOtherView.hidden = !_callButtonOther.markInOtherView.hidden;
    _checkButtonOther.markInOtherView.hidden = YES;
    _foldButtonOther.markInOtherView.hidden = YES;
}

-(void)checkButtonActionOther {
    _checkButtonOther.markInOtherView.hidden = !_checkButtonOther.markInOtherView.hidden;
    _foldButtonOther.markInOtherView.hidden = YES;
    _callButtonOther.markInOtherView.hidden = YES;
}

-(void)foldButtonActionOther {
    _foldButtonOther.markInOtherView.hidden = !_foldButtonOther.markInOtherView.hidden;
    _checkButtonOther.markInOtherView.hidden = YES;
    _callButtonOther.markInOtherView.hidden = YES;
}







