//方块类
#pragma once

#include "Thing.h"
#include "Define.h"
#include <time.h>
#include <stdlib.h>

class Block :public Thing
{
public:
	Block();//默认构造函数
	Block(int t, CString path, int x1, int y1, int x2, int y2, int bt);//构造函数
	virtual ~Block();//析构函数

	//数据获取
	int GetBlockType(){ return BlockType; }//类型
	bool GetIsTank(){ return IsTank; }//能否通过坦克
	bool GetIsBullet(){ return IsBullet; }//能否通过子弹
	bool GetIsReward(){ return IsReward; }//奖品
	int GetRank(){ return rank; }//等级
private:
	int BlockType;//方块类型
	bool IsTank;//能否通过坦克
	bool IsBullet;//能否通过子弹
	bool IsReward;//是否有奖品
	int rank;//方块等级(直接使用坦克等级表示)
};