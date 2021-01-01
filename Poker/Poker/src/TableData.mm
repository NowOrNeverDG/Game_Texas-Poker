#import "TableData.h"

void CTableData::fuck初始化所有变量(){
    _i自身玩家编号 = 88;
    _i当前玩家编号 = 88;
    _i下一玩家编号 = 88;
    
    _i大盲玩家编号 = 88;
    _i小盲玩家编号 = 88;
    
    _i玩家数量 = 0;
    _i庄家编号 = 88;
    _i边池数 = 0;
    
    _i大盲注 = 0;
    _i小盲注 = 0;
    _i前注 = 0;
    
    _i本轮最大注 = 0;
    
    for (int i = 0; i < 6; i++) {
        memset(_csz玩家昵称[i], 0, 32);
        _i手上筹码数[i] = 0;
        _i下注筹码数[i] = 0;
        _i边池筹码数[i] = 0;
        
        _bDirtyUserView[i] = 0;
        _bDirtyNickName[i] = 0;
        _bDirtyChips[i] = 0;
        _bDirtyPour[i] = 0;
        _bDirtyPool[i] = 0;
        
        _s私牌HS[i][0] = 0;
        _s私牌DX[i][0] = 0;
        
        _s私牌HS[i][1] = 0;
        _s私牌DX[i][1] = 0;
        

    }
    
    memset(_b浮起牌序号, 0, sizeof(_b浮起牌序号));
    memset(_iczMatchResult, 0, sizeof(_iczMatchResult));
    
    for (int i = 0; i<5; i++) {
        _s公牌HS[i] = 0;
        _s公牌DX[i] = 0;
    }    
}

void CTableData::fuck开始比赛清场() {
    
    _i边池数 = 0;
    _i本轮最大注 = 0;
    _i下一玩家编号 = 88;
    _i当前玩家编号 = 88;
    _i庄家编号 = 88;
    
    memset(_iczMatchResult, 0, sizeof(_iczMatchResult));

    for (int i = 0; i < 6; i++) {
        _bDirtyUserView[i] = 88;
        _bDirtyNickName[i] = 1;
        _bDirtyChips[i] = 1;
        _bDirtyPour[i] = 1;
        
        _s私牌HS[i][0] = 0;
        _s私牌DX[i][0] = 0;
        _s私牌HS[i][1] = 0;
        _s私牌DX[i][1] = 0;
    }
    
    
    for (int i = 0; i < 5; i++) {
        _s公牌HS[i] = 0;
        _s公牌DX[i] = 0;
        
        _i边池筹码数[i] = 0;
        _bDirtyPool[i] = 1;
    }
}

NSString* CTableData::fuck获取牌类型文本(int iPlayerNo){
    Byte FinalPokerCards[6] = {0};
    switch(fuck获取牌类型(iPlayerNo, FinalPokerCards)){
        case 牌型_皇家同花顺:{ return @"Royal flush";}
        case 牌型_同花顺:{ return @"Straight flush";}
        case 牌型_四条:{ return @"Four of a kind";}
        case 牌型_葫芦:{ return @"Full house";}
        case 牌型_同花:{ return @"Flush";}
        case 牌型_顺子:{ return @"Straight";}
        case 牌型_三条:{ return @"Three of a kind";}
        case 牌型_两对:{ return @"(Two pairs";}
        case 牌型_一对:{ return @"One pair";}
        case 牌型_高牌:{ return @"High card";}
    }
    return nil;
}

