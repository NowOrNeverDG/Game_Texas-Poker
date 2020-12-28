//
//  ViewController.m
//  Servers
//
//  Created by BioGo on 2016/12/22.
//  Copyright © 2016年 BioGo. All rights reserved.
//

#import "ViewController.h"
#include <arpa/inet.h>
#import <ifaddrs.h>
#include <sys/event.h>
#include <sys/socket.h>
#import  <AVFoundation/AVFoundation.h>
//服务器发给玩家的消息：10~99
#define MsgFromServer_玩家上线 10
#define MsgFromServer_玩家下线 12
#define MsgFromServer_玩家上桌 20
#define MsgFromServer_玩家离桌 22

#define MsgFromServer_玩家弃牌 30
#define MsgFromServer_玩家让牌 32
#define MsgFromServer_玩家下注 36
#define MsgFromServer_玩家操作 39

#define MsgFromServer_添加玩家 50
#define MsgFromServer_等待荷官 52
#define MsgFromServer_开始比赛 53
#define MsgFromServer_结束比赛 56 //未进行到最后的比赛
#define MsgFromServer_比赛结果 57 //经分析后得到的结果
#define MsgFromServer_荷官发牌 58
#define MsgFromServer_玩家明牌 59

#define MsgFromServer_创建房间 60
#define MsgFromServer_关闭房间 62
#define MsgFromServer_房间开赛 66

#define MsgFromServer_组桌_组桌成功 70
#define MsgFromServer_组桌_无此房间 72
#define MsgFromServer_组桌_人数已满 74
#define MsgFromServer_组桌_筹码不足 76
#define MsgFromServer_组桌_已经上桌 78
#define MsgFromServer_开局_玩家过少 80
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024

@implementation ViewController
{
    int g_socketServer;
    int clientSocket;
    int _iTmp;
    int _playerOP;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    g_socketServer = 0;
    
    [self BTNClick_StartSocket:nil];

}

-(void)viewWillDisappear {
    close(g_socketServer);
}

- (IBAction)BTNClick_StartSocket:(id)sender {
    //创建socket
    g_socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (g_socketServer < 0) {
        printf("创建socket失败\n");
        return;
    }
    
    //绑定socket
    struct sockaddr_in serverAddr;
    bzero(&serverAddr,sizeof(serverAddr)); //把一段内存区的内容全部设置为0
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_len = sizeof(serverAddr);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(60526);
    int opt =bind(g_socketServer,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if (opt < 0) {
        printf("服务器绑定失败\n");
        return;
    }
    NSLog(@"服务器绑定成功\n");
    
    //服务器端开始监听
    if (listen(g_socketServer, LENGTH_OF_LISTEN_QUEUE) == -1) {
        printf("服务器监听失败\n");
        close(g_socketServer);
        return;
    }
    printf("服务器监听成功\n");
    
    //定义客户端的socket地址结构client_addr
    struct sockaddr_in clientAddr;
    int iLength = sizeof(clientAddr);
    
    dispatch_queue_t queue = dispatch_queue_create("socketQueue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^{
        clientSocket = 0;
        
        while (1) {//服务器端要一直运行
            /*接受一个到server_socket代表的socket的一个连接
             如果没有连接请求,就等待到有连接请求--这是accept函数的特性
             accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信
             newServerSocket代表了服务器和客户端之间的一个通信通道
             accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中*/
            printf("服务器准备接收!\n");
            
            clientSocket = accept(g_socketServer,(struct sockaddr*)&clientAddr,&iLength);
            if (clientSocket < 0) {
                printf("服务器接受失败\n");
                close(g_socketServer);
                break;
            }
            printf("服务器完成接收!\n");
            
            dispatch_queue_t queue = dispatch_queue_create("socketQueue", DISPATCH_QUEUE_CONCURRENT);
            dispatch_async(queue, ^{
                NSLog(@"当前线程是：%@",[NSThread currentThread]);
                
                //创建发送的数据文件
//                typedef struct {
//                    short players_DX[12]; //玩家0的牌面大小
//                    short players_HS[12]; //玩家0的牌面花色
//                    short commons_DX[5];
//                    short commons_HS[5];
//                }TABLE_POKER, *PTABLE_POKER;
//                TABLE_POKER t = {{1,12,4,5,9,12,2,12,4,3,9,4},{1,3,4,2,2,3,1,1,1,3,2,4},{3,6,8,1,10},{1,3,4,2,3}};
                char csz[1024];
                
                while(1) {
                    //接收数据
                    char recvbuffer[BUFFER_SIZE];
                    bzero(recvbuffer, BUFFER_SIZE);
                    ssize_t length = recv(clientSocket,recvbuffer,BUFFER_SIZE,0);
                    NSLog(@"从客户端接收的数据长度为：%zd",length);//接受的长度
                    NSLog(@"客户端发送给服务地的信息：%@",[NSString stringWithFormat:@"%s",recvbuffer]);//接受的内容
                    //发送数据
//                    bzero(csz, 1024);
//                    memcpy(csz, &t, sizeof(TABLE_POKER));
//                    size_t iSendBufferLen = strlen(csz);
                    //ssize_t iSendedLen = send(clientSocket, &t, sizeof(TABLE_POKER), 0);
                    //NSLog(@"发送的字节数：%zd\n",iSendedLen);
                    //close(g_socketServer);
                }
                ;});
        }
    });

}

