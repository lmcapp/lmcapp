#pragma once
#define VISION_EXPORT __declspec(dllimport)
#include <vector>

enum Wax_Vision_ErrCode
{
	VISION_OK = 0,
	VISION_CROSS_LESS_THAN_ONE = -1,//��⵽MarkС��һ��
	VISION_CROSS_MORE_THAN_ONE = -2,//��⵽Mark����һ��
	VISION_OPENCV_ERR = -3,//Opencv�쳣
	VISION_PRE_PROCESS_ERR = -4//ͼ��Ԥ�����쳣
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
	ImgGray8 = 0,//��ͨ��8bit�ڰ�ͼ��
	ImgRGB24 = 1,//��ͨ��24bit RGB�Ų�
	ImgARGB32 = 2//��ͨ��32bit ARGB�Ų�
};

struct ImageData
{
	int width;//ͼ��Ŀ�
	int height;//ͼ��ĸ�
	ImageType type;//ͼ�������
	unsigned char *pbuff;//ͼ�������
};

//�������趨��ֵ��Χ
//lowValue������ֵ
//topValue������ֵ
VISION_EXPORT int SetThresholdValue(int lowValue, int topValue);

//��������λMark�������ĸ�Mark���������ĵ�ͽǶȣ��Լ��ĸ�Mark�ĵ������ĵ�
//imgData��ͼ������
//center�����ص��������ĵ�
//angle�����صĽǶ�
//marks�����ص�Mark�ĵ������ĵ�
VISION_EXPORT int LocateMark(const ImageData& imgData, WaxPoint2f& center, double& angle, std::vector<WaxPoint2f>& marks);