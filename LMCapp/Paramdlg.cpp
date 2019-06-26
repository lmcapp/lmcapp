// Paramdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LMCapp.h"
#include "Paramdlg.h"
#include "afxdialogex.h"
#include "Cpassword.h"

// CParamdlg 对话框

IMPLEMENT_DYNAMIC(CParamdlg, CDialogEx)

CParamdlg::CParamdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParamdlg::IDD, pParent)
	, m_homespeed(0)
	, m_startspeed(0)
	, m_accspeed(0)
	, m_maxspeed(0)
	, m_jogspeed(0)
	, m_pos(0)
	,motor_index(0)
{

}

CParamdlg::~CParamdlg()
{
	
}

void CParamdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOMESPED, m_homespeed);
	DDX_Text(pDX, IDC_STARTSPED, m_startspeed);
	DDX_Text(pDX, IDC_ACCSPED, m_accspeed);
	DDX_Text(pDX, IDC_MAXSPED, m_maxspeed);
	DDX_Text(pDX, IDC_JOGSPED, m_jogspeed);
	DDX_Text(pDX, IDC_POS, m_pos);
	DDX_Control(pDX, IDC_MOTORTREE, m_Motortree);
}


BEGIN_MESSAGE_MAP(CParamdlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_HOME, &CParamdlg::OnBnClickedHome)
	ON_BN_CLICKED(IDC_MOSTOP, &CParamdlg::OnBnClickedMostop)
	ON_BN_CLICKED(IDC_MOVE, &CParamdlg::OnBnClickedMove)
	ON_BN_CLICKED(IDC_SAVE, &CParamdlg::OnBnClickedSave)
	ON_EN_KILLFOCUS(IDC_HOMESPED, &CParamdlg::OnEnKillfocusHomesped)
	ON_EN_KILLFOCUS(IDC_STARTSPED, &CParamdlg::OnEnKillfocusStartsped)
	ON_EN_KILLFOCUS(IDC_ACCSPED, &CParamdlg::OnEnKillfocusAccsped)
	ON_EN_KILLFOCUS(IDC_MAXSPED, &CParamdlg::OnEnKillfocusMaxsped)
	ON_EN_KILLFOCUS(IDC_JOGSPED, &CParamdlg::OnEnKillfocusJogsped)
	ON_BN_CLICKED(IDC_CAHANGE, &CParamdlg::OnBnClickedCahange)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MOTORTREE, &CParamdlg::OnSelchangedMotortree)
	ON_WM_CTLCOLOR()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_SVO, &CParamdlg::OnBnClickedSvo)
	ON_BN_CLICKED(IDC_SVO2, &CParamdlg::OnBnClickedSvo2)
END_MESSAGE_MAP()


// CParamdlg 消息处理程序


