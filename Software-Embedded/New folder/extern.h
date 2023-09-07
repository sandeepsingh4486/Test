/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */



#endif	/* XC_HEADER_TEMPLATE_H */

//extern INCDEC_DATA miv;    //Modify Integer Value


extern uint8_t menu_absnt_flag,sub_menu_flag,image_flag;
extern uint16_t tftprv_swl,tftprv_wind,tftprv_jlen,tftprv_mlen,tftprv_jload,tftprv_mload,tftprv_rad,mm_len;
extern int16_t tftprv_fx,tftprv_rx,tftprv_fy,tftprv_ry,tftprv_jang,tftprv_mang;

extern char gbuf[100];
extern uint8_t rx_data[8],tx_data[8];
extern const char sys_sel[15][12];
extern const char len_drum[10][10];
extern const char sensor_sel[3][10];
//extern far uint8_t page[256];

//ESP32 IOT variables
extern uint8_t test_mode,spare_in_bit,esp_index,esp_frame_flag,esp_sbyte,load_stat;
extern uint16_t onscreen_data_tout,sp_size,sys_err,esp_bpk_tout_min;
extern uint32_t esp_bpk_tout_ms;
extern char esp_buf[150],esp_hooter_mute;
extern char sys_sr_no[10];

//PIC18F25K80 variables
extern uint8_t u4ready_bit,u4indx,mp3_play_flag,Srdata;
extern uint16_t digital_input_status,digital_output_status,pic25k80_tout;
extern char u4buf[128];
//==================GUI variables======================
extern uint8_t ui_key,led_status,err_led_stat,err_led_timeout,AngleErr,PressErr,LengthErr,_3TimeValue,_3TimeFlag,master_can_sync_tout,rig_dty_angl_flag;
extern volatile uint8_t Current_Track,Previous_Track;
extern uint8_t prv8_val1,prv8_val2,otg_once_flag,height_once_flag,load_once_flag,min_max_pcurve_flag,pcurve_up_dn_flag,por_mp3_flag;
extern uint8_t tower_lamp_out,can_bpk_state,can_frame_cnt,can_buzz_stat;
extern int8_t angleX_per,angleY_per;
extern uint16_t menu_stat,prv16_val1,prv16_val2,pos_t;
extern uint8_t byt1,byt2,byt3,byt4,byt5,byt6,byt7,byt8,byt9,byt10;
extern uint32_t prv32_val1;
extern int16_t prv16_sign_val;
extern const uint32_t baud[3];

extern uint16_t disp_refresh_cnt,hint_refresh_cnt,bar_status,tower_lamp_can_tout;
extern uint16_t p1_hyst,p2_hyst,p3_hyst,p4_hyst,prv_X_cnts,prv_Y_cnts;

//Operator variables
extern uint8_t duty;
extern uint8_t falls_cnt;
extern uint8_t uom_cnt;
extern uint16_t temp_interval_cnt,load_peak_Tout,known_load_pcurve;
//extern uint8_t  sys_sr_no[6];
//Operator variables end

//Supervisor variables
extern uint8_t bpk_enable_bit,peakcnt,TempBypassEnbFlag;            //bypass key enable/disable
extern uint8_t pw_stat_bit;
extern uint8_t bmdwn_rly_stat_bit;
extern uint8_t bmup_rly_stat_bit;
extern uint8_t hootr_rly_stat_bit;
extern uint8_t a2b_stat_bit;
extern uint8_t hk_height_stat_bit;
extern uint8_t duty_select_stat_bit;
extern uint8_t snatch_block_enable_bit;   //RollbackStatus
extern uint8_t bpk_method_enable_bit;
extern uint8_t calib_stat_bit,load_ann_timer_case;

extern uint16_t sp1_perc,sp2_perc,sp3_perc,sp4_perc;

extern int16_t bm_offset;                    //Boom offset
extern int16_t bm_head_offset;               //Boom head offset

extern int16_t bm_tip_offset;

extern uint16_t main_smpl_cnt;
extern uint16_t hook_laod;
extern uint16_t cal_len_min;                 //LowBmLength
extern uint16_t cal_len_min_cnt;
extern uint16_t cal_len_max;                 //HighBmLength
extern uint16_t cal_len_max_cnt;             //BLHighAdcCount
extern uint16_t cal_angle_min;               //LowBmAngle
extern uint16_t cal_angle_min_cnt;           //BALowAdcCount
extern uint16_t cal_angle_max;               //HighBmAngle
extern uint16_t cal_angle_max_cnt;           //BAHighAdcCount
extern int16_t min_angle;                   //MinAngle
extern uint16_t max_angle;                   //MaxAngle

