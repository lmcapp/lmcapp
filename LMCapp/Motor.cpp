// Motor.cpp : 实现文件
//

#include "stdafx.h"
#include "LMCapp.h"
#include "Motor.h"


// CMotor

IMPLEMENT_DYNAMIC(CMotor, CWnd)

CMotor::CMotor()
{
	Initial();
}

CMotor::~CMotor()
{
//	Close();
}


BEGIN_MESSAGE_MAP(CMotor, CWnd)
END_MESSAGE_MAP()



// CMotor 消息处理程序

bool CMotor::Initial()
{
	I32 boardID_InBits = 0;
	I32 mode           =0;//0;
	I32 ret          = 0;
	// Card(Board) initial
	ret = APS_initial( &boardID_InBits, mode);

	if( ret != ERR_NoError )
		return false;



	CString str1,str2;
	HMODULE module = GetModuleHandle(0); 
	TCHAR pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 
	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
	{
		str1 = _T("");
	}
	else 
	{
		str1.Format(_T("%s"),csFullPath.Left(nPos));
		str2.Format(_T("%s\\param.xml"),str1);
	}
	ret = APS_load_param_from_file("c:\\LMCapp\\param.xml");// (char*)str2.GetBuffer(0));
	if( ret != ERR_NoError )
	{
		::MessageBox(NULL,_T("加载马达配置文件失败！"),_T("错误信息"),NULL);return false;
	}
		
	for (int k = 0;k<Card_NUM;k++)
	{
		APS_read_d_output(k,0,&DO_Data[k]);//读取输出状态
		APS_read_d_input(k,0,&DI_Data[k]);//读取输入状态
	}
	loadpos();
	set_speed_param();
	for (int k =0;k<Motor_Num;k++)
	{
		ret = APS_set_servo_on( k, 1 ); 	
		if(ret) 
		{
			CString str ;
			str.Format(_T("Axis%dservo on failed!"),k);
			MessageBox(str);
			return false;
		}
	}
	//-----------------------设置电缸极限
	//PRA_SPEL_EN
//	ret =APS_set_axis_param(1,PRA_SPEL_EN,2);
	if( ret != ERR_NoError )
	{
		::MessageBox(NULL,_T("软限位启用失败！"),_T("错误信息"),NULL);return false;
	}
	APS_set_axis_param(1,PRA_SPEL_POS,11000);
//	APS_set_axis_param(2,PRA_SPEL_EN,2);
	APS_set_axis_param(2,PRA_SPEL_POS,11000);
//	APS_set_axis_param(17,PRA_SPEL_EN,2);
	APS_set_axis_param(17,PRA_SPEL_POS,11000);
//	APS_set_axis_param(18,PRA_SPEL_EN,2);
	APS_set_axis_param(18,PRA_SPEL_POS,11000);
//	APS_set_axis_param(1,PRA_SMEL_EN,2);
	APS_set_axis_param(1,PRA_SMEL_POS,-1000);
//	APS_set_axis_param(2,PRA_SMEL_EN,2);
	APS_set_axis_param(2,PRA_SMEL_POS,-1000);
//	APS_set_axis_param(17,PRA_SMEL_EN,2);
	APS_set_axis_param(17,PRA_SMEL_POS,-1000);
//	APS_set_axis_param(18,PRA_SMEL_EN,2);
    APS_set_axis_param(18,PRA_SMEL_POS,-1000);
	
	
	
	
	
	
	
	
	return true;
}
void CMotor::set_speed_param()
{
	for (int k = 0;k<Motor_Num;k++)
	{
		APS_set_axis_param_f(k,PRA_ACC,acc_speed[k]);
		APS_set_axis_param_f(k,PRA_DEC,acc_speed[k]);
		APS_set_axis_param_f(k,PRA_VS,start_speed[k]);
		APS_set_axis_param_f(k,PRA_VM,move_maxspeed[k]);
		APS_set_axis_param_f(k,PRA_VE,start_speed[k]);
		
		APS_set_axis_param_f(k,PRA_HOME_VM,go_homespeed[k]);
	}
}
bool CMotor::Close()
{
	I32 ret =0;
	ret = APS_close();
	//ret = Release_Card(0);
	return true;
}

