//������
#pragma once

#include "Thing.h"
#include "Define.h"
#include <time.h>
#include <stdlib.h>

class Block :public Thing
{
public:
	Block();//Ĭ�Ϲ��캯��
	Block(int t, CString path, int x1, int y1, int x2, int y2, int bt);//���캯��
	virtual ~Block();//��������

	//���ݻ�ȡ
	int GetBlockType(){ return BlockType; }//����
	bool GetIsTank(){ return IsTank; }//�ܷ�ͨ��̹��
	bool GetIsBullet(){ return IsBullet; }//�ܷ�ͨ���ӵ�
	bool GetIsReward(){ return IsReward; }//��Ʒ
	int GetRank(){ return rank; }//�ȼ�
private:
	int BlockType;//��������
	bool IsTank;//�ܷ�ͨ��̹��
	bool IsBullet;//�ܷ�ͨ���ӵ�
	bool IsReward;//�Ƿ��н�Ʒ
	int rank;//����ȼ�(ֱ��ʹ��̹�˵ȼ���ʾ)
};