int CTableData::fuck获取牌类型(int iPlayerNo, Byte FinalPokerCards[]) {
    int iPlayerCard_DX[15] = { 0 }; //牌面大小，第0位空出不用，第1、14个用来保存‘A’，做特殊处理
    int iPlayerCard_HS[5] = { 0 }; //牌面花色，第0位空出不用
    
    //取花色及花色数量
    iPlayerCard_HS[_s私牌HS[iPlayerNo][0]]++;
    iPlayerCard_HS[_s私牌HS[iPlayerNo][1]]++;
    
    for (int i = 0; i < 5; i++) {
        iPlayerCard_HS[_s公牌HS[i]]++;
    }
    
    //判断是不是同花
    for (int iHS = 1; iHS < 5; iHS++) {
        if (iPlayerCard_HS[iHS] < 5) { continue; }
        
        //是同花，则继续判断是不是顺子
        //取此花色的所有牌
        if (_s私牌HS[iPlayerNo][0] == iHS) { iPlayerCard_DX[_s私牌DX[iPlayerNo][0]]++; }
        if (_s私牌HS[iPlayerNo][1] == iHS) { iPlayerCard_DX[_s私牌DX[iPlayerNo][1]]++; }
        
        for (int i = 0; i < 5; i++) {
            if (_s公牌HS[i] == iHS) { iPlayerCard_DX[_s公牌DX[i]]++; }
        }
        
        iPlayerCard_DX[14] = iPlayerCard_DX[1]; // 特例：A
        
        int iCount = 0;
        //判断是不是顺子
        for (int iMinCard = 14; iMinCard > 0; iMinCard--) {
            if (iPlayerCard_DX[iMinCard] == 0) { iCount = 0; continue; }
            
            iCount++;
            if (iCount == 5) {//是同花顺子，继续判断是不是皇家同花顺
                if (iMinCard == 10) {
                    FinalPokerCards[0] = 牌型_皇家同花顺;
                    
                    取牌序号_皇家同花顺(iPlayerNo,iHS);
                    return 牌型_皇家同花顺; //是皇家同花顺
                }
                
                FinalPokerCards[0] = 牌型_同花顺;
                FinalPokerCards[1] = iMinCard;
                取牌序号_同花顺(iPlayerNo,iHS,iMinCard);
                return 牌型_同花顺; //仅仅是同花顺
            }
        }
        
        FinalPokerCards[0] = 牌型_同花;
        iCount = 0;
        for (int i = 14; i >= 2; i--) {
//        for (int i = 13; i >= 1; i--) {
            if (iPlayerCard_DX[i] == 0) { continue; }
            
            iCount++;
            FinalPokerCards[iCount] = i;
            if (iCount == 5) { break; }
        }
        取牌序号_同花(iPlayerNo,iHS,FinalPokerCards);
        return 牌型_同花; //仅仅是同花
    }
    
    //不是同花，取所有牌的大小
    iPlayerCard_DX[_s私牌DX[iPlayerNo][0]]++;
    iPlayerCard_DX[_s私牌DX[iPlayerNo][1]]++;
    for (int i = 0; i < 5; i++) { iPlayerCard_DX[_s公牌DX[i]]++; }
    
    //判断是不是顺子
    iPlayerCard_DX[14] = iPlayerCard_DX[1]; // 特例：A
    int iCount = 0;
    
    for (int iMinCard = 14; iMinCard > 0; iMinCard--) {
        if (iPlayerCard_DX[iMinCard] == 0) { iCount = 0; continue; }
        
        iCount++;
        if (iCount == 5) {//是顺子
            FinalPokerCards[0] = 牌型_顺子;
            FinalPokerCards[1] = iMinCard;
            void 取牌序号_顺子(int iPlayerNo,int iMinCard);
            return 牌型_顺子;
        }
    }
    
    //判断三条
    // iPlayerCard_DX[1] = 0; // 特例：A。去掉位置1的'A'，以后只使用位置14的'A'。
    for (int i = 14; i >= 2; i--) {
//    for (int i = 13; i >= 1; i--) {
        if (iPlayerCard_DX[i] < 3) { continue; }
        
        //有三条
        for (int j = i; j >= 2; j--) {//判断是否有四条
//        for (int j = i; j >= 1; j--) {
            if (iPlayerCard_DX[j] != 4) { continue; }
            
            
            FinalPokerCards[0] = 牌型_四条;
            FinalPokerCards[1] = j;
            
            for (int k = 14; k >= 2; k--) {//获取除了四条之外的最大牌
//            for (int k = 13; k >= 1; k--) {
                if (iPlayerCard_DX[k] == 0 || k == j) { continue; }
                
                FinalPokerCards[2] = k;
                break;
            }
            
            取牌序号_四条(iPlayerNo,FinalPokerCards);
            return 牌型_四条;
        }
        
        for (int j = 14; j >= 2; j--) {//判断是否有葫芦
//            for (int j = 13; j >= 1; j--) {

            if ((iPlayerCard_DX[j] < 2) || j == i) { continue; }
            
            FinalPokerCards[0] = 牌型_葫芦;
            FinalPokerCards[1] = i;
            FinalPokerCards[2] = j;
            取牌序号_葫芦(iPlayerNo, FinalPokerCards);
            return 牌型_葫芦;
        }
        
        FinalPokerCards[0] = 牌型_三条;
        FinalPokerCards[1] = i;
        iCount = 1;
        for (int j = 14; j >= 2; j--) {
//        for (int j = 13; j >= 1; j--) {
            if (iPlayerCard_DX[j] == 0 || j == i) { continue; }
            
            iCount++;
            FinalPokerCards[iCount] = j;
            if (iCount == 3) { break; }
        }
        取牌序号_三条(iPlayerNo, FinalPokerCards);
        return 牌型_三条;
    }
    
    //判断两对、一对、高牌
    iCount = 0;
    for (int i = 14; i >= 2; i--) {
//    for (int i = 13; i >= 1; i--) {

        if (iPlayerCard_DX[i] != 2) { continue; }
        
        iCount++;
        FinalPokerCards[iCount] = i;
        if (iCount < 2) { continue; }
        
        //牌型为两对
        for (int j = 14; j >= 2; j--) {
//            for (int j = 13; j >= 1; j--) {

            if (iPlayerCard_DX[j] == 0 || (j == FinalPokerCards[1] || j == FinalPokerCards[2])) { continue; }
            
            FinalPokerCards[3] = j;
            break;
        }
        
        FinalPokerCards[0] = 牌型_两对;
        取牌序号_两对(iPlayerNo, FinalPokerCards);
        return 牌型_两对;
    }
    
    //一对
    if (iCount == 1) {
        for (int j = 14; j >= 2; j--) {
//            for (int j = 13; j >= 1; j--) {

            if (iPlayerCard_DX[j] == 0 || j == FinalPokerCards[1]) { continue; }
            
            iCount++;
            FinalPokerCards[iCount] = j;
            if (iCount == 4) { break; }
        }
        取牌序号_一对(iPlayerNo, FinalPokerCards);
        FinalPokerCards[0] = 牌型_一对;
        return 牌型_一对;
    }
    
    //高牌//iCount == 0;
    for (int j = 14; j >= 2; j--) {
//        for (int j = 13; j >= 1; j--) {

        if (iPlayerCard_DX[j] == 0) { continue; }
        
        iCount++;
        FinalPokerCards[iCount] = j;
        if (iCount == 5) { break; }
    }
    FinalPokerCards[0] = 牌型_高牌;
    取牌序号_高牌(iPlayerNo, FinalPokerCards);
    return 牌型_高牌;
}