BOOL CParamdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();	
	/* 轴控件初始化*/
	Item = m_Motortree.InsertItem(_T("所有电机"));
	subitem[0] = m_Motortree.InsertItem(_T("通道1"),Item);
	subitem[1] = m_Motortree.InsertItem(_T("通道2"),Item);
	m_Motortree.Expand(Item,TVE_EXPAND);
	tree_str[0]= 		 _T("轴1---上料伺服电机");
	tree_str[1]=		 _T("轴2---拍边电缸1");
	tree_str[2]=		 _T("轴3---拍边电缸2");
	tree_str[3]=		 _T("轴4---顶升步进电机1");
	tree_str[4]=		 _T("轴5---旋转平台X0");
	tree_str[5]=		 _T("轴6---旋转平台X1");
	tree_str[6]=		 _T("轴7---旋转平台X2");
	tree_str[7]=		 _T("轴8---顶升步进电机2");
	tree_str[8]=		 _T("轴9---旋转平台X3");
	tree_str[9]=		 _T("轴10---旋转平台X4");
	tree_str[10]=		 _T("轴11---旋转平台X5");
	tree_str[11]=		 _T("轴12---喷头X伺服");
	tree_str[12]=		 _T("轴13---喷头Z伺服");
	tree_str[13]=		 _T("轴14---下料电机");
	tree_str[14]=		 _T("轴15---直线电机1");
	tree_str[15]=		 _T("轴16---直线电机2");
	tree_str[16]=		 _T("轴17---上料伺服电机");
	tree_str[17]=		 _T("轴18---拍边电缸1");
	tree_str[18]=		 _T("轴19---拍边电缸2");
	tree_str[19]=		 _T("轴20---顶升步进电机1");
	tree_str[20]=		 _T("轴21---旋转平台X0");
	tree_str[21]=		 _T("轴22---旋转平台X1");
	tree_str[22]=		 _T("轴23---旋转平台X2");
	tree_str[23]=		 _T("轴24---顶升步进电机2");
	tree_str[24]=		 _T("轴25---旋转平台X3");
	tree_str[25]=		 _T("轴26---旋转平台X4");
	tree_str[26]=		 _T("轴27---旋转平台X5");
	tree_str[27]=		 _T("轴28---喷头X伺服");
	tree_str[28]=		 _T("轴29---喷头Z伺服");
	tree_str[29]=		 _T("轴30---下料电机");
	tree_str[30]=		 _T("轴31---直线电机1");
	tree_str[31]=		 _T("轴32---直线电机2");
	for (int k = 0;k<32;k++)
	{
		if (k<16)
		{
		  motor_Item[k] = m_Motortree.InsertItem(tree_str[k],subitem[0]);
		}
		else
		{
		 motor_Item[k] = m_Motortree.InsertItem(tree_str[k],subitem[1]);
		}
	}
	m_Motortree.Expand(subitem[0],TVE_EXPAND);
	m_Motortree.Expand(subitem[1],TVE_EXPAND);
	m_Motortree.SetItemState(motor_Item[0], TVIS_SELECTED, TVIS_SELECTED);
	GetDlgItem(IDC_MOTORNAME)->SetWindowTextW(tree_str[0]);
	GetDlgItem(IDC_HOMESPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_STARTSPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_ACCSPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_MAXSPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_JOGSPED)->EnableWindow(FALSE);

	update_speed();
	SetTimer(0,100,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	
}
void CParamdlg::update_speed()
{
	UpdateData(true);
	m_homespeed =m_Motor.go_homespeed[motor_index];
	m_accspeed = m_Motor.acc_speed[motor_index];
	m_maxspeed = m_Motor.move_maxspeed[motor_index];
	m_startspeed = m_Motor.start_speed[motor_index];
	m_jogspeed = m_Motor.jog_speed[motor_index];
	UpdateData(FALSE);
	bool issvo,isalarm;
	if( ( ( APS_motion_io_status( motor_index ) >> MIO_SVON ) & 1 ) )  
	{
		issvo =true;
	}
	else
	{
		issvo =false;
		CButton *m_bt = (CButton*)GetDlgItem(IDC_SVO);
		m_bt->SetCheck(false);
	}
		


	//if( ( ( APS_motion_io_status( motor_index ) >> MIO_ALM ) & 1 ) )  
	//{
	//	isalarm =true;
	//}
	//else
	//	isalarm =false;
	//CButton *m_bt1 = (CButton*)GetDlgItem(IDC_SVO2);
	//m_bt1->SetCheck(isalarm);
}
void CParamdlg::update_status()
{
	int index = motor_index;
	/*
	0 ALM
	1 PEL 正向限位
	2 MEL 
	3 ORG
	*/
	I32 pos ;
	APS_get_position(index,&pos);
	I32  status = APS_motion_io_status(index);
	int pel  = status>>1&0x1;
	int mel = status >>2&0x1;
	int org = 0;
	if (index==14||index==15||index==30||index==31)
	{
		org = status>>MIO_EZ&0x1;
	}
	else
        org = status>>3&0x1;
	CString str;
	str.Format(_T("%d"),pos);
	CButton * btn = (CButton*)GetDlgItem(IDC_EDIT7);
	btn->SetWindowTextW(str);
	btn = (CButton*)GetDlgItem(IDC_PEL);
	btn->SetCheck(pel);
	btn = (CButton*)GetDlgItem(IDC_MEL);
	btn->SetCheck(mel);
	btn = (CButton*)GetDlgItem(IDC_ORG);
	btn->SetCheck(org);
}

void CParamdlg::OnTimer(UINT_PTR nIDEvent)
{	
	update_status();
	CDialogEx::OnTimer(nIDEvent);
}


void CParamdlg::OnClose()
{
	KillTimer(0);
	CDialogEx::OnClose();
}


