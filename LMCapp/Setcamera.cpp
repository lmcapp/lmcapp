// Setcamera.cpp : 实现文件
//

#include "stdafx.h"
#include "LMCapp.h"
#include "Setcamera.h"
#include "afxdialogex.h"
#include "Cam.h"
#include "SoftPLC.h"
// CSetcamera 对话框

IMPLEMENT_DYNAMIC(CSetcamera, CDialogEx)

CSetcamera::CSetcamera(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetcamera::IDD, pParent)
	, m_gain0(0)
	, m_shutter0(31)
	, m_gain1(0)
	, m_shutter1(31)
	, m_width0(0)
	, m_width1(0)
	, m_height0(0)
	, m_height1(0)
	, m_area0(0)
	, m_area1(0)
	, m_ra0(0)
	, m_ra1(0)
	, m_rb0(0)
	, m_rb1(0)
	, m_radius(0.0)
	, m_angle(0)
	, m_row0(0)
	, m_row1(0)
	, m_row2(0)
	, m_row3(0)
	, m_column0(0)
	, m_column1(0)
	, m_column2(0)
	, m_column3(0)
	, m_radius0(0)
	, m_radius1(0)
	, m_radius2(0)
	, m_radius3(0)
	, m_thresd0(0)
	, m_thresd1(0)
	, m_thresd2(0)
	, m_thresd3(0)
	, m_print_x(0)
	, m_print_y(0)
	, m_print_z(0)
	, m_camerax(0)
	, m_cameray(0)
	, m_real_x(0)
	, m_real_y(0)
	, m_real_z(0)
	, m_camer0_x(0)
	, m_camer0_y(0)
	, m_camera1_x(0)
	, m_camera1_y(0)
{

}

CSetcamera::~CSetcamera()
{
}

void CSetcamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAIN, m_gain0);
	DDV_MinMaxInt(pDX, m_gain0, 0, 20);
	DDX_Text(pDX, IDC_SHUT, m_shutter0);
	DDV_MinMaxInt(pDX, m_shutter0, 31, 1000000);
	DDX_Text(pDX, IDC_GAIN2, m_gain1);
	DDX_Text(pDX, IDC_SHUT2, m_shutter1);
	DDX_Text(pDX, IDC_WIDTH0, m_width0);
	DDX_Text(pDX, IDC_WIDTH1, m_width1);
	DDX_Text(pDX, IDC_HEIGHT0, m_height0);
	DDX_Text(pDX, IDC_HEIGHT1, m_height1);
	DDX_Text(pDX, IDC_AREA0, m_area0);
	DDX_Text(pDX, IDC_AREA1, m_area1);
	DDX_Text(pDX, IDC_RA0, m_ra0);
	DDX_Text(pDX, IDC_RA1, m_ra1);
	DDX_Text(pDX, IDC_RB0, m_rb0);
	DDX_Text(pDX, IDC_RB1, m_rb1);
	DDX_Text(pDX, IDC_RADIUS, m_radius);
	DDX_Text(pDX, IDC_MANGLE0, m_angle);
	DDV_MinMaxInt(pDX, m_shutter1, 31, 1000000);
	DDX_Text(pDX, IDC_EDITROW0, m_row0);
	DDX_Text(pDX, IDC_EDITROW1, m_row1);
	DDX_Text(pDX, IDC_EDITROW2, m_row2);
	DDX_Text(pDX, IDC_EDITROW3, m_row3);
	DDX_Text(pDX, IDC_EDITCOLUMN0, m_column0);
	DDX_Text(pDX, IDC_EDITCOLUMN1, m_column1);
	DDX_Text(pDX, IDC_EDITCOLUMN2, m_column2);
	DDX_Text(pDX, IDC_EDITCOLUMN3, m_column3);
	DDX_Text(pDX, IDC_EDITCIRCLE0, m_radius0);
	DDX_Text(pDX, IDC_EDITCIRCLE1, m_radius1);
	DDX_Text(pDX, IDC_EDITCIRCLE2, m_radius2);
	DDX_Text(pDX, IDC_EDITCIRCLE3, m_radius3);
	DDX_Text(pDX, IDC_EDITTHRE0, m_thresd0);
	DDX_Text(pDX, IDC_EDITTHRE1, m_thresd1);
	DDX_Text(pDX, IDC_EDITTHRE2, m_thresd2);
	DDX_Text(pDX, IDC_EDITTHRE3, m_thresd3);
	DDX_Text(pDX, IDC_PRINTXPOS, m_print_x);
	DDX_Text(pDX, IDC_PRINTYPOS, m_print_y);
	DDX_Text(pDX, IDC_PRINTZPOS2, m_print_z);
	DDX_Text(pDX, IDC_PRINTXPOS2, m_camerax);
	DDX_Text(pDX, IDC_PRINTYPOS2, m_cameray);
	DDX_Text(pDX, IDC_PRINTXPOS3, m_real_x);
	DDX_Text(pDX, IDC_PRINTYPOS3, m_real_y);
	DDX_Text(pDX, IDC_PRINTZPOS3, m_real_z);
	DDX_Text(pDX, IDC_MXPIXE0, m_camer0_x);
	DDX_Text(pDX, IDC_MYPIXE0, m_camer0_y);
	DDX_Text(pDX, IDC_MXPIXE1, m_camera1_x);
	DDX_Text(pDX, IDC_MYPIXE1, m_camera1_y);
}


