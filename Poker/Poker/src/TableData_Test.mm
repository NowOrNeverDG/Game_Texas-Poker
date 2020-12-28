#import "TableData.h"

void CTableData::test() {
    
    _i自身玩家编号 = 1;
    _i下一玩家编号 = 1;
    
    _i大盲玩家编号 = 3;
    _i小盲玩家编号 = 2;
    
    _i玩家数量 = 6;
    _i庄家编号 = 1;
    
    _i大盲注 = 1000;
    _i小盲注 = 500;
    _i前注 = 250;
    
    _i本轮最大注 = 1000;
    
    for (int i = 0; i < 6; i++) {
        char cszPlayerNickName[32] = {0};
        sprintf(cszPlayerNickName, "测试玩家 %d", i);
        memcpy(_csz玩家昵称[i], cszPlayerNickName, 32);
        
        _i手上筹码数[i] = 120000*(i+1);
        _i下注筹码数[i] = 10000*(i+1);
        _i边池筹码数[i] = 123123*(i+1);
        
        _bDirtyUserView[i] = 1;
        _bDirtyNickName[i] = 1;
        _bDirtyChips[i] = 1;
        _bDirtyPour[i] = 1;
        _bDirtyPool[i] = 1;
        
        _s私牌HS[i][0] = 0;
        _s私牌DX[i][0] = 0;
        
        _s私牌HS[i][1] = 0;
        _s私牌DX[i][1] = 0;
    }
    
    
    _s私牌HS[1][0] = 1;
    _s私牌DX[1][0] = 5;
    
    _s私牌HS[1][1] = 2;
    _s私牌DX[1][1] = 1;
    
    for (int i = 0; i<5; i++) {
        _s公牌HS[i] = 1;
        _s公牌DX[i] = i+9;
    }
    
}