BOOL CParamdlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_LBUTTONDOWN)
	{
		CButton* btn = (CButton*)GetDlgItem(IDC_JOG0);
		CButton* btn1 = (CButton*)GetDlgItem(IDC_JOG1);
		if (pMsg->hwnd==btn->m_hWnd)
		{
			m_Motor.JOG_ON(motor_index,0);
			btn->SetWindowTextW(_T("JOG..."));
		}
		if (pMsg->hwnd==btn1->m_hWnd)
		{
			m_Motor.JOG_ON(motor_index,1);
			btn1->SetWindowTextW(_T("JOG..."));
		}
	}
	if (pMsg->message==WM_LBUTTONUP)
	{
		CButton* btn = (CButton*)GetDlgItem(IDC_JOG0);
		CButton* btn1 = (CButton*)GetDlgItem(IDC_JOG1);
		if (pMsg->hwnd==btn->m_hWnd||pMsg->hwnd==btn1->m_hWnd)
		{
			m_Motor.JOG_OFF(motor_index);
			btn->SetWindowTextW(_T("JOG+"));
			btn1->SetWindowTextW(_T("JOG-"));
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CParamdlg::OnBnClickedHome()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_HOME);
	btn->EnableWindow(false);
	if (motor_index==11||motor_index==12||motor_index==14||motor_index==15
		||motor_index==27||motor_index==28||motor_index==30||motor_index==31||motor_index==3||motor_index==7||motor_index==19||motor_index==23)
	{	
		m_Motor.Go_home(motor_index);
	    m_Motor.wait_move_done(motor_index);
		m_Motor.reset_pos(motor_index);	
	}
	if (motor_index==4||motor_index==5||motor_index==6)
	{
		m_Motor.Go_home(4);
		m_Motor.Go_home(5);
		m_Motor.Go_home(6);
		m_Motor.wait_move_done(4);
		m_Motor.wait_move_done(5);
		m_Motor.wait_move_done(6);
		m_Motor.reset_pos(4);
		m_Motor.reset_pos(5);
		m_Motor.reset_pos(6);
		m_math.xxy_angle[0] = 0;
	}
	if (motor_index==8||motor_index==9||motor_index==10)
	{
		m_Motor.Go_home(8);
		m_Motor.Go_home(9);
		m_Motor.Go_home(10);
		m_Motor.wait_move_done(8);
		m_Motor.wait_move_done(9);
		m_Motor.wait_move_done(10);
		m_Motor.reset_pos(8);
		m_Motor.reset_pos(9);
		m_Motor.reset_pos(10);
		m_math.xxy_angle[1] = 0;
	}
	if (motor_index==20||motor_index==21||motor_index==22)
	{
		m_Motor.Go_home(20);
		Sleep(1000);
		m_Motor.Go_home(21);
		Sleep(1000);
		m_Motor.Go_home(22);
		m_Motor.wait_move_done(20);
		m_Motor.wait_move_done(21);
		m_Motor.wait_move_done(22);
		m_Motor.reset_pos(20);
		m_Motor.reset_pos(21);
		m_Motor.reset_pos(22);
		m_math.xxy_angle[2] = 0;
	}
	if (motor_index==24||motor_index==25||motor_index==26)
	{
		m_Motor.Go_home(24);
		m_Motor.Go_home(25);
		m_Motor.Go_home(26);
		m_Motor.wait_move_done(24);
		m_Motor.wait_move_done(25);
		m_Motor.wait_move_done(26);
		m_Motor.reset_pos(24);
		m_Motor.reset_pos(25);
		m_Motor.reset_pos(26);
		m_math.xxy_angle[3] = 0;
	}

	if(motor_index == 1)
	{
		m_Motor.WritePort(false,0,11,true);
        Sleep(2000);
		m_Motor.WritePort(false,0,11,false);
		if (!m_Motor.ReadPort(false,true,0,15))//判断输入点
		{
		  MessageBox(_T("电缸1回原点失败！"));
		  btn->EnableWindow(true);
		  return;
		}
		m_Motor.reset_pos(1);
		m_Motor.absolute_move(1,PAIBAINHOME0);
		m_Motor.wait_move_done(1);
	}
	if (motor_index==2)
	{
		m_Motor.WritePort(false,0,12,true);
       Sleep(2000);
		m_Motor.WritePort(false,0,12,false);
		if (!m_Motor.ReadPort(false,true,0,16))//判断输入点
		{
			MessageBox(_T("电缸2回原点失败！"));
			btn->EnableWindow(true);
			return;
		}
		m_Motor.reset_pos(2);
		m_Motor.absolute_move(2,PAIBAINHOME1);
		m_Motor.wait_move_done(2);
	}
	if (motor_index==17)
	{
		m_Motor.WritePort(false,2,11,true);
        Sleep(2000);
		m_Motor.WritePort(false,2,11,false);
		if (!m_Motor.ReadPort(false,true,2,15))//判断输入点
		{
			MessageBox(_T("电缸3回原点失败！"));
			btn->EnableWindow(true);
			return;
		}
		m_Motor.reset_pos(17);
		m_Motor.absolute_move(17,PAIBAINHOME2);
		m_Motor.wait_move_done(17);
	}
	if (motor_index==18)
	{
		m_Motor.WritePort(false,2,12,true);
        Sleep(2000);
		m_Motor.WritePort(false,2,12,false);
		if (!m_Motor.ReadPort(false,true,2,16))//判断输入点
		{
			MessageBox(_T("电缸4回原点失败！"));
			btn->EnableWindow(true);
			return;
		}
		m_Motor.reset_pos(18);
		m_Motor.absolute_move(18,PAIBAINHOME3);
		m_Motor.wait_move_done(18);
	}
	//else if (motor_index>=4&&motor_index<=6)
	//{
	//	m_Motor.velocity_move(motor_index,10000);
	//	m_Motor.wait_move_done(motor_index);
	//	m_Motor.Go_home(motor_index);
	//	m_Motor.wait_move_done(motor_index);
	//} 
	btn->EnableWindow(true);
}


