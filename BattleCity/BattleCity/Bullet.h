//子弹类
#pragma once

#include "Thing.h"
#include "Define.h"
#include "Tank.h"
#include "Map.h"
#include <vector>

class Tank;//声明坦克类
class Bullet :public Thing
{
public:
	Bullet();//默认构造函数
	Bullet(int t, CString path, int x1, int y1, int x2, int y2, Tank *tk);//构造函数
	virtual ~Bullet();//析构函数

	//数据更新
	void Move();//子弹移动

	//数据获取
	Tank* GetFromTank(){ return FromTank; }//来源坦克类型
	int GetSource(){ return source; }//来源
	int GetDirect(){ return direct; }//方向
	int GetSpeed(){ return speed; }//速度
private:
	Tank *FromTank;//来源坦克指针
	int source;//子弹来源坦克类型
	int direct;//子弹方向
	int speed;//子弹速度
};