#pragma once


// Cpassword 对话框

class Cpassword : public CDialogEx
{
	DECLARE_DYNAMIC(Cpassword)

public:
	Cpassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cpassword();

// 对话框数据
	enum { IDD = IDD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
