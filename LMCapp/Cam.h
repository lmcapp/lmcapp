#pragma once
//#define  DAHENG_USB
#define  DAHENG_MER
//#ifdef DAHENG_USB
//#include "stdafx.h"
//#include "LMCapp.h"
//#include "HVDAILT.h"
//#include "Raw2Rgb.h"
//#include "Halconcpp.h"
//using namespace Halcon;
//#define IS_USB_HV130(type)	       ((type) == (HV1300UCTYPE) || (type) == (HV1300UMTYPE) ||\
//	(type) == (HV1301UCTYPE) || (type) == (HV1302UMTYPE) ||\
//	(type) == (HV1302UCTYPE) || (type) == (HV1303UMTYPE) ||\
//	(type) == (HV1303UCTYPE) || (type) == (HV1350UMTYPE) ||\
//	(type) == (HV1350UCTYPE) || (type) == (HV1351UMTYPE) ||\
//	(type) == (HV1351UCTYPE))
//
//#define IS_USB_HV200(type)		   ((type) == (HV2000UCTYPE) || (type) == (HV2001UCTYPE) ||\
//	(type) == (HV2002UCTYPE) || (type) == (HV2003UCTYPE) ||\
//	(type) == (HV2050UCTYPE) || (type) == (HV2051UCTYPE))
//
//#define IS_USB_HV300(type)		   ((type) == (HV3000UCTYPE) || (type) == (HV3102UCTYPE) ||\
//	(type) == (HV3103UCTYPE) || (type) == (HV3150UCTYPE) ||\
//	(type) == (HV3151UCTYPE))
//
//#define IS_USB_GV400(type)		   ((type) == (GV400UCTYPE) || (type) == (GV400UMTYPE))
//
//#define IS_USB_HV5051(type)        ((type) == (HV5051UCTYPE) || (type) == (HV5051UMTYPE))
////�����Լ���0
//#define  MY_ZERO 0.000000001
//#define  CAMERA_NUMBER 2
//class CCam
//{
//public:
//	CCam(void);
//	virtual ~CCam(void);
//
//
//public:
//
//
//    int dwLastStatus;
//	HHV	m_hhv[CAMERA_NUMBER];			///< ������������	
//	long m_lHBlanking;	///< ˮƽ����
//	long m_lVBlanking;	///< ��ֱ����
//	BOOL m_bOpen;		///< ��ʼ����־
//	BOOL m_bStart;		///< ������־
//
//	HV_BAYER_LAYOUT m_Layout;	///< bayer��ʽ	
//	BITMAPINFO *m_pBmpInfo[CAMERA_NUMBER];		///< BITMAPINFO �ṹָ�룬��ʾͼ��ʱʹ��
//	BYTE *m_pRawBuffer[CAMERA_NUMBER];			///< �ɼ�ͼ��ԭʼ���ݻ�����
//	BYTE *m_pImageBuffer[CAMERA_NUMBER];		///< Bayerת���󻺳���
//	char m_chBmpBuf[CAMERA_NUMBER][2048];		///< BIMTAPINFO �洢��������m_pBmpInfo��ָ��˻�����
//	CString m_strSNleft;
//	CString m_strSNright;
//
//	CWnd                   *m_pWnd[CAMERA_NUMBER];                   ///< ��ʾͼ�񴰿�(�ؼ�)ָ��
//	HDC                     m_hDC[CAMERA_NUMBER];                    ///< ����ͼ��DC���
//
//	BYTE m_pLutR[256] ;		///< ��ɫ���ұ�,R����
//	BYTE m_pLutG[256] ;		///< ��ɫ���ұ�,G����
//	BYTE m_pLutB[256] ;		///< ��ɫ���ұ�,B����
//
//	bool initcam(UINT index);
//	/// �ɼ��ص��������û�Ҳ���Զ���Ϊȫ�ֺ����������Ϊ��ĳ�Ա����������Ϊ��̬��Ա������
//	static int CALLBACK SnapThreadCallback(HV_SNAP_INFO *pInfo); //0
//	static int CALLBACK SnapThreadCallback1(HV_SNAP_INFO *pInfo); //1
//	/// �����ع�ʱ��
//	HVSTATUS SetExposureTime(int nWindWidth,
//		long lTintUpper,
//		long lTintLower,
//		long HBlanking,
//		HV_SNAP_SPEED SnapSpeed,
//		HV_RESOLUTION Resolution,UINT index);
//	/// ��ȡ״̬��
//	HVSTATUS GetLastStatus(UINT index);
//	/// ��ȡbayer��ʽ
//	HV_BAYER_LAYOUT HVGetBayerType(UINT index);
//	void OnSnapShot(UINT index);
//	void OnSnapContinue(UINT index);
//	void OnStopSnap(UINT index);
//	void OnDrawImage(UINT index);
//	//--------------------------halcon ͼ����
//	HTuple  Row0, Column0, Phi0, Length01, Length02, Row1, Column1;//------------�����õı���
//	HTuple  Phi1, Length11, Length12, MeasureHandle, RowEdge;
//	HTuple  ColumnEdge, Amplitude, Distance, MeasureHandle1;
//	HTuple  RowEdge1, ColumnEdge1, Amplitude1, Distance1;
//	//--------------------------------------------------
//	Hlong WindowHandle[CAMERA_NUMBER];
//	Hlong bigwindow;
//	Hobject  Image[2]; 
//	void initimage(Hobject *image);
//	void creat_window(UINT index);
//	void move_window(UINT index,int row,int column,int width,int height);//set_window_extents
//	void NewRGBImage(UINT index);	
//	void NewGrayImage(Hobject *image, int width, int height, BYTE *pbuff) { gen_image1(image, "byte", width, height, (Hlong)pbuff); };
//	void dispImage(UINT index);
//	void openbigwindow();
//	void closebigwindow();
//	bool bigwindowisopen;
//	void dispcorss(UINT index);
//	int nWndWidth ;//���ڿ��
//	int nWndHeight;//���ڸ߶�
//    void save_image(UINT index);
//	void measure_image(UINT index);
//
//	void disp_message (Halcon::HTuple WindowHandle, Halcon::HTuple String, Halcon::HTuple CoordSystem, 
//	Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Color, Halcon::HTuple Box);
//	bool get_circle(UINT Image_dex ,double* result_row,double* result_column);
//
//	double get_angle(double row1,double column1,double row2,double column2);
//	void  saveini();
//	void  readini();
//	double calc0_x,calc0_y,calc1_x,calc1_y;//�궨���1���سߴ�
//	//---------------����У������
//	long calc_posx[3];//�ƶ����yong
//	long calc_posy[3];
//	void calc_mark_pos();
//	double stepx[2] ;
//	double stepy[2] ;//������������ĵľ���
//	double  buchang_angle;//�����Ƕ�
//	long  buchangposx[2];//����λ��
//	long  buchangposy[2];
//	int   shuttertime[2],gain[2];
//	double Y_angle[2];
//	//--------------------------------------����ģ�庯��
//	bool creat_model(UINT index);
//	bool read_model();
//	bool find_model(UINT index,double* row,double* column);
//	HTuple ModelID[CAMERA_NUMBER];
//	void save_image();
//	void setcamera(int index);
//	double cam_row[2];
//	double cam_column[2];
//	bool isgetcir;
//	//---------------------��������
//	int celiang_width[2];
//	int celiang_height[2];
//	int area[2];
//	int ra[2];
//	int rb[2];
//	float radius;//��Ե���Ͱ뾶
//	BOOL USE_MOBAN;
//};
//#endif // DAHENG_USB
#ifdef DAHENG_MER
#include "stdafx.h"
#include "LMCapp.h"
#include "GxIAPI.h"
#include "DxImageProc.h"
#include "Halconcpp.h"
#include "Cmath.h"
#include "WaxLocate.h"
using namespace Halcon;
class CStopWatch
{ 
public: 

