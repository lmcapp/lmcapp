#include "StdAfx.h"
#include "XDMcontrol.h"
#include <iostream>
using namespace std;
int repeatCount;
CXDMcontrol m_XDM;
CXDMcontrol::CXDMcontrol(void)
{
	 repeatCount = 0;  //Values Used in Call Back Functions
	 numTimesToPrint = 1; //Values Used in Call Back Functions
	 _numColors = 1; //number of colors printing
	 _numHibs = 0; // number of Hibs found
	 _masterPcFlag = true;  // Set false for non-master PCs in multiple pc setup.
	 _printBars = 1; //number of print bars
	 _bReversePrint = false; // Revers Print Flag
	 fireStatus = false; // fire Status flag


	 _numJetsForHead = 880;  //the number of jets for each head
	 _headRes = 300;  // The native resolutiong for the head
	 _yImageRes = 300; // The Y image Resolution

	 voltageDelta = 0.0;
	 quadEncoderRes = 12700; //  quad encoder count per inch


	// variable for setting temperature

	 pCurrentResTemp = &fCurrResTemp;
	 pCurrentLeftJSTemp = &fCurrLeftJSTemp;
	 pCurrentRightJSTemp = &fCurrRightJSTemp;



	 //------
	 pPugre1 =&Pugre1;
	 pPugre2 =&Pugre2;


	//initiallizing the dot clock Structure
	dotClockConfig.type = hibQuadEncoderPos;    // options: hibQuadEncoder, hibAutoFire, hibExternalDotClock; hibQuadEncoderPos;
	dotClockConfig.fAutoFireFreqHz = 5000;   // Only used for autofire dot clock source.
	dotClockConfig.uPrintResDpi = _yImageRes;
	dotClockConfig.bAutoFireFromMasterHib = true;
	dotClockConfig.bWaveAmpPresent = true;    // Must be true to actually jet ink.
	dotClockConfig.bHeadReadyOverride = false; // bHeadREadyOverride
	dotClockConfig.bEnablePageStart = true;  // Set false if dot clock gated externally or to print immediately.
	dotClockConfig.bEnablePageStop = false;
	dotClockConfig.fEncoderResolution = quadEncoderRes; //  quad encoder count per inch
	//initHib();
	isUseHead[0] =true;
	isUseHead[1] =true;
	isUseHead[2] = true;
	usehead_numbers =3;
}


