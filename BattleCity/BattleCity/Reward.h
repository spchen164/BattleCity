//��Ʒ��
#pragma once

#include "Thing.h"
#include "Define.h"
#include "Tank.h"
#include "Map.h"

class Tank;//ǰ������
class Reward :public Thing
{
public:
	Reward();//Ĭ�Ϲ��캯��
	Reward(int t, CString path, int x1, int y1, int x2, int y2, int rt);//���캯��
	virtual ~Reward();//��������
	void Improve(Tank &tk, Map *m);//��Ʒ�ӳ����

	//���ݻ�ȡ
	int GetRewardType(){ return RewardType; }
private:
	int RewardType;//��Ʒ����
};