
#pragma once
#include "Motor.h"
//---------输入点
//#define	P0	m_Motor.ReadPort(false,true,0,0)
//#define	P1	m_Motor.ReadPort(false,true,0,1)
//#define	P2	m_Motor.ReadPort(false,true,0,2)
//#define	P3	m_Motor.ReadPort(false,true,0,3)
//#define	P4	m_Motor.ReadPort(false,true,0,4)
//#define	P5	m_Motor.ReadPort(false,true,0,5)
//#define	P6	m_Motor.ReadPort(false,true,0,6)
//#define	P7	m_Motor.ReadPort(false,true,0,7)
//#define	P8	m_Motor.ReadPort(false,true,0,8)
//#define	P9	m_Motor.ReadPort(false,true,0,9)
//#define	P10	m_Motor.ReadPort(false,true,0,10)
//#define	P11	m_Motor.ReadPort(false,true,0,11)
//#define	P12	m_Motor.ReadPort(false,true,0,12)
//#define	P13	m_Motor.ReadPort(false,true,0,13)
//#define	P14	m_Motor.ReadPort(false,true,0,14)
//#define	P15	m_Motor.ReadPort(false,true,0,15)
//#define	P16	m_Motor.ReadPort(false,true,0,16)
//#define	P17	m_Motor.ReadPort(false,true,0,17)
//#define	P18	m_Motor.ReadPort(false,true,0,18)
//#define	P19	m_Motor.ReadPort(false,true,0,19)
//#define	P20	m_Motor.ReadPort(false,true,0,20)
//#define	P21	m_Motor.ReadPort(false,true,0,21)
//#define	P22	m_Motor.ReadPort(false,true,0,22)
//#define	P23	m_Motor.ReadPort(false,true,0,23)
//
//#define	P100	m_Motor.ReadPort(false,true,1,0)
//#define	P101	m_Motor.ReadPort(false,true,1,1)
//#define	P102	m_Motor.ReadPort(false,true,1,2)
//#define	P103	m_Motor.ReadPort(false,true,1,3)
//#define	P104	m_Motor.ReadPort(false,true,1,4)
//#define	P105	m_Motor.ReadPort(false,true,1,5)
//#define	P106	m_Motor.ReadPort(false,true,1,6)
//#define	P107	m_Motor.ReadPort(false,true,1,7)
//#define	P108	m_Motor.ReadPort(false,true,1,8)
//#define	P109	m_Motor.ReadPort(false,true,1,9)
//#define	P110	m_Motor.ReadPort(false,true,1,10)
//#define	P111	m_Motor.ReadPort(false,true,1,11)
//#define	P112	m_Motor.ReadPort(false,true,1,12)
//#define	P113	m_Motor.ReadPort(false,true,1,13)
//#define	P114	m_Motor.ReadPort(false,true,1,14)
//#define	P115	m_Motor.ReadPort(false,true,1,15)
//#define	P116	m_Motor.ReadPort(false,true,1,16)
//#define	P117	m_Motor.ReadPort(false,true,1,17)
//#define	P118	m_Motor.ReadPort(false,true,1,18)
//#define	P119	m_Motor.ReadPort(false,true,1,19)
//#define	P120	m_Motor.ReadPort(false,true,1,20)
//#define	P121	m_Motor.ReadPort(false,true,1,21)
//#define	P122	m_Motor.ReadPort(false,true,1,22)
//#define	P123	m_Motor.ReadPort(false,true,1,23)

#define	P0	0
#define	P1	1
#define	P2	2
#define	P3	3
#define	P4	4
#define	P5	5
#define	P6	6
#define	P7	7
#define	P8	8
#define	P9	9
#define	P10	10
#define	P11	11
#define	P12	12
#define	P13	13
#define	P14	14
#define	P15	15
#define	P16	16
#define	P17	17
#define	P18	18
#define	P19	19
#define	P20	20
#define	P21	21
#define	P22	22
#define	P23	23





//----------------------输出点
#define M0	0
#define	M1	1
#define	M2	2
#define	M3	3
#define	M4	4
#define	M5	5
#define	M6	6
#define	M7	7
#define	M8	8
#define	M9	9
#define	M10	10
#define	M11	11
#define	M12	12
#define	M13	13
#define	M14	14
#define	M15	15
#define	M16	16
#define	M17	17
#define	M18	18
#define	M19	19
#define	M20	20
#define	M21	21
#define	M22	22
#define	M23	23

