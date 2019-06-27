#pragma once
#include "DEFPLC.h"
#include "Logic.h"
/*
��Ȩ����
������ע������
���ߣ�����
���ڣ�2019-6-27
*/
enum val_type
{
	X,Y,M,T,D,N
};
struct PLCTIMER
{
	unsigned nID;			//��ʱ��ID
	unsigned nTimeElapce;	//��ʱ�����м��(ms)
	unsigned nTimeCreate;	//��ʱ������ʱ��
	unsigned nTimeLastRun;	//��ʱ���ϴ�����ʱ��
	bool bStatus;			//��ʱ��״̬��true���ã�falseͣ��
	bool tStatus;           //��ʱ����ʱ״̬��true����ʾ�����false��ʾʱ��û����
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
	int result;//����Ĵ���

public://
	void LD(int CardID,int port,val_type m_type);
	void LDI(int CardID,int port,val_type m_type);

	void AND(int CardID,int port,val_type m_type);
	void ANDI(int CardID,int port,val_type m_type);

	void SET(int CardID,int port,val_type m_type);
	void RSET(int CardID,int port,val_type m_type);

	void Out(int CardID,int port,val_type m_type); //T CARid ��ʾʱ��� port ��ʾʱ��

	void PULS(int move_type,I32 AXIS,I32 POS,I32 Speed);

	void STOP(I32 AXIS);

	void CMP(int cm_type,I32 va1,I32 va2 );

	void GetPOS(I32 axis, I32 &dst);

	void AXIS_DONE(I32 AXIS);

	void GETPEL(I32 AXIS);
	void GETMEL(I32 AXIS);
	void GETORG(I32 AXIS);
	void ORG(I32 AXIS);
/*virtual   void Out_mul_2(int CardID0,int port0,//���outר��
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