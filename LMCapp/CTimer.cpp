#include "StdAfx.h"
#include "CTimer.h"
#include <process.h>


CTimer::CTimer():
m_bRun(true)
{
}


CTimer::~CTimer()
{
	m_bRun = false;
	m_ltTimeList.clear();
}

void CTimer::SetTimer(unsigned nTimerID, unsigned nTimerMS, int nParam /* = 0 */, char* p /* = NULL */)
{
	if (nTimerMS == 0)
	{
		return;
	}
	tTIMER tTimer;
	tTimer.bStatus = true;
	tTimer.nID = nTimerID;
	unsigned nTimeNow = GetTickCount();
	tTimer.nTimeCreate = nTimeNow;
	tTimer.nTimeLastRun = nTimeNow;
	tTimer.nTimeElapce = nTimerMS;
	m_ltTimeList.push_back(tTimer);
	if (m_ltTimeList.size() == 1)
	{
		m_bRun = true;
		HANDLE handle = CreateThread(NULL, 0, TimerThread, this, 0, 0);
		CloseHandle(handle);
	}
}

void CTimer::KillTimer(unsigned nTimeerID)
{
	for (auto it = m_ltTimeList.begin(); it != m_ltTimeList.end(); ++it)
	{
		if (nTimeerID == it->nID)
		{
			it->bStatus = false;
			break;
		}
	}
}

DWORD WINAPI CTimer::TimerThread(LPVOID lpParam)
{
	CTimer *pTimer = (CTimer*)lpParam;
	while (pTimer->m_bRun)
	{
		if (pTimer->m_ltTimeList.size() < 1)
		{
			break;
		}
		//¶¨Ê±Æ÷ÅÅÐò
		pTimer->m_ltTimeList.sort();
		unsigned nTimeNow = GetTickCount();
		for (itListTimer it = pTimer->m_ltTimeList.begin(); it != pTimer->m_ltTimeList.end(); ++it)
		{
			if (!it->bStatus)
			{
				it = pTimer->m_ltTimeList.erase(it);
				continue;
			}
			if (nTimeNow >= it->nTimeLastRun + it->nTimeElapce)
			{
				it->nTimeLastRun = nTimeNow;
				pTimer->OnTimer(it->nID);
			}
			else
			{
				break;
			}
		}
		Sleep(0);
	}
	return 0;
}

int CTimer::OnTimer(int nID)
{
	KillTimer(nID);
	return 0;
}