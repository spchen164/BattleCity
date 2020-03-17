//坦克类
#pragma once

#include "Thing.h"
#include "Define.h"
#include "Bullet.h"
#include "Map.h"
#include "Reward.h"
#include <time.h>
#include <stdlib.h>
#include <vector>

class Bullet;//声明子弹类
class Reward;//声明奖品类
class Tank:public Thing
{
public:
	Tank();//默认构造函数
	Tank(int thingt, CString path, int x1, int y1, int x2, int y2, int tankt, int r, int d);//构造函数
	virtual ~Tank();//析构函数
	void Move(HWND hWnd, UINT nChar, Map *m, Tank *t);//移动函数 根据坦克信息变化位置信息
	void Stop(HWND hWnd, UINT nChar);//停止移动函数
	void ShootBullet(int t, CString path, int x1, int y1, int x2, int y2);//发射子弹
	void DestroyBullet();//销毁子弹

	//数据更新
	void ImproveLife();//增加生命数
	void DecreaseLife();//减少生命数
	void ImproveRank();//提升等级
	void SetRC(int r, int c);//设置位置
	void MoveUp(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);
	void MoveDown(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);
	void MoveLeft(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);
	void MoveRight(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);

	//数据获取
	int GetTankType(){ return TankType; }//坦克类型
	int GetLife(){ return life; }//生命数
	int GetRank(){ return rank; }//等级
	int GetSpeed(){ return speed; }//速度
	int GetDirect(){ return direct; }//方向
	Bullet* GetBullet(){ return bullet; }//子弹
private:
	int TankType;//坦克类型
	int life;//坦克生命数
	int rank;//坦克等级
	int speed;//坦克速度
	int direct;//坦克方向
	Bullet *bullet;//子弹
};
