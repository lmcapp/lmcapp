#include "StdAfx.h"
#include "Cam.h"
CCam m_Cam;
#ifdef DAHENG_USB
const int DeviceNum                     = 1;
const HV_RESOLUTION Resolution          = RES_MODE0;
const HV_SNAP_MODE SnapMode             = CONTINUATION;
const HV_BAYER_CONVERT_TYPE ConvertType = BAYER2RGB_NEIGHBOUR1;

const long Gain               = 10;
const long ExposureTint_Upper = 7;
const long ExposureTint_Lower = 1000;// 1000000;
const long ShutterDelay       = 0;
const long ADCLevel           = ADC_LEVEL4;
const int XStart              = 0;
const int YStart              = 0;
const int Width =2592 ;//1280;// 2592;
const int Height = 1944;//1024;// 1944;
const long lVBlanking         = 0;
const HV_SNAP_SPEED SnapSpeed = HIGH_SPEED;
void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
	throw except;
}

CCam::CCam(void)
{
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	CString str;
	CFile file;
	char pbuf[12];
	memset(pbuf,0,12);
	if(!file.Open(_T("c:\\LMCapp\\cameraSN.dat"),CFile::modeRead))
	{
		MessageBox(NULL,_T("���ܴ�������к��ļ���"),_T("XYY_Vision"),MB_OK|MB_ICONEXCLAMATION | MB_ICONWARNING);
		return;
	}
	file.Seek(4,CFile::begin);
	file.Read( pbuf, 12 );
	str = pbuf;
	m_strSNleft = str.Left(12);
	memset(pbuf,0,12);
	file.Seek(6,CFile::current);
	file.Read( pbuf, 12 );
	str = pbuf;
	m_strSNright = str.Left(12);


	for(int i=0;i<256;i++)
	{
		m_pLutR[i] = i;
		m_pLutG[i] = i;
		m_pLutB[i] = i;
	}

	// ����Ĭ��ֵ
	m_lHBlanking = 0;
	m_lVBlanking = 0;




	HHV hcam1=NULL;
	HHV hcam2=NULL;
	HVSTATUS status1 = BeginHVDevice(1, &hcam1);
	HVSTATUS status2 = BeginHVDevice(2, &hcam2);

	if (status1!=0 ||status2 !=0)
	{
		::MessageBox(NULL,_T("�����ʼ��ʧ�ܣ�"),_T(""),NULL);
		return ;
	}
	int nSize;
	CString strSN;
	HVGetDeviceInfo(hcam1,DESC_DEVICE_SERIESNUM,NULL,&nSize);
	BYTE* pbContext=new BYTE[nSize];
	DWORD* pdContext=(DWORD*)pbContext;
	HVGetDeviceInfo(hcam1,DESC_DEVICE_SERIESNUM,pdContext,&nSize);
	strSN=CString((char*)pbContext);
	strSN=strSN.Left(nSize);
	if(strSN==m_strSNleft)
	{
		m_hhv[0]=hcam1;
		m_hhv[1]=hcam2;		
	}
	else if(strSN==m_strSNright)
	{
		m_hhv[1]=hcam1;
		m_hhv[0]=hcam2;
	}
	else
	{
		EndHVDevice(hcam1);
		EndHVDevice(hcam2);
		::MessageBox(NULL,_T("Reading the camera's serial numbers error !"),_T("XYY_Vision"),MB_OK|MB_ICONEXCLAMATION |MB_ICONWARNING);
		delete []pdContext;
		return ;
	}
	delete []pdContext;
	readini();
	for (int k = 0;k<CAMERA_NUMBER;k++)
	{    
		initcam(k); 
		m_Layout = HVGetBayerType(k);		
	}
	
	//	���麯��ִ��״̬�����ʧ�ܣ��򷵻ش���״̬��Ϣ��
	//------------������λ��
	Row0 = 131;
	Column0 = 1183;
	Phi0 = 0;
	Length01 = 1136;
	Length02 = 2;
	Row1 = 1015;
	Column1 = 2291;
	Phi1 = 1.5708;
	Length11 = 868;
	Length12 = 2;
	read_model();
}

/*
	��ȡbayer��ʽ
*/
HV_BAYER_LAYOUT CCam::HVGetBayerType(UINT index) 
{
    int nSize = 0; 
	HVSTATUS status = STATUS_OK;;
	HV_BAYER_LAYOUT Layout;

	status = HVGetDeviceInfo(m_hhv[index], DESC_DEVICE_BAYER_LAYOUT, NULL,&nSize);	    
	if(STATUS_OK != status)
	{
		Layout = BAYER_GR;
	}
	else
	{
		BYTE *pbBayerLayout = NULL;
		pbBayerLayout = new BYTE[nSize];
		status = HVGetDeviceInfo(m_hhv[index], DESC_DEVICE_BAYER_LAYOUT, pbBayerLayout,&nSize);
		Layout = (HV_BAYER_LAYOUT)*pbBayerLayout;
		delete []pbBayerLayout; 
		pbBayerLayout=NULL;
	}
	
	return Layout;
}
CCam::~CCam(void)
{
	HVSTATUS status = STATUS_OK;

	//	�ر�������������ͷ�����������ڲ���Դ
	for (int k = 0;k<CAMERA_NUMBER;k++)
	{
		if (m_bOpen)
		{
			status = HVCloseSnap(m_hhv[k]);
			HV_VERIFY(status);

			if (HV_SUCCESS(status)) {
				m_bOpen		= FALSE;
				m_bStart	= FALSE;
			}
			status = EndHVDevice(m_hhv[k]);		
			HV_VERIFY(status);
		}
		delete []m_pRawBuffer[k];//	����ͼ�񻺳���
		delete []m_pImageBuffer[k];
	}
	//saveini();
}
bool CCam::initcam(UINT index)
{
		/*
	*	��ʼ�����������Ӳ��״̬���û�Ҳ����������λ�ó�ʼ�������������
	*	��Ӧ��֤����������Ѿ��򿪣������û���Ӧ�ó����ʼ��ʱ��
	*	ͬʱ��ʼ�����������Ӳ����
	*/
	
	//	��������������ֱ���
	HVSetResolution(m_hhv[index], Resolution);		
	

	//  ���ø�������������
	for (int i = 0;i<4;i++)
	{
		HVAGCControl(m_hhv[index], RED_CHANNEL + i, gain[index]);
	}
	
		
	//  ����ADC�ļ���
	HVADCControl(m_hhv[index], ADC_BITS, ADCLevel);

	//  ��ȡ�豸����
	HVTYPE type = UNKNOWN_TYPE;
	int size    = sizeof(HVTYPE);
	HVGetDeviceInfo(m_hhv[index],DESC_DEVICE_TYPE, &type, &size);	
	
	//  ����ͼ�񴰿ں�����ǰ�����Ȳ鿴�Ƿ���������������������ƣ�
	if (IS_USB_GV400(type))
	{
		int rate = 0;
		switch(Resolution)
		{
		case RES_MODE0:
			rate = 1;
			break;
		case RES_MODE1:
			rate = 2;
			break;
		default:
			break;
		}
		
		//GV400Ux���Ҫ��ͼ���Ⱥ�ˮƽ�����������¹�ʽ��
		//lHBlanking + Width*rate > 0x236
		//���������������������Ҫ�û���������������ͼ���Ȼ�����ˮƽ����
		
		if (m_lHBlanking + Width*rate <= 0x236)
		{
			//ȡ�������ı߽�ֵ
			DWORD pBlankSize[4];
			int nBufSize = 0;
			int nHmin = 0;
			int nHmax = 0;
			HVGetDeviceInfo(m_hhv[index],DESC_DEVICE_BLANKSIZE,NULL,&nBufSize);	
			HVGetDeviceInfo(m_hhv[index],DESC_DEVICE_BLANKSIZE,pBlankSize,&nBufSize);	
			nHmin = (int)pBlankSize[0];
			nHmax = (int)pBlankSize[2];
			int tHor = 0x236-Width*rate+1;
			
			//��ȡ��ͼ�����������ˮƽ������Сֵ
			m_lHBlanking = max(nHmin,min(tHor, nHmax));
		}

		//Ϊ��ֹ�������ò��ɹ��Ƚ�ͼ�񴰿���Ϊ���
		int nBuffSize = 0;
		HVGetDeviceInfo(m_hhv[index], DESC_RESOLUTION, NULL,&nBuffSize);	
		BYTE *pbContext = new BYTE[nBuffSize];
		DWORD *pdContext = (DWORD *)(pbContext);
		HVGetDeviceInfo(m_hhv[index], DESC_RESOLUTION, pdContext,&nBuffSize);	
		int	nMaxWid = *(pdContext + 2*Resolution);
		int nMaxHei = *(pdContext + 2*Resolution +1);		
		delete []pbContext;
		HVSetOutputWindow(m_hhv[index], 0, 0, nMaxWid, nMaxHei);
		
		//����������
		HVSetBlanking(m_hhv[index], m_lHBlanking, m_lVBlanking);
	}
	else
	{
		//����������
		HVSetBlanking(m_hhv[index], m_lHBlanking, m_lVBlanking);
	}
	
	/*
	*	��Ƶ������ڣ�����Ƶ�����Χ���������ȡֵ��Χ���������봰�ڷ�Χ���ڣ�
	*  ��Ƶ�������Ͻ�X����ʹ��ڿ��ӦΪ4�ı��������Ͻ�Y����ʹ��ڸ߶�ӦΪ2�ı���
	*	������ڵ���ʼλ��һ������Ϊ(0, 0)���ɡ�
	*/
	HVSetOutputWindow(m_hhv[index], XStart, YStart, Width, Height);
	
	//���òɼ��ٶ�
	HVSetSnapSpeed(m_hhv[index], SnapSpeed);

	//	�����ع�ʱ��
	SetExposureTime(Width, shuttertime[index], ExposureTint_Lower, m_lHBlanking, SnapSpeed, Resolution,index);
	//	m_pBmpInfo��ָ��m_chBmpBuf���������û������Լ�����BTIMAPINFO������	
	m_pBmpInfo[index]								= (BITMAPINFO *)m_chBmpBuf;
	//	��ʼ��BITMAPINFO �ṹ���˽ṹ�ڱ���bmp�ļ�����ʾ�ɼ�ͼ��ʱʹ��
	m_pBmpInfo[index]->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	ͼ���ȣ�һ��Ϊ������ڿ��
	m_pBmpInfo[index]->bmiHeader.biWidth			= Width;
	//	ͼ���ȣ�һ��Ϊ������ڸ߶�
	m_pBmpInfo[index]->bmiHeader.biHeight			= Height;
	
	/*
	*	��������һ����ͬ��
	*	���ڵ���8λ��λͼ����Ӧ������Ӧ��λͼ��ɫ��
	*/
	m_pBmpInfo[index]->bmiHeader.biPlanes			= 1;
	m_pBmpInfo[index]->bmiHeader.biBitCount		    = 24;
	m_pBmpInfo[index]->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo[index]->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo[index]->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo[index]->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo[index]->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo[index]->bmiHeader.biClrImportant	    = 0;
	
	/*
	*	����ԭʼͼ�񻺳�����һ�������洢�ɼ�ͼ��ԭʼ����
	*  һ��ͼ�񻺳�����С��������ڴ�С����Ƶ��ʽȷ����
	*/
	m_pRawBuffer[index] = new BYTE[Width * Height];
	ASSERT(m_pRawBuffer);
	
	/*
	����Bayerת����ͼ�����ݻ���
	*/
	m_pImageBuffer[index] = new BYTE[Width * Height * 3];
	ASSERT(m_pImageBuffer);
	initimage(&Image[index]);
	HVSTATUS status =STATUS_OK;

	//	�ɼ�ģʽ������ CONTINUATION(����)��TRIGGER(�ⴥ��)
	HVSetSnapMode(m_hhv[index], TRIGGER);


	if(index ==0)
		status = HVOpenSnap(m_hhv[index], SnapThreadCallback, this);	
	else
		status = HVOpenSnap(m_hhv[index], SnapThreadCallback1, this);	

	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bOpen = TRUE;		//��־�Ѿ���Snap����
	}

		/*
	 *	��������������ɼ�ͼ���ڴ�
	 */
	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer[index];
	status = HVStartSnap(m_hhv[index], ppBuf,1);

	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bStart = TRUE;
	}

	return true;
}
void CCam::setcamera(int index)
{
	//  ���ø�������������
	for (int i = 0;i<4;i++)
	{
		HVAGCControl(m_hhv[index], RED_CHANNEL + i, gain[index]);
	}
	SetExposureTime(Width, shuttertime[index], ExposureTint_Lower, m_lHBlanking, SnapSpeed, Resolution,index);
	saveini();
}

