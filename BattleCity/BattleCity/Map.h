//地图类
#pragma once

#include "Define.h"
#include "Block.h"
#include <string.h>
#include <fstream>
using namespace std;

class Map
{
public:
	Map();//默认构造函数
	Map(int s);//构造函数
	~Map();//析构函数

	//数据更新
	void SetMap(int r, int c, int bt);//更新地图界面
	void SetWallType(int w);//设置城墙类型

	//数据获取
	Block* GetMap(int r, int c);//地图
	int GetStage(){ return stage; }//关卡
	int GetWallType(){ return WallType; }//城墙类型
private:
	Block* map[15][15];//地图
	int stage;//关卡
	int WallType;//城墙类型
};