extern uint16_t rig_load_lmt;                //Hook load limit(HkLoadLimit)
extern uint16_t rig_bm_angl_lmt;             //Boom angle limit
extern uint16_t rig_bm_len_lmt;              //Boom length limit
extern uint16_t default_duty;
extern uint16_t hook_load;                   //HookLoad

extern uint32_t engine_number;

extern uint16_t art_derate_perc;

extern int16_t low_cutoff_angl;         //BALowCutOffLimit
extern int16_t temp_low_cutoff_angl;
extern uint16_t hi_cutoff_angl;          //BACutOffLimit
extern uint16_t snatch_block_val;        //RollbackThreshold
//  uint16_t bpk_method;

extern uint16_t super_pw;
extern uint16_t site_pw;
extern uint16_t factory_pw;
//Supervisor variables end

//Site enggr variables
extern uint8_t fail_safe_stat_bit,usb_menu_cnt;

extern uint16_t bm_length_min;               //MinBmLength
extern uint16_t bm_length_max;               //MaxBmLength

extern uint16_t pressure_p1_chann;
extern uint16_t pressure_p2_chann;
extern uint16_t bm_length_chann;
extern uint16_t bm_angle_chann,main_ang_chann;      //

extern uint16_t low_err_cnt;                 //LoErrCounts
extern uint16_t high_err_cnt;                //HiErrCounts
extern uint16_t cal_smpl_cnt;
extern uint16_t load_corr_factor;
extern uint16_t load_corr_limit;             //LoadCorrLmt
extern uint16_t length_cnt;
extern uint16_t bl_adc_cnt[8];                    //BL_AdcCount

extern int16_t bm_length_corr1;                   //LenCorr1 with sign
extern int16_t bm_length_corr2;                   //LenCorr2 with sign
extern int16_t bm_length_corr3;                   //LenCorr3 with sign
extern int16_t bm_length_corr4;                   //LenCorr4 with sign

extern int16_t load_corr1;                        //LDCorr with sign
extern int16_t load_corr2;                        //LDCorr2 with sign
extern int16_t load_corr3;                        //LDCorr3 with sign
extern int16_t load_corr4;                        //LDCorr4 with sign
extern int16_t load_corr5;                        //LDCorr5 with sign

extern uint32_t cust_care_num;
//Site enggr variables end

//Factory variables
extern uint8_t load_avg_enable_bit;            //BmSpdFlag
//  uint8_t num_of_calib_enable_bit;
extern uint8_t percentage_fact_en_bit;               //PercentageFactEn

extern uint16_t crane_ids[10];

extern uint16_t calib_pressure1_min;           //P1MinPress
extern uint16_t calib_P1LowAdcCount;           //P1LowAdcCount
extern uint16_t calib_pressure1_max;           //P1MaxPress
extern uint16_t calib_P1HighAdcCount;          //P1HighAdcCount
extern uint16_t calib_pressure2_min;           //P2MinPress
extern uint16_t calib_P2LowAdcCount;           //P2LowAdcCount
extern uint16_t calib_pressure2_max;           //P2MaxPress
extern uint16_t calib_P2HighAdcCount;          //P2HighAdcCount
/*
uint16_t fact_bm_angle_min;
uint16_t fact_bm_angle_max;
uint16_t fact_bm_length_min;
uint16_t fact_bm_length_max;
*/
extern uint16_t sel_sensor;
extern uint8_t sensor_cnt;
extern uint16_t load_avg_val;        //BmSpdVal

extern uint8_t window_sample_size;   //WindowSizeVal
extern uint8_t window_sample_size1;  //WindowSizeVal1
extern uint8_t num_of_cylinders;
extern uint8_t baudrate;
extern uint16_t sticker_type;        //Sticker_Type

extern uint16_t fact;                //Fact

extern uint16_t correction_load;     //CorrLoad
extern uint16_t num_cal;             //NumCal
extern uint32_t so_number;

extern uint8_t insta_dd;
extern uint8_t insta_mm;
extern uint16_t insta_yy;
//Factory variables end

//Other variables
extern char u1buffer[50],u2buffer[50],u3buffer[50];
extern uint8_t u1indx,u1ready_bit,u2indx,u2ready_bit,u3indx,u3ready_bit,NewCSVFlag,RxStart_flag,DataRxdOver,Page_done,Serial_buff[257];

