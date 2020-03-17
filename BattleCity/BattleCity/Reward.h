//奖品类
#pragma once

#include "Thing.h"
#include "Define.h"
#include "Tank.h"
#include "Map.h"

class Tank;//前置声明
class Reward :public Thing
{
public:
	Reward();//默认构造函数
	Reward(int t, CString path, int x1, int y1, int x2, int y2, int rt);//构造函数
	virtual ~Reward();//析构函数
	void Improve(Tank &tk, Map *m);//奖品加成情况

	//数据获取
	int GetRewardType(){ return RewardType; }
private:
	int RewardType;//奖品类型
};