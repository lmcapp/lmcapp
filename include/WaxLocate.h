#pragma once
#define VISION_EXPORT __declspec(dllimport)
#include <vector>

enum Wax_Vision_ErrCode
{
	VISION_OK = 0,
	VISION_CROSS_LESS_THAN_ONE = -1,//检测到Mark小于一个
	VISION_CROSS_MORE_THAN_ONE = -2,//检测到Mark大于一个
	VISION_OPENCV_ERR = -3,//Opencv异常
	VISION_PRE_PROCESS_ERR = -4//图像预处理异常
};

struct WaxPoint2f
{
	float X;
	float Y;

	WaxPoint2f() { X = 0, Y = 0; }

	WaxPoint2f(float x, float y)
	{
		X = x;
		Y = y;
	}
};
enum ImageType
{
	ImgGray8 = 0,//单通道8bit黑白图像
	ImgRGB24 = 1,//三通道24bit RGB排布
	ImgARGB32 = 2//四通道32bit ARGB排布
};

struct ImageData
{
	int width;//图像的宽
	int height;//图像的高
	ImageType type;//图像的类型
	unsigned char *pbuff;//图像的数据
};

//描述：设定阈值范围
//lowValue：低阈值
//topValue：高阈值
VISION_EXPORT int SetThresholdValue(int lowValue, int topValue);

//描述：定位Mark，返回四个Mark的整体中心点和角度，以及四个Mark的单独中心点
//imgData：图像数据
//center：返回的整体中心点
//angle：返回的角度
//marks：返回的Mark的单独中心点
VISION_EXPORT int LocateMark(const ImageData& imgData, WaxPoint2f& center, double& angle, std::vector<WaxPoint2f>& marks);