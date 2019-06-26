#include "StdAfx.h"
#include "Cmath.h"


Cmath::Cmath(void)
{
	 x_dilation = 0;
	 y_dilation = 0;
}


Cmath::~Cmath(void)
{
}
double Cmath::getangle(double row0,double column0,double row1,double column1,double x,double y)
{
	//x= 35,y = 38
	int width  = 2592/2;
	int height = 1944/2;
	double x0,y0,x1,y1;
	x0 = 0;//左上角坐标
	y0 = 0;
	x1 = 0;//右上角坐标
	y1 = 0;
	x0 = (column0-width)*m_Cam.calc0_x;
	y0 = (row0 - height)*m_Cam.calc0_y;
	x1 = (column1-width)*m_Cam.calc1_x;
	y1 = (row1 - height)*m_Cam.calc1_y;
	//x0 = (column0)*m_Cam.calc0_x;
	//y0 = (row0 )*m_Cam.calc0_y;
	//x1 = (column1)*m_Cam.calc1_x;
	//y1 = (row1)*m_Cam.calc1_y;
	double a =0;
	double b =0;
	double angle =0;
	if (1)//m_gbr.mark3 ==0)
	{
		 a = x-x0+x1;
		 b = y-y0+y1;
		 angle = atan(b/a)-atan(y/x);
	}
	else
	{
		a = x-x0+x1;
		b = y+y0-y1;
		angle = atan(a/b)-atan(x/y);
	}
//	double a = 
	//double a1 = atan(b/a);
	//double a2 = atan(y/x);
	
	//double angle = atan(y/x)-atan(b/a);
	//angle = (180/3.1415926)*angle;
	//逆时针减 顺时针加
	//double m_a =Cmath::angle(m_Cam.buchang_angle);
	return angle+(m_Cam.buchang_angle);
}
double  Cmath::angle(double a)
{
	return (180/3.1415926)*a;
}
double  Cmath::ang(double a)//角度转弧度
{
	return (a*3.1415926/180);
}
void   Cmath::XYYPos(double angle,long* posx,long* posy1,long* posy2)
{
	int b = 600;//mm
	double x1 = 0;
	double x2 = 0;
	double pos1,pos2,pos0;
	pos1 = 0;
	pos2 = 0;
   //if (angle>0)//逆时针旋转Y1-，Y2+,X-
   //{
	  // x = sin(angle)*b/2;
	  // pos1 =0-x;
	  // pos2 = x;
   //}
   //else
   //{
	  // x = sin(abs(angle))*b;
	  // pos2 =0-x;
	  // pos1 = x;
   //}
   //*posy1 = (int)(pos1/4*10000);
   //*posy2 = (int)(pos2/4*10000);
	if(angle>0)////逆时针旋转Y1-，Y2+,X-
	{
	   x2 = (sqrtf(720000)*sin(angle/2)*cos((3.1415926-angle)/2-ang((double)45)));
	   x1 = (sqrtf(720000)*sin(angle/2)*cos(ang(45)+angle/2));
	   pos1 =0-x1;
	   pos2 = x2;
	   pos0 = pos1;
	}
	else
	{
		//angle = angle-ang(0.3);
		angle = abs(angle);
		x2= (sqrtf(720000)*sin(angle/2)*sin((3.1415926-angle)/2-ang((double)45)));
		x1 = (sqrtf(720000)*sin(angle/2)*sin(ang(45)+angle/2));
	    pos2 =0-x2;
	    pos1 = x1;
		pos0 = pos1;
	}
	*posy1 = (int)(pos1/4*10000);
    *posy2 = (int)(pos2/4*10000);
	*posx =  (int)(pos0/4*10000);
}
void  Cmath::mov_hpos(double row0,double column0,double row1,double column1
	,double* posx,double* posy1,double* posy2)
{
	int width  = 2592/2;
	int height = 1944/2;
	double x0,y0,x1,y1;
	x0 = 0;//左上角坐标
	y0 = 0;
	x1 = 0;//右上角坐标
	y1 = 0;
	x0 = (column0-width)*m_Cam.calc0_x;
	y0 = (row0 - height)*m_Cam.calc0_y;
	x1 = (column1-width)*m_Cam.calc1_x;
	y1 = (row1 - height)*m_Cam.calc1_y;
	*posx = ((x0+x1)/2);
	*posy1 = ((y0+y1)/2);
	*posy2 = ((y1+y0)/2);
}
	/*
	P2
	| \
	|  \
	|   \
	P0---P1
	*/	
void Cmath::cal_dilation(double x0,double y0,double x1,double y1,double x2,double y2,double x,double y)
{
	double realx = sqrtf(pow(abs(x1-x0),2)+pow(abs(y1-y0),2));
	double realy = sqrtf(pow(abs(x2-x0),2)+pow(abs(y2-y0),2));
	x_dilation = realx/x;
	y_dilation = realy/y;
}
void Cmath::changePOS(int cameraNUM,int markNUM,double motorx,double motory,double row,double column,double *x,double *y)
{
	int width  = 2592/2;
	int height = 1944/2;
	double xpiexs =column;
	double ypiexs = row;
	if (cameraNUM ==0 &&markNUM ==0)//转换第一个坐标点
	{
		*x=(xpiexs-width)*m_Cam.calc0_x+motorx;
		*y =(ypiexs-height)*m_Cam.calc0_y+motory;
	}
	if (cameraNUM ==1 &&markNUM ==1)//转换第二个坐标点
	{
		*x=m_Cam.stepx[0]+m_Cam.stepx[1]-((xpiexs-width)*m_Cam.calc0_x+motorx);
		*y =m_Cam.stepy[0]+m_Cam.stepy[1]-((ypiexs-height)*m_Cam.calc0_y+motory);
	}
	if (cameraNUM ==0&&markNUM ==2)//转换第三个坐标（相机0）
	{
		*x=(xpiexs-width)*m_Cam.calc0_x+motorx;
		*y =(ypiexs-height)*m_Cam.calc0_y+motory;
	}
	if (cameraNUM ==1&&markNUM ==2)//转换第三个坐标（相机1）
	{
		*x=m_Cam.stepx[0]+m_Cam.stepx[1]-((xpiexs-width)*m_Cam.calc0_x+motorx);
		*y =m_Cam.stepy[0]+m_Cam.stepy[1]-((ypiexs-height)*m_Cam.calc0_y+motory);
	}
}
void Cmath::get_x0_x1_x2_POS(int id,double angle,long &x1,long &x2,long &y)
{
	double R = 65*sqrt((float)2);
	double angle_old = xxy_angle[id];
	double ox1 = ang(135);
	double ox2 = ang(315);
	double oy  = ang(225);
	x1 = (long)((double)(R*cos(angle+angle_old+ox1)-R*cos(ox1+angle_old))*1000);
	x2 = (long)((double)(R*cos(ox2+angle_old)-R*cos(angle+angle_old+ox2))*1000);//(long)((double)(R*cos(angle+angle_old+ox2)-R*cos(ox2+angle_old))*1000);
	y  = (long)((double)(R*sin(angle_old+angle+oy)-R*sin(oy+angle_old))*1000);
	xxy_angle[id] = angle+angle_old;
}
Cmath m_math;