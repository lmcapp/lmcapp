#ifndef _ADLINK_SYSTEMAPI_H
#define _ADLINK_SYSTEMAPI_H

//#define _MYLINUX //使用Liunx必須要開啟

#ifdef __cplusplus
extern "C" {
#endif

#if defined (_MYWIN32) || defined (_MYRTEVLIB)
	#include <windows.h>
	#define FNTYPE PASCAL
#elif defined (_MYLINUX)
	#ifndef FNTYPE
	#define FNTYPE
	#endif		
#elif defined(_MYRTE)	
	#define FNTYPE	_stdcall
#elif defined(_RTX)
	#define FNTYPE _stdcall
#else
	#ifndef FNTYPE
	#define FNTYPE PASCAL
	#endif
#endif

#include "type_def.h"

// System & Initialization
I32 FNTYPE APS_initial( I32 *BoardID_InBits, I32 Mode );
#if defined (_MYLINUX)
I32 FNTYPE APS_close(void);
I32 FNTYPE APS_version(void);
#else
I32 FNTYPE APS_close(void);
I32 FNTYPE APS_version(void);
#endif
I32 FNTYPE APS_device_driver_version( I32 Board_ID );
I32 FNTYPE APS_get_axis_info( I32 Axis_ID, I32 *Board_ID, I32 *Axis_No, I32 *Port_ID, I32 *Module_ID );
I32 FNTYPE APS_set_board_param( I32 Board_ID, I32 BOD_Param_No, I32 BOD_Param );
I32 FNTYPE APS_get_board_param( I32 Board_ID, I32 BOD_Param_No, I32 *BOD_Param );
I32 FNTYPE APS_set_axis_param( I32 Axis_ID, I32 AXS_Param_No, I32  AXS_Param );
I32 FNTYPE APS_get_axis_param( I32 Axis_ID, I32 AXS_Param_No, I32 *AXS_Param );
I32 FNTYPE APS_get_system_timer( I32 Board_ID, I32 *Timer );
I32 FNTYPE APS_get_device_info( I32 Board_ID, I32 Info_No, I32 *Info );
I32 FNTYPE APS_get_card_name( I32 Board_ID, I32 *CardName );
I32 FNTYPE APS_disable_device( I32 DeviceName );
I32 FNTYPE APS_get_first_axisId( I32 Board_ID, I32 *StartAxisID, I32 *TotalAxisNum );
I32 FNTYPE APS_set_security_key( I32 Board_ID, I32 OldPassword, I32 NewPassword );
I32 FNTYPE APS_check_security_key( I32 Board_ID, I32 Password );
I32 FNTYPE APS_reset_security_key( I32 Board_ID );
I32 FNTYPE APS_load_param_from_file( const char *pXMLFile );
//Virtual board settings [For PCI-8254/58]
I32 FNTYPE APS_register_virtual_board( I32 VirCardIndex, I32 Count );
I32 FNTYPE APS_get_virtual_board_info( I32 VirCardIndex, I32 *Count );
//Parameters setting by float [For PCI-8254/58]
I32 FNTYPE APS_set_axis_param_f( I32 Axis_ID, I32 AXS_Param_No, F64 AXS_Param );
I32 FNTYPE APS_get_axis_param_f( I32 Axis_ID, I32 AXS_Param_No, F64 *AXS_Param );
//Control driver mode [For PCI-8254/58]
I32 FNTYPE APS_get_curr_sys_ctrl_mode( I32 Axis_ID, I32 *Mode );
//[For PCI-7856, MNET series]
I32 FNTYPE APS_save_param_to_file( I32 Board_ID, const char *pXMLFile );

//Flash functions [For PCI-8253/56, PCI-8392(H)]
I32 FNTYPE APS_save_parameter_to_flash( I32 Board_ID );
I32 FNTYPE APS_load_parameter_from_flash( I32 Board_ID );
I32 FNTYPE APS_load_parameter_from_default( I32 Board_ID );

//SSCNET-3 functions [For PCI-8392(H)] 
I32 FNTYPE APS_start_sscnet( I32 Board_ID, I32 *AxisFound_InBits );
I32 FNTYPE APS_stop_sscnet( I32 Board_ID );
I32 FNTYPE APS_get_sscnet_servo_param( I32 Axis_ID, I32 Para_No1, I32 *Para_Dat1, I32 Para_No2, I32 *Para_Dat2 );
I32 FNTYPE APS_set_sscnet_servo_param( I32 Axis_ID, I32 Para_No1, I32 Para_Dat1, I32 Para_No2, I32 Para_Dat2 );
I32 FNTYPE APS_get_sscnet_servo_alarm( I32 Axis_ID, I32 *Alarm_No, I32 *Alarm_Detail );
I32 FNTYPE APS_reset_sscnet_servo_alarm( I32 Axis_ID );
I32 FNTYPE APS_save_sscnet_servo_param( I32 Board_ID );
I32 FNTYPE APS_get_sscnet_servo_abs_position( I32 Axis_ID, I32 *Cyc_Cnt, I32 *Res_Cnt );
I32 FNTYPE APS_save_sscnet_servo_abs_position( I32 Board_ID );
I32 FNTYPE APS_load_sscnet_servo_abs_position( I32 Axis_ID, I32 Abs_Option, I32 *Cyc_Cnt, I32 *Res_Cnt );
I32 FNTYPE APS_get_sscnet_link_status( I32 Board_ID, I32 *Link_Status );
I32 FNTYPE APS_set_sscnet_servo_monitor_src( I32 Axis_ID, I32 Mon_No, I32 Mon_Src );
I32 FNTYPE APS_get_sscnet_servo_monitor_src( I32 Axis_ID, I32 Mon_No, I32 *Mon_Src );
I32 FNTYPE APS_get_sscnet_servo_monitor_data( I32 Axis_ID, I32 Arr_Size, I32 *Data_Arr );
I32 FNTYPE APS_set_sscnet_control_mode( I32 Axis_ID, I32 Mode );
I32 FNTYPE APS_set_sscnet_abs_enable( I32 Board_ID, I32 Option);
I32 FNTYPE APS_set_sscnet_abs_enable_by_axis( I32 Axis_ID, I32 Option);

//Motion IO & motion status functions
I32 FNTYPE APS_motion_status( I32 Axis_ID );
I32 FNTYPE APS_motion_io_status( I32 Axis_ID );

//Monitor functions
I32 FNTYPE APS_get_command( I32 Axis_ID, I32 *Command );
I32 FNTYPE APS_set_command(I32 Axis_ID, I32 Command);
I32 FNTYPE APS_set_servo_on( I32 Axis_ID, I32 Servo_On );
I32 FNTYPE APS_get_position( I32 Axis_ID, I32 *Position );
I32 FNTYPE APS_set_position(I32 Axis_ID, I32 Position);
I32 FNTYPE APS_get_command_velocity(I32 Axis_ID, I32 *Velocity );
I32 FNTYPE APS_get_feedback_velocity(I32 Axis_ID, I32 *Velocity );
I32 FNTYPE APS_get_error_position( I32 Axis_ID, I32 *Err_Pos );
I32 FNTYPE APS_get_target_position( I32 Axis_ID, I32 *Targ_Pos );
I32 FNTYPE APS_get_actual_torque( I32 Axis_ID, I32 *Torque );



// Monitor functions by float [Only for PCI-8254/8]
I32 FNTYPE APS_get_command_f( I32 Axis_ID, F64 *Command );
I32 FNTYPE APS_set_command_f( I32 Axis_ID, F64 Command );
I32 FNTYPE APS_get_position_f( I32 Axis_ID, F64 *Position );
I32 FNTYPE APS_set_position_f(I32 Axis_ID, F64 Position);
I32 FNTYPE APS_get_command_velocity_f(I32 Axis_ID, F64 *Velocity );
I32 FNTYPE APS_get_target_position_f( I32 Axis_ID, F64 *Targ_Pos );
I32 FNTYPE APS_get_error_position_f( I32 Axis_ID, F64 *Err_Pos );
I32 FNTYPE APS_get_feedback_velocity_f(I32 Axis_ID, F64 *Velocity );

//Motion queue status [For PCI-8254/58]
I32 FNTYPE APS_get_mq_free_space( I32 Axis_ID, I32 *Space );
I32 FNTYPE APS_get_mq_usage( I32 Axis_ID, I32 *Usage );
//Motion stop code [For PCI-8254/58]
I32 FNTYPE APS_get_stop_code( I32 Axis_ID, I32 *Code );

// Single axis motion
I32 FNTYPE APS_relative_move( I32 Axis_ID, I32 Distance, I32 Max_Speed );
I32 FNTYPE APS_absolute_move( I32 Axis_ID, I32 Position, I32 Max_Speed );
I32 FNTYPE APS_velocity_move( I32 Axis_ID, I32 Max_Speed );
I32 FNTYPE APS_home_move( I32 Axis_ID );
I32 FNTYPE APS_stop_move( I32 Axis_ID );
I32 FNTYPE APS_emg_stop( I32 Axis_ID );
I32 FNTYPE APS_relative_move2( I32 Axis_ID, I32 Distance, I32 Start_Speed, I32 Max_Speed, I32 End_Speed, I32 Acc_Rate, I32 Dec_Rate );
I32 FNTYPE APS_absolute_move2( I32 Axis_ID, I32 Position, I32 Start_Speed, I32 Max_Speed, I32 End_Speed, I32 Acc_Rate, I32 Dec_Rate );
I32 FNTYPE APS_home_move2( I32 Axis_ID, I32 Dir, I32 Acc, I32 Start_Speed, I32 Max_Speed, I32 ORG_Speed );
I32 FNTYPE APS_home_escape( I32 Axis_ID );

//JOG functions [For PCI-8392(H), PCI-8253/56]
I32 FNTYPE APS_set_jog_param( I32 Axis_ID, JOG_DATA *pStr_Jog, I32 Mask );
I32 FNTYPE APS_get_jog_param( I32 Axis_ID, JOG_DATA *pStr_Jog );
I32 FNTYPE APS_jog_mode_switch( I32 Axis_ID, I32 Turn_No );
I32 FNTYPE APS_jog_start( I32 Axis_ID, I32 On );

// Interpolation
I32 FNTYPE APS_absolute_linear_move( I32 Dimension, I32 *Axis_ID_Array, I32 *Position_Array, I32 Max_Linear_Speed );
I32 FNTYPE APS_relative_linear_move( I32 Dimension, I32 *Axis_ID_Array, I32 *Distance_Array, I32 Max_Linear_Speed );
I32 FNTYPE APS_absolute_arc_move( I32 Dimension, I32 *Axis_ID_Array, I32 *Center_Pos_Array, I32 Max_Arc_Speed, I32 Angle );
I32 FNTYPE APS_relative_arc_move( I32 Dimension, I32 *Axis_ID_Array, I32 *Center_Offset_Array, I32 Max_Arc_Speed, I32 Angle );

//Helical interpolation [For PCI-8253/56]
I32 FNTYPE APS_absolute_helix_move( I32 Dimension, I32 *Axis_ID_Array, I32 *Center_Pos_Array, I32 Max_Arc_Speed, I32 Pitch, I32 TotalHeight, I32 CwOrCcw );
I32 FNTYPE APS_relative_helix_move( I32 Dimension, I32 *Axis_ID_Array, I32 *Center_PosOffset_Array, I32 Max_Arc_Speed, I32 Pitch, I32 TotalHeight, I32 CwOrCcw );

//Circular interpolation( Support 2D and 3D ) [For PCI-8253/56]
I32 FNTYPE APS_absolute_arc_move_3pe(I32 Dimension, I32 *Axis_ID_Array, I32 *Pass_Pos_Array, I32 *End_Pos_Array, I32 Max_Arc_Speed );
I32 FNTYPE APS_relative_arc_move_3pe(I32 Dimension, I32 *Axis_ID_Array, I32 *Pass_PosOffset_Array, I32 *End_PosOffset_Array, I32 Max_Arc_Speed );

// Interrupt functions
#if defined (_MYLINUX)
I32 FNTYPE APS_int_enable( I32 Board_ID, I32 Enable, void (*event_handler)(int));
I32 FNTYPE APS_get_int_status( I32 Board_ID, I32 Item_No, I32 Factor_No, I32 *Event_int_status );
#else
I32 FNTYPE APS_int_enable( I32 Board_ID, I32 Enable );
#endif

I32 FNTYPE APS_set_int_factor( I32 Board_ID, I32 Item_No, I32 Factor_No, I32 Enable );
I32 FNTYPE APS_get_int_factor( I32 Board_ID, I32 Item_No, I32 Factor_No, I32 *Enable );

HANDLE FNTYPE APS_set_int_factorH( I32 Board_ID, I32 Item_No, I32 Factor_No, I32 Enable );
HANDLE FNTYPE APS_int_no_to_handle( I32 Int_No );

I32 FNTYPE APS_wait_single_int( I32 Int_No, I32 Time_Out );
I32 FNTYPE APS_wait_multiple_int( I32 Int_Count, I32 *Int_No_Array, I32 Wait_All, I32 Time_Out );
I32 FNTYPE APS_reset_int( I32 Int_No );
I32 FNTYPE APS_set_int( I32 Int_No );
I32 FNTYPE APS_wait_error_int( I32 Board_ID, I32 Item_No, I32 Time_Out );


//Field bus motion interrupt [For PCI-7856, MNET series]
I32 FNTYPE APS_set_field_bus_int_factor_motion( I32 Axis_ID, I32 Factor_No, I32  Enable );
I32 FNTYPE APS_get_field_bus_int_factor_motion( I32 Axis_ID, I32 Factor_No, I32 *Enable );
I32 FNTYPE APS_set_field_bus_int_factor_error( I32 Axis_ID, I32 Factor_No, I32  Enable );
I32 FNTYPE APS_get_field_bus_int_factor_error( I32 Axis_ID, I32 Factor_No, I32 *Enable );
I32 FNTYPE APS_reset_field_bus_int_motion( I32 Axis_ID );
I32 FNTYPE APS_wait_field_bus_error_int_motion( I32 Axis_ID, I32 Time_Out );

I32 FNTYPE APS_set_field_bus_int_factor_di( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32  bitsOfCheck );
I32 FNTYPE APS_get_field_bus_int_factor_di( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *bitsOfCheck );

//Sampling functions [For PCI-8392(H), PCI-8253/56, PCI-8254/58]
I32 FNTYPE APS_set_sampling_param( I32 Board_ID, I32 ParaNum, I32 ParaDat );
I32 FNTYPE APS_get_sampling_param( I32 Board_ID, I32 ParaNum, I32 *ParaDat );
I32 FNTYPE APS_wait_trigger_sampling( I32 Board_ID, I32 Length, I32 PreTrgLen, I32 TimeOutMs, STR_SAMP_DATA_4CH *DataArr );
I32 FNTYPE APS_wait_trigger_sampling_async( I32 Board_ID, I32 Length, I32 PreTrgLen, I32 TimeOutMs, STR_SAMP_DATA_4CH *DataArr );
I32 FNTYPE APS_get_sampling_count( I32 Board_ID, I32 *SampCnt );
I32 FNTYPE APS_stop_wait_sampling( I32 Board_ID );
I32 FNTYPE APS_auto_sampling( I32 Board_ID, I32 StartStop );
I32 FNTYPE APS_get_sampling_data( I32 Board_ID, I32 *Length, STR_SAMP_DATA_4CH *DataArr, I32 *Status );

//Sampling functions extension [For PCI-8254/58]
I32 FNTYPE APS_set_sampling_param_ex( I32 Board_ID, SAMP_PARAM *Param );
I32 FNTYPE APS_get_sampling_param_ex( I32 Board_ID, SAMP_PARAM *Param );
I32 FNTYPE APS_wait_trigger_sampling_ex( I32 Board_ID, I32 Length, I32 PreTrgLen, I32 TimeOutMs, STR_SAMP_DATA_8CH *DataArr );
I32 FNTYPE APS_wait_trigger_sampling_async_ex( I32 Board_ID, I32 Length, I32 PreTrgLen, I32 TimeOutMs, STR_SAMP_DATA_8CH *DataArr );
I32 FNTYPE APS_get_sampling_data_ex( I32 Board_ID, I32 *Length, STR_SAMP_DATA_8CH *DataArr, I32 *Status );

//DIO & AIO functions
I32 FNTYPE APS_write_d_output(I32 Board_ID, I32 DO_Group, I32 DO_Data);
I32 FNTYPE APS_read_d_output(I32 Board_ID, I32 DO_Group, I32 *DO_Data);
I32 FNTYPE APS_read_d_input(I32 Board_ID, I32 DI_Group, I32 *DI_Data);

I32 FNTYPE APS_write_d_channel_output(I32 Board_ID, I32 DO_Group, I32 Ch_No, I32 DO_Data);
I32 FNTYPE APS_read_d_channel_output(I32 Board_ID, I32 DO_Group, I32 Ch_No, I32 *DO_Data);
I32 FNTYPE APS_read_d_channel_input(I32 Board_ID, I32 DI_Group, I32 Ch_No, I32 *DI_Data );

I32 FNTYPE APS_read_a_input_value(I32 Board_ID, I32 Channel_No, F64 *Convert_Data);
I32 FNTYPE APS_read_a_input_data(I32 Board_ID, I32 Channel_No, I32 *Raw_Data);
I32 FNTYPE APS_write_a_output_value(I32 Board_ID, I32 Channel_No, F64 Convert_Data);
I32 FNTYPE APS_write_a_output_data(I32 Board_ID, I32 Channel_No, I32 Raw_Data);
//AIO [For PCI-8254/58]
I32 FNTYPE APS_read_a_output_value(I32 Board_ID, I32 Channel_No, F64 *Convert_Data);

//Point table move functions [For PCI-8253/56, PCI-8392(H)]
I32 FNTYPE APS_set_point_table( I32 Axis_ID, I32 Index, POINT_DATA *Point );
I32 FNTYPE APS_get_point_table( I32 Axis_ID, I32 Index, POINT_DATA *Point );
I32 FNTYPE APS_get_running_point_index( I32 Axis_ID, I32 *Index );
I32 FNTYPE APS_get_start_point_index( I32 Axis_ID, I32 *Index );
I32 FNTYPE APS_get_end_point_index( I32 Axis_ID, I32 *Index );
I32 FNTYPE APS_set_table_move_pause( I32 Axis_ID, I32 Pause_en );
I32 FNTYPE APS_set_table_move_repeat( I32 Axis_ID, I32 Repeat_en );
I32 FNTYPE APS_get_table_move_repeat_count( I32 Axis_ID, I32 *RepeatCnt );
I32 FNTYPE APS_point_table_move( I32 Dimension, I32 *Axis_ID_Array, I32 StartIndex, I32 EndIndex );

I32 FNTYPE APS_set_point_tableEx( I32 Axis_ID, I32 Index, PNT_DATA *Point );
I32 FNTYPE APS_set_point_tableEx_2D( I32 Axis_ID, I32 Axis_ID_2, I32 Index, PNT_DATA_2D *Point );
I32 FNTYPE APS_set_point_table_4DL( I32 *Axis_ID_Array, I32 Index, PNT_DATA_4DL *Point );

//Point table + IO - Pause / Resume [For PCI-8253/56]
I32 FNTYPE APS_set_table_move_ex_pause( I32 Axis_ID );
I32 FNTYPE APS_set_table_move_ex_rollback( I32 Axis_ID, I32 Max_Speed );
I32 FNTYPE APS_set_table_move_ex_resume( I32 Axis_ID );

//Point table with extend option [For PCI-8392(H)]
I32 FNTYPE APS_set_point_table_ex( I32 Axis_ID, I32 Index, POINT_DATA_EX *Point );
I32 FNTYPE APS_get_point_table_ex( I32 Axis_ID, I32 Index, POINT_DATA_EX *Point );

//Point table feeder [For PCI-8253/56, PCI-8392(H)]
I32 FNTYPE APS_set_feeder_group( I32 GroupId, I32 Dimension, I32 *Axis_ID_Array );
I32 FNTYPE APS_get_feeder_group( I32 GroupId, I32 *Dimension, I32 *Axis_ID_Array );
I32 FNTYPE APS_free_feeder_group( I32 GroupId );
I32 FNTYPE APS_reset_feeder_buffer( I32 GroupId );
I32 FNTYPE APS_set_feeder_point_2D( I32 GroupId, PNT_DATA_2D* PtArray, I32 Size, I32 LastFlag );
I32 FNTYPE APS_set_feeder_point_2D_ex( I32 GroupId, PNT_DATA_2D_F64* PtArray, I32 Size, I32 LastFlag );
I32 FNTYPE APS_start_feeder_move( I32 GroupId );
I32 FNTYPE APS_get_feeder_status( I32 GroupId, I32 *State, I32 *ErrCode );
I32 FNTYPE APS_get_feeder_running_index( I32 GroupId, I32 *Index );
I32 FNTYPE APS_get_feeder_feed_index( I32 GroupId, I32 *Index );

//Point table feeder [For PCI-8253/56]
I32 FNTYPE APS_set_feeder_ex_pause( I32 GroupId );
I32 FNTYPE APS_set_feeder_ex_rollback( I32 GroupId, I32 Max_Speed );
I32 FNTYPE APS_set_feeder_ex_resume( I32 GroupId );
I32 FNTYPE APS_set_feeder_cfg_acc_type( I32 GroupId, I32 Type );

//Point table functions [For MNET-4XMO-C]
I32 FNTYPE APS_set_point_table_mode2( I32 Axis_ID, I32 Mode );
I32 FNTYPE APS_set_point_table2( I32 Dimension, I32 *Axis_ID_Array, I32 Index, POINT_DATA2 *Point );
I32 FNTYPE APS_point_table_continuous_move2( I32 Dimension, I32 *Axis_ID_Array );
I32 FNTYPE APS_point_table_single_move2( I32 Axis_ID, I32 Index );
I32 FNTYPE APS_get_running_point_index2( I32 Axis_ID, I32 *Index );
I32 FNTYPE APS_point_table_status2( I32 Axis_ID, I32 *Status );
I32 FNTYPE APS_point_table_setting_continuous_move2( I32 Dimension, I32 *Axis_ID_Array, I32 TotalPoints, POINT_DATA2 *Point );
I32 FNTYPE APS_set_point_table2_maximum_speed_check( I32 Dimension, I32 *Axis_ID_Array, I32 Index, POINT_DATA2 *Point );

//Point table functions [For HSL-4XMO]
I32 FNTYPE APS_set_point_table3( I32 Dimension, I32 *Axis_ID_Array, I32 Index, POINT_DATA3 *Point );
I32 FNTYPE APS_point_table_move3( I32 Dimension, I32 *Axis_ID_Array, I32 StartIndex, I32 EndIndex );
I32 FNTYPE APS_set_point_table_param3( I32 FirstAxid, I32 ParaNum, I32 ParaDat );

//Gantry functions [For PCI-8392(H), PCI-8253/56]
I32 FNTYPE APS_set_gantry_param( I32 Board_ID, I32 GroupNum, I32 ParaNum, I32 ParaDat );
I32 FNTYPE APS_get_gantry_param( I32 Board_ID, I32 GroupNum, I32 ParaNum, I32 *ParaDat );
I32 FNTYPE APS_set_gantry_axis( I32 Board_ID, I32 GroupNum, I32 Master_Axis_ID, I32 Slave_Axis_ID );
I32 FNTYPE APS_get_gantry_axis( I32 Board_ID, I32 GroupNum, I32 *Master_Axis_ID, I32 *Slave_Axis_ID );
I32 FNTYPE APS_get_gantry_error( I32 Board_ID, I32 GroupNum, I32 *GentryError );

//Digital filter functions [For PCI-8253/56]
I32 FNTYPE APS_set_filter_param( I32 Axis_ID, I32 Filter_paramNo, I32 param_val );
I32 FNTYPE APS_get_filter_param( I32 Axis_ID, I32 Filter_paramNo, I32 *param_val );

//Field bus master functions
I32 FNTYPE APS_set_field_bus_param( I32 Board_ID, I32 BUS_No, I32 BUS_Param_No, I32  BUS_Param );
I32 FNTYPE APS_get_field_bus_param( I32 Board_ID, I32 BUS_No, I32 BUS_Param_No, I32 *BUS_Param );
I32 FNTYPE APS_start_field_bus( I32 Board_ID, I32 BUS_No, I32 Start_Axis_ID );
I32 FNTYPE APS_scan_field_bus( I32 Board_ID, I32 BUS_No );
I32 FNTYPE APS_stop_field_bus( I32 Board_ID, I32 BUS_No );
I32 FNTYPE APS_get_field_bus_master_status( I32 Board_ID, I32 BUS_No, U32 *Status );

I32 FNTYPE APS_get_field_bus_device_info( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Info_No, I32 *Info );
I32 FNTYPE APS_get_field_bus_last_scan_info( I32 Board_ID, I32 BUS_No, I32 *Info_Array, I32 Array_Size, I32 *Info_Count );
I32 FNTYPE APS_get_field_bus_module_info(I32 Board_ID, I32 BUS_No, I32 MOD_No, PEC_MODULE_INFO Module_info );

I32 FNTYPE APS_set_field_bus_od_data( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 SubMOD_No, I32 ODIndex, U32 RawData );
I32 FNTYPE APS_get_field_bus_od_data( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 SubMOD_No, I32 ODIndex, U32 *RawData );
I32 FNTYPE APS_get_field_bus_od_module_info( I32 Board_ID, I32 BUS_No, I32 MOD_No, PEC_Sub_MODULE_INFO Sub_Module_info );
I32 FNTYPE APS_get_field_bus_od_number( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 SubMOD_No, I32 *TxODNum, I32 *RxODNum );
I32 FNTYPE APS_get_field_bus_od_tx( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 SubMOD_No, I32 TxODIndex, PEC_Sub_MODULE_OD_INFO Sub_MODULE_OD_INFO );
I32 FNTYPE APS_get_field_bus_od_rx( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 SubMOD_No, I32 RxODIndex, PEC_Sub_MODULE_OD_INFO Sub_MODULE_OD_INFO );

I32 FNTYPE APS_get_field_bus_master_type( I32 Board_ID, I32 BUS_No, I32 *BUS_Type );
I32 FNTYPE APS_get_field_bus_slave_type( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *MOD_Type );
I32 FNTYPE APS_get_field_bus_slave_name( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *MOD_Name );
I32 FNTYPE APS_get_field_bus_slave_serialID( I32 Board_ID, I32 BUS_No, I32 MOD_No, I16 *Serial_ID );	//Added by Jack Tseng: 2012.12.7
I32 FNTYPE APS_get_field_bus_slave_first_axisno( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *AxisNo, I32 *TotalAxes );

//Field bus slave functions
I32 FNTYPE APS_set_field_bus_slave_param( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, I32 ParaNum, I32 ParaDat  );
I32 FNTYPE APS_get_field_bus_slave_param( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, I32 ParaNum, I32 *ParaDat );
I32 FNTYPE APS_get_slave_connect_quality( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *Sts_data );
I32 FNTYPE APS_get_slave_online_status( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *Live );

//Field bus DIO slave functions [For PCI-8392(H)]
I32 FNTYPE APS_set_field_bus_d_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 DO_Value );
I32 FNTYPE APS_get_field_bus_d_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *DO_Value );
I32 FNTYPE APS_get_field_bus_d_input( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *DI_Value );
I32 FNTYPE APS_set_field_bus_d_channel_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, I32  DO_Value );
I32 FNTYPE APS_get_field_bus_d_channel_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, I32 *DO_Value );
I32 FNTYPE APS_get_field_bus_d_channel_input(  I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, I32 *DI_Value );

