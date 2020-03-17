//宏定义头文件
#pragma once

//游戏状态
#define GAME_DOING 100
#define GAME_FINISH 101
#define TOTAL_STAGE 3

//界面
#define GAME_WIDTH 480
#define GAME_HEIGHT 480
#define INFO_WIDTH 200
#define BLOCK_LENGTH 32
#define BULLET_LENGTH 12

//定时器宏定义
#define TIMER_PAINT 0
#define TIMER_TIMESTOP 1
#define TIMER_DIR_UP 2
#define TIMER_DIR_DOWN 3
#define TIMER_DIR_LEFT 4
#define TIMER_DIR_RIGHT 5
#define TIMER_ENEMY 6

//方向
#define DIR_UP 40
#define DIR_DOWN 41
#define DIR_LEFT 42
#define DIR_RIGHT 43
#define DIR_LEFTUP 44
#define DIR_RIGHTUP 45
#define DIR_LEFTDOWN 46
#define DIR_RIGHTDOWN 47

//物品类类型
#define THING_TANK 50
#define THING_BULLET 51
#define THING_BLOCK 52
#define THING_REWARD 53

//坦克类宏定义
//类型
#define TANK_TYPE_PLAYER 54
#define TANK_TYPE_ENEMY 55
//等级
#define TANK_LEVEL1 1
#define TANK_LEVEL2 2
#define TANK_LEVEL3 3
//速度(参数)
#define TANK_SPEED_SLOW 2
#define TANK_SPEED_MEDIUM 3
#define TANK_SPEED_FAST 4
//敌人状态标志
#define ENEMY_HIDE 60
#define ENEMY_APPEAR 61
#define ENEMY_BEATEN 62

//子弹类宏定义
//速度(参数)
#define BULLET_SPEED_SLOW 4
#define BULLET_SPEED_MEDIUM 5
#define BULLET_SPEED_FAST 6

//方块类宏定义
//类型(参数)
#define BLOCK_TYPE_BLANK 0
#define BLOCK_TYPE_WOOD 1
#define BLOCK_TYPE_IRON 2
#define BLOCK_TYPE_RIVER 3
#define BLOCK_TYPE_GRASS 4
#define BLOCK_TYPE_BRICK 5
#define BLOCK_TYPE_BASE 6
#define BLOCK_TYPE_LOSE 7

//奖品类宏定义
//类型
#define REWARD_TYPE_LIFEUP 70
#define REWARD_TYPE_LEVELUP 71
#define REWARD_TYPE_STRENGTH 72
#define REWARD_TYPE_TIMESTOP 73