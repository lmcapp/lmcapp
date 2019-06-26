// Cpassword.cpp : 实现文件
//

#include "stdafx.h"
#include "LMCapp.h"
#include "Cpassword.h"
#include "afxdialogex.h"


// Cpassword 对话框

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


// Cpassword 消息处理程序


void Cpassword::OnBnClickedOk2()
{
	CDialogEx::OnCancel();
}


void Cpassword::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


HBRUSH Cpassword::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	pDC->SetBkMode(TRANSPARENT);
	return theApp.m_brush;//hbr;
}
