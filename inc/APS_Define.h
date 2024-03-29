#ifndef _APS_DEFINE_H
#define _APS_DEFINE_H

// Initial option
#define INIT_AUTO_CARD_ID       (0x00)   // (Bit 0) CardId assigned by system, Input parameter of APS_initial( cardId, "MODE" )
#define INIT_MANUAL_ID      		(0x01)   // (Bit 0) CardId manual by dip switch, Input parameter of APS_initial( cardId, "MODE" )
#define INIT_PARALLEL_FIXED 		(0x02)   // (Bit 1) Fixed axis indexing mode in Parallel type
#define INIT_SERIES_FIXED   		(0x04)   // (Bit 2) Fixed axis indexing mode in Series type
#define INIT_NOT_RESET_DO   		(0x08)   // (Bit 3) HSL Digital output not reset, (DO status will follow the slave status.)
#define INIT_PARAM_IGNORE       (0x00)   // (Bit 4-5) Load parameter method - ignore, keep current value
#define INIT_PARAM_LOAD_DEFAULT (0x10)   // (Bit 4-5) Load parameter method - load parameter as default value 
#define INIT_PARAM_LOAD_FLASH   (0x20)   // (Bit 4-5) Load parameter method - load parameter from flash memory
#define INIT_MNET_INTERRUPT 		(0x40)  // (Bit 6) Enable MNET interrupt mode. (Support motion interrupt for MotionNet series)

// Board parameter define (General)
#define PRB_EMG_LOGIC           (0x0)   // Board EMG logic
#define PRB_EMG_MODE            (0x101)
#define PRB_ECAT_MODE           (0x102)
#define PRB_ECAT_CYCLE          (0x103)
#define PRB_ECAT_RESTORE_OUTPUT (0x104)
#define PRB_DI_EMG_FILTER_ENABLE (0x105)
#define PRB_DI_EMG_FILTER_RANGE  (0x106)
#define PRB_PULSER_FILTER_RANGE  (0x107)
#define PRB_PULSER_FILTER_ENABLE (0x108)
#define PRB_ECAT_AUTO_RECOVERY   (0x109)
#define PRB_IO_ACCESS_SEL        (0x16)
#define PRB_ECAT_SYNC_MODE       (0x17)  // 0: DC(default); 1: FreeRun;




#define PRB_WDT0_VALUE      (0x10)  // Set / Get watch dog limit.
#define PRB_WDT0_COUNTER    (0x11)  // Reset Wdt / Get Wdt_Count_Value
#define PRB_WDT0_UNIT       (0x12)  // wdt_unit
#define PRB_WDT0_ACTION     (0x13)  // wdt_action

#define PRB_DO_LOGIC			(0x14)	//DO logic, 0: no invert; 1: invert
#define PRB_DI_LOGIC				(0x15)	//DI logic, 0: no invert; 1: invert

#define MHS_GET_SERVO_OFF_INFO	(0x16) //
#define MHS_RESET_SERVO_OFF_INFO	(0x0017)
#define MHS_GET_ALL_STATE	(0x0018)

#define PRB_TMR0_BASE       (0x20)  // Set TMR Value
#define PRB_TMR0_VALUE      (0x21)  // Get timer int count value

#define PRB_SYS_TMP_MONITOR (0x30)  // Get system temperature monitor data
#define PRB_CPU_TMP_MONITOR (0x31)  // Get CPU temperature monitor data
#define PRB_AUX_TMP_MONITOR (0x32)  // Get AUX temperature monitor data

#define PRB_UART_MULTIPLIER (0x40)  // Set UART Multiplier

#define PRB_PSR_MODE        (0x90)  // Config pulser mode
#define PRB_PSR_EA_LOGIC    (0x91)  // Set EA inverted
#define PRB_PSR_EB_LOGIC    (0x92)  // Set EB inverted

// Board parameter define (For PCI-8253/56)
#define PRB_DENOMINATOR     (0x80)  // Floating number denominator
//#define PRB_PSR_MODE      (0x90)  // Config pulser mode
#define PRB_PSR_ENABLE      (0x91)  // Enable/disable pulser mode
#define PRB_BOOT_SETTING    (0x100) // Load motion parameter method when DSP boot

#define PRB_PWM0_MAP_DO		(0x110)  // Enable & Map PWM0 to Do channels
#define PRB_PWM1_MAP_DO		(0x111)  // Enable & Map PWM1 to Do channels
#define PRB_PWM2_MAP_DO		(0x112)  // Enable & Map PWM2 to Do channels
#define PRB_PWM3_MAP_DO		(0x113)  // Enable & Map PWM3 to Do channels

// Board parameter define (For PCI-8392 SSCNET)
#define PRB_SSC_APPLICATION     (0x10000) // Reserved
#define PRB_SSC_CYCLE_TIME      (0x10000) // SSCNET cycle time selection(vaild befor start sscnet)
#define PRB_PARA_INIT_OPT       (0x00020) // Initial boot mode.

// Board parameter define (For DPAC)
#define PRB_DPAC_DISPLAY_MODE           (0x10001) //DPAC Display mode
#define PRB_DPAC_DI_MODE                (0x10002) //Set DI pin modes

#define PRB_DPAC_THERMAL_MONITOR_NO     (0x20001) //DPAC TEST
#define PRB_DPAC_THERMAL_MONITOR_VALUE  (0x20002) //DPAC TEST

// Axis parameter define (General)
#define PRA_EL_LOGIC        (0x00)  // EL logic
#define PRA_ORG_LOGIC       (0x01)  // ORG logic
#define PRA_EL_MODE         (0x02)  // EL stop mode
#define PRA_MDM_CONDI       (0x03)  // Motion done condition
#define PRA_EL_EXCHANGE     (0x04)  // PEL, MEL exchange enable

#define PRA_ALM_LOGIC       (0x04)  // ALM logic
#define PRA_ZSP_LOGIC       (0x05)  // ZSP logic [PCI-8253/56 only]
#define PRA_EZ_LOGIC        (0x06)  // EZ logic 
#define PRA_STP_DEC         (0x07)  // Stop deceleration
#define PRA_SD_DEC          (0x07)  // Stop deceleration
#define PRA_SPEL_EN         (0x08)  // SPEL Enable
#define PRA_SMEL_EN         (0x09)  // SMEL Enable
#define PRA_EFB_POS0        (0x0A)  // EFB position 0 [PCI-8253/56]
#define PRA_EFB_POS1        (0x0B)  // EFB position 1 [PCI-8253/56]
#define PRA_SPEL_POS        (0x0A)  // Soft-end-limit for positive end [PCI-8254/58]
#define PRA_SMEL_POS        (0x0B)  // Soft-end-limit for negative end [PCI-8254/58]
#define PRA_EFB_CONDI0      (0x0C)  // EFB position 0 condition
#define PRA_EFB_CONDI1      (0x0D)  // EFB position 1 condition
#define PRA_EFB_SRC0        (0x0E)  // EFB position 0 source
#define PRA_EFB_SRC1        (0x0F)  // EFB position 1 source
#define PRA_HOME_MODE       (0x10)  // home mode
#define PRA_HOME_DIR        (0x11)  // homing direction
#define PRA_HOME_CURVE      (0x12)  // homing curve parten(T or s curve)
#define PRA_HOME_ACC        (0x13)  // Acceleration deceleration rate
#define PRA_HOME_VS         (0x14)  // homing start velocity
#define PRA_HOME_VM         (0x15)  // homing max velocity
#define PRA_HOME_VA         (0x16)  // homing approach velocity [PCI-8253/56 only]
#define PRA_HOME_SHIFT	    (0x17)  // The shift from ORG [PCI-8254/58 only]
#define PRA_HOME_EZA        (0x18)  // EZ alignment enable
#define PRA_HOME_VO         (0x19)  // Homing leave ORG velocity
#define PRA_HOME_OFFSET     (0x1A)  // The escape pulse amounts(Leaving home by position)
#define PRA_HOME_POS		(0x1B)  // The position from ORG [PCI-8254/58 only]
#define PRA_HOME_TORQUE     (0x1C) //Torque-Limit value setting for home move

