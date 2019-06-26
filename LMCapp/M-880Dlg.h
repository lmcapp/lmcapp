
// M-880Dlg.h : 头文件
//

#pragma once
#include "XDMcontrol.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "Cam.h"
// CM880Dlg 对话框
class CM880Dlg : public CDialog
{
// 构造
public:
	CM880Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_M880_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//CMotordlg *M_DLG;
	afx_msg void OnBnClickedInit();
	int m_hibnum;
	int m_nFirstpbCol;
	int m_nfirstHdCol;
	int m_nlastHdCol;
	float m_readresTemp;
	float m_readLeftJsTemp;
	float m_readRightJsTemp;
	float m_setResTemp;
	float m_setLeftJsTemp;
	float m_setRightJsTemp;
	CString m_wavefile;
	float m_changeVol;
	afx_msg void OnBnClickedAddtoprintbar();
	CComboBox m_HibCombo;
	int m_HDnumOnbar;
	afx_msg void OnBnClickedConfigprintbar();
	float m_auto_fire_frez;
	UINT m_ydpi;
	float m_encodes_perin;
	CComboBox m_dottype;
	afx_msg void OnBnClickedSetdot();
	afx_msg void OnBnClickedGettemp();
	afx_msg void OnBnClickedSettemp();
	CString m_imageFile;
	int m_repeatTimes;
	int m_pageLen;
	afx_msg void OnBnClickedFindfile();
	afx_msg void OnBnClickedSetvol();
	afx_msg void OnBnClickedSetwavefile();
	afx_msg void OnBnClickedGetimgpath();
	afx_msg void OnBnClickedStartprint();
	afx_msg void OnBnClickedAutofirecheck();
	int m_startydelayjet;
	int m_stopydelayjet;
	UINT m_delaypiexs;
	afx_msg void OnBnClickedSetydelay();
	int m_inklevle1;
	int m_inklevle2;
	int m_inklevle3;
	int m_inklevle4;
	int m_inkpressure1;
	int m_inkpressure2;
	afx_msg void OnBnClickedGetinklevel();
	afx_msg void OnBnClickedGetpressure();
	afx_msg void OnBnClickedSavewaefile();
	CComboBox m_wave_combo;
	afx_msg void OnBnClickedSettemp2();
	afx_msg void OnBnClickedGetsize();
	afx_msg void OnBnClickedGetsize2();
	int m_enpos;
	afx_msg void OnBnClickedGetpos();
	int m_setpos;
	afx_msg void OnBnClickedSetpos2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOpenmotordlg();
	afx_msg void OnBnClickedSetdropsize();
	CListCtrl m_Wave_list;
	afx_msg void OnBnClickedGetinfo();
	afx_msg void OnBnClickedShowhcd();
	afx_msg void OnBnClickedOpencmd();
	afx_msg void OnBnClickedOpencmd2();
	static UINT Print_thread(LPVOID param);
	static UINT SCAN_Print_thread(LPVOID param);
	afx_msg void OnBnClickedStopprint();
	afx_msg void OnBnClickedPacktofile();
	UINT m_fire_count;
	int ink_levle[4];
	HBRUSH hbrush;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedGettemp2();
	afx_msg void OnBnClickedStartprint3();
	int image_width;
	int image_height;
	int m_xdpi;
	afx_msg void OnBnClickedSetdropsize2();
	afx_msg void OnBnClickedSetdropsize3();
	afx_msg void OnBnClickedStartprint4();
	bool dingwei;
	bool stopprint;
	afx_msg void OnBnClickedAutofirecheck2();
	afx_msg void OnBnClickedGetimgpath2();
	void auto_print();
	bool isprinting;
	void chaifen(int laststep_use_words);
	afx_msg void OnBnClickedGetimgpath3();
	int use_last_jet_numbers;
	afx_msg void OnBnClickedStartprint5();
	afx_msg void OnBnClickedGetimgpath4();
	afx_msg void OnBnClickedStartprint6();
	afx_msg void OnBnClickedUsehead1();
	afx_msg void OnBnClickedUsehead2();
	afx_msg void OnBnClickedUsehead3();
	afx_msg void OnCbnSelchangeHibcombo();
};
