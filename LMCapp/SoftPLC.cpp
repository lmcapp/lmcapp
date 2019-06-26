#include "StdAfx.h"
#include "SoftPLC.h"

CSoftPLC plc;
CSoftPLC::CSoftPLC(void)
{
	for(int k = 0;k<256;k++)
	{
		if (k<32)
		{
			d[k] = 0;
			m[k] = 0;
		}
		else
		{
			d[k] = 0;
			m[k] = 0;
		}
	}
	scan_io();
}


CSoftPLC::~CSoftPLC(void)
{
}
void CSoftPLC::LD(int CardID,int port,val_type m_type)
{
	switch(m_type)
	{
	case X:
		scan_io();
		result = (in[CardID]>>port)&1;
		break;
	case Y:
		scan_io();
		result = (out[CardID]>>port)&1;
		break;
	case M:
		result = m[port];
		break;
	case N:
		result = n[port];
		break;
	}
}
void CSoftPLC::LDI(int CardID,int port,val_type m_type)
{
	switch(m_type)
	{
	case X:
		scan_io();
		result = !((in[CardID]>>port)&1);
		break;
	case Y:
		scan_io();
		result = !((out[CardID]>>port)&1);
		break;
	case M:
		result = !(m[port]);
	case N:
		result = !(n[port]);
		break;
	}
}
void CSoftPLC::AND(int CardID,int port,val_type m_type)
{
	switch(m_type)
	{
	case X:
		scan_io();
		result =result&&((in[CardID]>>port)&1);
		break;
	case Y:
		scan_io();
		result = result&&((out[CardID]>>port)&1);
		break;
	case M:
		result = result&&m[port];
		break;
	case N:
		result = result&&n[port];
		break;
	}
}
void CSoftPLC::ANDI(int CardID,int port,val_type m_type)
{
	switch(m_type)
	{
	case X:
		scan_io();
		result =(result&&(!(((in[CardID]>>port)&1))));
		break;
	case Y:
		scan_io();
		result = (result&&(!(((out[CardID]>>port)&1))));
		break;
	case M:
		result = (result&&(!(m[port])));
		break;
	case N:
		result = (result&&(!(n[port])));
		break;
	}
}
void CSoftPLC::Out(int CardID,int port,val_type m_type)
{
	switch(m_type)
	{
	case X://暂时不可以强制输入点
  
		break;
	case Y:
		m_Motor.WritePort(0,CardID,port,result>0?true:false);
		break;
	case M:
		m[port] = result;
		break;
	case N:
		n[port] = result;
		break;
	case T:
		if (result<=0)
		{
			t[CardID].nID = -1;
			t[CardID].nTimeCreate = 0;
			t[CardID].nTimeElapce = 0;
			t[CardID].nTimeLastRun = 0;
			t[CardID].nCountTime = 0;
			t[CardID].bStatus = false;
			t[CardID].tStatus =false;
		}
		else
		{
			if (t[CardID].bStatus ==false)
			{
				t[CardID].bStatus = true;
				t[CardID].nID = CardID;
				unsigned nTimeNow = GetTickCount();
				t[CardID].nTimeCreate = nTimeNow;
				t[CardID].nTimeLastRun = nTimeNow;
				t[CardID].nTimeElapce = port;
				HANDLE handle = CreateThread(NULL, 0, TimerThread, &t[CardID], 0, 0);
			}
		}
		break;
	}
}
DWORD WINAPI CSoftPLC::TimerThread(LPVOID lpParam)
{
	PLCTIMER *pTimer = (PLCTIMER*)lpParam;
	while (pTimer->bStatus)
	{
		//定时器排序
		unsigned nTimeNow = GetTickCount();
		pTimer->nCountTime = nTimeNow - pTimer->nTimeCreate;
		if (nTimeNow >= pTimer->nTimeLastRun + pTimer->nTimeElapce)
		{
			pTimer->nCountTime = nTimeNow - pTimer->nTimeCreate;
			pTimer->tStatus =true;
			break;
		}
		//Sleep(0);
	}
	return 0;
}

void CSoftPLC::SET(int CardID,int port,val_type m_type)
{
	if (result)
	{
		switch(m_type)
		{
		case X://暂时不可以强制输入点

			break;
		case Y:
			m_Motor.WritePort(0,CardID,port,true);
			break;
		case M:
			m[port] = 1;
			break;
		case N:
			n[port] = 1;
			break;
		}
	}
}
void CSoftPLC::RSET(int CardID,int port,val_type m_type)
{
	if (result)
	{
		switch(m_type)
		{
		case X://暂时不可以强制输入点

			break;
		case Y:
			m_Motor.WritePort(0,CardID,port,false);
			break;
		case M:
			m[port] = 0;
			break;
		case N:
			n[port] = 0;
			break;
		case T:
			t[CardID].bStatus =false;
			t[CardID].tStatus =false;
			break;
		}
	}
}

void CSoftPLC::PULS(int move_type,I32 AXIS,I32 POS,I32 Speed)
{
	if (result)
	{
		switch(move_type)
		{
		case 0://绝对移动
			m_Motor.absolute_move(AXIS,POS);
			break;
		case 1://相对移动
			m_Motor.relative_move(AXIS,POS);
			break;
		case 2://连续速度运动
			m_Motor.velocity_move(AXIS,Speed);
			break;
		}
	}
}
void CSoftPLC::CMP(int cm_type,I32 va1,I32 va2 )
{
	if (result)
	{
		switch(cm_type)
		{
		case 0://等于 返回true 
			result = result&&(va1 ==va2?true:false);
			break;
		case 1://大于 返回true 
			result = result&&(va1 >va2?true:false);
			break;
		case 2://小于 返回true 
			result = result&&(va1 <va2?true:false);
			break;
		}
	}
}
void CSoftPLC::GetPOS(I32 axis, I32 &dst)
{
	if (result)
	{
	 APS_get_position(axis,&dst);
	}
}
void CSoftPLC::STOP(I32 AXIS)
{
	if (result)
	{
		m_Motor.stop(AXIS);
	}
}
void CSoftPLC::AXIS_DONE(I32 AXIS)
{
	bool ret = m_Motor.is_move_done(AXIS);
    result =result&&ret;
}

void CSoftPLC::scan_io()
{
	for (int k = 0;k<Card_NUM;k++)
	{
		APS_read_d_output(k,0,&m_Motor.DO_Data[k]);//读取输出状态
		APS_read_d_input(k,0,&m_Motor.DI_Data[k]);//读取输入状态
		in[k] = m_Motor.DI_Data[k];
		out[k] = m_Motor.DO_Data[k];
	}
}
void CSoftPLC::run()
{
	LD(0,0,M);
	Out(0,1,M);
}
void CSoftPLC::GETPEL(I32 AXIS)
{
	I32  status = APS_motion_io_status(AXIS);
	int pel  = status>>MIO_PEL&0x1;
	result=result&&pel;
}
void CSoftPLC::GETMEL(I32 AXIS)
{
	I32  status = APS_motion_io_status(AXIS);
	int mel  = status>>MIO_MEL&0x1;
	result=result&&mel;
}
void CSoftPLC::GETORG(I32 AXIS)
{
	I32  status = APS_motion_io_status(AXIS);
	int org  = status>>MIO_ORG&0x1;
	result=result&&org;
}
void CSoftPLC::ORG(I32 AXIS)
{
	if (result)
	{
		m_Motor.Go_home(AXIS);
	}
}