void CTableData::fuck收注() {
    Byte Byte本轮ALLIN玩家数 = 0;
    Byte BytePos[6] = { 0 };//allin玩家
    UInt32 dwPour[6] = { 0 };

    for (Byte i = 0; i < 6; i++) {
        if (_s玩家状态[i] != WJZT_本轮饿赢) { continue; }
        
        BytePos[Byte本轮ALLIN玩家数] = i;
        dwPour[Byte本轮ALLIN玩家数] = _i下注筹码数[i];
        Byte本轮ALLIN玩家数++;
        
        _s玩家状态[i] = WJZT_饿赢玩家;
    }
    
    if (Byte本轮ALLIN玩家数 != 0) {
        UInt32 dwTmp;
        Byte ByteTmp;
        for (int i = 0; i < Byte本轮ALLIN玩家数; i++) {//从小到大排序ALLIN玩家下注的筹码
            for (int j = i + 1; j < Byte本轮ALLIN玩家数; j++) {
                if (dwPour[i] > dwPour[j]) {
                    dwTmp = dwPour[i]; dwPour[i] = dwPour[j]; dwPour[j] = dwTmp;
                    ByteTmp = BytePos[i]; BytePos[i] = BytePos[j]; BytePos[j] = ByteTmp;
                }
            }
        }
        
        for (Byte k = 0; k < Byte本轮ALLIN玩家数; k++) { //开始计算边池
            for (int i = 0; i < 6; i++) {
                if (_i下注筹码数[i] == 0) { continue; }
                
                if (_i下注筹码数[i] > dwPour[k]) {
                    _i下注筹码数[i] -= dwPour[k];
                    _i边池筹码数[_i边池数] += dwPour[k];
                }
                else {
                    _i边池筹码数[_i边池数] += _i下注筹码数[i];
                    _i下注筹码数[i] = 0;
                }
            }
            _i玩家边池对应表[BytePos[k]] = _i边池数; //相应玩家对应的边池号
            _bDirtyPool[_i边池数] = 1;
            
            dwTmp = dwPour[k];//所有ALLIN筹码中，去掉已割掉的筹码
            for (Byte z = k+1; z < Byte本轮ALLIN玩家数; z++) {
                dwPour[z] -= dwTmp;
                
                if (0 == dwPour[z]) {//考虑多人同享一个边池的情况
                    k++;
                    _i玩家边池对应表[BytePos[k]] = _i边池数; //相应玩家对应的边池号
                }
            }
            _i边池数++;
        }
    }
    
    for (int i = 0; i < 6; i++) {
        _bDirtyPour[i] = 1;
        if (_i下注筹码数[i] == 0) { continue; }
        _i边池筹码数[_i边池数] += _i下注筹码数[i];
        _bDirtyPool[_i边池数] = 1;
        _i下注筹码数[i] = 0;
    }
    
    _i本轮最大注 = 0;
    
    
    //判断是否需要改变 dw一注擎天
    UInt32 dwChip[6] = { 0 }, dwTmp = 0;
    for (int i = 0; i < 6; i++) {
        if (_s玩家状态[i] >= WJZT_有效玩家) {
            dwChip[i] = _i手上筹码数[i] + _i下注筹码数[i];
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = i; j < 6; j++) {
            if (dwChip[i] < dwChip[j]) { //从大到小排序
                dwTmp = dwChip[i];
                dwChip[i] = dwChip[j];
                dwChip[j] = dwTmp;
            }
        }
    }
    _i一注擎天 = dwChip[1];
}