void CParamdlg::OnBnClickedMostop()
{
	for (int k = 0;k<MOTOR_NUM;k++)
	{
		m_Motor.stop(k);
	}
}


void CParamdlg::OnBnClickedMove()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_MOVE);
	btn->EnableWindow(false);

	UpdateData(true);
	I32 pos = m_pos;
	m_Motor.relative_move(motor_index,pos);
	m_Motor.wait_move_done(motor_index);


	btn->EnableWindow(true);
}


void CParamdlg::OnBnClickedSave()
{
	UpdateData(TRUE);
	m_Motor.set_speed_param();
	m_Motor.savepos();
	UpdateData(FALSE);
	GetDlgItem(IDC_HOMESPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_STARTSPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_ACCSPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_MAXSPED)->EnableWindow(FALSE);
	GetDlgItem(IDC_JOGSPED)->EnableWindow(FALSE);
	//CDialogEx::OnOK();
}


void CParamdlg::OnEnKillfocusHomesped()
{
  UpdateData();
  m_Motor.go_homespeed[motor_index] = m_homespeed; 
}


void CParamdlg::OnEnKillfocusStartsped()
{
	UpdateData();
	m_Motor.start_speed[motor_index] = m_startspeed; 
}


void CParamdlg::OnEnKillfocusAccsped()
{
	UpdateData();
	  
	m_Motor.acc_speed[motor_index] = m_accspeed; 
}


void CParamdlg::OnEnKillfocusMaxsped()
{
	UpdateData();
	m_Motor.move_maxspeed[motor_index] = m_maxspeed; 
}


void CParamdlg::OnEnKillfocusJogsped()
{
	UpdateData();
	m_Motor.jog_speed[motor_index] = m_jogspeed; 
}


void CParamdlg::OnCbnSelchangeCombo1()
{
	update_speed();
}


void CParamdlg::OnBnClickedCahange()
{
	Cpassword dlg;

	if (IDOK ==dlg.DoModal() )
	{
		if (dlg.m_password ==_T("8888"))
		{
			GetDlgItem(IDC_HOMESPED)->EnableWindow(TRUE);
			GetDlgItem(IDC_STARTSPED)->EnableWindow(TRUE);
			GetDlgItem(IDC_ACCSPED)->EnableWindow(TRUE);
			GetDlgItem(IDC_MAXSPED)->EnableWindow(TRUE);
			GetDlgItem(IDC_JOGSPED)->EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("密码错误！"),_T(""),MB_ICONERROR);
		}
	}
}


void CParamdlg::OnSelchangedMotortree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM m_item = m_Motortree.GetSelectedItem();
	for (int k = 0;k<32;k++)
	{
		if (m_item == motor_Item[k])
		{
			motor_index = k;
			GetDlgItem(IDC_MOTORNAME)->SetWindowTextW(tree_str[k]);
			update_speed();
			break;
		}
	}
	*pResult = 0;
}


HBRUSH CParamdlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	pDC->SetBkMode(TRANSPARENT);
	return theApp.m_brush;//hbr;
}
void CParamdlg::OnContextMenu(CWnd* pWnd, CPoint pos)
{

}

void CParamdlg::OnBnClickedSvo()
{
	CButton *m_bt = (CButton*)GetDlgItem(IDC_SVO);
	int ret = m_bt->GetCheck();
	m_bt->EnableWindow(FALSE);
	APS_set_servo_on( motor_index, ret); 
	Sleep(1000);
	m_bt->EnableWindow(TRUE);
	update_speed();

}


void CParamdlg::OnBnClickedSvo2()
{
	CButton *m_bt = (CButton*)GetDlgItem(IDC_SVO2);
	int ret = m_bt->GetCheck();
	if (ret)
	{
		m_bt->EnableWindow(false);
		int cardid = motor_index/8;
		int port = motor_index%8;
		m_Motor.WritePort(false,cardid,port,true);
		Sleep(2000);
		m_Motor.WritePort(false,cardid,port,false);
		m_bt->EnableWindow(true);
	}
	m_bt->SetCheck(false);
	update_speed();
}