I32 FNTYPE APS_set_field_bus_d_port_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Port_No, U32 DO_Value );
I32 FNTYPE APS_get_field_bus_d_port_input( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Port_No, U32 *DI_Value );
I32 FNTYPE APS_get_field_bus_d_port_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Port_No, U32 *DO_Value );
I32 FNTYPE APS_reset_field_bus_alarm( I32 Axis_ID );
I32 FNTYPE APS_get_field_bus_alarm( I32 Axis_ID, U32 *AlarmCode );
I32 FNTYPE APS_set_field_bus_pdo( I32 Board_ID, I32 BUS_No, U16 ByteOffset, U16 Size, U32 Value );
I32 FNTYPE APS_get_field_bus_pdo( I32 Board_ID, I32 BUS_No, U16 ByteOffset, U16 Size, U32 *Value );
I32 FNTYPE APS_get_field_bus_pdo_offset( I32 Board_ID, I32 BUS_No, I32 MOD_No, 
										 PPDO_OFFSET *PPTx, U32 *NumOfTx, 
										 PPDO_OFFSET *PPRx, U32 *NumOfRx 
						               );

I32 FNTYPE APS_set_field_bus_sdo( I32  Board_ID, 
								  I32  BUS_No, 
								  I32  MOD_No,
								  U16  ODIndex,
								  U16  ODSubIndex,
								  U8   *Data,
							      U32  DataLen,
								  U32  Timeout,
								  U32  Flags  
								);