#define Alarm_Time 10
#define MOTOR_NUM  32
// CLogic

class CLogic : public CWnd
{
	DECLARE_DYNAMIC(CLogic)

public:
	CLogic();
	virtual ~CLogic();
protected:
	DECLARE_MESSAGE_MAP()


public:
	bool 	T0	;
	bool 	T1	;
	bool 	T2	;
	bool 	T3	;
	bool 	T4	;
	bool 	T5	;
	bool 	T6	;
	bool 	T7	;
	bool 	T8	;
	bool 	T9	;
	bool 	T10	;
	bool 	T11	;
	bool 	T12	;
	bool 	T13	;
	bool 	T14	;
	bool 	T15	;
	bool 	T16	;
	bool 	T17	;
	bool 	T18	;
	bool 	T19	;
	bool 	T20	;
	bool 	T21	;
	bool 	T22	;
	bool 	T23	;
	bool 	T24	;
	bool 	T25	;
	bool 	T26	;
	bool 	T27	;
	bool 	T28	;
	bool 	T29	;
	bool 	T30	;
	bool 	T31	;
	bool 	T32	;
	bool 	T33	;
	bool 	T34	;
	bool 	T35	;
	bool 	T36	;
	bool 	T37	;
	bool 	T38	;
	bool 	T39	;
	bool 	T40	;
	bool 	T41	;
	bool 	T42	;
	bool 	T43	;
	bool 	T44	;
	bool 	T45	;
	bool 	T46	;
	bool 	T47	;
	bool 	T48	;
	bool 	T49	;
	//------------------------报警标志信号
	bool 	A0	;
	bool 	A1	;
	bool 	A2	;
	bool 	A3	;
	bool 	A4	;
	bool 	A5	;
	bool 	A6	;
	bool 	A7	;
	bool 	A8	;
	bool 	A9	;
	bool 	A10	;
	bool 	A11	;
	bool 	A12	;
	bool 	A13	;
	bool 	A14	;
	bool 	A15	;
	bool 	A16	;
	bool 	A17	;
	bool 	A18	;
	bool 	A19	;
	bool 	A20	;
	bool 	A21	;
	bool 	A22	;
	bool 	A23	;
	bool 	A24	;
	bool 	A25	;
	bool 	A26	;
	bool 	A27	;
	bool 	A28	;
	bool 	A29	;
	bool 	A30	;
	bool 	A31	;
	bool 	A32	;
	bool 	A33	;
	bool 	A34	;
	bool 	A35	;
	bool 	A36	;
	bool 	A37	;
	bool 	A38	;
	bool 	A39	;
	bool 	A40	;
	bool 	A41	;
	bool 	A42	;
	bool 	A43	;
	bool 	A44	;
	bool 	A45	;
	bool 	A46	;
	bool 	A47	;
	bool 	A48	;
	bool 	A49	;
public:
	bool start,stop,reset,alarm,close,SVON[MOTOR_NUM]
	,Cam_measure_alarm[2],server_on[MOTOR_NUM];
	bool comein,goout;//来料信号 出料信号
	bool isCameraReady;
	bool isPaibianReady;
	bool tingzhi_xiaoliao;


	static UINT Check_Alarm(LPVOID param);
	bool Ld(UINT CardID,UINT IO);
	bool LdN(UINT CardID,UINT IO);
	void Set(UINT CardID,UINT IO);
	void Reset(UINT CardID,UINT IO);
	void T(UINT delay_val);
	void ResetT(bool t_val);
    bool readout(UINT CardID,UINT IO);
	/*in2 原点*/
	bool m_alarm(UINT CardID1,UINT out1,UINT CardID2,UINT in2,UINT CardID3,UINT in3);
	bool sp_alarm(UINT CardID1,UINT out1,UINT CardID2,UINT in2 );

	bool firstAshangliaoOK,firstBshangliaoOK,secondAshangliaoOK,secondBshangliaoOK;
	
	I32 H0;

	
	bool go_home_stop;
};
extern CMotor m_Motor;
extern CLogic m_logic;

