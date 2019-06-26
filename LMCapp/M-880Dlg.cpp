
// M-880Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LMCapp.h"
#include "M-880Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>
#include "Logic.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')


// CM880Dlg 对话框


 

CM880Dlg::CM880Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CM880Dlg::IDD, pParent)
	, m_hibnum(-1)
	, m_nFirstpbCol(1)
	, m_nfirstHdCol(1)
	, m_nlastHdCol(0)
	, m_readresTemp(0)
	, m_readLeftJsTemp(0)
	, m_readRightJsTemp(0)
	, m_setResTemp(0)
	, m_setLeftJsTemp(0)
	, m_setRightJsTemp(0)
	, m_wavefile(_T(""))
	, m_changeVol(0)
	, m_HDnumOnbar(1)
	, m_auto_fire_frez(5000)
	, m_ydpi(323)
	, m_encodes_perin(12700)//12700)
	, m_imageFile(_T(""))
	, m_repeatTimes(1)
	, m_pageLen(0)
	, m_startydelayjet(1)
	, m_stopydelayjet(10)
	, m_delaypiexs(5)
	, m_inklevle1(0)
	, m_inklevle2(0)
	, m_inklevle3(0)
	, m_inklevle4(0)
	, m_inkpressure1(0)
	, m_inkpressure2(0)
	, m_enpos(0)
	, m_setpos(0)
	, m_fire_count(200)
	, m_xdpi(300)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM880Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HIBNUM, m_hibnum);
	DDX_Text(pDX, IDC_NFPBCOL, m_nFirstpbCol);
	DDX_Text(pDX, IDC_NFHDCOL, m_nfirstHdCol);
	DDX_Text(pDX, IDC_NLHDCOL, m_nlastHdCol);
	DDX_Text(pDX, IDC_GETRES, m_readresTemp);
	DDX_Text(pDX, IDC_GETLEFTJS, m_readLeftJsTemp);
	DDX_Text(pDX, IDC_GETRIGHTJS, m_readRightJsTemp);
	DDX_Text(pDX, IDC_SETRES, m_setResTemp);
	DDX_Text(pDX, IDC_SETLEFTJS, m_setLeftJsTemp);
	DDX_Text(pDX, IDC_SETRIGHTJS, m_setRightJsTemp);
	DDX_Text(pDX, IDC_FILENAME, m_wavefile);
	DDX_Text(pDX, IDC_WAVEVOL, m_changeVol);
	DDX_Control(pDX, IDC_HIBCOMBO, m_HibCombo);
	DDX_Text(pDX, IDC_PRINTBARHD, m_HDnumOnbar);
	DDX_Text(pDX, IDC_FIREFREZ, m_auto_fire_frez);
	DDX_Text(pDX, IDC_YDPI, m_ydpi);
	DDX_Text(pDX, IDC_ENCODERES, m_encodes_perin);
	DDX_Control(pDX, IDC_DOTSOURCECOMBO, m_dottype);
	DDX_Text(pDX, IDC_IMAGEFILE, m_imageFile);
	DDX_Text(pDX, IDC_PRINTTIMES, m_repeatTimes);
	DDX_Text(pDX, IDC_PAGELEN, m_pageLen);
	DDX_Text(pDX, IDC_YDELAYJETF, m_startydelayjet);
	DDX_Text(pDX, IDC_YDELAYJETE, m_stopydelayjet);
	DDX_Text(pDX, IDC_YDELAYPIEXS, m_delaypiexs);
	DDX_Text(pDX, IDC_INKLEVEL1, m_inklevle1);
	DDX_Text(pDX, IDC_INKLEVEL2, m_inklevle2);
	DDX_Text(pDX, IDC_INKLEVEL3, m_inklevle3);
	DDX_Text(pDX, IDC_INKLEVEL4, m_inklevle4);
	DDX_Control(pDX, IDC_WAVECOMBO, m_wave_combo);
	DDX_Text(pDX, IDC_ENPOS, m_enpos);
	DDX_Text(pDX, IDC_ENPOS2, m_setpos);
	DDX_Control(pDX, IDC_WAVELIST, m_Wave_list);
	DDX_Text(pDX, IDC_COUNTS, m_fire_count);
	DDX_Text(pDX, IDC_XDPI, m_xdpi);
}

BEGIN_MESSAGE_MAP(CM880Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INIT, &CM880Dlg::OnBnClickedInit)
	ON_BN_CLICKED(IDC_ADDTOPRINTBAR, &CM880Dlg::OnBnClickedAddtoprintbar)
	ON_BN_CLICKED(IDC_CONFIGPRINTBAR, &CM880Dlg::OnBnClickedConfigprintbar)
	ON_BN_CLICKED(IDC_SETDOT, &CM880Dlg::OnBnClickedSetdot)
	ON_BN_CLICKED(IDC_GETTEMP, &CM880Dlg::OnBnClickedGettemp)
	ON_BN_CLICKED(IDC_SETTEMP, &CM880Dlg::OnBnClickedSettemp)
	ON_BN_CLICKED(IDC_FINDFILE, &CM880Dlg::OnBnClickedFindfile)
	ON_BN_CLICKED(IDC_SETVOL, &CM880Dlg::OnBnClickedSetvol)
	ON_BN_CLICKED(IDC_SETWAVEFILE, &CM880Dlg::OnBnClickedSetwavefile)
	ON_BN_CLICKED(IDC_GETIMGPATH, &CM880Dlg::OnBnClickedGetimgpath)
	ON_BN_CLICKED(IDC_STARTPRINT, &CM880Dlg::OnBnClickedStartprint)
	ON_BN_CLICKED(IDC_AUTOFIRECHECK, &CM880Dlg::OnBnClickedAutofirecheck)
	ON_BN_CLICKED(IDC_SETYDELAY, &CM880Dlg::OnBnClickedSetydelay)
	ON_BN_CLICKED(IDC_GETINKLEVEL, &CM880Dlg::OnBnClickedGetinklevel)
	ON_BN_CLICKED(IDC_SAVEWAEFILE, &CM880Dlg::OnBnClickedSavewaefile)
	ON_BN_CLICKED(IDC_SETTEMP2, &CM880Dlg::OnBnClickedSettemp2)
	ON_BN_CLICKED(IDC_GETPOS, &CM880Dlg::OnBnClickedGetpos)
	ON_BN_CLICKED(IDC_SETPOS2, &CM880Dlg::OnBnClickedSetpos2)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_OPENMOTORDLG, &CM880Dlg::OnBnClickedOpenmotordlg)
	ON_BN_CLICKED(IDC_SETDROPSIZE, &CM880Dlg::OnBnClickedSetdropsize)
	ON_BN_CLICKED(IDC_GETINFO, &CM880Dlg::OnBnClickedGetinfo)
	ON_BN_CLICKED(IDC_SHOWHCD, &CM880Dlg::OnBnClickedShowhcd)
	ON_BN_CLICKED(IDC_OPENCMD, &CM880Dlg::OnBnClickedOpencmd)
	ON_BN_CLICKED(IDC_OPENCMD2, &CM880Dlg::OnBnClickedOpencmd2)
	ON_BN_CLICKED(IDC_STOPPRINT, &CM880Dlg::OnBnClickedStopprint)
	ON_BN_CLICKED(IDC_PACKTOFILE, &CM880Dlg::OnBnClickedPacktofile)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_GETTEMP2, &CM880Dlg::OnBnClickedGettemp2)
	ON_BN_CLICKED(IDC_STARTPRINT3, &CM880Dlg::OnBnClickedStartprint3)
	ON_BN_CLICKED(IDC_SETDROPSIZE2, &CM880Dlg::OnBnClickedSetdropsize2)
	ON_BN_CLICKED(IDC_SETDROPSIZE3, &CM880Dlg::OnBnClickedSetdropsize3)
	ON_BN_CLICKED(IDC_STARTPRINT4, &CM880Dlg::OnBnClickedStartprint4)
	ON_BN_CLICKED(IDC_AUTOFIRECHECK2, &CM880Dlg::OnBnClickedAutofirecheck2)
	ON_BN_CLICKED(IDC_GETIMGPATH2, &CM880Dlg::OnBnClickedGetimgpath2)
	ON_BN_CLICKED(IDC_GETIMGPATH3, &CM880Dlg::OnBnClickedGetimgpath3)
	ON_BN_CLICKED(IDC_STARTPRINT5, &CM880Dlg::OnBnClickedStartprint5)
	ON_BN_CLICKED(IDC_GETIMGPATH4, &CM880Dlg::OnBnClickedGetimgpath4)
	ON_BN_CLICKED(IDC_STARTPRINT6, &CM880Dlg::OnBnClickedStartprint6)
	ON_BN_CLICKED(IDC_USEHEAD1, &CM880Dlg::OnBnClickedUsehead1)
	ON_BN_CLICKED(IDC_USEHEAD2, &CM880Dlg::OnBnClickedUsehead2)
	ON_BN_CLICKED(IDC_USEHEAD3, &CM880Dlg::OnBnClickedUsehead3)
	ON_CBN_SELCHANGE(IDC_HIBCOMBO, &CM880Dlg::OnCbnSelchangeHibcombo)
END_MESSAGE_MAP()


// CM880Dlg 消息处理程序

