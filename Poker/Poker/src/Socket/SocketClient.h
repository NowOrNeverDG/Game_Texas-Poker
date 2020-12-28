#import "Commons.h"

class CSocketClient {
public:
    CSocketClient();
    ~CSocketClient();
    
    //void RecvThread();
    int ConnectServers();
    int ConnectLocalHost();
    int SendData();
    int HJ_Send(char* pcszSendData, int iSendDataLen);

public:
    int  fuck上桌();
    void fuck让牌(Byte bPlayerPos);
    void fuck弃牌(Byte bPlayerPos);
    void fuck下注(int iPour,Byte iPlayerPos);
    
private:
    char _recvbuffer[BUFFER_SIZE];


    int _iPlayerCount;//桌上玩家总人数
    int _selfNo;//本机玩家座位号
    int _starterNo;//首个玩家的座位号
};

#define MSG_PLAYER_ONTABLE	20		//玩家上桌
#define MSG_PLAYER_OFFTABLE	21		//玩家离桌
#define MSG_PLAYER_OPERATION	22	//玩家的操作
#define MSG_PLAYER_ONLINE	25	//玩家上线
#define MSG_PLAYER_OFFLINE	26	//玩家下线

#define Test_PlayerID 1234567890
#define Test_VIPRoomID 1234567890
#define Test_TableID 12345678

#define MT_暂未参加任何比赛   0
#define MT_自由桌5W金币场   1
#define MT_自由桌10W金币场   2
#define MT_自由桌30W金币场   3
#define MT_比赛场5W金币整点赛  4
#define MT_比赛场8W金币日常赛  5
#define MT_比赛场10W金币午夜赛  6
#define MT_比赛场10W金币周赛  7
#define MT_免费场50W金币日常赛  8
#define MT_免费场520房卡日常赛  9
#define MT_免费场100W金币周赛  10
#define MT_免费场1314房卡周赛  11
#define MT_房卡房5W金币场   12
#define MT_房卡房20W金币场   13
#define MT_房卡房50W金币场   14
#define MT_房卡房100W金币场   15
#define MT_房卡房100W积分场   16
#define MT_场次      17

//玩家发给服务器的消息：10~99
#define MsgToServer_玩家上线 10
#define MsgToServer_玩家下线 12
#define MsgToServer_玩家上桌 20
#define MsgToServer_玩家离桌 22

#define MsgToServer_玩家弃牌 30
#define MsgToServer_玩家让牌 32
#define MsgToServer_玩家下注 36

//玩家发给服务器的消息：房卡房中使用
#define MsgToServer_创建房间 60
#define MsgToServer_关闭房间 62
#define MsgToServer_房间开赛 66

