//方块类实现
#include "stdafx.h"
#include "Block.h"

Block::Block()//默认构造函数
{
	BlockType = BLOCK_TYPE_WOOD;
	IsTank = false;
	IsBullet = false;
	IsReward = false;
	rank = TANK_LEVEL1;
}

//构造函数
Block::Block(int t, CString path, int x1, int y1, int x2, int y2, int bt)
	:Thing(t, path, x1, y1, x2, y2)
{
	BlockType = bt;
	switch (BlockType)
	{
	case BLOCK_TYPE_BLANK:
		IsTank = true;
		IsBullet = true;
		rank = TANK_LEVEL1;
		break;
	case BLOCK_TYPE_WOOD:
		IsTank = false;
		IsBullet = false;
		rank = TANK_LEVEL1;
		break;
	case BLOCK_TYPE_IRON:
		IsTank = false;
		IsBullet = false;
		rank = TANK_LEVEL3;
		break;
	case BLOCK_TYPE_RIVER:
		IsTank = false;
		IsBullet = true;
		rank = TANK_LEVEL1;
		break;
	case BLOCK_TYPE_GRASS:
		IsTank = true;
		IsBullet = true;
		rank = TANK_LEVEL1;
		break;
	case BLOCK_TYPE_BRICK:
		IsTank = false;
		IsBullet = false;
		rank = TANK_LEVEL2;
		break;
	case BLOCK_TYPE_BASE:
		IsTank = false;
		IsBullet = false;
		rank = TANK_LEVEL1;
		break;
	case BLOCK_TYPE_LOSE:
		IsTank = false;
		IsBullet = true;
		rank = TANK_LEVEL1;
		break;
	}

	IsReward = false;
	if (BlockType != BLOCK_TYPE_BASE)
	{
		double p = (double)rand() / RAND_MAX;
		if (p < 0.03)
			IsReward = true;
		else
			IsReward = false;
	}
}

Block::~Block()//析构函数
{

}