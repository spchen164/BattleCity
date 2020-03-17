
// BattleCityView.h : CBattleCityView 类的接口
//

#pragma once

#include <math.h>
#include <atlimage.h>
#include "Define.h"
#include "Tank.h"
#include "Bullet.h"
#include "Block.h"
#include "Map.h"
#include "Reward.h"
#include <vector>
#include <string.h>
#include <fstream>
using namespace std;

class CBattleCityView : public CView
{
protected: // 仅从序列化创建
	CBattleCityView();
	DECLARE_DYNCREATE(CBattleCityView)

// 特性
public:
	CBattleCityDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CBattleCityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 变量
private:
	//一般
	int stage;//当前关卡
	int EnemyAppear;//敌人出现控制
	int EnemyCount;//统计敌人数
	int status;//游戏状态

	//绘图
	CImage *background;//背景图
	CImage *Info;//游戏信息背景
	CRect *rcInfo;//游戏信息背景区

	//物品
	Tank* Enemy[20];//20个敌人
	int EnemyFlag[20];//敌人状态标志
	Tank* Player;//玩家
	Map *map;//地图
	vector<Reward*> reward;//奖品
	vector<Bullet*> bullet;//子弹
	
// 自定义函数
public:
	void DrawTank(HDC hdc);//绘制坦克
	void DrawMap(HDC hdc);//绘制地图方块
	void DrawReward(HDC hdc);//绘制奖品
	void DrawBullet(HDC hdc);//绘制子弹
	void DrawGameInfo(HDC hdc);//绘制游戏信息
	bool IsBulletMeet(Bullet *b);//子弹是否与其它物品发生碰撞
	void InitStage(int s);//初始化关卡

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // BattleCityView.cpp 中的调试版本
inline CBattleCityDoc* CBattleCityView::GetDocument() const
   { return reinterpret_cast<CBattleCityDoc*>(m_pDocument); }
#endif