BOOL CM880Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	AllocConsole();
	freopen("CONOUT$","w",stdout);             // 重定向输出
	ink_levle[0] = 0;
	ink_levle[1] = 0;
	ink_levle[2] = 0;
	ink_levle[3] = 0;

	m_dottype.AddString(_T("hibAutoFire"));
	m_dottype.AddString(_T("hibQuadEncoder"));
	m_dottype.AddString(_T("hibExternalDotClock"));
	m_dottype.AddString(_T("hibQuadEncoderPos"));
	m_dottype.SetCurSel(3);

	m_wave_combo.AddString(_T("1"));
	m_wave_combo.AddString(_T("2"));
	m_wave_combo.AddString(_T("3"));
	m_wave_combo.SetCurSel(0);
	CButton *b_tn = (CButton* )GetDlgItem(IDC_CHECKUSEMTHIB);
	b_tn->SetCheck(true);
	b_tn = (CButton*)GetDlgItem(IDC_CHECKENSTART);
	b_tn->SetCheck(true);
	b_tn = (CButton*)GetDlgItem(IDC_CHECKENSTOP);
	b_tn->SetCheck(false);
	b_tn = (CButton*)GetDlgItem(IDC_USEHEAD1);
	b_tn->SetCheck(m_XDM.isUseHead[0]);
	b_tn = (CButton*)GetDlgItem(IDC_USEHEAD2);
	b_tn->SetCheck(m_XDM.isUseHead[1]);
	b_tn = (CButton*)GetDlgItem(IDC_USEHEAD3);
	b_tn->SetCheck(m_XDM.isUseHead[2]);
	stopprint =false;
	m_hibnum = m_XDM._numHibs;

	hbrush = CreateSolidBrush(RGB(213,228,242));//RGB(0xE0,0xFF,0xFF));

	 m_Wave_list.InsertColumn(0,_T("节点"),0,40);
	 m_Wave_list.InsertColumn(1,_T("时间（us）"),0,80);
	 m_Wave_list.InsertColumn(2,_T("电压（v）"),0,80);
	 m_Wave_list.InsertColumn(3,_T("drive"),0,50);
	 m_Wave_list.InsertColumn(4,_T("connect"),0,50);
	 m_Wave_list.InsertColumn(5,_T("scalable"),0,50);
	 m_Wave_list.InsertColumn(6,_T("ref"),0,50);
	 m_Wave_list.InsertColumn(7,_T("nmreg"),0,50);
	UpdateData(FALSE);
	isprinting =false;
	OnBnClickedInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CM880Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	//{
	//	CAboutDlg dlgAbout;
	//	dlgAbout.DoModal();
	//}
	//else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CM880Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CM880Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM880Dlg::OnBnClickedInit()
{
	if(!m_XDM.initHib())
		m_hibnum =-1;
	else
		m_hibnum = m_XDM._numHibs;
	UpdateData(FALSE);
	m_HibCombo.Clear();
	CString str;
	for (int k = 0;k<m_hibnum;k++)
	{
		str.Format(_T("Hibnum%d"),k+1);
		m_HibCombo.AddString(str);
	}
	m_HibCombo.SetCurSel(0);
}


void CM880Dlg::OnBnClickedAddtoprintbar()
{
	int count =0;
	for (int k = 0;k<3;k++)
	{
		if (m_XDM.isUseHead[k])
		{
			m_XDM.addHeadToPrintbar(1,k+1,k+1,1+count*880,1,0);
			count++;
		}
	}
}


void CM880Dlg::OnBnClickedConfigprintbar()
{
	//UpdateData();
	//if (m_hibnum ==-1)
	//{
	//	return;
	//}
	//if ( m_HDnumOnbar ==0)
	//{
	//	MessageBox(_T("参数2不能位0"));
	//}
	//m_XDM.configPrintBarHead(1,m_HDnumOnbar,m_nFirstpbCol,m_nfirstHdCol,m_nlastHdCol);
	int count =0;
	for (int k = 0;k<3;k++)
	{
		if (m_XDM.isUseHead[k])
		{
			m_XDM.configPrintBarHead(1,k+1,1+count*880,1,0);
			count++;
		}
	}
}


void CM880Dlg::OnBnClickedSetdot()
{
	UpdateData(TRUE);

	//initiallizing the dot clock Structure
	int index = m_dottype.GetCurSel();
	switch(index)
	{
	case 0:
		m_XDM.dotClockConfig.type = hibAutoFire;  
		break;
	case 1:
		m_XDM.dotClockConfig.type = hibQuadEncoder;  
		break;
	case 2:
		m_XDM.dotClockConfig.type = hibExternalDotClock;  
		break;
	case 3:
		m_XDM.dotClockConfig.type = hibQuadEncoderPos;  
		break;

	}
	  // options: hibQuadEncoder, hibAutoFire, hibExternalDotClock; hibQuadEncoderPos;
	m_XDM.dotClockConfig.fAutoFireFreqHz = 5000;   // Only used for autofire dot clock source.
	m_XDM.dotClockConfig.uPrintResDpi = m_ydpi;
	m_XDM._yImageRes = m_ydpi;

	CButton *b_tn = (CButton* )GetDlgItem(IDC_CHECKUSEMTHIB);
	bool ret = b_tn->GetCheck();
	m_XDM.dotClockConfig.bAutoFireFromMasterHib = ret;

	m_XDM.dotClockConfig.bWaveAmpPresent = true;    // Must be true to actually jet ink.
	m_XDM.dotClockConfig.bHeadReadyOverride = false; // bHeadREadyOverride

	b_tn = (CButton*)GetDlgItem(IDC_CHECKENSTART);
	ret = b_tn->GetCheck();
	m_XDM.dotClockConfig.bEnablePageStart = ret;  // Set false if dot clock gated externally or to print immediately.
	b_tn = (CButton*)GetDlgItem(IDC_CHECKENSTOP);
	ret = b_tn->GetCheck();
	m_XDM.dotClockConfig.bEnablePageStop = ret;
	m_XDM.dotClockConfig.fEncoderResolution = m_encodes_perin; //  quad encoder count per inch
	m_XDM.setupAllDotclocks(&m_XDM.dotClockConfig);
}


void CM880Dlg::OnBnClickedGettemp()
{
	m_XDM.readTemp(1,1, 1, &m_XDM.fSetResTemp);
	m_XDM.readTemp(1,1, 2, &m_XDM.fSetLeftJSTemp);
	m_XDM.readTemp(1,1, 3, &m_XDM.fSetRightJSTemp);

	m_setResTemp=m_XDM.fSetResTemp;
	m_setLeftJsTemp=m_XDM.fSetLeftJSTemp;
	m_setRightJsTemp=m_XDM.fSetRightJSTemp;
	UpdateData(FALSE);
	SetTimer(0,500,NULL);
	GetDlgItem(IDC_GETTEMP)->EnableWindow(FALSE);
}


void CM880Dlg::OnBnClickedSettemp()
{
	int index = m_HibCombo.GetCurSel()+1;//选择HIB
	UpdateData();
	m_XDM.fSetResTemp =m_setResTemp;
	m_XDM.fSetLeftJSTemp = m_setLeftJsTemp;
    m_XDM.fSetRightJSTemp = m_setRightJsTemp;
	UpdateData(FALSE);
	m_XDM.setTemp(index,1, 1, m_XDM.fSetResTemp);
	m_XDM.setTemp(index,1, 2, m_XDM.fSetLeftJSTemp);
	m_XDM.setTemp(index,1, 3, m_XDM.fSetRightJSTemp);
}


void CM880Dlg::OnBnClickedFindfile()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_SHAREAWARE|OFN_PATHMUSTEXIST,
		TEXT("波形文件(*.wfm)|*.wfm|"),NULL);
	CString m_filepath;
	CString m_filename;
	if (dlg.DoModal()!=IDOK)
		return;
	else
	{
		m_filepath = dlg.GetPathName();
		m_filename = dlg.GetFileName();
	}
	m_wavefile = m_filepath;
	UpdateData(FALSE);
}


void CM880Dlg::OnBnClickedSetvol()
{
	UpdateData();
	UpdateData(FALSE);
	m_XDM.voltageDelta = m_changeVol;
	int index = m_wave_combo.GetCurSel();
	int hibnex = m_HibCombo.GetCurSel()+1;
	m_XDM.adjustWaveformVoltage(hibnex,index+1,m_XDM.voltageDelta);
	//----更新电压值
	OnBnClickedSavewaefile();
}


void CM880Dlg::OnBnClickedSetwavefile()
{
	int hibnex = m_HibCombo.GetCurSel()+1;
	if (m_wavefile ==_T(""))
	{
		return;
	}
	string str = (CStringA)m_wavefile;
	const char *p = str.c_str();
	char q[256];
	strcpy(q,p);
	int index = m_wave_combo.GetCurSel();
	m_XDM.loadWaveform(hibnex,index+1,q);
}