BEGIN_MESSAGE_MAP(CSetcamera, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGE, &CSetcamera::OnBnClickedChange)
	ON_BN_CLICKED(IDOK, &CSetcamera::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_GRABONCE0, &CSetcamera::OnBnClickedGrabonce0)
	ON_BN_CLICKED(IDC_GRABONCE1, &CSetcamera::OnBnClickedGrabonce1)
	ON_BN_CLICKED(IDC_CONGRB0, &CSetcamera::OnBnClickedCongrb0)
	ON_BN_CLICKED(IDC_CONGRB1, &CSetcamera::OnBnClickedCongrb1)
	ON_BN_CLICKED(IDC_OPENLED0, &CSetcamera::OnBnClickedOpenled0)
	ON_BN_CLICKED(IDC_OPENLED1, &CSetcamera::OnBnClickedOpenled1)
	ON_BN_CLICKED(IDC_MESAURE0, &CSetcamera::OnBnClickedMesaure0)
	ON_BN_CLICKED(IDC_SAVEIMG0, &CSetcamera::OnBnClickedSaveimg0)
	ON_BN_CLICKED(IDC_SAVEIMG1, &CSetcamera::OnBnClickedSaveimg1)
	ON_BN_CLICKED(IDC_CHANGEANGLE0, &CSetcamera::OnBnClickedChangeangle0)
	ON_BN_CLICKED(IDC_CHANGEANGLE2, &CSetcamera::OnBnClickedChangeangle2)
	ON_BN_CLICKED(IDC_DISPCIRCLE, &CSetcamera::OnBnClickedDispcircle)
	ON_BN_CLICKED(IDC_DRAW0, &CSetcamera::OnBnClickedDraw0)
	ON_BN_CLICKED(IDC_DRAW1, &CSetcamera::OnBnClickedDraw1)
	ON_BN_CLICKED(IDC_DRAW2, &CSetcamera::OnBnClickedDraw2)
	ON_BN_CLICKED(IDC_DRAW3, &CSetcamera::OnBnClickedDraw3)
	ON_BN_CLICKED(IDC_GETDAYINPOS, &CSetcamera::OnBnClickedGetdayinpos)
	ON_BN_CLICKED(IDC_GETDAYINPOS2, &CSetcamera::OnBnClickedGetdayinpos2)
	ON_BN_CLICKED(IDC_GETDAYINPOS3, &CSetcamera::OnBnClickedGetdayinpos3)
	ON_CBN_SELCHANGE(IDC_COMBOCHOSE, &CSetcamera::OnCbnSelchangeCombochose)
	ON_BN_CLICKED(IDC_CREATMODEL, &CSetcamera::OnBnClickedCreatmodel)
	ON_BN_CLICKED(IDC_ISSAVEIMG, &CSetcamera::OnBnClickedIssaveimg)
	ON_EN_CHANGE(IDC_MYPIXE1, &CSetcamera::OnEnChangeMypixe1)
	ON_BN_CLICKED(IDC_GOXZPOS, &CSetcamera::OnBnClickedGoxzpos)
	ON_BN_CLICKED(IDC_CALCXY0, &CSetcamera::OnBnClickedCalcxy0)
	ON_BN_CLICKED(IDC_MESAURE2, &CSetcamera::OnBnClickedMesaure2)