I32 FNTYPE APS_get_field_bus_sdo( I32 Board_ID, 
								  I32 BUS_No,
								  I32 MOD_No,
								  U16 ODIndex,
								  U16 ODSubIndex,
								  U8  *Data,
								  U32 DataLen,
								  U32 *OutDatalen,
								  U32 Timeout,
								  U32 Flags
								);

I32 FNTYPE APS_get_field_bus_od_num( I32 Board_ID, I32 BUS_No, I32 MOD_No, U16 *Num, U16 **ODList );
I32 FNTYPE APS_get_field_bus_od_desc( I32 Board_ID, I32 BUS_No, I32 MOD_No, U16 ODIndex, U16 *MaxNumSubIndex, U8 *Description, U32 Size );
I32 FNTYPE APS_get_field_bus_od_desc_entry( I32 Board_ID, I32 BUS_No, I32 MOD_No, U16 ODIndex, U16 ODSubIndex, POD_DESC_ENTRY pOD_DESC_ENTRY );
I32 FNTYPE APS_get_field_bus_loss_package( I32 Board_ID, I32 BUS_No, I32 *Loss_Count );


//Modules be 64 bits gpio
I32 FNTYPE APS_set_field_bus_d_output_ex( I32 Board_ID, I32 BUS_No, I32 MOD_No, DO_DATA_EX DO_Value );
I32 FNTYPE APS_get_field_bus_d_output_ex( I32 Board_ID, I32 BUS_No, I32 MOD_No, DO_DATA_EX *DO_Value );
I32 FNTYPE APS_get_field_bus_d_input_ex( I32 Board_ID, I32 BUS_No, I32 MOD_No, DI_DATA_EX *DI_Value );

