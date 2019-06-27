#pragma once
#include <math.h>
#include "Cam.h"
using namespace std;
/*math.h 
1 ���Ǻ���
double sin (double);
double cos (double);
double tan (double);
2 �����Ǻ���
double asin (double); �������[-PI/2, PI/2]
double acos (double); �������[0, PI]
double atan (double); ������(��ֵ), �������[-PI/2, PI/2]
double atan2 (double, double); ������(��Բֵ), �������[-PI/2, PI/2]
3 ˫�����Ǻ���
double sinh (double);
double cosh (double);
double tanh (double);
4 ָ�������
double exp (double);
double pow (double, double);
double sqrt (double);
double log (double); ��eΪ�׵Ķ���
double log10 (double);c++����Ȼ����������log(N)   ��10Ϊ�ף�log10(N)��û����2Ϊ�׵ĺ������ǿ����û��׹�ʽ�� ����log2(N)=log10(N)/log10(2)
5 ȡ��
	double ceil (double); ȡ����
	double floor (double); ȡ����
6 ����ֵ
double fabs (double);
7 ��׼��������
	double frexp (double f, int *p); ��׼��������, f = x * 2^p, ��֪f��x, p ( x����[0.5, 1] )
	double ldexp (double x, int p); ��frexp�෴, ��֪x, p��f
	8 ȡ����ȡ��
	double modf (double, double*); ����������������ͨ��ָ��ش�, ����С������
	double fmod (double, double); �������������������
source: ��C & C++ Code Capsules��
		9 ƽ����
		sqrt
*/
class Cmath
{
public:
	Cmath(void);
	virtual ~Cmath(void);
public:
	double getangle(double row0,double column0,double row1,double column1,double x,double y);/*row0~column1 mark �����꣬X,Y�������������λ��*/
	void   XYYPos(double angle,long* posx,long* posy1,long* posy2);
	double  angle(double a);//����ת�Ƕ�
	double  ang(double a);//�Ƕ�ת����
	void  mov_hpos(double row0,double column0,double row1,double column1,double* posx,double* posy1,double* posy2);
	/*����������С����
	P2
	| \
	|  \
	|   \
	P0---P1
	*/	
	void cal_dilation(double x0,double y0,double x1,double y1,double x2,double y2,double x,double y);
public:
	double x_dilation;
	double y_dilation;
	/*����������ת��Ϊ����ϵ����*/
	void changePOS(int cameraNUM,int markNUM,double motorx,double motory,double row,double column,double *x,double *y);

	void get_x0_x1_x2_POS(int id,double angle,long &x1,long &x2,long &y);//����
    double xxy_angle[4];
};

extern Cmath m_math;