END_MESSAGE_MAP()


// CSetcamera 消息处理程序


void CSetcamera::OnBnClickedChange()
{
	UpdateData(TRUE);
	m_Cam.shuttertime[0] =m_shutter0;
	m_Cam.gain[0] =m_gain0;
	m_Cam.shuttertime[1] =m_shutter1;
	m_Cam.gain[1] =m_gain1;
	UpdateData(FALSE);
	m_Cam.Setcamera(0);
	m_Cam.Setcamera(1);
	m_Cam.saveini();
}


BOOL CSetcamera::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Cam.readini();
	CComboBox* m_tn = (CComboBox*)GetDlgItem(IDC_COMBOCHOSE);
	m_tn->AddString(_T("1道载台A"));
	m_tn->AddString(_T("1道载台B"));
	m_tn->AddString(_T("2道载台A"));
	m_tn->AddString(_T("2道载台B"));
	m_tn->SetCurSel(0);
	int comindex = m_tn->GetCurSel();
	UpdateData(TRUE);
	m_shutter0 =m_Cam.shuttertime[0] ;
	m_gain0 =m_Cam.gain[0];
	m_shutter1 =m_Cam.shuttertime[1] ;
    m_gain1 = 	m_Cam.gain[1];
	m_width0 = m_Cam.celiang_width[0];
	m_width1 = m_Cam.celiang_width[1];
	
	m_height0 = m_Cam.celiang_height[0];
	m_height1 = m_Cam.celiang_height[1];

	m_area0 = m_Cam.area[0];
	m_area1 = m_Cam.area[1];

	m_ra0 = m_Cam.ra[0];
	m_ra1 = m_Cam.ra[1];
	m_rb0 = m_Cam.rb[0];
	m_rb1 = m_Cam.rb[1];
	m_radius = m_Cam.radius;

	m_row0 = m_Cam.sunny_row[0];
	m_row1 = m_Cam.sunny_row[1];
	m_row2 = m_Cam.sunny_row[2];
	m_row3 = m_Cam.sunny_row[3];

	m_column0 = m_Cam.sunny_column[0];
	m_column1 = m_Cam.sunny_column[1];
	m_column2 = m_Cam.sunny_column[2];
	m_column3 = m_Cam.sunny_column[3];

	m_radius0 = m_Cam.sunny_radius[0];
	m_radius1 = m_Cam.sunny_radius[1];
	m_radius2 = m_Cam.sunny_radius[2];
	m_radius3 = m_Cam.sunny_radius[3];

	m_thresd0 = m_Cam.sunny_thresd[0];
	m_thresd1 = m_Cam.sunny_thresd[1];
	m_thresd2 = m_Cam.sunny_thresd[2];
	m_thresd3 = m_Cam.sunny_thresd[3];
	m_real_x = m_Cam.print_camerax[comindex];
	m_real_y = m_Cam.print_cameray[comindex];
	m_real_z = m_Cam.print_cameraz[comindex];

	m_camer0_x = m_Cam.calc0_x;
	m_camer0_y = m_Cam.calc0_y;
	m_camera1_x = m_Cam.calc1_x;
	m_camera1_y = m_Cam.calc1_y;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetcamera::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_Cam.celiang_width[0]=m_width0;
	m_Cam.celiang_width[1]=m_width1;

	m_Cam.celiang_height[0]=m_height0;
	m_Cam.celiang_height[1]=m_height1;

	m_Cam.area[0]=m_area0;
	m_Cam.area[1]=m_area1;

	m_Cam.ra[0]=m_ra0;
	m_Cam.ra[1]=m_ra1;
	m_Cam.rb[0]=m_rb0;
	m_Cam.rb[1]=m_rb1;
	m_Cam.radius =m_radius;

	m_Cam.sunny_row[0]=m_row0;
	m_Cam.sunny_row[1]=m_row1;
	m_Cam.sunny_row[2]=m_row2;
	m_Cam.sunny_row[3]=m_row3;

	m_Cam.sunny_column[0]=m_column0;
	m_Cam.sunny_column[1]=m_column1;
	m_Cam.sunny_column[2]=m_column2;
	m_Cam.sunny_column[3]=m_column3;

	m_Cam.sunny_radius[0]=m_radius0;
	m_Cam.sunny_radius[1]=m_radius1;
	m_Cam.sunny_radius[2]=m_radius2;
	m_Cam.sunny_radius[3]=m_radius3;

	m_Cam.sunny_thresd[0]=m_thresd0;
	m_Cam.sunny_thresd[1]=m_thresd1;
	m_Cam.sunny_thresd[2]=m_thresd2;
	m_Cam.sunny_thresd[3]=m_thresd3;

	m_Cam.calc0_x=m_camer0_x;
	m_Cam.calc0_y=m_camer0_y;
	m_Cam.calc1_x=m_camera1_x;
	m_Cam.calc1_y=m_camera1_y;

	m_Cam.saveini();
}


