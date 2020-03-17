//奖品类实现
#include "stdafx.h"
#include "Reward.h"

extern bool stop;

Reward::Reward()//默认构造函数
{
	RewardType = REWARD_TYPE_LEVELUP;
}

//构造函数
Reward::Reward(int t, CString path, int x1, int y1, int x2, int y2, int rt)
	:Thing(t, path, x1, y1, x2, y2)
{
	RewardType = rt;
}

Reward::~Reward()//析构函数
{

}

void Reward::Improve(Tank &tk, Map *m)//奖品加成情况
{
	int temp = 0;
	switch (RewardType)
	{
	case REWARD_TYPE_LIFEUP:
		tk.ImproveLife();
		break;
	case REWARD_TYPE_LEVELUP:
		tk.ImproveRank();
		break;
	case REWARD_TYPE_STRENGTH:
		temp = m->GetWallType();
		if (temp == BLOCK_TYPE_WOOD)
		{
			temp = BLOCK_TYPE_BRICK;
			m->SetWallType(BLOCK_TYPE_BRICK);
		}
		else if (temp == BLOCK_TYPE_BRICK)
		{
			temp = BLOCK_TYPE_IRON;
			m->SetWallType(BLOCK_TYPE_IRON);
		}
		else
			break;
		m->SetMap(13, 6, temp);
		m->SetMap(13, 7, temp);
		m->SetMap(13, 8, temp);
		m->SetMap(14, 6, temp);
		m->SetMap(14, 8, temp);
		break;
	case REWARD_TYPE_TIMESTOP:
		stop = true;
		break;
	default:
		break;
	}
}
