#pragma once
#include "Cmath.h"
#include "Cpassword.h"
// CSetcamera 对话框

class CSetcamera : public CDialogEx
{
	DECLARE_DYNAMIC(CSetcamera)

public:
	CSetcamera(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetcamera();

// 对话框数据
	enum { IDD = IDD_setcamera };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_gain0;
	int m_shutter0;
	afx_msg void OnBnClickedChange();
	virtual BOOL OnInitDialog();
	int m_gain1;
	int m_shutter1;
	afx_msg void OnBnClickedOk();
	int m_width0;
	int m_width1;
	int m_height0;
	int m_height1;
	int m_area0;
	int m_area1;
	int m_ra0;
	int m_ra1;
	int m_rb0;
	int m_rb1;
	float m_radius;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnBnClickedGrabonce0();
	afx_msg void OnBnClickedGrabonce1();
	afx_msg void OnBnClickedCongrb0();
	afx_msg void OnBnClickedCongrb1();
	afx_msg void OnBnClickedOpenled0();
	afx_msg void OnBnClickedOpenled1();
	afx_msg void OnBnClickedMesaure0();
	afx_msg void OnBnClickedSaveimg0();
	afx_msg void OnBnClickedSaveimg1();
	float m_angle;
	afx_msg void OnBnClickedChangeangle0();
	afx_msg void OnBnClickedChangeangle2();
	double m_row0;
	double m_row1;
	double m_row2;
	double m_row3;
	double m_column0;
	double m_column1;
	double m_column2;
	double m_column3;
	double m_radius0;
	double m_radius1;
	double m_radius2;
	double m_radius3;
	int m_thresd0;
	int m_thresd1;
	int m_thresd2;
	int m_thresd3;
	afx_msg void OnBnClickedDispcircle();
	afx_msg void OnBnClickedDraw0();
	afx_msg void OnBnClickedDraw1();
	afx_msg void OnBnClickedDraw2();
	afx_msg void OnBnClickedDraw3();
	void updatasta();
	long m_print_x;
	long m_print_y;
	long m_print_z;
	long m_camerax;
	long m_cameray;
	afx_msg void OnBnClickedGetdayinpos();
	afx_msg void OnBnClickedGetdayinpos2();
	afx_msg void OnBnClickedGetdayinpos3();
	long m_real_x;
	long m_real_y;
	long m_real_z;
	afx_msg void OnCbnSelchangeCombochose();
	afx_msg void OnBnClickedCreatmodel();
	afx_msg void OnBnClickedIssaveimg();
	double m_camer0_x;
	double m_camer0_y;
	double m_camera1_x;
	afx_msg void OnEnChangeMypixe1();
	double m_camera1_y;
	afx_msg void OnBnClickedGoxzpos();
	afx_msg void OnBnClickedCalcxy0();
	afx_msg void OnBnClickedMesaure2();
};
