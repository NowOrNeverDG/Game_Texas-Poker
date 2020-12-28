#import <Foundation/Foundation.h>
#import <arpa/inet.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <UIKit/UIKit.h>

#define ksboundsWidth   [UIScreen mainScreen].bounds.size.width
#define ksboundsHeight  [UIScreen mainScreen].bounds.size.height
#define BUFFER_SIZE 1024
#define EVERYPLAYER_TIME    15

#define 第一张私牌的序号    0
#define 第二张私牌的序号    1
#define 第一张公牌的序号    0
#define 第二张公牌的序号    1
#define 第三张公牌的序号    2
#define 第四张公牌的序号    3
#define 第五张公牌的序号    4
@interface Commons : NSObject

@end