CXDMcontrol::~CXDMcontrol(void)
{
//	closeHib();
}
bool CXDMcontrol::initHib()
{
	hibStatus = hibInitAllBoards(&_numHibs, _masterPcFlag); //hibLibAPi Call discovering HIB
	return ErrorMsg();
	isUseHead[0]=true;
}
bool CXDMcontrol::closeHib()
{
	hibStatus = hibCloseAllBoards(); 
	return ErrorMsg();
}
bool CXDMcontrol::ErrorMsg()
{
	if (hibStatus != hibSuccess)
	{
		CString	errmsg[]=
		{
			_T("hibSuccess") ,
			_T("hibFailure"),			// generic failure
			_T("hibNoBoardsFound") ,		// Can't find an interface board attached to the system
			_T("hibBoardNotAvailable") ,	// e.g., requested use of a board that wasn't discovered.
			_T("hibHeadInitNotComplete"),// Known head type not connected, or head nvram not read/decoded
			_T("hibMemoryError"),		// Memory allocation error in the library
			_T("hibDriverMemoryError"),	// Memory allocation error in the driver
			_T("hibWaveampFaultError"),	// Waveamp fault (or wave amp is not connected)
			_T("hibNotApplicable"),		// Not applicable for hib/head type or situation
			_T("hibWaveformClipped"),	// Waveform voltage clipped at max allowed.
			_T("hibWaveCalFailure"),	// waveCal failed
			_T("hibBiasVoltageShort"),	// Unable to apply waveform bias.
			_T("hibDataNotAvailable"),	// Data not available.
			_T("hibMotorStallDetected"),// Stitch/Roll adjust stall error detected.
			_T("hibMotorShortDetected"),// Stitch/Roll adjust short error detected.
			_T("hibMotorOpenDetected"), // Stitch/Roll adjust open error detected.
			_T("hibFileAlreadyExists"), // File to be created already exists.
			_T("hibWaitTimeout")		// Timeout exceeded during wait for event.
		};
		//CString str;
		//if(abs(hibStatus)>17)
		//	str.Format(_T("Error code = %d,未知错误"),hibStatus);
		//else
		//str.Format(_T("Error code = %d,%s"),hibStatus,errmsg[abs(hibStatus)]);
		//::MessageBox(NULL,str,_T("API调用失败"),MB_ICONERROR);
		
		char msg[1024];
		if(abs(hibStatus)>17)
			sprintf(msg,("Error code = %d,Unknown Error"),hibStatus);
		else
		{
			CStringA str= (CStringA)errmsg[abs(hibStatus)];
			sprintf(msg,("Error code = %d,%10s"),hibStatus,str.GetBuffer());
		}
			
		cout<<msg<<endl;
		return false;
	}
	else
		return true;
}
bool CXDMcontrol::addHeadToPrintbar(int nPrintBarNum, int nPrintBarHdNum, int nHibNum, int nFirstImgCol, int nFirstHdCol, int nLastHdCol)
{
	hibStatus = hibAddHeadToPrintBar(nPrintBarNum, nPrintBarHdNum, nHibNum, nFirstImgCol, nFirstHdCol, nLastHdCol);
	return ErrorMsg();
}
bool CXDMcontrol::configPrintBarHead(int nPrintBarNum, int nPrintBarHdNum, int nFirstImgCol, int nFirstHdCol, int nLastHdCol)
{
	hibStatus = hibConfigPrintBarHead(nPrintBarNum,nPrintBarHdNum,nFirstImgCol,nFirstHdCol,nLastHdCol);
	return ErrorMsg();
}
bool CXDMcontrol::setupAllDotclocks(hibDotClockDef_t *pDotClockDef)
{
	hibStatus =  hibSetupAllDotclocks(pDotClockDef);
	return ErrorMsg();
}
bool CXDMcontrol::readTemp(int nHibChainNum, int nWaveNum, int nHeaterNum, float *pfSetPointTempC)
{
	hibStatus = hibGetThermalSetpoint( nHibChainNum,  nWaveNum,  nHeaterNum, pfSetPointTempC);
	return ErrorMsg();
}
bool CXDMcontrol::setTemp(int nHibChainNum, int nWaveNum, int nHeaterNum, float fSetPointTempC)
{
	hibStatus = hibSetThermalSetpoint( nHibChainNum,  nWaveNum,  nHeaterNum,  fSetPointTempC);
	return ErrorMsg();
}
bool CXDMcontrol::readHeaterTemp(int nHibChainNum, int nHeaterNum, float *pfHeaterTempC)
{
	hibStatus = hibGetHeaterTemp( nHibChainNum,  nHeaterNum, pfHeaterTempC);
	return ErrorMsg();
}
bool CXDMcontrol::adjustWaveformVoltage(int nHibChainNum, int nWaveNum, float fDeltaVoltage)
{
	hibStatus = hibAdjustWaveformVoltage(nHibChainNum, nWaveNum, fDeltaVoltage);
	return ErrorMsg();
}