//Field bus AIO slave functions
I32 FNTYPE APS_set_field_bus_a_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64  AO_Value );
I32 FNTYPE APS_set_field_bus_a_output_plc( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64  AO_Value, I16 RunStep );
I32 FNTYPE APS_get_field_bus_a_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64 *AO_Value );
I32 FNTYPE APS_get_field_bus_a_input( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64 *AI_Value );
I32 FNTYPE APS_get_field_bus_a_input_plc( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64 *AI_Value, I16 RunStep );

//Field bus comparing trigger functions
I32 FNTYPE APS_set_field_bus_trigger_param( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Param_No, I32 Param_Val );
I32 FNTYPE APS_get_field_bus_trigger_param( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Param_No, I32 *Param_Val );
I32 FNTYPE APS_set_field_bus_trigger_linear( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 LCmpCh, I32 StartPoint, I32 RepeatTimes, I32 Interval );
I32 FNTYPE APS_set_field_bus_trigger_table( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 TCmpCh, I32 *DataArr, I32 ArraySize ); 
I32 FNTYPE APS_set_field_bus_trigger_manual( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 TrgCh );
I32 FNTYPE APS_set_field_bus_trigger_manual_s( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 TrgChInBit );
I32 FNTYPE APS_get_field_bus_trigger_table_cmp( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 TCmpCh, I32 *CmpVal );
I32 FNTYPE APS_get_field_bus_trigger_linear_cmp( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 LCmpCh, I32 *CmpVal );
I32 FNTYPE APS_get_field_bus_trigger_count( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 TrgCh, I32 *TrgCnt );
I32 FNTYPE APS_reset_field_bus_trigger_count( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 TrgCh );
I32 FNTYPE APS_get_field_bus_linear_cmp_remain_count( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 LCmpCh, I32 *Cnt );
I32 FNTYPE APS_get_field_bus_table_cmp_remain_count( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 TCmpCh, I32 *Cnt );
I32 FNTYPE APS_get_field_bus_encoder( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 EncCh, I32 *EncCnt );
I32 FNTYPE APS_set_field_bus_encoder( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 EncCh, I32 EncCnt );

