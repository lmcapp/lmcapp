#pragma once


// Cpassword �Ի���

class Cpassword : public CDialogEx
{
	DECLARE_DYNAMIC(Cpassword)

public:
	Cpassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cpassword();

// �Ի�������
	enum { IDD = IDD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