bool CXDMcontrol::loadWaveform(int nHibChainNum, int nWaveNum, char * waveformFile)
{
	hibStatus = hibLoadWaveform(nHibChainNum, nWaveNum,  waveformFile);
	return ErrorMsg();
}
bool CXDMcontrol::getEncodepos(int nHibChainNum, int *pnEncoderPosQuadratureCounts)
{
	hibStatus = hibGetEncoderPos( nHibChainNum, pnEncoderPosQuadratureCounts);
	return ErrorMsg();
}
bool CXDMcontrol::setEncodepos(int nHibChainNum, int nEncoderPosQuadratureCounts)
{
	hibStatus = hibSetEncoderPos(nHibChainNum, nEncoderPosQuadratureCounts);
	return ErrorMsg();
}
//-----墨水控制
bool CXDMcontrol::setInkLevelSenseConfig(int nHibChainNum, hibLevelSenseConfig_t *pLevelSenseConfig)
{
	hibStatus = hibSetInkLevelSenseConfig( nHibChainNum, pLevelSenseConfig);
	return ErrorMsg();
}
bool CXDMcontrol::getInkLevelSenseConfig(int nHibChainNum, hibLevelSenseConfig_t *pLevelSenseConfig)
{
	hibStatus = hibGetInkLevelSenseConfig( nHibChainNum, pLevelSenseConfig);
	return ErrorMsg();
}
bool CXDMcontrol::getHeadInkLevels(int nHibChainNum, int &nIl1, int &nIl2, int &nIl3, int &nIl4)
{
	hibStatus = hibGetHeadInkLevels( nHibChainNum, nIl1, nIl2, nIl3, nIl4);
	return ErrorMsg();
}
bool CXDMcontrol::getHeadInkPressure(int nHibChainNum, int *pPressureChan1, int *pPressureChan2)
{
	hibStatus = hibGetHeadInkPressure(nHibChainNum, pPressureChan1, pPressureChan2);
	return ErrorMsg();
}
///----
void CXDMcontrol::autofirestart(int hibchainnum,float rate,int counts)
{
	//Variables to be Used in Program

	int _numColors = 1; //number of colors printing
	//int _numHibs = 1; // number of Hibs found
	bool _masterPcFlag = true;  // Set false for non-master PCs in multiple pc setup.
	int _printBars = 1; //number of print bars
	bool _bReversePrint = false; // Revers Print Flag
	bool fireStatus = false; // fire Status flag
	int _numJetsForHead = 880;  //the number of jets for each head
	int _headRes = 300;  // The native resolutiong for the head
	int _yImageRes = 300; // The Y image Resolution
	float quadEncoderRes = 6350; //  quad encoder count per inch


	hibDotClockDef_t dotClockConfig; //dot clock configuration for the XDMS
	hibStatus_t hibStatus;


	char dummyChar;

	//initiallizing the dot clock Structure
	dotClockConfig.type = hibAutoFire;    // options: hibQuadEncoder, hibAutoFire, hibExternalDotClock; hibQuadEncoderPos;
	dotClockConfig.fAutoFireFreqHz = rate;   // Only used for autofire dot clock source.
	dotClockConfig.uPrintResDpi = _yImageRes;
	dotClockConfig.bAutoFireFromMasterHib = true;
	dotClockConfig.bWaveAmpPresent = true;    // Must be true to actually jet ink.
	dotClockConfig.bHeadReadyOverride = false; // bHeadREadyOverride
	dotClockConfig.bEnablePageStart = true;  // Set false if dot clock gated externally or to print immediately.
	dotClockConfig.bEnablePageStop = false;
	dotClockConfig.fEncoderResolution = quadEncoderRes; //  quad encoder count per inch

	/////////////////////
	//
	//   Adding the head to the Print Bar 
	//   Configuring the Head to the Print Bar
	//   Setting up the Dot Clock
	//
	//////////////////////

	//cout << endl << "Adding the Head to the Print Bar  " << endl;
	hibStatus = hibAddHeadToPrintBar(1, 1, 1, 1, 1, 0); //hibLibAPi Call Adding the Head to the Print Bar
	if (!ErrorMsg()){::MessageBox(NULL,_T("error::hibAddHeadToPrintBar"),_T("API调用失败"),MB_ICONERROR); return;}

	//cout << endl << "Configuring the Head to the Print Bar  " << endl;
	hibStatus = hibConfigPrintBarHead(1, 1, 1, 1, 0); //hibLibAPi Call Configuring the Head to the Print Bar
	if (!ErrorMsg()){::MessageBox(NULL,_T("error::hibConfigPrintBarHead"),_T("API调用失败"),MB_ICONERROR); return;}

	//cout << endl << "Setting Up the Dot Clock  " << endl;
	hibStatus = hibSetupAllDotclocks(&dotClockConfig); //hibLibAPi Call Setting Dot Clock
	if (!ErrorMsg()) {::MessageBox(NULL,_T("error::hibSetupAllDotclocks"),_T("API调用失败"),MB_ICONERROR); return;}

	//hibStatus =hibSetActiveWaveform(1,1);
	//if (!ErrorMsg()) {::MessageBox(NULL,_T("error::hibSetupAllDotclocks"),_T("API调用失败"),MB_ICONERROR); return;}
	/////////////////////
	//
	//   Turning on and off Auto Fire of all jets for head
	//
	//////////////////////


	int mask[880] = { 1 };
	for (int k = 0; k<880;k++)
	{
		mask[k] = 1;
	}
	hibStatus = hibLoadAutofireMask(1, 880, mask);
	if (!ErrorMsg()) {::MessageBox(NULL,_T("error::hibLoadAutofireMask"),_T("API调用失败"),MB_ICONERROR); return;}
	hibStatus = hibAutofireStart(1, rate, 0, 100, counts);
	if (!ErrorMsg()) {::MessageBox(NULL,_T("error::hibAutofireStart"),_T("API调用失败"),MB_ICONERROR); return;}
}
bool CXDMcontrol::autofirestop(int hibchainnum)
{
	hibStatus = hibAutofireStop(1);
	return ErrorMsg();
}
///////////////////////////////////////////////////////////////////////
////   Global Callback Function
//	 This CALLBACK function uses a pointer to packed image data in memory for printing
//
//////////////////////////////////////////////////////////////////////