- (IBAction)BTNClick_endSocket:(id)sender {
    //关闭与客户端的连接
    close(g_socketServer);
}

- (IBAction)playerOnTableAction:(id)sender {
    
    
    char csz[] = "xx1xxxx丫000001400xx牛100001500xx王200001600xx张300001700xx赵400001800";
    int iLen = (int)strlen(csz);
    csz[0] = 0;
    csz[1] = iLen - 2;
    
    csz[2] = MsgFromServer_玩家上桌;
    csz[3] = 5;//玩家人数
    csz[4] = 3;//玩家自己的编号
    
    csz[5] = 0;//玩家编号0
    csz[6] = 4;
    csz[19] = 1;//玩家编号1
    csz[20] = 4;
    csz[33] = 2;//玩家编号2
    csz[34] = 4;
    csz[47] = 3;//玩家编号3
    csz[48] = 4;
    csz[61] = 4;//玩家编号4
    csz[62] = 4;
    send(clientSocket, csz, iLen, 0);
}

- (IBAction)addPlayer:(id)sender {
    char csz[] = "xxxxx增500002000";
    int iLen = (int)strlen(csz);
    csz[0] = 0;
    csz[1] = iLen - 2;
    
    csz[2] = MsgFromServer_添加玩家;
    csz[3] = 5;
    csz[4] = 4;
    send(clientSocket, csz, iLen, 0);
}

- (IBAction)startMatch:(id)sender {
    _iTmp = 0; _playerOP = 0;
    
    //[协议号(1位ASCII码)][庄家坐位号(1位A码)][小盲坐位号(1位A码)][大盲坐位号(1位A码)][大盲注(8位十六进制)][小盲注(8位十六进制)][前注(8位十六进制)]
    //[玩家数量(1位A码)]{[玩家坐位号(1位A码)][玩家当前筹码数(8位十六进制)][玩家当前当前下注数(8位十六进制)]}
    char csz[] = "xxxxxx000002000000015000000100xx0000010000000100x0000010000000200x0000010000000300x0000010000000400x0000010000000500x0000010000000600";
    int iLen = (int)strlen(csz);
    csz[0] = 0;
    csz[1] = iLen - 2;
    
    csz[2] = MsgFromServer_开始比赛;
    csz[3] = 0;
    csz[4] = 1;
    csz[5] = 2;
    csz[30] = 6;
    csz[31] = 0;//1号玩家设置筹码和下注数
    csz[48] = 1;
    csz[65] = 2;
    csz[82] = 3;
    csz[99] = 4;
    csz[116] = 5;
    send(clientSocket, csz, iLen, 0);
}

- (IBAction)dealPokerAction:(id)sender {
    char csz_Deal[8] = {0};
    csz_Deal[0] = 0;
    csz_Deal[1] = sizeof(csz_Deal) - 2;
    csz_Deal[2] = MsgFromServer_荷官发牌;
    
    if (_iTmp <= 5) {
        //        csz_Deal[3] = 88;
        //        csz_Deal[4] = _iTmp;
        csz_Deal[3] = (_iTmp)%6;
        csz_Deal[4] = 0;
        csz_Deal[5] = 0;//花色
        csz_Deal[6] = 0;//大小
        csz_Deal[7] = 88;
    } else if (6 <= _iTmp &&  _iTmp < 11){
        csz_Deal[3] = (_iTmp)%6;
        csz_Deal[4] = 1;
        csz_Deal[5] = 0;//花色
        csz_Deal[6] = 0;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 11) {
        csz_Deal[3] = 5;
        csz_Deal[4] = 1;
        csz_Deal[5] = 0;//花色
        csz_Deal[6] = 0;//大小
        csz_Deal[7] = 88;
        
    } else if ( _iTmp == 12) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 0;
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 6;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 13) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 1;
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 5;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 14) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 2;
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 4;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 15) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 3;
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 3;//大小
        csz_Deal[7] = 88;
    } else if ( _iTmp == 16) {
        csz_Deal[3] = 88;
        csz_Deal[4] = 4;
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 2;//大小
        csz_Deal[7] = 0;
    }
    
    if (_iTmp == 3) {
        csz_Deal[5] = 3;//花色
        csz_Deal[6] = 11;//大小
    }
    if (_iTmp == 9) {
        csz_Deal[5] = 4;//花色
        csz_Deal[6] = 11;//大小
    }
    _iTmp++;
    send(clientSocket, csz_Deal, sizeof(csz_Deal), 0);
}
- (IBAction)dealerPoker12:(id)sender {
    for (int i = 0; i < 17; i++) {
        [self dealPokerAction:nil];
    }
}

