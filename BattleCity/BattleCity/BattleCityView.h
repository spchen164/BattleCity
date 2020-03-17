
// BattleCityView.h : CBattleCityView ��Ľӿ�
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
protected: // �������л�����
	CBattleCityView();
	DECLARE_DYNCREATE(CBattleCityView)

// ����
public:
	CBattleCityDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CBattleCityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ����
private:
	//һ��
	int stage;//��ǰ�ؿ�
	int EnemyAppear;//���˳��ֿ���
	int EnemyCount;//ͳ�Ƶ�����
	int status;//��Ϸ״̬

	//��ͼ
	CImage *background;//����ͼ
	CImage *Info;//��Ϸ��Ϣ����
	CRect *rcInfo;//��Ϸ��Ϣ������

	//��Ʒ
	Tank* Enemy[20];//20������
	int EnemyFlag[20];//����״̬��־
	Tank* Player;//���
	Map *map;//��ͼ
	vector<Reward*> reward;//��Ʒ
	vector<Bullet*> bullet;//�ӵ�
	
// �Զ��庯��
public:
	void DrawTank(HDC hdc);//����̹��
	void DrawMap(HDC hdc);//���Ƶ�ͼ����
	void DrawReward(HDC hdc);//���ƽ�Ʒ
	void DrawBullet(HDC hdc);//�����ӵ�
	void DrawGameInfo(HDC hdc);//������Ϸ��Ϣ
	bool IsBulletMeet(Bullet *b);//�ӵ��Ƿ���������Ʒ������ײ
	void InitStage(int s);//��ʼ���ؿ�

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // BattleCityView.cpp �еĵ��԰汾
inline CBattleCityDoc* CBattleCityView::GetDocument() const
   { return reinterpret_cast<CBattleCityDoc*>(m_pDocument); }
#endif

