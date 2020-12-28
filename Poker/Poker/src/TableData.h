#pragma once
#import <Foundation/Foundation.h>
#define WJZT_空置坐位    0
#define WJZT_弃牌玩家    1
#define WJZT_有效玩家    2
#define WJZT_饿赢玩家    3//ALLIN
#define WJZT_本轮饿赢    4//ALLIN
#define WJZT_正常玩家    5

class CTableData {
public:
    int _i自身玩家编号;
    int _i当前玩家编号;
    int _i下一玩家编号;
    
    int _i大盲玩家编号;
    int _i小盲玩家编号;
    
    int _i玩家数量;
    int _i庄家编号;
    
    int _i大盲注;
    int _i小盲注;
    int _i前注;
    
    int _i本轮最大注;
    int _i一注擎天;
    char _csz玩家昵称[6][32];
    
    int _i手上筹码数[6];
    int _i下注筹码数[6];
    
    int _i边池筹码数[6];
    int _i玩家边池对应表[6];
    int _i边池数;

    short _s玩家状态[6];
    short _s私牌HS[6][2];
    short _s私牌DX[6][2];

    short _s公牌HS[5];
    short _s公牌DX[5];
    
    Byte _b浮起牌序号[6][7];
    int _iczMatchResult[5][6];
    
public: //更新显示各控件
    Byte _bDirtyUserView[6];
    Byte _bDirtyNickName[6];
    Byte _bDirtyChips[6];
    Byte _bDirtyPour[6];
    Byte _bDirtyPool[6];
    
public:
    void fuck初始化所有变量();
    int fuck获取牌类型(int iPlayerNo, Byte FinalPokerCards[]);
    NSString* fuck获取牌类型文本(int iPlayerNo);
    void fuck收注();
    void fuck结束比赛();
    Byte fuck比较牌面大小();
   
    void fuck开始比赛清场();
    Byte _b玩家牌型[6][6] = { 0 };
    Byte _b比牌玩家的坐位号[6] = { 0 };
    
public:
    void 取牌序号_皇家同花顺(int iPlayerNo, int iHS);
    void 取牌序号_同花顺(int iPlayerNo, int iHS, int iMinCard);
    void 取牌序号_同花(int iPlayerNo, int iHS, Byte FinalPokerCards[]);
    void 取牌序号_顺子(int iPlayerNo, int iMinCard);
    void 取牌序号_四条(int iPlayerNo, Byte FinalPokerCards[]);
    void 取牌序号_葫芦(int iPlayerNo, Byte FinalPokerCards[]);
    void 取牌序号_三条(int iPlayerNo, Byte FinalPokerCards[]);
    void 取牌序号_两对(int iPlayerNo, Byte FinalPokerCards[]);
    void 取牌序号_一对(int iPlayerNo, Byte FinalPokerCards[]);
    void 取牌序号_高牌(int iPlayerNo, Byte FinalPokerCards[]);
    
    void 组合公私牌(int iPlayerNo);
    void 取牌的序号_全取(int iPlayerNo, int iDX, int iHS=0);
    void 取牌的序号_一张(int iPlayerNo, int iDX, int iHS=0);
    
    short m_ssz公私牌HS[7];
    short m_ssz公私牌DX[7];
    
public:
     void test();
    
};

#define 牌型_皇家同花顺    10
#define 牌型_同花顺      9
#define 牌型_四条       8
#define 牌型_葫芦       7
#define 牌型_同花       6
#define 牌型_顺子       5
#define 牌型_三条       4
#define 牌型_两对       3
#define 牌型_一对       2
#define 牌型_高牌       1