- (IBAction)matchResultAction:(id)sender {
    //[协议号(1位A码)][赢家人数(1位A码)]{[赢家坐位号(1位A码:0~5)][筹码数(8位十六进制)]}
    char csz_FinishOP[] = "xxxxx00005000x00003000";
    csz_FinishOP[0] = 0;
    csz_FinishOP[1] = sizeof(csz_FinishOP) - 2;
    csz_FinishOP[2] = MsgFromServer_比赛结果;
    csz_FinishOP[3] = 2;
    csz_FinishOP[4] = 3;
    csz_FinishOP[13] = 4;
    send(clientSocket, csz_FinishOP, sizeof(csz_FinishOP), 0);
}

- (IBAction)endMatchAction:(id)sender {
    //[协议号(1位A码)][赢家坐位号(1位A码:0~5)][筹码数(8位十六进制)]
    char csz_endMatchOP[] = "xxxx00005000";
    csz_endMatchOP[0] = 0;
    csz_endMatchOP[1] = sizeof(csz_endMatchOP) - 2;
    csz_endMatchOP[2] = MsgFromServer_结束比赛;
    csz_endMatchOP[3] = 5;
    send(clientSocket, csz_endMatchOP, sizeof(csz_endMatchOP), 0);
}

- (IBAction)foldMatch:(id)sender {
    char csz_FoldOP[5] = { 0 };
    csz_FoldOP[0] = 0;
    csz_FoldOP[1] = sizeof(csz_FoldOP) - 2;
    csz_FoldOP[2] = MsgFromServer_玩家弃牌;
    csz_FoldOP[3] = _playerOP;
    csz_FoldOP[4] = ++_playerOP;
    if (csz_FoldOP[3] == 5) {
        csz_FoldOP[4] = 88; }
    
    send(clientSocket, csz_FoldOP, sizeof(csz_FoldOP), 0);
    
    
}

- (IBAction)checkMatch:(id)sender {
    char csz_CheckOP[16] = { 0 };
    csz_CheckOP[0] = 0;
    csz_CheckOP[1] = sizeof(csz_CheckOP) - 2;
    csz_CheckOP[2] = MsgFromServer_玩家让牌;
    csz_CheckOP[3] = _playerOP;
    csz_CheckOP[4] = ++_playerOP;
    if (csz_CheckOP[3] == 5) { csz_CheckOP[4] = 88; }
    send(clientSocket, csz_CheckOP, sizeof(csz_CheckOP), 0);
}

- (IBAction)addPourAction:(id)sender {
    char csz_CallOP[] = "xxxx00000100x";
    csz_CallOP[0] = 0;
    csz_CallOP[1] = sizeof(csz_CallOP) - 2;
    csz_CallOP[2] = MsgFromServer_玩家下注;
    csz_CallOP[3] = _playerOP;
    csz_CallOP[12] = ++_playerOP;
    if (csz_CallOP[3] == 5) { csz_CallOP[12] = 88; }
    send(clientSocket, csz_CallOP, sizeof(csz_CallOP), 0);
}

- (IBAction)openPokerActon:(id)sender {
    char csz_OpenPoker[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    csz_OpenPoker[0] = 0;
    csz_OpenPoker[1] = sizeof(csz_OpenPoker) - 2;
    csz_OpenPoker[2] = MsgFromServer_玩家明牌;
    csz_OpenPoker[3] = 5;
    csz_OpenPoker[4] = 0;//玩家座位号
    csz_OpenPoker[5] = 1;
    csz_OpenPoker[6] = 1;
    csz_OpenPoker[7] = 2;
    csz_OpenPoker[8] = 1;
    csz_OpenPoker[9] = 1;//玩家座位号
    csz_OpenPoker[10] = 2;
    csz_OpenPoker[11] = 13;
    csz_OpenPoker[12] = 1;
    csz_OpenPoker[13] = 12;
    csz_OpenPoker[14] = 2;//玩家座位号
    csz_OpenPoker[15] = 1;
    csz_OpenPoker[16] = 13;
    csz_OpenPoker[17] = 2;
    csz_OpenPoker[18] = 12;
    csz_OpenPoker[19] = 4;//玩家座位号
    csz_OpenPoker[20] = 4;
    csz_OpenPoker[21] = 10;
    csz_OpenPoker[22] = 3;
    csz_OpenPoker[23] = 10;
    csz_OpenPoker[24] = 5;//玩家座位号
    csz_OpenPoker[25] = 2;
    csz_OpenPoker[26] = 3;
    csz_OpenPoker[27] = 1;
    csz_OpenPoker[28] = 4;
    send(clientSocket, csz_OpenPoker, sizeof(csz_OpenPoker), 0);
}

//获取IP地址的方法
- (NSString *)getIPAddress {
    NSString *address = @"getIPAddress";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);
    return address;
}
@end