extern uint8_t crane_detail_cnt,ART_Table,calib_mode,prv_duty,start_cpy_dty,end_cpy_dty;
extern uint8_t rig_duty_bit,mute_led_bit,DataLogFlag,DataLogFlagOvrLmt;
extern uint8_t value_sign_flag,NLZ_Flag,SnatchBlock_Duty;
extern uint8_t art_ip_bit,art_led_bit,buzzer_bit,ByPassFlag;
extern uint8_t Radius_Cutoff,LoopCntr;
extern uint8_t slew_ftd,a2b_ftd,all_keys_released,can_msg_stat,a2b_ledblink,art_ledblink,err_led_status,up_dn_dir;
extern uint8_t common_byte,complimnt_flag;
extern uint16_t common_short,common_tout,track_change_tout,direction_tout,prv_bm_angle,p1peak,p2peak;
extern uint32_t common_long;
extern float common_flot,StartLength;

extern uint16_t can_interval_cnt,Rxcount,art_duty_table,bargraph_status,ms_count,bpk_tout,pc_tout;

extern uint16_t data_log_cnt,condition,PercLoad;
extern uint16_t duty_table,End_duty_table,cntr,CapCalMethodSwitch;
extern uint16_t hi_cap_angle,cap_angle,AnglePresent,AnglePrevious;
extern uint16_t LowNlzRad,HighNlzRad,PrevEntryCntr,PrevCntr;

extern uint8_t input_stat[20],digi_input[8],a2b_blink_interval,art_blink_interval;

extern uint8_t second;             //RTC time
extern uint8_t minute;
extern uint8_t hour;
extern uint8_t day;
extern uint8_t month;
extern uint16_t year;

extern uint8_t calsecond;
extern uint8_t calminute;
extern uint8_t calhour;
extern uint8_t calday;
extern uint8_t calmonth;
extern uint16_t calyear;

extern uint16_t crane_id,cursX,cursY,valX,valY,countX;

extern float PRCHN;
extern float f1,f2,f3,f11,f12,f13;
extern float Den_Float,Alpha_Float,Num_Float,RateChange_P2;
extern float P1Fact,P2Fact,BLFact,BAFact,LENGTH_FLOAT;
extern float CrtP1_Mtm2_Float,CrtP2_Mtm2_Float;
extern float P1_Mtm2_Min_Float,P2_Mtm2_Min_Float,P1_Mtm2_Max_Float,P2_Mtm2_Max_Float;
extern float CalcLoad,SafeLimit,ApproachLimit,CutoffLimit,OverLoadLimit;
extern float  Radius,RAD,CAP,DER_CAP;

extern double Hook_hight;

extern uint16_t Radius1,RadPresent,RadPrevious,RadBegin,RadEnd,CapPresent,CapPrevious;
extern uint16_t Cap1,HookHight,test_tout;;

extern int16_t bm_angle,DispBoomAngle1;

extern uint8_t TempMM1;
extern uint16_t bm_length,bm_radius,swl_capa,ActualPickingLength;
extern uint16_t Alpha_Int,Beta_Int,Num_Int,Den_Int;
extern uint16_t TempDispBoomAngle,BoomLength_BmTip,TotalBmLength,TempDispBoomLength;
extern uint16_t DispBoomLength1,JibLength;
extern uint16_t NewP1Reading,BoomSection,BmSection1,TempMM2;
extern uint16_t mainbyteh,mainbytel;
extern uint16_t Diff_Force_HK_Min,Diff_Force_HK_Max,Temp12,Temp34;
extern uint16_t DispLoadVal,frz_DispLoadVal,peakDispLoadVal,DispLoadArr[10];

extern uint8_t BmSectCntr,SpdCntr,SnatchBlockflag,Cutt_Off_Flag,dpoint;
extern uint8_t tilt1X_ok_flag,tilt1Y_ok_flag,tilt2X_ok_flag,tilt2Y_ok_flag;
extern uint8_t otg_p1_ok_flag,otg_p2_ok_flag,otg_p3_ok_flag,otg_p4_ok_flag,press_chann_num;

extern uint16_t Gamma_Int_Rad,sin_Gamma_Int,cos_Gamma_Int,constK_Int,DispSinQ,DispCosQ;
extern uint16_t PistonArea_Int,RodArea_Int,DiffArea_Int;
extern uint32_t CrtP1_Mtm2_Int,CrtP2_Mtm2_Int,Diff_Force_CRTLD;
extern uint32_t P1_Mtm2_Min_Int,P2_Mtm2_Min_Int,P1_Mtm2_Max_Int,P2_Mtm2_Max_Int;
extern uint32_t PressP1_ZrLoad,PressP2_ZrLoad,Diff_Force_Act;

