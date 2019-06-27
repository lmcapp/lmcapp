#pragma once
#include <Windows.h>
#include <list>
#include <iostream>
using namespace std;

struct tTIMER
{
	unsigned nID;			//��ʱ��ID
	unsigned nTimeElapce;	//��ʱ�����м��(ms)
	unsigned nTimeCreate;	//��ʱ������ʱ��
	unsigned nTimeLastRun;	//��ʱ���ϴ�����ʱ��
	bool bStatus;			//��ʱ��״̬��true���ã�falseͣ��
	tTIMER()
	{
		nID = -1;
		nTimeCreate = 0;
		nTimeElapce = 0;
		nTimeLastRun = 0;
		bStatus = true;
	}

	bool operator < (const tTIMER &timer) const
	{
		return this->nTimeElapce + this->nTimeLastRun < timer.nTimeElapce + timer.nTimeLastRun;
	}
};

typedef list<tTIMER> listTimer;
typedef list<tTIMER>::iterator itListTimer;

class CTimer
{
public:
	CTimer();
	~CTimer();

public:
	//���ö�ʱ��
	virtual void SetTimer(unsigned nTimerID, unsigned nTimerMS, int nParam = 0, char* p = NULL);

	//ɾ����ʱ��
	virtual void KillTimer(unsigned nTimeerID);

	//��ʱ��������
	virtual int OnTimer(int nID) = 0;

protected:
	static DWORD WINAPI TimerThread(LPVOID lpParam);
private:
	listTimer m_ltTimeList;		//��ʱ���б�
	bool m_bRun;
};