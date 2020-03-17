//物品类
#pragma once

#include "Define.h"
#include <atlimage.h>
#include <math.h>

class Thing
{
public:
	Thing();//默认构造函数
	Thing(int t, CString path, int x1, int y1, int x2, int y2);//构造函数
	virtual ~Thing();//析构函数
	static bool IsMeet(Thing *t1, Thing *t2);//碰撞检测

	//数据更新
	void SetPicture(CString path);//更新图片

	//数据获取
	virtual int GetThingType(){ return ThingType; }//物品类型
	virtual CImage* GetPicture(){ return picture; }//图片
	virtual CRect* GetRC(){ return &rc; }//区域
protected:
	int ThingType;//物品类型
	CImage *picture;//图片资源
	CRect rc;//物品区域
};