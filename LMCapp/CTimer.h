#pragma once
#include <Windows.h>
#include <list>
#include <iostream>
using namespace std;

struct tTIMER
{
	unsigned nID;			//定时器ID
	unsigned nTimeElapce;	//定时器运行间隔(ms)
	unsigned nTimeCreate;	//定时器创建时间
	unsigned nTimeLastRun;	//定时器上次运行时间
	bool bStatus;			//定时器状态，true启用，false停用
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
	//设置定时器
	virtual void SetTimer(unsigned nTimerID, unsigned nTimerMS, int nParam = 0, char* p = NULL);

	//删除定时器
	virtual void KillTimer(unsigned nTimeerID);

	//定时器处理函数
	virtual int OnTimer(int nID) = 0;

protected:
	static DWORD WINAPI TimerThread(LPVOID lpParam);
private:
	listTimer m_ltTimeList;		//定时器列表
	bool m_bRun;
};