#define PRA_CURVE           (0x20)  // Move curve pattern
#define PRA_SF              (0x20)  // Move s-factor
#define PRA_ACC             (0x21)  // Move acceleration
#define PRA_DEC             (0x22)  // Move deceleration
#define PRA_VS              (0x23)  // Move start velocity
#define PRA_VM              (0x24)  // Move max velocity
#define PRA_VE              (0x25)  // Move end velocity
#define PRA_SACC			(0x26)  // S curve acceleration
#define PRA_SDEC	        (0x27)  // S curve deceleration
#define PRA_ACC_SR          (0x28)  // S curve ratio in acceleration( S curve with linear acceleration)
#define PRA_DEC_SR          (0x29)  // S curve ratio in deceleration( S curve with linear deceleration)

#define PRA_PRE_EVENT_DIST		(0x2A) //Pre-event distance
#define PRA_POST_EVENT_DIST		(0x2B) //Post-event distance
//following only for V2...
#define PRA_DIST            (0x30)  // Move distance
#define PRA_MAX_VELOCITY    (0x31)  // Maximum velocity
#define PRA_SCUR_PERCENTAGE (0x32)  // Scurve percentage
#define PRA_BLENDING_MODE   (0x33)  // Blending mode
#define PRA_STOP_MODE       (0x34)  // Stop mode
#define PRA_STOP_DELRATE    (0x35)  // Stop function deceleration rate
//================================================================================

#define PRA_PT_STOP_ENDO    (0x32)  // Disable do when point table stopping.
#define PRA_PT_STP_DO_EN    (0x32)  // Disable do when point table stopping.



#define PRA_PT_STOP_DO      (0x33)  // Set do value when point table stopping.
#define PRA_PT_STP_DO       (0x33)  // Set do value when point table stopping.
#define PRA_PWM_OFF         (0x34)  // Disable specified PWM output when ASTP input signal is active.
#define PRA_DO_OFF          (0x35)  // Set DO value when ASTP input signal is active.

#define PRA_JG_MODE         (0x40)  // Jog mode
#define PRA_JG_DIR          (0x41)  // Jog move direction
#define PRA_JG_CURVE        (0x42)  // Jog curve parten(T or s curve)
#define PRA_JG_SF           (0x42)  // Jog curve parten(T or s curve)
#define PRA_JG_ACC          (0x43)  // Jog move acceleration
#define PRA_JG_DEC          (0x44)  // Jog move deceleration
#define PRA_JG_VM           (0x45)  // Jog move max velocity
#define PRA_JG_STEP         (0x46)  // Jog offset (For step mode)
#define PRA_JG_OFFSET       (0x46)  // Jog offset (For step mode)
#define PRA_JG_DELAY        (0x47)  // Jog delay (For step mode)
#define PRA_JG_MAP_DI_EN    (0x48) // (I32) Enable Digital input map to jog command signal
#define PRA_JG_P_JOG_DI     (0x49) // (I32) Mapping configuration for positive jog and digital input.
#define PRA_JG_N_JOG_DI     (0x4A) // (I32) Mapping configuration for negative jog and digital input.
#define PRA_JG_JOG_DI       (0x4B) // (I32) Mapping configuration for jog and digital input.

#define PRA_MDN_DELAY       (0x50)  // NSTP delay setting
#define PRA_SINP_WDW        (0x51)  // Soft INP window setting
#define PRA_SINP_STBL       (0x52)  // Soft INP stable cycle
#define PRA_SINP_STBT       (0x52)  // Soft INP stable cycle
#define PRA_SERVO_LOGIC     (0x53) //  SERVO logic

#define PRA_GEAR_MASTER       (0x60)  // (I32) Select gearing master
#define PRA_GEAR_ENGAGE_RATE  (0x61)  // (F64) Gear engage rate
#define PRA_GEAR_RATIO        (0x62)  // (F64) Gear ratio
#define PRA_GANTRY_PROTECT_1  (0x63)  // (F64) E-gear gantry mode protection level 1
#define PRA_GANTRY_PROTECT_2  (0x64)  // (F64) E-gear gantry mode protection level 2
#define PRA_EGEAR_MASTER      (0x65) //Select gearing master: 0~63
#define PRA_EGEAR_SOURCE      (0x66) //Select gearing source // 0: command position deviation1: feedback position deviation

// Axis parameter define (For PCI-8253/56)
#define PRA_PLS_IPT_MODE    (0x80)  // Pulse input mode setting
#define PRA_PLS_OPT_MODE    (0x81)  // Pulse output mode setting
#define PRA_MAX_E_LIMIT     (0x82)  // Maximum encoder count limit
#define PRA_ENC_FILTER      (0x83)  // Encoder filter
#define PRA_ENCODER_FILTER  (0x83)  // Encoder filter
#define PRA_MOVE_RATIO      (0x88)  //Move ratio 
#define PRA_EGEAR						(0x84)  // E-Gear ratio
#define PRA_ENCODER_DIR     (0x85)  // Encoder direction
#define PRA_POS_UNIT_FACTOR (0x86)  // position unit factor setting


//#define __8258_PRA_EGEAR         (0x84) // 8253/6 use this para as unit factor, but 8258 use 0x86. 
#define PRA_KP_GAIN         (0x90)  // PID controller Kp gain
#define PRA_KI_GAIN         (0x91)  // PID controller Ki gain
#define PRA_KD_GAIN         (0x92)  // PID controller Kd gain
#define PRA_KFF_GAIN        (0x93)  // Velocity feedforward Kff gain
#define PRA_KVFF_GAIN       (0x93)  // Velocity feedforward Kff gain
#define PRA_KVGTY_GAIN      (0x94)  // Gantry controller Kvgty gain
#define PRA_KPGTY_GAIN      (0x95)  // Gantry controller Kpgty gain
#define PRA_IKP_GAIN        (0x96)  // PID controller Kp gain in torque mode
#define PRA_IKI_GAIN        (0x97)  // PID controller Ki gain in torque mode
#define PRA_IKD_GAIN        (0x98)  // PID controller Kd gain in torque mode
#define PRA_IKFF_GAIN       (0x99)  // Velocity feedforward Kff gain in torque mode
#define PRA_KAFF_GAIN       (0x9A)  // Acceleration feedforward Kaff gain
#define PRA_KP_SHIFT	 (0x9B) //Proportional control result shift 
#define PRA_KI_SHIFT 	(0x9C)         //Integral control result shift 
#define PRA_KD_SHIFT 	(0x9D)         // Derivative control result shift
#define PRA_KVFF_SHIFT 	(0x9E)       //Velocity feed-forward control result shift
#define PRA_KAFF_SHIFT 	(0x9F) //Acceleration feed-forward control result shift 
#define PRA_PID_SHIFT 	(0xA0) //PID control result shift


