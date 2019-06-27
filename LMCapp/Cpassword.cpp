// Cpassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LMCapp.h"
#include "Cpassword.h"
#include "afxdialogex.h"


// Cpassword �Ի���

IMPLEMENT_DYNAMIC(Cpassword, CDialogEx)

Cpassword::Cpassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cpassword::IDD, pParent)
	, m_password(_T(""))
{

}

Cpassword::~Cpassword()
{
}

void Cpassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PASS, m_password);
}


BEGIN_MESSAGE_MAP(Cpassword, CDialogEx)
	ON_BN_CLICKED(IDOK2, &Cpassword::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, &Cpassword::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Cpassword ��Ϣ�������


void Cpassword::OnBnClickedOk2()
{
	CDialogEx::OnCancel();
}


void Cpassword::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


HBRUSH Cpassword::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	pDC->SetBkMode(TRANSPARENT);
	return theApp.m_brush;//hbr;
}