// Comparing trigger functions
I32 FNTYPE APS_set_trigger_param( I32 Board_ID, I32 Param_No, I32 Param_Val );
I32 FNTYPE APS_get_trigger_param( I32 Board_ID, I32 Param_No, I32 *Param_Val );
I32 FNTYPE APS_set_trigger_linear( I32 Board_ID, I32 LCmpCh, I32 StartPoint, I32 RepeatTimes, I32 Interval );
I32 FNTYPE APS_set_trigger_table( I32 Board_ID, I32 TCmpCh, I32 *DataArr, I32 ArraySize ); 
I32 FNTYPE APS_set_trigger_manual( I32 Board_ID, I32 TrgCh );
I32 FNTYPE APS_set_trigger_manual_s( I32 Board_ID, I32 TrgChInBit );
I32 FNTYPE APS_get_trigger_table_cmp( I32 Board_ID, I32 TCmpCh, I32 *CmpVal );
I32 FNTYPE APS_get_trigger_linear_cmp( I32 Board_ID, I32 LCmpCh, I32 *CmpVal );
I32 FNTYPE APS_get_trigger_count( I32 Board_ID, I32 TrgCh, I32 *TrgCnt );
I32 FNTYPE APS_reset_trigger_count( I32 Board_ID, I32 TrgCh );
I32 FNTYPE APS_enable_trigger_fifo_cmp( I32 Board_ID, I32 FCmpCh, I32 Enable );
I32 FNTYPE APS_get_trigger_fifo_cmp( I32 Board_ID, I32 FCmpCh, I32 *CmpVal );
I32 FNTYPE APS_get_trigger_fifo_status( I32 Board_ID, I32 FCmpCh, I32 *FifoSts );
I32 FNTYPE APS_set_trigger_fifo_data( I32 Board_ID, I32 FCmpCh, I32 *DataArr, I32 ArraySize, I32 ShiftFlag ); 
I32 FNTYPE APS_set_trigger_encoder_counter( I32 Board_ID, I32 TrgCh, I32 TrgCnt );
I32 FNTYPE APS_get_trigger_encoder_counter( I32 Board_ID, I32 TrgCh, I32 *TrgCnt );
I32 FNTYPE APS_start_timer( I32 Board_ID, I32 TrgCh, I32 Start );
I32 FNTYPE APS_get_timer_counter( I32 Board_ID, I32 TmrCh, I32 *Cnt );
I32 FNTYPE APS_set_timer_counter( I32 Board_ID, I32 TmrCh, I32 Cnt );
I32 FNTYPE APS_start_trigger_timer( I32 Board_ID, I32 TrgCh, I32 Start );
I32 FNTYPE APS_get_trigger_timer_counter( I32 Board_ID, I32 TmrCh, I32 *TmrCnt );

//Multi-dimension comparator functions [For PCI-8254/58]
I32 FNTYPE APS_set_multi_trigger_table( I32 Board_ID, I32 Dimension, MCMP_POINT *DataArr, I32 ArraySize, I32 Window  );
I32 FNTYPE APS_get_multi_trigger_table_cmp( I32 Board_ID, I32 Dimension, MCMP_POINT *CmpVal );

//Pulser counter functions
I32 FNTYPE APS_get_pulser_counter( I32 Board_ID, I32 *Counter );
I32 FNTYPE APS_set_pulser_counter( I32 Board_ID, I32 Counter );

// Reserved functions[Legacy functions]
I32 FNTYPE APS_field_bus_slave_set_param( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, I32 ParaNum, I32 ParaDat  );
I32 FNTYPE APS_field_bus_slave_get_param( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, I32 ParaNum, I32 *ParaDat );

I32 FNTYPE APS_field_bus_d_set_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 DO_Value );
I32 FNTYPE APS_field_bus_d_get_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *DO_Value );
I32 FNTYPE APS_field_bus_d_get_input( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 *DI_Value );

I32 FNTYPE APS_field_bus_A_set_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64  AO_Value );
I32 FNTYPE APS_field_bus_A_set_output_plc( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64  AO_Value, I16 RunStep );
I32 FNTYPE APS_field_bus_A_get_output( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64 *AO_Value );
I32 FNTYPE APS_field_bus_A_get_input( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64 *AI_Value );
I32 FNTYPE APS_field_bus_A_get_input_plc( I32 Board_ID, I32 BUS_No, I32 MOD_No, I32 Ch_No, F64 *AI_Value, I16 RunStep );
I32 FNTYPE APS_get_eep_curr_drv_ctrl_mode( I32 Board_ID, I32 *ModeInBit );

//DPAC functions
I32 FNTYPE APS_rescan_CF( I32 Board_ID );
I32 FNTYPE APS_get_battery_status( I32 Board_ID, I32 *Battery_status);

//DPAC display & Display button
I32 FNTYPE APS_get_display_data( I32 Board_ID, I32 displayDigit, I32 *displayIndex);
I32 FNTYPE APS_set_display_data( I32 Board_ID, I32 displayDigit, I32 displayIndex);
I32 FNTYPE APS_get_button_status( I32 Board_ID, I32 *buttonstatus);

