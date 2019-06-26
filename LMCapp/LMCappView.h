
// LMCappView.h : CLMCappView 类的接口
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#define IDC_TABCTRL                     16888
extern  int Step[5];
class CLMCappView : public CFormView
{
protected: // 仅从序列化创建
	CLMCappView();
	DECLARE_DYNCREATE(CLMCappView)

public:
	enum{ IDD = IDD_LMCAPP_FORM };

// 特性
public:
	CLMCappDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CLMCappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// 生成的消息映射函数
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

#ifndef _DEBUG  // LMCappView.cpp 中的调试版本
inline CLMCappDoc* CLMCappView::GetDocument() const
   { return reinterpret_cast<CLMCappDoc*>(m_pDocument); }
#endif