void CTableData::fuck结束比赛() {
    //_i下注筹码数，临时借用于保存玩家赢得的筹码
    for (Byte i = 0; i < 6; i++) { _i下注筹码数[i] = 0; }
 
    memset(_b比牌玩家的坐位号, 0, sizeof(_b比牌玩家的坐位号));
    memset(_b玩家牌型, 0, sizeof(_b玩家牌型));
    
    //计算各有效玩家的牌面
    for (Byte i = 0; i < 6; i++) {
        if (_s玩家状态[i] < WJZT_有效玩家) { continue; }
        fuck获取牌类型(i, _b玩家牌型[i]);
    }
    
    //根据边池，比较大小
    Byte b可下注玩家数;
    for (Byte i = 0; i < 6; i++) {
        if (_s玩家状态[i] != WJZT_正常玩家) {  continue; }
        
        b可下注玩家数++;
        _b比牌玩家的坐位号[i] = 1;
    }
    
    if (b可下注玩家数 > 1) {//多个玩家争当前池
        Byte Byte最大牌型玩家数 = fuck比较牌面大小();
        
        UInt32 dwChips = _i边池筹码数[_i边池数]/ Byte最大牌型玩家数;
        for (Byte i = 0; i < 6; i++) {
            if (_b比牌玩家的坐位号[i] == 0) { continue; }
            
            _i下注筹码数[i] = dwChips;
            _iczMatchResult[_i边池数][i] = dwChips;
        }
    }
    else if (b可下注玩家数 == 1) {//最后一人赢得当前池
        for (Byte i = 0; i < 6; i++) {
            if (_s玩家状态[i] != WJZT_正常玩家) { continue; }
            
            _i下注筹码数[i] = _i边池筹码数[_i边池数];
            _iczMatchResult[_i边池数][i] =  _i边池筹码数[_i边池数];
            break;
        }
    }
        
    for (int i = _i边池数 - 1; i >= 0; i--) {
        for (Byte j = 0; j < 6; j++) { //取可以分此边池的玩家，再比较大小
            if (_i玩家边池对应表[j] != i) { continue; }
            _b比牌玩家的坐位号[j] = 1;
        }
        
        Byte Byte最大牌型玩家数 = fuck比较牌面大小();
        
        UInt32 dwChips = _i边池筹码数[i] / Byte最大牌型玩家数;
        for (Byte j = 0; j < 6; j++) {
            if (_b比牌玩家的坐位号[j] == 0) { continue; }
            
            _i下注筹码数[j] += dwChips;
            _iczMatchResult[i][j] = dwChips;
        }
    }
}

