
// LMCapp.h : LMCapp Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLMCappApp:
// �йش����ʵ�֣������ LMCapp.cpp
//

class CLMCappApp : public CWinAppEx
{
public:
	CLMCappApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	BOOL  is_app_run;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public://����ȫ�ֱ���
	HBRUSH m_brush;
};

extern CLMCappApp theApp;
