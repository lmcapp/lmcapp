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
////定义自己的0
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
//	HHV	m_hhv[CAMERA_NUMBER];			///< 数字摄像机句柄	
//	long m_lHBlanking;	///< 水平消隐
//	long m_lVBlanking;	///< 垂直消隐
//	BOOL m_bOpen;		///< 初始化标志
//	BOOL m_bStart;		///< 启动标志
//
//	HV_BAYER_LAYOUT m_Layout;	///< bayer格式	
//	BITMAPINFO *m_pBmpInfo[CAMERA_NUMBER];		///< BITMAPINFO 结构指针，显示图像时使用
//	BYTE *m_pRawBuffer[CAMERA_NUMBER];			///< 采集图像原始数据缓冲区
//	BYTE *m_pImageBuffer[CAMERA_NUMBER];		///< Bayer转换后缓冲区
//	char m_chBmpBuf[CAMERA_NUMBER][2048];		///< BIMTAPINFO 存储缓冲区，m_pBmpInfo即指向此缓冲区
//	CString m_strSNleft;
//	CString m_strSNright;
//
//	CWnd                   *m_pWnd[CAMERA_NUMBER];                   ///< 显示图像窗口(控件)指针
//	HDC                     m_hDC[CAMERA_NUMBER];                    ///< 绘制图像DC句柄
//
//	BYTE m_pLutR[256] ;		///< 颜色查找表,R分量
//	BYTE m_pLutG[256] ;		///< 颜色查找表,G分量
//	BYTE m_pLutB[256] ;		///< 颜色查找表,B分量
//
//	bool initcam(UINT index);
//	/// 采集回调函数，用户也可以定义为全局函数，如果作为类的成员函数，必须为静态成员函数。
//	static int CALLBACK SnapThreadCallback(HV_SNAP_INFO *pInfo); //0
//	static int CALLBACK SnapThreadCallback1(HV_SNAP_INFO *pInfo); //1
//	/// 设置曝光时间
//	HVSTATUS SetExposureTime(int nWindWidth,
//		long lTintUpper,
//		long lTintLower,
//		long HBlanking,
//		HV_SNAP_SPEED SnapSpeed,
//		HV_RESOLUTION Resolution,UINT index);
//	/// 获取状态码
//	HVSTATUS GetLastStatus(UINT index);
//	/// 获取bayer格式
//	HV_BAYER_LAYOUT HVGetBayerType(UINT index);
//	void OnSnapShot(UINT index);
//	void OnSnapContinue(UINT index);
//	void OnStopSnap(UINT index);
//	void OnDrawImage(UINT index);
//	//--------------------------halcon 图像处理
//	HTuple  Row0, Column0, Phi0, Length01, Length02, Row1, Column1;//------------测量用的变量
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
//	int nWndWidth ;//窗口宽度
//	int nWndHeight;//窗口高度
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
//	double calc0_x,calc0_y,calc1_x,calc1_y;//标定相机1像素尺寸
//	//---------------新增校正补偿
//	long calc_posx[3];//移动相机yong
//	long calc_posy[3];
//	void calc_mark_pos();
//	double stepx[2] ;
//	double stepy[2] ;//相机距虚拟中心的距离
//	double  buchang_angle;//补偿角度
//	long  buchangposx[2];//补偿位置
//	long  buchangposy[2];
//	int   shuttertime[2],gain[2];
//	double Y_angle[2];
//	//--------------------------------------创建模板函数
//	bool creat_model(UINT index);
//	bool read_model();
//	bool find_model(UINT index,double* row,double* column);
//	HTuple ModelID[CAMERA_NUMBER];
//	void save_image();
//	void setcamera(int index);
//	double cam_row[2];
//	double cam_column[2];
//	bool isgetcir;
//	//---------------------测量参数
//	int celiang_width[2];
//	int celiang_height[2];
//	int area[2];
//	int ra[2];
//	int rb[2];
//	float radius;//边缘膨胀半径
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

	/// 构造函数 
	CStopWatch()
	{ 
		Start(); 
	} 

	/// 开始计时
	void Start() 
	{ 
		QueryPerformanceCounter(&m_StartTime);
	} 

	/// 停止计时,ms
	double Stop() 
	{
		QueryPerformanceCounter(&m_StopTime);
		double theElapsedTime = ElapsedTime();

		m_StartTime = m_StopTime; 
		return theElapsedTime;
	} 

	/// 获取时间差 
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
	LARGE_INTEGER m_StartTime;   ///< 开始时间
	LARGE_INTEGER m_StopTime;    ///< 停止时间 
};
///相机参数结构体
typedef struct CAMER_INFO
{
	BITMAPINFO					*pBmpInfo;		  ///< BITMAPINFO 结构指针，显示图像时使用
	BYTE						*pImageBuffer;	  ///< 指向经过处理后的图像数据缓冲区
	BYTE                        *pRawBuffer;      ///< 指向原始RAW图缓冲区
	BYTE                        *disp_char;
	char						chBmpBuf[2048];	  ///< BIMTAPINFO 存储缓冲区，m_pBmpInfo即指向此缓冲区	
	int64_t                     nPayLoadSise;     ///< 图像块大小
	int64_t					    nImageWidth;	  ///< 图像宽度
	int64_t					    nImageHeight;	  ///< 图像高度	
	int64_t					    nBayerLayout;	  ///< Bayer排布格式
	bool						bIsColorFilter;	  ///< 判断是否为彩色相机
	BOOL						bIsOpen;		  ///< 相机已打开标志
	BOOL						bIsSnap;		  ///< 相机正在连续采集标志
	float						fFps;			  ///< 帧率
}CAMER_INFO;
#define  CAMERA_NUMBER 2
#define  GX_VERIFY(emStatus) \
	if(emStatus != GX_STATUS_SUCCESS) \
{\
	ShowErrorString(emStatus); \
	return emStatus;\
}  ///< 错误提示函数宏定义
#define  GX_VVERIFY(emStatus) \
	if(emStatus != GX_STATUS_SUCCESS) \
{\
	ShowErrorString(emStatus); \
	return ;\
}  ///< 错误提示函数宏定义
class CCam
{
public:
	CCam(void);
	virtual ~CCam(void);