//NV RAM functions
I32 FNTYPE APS_set_nv_ram( I32 Board_ID, I32 RamNo, I32 DataWidth, I32 Offset, I32 Data );
I32 FNTYPE APS_get_nv_ram( I32 Board_ID, I32 RamNo, I32 DataWidth, I32 Offset, I32 *Data );
I32 FNTYPE APS_clear_nv_ram( I32 Board_ID, I32 RamNo );

//VAO functions [For PCI-8253/56]
I32 FNTYPE APS_set_vao_param( I32 Board_ID, I32 Param_No, I32 Param_Val );
I32 FNTYPE APS_get_vao_param( I32 Board_ID, I32 Param_No, I32 *Param_Val );
I32 FNTYPE APS_set_vao_table( I32 Board_ID, I32 Table_No, I32 MinVelocity, I32 VelInterval, I32 TotalPoints, I32 *MappingDataArray );
I32 FNTYPE APS_switch_vao_table( I32 Board_ID, I32 Table_No  );
I32 FNTYPE APS_start_vao( I32 Board_ID, I32 Output_Ch, I32 Enable );
I32 FNTYPE APS_get_vao_status( I32 Board_ID, I32 *Status );
I32 FNTYPE APS_check_vao_param( I32 Board_ID, I32 Table_No, I32 *Status );
I32 FNTYPE APS_set_vao_param_ex( I32 Board_ID, I32 Table_No, VAO_DATA* VaoData );
I32 FNTYPE APS_get_vao_param_ex( I32 Board_ID, I32 Table_No, VAO_DATA* VaoData );

//ODM functions
I32 FNTYPE APS_start_vao_by_mode( I32 Board_ID, I32 ChannelInBit, I32 Mode, I32 Enable );
I32 FNTYPE APS_set_vao_pwm_burst_count( I32 Board_ID, I32 Table_No, I32 Count );

//PWM functions
I32 FNTYPE APS_set_pwm_width( I32 Board_ID, I32 PWM_Ch, I32 Width );
I32 FNTYPE APS_get_pwm_width( I32 Board_ID, I32 PWM_Ch, I32 *Width );
I32 FNTYPE APS_set_pwm_frequency( I32 Board_ID, I32 PWM_Ch, I32 Frequency );
I32 FNTYPE APS_get_pwm_frequency( I32 Board_ID, I32 PWM_Ch, I32 *Frequency );
I32 FNTYPE APS_set_pwm_on( I32 Board_ID, I32 PWM_Ch, I32 PWM_On );

//Simultaneous move
I32 FNTYPE APS_set_relative_simultaneous_move  ( I32 Dimension, I32 *Axis_ID_Array, I32 *Distance_Array, I32 *Max_Speed_Array );
I32 FNTYPE APS_set_absolute_simultaneous_move  ( I32 Dimension, I32 *Axis_ID_Array, I32 *Position_Array, I32 *Max_Speed_Array );
I32 FNTYPE APS_start_simultaneous_move         ( I32 Axis_ID );
I32 FNTYPE APS_stop_simultaneous_move          ( I32 Axis_ID );
I32 FNTYPE APS_set_velocity_simultaneous_move  ( I32 Dimension, I32 *Axis_ID_Array, I32 *Max_Speed_Array ); 
I32 FNTYPE APS_Release_simultaneous_move       ( I32 Axis_ID ); 
I32 FNTYPE APS_release_simultaneous_move       ( I32 Axis_ID );
I32 FNTYPE APS_emg_stop_simultaneous_move      ( I32 Axis_ID ); 

//Override functions
I32 FNTYPE APS_speed_override( I32 Axis_ID, I32 MaxSpeed );
I32 FNTYPE APS_relative_move_ovrd( I32 Axis_ID, I32 Distance, I32 Max_Speed );
I32 FNTYPE APS_absolute_move_ovrd( I32 Axis_ID, I32 Position, I32 Max_Speed );

//Advanced single move & interpolation [For PCI-8254/58]
I32 FNTYPE APS_ptp( I32 Axis_ID, I32 Option, F64 Position, ASYNCALL *Wait);
I32 FNTYPE APS_ptp_v( I32 Axis_ID, I32 Option, F64 Position, F64 Vm, ASYNCALL *Wait);
I32 FNTYPE APS_ptp_all( I32 Axis_ID, I32 Option, F64 Position, F64 Vs,	F64 Vm, F64	Ve, F64 Acc,	F64 Dec, F64 SFac, ASYNCALL *Wait);
I32 FNTYPE APS_vel( I32 Axis_ID, I32 Option, F64 Vm, ASYNCALL *Wait);
I32 FNTYPE APS_vel_all( I32 Axis_ID, I32 Option, F64 Vs, F64 Vm, F64 Ve, F64 Acc,	F64 Dec, F64 SFac, ASYNCALL *Wait);
I32 FNTYPE APS_line( I32 Dimension, I32 *Axis_ID_Array, I32 Option, F64 *PositionArray, F64 *TransPara, ASYNCALL *Wait);
I32 FNTYPE APS_line_v( I32 Dimension, I32 *Axis_ID_Array, I32 Option, F64 *PositionArray, F64 *TransPara, F64 Vm, ASYNCALL *Wait);
I32 FNTYPE APS_line_all( I32 Dimension, I32 *Axis_ID_Array, I32 Option, F64 *PositionArray, F64 *TransPara, F64 Vs, F64 Vm, F64 Ve, F64 Acc,F64 Dec, F64 SFac, ASYNCALL *Wait);
I32 FNTYPE APS_arc2_ca( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 Angle, F64 *TransPara, ASYNCALL *Wait );
I32 FNTYPE APS_arc2_ca_v( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 Angle, F64 *TransPara, F64 Vm, ASYNCALL *Wait );
I32 FNTYPE APS_arc2_ca_all( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 Angle, F64 *TransPara, F64 Vs, F64 Vm, F64 Ve, F64 Acc,F64 Dec, F64 SFac, ASYNCALL *Wait );
I32 FNTYPE APS_arc2_ce( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *EndArray, I16 Dir, F64 *TransPara, ASYNCALL *Wait );
I32 FNTYPE APS_arc2_ce_v( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *EndArray, I16 Dir, F64 *TransPara, F64 Vm, ASYNCALL *Wait );
I32 FNTYPE APS_arc2_ce_all( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *EndArray, I16 Dir, F64 *TransPara, F64 Vs, F64 Vm, F64 Ve, F64 Acc,F64 Dec, F64 SFac, ASYNCALL *Wait );
I32 FNTYPE APS_arc3_ca( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 Angle, F64 *TransPara, ASYNCALL *Wait );
I32 FNTYPE APS_arc3_ca_v( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 Angle, F64 *TransPara, F64 Vm, ASYNCALL *Wait );
I32 FNTYPE APS_arc3_ca_all( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 Angle, F64 *TransPara, F64 Vs, F64 Vm, F64 Ve, F64 Acc,F64 Dec, F64 SFac, ASYNCALL *Wait );
I32 FNTYPE APS_arc3_ce( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *EndArray, I16 Dir, F64 *TransPara, ASYNCALL *Wait );
I32 FNTYPE APS_arc3_ce_v( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *EndArray, I16 Dir, F64 *TransPara, F64 Vm, ASYNCALL *Wait );
I32 FNTYPE APS_arc3_ce_all( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *EndArray, I16 Dir, F64 *TransPara, F64 Vs, F64 Vm, F64 Ve, F64 Acc,F64 Dec, F64 SFac, ASYNCALL *Wait );
I32 FNTYPE APS_spiral_ca( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 Angle, F64 DeltaH, F64 FinalR, F64 *TransPara, ASYNCALL *Wait );
I32 FNTYPE APS_spiral_ca_v( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 Angle, F64 DeltaH, F64 FinalR, F64 *TransPara, F64 Vm, ASYNCALL *Wait );
I32 FNTYPE APS_spiral_ca_all( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 Angle, F64 DeltaH, F64 FinalR, F64 *TransPara, F64 Vs, F64 Vm, F64 Ve, F64 Acc,F64 Dec, F64 SFac, ASYNCALL *Wait );
I32 FNTYPE APS_spiral_ce( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 *EndArray, I16 Dir, F64 *TransPara, ASYNCALL *Wait );
I32 FNTYPE APS_spiral_ce_v( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 *EndArray, I16 Dir, F64 *TransPara, F64 Vm, ASYNCALL *Wait );
I32 FNTYPE APS_spiral_ce_all( I32 *Axis_ID_Array, I32 Option, F64 *CenterArray, F64 *NormalArray, F64 *EndArray, I16 Dir, F64 *TransPara, F64 Vs, F64 Vm, F64 Ve, F64 Acc,F64 Dec, F64 SFac, ASYNCALL *Wait );