//
//typedef struct packedCbImg_t
//{
//	unsigned int * pImgBuf[4];       // One pointer for each of the head's color planes.
//	int imgLengthPixels;
//	int imgWidthPixels;
//	int bitsPerPixel;
//	int imgXResDpi;
//	int imgYResDpi;
//	bool imgReversed;
//} packedCbImg_t;

void   imageXferCallback(int nPrintBarNum, packedCbImg_t * pCbImageData, void * pUserData)
{



	//cout << "imageXferCallback() " << nPrintBarNum << " ..dataPtr: " << (int)pCbImageData << "  repeat count " << repeatCount << endl;
	//cout << "imageXferCallback() " << nPrintBarNum << "imgLengthPixels: " << pCbImageData->imgLengthPixels << "  repeat count " << repeatCount << endl;
	//cout << "imageXferCallback() " << nPrintBarNum << "imgWidthPixels: " << pCbImageData->imgWidthPixels << "  repeat count " << repeatCount << endl;
	//cout << "imageXferCallback() " << nPrintBarNum << "bitsPerPixel: " << pCbImageData->bitsPerPixel << "  repeat count " << repeatCount << endl;
	//cout << "imageXferCallback() " << nPrintBarNum << "imgXResDpi: " << pCbImageData->imgXResDpi << "  repeat count " << repeatCount << endl;
	//cout << "imageXferCallback() " << nPrintBarNum << "imgYResDpi: " << pCbImageData->imgYResDpi << "  repeat count " << repeatCount << endl;
	//cout << "imageXferCallback() " << nPrintBarNum << "imgReversed: " << pCbImageData->imgReversed << "  repeat count " << repeatCount << endl;
	if (++repeatCount <= numTimesToPrint)
	{

		*pCbImageData = getPointerToImage();

	}
	//else
//		pCbImageData->pImgBuf[0] = NULL;
}



///////////////////////////////////////////////////////////////////////
//
//   Global Callback Function
//	 This CALLBACK function uses a pointer to allow memory to be freed after data has been printed
//
//////////////////////////////////////////////////////////////////////


void  imageFreeMemCallback(int nPrintBarNum, packedCbImg_t * pCbImageData, void * pUserData)
{
	cout << "imageFreeMemCallback() " << nPrintBarNum << " ..dataPtr: " << (int)pCbImageData << endl;

	// Don't actually free memory. Buffer is owned by the library.
}





//////////////////////////////////////
//
//	Simple Function to return a pointer to a packed image
//  Note:  This function could pack the image if so desired
//
//////////////////////////////////////

packedCbImg_t getPointerToImage()
{
	packedCbImg_t packedImage;

	// Get pointer to image just packed. Image transfer callback will use this global pointer.
	int printBarNum = 1;
	hibGetLastPackedImage(printBarNum, &packedImage);

	return packedImage;
}