/*
����:
		SetExposureTime
�������:
		int nWindWidth			��ǰͼ����		
		int lTintUpper			�ع�ʱ��ķ��ӣ�shutter��ȡֵ
		int lTintLower			�ع�ʱ��ķ�ĸ����shutter�ĵ�λ���
								��ms:1000��s:1��
�������:
		��						
˵��:
		�����ع�ʱ�䣨�����Ĳ����������ʱ��Ƶ�ʣ�����ֵ��ȡĬ��ֵ��
*/
HVSTATUS CCam::SetExposureTime(int nWindWidth,
									 long lTintUpper,
									 long lTintLower, 
									 long HBlanking,
									 HV_SNAP_SPEED SnapSpeed, 
									 HV_RESOLUTION Resolution,UINT index)
{
	HVTYPE type = UNKNOWN_TYPE;
	int size    = sizeof(HVTYPE);
	HVGetDeviceInfo(m_hhv[index],DESC_DEVICE_TYPE, &type, &size);	

	int nOutputWid = nWindWidth;

	double dExposure = 0.0;
	double dTint = max((double)lTintUpper/(double)lTintLower,MY_ZERO);

	double lClockFreq = 0.0;  
	if (IS_USB_GV400(type))
	{
		long lTb = HBlanking;
		lTb += 0x5e;	
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 26600000.0:13300000.0; 		
		long rate = 0;

		switch(Resolution)
		{
		case RES_MODE0:
			rate = 1;
			break;
		case RES_MODE1:
			rate = 2;
			break;

		default:
			return STATUS_PARAMETER_OUT_OF_BOUND;
		}
		
		nOutputWid = nOutputWid * rate;	//width*rate
		if ((dTint * lClockFreq) <= (nOutputWid+ lTb - 255))
		{
			dExposure = 1;
		}
		else
			dExposure = ((dTint * lClockFreq) - (nOutputWid + lTb - 255) ) / (nOutputWid + lTb);				

		if (dExposure < 3) 
			dExposure = 3;
		else if (dExposure > 32766)
			dExposure = 32766;

	}
	else if( IS_USB_HV300(type))
	{
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 24000000:12000000;
		long lTb = HBlanking;
		lTb += 142;
		if(lTb<21)
			lTb = 21;
		long lP1 = 331, lP2 = 38;
		long lp4 = 316;
		if(Resolution == RES_MODE1)
		{
			lP1 = 673;
			lP2 = 22;
			lp4 = 316*2;
		}
		long lAQ = (long)(nOutputWid + lP1 + lP2 + lTb);
		long lTrow = max(lAQ,(lP1+lp4));
		dExposure = ((dTint* lClockFreq)+ lP1 - 132.0)/lTrow;	
		
		if((dExposure-(int)dExposure) >0.5)
			dExposure += 1.0;		
		if(dExposure <= 0)
			dExposure = 1;
		else if(dExposure > 1048575) 
			dExposure = 1048575;
	}
	else if(IS_USB_HV200(type))
	{
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 24000000:12000000;
		long lTb = HBlanking;
		lTb += 53;
		if(lTb<19)
			lTb = 19;
		long lAQ = (long)(nOutputWid + 305.0 + lTb);
		long lTrow = max(617,lAQ);
		dExposure = (dTint* lClockFreq + 180.0)/lTrow + 1;
		
		if((dExposure-(int)dExposure) >0.5)//��������
			dExposure += 1.0;
		if(dExposure <= 0)
			dExposure = 1;
		else if(dExposure > 16383) 
			dExposure = 16383;
	}
	else if(IS_USB_HV5051(type))
	{
		SHUTTER_UNIT_VALUE nUnit = SHUTTER_MS;
		HVSTATUS status          = STATUS_OK;

		if (lTintLower == 1000000)
		{
			nUnit = SHUTTER_US;
		}		
		//�����ع�ʱ�䵥λ
		status = HVAECControl(m_hhv[index], AEC_SHUTTER_UNIT, nUnit);
		if (!HV_SUCCESS(status))
		{
			return status;
		}
		
		//�����ع�ʱ�䡣
		return HVAECControl(m_hhv[index], AEC_SHUTTER_SPEED, lTintUpper);			
	}
	else
	{		
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 24000000:12000000;
		long lTb = HBlanking;
		lTb += 9;
		lTb -= 19;	
		if(lTb <= 0) lTb =0;
		if(((double)nOutputWid + 244.0 + lTb ) > 552)	
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 244.0 + lTb);
		else
			dExposure = ((dTint * lClockFreq)+ 180.0) / 552 ;

		if((dExposure-(int)dExposure) >0.5)
			dExposure += 1.0;
		if(dExposure <= 0)
			dExposure = 1;
		else if(dExposure > 16383) 
			dExposure = 16383;
	}

	return HVAECControl(m_hhv[index], AEC_EXPOSURE_TIME, (long)dExposure);
}
void CCam::OnSnapShot(UINT index) 
{
	//// TODO: Add your command handler code here
	//HVSetSnapMode(m_hhv[index], SnapMode);
	//HVSTATUS status = STATUS_OK;
	//CString strMsg;


	////ֻ����һ��������������ͼ������
	//BYTE *ppBuf[1];
	//ppBuf[0] = m_pRawBuffer[index];

	//status = HVSnapShot(m_hhv[index], ppBuf, 1);	
	//if (STATUS_OK < status  || status < STATUS_INTERNAL_ERROR)
	//{
	//	CString str=_T("");
	//	str.Format(_T("Error : 0x%08x"),status);
	//	::MessageBox(NULL, str , _T("Error"), MB_ICONWARNING | MB_OK);   
	//}else{
	//	HV_VERIFY(status);
	//}

	//m_bStart = true;
	//if (HV_SUCCESS(status)) {
	//	OnDrawImage(index);
	//}	
	isgetcir = true;
    HVTriggerShot(m_hhv[index]);
}
void CCam::OnSnapContinue(UINT index)
{
	HVSTATUS status = STATUS_OK;
	isgetcir =false;
	/*
	*	��ʼ������������ɼ�ͼ���ڴ�Ŀ��ƣ�
	*	ָ���ص�����SnapThreadCallback��thisָ��
	*/


	 status = STATUS_OK;
	 //	ֹͣ�ɼ�ͼ���ڴ棬�����ٴε���HVStartSnapEx��������������ɼ�
	 status = HVStopSnap(m_hhv[index]);
	 HV_VERIFY(status);
	 if (HV_SUCCESS(status)) {
		 m_bStart = FALSE;
	 }

	 HVSetSnapMode(m_hhv[index], CONTINUATION);
	/*
	 *	��������������ɼ�ͼ���ڴ�
	 */
	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer[index];
	status = HVStartSnap(m_hhv[index], ppBuf,1);

	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bStart = TRUE;
	}

}
int CALLBACK CCam::SnapThreadCallback(HV_SNAP_INFO *pInfo)//---------------------���0 �ص�����
{

	CCam *This = (CCam *)(pInfo->pParam);
	//HWND hwnd = This->m_hWnd;

	HVSTATUS status = This->GetLastStatus(0);	// ��ȡ�����ͼ��ɼ�����״̬
	
	if(!HV_SUCCESS(status)){	//����������ò��ɹ��������ֹͣͼ��ɼ���
		
		return 1;
	}
		
	if(This->dwLastStatus == 0)	// ��״ֵ̬����0ʱ����ʾ�����ͼ��ɼ������������SendMessage��ʾͼ��
	{
       This->OnDrawImage(0);
		return 1;		
	}
	return 1;
}
int CALLBACK CCam::SnapThreadCallback1(HV_SNAP_INFO *pInfo)//---------------------���0 �ص�����
{

	CCam *This = (CCam *)(pInfo->pParam);
	//HWND hwnd = This->m_hWnd;

	HVSTATUS status = This->GetLastStatus(1);	// ��ȡ�����ͼ��ɼ�����״̬
	
	if(!HV_SUCCESS(status)){	//����������ò��ɹ��������ֹͣͼ��ɼ���
		
		return 1;
	}
		
	if(This->dwLastStatus == 0)	// ��״ֵ̬����0ʱ����ʾ�����ͼ��ɼ������������SendMessage��ʾͼ��
	{
       This->OnDrawImage(1);
		return 1;		
	}
	return 1;
}
HVSTATUS CCam::GetLastStatus(UINT index)
{
	HV_ARG_GET_LAST_STATUS ArgFeature;
	ArgFeature.type = HV_LAST_STATUS_TRANSFER;

	HV_RES_GET_LAST_STATUS ResFeature;

	HVAPI_CONTROL_PARAMETER  p;
	p.pInBuf		 = &ArgFeature;
	p.dwInBufSize	 = sizeof(ArgFeature);	
	p.pOutBuf		 = &ResFeature;
	p.dwOutBufSize	 = sizeof(ResFeature);
	p.pBytesRet		 = NULL;		
	p.code			 = ORD_GET_LAST_STATUS;
	int	dwSize = sizeof(p);

	HVSTATUS status = HVCommand(m_hhv[index], CMD_HVAPI_CONTROL, &p, &dwSize);
	if(status != STATUS_OK)
	{
		TRACE("HVCommand return status is %d", status);
	}

	dwLastStatus = 0;

	if (HV_SUCCESS(status)) {
		dwLastStatus = ResFeature.status;
	}

	return status;
}
void CCam::OnDrawImage(UINT index)
{
	//strMsg.Format("Snap shot %d images totally to memory ", 1);
	//::MessageBox(NULL,strMsg, "Notice", MB_OK);
	//	��ԭʼͼ�����ݽ���Bayerת����ת����Ϊ24λ��
	//ͬʱ��ԭʼ���ݽ������·�ת
	ConvertBayer2Rgb(m_pImageBuffer[index],m_pRawBuffer[index],Width,Height,ConvertType,
		m_pLutR,m_pLutG,m_pLutB,true,m_Layout);

	//int  nWndWidth  = 0;
	//int  nWndHeight = 0;

	//// Ϊ��ͼ��׼��
	RECT objRect;
	m_pWnd[index]->GetClientRect(&objRect);	
	nWndWidth  = objRect.right  - objRect.left;
	nWndHeight = objRect.bottom - objRect.top;

	// ������ø���䣬����ͼ�����ˮ��
	//::SetStretchBltMode(m_hDC[index], COLORONCOLOR);
	//::StretchDIBits(m_hDC[index],
	//	0,						
	//	0,
	//	nWndWidth,
	//	nWndHeight,
	//	0,
	//	0,
	//	(int)Width,
	//	(int)Height,
	//	m_pImageBuffer[index],
	//	m_pBmpInfo[index],
	//	DIB_RGB_COLORS,
	//	SRCCOPY
	//	);
	dispImage(index);
	cam_row[index] = 0;cam_column[index]=0;
	if (isgetcir)
	{
		if (!USE_MOBAN)
		{
			get_circle(index,&cam_row[index],&cam_column[index]);
		}
		else
		{
			find_model(index,&cam_row[index],&cam_column[index]);
		}
	}
}
void CCam::OnStopSnap(UINT index) 
{
	// TODO: Add your command handler code here
	HVSTATUS status =STATUS_OK;
	Sleep(1);
	m_bStart = FALSE;
	//	ֹͣ�ɼ�ͼ���ڴ棬�����ٴε���HVStartSnapEx��������������ɼ�
	status = HVStopSnap(m_hhv[index]);
	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bStart = FALSE;
	}
		 HVSetSnapMode(m_hhv[index], TRIGGER);
	/*
	 *	��������������ɼ�ͼ���ڴ�
	 */
	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer[index];
	status = HVStartSnap(m_hhv[index], ppBuf,1);

	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bStart = TRUE;
	}
}
#endif // DAHENG_USB
#ifdef DAHENG_MER
void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
	throw except;
}
CCam::CCam(void)
{
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	CString str;
	char sn0[13];
	char sn1[13];
	CFile file;
	if(!file.Open(_T("c:\\LMCapp\\cameraSN.dat"),CFile::modeRead))
	{
		MessageBox(NULL,_T("���ܴ�������к��ļ���"),_T("XYY_Vision"),MB_OK|MB_ICONEXCLAMATION | MB_ICONWARNING);
		return;
	}
	file.Seek(4,CFile::begin);
	file.Read( sn0, 12 );
	sn0[12] = '\0';
	file.Seek(6,CFile::current);
	file.Read( sn1, 12 );
	sn1[12] = '\0';
	readini();
	//----��ʼ��API��
	GX_STATUS emStatus = GX_STATUS_ERROR;
	emStatus = GXInitLib();
	if (emStatus != GX_STATUS_SUCCESS)
	{
		ShowErrorString(emStatus);
		//exit(0);
	}
	emStatus = Open_camera(sn0,0);
	if (emStatus!=GX_STATUS_SUCCESS)
	{
		//exit(0);
	}
	emStatus = Open_camera(sn1,1);

	if (emStatus!=GX_STATUS_SUCCESS)
	{
		//exit(0);
	}
	read_model();
	is_save_img =false;
}
CCam::~CCam(void)
{
	GX_STATUS emStatus = GX_STATUS_ERROR;

	OnCloseDevice(0);
	OnCloseDevice(1);
	emStatus = GXCloseLib();
	//saveini();
}
GX_STATUS CCam::Open_camera(char* sn,int camera_index)
{
	int m_nOperateID = camera_index;
	int64_t   nValue   = 0;
	bool      bIsImplemented = false;
	GX_STATUS emStatus = GX_STATUS_SUCCESS;
	// ���岢��ʼ���豸�򿪲���
	GX_OPEN_PARAM stOpenParam;
	stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
	stOpenParam.openMode   = GX_OPEN_SN;
	stOpenParam.pszContent = sn;

	emStatus = GXOpenDevice(&stOpenParam, &m_hDevices[m_nOperateID]);

	GX_VERIFY(emStatus);
	m_pstCam[m_nOperateID].bIsOpen = TRUE;

	//��ȡ���Bayerת�����ͼ��Ƿ�֧�������ɫͼ��
	emStatus = GXIsImplemented(m_hDevices[m_nOperateID], GX_ENUM_PIXEL_COLOR_FILTER, &bIsImplemented);
	GX_VERIFY(emStatus);
	m_pstCam[m_nOperateID].bIsColorFilter = bIsImplemented;
	if (bIsImplemented)
	{
		emStatus = GXGetEnum(m_hDevices[m_nOperateID], GX_ENUM_PIXEL_COLOR_FILTER, &nValue);
		GX_VERIFY(emStatus);
		m_pstCam[m_nOperateID].nBayerLayout = nValue;
	}

	// ��ȡͼ���
	emStatus = GXGetInt(m_hDevices[m_nOperateID], GX_INT_WIDTH, &nValue);
	GX_VERIFY(emStatus);
	m_pstCam[m_nOperateID].nImageWidth = nValue;
	Width = nValue;
	// ��ȡͼ���
	emStatus = GXGetInt(m_hDevices[m_nOperateID], GX_INT_HEIGHT, &nValue);
	GX_VERIFY(emStatus);
	m_pstCam[m_nOperateID].nImageHeight = nValue;
	Height = nValue;

	// ��֪��ǰ���֧���ĸ�8λͼ�����ݸ�ʽ����ֱ������
	// �����豸֧�����ݸ�ʽGX_PIXEL_FORMAT_BAYER_GR8,��ɰ������´���ʵ��
	// emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, GX_PIXEL_FORMAT_BAYER_GR8);
	// VERIFY_STATUS_RET(emStatus);

	// �������ǰ��������ݸ�ʽʱ�����Ե������º�����ͼ�����ݸ�ʽ����Ϊ8Bit
	emStatus = SetPixelFormat8bit(m_hDevices[m_nOperateID]); 
	GX_VERIFY(emStatus);

	// ��ȡԭʼͼ���С
	emStatus = GXGetInt(m_hDevices[m_nOperateID], GX_INT_PAYLOAD_SIZE, &nValue);
	GX_VERIFY(emStatus);
	m_pstCam[m_nOperateID].nPayLoadSise = nValue;

	//���òɼ�ģʽ�����ɼ�
	emStatus = GXSetEnum(m_hDevices[m_nOperateID], GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
	GX_VERIFY(emStatus);

	//���ô���ģʽΪ�� 
	emStatus = GXSetEnum(m_hDevices[m_nOperateID], GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON);
	GX_VERIFY(emStatus);

	// ѡ�񴥷�ԴΪ����
	emStatus = GXSetEnum(m_hDevices[m_nOperateID],GX_ENUM_TRIGGER_SOURCE, GX_TRIGGER_SOURCE_SOFTWARE);
	GX_VERIFY(emStatus);

	//��������
	
	emStatus = GXSetInt(m_hDevices[m_nOperateID], GX_INT_GEV_HEARTBEAT_TIMEOUT, 1000*300);
	GX_VERIFY(emStatus);
	bool bIsColorFilter = m_pstCam[m_nOperateID].bIsColorFilter;
	//�����ع�
	Setcamera(m_nOperateID);

	//// ��ȡDCΪͼ����ʾ׼��UI��Դ
	//if (m_hDC[m_nOperateID] == NULL)
	//{
	//	m_hDC[m_nOperateID]   = ::GetDC(m_pWnd[m_nOperateID]->m_hWnd);
	//}

	// ��ʼ��BMPͷ��Ϣ
	m_pstCam[m_nOperateID].pBmpInfo		                        = (BITMAPINFO *)(m_pstCam[m_nOperateID].chBmpBuf);
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biSize           = sizeof(BITMAPINFOHEADER);
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biWidth			= (LONG)m_pstCam[m_nOperateID].nImageWidth;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biHeight			= (LONG)m_pstCam[m_nOperateID].nImageHeight;

	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biPlanes			= 1;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biBitCount		= bIsColorFilter ? 24 : 8; // ��ɫͼ��Ϊ24,�ڰ�ͼ��Ϊ8;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biCompression	= BI_RGB;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biClrUsed		= 0;
	m_pstCam[m_nOperateID].pBmpInfo->bmiHeader.biClrImportant	= 0;

	// �ڰ������Ҫ��ʼ����ɫ����Ϣ
	if (!bIsColorFilter)
	{
		// �ڰ������Ҫ���г�ʼ����ɫ�����
		for(int i = 0; i < 256; i++)
		{
			m_pstCam[m_nOperateID].pBmpInfo->bmiColors[i].rgbBlue	  = i;
			m_pstCam[m_nOperateID].pBmpInfo->bmiColors[i].rgbGreen	  = i;
			m_pstCam[m_nOperateID].pBmpInfo->bmiColors[i].rgbRed	  = i;
			m_pstCam[m_nOperateID].pBmpInfo->bmiColors[i].rgbReserved = i;
		}
	}

	// ���Buffer
	if(m_pstCam[m_nOperateID].pImageBuffer != NULL)
	{
		delete[]m_pstCam[m_nOperateID].pImageBuffer;
		m_pstCam[m_nOperateID].pImageBuffer = NULL;
	}

	if (m_pstCam[m_nOperateID].pRawBuffer != NULL)
	{
		delete []m_pstCam[m_nOperateID].pRawBuffer;
		m_pstCam[m_nOperateID].pRawBuffer = NULL;
	}

	// ������Դ
	m_pstCam[m_nOperateID].pRawBuffer = new BYTE[(size_t)(m_pstCam[m_nOperateID].nPayLoadSise)];
	if(m_pstCam[m_nOperateID].pRawBuffer == NULL)
	{
		::MessageBox(0,_T("������Դʧ��!"),_T(""),0);
		return GX_STATUS_ERROR;
	}

	// ����ǲ�ɫ�����Ϊ��ɫ���������Դ
	if(bIsColorFilter)
	{
		m_pstCam[m_nOperateID].pImageBuffer = new BYTE[(size_t)(m_pstCam[m_nOperateID].nImageWidth * m_pstCam[m_nOperateID].nImageHeight * 3)];
		if (m_pstCam[m_nOperateID].pImageBuffer == NULL)
		{
			::MessageBox(0,_T("������Դʧ��!"),_T(""),0);
			delete []m_pstCam[m_nOperateID].pRawBuffer;
			m_pstCam[m_nOperateID].pRawBuffer = NULL;
			return GX_STATUS_ERROR;
		}
	}

	// ����Ǻڰ������ Ϊ�ڰ����������Դ
	else
	{
		m_pstCam[m_nOperateID].pImageBuffer = new BYTE[(size_t)(m_pstCam[m_nOperateID].nImageWidth * m_pstCam[m_nOperateID].nImageHeight)];
		//m_pstCam[m_nOperateID].disp_char = new BYTE[(size_t)(m_pstCam[m_nOperateID].nImageWidth * m_pstCam[m_nOperateID].nImageHeight)];
		if (m_pstCam[m_nOperateID].pImageBuffer == NULL)
		{
			::MessageBox(0,_T("������Դʧ��!"),_T(""),0);
			delete []m_pstCam[m_nOperateID].pRawBuffer;
			m_pstCam[m_nOperateID].pRawBuffer = NULL;
			return GX_STATUS_ERROR;
		}
	}
	//ע��ص�
	initimage(&Image[m_nOperateID]);
	RegisterCallback(m_nOperateID);

	//��ʼ�ɼ�
	emStatus = GXSendCommand(m_hDevices[m_nOperateID], GX_COMMAND_ACQUISITION_START);
	GX_VERIFY(emStatus);

    return emStatus;
}

GX_STATUS CCam::SetPixelFormat8bit(GX_DEV_HANDLE hDevice)
{
	GX_STATUS emStatus    = GX_STATUS_SUCCESS;
	int64_t   nPixelSize  = 0;
	uint32_t  nEnmuEntry  = 0;
	size_t    nBufferSize = 0;
	BOOL      bIs8bit     = TRUE;

	GX_ENUM_DESCRIPTION  *pEnumDescription = NULL;
	GX_ENUM_DESCRIPTION  *pEnumTemp        = NULL;

	// ��ȡ���ص��С
	emStatus = GXGetEnum(hDevice, GX_ENUM_PIXEL_SIZE, &nPixelSize);
	if (emStatus != GX_STATUS_SUCCESS)
	{
		return emStatus;
	}

	// �ж�Ϊ8bitʱֱ�ӷ���,��������Ϊ8bit
	if (nPixelSize == GX_PIXEL_SIZE_BPP8)
	{
		return GX_STATUS_SUCCESS;
	}
	else
	{
		// ��ȡ�豸֧�ֵ����ظ�ʽö����
		emStatus = GXGetEnumEntryNums(hDevice, GX_ENUM_PIXEL_FORMAT, &nEnmuEntry);
		if (emStatus != GX_STATUS_SUCCESS)
		{
			return emStatus;
		}

		// Ϊ��ȡ�豸֧�ֵ����ظ�ʽö��ֵ׼����Դ
		nBufferSize      = nEnmuEntry * sizeof(GX_ENUM_DESCRIPTION);
		pEnumDescription = new GX_ENUM_DESCRIPTION[nEnmuEntry];

		// ��ȡ֧�ֵ�ö��ֵ
		emStatus = GXGetEnumDescription(hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription, &nBufferSize);
		if (emStatus != GX_STATUS_SUCCESS)
		{
			if (pEnumDescription != NULL)
			{
				delete []pEnumDescription;
				pEnumDescription = NULL;
			}
			return emStatus;
		}

		// �����豸֧�ֵ����ظ�ʽ,�������ظ�ʽΪ8bit,
		// ���豸֧�ֵ����ظ�ʽΪMono10��Mono8��������ΪMono8
		for (uint32_t i = 0; i < nEnmuEntry; i++)
		{
			if ((pEnumDescription[i].nValue & GX_PIXEL_8BIT) == GX_PIXEL_8BIT)
			{
				emStatus = GXSetEnum(hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription[i].nValue);
				break;
			}
		}	

		// �ͷ���Դ
		if (pEnumDescription != NULL)
		{
			delete []pEnumDescription;
			pEnumDescription = NULL;
		}
	}

	return emStatus;
}
//----------------------------------------------------------------------------------
/**
\brief  ����������Ϣ
\param  emErrorStatus   [in] ������

\return �޷���ֵ
*/
//----------------------------------------------------------------------------------
void CCam::ShowErrorString(GX_STATUS emErrorStatus)
{
	char*     pchErrorInfo = NULL;
	size_t    nSize        = 0;
	GX_STATUS emStatus     = GX_STATUS_ERROR;

	// ��ȡ������Ϣ���ȣ��������ڴ�ռ�
	emStatus = GXGetLastError(&emErrorStatus, NULL, &nSize);
	pchErrorInfo = new char[nSize];
	if (NULL == pchErrorInfo)
	{
		return;
	}

	// ��ȡ������Ϣ������ʾ
	emStatus = GXGetLastError (&emErrorStatus, pchErrorInfo, &nSize);
	if (emStatus != GX_STATUS_SUCCESS)
	{
		::MessageBox(0,_T("GXGetLastError�ӿڵ���ʧ�ܣ�"),_T(""),0);
	}
	else
	{
		::MessageBox(0,CString(pchErrorInfo),_T(""),0);
	}

	// �ͷ�������ڴ�ռ�
	if (NULL != pchErrorInfo)
	{
		delete[] pchErrorInfo;
		pchErrorInfo = NULL;
	}
}
GX_STATUS CCam::Setcamera(int index)
{
	int m_nOperateID = index;
	int64_t   nValue   = 0;
	bool      bIsImplemented = false;
	GX_STATUS emStatus = GX_STATUS_SUCCESS;

	//�����ع�ʱ��
	emStatus = GXSetFloat(m_hDevices[m_nOperateID],GX_FLOAT_EXPOSURE_TIME,shuttertime[m_nOperateID]);
	GX_VERIFY(emStatus);
	//��������
	emStatus = GXSetFloat(m_hDevices[m_nOperateID],GX_FLOAT_GAIN,gain[m_nOperateID]);
	GX_VERIFY(emStatus);
	return emStatus;
}
void CCam::RegisterCallback(int nCamID)
{
	GX_STATUS emStatus = GX_STATUS_ERROR;

	//ע��ص�
	switch(nCamID)
	{
	case 0:
		emStatus = GXRegisterCaptureCallback(m_hDevices[nCamID], this, OnFrameCallbackFun1);
		GX_VVERIFY(emStatus);
		break;

	case 1:
		emStatus = GXRegisterCaptureCallback(m_hDevices[nCamID], this, OnFrameCallbackFun2);
		GX_VVERIFY(emStatus);
		break;

	//case 2:
	//	emStatus = GXRegisterCaptureCallback(m_hDevices[nCamID], this, OnFrameCallbackFun3);
	//	GX_VVERIFY(emStatus);
	//	break;

	//case 3:
	//	emStatus = GXRegisterCaptureCallback(m_hDevices[nCamID], this, OnFrameCallbackFun4);
	//	GX_VVERIFY(emStatus);
		break;

	default:
		break;
	}

}
GX_STATUS CCam::OnCONSnap(int index) 
{
	int m_nOperateID = index;
	// TODO: Add your control notification handler code here
	GX_STATUS emStatus = GX_STATUS_SUCCESS;
	//----ֹͣ�ɼ�
//	emStatus = GXSendCommand(m_hDevices[m_nOperateID], GX_COMMAND_ACQUISITION_STOP);
	//���òɼ�ģʽ�����ɼ�
//	emStatus = GXSetEnum(m_hDevices[m_nOperateID], GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
//	GX_VERIFY(emStatus);

	//���ô���ģʽΪ�� 
	emStatus = GXSetEnum(m_hDevices[m_nOperateID], GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_OFF);
	GX_VERIFY(emStatus);

	//----ֹͣ�ɼ�
//	emStatus = GXSendCommand(m_hDevices[m_nOperateID], GX_COMMAND_ACQUISITION_START);
	
	m_pstCam[m_nOperateID].bIsSnap = TRUE;
	return emStatus;
}

GX_STATUS CCam::OnStopCONSnap(int index) 
{
	int m_nOperateID = index;
	// TODO: Add your control notification handler code here
	GX_STATUS emStatus = GX_STATUS_SUCCESS;
	//----ֹͣ�ɼ�
//	emStatus = GXSendCommand(m_hDevices[m_nOperateID], GX_COMMAND_ACQUISITION_STOP);
	//���òɼ�ģʽ�����ɼ�
//	emStatus = GXSetEnum(m_hDevices[m_nOperateID], GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
	GX_VERIFY(emStatus);

	//���ô���ģʽΪ�� 
	emStatus = GXSetEnum(m_hDevices[m_nOperateID], GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON);
	GX_VERIFY(emStatus);

	//----ֹͣ�ɼ�
//	emStatus = GXSendCommand(m_hDevices[m_nOperateID], GX_COMMAND_ACQUISITION_START);

	m_pstCam[m_nOperateID].bIsSnap = FALSE;
	return emStatus;
}

GX_STATUS CCam::OnCloseDevice(int index) 
{
	// TODO: Add your control notification handler code here
	GX_STATUS emStatus = GX_STATUS_SUCCESS;

	int m_nOperateID = index;
	// δͣ��ʱ��ֹͣ�ɼ�
	if (m_pstCam[m_nOperateID].bIsSnap)
	{
		// ����ֹͣ�ɼ�����
		emStatus = GXSendCommand(m_hDevices[m_nOperateID], GX_COMMAND_ACQUISITION_STOP);
        GX_VERIFY(emStatus);

		// ע���ɼ��ص�����
		emStatus = GXUnregisterCaptureCallback(m_hDevices[m_nOperateID]);
        GX_VERIFY(emStatus);
		m_pstCam[m_nOperateID].bIsSnap = false;
		delete[]m_pstCam[m_nOperateID].pRawBuffer;
		delete[]m_pstCam[m_nOperateID].pImageBuffer;
	}
	if (m_pstCam[m_nOperateID].bIsOpen)
	{
		// �ر����
		emStatus = GXCloseDevice(m_hDevices[m_nOperateID]);
		GX_VERIFY(emStatus);
		m_hDevices[m_nOperateID] = NULL;
		m_pstCam[m_nOperateID].bIsOpen = false;
		delete[]m_pstCam[m_nOperateID].pRawBuffer;
		delete[]m_pstCam[m_nOperateID].pImageBuffer;
	}

	return emStatus;
}

GX_STATUS CCam::OnSendSoftCommand(int index) 
{
	// TODO: Add your control notification handler code here
	GX_STATUS  emStatus = GX_STATUS_SUCCESS;

	// ������������
	if (m_pstCam[index].bIsSnap)
	{
		OnStopCONSnap(index);
		
	}
	emStatus = GXSendCommand(m_hDevices[index],GX_COMMAND_TRIGGER_SOFTWARE);
    GX_VERIFY(emStatus);
	Sleep(320);
	return emStatus;
}


//---------------------------------------------------------------------------------
/**
\brief  1������ص�����
\param  pFrame  �ص�����

\return void
*/
//---------------------------------------------------------------------------------
void __stdcall CCam::OnFrameCallbackFun1(GX_FRAME_CALLBACK_PARAM* pFrame)
{
	if (pFrame->status != 0)
	{
		return;
	}

	CCam  *pf = (CCam*)(pFrame->pUserParam);
	int		    nID = 0;             //ID��

	BYTE	    *pImageBuffer = NULL;          //ת�����ͼ��buffer
	BYTE        *pRawBuf      = NULL;          //ת��ǰͼ��
	BITMAPINFO	*pBmpInfo     = NULL;          //ͼ����Ϣ
	int64_t	    nBayerLayout  = 0;             //Bayer��ʽ
	int		    nImgWidth     = 0;             //ͼ��Ŀ�
	int         nImgHeight    = 0;             //ͼ��ĸ�
	int        	nWndWidth     = 0;             //��ʾ���ڿ�
	int  	    nWndHeight    = 0;             //��ʾ���ڸ�
	int         i             = 0;             //ѭ������
	CRect       objRect;                       //��ʾ���ڵĴ�С   
//	HDC         objMemDC;                      //����ʾ���ݵĻ������
//	HBITMAP     objMemBmp;                     //�豸������ص��豸���ݵ�λͼ
	char        chPutStr[40] = {'\0'};         //��ʾ֡���ַ�������

	//��ʼ������
//	pf->m_npfpsCont[nID]++;
	nImgWidth    = (int)(pf->m_pstCam[nID].nImageWidth);
	nImgHeight   = (int)(pf->m_pstCam[nID].nImageHeight);
	pImageBuffer = pf->m_pstCam[nID].pImageBuffer;
	pRawBuf      = pf->m_pstCam[nID].pRawBuffer;
	nBayerLayout = pf->m_pstCam[nID].nBayerLayout;
	pBmpInfo     = pf->m_pstCam[nID].pBmpInfo;
	//pf->m_pWnd[0]->getclientrect(objrect); 
	//nwndwidth    = objrect.width();
	//nwndheight   = objrect.height();

	//����ͼ��pRawBuffer��
	memcpy(pf->m_pstCam[nID].pRawBuffer, pFrame->pImgBuf, (size_t)(pf->m_pstCam[nID].nPayLoadSise));

	//ͼ��ת��
	if(pf->m_pstCam[nID].bIsColorFilter)   
	{
		//��ɫ�����Ҫ����RGBת��
		DxRaw8toRGB24(pRawBuf, pImageBuffer, nImgWidth, nImgHeight, RAW2RGB_NEIGHBOUR, DX_PIXEL_COLOR_FILTER(nBayerLayout), TRUE);
	}
	else     
	{
		//�ڰ�ͼ����Ҫͼ��ת
		for(i = 0; i < nImgHeight; i++)
		{
			//memcpy((pImageBuffer + i * nImgWidth), (pRawBuf + ( nImgHeight - i - 1) * nImgWidth), nImgWidth);
			memcpy((pImageBuffer + i * nImgWidth), (pRawBuf + i * nImgWidth), nImgWidth);
		}
	}

	pf->m_pImageBuffer[nID] =pImageBuffer;

	pf->dispImage(nID);



	//double          dTime         = 0;        // ÿ�����е�ʱ��
	//double          dSum          = 0;        // ����ʱ���

	//if (!pf->m_bViewID)       //��ʾͼ�񣬲���ʾ֡�ʣ�
	//{
	//	//������ø���䣬����ͼ�����ˮ��
	//	::SetStretchBltMode(pf->m_hDCs[0], COLORONCOLOR);
	//	StretchDIBits(pf->m_hDCs[0],
	//		0,						
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		0,
	//		0,
	//		nImgWidth,
	//		nImgHeight,
	//		pImageBuffer,
	//		pBmpInfo,
	//		DIB_RGB_COLORS,
	//		SRCCOPY);
	//}
	//else           //��ʾͼ����ʾ֡��
	//{
	//	objMemDC = ::CreateCompatibleDC(pf->m_hDCs[0]);
	//	objMemBmp= CreateCompatibleBitmap(pf->m_hDCs[0], nWndWidth, nWndHeight);
	//	::SelectObject(objMemDC,objMemBmp);

	//	// ������ø���䣬����ͼ�����ˮ��
	//	::SetStretchBltMode(objMemDC, COLORONCOLOR);
	//	StretchDIBits(objMemDC,
	//		0,						
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		0,
	//		0,
	//		nImgWidth,
	//		nImgHeight,
	//		pImageBuffer,
	//		pBmpInfo,
	//		DIB_RGB_COLORS,
	//		SRCCOPY);

	//	//��ʾ֡�ʣ����к�
	//	sprintf(chPutStr, "���:1 SN:%s FPS:%.2f", pf->m_pBaseinfo[nID].szSN, pf->m_pstCam[nID].fFps);
	//	TextOut(objMemDC,0, 0, chPutStr, (int)strlen(chPutStr));
	//	StretchBlt(pf->m_hDCs[0],
	//		0,
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		objMemDC,
	//		0,
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		SRCCOPY);

	//	::DeleteDC(objMemDC);
	//	DeleteObject(objMemBmp);
	//}
}
void __stdcall CCam::OnFrameCallbackFun2(GX_FRAME_CALLBACK_PARAM* pFrame)
{
	if (pFrame->status != 0)
	{
		return;
	}

	CCam  *pf = (CCam*)(pFrame->pUserParam);
	int		    nID = 1;             //ID��

	BYTE	    *pImageBuffer = NULL;          //ת�����ͼ��buffer
	BYTE        *pRawBuf      = NULL;          //ת��ǰͼ��
	BITMAPINFO	*pBmpInfo     = NULL;          //ͼ����Ϣ
	int64_t	    nBayerLayout  = 0;             //Bayer��ʽ
	int		    nImgWidth     = 0;             //ͼ��Ŀ�
	int         nImgHeight    = 0;             //ͼ��ĸ�
	int        	nWndWidth     = 0;             //��ʾ���ڿ�
	int  	    nWndHeight    = 0;             //��ʾ���ڸ�
	int         i             = 0;             //ѭ������
	CRect       objRect;                       //��ʾ���ڵĴ�С   
//	HDC         objMemDC;                      //����ʾ���ݵĻ������
//	HBITMAP     objMemBmp;                     //�豸������ص��豸���ݵ�λͼ
	char        chPutStr[40] = {'\0'};         //��ʾ֡���ַ�������

	//��ʼ������
	//pf->m_npfpsCont[nID]++;
	nImgWidth    = (int)(pf->m_pstCam[nID].nImageWidth);
	nImgHeight   = (int)(pf->m_pstCam[nID].nImageHeight);
	pImageBuffer = pf->m_pstCam[nID].pImageBuffer;
	pRawBuf      = pf->m_pstCam[nID].pRawBuffer;
	nBayerLayout = pf->m_pstCam[nID].nBayerLayout;
	pBmpInfo     = pf->m_pstCam[nID].pBmpInfo;
	//pf->m_pWnd[0]->getclientrect(objrect); 
	//nwndwidth    = objrect.width();
	//nwndheight   = objrect.height();

	//����ͼ��pRawBuffer��
	memcpy(pf->m_pstCam[nID].pRawBuffer, pFrame->pImgBuf, (size_t)(pf->m_pstCam[nID].nPayLoadSise));

	//ͼ��ת��
	if(pf->m_pstCam[nID].bIsColorFilter)   
	{
		//��ɫ�����Ҫ����RGBת��
		DxRaw8toRGB24(pRawBuf, pImageBuffer, nImgWidth, nImgHeight, RAW2RGB_NEIGHBOUR, DX_PIXEL_COLOR_FILTER(nBayerLayout), TRUE);
	}
	else     
	{
		//�ڰ�ͼ����Ҫͼ��ת
		for(i = 0; i < nImgHeight; i++)
		{
			memcpy((pImageBuffer + i * nImgWidth), (pRawBuf + ( nImgHeight - i - 1) * nImgWidth), nImgWidth);
		}
	}

	pf->m_pImageBuffer[nID] =pImageBuffer;

	pf->dispImage(nID);



	//double          dTime         = 0;        // ÿ�����е�ʱ��
	//double          dSum          = 0;        // ����ʱ���

	//if (!pf->m_bViewID)       //��ʾͼ�񣬲���ʾ֡�ʣ�
	//{
	//	//������ø���䣬����ͼ�����ˮ��
	//	::SetStretchBltMode(pf->m_hDCs[0], COLORONCOLOR);
	//	StretchDIBits(pf->m_hDCs[0],
	//		0,						
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		0,
	//		0,
	//		nImgWidth,
	//		nImgHeight,
	//		pImageBuffer,
	//		pBmpInfo,
	//		DIB_RGB_COLORS,
	//		SRCCOPY);
	//}
	//else           //��ʾͼ����ʾ֡��
	//{
	//	objMemDC = ::CreateCompatibleDC(pf->m_hDCs[0]);
	//	objMemBmp= CreateCompatibleBitmap(pf->m_hDCs[0], nWndWidth, nWndHeight);
	//	::SelectObject(objMemDC,objMemBmp);

	//	// ������ø���䣬����ͼ�����ˮ��
	//	::SetStretchBltMode(objMemDC, COLORONCOLOR);
	//	StretchDIBits(objMemDC,
	//		0,						
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		0,
	//		0,
	//		nImgWidth,
	//		nImgHeight,
	//		pImageBuffer,
	//		pBmpInfo,
	//		DIB_RGB_COLORS,
	//		SRCCOPY);

	//	//��ʾ֡�ʣ����к�
	//	sprintf(chPutStr, "���:1 SN:%s FPS:%.2f", pf->m_pBaseinfo[nID].szSN, pf->m_pstCam[nID].fFps);
	//	TextOut(objMemDC,0, 0, chPutStr, (int)strlen(chPutStr));
	//	StretchBlt(pf->m_hDCs[0],
	//		0,
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		objMemDC,
	//		0,
	//		0,
	//		nWndWidth,
	//		nWndHeight,
	//		SRCCOPY);

	//	::DeleteDC(objMemDC);
	//	DeleteObject(objMemBmp);
	//}
}