extern uint16_t p1_pressure_cnt,p1_pressure_avg;              //AbsP1AdcCount
extern uint16_t p2_pressure_cnt,p2_pressure_avg;              //AbsP2AdcCount
extern uint16_t can_p1_cnt,can_p2_cnt;
extern uint16_t can_p3_cnt,can_p4_cnt;
extern uint16_t can_loadcell_cnt,loadcell_cnt,can_175_tout,can_180_tout,can_201_tout,can_352_tout,can_len_angle_tout,can_p1p2_tout;
extern uint16_t len_adc_cnt,len_avg_cnt,ht_adc_cnt,can_357_tout,can_358_tout;                  //Boom length count
extern uint16_t ang_adc_cnt,ang_avg_cnt;                  //Boom angle count
//whiteline..........................
/*extern uint16_t Tilt_1_X_cnt,Tilt_1_Y_cnt;              //
extern uint16_t Tilt_2_X_cnt,Tilt_2_Y_cnt; 
extern uint8_t OTG_status,Dummy_status;
extern int16_t TiltAngle_1_X,TiltAngle_1_Y;
extern int16_t TiltAngle_2_X,TiltAngle_2_Y;*/

//==============================================
extern uint16_t vradcntr,vrad,vcapa,total_dty_tables;
extern uint8_t a2b_stat,AlarmAck,bm_dn_rly_stat,bm_up_rly_stat,hooter_rly_stat;
extern uint8_t slew_stat,disp_error;

extern uint8_t la_sampl_cnt,p_sampl_cnt,poweron_flag1,poweron_flag2,poweron_flag3,poweron_flag4,FIFO_Cntr1,FIFO_Cntr2,FIFO_Cntr3,FIFO_Cntr4;
extern uint8_t poweron_flag5,FIFO_Cntr5;
extern uint16_t len_adc_buf[60],ang_adc_buf[60],knuckl_ang_adc_buf[60],p1_adc_buf[60],p2_adc_buf[60];
extern uint32_t len_cumulative,angl_cumulative,p1_cumulative,p2_cumulative;

extern uint16_t duty_type[10],bl_fact[5];
extern uint16_t len_calib_cnt;               //Num of length calibration points
extern uint8_t temp_duty_indx;
extern uint16_t length_array[60];
extern uint16_t length_array_val;
extern uint16_t length_array_ptr;
extern uint8_t len_calib_pt;
extern uint8_t csv_ref_len;                  //length reference for csv
extern uint8_t csv_ref_nol;                  //number of lengths
extern uint8_t angle_calib_pt;

extern uint16_t p1_pcurve_min_up[100];
extern uint16_t p2_pcurve_min_up[100];    
extern uint16_t p1_pcurve_max_up[100];
extern uint16_t p2_pcurve_max_up[100];

extern uint16_t p1_pcurve_min_dn[100];
extern uint16_t p2_pcurve_min_dn[100];    
extern uint16_t p1_pcurve_max_dn[100];
extern uint16_t p2_pcurve_max_dn[100];

extern int16_t temp_bm_len_corr1;
extern int16_t temp_bm_len_corr2;
extern int16_t temp_bm_len_corr3;
extern int16_t temp_bm_len_corr4;
extern int16_t temp_load_corr1;
extern int16_t temp_load_corr2;
extern int16_t temp_load_corr3;
extern int16_t temp_load_corr4;
extern int16_t temp_load_corr5;

//  uint16_t pc_total_sectors;
//  uint16_t pc_sector_cnt;
extern uint16_t pc_sector;
extern uint16_t pc_sector_quotient;
extern uint8_t pc_sector_remainder,pc_page;
extern uint32_t pc_page_addr;
extern uint16_t pc_buf[2][91];     //pressure curve buffer to save P1 and P2 counts during calibration
extern uint16_t min_log_angle;
extern uint16_t max_log_angle;
extern uint16_t count_step_val_P1;
extern uint16_t count_step_val_P2;
extern uint16_t test_cntr;

extern uint16_t CrtBoomAngle,p1_cnt,p2_cnt;
extern uint16_t PrevBoomAngle;
extern uint8_t data_log_arr[91];

extern uint16_t BAngle[30];

