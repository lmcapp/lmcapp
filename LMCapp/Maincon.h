#pragma once
#include "Cmath.h"
#include "SoftPLC.h"
#include "M-880Dlg.h"
// CMaincon 对话框
#include "XDMcontrol.h"
class CMaincon : public CDialogEx
{
	DECLARE_DYNAMIC(CMaincon)

public:
	CMaincon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMaincon();
	CM880Dlg m_print;
// 对话框数据
	enum { IDD = IDD_MAINCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	static UINT auto_run_shangliao(LPVOID param);
	static UINT auto_get_camera_print(LPVOID param);
	static UINT auto_go_home(LPVOID param);
	static UINT auto_xialiao(LPVOID param);

	//----优化逻辑
	static UINT auto_run_1A(LPVOID param);
	static UINT auto_run_1B(LPVOID param);
	//----------CE SHI 
	static UINT CESHI(LPVOID param);
	//static UINT auto_calc_camera(LPVOID param);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartshangliao();
	afx_msg void OnBnClickedCheckout8();
	afx_msg void OnBnClickedCheckout9();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedResetalarm();
	afx_msg void OnBnClickedStartprint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	long m_paibian0;
	long m_paibian1;
	long m_dengliao0;
	long m_dengliao1;
	long m_quliao0;
	long m_quliao1;
	long m_dingsheng0;
	long m_dingsheng1;
	long m_paizhao0;
	long m_paizhao1;
	long m_dayin0;
	long m_dayin1;
	long m_fangliao0;
	long m_fangliao1;
	void updatapos();
	afx_msg void OnBnClickedReadpaibianpos0();
	afx_msg void OnBnClickedReadpaibianpos1();
	afx_msg void OnBnClickedReaddengliaopos0();
	afx_msg void OnBnClickedReaddengliaopos1();
	afx_msg void OnBnClickedReadquliaopos0();
	afx_msg void OnBnClickedReadquliaopos1();
	afx_msg void OnBnClickedReaddingshengpos0();
	afx_msg void OnBnClickedReaddingshengpos1();
	afx_msg void OnBnClickedReadgrbgpos0();
	afx_msg void OnBnClickedReadgrbgpos1();
	afx_msg void OnBnClickedReadprintpos0();
	afx_msg void OnBnClickedReadprintpos1();
	afx_msg void OnBnClickedReadputpos0();
	afx_msg void OnBnClickedReadputpos1();
	afx_msg void OnBnClickedCheckout10();
	afx_msg void OnBnClickedCheckout11();
	afx_msg void OnBnClickedCheckout12();
	afx_msg void OnBnClickedCheckout13();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedAllgohome();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedChangepos();
	void enablebutton(bool ret);
	afx_msg void OnBnClickedChangepos2();
	afx_msg void OnBnClickedReadputdingsheng1();
	long m_printok0;
	long m_printok1;
	long m_putdingshneg0;
	long m_putdingsheng1;
	afx_msg void OnBnClickedReadprintok0();
	afx_msg void OnBnClickedReadprintok1();
	afx_msg void OnBnClickedReadputdingsheng0();
	afx_msg void OnBnClickedCheckout14();
	afx_msg void OnBnClickedStartxialiao();
	afx_msg void OnBnClickedStartxialiao2();
	int xxy_move(int id);
	bool use1dao;
	bool use2dao;
	bool use1daoA;
	bool use1daoB;
	bool use2daoA;
	bool use2daoB;
	afx_msg void OnBnClickedCheckuse1dao();
	afx_msg void OnBnClickedCheckuse2dao();
	bool go_homeOK;
	void con_enablebutton(bool ret);
	afx_msg void OnBnClickedGopaibianpos0();
	afx_msg void OnBnClickedGopaibianpos1();
	afx_msg void OnBnClickedGodengliaopos20();
	afx_msg void OnBnClickedGodengliaopos21();
	afx_msg void OnBnClickedGoquliaopos0();
	afx_msg void OnBnClickedGoquliaopos1();
	afx_msg void OnBnClickedGodingshengpos0();
	afx_msg void OnBnClickedGodingshengpos1();
	afx_msg void OnBnClickedGogrbgpos0();
	afx_msg void OnBnClickedGogrbgpos1();
	afx_msg void OnBnClickedGoprintpos0();
	afx_msg void OnBnClickedGoprintpos1();
	afx_msg void OnBnClickedGoputpos0();
	afx_msg void OnBnClickedGoputpos1();
	afx_msg void OnBnClickedGoprintok0();
	afx_msg void OnBnClickedGoprintok1();
	afx_msg void OnBnClickedGoputdingsheng0();
	afx_msg void OnBnClickedGoputdingsheng1();
	afx_msg void OnBnClickedCheck1a();
	afx_msg void OnBnClickedCheck1b();
	afx_msg void OnBnClickedCheck2a();
	afx_msg void OnBnClickedCheck2b();
	afx_msg void OnBnClickedCheckout15();
	afx_msg void OnBnClickedCheckout16();
	afx_msg void OnBnClickedBoli();
	afx_msg void OnBnClickedGuipian();
	bool isprint_boli;
	float m_headtemp0;
	float m_headtemp1;
	float m_headtemp2;
	float m_headtempx;
	afx_msg void OnBnClickedChangepos3();
};