	// Operations
public:
	//打开指定SN相机
	GX_STATUS Open_camera(char* sn,int camera_index);
	//设置相机
	GX_STATUS Setcamera(int index);
	///给相机注册相应的回调，目前最多支持4相机
	void RegisterCallback(int nCamID);

	///错误信息提示
	void ShowErrorString(GX_STATUS emErrorStatus);

	///设置设备的数据位深为8
	GX_STATUS SetPixelFormat8bit(GX_DEV_HANDLE hDevice);

	 GX_STATUS OnCONSnap(int index);//开始连续拍照
	 GX_STATUS OnStopCONSnap(int index);//停止连续拍照
	 GX_STATUS OnCloseDevice(int index);//关闭相机
	 GX_STATUS OnSendSoftCommand(int index);//拍一张照片


	///0号相机回调
	static void __stdcall OnFrameCallbackFun1(GX_FRAME_CALLBACK_PARAM* pFrame);

	///1号相机回调
	static void __stdcall OnFrameCallbackFun2(GX_FRAME_CALLBACK_PARAM* pFrame);

	GX_DEV_HANDLE	    m_hDevices[CAMERA_NUMBER];			///< 设备句柄指针
	CAMER_INFO	  	    m_pstCam[CAMERA_NUMBER];			///< 相机数据结构体		
	int				    m_nOperateID[CAMERA_NUMBER];		///< 操作设备ID
	uint32_t		    m_nCamNum;			///< 相机数目
	BOOL			    m_bViewID;			///< 是否显示相机编号
	int*		 	    m_npfpsCont;		///< 帧率计数
	GX_DEVICE_BASE_INFO *m_pBaseinfo[CAMERA_NUMBER]; 	    ///< 设备信息结构体

	// 图像显示资源定义
	CWnd                *m_pWnd[CAMERA_NUMBER];       ///< 切分窗口指针数组
	HDC                  m_hDC[CAMERA_NUMBER];         ///< 切分窗口DC数组 
	BYTE                *m_pImageBuffer[CAMERA_NUMBER];		///< Bayer转换后缓冲区


	bool initcam(UINT index);
	///// 采集回调函数，用户也可以定义为全局函数，如果作为类的成员函数，必须为静态成员函数。
	//static int CALLBACK SnapThreadCallback(HV_SNAP_INFO *pInfo); //0
	//static int CALLBACK SnapThreadCallback1(HV_SNAP_INFO *pInfo); //1
	///// 设置曝光时间
	//HVSTATUS SetExposureTime(int nWindWidth,
	//	long lTintUpper,
	//	long lTintLower,
	//	long HBlanking,
	//	HV_SNAP_SPEED SnapSpeed,
	//	HV_RESOLUTION Resolution,UINT index);
	///// 获取状态码
	//HVSTATUS GetLastStatus(UINT index);
	///// 获取bayer格式
	//HV_BAYER_LAYOUT HVGetBayerType(UINT index);
	//void OnSnapShot(UINT index);
	//void OnSnapContinue(UINT index);
	//void OnStopSnap(UINT index);
	//void OnDrawImage(UINT index);
	//--------------------------halcon 图像处理
	HTuple  Row0, Column0, Phi0, Length01, Length02, Row1, Column1;//------------测量用的变量
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
	int nWndWidth ;//窗口宽度
	int nWndHeight;//窗口高度
	int Width,Height;
	void save_image(UINT index);
	void measure_image(UINT index);

	void disp_message (Halcon::HTuple WindowHandle, Halcon::HTuple String, Halcon::HTuple CoordSystem, 
		Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Color, Halcon::HTuple Box);
	bool get_circle(UINT Image_dex ,double* result_row,double* result_column);

	double get_angle(double row1,double column1,double row2,double column2);
	void  saveini();
	void  readini();
	double calc0_x,calc0_y,calc1_x,calc1_y;//标定相机1像素尺寸
	//---------------新增校正补偿
	long calc_posx[3];//移动相机yong
	long calc_posy[3];
	void calc_mark_pos();
	double stepx[2] ;
	double stepy[2] ;//相机距虚拟中心的距离
	double  buchang_angle;//补偿角度
	long  buchangposx[2];//补偿位置
	long  buchangposy[2];
	int   shuttertime[2],gain[2];
	double Y_angle[2];
	//--------------------------------------创建模板函数
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
	//---------------------测量参数
	int celiang_width[2];
	int celiang_height[2];
	int area[2];
	int ra[2];
	int rb[2];
	float radius;//边缘膨胀半径
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
	double sunny_angle;//弧度
	long print_camerax[4];//喷头打印中心到相机位置；
	long print_cameray[4];
	long print_cameraz[4];

	long Print_z;//打印高度；

	long calc_print_camerax[4];//根据测量结果算出来的位置；
	long calc_print_cameray[4];
	long calc_print_cameraz[4];
    

	bool is_save_img;

	//-------------------新增定位算法用于常州日升
	bool czrs_measure();
};
#endif // DAHENG_MER
extern CCam m_Cam;