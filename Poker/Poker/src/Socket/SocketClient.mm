#import "SocketClient.h"
#import <Foundation/Foundation.h>

int _socketServer;//socket的号码

void RecvThread() {
    NSNotification *notification;
    int iRecvLen = 0;
    char recvbuffer[BUFFER_SIZE];
    
    while(1){
        
        bzero(recvbuffer, BUFFER_SIZE);
        iRecvLen = recv(_socketServer, recvbuffer, BUFFER_SIZE, 0);
        
        if (iRecvLen == -1||iRecvLen == 0) {
            //Socket 错误，做相应处理
            return; }
        
        //创建通知
        NSData *data1 = [NSData dataWithBytes:recvbuffer length:iRecvLen];
        NSString *recvLenStr = [[NSString alloc] initWithFormat:@"%d",iRecvLen];
        NSDictionary *recvLenDic = [[NSDictionary alloc] initWithObjectsAndKeys:recvLenStr,@"RecvLen",nil];
        notification =[NSNotification notificationWithName:@"通知_收到服务器消息" object:data1 userInfo:recvLenDic];
        
        //通过通知中心发送通知
        [[NSNotificationCenter defaultCenter] postNotification:notification];
    }
}

CSocketClient::CSocketClient(){}
CSocketClient::~CSocketClient(){}

int CSocketClient::ConnectServers() {//链接服务器
    //创建socket：socket（协议族IPv4，socket类型TCP、UDP、协议）
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == _socketServer) {
        NSLog(@"创建socket失败\n");
        return -1;
    }

    //连接服务器
    struct sockaddr_in socketParameters;
    socketParameters.sin_family = AF_INET;
    socketParameters.sin_addr.s_addr = inet_addr("192.168.0.123");
    socketParameters.sin_port = htons(60527);
    socketParameters.sin_len = sizeof(socketParameters);
    //connect(socket描述符、属性结构体、结构体长度)
    int iTmp = connect(_socketServer, (struct sockaddr *) &socketParameters, sizeof(socketParameters));
    if (-1 == iTmp) {
        NSLog(@"连接服务器socket失败\n");
        close(_socketServer);
        return -2; }
    
    //开Recv线程
    dispatch_queue_t queue = dispatch_queue_create("socketQueue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^{ RecvThread(); });
    
    return 1;
}

int CSocketClient::ConnectLocalHost() {//链接服务器
    //创建socket：socket（协议族IPv4，socket类型TCP、UDP、协议）
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == _socketServer) {
        NSLog(@"创建socket失败\n");
        return -1;
    }
    
    //连接服务器
    struct sockaddr_in socketParameters;
    socketParameters.sin_family = AF_INET;
    socketParameters.sin_addr.s_addr = inet_addr("192.168.0.102");
    socketParameters.sin_port = htons(60527);
    socketParameters.sin_len = sizeof(socketParameters);
    //connect(socket描述符、属性结构体、结构体长度)
    int iTmp = connect(_socketServer, (struct sockaddr *) &socketParameters, sizeof(socketParameters));
    if (-1 == iTmp) {
        NSLog(@"连接本地socket失败\n");
        close(_socketServer);
        return -2; }
    
    //开Recv线程
    dispatch_queue_t queue = dispatch_queue_create("socketQueue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^{ RecvThread(); });
    
    return 1;
}

//玩家发给服务器的消息：10~99
#define MsgToServer_玩家上线 10
#define MsgToServer_玩家下线 12
#define MsgToServer_玩家上桌 20
#define MsgToServer_玩家离桌 22

#define MsgToServer_玩家弃牌 30
#define MsgToServer_玩家让牌 32
#define MsgToServer_玩家下注 36

void CSocketClient::fuck让牌(Byte bPlayerPos){
    char csz_CheckOP[] = "xx";
    
    csz_CheckOP[0] = MsgToServer_玩家让牌;
    csz_CheckOP[1] = bPlayerPos;
    HJ_Send(csz_CheckOP, sizeof(csz_CheckOP));
}

void CSocketClient::fuck弃牌(Byte bPlayerPos){
    char csz_FoldOP[] = "xx";
    
    csz_FoldOP[0] = MsgToServer_玩家弃牌;
    csz_FoldOP[1] = bPlayerPos;
    HJ_Send(csz_FoldOP, sizeof(csz_FoldOP));
}

void CSocketClient::fuck下注(int iPour,Byte iPlayerPos){
    //数据结构：[协议号(1位A码)][玩家坐位号(1位A码)][下注筹码数(8位十六进制)]
    char csz_FoldOP[] = "xx00000100";
    csz_FoldOP[0] = MsgToServer_玩家下注;
    csz_FoldOP[1] = iPlayerPos;
    sprintf(csz_FoldOP + 2, "%08X", iPour);
    HJ_Send(csz_FoldOP, sizeof(csz_FoldOP));
}

int CSocketClient::fuck上桌() {//发送上桌消息
    //数据结构：协议号（1位）+ 玩家报名参考的比赛场次（1位）+ 玩家ID（8位十六进制）+ 房间号（8位十六进制）

    char cszSendBuff[24] = {0};
    cszSendBuff[0] = MSG_PLAYER_ONTABLE;
    cszSendBuff[1] = MT_房卡房100W积分场;
    sprintf(cszSendBuff+2, "%08X", 88888888);
    sprintf(cszSendBuff+10, "%08X", Test_VIPRoomID);
    
    return HJ_Send(cszSendBuff, 24);//请求char型数据
    
}

int CSocketClient::HJ_Send(char* pcszSendData, int iSendDataLen) {
    char cszSendData[256] = { 0 };
    
    cszSendData[0] = iSendDataLen/256;
    cszSendData[1] = iSendDataLen%256;
    
    memcpy(cszSendData+2, pcszSendData, iSendDataLen);
    
    return send(_socketServer, cszSendData, iSendDataLen+2, 0); //请求char型数据
}

