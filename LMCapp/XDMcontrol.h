#pragma once
#include "stdafx.h"
#include "hibLibApi.h"
#include "Logic.h"
extern int repeatCount;  //Values Used in Call Back Functions
static int numTimesToPrint; //Values Used in Call Back Functions
class CXDMcontrol
{
public:
	CXDMcontrol(void);
	virtual ~CXDMcontrol(void);

	//控制变量
	int _numColors; //number of colors printing
	int _numHibs ; // number of Hibs found
	bool _masterPcFlag;  // Set false for non-master PCs in multiple pc setup.
	int _printBars ; //number of print bars
	bool _bReversePrint ; // Revers Print Flag
	bool fireStatus; // fire Status flag


	int _numJetsForHead ;  //the number of jets for each head
	int _headRes ;  // The native resolutiong for the head
	int _yImageRes ; // The Y image Resolution





	hibDotClockDef_t dotClockConfig; //dot clock configuration for the XDMS
	hibStatus_t hibStatus;

	int repeatTime;
	int pageLength;
	float voltageDelta ;
	float quadEncoderRes ; //  quad encoder count per inch
	char checkValue;

	// variable for setting temperature
	float fCurrResTemp;
	float fCurrLeftJSTemp;
	float fCurrRightJSTemp;	
	
	float *pCurrentResTemp ;
	float *pCurrentLeftJSTemp ;
	float *pCurrentRightJSTemp;
	float  fSetResTemp;
	float  fSetLeftJSTemp;
	float  fSetRightJSTemp;
	//----yali 
	int *pPugre1;
	int *pPugre2;
	int Pugre1;
	int Pugre2;
	//variables for setting Y-delays
	int lowJetNumber;
	int highJetNumber;
	int yDelayNumber;
	//-------------------------封装函数
	bool ErrorMsg();
	bool initHib();
	bool closeHib();
	bool addHeadToPrintbar(int nPrintBarNum, int nPrintBarHdNum, int nHibNum, int nFirstImgCol, int nFirstHdCol, int nLastHdCol);
	bool configPrintBarHead(int nPrintBarNum, int nPrintBarHdNum, int nFirstImgCol, int nFirstHdCol, int nLastHdCol);
	bool setupAllDotclocks(hibDotClockDef_t *pDotClockDef);
	bool readTemp(int nHibChainNum, int nWaveNum, int nHeaterNum, float *pfSetPointTempC);
	bool setTemp(int nHibChainNum, int nWaveNum, int nHeaterNum, float fSetPointTempC);
	bool readHeaterTemp(int nHibChainNum, int nHeaterNum, float *pfHeaterTempC);//获取加热器温度


	bool adjustWaveformVoltage(int nHibChainNum, int nWaveNum, float fDeltaVoltage);
	bool loadWaveform(int nHibChainNum, int nWaveNum, char * waveformFile);

	//---获取编码器位置
	bool getEncodepos(int nHibChainNum, int *pnEncoderPosQuadratureCounts);
   //----设置编码器位置
	bool setEncodepos(int nHibChainNum, int pnEncoderPosQuadratureCounts);
	//-----------------------墨水量控制
	bool setInkLevelSenseConfig(int nHibChainNum, hibLevelSenseConfig_t *pLevelSenseConfig);
	bool getInkLevelSenseConfig(int nHibChainNum, hibLevelSenseConfig_t *pLevelSenseConfig);
	bool getHeadInkLevels(int nHibChainNum, int &nIl1, int &nIl2, int &nIl3, int &nIl4);
	bool getHeadInkPressure(int nHibChainNum, int *pPressureChan1, int *pPressureChan2);
	//-----------------------
	void SetupPackedImageTransfer(int nPrintBarNum, void *pUserData);  //Call Back Routine
	
	void SetFreePackedMemoryCallback(int nPrintBarNum,  void *pUserData); //Call Back Routine


	bool standPrint(int nPrintBarNum, char* bmpFile);
	//------闪喷
	void autofirestart(int hibchainnum,float rate,int counts);
	bool autofirestop(int hibchainnum);
	void  xdm_auto_print();
	static UINT xdm_SCAN_Print_thread(LPVOID param);
	bool stopprint;
	bool isprinting;
	static UINT mulit_Head_thread(LPVOID param);
	int xdm_imageWidth;//浏览图片的时候赋值
	int xdm_imageHeight;
	int xdm_xdpi;
	int xdm_ydpi;
	bool isUseHead[3];
	int use_last_jet_numbers;
	//---------------------拆分图像
	void xdm_chaifen(int laststep_use_words,int X_DPI,INT headnums,CString filepath);
	void xdm_hebing(int head_Nums,int X_DPI);
	char* get_imagebuf(CString str);
	char * readimgbuf;
	int usehead_numbers;
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')
};
//--------回调函数
packedCbImg_t  getPointerToImage();
void  imageXferCallback(int nPrintBarNum, packedCbImg_t * pCbImageData, void * pUserData);
void  imageFreeMemCallback(int nPrintBarNum, packedCbImg_t * pCbImageData, void * pUserData);
 extern CXDMcontrol m_XDM;