HBRUSH CSetcamera::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	pDC->SetBkMode(TRANSPARENT);
	return theApp.m_brush;//hbr;
}
void CSetcamera::OnContextMenu(CWnd* pWnd, CPoint pos)
{

}

void CSetcamera::OnBnClickedGrabonce0()
{
	m_Cam.OnSendSoftCommand(0);
}


void CSetcamera::OnBnClickedGrabonce1()
{
	m_Cam.OnSendSoftCommand(1);
}


void CSetcamera::OnBnClickedCongrb0()
{
	CButton *m_btn=(CButton*)GetDlgItem(IDC_CONGRB0);
	CString str;
	m_btn->GetWindowTextW(str);
	if (str == _T("连续拍照"))
	{
		m_Cam.OnCONSnap(0);
		m_btn->SetWindowTextW(_T("停止拍照"));
	}
	else
	{
		m_Cam.OnStopCONSnap(0);
		m_btn->SetWindowTextW(_T("连续拍照"));
	}
}


void CSetcamera::OnBnClickedCongrb1()
{
	CButton *m_btn=(CButton*)GetDlgItem(IDC_CONGRB1);
	CString str;
	m_btn->GetWindowTextW(str);
	if (str == _T("连续拍照"))
	{
		m_Cam.OnCONSnap(1);
		m_btn->SetWindowTextW(_T("停止拍照"));
	}
	else
	{
		m_Cam.OnStopCONSnap(1);
		m_btn->SetWindowTextW(_T("连续拍照"));
	}
}


void CSetcamera::OnBnClickedOpenled0()
{
	//打开LED1
}


void CSetcamera::OnBnClickedOpenled1()
{
	// 打开LED2
}


void CSetcamera::OnBnClickedMesaure0()
{
   //m_Cam.sunny_measure();
   //m_Cam.sunny_find_model(0);
   m_Cam.czrs_measure();
}


void CSetcamera::OnBnClickedSaveimg0()
{
	CStringA s,str1;
	SYSTEMTIME    sysTime;
	GetLocalTime(&sysTime);
	str1.Format(("%d_%d_%d_%d_%d_%d_%d_0.bmp"),
		sysTime.wYear,
		sysTime.wMonth,
		sysTime.wDay,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		sysTime.wMilliseconds);
	s=("d:/images/")+str1;
	write_image (m_Cam.Image[0], "bmp", 0,s.GetBuffer());
}


void CSetcamera::OnBnClickedSaveimg1()
{
	CStringA s,str1;
	SYSTEMTIME    sysTime;
	GetLocalTime(&sysTime);
	str1.Format(("%d_%d_%d_%d_%d_%d_%d_1.bmp"),
		sysTime.wYear,
		sysTime.wMonth,
		sysTime.wDay,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		sysTime.wMilliseconds);
	s=("d:/images/")+str1;
	write_image (m_Cam.Image[1], "bmp", 0,s.GetBuffer());
}


void CSetcamera::OnBnClickedChangeangle0()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
	float angle0 = m_math.ang(m_angle);
	long x1,x2,y;
	m_math.get_x0_x1_x2_POS(0,angle0,x1,x2,y);	
	m_Motor.mul_real_move(4,x1,5,x2,6,y);
}


void CSetcamera::OnBnClickedChangeangle2()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
	float angle0 = m_math.ang(m_angle);
	long x1,x2,y;
	m_math.get_x0_x1_x2_POS(1,angle0,x1,x2,y);
	m_Motor.mul_real_move(8,x1,9,x2,10,y);
}