//following only for V2...
#define PRA_VOLTAGE_MAX     (0x9B)  // Maximum output limit
#define PRA_VOLTAGE_MIN     (0x9C)  // Minimum output limit
//================================================================================

#define PRA_M_INTERFACE     (0x100) // Motion interface

#define PRA_M_VOL_RANGE     (0x110) // Motor voltage input range
#define PRA_M_MAX_SPEED     (0x111) // Motor maximum speed
#define PRA_M_ENC_RES       (0x112) // Motor encoder resolution

#define PRA_V_OFFSET        (0x120) // Voltage offset
#define PRA_SERVO_V_BIAS    (0x120) // Voltage offset
#define PRA_DZ_LOW          (0x121) // Dead zone low side
#define PRA_DZ_UP           (0x122) // Dead zone up side
#define PRA_SAT_LIMIT       (0x123) // Voltage saturation output limit
#define PRA_SERVO_V_LIMIT   (0x123) // Voltage saturation output limit
#define PRA_ERR_C_LEVEL     (0x124) // Error counter check level
#define PRA_ERR_POS_LEVEL   (0x124) // Error counter check level
#define PRA_V_INVERSE       (0x125) // Output voltage inverse
#define PRA_SERVO_V_INVERSE (0x125) // Output voltage inverse
#define PRA_DZ_VAL          (0x126) // Dead zone output value
#define PRA_IW_MAX          (0x127) // Integral windup maximum value
#define PRA_IW_MIN          (0x128) // Integral windup minimum value
#define PRA_BKL_DIST        (0x129) // Backlash distance
#define PRA_BKL_CNSP        (0x12a) // Backlash consumption
#define PRA_INTEGRAL_LIMIT  (0x12B) // (I32) Integral limit
#define PRA_D_SAMPLE_TIME   (0x12C) // (I32) Derivative Sample Time

#define PRA_PSR_LINK        (0x130) // Connect pulser number
#define PRA_PSR_RATIO       (0X131) // Set pulser ratio

#define PRA_BIQUAD0_A1      (0x132) // (F64) Biquad filter0 coefficient A1
#define PRA_BIQUAD0_A2      (0x133) // (F64) Biquad filter0 coefficient A2
#define PRA_BIQUAD0_B0      (0x134) // (F64) Biquad filter0 coefficient B0
#define PRA_BIQUAD0_B1      (0x135) // (F64) Biquad filter0 coefficient B1
#define PRA_BIQUAD0_B2      (0x136) // (F64) Biquad filter0 coefficient B2
#define PRA_BIQUAD0_DIV     (0x137) // (F64) Biquad filter0 divider
#define PRA_BIQUAD1_A1      (0x138) // (F64) Biquad filter1 coefficient A1
#define PRA_BIQUAD1_A2      (0x139) // (F64) Biquad filter1 coefficient A2
#define PRA_BIQUAD1_B0      (0x13A) // (F64) Biquad filter1 coefficient B0
#define PRA_BIQUAD1_B1      (0x13B) // (F64) Biquad filter1 coefficient B1
#define PRA_BIQUAD1_B2      (0x13C) // (F64) Biquad filter1 coefficient B2
#define PRA_BIQUAD1_DIV    (0x13D) // (F64) Biquad filter1 divider
#define PRA_FRIC_GAIN		  (0x13E) // (F64) Friction voltage compensation


#define PRA_DA_TYPE         (0x140) // DAC output type
#define PRA_CONTROL_MODE    (0x141) // Closed loop control mode
// ADLINK internal use
#define PRA_CMD_Freq        (0x142) // (F64) Command Preshaping Frequency                    
#define PRA_CMD_Damp        (0x143) // (F64) Command Preshaping Damping                     
#define PRA_CMD_PSF         (0x144) // (F64) Command Preshaping Path Smooth Factor      
#define PRA_CMD_LPF2        (0x145) // (F64) Command Preshaping 2nd Order Low-Pass-Filter

// ADLINK internal use
#define PRA_USER_I32_1      (0x150) // (I32) For AMC data exchange
#define PRA_USER_I32_2      (0x151) // (I32) For AMC data exchange
#define PRA_USER_I32_3      (0x152) // (I32) For AMC data exchange
#define PRA_USER_I32_4      (0x153) // (I32) For AMC data exchange
#define PRA_USER_I32_5      (0x154) // (I32) For AMC data exchange
#define PRA_USER_F64_1      (0x155) // (F64) For AMC data exchange
#define PRA_USER_F64_2      (0x156) // (F64) For AMC data exchange
#define PRA_USER_F64_3      (0x157) // (F64) For AMC data exchange
#define PRA_USER_F64_4      (0x158) // (F64) For AMC data exchange
#define PRA_USER_F64_5      (0x159) // (F64) For AMC data exchange

//Pulser function
#define PRA_PSR_IPT_MODE		(0x160) // Pulser pulse input mode setting
#define PRA_PSR_IPT_LOGIC		(0x161) // Pulser pulse input logic
#define PRA_PSR_IPT_DIR			(0x162) // Pulser pulse input direction
#define PRA_PSR_RATIO_VALUE	(0x163) // reserved
#define PRA_PSR_PDV					(0x164) // Pulser ratio by PDV
#define PRA_PSR_PMG					(0x165) // Pulser ratio by PMG
#define PRA_PSR_HOME_TYPE	(0x166) // Pulser home type
#define 	PRA_PSR_HOME_SPD		(0x167) // Pulser home maximun speedlimit
#define PRA_PSR_ACC					(0x168) // reserved
#define PRA_PSR_JERK				(0x169) // reserved

// Axis parameter define (For PCI-8154/58)
// Input/Output Mode
#define PRA_PLS_IPT_LOGIC   (0x200) //Reverse pulse input counting
#define PRA_FEEDBACK_SRC    (0x201) //Select feedback conter

//IO Config
#define PRA_ALM_MODE        (0x210) //ALM Mode
#define PRA_INP_LOGIC       (0x211) //INP Logic
#define PRA_SD_EN           (0x212) //SD Enable -- Bit 8
#define PRA_SD_MODE         (0x213) //SD Mode
#define PRA_SD_LOGIC        (0x214) //SD Logic
#define PRA_SD_LATCH        (0x215) //SD Latch
#define PRA_ERC_MODE        (0x216) //ERC Mode
#define PRA_ERC_LOGIC       (0x217) //ERC Logic
#define PRA_ERC_LEN         (0x218) //ERC Pulse Width
#define PRA_RESET_COUNTER   (0x219) //Reset Counter When Home Move is Complete
#define PRA_PLS_IPT_FLT     (0x21B) //EA/EB Filter Enable
#define PRA_INP_MODE        (0x21C) //INP Mode
#define PRA_LTC_LOGIC       (0x21D) //LTC LOGIC
#define PRA_IO_FILTER       (0x21E) //+-EZ, SD, ORG, ALM, INP filter
#define PRA_COMPENSATION_PULSE  (0x221) //BACKLASH PULSE
#define PRA_COMPENSATION_MODE   (0x222) //BACKLASH MODE
#define PRA_LTC_SRC         (0x223) //LTC Source
#define PRA_LTC_DEST        (0x224) //LTC Destination
#define PRA_LTC_DATA        (0x225) //Get LTC DATA

#define PRA_VIBSUP_RT       (0x22B) // Vibration Reverse Time
#define PRA_VIBSUP_FT       (0x22C) // Vibration Forward Time
#define PRA_LTC_DATA_SPD       (0x22D) // Choose latch data for current speed or error position