Byte CTableData::fuck比较牌面大小() {
    for (Byte i = 0; i < 6; i++) {
        if (_b比牌玩家的坐位号[i] == 0) { continue; }
        
        for (Byte j = i; j < 6; j++) {
            if (_b比牌玩家的坐位号[j] == 0) { continue; }
            
            for (Byte b = 0; b < 6; b++) {
                if (_b玩家牌型[i][b] > _b玩家牌型[j][b]) {
                    _b比牌玩家的坐位号[j] = 0;
                    break;
                }
                
                if (_b玩家牌型[i][b] < _b玩家牌型[j][b]) {
                    _b比牌玩家的坐位号[i] = 0;
                    break;
                }
            }
            
            if (_b比牌玩家的坐位号[i] == 0) { break; }
        }
    }
    
    Byte ByteRTN = 0;
    for (Byte i = 0; i < 6; i++) {
        if (_b比牌玩家的坐位号[i] == 0) { continue; }
        
        ByteRTN++;
    }
    return ByteRTN;
}

void CTableData::取牌序号_皇家同花顺(int iPlayerNo, int iHS) {
    组合公私牌(iPlayerNo);
    取牌的序号_一张(iPlayerNo, 14, iHS);
    取牌的序号_一张(iPlayerNo, 13, iHS);
    取牌的序号_一张(iPlayerNo, 12, iHS);
    取牌的序号_一张(iPlayerNo, 11, iHS);
    取牌的序号_一张(iPlayerNo, 10, iHS);
}

void CTableData::取牌序号_同花顺(int iPlayerNo, int iHS, int iMinCard) {
    组合公私牌(iPlayerNo);
    for (int i = iMinCard + 4; i >= iMinCard; i--) {
        取牌的序号_一张(iPlayerNo, i, iHS);
    }
}

void CTableData::取牌序号_同花(int iPlayerNo,int iHS,Byte FinalPokerCards[]) {
    组合公私牌(iPlayerNo);
    取牌的序号_一张(iPlayerNo,FinalPokerCards[1],iHS);
    取牌的序号_一张(iPlayerNo,FinalPokerCards[2],iHS);
    取牌的序号_一张(iPlayerNo,FinalPokerCards[3],iHS);
    取牌的序号_一张(iPlayerNo,FinalPokerCards[4],iHS);
    取牌的序号_一张(iPlayerNo,FinalPokerCards[5],iHS);
}

void CTableData::取牌序号_顺子(int iPlayerNo,int iMinCard) {
    组合公私牌(iPlayerNo);
    for (int i = iMinCard; i < iMinCard + 5; i++) {
       取牌的序号_一张(iPlayerNo, i);
    }
}

void CTableData::取牌序号_四条(int iPlayerNo,Byte FinalPokerCards[]) {
    组合公私牌(iPlayerNo);
    取牌的序号_全取(iPlayerNo, FinalPokerCards[1]);//设置四条的四张牌为1状态
    取牌的序号_一张(iPlayerNo, FinalPokerCards[2]); //设置单牌的一张牌为1状态
}

void CTableData::取牌序号_葫芦(int iPlayerNo,Byte FinalPokerCards[]) {
    组合公私牌(iPlayerNo);
    取牌的序号_全取(iPlayerNo, FinalPokerCards[1]);//设置葫芦中的三张牌为1状态
    取牌的序号_一张(iPlayerNo, FinalPokerCards[2]);//设置葫芦中的两张牌为1状态
    取牌的序号_一张(iPlayerNo, FinalPokerCards[2]);//设置葫芦中的两张牌为1状态
}

