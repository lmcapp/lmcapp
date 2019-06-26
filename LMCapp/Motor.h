#pragma once
//Adlink head file////////
#include "APS168.h"
#include "ErrorCodeDef.h"
#include "APS_define.h"
#include "type_def.h"
//////////////////////////
// Util7230Dlg.h : header file
//
#include "Dask64.h"


#define PAIBAINHOME0 3600
#define PAIBAINHOME1 3600
#define PAIBAINHOME2 5500
#define PAIBAINHOME3 5500

#define 	MOTOR0	0
#define 	MOTOR1	1
#define 	MOTOR2	2
#define 	MOTOR3	3
#define 	MOTOR4	4
#define 	MOTOR5	5
#define 	MOTOR6	6
#define 	MOTOR7	7
#define 	MOTOR8	8
#define 	MOTOR9	9
#define 	MOTOR10	10
#define 	MOTOR11	11
#define 	MOTOR12	12
#define 	MOTOR13	13
#define 	MOTOR14	14
#define 	MOTOR15	15
#define 	MOTOR16	16
#define 	MOTOR17	17
#define 	MOTOR18	18
#define 	MOTOR19	19
#define 	MOTOR20	20
#define 	MOTOR21	21
#define 	MOTOR22	22
#define 	MOTOR23	23
#define 	MOTOR24	24
#define 	MOTOR25	25
#define 	MOTOR26	26
#define 	MOTOR27	27
#define 	MOTOR28	28
#define 	MOTOR29	29
#define 	MOTOR30	30
#define 	MOTOR31	31


// CMotor


#define Motor_Num 32
#define Card_NUM  4

class CMotor : public CWnd
{
	DECLARE_DYNAMIC(CMotor)

public:
	CMotor();
	virtual ~CMotor();
	
	////////////////////////////////////////////////
	I32  CurrentAxisPos[16];//获取当前位置


	void savepos();//存储信息文件
	void loadpos();

	I32 DI_Data[Card_NUM],DO_Data[Card_NUM];				//运动板卡IO口0

	U32 DI_Data2,DO_Data2;									//运动板卡扩展IO口2

	bool Initial();//初始化板卡
	bool Close();//关闭板卡


	void WritePort(bool isextent,I32 Car_ID,I32 port,bool status);//写IO状态
	bool ReadPort(bool isextent,bool isin, I32 Car_ID, I32 port);//isin ==true 读取输入状态
	void WritePort_mul(bool isextent,I32 Car_ID,I32 port0,I32 port1,I32 port2,bool status);//写IO状态
	void WritePort_4(bool isextent,I32 Car_ID,I32 port0,I32 port1,I32 port2,I32 port3,bool status);//写IO状态
	void WritePort_2(bool isextent,I32 Car_ID,I32 port0,I32 port1,bool status);//写IO状态

	bool Go_home(I32 Axis_ID);

	void absolute_move(I32 Axis_ID,I32 Pos);
	void relative_move(I32 Axis_ID,I32 Pos);
	void mul_real_move(I32 Axis_ID1,I32 Pos1,I32 Axis_ID2,I32 Pos2,I32 Axis_ID3,I32 Pos3);

	void velocity_move( I32 Axis_ID, I32 Max_Speed );
	void stop(I32 Axis_ID);


	void wait_move_done(I32 Axis_ID);
	bool is_move_done(I32 Axis_ID);
	void reset_pos(I32 Axis_ID);
	void JOG_ON(I32 Axis_ID,UINT dir);
	void JOG_OFF(I32 Axis_ID);
	//--------运动参数
	I32 go_homespeed[Motor_Num],move_maxspeed[Motor_Num],
		start_speed[Motor_Num],acc_speed[Motor_Num],jog_speed[Motor_Num];
	I32 PAIBIANPOS[4],DENGLIAOPOS[4],QULIAOPOS[4],DINGSHENGPOS[4],PAIZHAOPOS[4],
		PRINTPOS[4],FANGLIAOPOS[4],PRINTOKPOS[4],PUTDINGSHENGPOS[4];
	float headTemp[3];
	float headTempX;
	
	
	void set_speed_param();
	I32 X[2],Y[2];//相机位置
	void move_pt(I32 AXIS0,I32 AXIS1,I32 POS0,I32 POS1);
protected:
	DECLARE_MESSAGE_MAP()
};


