
// LMCappView.h : CLMCappView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#define IDC_TABCTRL                     16888
extern  int Step[5];
class CLMCappView : public CFormView
{
protected: // �������л�����
	CLMCappView();
	DECLARE_DYNCREATE(CLMCappView)

public:
	enum{ IDD = IDD_LMCAPP_FORM };

// ����
public:
	CLMCappDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CLMCappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_static0;
	CStatic m_static1;
	CListCtrl m_runlist1;
	CListCtrl m_runlist2;
	void addruninfo1(CString str);
	void addruninfo2(CString str);
	int  m_Step[5];
	void AddStep(int &step);
	CEdit m_alarminfo;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // LMCappView.cpp �еĵ��԰汾
inline CLMCappDoc* CLMCappView::GetDocument() const
   { return reinterpret_cast<CLMCappDoc*>(m_pDocument); }
#endif