void CM880Dlg::OnBnClickedGetimgpath()
{
	//UpdateData();
	//UpdateData(FALSE);
	//CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_SHAREAWARE|OFN_PATHMUSTEXIST,
	//	TEXT("bmp文件(*.bmp)|*.bmp|所有文件(*)|*|"),NULL);
	//CString m_filepath;
	//CString m_filename;
	//if (dlg.DoModal()!=IDOK)
	//	return;
	//else
	//{
	//	m_filepath = dlg.GetPathName();
	//	m_filename = dlg.GetFileName();
	//}
	//m_imageFile = m_filepath;
	//UpdateData(FALSE);

	//TCHAR* pszFileName = (LPTSTR)(LPCTSTR)m_filepath;
	//CFile file;
	//if(!file.Open(pszFileName, CFile::modeRead))
	//	return ;
	//BITMAPFILEHEADER bmfHdr;
	//BITMAPINFOHEADER IpBI;
	//file.Read(&bmfHdr,sizeof(bmfHdr));
	//file.Read(&IpBI,sizeof(IpBI));
	//file.Close();
	//image_width= IpBI.biWidth;
	//image_height = IpBI.biHeight;
	//---------------------------------
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_SHAREAWARE|OFN_PATHMUSTEXIST,
		TEXT("bmp文件(*.bmp)|*.bmp|所有文件(*)|*|"),NULL);
	CString m_filepath;
	CString m_filename;
	if (dlg.DoModal()!=IDOK)
		return;
	else
	{
		m_filepath = dlg.GetPathName();
		m_filename = dlg.GetFileName();
	}
	UpdateData();
	m_imageFile = m_filepath;
	UpdateData(FALSE);
	TCHAR* pszFileName = (LPTSTR)(LPCTSTR)m_filepath;
	CFile file;
	if(!file.Open(pszFileName, CFile::modeRead))
		return ;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER IpBI;
	RGBQUAD quad[2];

	file.Read(&bmfHdr,sizeof(bmfHdr));
	file.Read(&IpBI,sizeof(IpBI));
	file.Read(quad,sizeof(RGBQUAD)*2);
	int width = IpBI.biWidth;
	int height = IpBI.biHeight;

	image_width = width;
	image_height = height;

	int imagewidth = WIDTHBYTES(width);
	char * imgbuf = new char[WIDTHBYTES(width)*height];
	memset(imgbuf,0xff,imagewidth*height);
	file.Read(imgbuf,WIDTHBYTES(width)*height);
	file.Close();
	//拆分600DPI
	if (quad[0].rgbGreen ==0xff)//imag qu fan ;
	{
		quad[0].rgbBlue=0;
		quad[0].rgbGreen=0;
		quad[0].rgbRed=0;
		quad[0].rgbReserved=0;

		quad[1].rgbBlue=255;
		quad[1].rgbGreen=255;
		quad[1].rgbRed=255;
		quad[1].rgbReserved=0;

		for (int k = 0;k<height;k++)
		{
			for (int j = 0;j<imagewidth;j++)
			{
				imgbuf[k*imagewidth+j] = ~imgbuf[k*imagewidth+j];
			}
		}
	}


	//拆分600DPI
	int x_dpi = m_xdpi;
	int passnum = x_dpi/300;//每一大步；
	int steps = width/(880*passnum);
	int mstep = (width%(880*passnum)>0?1:0);



	int totalstep = steps+mstep;



	height +=1000;//新图前后添加空白各500行
	int stepwidth = WIDTHBYTES(880*passnum);
	char *buff = new char[stepwidth*height];//da tu

	int smallwidth = WIDTHBYTES(880);
	char *smallbuf = new char[smallwidth*height];
	int count =0;
	if (steps!=0)
	{
		for (int k = 0;k<totalstep;k++)
		{

			memset(buff,0xff,stepwidth*height);

			if (k!=totalstep-1)
			{
				for(int j = 500;j<height-500;j++)
				{
					memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,110*passnum);
				}
			}
			else
			{
				for(int j = 500;j<height-500;j++)
				{
					if (totalstep >1)
					{
						int other = (width-passnum*880*(totalstep-1))/8;///8;//imagewidth-k*110*passnum;
						if (other >110*passnum)
						{
							other =110*passnum;
							memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,other);
						}
						else 
						{
							memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,other);
							int yushu = (width-passnum*880)%8;
							BYTE mo = 0xff;
							mo = mo>>yushu;

							char result =  imgbuf[(j-500)*imagewidth+k*110*passnum+other]|mo;
							memcpy(buff+j*stepwidth+other,&result,1);
						}
					}
					else
					{
						int other = imagewidth-k*110*passnum;
						if (other >110*passnum)
						{
							other =110*passnum;
						}
						memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,other);
					}

				}
			}
			for (int pass =0;pass<passnum;pass++)
			{
				memset(smallbuf,0x00,smallwidth*height);
				for (int k1 = 0;k1<height;k1++)
				{
					for (int j1 =0;j1<110;j1++)
					{
						for (int i1 =0;i1<8;i1++)
						{
							LONG64  bitcount= ((i1*passnum+pass)+(j1)*(8*passnum));
							int  bigword = bitcount/8+k1*stepwidth;
							int  bigbit = bitcount%8;
							char movbit = 0x01;
							char rel = (buff[bigword]>>((7-bigbit)))&movbit;//(buff[bigword]&(movbit<<(7-bigbit)));
							smallbuf[j1+k1*smallwidth]|=(rel<<7-i1);// 0wei = (i1*passnum+pass)+j1*(7*pasnum)/8
						}
					}
				}
				CFile filewrite;
				CString name;
				name.Format(_T("D:\\XDPI\\%d.bmp"),count);
				pszFileName = (LPTSTR)(LPCTSTR)name;

				if(!filewrite.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
					return ;

				bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
				bmfHdr.bfSize=smallwidth*height+bmfHdr.bfOffBits;
				bmfHdr.bfType=DIB_HEADER_MARKER;
				bmfHdr.bfReserved1=0;
				bmfHdr.bfReserved2=0;

				IpBI.biBitCount=1;
				IpBI.biClrImportant=0;
				IpBI.biClrUsed=0;
				IpBI.biCompression=BI_RGB;
				IpBI.biHeight=height;
				IpBI.biPlanes=1;
				IpBI.biSize=sizeof(BITMAPINFOHEADER);
				IpBI.biSizeImage=smallwidth*height;
				IpBI.biWidth=880;

				filewrite.Write(&bmfHdr,sizeof(bmfHdr));
				filewrite.Write(&IpBI,sizeof(IpBI));
				filewrite.Write(quad,sizeof(RGBQUAD)*2);
				filewrite.Write(smallbuf,smallwidth*height);
				filewrite.Close();
				count ++;
			}



			CFile filewrite1;
			CString name;
			name.Format(_T("D:\\XDPI\\%d.bmp"),k+200);
			pszFileName = (LPTSTR)(LPCTSTR)name;

			if(!filewrite1.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
				return ;

			bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
			bmfHdr.bfSize=stepwidth*height+bmfHdr.bfOffBits;
			bmfHdr.bfType=DIB_HEADER_MARKER;
			bmfHdr.bfReserved1=0;
			bmfHdr.bfReserved2=0;

			IpBI.biBitCount=1;
			IpBI.biClrImportant=0;
			IpBI.biClrUsed=0;
			IpBI.biCompression=BI_RGB;
			IpBI.biHeight=height;
			IpBI.biPlanes=1;
			IpBI.biSize=sizeof(BITMAPINFOHEADER);
			IpBI.biSizeImage=stepwidth*height;
			IpBI.biWidth=880*passnum;
			filewrite1.Write(&bmfHdr,sizeof(bmfHdr));
			filewrite1.Write(&IpBI,sizeof(IpBI));
			filewrite1.Write(quad,sizeof(RGBQUAD)*2);
			filewrite1.Write(buff,stepwidth*height);
			filewrite1.Close();
		}
	}
	else
	{
		memset(buff,0xff,stepwidth*height);

		for(int j = 500;j<height-500;j++)
		{
			memcpy(buff+j*stepwidth,imgbuf+(j-500)*WIDTHBYTES(width),(width/8));
		}
		for (int pass =0;pass<passnum;pass++)
		{
			memset(smallbuf,0x00,smallwidth*height);
			for (int k1 = 0;k1<height;k1++)
			{
				for (int j1 =0;j1<110;j1++)
				{
					for (int i1 =0;i1<8;i1++)
					{
						LONG64  bitcount= ((i1*passnum+pass)+(j1)*(8*passnum));
						int  bigword = bitcount/8+k1*stepwidth;
						int  bigbit = bitcount%8;
						char movbit = 0x01;
						char rel = (buff[bigword]>>((7-bigbit)))&movbit;//(buff[bigword]&(movbit<<(7-bigbit)));
						smallbuf[j1+k1*smallwidth]|=(rel<<7-i1);// 0wei = (i1*passnum+pass)+j1*(7*pasnum)/8
					}
				}
			}
			CFile filewrite2;
			CString name;
			name.Format(_T("D:\\XDPI\\%d.bmp"),count);
			pszFileName = (LPTSTR)(LPCTSTR)name;

			if(!filewrite2.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
				return ;

			bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
			bmfHdr.bfSize=smallwidth*height+bmfHdr.bfOffBits;
			bmfHdr.bfType=DIB_HEADER_MARKER;
			bmfHdr.bfReserved1=0;
			bmfHdr.bfReserved2=0;

			IpBI.biBitCount=1;
			IpBI.biClrImportant=0;
			IpBI.biClrUsed=0;
			IpBI.biCompression=BI_RGB;
			IpBI.biHeight=height;
			IpBI.biPlanes=1;
			IpBI.biSize=sizeof(BITMAPINFOHEADER);
			IpBI.biSizeImage=smallwidth*height;
			IpBI.biWidth=880;

			filewrite2.Write(&bmfHdr,sizeof(bmfHdr));
			filewrite2.Write(&IpBI,sizeof(IpBI));
			filewrite2.Write(quad,sizeof(RGBQUAD)*2);
			filewrite2.Write(smallbuf,smallwidth*height);
			filewrite2.Close();
			count ++;
		}
		CFile filewrite3;
		CString name;
		name.Format(_T("D:\\XDPI\\%d.bmp"),100);
		pszFileName = (LPTSTR)(LPCTSTR)name;

		if(!filewrite3.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
			return ;

		bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
		bmfHdr.bfSize=stepwidth*height+bmfHdr.bfOffBits;
		bmfHdr.bfType=DIB_HEADER_MARKER;
		bmfHdr.bfReserved1=0;
		bmfHdr.bfReserved2=0;

		IpBI.biBitCount=1;
		IpBI.biClrImportant=0;
		IpBI.biClrUsed=0;
		IpBI.biCompression=BI_RGB;
		IpBI.biHeight=height;
		IpBI.biPlanes=1;
		IpBI.biSize=sizeof(BITMAPINFOHEADER);
		IpBI.biSizeImage=stepwidth*height;
		IpBI.biWidth=880*passnum;

		filewrite3.Write(&bmfHdr,sizeof(bmfHdr));
		filewrite3.Write(&IpBI,sizeof(IpBI));
		filewrite3.Write(quad,sizeof(RGBQUAD)*2);
		filewrite3.Write(buff,stepwidth*height);
		filewrite3.Close();

	}
	delete []buff;
	delete []smallbuf;
	delete []imgbuf;
}


void CM880Dlg::OnBnClickedStartprint()
{
	//UpdateData();
	m_repeatTimes =1;
	if (m_repeatTimes<=0)
	{
		MessageBox(_T("打印次数为0！"));
		return;
	}
	if (m_pageLen<=1)
	{
		//MessageBox(_T("打印长度错误！"));
		//return;
	}

	//OnBnClickedAddtoprintbar();
	//OnBnClickedConfigprintbar();
	//OnBnClickedSetdot();
	//if (!m_XDM.ErrorMsg())return ;
	CWinThread *thread = AfxBeginThread(Print_thread, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	thread->ResumeThread();
	cout<<"开始打印！"<<endl;
}
UINT CM880Dlg::Print_thread(LPVOID param)
{
	CM880Dlg *p = (CM880Dlg*)param;
	string str = (CStringA)p->m_imageFile;
	const char *p1 = str.c_str();
	char q[256];
	strcpy(q,p1);
	cout << endl<<q << endl;
	//----开始打印
	m_Motor.WritePort(false,0,M10,true);
	repeatCount = 0;
	m_XDM.hibStatus = hibSetEncoderPos(1, 1);//-m_Cam.calc_print_cameray
	if (!m_XDM.ErrorMsg())return 0;
	//p->m_XDM.hibStatus =hibSetPrintStartPos(1, m_Cam.print_cameray[1]/2);
	//if (!p->m_XDM.ErrorMsg())return 0;
	m_XDM.hibStatus = hibConfigPage(1, -100, 1, p->m_pageLen, 0);
	if (!m_XDM.ErrorMsg())return 0;
	m_XDM.hibStatus = hibResetGather(); 
	if (!m_XDM.ErrorMsg())return 0;
	m_XDM.hibStatus = hibClearPackedImages(1); //hibLibAPi Call to Clear the any Packed Images 
	if (!m_XDM.ErrorMsg())return 0;
	m_XDM.hibStatus = hibLoadImageFileX(1, q,m_XDM._headRes, m_XDM._yImageRes, 0, 0, 0, 0, 0); //hibLibAPi Call to Load the Image
	if (!m_XDM.ErrorMsg())return 0;
	m_XDM.hibStatus = hibPackImage(1, m_XDM._yImageRes, true); //hibLibAPi Call to Pack the Image
	if (!m_XDM.ErrorMsg())return 0;
	for (int i = 0; i < p->m_repeatTimes; i++)
	{
		/////////////////////
		//
		//  Setting up the Callbacks 
		//
		//////////////////////


		m_XDM.SetupPackedImageTransfer(1, NULL);  //Call Back Routine
		if (!m_XDM.ErrorMsg())return 0;
		m_XDM.SetFreePackedMemoryCallback(1,  (void *)(654321 + 1)); //Call Back Routine
		if (!m_XDM.ErrorMsg())return 0;

		/////////////////////
		//
		//  Print
		//
		//////////////////////


		m_XDM.hibStatus = hibEnablePrinting(); //hibLibAPi Call to run the call backs and print image data
		if (!m_XDM.ErrorMsg())return 0 ;
		//cout << endl << "Waiting for Image Transfer " << endl;
		//cout << endl << "Pass = " << i+1 << endl;
		//cout << "Start Moving the Stage !!!!!!! " << endl;
		//m_Motor.absolute_move(MOTOR15,m_Motor.PRINTOKPOS[1]);
		//m_Motor.wait_move_done(MOTOR15);
		m_XDM.hibStatus = hibWaitForImageTransferComplete(1);
		cout<<"图像传输完成！"<<endl;
		if (!m_XDM.ErrorMsg())return 0;		
		//cout << endl << "Move the Stage Back to the Start !!!!!!! " << endl;
		//m_Motor.absolute_move(MOTOR15,m_Motor.PAIZHAOPOS[1]);
		//m_Motor.wait_move_done(MOTOR15);
		repeatCount = 0; // setting the repeat count back to 0 for the image call back functions
	}
	/////////////////////
	//
	//  Finished Printing
	//
	//////////////////////
	m_Motor.WritePort(false,0,M10,false);
	cout << endl << "Reseting Gather " << endl;
	m_XDM.hibStatus = hibResetGather(); //hibLibAPi Call to reset the gather routine
	if (!m_XDM.ErrorMsg())return 0;

		cout << endl << "Clearing any Packed Image " << endl;
	m_XDM.hibStatus = hibClearPackedImages(1); //hibLibAPi Call to Clear the any Packed Images 
	if (!m_XDM.ErrorMsg())return 0;
	
	return 0;
	//cout << endl << "Finished Printing " << endl;
}

UINT CM880Dlg::SCAN_Print_thread(LPVOID param)
{
	//去打印位置；
	m_Cam.sunny_center_row=1836;
	m_Cam.sunny_center_column =2748;
	m_Motor.absolute_move(MOTOR11,359000+4150+((1798.5-1836)*m_Cam.calc0_y*1000)+((m_Cam.sunny_center_row-1836)*m_Cam.calc0_y*1000));//m_Cam.calc_print_camerax[1]);移动到正县委 反向打
	cout<<"打印高度"<< m_Cam.Print_z<<endl;
	m_Motor.absolute_move(MOTOR12,m_Cam.Print_z);//m_Cam.print_cameraz[1]);
	m_Motor.wait_move_done(MOTOR11);
	m_Motor.wait_move_done(MOTOR12);
	CM880Dlg *p = (CM880Dlg*)param;
	//----开始打印
	cout<<"image_width"<< p->image_width<<endl;
	cout<<"xdpi"<< p->m_xdpi<<endl;
    int dpi = p->m_xdpi;
	int width = p->image_width;
	int passnum = dpi/300;//每一大步；
	int steps = width/(880*passnum);
	int mstep = (width%(880*passnum)>0?1:0);
	int totalstep = steps+mstep;
	
	int count = 0;
	if (p->dingwei)
	{
	     count = passnum*totalstep-1;
	}
	else
	{
		 count = 0;
	}
	long xcurpos =0;
	//APS_get_position(MOTOR11,&xcurpos);
	//cout<<"X轴电机位置距离："<<xcurpos<<endl;
	//cout<<"X轴移动5mm(验证行进中是否有误差)："<<-5000<<endl;
	//m_Motor.relative_move(MOTOR11,-5000);
	m_Motor.WritePort(false,0,M10,true);
	int x_movepos = 0;
	cout<<"totalstep"<< totalstep<<endl;
	for (int k = 0;k<totalstep;k++)
	{
		if (p->stopprint)
		{
			break;
		}
		x_movepos = 0;
		for (int j = 0;j<passnum;j++)
		{
			if (p->stopprint)
			{
				break;
			}
			CString filepath;
			filepath.Format(_T("D:\\XDPI\\%d.bmp"),count);
			string str = (CStringA)filepath;
			const char *p1 = str.c_str();
			char q[256];
			strcpy(q,p1);
			cout << endl<<q << endl;
			repeatCount = 0;
			if (p->dingwei)
			{
				int start_pos = -430041+(25400*2*500)/m_XDM._yImageRes+12700*2+(2748-2648.5)*m_Cam.calc0_x*2000
					+(2748-m_Cam.sunny_center_column)*m_Cam.calc0_x*2000+10*2000;
				if (start_pos>=0)
				{
					cout<<"开始打印位置错误"<<endl;
					p->isprinting =false;
					return 0;
				}

				m_XDM.hibStatus = hibSetEncoderPos(1, start_pos);//-430041);//-m_Cam.calc_print_cameray[1]);
			}
			else
			{
				m_XDM.hibStatus = hibSetEncoderPos(1, -m_Cam.print_cameray[1]);//-m_Cam.calc_print_cameray
			}
			
			if (!m_XDM.ErrorMsg())return 0;
			//p->m_XDM.hibStatus =hibSetPrintStartPos(1, m_Cam.print_cameray[1]/2);
			//if (!p->m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibConfigPage(1, 1, 1, p->m_pageLen, 0);
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibResetGather(); 
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibClearPackedImages(1); //hibLibAPi Call to Clear the any Packed Images 
			if (!m_XDM.ErrorMsg())return 0;
			cout<<"m_XDM._yImageRes"<< m_XDM._yImageRes<<endl;
			cout<<"p->m_ydpi"<< p->m_ydpi<<endl;
			m_XDM.hibStatus = hibLoadImageFileX(1, q,m_XDM._headRes, m_XDM._yImageRes, 0, 0, 0, 0, 0); //hibLibAPi Call to Load the Image
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibPackImage(1, m_XDM._yImageRes, false); //hibLibAPi Call to Pack the Image
			if (!m_XDM.ErrorMsg())return 0;
			for (int i = 0; i < p->m_repeatTimes; i++)
			{
				/////////////////////
				//
				//  Setting up the Callbacks 
				//
				//////////////////////


				m_XDM.SetupPackedImageTransfer(1, NULL);  //Call Back Routine
				if (!m_XDM.ErrorMsg())return 0;
				m_XDM.SetFreePackedMemoryCallback(1,  (void *)(654321 + 1)); //Call Back Routine
				if (!m_XDM.ErrorMsg())return 0;

				/////////////////////
				//
				//  Print
				//
				//////////////////////


				m_XDM.hibStatus = hibEnablePrinting(); //hibLibAPi Call to run the call backs and print image data
				if (!m_XDM.ErrorMsg())return 0 ;
				//cout << endl << "Waiting for Image Transfer " << endl;
				//cout << endl << "Pass = " << i+1 << endl;
				//cout << "Start Moving the Stage !!!!!!! " << endl;
				m_Motor.absolute_move(MOTOR15,m_Motor.PRINTOKPOS[1]);
				m_XDM.hibStatus = hibWaitForImageTransferComplete(1);
				m_Motor.wait_move_done(MOTOR15);
				Sleep(1000);
				cout<<"图像传输完成！"<<endl;
				if (!m_XDM.ErrorMsg())return 0;		
				//cout << endl << "Move the Stage Back to the Start !!!!!!! " << endl;
				m_Motor.absolute_move(MOTOR15,m_Motor.PAIZHAOPOS[1]);
				

				int xpos = 25400/dpi;
				if (j!=passnum-1)
				{
					x_movepos+=xpos;
					if (p->dingwei)
					{
						long xcurpos =0;
						APS_get_position(MOTOR11,&xcurpos);
						cout<<"X轴电机位置距离："<<xcurpos<<endl;
						m_Motor.relative_move(MOTOR11,-xpos);
						cout<<"X轴pass距离："<<-xpos<<endl;
					}
					else
					{
						long xcurpos =0;
						APS_get_position(MOTOR11,&xcurpos);
						cout<<"X轴电机位置距离："<<xcurpos<<endl;
						m_Motor.relative_move(MOTOR11,xpos);
						cout<<"X轴pass距离："<<-xpos<<endl;
					}
				}				
				m_Motor.wait_move_done(MOTOR15);
				m_Motor.wait_move_done(MOTOR11);
				Sleep(1000);
				repeatCount = 0; // setting the repeat count back to 0 for the image call back functions
			}
			if (p->dingwei)
			{
				count--;
			}
			else
			{
				count++;
			}
			
		}
		if(k!=totalstep-1)
		{
			long xcurpos =0;
			APS_get_position(MOTOR11,&xcurpos);
			cout<<"X轴电机位置距离："<<xcurpos<<endl;
			int pos = 0;
			if (k==0)
			 pos = (int)(25400/dpi)+(p->use_last_jet_numbers*84.5)-90;
			 else
		     pos = (int)(25400/dpi)+74380-50;
			//int pos = (int)((float)((float)((float)25400/(float)300))*(float)880)-x_movepos;
			cout<<"X轴大步需移动距离：";
			//cout<<"X轴已经移动距离："<<x_movepos<<endl;
			if (p->dingwei)//手动定位反方向
			{
				m_Motor.relative_move(MOTOR11,-pos);//移动一大步
				cout<<-pos<<endl;
			}
			else
			{
				m_Motor.relative_move(MOTOR11,pos);//移动一大步
				cout<<pos<<endl;
			}
			
			m_Motor.wait_move_done(MOTOR11);
		}
	}
	p->stopprint =false;
	m_Motor.absolute_move(MOTOR11,m_Cam.print_camerax[1]);
	m_Motor.absolute_move(MOTOR12,m_Cam.Print_z);//m_Cam.print_cameraz[1]);
	m_Motor.wait_move_done(MOTOR11);
	m_Motor.wait_move_done(MOTOR12);
	if (!p->isprinting)
	{
		m_Motor.WritePort(false,0,M10,false);
	}
	cout << endl << "Reseting Gather " << endl;
	m_XDM.hibStatus = hibResetGather(); //hibLibAPi Call to reset the gather routine
	if (!m_XDM.ErrorMsg())return 0;

	cout << endl << "Clearing any Packed Image " << endl;
	m_XDM.hibStatus = hibClearPackedImages(1); //hibLibAPi Call to Clear the any Packed Images 
	if (!m_XDM.ErrorMsg())return 0;
	p->isprinting =false;
	cout<<"打印完成，多PASSS打印线程退出"<<endl;
	return 0;
}
void CM880Dlg::OnBnClickedAutofirecheck()
{
	CButton* m_btn = (CButton*)GetDlgItem(IDC_AUTOFIRECHECK);
	UpdateData();
	int ret = m_btn->GetCheck();
	if (ret)
	{
		m_Motor.absolute_move(MOTOR15,m_Motor.PRINTPOS[1]);
		m_Motor.wait_move_done(MOTOR15);
		m_XDM.autofirestart(1,m_auto_fire_frez,m_fire_count);
		Sleep(1000);
		m_XDM.autofirestop(1);
		m_Motor.absolute_move(MOTOR15,m_Motor.PAIZHAOPOS[1]);
		m_Motor.wait_move_done(MOTOR15);
		m_XDM.autofirestop(1);
	}
	else
	{
		m_XDM.autofirestop(1);
	}
}


void CM880Dlg::OnBnClickedSetydelay()
{
	UpdateData();
	if (m_startydelayjet>m_stopydelayjet)
	{
		return;
	}
	for (int k = m_startydelayjet;k<m_stopydelayjet;k++)
	{
		m_XDM.hibStatus = hibSetJetYdelay(1, 1, k, m_delaypiexs);
		if (!m_XDM.ErrorMsg())
		{
			break;
		}
	}
}


void CM880Dlg::OnBnClickedGetinklevel()
{
	int hibnex = m_HibCombo.GetCurSel()+1;
	m_XDM.getHeadInkLevels(hibnex,m_inklevle1,m_inklevle2,m_inklevle3,m_inklevle4);
	// hibGetHeadInkLevels( 1, m_inklevle1, m_inklevle2, m_inklevle3, m_inklevle4);
	UpdateData(FALSE);
}


void CM880Dlg::OnBnClickedGetpressure()
{

	m_XDM.hibStatus=hibGetHeadInkPressure(1,m_XDM.pPugre1,m_XDM.pPugre2);
	m_inkpressure1 = *m_XDM.pPugre1;
	m_inkpressure1 = *m_XDM.pPugre1;
	if (!m_XDM.ErrorMsg())return ;
	UpdateData(FALSE);
}


void CM880Dlg::OnBnClickedSavewaefile()
{
	int hibnex = m_HibCombo.GetCurSel()+1;
	char *waveformFile1 = "d:\\1.wfm";
	char *waveformFile2 = "d:\\2.wfm";
	char *waveformFile3 = "d:\\3.wfm";
	int index = m_wave_combo.GetCurSel();
	if (index == 0)
	{
		m_XDM.hibStatus =hibDumpWaveform(hibnex, index+1, waveformFile1) ;
		if (!m_XDM.ErrorMsg())return ;
	}
	if (index == 1)
	{
		m_XDM.hibStatus =hibDumpWaveform(hibnex, index+1, waveformFile2) ;
		if (!m_XDM.ErrorMsg())return ;
	}
	if (index == 2)
	{
		m_XDM.hibStatus =hibDumpWaveform(hibnex, index+1, waveformFile3) ;
		if (!m_XDM.ErrorMsg())return ;
	}
	
	int counts = hibWaveformMaxKnotCount(hibnex);
	hibWaveKnot_t *wave_knot = new hibWaveKnot_t[counts];
	m_XDM.hibStatus = hibGetWaveform(hibnex,1,wave_knot);

	m_Wave_list.DeleteAllItems();
	CString str;
   for (int k = 0;k<counts;k++)
   {
	   if (wave_knot[k].timeUs==0)
	   {
		   break;
	   }
	   str.Format(_T("%d"),k+1);
	   m_Wave_list.InsertItem(k,str);
	   str.Format(_T("%0.3f"),wave_knot[k].timeUs);
	   m_Wave_list.SetItemText(k,1,str);
	   str.Format(_T("%0.3f"),wave_knot[k].voltageV);
	   m_Wave_list.SetItemText(k,2,str);
	   if (wave_knot[k].drive == VPPx)
	   {
		   str =_T("VPPx");
	   }
	   else
	   {
		    str =_T("VSSx");;
	   }
	   m_Wave_list.SetItemText(k,3,str);
	   if (wave_knot[k].connect == VPPx)
	   {
		   str =_T("VPPx");
	   }
	   else
	   {
		   str =_T("VSSx");;
	   }
	   m_Wave_list.SetItemText(k,4,str);
	   str.Format(_T("%d"),wave_knot[k].scalable);
	   m_Wave_list.SetItemText(k,5,str);
	   str.Format(_T("%d"),wave_knot[k].reference);
	   m_Wave_list.SetItemText(k,6,str);
	   str.Format(_T("%d"),wave_knot[k].normRegion);
	   m_Wave_list.SetItemText(k,7,str);
   }
   delete []wave_knot;
}


void CM880Dlg::OnBnClickedSettemp2()
{
	int hibnex = m_HibCombo.GetCurSel()+1;
	m_XDM.readTemp(hibnex,1, 1, &m_XDM.fSetResTemp);
	m_XDM.readTemp(hibnex,1, 2, &m_XDM.fSetLeftJSTemp);
	m_XDM.readTemp(hibnex,1, 3, &m_XDM.fSetRightJSTemp);

	 m_setResTemp=m_XDM.fSetResTemp;
	 m_setLeftJsTemp=m_XDM.fSetLeftJSTemp;
	 m_setRightJsTemp=m_XDM.fSetRightJSTemp;
	UpdateData(FALSE);
}


void CM880Dlg::OnBnClickedGetsize()
{
	int size[880]={1};
	m_XDM.hibStatus =  hibGetJetDropSizes (1,880,size);
	if (!m_XDM.ErrorMsg())return ;
}


void CM880Dlg::OnBnClickedGetsize2()
{
	int size[880]={1};
	for (int k = 0;k<880;k++)
	{
		size[k] = 2;
	}
	m_XDM.hibStatus =  hibSetJetDropSizes (1,880,size);
	if (!m_XDM.ErrorMsg())return ;
}


void CM880Dlg::OnBnClickedGetpos()
{
	m_XDM.hibStatus =  hibGetEncoderPos(1,&m_enpos);
	if (!m_XDM.ErrorMsg())return ;
	UpdateData(FALSE);
}


void CM880Dlg::OnBnClickedSetpos2()
{
	UpdateData();
	UpdateData(FALSE);
	m_XDM.hibStatus =  hibSetEncoderPos (1,m_setpos);
	if (!m_XDM.ErrorMsg())return ;
}


void CM880Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	if (nIDEvent ==0)
	{
		int index = m_HibCombo.GetCurSel()+1;//选择HIB
		m_XDM.readHeaterTemp(index,1,m_XDM.pCurrentResTemp);
		m_XDM.readHeaterTemp(index,2,m_XDM.pCurrentLeftJSTemp);
		m_XDM.readHeaterTemp(index,3,m_XDM.pCurrentRightJSTemp);
		m_XDM.getHeadInkLevels(index,ink_levle[0],ink_levle[1],ink_levle[2],ink_levle[3]);
		m_readresTemp = *m_XDM.pCurrentResTemp;
		str.Format(_T("%0.3f"),m_readresTemp);
		GetDlgItem(IDC_GETRES)->SetWindowTextW(str);
		m_readLeftJsTemp = *m_XDM.pCurrentLeftJSTemp;
		str.Format(_T("%0.3f"),m_readLeftJsTemp);
		GetDlgItem(IDC_GETLEFTJS)->SetWindowTextW(str);
		m_readRightJsTemp = *m_XDM.pCurrentRightJSTemp;
		str.Format(_T("%0.3f"),m_readRightJsTemp);
	GetDlgItem(IDC_GETRIGHTJS)->SetWindowTextW(str);
		m_XDM.hibStatus =  hibGetEncoderPos(index,&m_enpos);
        str.Format(_T("%d"),m_enpos);
		GetDlgItem(IDC_ENPOS)->SetWindowTextW(str);
		str.Format(_T("%d"),ink_levle[0]);
		GetDlgItem(IDC_INKLEVEL1)->SetWindowTextW(str);
		str.Format(_T("%d"),ink_levle[1]);
		GetDlgItem(IDC_INKLEVEL2)->SetWindowTextW(str);
		str.Format(_T("%d"),ink_levle[2]);
		GetDlgItem(IDC_INKLEVEL3)->SetWindowTextW(str);
		str.Format(_T("%d"),ink_levle[3]);
		GetDlgItem(IDC_INKLEVEL4)->SetWindowTextW(str);
	}
	CDialog::OnTimer(nIDEvent);
}


void CM880Dlg::OnClose()
{
	FreeConsole();
	KillTimer(0);
	m_XDM.hibStatus = hibResetGather(); //hibLibAPi Call to reset the gather routine
	if (!m_XDM.ErrorMsg())return ;

	cout << endl << "Clearing any Packed Image " << endl;
	m_XDM.hibStatus = hibClearPackedImages(1); //hibLibAPi Call to Clear the any Packed Images 
	if (!m_XDM.ErrorMsg())return ;


	m_XDM.closeHib();
	CDialog::OnClose();
}





void CM880Dlg::OnBnClickedOpenmotordlg()
{
	//M_DLG = new CMotordlg();

	//M_DLG->Create(IDD_MOTORDLG,this);
	//M_DLG->ShowWindow(TRUE);
}


void CM880Dlg::OnBnClickedSetdropsize()
{
	m_XDM.hibStatus = hibSetGrayscaleMode(1,2);
	if (!m_XDM.ErrorMsg())return ;
	int size[880]={1};
	for (int k = 0;k<880;k++)
	{
		size[k] = 2;
	}
	m_XDM.hibStatus =  hibSetJetDropSizes (1,880,size);
	if (!m_XDM.ErrorMsg())return ;
}


void CM880Dlg::OnBnClickedGetinfo()
{
	int index = m_HibCombo.GetCurSel()+1;//选择HIB
	headHcdMisc_t *pMiscInfo = new headHcdMisc_t;
	m_XDM.hibStatus =  hibGetHeadMisc(index, pMiscInfo) ;
	if (!m_XDM.ErrorMsg())return ;
	CString str,str1;
	str1=CString(pMiscInfo->headSn);
	str.Format( _T("喷头%d序列号："),index);
	str = str+str1+_T("\n");
	switch(pMiscInfo->headType)
	{
	case -1:
		str1 =_T("hibUnknownHead");
		break;
	case 0:
		str1 =_T("hibWorkhorseHead");
		break;
	case 1:
		str1 =_T("hibMSeriesHead");
		break;
	case 2:
		str1 =_T("hibTSeriesHead");
		break;
	}
	str = str+_T("喷头类型：")+str1+_T("\n");
	str1.Format(_T("喷孔数量：%d"),pMiscInfo->numJets);
	str = str+str1+_T("\n");
	str1.Format(_T("每英寸喷孔数量：%d"),pMiscInfo->numJetsPerInch);
	str = str+str1+_T("\n");
	str1.Format(_T("行数：%d"),pMiscInfo->numRows);
	str = str+str1+_T("\n");
	str1.Format(_T("波形数：%d"),pMiscInfo->numWaveforms);
	str = str+str1+_T("\n");
	str1.Format(_T("gsWaveformType：%d"),pMiscInfo->gsWaveformType);
	str = str+str1+_T("\n");
	str1.Format(_T("smallDropWfm：%d"),pMiscInfo->smallDropWfm);
	str = str+str1+_T("\n");
	str1.Format(_T("largeDropWfm：%d"),pMiscInfo->largeDropWfm);
	str = str+str1+_T("\n");
	str1.Format(_T("颜色数量：%d"),pMiscInfo->numColors);
	str = str+str1+_T("\n");
	str1.Format(_T("numArrays：%d"),pMiscInfo->numArrays);
	str = str+str1+_T("\n");
	str1.Format(_T("arrayColorIdx：%d,%d,%d,%d"),pMiscInfo->arrayColorIdx[0],pMiscInfo->arrayColorIdx[1],pMiscInfo->arrayColorIdx[2],pMiscInfo->arrayColorIdx[3]);
	str = str+str1+_T("\n");
	str1.Format(_T("arrayColumnIdx：%d,%d,%d,%d"),pMiscInfo->arrayColumnIdx[0],pMiscInfo->arrayColumnIdx[1],pMiscInfo->arrayColumnIdx[2],pMiscInfo->arrayColumnIdx[3]);
	str = str+str1+_T("\n");
	str1.Format(_T("numBitsPerPixel：%d"),pMiscInfo->numBitsPerPixel);
	str = str+str1+_T("\n");
	str1.Format(_T("numImageCols：%d"),pMiscInfo->numImageCols);
	str = str+str1+_T("\n");
	str1.Format(_T("numThermalChannels：%d"),pMiscInfo->numThermalChannels);
	str = str+str1+_T("\n");
	MessageBox(str);
	delete pMiscInfo;
}


void CM880Dlg::OnBnClickedShowhcd()
{	
    char * a = "d:\\image.jpg";
	 hibDumpShadowHcdToFile(1, a) ;
	 if (!m_XDM.ErrorMsg())return ;
}


void CM880Dlg::OnBnClickedOpencmd()
{
	 AllocConsole();
	 freopen("CONOUT$","w",stdout);             // 重定向输出
}


void CM880Dlg::OnBnClickedOpencmd2()
{
	FreeConsole();
}


void CM880Dlg::OnBnClickedStopprint()
{
	m_XDM.hibStatus = hibCancelImageTransfer(1, false);
	if (!m_XDM.ErrorMsg())return ;
	stopprint =true;
	m_XDM.stopprint =true;
}


void CM880Dlg::OnBnClickedPacktofile()
{
	UpdateData();
	string str = (CStringA)m_imageFile;
	const char *p1 = str.c_str();
	char q[256];
	strcpy(q,p1);
	char *bmp[]= {q};
	char *filename = "d:\\pack.bmp";
	m_XDM.hibStatus =hibPackBmpToFile(bmp, 1, filename, m_ydpi, 1, false,0,0,0,0,0,0);
	if (!m_XDM.ErrorMsg())return ;
}


HBRUSH CM880Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	pDC->SetBkMode(TRANSPARENT);
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbrush;
}


