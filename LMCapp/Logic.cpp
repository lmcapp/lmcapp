// Logic.cpp : 实现文件
//

#include "stdafx.h"
#include "LMCapp.h"
#include "Logic.h"


// CLogic

IMPLEMENT_DYNAMIC(CLogic, CWnd)

CLogic::CLogic()
{
	alarm = false;
	close = false;
	for (int k = 0; k<MOTOR_NUM;k++)
	{
		SVON[k] =false;
	}
	firstAshangliaoOK=false;
	firstBshangliaoOK=false;
	secondAshangliaoOK=false;
	secondBshangliaoOK=false;
	isPaibianReady =false;
	isCameraReady = false;
	go_home_stop =false;
	 	CWinThread* checkalarm= AfxBeginThread(Check_Alarm, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	 checkalarm->ResumeThread();
}

CLogic::~CLogic()
{
}


BEGIN_MESSAGE_MAP(CLogic, CWnd)
END_MESSAGE_MAP()



// CLogic 消息处理程序

bool CLogic::Ld(UINT CardID,UINT IO)
{
 return	m_Motor.ReadPort(false,true,CardID,IO);
}
bool CLogic::LdN(UINT CardID,UINT IO)
{
 return	!m_Motor.ReadPort(false,true,CardID,IO);
}
void CLogic::Set(UINT CardID,UINT IO)
{
	m_Motor.WritePort(false,CardID,IO,true);
}
void CLogic::Reset(UINT CardID,UINT IO)
{
	m_Motor.WritePort(false,CardID,IO,false);
}
void CLogic::T(UINT delay_val)
{
	Sleep(delay_val);
}
void CLogic::ResetT(bool t_val)
{
	t_val = false;
}
 bool CLogic::readout(UINT CardID,UINT IO)
 {
  return	m_Motor.ReadPort(false,false,CardID,IO);
 }
 bool CLogic::m_alarm(UINT CardID1,UINT out1,UINT CardID2,UINT in2,UINT CardID3,UINT in3)
 {
	 return((readout(CardID1,out1)&&Ld(CardID2,in2))||(readout(CardID1,out1)&&!Ld(CardID3,in3))
		 ||((!readout(CardID1,out1)&&!Ld(CardID2,in2)))||((!readout(CardID1,out1)&&Ld(CardID3,in3))));	
 }
 bool CLogic::sp_alarm(UINT CardID1,UINT out1,UINT CardID2,UINT in2 )
 {
	 return((readout(CardID1,out1)&&Ld(CardID2,in2))
		 ||((!readout(CardID1,out1)&&!Ld(CardID2,in2))));	
 }
UINT CLogic::Check_Alarm(LPVOID param)
{
	int a1 = 0;
	int a2 = 0;
	int a3 = 0;
	int a4 = 0;
	int a5 = 0;
	int a6 = 0;
	int a7 = 0;
	int a8 = 0;
	int a9 = 0;
	int a10 = 0;
	int a11 = 0;
	int a12 =0;
	int a13 = 0;
	int ret =0;
	CLogic *p = (CLogic *)param;
	while (!p->close)
	{
		//_________________检测挡料气缸报警
		if(p->m_alarm(0,M8,0,P11,0,P12))			
		{
			a1++;
			if (a1>Alarm_Time)
			{
				p->alarm =true;
				p->A0 =TRUE;
			}
		}
		else
		{
			a1=0;
		}
		//_________________检测挡料气缸报警
	if(p->m_alarm(2,M8,2,P11,2,P12))					
		{
			a2++;
			if (a2>Alarm_Time)
			{
				p->alarm =true;
				p->A1 =TRUE;
			}
		}
		else
		{
			a2=0;
		}
		//_________________检测气缸报警
  //     if(p->m_alarm(0,M10,0,P12,0,P11))				
		//{
		//	a3++;
		//	if (a3>Alarm_Time)
		//	{
		//		p->alarm =true;
		//		p->A2 =TRUE;
		//	}
		//}
		//else
		//{
		//	a3=0;
		//}
	   //_________________检测气缸报警
	   //if(p->m_alarm(0,M11,0,P21,0,P20))				
	   //{
		  // a4++;
		  // if (a4>Alarm_Time)
		  // {
			 //  p->alarm =true;
			 //  p->A3 =TRUE;
		  // }
	   //}
	   //else
	   //{
		  // a4=0;
	   //}
	   //_________________检测气缸报警//拍边12
	   //if(p->m_alarm(0,M11,0,P22,0,P23))				
	   //{
		  // a5++;
		  // if (a5>Alarm_Time)
		  // {
			 //  p->alarm =true;
			 //  p->A4 =TRUE;
		  // }
	   //}
	   //else
	   //{
		  // a5=0;
	   //}
	   ////_________________检测气缸报警
	   //if(p->m_alarm(0,M12,0,P19,0,P18))	//拍边34			
	   //{
		  // a6++;
		  // if (a6>Alarm_Time)
		  // {
			 //  p->alarm =true;
			 //  p->A5 =TRUE;
		  // }
	   //}
	   //else
	   //{
		  // a6=0;
	   //}
	   ////_________________检测气缸报警
	   ////if(p->m_alarm(0,M12,0,P19,0,P18))				
	   ////{
		  //// a7++;
		  //// if (a7>Alarm_Time)
		  //// {
			 ////  p->alarm =true;
			 ////  p->A6 =TRUE;
		  //// }
	   ////}
	   ////else
	   ////{
		  //// a7=0;
	   ////}
	   ////_________________检测气缸报警
	   //if(p->m_alarm(0,M13,1,P13,1,P12))	//拍边5			
	   //{
		  // a8++;
		  // if (a8>Alarm_Time)
		  // {
			 //  p->alarm =true;
			 //  p->A7 =TRUE;
		  // }
	   //}
	   //else
	   //{
		  // a8=0;
	   //}
	   ////_________________检测气缸报警
	   //if(p->m_alarm(0,M14,1,P11,1,P10))	//拍边6			
	   //{
		  // a9++;
		  // if (a9>Alarm_Time)
		  // {
			 //  p->alarm =true;
			 //  p->A8 =TRUE;
		  // }
	   //}
	   //else
	   //{
		  // a9=0;
	   //}
	   //_________________检测压板气缸报警

	
		   //if(p->sp_alarm(0,M15,1,P14))				
		   //{
			  // a10++;
			  // if (a10>Alarm_Time)
			  // {
				 //  p->alarm =true;
				 //  p->A9 =TRUE;
			  // }
		   //}
		   //else
		   //{
			  // a10=0;
		   //}


	   //_________________检测气缸报警---卡爪气缸
		   //if(!m_logic.Ld(1,M9))//////////////////////////////////////////////////////////////////////////
		   //{
			  // if(p->m_alarm(1,M12,1,P19,1,P18))				
			  // {
				 //  a11++;
				 //  if (a11>Alarm_Time)
				 //  {
					//   p->alarm =true;
					//   p->A10 =TRUE;
				 //  }
			  // }
			  // else
			  // {
				 //  a11=0;
			  // }
			  // //_________________检测气缸报警---卡爪气缸
			  // if(p->m_alarm(1,M12,1,P20,1,P21))				
			  // {
				 //  a12++;
				 //  if (a12>Alarm_Time)
				 //  {
					//   p->alarm =true;
					//   p->A11 =TRUE;
				 //  }
			  // }
			  // else
			  // {
				 //  a12=0;
			  // }
		   //}

	   //------------------------轴报警

	   for (int k = 0;k<MOTOR_NUM;k++)
	   {
		   if( ( ( APS_motion_io_status( k ) >> MIO_ALM ) & 1 ) )  
		   {

				   p->SVON[k] =true;
				   p->alarm =true;

		   }
		   else
		   {
            p->SVON[k] =false;
		   }
		   if( !( ( APS_motion_io_status( k ) >> MIO_SVON ) & 1 ) )  
		   {
			   if (k ==20||k==22||k==31)//屏蔽电机报警
			   {
			   }
			   else
			   {
				   p->server_on[k] =true;
				   p->alarm =true;
			   }

		   }
		   else
		   {
			   p->server_on[k] =false;
		   }
		  
	   }
	   if (p->reset)
	   {
		   p->reset =false;
		   p->alarm =false;
		   a1=0;
		   a2=0;
		   a3=0;
		   a4=0;
		   a5=0;
		   a6=0;
		   a7=0;
		   a8=0;
		   a9=0;
		   a10=0;
		   a11=0;
		   a12=0;
		   a13=0;
		   p->A0=false;
		   p->A1=false;
		   p->A2=false;
		   p->A3=false;
		   p->A4=false;
		   p->A5=false;
		   p->A6=false;
		   p->A7=false;
		   p->A8=false;
		   p->A9=false;
		   p->A10=false;
		   p->A11=false;
		   p->A12=false;
		   p->A13=false;
		   m_logic.Cam_measure_alarm[0] =false;
		   m_logic.Cam_measure_alarm[1] =false;
		   for (int k = 0;k<MOTOR_NUM;k++)
		   {
			   p->SVON[k] = false;
		   }
		   p->reset =false;
	   }
	   if (p->alarm)
	   {
		   p->start =false;
		  p->stop =true;
	   }
	   Sleep(200);
	}
	m_Motor.Close();
	return 0;
}
 CMotor m_Motor;
 CLogic m_logic;