void CTableData::取牌序号_三条(int iPlayerNo,Byte FinalPokerCards[]) {
    组合公私牌(iPlayerNo);
    取牌的序号_全取(iPlayerNo, FinalPokerCards[1]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[2]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[3]);
}

void CTableData::取牌序号_两对(int iPlayerNo,Byte FinalPokerCards[]) {
    组合公私牌(iPlayerNo);
    取牌的序号_全取(iPlayerNo, FinalPokerCards[1]);
    取牌的序号_全取(iPlayerNo, FinalPokerCards[2]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[3]);
}

void CTableData::取牌序号_一对(int iPlayerNo,Byte FinalPokerCards[]) {
    组合公私牌(iPlayerNo);
    取牌的序号_全取(iPlayerNo, FinalPokerCards[1]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[2]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[3]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[4]);
}

void CTableData::取牌序号_高牌(int iPlayerNo,Byte FinalPokerCards[]) {
    组合公私牌(iPlayerNo);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[1]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[2]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[3]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[4]);
    取牌的序号_一张(iPlayerNo, FinalPokerCards[5]);
}

void CTableData::组合公私牌(int iPlayerNo) {
    for (int i = 0; i < 7; i++) {
        _b浮起牌序号[iPlayerNo][i] = 0;
    }
    
    m_ssz公私牌HS[0] = _s私牌HS[iPlayerNo][0];
    m_ssz公私牌HS[1] = _s私牌HS[iPlayerNo][1];
    m_ssz公私牌HS[2] = _s公牌HS[0];
    m_ssz公私牌HS[3] = _s公牌HS[1];
    m_ssz公私牌HS[4] = _s公牌HS[2];
    m_ssz公私牌HS[5] = _s公牌HS[3];
    m_ssz公私牌HS[6] = _s公牌HS[4];
    
    m_ssz公私牌DX[0] = _s私牌DX[iPlayerNo][0];
    m_ssz公私牌DX[1] = _s私牌DX[iPlayerNo][1];
    m_ssz公私牌DX[2] = _s公牌DX[0];
    m_ssz公私牌DX[3] = _s公牌DX[1];
    m_ssz公私牌DX[4] = _s公牌DX[2];
    m_ssz公私牌DX[5] = _s公牌DX[3];
    m_ssz公私牌DX[6] = _s公牌DX[4];
}

void CTableData::取牌的序号_全取(int iPlayerNo, int iDX, int iHS/*=0*/) {
    if (iDX == 14) { iDX = 1; }
    
    if (iHS != 0) {
        for(int i = 6; i >= 0; i--) {
            if ((m_ssz公私牌HS[i] == iHS) && m_ssz公私牌DX[i] == iDX) {
                m_ssz公私牌HS[i] = 0;
                m_ssz公私牌DX[i] = 0;
                
                _b浮起牌序号[iPlayerNo][i] = 1;
            }
        }
    } else {
        for(int i = 6; i >= 0; i--) {
            if (m_ssz公私牌DX[i] == iDX) {
                m_ssz公私牌HS[i] = 0;
                m_ssz公私牌DX[i] = 0;
                
                _b浮起牌序号[iPlayerNo][i] = 1;
            }
        }
    }
}

void CTableData::取牌的序号_一张(int iPlayerNo, int iDX, int iHS/*=0*/) {
    if (iDX == 14) { iDX = 1; }
    
    if (iHS != 0) {
        for(int i = 6; i >= 0; i--) {
            if ((m_ssz公私牌HS[i] == iHS) && m_ssz公私牌DX[i] == iDX) {
                m_ssz公私牌HS[i] = 0;
                m_ssz公私牌DX[i] = 0;
                
                _b浮起牌序号[iPlayerNo][i] = 1;
                break;
            }
        }
    } else {
        for(int i = 6; i >= 0; i--) {
            if (m_ssz公私牌DX[i] == iDX) {
                m_ssz公私牌HS[i] = 0;
                m_ssz公私牌DX[i] = 0;
                
                _b浮起牌序号[iPlayerNo][i] = 1;
                break;
            }
        }
    }
}
