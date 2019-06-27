#pragma once
#include "DEFPLC.h"
#include "Logic.h"
/*
版权所有
引用请注明出处
作者：刘辉
日期：2019-6-27
*/
enum val_type
{
	X,Y,M,T,D,N
};
struct PLCTIMER
{
	unsigned nID;			//定时器ID
	unsigned nTimeElapce;	//定时器运行间隔(ms)
	unsigned nTimeCreate;	//定时器创建时间
	unsigned nTimeLastRun;	//定时器上次运行时间
	bool bStatus;			//定时器状态，true启用，false停用
	bool tStatus;           //定时器计时状态，true，表示溢出；false表示时间没到；
	unsigned nCountTime;
	PLCTIMER()
	{
		nID = -1;
		nTimeCreate = 0;
		nTimeElapce = 0;
		nTimeLastRun = 0;
		nCountTime = 0;
		bStatus = false;
		tStatus =false;
	}

	bool operator < (const PLCTIMER &timer) const
	{
		return this->nTimeElapce + this->nTimeLastRun < timer.nTimeElapce + timer.nTimeLastRun;
	}
};
class CSoftPLC
{
public:
	CSoftPLC(void);
	virtual ~CSoftPLC(void);
	I32 in[Card_NUM];
	I32 out[Card_NUM];
	I32 d[256];
	I32 m[256];
	I32 n[256];
	PLCTIMER t[256];
private:
	int result;//结果寄存器

public://
	void LD(int CardID,int port,val_type m_type);
	void LDI(int CardID,int port,val_type m_type);

	void AND(int CardID,int port,val_type m_type);
	void ANDI(int CardID,int port,val_type m_type);

	void SET(int CardID,int port,val_type m_type);
	void RSET(int CardID,int port,val_type m_type);

	void Out(int CardID,int port,val_type m_type); //T CARid 表示时间号 port 表示时间

	void PULS(int move_type,I32 AXIS,I32 POS,I32 Speed);

	void STOP(I32 AXIS);

	void CMP(int cm_type,I32 va1,I32 va2 );

	void GetPOS(I32 axis, I32 &dst);

	void AXIS_DONE(I32 AXIS);

	void GETPEL(I32 AXIS);
	void GETMEL(I32 AXIS);
	void GETORG(I32 AXIS);
	void ORG(I32 AXIS);
/*virtual   void Out_mul_2(int CardID0,int port0,//马达out专用
		                 int CardID1,int port1); 
virtual	  void Out_mul_3(int CardID0,int port0,
		               int CardID1,int port1,
		               int CardID2,int port2); */

	void scan_io();
public:
	void run();
protected:
	static DWORD WINAPI TimerThread(LPVOID lpParam);
};
extern CSoftPLC plc;