void CSetcamera::updatasta()
{
	UpdateData(TRUE);
	m_shutter0 =m_Cam.shuttertime[0] ;
	m_gain0 =m_Cam.gain[0];
	m_shutter1 =m_Cam.shuttertime[1] ;
	m_gain1 = 	m_Cam.gain[1];
	m_width0 = m_Cam.celiang_width[0];
	m_width1 = m_Cam.celiang_width[1];

	m_height0 = m_Cam.celiang_height[0];
	m_height1 = m_Cam.celiang_height[1];

	m_area0 = m_Cam.area[0];
	m_area1 = m_Cam.area[1];

	m_ra0 = m_Cam.ra[0];
	m_ra1 = m_Cam.ra[1];
	m_rb0 = m_Cam.rb[0];
	m_rb1 = m_Cam.rb[1];
	m_radius = m_Cam.radius;

	m_row0 = m_Cam.sunny_row[0];
	m_row1 = m_Cam.sunny_row[1];
	m_row2 = m_Cam.sunny_row[2];
	m_row3 = m_Cam.sunny_row[3];

	m_column0 = m_Cam.sunny_column[0];
	m_column1 = m_Cam.sunny_column[1];
	m_column2 = m_Cam.sunny_column[2];
	m_column3 = m_Cam.sunny_column[3];

	m_radius0 = m_Cam.sunny_radius[0];
	m_radius1 = m_Cam.sunny_radius[1];
	m_radius2 = m_Cam.sunny_radius[2];
	m_radius3 = m_Cam.sunny_radius[3];

	m_thresd0 = m_Cam.sunny_thresd[0];
	m_thresd1 = m_Cam.sunny_thresd[1];
	m_thresd2 = m_Cam.sunny_thresd[2];
	m_thresd3 = m_Cam.sunny_thresd[3];

	UpdateData(FALSE);
}

void CSetcamera::OnBnClickedDispcircle()
{
	m_Cam.m_disp_circle();
}


void CSetcamera::OnBnClickedDraw0()
{
	m_Cam.m_draw_roi(0);
	updatasta();
	m_Cam.saveini();
}


void CSetcamera::OnBnClickedDraw1()
{
	m_Cam.m_draw_roi(1);
	updatasta();
	m_Cam.saveini();
}


void CSetcamera::OnBnClickedDraw2()
{
	m_Cam.m_draw_roi(2);
	updatasta();
	m_Cam.saveini();
}


void CSetcamera::OnBnClickedDraw3()
{
	m_Cam.m_draw_roi(3);
	updatasta();
	m_Cam.saveini();
}


void CSetcamera::OnBnClickedGetdayinpos()
{
	CComboBox* m_tn = (CComboBox*)GetDlgItem(IDC_COMBOCHOSE);
	int comindex = m_tn->GetCurSel();
	UpdateData(TRUE);
	switch(comindex)
	{
	case 0:
		APS_get_position(MOTOR11,&m_print_x);
		APS_get_position(MOTOR12,&m_print_z);
		APS_get_position(MOTOR14,&m_print_y);
		break;
	case 1:
		APS_get_position(MOTOR11,&m_print_x);
		APS_get_position(MOTOR12,&m_print_z);
		APS_get_position(MOTOR15,&m_print_y);
		break;
	case 2:
		break;
	case 3:
		break;
	}

	UpdateData(FALSE);
}


void CSetcamera::OnBnClickedGetdayinpos2()
{
	//UpdateData(TRUE);
	////APS_get_position(MOTOR11,&m_camerax);
	////APS_get_position(MOTOR12,&m_print_z);
	//APS_get_position(MOTOR15,&m_cameray);
	//UpdateData(FALSE);

	CComboBox* m_tn = (CComboBox*)GetDlgItem(IDC_COMBOCHOSE);
	int comindex = m_tn->GetCurSel();
	UpdateData(TRUE);
	double row,column;
	switch(comindex)
	{
	case 0:
		APS_get_position(MOTOR14,&m_cameray);
		APS_get_position(MOTOR11,&m_camerax);
		m_Cam.get_button_pos(m_Cam.WindowHandle[0],row,column,_T("点击图形的右下角！"));
		m_camerax = m_camerax+row*m_Cam.calc0_x*1000;
		m_cameray = m_cameray-column*m_Cam.calc0_y*2000;//0.5um
		break;
	case 1:
		APS_get_position(MOTOR15,&m_cameray);
		APS_get_position(MOTOR11,&m_camerax);
		m_Cam.get_button_pos(m_Cam.WindowHandle[0],row,column,_T("点击图形的右下角！"));
		m_camerax = m_camerax+row*m_Cam.calc0_x*1000;
		m_cameray = m_cameray-column*m_Cam.calc0_y*2000;//0.5um
		break;
	case 2:
		break;
	case 3:
		break;
	}

	UpdateData(FALSE);
}


