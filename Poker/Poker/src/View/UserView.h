#import <UIKit/UIKit.h>
@interface UserView : UIView//UIView.size 100 100

@property(nonatomic,strong)UIImageView *potrait;//玩家头像
@property(nonatomic,strong)UILabel *username;//玩家的用户名
@property(nonatomic,strong)UIImageView *firstPoker;//玩家的第一张牌
@property(nonatomic,strong)UIImageView *secondPoker;//玩家的第二张牌
@property(nonatomic,strong)UILabel *chipLabel;//玩家的筹码数
@property(nonatomic,strong)UIImageView *potraitBGImgView;//黑色大框
@property(nonatomic,strong)UIImageView *potraitCoverView;//黑色大框
@property(nonatomic,strong)CAShapeLayer *shapeLayer;
//@property(nonatomic,strong)NSTimer *timer;//定时器
@property(nonatomic,retain)CADisplayLink *timer;//定时器
-(void)startCycle;
-(void)endCycle;

//-(void)setPokersSize:(BOOL)bIsBigSize;
-(void)setCoverImgZIndex:(BOOL)bIsCover;
-(void)setIsSelf;
@end