#define PRA_GPDO_SEL        (0x230) //Select DO/CMP Output mode
#define PRA_GPDI_SEL        (0x231) //Select DO/CMP Output mode
#define PRA_GPDI_LOGIC      (0x232) //Set GPIO Input Logic
#define PRA_RDY_LOGIC       (0x233) //RDY Logic
#define PRA_DI_FILTER_WIDTH (0x234) //DI Input Tunable Filter Width 
#define PRA_DI_FILTER_EN    (0x235) //DI Input Tunable Filter Enable

//Fixed Speed
#define PRA_SPD_LIMIT       (0x240) // Set Fixed Speed
#define PRA_MAX_ACCDEC      (0x241) // Get max acceleration by fixed speed
#define PRA_MIN_ACCDEC      (0x242) // Get min acceleration by fixed speed
#define PRA_ENABLE_SPD      (0x243) // Disable/Enable Fixed Speed only for HSL-4XMO.

//Continuous Move
#define PRA_CONTI_MODE      (0x250) // Continuous Mode
#define PRA_CONTI_BUFF      (0x251) // Continuous Buffer

//Simultaneous Move
#define PRA_SYNC_STOP_MODE      (0x260) // Sync Mode

//Error compare
#define PRA_ECMP_EN		(0x280) // Error CMP Enable
#define PRA_ECMP_POS		(0x281) // Get CMP position
#define PRA_ECMP_SRC		(0x282) // Set CMP source
#define PRA_ECMP_ACTION		(0x283) // CMP Status
#define PRA_ECMP_STS	(0x284) //Error CMP logic
#define PRA_ERR_RESCOUNT	(0x285) // Reset Counter 3 (Error Counter)  
#define PRA_ERR_COUNTER	(0x290) // Counter 3(Error Counter) 

//General compare
#define PRA_GCMP_EN         (0x226) // CMP Enable
#define PRA_GCMP_POS        (0x227) // Get CMP position
#define PRA_GCMP_SRC        (0x228) // CMP source
#define PRA_GCMP_ACTION     (0x229) // CMP Action
#define PRA_GCMP_STS        (0x22A) // CMP Status

//Trigger compare
#define PRA_TCMP_EN			(0x270) // trigger CMP Enable
#define PRA_TCMP_POS		(0x271) // Get CMP position
#define PRA_TCMP_SRC		(0x272) // Set CMP source
#define PRA_TCMP_STS		(0x273) // CMP Status
#define PRA_TCMP_LOGIC	(0x274) // CMP logic
#define PRA_TCMP_ACTION	(0x275) // CMP Action

//PCS
#define PRA_PCS_EN			(0x2A0)	//PCS Enable
#define PRA_PCS_LOGIC		(0x2A1)	//PCS Logic


// PCI-8144 axis parameter define
#define PRA_CMD_CNT_EN      (0x10000)
#define PRA_MIO_SEN         (0x10001)
#define PRA_START_STA       (0x10002)
#define PRA_SPEED_CHN       (0x10003)
#define PRA_ORG_STP         (0x1A)

// Axis parameter define (For PCI-8392 SSCNET)
#define PRA_SSC_SERVO_PARAM_SRC     (0x10000) //Servo parameter source
#define PRA_SSC_SERVO_ABS_POS_OPT   (0x10001) //Absolute position system option
#define PRA_SSC_SERVO_ABS_CYC_CNT   (0x10002) //Absolute cycle counter of servo driver
#define PRA_SSC_SERVO_ABS_RES_CNT   (0x10003) //Absolute resolution counter of servo driver
#define PRA_SSC_TORQUE_LIMIT_P      (0x10004) //Torque limit positive (0.1%)
#define PRA_SSC_TORQUE_LIMIT_N      (0x10005) //Torque limit negative (0.1%)
#define PRA_SSC_TORQUE_CTRL         (0x10006) //Torque control
#define PRA_SSC_RESOLUTION          (0x10007) //resolution (E-gear)
#define PRA_SSC_GMR					(0x10008) //resolution (New E-gear)
#define PRA_SSC_GDR					(0x10009) //resolution (New E-gear)

// Sampling parameter define
#define SAMP_PA_RATE        (0x0) //Sampling rate
#define SAMP_PA_EDGE        (0x2) //Edge select
#define SAMP_PA_LEVEL       (0x3) //Level select
#define SAMP_PA_TRIGCH      (0x5) //Select trigger channel
//following only for V2
#define SAMP_PA_SEL         (0x6)
//================================================================================

#define SAMP_PA_SRC_CH0     (0x10) //Sample source of channel 0
#define SAMP_PA_SRC_CH1     (0x11) //Sample source of channel 1
#define SAMP_PA_SRC_CH2     (0x12) //Sample source of channel 2
#define SAMP_PA_SRC_CH3     (0x13) //Sample source of channel 3

// Sampling source
#define SAMP_AXIS_MASK      (0xF00)
#define SAMP_PARAM_MASK     (0xFF)
#define SAMP_COM_POS        (0x00) //command position
#define SAMP_FBK_POS        (0x01) //feedback position
#define SAMP_CMD_VEL        (0x02) //command velocity
#define SAMP_FBK_VEL        (0x03) //feedback velocity
#define SAMP_MIO            (0x04) //motion IO
#define SAMP_MSTS           (0x05) //motion status
#define SAMP_MSTS_ACC       (0x06) //motion status acc
#define SAMP_MSTS_MV        (0x07) //motion status at max velocity
#define SAMP_MSTS_DEC       (0x08) //motion status at dec
#define SAMP_MSTS_CSTP      (0x09) //motion status CSTP
#define SAMP_MSTS_MDN       (0x0A) //motion status MDN, the same with NSTP
#define SAMP_MIO_INP        (0x0B) //motion status INP
#define SAMP_MIO_ZERO       (0x0C) //motion status ZERO
#define SAMP_MIO_ORG        (0x0D) //motion status ORG

#define SAMP_CONTROL_VOL				(0x20)  // Control command voltage
#define SAMP_GTY_DEVIATION			(0x21) // Gantry deviation
#define SAMP_ENCODER_RAW			  (0x22) // Encoder raw data
#define SAMP_ERROR_COUNTER			(0x23) // Error counter data
#define SAMP_ERROR_POS					(SAMP_ERROR_COUNTER) //Error position [PCI-8254/58]
#define SAMP_PTBUFF_RUN_INDEX		(0x24) //Point table running index

//Only for PCI-8392
#define SAMP_SSC_MON_0      (0x10)  // SSCNET servo monitor ch0
#define SAMP_SSC_MON_1      (0x11)  // SSCNET servo monitor ch1
#define SAMP_SSC_MON_2      (0x12)  // SSCNET servo monitor ch2
#define SAMP_SSC_MON_3      (0x13)  // SSCNET servo monitor ch3

//Only for PCI-8254/8, AMP-204/8C
#define SAMP_COM_POS_F64						(0x10) // Command position
#define SAMP_FBK_POS_F64						(0x11) // Feedback position
#define SAMP_CMD_VEL_F64						(0x12) // Command velocity
#define SAMP_FBK_VEL_F64						(0x13) // Feedback velocity
#define SAMP_CONTROL_VOL_F64				(0x14) // Control command voltage
#define SAMP_ERR_POS_F64						(0x15) // Error position
#define SAMP_PWM_FREQUENCY_F64		  (0x18) // PWM frequency (Hz)
#define SAMP_PWM_DUTY_CYCLE_F64		  (0x19) // PWM duty cycle (%)
#define SAMP_PWM_WIDTH_F64					(0x1A) // PWM width (ns)
#define SAMP_VAO_COMP_VEL_F64			  (0x1B) // Composed velocity for Laser power control (pps)
#define SAMP_PTBUFF_COMP_VEL_F64		(0x1C) // Composed velocity of point table
#define SAMP_PTBUFF_COMP_ACC_F64		(0x1D) // Composed acceleration of point table

