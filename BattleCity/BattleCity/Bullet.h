//�ӵ���
#pragma once

#include "Thing.h"
#include "Define.h"
#include "Tank.h"
#include "Map.h"
#include <vector>

class Tank;//����̹����
class Bullet :public Thing
{
public:
	Bullet();//Ĭ�Ϲ��캯��
	Bullet(int t, CString path, int x1, int y1, int x2, int y2, Tank *tk);//���캯��
	virtual ~Bullet();//��������

	//���ݸ���
	void Move();//�ӵ��ƶ�

	//���ݻ�ȡ
	Tank* GetFromTank(){ return FromTank; }//��Դ̹������
	int GetSource(){ return source; }//��Դ
	int GetDirect(){ return direct; }//����
	int GetSpeed(){ return speed; }//�ٶ�
private:
	Tank *FromTank;//��Դ̹��ָ��
	int source;//�ӵ���Դ̹������
	int direct;//�ӵ�����
	int speed;//�ӵ��ٶ�
};