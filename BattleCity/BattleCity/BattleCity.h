
// BattleCity.h : BattleCity Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

// CBattleCityApp:
// �йش����ʵ�֣������ BattleCity.cpp
//

class CBattleCityApp : public CWinApp
{
public:
	CBattleCityApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBattleCityApp theApp;