extern int16_t ld_corr_bmup[10];   //LoadCorrBmUp[10]   signed value

extern uint16_t data_log_cntr;
extern uint16_t memory_addr;        //MemoryAddr
extern uint16_t addr_low;           //AddrLow
extern uint16_t addr_high;          //AddrHigh
extern uint8_t addr_low_byte1;      //AddrLowByte1
extern uint8_t addr_low_byte2;      //AddrLowByte2
extern uint8_t addr_high_byte1;     //AddrHighByte1
extern uint8_t addr_high_byte2;     //AddrHighByte2

extern uint16_t group_duty_s;      //GroupDuty_S
extern uint16_t group_duty_e;      //GroupDuty_E
extern uint16_t vertical_offset;   //VerticalOfst
extern uint16_t horizontal_offset; //HorizontalOfst
extern uint16_t rampivot_offset;   //RamPivotOfst
extern uint16_t bm_cntr_line_offset; //BmCntrLineOfst
extern uint16_t piston_diameter;     //DiaPiston
extern uint16_t rod_diameter;        //DiaRod

extern uint16_t lc_max_falls;       //here lc means load chart
extern uint16_t lc_max_capacity;
extern uint16_t lc_falls_page_s;
extern uint16_t lc_duty_cycle_page_s;
extern uint16_t lc_duty_hint_page_s;
extern uint16_t lc_duty_hint_page_e;
extern uint16_t lc_duty_table_page_s;
extern uint16_t lc_duty_table_page_e;
extern uint16_t lc_art_table_switch,lc_art_dty_tbl;
extern uint16_t lc_art_table_page_s;
extern uint16_t lc_num_of_bm_part;
extern uint8_t lc_tele_present_switch;
extern uint8_t lc_pressure_curve_switch;
extern uint16_t lc_spi_file_id;
extern uint16_t lc_duty_group_page_s;
extern uint16_t lc_duty_group_page_e;
extern uint16_t lc_hk_description_page_s;
extern uint16_t lc_hk_description_page_e;
extern int16_t lc_bm_offset;
extern int16_t temp_bm_offset;
extern int16_t temp_head_offset;
extern int16_t temp_tip_offset;
extern uint16_t lc_total_duty;
extern uint16_t lc_default_duty;
extern uint16_t lc_press_curve_page_s;
extern uint16_t lc_press_curve_page_e;
extern uint16_t lc_bm_length_min;
extern uint16_t lc_bm_length_max;
extern uint16_t lc_vert_offset;
extern uint16_t lc_horiz_offset;
extern uint16_t lc_rampivo_offset;
extern uint16_t lc_bmcntrline_offset;
extern uint16_t lc_piston_diameter;
extern uint16_t lc_rod_diameter;
extern uint16_t lc_vertical_dist;
extern uint16_t lc_idex_page_s;
extern char crane_make[20];
extern char crane_model[20];
extern char crane_type[20];
extern char csv_name[33];
extern uint8_t csv_dd,csv_mm,csv_hh,csv_mn,csv_ss;
extern uint16_t csv_yy;
extern uint32_t lc_csv_id,flash_page_addr,flash_memory_offset,load_ann_tout;

extern const float cosangle1[901];

extern    uint16_t temp_Tilt1X;
extern    uint16_t temp_Tilt1Y;
extern    uint16_t temp_Tilt2X;
extern    uint16_t temp_Tilt2Y;

extern uint32_t Track_Counter;
//extern uint8_t OTG_ip_bit;
extern uint8_t Start_Loop,Track_Flag;
//whiteline..........................
extern uint16_t Tilt_1_X_cnt,Tilt_1_Y_cnt;              //
extern uint16_t Tilt_2_X_cnt,Tilt_2_Y_cnt; 
extern uint16_t Tele_Counter;

extern volatile uint8_t OTG_status,Dummy_status;
extern int16_t TiltAngle_1_X,TiltAngle_1_Y;
extern int16_t TiltAngle_2_X,TiltAngle_2_Y;
extern uint8_t _3TimeValue,_3TimeFlag;
extern uint8_t TxdBuff[50];
extern const char Voice_Language[3][13];


extern uint16_t BACount_CAN,BLCount_CAN,P1Count_CAN,P2Count_CAN;
extern uint8_t CAN_ERROR_LenAngA2B,CAN_ERROR_P1_P2_SLEW,A2B_CAN,Slew_CAN;
extern uint8_t SlewMode;


extern uint16_t Main_ang_adc_cnt;
extern int16_t Knbm_angle;