//Point table functions [For PCI-8254/58]
I32 FNTYPE APS_pt_dwell( I32 Board_ID, I32 PtbId,  PPTDWL Prof, PPTSTS Status );
I32 FNTYPE APS_pt_line( I32 Board_ID, I32 PtbId,  PPTLINE Prof, PPTSTS Status );
I32 FNTYPE APS_pt_arc2_ca( I32 Board_ID, I32 PtbId, PPTA2CA Prof, PPTSTS Status );
I32 FNTYPE APS_pt_arc2_ce( I32 Board_ID, I32 PtbId, PPTA2CE Prof, PPTSTS Status );
I32 FNTYPE APS_pt_arc3_ca( I32 Board_ID, I32 PtbId, PPTA3CA Prof, PPTSTS Status );
I32 FNTYPE APS_pt_arc3_ce( I32 Board_ID, I32 PtbId, PPTA3CE Prof, PPTSTS Status );
I32 FNTYPE APS_pt_spiral_ca( I32 Board_ID, I32 PtbId, PPTHCA Prof, PPTSTS Status );
I32 FNTYPE APS_pt_spiral_ce( I32 Board_ID, I32 PtbId, PPTHCE Prof, PPTSTS Status );

I32 FNTYPE APS_pt_enable( I32 Board_ID, I32 PtbId, I32 Dimension, I32 *AxisArr );
I32 FNTYPE APS_pt_disable( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_get_pt_info( I32 Board_ID, I32 PtbId, PPTINFO Info );
I32 FNTYPE APS_pt_set_vs( I32 Board_ID, I32 PtbId, F64 Vs );
I32 FNTYPE APS_pt_get_vs( I32 Board_ID, I32 PtbId, F64 *Vs );
I32 FNTYPE APS_pt_start( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_pt_stop( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_get_pt_status( I32 Board_ID, I32 PtbId, PPTSTS Status );
I32 FNTYPE APS_reset_pt_buffer( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_pt_roll_back( I32 Board_ID, I32 PtbId, F64 Max_Speed );
I32 FNTYPE APS_pt_get_error( I32 Board_ID, I32 PtbId, I32 *ErrCode );

//Cmd buffer setting
I32 FNTYPE APS_pt_ext_set_do_ch( I32 Board_ID, I32 PtbId, I32 Channel, I32 OnOff );
I32 FNTYPE APS_pt_ext_set_table_no( I32 Board_ID, I32 PtbId, I32 CtrlNo, I32 TableNo );

//Profile buffer setting
I32 FNTYPE APS_pt_set_absolute( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_pt_set_relative( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_pt_set_trans_buffered( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_pt_set_trans_inp( I32 Board_ID, I32 PtbId );
I32 FNTYPE APS_pt_set_trans_blend_dec( I32 Board_ID, I32 PtbId, F64 Bp );
I32 FNTYPE APS_pt_set_trans_blend_dist( I32 Board_ID, I32 PtbId, F64 Bp );
I32 FNTYPE APS_pt_set_trans_blend_pcnt( I32 Board_ID, I32 PtbId, F64 Bp );
I32 FNTYPE APS_pt_set_acc( I32 Board_ID, I32 PtbId, F64 Acc );
I32 FNTYPE APS_pt_set_dec( I32 Board_ID, I32 PtbId, F64 Dec );
I32 FNTYPE APS_pt_set_acc_dec( I32 Board_ID, I32 PtbId, F64 AccDec );
I32 FNTYPE APS_pt_set_s( I32 Board_ID, I32 PtbId, F64 Sf );
I32 FNTYPE APS_pt_set_vm( I32 Board_ID, I32 PtbId, F64 Vm );
I32 FNTYPE APS_pt_set_ve( I32 Board_ID, I32 PtbId, F64 Ve );

//Program download functions
I32 FNTYPE APS_load_amc_program( I32 Board_ID, I32 TaskNum, const char *pFile, I32 Password);
I32 FNTYPE APS_save_amc_program( I32 Board_ID, I32 TaskNum, const char *pFile, I32 Password);
I32 FNTYPE APS_set_task_mode( I32 Board_ID, I32 TaskNum, U8 Mode, U16 LastIP );
I32 FNTYPE APS_get_task_mode( I32 Board_ID, I32 TaskNum, U8 *Mode, U16 *LastIP );
I32 FNTYPE APS_start_task( I32 Board_ID, I32 TaskNum, I32 CtrlCmd );
I32 FNTYPE APS_get_task_info( I32 Board_ID, I32 TaskNum, TSK_INFO *Info );
I32 FNTYPE APS_get_task_msg( I32 Board_ID, U16 *QueueSts, U16 *ActualSize, U8 *CharArr );

//Latch functions
I32 FNTYPE APS_get_encoder( I32 Axis_ID, I32 *Encoder );
I32 FNTYPE APS_get_latch_counter( I32 Axis_ID, I32 Src, I32 *Counter );
I32 FNTYPE APS_get_latch_event( I32 Axis_ID, I32 Src, I32 *Event );

//Raw command counter [For PCI-8254/58]
I32 FNTYPE APS_get_command_counter( I32 Axis_ID, I32 *Counter );

//Watch dog timer [For PCI-8254/58]
I32 FNTYPE APS_wdt_start( I32 Board_ID, I32 TimerNo, I32 TimeOut );
I32 FNTYPE APS_wdt_get_timeout_period( I32 Board_ID, I32 TimerNo, I32 *TimeOut );
I32 FNTYPE APS_wdt_reset_counter( I32 Board_ID, I32 TimerNo );
I32 FNTYPE APS_wdt_get_counter( I32 Board_ID, I32 TimerNo, I32 *Counter );
I32 FNTYPE APS_wdt_set_action_event( I32 Board_ID, I32 TimerNo, I32 EventByBit );
I32 FNTYPE APS_wdt_get_action_event( I32 Board_ID, I32 TimerNo, I32 *EventByBit );

//Multi-axes simultaneuos move start/stop [For PCI-8254/58]
I32 FNTYPE APS_move_trigger( I32 Dimension, I32 *Axis_ID_Array );
I32 FNTYPE APS_stop_move_multi( I32 Dimension, I32 *Axis_ID_Array );
I32 FNTYPE APS_emg_stop_multi( I32 Dimension, I32 *Axis_ID_Array );

//Gear/Gantry functions [For PCI-8254/58]
I32 FNTYPE APS_start_gear( I32 Axis_ID, I32 Mode );
I32 FNTYPE APS_get_gear_status( I32 Axis_ID, I32* Status );

//Multi-latch functions
I32 FNTYPE APS_set_ltc_counter( I32 Board_ID, I32 CntNum, I32 CntValue );
I32 FNTYPE APS_get_ltc_counter( I32 Board_ID, I32 CntNum, I32 *CntValue );
I32 FNTYPE APS_set_ltc_fifo_param( I32 Board_ID, I32 FLtcCh, I32 Param_No, I32 Param_Val );
I32 FNTYPE APS_get_ltc_fifo_param( I32 Board_ID, I32 FLtcCh, I32 Param_No, I32 *Param_Val );
I32 FNTYPE APS_manual_latch( I32 Board_ID, I32 LatchSignalInBits );
I32 FNTYPE APS_enable_ltc_fifo( I32 Board_ID, I32 FLtcCh, I32 Enable );
I32 FNTYPE APS_reset_ltc_fifo( I32 Board_ID, I32 FLtcCh );
I32 FNTYPE APS_get_ltc_fifo_data( I32 Board_ID, I32 FLtcCh, I32 *Data );
I32 FNTYPE APS_get_ltc_fifo_usage( I32 Board_ID, I32 FLtcCh, I32 *Usage );
I32 FNTYPE APS_get_ltc_fifo_free_space( I32 Board_ID, I32 FLtcCh, I32 *FreeSpace );
I32 FNTYPE APS_get_ltc_fifo_status( I32 Board_ID, I32 FLtcCh, I32 *Status );
I32 FNTYPE APS_get_ltc_fifo_point( I32 Board_ID, I32 FLtcCh, I32 *ArraySize, LATCH_POINT *LatchPoint );

//Single latch functions [For PCI-8154/58, MNET-4XMO-C]
I32 FNTYPE APS_manual_latch2( I32 Axis_ID );
I32 FNTYPE APS_get_latch_data2( I32 Axis_ID, I32 LatchNum, I32 *LatchData );

I32 FNTYPE APS_set_backlash_en(I32 Axis_ID, I32 Enable );
I32 FNTYPE APS_get_backlash_en( I32 Axis_ID, I32 *Enable );

//ODM functions for Mechatrolink
I32 FNTYPE APS_start_mlink( I32 Board_ID, I32 *AxisFound_InBits );
I32 FNTYPE APS_stop_mlink( I32 Board_ID );
I32 FNTYPE APS_set_mlink_servo_param( I32 Axis_ID, I32 Para_No, I32 Para_Dat);
I32 FNTYPE APS_get_mlink_servo_param( I32 Axis_ID, I32 Para_No, I32 *Para_Dat);
I32 FNTYPE APS_config_mlink( I32 Board_ID, I32 TotalAxes, I32* AxesArray);
I32 FNTYPE APS_get_mlink_rv_ptr(I32 Axis_ID, U32 **rptr);
I32 FNTYPE APS_get_mlink_sd_ptr(I32 Axis_ID, U32 **sptr);
I32 FNTYPE APS_get_mlink_servo_alarm( I32 Axis_ID, I32 Alarm_No, I32 *Alarm_Detail );
I32 FNTYPE APS_reset_mlink_servo_alarm( I32 Axis_ID );
I32 FNTYPE APS_set_mlink_pulse_per_rev( I32 Axis_ID, I32 PPR );

//Apply smooth servo off [For PCI-8254/58]
I32 FNTYPE APS_smooth_servo_off(I32 Axis_ID, F64  Decay_Rate );
I32 FNTYPE APS_set_smooth_servo_off(I32 Board_ID, I32 Axis_ID, I32 cnt_Max, I32 *cnt_Err );

//ODM functions
I32 FNTYPE APS_relative_move_wait( I32 Axis_ID, I32 Distance, I32 Max_Speed, I32 Time_Out, I32 Delay_Time, I32 *MotionSts );
I32 FNTYPE APS_absolute_move_wait( I32 Axis_ID, I32 Position, I32 Max_Speed, I32 Time_Out, I32 Delay_Time, I32 *MotionSts );
I32 FNTYPE APS_relative_linear_move_wait( I32 Dimension, I32 *Axis_ID_Array, I32 *Distance_Array, I32 Max_Linear_Speed, I32 Time_Out, I32 Delay_Time, I32 *MotionSts );
I32 FNTYPE APS_absolute_linear_move_wait( I32 Dimension, I32 *Axis_ID_Array, I32 *Position_Array, I32 Max_Linear_Speed, I32 Time_Out, I32 Delay_Time, I32 *MotionSts );
I32 FNTYPE APS_relative_move_non_wait( I32 Axis_ID, I32 Distance, I32 Max_Speed, I32 Time_Out, I32 Delay_Time );
I32 FNTYPE APS_absolute_move_non_wait( I32 Axis_ID, I32 Position, I32 Max_Speed, I32 Time_Out, I32 Delay_Time );
I32 FNTYPE APS_relative_linear_move_non_wait( I32 Dimension, I32 *Axis_ID_Array, I32 *Distance_Array, I32 Max_Linear_Speed, I32 Time_Out, I32 Delay_Time );
I32 FNTYPE APS_absolute_linear_move_non_wait( I32 Dimension, I32 *Axis_ID_Array, I32 *Position_Array, I32 Max_Linear_Speed, I32 Time_Out, I32 Delay_Time );
I32 FNTYPE APS_wait_move_done( I32 Axis_ID, I32 *MotionSts  );

//ODM functions [For MNET-4XMO-C]
I32 FNTYPE APS_absolute_arc_move_ex( I32 Dimension, I32 *Axis_ID_Array, I32 *Center_Pos_Array, I32 *End_Pos_Array, I32 CwOrCcw, I32 Max_Arc_Speed ); 
I32 FNTYPE APS_motion_status_ex( I32 Axis_ID );
I32 FNTYPE APS_motion_io_status_ex( I32 Axis_ID );

//Ring counter functions [For PCI-8154/8]
I32 FNTYPE APS_set_ring_counter( I32 Axis_ID, I32 RingVal );
I32 FNTYPE APS_get_ring_counter( I32 Axis_ID, I32 *RingVal );

//Circular limit functions
I32 FNTYPE APS_set_circular_limit( I32 Axis_A, I32 Axis_B, F64 Center_A, F64 Center_B, F64 Radius, I32 Stop_Mode, I32 Enable );
I32 FNTYPE APS_get_circular_limit( I32 Axis_A, I32 Axis_B, F64 *Center_A, F64 *Center_B, F64 *Radius, I32 *Stop_Mode, I32 *Enable );

//Pulser functions
I32 FNTYPE APS_manual_pulser_start( I32 Board_ID, I32 Enable );
I32 FNTYPE APS_manual_pulser_velocity_move( I32 Axis_ID, F64 SpeedLimit );
I32 FNTYPE APS_manual_pulser_relative_move( I32 Axis_ID, F64 Distance, F64 SpeedLimit );
I32 FNTYPE APS_manual_pulser_home_move( I32 Axis_ID );

//Pitch error compensation [For PCI-8254/58]
I32 FNTYPE APS_set_pitch_table( I32 Axis_ID, I32 Comp_Type, I32 Total_Points, I32 MinPosition, U32 Interval, I32 *Comp_Data);
I32 FNTYPE APS_get_pitch_table( I32 Axis_ID, I32 *Comp_Type, I32 *Total_Points, I32 *MinPosition, U32 *Interval, I32 *Comp_Data);
I32 FNTYPE APS_start_pitch_comp( I32 Axis_ID, I32 Enable );

// PVT function; 
I32 FNTYPE APS_pvt_add_point( I32 Axis_ID, I32 ArraySize, F64 *PositionArray, F64 *VelocityArray, F64 *TimeArray );
I32 FNTYPE APS_pvt_get_status( I32 Axis_ID, I32 *FreeSize, I32 *PointCount, I32 *State );
I32 FNTYPE APS_pvt_start( I32 Dimension, I32 *Axis_ID_Array, I32 Enable );
I32 FNTYPE APS_pvt_reset( I32 Axis_ID );




#ifdef __cplusplus
}
#endif

#endif