//---------------------------------------------------------------------------------
/**
\brief 2������ص�����
\param pFrame �ص�����

\return void
*/
//---------------------------------------------------------------------------------


#endif // DAHENG_MER
#define WIDTHBYTES1(bits)    (((bits)*3 + 3) / 4 * 4)
#define WIDTHBYTES(bits)    (((bits) + 3) / 4 * 4)
//------------------------halcon������
void CCam::initimage(Hobject *image)
{
	//BYTE  *red = new  BYTE[Width*Height] ;
	//BYTE  *green= new BYTE[Width*Height] ;
	//BYTE  *blue= new  BYTE[Width*Height] ;
	//int            r,c;
	//for (r=0; r<Height; r++)
	//{
	//	for (c=0; c<Width; c++)
	//	{
	//		red[r*Width+c]   =255;//pbuff[r*width*3+c*3+0]; 
	//		green[r*Width+c] =0;//pbuff[r*width*3+c*3+1];
	//		blue[r*Width+c]  =0;//pbuff[r*width*3+c*3+2];
	//	}
	//}
	//gen_image3(image,"byte",Width,Height,(long)red,(long)green,(long)blue);
	//delete[]red;
	//delete[]green;
	//delete[]blue;
	BYTE  *red = new  BYTE[Width*Height] ;
    memset(red,0,Width*Height);
	gen_image1(image,"byte",Width,Height,(Hlong)red);
	delete []red;
}
void CCam::NewRGBImage(UINT index)//IMAGE �����ȳ�ʼ����
{
	//BYTE  *red = new  BYTE[width*height];
	//BYTE  *green = new  BYTE[width*height];
	//BYTE  *blue = new  BYTE[width*height];
	//int  r, c;
	////for (r = 0; r < height; r++)
	////{
	////	for (c = 0; c < width; c++)
	////	{
	////		red[r*width + c] = pbuff[r*width * 3 + c * 3 + 0];
	////		green[r*width + c] = pbuff[r*width * 3 + c * 3 + 1];
	////		blue[r*width + c] = pbuff[r*width * 3 + c * 3 + 2];
	////	}
	////}
	////gen_image3(image, "byte", width, height, (Hlong)red, (Hlong)green, (Hlong)blue);
	//for (r = 0; r < height; r++)
	//{
	//	for (c = 0; c < width; c++)
	//	{
	//		red[r*width + c] = pbuff[(height - r - 1)*width * 3 + c * 3 + 0];
	//		green[r*width + c] = pbuff[(height - r - 1)*width * 3 + c * 3 + 1];
	//		blue[r*width + c] = pbuff[(height - r - 1)*width * 3 + c * 3 + 2];
	//	}
	//}
	//gen_image3(image, "byte", width, height, (long)red, (long)blue, (long)green);
	//delete[]red;
	//delete[]green;
	//delete[]blue;

	//BYTE  *red = new  BYTE[m_pstCam[index].nImageWidth*m_pstCam[index].nImageHeight];
	//int  r;
	//for (r = 0; r <m_pstCam[index].nImageHeight; r++)
	//{
	//	memcpy(red+r*m_pstCam[index].nImageWidth,m_pstCam[index].pImageBuffer+r*m_pstCam[index].nImageWidth,m_pstCam[index].nImageWidth);
	//}
	gen_image1(&Image[index],"byte",m_pstCam[index].nImageWidth,m_pstCam[index].nImageHeight,(Hlong)m_pstCam[index].pImageBuffer);
	if (is_save_img)
	{
		CStringA s,str1;
		SYSTEMTIME    sysTime;
		GetLocalTime(&sysTime);
		str1.Format(("%d_%d_%d_%d_%d_%d_%d_0.bmp"),
			sysTime.wYear,
			sysTime.wMonth,
			sysTime.wDay,
			sysTime.wHour,
			sysTime.wMinute,
			sysTime.wSecond,
			sysTime.wMilliseconds);
		s=("d:/images/")+str1;
		write_image (Image[index], "bmp", 0,s.GetBuffer());
	}

	//delete []red;
}
void CCam::dispImage(UINT index)
{
	NewRGBImage(index);
	//NewGrayImage(&Image, Width, Height, m_pImageBuffer[index]);
	//disp_color(Image,WindowHandle[index]);
	disp_image(Image[index], WindowHandle[index]);
	if (bigwindowisopen)
	{
		disp_color(Image[index],bigwindow);
	}
	m_Cam.dispcorss(index);
}
void CCam::openbigwindow()
{	
	open_window(0,0,Width/3,Height/3,0,"","",&bigwindow);
	set_draw(bigwindow,"margin");
	set_color(bigwindow,"green");
	set_line_width(bigwindow,1);
}
void CCam::closebigwindow()
{	
	close_window(bigwindow);
}
void CCam::creat_window(UINT index)
{
	RECT objRect;
	m_pWnd[index]->GetClientRect(&objRect);	
	nWndWidth  = objRect.right  - objRect.left;
	nWndHeight = objRect.bottom - objRect.top;
	set_check("~father");
	open_window(0,0,nWndWidth,nWndHeight,(Hlong)m_pWnd[index]->m_hWnd,"visible","",&WindowHandle[index]);
	set_check("father");
	set_draw(WindowHandle[index],"margin");
	set_color(WindowHandle[index],"green");
	set_line_width(WindowHandle[index],1);
}
void CCam::dispcorss(UINT index)
{
	disp_line(WindowHandle[index],0,Width/2,Height,Width/2);
	disp_line(WindowHandle[index],Height/2,0,Height/2,Width);
	if (bigwindowisopen)
	{
		disp_line(bigwindow,0,Width/2,Height,Width/2);
		disp_line(bigwindow,Height/2,0,Height/2,Width);
	}
}
void CCam::save_image(UINT index)
{
	CString str, str1;
	CTime time = CTime::GetCurrentTime();
	str = time.Format("%Y%m%d%H%M%S");
	str1.Format(_T("_%d"), index);
	str += str1;
	//write_image(Image[index], TEXT("bmp"), 0, str);
}
void CCam::measure_image(UINT index)
{
	gen_measure_rectangle2(Row0, Column0, Phi0, Length01, Length02, Width, Height, 
		"nearest_neighbor", &MeasureHandle);
	 disp_rectangle2(WindowHandle[index], Row0, Column0, Phi0, Length01, Length02);
	gen_measure_rectangle2(Row1, Column1, Phi1, Length11, Length12, Width, Height, 
		"nearest_neighbor", &MeasureHandle1);
	disp_rectangle2(WindowHandle[index], Row1, Column1, Phi1, Length11, Length12);
	measure_pos(Image[index], MeasureHandle, 5, 30, "all", "all", &RowEdge, &ColumnEdge, 
		&Amplitude, &Distance);
	measure_pos(Image[index], MeasureHandle1, 5, 30, "all", "all", &RowEdge1, &ColumnEdge1, 
		&Amplitude1, &Distance1);
//	if(m_Cam.RowEdge.Number()>0)

	disp_cross(WindowHandle[index], RowEdge, ColumnEdge, 100, Phi0);
//	if(m_Cam.RowEdge1.Number()>0)
	disp_cross(WindowHandle[index], RowEdge1, ColumnEdge1, 100, Phi1);
}
void CCam::move_window(UINT index,int row,int column,int width,int height)//set_window_extents
{
	set_window_extents(WindowHandle[index],row,column,width,height);
}