//FieldBus parameter define
#define PRF_COMMUNICATION_TYPE      (0x00)// FiledBus Communication Type(Full/half duplex)
#define PRF_TRANSFER_RATE           (0x01)// FiledBus Transfer Rate
#define PRF_HUB_NUMBER              (0x02)// FiledBus Hub Number
#define PRF_INITIAL_TYPE            (0x03)// FiledBus Initial Type(Clear/Reserve Do area)
#define PRF_CHKERRCNT_LAYER         (0x04)// Set the check error count layer.
#define PRF_RESEND_CNT	         (0x05)// Set resend counts

//Gantry parameter number define [Only for PCI-8392, PCI-8253/56]
#define GANTRY_MODE                 (0x0)
#define GENTRY_DEVIATION            (0x1)
#define GENTRY_DEVIATION_STP        (0x2)

// Filter parameter number define [Only for PCI-8253/56]
#define FTR_TYPE_ST0                    (0x00)  // Station 0 filter type
#define FTR_FC_ST0                      (0x01)  // Station 0 filter cutoff frequency
#define FTR_BW_ST0                      (0x02)  // Station 0 filter bandwidth
#define FTR_ENABLE_ST0                  (0x03)  // Station 0 filter enable/disable
#define FTR_TYPE_ST1                    (0x10)  // Station 1 filter type
#define FTR_FC_ST1                      (0x11)  // Station 1 filter cutoff frequency
#define FTR_BW_ST1                      (0x12)  // Station 1 filter bandwidth
#define FTR_ENABLE_ST1                  (0x13)  // Station 1 filter enable/disable

// Device name define
#define DEVICE_NAME_NULL            (0xFFFF)
#define DEVICE_NAME_PCI_8392        (0)
#define DEVICE_NAME_PCI_825X        (1)
#define DEVICE_NAME_PCI_8154        (2)
#define DEVICE_NAME_PCI_785X        (3)
#define DEVICE_NAME_PCI_8158        (4)
#define DEVICE_NAME_PCI_7856        (5)
#define DEVICE_NAME_ISA_DPAC1000    (6)
#define DEVICE_NAME_ISA_DPAC3000    (7)
#define DEVICE_NAME_PCI_8144        (8)
#define DEVICE_NAME_PCI_825458      (9)
#define DEVICE_NAME_PCI_8102        (10)
#define DEVICE_NAME_PCI_V8258       (11)
#define DEVICE_NAME_PCI_V8254       (12)
#define DEVICE_NAME_PCI_8158A       (13)
#define DEVICE_NAME_AMP_20408C      (14)
#define DEVICE_NAME_PCI_8353        (15)
#define DEVICE_NAME_PCI_8392F 	    (16)
#define DEVICE_NAME_PCI_C154 	    (17)
#define DEVICE_NAME_PCI_C154_PLUS   (18)
#define DEVICE_NAME_PCI_8353_RTX    (19)
#define DEVICE_NAME_PCIE_8338       (20)
#define DEVICE_NAME_PCIE_8154	    (21)
#define DEVICE_NAME_PCIE_8158	    (22)


///////////////////////////////////////////////
//   HSL Slave module definition
///////////////////////////////////////////////
#define SLAVE_NAME_UNKNOWN          (0x000)
#define SLAVE_NAME_HSL_DI32         (0x100)
#define SLAVE_NAME_HSL_DO32         (0x101)
#define SLAVE_NAME_HSL_DI16DO16     (0x102)
#define SLAVE_NAME_HSL_AO4          (0x103)
#define SLAVE_NAME_HSL_AI16AO2_VV   (0x104)
#define SLAVE_NAME_HSL_AI16AO2_AV   (0x105)
#define SLAVE_NAME_HSL_DI16UL       (0x106)
#define SLAVE_NAME_HSL_DI16RO8      (0x107)
#define SLAVE_NAME_HSL_4XMO         (0x108)
#define SLAVE_NAME_HSL_DI16_UCT     (0x109)
#define SLAVE_NAME_HSL_DO16_UCT     (0x10A)
#define SLAVE_NAME_HSL_DI8DO8       (0x10B)
#define SLAVE_NAME_HSL_DI56DO32_FCN     (0x10C)
///////////////////////////////////////////////
//   MNET Slave module definition
///////////////////////////////////////////////
#define SLAVE_NAME_MNET_1XMO        (0x200)
#define SLAVE_NAME_MNET_4XMO        (0x201)
#define SLAVE_NAME_MNET_4XMO_C      (0x202)



///////////////////////////////////////////////
//   PCIe-8338 Slave module definition
///////////////////////////////////////////////
#define SLAVE_ADLINK_ECAT_EPS_1132       (0x1132) //DI32
#define SLAVE_ADLINK_ECAT_EPS_2032       (0x2032) //DO32
#define SLAVE_ADLINK_ECAT_EPS_2132       (0x2132) //DO32
#define SLAVE_ADLINK_ECAT_EPS_3032       (0x3032) //AI32
#define SLAVE_ADLINK_ECAT_EPS_3216       (0x3216) //AI16
#define SLAVE_ADLINK_ECAT_EPS_3504       (0x3504) //AI04
#define SLAVE_ADLINK_ECAT_EPS_4008       (0x4008) //AO8
#define SLAVE_ADLINK_ECAT_EPS_2308       (0x2308) //DO8
#define SLAVE_ADLINK_ECAT_EPS_7002       (0x7002) //MO2

///////////////////////////////////////////////
//   PCIe-8338 EtherCAT master/slave status definition
///////////////////////////////////////////////
#define EC_STATE_NOT_RDY					(0x0000)
#define EC_STATE_RDY						(0x0001)
#define EC_STATE_BUS_SCAN					(0x0002)
#define EC_STATE_INIT						(0x0003)
#define EC_STATE_PREOP						(0x0004)
#define EC_STATE_SAFEOP						(0x0005)
#define EC_STATE_OP							(0x0006)


//Trigger parameter number define. [Only for DB-8150]
//////////////////////////////////////
#define TG_PWM0_PULSE_WIDTH    (0x00)
#define TG_PWM1_PULSE_WIDTH    (0x01)

#define TG_PWM0_MODE           (0x02)
#define TG_PWM1_MODE           (0x03)

#define TG_TIMER0_INTERVAL     (0x04)
#define TG_TIMER1_INTERVAL     (0x05)

#define TG_ENC0_CNT_DIR        (0x06)
#define TG_ENC1_CNT_DIR        (0x07)

#define TG_IPT0_MODE           (0x08)
#define TG_IPT1_MODE           (0x09)

#define TG_EZ0_CLEAR_EN        (0x0A)
#define TG_EZ1_CLEAR_EN        (0x0B)

#define TG_EZ0_CLEAR_LOGIC     (0x0C)
#define TG_EZ1_CLEAR_LOGIC     (0x0D)

#define TG_CNT0_SOURCE         (0x0E)
#define TG_CNT1_SOURCE         (0x0F)

#define TG_FTR0_EN		       (0x10)
#define TG_FTR1_EN		       (0x11)

#define TG_DI_LATCH0_EN        (0x12)
#define TG_DI_LATCH1_EN        (0x13)