void CSetcamera::OnBnClickedGetdayinpos3()
{

	Cpassword dlg;

	if (IDOK ==dlg.DoModal() )
	{
		if (dlg.m_password ==_T("8888"))
		{

		}
		else
		{
			MessageBox(_T("密码错误！"),_T(""),MB_ICONERROR);
			return;
		}
	}
	else
	{
		MessageBox(_T("密码错误！"),_T(""),MB_ICONERROR);
		return;
	}

	CComboBox* m_tn = (CComboBox*)GetDlgItem(IDC_COMBOCHOSE);
	int comindex = m_tn->GetCurSel();
	if ( m_print_y==0||m_cameray ==0)
	{
		m_Cam.print_cameraz[comindex] = m_print_z;
	}
	else
	{
		m_Cam.print_cameray[comindex] = m_print_y-m_cameray;
		m_Cam.print_camerax[comindex] = m_camerax;
		m_Cam.print_cameraz[comindex] = m_print_z; 
	}
	UpdateData(TRUE);
    m_real_x = m_Cam.print_camerax[comindex];
	m_real_y = m_Cam.print_cameray[comindex];
	m_real_z = m_Cam.print_cameraz[comindex];
	UpdateData(FALSE);
	m_Cam.saveini();
}


void CSetcamera::OnCbnSelchangeCombochose()
{
	CComboBox* m_tn = (CComboBox*)GetDlgItem(IDC_COMBOCHOSE);
	int comindex = m_tn->GetCurSel();
	UpdateData(TRUE);
	m_real_x = m_Cam.print_camerax[comindex];
	m_real_y = m_Cam.print_cameray[comindex];
	m_real_z = m_Cam.print_cameraz[comindex];
	UpdateData(FALSE);
}


void CSetcamera::OnBnClickedCreatmodel()
{
	m_Cam.creat_model(0);
}


void CSetcamera::OnBnClickedIssaveimg()
{
	CButton *m_btn = (CButton*)GetDlgItem(IDC_ISSAVEIMG);
	int a = m_btn->GetCheck();
	m_Cam.is_save_img = a;
}


void CSetcamera::OnEnChangeMypixe1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSetcamera::OnBnClickedGoxzpos()
{

	CComboBox* m_tn = (CComboBox*)GetDlgItem(IDC_COMBOCHOSE);
	int comindex = m_tn->GetCurSel();
	m_Motor.absolute_move(MOTOR11,m_Cam.print_camerax[comindex]);
	m_Motor.absolute_move(MOTOR12,m_Cam.print_cameraz[0]);
	m_Motor.wait_move_done(MOTOR11);
	m_Motor.wait_move_done(MOTOR12);
}


void CSetcamera::OnBnClickedCalcxy0()
{
	double row[4],column[4];
	m_Cam.get_button_pos(m_Cam.WindowHandle[0],row[0],column[0],_T("下边缘左侧！！"));
	m_Cam.get_button_pos(m_Cam.WindowHandle[0],row[1],column[1],_T("下边缘右侧！！"));
	m_Cam.get_button_pos(m_Cam.WindowHandle[0],row[2],column[2],_T("右边缘上侧！！"));
	m_Cam.get_button_pos(m_Cam.WindowHandle[0],row[3],column[3],_T("右边缘下侧！！"));
	m_Cam.sunny_center_row = (row[0]+row[1])/2;
	m_Cam.sunny_center_column = (column[2]+column[3])/2;
	m_Cam.calc_print_camerax[1] = m_Cam.print_camerax[1]-(m_Cam.sunny_center_row)*m_Cam.calc0_x*1000;
	m_Cam.calc_print_cameray[1] = m_Cam.print_cameray[1]-(m_Cam.sunny_center_column)*m_Cam.calc0_y*2000;
}


void CSetcamera::OnBnClickedMesaure2()
{
	m_Cam.sunny_measure();
	//m_Cam.sunny_find_model(0);
	//m_Cam.czrs_measure();
}
