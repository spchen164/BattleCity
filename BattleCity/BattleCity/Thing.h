//��Ʒ��
#pragma once

#include "Define.h"
#include <atlimage.h>
#include <math.h>

class Thing
{
public:
	Thing();//Ĭ�Ϲ��캯��
	Thing(int t, CString path, int x1, int y1, int x2, int y2);//���캯��
	virtual ~Thing();//��������
	static bool IsMeet(Thing *t1, Thing *t2);//��ײ���

	//���ݸ���
	void SetPicture(CString path);//����ͼƬ

	//���ݻ�ȡ
	virtual int GetThingType(){ return ThingType; }//��Ʒ����
	virtual CImage* GetPicture(){ return picture; }//ͼƬ
	virtual CRect* GetRC(){ return &rc; }//����
protected:
	int ThingType;//��Ʒ����
	CImage *picture;//ͼƬ��Դ
	CRect rc;//��Ʒ����
};