#define TG_DI_LATCH0_EDGE      (0x14)
#define TG_DI_LATCH1_EDGE      (0x15)

#define TG_DI_LATCH0_VALUE     (0x16)
#define TG_DI_LATCH1_VALUE     (0x17)

#define TG_TRGOUT_MAP          (0x18)
#define TG_TRGOUT_LOGIC        (0x19)

#define TG_FIFO_LEVEL          (0x1A)

#define TG_PWM0_SOURCE         (0x1B)
#define TG_PWM1_SOURCE         (0x1C)
//////////////////////////////////////





//Trigger parameter number define. [Only for PCI-8253/56]
#define TG_LCMP0_SRC    (0x00)
#define TG_LCMP1_SRC    (0x01)
#define TG_TCMP0_SRC    (0x02)
#define TG_TCMP1_SRC    (0x03)
#define TG_LCMP0_EN     (0x04)
#define TG_LCMP1_EN     (0x05)
#define TG_TCMP0_EN     (0x06)
#define TG_TCMP1_EN     (0x07)
#define TG_TRG0_SRC     (0x10)
#define TG_TRG1_SRC     (0x11)
#define TG_TRG2_SRC     (0x12)
#define TG_TRG3_SRC     (0x13)
#define TG_TRG0_PWD     (0x14)
#define TG_TRG1_PWD     (0x15)
#define TG_TRG2_PWD     (0x16)
#define TG_TRG3_PWD     (0x17)
#define TG_TRG0_CFG     (0x18) //Also for HSL-4XMO
#define TG_TRG1_CFG     (0x19) //Also for HSL-4XMO
#define TG_TRG2_CFG     (0x1A) //Also for HSL-4XMO
#define TG_TRG3_CFG     (0x1B) //Also for HSL-4XMO

#define TMR_ITV         (0x20)
#define TMR_EN          (0x21)

//Trigger parameter number define. [Only for MNET-4XMO-C & HSL-4XMO]
#define TG_CMP0_SRC             (0x00)
#define TG_CMP1_SRC             (0x01)
#define TG_CMP2_SRC             (0x02)
#define TG_CMP3_SRC             (0x03)

#define TG_CMP0_EN              (0x04)
#define TG_CMP1_EN              (0x05)
#define TG_CMP2_EN              (0x06)
#define TG_CMP3_EN              (0x07)

#define TG_CMP0_TYPE            (0x08)
#define TG_CMP1_TYPE            (0x09)
#define TG_CMP2_TYPE            (0x0A)
#define TG_CMP3_TYPE            (0x0B)

#define TG_CMPH_EN              (0x0C) //Not for HSL-4XMO
#define TG_CMPH_DIR_EN          (0x0D) //Not for HSL-4XMO
#define TG_CMPH_DIR             (0x0E) //Not for HSL-4XMO

//#define TG_TRG0_SRC           (0x10)
//#define TG_TRG1_SRC           (0x11)
//#define TG_TRG2_SRC           (0x12)
//#define TG_TRG3_SRC           (0x13)

//#define TG_TRG0_PWD           (0x14)
//#define TG_TRG1_PWD           (0x15)
//#define TG_TRG2_PWD           (0x16)
//#define TG_TRG3_PWD           (0x17)

//#define TG_TRG0_CFG           (0x18)
//#define TG_TRG1_CFG           (0x19)
//#define TG_TRG2_CFG           (0x1A)
//#define TG_TRG3_CFG           (0x1B)

#define TG_ENCH_CFG             (0x20) //Not for HSL-4XMO

#define TG_TRG0_CMP_DIR         (0x21) //Only for HSL-4XMO
#define TG_TRG1_CMP_DIR         (0x22) //Only for HSL-4XMO
#define TG_TRG2_CMP_DIR         (0x23) //Only for HSL-4XMO
#define TG_TRG3_CMP_DIR         (0x24) //Only for HSL-4XMO

//Trigger parameter number define. [Only for PCI-8258]
#define TGR_LCMP0_SRC    (0x00)
#define TGR_LCMP1_SRC    (0x01)
#define TGR_TCMP0_SRC    (0x02)
#define TGR_TCMP1_SRC    (0x03)

#define TGR_TCMP0_DIR     (0x04)
#define TGR_TCMP1_DIR     (0x05)
#define TGR_TRG_EN		   (0x06)

#define TGR_TRG0_SRC     (0x10)
#define TGR_TRG1_SRC     (0x11)
#define TGR_TRG2_SRC     (0x12)
#define TGR_TRG3_SRC     (0x13)

#define TGR_TRG0_PWD     (0x14)
#define TGR_TRG1_PWD     (0x15)
#define TGR_TRG2_PWD     (0x16)
#define TGR_TRG3_PWD     (0x17)

#define TGR_TRG0_LOGIC     (0x18) 
#define TGR_TRG1_LOGIC     (0x19) 
#define TGR_TRG2_LOGIC     (0x1A)
#define TGR_TRG3_LOGIC     (0x1B)

#define TGR_TRG0_TGL	     (0x1C) 
#define TGR_TRG1_TGL		 (0x1D) 
#define TGR_TRG2_TGL		 (0x1E)
#define TGR_TRG3_TGL		 (0x1F)

#define TIMR_ITV				(0x20)
#define TIMR_DIR				(0x21)
#define TIMR_RING_EN     (0x22)
#define TIMR_EN				(0x23)

// Multi-dimension comparator define [Only for PCI-8254/58]
#define TGR_MCMP0_SRC				(0x30)
#define TGR_MCMP1_SRC				(0x31)
#define TGR_MCMP2_SRC				(0x32)
#define TGR_MCMP3_SRC				(0x33)

// Motion IO status bit number define.
#define MIO_ALM         (0)     // Servo alarm.
#define MIO_PEL         (1)     // Positive end limit.
#define MIO_MEL         (2)     // Negative end limit.
#define MIO_ORG         (3)     // ORG (Home)
#define MIO_EMG         (4)     // Emergency stop
#define MIO_EZ          (5)     // EZ.
#define MIO_INP         (6)     // In position.
#define MIO_SVON        (7)     // Servo on signal.
#define MIO_RDY         (8)     // Ready.
#define MIO_WARN        (9)     // Warning.
#define MIO_ZSP         (10)    // Zero speed.
#define MIO_SPEL        (11)    // Soft positive end limit.
#define MIO_SMEL        (12)    // Soft negative end limit.
#define MIO_TLC         (13)    // Torque is limited by torque limit value.
#define MIO_ABSL        (14)    // Absolute position lost.
#define MIO_STA         (15)    // External start signal.
#define MIO_PSD         (16)    // Positive slow down signal
#define MIO_MSD         (17)    // Negative slow down signal