void CM880Dlg::OnBnClickedGettemp2()
{
	KillTimer(0);
	GetDlgItem(IDC_GETTEMP)->EnableWindow(TRUE);
}


void CM880Dlg::OnBnClickedStartprint3()//多pass
{
	dingwei = false;
	m_Motor.WritePort(false,0,M13,true);
	OnBnClickedAddtoprintbar();
	OnBnClickedConfigprintbar();
	OnBnClickedSetdot();
	if (!m_XDM.ErrorMsg())return ;

	// setting up the variables
	if (m_xdpi ==0)
	{
		return;
	}
	//去打印位置；
	m_Motor.absolute_move(MOTOR11,m_Cam.print_camerax[1]);
	m_Motor.absolute_move(MOTOR12,m_Cam.print_cameraz[1]);
	m_Motor.wait_move_done(MOTOR11);
	m_Motor.wait_move_done(MOTOR12);
	cout<<"开始扫描打印打印！"<<endl;
	CWinThread *thread = AfxBeginThread(SCAN_Print_thread, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	thread->ResumeThread();
}


void CM880Dlg::OnBnClickedSetdropsize2()
{
	m_XDM.hibStatus = hibSetGrayscaleMode(1,1);
	if (!m_XDM.ErrorMsg())return ;
	int size[880]={1};
	for (int k = 0;k<880;k++)
	{
		size[k] = 1;
	}
	m_XDM.hibStatus =  hibSetJetDropSizes (1,880,size);
	if (!m_XDM.ErrorMsg())return ;
}


void CM880Dlg::OnBnClickedSetdropsize3()
{
	m_XDM.hibStatus = hibSetGrayscaleMode(1,0);
	if (!m_XDM.ErrorMsg())return ;
	int size[880]={1};
	for (int k = 0;k<880;k++)
	{
		size[k] = 2;
	}
	m_XDM.hibStatus =  hibSetJetDropSizes (1,880,size);
	if (!m_XDM.ErrorMsg())return ;
}


void CM880Dlg::OnBnClickedStartprint4()
{
	dingwei =true;
	m_Motor.WritePort(false,0,M13,true);
	OnBnClickedAddtoprintbar();
	OnBnClickedConfigprintbar();
	OnBnClickedSetdot();
	if (!m_XDM.ErrorMsg())return ;

	// setting up the variables
	if (m_xdpi ==0)
	{
		return;
	}
	//去打印位置；
	//m_Motor.absolute_move(MOTOR11,359000);//m_Cam.calc_print_camerax[1]);移动到正县委 反向打
	//m_Motor.absolute_move(MOTOR12,m_Cam.Print_z);//m_Cam.print_cameraz[1]);
	//m_Motor.wait_move_done(MOTOR11);
	//m_Motor.wait_move_done(MOTOR12);
	cout<<"开始扫描打印打印！"<<endl;
	use_last_jet_numbers = 80;
	//CWinThread *thread = AfxBeginThread(SCAN_Print_thread, this,
	CWinThread *thread = AfxBeginThread(m_XDM.mulit_Head_thread, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	thread->ResumeThread();
}
void CM880Dlg::auto_print()
{
	dingwei =true;
	isprinting = true;
	m_Motor.WritePort(false,0,M13,true);//编码器继电器
	//OnBnClickedAddtoprintbar();
	//OnBnClickedConfigprintbar();
	//OnBnClickedSetdot();
	if (!m_XDM.ErrorMsg())

	{
		isprinting =false;
		return ;
	}

	// setting up the variables
	if (m_xdpi ==0)
	{
		isprinting =false;
		return;
	}
	cout<<"开始扫描打印打印！"<<endl;
	CWinThread *thread = AfxBeginThread(SCAN_Print_thread, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	thread->ResumeThread();
}

void CM880Dlg::OnBnClickedAutofirecheck2()
{
	CButton* m_btn = (CButton*)GetDlgItem(IDC_AUTOFIRECHECK2);
	UpdateData();
	int ret = m_btn->GetCheck();
	if (ret)
	{
		//m_Motor.absolute_move(MOTOR15,m_Motor.PRINTPOS[1]);
		//m_Motor.wait_move_done(MOTOR15);
		m_XDM.autofirestart(1,m_auto_fire_frez,m_fire_count);
		//Sleep(1000);
		//m_XDM.autofirestop(1);
		//m_Motor.absolute_move(MOTOR15,m_Motor.PAIZHAOPOS[1]);
		//m_Motor.wait_move_done(MOTOR15);
	}
	else
	{
		m_XDM.autofirestop(1);
	}
}


void CM880Dlg::OnBnClickedGetimgpath2()
{
	chaifen(10);
}
void CM880Dlg::OnBnClickedGetimgpath3()
{
	chaifen(15);
}

void CM880Dlg::chaifen(int laststep_use_words)
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_SHAREAWARE|OFN_PATHMUSTEXIST,
		TEXT("bmp文件(*.bmp)|*.bmp|所有文件(*)|*|"),NULL);
	CString m_filepath;
	CString m_filename;
	if (dlg.DoModal()!=IDOK)
		return;
	else
	{
		m_filepath = dlg.GetPathName();
		m_filename = dlg.GetFileName();
	}
	UpdateData();
	m_imageFile = m_filepath;
	UpdateData(FALSE);
	m_XDM.xdm_chaifen(laststep_use_words,m_xdpi,m_XDM.usehead_numbers,m_filepath);
	//TCHAR* pszFileName = (LPTSTR)(LPCTSTR)m_filepath;
	//CFile file;
	//if(!file.Open(pszFileName, CFile::modeRead))
	//	return ;
	//BITMAPFILEHEADER bmfHdr;
	//BITMAPINFOHEADER IpBI;
	//RGBQUAD quad[2];

	//file.Read(&bmfHdr,sizeof(bmfHdr));
	//file.Read(&IpBI,sizeof(IpBI));
	//file.Read(quad,sizeof(RGBQUAD)*2);
	//int width = IpBI.biWidth;
	//int height = IpBI.biHeight;

	//image_width = width;
	//image_height = height;

	//int imagewidth = WIDTHBYTES(width);
	//char * imgbuf = new char[WIDTHBYTES(width)*height];
	//memset(imgbuf,0xff,imagewidth*height);
	//file.Read(imgbuf,WIDTHBYTES(width)*height);
	//file.Close();
	////拆分600DPI
	//if (quad[0].rgbGreen ==0xff)//imag qu fan ;
	//{
	//	quad[0].rgbBlue=0;
	//	quad[0].rgbGreen=0;
	//	quad[0].rgbRed=0;
	//	quad[0].rgbReserved=0;

	//	quad[1].rgbBlue=255;
	//	quad[1].rgbGreen=255;
	//	quad[1].rgbRed=255;
	//	quad[1].rgbReserved=0;

	//	for (int k = 0;k<height;k++)
	//	{
	//		for (int j = 0;j<imagewidth;j++)
	//		{
	//			imgbuf[k*imagewidth+j] = ~imgbuf[k*imagewidth+j];
	//		}
	//	}
	//}


	////拆分600DPI
	//int x_dpi = m_xdpi;
	//int passnum = x_dpi/300;//每一大步；
	//int steps = width/(880*passnum);
	//int mstep = (width%(880*passnum)>0?1:0);



	//int totalstep = steps+mstep;



	//height +=1000;//新图前后添加空白各500行
	//int stepwidth = WIDTHBYTES(880*passnum);
	//char *buff = new char[stepwidth*height];//da tu

	//int smallwidth = WIDTHBYTES(880);
	//char *smallbuf = new char[smallwidth*height];
	//int count =0;
	//char *zero = new char[laststep_use_words];
	//char *old = new char[laststep_use_words];
	//if (steps!=0)
	//{
	//	for (int k = 0;k<totalstep;k++)
	//	{

	//		memset(buff,0xff,stepwidth*height);

	//		if (k!=totalstep-1)
	//		{
	//			for(int j = 500;j<height-500;j++)
	//			{
	//				memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,110*passnum);
	//			}
	//		}
	//		else
	//		{
	//			for(int j = 500;j<height-500;j++)
	//			{
	//				if (totalstep >1)
	//				{
	//					int other = (width-passnum*880*(totalstep-1))/8;///8;//imagewidth-k*110*passnum;
	//					if (other >110*passnum)
	//					{
	//						other =110*passnum;
	//						memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,other);
	//					}
	//					else 
	//					{
	//						memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,other);
	//						int yushu = (width-passnum*880)%8;
	//						BYTE mo = 0xff;
	//						mo = mo>>yushu;

	//						char result =  imgbuf[(j-500)*imagewidth+k*110*passnum+other]|mo;
	//						memcpy(buff+j*stepwidth+other,&result,1);
	//					}
	//				}
	//				else
	//				{
	//					int other = imagewidth-k*110*passnum;
	//					if (other >110*passnum)
	//					{
	//						other =110*passnum;
	//					}
	//					memcpy(buff+j*stepwidth,imgbuf+(j-500)*imagewidth+k*110*passnum,other);
	//				}

	//			}
	//		}
	//		for (int pass =0;pass<passnum;pass++)
	//		{
	//			memset(smallbuf,0x00,smallwidth*height);
	//			if (k!=totalstep-1)
	//			{
	//				for (int k1 = 0;k1<height;k1++)
	//				{
	//					for (int j1 =0;j1<110;j1++)
	//					{
	//						for (int i1 =0;i1<8;i1++)
	//						{
	//							LONG64  bitcount= ((i1*passnum+pass)+(j1)*(8*passnum));
	//							int  bigword = bitcount/8+k1*stepwidth;
	//							int  bigbit = bitcount%8;
	//							char movbit = 0x01;
	//							char rel = (buff[bigword]>>((7-bigbit)))&movbit;//(buff[bigword]&(movbit<<(7-bigbit)));
	//							smallbuf[j1+k1*smallwidth]|=(rel<<7-i1);// 0wei = (i1*passnum+pass)+j1*(7*pasnum)/8
	//						}
	//					}
	//				}
	//			}
	//			else
	//			{
	//				for (int k1 = 0;k1<height;k1++)
	//				{
	//					for (int j1 =0;j1<110;j1++)
	//					{
	//						for (int i1 =0;i1<8;i1++)
	//						{
	//							LONG64  bitcount= ((i1*passnum+pass)+(j1)*(8*passnum));
	//							int  bigword = bitcount/8+k1*stepwidth;
	//							int  bigbit = bitcount%8;
	//							char movbit = 0x01;
	//							char rel = (buff[bigword]>>((7-bigbit)))&movbit;//(buff[bigword]&(movbit<<(7-bigbit)));
	//							smallbuf[j1+k1*smallwidth]|=(rel<<7-i1);// 0wei = (i1*passnum+pass)+j1*(7*pasnum)/8
	//						}
	//					}
	//					memset(zero,0xff,laststep_use_words);
	//					memset(old,0xff,laststep_use_words);
	//					memcpy(old,smallbuf+k1*smallwidth,laststep_use_words);
	//					memcpy(smallbuf+k1*smallwidth,zero,laststep_use_words);
	//					memcpy(smallbuf+k1*smallwidth+(110-laststep_use_words),old,laststep_use_words);
	//				}
	//			}
	//			CFile filewrite;
	//			CString name;
	//			name.Format(_T("D:\\XDPI\\%d.bmp"),count);
	//			pszFileName = (LPTSTR)(LPCTSTR)name;

	//			if(!filewrite.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
	//				return ;

	//			bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
	//			bmfHdr.bfSize=smallwidth*height+bmfHdr.bfOffBits;
	//			bmfHdr.bfType=DIB_HEADER_MARKER;
	//			bmfHdr.bfReserved1=0;
	//			bmfHdr.bfReserved2=0;

	//			IpBI.biBitCount=1;
	//			IpBI.biClrImportant=0;
	//			IpBI.biClrUsed=0;
	//			IpBI.biCompression=BI_RGB;
	//			IpBI.biHeight=height;
	//			IpBI.biPlanes=1;
	//			IpBI.biSize=sizeof(BITMAPINFOHEADER);
	//			IpBI.biSizeImage=smallwidth*height;
	//			IpBI.biWidth=880;

	//			filewrite.Write(&bmfHdr,sizeof(bmfHdr));
	//			filewrite.Write(&IpBI,sizeof(IpBI));
	//			filewrite.Write(quad,sizeof(RGBQUAD)*2);
	//			filewrite.Write(smallbuf,smallwidth*height);
	//			filewrite.Close();
	//			count ++;
	//		}



	//		CFile filewrite1;
	//		CString name;
	//		name.Format(_T("D:\\XDPI\\%d.bmp"),k+200);
	//		pszFileName = (LPTSTR)(LPCTSTR)name;

	//		if(!filewrite1.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
	//			return ;

	//		bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
	//		bmfHdr.bfSize=stepwidth*height+bmfHdr.bfOffBits;
	//		bmfHdr.bfType=DIB_HEADER_MARKER;
	//		bmfHdr.bfReserved1=0;
	//		bmfHdr.bfReserved2=0;

	//		IpBI.biBitCount=1;
	//		IpBI.biClrImportant=0;
	//		IpBI.biClrUsed=0;
	//		IpBI.biCompression=BI_RGB;
	//		IpBI.biHeight=height;
	//		IpBI.biPlanes=1;
	//		IpBI.biSize=sizeof(BITMAPINFOHEADER);
	//		IpBI.biSizeImage=stepwidth*height;
	//		IpBI.biWidth=880*passnum;
	//		filewrite1.Write(&bmfHdr,sizeof(bmfHdr));
	//		filewrite1.Write(&IpBI,sizeof(IpBI));
	//		filewrite1.Write(quad,sizeof(RGBQUAD)*2);
	//		filewrite1.Write(buff,stepwidth*height);
	//		filewrite1.Close();
	//	}
	//}
	//else
	//{
	//	memset(buff,0xff,stepwidth*height);

	//	for(int j = 500;j<height-500;j++)
	//	{
	//		memcpy(buff+j*stepwidth,imgbuf+(j-500)*WIDTHBYTES(width),(width/8));
	//	}
	//	for (int pass =0;pass<passnum;pass++)
	//	{
	//		memset(smallbuf,0x00,smallwidth*height);
	//		for (int k1 = 0;k1<height;k1++)
	//		{
	//			for (int j1 =0;j1<110;j1++)
	//			{
	//				for (int i1 =0;i1<8;i1++)
	//				{
	//					LONG64  bitcount= ((i1*passnum+pass)+(j1)*(8*passnum));
	//					int  bigword = bitcount/8+k1*stepwidth;
	//					int  bigbit = bitcount%8;
	//					char movbit = 0x01;
	//					char rel = (buff[bigword]>>((7-bigbit)))&movbit;//(buff[bigword]&(movbit<<(7-bigbit)));
	//					smallbuf[j1+k1*smallwidth]|=(rel<<7-i1);// 0wei = (i1*passnum+pass)+j1*(7*pasnum)/8
	//				}
	//			}
	//		}
	//		CFile filewrite2;
	//		CString name;
	//		name.Format(_T("D:\\XDPI\\%d.bmp"),count);
	//		pszFileName = (LPTSTR)(LPCTSTR)name;

	//		if(!filewrite2.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
	//			return ;

	//		bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
	//		bmfHdr.bfSize=smallwidth*height+bmfHdr.bfOffBits;
	//		bmfHdr.bfType=DIB_HEADER_MARKER;
	//		bmfHdr.bfReserved1=0;
	//		bmfHdr.bfReserved2=0;

	//		IpBI.biBitCount=1;
	//		IpBI.biClrImportant=0;
	//		IpBI.biClrUsed=0;
	//		IpBI.biCompression=BI_RGB;
	//		IpBI.biHeight=height;
	//		IpBI.biPlanes=1;
	//		IpBI.biSize=sizeof(BITMAPINFOHEADER);
	//		IpBI.biSizeImage=smallwidth*height;
	//		IpBI.biWidth=880;

	//		filewrite2.Write(&bmfHdr,sizeof(bmfHdr));
	//		filewrite2.Write(&IpBI,sizeof(IpBI));
	//		filewrite2.Write(quad,sizeof(RGBQUAD)*2);
	//		filewrite2.Write(smallbuf,smallwidth*height);
	//		filewrite2.Close();
	//		count ++;
	//	}
	//	CFile filewrite3;
	//	CString name;
	//	name.Format(_T("D:\\XDPI\\%d.bmp"),100);
	//	pszFileName = (LPTSTR)(LPCTSTR)name;

	//	if(!filewrite3.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
	//		return ;

	//	bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
	//	bmfHdr.bfSize=stepwidth*height+bmfHdr.bfOffBits;
	//	bmfHdr.bfType=DIB_HEADER_MARKER;
	//	bmfHdr.bfReserved1=0;
	//	bmfHdr.bfReserved2=0;

	//	IpBI.biBitCount=1;
	//	IpBI.biClrImportant=0;
	//	IpBI.biClrUsed=0;
	//	IpBI.biCompression=BI_RGB;
	//	IpBI.biHeight=height;
	//	IpBI.biPlanes=1;
	//	IpBI.biSize=sizeof(BITMAPINFOHEADER);
	//	IpBI.biSizeImage=stepwidth*height;
	//	IpBI.biWidth=880*passnum;

	//	filewrite3.Write(&bmfHdr,sizeof(bmfHdr));
	//	filewrite3.Write(&IpBI,sizeof(IpBI));
	//	filewrite3.Write(quad,sizeof(RGBQUAD)*2);
	//	filewrite3.Write(buff,stepwidth*height);
	//	filewrite3.Close();

	//}
	//delete []buff;
	//delete []smallbuf;
	//delete []imgbuf;
	//delete[]zero;
	//delete[]old;
}



void CM880Dlg::OnBnClickedStartprint5()
{
	dingwei =true;
	m_Motor.WritePort(false,0,M13,true);
	OnBnClickedAddtoprintbar();
	OnBnClickedConfigprintbar();
	OnBnClickedSetdot();
	if (!m_XDM.ErrorMsg())return ;

	// setting up the variables
	if (m_xdpi ==0)
	{
		return;
	}
	//去打印位置；
	//m_Motor.absolute_move(MOTOR11,359000);//m_Cam.calc_print_camerax[1]);移动到正县委 反向打
	//m_Motor.absolute_move(MOTOR12,m_Cam.Print_z);//m_Cam.print_cameraz[1]);
	//m_Motor.wait_move_done(MOTOR11);
	//m_Motor.wait_move_done(MOTOR12);
	cout<<"开始扫描打印打印！"<<endl;
	use_last_jet_numbers = 120;
	CWinThread *thread = AfxBeginThread(SCAN_Print_thread, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	thread->ResumeThread();
}


void CM880Dlg::OnBnClickedGetimgpath4()
{
	chaifen(75);
}


void CM880Dlg::OnBnClickedStartprint6()
{
	dingwei =true;
	m_Motor.WritePort(false,0,M13,true);
	OnBnClickedAddtoprintbar();
	OnBnClickedConfigprintbar();
	OnBnClickedSetdot();
	if (!m_XDM.ErrorMsg())return ;

	// setting up the variables
	if (m_xdpi ==0)
	{
		return;
	}
	//去打印位置；
	//m_Motor.absolute_move(MOTOR11,359000);//m_Cam.calc_print_camerax[1]);移动到正县委 反向打
	//m_Motor.absolute_move(MOTOR12,m_Cam.Print_z);//m_Cam.print_cameraz[1]);
	//m_Motor.wait_move_done(MOTOR11);
	//m_Motor.wait_move_done(MOTOR12);
	cout<<"开始扫描打印打印！"<<endl;
	use_last_jet_numbers = 600;
	CWinThread *thread = AfxBeginThread(SCAN_Print_thread, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	thread->ResumeThread();
}


void CM880Dlg::OnBnClickedUsehead1()
{
	m_XDM.isUseHead[0]=!m_XDM.isUseHead[0];
	CButton*b_tn = (CButton*)GetDlgItem(IDC_USEHEAD1);
	b_tn->SetCheck(m_XDM.isUseHead[0]);
	m_XDM.isUseHead[0] = true?m_XDM.usehead_numbers+1:m_XDM.usehead_numbers-1;
}


void CM880Dlg::OnBnClickedUsehead2()
{
	m_XDM.isUseHead[1]=!m_XDM.isUseHead[1];
	CButton*b_tn = (CButton*)GetDlgItem(IDC_USEHEAD2);
	b_tn->SetCheck(m_XDM.isUseHead[1]);
	m_XDM.isUseHead[1] = true?m_XDM.usehead_numbers+1:m_XDM.usehead_numbers-1;
}


void CM880Dlg::OnBnClickedUsehead3()
{
	m_XDM.isUseHead[2]=!m_XDM.isUseHead[2];
	CButton*b_tn = (CButton*)GetDlgItem(IDC_USEHEAD3);
	b_tn->SetCheck(m_XDM.isUseHead[2]);
	m_XDM.isUseHead[2] = true?m_XDM.usehead_numbers+1:m_XDM.usehead_numbers-1;
}


void CM880Dlg::OnCbnSelchangeHibcombo()
{
	if (m_hibnum>0)
	{
		OnBnClickedSavewaefile();
	}	
}