	/// ���캯�� 
	CStopWatch()
	{ 
		Start(); 
	} 

	/// ��ʼ��ʱ
	void Start() 
	{ 
		QueryPerformanceCounter(&m_StartTime);
	} 

	/// ֹͣ��ʱ,ms
	double Stop() 
	{
		QueryPerformanceCounter(&m_StopTime);
		double theElapsedTime = ElapsedTime();

		m_StartTime = m_StopTime; 
		return theElapsedTime;
	} 

	/// ��ȡʱ��� 
	double ElapsedTime() 
	{ 
		LARGE_INTEGER timerFrequency; QueryPerformanceFrequency(&timerFrequency); 
		__int64 oldTicks = ((__int64)m_StartTime.HighPart << 32) + (__int64)m_StartTime.LowPart;
		__int64 newTicks = ((__int64)m_StopTime.HighPart << 32) + (__int64)m_StopTime.LowPart; 
		long double timeDifference = (long double) (newTicks - oldTicks); 
		long double ticksPerSecond = (long double) (((__int64)timerFrequency.HighPart << 32) + (__int64)timerFrequency.LowPart); 
		return (double)(timeDifference * 1000/ ticksPerSecond); 
	}
protected: 
	LARGE_INTEGER m_StartTime;   ///< ��ʼʱ��
	LARGE_INTEGER m_StopTime;    ///< ֹͣʱ�� 
};
///��������ṹ��
typedef struct CAMER_INFO
{
	BITMAPINFO					*pBmpInfo;		  ///< BITMAPINFO �ṹָ�룬��ʾͼ��ʱʹ��
	BYTE						*pImageBuffer;	  ///< ָ�򾭹�������ͼ�����ݻ�����
	BYTE                        *pRawBuffer;      ///< ָ��ԭʼRAWͼ������
	BYTE                        *disp_char;
	char						chBmpBuf[2048];	  ///< BIMTAPINFO �洢��������m_pBmpInfo��ָ��˻�����	
	int64_t                     nPayLoadSise;     ///< ͼ����С
	int64_t					    nImageWidth;	  ///< ͼ����
	int64_t					    nImageHeight;	  ///< ͼ��߶�	
	int64_t					    nBayerLayout;	  ///< Bayer�Ų���ʽ
	bool						bIsColorFilter;	  ///< �ж��Ƿ�Ϊ��ɫ���
	BOOL						bIsOpen;		  ///< ����Ѵ򿪱�־
	BOOL						bIsSnap;		  ///< ������������ɼ���־
	float						fFps;			  ///< ֡��
}CAMER_INFO;
#define  CAMERA_NUMBER 2
#define  GX_VERIFY(emStatus) \
	if(emStatus != GX_STATUS_SUCCESS) \
{\
	ShowErrorString(emStatus); \
	return emStatus;\
}  ///< ������ʾ�����궨��
#define  GX_VVERIFY(emStatus) \
	if(emStatus != GX_STATUS_SUCCESS) \
{\
	ShowErrorString(emStatus); \
	return ;\
}  ///< ������ʾ�����궨��
class CCam
{
public:
	CCam(void);
	virtual ~CCam(void);