// Motion status bit number define.
#define MTS_CSTP        (0)         // Command stop signal.
#define MTS_VM          (1)         // At maximum velocity.
#define MTS_ACC         (2)         // In acceleration.
#define MTS_DEC         (3)         // In deceleration.
#define MTS_DIR         (4)         // (Last)Moving direction.
#define MTS_NSTP        (5)         // Normal stop(Motion done).
#define MTS_HMV         (6)         // In home operation.
#define MTS_SMV         (7)         // Single axis move( relative, absolute, velocity move).
#define MTS_LIP         (8)         // Linear interpolation.
#define MTS_CIP         (9)         // Circular interpolation.
#define MTS_VS          (10)        // At start velocity.
#define MTS_PMV         (11)        // Point table move.
#define MTS_PDW         (12)        // Point table dwell move.
#define MTS_PPS         (13)        // Point table pause state.
#define MTS_SLV         (14)        // Slave axis move.
#define MTS_JOG         (15)        // Jog move.
#define MTS_ASTP        (16)        // Abnormal stop.
#define MTS_SVONS       (17)        // Servo off stopped.
#define MTS_EMGS        (18)        // EMG / SEMG stopped.
#define MTS_ALMS        (19)        // Alarm stop.
#define MTS_WANS        (20)        // Warning stopped.
#define MTS_PELS        (21)        // PEL stopped.
#define MTS_MELS        (22)        // MEL stopped.
#define MTS_ECES        (23)        // Error counter check level reaches and stopped.
#define MTS_SPELS       (24)        // Soft PEL stopped.
#define MTS_SMELS       (25)        // Soft MEL stopped.
#define MTS_STPOA       (26)        // Stop by others axes.
#define MTS_GDCES       (27)        // Gantry deviation error level reaches and stopped.
#define MTS_GTM         (28)        // Gantry mode turn on.
#define MTS_PAPB        (29)        // Pulsar mode turn on.
	//Following definition for PCI-8254/8
#define MTS_MDN        (5)         // Motion done. 0: In motion, 1: Motion done ( It could be abnormal stop)
#define MTS_WAIT       (10)        // Axis is in waiting state. ( Wait move trigger )
#define MTS_PTB         (11)        // Axis is in point buffer moving. ( When this bit on, MDN and ASTP will be cleared )
#define MTS_BLD		    (17)        // Axis (Axes) in blending moving
#define MTS_PRED       (18)        // Pre-distance event, 1: event arrived. The event will be clear when axis start moving 
#define MTS_POSTD     (19)        // Post-distance event. 1: event arrived. The event will be clear when axis start moving
#define MTS_GER         (28)        // 1: In geared ( This axis as slave axis and it follow a master specified in axis parameter. )

// Motion IO status bit value define.
#define MIO_ALM_V       (0x1)       // Servo alarm.
#define MIO_PEL_V       (0x2)       // Positive end limit.
#define MIO_MEL_V       (0x4)       // Negative end limit.
#define MIO_ORG_V       (0x8)       // ORG (Home).
#define MIO_EMG_V       (0x10)      // Emergency stop.
#define MIO_EZ_V        (0x20)      // EZ.
#define MIO_INP_V       (0x40)      // In position.
#define MIO_SVON_V      (0x80)      // Servo on signal.
#define MIO_RDY_V       (0x100)     // Ready.
#define MIO_WARN_V      (0x200)     // Warning.
#define MIO_ZSP_V       (0x400)     // Zero speed.
#define MIO_SPEL_V      (0x800)     // Soft positive end limit.
#define MIO_SMEL_V      (0x1000)    // Soft negative end limit.
#define MIO_TLC_V       (0x2000)    // Torque is limited by torque limit value.
#define MIO_ABSL_V      (0x4000)    // Absolute position lost.
#define MIO_STA_V       (0x8000)    // External start signal.
#define MIO_PSD_V       (0x10000)   // Positive slow down signal.
#define MIO_MSD_V       (0x20000)   // Negative slow down signal.

// Motion status bit value define.
#define MTS_CSTP_V      (0x1)           // Command stop signal.
#define MTS_VM_V        (0x2)           // At maximum velocity.
#define MTS_ACC_V       (0x4)           // In acceleration.
#define MTS_DEC_V       (0x8)           // In deceleration.
#define MTS_DIR_V       (0x10)          // (Last)Moving direction.
#define MTS_NSTP_V      (0x20)          // Normal stop(Motion done).
#define MTS_HMV_V       (0x40)          // In home operation.
#define MTS_SMV_V       (0x80)          // Single axis move( relative, absolute, velocity move).
#define MTS_LIP_V       (0x100)         // Linear interpolation.
#define MTS_CIP_V       (0x200)         // Circular interpolation.
#define MTS_VS_V        (0x400)         // At start velocity.
#define MTS_PMV_V       (0x800)         // Point table move.
#define MTS_PDW_V       (0x1000)        // Point table dwell move.
#define MTS_PPS_V       (0x2000)        // Point table pause state.
#define MTS_SLV_V       (0x4000)        // Slave axis move.
#define MTS_JOG_V       (0x8000)        // Jog move.
#define MTS_ASTP_V      (0x10000)       // Abnormal stop.
#define MTS_SVONS_V     (0x20000)       // Servo off stopped.
#define MTS_EMGS_V      (0x40000)       // EMG / SEMG stopped.
#define MTS_ALMS_V      (0x80000)       // Alarm stop.
#define MTS_WANS_V      (0x100000)      // Warning stopped.
#define MTS_PELS_V      (0x200000)      // PEL stopped.
#define MTS_MELS_V      (0x400000)      // MEL stopped.
#define MTS_ECES_V      (0x800000)      // Error counter check level reaches and stopped.
#define MTS_SPELS_V     (0x1000000)     // Soft PEL stopped.
#define MTS_SMELS_V     (0x2000000)     // Soft MEL stopped.
#define MTS_STPOA_V     (0x4000000)     // Stop by others axes.
#define MTS_GDCES_V     (0x8000000)     // Gantry deviation error level reaches and stopped.
#define MTS_GTM_V       (0x10000000)    // Gantry mode turn on.
#define MTS_PAPB_V      (0x20000000)    // Pulsar mode turn on.

// PointTable, option
//
#define PT_OPT_ABS      (0x00000000)    // move, absolute
#define PT_OPT_REL      (0x00000001)    // move, relative
#define PT_OPT_LINEAR   (0x00000000)    // move, linear
#define PT_OPT_ARC      (0x00000004)    // move, arc
#define PT_OPT_FC_CSTP  (0x00000000)    // signal, command stop (finish condition)
#define PT_OPT_FC_INP   (0x00000010)    // signal, in position
#define PT_OPT_LAST_POS (0x00000020)    // last point index
#define PT_OPT_DWELL    (0x00000040)    // dwell
#define PT_OPT_RAPID    (0x00000080)    // rapid positioning
#define PT_OPT_NOARC    (0x00010000)    // do not add arc
#define PT_OPT_SCUVE    (0x00000002)    // s-curve

// move option define
#define OPT_ABSOLUTE      (0x00000000)
#define OPT_RELATIVE      (0x00000001)
#define OPT_WAIT          (0x00000100)

// PTP buffer mode define
#define PTP_OPT_ABORTING       (0x00000000)
#define PTP_OPT_BUFFERED       (0x00001000)
#define PTP_OPT_BLEND_LOW      (0x00002000)
#define PTP_OPT_BLEND_PREVIOUS (0x00003000)
#define PTP_OPT_BLEND_NEXT     (0x00004000)
#define PTP_OPT_BLEND_HIGH     (0x00005000)

#define ITP_OPT_ABORT_BLEND     (0x00000000)
#define ITP_OPT_ABORT_FORCE     (0x00001000)
#define ITP_OPT_ABORT_STOP      (0x00002000)
#define ITP_OPT_BUFFERED        (0x00003000)
#define ITP_OPT_BLEND_DEC_EVENT (0x00004000)
#define ITP_OPT_BLEND_RES_DIST  (0x00005000)
#define ITP_OPT_BLEND_RES_DIST_PERCENT (0x00006000)



