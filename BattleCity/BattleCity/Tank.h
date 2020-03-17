//̹����
#pragma once

#include "Thing.h"
#include "Define.h"
#include "Bullet.h"
#include "Map.h"
#include "Reward.h"
#include <time.h>
#include <stdlib.h>
#include <vector>

class Bullet;//�����ӵ���
class Reward;//������Ʒ��
class Tank:public Thing
{
public:
	Tank();//Ĭ�Ϲ��캯��
	Tank(int thingt, CString path, int x1, int y1, int x2, int y2, int tankt, int r, int d);//���캯��
	virtual ~Tank();//��������
	void Move(HWND hWnd, UINT nChar, Map *m, Tank *t);//�ƶ����� ����̹����Ϣ�仯λ����Ϣ
	void Stop(HWND hWnd, UINT nChar);//ֹͣ�ƶ�����
	void ShootBullet(int t, CString path, int x1, int y1, int x2, int y2);//�����ӵ�
	void DestroyBullet();//�����ӵ�

	//���ݸ���
	void ImproveLife();//����������
	void DecreaseLife();//����������
	void ImproveRank();//�����ȼ�
	void SetRC(int r, int c);//����λ��
	void MoveUp(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);
	void MoveDown(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);
	void MoveLeft(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);
	void MoveRight(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward);

	//���ݻ�ȡ
	int GetTankType(){ return TankType; }//̹������
	int GetLife(){ return life; }//������
	int GetRank(){ return rank; }//�ȼ�
	int GetSpeed(){ return speed; }//�ٶ�
	int GetDirect(){ return direct; }//����
	Bullet* GetBullet(){ return bullet; }//�ӵ�
private:
	int TankType;//̹������
	int life;//̹��������
	int rank;//̹�˵ȼ�
	int speed;//̹���ٶ�
	int direct;//̹�˷���
	Bullet *bullet;//�ӵ�
};
