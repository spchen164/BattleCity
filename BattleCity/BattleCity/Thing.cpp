//��Ʒ��ʵ��
#include "stdafx.h"
#include "Thing.h"

Thing::Thing()//Ĭ�Ϲ��캯��
{
	ThingType = THING_BLOCK;
	picture = NULL;
	rc.SetRect(0, 0, 0, 0);
}

Thing::Thing(int t, CString path, int x1, int y1, int x2, int y2)//���캯��
{
	ThingType = t;
	picture = new CImage();
	if (path == "")
	{
		delete picture;
		picture = NULL;
	}
	else
		picture->Load(path);
	rc.SetRect(x1, y1, x2, y2);
}

Thing::~Thing()//��������
{
	if (picture != NULL)
	{
		picture->ReleaseGDIPlus();
		delete picture;
	}
}

bool Thing::IsMeet(Thing *t1, Thing *t2)//��ײ���
{
	if (t1 == NULL || t2 == NULL)
		return false;
	int Xcenter1, Ycenter1;
	int Xcenter2, Ycenter2;
	int width1, height1;
	int width2, height2;

	width1 = t1->rc.Width();
	height1 = t1->rc.Height();
	width2 = t2->rc.Width();
	height2 = t2->rc.Height();

	//����2����Ʒ����������
	Xcenter1 = t1->rc.left + width1 / 2;
	Ycenter1 = t1->rc.top + height1 / 2;
	Xcenter2 = t2->rc.left + width2 / 2;
	Ycenter2 = t2->rc.top + height2 / 2;

	if (abs(Xcenter1 - Xcenter2) < (width1 + width2) / 2 && 
		abs(Ycenter1 - Ycenter2) < (height1 + height2) / 2
		)
		return true;
	return false;
}

void Thing::SetPicture(CString path)//����ͼ��
{
	delete picture;
	if (path == "")
		return;
	picture = new CImage();
	picture->Load(path);
}