//Latch Parameter Number Define. [ Only for PCI-8158A & PCI-C154(+) ]
#define LTC_ENC_IPT_MODE          (0x00)
#define LTC_ENC_EA_INV            (0x01)
#define LTC_ENC_EB_INV            (0x02)
#define LTC_ENC_SIGNAL_FILITER_EN (0x05)
#define LTC_FIFO_HIGH_LEVEL       (0x06)
#define LTC_SIGNAL_FILITER_EN     (0x07)
#define LTC_SIGNAL_TRIG_LOGIC     (0x08)

//Latch Parameter Number Define. [ Only for PCI-8258 ]
#define LTC_IPT          (0x10)
#define LTC_ENC          (0x11)
#define LTC_LOGIC        (0x12)

//Comparator Trigger Parameter Number Define. [ Only for PCI-8158A & PCI-C154(+) ]
#define	TIG_ENC_IPT_MODE0			(0x00)
#define TIG_ENC_IPT_MODE1			(0x01)
#define	TIG_ENC_IPT_MODE2			(0x02)
#define	TIG_ENC_IPT_MODE3			(0x03)
#define	TIG_ENC_IPT_MODE4			(0x04)
#define	TIG_ENC_IPT_MODE5			(0x05)
#define	TIG_ENC_IPT_MODE6			(0x06)
#define	TIG_ENC_IPT_MODE7			(0x07)
#define	TIG_ENC_EA_INV0				(0x08)
#define	TIG_ENC_EA_INV1				(0x09)
#define	TIG_ENC_EA_INV2				(0x0A)
#define	TIG_ENC_EA_INV3				(0x0B)
#define	TIG_ENC_EA_INV4				(0x0C)
#define	TIG_ENC_EA_INV5				(0x0D)
#define	TIG_ENC_EA_INV6				(0x0E)
#define	TIG_ENC_EA_INV7				(0x0F)
#define	TIG_ENC_EB_INV0				(0x10)
#define	TIG_ENC_EB_INV1				(0x11)
#define	TIG_ENC_EB_INV2				(0x12)
#define	TIG_ENC_EB_INV3				(0x13)
#define	TIG_ENC_EB_INV4				(0x14)
#define	TIG_ENC_EB_INV5				(0x15)
#define	TIG_ENC_EB_INV6				(0x16)
#define	TIG_ENC_EB_INV7				(0x17)
#define	TIG_ENC_SIGNAL_FILITER_EN0	(0x28)
#define	TIG_ENC_SIGNAL_FILITER_EN1	(0x29)
#define	TIG_ENC_SIGNAL_FILITER_EN2	(0x2A)
#define	TIG_ENC_SIGNAL_FILITER_EN3	(0x2B)
#define	TIG_ENC_SIGNAL_FILITER_EN4	(0x2C)
#define	TIG_ENC_SIGNAL_FILITER_EN5	(0x2D)
#define	TIG_ENC_SIGNAL_FILITER_EN6	(0x2E)
#define	TIG_ENC_SIGNAL_FILITER_EN7	(0x2F)
#define	TIG_TIMER8_DIR				(0x30)
#define	TIG_TIMER8_ITV				(0x31)
#define	TIG_CMP0_SRC				(0x32)
#define	TIG_CMP1_SRC				(0x33)
#define	TIG_CMP2_SRC				(0x34)
#define	TIG_CMP3_SRC				(0x35)
#define	TIG_CMP4_SRC				(0x36)
#define	TIG_CMP5_SRC				(0x37)
#define	TIG_CMP6_SRC				(0x38)
#define	TIG_CMP7_SRC				(0x39)
#define	TIG_TRG0_SRC				(0x3A)
#define	TIG_TRG1_SRC				(0x3B)
#define	TIG_TRG2_SRC				(0x3C)
#define	TIG_TRG3_SRC				(0x3D)
#define	TIG_TRG4_SRC				(0x3E)
#define	TIG_TRG5_SRC				(0x3F)
#define	TIG_TRG6_SRC				(0x40)
#define	TIG_TRG7_SRC				(0x41)
#define	TIG_TRGOUT0_MAP				(0x42)
#define	TIG_TRGOUT1_MAP				(0x43)
#define	TIG_TRGOUT2_MAP				(0x44)
#define	TIG_TRGOUT3_MAP				(0x45)
#define	TIG_TRGOUT4_MAP				(0x46)
#define	TIG_TRGOUT5_MAP				(0x47)
#define	TIG_TRGOUT6_MAP				(0x48)
#define	TIG_TRGOUT7_MAP				(0x49)
#define	TIG_TRGOUT0_LOGIC			(0x4A)
#define	TIG_TRGOUT1_LOGIC			(0x4B)
#define	TIG_TRGOUT2_LOGIC			(0x4C)
#define	TIG_TRGOUT3_LOGIC			(0x4D)
#define	TIG_TRGOUT4_LOGIC			(0x4E)
#define	TIG_TRGOUT5_LOGIC			(0x4F)
#define	TIG_TRGOUT6_LOGIC			(0x50)
#define	TIG_TRGOUT7_LOGIC			(0x51)
#define	TIG_PWM0_PULSE_WIDTH		(0x52)
#define	TIG_PWM1_PULSE_WIDTH		(0x53)
#define	TIG_PWM2_PULSE_WIDTH		(0x54)
#define	TIG_PWM3_PULSE_WIDTH		(0x55)
#define	TIG_PWM4_PULSE_WIDTH		(0x56)
#define	TIG_PWM5_PULSE_WIDTH		(0x57)
#define	TIG_PWM6_PULSE_WIDTH		(0x58)
#define	TIG_PWM7_PULSE_WIDTH		(0x59)
#define	TIG_PWM0_MODE				(0x5A)
#define	TIG_PWM1_MODE				(0x5B)
#define	TIG_PWM2_MODE				(0x5C)
#define	TIG_PWM3_MODE				(0x5D)
#define	TIG_PWM4_MODE				(0x5E)
#define	TIG_PWM5_MODE				(0x5F)
#define	TIG_PWM6_MODE				(0x60)
#define	TIG_PWM7_MODE				(0x61)
#define	TIG_TIMER0_ITV				(0x62)
#define	TIG_TIMER1_ITV				(0x63)
#define	TIG_TIMER2_ITV				(0x64)
#define	TIG_TIMER3_ITV				(0x65)
#define	TIG_TIMER4_ITV				(0x66)
#define	TIG_TIMER5_ITV				(0x67)
#define	TIG_TIMER6_ITV				(0x68)
#define	TIG_TIMER7_ITV				(0x69)
#define	TIG_FIFO_LEVEL0				(0x6A)
#define	TIG_FIFO_LEVEL1				(0x6B)
#define	TIG_FIFO_LEVEL2				(0x6C)
#define	TIG_FIFO_LEVEL3				(0x6D)
#define	TIG_FIFO_LEVEL4				(0x6E)
#define	TIG_FIFO_LEVEL5				(0x6F)
#define	TIG_FIFO_LEVEL6				(0x70)
#define	TIG_FIFO_LEVEL7				(0x71)
#define	TIG_OUTPUT_EN0				(0x72)
#define	TIG_OUTPUT_EN1				(0x73)
#define	TIG_OUTPUT_EN2				(0x74)
#define	TIG_OUTPUT_EN3				(0x75)
#define	TIG_OUTPUT_EN4				(0x76)
#define	TIG_OUTPUT_EN5				(0x77)
#define	TIG_OUTPUT_EN6				(0x78)
#define	TIG_OUTPUT_EN7				(0x79)

#define PRA_HOME_LATCH				(0x900)  // Select Home latch source [PCI-8353 only]
#endif