void CMotor::WritePort(bool isextent,I32 Car_ID,I32 port,bool status)
{
	I32 data_port[24] = 
	{
		0x000001,0x000002,0x000004,0x000008,
		0x000010,0x000020,0x000040,0x000080,
		0x000100,0x000200,0x000400,0x000800,
		0x001000,0x002000,0x004000,0x008000,
		0x010000,0x020000,0x040000,0x080000,
		0x100000,0x200000,0x400000,0x800000 
	};
	if (!isextent)//运动控制卡
	{

			if(status)
			{
				DO_Data[Car_ID] |= data_port[port];
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			}
			else
			{
				DO_Data[Car_ID] &= (~data_port[port]);
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			} 

	}
	else //扩展板卡
	{
		//if (port>=16)
		//{
		//	MessageBox(_T("扩展板卡只有16路输出口！"));
		//	return ;
		//}
		//if(status)
		//{
		//	DO_Data2 |= data_port[port];
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
		//else
		//{
		//	DO_Data2 &= (~data_port[port]);
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
	}
}
void CMotor::WritePort_mul(bool isextent,I32 Car_ID,I32 port0,I32 port1,I32 port2,bool status)//写IO状态
{
	I32 data_port[24] = 
	{
		0x000001,0x000002,0x000004,0x000008,
		0x000010,0x000020,0x000040,0x000080,
		0x000100,0x000200,0x000400,0x000800,
		0x001000,0x002000,0x004000,0x008000,
		0x010000,0x020000,0x040000,0x080000,
		0x100000,0x200000,0x400000,0x800000 
	};
	if (!isextent)//运动控制卡
	{
			if(status)
			{
				DO_Data[Car_ID] |= data_port[port0];
				DO_Data[Car_ID] |= data_port[port1];
				DO_Data[Car_ID] |= data_port[port2];
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			}
			else
			{
				DO_Data[Car_ID] &= (~data_port[port0]);
				DO_Data[Car_ID] &= (~data_port[port1]);
				DO_Data[Car_ID] &= (~data_port[port2]);
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			} 
	}
	else //扩展板卡
	{
		//if (port>=16)
		//{
		//	MessageBox(_T("扩展板卡只有16路输出口！"));
		//	return ;
		//}
		//if(status)
		//{
		//	DO_Data2 |= data_port[port];
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
		//else
		//{
		//	DO_Data2 &= (~data_port[port]);
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
	}
}
void CMotor::WritePort_2(bool isextent,I32 Car_ID,I32 port0,I32 port1,bool status)//写IO状态
{
	I32 data_port[24] = 
	{
		0x000001,0x000002,0x000004,0x000008,
		0x000010,0x000020,0x000040,0x000080,
		0x000100,0x000200,0x000400,0x000800,
		0x001000,0x002000,0x004000,0x008000,
		0x010000,0x020000,0x040000,0x080000,
		0x100000,0x200000,0x400000,0x800000 
	};
	if (!isextent)//运动控制卡
	{
			if(status)
			{
				DO_Data[Car_ID] |= data_port[port0];
				DO_Data[Car_ID] |= data_port[port1];
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			}
			else
			{
				DO_Data[Car_ID] &= (~data_port[port0]);
				DO_Data[Car_ID] &= (~data_port[port1]);
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			} 
	}
	else //扩展板卡
	{
		//if (port>=16)
		//{
		//	MessageBox(_T("扩展板卡只有16路输出口！"));
		//	return ;
		//}
		//if(status)
		//{
		//	DO_Data2 |= data_port[port];
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
		//else
		//{
		//	DO_Data2 &= (~data_port[port]);
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
	}
}
void CMotor::WritePort_4(bool isextent,I32 Car_ID,I32 port0,I32 port1,I32 port2,I32 port3,bool status)//写IO状态
{
	I32 data_port[24] = 
	{
		0x000001,0x000002,0x000004,0x000008,
		0x000010,0x000020,0x000040,0x000080,
		0x000100,0x000200,0x000400,0x000800,
		0x001000,0x002000,0x004000,0x008000,
		0x010000,0x020000,0x040000,0x080000,
		0x100000,0x200000,0x400000,0x800000 
	};
	if (!isextent)//运动控制卡
	{
			if(status)
			{
				DO_Data[Car_ID] |= data_port[port0];
				DO_Data[Car_ID] |= data_port[port1];
				DO_Data[Car_ID] |= data_port[port2];
				DO_Data[Car_ID] |= data_port[port3];
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			}
			else
			{
				DO_Data[Car_ID] &= (~data_port[port0]);
				DO_Data[Car_ID] &= (~data_port[port1]);
				DO_Data[Car_ID] &= (~data_port[port2]);
				DO_Data[Car_ID] &= (~data_port[port3]);
				APS_write_d_output(Car_ID,0,DO_Data[Car_ID]);
			} 
	}
	else //扩展板卡
	{
		//if (port>=16)
		//{
		//	MessageBox(_T("扩展板卡只有16路输出口！"));
		//	return ;
		//}
		//if(status)
		//{
		//	DO_Data2 |= data_port[port];
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
		//else
		//{
		//	DO_Data2 &= (~data_port[port]);
		//	DO_WritePort( 0, 0, DO_Data2 );
		//}
	}
}
bool CMotor::ReadPort(bool isextent,bool isin, I32 Car_ID, I32 port)
{
	I32 read_data =0;
	I32 data_port[24] = 
	{
		0x000001,0x000002,0x000004,0x000008,
		0x000010,0x000020,0x000040,0x000080,
		0x000100,0x000200,0x000400,0x000800,
		0x001000,0x002000,0x004000,0x008000,
		0x010000,0x020000,0x040000,0x080000,
		0x100000,0x200000,0x400000,0x800000
	};
	if (!isextent)//运动板卡
	{
			if (isin)
			{
				APS_read_d_input(Car_ID,0,&DI_Data[Car_ID]);
				return ((DI_Data[Car_ID]&data_port[port])>0?TRUE:FALSE);
			}
			else
			{
				APS_read_d_output(Car_ID,0,&DO_Data[Car_ID]);
				return ((DO_Data[Car_ID]&data_port[port])>0?TRUE:FALSE);
			}
	}
	else
	{
		//if (port>=16)
		//{
		//	MessageBox(_T("扩展板卡只有16路输出口！"));
		//	return false ;
		//}
		//if (isin)
		//{		
		//	DI_ReadPort(0,0,&DI_Data2);
		//    return (DI_Data2&data_port[port]);
		//}
		//else
		//{
		//	DO_ReadPort(0,0,&DO_Data2);
		//	return (DO_Data2&data_port[port]);
		//}

	}
	return false;
}
bool CMotor::Go_home(I32 Axis_ID)
{
	//This example shows how home move operation
	I32 axis_id = Axis_ID;
	I32 return_code;
	I32 ret = 0;
	// 1. Select home mode and config home parameters 
	//APS_set_axis_param( axis_id, PRA_HOME_MODE,      0 ); // Set home mode
	//APS_set_axis_param( axis_id, PRA_HOME_DIR,       1 ); // Set home direction
	//APS_set_axis_param_f( axis_id, PRA_HOME_CURVE,     0 ); // Set acceleration paten (T-curve)
	//APS_set_axis_param_f( axis_id, PRA_HOME_ACC, 1000000 ); // Set homing acceleration rate
	//APS_set_axis_param_f( axis_id, PRA_HOME_VM,   100000 ); // Set homing maximum velocity.
	//APS_set_axis_param_f( axis_id, PRA_HOME_VO,    go_homespeed[Axis_ID] ); // Set homing VO speed
	//APS_set_axis_param( axis_id, PRA_HOME_EZA,       0 ); // Set EZ signal alignment (yes or no)
	//APS_set_axis_param_f( axis_id, PRA_HOME_SHIFT,     0 ); // Set home position shfit distance. 
	//APS_set_axis_param_f( axis_id, PRA_HOME_POS,       0 ); // Set final home position.


	//Check servo on or not
	if( !( ( APS_motion_io_status( Axis_ID ) >> MIO_SVON ) & 1 ) )  
	{
		ret = APS_set_servo_on( Axis_ID, 1 ); 	
		if(ret) 
		{
			CString str ;
			str.Format(_T("Axis%dservo on failed!"),Axis_ID);
			MessageBox(str);
			return false;
		}
		Sleep( 300 ); // Wait stable.
	}
	return_code = APS_home_move( axis_id ); //Start homing 
	if( return_code == ERR_NoError )
	{ 
		return true;
	}
	return false;
}
void CMotor::wait_move_done(I32 Axis_ID)
{
	I32 MotionStatus =0;
	do{ MotionStatus = APS_motion_status( Axis_ID ); //Get Motion status 
	}while ( ( MotionStatus>>5 & 0x1 ) == 0 );
}
bool CMotor::is_move_done(I32 Axis_ID)
{
	I32 MotionStatus =0;
	MotionStatus = APS_motion_status( Axis_ID ); //Get Motion status 
	return ( MotionStatus>>5 & 0x1 ) ;
}
void CMotor::reset_pos(I32 Axis_ID)
{
	APS_set_position(Axis_ID, 0x00);					//复位完成设脉冲位置为0	
}

