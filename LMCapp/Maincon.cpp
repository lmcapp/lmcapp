// Maincon.cpp : 实现文件
//

#include "stdafx.h"
#include "LMCapp.h"
#include "MainFrm.h"

#include "LMCappDoc.h"
#include "LMCappView.h"
#include "Maincon.h"
#include "afxdialogex.h"
#include "Logic.h"
#include "Motor.h"
#include "Cpassword.h"
// CMaincon 对话框

IMPLEMENT_DYNAMIC(CMaincon, CDialogEx)

CMaincon::CMaincon(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMaincon::IDD, pParent)
	, m_paibian0(0)
	, m_paibian1(0)
	, m_dengliao0(0)
	, m_dengliao1(0)
	, m_quliao0(0)
	, m_quliao1(0)
	, m_dingsheng0(0)
	, m_dingsheng1(0)
	, m_paizhao0(0)
	, m_paizhao1(0)
	, m_dayin0(0)
	, m_dayin1(0)
	, m_fangliao0(0)
	, m_fangliao1(0)
	, m_printok0(0)
	, m_printok1(0)
	, m_putdingshneg0(0)
	, m_putdingsheng1(0)
	, m_headtemp0(0)
	, m_headtemp1(0)
	, m_headtemp2(0)
	, m_headtempx(0)
{

}

CMaincon::~CMaincon()
{
}

void CMaincon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITPAIBIAN0, m_paibian0);
	DDX_Text(pDX, IDC_EDITPAIBIAN1, m_paibian1);
	DDX_Text(pDX, IDC_EDITDENGLIAO0, m_dengliao0);
	DDX_Text(pDX, IDC_EDITDENGLIAO1, m_dengliao1);
	DDX_Text(pDX, IDC_EDITQULIAO0, m_quliao0);
	DDX_Text(pDX, IDC_EDITQULIAO1, m_quliao1);
	DDX_Text(pDX, IDC_EDITDINGSHENG1, m_dingsheng0);
	DDX_Text(pDX, IDC_EDITDINGSHENG2, m_dingsheng1);
	DDX_Text(pDX, IDC_EDITPAIZHAO0, m_paizhao0);
	DDX_Text(pDX, IDC_EDITPAIZHAO1, m_paizhao1);
	DDX_Text(pDX, IDC_EDITDAYIN0, m_dayin0);
	DDX_Text(pDX, IDC_EDITDAYIN1, m_dayin1);
	DDX_Text(pDX, IDC_EDITFANGLIAO0, m_fangliao0);
	DDX_Text(pDX, IDC_EDITFANGLIAO1, m_fangliao1);
	DDX_Text(pDX, IDC_EDITPRINTOKPOS0, m_printok0);
	DDX_Text(pDX, IDC_EDITPRINTOKPOS1, m_printok1);
	DDX_Text(pDX, IDC_EDITPUTDINGSHENG0, m_putdingshneg0);
	DDX_Text(pDX, IDC_EDITPUTDINGSHENG1, m_putdingsheng1);
	DDX_Text(pDX, IDC_TEMPHEAD1, m_headtemp0);
	DDX_Text(pDX, IDC_TEMPHEAD2, m_headtemp1);
	DDX_Text(pDX, IDC_TEMPHEAD3, m_headtemp2);
	DDX_Text(pDX, IDC_TEMPHEADX, m_headtempx);
}


BEGIN_MESSAGE_MAP(CMaincon, CDialogEx)
	ON_BN_CLICKED(IDC_STARTSHANGLIAO, &CMaincon::OnBnClickedStartshangliao)
	ON_BN_CLICKED(IDC_CHECKOUT8, &CMaincon::OnBnClickedCheckout8)
	ON_BN_CLICKED(IDC_CHECKOUT9, &CMaincon::OnBnClickedCheckout9)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RESETALARM, &CMaincon::OnBnClickedResetalarm)
	ON_BN_CLICKED(IDC_STARTPRINT, &CMaincon::OnBnClickedStartprint)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_READPAIBIANPOS0, &CMaincon::OnBnClickedReadpaibianpos0)
	ON_BN_CLICKED(IDC_READPAIBIANPOS1, &CMaincon::OnBnClickedReadpaibianpos1)
	ON_BN_CLICKED(IDC_READDENGLIAOPOS0, &CMaincon::OnBnClickedReaddengliaopos0)
	ON_BN_CLICKED(IDC_READDENGLIAOPOS1, &CMaincon::OnBnClickedReaddengliaopos1)
	ON_BN_CLICKED(IDC_READQULIAOPOS0, &CMaincon::OnBnClickedReadquliaopos0)
	ON_BN_CLICKED(IDC_READQULIAOPOS1, &CMaincon::OnBnClickedReadquliaopos1)
	ON_BN_CLICKED(IDC_READDINGSHENGPOS0, &CMaincon::OnBnClickedReaddingshengpos0)
	ON_BN_CLICKED(IDC_READDINGSHENGPOS1, &CMaincon::OnBnClickedReaddingshengpos1)
	ON_BN_CLICKED(IDC_READGRBGPOS0, &CMaincon::OnBnClickedReadgrbgpos0)
	ON_BN_CLICKED(IDC_READGRBGPOS1, &CMaincon::OnBnClickedReadgrbgpos1)
	ON_BN_CLICKED(IDC_READPRINTPOS0, &CMaincon::OnBnClickedReadprintpos0)
	ON_BN_CLICKED(IDC_READPRINTPOS1, &CMaincon::OnBnClickedReadprintpos1)
	ON_BN_CLICKED(IDC_READPUTPOS0, &CMaincon::OnBnClickedReadputpos0)
	ON_BN_CLICKED(IDC_READPUTPOS1, &CMaincon::OnBnClickedReadputpos1)
	ON_BN_CLICKED(IDC_CHECKOUT10, &CMaincon::OnBnClickedCheckout10)
	ON_BN_CLICKED(IDC_CHECKOUT11, &CMaincon::OnBnClickedCheckout11)
	ON_BN_CLICKED(IDC_CHECKOUT12, &CMaincon::OnBnClickedCheckout12)
	ON_BN_CLICKED(IDC_CHECKOUT13, &CMaincon::OnBnClickedCheckout13)
	ON_BN_CLICKED(IDC_STOP, &CMaincon::OnBnClickedStop)
	ON_BN_CLICKED(IDC_ALLGOHOME, &CMaincon::OnBnClickedAllgohome)
	ON_BN_CLICKED(IDC_START, &CMaincon::OnBnClickedStart)
	ON_BN_CLICKED(IDC_CHANGEPOS, &CMaincon::OnBnClickedChangepos)
	ON_BN_CLICKED(IDC_CHANGEPOS2, &CMaincon::OnBnClickedChangepos2)
	ON_BN_CLICKED(IDC_READPUTDINGSHENG1, &CMaincon::OnBnClickedReadputdingsheng1)
	ON_BN_CLICKED(IDC_READPRINTOK0, &CMaincon::OnBnClickedReadprintok0)
	ON_BN_CLICKED(IDC_READPRINTOK1, &CMaincon::OnBnClickedReadprintok1)
	ON_BN_CLICKED(IDC_READPUTDINGSHENG0, &CMaincon::OnBnClickedReadputdingsheng0)
	ON_BN_CLICKED(IDC_CHECKOUT14, &CMaincon::OnBnClickedCheckout14)
	ON_BN_CLICKED(IDC_STARTXIALIAO, &CMaincon::OnBnClickedStartxialiao)
	ON_BN_CLICKED(IDC_STARTXIALIAO2, &CMaincon::OnBnClickedStartxialiao2)
	ON_BN_CLICKED(IDC_CHECKUSE1DAO, &CMaincon::OnBnClickedCheckuse1dao)
	ON_BN_CLICKED(IDC_CHECKUSE2DAO, &CMaincon::OnBnClickedCheckuse2dao)
	ON_BN_CLICKED(IDC_GOPAIBIANPOS0, &CMaincon::OnBnClickedGopaibianpos0)
	ON_BN_CLICKED(IDC_GOPAIBIANPOS1, &CMaincon::OnBnClickedGopaibianpos1)
	ON_BN_CLICKED(IDC_GODENGLIAOPOS20, &CMaincon::OnBnClickedGodengliaopos20)
	ON_BN_CLICKED(IDC_GODENGLIAOPOS21, &CMaincon::OnBnClickedGodengliaopos21)
	ON_BN_CLICKED(IDC_GOQULIAOPOS0, &CMaincon::OnBnClickedGoquliaopos0)
	ON_BN_CLICKED(IDC_GOQULIAOPOS1, &CMaincon::OnBnClickedGoquliaopos1)
	ON_BN_CLICKED(IDC_GODINGSHENGPOS0, &CMaincon::OnBnClickedGodingshengpos0)
	ON_BN_CLICKED(IDC_GODINGSHENGPOS1, &CMaincon::OnBnClickedGodingshengpos1)
	ON_BN_CLICKED(IDC_GOGRBGPOS0, &CMaincon::OnBnClickedGogrbgpos0)
	ON_BN_CLICKED(IDC_GOGRBGPOS1, &CMaincon::OnBnClickedGogrbgpos1)
	ON_BN_CLICKED(IDC_GOPRINTPOS0, &CMaincon::OnBnClickedGoprintpos0)
	ON_BN_CLICKED(IDC_GOPRINTPOS1, &CMaincon::OnBnClickedGoprintpos1)
	ON_BN_CLICKED(IDC_GOPUTPOS0, &CMaincon::OnBnClickedGoputpos0)
	ON_BN_CLICKED(IDC_GOPUTPOS1, &CMaincon::OnBnClickedGoputpos1)
	ON_BN_CLICKED(IDC_GOPRINTOK0, &CMaincon::OnBnClickedGoprintok0)
	ON_BN_CLICKED(IDC_GOPRINTOK1, &CMaincon::OnBnClickedGoprintok1)
	ON_BN_CLICKED(IDC_GOPUTDINGSHENG0, &CMaincon::OnBnClickedGoputdingsheng0)
	ON_BN_CLICKED(IDC_GOPUTDINGSHENG1, &CMaincon::OnBnClickedGoputdingsheng1)
	ON_BN_CLICKED(IDC_CHECK1A, &CMaincon::OnBnClickedCheck1a)
	ON_BN_CLICKED(IDC_CHECK1B, &CMaincon::OnBnClickedCheck1b)
	ON_BN_CLICKED(IDC_CHECK2A, &CMaincon::OnBnClickedCheck2a)
	ON_BN_CLICKED(IDC_CHECK2B, &CMaincon::OnBnClickedCheck2b)
	ON_BN_CLICKED(IDC_CHECKOUT15, &CMaincon::OnBnClickedCheckout15)
	ON_BN_CLICKED(IDC_CHECKOUT16, &CMaincon::OnBnClickedCheckout16)
	ON_BN_CLICKED(IDC_BOLI, &CMaincon::OnBnClickedBoli)
	ON_BN_CLICKED(IDC_GUIPIAN, &CMaincon::OnBnClickedGuipian)
	ON_BN_CLICKED(IDC_CHANGEPOS3, &CMaincon::OnBnClickedChangepos3)
END_MESSAGE_MAP()


// CMaincon 消息处理程序


