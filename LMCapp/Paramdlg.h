#pragma once
#include "Motor.h"
#include "Logic.h"
#include "afxcmn.h"
#include "Cmath.h"
// CParamdlg 对话框

class CParamdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParamdlg)

public:
	CParamdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamdlg();

// 对话框数据
	enum { IDD = IDD_MOTORDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	long m_homespeed;
	long m_startspeed;
	long m_accspeed;
	long m_maxspeed;
	long m_jogspeed;
	virtual BOOL OnInitDialog();
	void update_speed();
	void update_status();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedHome();
	afx_msg void OnBnClickedMostop();
	afx_msg void OnBnClickedMove();
	long m_pos;
	afx_msg void OnBnClickedSave();
	afx_msg void OnEnKillfocusHomesped();
	afx_msg void OnEnKillfocusStartsped();
	afx_msg void OnEnKillfocusAccsped();
	afx_msg void OnEnKillfocusMaxsped();
	afx_msg void OnEnKillfocusJogsped();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCahange();
	CTreeCtrl m_Motortree;
	HTREEITEM Item,subitem[2],motor_Item[32];
	CString tree_str[32];
	UINT motor_index;
	afx_msg void OnSelchangedMotortree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnBnClickedSvo();
	afx_msg void OnBnClickedSvo2();
};