void CMotor::absolute_move(I32 Axis_ID,I32 Pos)
{
	APS_absolute_move(Axis_ID,Pos,move_maxspeed[Axis_ID]);
	//wait_move_done(Axis_ID);
}
void CMotor::relative_move(I32 Axis_ID,I32 Pos)
{
	APS_relative_move(Axis_ID,Pos,move_maxspeed[Axis_ID]);
	//wait_move_done(Axis_ID);
}
void CMotor::velocity_move( I32 Axis_ID, I32 Max_Speed )
{
	APS_velocity_move( Axis_ID, Max_Speed );
}
void CMotor::JOG_ON(I32 Axis_ID,UINT dir)
{
	APS_set_axis_param( Axis_ID, PRA_JG_MODE, 0 );  // Set jog mode
	APS_set_axis_param( Axis_ID, PRA_JG_DIR,  dir );  // Set jog direction

	APS_set_axis_param_f( Axis_ID, PRA_JG_CURVE, 0.0  );
	APS_set_axis_param_f( Axis_ID, PRA_JG_ACC, 50000.0 );
	APS_set_axis_param_f( Axis_ID, PRA_JG_DEC, 50000.0 );
	APS_set_axis_param_f( Axis_ID, PRA_JG_VM,  jog_speed[Axis_ID]  );

	//Check servo on or not
	if( !( ( APS_motion_io_status( Axis_ID ) >> MIO_SVON ) & 1 ) )  
	{
		APS_set_servo_on( Axis_ID, 1 ); 
		Sleep( 500 ); // Wait stable.
	}

	// Create a rising edge.
	APS_jog_start( Axis_ID, 0 );  //Jog Off
	APS_jog_start( Axis_ID, 1 );  //Jog ON
}
void CMotor::JOG_OFF(I32 Axis_ID)
{
	// Create a rising edge.
	APS_jog_start( Axis_ID, 1 );  //Jog On
	APS_jog_start( Axis_ID, 0 );  //Jog Off
}
void CMotor::savepos()
{
	CString str1,str2;
	HMODULE module = GetModuleHandle(0); 
	TCHAR pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 
	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
	{
		str1 = _T("");
	}
	else 
	{
		str1.Format(_T("%s"),csFullPath.Left(nPos));
		str2.Format(_T("%s\\pos.ini"),str1);
	}
	str2 = _T("C:\\LMCapp\\pos.ini");
	CString str_name,str_value;
	for (int k = 0 ;k<Motor_Num ; k++)
	{
		str_name.Format(_T("go_homespeed%d"),k);
		str_value.Format(_T("%d"),go_homespeed[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("Speed"),str_name,str_value,str2);
		str_name.Format(_T("move_maxspeed%d"),k);
		str_value.Format(_T("%d"),move_maxspeed[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("Speed"),str_name,str_value,str2);
		str_name.Format(_T("start_speed%d"),k);
		str_value.Format(_T("%d"),start_speed[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("Speed"),str_name,str_value,str2);
		str_name.Format(_T("acc_speed%d"),k);
		str_value.Format(_T("%d"),acc_speed[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("Speed"),str_name,str_value,str2);
		str_name.Format(_T("jog_speed%d"),k);
		str_value.Format(_T("%d"),jog_speed[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("Speed"),str_name,str_value,str2);
	}
	for (int k =0;k<4;k++)
	{
		str_name.Format(_T("PAIBIANPOS%d"),k);
		str_value.Format(_T("%d"),PAIBIANPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("DENGLIAOPOS%d"),k);
		str_value.Format(_T("%d"),DENGLIAOPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("QULIAOPOS%d"),k);
		str_value.Format(_T("%d"),QULIAOPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("DINGSHENGPOS%d"),k);
		str_value.Format(_T("%d"),DINGSHENGPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("PAIZHAOPOS%d"),k);
		str_value.Format(_T("%d"),PAIZHAOPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("PRINTPOS%d"),k);
		str_value.Format(_T("%d"),PRINTPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("FANGLIAOPOS%d"),k);
		str_value.Format(_T("%d"),FANGLIAOPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("PRINTOKPOS%d"),k);
		str_value.Format(_T("%d"),PRINTOKPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);

		str_name.Format(_T("PUTDINGSHENGPOS%d"),k);
		str_value.Format(_T("%d"),PUTDINGSHENGPOS[k]);
		str_value.TrimLeft();
		::WritePrivateProfileString(_T("POSITION"),str_name,str_value,str2);
	}
	 str_value.Format(_T("%f"),headTemp[0]);
	 str_value.TrimLeft();
	 ::WritePrivateProfileString(_T("Headtemp"),_T("headTemp[0]"),str_value,str2);
	 str_value.Format(_T("%f"),headTemp[1]);
	 str_value.TrimLeft();
	 ::WritePrivateProfileString(_T("Headtemp"),_T("headTemp[1]"),str_value,str2);
	 str_value.Format(_T("%f"),headTemp[2]);
	 str_value.TrimLeft();
	 ::WritePrivateProfileString(_T("Headtemp"),_T("headTemp[2]"),str_value,str2);

	 str_value.Format(_T("%f"),headTempX);
	 str_value.TrimLeft();
	 ::WritePrivateProfileString(_T("Headtemp"),_T("headTempX"),str_value,str2);

}
void CMotor::loadpos()
{
	CString str1,str2;
	HMODULE module = GetModuleHandle(0); 
	TCHAR pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 
	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
	{
		str1 = _T("");
	}
	else 
	{
		str1.Format(_T("%s"),csFullPath.Left(nPos));
		str2.Format(_T("%s\\pos.ini"),str1);
	}
	str2 = _T("C:\\LMCapp\\pos.ini");
	CString str_name,str_value;
	for (int k = 0 ;k<Motor_Num ; k++)
	{
		str_name.Format(_T("go_homespeed%d"),k);
		GetPrivateProfileString(_T("Speed"),str_name,_T("50000"),str_value.GetBuffer(256),256,str2);
		go_homespeed[k] = _wtoi(str_value);
		str_name.Format(_T("move_maxspeed%d"),k);
		GetPrivateProfileString(_T("Speed"),str_name,_T("50000"),str_value.GetBuffer(256),256,str2);
		move_maxspeed[k] = _wtoi(str_value);
		str_name.Format(_T("start_speed%d"),k);
		GetPrivateProfileString(_T("Speed"),str_name,_T("10000"),str_value.GetBuffer(256),256,str2);
		start_speed[k] = _wtoi(str_value);
		str_name.Format(_T("acc_speed%d"),k);
		GetPrivateProfileString(_T("Speed"),str_name,_T("10000"),str_value.GetBuffer(256),256,str2);
		acc_speed[k] = _wtoi(str_value);
		str_name.Format(_T("jog_speed%d"),k);
		GetPrivateProfileString(_T("Speed"),str_name,_T("50000"),str_value.GetBuffer(256),256,str2);
		jog_speed[k] = _wtoi(str_value);
	}
	for(int k =0;k<4;k++)
	{
		str_name.Format(_T("PAIBIANPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		PAIBIANPOS[k] = _wtol(str_value);

		str_name.Format(_T("DENGLIAOPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		DENGLIAOPOS[k] = _wtol(str_value);

		str_name.Format(_T("QULIAOPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		QULIAOPOS[k] = _wtol(str_value);

		str_name.Format(_T("DINGSHENGPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		DINGSHENGPOS[k] = _wtol(str_value);

		str_name.Format(_T("PAIZHAOPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		PAIZHAOPOS[k] = _wtol(str_value);

		str_name.Format(_T("PRINTPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		PRINTPOS[k] = _wtol(str_value);

		str_name.Format(_T("FANGLIAOPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		FANGLIAOPOS[k] = _wtol(str_value);

		str_name.Format(_T("PRINTOKPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		PRINTOKPOS[k] = _wtol(str_value);

		str_name.Format(_T("PUTDINGSHENGPOS%d"),k);
		GetPrivateProfileString(_T("POSITION"),str_name,_T("0"),str_value.GetBuffer(256),256,str2);
		PUTDINGSHENGPOS[k] = _wtol(str_value);
	}

	GetPrivateProfileString(_T("Headtemp"),_T("headTempX"),_T("0"),str_value.GetBuffer(256),256,str2);
	headTempX = _wtof(str_value);

	GetPrivateProfileString(_T("Headtemp"),_T("headTemp[0]"),_T("0"),str_value.GetBuffer(256),256,str2);
	headTemp[0] = _wtof(str_value);

	GetPrivateProfileString(_T("Headtemp"),_T("headTemp[1]"),_T("0"),str_value.GetBuffer(256),256,str2);
	headTemp[1] = _wtof(str_value);

	GetPrivateProfileString(_T("Headtemp"),_T("headTemp[2]"),_T("0"),str_value.GetBuffer(256),256,str2);
	headTemp[2] = _wtof(str_value);
}
void CMotor::stop(I32 Axis_ID)
{
	APS_stop_move(Axis_ID);
}
void CMotor::move_pt(I32 AXIS0,I32 AXIS1,I32 POS,I32 POS1)
{
	I32 Dimension =2;
	I32 Axis[2] = {AXIS0,AXIS1};
	I32 opt = 0x3001;
	F64 PositionArray[2] ={POS,POS1};

	F64 TransPara = 0; //don’t care in buffered mode
	ASYNCALL *wait = NULL; //A waiting call
	APS_line_all( Dimension, Axis, opt, PositionArray, &TransPara, 10000, 10000, 10000, 10000, 10000, 0.5, wait );

	wait_move_done(AXIS0);
	wait_move_done(AXIS1);
	
}

void CMotor::mul_real_move(I32 Axis_ID1,I32 Pos1,I32 Axis_ID2,I32 Pos2,I32 Axis_ID3,I32 Pos3)
{
	I32 Axis_ID_Array[3] = { Axis_ID1, Axis_ID2,Axis_ID3 };
	//Bit 8 set to 1. Be a waiting state.
	I32 opt = 0x0101; //absolute, wait trigger, Aborting mode
	ASYNCALL *wait = NULL;
	//An absolute move to position 10000 in wating state
	APS_ptp( Axis_ID1, opt, Pos1, wait );
	APS_ptp( Axis_ID2, opt, Pos2, wait );
	APS_ptp( Axis_ID3, opt, Pos3, wait );
	// send a trigger to sync all waiting moves
	APS_move_trigger( 3, Axis_ID_Array );
	wait_move_done(Axis_ID1);
	wait_move_done(Axis_ID2);
	wait_move_done(Axis_ID3);
	Sleep(100);
}