UINT CMaincon::auto_run_shangliao(LPVOID param)
{
	CLMCappApp* pApp=(CLMCappApp*)AfxGetApp();  

	CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	ASSERT_KINDOF(CMainFrame, pAppFrame);
	CLMCappView *p=(CLMCappView *) pAppFrame->GetActiveView();

	p->addruninfo1(_T("上料线程启动！"));
	
	CString str;
	while (!m_logic.stop&&!m_logic.alarm)
	{
		if (!m_logic.alarm&&(Step[0] ==0)&&!m_logic.stop&&!m_logic.firstAshangliaoOK)
		{
			while (!m_logic.Ld(0,P8))//等待来料信号
			{
				//	bool ret = m_logic.Ld(0,P8);
				//	bool ret1 = m_logic.Ld(1,P18);
				if (str!=(_T("等待来料信号！")))
				{
					str=(_T("等待来料信号！"));
					p->addruninfo1(str);
				}
				if (m_logic.stop||m_logic.alarm)
				{
					break;
				}
				Sleep(10);
			}
			p->AddStep(Step[0]);
		}

		//------------------------送料电机开始送料
		if ((Step[0]==1)&&!m_logic.alarm&&!m_logic.stop)
		{				
			if (!m_logic.Ld(0,P10)&&!m_logic.Ld(0,P9))//载台2到位感应器
			{
				if (str!=(_T("载台2光纤缺料，往载台2送料！")))
				{
					str=(_T("载台2光纤缺料，往载台2送料！"));
					p->addruninfo1(str);
				}
				while(!m_logic.Ld(0,P11))//挡料气缸在原点
				{
					if (str!=(_T("判断挡料气缸原点！")))
					{
						str=(_T("判断挡料气缸原点！"));
						p->addruninfo1(str);
					}
					if (m_logic.stop||m_logic.alarm)
					{
						break;
					}
					Sleep(10);
				}
				m_Motor.velocity_move(MOTOR0,m_Motor.move_maxspeed[MOTOR0]);//送料

				while (!m_logic.Ld(0,P10))//载台2到位感应器
				{
					if (str!=(_T("等待载台2光纤信号！")))
					{
						str=(_T("等待载台2光纤信号！"));
						p->addruninfo1(str);
					}
					if (m_logic.stop||m_logic.alarm)
					{
						break;
					}
					Sleep(10);
				} 
				m_Motor.stop(MOTOR0);
				m_Motor.wait_move_done(MOTOR0);
			}
			else
			{
				if (str!=(_T("载台2不需要送料！")))
				{
					str=(_T("载台2不需要送料！"));
					p->addruninfo1(str);
				}
			}
			p->AddStep(Step[0]);
		}

		if ((Step[0]==2)&&!m_logic.alarm&&!m_logic.stop)
		{				
			if (!m_logic.Ld(0,P9)&&m_logic.Ld(0,P10))//载台1到位感应器
			{
				if (str!=(_T("载台1光纤缺料，往载台1送料！")))
				{
					str=(_T("载台1光纤缺料，往载台1送料！"));
					p->addruninfo1(str);
				}
				while(!m_logic.Ld(0,P11))//挡料气缸在原点
				{
					if (str!=(_T("判断挡料气缸原点！")))
					{
						str=(_T("判断挡料气缸原点！"));
						p->addruninfo1(str);
					}
					if (m_logic.stop||m_logic.alarm)
					{
						break;
					}
					Sleep(10);
				}
				m_logic.Set(0,M8);//挡料气缸 下来
				while(!m_logic.Ld(0,P12))//||!m_logic.Ld(0,P22))//--------------16 
				{
					if (str!=(_T("等待挡料气缸到位！")))
					{
						str=(_T("等待挡料气缸到位！"));
						p->addruninfo1(str);
					}
					if (m_logic.stop||m_logic.alarm)
					{
						break;
					}
					Sleep(10);
				}
				//while (!m_logic.Ld(0,P8))//等待来料信号
				//{
				//	//	bool ret = m_logic.Ld(0,P8);
				//	//	bool ret1 = m_logic.Ld(1,P18);
				//	if (str!=(_T("等待来料信号！")))
				//	{
				//		str=(_T("等待来料信号！"));
				//		p->addruninfo1(str);
				//	}
				//	if (m_logic.stop||m_logic.alarm)
				//	{
				//		break;
				//	}
				//	Sleep(10);
				//}
				

				while (!m_logic.Ld(0,P9))//载台1到位感应器
				{
					m_Motor.velocity_move(MOTOR0,m_Motor.move_maxspeed[MOTOR0]);//送料
					if (str!=(_T("等待载台1光纤信号！")))
					{
						str=(_T("等待载台1光纤信号！"));
						p->addruninfo1(str);
					}
					if (m_logic.stop||m_logic.alarm)
					{
						break;
					}
					Sleep(10);
				} 
				m_Motor.stop(MOTOR0);
				m_Motor.wait_move_done(MOTOR0);
			}
			else
			{
				if (m_logic.Ld(0,P9)&&m_logic.Ld(0,P10))//载台1到位感应器
				{
					if (str!=(_T("载台1不需要送料，等待取料！")))
					{
						str=(_T("载台1不需要送料，等待取料！"));
						p->addruninfo1(str);
					}
				}
			}
			p->AddStep(Step[0]);
		}
		if (Step[0]==3&&!m_logic.alarm&&!m_logic.stop)//开始拍边
		{
			//---------------开始拍边
			m_Motor.absolute_move(MOTOR1,m_Motor.PAIBIANPOS[0]);//拍边距离------变量 添加；
			

			//---------------开始拍边
			m_Motor.absolute_move(MOTOR2,m_Motor.PAIBIANPOS[1]);//拍边距离------变量 添加；
			m_Motor.wait_move_done(MOTOR2);
			m_Motor.wait_move_done(MOTOR1);
			m_Motor.absolute_move(MOTOR1,PAIBAINHOME0);//拍边复位
			m_Motor.absolute_move(MOTOR2,PAIBAINHOME1);//拍边复位

			m_logic.Reset(0,M8);//挡料气缸 复位
			while(!m_logic.Ld(0,P11))//||!m_logic.Ld(0,P22))//--------------16 
			{
				if (str!=(_T("判断挡料气缸原点！")))
				{
					str=(_T("判断挡料气缸原点！"));
					p->addruninfo1(str);
				}
				if (m_logic.stop||m_logic.alarm)
				{
					break;
				}
				Sleep(10);
			}
			m_Motor.wait_move_done(MOTOR1);
			m_Motor.wait_move_done(MOTOR2);
			Step[0] = 0;
			if (str!=(_T("上料完成！")))
			{
				str=(_T("上料完成！"));
				p->addruninfo1(str);
			}
			m_logic.firstAshangliaoOK =true;
		}
	}
	p->addruninfo1(_T("上料线程停止！"));
	return 0;
}
 UINT CMaincon::auto_get_camera_print(LPVOID param)
 {
	 CLMCappApp* pApp=(CLMCappApp*)AfxGetApp();  

	 CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	 ASSERT_KINDOF(CMainFrame, pAppFrame);
	 CLMCappView *p=(CLMCappView *) pAppFrame->GetActiveView();

	 if (m_Motor.DENGLIAOPOS[0]==0||m_Motor.QULIAOPOS[0]==0)
	 {
		 p->addruninfo1(_T("运动位置参数为0，请调整位置！！"));
		 return 0;
	 }
	 p->addruninfo1(_T("取料打印线程启动！"));

	 CString str;
	 while (!m_logic.stop&&!m_logic.alarm)
	 {
		 m_Motor.absolute_move(MOTOR14,m_Motor.DENGLIAOPOS[0]);//----------------等料位置，添加变量 直线电机15
		 m_Motor.absolute_move(MOTOR15,m_Motor.DENGLIAOPOS[1]);//----------------等料位置，添加变量 直线电机16

		 m_Motor.wait_move_done(MOTOR14);
		 m_Motor.wait_move_done(MOTOR15);
		 Sleep(1000);
		 if (!m_logic.alarm&&(Step[1] ==0)&&!m_logic.stop)//料没准备好，去等料位
		 {
			 while(!m_logic.firstAshangliaoOK)//料没准备好
			 {
				 if (str!=(_T("料没准备好！")))
				 {
					 str=(_T("料没准备好！"));
					 p->addruninfo1(str);
				 }
				 if (m_logic.stop||m_logic.alarm)
				 {
					 break;
				 }
				 Sleep(10);
			 }
			 p->AddStep(Step[1]);
		 }

		 //------------------------去接料位置
		 if ((Step[1]==1)&&!m_logic.alarm&&m_logic.firstAshangliaoOK)//料准备好，去接料位
		 {	
			 while(!m_logic.Ld(0,P11))//挡料气缸在原点
			 {
				 if (str!=(_T("去接料位，判断挡料气缸原点！")))
				 {
					 str=(_T("去接料位，判断挡料气缸原点！"));
					 p->addruninfo1(str);
				 }
				 if (m_logic.stop||m_logic.alarm)
				 {
					 break;
				 }
				 Sleep(10);
			 }

			 m_Motor.absolute_move(MOTOR14,m_Motor.QULIAOPOS[0]);//----------------取料位置，添加变量 直线电机15
			 m_Motor.wait_move_done(MOTOR14);
			 m_Motor.absolute_move(MOTOR3,m_Motor.DINGSHENGPOS[0]);//-----------------顶升电机位置，添加变量
			
			 m_Motor.absolute_move(MOTOR15,m_Motor.QULIAOPOS[1]);//----------------取料位置，添加变量 直线电机16
			 m_Motor.wait_move_done(MOTOR15);
			 m_Motor.absolute_move(MOTOR7,m_Motor.DINGSHENGPOS[1]);//-----------------顶升电机位置，添加变量
			 
			 m_Motor.wait_move_done(MOTOR3);
			 m_Motor.wait_move_done(MOTOR7);
			 //---------------
			 m_Motor.WritePort_2(false,0,9,10,true);//--------------吸附
			 //---------------
			 Sleep(1000);
			 p->AddStep(Step[1]);
		 }

		 if ((Step[1]==2)&&!m_logic.alarm&&!m_logic.stop)//直线电机16去拍照位置
		 {				
	        m_Motor.absolute_move(MOTOR15,m_Motor.PAIZHAOPOS[1]);//----------------拍照位置，添加变量 直线电机16
			m_Motor.wait_move_done(MOTOR15);
			//----------拍照定位---待添加
			m_Cam.OnSendSoftCommand(0);
			//-----------定位完成--16 开始打印
			p->AddStep(Step[1]);
		 }
		 if (Step[1]==3&&!m_logic.alarm&&!m_logic.stop)//直线电机16 去打印完成位置  直线电机15 去拍照位置 
		 {
			 m_Motor.absolute_move(MOTOR15,m_Motor.PRINTOKPOS[1]);//----------------直线电机16打印位置，添加变量 直线电机16
			 m_Motor.absolute_move(MOTOR14,m_Motor.PAIZHAOPOS[0]);//----------------直线电机15拍照位置，添加变量 直线电机15
			 m_Motor.wait_move_done(MOTOR14);
			 //----------拍照定位---待添加
			 m_Cam.OnSendSoftCommand(0);
			 //---------------------定位完成-直线电机15 开始打印
			 m_Motor.wait_move_done(MOTOR15);
			 //-------------
			  m_Motor.absolute_move(MOTOR7,m_Motor.PUTDINGSHENGPOS[1]);
			  m_Motor.wait_move_done(MOTOR7);
			  m_Motor.absolute_move(MOTOR15,m_Motor.FANGLIAOPOS[1]);//----------------直线电机16下料位置，添加变量 直线电机16
			  m_Motor.wait_move_done(MOTOR15);
			 //-------------
			  p->AddStep(Step[1]);
		 }
		 if (Step[1]==4&&!m_logic.alarm&&!m_logic.stop)//直线电机15 去打印完成位置  
		 {
			 m_Motor.absolute_move(MOTOR14,m_Motor.PRINTOKPOS[0]);//----------------直线电机15打印位置，添加变量 直线电机15

			 //---------------------直线电机15 开始打印
			 m_Motor.wait_move_done(MOTOR14);
			 //-------------
			 //
			 m_Motor.absolute_move(MOTOR3,m_Motor.PUTDINGSHENGPOS[0]);
			 m_Motor.wait_move_done(MOTOR3);
			 m_Motor.absolute_move(MOTOR14,m_Motor.FANGLIAOPOS[0]);//----------------直线电机15下料位置，添加变量 直线电机15
			 m_Motor.wait_move_done(MOTOR14);
			 //-------------
			 p->AddStep(Step[1]);
		 }
		 if (Step[1]==5&&!m_logic.alarm&&!m_logic.stop)//开始下料
		 {
             //---------------------顶升气缸回原点
			 //--------------吸附电磁阀打开
			  m_Motor.WritePort_2(false,0,9,10,false);//--------------吸附
			  m_Motor.absolute_move(MOTOR3,0);//-----------------顶升电机A
			  m_Motor.absolute_move(MOTOR7,0);//-----------------顶升电机b
			  m_Motor.wait_move_done(MOTOR3);
			  m_Motor.wait_move_done(MOTOR7);
			 //-------------
			  m_logic.firstAshangliaoOK =false;
			  m_Motor.relative_move(MOTOR13,-20000);//-----------下料电机
			  m_Motor.absolute_move(MOTOR14,m_Motor.DENGLIAOPOS[0]);//----------------等料位置，添加变量 直线电机15
			  Sleep(500);
			  m_Motor.absolute_move(MOTOR15,m_Motor.DENGLIAOPOS[1]);//----------------等料位置，添加变量 直线电机16
			  m_Motor.wait_move_done(MOTOR13);
			 
			  Step[1]=0;
		 }
	 }
	 p->addruninfo1(_T("取料打印线程停止！"));
	 return 0;
 }
 UINT CMaincon::auto_run_1B(LPVOID param)
 {
	 CMaincon * m_con = (CMaincon*)param;
	 CLMCappApp* pApp=(CLMCappApp*)AfxGetApp();  

	 CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	 ASSERT_KINDOF(CMainFrame, pAppFrame);
	 CLMCappView *p=(CLMCappView *) pAppFrame->GetActiveView();
	 p->addruninfo1(_T("载台启动！"));
	 plc.m[100] =m_logic.start;//------------开始
	 plc.m[101] = m_logic.stop;//------------停止
	 plc.m[102] = m_logic.reset;//-----------复位
	 plc.m[103] = m_logic.alarm;//-----------报警
	 plc.m[105] = 1;//-----------------------常通信号
	 plc.LD(0,100,M);plc.ANDI(0,101,M);plc.ANDI(0,103,M);plc.Out(0,104,M);//M104启动保持信号
	 		int count = 0;
			int ret =false;
	while(plc.m[104])
	{
		if (m_con->use1dao)
		{
		
		plc.m[100] =m_logic.start;//------------开始
		plc.m[101] = m_logic.stop;//------------停止
		plc.m[102] = m_logic.reset;//-----------复位
		plc.m[103] = m_logic.alarm;//-----------报警
		plc.m[105] = 1;//-----------------------常通信号
	plc.LD(0,100,M);plc.ANDI(0,101,M);plc.ANDI(0,103,M);plc.Out(0,104,M);//M104启动保持信号
	if (m_con->use1daoB)
	{
	
	plc.ANDI(0,10,X);plc.AND(0,11,X);plc.AND(0,104,M);plc.ANDI(0,1,M);plc.ANDI(0,60,M);plc.ANDI(0,61,M);plc.ANDI(0,151,M);plc.ANDI(0,50,M);plc.SET(0,0,M);
	                                                                                                                      if(m_con->use1daoA)
	                                                                                                                      plc.SET(0,151,M);
	                                                                                  
	plc.LD(0,0,M);plc.AND(0,104,M);plc.SET(0,1,M);
	                               plc.RSET(0,0,M);
	                               plc.PULS(2,MOTOR0,0,m_Motor.move_maxspeed[MOTOR0]);//送料
								  // Sleep(5);
	plc.LD(0,10,X);plc.AND(0,1,M);plc.SET(0,3,M);
	plc.LD(0,3,M);plc.RSET(0,1,M);
	              plc.RSET(0,3,M);
	              plc.SET(0,4,M);//送料到位              
	              plc.SET(0,50,M);//屏蔽上料
	plc.LD(0,4,M);plc.STOP(MOTOR0);
	if(m_con->use1daoA)
	              plc.SET(0,61,M);//B载台使用信号
	plc.LD(0,4,M);plc.AND(0,104,M);plc.AXIS_DONE(MOTOR0);plc.SET(0,5,M);//拍边信号
		                                                 plc.RSET(0,4,M);

    plc.SET(0,5,M);plc.AND(0,104,M);plc.SET(0,6,M);
		                            plc.RSET(0,5,M);
	                                plc.PULS(0,MOTOR2,m_Motor.PAIBIANPOS[1],0);
                                    //Sleep(5);
    plc.LD(0,6,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR2);plc.RSET(0,6,M);
                                                          plc.SET(0,7,M);//拍边张开
										                  
	plc.LD(0,7,M);                 plc.SET(0,8,M);
	                               plc.RSET(0,7,M);
	                               plc.PULS(0,MOTOR2,PAIBAINHOME1,0);
								  // Sleep(5);
	 plc.LD(0,8,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR2);plc.RSET(0,8,M);
								                           plc.SET(0,9,M);//直线电机16来接料
														  
    
    plc.LD(0,105,M);plc.GETPEL(MOTOR7);plc.Out(0,55,M);//检测顶升电机是否在原点；
	plc.LD(0,105,M);plc.GetPOS(MOTOR14,plc.d[14]);
	plc.LD(0,105,M); plc.AND(0,104,M);plc.AND(0,55,M);plc.ANDI(0,57,M); plc.AND(0,201,M); plc.ANDI(0,51,M);
	                                                  
	                                                 plc.SET(0,10,M);
	                                                 //plc.RSET(0,9,M);
	                                                 plc.PULS(0,MOTOR15,m_Motor.QULIAOPOS[1],0);
									                 plc.SET(0,51,M);//屏蔽取料
													 plc.SET(0,202,M);//反向运动；
								//	Sleep(5);
	plc.LD(0,105,M); plc.AND(0,104,M);plc.AND(0,55,M); plc.ANDI(0,57,M);plc.CMP(0,plc.d[14],m_Motor.QULIAOPOS[0]);plc.ANDI(0,201,M);plc.ANDI(0,203,M); plc.ANDI(0,51,M);plc.SET(0,10,M);
													// plc.RSET(0,9,M);
													 plc.PULS(0,MOTOR15,m_Motor.QULIAOPOS[1],0);
													 plc.SET(0,51,M);//屏蔽取料
	plc.LD(0,105,M);plc.GetPOS(MOTOR15,plc.d[15]);
	plc.LD(0,10,M);plc.CMP(2,plc.d[15],m_Motor.PRINTOKPOS[1]);plc.PULS(0,MOTOR7,0,0);
	                                                         
	plc.LD(0,10,M);plc.AND(0,9,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR15);plc.AXIS_DONE(MOTOR7);plc.SET(0,11,M);
	                                                                             plc.RSET(0,10,M);//开始顶升
																				 plc.RSET(0,202,M);//反向运动；
																				 plc.RSET(0,9,M);
    
	plc.LD(0,11,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR8);plc.AXIS_DONE(MOTOR9);plc.AXIS_DONE(MOTOR10);plc.SET(0,12,M); //电磁阀吸附信号
									                                                                    plc.RSET(0,11,M);
									                                                                    plc.PULS(0,MOTOR7,m_Motor.DINGSHENGPOS[1],0);
								//	 Sleep(5);
	plc.LD(0,12,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR7);plc.SET(0,10,Y); //电磁阀吸附信号
									                       plc.SET(0,13,M);//去拍照位置;
	                                                       plc.RSET(0,12,M);
    plc.LD(0,13,M); plc.AND(0,104,M);plc.SET(0,14,M); //直线电机16去拍照位置
									 plc.RSET(0,13,M);
									 plc.PULS(0,MOTOR15,m_Motor.PAIZHAOPOS[1],0);	
									 
								//	 Sleep(5);
	
    plc.LD(0,14,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR15);plc.SET(0,40,M); //直线电机16拍照
								                            plc.RSET(0,14,M);
															plc.RSET(0,50,M);//解除屏蔽上料
															plc.ORG(MOTOR7);
   
    plc.LD(0,40,M);plc.AXIS_DONE(MOTOR7);plc.SET(0,15,M);
	                                     plc.RSET(0,40,M);//顶升电机回原点
	if(plc.m[15]||plc.m[152])
	{
		plc.LD(0,105,M);plc.RSET(0,15,M);
		if(++count<8&&ret!=1)
		{
			ret = m_con->xxy_move(1);//载台1;
			if (ret==0)
			{
				CString str;
				str.Format(_T("第%d次抓点失败！"),count);
				p->addruninfo1(str);
				//break;
			}
			else
			{
				CString str;
				str.Format(_T("第%d次角度: %.4f"),count,m_math.angle(m_Cam.sunny_angle));
				p->addruninfo1(str);

			}
			plc.LD(0,105,M);plc.SET(0,152,M);
			//ret =1;//关闭拍照，直接打印
		}
		else
		{
			plc.LD(0,105,M);plc.RSET(0,152,M);
            plc.LD(0,105,M);plc.SET(0,153,M);//开始往后送料；
			if (ret==1)
			{
				plc.LD(0,105,M);plc.SET(0,154,M);//打印开启；
			    m_Cam.calc_print_camerax[1] = m_Cam.print_camerax[1]+(m_Cam.sunny_center_row-m_Cam.Height/2)*m_Cam.calc0_x*1000;
				m_Cam.calc_print_cameray[1] = m_Cam.print_cameray[1]-(m_Cam.sunny_center_column-m_Cam.Width/2)*m_Cam.calc0_y*2000;
			}
			count = 0;
			ret =0;
		}
	}

	plc.LD(0,154,M); plc.AND(0,104,M);plc.SET(0,155,M); 
	                                  plc.RSET(0,154,M);
	                                 // plc.PULS(0,MOTOR11,m_Cam.calc_print_camerax[1],0);//定位计算的位置先不执行
							         // plc.PULS(0,MOTOR12,m_Cam.print_cameraz[1],0);
									  plc.SET(0,156,M);
									  if (plc.m[156]&&plc.m[55])//拍照OK且顶升电机在原点
									  {
										  plc.RSET(0,156,M);
										//  m_con->m_print.m_imageFile=_T("D:\\Mono.bmp");
										  {											  
											  m_XDM.isprinting =true;
											  m_XDM.stopprint =false;			
											  m_XDM._yImageRes =969;
											  m_XDM.xdm_auto_print();
											  plc.Out(0,1000,T);
											  plc.SET(0,42,M);//正在打印
										  }
									  }
	                                                   
	 plc.LD(0,153,M); plc.AND(0,104,M);plc.ANDI(0,155,M);plc.AXIS_DONE(MOTOR15);plc.SET(0,16,M);//没定位 
	                                                         plc.RSET(0,153,M);
															 plc.PULS(0,MOTOR15,m_Motor.PRINTOKPOS[1],0);
															 plc.SET(0,200,M);//直线电机16 开始正向移动；
	
															 
															 //		 Sleep(5);
	if (!m_XDM.isprinting)
	{
		 plc.LD(0,105,M);plc.RSET(0,42,M);//打印完成
	}
	plc.LD(0,153,M); plc.AND(0,104,M);plc.AND(0,155,M);plc.ANDI(0,42,M);plc.AXIS_DONE(MOTOR15);plc.AXIS_DONE(MOTOR11);plc.AXIS_DONE(MOTOR12);plc.AND(0,1000,T);plc.SET(0,16,M); 
															 plc.RSET(0,153,M);
															 plc.PULS(0,MOTOR15,m_Motor.PRINTOKPOS[1],0);
															 plc.SET(0,200,M);//直线电机16 开始正向移动；
															 plc.RSET(0,155,M);
															 plc.RSET(0,1000,T);
    plc.LD(0,105,M);plc.GetPOS(MOTOR15,plc.d[15]);
	plc.LD(0,16,M); /*plc.AND(0,104,M);plc.CMP(1,plc.d[15],m_Motor.PRINTOKPOS[1]);*/plc.AXIS_DONE(MOTOR15);plc.SET(0,17,M); 
															                    plc.RSET(0,16,M);
																				plc.RSET(0,10,Y); //电磁阀吸附信号
															                    plc.PULS(0,MOTOR7,m_Motor.PUTDINGSHENGPOS[1],0);
																				plc.STOP(MOTOR15);
															                  //  Sleep(5);
	
	plc.LD(0,17,M);plc.AND(0,104,M);plc.AXIS_DONE(MOTOR7);plc.SET(0,18,M);
	                                                      plc.RSET(0,17,M);
														  plc.PULS(0,MOTOR15,m_Motor.FANGLIAOPOS[1],0);
														 // Sleep(50);
	plc.LD(0,18,M);plc.AND(0,104,M);plc.AXIS_DONE(MOTOR15);plc.SET(0,19,M);
	                                                       plc.RSET(0,10,Y); //电磁阀吸附信号
	                                                       plc.RSET(0,18,M);
														   plc.ORG(MOTOR7);
														   plc.RSET(0,200,M);//直线电机16 开始正向移动；
														   plc.ORG(MOTOR8);
														   plc.ORG(MOTOR9);
														   plc.ORG(MOTOR10);
													  //   Sleep(5);
    plc.LD(0,19,M);plc.AXIS_DONE(MOTOR7);plc.GETPEL(MOTOR7);plc.ANDI(0,57,M);
	                                                        plc.SET(0,20,M);
		                                                    plc.RSET(0,19,M);
															plc.PULS(1,MOTOR13,-40000,0);
															plc.RSET(0,51,M);//解除屏蔽取料；
														//	Sleep(5);
	 }
     //----------------------------------------------以上为载台B,以下为载台A M60 开始
	 if (m_con->use1daoA)
	 {
	 if (m_con->use1daoB)
	 plc.LD(0,61,M);
	 else
	 plc.LD(0,105,M);
	 plc.ANDI(0,60,M);plc.ANDI(0,150,M);plc.ANDI(0,9,X);plc.SET(0,62,M);
	                                                   plc.SET(0,8,Y);
	                                                   plc.SET(0,150,M);
	 plc.LD(0,62,M);plc.AND(0,104,M);plc.AND(0,12,X);plc.RSET(0,62,M);
									 plc.SET(0,63,M);//送料
									 plc.PULS(2,MOTOR0,0,m_Motor.move_maxspeed[MOTOR0]);
									 plc.SET(0,57,M);
	 plc.LD(0,63,M);plc.AND(0,9,X);plc.STOP(MOTOR0);
	                               plc.RSET(0,63,M);
								   plc.SET(0,64,M);
								   plc.RSET(0,8,Y);
								   plc.SET(0,60,M);//A送料到位
	 plc.LD(0,64,M);plc.AND(0,104,M);plc.AND(0,11,X);plc.AXIS_DONE(MOTOR0);plc.SET(0,65,M);
	                                                       plc.RSET(0,64,M);
     plc.LD(0,65,M);plc.AND(0,104,M);plc.SET(0,66,M);
	                                 plc.RSET(0,65,M);
									 plc.PULS(0,MOTOR1,m_Motor.PAIBIANPOS[0],0);
	plc.LD(0,66,M);plc.AND(0,104,M);plc.AXIS_DONE(MOTOR1);plc.SET(0,67,M);
	                                                      plc.RSET(0,66,M);

    plc.LD(0,67,M);plc.AND(0,104,M);plc.SET(0,68,M);
	                                plc.RSET(0,67,M);
									plc.PULS(0,MOTOR1,PAIBAINHOME0,0);
	plc.LD(0,68,M);plc.AND(0,104,M);plc.AXIS_DONE(MOTOR1);plc.SET(0,69,M);
									                      plc.RSET(0,68,M);
	plc.LD(0,105,M);plc.GETPEL(MOTOR3);plc.Out(0,56,M);//检测顶升电机是否在原点；
	plc.LD(0,105,M); plc.AND(0,104,M);plc.AND(0,56,M); plc.ANDI(0,91,M);plc.SET(0,70,M);
													 //plc.RSET(0,69,M);
													 plc.PULS(0,MOTOR14,m_Motor.QULIAOPOS[0],0);
													 plc.SET(0,91,M);//屏蔽取料
													 plc.SET(0,201,M);//反向运动
    plc.LD(0,105,M);plc.GetPOS(MOTOR14,plc.d[14]);
    plc.LD(0,70,M);plc.CMP(2,plc.d[14],m_Motor.PRINTOKPOS[0]);plc.PULS(0,MOTOR3,0,0);
	
	plc.LD(0,70,M);plc.AND(0,104,M);plc.AND(0,69,M);plc.AXIS_DONE(MOTOR14);plc.AXIS_DONE(MOTOR3);plc.SET(0,71,M);
	                                                                             plc.RSET(0,70,M);//开始顶升
																				 plc.RSET(0,201,M);//反向运动
																				 plc.RSET(0,69,M);
																				
	plc.LD(0,71,M); plc.AND(0,104,M);plc.SET(0,72,M); //电磁阀吸附信号
	                                  plc.RSET(0,71,M);
									  plc.PULS(0,MOTOR3,m_Motor.DINGSHENGPOS[0],0);
	plc.LD(0,72,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR3);plc.SET(0,9,Y); //电磁阀吸附信号
	                                                       plc.SET(0,73,M);//去拍照位置;
	                                                       plc.RSET(0,72,M);
	plc.LD(0,105,M);plc.GetPOS(MOTOR15,plc.d[15]);
	plc.LD(0,73,M); plc.AND(0,104,M);plc.CMP(1,plc.d[15],m_Motor.PAIZHAOPOS[1]+200000);plc.AND(0,200,M);plc.ANDI(0,202,M);plc.SET(0,74,M); //直线电机15去拍照位置
	                                                                                                   plc.RSET(0,73,M);
	                                                                                                   plc.PULS(0,MOTOR14,m_Motor.PAIZHAOPOS[0],0);
																									   plc.SET(0,203,M);
	//	 Sleep(5);
    plc.LD(0,73,M); plc.AND(0,104,M);plc.CMP(0,plc.d[15],m_Motor.FANGLIAOPOS[1]);plc.ANDI(0,200,M);plc.ANDI(0,202,M);plc.SET(0,74,M); //直线电机15去拍照位置
																									   plc.RSET(0,73,M);
																									   plc.PULS(0,MOTOR14,m_Motor.PAIZHAOPOS[0],0);	
																									   plc.SET(0,203,M);
	plc.LD(0,74,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR14);plc.SET(0,41,M); //直线电机15拍照
	                                                        plc.RSET(0,74,M);
															plc.RSET(0,60,M);//解除屏蔽上料
															plc.RSET(0,61,M);//解除屏蔽上料
															plc.RSET(0,150,M);//解除屏蔽上料
															plc.RSET(0,151,M);//解除屏蔽上料
															plc.ORG(MOTOR3);
	plc.LD(0,41,M);plc.AXIS_DONE(MOTOR3); plc.SET(0,75,M);
	                                      plc.RSET(0,41,M);
	if(plc.m[75])
	{
		plc.RSET(0,75,M);
		int count = 0;
		int ret =false;
		while(++count<5&&ret!=1)
		{
			ret = m_con->xxy_move(0);//载台1;
			if (ret==0)
			{
				//break;
			}
		}

		plc.SET(0,76,M);
		//-----添加ccd代码
	}
	plc.LD(0,105,M);plc.GetPOS(MOTOR15,plc.d[15]);
	plc.LD(0,76,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR14);plc.CMP(1,plc.d[15],m_Motor.PRINTOKPOS[1]+200000);plc.AND(0,200,M);plc.SET(0,77,M); 
	                                                                                                          plc.RSET(0,76,M);
	                                                                                                          plc.PULS(0,MOTOR14,m_Motor.PRINTOKPOS[0],0);
																											   plc.SET(0,203,M);
	
																											  //Sleep(5);
	plc.LD(0,76,M); plc.AND(0,104,M);plc.AXIS_DONE(MOTOR14);plc.CMP(0,plc.d[15],m_Motor.FANGLIAOPOS[1]);plc.ANDI(0,200,M);plc.ANDI(0,202,M);plc.SET(0,77,M); 
																											  plc.RSET(0,76,M);
																											  plc.PULS(0,MOTOR14,m_Motor.PRINTOKPOS[0],0);
																											  plc.SET(0,203,M);
	plc.LD(0,105,M);plc.GetPOS(MOTOR14,plc.d[14]);
	plc.LD(0,77,M);  /*plc.AND(0,104,M);;plc.CMP(1,plc.d[14],m_Motor.PRINTOKPOS[0]);*/plc.AXIS_DONE(MOTOR14);plc.SET(0,78,M); 
	                                                                            plc.RSET(0,77,M);
																				plc.RSET(0,10,Y); //电磁阀吸附信号
	                                                                            plc.PULS(0,MOTOR3,m_Motor.PUTDINGSHENGPOS[0],0);
																				plc.STOP(MOTOR14);
   
	plc.LD(0,78,M);plc.AND(0,104,M);plc.AXIS_DONE(MOTOR3);plc.SET(0,79,M);
														  plc.RSET(0,78,M);
														  plc.PULS(0,MOTOR14,m_Motor.FANGLIAOPOS[0],0);
																				// Sleep(50);
	plc.LD(0,79,M);plc.AND(0,104,M);plc.AXIS_DONE(MOTOR14);plc.SET(0,80,M);
														   plc.RSET(0,9,Y); //电磁阀吸附信号
														   plc.RSET(0,79,M);
														   plc.ORG(MOTOR3);
														   plc.RSET(0,203,M);
																				//   Sleep(5);
	plc.LD(0,80,M);plc.AXIS_DONE(MOTOR3);plc.GETPEL(MOTOR3);plc.SET(0,87,M);
																plc.RSET(0,80,M);
																plc.PULS(1,MOTOR13,-40000,0);
																plc.RSET(0,91,M);//解除屏蔽取料；
																plc.RSET(0,57,M);
	}
	}
	if (m_con->use2dao)
	{
		plc.n[100] =m_logic.start;//------------开始
		plc.n[101] = m_logic.stop;//------------停止
		plc.n[102] = m_logic.reset;//-----------复位
		plc.n[103] = m_logic.alarm;//-----------报警
		plc.n[105] = 1;//-----------------------常通信号
		plc.LD(0,100,N);plc.ANDI(0,101,N);plc.ANDI(0,103,N);plc.Out(0,104,N);//M104启动保持信号

		plc.ANDI(2,10,X);plc.AND(2,11,X);plc.AND(0,104,N);plc.ANDI(0,1,N);plc.ANDI(0,60,N);plc.ANDI(0,61,N);plc.ANDI(0,151,N);plc.ANDI(0,50,N);plc.SET(0,0,N);
		plc.SET(0,151,N);

		plc.LD(0,0,N);plc.AND(0,104,N);plc.SET(0,1,N);
		plc.RSET(0,0,N);
		plc.PULS(2,MOTOR0+16,0,-m_Motor.move_maxspeed[MOTOR0+16]);//送料
		// Sleep(5);
		plc.LD(2,10,X);plc.AND(0,1,N);plc.SET(0,3,N);
		plc.LD(0,3,N);plc.RSET(0,1,N);
		plc.RSET(0,3,N);
		plc.SET(0,4,N);//送料到位              
		plc.SET(0,50,N);//屏蔽上料
		plc.LD(0,4,N);plc.STOP(MOTOR0+16);
		plc.SET(0,61,N);//B载台使用信号
		plc.LD(0,4,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR0+16);plc.SET(0,5,N);//拍边信号
		plc.RSET(0,4,N);

		plc.SET(0,5,N);plc.AND(0,104,N);plc.SET(0,6,N);
		plc.RSET(0,5,N);
		plc.PULS(0,MOTOR2+16,m_Motor.PAIBIANPOS[1],0);
		//Sleep(5);
		plc.LD(0,6,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR2+16);plc.RSET(0,6,N);
		plc.SET(0,7,N);//拍边张开

		plc.LD(0,7,N);                 plc.SET(0,8,N);
		plc.RSET(0,7,N);
		plc.PULS(0,MOTOR2+16,PAIBAINHOME1,0);
		// Sleep(5);
		plc.LD(0,8,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR2+16);plc.RSET(0,8,N);
		plc.SET(0,9,N);//直线电机16来接料


		plc.LD(0,105,N); plc.GETPEL(MOTOR7+16);plc.Out(0,55,N);//检测顶升电机是否在原点；
		plc.LD(0,105,N);plc.GetPOS(MOTOR14+16,plc.d[30]);
		plc.LD(0,105,N); plc.AND(0,104,N);plc.AND(0,55,N);plc.ANDI(0,57,N); plc.AND(0,201,N); plc.ANDI(0,51,N);plc.SET(0,10,N);
		//plc.RSET(0,9,N);
		plc.PULS(0,MOTOR15+16,m_Motor.QULIAOPOS[1],0);
		plc.SET(0,51,N);//屏蔽取料
		plc.SET(0,202,N);//反向运动；
		//	Sleep(5);
		plc.LD(0,105,N); plc.AND(0,104,N);plc.AND(0,55,N);plc.ANDI(0,57,N); plc.CMP(0,plc.d[30],m_Motor.QULIAOPOS[0]);plc.ANDI(0,201,N);plc.ANDI(0,203,N); plc.ANDI(0,51,N);plc.SET(0,10,N);
		//plc.RSET(0,9,N);
		plc.PULS(0,MOTOR15+16,m_Motor.QULIAOPOS[1],0);
		plc.SET(0,51,N);//屏蔽取料
		plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
		plc.LD(0,10,N);plc.CMP(2,plc.d[31],m_Motor.PRINTOKPOS[1]);plc.PULS(0,MOTOR7+16,0,0);

		plc.LD(0,10,N);plc.AND(0,9,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.AXIS_DONE(MOTOR7+16);plc.SET(0,11,N);
		plc.RSET(0,10,N);//开始顶升
		plc.RSET(0,202,N);//反向运动；
		plc.RSET(0,9,N);
		plc.LD(0,11,N); plc.AND(0,104,N);plc.SET(0,12,N); //电磁阀吸附信号
		plc.RSET(0,11,N);
		plc.PULS(0,MOTOR7+16,m_Motor.DINGSHENGPOS[1],0);
		//	 Sleep(5);
		plc.LD(0,12,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR7+16);plc.SET(2,10,Y); //电磁阀吸附信号
		plc.SET(0,13,N);//去拍照位置;
		plc.RSET(0,12,N);
		plc.LD(0,13,N); plc.AND(0,104,N);plc.SET(0,14,N); //直线电机16去拍照位置
		plc.RSET(0,13,N);
		plc.PULS(0,MOTOR15+16,m_Motor.PAIZHAOPOS[1],0);	

		//	 Sleep(5);

		plc.LD(0,14,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.SET(0,15,N); //直线电机16拍照
		plc.RSET(0,14,N);
		plc.RSET(0,50,N);//解除屏蔽上料
		if(plc.n[15])
		{
			plc.RSET(0,15,N);
			int count = 0;
			int ret =false;
			while(++count<5&&ret!=1)
			{
				ret = m_con->xxy_move(3);//载台1;
				if (ret==0)
				{
					//break;
				}
			}

			plc.SET(0,152,N);
		}
		plc.LD(0,152,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.SET(0,16,N); 
		plc.RSET(0,152,N);
		plc.PULS(0,MOTOR15+16,m_Motor.FANGLIAOPOS[1],0);
		plc.SET(0,200,N);//直线电机16 开始正向移动；
		//		 Sleep(5);

		plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
		plc.LD(0,16,N);  /*plc.AND(0,104,M);*/plc.CMP(1,plc.d[31],m_Motor.PRINTOKPOS[1]);plc.SET(0,17,N); 
		plc.RSET(0,16,N);
		plc.PULS(0,MOTOR7+16,m_Motor.PUTDINGSHENGPOS[1],0);
		//  Sleep(5);

		plc.LD(0,17,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR7+16);plc.SET(0,18,N);
		plc.RSET(0,17,N);
		// plc.PULS(0,NOTOR15,N_Motor.FANGLIAOPOS[1],0);
		// Sleep(50);
		plc.LD(0,18,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.SET(0,19,N);
		plc.RSET(2,10,Y); //电磁阀吸附信号
		plc.RSET(0,18,N);
		plc.ORG(MOTOR7+16);
		plc.RSET(0,200,N);//直线电机16 开始正向移动；
		//   Sleep(5);
		plc.LD(0,19,N);plc.AXIS_DONE(MOTOR7+16);plc.GETPEL(MOTOR7+16);plc.SET(0,20,N);plc.ANDI(0,57,N);
		plc.RSET(0,19,N);
		plc.PULS(1,MOTOR13+16,40000,0);
		plc.RSET(0,51,N);//解除屏蔽取料；
		//	Sleep(5);
		//----------------------------------------------以上为载台B,以下为载台A M60 开始
		plc.LD(0,61,N);plc.ANDI(0,60,N);plc.ANDI(0,150,N);plc.ANDI(2,9,X);plc.SET(0,62,N);
		plc.SET(2,8,Y);
		plc.SET(0,150,N);
		plc.LD(0,62,N);plc.AND(0,104,N);plc.AND(2,12,X);plc.RSET(0,62,N);
		plc.SET(0,63,N);//送料
		plc.PULS(2,MOTOR0+16,0,-m_Motor.move_maxspeed[MOTOR0+16]);
		plc.SET(0,57,N);
		plc.LD(0,63,N);plc.AND(2,9,X);plc.STOP(MOTOR0+16);
		plc.RSET(0,63,N);
		plc.SET(0,64,N);
		plc.RSET(2,8,Y);
		plc.SET(0,60,N);//A送料到位
		plc.LD(0,64,N);plc.AND(0,104,N);plc.AND(2,11,X);plc.AXIS_DONE(MOTOR0+16);plc.SET(0,65,N);
		plc.RSET(0,64,N);
		plc.LD(0,65,N);plc.AND(0,104,N);plc.SET(0,66,N);
		plc.RSET(0,65,N);
		plc.PULS(0,MOTOR1+16,m_Motor.PAIBIANPOS[0],0);
		plc.LD(0,66,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR1+16);plc.SET(0,67,N);
		plc.RSET(0,66,N);

		plc.LD(0,67,N);plc.AND(0,104,N);plc.SET(0,68,N);
		plc.RSET(0,67,N);
		plc.PULS(0,	MOTOR1+16,PAIBAINHOME0,0);
		plc.LD(0,68,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR1+16);plc.SET(0,69,N);
		plc.RSET(0,68,N);
		plc.LD(0,105,N); plc.GETPEL(MOTOR3+16);plc.Out(0,56,N);//检测顶升电机是否在原点；
		plc.LD(0,105,N);plc.AND(0,104,N);plc.AND(0,56,N); plc.ANDI(0,91,N);plc.SET(0,70,N);
		//plc.RSET(0,69,N);
		plc.PULS(0,MOTOR14+16,m_Motor.QULIAOPOS[0],0);
		plc.SET(0,91,N);//屏蔽取料
		plc.SET(0,201,N);//反向运动
		plc.LD(0,105,N);plc.GetPOS(MOTOR14+16,plc.d[30]);
		plc.LD(0,70,N);plc.CMP(2,plc.d[30],m_Motor.PRINTOKPOS[0]);plc.PULS(0,MOTOR3+16,0,0);

		plc.LD(0,70,N);plc.AND(0,69,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.AXIS_DONE(MOTOR3+16);plc.SET(0,71,N);
		plc.RSET(0,70,N);//开始顶升
		plc.RSET(0,201,N);//反向运动
		plc.RSET(0,69,N);
		plc.LD(0,71,N); plc.AND(0,104,N);plc.SET(0,72,N); //电磁阀吸附信号
		plc.RSET(0,71,N);
		plc.PULS(0,MOTOR3+16,m_Motor.DINGSHENGPOS[0],0);
		plc.LD(0,72,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR3+16);plc.SET(2,9,Y); //电磁阀吸附信号
		plc.SET(0,73,N);//去拍照位置;
		plc.RSET(0,72,N);
		plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
		plc.LD(0,73,N); plc.AND(0,104,N);plc.CMP(1,plc.d[31],m_Motor.PAIZHAOPOS[1]+200000);plc.AND(0,200,N);plc.ANDI(0,202,N);plc.SET(0,74,N); //直线电机15去拍照位置
		plc.RSET(0,73,N);
		plc.PULS(0,MOTOR14+16,m_Motor.PAIZHAOPOS[0],0);
		plc.SET(0,203,N);
		//	 Sleep(5);
		plc.LD(0,73,N); plc.AND(0,104,N);plc.CMP(0,plc.d[31],m_Motor.FANGLIAOPOS[1]);plc.ANDI(0,200,N);plc.ANDI(0,202,N);plc.SET(0,74,N); //直线电机15去拍照位置
		plc.RSET(0,73,N);
		plc.PULS(0,MOTOR14+16,m_Motor.PAIZHAOPOS[0],0);	
		plc.SET(0,203,N);
		plc.LD(0,74,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.SET(0,75,N); //直线电机15拍照
		plc.RSET(0,74,N);
		plc.RSET(0,60,N);//解除屏蔽上料
		plc.RSET(0,61,N);//解除屏蔽上料
		plc.RSET(0,150,N);//解除屏蔽上料
		plc.RSET(0,151,N);//解除屏蔽上料
		if(plc.n[75])
		{
			plc.RSET(0,75,N);
			int count = 0;
			int ret =false;
			while(++count<5&&ret!=1)
			{
				ret = m_con->xxy_move(2);//载台1;
				if (ret==0)
				{
					//break;
				}
			}

			plc.SET(0,76,N);
			//-----添加ccd代码
		}
		plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
		plc.LD(0,76,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.CMP(1,plc.d[31],m_Motor.PRINTOKPOS[1]+200000);plc.AND(0,200,N);plc.SET(0,77,N); 
		plc.RSET(0,76,N);
		plc.PULS(0,MOTOR14+16,m_Motor.FANGLIAOPOS[0],0);
		plc.SET(0,203,N);

		//Sleep(5);
		plc.LD(0,76,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.CMP(0,plc.d[31],m_Motor.FANGLIAOPOS[1]);plc.ANDI(0,200,N);plc.ANDI(0,202,N);plc.SET(0,77,N); 
		plc.RSET(0,76,N);
		plc.PULS(0,MOTOR14+16,m_Motor.FANGLIAOPOS[0],0);
		plc.SET(0,203,N);
		plc.LD(0,105,N);plc.GetPOS(MOTOR14+16,plc.d[30]);
		plc.LD(0,77,N);  /*plc.AND(0,104,M);*/;plc.CMP(1,plc.d[30],m_Motor.PRINTOKPOS[0]);plc.SET(0,78,N); 
		plc.RSET(0,77,N);
		plc.PULS(0,MOTOR3+16,m_Motor.PUTDINGSHENGPOS[0],0);

		plc.LD(0,78,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR3+16);plc.SET(0,79,N);
		plc.RSET(0,78,N);
		// plc.PULS(0,NOTOR15,N_Motor.FANGLIAOPOS[1],0);
		// Sleep(50);
		plc.LD(0,79,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.SET(0,80,N);
		plc.RSET(2,9,Y); //电磁阀吸附信号
		plc.RSET(0,79,N);
		plc.ORG(MOTOR3+16);
		plc.RSET(0,203,N);
		//   Sleep(5);
		plc.LD(0,80,N);plc.AXIS_DONE(MOTOR3+16);plc.GETPEL(MOTOR3+16);plc.SET(0,87,N);
		plc.RSET(0,80,N);
		plc.PULS(1,MOTOR13+16,40000,0);
		plc.RSET(0,91,N);//解除屏蔽取料；
		plc.RSET(0,57,N);
	}
	}
	p->addruninfo1(_T("载台停止！"));
	return 0;
 }


 UINT CMaincon::auto_go_home(LPVOID param)
 {
	 CMaincon *mp = (CMaincon *)param;
	 CLMCappApp* pApp=(CLMCappApp*)AfxGetApp();  

	 CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	 ASSERT_KINDOF(CMainFrame, pAppFrame);
	 CLMCappView *p=(CLMCappView *) pAppFrame->GetActiveView();
	 CString str;
	
	 if (m_logic.start)
	 {
		 p->addruninfo1(_T("先停止再复位！"));
		 return 0;
	 }
	  p->addruninfo1(_T("设备开始复位！"));
	  m_logic.Reset(0,M8);
	  m_logic.Reset(2,M8);
	  m_Motor.WritePort_2(false,0,9,10,false);//--------------吸附
	  m_Motor.WritePort_2(false,2,9,10,false);//--------------吸附
	  while(!m_logic.Ld(0,P11))//||!m_logic.Ld(0,P22))//--------------16 
	  {
		  if (str!=(_T("判断1挡料气缸原点！")))
		  {
			  str=(_T("判断1挡料气缸原点！"));
			  p->addruninfo1(str);
		  }
		  if (m_logic.stop||m_logic.alarm)
		  {
			  break;
		  }
		  Sleep(10);
	  }
	  while(!m_logic.Ld(2,P11))//||!m_logic.Ld(0,P22))//--------------16 
	  {
		  if (str!=(_T("判断2挡料气缸原点！")))
		  {
			  str=(_T("判断2挡料气缸原点！"));
			  p->addruninfo1(str);
		  }
		  if (m_logic.stop||m_logic.alarm)
		  {
			  break;
		  }
		  Sleep(10);
	  }
	  if(m_logic.Ld(0,9)||m_logic.Ld(0,10))
	  {
		  m_Motor.relative_move(MOTOR0,-2000);
	  }
	  if (m_logic.go_home_stop)
	  {
		  return 0;
	  }
	  m_Motor.Go_home(12);
	  str=(_T("1道Z轴正在复位...."));
	  p->addruninfo1(str);
	  m_Motor.Go_home(28);
	  str=(_T("2道Z轴正在复位...."));
	   p->addruninfo2(str);

	   m_Motor.wait_move_done(12);
	   m_Motor.wait_move_done(28);
	   if (m_logic.go_home_stop)
	   {
		   return 0;
	   }

	   m_Motor.Go_home(11);
	   str=(_T("1道X轴正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.Go_home(27);
	   str=(_T("2道X轴正在复位...."));
	   p->addruninfo2(str);

	   m_Motor.wait_move_done(11);
	   m_Motor.wait_move_done(27);
	 //
	   if (m_logic.go_home_stop)
	   {
		   return 0;
	   }
	   m_Motor.Go_home(3);
	   m_Motor.Go_home(7);
	   m_Motor.Go_home(19);
	   m_Motor.Go_home(23);
	   str=(_T("1道顶升电机A正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.wait_move_done(3);

	   str=(_T("1道顶升电机B正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.wait_move_done(7);

	   str=(_T("2道顶升电机A正在复位...."));
	   p->addruninfo2(str);
	   m_Motor.wait_move_done(19);

	   str=(_T("2道顶升电机B正在复位...."));
	   p->addruninfo2(str);
	   m_Motor.wait_move_done(23);

	   m_Motor.Go_home(14);
	   str=(_T("1道直线电机A轴正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.Go_home(30);
	   str=(_T("2道直线电机A轴正在复位...."));
	   p->addruninfo2(str);


	   if (m_logic.go_home_stop)
	   {
		   return 0;
	   }
	   m_Motor.stop(MOTOR0);
	   m_Motor.WritePort_2(false,0,11,12,true);
	   m_Motor.WritePort_2(false,2,11,12,true);
	   m_Motor.Go_home(15);
	   str=(_T("1道直线电机B轴正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.Go_home(31);
	   str=(_T("2道直线电机B轴正在复位...."));
	   p->addruninfo2(str);

	   m_Motor.Go_home(4);
	   m_Motor.Go_home(5);
	   m_Motor.Go_home(6);

	   m_Motor.Go_home(8);
	   m_Motor.Go_home(9);
	   m_Motor.Go_home(10);


	   m_Motor.Go_home(20);
	   m_Motor.Go_home(21);
	   Sleep(1000);
	   m_Motor.Go_home(22);

	   m_Motor.Go_home(24);
	   m_Motor.Go_home(25);
	   m_Motor.Go_home(26);

	   m_Motor.wait_move_done(14);
	   m_Motor.wait_move_done(30);
	   m_Motor.wait_move_done(15);
	   m_Motor.wait_move_done(31);

	   str=(_T("1道载台A正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.wait_move_done(4);
	   m_Motor.wait_move_done(5);
	   m_Motor.wait_move_done(6);
	   m_Motor.reset_pos(4);
	   m_Motor.reset_pos(5);
	   m_Motor.reset_pos(6);
	   m_math.xxy_angle[0] = 0;
	   str=(_T("1道载台B正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.wait_move_done(8);
	   m_Motor.wait_move_done(9);
	   m_Motor.wait_move_done(10);
	   m_Motor.reset_pos(8);
	   m_Motor.reset_pos(9);
	   m_Motor.reset_pos(10);
	    m_math.xxy_angle[1] = 0;

	   str=(_T("2道载台A正在复位...."));
	   p->addruninfo2(str);
	   m_Motor.wait_move_done(20);
	   m_Motor.wait_move_done(21);
	   m_Motor.wait_move_done(22);
	   m_Motor.reset_pos(20);
	   m_Motor.reset_pos(21);
	   m_Motor.reset_pos(22);
	    m_math.xxy_angle[2] = 0;

	   str=(_T("2道载台B正在复位...."));
	   p->addruninfo2(str);
	   m_Motor.wait_move_done(24);
	   m_Motor.wait_move_done(25);
	   m_Motor.wait_move_done(26);
	   m_Motor.reset_pos(24);
	   m_Motor.reset_pos(25);
	   m_Motor.reset_pos(26);
	    m_math.xxy_angle[3] = 0;
	   if (m_logic.go_home_stop)
	   {
		   return 0;
	   }
	   m_Motor.WritePort_2(false,0,11,12,false);
	   m_Motor.WritePort_2(false,2,11,12,false);
	   m_Motor.reset_pos(1);
	   m_Motor.reset_pos(2);
	   m_Motor.reset_pos(17);
	   m_Motor.reset_pos(18);


	   m_Motor.absolute_move(1,PAIBAINHOME0);
	   m_Motor.absolute_move(2,PAIBAINHOME1);
	   m_Motor.absolute_move(17,PAIBAINHOME2);
	   m_Motor.absolute_move(18,PAIBAINHOME3);

	   str=(_T("1道电缸A正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.wait_move_done(1);
	   str=(_T("1道电缸B正在复位...."));
	   p->addruninfo1(str);
	   m_Motor.wait_move_done(2);
	   str=(_T("2道电缸A正在复位...."));
	   p->addruninfo2(str);
	   m_Motor.wait_move_done(17);
	   str=(_T("2道电缸B正在复位...."));
	   p->addruninfo2(str);
	   m_Motor.wait_move_done(18);
	   str=(_T("1道复位完成！"));
	   p->addruninfo1(str);
	   str=(_T("2道复位完成！"));
	   p->addruninfo2(str);

	   for (int k = 0;k<256;k++)
	   {
		   plc.m[k] =0;
		   plc.n[k] =0;
	   }
	   m_logic.reset = true;
	   m_logic.start = false;
	   mp->go_homeOK =true;
	   m_logic.firstAshangliaoOK =false;
	   mp->GetDlgItem(IDC_ALLGOHOME)->EnableWindow(true);
	   return 0;
 }
 UINT CMaincon::auto_xialiao(LPVOID param)
 {
	 return 0;
 }


void CMaincon::OnBnClickedStartshangliao()
{
	CButton *m_btn = (CButton*)GetDlgItem(IDC_STARTSHANGLIAO);
	CString str;
	m_btn->GetWindowText(str);
	if (str == _T("上料模块启动"))
	{
		m_logic.stop =false;
		m_logic.start = true;
		m_btn->SetWindowTextW(_T("上料模块停止"));
		CWinThread* m_run= AfxBeginThread(auto_run_shangliao, this,
			THREAD_PRIORITY_NORMAL,0,
			CREATE_SUSPENDED, NULL);
		m_run->ResumeThread();
	}
	else
	{
		m_logic.firstAshangliaoOK =false;
		Step[0]=0;
		m_btn->SetWindowTextW(_T("上料模块启动"));
		m_logic.stop =true;
		m_logic.start = false;
	}
}


void CMaincon::OnBnClickedCheckout8()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT8);
	bool ret = m_btn->GetCheck();
	m_Motor.WritePort(false,0,M8,ret);
}


void CMaincon::OnBnClickedCheckout9()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT9);
	bool ret = m_btn->GetCheck();
	m_Motor.WritePort(false,2,M8,ret);
}


void CMaincon::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent ==0)
	{
		CButton * m_btn;
		int ID1[] ={IDC_CHECKIN8,IDC_CHECKIN9,IDC_CHECKIN10,IDC_CHECKIN11,IDC_CHECKIN12};
		int ID2[] ={IDC_CHECKIN13,IDC_CHECKIN14,IDC_CHECKIN15,IDC_CHECKIN16,IDC_CHECKIN17};
		for (int k = 8;k<13;k++)
		{
			bool ret = m_Motor.ReadPort(false,true,0,k);
			m_btn = (CButton*)GetDlgItem(ID1[k-8]);
			m_btn->SetCheck(ret);
		}

		for (int k = 8;k<13;k++)
		{
			bool ret = m_Motor.ReadPort(false,true,2,k);
			m_btn = (CButton*)GetDlgItem(ID2[k-8]);
			m_btn->SetCheck(ret);
		}
	}
	if (nIDEvent ==1)
	{
		int ink_levle[4] ={0,0,0,0};
		m_XDM.getHeadInkLevels(1,ink_levle[0],ink_levle[1],ink_levle[2],ink_levle[3]);
		if (ink_levle[0]<103000)
		{
			m_Motor.WritePort_2(false,0,18,19,true);
		}
		else
		{
			m_Motor.WritePort_2(false,0,18,19,false);
			KillTimer(1);
		}
	}
	if (nIDEvent ==2)
	{
		int ink_levle[4] ={0,0,0,0};
		m_XDM.getHeadInkLevels(1,ink_levle[0],ink_levle[1],ink_levle[2],ink_levle[3]);
		if (1)//ink_levle[0]<103000)
		{
			m_Motor.WritePort_2(false,0,16,17,true);
		}
		else
		{
			m_Motor.WritePort_2(false,0,16,17,false);
			KillTimer(2);
		}
	}
	
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CMaincon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(0,500,0);
	updatapos();
	enablebutton(false);
	use1dao =true;
	use2dao =true;
	 use1daoA=true;
	 use1daoB=true;
	 use2daoA=true;
	 use2daoB=true;
	go_homeOK =false;
	CButton *m_btn = (CButton*)GetDlgItem(IDC_CHECKUSE1DAO);
	m_btn->SetCheck(use1dao);
	m_btn = (CButton*)GetDlgItem(IDC_CHECKUSE2DAO);
	m_btn->SetCheck(use2dao);
	m_btn = (CButton*)GetDlgItem(IDC_CHECK1A);
	m_btn->SetCheck(use1daoA);
	m_btn = (CButton*)GetDlgItem(IDC_CHECK1B);
	m_btn->SetCheck(use1daoB);
	m_btn = (CButton*)GetDlgItem(IDC_CHECK2A);
	m_btn->SetCheck(use2daoA);
	m_btn = (CButton*)GetDlgItem(IDC_CHECK2B);
	m_btn->SetCheck(use2daoB);
	m_btn = (CButton*)GetDlgItem(IDC_BOLI);
	
	m_Cam.Print_z = m_Cam.print_cameraz[0];
	isprint_boli = true;
	m_btn->SetCheck(isprint_boli);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMaincon::OnClose()
{
	KillTimer(0);

	CDialogEx::OnClose();
}


void CMaincon::OnBnClickedResetalarm()
{
	m_logic.reset = true;
}


void CMaincon::OnBnClickedStartprint()
{
	CButton *m_btn = (CButton*)GetDlgItem(IDC_STARTPRINT);
	CString str;
	m_btn->GetWindowText(str);
	if (str == _T("定位喷印模块启动"))
	{
		m_logic.stop =false;
		m_logic.start = true;
		m_btn->SetWindowTextW(_T("定位喷印模块停止"));
		CWinThread* m_run= AfxBeginThread(auto_get_camera_print, this,
			THREAD_PRIORITY_NORMAL,0,
			CREATE_SUSPENDED, NULL);
		m_run->ResumeThread();
	}
	else
	{
		Step[1]=0;
		m_btn->SetWindowTextW(_T("定位喷印模块启动"));
		m_logic.stop =true;
		m_logic.start = false;
	}
}


HBRUSH CMaincon::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	pDC->SetBkMode(TRANSPARENT);
	return theApp.m_brush;//hbr;
}
void CMaincon::updatapos()
{
	UpdateData(TRUE);
	 m_paibian0 = m_Motor.PAIBIANPOS[0];
	 m_paibian1 = m_Motor.PAIBIANPOS[1];
	 m_dengliao0 = m_Motor.DENGLIAOPOS[0];
	 m_dengliao1 = m_Motor.DENGLIAOPOS[1];
	 m_quliao0 = m_Motor.QULIAOPOS[0];
	 m_quliao1 = m_Motor.QULIAOPOS[1];
	 m_dingsheng0 = m_Motor.DINGSHENGPOS[0];
	 m_dingsheng1 = m_Motor.DINGSHENGPOS[1];
	 m_paizhao0 = m_Motor.PAIZHAOPOS[0];
	 m_paizhao1 = m_Motor.PAIZHAOPOS[1];
	 m_dayin0 = m_Motor.PRINTPOS[0];
	 m_dayin1 = m_Motor.PRINTPOS[1];
	 m_fangliao0 = m_Motor.FANGLIAOPOS[0];
	 m_fangliao1 = m_Motor.FANGLIAOPOS[1];
	 m_printok0 = m_Motor.PRINTOKPOS[0];
	 m_printok1 = m_Motor.PRINTOKPOS[1];
	 m_putdingshneg0 = m_Motor.PUTDINGSHENGPOS[0];
	 m_putdingsheng1 = m_Motor.PUTDINGSHENGPOS[1];
	 m_headtemp0 = m_Motor.headTemp[0];
	 m_headtemp1 = m_Motor.headTemp[1];
	 m_headtemp2 = m_Motor.headTemp[2];
	 m_headtempx = m_Motor.headTempX;
	 UpdateData(FALSE);
}

void CMaincon::OnBnClickedReadpaibianpos0()
{
	APS_get_position(MOTOR1,&m_Motor.PAIBIANPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadpaibianpos1()
{
	APS_get_position(MOTOR2,&m_Motor.PAIBIANPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReaddengliaopos0()
{
	APS_get_position(MOTOR14,&m_Motor.DENGLIAOPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReaddengliaopos1()
{
	APS_get_position(MOTOR15,&m_Motor.DENGLIAOPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadquliaopos0()
{
	APS_get_position(MOTOR14,&m_Motor.QULIAOPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadquliaopos1()
{
	APS_get_position(MOTOR15,&m_Motor.QULIAOPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReaddingshengpos0()
{
	APS_get_position(MOTOR3,&m_Motor.DINGSHENGPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReaddingshengpos1()
{
	APS_get_position(MOTOR7,&m_Motor.DINGSHENGPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadgrbgpos0()
{
	APS_get_position(MOTOR14,&m_Motor.PAIZHAOPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadgrbgpos1()
{
	APS_get_position(MOTOR15,&m_Motor.PAIZHAOPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadprintpos0()
{
	APS_get_position(MOTOR14,&m_Motor.PRINTPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadprintpos1()
{
	APS_get_position(MOTOR15,&m_Motor.PRINTPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadputpos0()
{
	APS_get_position(MOTOR14,&m_Motor.FANGLIAOPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadputpos1()
{
	APS_get_position(MOTOR15,&m_Motor.FANGLIAOPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedCheckout10()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT10);
	bool ret = m_btn->GetCheck();
	m_Motor.WritePort(false,0,M9,ret);
}


void CMaincon::OnBnClickedCheckout11()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT11);
	bool ret = m_btn->GetCheck();
	m_Motor.WritePort(false,0,M10,ret);
}


void CMaincon::OnBnClickedCheckout12()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT12);
	bool ret = m_btn->GetCheck();
	m_Motor.WritePort(false,2,M9,ret);
}


void CMaincon::OnBnClickedCheckout13()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT13);
	bool ret = m_btn->GetCheck();
	m_Motor.WritePort(false,2,M10,ret);
}


void CMaincon::OnBnClickedStop()
{
	m_logic.stop =true;
	m_logic.start =false;
	m_logic.go_home_stop =true;
	for (int k = 0;k<MOTOR_NUM;k++)
	{
		m_Motor.stop(k);
	}
	go_homeOK =false;
	GetDlgItem(IDC_ALLGOHOME)->EnableWindow(true);
	CButton *m_btn = (CButton*)GetDlgItem(IDC_STARTXIALIAO);
	m_btn->SetWindowTextW(_T("启动"));
	con_enablebutton(true);
}


void CMaincon::OnBnClickedAllgohome()
{
	CButton *m_btn = (CButton*)GetDlgItem(IDC_ALLGOHOME);
	CString str;
	m_btn->GetWindowText(str);
	m_logic.go_home_stop =false;
	if (str == _T("设备复位"))
	{
		m_logic.stop =false;
		//m_btn->SetWindowTextW(_T("停止复位"));
		GetDlgItem(IDC_ALLGOHOME)->EnableWindow(false);
		CWinThread* m_run= AfxBeginThread(auto_go_home, this,
			THREAD_PRIORITY_NORMAL,0,
			CREATE_SUSPENDED, NULL);
		m_run->ResumeThread();
	}
	else
	{  

	//	m_logic.stop =true;
	//	m_logic.start = false;
	}
}


void CMaincon::OnBnClickedStart()
{
	GetDlgItem(IDC_ALLGOHOME)->EnableWindow(false);
}


void CMaincon::OnBnClickedChangepos()
{
	Cpassword dlg;

	if (IDOK ==dlg.DoModal() )
	{
		if (dlg.m_password ==_T("8888"))
		{
          enablebutton(true);
		}
		else
		{
			MessageBox(_T("密码错误！"),_T(""),MB_ICONERROR);
		}
	}
}
void CMaincon::con_enablebutton(bool ret)
{
	GetDlgItem(IDC_ALLGOHOME)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKOUT8)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKOUT9)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKOUT10)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKOUT11)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKOUT12)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKOUT13)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKOUT14)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKUSE1DAO)->EnableWindow(ret);
	GetDlgItem(IDC_CHECKUSE2DAO)->EnableWindow(ret);
	GetDlgItem(IDC_CHECK1A)->EnableWindow(ret);
	GetDlgItem(IDC_CHECK1B)->EnableWindow(ret);
	GetDlgItem(IDC_CHECK2A)->EnableWindow(ret);
	GetDlgItem(IDC_CHECK2B)->EnableWindow(ret);
}
void CMaincon::enablebutton(bool ret)
{
	GetDlgItem(IDC_READPAIBIANPOS0)->EnableWindow(ret);
	GetDlgItem(IDC_READPAIBIANPOS1)->EnableWindow(ret);

	GetDlgItem(IDC_READDENGLIAOPOS0)->EnableWindow(ret);
	GetDlgItem(IDC_READDENGLIAOPOS1)->EnableWindow(ret);

	GetDlgItem(IDC_READQULIAOPOS0)->EnableWindow(ret);
	GetDlgItem(IDC_READQULIAOPOS1)->EnableWindow(ret);

	GetDlgItem(IDC_READDINGSHENGPOS0)->EnableWindow(ret);
	GetDlgItem(IDC_READDINGSHENGPOS1)->EnableWindow(ret);

	GetDlgItem(IDC_READGRBGPOS0)->EnableWindow(ret);
	GetDlgItem(IDC_READGRBGPOS1)->EnableWindow(ret);

	GetDlgItem(IDC_READPRINTPOS0)->EnableWindow(ret);
	GetDlgItem(IDC_READPRINTPOS1)->EnableWindow(ret);

	GetDlgItem(IDC_READPUTPOS0)->EnableWindow(ret);
	GetDlgItem(IDC_READPUTPOS1)->EnableWindow(ret);

	GetDlgItem(IDC_READPRINTOK0)->EnableWindow(ret);
	GetDlgItem(IDC_READPRINTOK1)->EnableWindow(ret);

	GetDlgItem(IDC_READPUTDINGSHENG0)->EnableWindow(ret);
	GetDlgItem(IDC_READPUTDINGSHENG1)->EnableWindow(ret);

}

void CMaincon::OnBnClickedChangepos2()
{
	m_Motor.savepos();
	updatapos();
	enablebutton(false);
}


void CMaincon::OnBnClickedReadputdingsheng1()
{
	APS_get_position(MOTOR7,&m_Motor.PUTDINGSHENGPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadprintok0()
{
	APS_get_position(MOTOR14,&m_Motor.PRINTOKPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadprintok1()
{
	APS_get_position(MOTOR15,&m_Motor.PRINTOKPOS[1]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedReadputdingsheng0()
{
	APS_get_position(MOTOR3,&m_Motor.PUTDINGSHENGPOS[0]);
	m_Motor.savepos();
	updatapos();
}


void CMaincon::OnBnClickedCheckout14()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT14);
	bool ret = m_btn->GetCheck();
	m_Motor.WritePort(false,0,M13,ret);
}


void CMaincon::OnBnClickedStartxialiao()
{
	CString str;
	if (isprint_boli)
	{
		str = _T("确定打印基材是玻璃吗？");
	}
	else
	{
		str = _T("确定打印基材是硅片吗？");
	}
	if (IDCANCEL ==MessageBox(str,_T("注意"),MB_OKCANCEL) )
	{
		return;
	}
	else
	{	
	CLMCappApp* pApp=(CLMCappApp*)AfxGetApp();  

	CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	ASSERT_KINDOF(CMainFrame, pAppFrame);
	CLMCappView *p=(CLMCappView *) pAppFrame->GetActiveView();
	str.Format(_T("%d"),m_Cam.Print_z);
	p->addruninfo1(str);

	}
	
	if (!go_homeOK)
	{
		MessageBox(_T("设备未复位"));
		return ;
	}
	CButton *m_btn = (CButton*)GetDlgItem(IDC_STARTXIALIAO);
	m_btn->GetWindowText(str);
	if (str == _T("启动"))
	{
		con_enablebutton(false);
		m_logic.stop =false;
		m_logic.start = true;
		m_btn->SetWindowTextW(_T("暂停"));
		CWinThread* m_run= AfxBeginThread(auto_run_1B, this,
			THREAD_PRIORITY_NORMAL,0,
			CREATE_SUSPENDED, NULL);
		m_run->ResumeThread();
	}
	else
	{
		Step[1]=0;
		m_btn->SetWindowTextW(_T("启动"));
		m_logic.stop =true;
		m_logic.start = false;
		con_enablebutton(true);
	}
}


void CMaincon::OnBnClickedStartxialiao2()
{
	CButton *m_btn = (CButton*)GetDlgItem(IDC_STARTXIALIAO2);
	CString str;
	m_btn->GetWindowText(str);
	if (str == _T("测试B启动"))
	{
		m_logic.stop =false;
		m_logic.start = true;
		m_btn->SetWindowTextW(_T("测试B停止"));
		CWinThread* m_run= AfxBeginThread(CESHI, this,
			THREAD_PRIORITY_NORMAL,0,
			CREATE_SUSPENDED, NULL);
		m_run->ResumeThread();
	}
	else
	{
		Step[1]=0;
		m_btn->SetWindowTextW(_T("测试B启动"));
		m_logic.stop =true;
		m_logic.start = false;
	}
}
UINT CMaincon::CESHI(LPVOID param)
{
	//CMaincon * m_con = (CMaincon*)param;
	//CLMCappApp* pApp=(CLMCappApp*)AfxGetApp();  

	//CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	//ASSERT_KINDOF(CMainFrame, pAppFrame);
	//CLMCappView *p=(CLMCappView *) pAppFrame->GetActiveView();
	//p->addruninfo2(_T("载台B启动！"));
	//plc.n[100] =m_logic.start;//------------开始
	//plc.n[101] = m_logic.stop;//------------停止
	//plc.n[102] = m_logic.reset;//-----------复位
	//plc.n[103] = m_logic.alarm;//-----------报警
	//plc.n[105] = 1;//-----------------------常通信号
	//plc.LD(0,100,N);plc.ANDI(0,101,N);plc.ANDI(0,103,N);plc.Out(0,104,N);//M104启动保持信号

	//while(plc.n[104])
	//{
	//	plc.n[100] =m_logic.start;//------------开始
	//	plc.n[101] = m_logic.stop;//------------停止
	//	plc.n[102] = m_logic.reset;//-----------复位
	//	plc.n[103] = m_logic.alarm;//-----------报警
	//	plc.n[105] = 1;//-----------------------常通信号
	//	plc.LD(0,100,N);plc.ANDI(0,101,N);plc.ANDI(0,103,N);plc.Out(0,104,N);//M104启动保持信号

	//	plc.ANDI(2,10,X);plc.AND(2,11,X);plc.AND(0,104,N);plc.ANDI(0,1,N);plc.ANDI(0,60,N);plc.ANDI(0,61,N);plc.ANDI(0,151,N);plc.ANDI(0,50,N);plc.SET(0,0,N);
	//	plc.SET(0,151,N);

	//	plc.LD(0,0,N);plc.AND(0,104,N);plc.SET(0,1,N);
	//	plc.RSET(0,0,N);
	//	plc.PULS(2,MOTOR0+16,0,-m_Motor.move_maxspeed[MOTOR0+16]);//送料
	//	// Sleep(5);
	//	plc.LD(2,10,X);plc.AND(0,1,N);plc.SET(0,3,N);
	//	plc.LD(0,3,N);plc.RSET(0,1,N);
	//	plc.RSET(0,3,N);
	//	plc.SET(0,4,N);//送料到位              
	//	plc.SET(0,50,N);//屏蔽上料
	//	plc.LD(0,4,N);plc.STOP(MOTOR0+16);
	//	plc.SET(0,61,N);//B载台使用信号
	//	plc.LD(0,4,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR0+16);plc.SET(0,5,N);//拍边信号
	//	plc.RSET(0,4,N);

	//	plc.SET(0,5,N);plc.AND(0,104,N);plc.SET(0,6,N);
	//	plc.RSET(0,5,N);
	//	plc.PULS(0,MOTOR2+16,m_Motor.PAIBIANPOS[1],0);
	//	//Sleep(5);
	//	plc.LD(0,6,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR2+16);plc.RSET(0,6,N);
	//	plc.SET(0,7,N);//拍边张开

	//	plc.LD(0,7,N);                 plc.SET(0,8,N);
	//	plc.RSET(0,7,N);
	//	plc.PULS(0,MOTOR2+16,PAIBAINHOME1,0);
	//	// Sleep(5);
	//	plc.LD(0,8,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR2+16);plc.RSET(0,8,N);
	//	plc.SET(0,9,N);//直线电机16来接料


	//	plc.LD(0,9,N); plc.GETPEL(MOTOR7+16);plc.Out(0,55,N);//检测顶升电机是否在原点；
	//	plc.LD(0,105,N);plc.GetPOS(MOTOR14+16,plc.d[30]);
	//	plc.LD(0,9,N); plc.AND(0,104,N);plc.LD(0,55,N); plc.AND(0,201,N); plc.ANDI(0,51,N);plc.SET(0,10,N);
	//	plc.RSET(0,9,N);
	//	plc.PULS(0,MOTOR15+16,m_Motor.QULIAOPOS[1],0);
	//	plc.SET(0,51,N);//屏蔽取料
	//	plc.SET(0,202,N);//反向运动；
	//	//	Sleep(5);
	//	plc.LD(0,9,N); plc.AND(0,104,N);plc.LD(0,55,N); plc.CMP(2,plc.d[30],m_Motor.QULIAOPOS[0]);plc.ANDI(0,201,N);plc.ANDI(0,203,N); plc.ANDI(0,51,N);plc.SET(0,10,N);
	//	plc.RSET(0,9,N);
	//	plc.PULS(0,MOTOR15+16,m_Motor.QULIAOPOS[1],0);
	//	plc.SET(0,51,N);//屏蔽取料
	//	plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
	//	plc.LD(0,10,N);plc.CMP(2,plc.d[31],m_Motor.PRINTOKPOS[1]);plc.PULS(0,MOTOR7+16,0,0);

	//	plc.LD(0,10,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.AXIS_DONE(MOTOR7+16);plc.SET(0,11,N);
	//	plc.RSET(0,10,N);//开始顶升
	//	plc.RSET(0,202,N);//反向运动；

	//	plc.LD(0,11,N); plc.AND(0,104,N);plc.SET(0,12,N); //电磁阀吸附信号
	//	plc.RSET(0,11,N);
	//	plc.PULS(0,MOTOR7+16,m_Motor.DINGSHENGPOS[1],0);
	//	//	 Sleep(5);
	//	plc.LD(0,12,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR7+16);plc.SET(2,10,Y); //电磁阀吸附信号
	//	plc.SET(0,13,N);//去拍照位置;
	//	plc.RSET(0,12,N);
	//	plc.LD(0,13,N); plc.AND(0,104,N);plc.SET(0,14,N); //直线电机16去拍照位置
	//	plc.RSET(0,13,N);
	//	plc.PULS(0,MOTOR15+16,m_Motor.PAIZHAOPOS[1],0);	

	//	//	 Sleep(5);

	//	plc.LD(0,14,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.SET(0,15,N); //直线电机16拍照
	//	plc.RSET(0,14,N);
	//	plc.RSET(0,50,N);//解除屏蔽上料
	//	if(plc.n[15])
	//	{
	//		plc.RSET(0,15,N);
	//		int count = 0;
	//		int ret =false;
	//		while(++count<5&&ret!=1)
	//		{
	//			ret = m_con->xxy_move(3);//载台1;
	//			if (ret==0)
	//			{
	//				//break;
	//			}
	//		}

	//		plc.SET(0,152,N);
	//	}
	//	plc.LD(0,152,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.SET(0,16,N); 
	//	plc.RSET(0,152,N);
	//	plc.PULS(0,MOTOR15+16,m_Motor.FANGLIAOPOS[1],0);
	//	plc.SET(0,200,N);//直线电机16 开始正向移动；
	//	//		 Sleep(5);

	//	plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
	//	plc.LD(0,16,N); plc.AND(0,104,N);plc.CMP(1,plc.d[31],m_Motor.PRINTOKPOS[1]);plc.SET(0,17,N); 
	//	plc.RSET(0,16,N);
	//	plc.PULS(0,MOTOR7+16,m_Motor.PUTDINGSHENGPOS[1],0);
	//	//  Sleep(5);

	//	plc.LD(0,17,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR7+16);plc.SET(0,18,N);
	//	plc.RSET(0,17,N);
	//	// plc.PULS(0,NOTOR15,N_Motor.FANGLIAOPOS[1],0);
	//	// Sleep(50);
	//	plc.LD(0,18,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR15+16);plc.SET(0,19,N);
	//	plc.RSET(2,10,Y); //电磁阀吸附信号
	//	plc.RSET(0,18,N);
	//	plc.PULS(0,MOTOR7+16,0,0);
	//	plc.RSET(0,200,N);//直线电机16 开始正向移动；
	//	//   Sleep(5);
	//	plc.LD(0,19,N);plc.AXIS_DONE(MOTOR7+16);plc.GETPEL(MOTOR7+16);plc.SET(0,20,N);
	//	plc.RSET(0,19,N);
	//	plc.PULS(1,MOTOR13+16,40000,0);
	//	plc.RSET(0,51,N);//解除屏蔽取料；
	//	//	Sleep(5);
	//	//----------------------------------------------以上为载台B,以下为载台A M60 开始
	//	plc.LD(0,61,N);plc.ANDI(0,60,N);plc.ANDI(0,150,N);plc.ANDI(2,9,X);plc.SET(0,62,N);
	//	plc.SET(2,8,Y);
	//	plc.SET(0,150,N);
	//	plc.LD(0,62,N);plc.AND(0,104,N);plc.AND(2,12,X);plc.RSET(0,62,N);
	//	plc.SET(0,63,N);//送料
	//	plc.PULS(2,MOTOR0+16,0,-m_Motor.move_maxspeed[MOTOR0+16]);
	//	plc.LD(0,63,N);plc.AND(2,9,X);plc.STOP(MOTOR0+16);
	//	plc.RSET(0,63,N);
	//	plc.SET(0,64,N);
	//	plc.RSET(2,8,Y);
	//	plc.SET(0,60,N);//A送料到位
	//	plc.LD(0,64,N);plc.AND(0,104,N);plc.AND(2,11,X);plc.AXIS_DONE(MOTOR0+16);plc.SET(0,65,N);
	//	plc.RSET(0,64,N);
	//	plc.LD(0,65,N);plc.AND(0,104,N);plc.SET(0,66,N);
	//	plc.RSET(0,65,N);
	//	plc.PULS(0,MOTOR1+16,m_Motor.PAIBIANPOS[0],0);
	//	plc.LD(0,66,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR1+16);plc.SET(0,67,N);
	//	plc.RSET(0,66,N);

	//	plc.LD(0,67,N);plc.AND(0,104,N);plc.SET(0,68,N);
	//	plc.RSET(0,67,N);
	//	plc.PULS(0,	MOTOR1+16,PAIBAINHOME0,0);
	//	plc.LD(0,68,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR1+16);plc.SET(0,69,N);
	//	plc.RSET(0,68,N);
	//	plc.LD(0,69,N); plc.GETPEL(MOTOR3+16);plc.Out(0,56,N);//检测顶升电机是否在原点；
	//	plc.LD(0,69,N); plc.AND(0,104,N);plc.LD(0,56,N); plc.ANDI(0,91,N);plc.SET(0,70,N);
	//	plc.RSET(0,69,N);
	//	plc.PULS(0,MOTOR14+16,m_Motor.QULIAOPOS[0],0);
	//	plc.SET(0,91,N);//屏蔽取料
	//	plc.SET(0,201,N);//反向运动
	//	plc.LD(0,105,N);plc.GetPOS(MOTOR14+16,plc.d[30]);
	//	plc.LD(0,70,N);plc.CMP(2,plc.d[30],m_Motor.PRINTOKPOS[0]);plc.PULS(0,MOTOR3+16,0,0);

	//	plc.LD(0,70,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.AXIS_DONE(MOTOR3+16);plc.SET(0,71,N);
	//	plc.RSET(0,70,N);//开始顶升
	//	plc.RSET(0,201,N);//反向运动
	//	plc.LD(0,71,N); plc.AND(0,104,N);plc.SET(0,72,N); //电磁阀吸附信号
	//	plc.RSET(0,71,N);
	//	plc.PULS(0,MOTOR3+16,m_Motor.DINGSHENGPOS[0],0);
	//	plc.LD(0,72,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR3+16);plc.SET(2,9,Y); //电磁阀吸附信号
	//	plc.SET(0,73,N);//去拍照位置;
	//	plc.RSET(0,72,N);
	//	plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
	//	plc.LD(0,73,N); plc.AND(0,104,N);plc.CMP(1,plc.d[31],m_Motor.PAIZHAOPOS[1]+200000);plc.AND(0,200,N);plc.ANDI(0,202,N);plc.SET(0,74,N); //直线电机15去拍照位置
	//	plc.RSET(0,73,N);
	//	plc.PULS(0,MOTOR14+16,m_Motor.PAIZHAOPOS[0],0);
	//	plc.SET(0,203,N);
	//	//	 Sleep(5);
	//	plc.LD(0,73,N); plc.AND(0,104,N);plc.CMP(0,plc.d[31],m_Motor.FANGLIAOPOS[1]);plc.ANDI(0,200,N);plc.ANDI(0,202,N);plc.SET(0,74,N); //直线电机15去拍照位置
	//	plc.RSET(0,73,N);
	//	plc.PULS(0,MOTOR14+16,m_Motor.PAIZHAOPOS[0],0);	
	//	plc.SET(0,203,N);
	//	plc.LD(0,74,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.SET(0,75,N); //直线电机15拍照
	//	plc.RSET(0,74,N);
	//	plc.RSET(0,60,N);//解除屏蔽上料
	//	plc.RSET(0,61,N);//解除屏蔽上料
	//	plc.RSET(0,150,N);//解除屏蔽上料
	//	plc.RSET(0,151,N);//解除屏蔽上料
	//	if(plc.n[75])
	//	{
	//		plc.RSET(0,75,N);
	//		int count = 0;
	//		int ret =false;
	//		while(++count<5&&ret!=1)
	//		{
	//			ret = m_con->xxy_move(2);//载台1;
	//			if (ret==0)
	//			{
	//				//break;
	//			}
	//		}

	//		plc.SET(0,76,N);
	//		//-----添加ccd代码
	//	}
	//	plc.LD(0,105,N);plc.GetPOS(MOTOR15+16,plc.d[31]);
	//	plc.LD(0,76,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.CMP(1,plc.d[31],m_Motor.PRINTOKPOS[1]+200000);plc.AND(0,200,N);plc.SET(0,77,N); 
	//	plc.RSET(0,76,N);
	//	plc.PULS(0,MOTOR14+16,m_Motor.FANGLIAOPOS[0],0);
	//	plc.SET(0,203,N);

	//	//Sleep(5);
	//	plc.LD(0,76,N); plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.CMP(0,plc.d[31],m_Motor.FANGLIAOPOS[1]);plc.ANDI(0,200,N);plc.ANDI(0,202,N);plc.SET(0,77,N); 
	//	plc.RSET(0,76,N);
	//	plc.PULS(0,MOTOR14+16,m_Motor.FANGLIAOPOS[0],0);
	//	plc.SET(0,203,N);
	//	plc.LD(0,105,N);plc.GetPOS(MOTOR14+16,plc.d[30]);
	//	plc.LD(0,77,N); plc.AND(0,104,N);plc.CMP(1,plc.d[30],m_Motor.PRINTOKPOS[0]);plc.SET(0,78,N); 
	//	plc.RSET(0,77,N);
	//	plc.PULS(0,MOTOR3+16,m_Motor.PUTDINGSHENGPOS[0],0);

	//	plc.LD(0,78,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR3+16);plc.SET(0,79,N);
	//	plc.RSET(0,78,N);
	//	// plc.PULS(0,NOTOR15,N_Motor.FANGLIAOPOS[1],0);
	//	// Sleep(50);
	//	plc.LD(0,79,N);plc.AND(0,104,N);plc.AXIS_DONE(MOTOR14+16);plc.SET(0,80,N);
	//	plc.RSET(2,9,Y); //电磁阀吸附信号
	//	plc.RSET(0,79,N);
	//	plc.PULS(0,MOTOR3+16,0,0);
	//	plc.RSET(0,203,N);
	//	//   Sleep(5);
	//	plc.LD(0,80,N);plc.AXIS_DONE(MOTOR3+16);plc.GETPEL(MOTOR3+16);plc.SET(0,87,N);
	//	plc.RSET(0,80,N);
	//	plc.PULS(1,MOTOR13+16,40000,0);
	//	plc.RSET(0,91,N);//解除屏蔽取料；

	//}
	//p->addruninfo2(_T("载台B停止！"));
	return 0;
}
int CMaincon::xxy_move(int id)
{
	m_Cam.sunny_angle = 0;
	m_Cam.sunny_center_column = 0;
	m_Cam.sunny_center_row =0;
	if(id ==0||id==1)
	    m_Cam.OnSendSoftCommand(0);
	else
		m_Cam.OnSendSoftCommand(1);

	//if (!m_Cam.sunny_measure())
	if (!m_Cam.czrs_measure())
	{
		return 0;
	}
	else
	{
		double a = abs(m_math.angle(m_Cam.sunny_angle));
		if (a>0.005)
		{
			long x1,x2,y;
			m_math.get_x0_x1_x2_POS(id,m_Cam.sunny_angle,x1,x2,y);	
			switch(id)
			{
			case 0:
				m_Motor.mul_real_move(4,x1,5,x2,6,y);
				break;
			case 1:
				m_Motor.mul_real_move(8,x1,9,x2,10,y);
				break;
			}
			
			return 2;//在调整
		}
		else
		{
			return 1;//调整OK
		}
	}
}

void CMaincon::OnBnClickedCheckuse1dao()
{
	CButton *m_btn = (CButton*)GetDlgItem(IDC_CHECKUSE1DAO);
	int ret = m_btn->GetCheck();
	use1dao = ret;
}


void CMaincon::OnBnClickedCheckuse2dao()
{
	CButton *m_btn = (CButton*)GetDlgItem(IDC_CHECKUSE2DAO);
	int ret = m_btn->GetCheck();
	use2dao = ret;
}


void CMaincon::OnBnClickedGopaibianpos0()
{
	m_Motor.absolute_move(MOTOR1,m_Motor.PAIBIANPOS[0]);
	m_Motor.wait_move_done(MOTOR1);
}


void CMaincon::OnBnClickedGopaibianpos1()
{
	m_Motor.absolute_move(MOTOR2,m_Motor.PAIBIANPOS[1]);
	m_Motor.wait_move_done(MOTOR2);
}


void CMaincon::OnBnClickedGodengliaopos20()
{
	m_Motor.absolute_move(MOTOR14,m_Motor.DENGLIAOPOS[0]);
	m_Motor.wait_move_done(MOTOR14);
}


void CMaincon::OnBnClickedGodengliaopos21()
{
	m_Motor.absolute_move(MOTOR15,m_Motor.DENGLIAOPOS[1]);
	m_Motor.wait_move_done(MOTOR15);
}


void CMaincon::OnBnClickedGoquliaopos0()
{
	m_Motor.absolute_move(MOTOR14,m_Motor.QULIAOPOS[0]);
	m_Motor.wait_move_done(MOTOR14);
}


void CMaincon::OnBnClickedGoquliaopos1()
{
	m_Motor.absolute_move(MOTOR15,m_Motor.QULIAOPOS[1]);
	m_Motor.wait_move_done(MOTOR15);
}


void CMaincon::OnBnClickedGodingshengpos0()
{
	m_Motor.absolute_move(MOTOR3,m_Motor.DINGSHENGPOS[0]);
	m_Motor.wait_move_done(MOTOR3);
}


void CMaincon::OnBnClickedGodingshengpos1()
{
	m_Motor.absolute_move(MOTOR7,m_Motor.DINGSHENGPOS[1]);
	m_Motor.wait_move_done(MOTOR7);
}


void CMaincon::OnBnClickedGogrbgpos0()
{
	m_Motor.absolute_move(MOTOR14,m_Motor.PAIZHAOPOS[0]);
	m_Motor.wait_move_done(MOTOR14);
}


void CMaincon::OnBnClickedGogrbgpos1()
{
	m_Motor.absolute_move(MOTOR15,m_Motor.PAIZHAOPOS[1]);
	m_Motor.wait_move_done(MOTOR15);
}


void CMaincon::OnBnClickedGoprintpos0()
{
	m_Motor.absolute_move(MOTOR14,m_Motor.PRINTPOS[0]);
	m_Motor.wait_move_done(MOTOR14);
}


void CMaincon::OnBnClickedGoprintpos1()
{
	m_Motor.absolute_move(MOTOR15,m_Motor.PRINTPOS[1]);
	m_Motor.wait_move_done(MOTOR15);
}


void CMaincon::OnBnClickedGoputpos0()
{
	m_Motor.absolute_move(MOTOR14,m_Motor.FANGLIAOPOS[0]);
	m_Motor.wait_move_done(MOTOR14);
}


void CMaincon::OnBnClickedGoputpos1()
{
	m_Motor.absolute_move(MOTOR15,m_Motor.FANGLIAOPOS[1]);
	m_Motor.wait_move_done(MOTOR15);
}


void CMaincon::OnBnClickedGoprintok0()
{
	m_Motor.absolute_move(MOTOR14,m_Motor.PRINTOKPOS[0]);
	m_Motor.wait_move_done(MOTOR14);
}


void CMaincon::OnBnClickedGoprintok1()
{
	m_Motor.absolute_move(MOTOR15,m_Motor.PRINTOKPOS[1]);
	m_Motor.wait_move_done(MOTOR15);
}


void CMaincon::OnBnClickedGoputdingsheng0()
{
	m_Motor.absolute_move(MOTOR3,m_Motor.PUTDINGSHENGPOS[0]);
	m_Motor.wait_move_done(MOTOR3);
}


void CMaincon::OnBnClickedGoputdingsheng1()
{
	m_Motor.absolute_move(MOTOR7,m_Motor.PUTDINGSHENGPOS[1]);
	m_Motor.wait_move_done(MOTOR7);
}


void CMaincon::OnBnClickedCheck1a()
{
	CButton*m_btn = (CButton*)GetDlgItem(IDC_CHECK1A);
	BOOL RET = m_btn->GetCheck();
	use1daoA = RET;
}


void CMaincon::OnBnClickedCheck1b()
{
	CButton*m_btn = (CButton*)GetDlgItem(IDC_CHECK1B);
	BOOL RET = m_btn->GetCheck();
	use1daoB = RET;
}


void CMaincon::OnBnClickedCheck2a()
{
	CButton*m_btn = (CButton*)GetDlgItem(IDC_CHECK2A);
	BOOL RET = m_btn->GetCheck();
	use2daoA = RET;
}


void CMaincon::OnBnClickedCheck2b()
{
	CButton*m_btn = (CButton*)GetDlgItem(IDC_CHECK2B);
	BOOL RET = m_btn->GetCheck();
	use2daoB = RET;
}


void CMaincon::OnBnClickedCheckout15()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT15);
	bool ret = m_btn->GetCheck();
	if(ret)
	{
		SetTimer(1,100,0);
	}
	else
	{  
		KillTimer(1);
		m_Motor.WritePort_2(false,0,18,19,false);
	}
	
}


void CMaincon::OnBnClickedCheckout16()
{
	CButton * m_btn = (CButton*)GetDlgItem(IDC_CHECKOUT16);
	bool ret = m_btn->GetCheck();
	if(ret)
	{
		SetTimer(2,1000,0);
	}
	else
	{  
		KillTimer(2);
		m_Motor.WritePort_2(false,0,16,17,false);
	}
}


void CMaincon::OnBnClickedBoli()
{
	isprint_boli =true;
	m_Cam.Print_z = m_Cam.print_cameraz[0];
}


void CMaincon::OnBnClickedGuipian()
{
	isprint_boli =false;
	m_Cam.Print_z = m_Cam.print_cameraz[1];
}


void CMaincon::OnBnClickedChangepos3()
{
	UpdateData(TRUE);
	 m_Motor.headTemp[0] = m_headtemp0;
	 m_Motor.headTemp[1] = m_headtemp1;
	 m_Motor.headTemp[2] = m_headtemp2;
	 m_Motor.headTempX = m_headtempx;
	 UpdateData(FALSE);
	 m_Motor.savepos();
}