void CCam::disp_message (Halcon::HTuple WindowHandle, Halcon::HTuple String, Halcon::HTuple CoordSystem, 
	Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Color, Halcon::HTuple Box)
{
	using namespace Halcon;

	// Local control variables 
	HTuple  Red, Green, Blue, Row1Part, Column1Part;
	HTuple  Row2Part, Column2Part, RowWin, ColumnWin, WidthWin;
	HTuple  HeightWin, MaxAscent, MaxDescent, MaxWidth, MaxHeight;
	HTuple  R1, C1, FactorRow, FactorColumn, Width, Index, Ascent;
	HTuple  Descent, W, H, FrameHeight, FrameWidth, R2, C2;
	HTuple  DrawMode, Exception, CurrentColor;


	// Install default exception handler 
	

	get_rgb(WindowHandle, &Red, &Green, &Blue);
	get_part(WindowHandle, &Row1Part, &Column1Part, &Row2Part, &Column2Part);
	get_window_extents(WindowHandle, &RowWin, &ColumnWin, &WidthWin, &HeightWin);
	set_part(WindowHandle, 0, 0, HeightWin-1, WidthWin-1);
	//
	//default settings
	if (0 != (Row==-1))
	{
		Row = 12;
	}
	if (0 != (Column==-1))
	{
		Column = 12;
	}
	if (0 != (Color==HTuple()))
	{
		Color = "";
	}
	//
	String = ((""+String)+"").Split("\n");
	//
	//Estimate extentions of text depending on font size.
	get_font_extents(WindowHandle, &MaxAscent, &MaxDescent, &MaxWidth, &MaxHeight);
	if (0 != (CoordSystem==HTuple("window")))
	{
		R1 = Row;
		C1 = Column;
	}
	else
	{
		//transform image to window coordinates
		FactorRow = (1.0*HeightWin)/((Row2Part-Row1Part)+1);
		FactorColumn = (1.0*WidthWin)/((Column2Part-Column1Part)+1);
		R1 = ((Row-Row1Part)+0.5)*FactorRow;
		C1 = ((Column-Column1Part)+0.5)*FactorColumn;
	}
	//
	//display text box depending on text size
	if (0 != (Box==HTuple("true")))
	{
		//calculate box extents
		String = (" "+String)+" ";
		Width = HTuple();
		for (Index=0; Index<=(String.Num())-1; Index+=1)
		{
			get_string_extents(WindowHandle, HTuple(String[Index]), &Ascent, &Descent, 
				&W, &H);
			Width.Append(W);
		}
		FrameHeight = MaxHeight*(String.Num());
		FrameWidth = (HTuple(0).Concat(Width)).Max();
		R2 = R1+FrameHeight;
		C2 = C1+FrameWidth;
		//display rectangles
		get_draw(WindowHandle, &DrawMode);
		set_draw(WindowHandle, "fill");
		set_color(WindowHandle, "light gray");
		disp_rectangle1(WindowHandle, R1+3, C1+3, R2+3, C2+3);
		set_color(WindowHandle, "white");
		disp_rectangle1(WindowHandle, R1, C1, R2, C2);
		set_draw(WindowHandle, DrawMode);
	}
	else if (0 != (Box!=HTuple("false")))
	{
		Exception = "Wrong value of control parameter Box";
		throw HException(Exception);
	}
	//Write text.
	for (Index=0; Index<=(String.Num())-1; Index+=1)
	{
		CurrentColor = Color[Index%(Color.Num())];
		if (0 != (HTuple(CurrentColor!=HTuple("")).And(CurrentColor!=HTuple("auto"))))
		{
			set_color(WindowHandle, CurrentColor);
		}
		else
		{
			set_rgb(WindowHandle, Red, Green, Blue);
		}
		Row = R1+(MaxHeight*Index);
		set_tposition(WindowHandle, Row, C1);
		write_string(WindowHandle, HTuple(String[Index]));
	}
	//reset changed window settings
	set_rgb(WindowHandle, Red, Green, Blue);
	set_part(WindowHandle, Row1Part, Column1Part, Row2Part, Column2Part);
	return;
}
bool CCam::get_circle(UINT Image_dex ,double* result_row,double* result_column)
{
	using namespace Halcon;
	//HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	// Local iconic variables 
	Hobject  Region, ConnectedRegions, SelectedRegions,Circle;
	Hobject  SelectedRegions1,SelectedRegions2,SelectedRegions3, RegionBorder, RegionDilation,SelectedRegions4,SelectedRegions5;
	Hobject  RegionUnion, ImageReduced, Edges, SmoothedContours;
	Hobject  ContoursSplit, SelectedContours, Circles, ObjectSelected,ObjectSelected1;
	Hobject  UnionContours, ContCircle;


	// Local control variables 
	HTuple   i, Attrib, NumberCircles,NumberContours;
	HTuple  CenterRow, CenterColumn, Row, Column, Radius, StartPhi,Area,CenterRadius;
	HTuple  EndPhi, PointOrder, Row2, Column2, exist,Indices;
	HTuple  j, DistanceCenters;

	try
	{	
		//gen_circle(&Circle, Height/2, Width/2, 1200);
		//reduce_domain(Image[Image_dex], Circle, &ImageReduced);

		//fast_threshold(Image[Image_dex], &Region, 180, 255, 20);
		threshold(Image[Image_dex], &Region, 240, 255);			   

		connection(Region, &ConnectedRegions);

		select_shape(ConnectedRegions, &SelectedRegions1, "width", "and", celiang_width[0], celiang_width[1]);
		select_shape(SelectedRegions1, &SelectedRegions2, "height", "and", celiang_height[0], celiang_height[1]);
		select_shape(SelectedRegions2, &SelectedRegions3, "area", "and", area[0], area[1]);

		select_shape (SelectedRegions3, &SelectedRegions4, "ra", "and", ra[0], ra[1]);
		select_shape (SelectedRegions4, &SelectedRegions5,"rb", "and", rb[0], rb[1]);
		area_center (SelectedRegions5, &Area, &Row, &Column);
		tuple_sort_index(Area, &Indices);

		select_obj(SelectedRegions5, &ObjectSelected1, HTuple(Indices[0])+1);

		//step: create ROI for contour processing
		//
		boundary(SelectedRegions5, &RegionBorder, "inner_filled");
		dilation_circle(RegionBorder, &RegionDilation, radius);
		union1(RegionDilation, &RegionUnion);
		reduce_domain(Image[Image_dex], RegionUnion, &ImageReduced);


		edges_sub_pix(ImageReduced, &Edges, "canny", 1.5, 10, 40);
		segment_contours_xld(Edges, &ContoursSplit, "lines_circles", 5,10,10);
		select_contours_xld(ContoursSplit, &SelectedContours, "contour_length", 5, 99999, 
			-0.5, 0.5);
		count_obj(SelectedContours, &NumberContours);
		gen_empty_obj(&Circles);
		for (i=1; i<=NumberContours; i+=1)
		{
			select_obj(SelectedContours, &ObjectSelected, i);
			get_contour_global_attrib_xld(ObjectSelected, "cont_approx", &Attrib);
			if (0 != (Attrib==1))
			{
				concat_obj(Circles, ObjectSelected, &Circles);
			}
		}
		union_cocircular_contours_xld(Circles, &UnionContours, HTuple(60).Rad(), HTuple(10).Rad(), 
			HTuple(30).Rad(), 50, 50, 10, "true", 1);
		count_obj(UnionContours, &NumberCircles);
		CenterRow = HTuple();
		CenterColumn = HTuple();
		for (i=1; i<=NumberCircles; i+=1)
		{
			select_obj(UnionContours, &ObjectSelected, i);
			fit_circle_contour_xld(ObjectSelected, "algebraic", -1, 0, 0, 3, 2, &Row, &Column, 
				&Radius, &StartPhi, &EndPhi, &PointOrder);
			gen_circle_contour_xld(&ContCircle, Row, Column, Radius, 0, HTuple(360).Rad(), 
				"positive", 1.5);
			CenterRow.Append(Row);
			CenterColumn.Append(Column);
			CenterRadius.Append(Radius);
		}
		
	//	disp_cross(WindowHandle[Image_dex],CenterRow, CenterColumn,50,0);
		int a = (int)CenterRow.Num();
		if (a==0)
		{
			return false;
		}
		double *ra = new double[a];
		for (int  k = 0;k<a;k++)
		{
			ra[k] = abs(CenterRadius[k].D()-100);
		}
		double less= ra[0];
		int p =0;
		for (int k = 0 ;k<a;k++)
		{
          if (ra[k]<less)
          {
			  less =ra[k];
			  p =k;
          }
		}
		delete []ra;
		disp_circle(WindowHandle[Image_dex], CenterRow[p], CenterColumn[p], CenterRadius[p]);
		disp_cross(WindowHandle[Image_dex],CenterRow[p], CenterColumn[p],100,0);
		*result_row = CenterRow[p].D();
		*result_column = CenterColumn[p].D();
	}
	catch (HException &HDevExpDefaultException)
	{
		char *p = HDevExpDefaultException.message;
		CString a = CString(p);
		//MessageBox(0,a,NULL,0);
		return false;
	}
	return true;
}
double CCam::get_angle(double row1,double column1,double row2,double column2)
{
	HTuple Angle;
	angle_lx((HTuple)row1, (HTuple)column1,(HTuple) row2, (HTuple)column2, &Angle);
	Angle = Angle.Deg();
	return Angle[0].D();
}
void CCam::saveini()
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
	str2 = _T("C:\\LMCAPP\\pos.ini");
	CString str;
	str.Format(_T("%f"),calc0_x);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("calc0_x"),str,str2);
	str.Format(_T("%f"),calc0_y);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("calc0_y"),str,str2);
	str.Format(_T("%f"),calc1_x);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("calc1_x"),str,str2);
	str.Format(_T("%f"),calc1_y);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("calc1_y"),str,str2);

	str.Format(_T("%d"),shuttertime[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("shuttertime[0]"),str,str2);

	str.Format(_T("%d"),gain[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("gain[0]"),str,str2);

	str.Format(_T("%d"),shuttertime[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("shuttertime[1]"),str,str2);

	str.Format(_T("%d"),gain[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("gain[1]"),str,str2);

	str.Format(_T("%f"),stepx[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("stepx[0]"),str,str2);

	str.Format(_T("%f"),stepx[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("stepx[1]"),str,str2);

	str.Format(_T("%f"),stepy[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("stepy[0]"),str,str2);

	str.Format(_T("%f"),stepy[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("stepy[1]"),str,str2);

	str.Format(_T("%f"),buchang_angle);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("buchang_angle"),str,str2);

	str.Format(_T("%ld"),buchangposx[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("buchangposx[0]"),str,str2);

	str.Format(_T("%ld"),buchangposx[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("buchangposx[1]"),str,str2);

	str.Format(_T("%ld"),buchangposy[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("buchangposy[0]"),str,str2);

	str.Format(_T("%ld"),buchangposy[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("buchangposy[1]"),str,str2);

	str.Format(_T("%lf"),Y_angle[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("Y_angle[0]"),str,str2);

	str.Format(_T("%lf"),Y_angle[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Calc"),_T("Y_angle[1]"),str,str2);

	str.Format(_T("%f"),radius);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("radius"),str,str2);

	str.Format(_T("%d"),celiang_width[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("celiang_width[0]"),str,str2);
	str.Format(_T("%d"),celiang_width[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("celiang_width[1]"),str,str2);

	str.Format(_T("%d"),celiang_height[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("celiang_height[0]"),str,str2);
	str.Format(_T("%d"),celiang_height[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("celiang_height[1]"),str,str2);

	str.Format(_T("%d"),area[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("area[0]"),str,str2);
	str.Format(_T("%d"),area[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("area[1]"),str,str2);

	str.Format(_T("%d"),ra[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("ra[0]"),str,str2);
	str.Format(_T("%d"),ra[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("ra[1]"),str,str2);

	str.Format(_T("%d"),rb[0]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("rb[0]"),str,str2);
	str.Format(_T("%d"),rb[1]);
	str.TrimLeft();
	::WritePrivateProfileString(_T("Measure"),_T("rb[1]"),str,str2);

	for (int k = 0;k<4;k++)
	{
		
		str.Format(_T("%lf"),sunny_row[k]);
		str.TrimLeft();
		str1.Format(_T("sunny_row%d"),k);
		::WritePrivateProfileString(_T("Measure"),str1,str,str2);

		str.Format(_T("%lf"),sunny_column[k]);
		str.TrimLeft();
		str1.Format(_T("sunny_column%d"),k);
		::WritePrivateProfileString(_T("Measure"),str1,str,str2);

		str.Format(_T("%lf"),sunny_radius[k]);
		str.TrimLeft();
		str1.Format(_T("sunny_radius%d"),k);
		::WritePrivateProfileString(_T("Measure"),str1,str,str2);

		str.Format(_T("%d"),sunny_thresd[k]);
		str.TrimLeft();
		str1.Format(_T("sunny_thresd%d"),k);
		::WritePrivateProfileString(_T("Measure"),str1,str,str2);


		str.Format(_T("%d"),print_camerax[k]);
		str.TrimLeft();
		str1.Format(_T("print_camerax%d"),k);
		::WritePrivateProfileString(_T("Measure"),str1,str,str2);


		str.Format(_T("%d"),print_cameray[k]);
		str.TrimLeft();
		str1.Format(_T("print_cameray%d"),k);
		::WritePrivateProfileString(_T("Measure"),str1,str,str2);

		str.Format(_T("%d"),print_cameraz[k]);
		str.TrimLeft();
		str1.Format(_T("print_cameraz%d"),k);
		::WritePrivateProfileString(_T("Measure"),str1,str,str2);
	}
}
void CCam::readini()
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
	CString str;
	GetPrivateProfileString(_T("Calc"),_T("calc0_x"),_T("0"),str.GetBuffer(256),256,str2);
	calc0_x = _wtof(str);
	GetPrivateProfileString(_T("Calc"),_T("calc0_y"),_T("0"),str.GetBuffer(256),256,str2);
	calc0_y = _wtof(str);
	GetPrivateProfileString(_T("Calc"),_T("calc1_x"),_T("0"),str.GetBuffer(256),256,str2);
	calc1_x = _wtof(str);
	GetPrivateProfileString(_T("Calc"),_T("calc1_y"),_T("0"),str.GetBuffer(256),256,str2);
	calc1_y = _wtof(str);
	GetPrivateProfileString(_T("Calc"),_T("shuttertime[0]"),_T("6"),str.GetBuffer(256),256,str2);
	shuttertime[0] = _wtoi(str);
	GetPrivateProfileString(_T("Calc"),_T("gain[0]"),_T("10"),str.GetBuffer(256),256,str2);
	gain[0] = _wtoi(str);

	GetPrivateProfileString(_T("Calc"),_T("shuttertime[1]"),_T("6"),str.GetBuffer(256),256,str2);
	shuttertime[1] = _wtoi(str);
	GetPrivateProfileString(_T("Calc"),_T("gain[1]"),_T("10"),str.GetBuffer(256),256,str2);
	gain[1] = _wtoi(str);

	GetPrivateProfileString(_T("Calc"),_T("stepx[0]"),_T("0"),str.GetBuffer(256),256,str2);
	stepx[0] = _wtof(str);
	GetPrivateProfileString(_T("Calc"),_T("stepx[1]"),_T("0"),str.GetBuffer(256),256,str2);
	stepx[1] = _wtof(str);
	GetPrivateProfileString(_T("Calc"),_T("stepy[0]"),_T("0"),str.GetBuffer(256),256,str2);
	stepy[0] = _wtof(str);
	GetPrivateProfileString(_T("Calc"),_T("stepy[1]"),_T("0"),str.GetBuffer(256),256,str2);
	stepy[1] = _wtof(str);

	GetPrivateProfileString(_T("Calc"),_T("buchang_angle"),_T("0"),str.GetBuffer(256),256,str2);
	buchang_angle = _wtof(str);

	GetPrivateProfileString(_T("Calc"),_T("Y_angle[0]"),_T("0"),str.GetBuffer(256),256,str2);
	Y_angle[0] = _wtof(str);


	GetPrivateProfileString(_T("Calc"),_T("Y_angle[1]"),_T("0"),str.GetBuffer(256),256,str2);
	Y_angle[1] = _wtof(str);

	GetPrivateProfileString(_T("Calc"),_T("buchangposx[0]"),_T("0"),str.GetBuffer(256),256,str2);
	buchangposx[0] = _wtoi(str);
	GetPrivateProfileString(_T("Calc"),_T("buchangposx[1]"),_T("0"),str.GetBuffer(256),256,str2);
	buchangposx[1] = _wtoi(str);
	GetPrivateProfileString(_T("Calc"),_T("buchangposy[0]"),_T("0"),str.GetBuffer(256),256,str2);
	buchangposy[0] = _wtoi(str);
	GetPrivateProfileString(_T("Calc"),_T("buchangposy[1]"),_T("0"),str.GetBuffer(256),256,str2);
	buchangposy[1] = _wtoi(str);




		GetPrivateProfileString(_T("Measure"),_T("celiang_width[0]"),_T("150"),str.GetBuffer(256),256,str2);
		celiang_width[0] = _wtoi(str);
		GetPrivateProfileString(_T("Measure"),_T("celiang_width[1]"),_T("300"),str.GetBuffer(256),256,str2);
		celiang_width[1] = _wtoi(str);

		GetPrivateProfileString(_T("Measure"),_T("celiang_height[0]"),_T("150"),str.GetBuffer(256),256,str2);
		celiang_height[0] = _wtoi(str);
		GetPrivateProfileString(_T("Measure"),_T("celiang_height[1]"),_T("300"),str.GetBuffer(256),256,str2);
		celiang_height[1] = _wtoi(str);

		GetPrivateProfileString(_T("Measure"),_T("area[0]"),_T("25000"),str.GetBuffer(256),256,str2);
		area[0] = _wtoi(str);
		GetPrivateProfileString(_T("Measure"),_T("area[1]"),_T("50000"),str.GetBuffer(256),256,str2);
		area[1] = _wtoi(str);

		GetPrivateProfileString(_T("Measure"),_T("ra[0]"),_T("70"),str.GetBuffer(256),256,str2);
		ra[0] = _wtoi(str);
		GetPrivateProfileString(_T("Measure"),_T("ra[1]"),_T("106"),str.GetBuffer(256),256,str2);
		ra[1] = _wtoi(str);

		GetPrivateProfileString(_T("Measure"),_T("rb[0]"),_T("70"),str.GetBuffer(256),256,str2);
		rb[0] = _wtoi(str);
		GetPrivateProfileString(_T("Measure"),_T("rb[1]"),_T("106"),str.GetBuffer(256),256,str2);
		rb[1] = _wtoi(str);

		GetPrivateProfileString(_T("Measure"),_T("radius"),_T("4"),str.GetBuffer(256),256,str2);
		radius =(float) _wtof(str);


		for (int k = 0;k<4;k++)
		{
			str1.Format(_T("sunny_row%d"),k);
			GetPrivateProfileString(_T("Measure"),str1,_T("0"),str.GetBuffer(256),256,str2);
			sunny_row[k] = _wtof(str);

			str1.Format(_T("sunny_column%d"),k);
			GetPrivateProfileString(_T("Measure"),str1,_T("0"),str.GetBuffer(256),256,str2);
			sunny_column[k] = _wtof(str);

			str1.Format(_T("sunny_radius%d"),k);
			GetPrivateProfileString(_T("Measure"),str1,_T("0"),str.GetBuffer(256),256,str2);
			sunny_radius[k] =_wtof(str);

			str1.Format(_T("sunny_thresd%d"),k);
			GetPrivateProfileString(_T("Measure"),str1,_T("0"),str.GetBuffer(256),256,str2);
			sunny_thresd[k] = _wtoi(str);



			str1.Format(_T("print_camerax%d"),k);
			GetPrivateProfileString(_T("Measure"),str1,_T("0"),str.GetBuffer(256),256,str2);
			print_camerax[k] = _wtol(str);

			str1.Format(_T("print_cameray%d"),k);
			GetPrivateProfileString(_T("Measure"),str1,_T("0"),str.GetBuffer(256),256,str2);
			print_cameray[k] = _wtol(str);

			str1.Format(_T("print_cameraz%d"),k);
			GetPrivateProfileString(_T("Measure"),str1,_T("0"),str.GetBuffer(256),256,str2);
			print_cameraz[k] = _wtol(str);
		}
}
bool CCam::creat_model(UINT index)
{
	using namespace Halcon;
	Hobject   Rectangle, ImageReduced;


	// Local control variables 
	HTuple  Pointer, Type, Width, Height;
	HTuple  Row11, Column11, Row2, Column2, Area, Row, Column;
	HTuple  Row1, Column1  ;
	try
	{
		set_color(WindowHandle[index],"blue");
		set_tposition(WindowHandle[index], 0, 0);
		write_string(WindowHandle[index], "�밴ס�������϶�����һ�����ο���������ģ�壡");
		draw_rectangle1(WindowHandle[index], &Row11, &Column11, &Row2, &Column2);
		gen_rectangle1(&Rectangle, Row11, Column11, Row2, Column2);
		area_center(Rectangle, &Area, &Row, &Column);
		set_color(WindowHandle[index],"red");		
		reduce_domain(Image[index], Rectangle, &ImageReduced);
		create_ncc_model(ImageReduced, "auto", -0.39, 0.79, "auto", "use_polarity", &ModelID[index]);
		CStringA s,s1,s2;
		s1.Format(("%d"),index);
		s= "D:/"+s1+".ncm";	
		s2 = "D:/"+s1;
		write_ncc_model(ModelID[index], s.GetBuffer());
		write_image(ImageReduced,"bmp",0,s2.GetBuffer());
		clear_window(WindowHandle[index]);
		disp_rectangle1 (WindowHandle[index], Row11, Column11, Row2, Column2);
		disp_cross(WindowHandle[index], Row, Column, 10, 0);
		disp_image(Image[index],WindowHandle[index]);
		set_color(WindowHandle[index],"green");
		return true;
	}
	catch (HException &HDevExpDefaultException)
	{
		char *E = HDevExpDefaultException.message;
		return false;
	}
}
void CCam::save_image()
{
	try
	{
		CStringA s,s1,s2;
		s1.Format(("camera%d"),0);
		s2 = "D:/"+s1;
		write_image(Image[0],"bmp",0,s2.GetBuffer());
		s1.Format(("camera%d"),1);
		s2 = "D:/"+s1;
		write_image(Image[1],"bmp",0,s2.GetBuffer());
	}
	catch (HException &HDevExpDefaultException)
	{
		char *E = HDevExpDefaultException.message;
		return ;
	}
}

bool CCam::read_model()
{
	using namespace Halcon;
	try
	{
		  read_ncc_model("D:/0.ncm", &ModelID[0]);
		  read_ncc_model("D:/1.ncm", &ModelID[1]);
	}
	catch (HException &HDevExpDefaultException)
	{
		char *E = HDevExpDefaultException.message;
		return false;
	}	
	return true;
}

bool CCam::find_model(UINT index,double * row,double *column)
{
	using namespace Halcon;
	HTuple  Row1, Column1, Angle, Score;
	try
	{
		find_ncc_model(Image[index], ModelID[index], -0.39, 0.78, 0.8, 1, 0.5, "true", 0, &Row1, &Column1, 
			&Angle, &Score);
		if (Row1[0].D()==0)
		{
			return false;
		}
			disp_cross(WindowHandle[index],Row1,Column1,50,0);
	*row = Row1[0].D();
	*column = Column1[0].D();
	}
	catch (HException &HDevExpDefaultException)
	{
		char *p = HDevExpDefaultException.message;
		CString a = CString(p);
		MessageBox(0,a,NULL,0);
		return false;
	}
	return true;
}
bool CCam::sunny_find_model(UINT index)
{
	using namespace Halcon;
	HTuple  Row1, Column1, Angle, Score;
	Hobject  Circle, ImageReduced, Region;
	Hobject  ConnectedRegions, SelectedRegions,SelectedRegions1,SelectedRegions2;


	// Local control variables 
	HTuple  Pointer, Type, Width, Height;
	HTuple  m_row, m_column, m_radius, Area, Row, Column;
	double re_row[4],re_column[4],re_angle[2];
	try
	{



		int count[4] ={0,0,0,0};
		for (int k =0;k<4;k++)
		{
			m_row = sunny_row[k];
			m_column = sunny_column[k];
			m_radius = sunny_radius[k];
			gen_circle(&Circle, m_row, m_column, m_radius);

			reduce_domain(Image[0], Circle, &ImageReduced);
			find_ncc_model(ImageReduced, ModelID[index], -0.39, 0.78, 0.5, 1, 0.5, "true", 0, &Row1, &Column1, 
				&Angle, &Score);
			if (Row1[0].D()==0)
			{
				return false;
			}
			disp_cross(WindowHandle[index],Row1,Column1,50,0);
			count[k] = Row.Num();
			if (count[k]!=1)
			{
				re_row[k] = 0;
				re_column[k] = 0;
			}
			else
			{
				re_row[k] = Row1[0].D();
				re_column[k] = Column1[0].D();
			}
		}
		for (int k = 0;k<4;k++)
		{
			if (count[k]!=1)
			{
				return false;
			}
		}
		sunny_center_row = (re_row[0]+re_row[1]+re_row[2]+re_row[3])/4;
		sunny_center_column = (re_column[0]+re_column[1]+re_column[2]+re_column[3])/4;
		angle_lx((re_row[0]+re_row[2])/2,(re_column[0]+re_column[2])/2,(re_row[1]+re_row[3])/2,(re_column[1]+re_column[3])/2,&re_angle[0]);
		//angle_lx(re_row[2],re_column[2],re_row[3],re_column[3],&re_angle[1]);
		sunny_angle=  (re_angle[0]);//���ȣ�

		CString str ;
		str.Format(_T("��������ROW:%.3f,COLUMN:%.3f\r\n�Ƕ�: %.4f"),sunny_center_row,sunny_center_column,m_math.angle(sunny_angle));
		CStringA str1 = (CStringA)str;

		set_color(WindowHandle[0],"green");
		set_tposition(WindowHandle[0], 500, 100);
		write_string(WindowHandle[0], str1.GetBuffer());
	}
	catch (HException &HDevExpDefaultException)
	{
		char *p = HDevExpDefaultException.message;
		CString a = CString(p);
		MessageBox(0,a,NULL,0);
		return false;
	}


	return true;
}
void CCam::m_disp_circle()
{
	for (int k = 0;k<4;k++)
	{
		disp_circle(WindowHandle[0],sunny_row[k],sunny_column[k],sunny_radius[k]);
	}
}
void CCam::m_draw_roi(int id)
{
	CString str ;
	str.Format(_T("�����꣬Ȼ���϶���껭Բ%d"),id+1);
	CStringA str1 = (CStringA)str;

	set_color(WindowHandle[0],"green");
	set_tposition(WindowHandle[0], 0, 0);
	write_string(WindowHandle[0], str1.GetBuffer());
	draw_circle(WindowHandle[0], &sunny_row[id], &sunny_column[id], &sunny_radius[id]);
}

bool CCam::sunny_measure()
{
	using namespace Halcon;
	HTuple  Row1, Column1, Angle, Score;
	try
	{
		Hobject  Circle, ImageReduced, Region;
		Hobject  ConnectedRegions, SelectedRegions,SelectedRegions1,SelectedRegions2;


		// Local control variables 
		HTuple  Pointer, Type, Width, Height;
		HTuple  m_row, m_column, m_radius, Area, Row, Column;
		double re_row[4],re_column[4],re_angle[2];
		CStringA s,str1;
		//SYSTEMTIME    sysTime;
		//GetLocalTime(&sysTime);
		//str1.Format(("%d_%d_%d_%d_%d_%d_%d_0.bmp"),
		//	sysTime.wYear,
		//	sysTime.wMonth,
		//	sysTime.wDay,
		//	sysTime.wHour,
		//	sysTime.wMinute,
		//	sysTime.wSecond,
		//	sysTime.wMilliseconds);
		//s=("d:/images/")+str1;
		//write_image (Image[0], "bmp", 0,s.GetBuffer());
		set_draw(WindowHandle[0],"margin");
		int count[4] ={0,0,0,0};
		for (int k =0;k<4;k++)
		{
			m_row = sunny_row[k];
			m_column = sunny_column[k];
			m_radius = sunny_radius[k];
			gen_circle(&Circle, m_row, m_column, m_radius);

			reduce_domain(Image[0], Circle, &ImageReduced);
			//threshold(ImageReduced, &Region, sunny_thresd[k], 255);
			fast_threshold(ImageReduced, &Region, sunny_thresd[k], 255, 10);
			connection(Region, &ConnectedRegions);
			select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 50, 500);
			select_shape(SelectedRegions, &SelectedRegions1, "width", "and", 5, 50);
			select_shape(SelectedRegions1, &SelectedRegions2, "height", "and",5, 50);
			area_center(SelectedRegions2, &Area, &Row, &Column);
			disp_cross(WindowHandle[0], Row, Column, 100, 0);
			count[k] = Row.Num();
			if (count[k]!=1)
			{
				re_row[k] = 0;
				re_column[k] = 0;
			}
			else
			{
				re_row[k] = Row[0].D();
				re_column[k] = Column[0].D();
			}
		}
		for (int k = 0;k<4;k++)
		{
			if (count[k]!=1)
			{
	           return false;
			}
		}
		sunny_center_row = (re_row[0]+re_row[1]+re_row[2]+re_row[3])/4;
		sunny_center_column = (re_column[0]+re_column[1]+re_column[2]+re_column[3])/4;
		angle_lx((re_row[0]+re_row[2])/2,(re_column[0]+re_column[2])/2,(re_row[1]+re_row[3])/2,(re_column[1]+re_column[3])/2,&re_angle[0]);
		//angle_lx(re_row[2],re_column[2],re_row[3],re_column[3],&re_angle[1]);
		sunny_angle=  (re_angle[0]);//���ȣ�
		
		CString str ;
		str.Format(_T("��������ROW:%.3f,COLUMN:%.3f\r\n�Ƕ�: %.4f"),sunny_center_row,sunny_center_column,m_math.angle(sunny_angle));
		 str1 = (CStringA)str;

		set_color(WindowHandle[0],"green");
		set_tposition(WindowHandle[0], 500, 100);
		write_string(WindowHandle[0], str1.GetBuffer());
	}
	catch (HException &HDevExpDefaultException)
	{
		char *p = HDevExpDefaultException.message;
		CString a = CString(p);
		//MessageBox(0,a,NULL,0);
		return false;
	}
	return true;
}

bool CCam::czrs_measure()
{
	ImageData m_data;
	WaxPoint2f center;
	vector<WaxPoint2f> m_marks;
	double m_angle =0;

	m_data.height = m_pstCam[0].nImageHeight;
	m_data.width = m_pstCam[0].nImageWidth;
	m_data.type = ImgGray8;
	m_data.pbuff = m_pstCam[0].pImageBuffer;
	SetThresholdValue(sunny_thresd[0],255);
	if (LocateMark(m_data, center, m_angle, m_marks)==VISION_OK)
	{
		sunny_angle = -(m_angle)+m_math.ang(0.032);
		sunny_center_row = center.Y;
		sunny_center_column = center.X;


		CString str ;
		CStringA str1;
		str.Format(_T("��������ROW:%.3f,COLUMN:%.3f\r\n�Ƕ�: %.4f"),sunny_center_row,sunny_center_column,m_math.angle(sunny_angle));
		str1 = (CStringA)str;

		set_color(WindowHandle[0],"green");
		set_tposition(WindowHandle[0], 100, 100);
		write_string(WindowHandle[0], str1.GetBuffer());

		disp_cross(WindowHandle[0], m_marks.at(0).Y,m_marks.at(0).X, 100, 0);
		disp_cross(WindowHandle[0], m_marks.at(1).Y,m_marks.at(1).X, 100, 0);
		disp_cross(WindowHandle[0], m_marks.at(2).Y,m_marks.at(2).X, 100, 0);
		disp_cross(WindowHandle[0], m_marks.at(3).Y,m_marks.at(3).X, 100, 0);
		return true;
	}
	else
	{
		CString str ;
		CStringA str1;
		str.Format(_T("����ʧ�ܣ�"));
		str1 = (CStringA)str;

		set_color(WindowHandle[0],"red");
		set_tposition(WindowHandle[0], 100, 100);
		write_string(WindowHandle[0], str1.GetBuffer());
		return false;
	}
}
void CCam::get_button_pos(Hlong WindowHandle,double  &row,double &column,CString str)
{
	HTuple  Row, Column, Button;
   
	CStringA str1;

	str1 = (CStringA)str;

	set_color(WindowHandle,"green");
	set_tposition(WindowHandle, 500, 100);
	write_string(WindowHandle, str1.GetBuffer());

	get_mbutton(WindowHandle, &Row, &Column, &Button);
	row = (Row[0].D()-Height/2);
	column = (Column[0].D()-Width/2);
}