bool CXDMcontrol::standPrint(int nPrintBarNum, char* bmpFile)
{
	return true;
}
void CXDMcontrol::SetupPackedImageTransfer(int nPrintBarNum, void *pUserData)  //Call Back Routine
{
	hibStatus = hibSetupPackedImageTransfer(nPrintBarNum, imageXferCallback, pUserData);  //Call Back Routine
}
void CXDMcontrol::SetFreePackedMemoryCallback(int nPrintBarNum,  void *pUserData)//Call Back Routine
{
	hibStatus = hibSetFreePackedMemoryCallback(nPrintBarNum, imageFreeMemCallback, (void *)(654321 + 1)); //Call Back Routine
}
void  CXDMcontrol::xdm_auto_print()
{
	isprinting = true;
	m_Motor.WritePort(false,0,M13,true);//编码器继电器
	//OnBnClickedAddtoprintbar();
	//OnBnClickedConfigprintbar();
	//OnBnClickedSetdot();
	if ((!m_XDM.ErrorMsg())||(m_Cam.Print_z==0))

	{
		isprinting =false;
		return ;
	}
	m_XDM.addHeadToPrintbar(1,1,1,1,1,0);					
	m_XDM.configPrintBarHead(1,1,1,1,0);

	m_XDM.dotClockConfig.type = hibQuadEncoderPos;  			
	// options: hibQuadEncoder, hibAutoFire, hibExternalDotClock; hibQuadEncoderPos;				
	m_XDM.dotClockConfig.fAutoFireFreqHz = 5000;   // Only used for autofire dot clock source.				
	m_XDM.dotClockConfig.uPrintResDpi = 969;				
	m_XDM._yImageRes = 969;				
	m_XDM.dotClockConfig.bAutoFireFromMasterHib = true;				
	m_XDM.dotClockConfig.bWaveAmpPresent = true;    // Must be true to actually jet ink.				
	m_XDM.dotClockConfig.bHeadReadyOverride = false; // bHeadREadyOverride				
	m_XDM.dotClockConfig.bEnablePageStart = true;  // Set false if dot clock gated externally or to print immediately.				
	m_XDM.dotClockConfig.bEnablePageStop = false;				
	m_XDM.dotClockConfig.fEncoderResolution = 12700; //  quad encoder count per inch				
	
	m_XDM.setupAllDotclocks(&m_XDM.dotClockConfig);				



	cout<<"开始扫描打印打印！"<<endl;
	CWinThread *thread = AfxBeginThread(xdm_SCAN_Print_thread, this,
		THREAD_PRIORITY_NORMAL,0,
		CREATE_SUSPENDED, NULL);
	thread->ResumeThread();
}
UINT CXDMcontrol::xdm_SCAN_Print_thread(LPVOID param)
{
	//去打印位置；
	int m_xpos = 359000+4150+((1798.5-1836)*m_Cam.calc0_y*1000)+
		((-m_Cam.sunny_center_row+1836)*m_Cam.calc0_y*1000)
		+(2.03-0.35+0.52-2.26-0.15)*1000;
	cout<<"m_xpos"<<m_xpos<<endl;
	m_Motor.absolute_move(MOTOR11,m_xpos);//m_Cam.calc_print_camerax[1]);移动到正县委 反向打
	m_Motor.absolute_move(MOTOR12,m_Cam.Print_z);//print_cameraz[1]);
	m_Motor.wait_move_done(MOTOR11);
	m_Motor.wait_move_done(MOTOR12);
	CXDMcontrol *p = (CXDMcontrol*)param;
	int dpi = 900;
	int width = 5496;
	int passnum = dpi/300;//每一大步；
	int steps = width/(880*passnum);
	int mstep = (width%(880*passnum)>0?1:0);
	int totalstep = steps+mstep;

	int count = 0;
	if (1)
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
			filepath.Format(_T("D:\\XDPICZRS\\%d.bmp"),count);
			string str = (CStringA)filepath;
			const char *p1 = str.c_str();
			char q[256];
			strcpy(q,p1);
			cout << endl<<q << endl;
			repeatCount = 0;
			if (1)
			{
				int start_pos = -430041+(25400*2*500)/m_XDM._yImageRes+12700*2+(2748-2648.5)*m_Cam.calc0_x*2000
					+(-2748+m_Cam.sunny_center_column)*m_Cam.calc0_x*2000-(0.41+0.28-0.13-0.65)*2000;
				if (start_pos>=0)
				{
					cout<<"开始打印位置错误"<<endl;
					p->isprinting =false;
					return 0;
				}
				cout<<"start_pos"<< start_pos<<endl;
				m_XDM.hibStatus = hibSetEncoderPos(1, start_pos);//-430041);//-m_Cam.calc_print_cameray[1]);
			}
			else
			{
				m_XDM.hibStatus = hibSetEncoderPos(1, -m_Cam.print_cameray[1]);//-m_Cam.calc_print_cameray
			}

			if (!m_XDM.ErrorMsg())return 0;
			//p->m_XDM.hibStatus =hibSetPrintStartPos(1, m_Cam.print_cameray[1]/2);
			//if (!p->m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibConfigPage(1, 1, 1, 0, 0);
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibResetGather(); 
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibClearPackedImages(1); //hibLibAPi Call to Clear the any Packed Images 
			if (!m_XDM.ErrorMsg())return 0;
			cout<<"m_XDM._yImageRes"<< m_XDM._yImageRes<<endl;
			m_XDM.hibStatus = hibLoadImageFileX(1, q,m_XDM._headRes, m_XDM._yImageRes, 0, 0, 0, 0, 0); //hibLibAPi Call to Load the Image
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibPackImage(1, m_XDM._yImageRes, false); //hibLibAPi Call to Pack the Image
			if (!m_XDM.ErrorMsg())return 0;
			for (int i = 0; i < 1; i++)
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
					if (1)
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
			if (1)
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
				pos = (int)(25400/dpi)+6760-50;
			else
				pos = (int)(25400/dpi)+74380-50;
			//int pos = (int)((float)((float)((float)25400/(float)300))*(float)880)-x_movepos;
			cout<<"X轴大步需移动距离：";
			//cout<<"X轴已经移动距离："<<x_movepos<<endl;
			if (1)//手动定位反方向
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
UINT CXDMcontrol::mulit_Head_thread(LPVOID param)
{
	//去打印位置；
	CXDMcontrol *p = (CXDMcontrol*)param;
	int headNums = 0;
	for ( int k=0;k<3;k++)
	{
		if (p->isUseHead[k])
		{
			headNums++;
		}
	}

	int m_xpos = 359000+4150+((1798.5-1836)*m_Cam.calc0_y*1000)+
		((-m_Cam.sunny_center_row+1836)*m_Cam.calc0_y*1000)
		+(2.03-0.35+0.52-2.26-0.15)*1000;
	cout<<"m_xpos"<<m_xpos<<endl;
	m_Motor.absolute_move(MOTOR11,m_xpos);//m_Cam.calc_print_camerax[1]);移动到正县委 反向打
	m_Motor.absolute_move(MOTOR12,m_Cam.Print_z);//print_cameraz[1]);
	m_Motor.wait_move_done(MOTOR11);
	m_Motor.wait_move_done(MOTOR12);
	
	int dpi = p->xdm_xdpi;
	if ((dpi%(300*headNums))!=0)
	{
		cout<<"使用"<<headNums<<"个喷头无法打印出"<<dpi<<"dpi的图形!"<<endl;
		return 0;
	}
	int width = p->xdm_imageWidth;
	int passnum = dpi/(300*headNums);//每一大步；
	int steps = width/(880*passnum);
	int mstep = (width%(880*passnum)>0?1:0);
	int totalstep = steps+mstep;

	int count = 0;
	if (1)
	{
		count = totalstep*passnum-1;//总的拆图数量
	}
	else
	{
		count = 0;
	}
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
		for (int j = 0;j<passnum/headNums;j++)//开始为每一个喷头加载图像
		{
			if (p->stopprint)
			{
				break;
			}

			CString filepath;
			filepath.Format(_T("D:\\MulitHead\\%d.bmp"),count);
			string str = (CStringA)filepath;
			const char *p1 = str.c_str();
			char q[256];
			strcpy(q,p1);
			cout << endl<<q << endl;



			for(int i = 0;i<3;i++)
			{
				if (p->isUseHead[i])
				{
					repeatCount = 0;
					if (1)
					{
						int start_pos = -430041+(25400*2*500)/m_XDM._yImageRes+12700*2+(2748-2648.5)*m_Cam.calc0_x*2000
							+(-2748+m_Cam.sunny_center_column)*m_Cam.calc0_x*2000-(0.41+0.28-0.13-0.65)*2000;
						if (start_pos>=0)
						{
							cout<<"开始打印位置错误"<<endl;
							p->isprinting =false;
							return 0;
						}
						cout<<"start_pos"<< start_pos<<endl;
						m_XDM.hibStatus = hibSetEncoderPos(i, start_pos-i*5000);//设置打印位置
					}
					else
					{
						m_XDM.hibStatus = hibSetEncoderPos(i, -m_Cam.print_cameray[1]);//-m_Cam.calc_print_cameray
					}

					if (!m_XDM.ErrorMsg())return 0;
					//p->m_XDM.hibStatus =hibSetPrintStartPos(1, m_Cam.print_cameray[1]/2);
					//if (!p->m_XDM.ErrorMsg())return 0;
					m_XDM.hibStatus = hibConfigPage(i, 1, 1, 0, 0);
					if (!m_XDM.ErrorMsg())return 0;
				}
			}
			m_XDM.hibStatus = hibResetGather(); 
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibClearPackedImages(1); //hibLibAPi Call to Clear the any Packed Images 
			if (!m_XDM.ErrorMsg())return 0;
			cout<<"m_XDM._yImageRes"<< m_XDM._yImageRes<<endl;
			m_XDM.hibStatus = hibLoadImageFileX(1, q,m_XDM._headRes, m_XDM._yImageRes, 0, 0, 0, 0, 0); //hibLibAPi Call to Load the Image
			if (!m_XDM.ErrorMsg())return 0;
			m_XDM.hibStatus = hibPackImage(1, m_XDM._yImageRes, false); //hibLibAPi Call to Pack the Image
			if (!m_XDM.ErrorMsg())return 0;

			if (1)
			{
				count--;
			}
			else
			{
				count++;
			}
			for (int i = 0; i < 1; i++)
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
					if (1)
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
		}
		if(k!=totalstep-1)
		{
			long xcurpos =0;
			APS_get_position(MOTOR11,&xcurpos);
			cout<<"X轴电机位置距离："<<xcurpos<<endl;
			int pos = 0;
			if (k==0)
				pos = (int)(25400/dpi)+(p->use_last_jet_numbers*84.5)-50;
			else
				pos = (int)(25400/dpi)+74380-50;
			//int pos = (int)((float)((float)((float)25400/(float)300))*(float)880)-x_movepos;
			cout<<"X轴大步需移动距离：";
			//cout<<"X轴已经移动距离："<<x_movepos<<endl;
			if (1)//手动定位反方向
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
void CXDMcontrol::xdm_chaifen(int laststep_use_words,int X_DPI,INT headnums,CString filepath)
{
		TCHAR* pszFileName = (LPTSTR)(LPCTSTR)filepath;
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

		xdm_imageWidth = width;
		xdm_imageHeight = height;
		xdm_xdpi = X_DPI;
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
		int x_dpi = X_DPI;
		int passnum = x_dpi/300;//每一大步单个喷头pass数
		if (headnums ==0)
		{
			cout<<"喷头数量为0"<<endl;
			return;
		}
		if (passnum%headnums!=0)
		{
			cout<<"DPI与喷头数量不匹配"<<endl;
			return; 
		}

		int mulitpass = passnum/headnums;//每一大步多个喷头pass数
		int steps = width/(880*passnum);
		int mstep = (width%(880*passnum)>0?1:0);



		int totalstep = steps+mstep;



		height +=1000;//新图前后添加空白各500行
		int stepwidth = WIDTHBYTES(880*passnum);
		char *buff = new char[stepwidth*height];//一大步大图

		int smallwidth = WIDTHBYTES(880);
		char *smallbuf = new char[smallwidth*height];
		int count =0;
		char *zero = new char[laststep_use_words];
		char *old = new char[laststep_use_words];
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
					if (k!=totalstep-1)
					{
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
					}
					else
					{
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
							memset(zero,0xff,laststep_use_words);
							memset(old,0xff,laststep_use_words);
							memcpy(old,smallbuf+k1*smallwidth,laststep_use_words);
							memcpy(smallbuf+k1*smallwidth,zero,laststep_use_words);
							memcpy(smallbuf+k1*smallwidth+(110-laststep_use_words),old,laststep_use_words);
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
		delete[]zero;
		delete[]old;
		xdm_hebing( headnums, X_DPI);
}
void CXDMcontrol::xdm_hebing(int head_Nums,int X_DPI)
{
	int passnum = X_DPI/(300);//每一大步；
	int steps = xdm_imageWidth/(880*passnum);
	int mstep = (xdm_imageWidth%(880*passnum)>0?1:0);
	int totalstep = steps+mstep;
	int imagewordwidth = WIDTHBYTES(880*head_Nums);
	int count = 0;

	count = totalstep*passnum;//总的拆图数量
	CString filepath;
	char * bigimgbuf = new char[WIDTHBYTES(880*head_Nums)*(xdm_imageHeight+1000)];
	memset(bigimgbuf,0x00,WIDTHBYTES(880*head_Nums)*(xdm_imageHeight+1000));
	for (int k = 0;k<count/head_Nums;k++)
	{
		for (int j=0;j<head_Nums;j++)
		{
			int name = j+k*head_Nums;
			filepath.Format(_T("d:\\XDPI\\%d.bmp"),name);
			get_imagebuf(filepath);
			for (int i = 0;i<xdm_imageHeight+1000;i++)
			{
				memcpy(bigimgbuf+110*j+(imagewordwidth)*i,readimgbuf+WIDTHBYTES(880)*i,110);
			}
			delete []readimgbuf;
		}
		CFile filewrite3;
		CString name1;
		name1.Format(_T("D:\\MulitHead\\%d.bmp"),k);
		TCHAR *pszFileName = (LPTSTR)(LPCTSTR)name1;
		BITMAPFILEHEADER bmfHdr;
		BITMAPINFOHEADER IpBI;
		RGBQUAD quad[2];
		quad[0].rgbBlue=0;
		quad[0].rgbGreen=0;
		quad[0].rgbRed=0;
		quad[0].rgbReserved=0;

		quad[1].rgbBlue=255;
		quad[1].rgbGreen=255;
		quad[1].rgbRed=255;
		quad[1].rgbReserved=0;
		if(!filewrite3.Open(pszFileName, CFile::modeWrite|CFile::modeCreate))
			return ;

		bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
		bmfHdr.bfSize=WIDTHBYTES(880*head_Nums)*(xdm_imageHeight+1000)+bmfHdr.bfOffBits;
		bmfHdr.bfType=DIB_HEADER_MARKER;
		bmfHdr.bfReserved1=0;
		bmfHdr.bfReserved2=0;

		IpBI.biBitCount=1;
		IpBI.biClrImportant=0;
		IpBI.biClrUsed=0;
		IpBI.biCompression=BI_RGB;
		IpBI.biHeight=(xdm_imageHeight+1000);
		IpBI.biPlanes=1;
		IpBI.biSize=sizeof(BITMAPINFOHEADER);
		IpBI.biSizeImage=WIDTHBYTES(880*head_Nums)*(xdm_imageHeight+1000);
		IpBI.biWidth=880*passnum;

		filewrite3.Write(&bmfHdr,sizeof(bmfHdr));
		filewrite3.Write(&IpBI,sizeof(IpBI));
		filewrite3.Write(quad,sizeof(RGBQUAD)*2);
		filewrite3.Write(bigimgbuf,WIDTHBYTES(880*head_Nums)*(xdm_imageHeight+1000));
		filewrite3.Close();

	}
	 delete []bigimgbuf;

}
char* CXDMcontrol::get_imagebuf(CString str)
{
	TCHAR* pszFileName = (LPTSTR)(LPCTSTR)str;
	CFile file;
	if(!file.Open(pszFileName, CFile::modeRead))
		return  NULL;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER IpBI;
	RGBQUAD quad[2];

	file.Read(&bmfHdr,sizeof(bmfHdr));
	file.Read(&IpBI,sizeof(IpBI));
	file.Read(quad,sizeof(RGBQUAD)*2);
	int width = IpBI.biWidth;
	int height = IpBI.biHeight;

	int imagewidth = WIDTHBYTES(width);
	readimgbuf = new char[WIDTHBYTES(width)*height];
	memset(readimgbuf,0xff,imagewidth*height);
	file.Read(readimgbuf,WIDTHBYTES(width)*height);
	file.Close();
	return readimgbuf;
}
