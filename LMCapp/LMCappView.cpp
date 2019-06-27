
// LMCappView.cpp : CLMCappView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "LMCapp.h"
#endif

#include "LMCappDoc.h"
#include "LMCappView.h"
#include "Cam.h"
#include "Logic.h"
#include "Motor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 int Step[5];
// CLMCappView

IMPLEMENT_DYNCREATE(CLMCappView, CFormView)

BEGIN_MESSAGE_MAP(CLMCappView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CLMCappView ����/����

CLMCappView::CLMCappView()
	: CFormView(CLMCappView::IDD)
{
	// TODO: �ڴ˴���ӹ������

}

CLMCappView::~CLMCappView()
{
   
}

void CLMCappView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAMERA0, m_static0);
	DDX_Control(pDX, IDC_CAMERA1, m_static1);
	DDX_Control(pDX, IDC_RUNINFO1, m_runlist1);
	DDX_Control(pDX, IDC_RUNINFO2, m_runlist2);
	DDX_Control(pDX, IDC_ALARMINFO, m_alarminfo);
}

BOOL CLMCappView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CLMCappView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	
		m_Cam.m_pWnd[0] = &m_static0;
		m_Cam.creat_window(0);
		m_Cam.m_hDC[0] = m_static0.GetDC()->GetSafeHdc();

		m_Cam.m_pWnd[1] = &m_static1;
		m_Cam.creat_window(1);
		m_Cam.m_hDC[1] = m_static1.GetDC()->GetSafeHdc();

		m_runlist1.SetExtendedStyle(LVS_EX_TRACKSELECT|LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
		m_runlist1.InsertColumn(0,_T("��ǰ��Ϣ...."),0,250);
		addruninfo1(_T("�����ʼ����ɡ�"));

		m_runlist2.SetExtendedStyle(LVS_EX_TRACKSELECT|LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
		m_runlist2.InsertColumn(0,_T("��ǰ��Ϣ...."),0,250);
		addruninfo2(_T("�����ʼ����ɡ�"));

		SetTimer(0,1000,0);
}

void CLMCappView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLMCappView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
}


// CLMCappView ���

#ifdef _DEBUG
void CLMCappView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLMCappView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLMCappDoc* CLMCappView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLMCappDoc)));
	return (CLMCappDoc*)m_pDocument;
}
#endif //_DEBUG


// CLMCappView ��Ϣ�������


int CLMCappView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	

	return 0;
}


HBRUSH CLMCappView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	int nID = pWnd->GetDlgCtrlID();
	if(nID== IDC_ALARMINFO)
	{	
		pDC->SetBkMode(TRANSPARENT);

		if (!m_logic.alarm)
		{		
			pDC->SetTextColor(RGB(0,0,255));
		}
		else if (m_logic.alarm)
		{
			pDC->SetTextColor(RGB(205,0,0));
		}
	}
	pDC->SetBkMode(TRANSPARENT);
	return theApp.m_brush;//hbr;
}
void CLMCappView::addruninfo1(CString str)
{
	CString str1;
	CTime tic1 = CTime::GetCurrentTime();
	str1=tic1.Format("%H:%M:%S"); 
	int k = m_runlist1.GetItemCount();
	if (k>1000)
	{
		m_runlist1.DeleteAllItems();
	}
	m_runlist1.InsertItem(k,str1+_T(" ")+str);
	m_runlist1.EnsureVisible(k,true);
}
void CLMCappView::addruninfo2(CString str)
{
	CString str1;
	CTime tic1 = CTime::GetCurrentTime();
	str1=tic1.Format("%H:%M:%S"); 
	int k = m_runlist2.GetItemCount();
	if (k>1000)
	{
		m_runlist2.DeleteAllItems();
	}
	m_runlist2.InsertItem(k,str1+_T(" ")+str);
	m_runlist2.EnsureVisible(k,true);
}
void CLMCappView::AddStep(int &step)
{
	if (!m_logic.stop&&!m_logic.alarm)
	{
		step++;
	}
}

void CLMCappView::OnTimer(UINT_PTR nIDEvent)
{
	   CString str,str1;

		str  = _T("");
		if (!m_logic.alarm)
		{
			str = _T("�豸����������");
		}
		else
		{
			if (m_logic.A0)//���ױ���
			{ 
				str+= _T("1���������ױ�����\r\n");
			}
			if (m_logic.A1)//���ױ���
			{ 
				str+= _T("2���������ױ�����\r\n");
			}
			if (m_logic.Cam_measure_alarm[0])
			{ 
				str+= _T("1����λ������\r\n");
			}
			if (m_logic.Cam_measure_alarm[1])
			{ 
				str+= _T("2����λ������\r\n");
			}
			for (int k = 0;k<MOTOR_NUM;k++)
			{
				if (m_logic.SVON[k])
				{	
					str1.Format(_T("��%d������\r\n"),k+1);
					str+=str1;
				}
				if (m_logic.server_on[k])
				{
					str1.Format(_T("��%dδ�ϵ磡\r\n"),k+1);
					str+=str1;
				}
			}
			if (str ==_T(""))
			{
				str =_T("������ť���������");
			}
			//if (!m_logic.readout(0,M23))//--fengmingqi 
			//{
			//	m_logic.Set(0,M23);
			//	Sleep(50);
			//	m_logic.Reset(0,M23);
			//	Sleep(3000);
			//}
		}
		if(m_logic.stop)
		{
			if (!m_logic.readout(0,M20))//
			{
				m_logic.Set(0,M20);//---------ֹͣ��
				m_logic.Reset(0,M21);//----------������
			}
			else
			{
				m_logic.Reset(0,M20);//---------ֹͣ��
			}
		}
		if (m_logic.start)
		{
			if (!m_logic.readout(0,M21))//
			{
				m_logic.Set(0,M21);//---------������
				m_logic.Reset(0,M20);//-------ֹͣ��
			}
		}
		if (m_logic.readout(0,M23))//--fengmingqi 
		{
			m_logic.Reset(0,M23);
		}

		m_alarminfo.SetWindowTextW(str);
		//Sleep(300);
		//str  = _T("");
		//p->m_alarminfo.SetWindowTextW(str);
	CFormView::OnTimer(nIDEvent);
}


void CLMCappView::OnClose()
{
	KillTimer(0);

	CFormView::OnClose();
}