	// Operations
public:
	//��ָ��SN���
	GX_STATUS Open_camera(char* sn,int camera_index);
	//�������
	GX_STATUS Setcamera(int index);
	///�����ע����Ӧ�Ļص���Ŀǰ���֧��4���
	void RegisterCallback(int nCamID);

	///������Ϣ��ʾ
	void ShowErrorString(GX_STATUS emErrorStatus);

	///�����豸������λ��Ϊ8
	GX_STATUS SetPixelFormat8bit(GX_DEV_HANDLE hDevice);

	 GX_STATUS OnCONSnap(int index);//��ʼ��������
	 GX_STATUS OnStopCONSnap(int index);//ֹͣ��������
	 GX_STATUS OnCloseDevice(int index);//�ر����
	 GX_STATUS OnSendSoftCommand(int index);//��һ����Ƭ


	///0������ص�
	static void __stdcall OnFrameCallbackFun1(GX_FRAME_CALLBACK_PARAM* pFrame);

	///1������ص�
	static void __stdcall OnFrameCallbackFun2(GX_FRAME_CALLBACK_PARAM* pFrame);

	GX_DEV_HANDLE	    m_hDevices[CAMERA_NUMBER];			///< �豸���ָ��
	CAMER_INFO	  	    m_pstCam[CAMERA_NUMBER];			///< ������ݽṹ��		
	int				    m_nOperateID[CAMERA_NUMBER];		///< �����豸ID
	uint32_t		    m_nCamNum;			///< �����Ŀ
	BOOL			    m_bViewID;			///< �Ƿ���ʾ������
	int*		 	    m_npfpsCont;		///< ֡�ʼ���
	GX_DEVICE_BASE_INFO *m_pBaseinfo[CAMERA_NUMBER]; 	    ///< �豸��Ϣ�ṹ��

	// ͼ����ʾ��Դ����
	CWnd                *m_pWnd[CAMERA_NUMBER];       ///< �зִ���ָ������
	HDC                  m_hDC[CAMERA_NUMBER];         ///< �зִ���DC���� 
	BYTE                *m_pImageBuffer[CAMERA_NUMBER];		///< Bayerת���󻺳���


	bool initcam(UINT index);
	///// �ɼ��ص��������û�Ҳ���Զ���Ϊȫ�ֺ����������Ϊ��ĳ�Ա����������Ϊ��̬��Ա������
	//static int CALLBACK SnapThreadCallback(HV_SNAP_INFO *pInfo); //0
	//static int CALLBACK SnapThreadCallback1(HV_SNAP_INFO *pInfo); //1
	///// �����ع�ʱ��
	//HVSTATUS SetExposureTime(int nWindWidth,
	//	long lTintUpper,
	//	long lTintLower,
	//	long HBlanking,
	//	HV_SNAP_SPEED SnapSpeed,
	//	HV_RESOLUTION Resolution,UINT index);
	///// ��ȡ״̬��
	//HVSTATUS GetLastStatus(UINT index);
	///// ��ȡbayer��ʽ
	//HV_BAYER_LAYOUT HVGetBayerType(UINT index);
	//void OnSnapShot(UINT index);
	//void OnSnapContinue(UINT index);
	//void OnStopSnap(UINT index);
	//void OnDrawImage(UINT index);
	//--------------------------halcon ͼ����
	HTuple  Row0, Column0, Phi0, Length01, Length02, Row1, Column1;//------------�����õı���
	HTuple  Phi1, Length11, Length12, MeasureHandle, RowEdge;
	HTuple  ColumnEdge, Amplitude, Distance, MeasureHandle1;
	HTuple  RowEdge1, ColumnEdge1, Amplitude1, Distance1;
	//--------------------------------------------------
	Hlong WindowHandle[CAMERA_NUMBER];
	Hlong bigwindow;
	Hobject  Image[CAMERA_NUMBER]; 
	void initimage(Hobject *image);
	void creat_window(UINT index);
	void move_window(UINT index,int row,int column,int width,int height);//set_window_extents
	void NewRGBImage(UINT index);	
	void NewGrayImage(Hobject *image, int width, int height, BYTE *pbuff) { gen_image1(image, "byte", width, height, (Hlong)pbuff); };
	void dispImage(UINT index);
	void openbigwindow();
	void closebigwindow();
	bool bigwindowisopen;
	void dispcorss(UINT index);
	int nWndWidth ;//���ڿ��
	int nWndHeight;//���ڸ߶�
	int Width,Height;
	void save_image(UINT index);
	void measure_image(UINT index);

	void disp_message (Halcon::HTuple WindowHandle, Halcon::HTuple String, Halcon::HTuple CoordSystem, 
		Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Color, Halcon::HTuple Box);
	bool get_circle(UINT Image_dex ,double* result_row,double* result_column);

	double get_angle(double row1,double column1,double row2,double column2);
	void  saveini();
	void  readini();
	double calc0_x,calc0_y,calc1_x,calc1_y;//�궨���1���سߴ�
	//---------------����У������
	long calc_posx[3];//�ƶ����yong
	long calc_posy[3];
	void calc_mark_pos();
	double stepx[2] ;
	double stepy[2] ;//������������ĵľ���
	double  buchang_angle;//�����Ƕ�
	long  buchangposx[2];//����λ��
	long  buchangposy[2];
	int   shuttertime[2],gain[2];
	double Y_angle[2];
	//--------------------------------------����ģ�庯��
	bool creat_model(UINT index);
	bool read_model();
	bool find_model(UINT index,double* row,double* column);
	bool sunny_find_model(UINT index);
	void get_button_pos(Hlong WindowHandle,double  &row,double &column ,CString str);
	HTuple ModelID[CAMERA_NUMBER];
	void save_image();
	double cam_row[2];
	double cam_column[2];
	bool isgetcir;
	//---------------------��������
	int celiang_width[2];
	int celiang_height[2];
	int area[2];
	int ra[2];
	int rb[2];
	float radius;//��Ե���Ͱ뾶
	BOOL USE_MOBAN;
	//sunny-celiang
	double sunny_row[4];
	double sunny_column[4];
	double sunny_radius[4];
	int sunny_thresd[4];
	void m_disp_circle();
	void m_draw_roi(int id);
	bool sunny_measure();
	double sunny_center_row;
	double sunny_center_column;
	double sunny_angle;//����
	long print_camerax[4];//��ͷ��ӡ���ĵ����λ�ã�
	long print_cameray[4];
	long print_cameraz[4];

	long Print_z;//��ӡ�߶ȣ�

	long calc_print_camerax[4];//���ݲ�������������λ�ã�
	long calc_print_cameray[4];
	long calc_print_cameraz[4];
    

	bool is_save_img;

	//-------------------������λ�㷨���ڳ�������
	bool czrs_measure();
};
#endif // DAHENG_MER
extern CCam m_Cam;