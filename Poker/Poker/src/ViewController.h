#import <UIKit/UIKit.h>
#import "Socket/SocketClient.h"
#import "TableData.h"

//C++混合编程部分
@interface ViewController : UIViewController<UITextFieldDelegate,CAAnimationDelegate> {
    
@public
    CSocketClient* _socketClient;
    CTableData* _tableData;
}

@property(nonatomic,strong)UIView* poolBGView;
//@property (nonatomic) NSMutableArray    *notifications;         // 通知队列
//@property (nonatomic) NSThread          *notificationThread;    // 期望线程
//@property (nonatomic) NSLock            *notificationLock;      // 用于对通知队列加锁的锁对象，避免线程冲突
//@property (nonatomic) NSMachPort        *notificationPort;      // 用于向期望线程发送信号的通信端口



@end

