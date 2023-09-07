
#include "main.h"


struct MENU_VARIABLES mv;
struct SYS_PARA_BITS spbit;
SYS_PARAMETERS_U sys;
KEYPOLLING key;

INCDEC_DATA mi;

uint8_t prv8_val1,prv8_val2;
uint16_t prv16_val1,prv16_val2;
int16_t prv16_sign_val;
uint32_t prv32_val1;


const char len_drum[10][10] = {"20 METERS","25 METERS","36 METERS","48 METERS","60 METERS","10 METERS","48TLON CAN"};
const char sys_sel[15][12] = {"DEFLT PNC ","WHITELINE ","NX-360    ","KNUCK BOOM","PNC MANBAS","FORK-LIFT ","TMC MANB-1","TIL PIXEF ","PNC-FORK  ","TMC MANB-2","TELE RT40 "};
const char sensor_sel[3][10] = {"  Hydac  ","Honeywell","Hydac 12v"};

//ESP32 IOT variables
uint8_t test_mode,spare_in_bit,esp_index,esp_frame_flag,esp_sbyte,load_stat,ui_key,rig_dty_angl_flag,Srdata;
uint16_t onscreen_data_tout,sp_size,sys_err,esp_bpk_tout_min;
uint32_t esp_bpk_tout_ms;
char esp_buf[150],esp_hooter_mute;
char sys_sr_no[10];
//PIC18F25K80 variables
uint8_t u4ready_bit,u4indx,mp3_play_flag;
uint16_t digital_input_status,digital_output_status,pic25k80_tout;
char u4buf[128];

uint8_t menu_absnt_flag,sub_menu_flag,image_flag;
uint16_t tftprv_swl,tftprv_wind,tftprv_jlen,tftprv_mlen,tftprv_jload,tftprv_mload,tftprv_rad,mm_len;
int16_t tftprv_fx,tftprv_rx,tftprv_fy,tftprv_ry,tftprv_mang,tftprv_jang;


uint16_t Main_ang_adc_cnt;
int16_t Knbm_angle;

//Operator variables
//uint8_t duty;
//uint8_t falls_cnt;
//uint8_t uom_cnt;
uint16_t temp_interval_cnt,load_peak_Tout,known_load_pcurve,tower_lamp_can_tout=10000;
//Operator variables end

//Supervisor variables
uint8_t bpk_enable_bit,peakcnt,TempBypassEnbFlag,min_max_pcurve_flag,pcurve_up_dn_flag,por_mp3_flag,tower_lamp_out,can_bpk_state;            //bypass key enable/disable
uint8_t can_frame_cnt,can_buzz_stat;

uint16_t p1_hyst,p2_hyst,p3_hyst,p4_hyst,prv_X_cnts,prv_Y_cnts;
//uint8_t pw_stat_bit;
//uint8_t bmdwn_rly_stat_bit;
//uint8_t bmup_rly_stat_bit;
//uint8_t hootr_rly_stat_bit;
//uint8_t a2b_stat_bit;
//uint8_t hk_height_stat_bit;
//uint8_t duty_select_stat_bit;
//uint8_t snatch_block_enable_bit;   //RollbackStatus
//uint8_t bpk_method_enable_bit;
uint8_t calib_stat_bit,load_ann_timer_case;

//uint16_t sp1_perc;
//uint16_t sp2_perc;
//uint16_t sp3_perc;
//uint16_t sp4_perc;
//
//int16_t bm_offset;                    //Boomoffset
//int16_t bm_head_offset;               //Boomheadoffset
//int16_t bm_tip_offset;                //BoomTipOffset

//uint16_t main_smpl_cnt;
//uint16_t hook_laod;
//uint16_t cal_len_min;                 //LowBmLength
//uint16_t cal_len_min_cnt;
//uint16_t cal_len_max;                 //HighBmLength
//uint16_t cal_len_max_cnt;             //BLHighAdcCount
//uint16_t cal_angle_min;               //LowBmAngle
//uint16_t cal_angle_min_cnt;           //BALowAdcCount
//uint16_t cal_angle_max;               //HighBmAngle
//uint16_t cal_angle_max_cnt;           //BAHighAdcCount
//int16_t min_angle;                   //MinAngle
//uint16_t max_angle;                   //MaxAngle

//uint16_t rig_load_lmt;                //HkLoadLimit
//uint16_t rig_bm_angl_lmt;             //BAValLimit
//uint16_t rig_bm_len_lmt;              //BLValLimit
//uint16_t default_duty;
//uint16_t hook_load;                   //HookLoad
//
//uint32_t engine_number;
//
//uint16_t art_derate_perc;
//
//int16_t low_cutoff_angl;         //BALowCutOffLimit
int16_t temp_low_cutoff_angl;
//uint16_t hi_cutoff_angl;          //BACutOffLimit
//uint16_t snatch_block_val;        //RollbackThreshold
//  uint16_t bpk_method;

//uint16_t super_pw;
//uint16_t site_pw;
//uint16_t factory_pw;
//Supervisor variables end

//Site enggr variables
uint8_t fail_safe_stat_bit,usb_menu_cnt,master_can_sync_tout=200;
int8_t angleX_per,angleY_per;

//uint16_t bm_length_min;               //MinBmLength
//uint16_t bm_length_max;               //MaxBmLength

//uint16_t pressure_p1_chann;
//uint16_t pressure_p2_chann;
//uint16_t bm_length_chann;
//uint16_t bm_angle_chann;

//uint16_t low_err_cnt;                 //LoErrCounts
//uint16_t high_err_cnt;                //HiErrCounts
//uint16_t cal_smpl_cnt;
//uint16_t load_corr_factor;
//uint16_t load_corr_limit;             //LoadCorrLmt
uint16_t length_cnt;
//uint16_t bl_adc_cnt[8];                    //BL_AdcCount

//int16_t bm_length_corr1;                   //LenCorr1 with sign
//int16_t bm_length_corr2;                   //LenCorr2 with sign
//int16_t bm_length_corr3;                   //LenCorr3 with sign
//int16_t bm_length_corr4;                   //LenCorr4 with sign

//int16_t load_corr1;                        //LDCorr with sign
//int16_t load_corr2;                        //LDCorr2 with sign
//int16_t load_corr3;                        //LDCorr3 with sign
//int16_t load_corr4;                        //LDCorr4 with sign
//int16_t load_corr5;                        //LDCorr5 with sign

uint32_t cust_care_num;
//Site enggr variables end

//Factory variables
//uint8_t load_avg_enable_bit;            //BmSpdFlag
//  uint8_t num_of_calib_enable_bit;
//uint8_t percentage_fact_en_bit;               //PercentageFactEn

uint16_t crane_ids[10];

//uint16_t calib_pressure1_min;           //P1MinPress
//uint16_t calib_P1LowAdcCount;           //P1LowAdcCount
//uint16_t calib_pressure1_max;           //P1MaxPress
//uint16_t calib_P1HighAdcCount;          //P1HighAdcCount
//uint16_t calib_pressure2_min;           //P2MinPress
//uint16_t calib_P2LowAdcCount;           //P2LowAdcCount
//uint16_t calib_pressure2_max;           //P2MaxPress
//uint16_t calib_P2HighAdcCount;          //P2HighAdcCount
/*
uint16_t fact_bm_angle_min;
uint16_t fact_bm_angle_max;
uint16_t fact_bm_length_min;
uint16_t fact_bm_length_max;
*/
//uint16_t sel_sensor;
uint8_t sensor_cnt;
//uint16_t load_avg_val;        //BmSpdVal

//uint8_t window_sample_size;   //WindowSizeVal
//uint8_t window_sample_size1;  //WindowSizeVal1
//uint8_t num_of_cylinders;
//uint8_t baudrate;
//uint16_t sticker_type;        //Sticker_Type

//uint16_t fact;                //Fact

//uint16_t correction_load;     //CorrLoad
//uint16_t num_cal;             //NumCal
//uint32_t so_number;

uint8_t insta_dd;
uint8_t insta_mm;
uint16_t insta_yy;
//Factory variables end

//Other variables
const uint32_t baud[3] = {9600,38400,115200};
//const uint32_t baud[3] = {0x00002480,0x00009600,0x0001C200};
char u1buffer[50],u2buffer[50],u3buffer[50];
uint8_t u1indx,u1ready_bit,u2indx,u2ready_bit,u3indx,u3ready_bit,NewCSVFlag,RxStart_flag,DataRxdOver,Page_done,Serial_buff[257];

uint8_t crane_detail_cnt,ART_Table,calib_mode,prv_duty,start_cpy_dty,end_cpy_dty;
uint8_t rig_duty_bit,mute_led_bit,DataLogFlag,DataLogFlagOvrLmt;
uint8_t value_sign_flag,NLZ_Flag,SnatchBlock_Duty;
uint8_t art_ip_bit,art_led_bit,buzzer_bit,ByPassFlag; //ART_IP
uint8_t Radius_Cutoff,LoopCntr;
uint8_t slew_ftd,a2b_ftd,can_msg_stat,a2b_ledblink,art_ledblink,up_dn_dir;
uint8_t common_byte,complimnt_flag;
uint16_t common_short,common_tout,track_change_tout,direction_tout,prv_bm_angle,p1peak,p2peak;
uint32_t common_long;
float common_flot,StartLength;

uint8_t input_stat[20],digi_input[8],a2b_blink_interval,art_blink_interval,err_led_status;

uint16_t can_interval_cnt,Rxcount=0,art_duty_table;
uint16_t bargraph_status,ms_count,bpk_tout,pc_tout=0;

uint16_t data_log_cnt,condition,PercLoad;
uint16_t duty_table,End_duty_table,cntr,CapCalMethodSwitch;
uint16_t hi_cap_angle,cap_angle,AnglePresent,AnglePrevious;
uint16_t LowNlzRad,HighNlzRad,PrevEntryCntr,PrevCntr;

uint8_t second;             //RTC time
uint8_t minute;
uint8_t hour;
uint8_t day;
uint8_t month;
uint16_t year;

uint8_t calsecond;
uint8_t calminute;
uint8_t calhour;
uint8_t calday;
uint8_t calmonth;
uint16_t calyear;

uint16_t crane_id,cursX,cursY,valX,valY,countX;

float PRCHN;
float f1,f2,f3,f11,f12,f13;
float Den_Float,Alpha_Float,Num_Float,RateChange_P2;
float P1Fact,P2Fact,BLFact,BAFact;
float CrtP1_Mtm2_Float,CrtP2_Mtm2_Float;
float P1_Mtm2_Min_Float,P2_Mtm2_Min_Float,P1_Mtm2_Max_Float,P2_Mtm2_Max_Float;
float CalcLoad,SafeLimit,ApproachLimit,CutoffLimit,OverLoadLimit;
float Radius,RAD,CAP,DER_CAP;

double Hook_hight;

uint16_t Radius1,RadPresent,RadPrevious,RadBegin,RadEnd,CapPresent,CapPrevious;
uint16_t Cap1,HookHight,test_tout;

int16_t bm_angle,DispBoomAngle1=0;

uint8_t TempMM1;

uint16_t bm_length,bm_radius,ActualPickingLength;
uint16_t Alpha_Int,Beta_Int,Num_Int,Den_Int;
uint16_t TempDispBoomAngle,BoomLength_BmTip,TotalBmLength,TempDispBoomLength;
uint16_t DispBoomLength1,JibLength;
uint16_t NewP1Reading,BoomSection,BmSection1,TempMM2;
uint16_t mainbyteh,mainbytel;
uint16_t Diff_Force_HK_Min,Diff_Force_HK_Max,Temp12,Temp34;
uint16_t DispLoadVal,frz_DispLoadVal,peakDispLoadVal,DispLoadArr[10];

uint8_t BmSectCntr,SpdCntr,SnatchBlockflag,Cutt_Off_Flag;
uint8_t tilt1X_ok_flag,tilt1Y_ok_flag,tilt2X_ok_flag,tilt2Y_ok_flag;
uint8_t otg_p1_ok_flag,otg_p2_ok_flag,otg_p3_ok_flag,otg_p4_ok_flag,press_chann_num;

uint16_t Gamma_Int_Rad,sin_Gamma_Int,cos_Gamma_Int,constK_Int,DispSinQ,DispCosQ;
uint16_t PistonArea_Int,RodArea_Int,DiffArea_Int;
uint32_t CrtP1_Mtm2_Int,CrtP2_Mtm2_Int,Diff_Force_CRTLD;
uint32_t P1_Mtm2_Min_Int,P2_Mtm2_Min_Int,P1_Mtm2_Max_Int,P2_Mtm2_Max_Int;
uint32_t PressP1_ZrLoad,PressP2_ZrLoad,Diff_Force_Act;

uint16_t p1_pressure_cnt,p1_pressure_avg;              //AbsP1AdcCount
uint16_t p2_pressure_cnt,p2_pressure_avg;              //AbsP2AdcCount
uint16_t can_p1_cnt,can_p2_cnt;
uint16_t can_p3_cnt,can_p4_cnt;
uint16_t can_loadcell_cnt,loadcell_cnt,can_175_tout=5000,can_180_tout=5000,can_201_tout=5000,can_352_tout=5000,can_len_angle_tout=5000,can_p1p2_tout=5000;
uint16_t len_adc_cnt,len_avg_cnt,ht_adc_cnt,can_357_tout=5000,can_358_tout=5000;                  
uint16_t ang_adc_cnt,ang_avg_cnt,knuckl_ang_adc_cnt;                  //Boom angle count
//=====================================================================
//White line variables .........
/*uint16_t Tilt_1_X_cnt,Tilt_1_Y_cnt;              //ADC Count tilt 1  Angle Sensor 
uint16_t Tilt_2_X_cnt,Tilt_2_Y_cnt;              //ADC Count tilt 2  Angle Sensor 
int16_t TiltAngle_1_X,TiltAngle_1_Y;
int16_t TiltAngle_2_X,TiltAngle_2_Y;

uint8_t OTG_status,Dummy_status;*/
//========================================================================
uint16_t vradcntr,vrad,vcapa,total_dty_tables;
uint8_t a2b_stat,AlarmAck,bm_dn_rly_stat,bm_up_rly_stat,hooter_rly_stat;
uint8_t slew_stat,err_led_stat,err_led_timeout,AngleErr,PressErr,LengthErr;

uint16_t adc_buffer[4][32];

uint8_t la_sampl_cnt,p_sampl_cnt,poweron_flag1,poweron_flag2,poweron_flag3,poweron_flag4,FIFO_Cntr1,FIFO_Cntr2,FIFO_Cntr3,FIFO_Cntr4;
uint8_t poweron_flag5,FIFO_Cntr5;
uint16_t len_adc_buf[60],ang_adc_buf[60],knuckl_ang_adc_buf[60],p1_adc_buf[60],p2_adc_buf[60];
uint32_t len_cumulative,angl_cumulative,p1_cumulative,p2_cumulative;

uint16_t duty_type[10],bl_fact[5];
uint16_t len_calib_cnt;               //Num of length calibration points
uint8_t temp_duty_indx;
uint16_t length_array[60];
uint16_t length_array_val;
uint16_t length_array_ptr;
uint8_t len_calib_pt;
uint8_t csv_ref_len;                  //length reference for csv
uint8_t csv_ref_nol;                  //number of lengths
uint8_t angle_calib_pt;

uint16_t p1_pcurve_min_up[100];
uint16_t p2_pcurve_min_up[100];    
uint16_t p1_pcurve_max_up[100];
uint16_t p2_pcurve_max_up[100];

uint16_t p1_pcurve_min_dn[100];
uint16_t p2_pcurve_min_dn[100];    
uint16_t p1_pcurve_max_dn[100];
uint16_t p2_pcurve_max_dn[100];

int16_t temp_bm_len_corr1;
int16_t temp_bm_len_corr2;
int16_t temp_bm_len_corr3;
int16_t temp_bm_len_corr4;
int16_t temp_load_corr1;
int16_t temp_load_corr2;
int16_t temp_load_corr3;
int16_t temp_load_corr4;
int16_t temp_load_corr5;

//  uint16_t pc_total_sectors;
//  uint16_t pc_sector_cnt;
uint16_t pc_sector;
uint16_t pc_sector_quotient;
uint8_t pc_sector_remainder,pc_page;
uint32_t pc_page_addr;
uint16_t pc_buf[2][91];     //pressure curve buffer to save P1 and P2 counts during calibration
uint16_t min_log_angle;
uint16_t max_log_angle;
uint16_t count_step_val_P1;
uint16_t count_step_val_P2;
uint16_t test_cntr;

uint16_t CrtBoomAngle,p1_cnt,p2_cnt;
uint16_t PrevBoomAngle;
uint8_t data_log_arr[91];

uint16_t BAngle[30];

int16_t ld_corr_bmup[10];   //LoadCorrBmUp[10]   signed value

uint16_t data_log_cntr;
uint16_t memory_addr;        //MemoryAddr
uint16_t addr_low;           //AddrLow
uint16_t addr_high;          //AddrHigh
uint8_t addr_low_byte1;      //AddrLowByte1
uint8_t addr_low_byte2;      //AddrLowByte2
uint8_t addr_high_byte1;     //AddrHighByte1
uint8_t addr_high_byte2;     //AddrHighByte2

uint16_t group_duty_s;      //GroupDuty_S
uint16_t group_duty_e;      //GroupDuty_E
uint16_t vertical_offset;   //VerticalOfst
uint16_t horizontal_offset; //HorizontalOfst
uint16_t rampivot_offset;   //RamPivotOfst
uint16_t bm_cntr_line_offset; //BmCntrLineOfst
uint16_t piston_diameter;     //DiaPiston
uint16_t rod_diameter;        //DiaRod

uint16_t lc_max_falls;       //here lc means load chart
uint16_t lc_max_capacity;
uint16_t lc_falls_page_s;
uint16_t lc_duty_cycle_page_s;
uint16_t lc_duty_hint_page_s;
uint16_t lc_duty_hint_page_e;
uint16_t lc_duty_table_page_s;
uint16_t lc_duty_table_page_e;
uint16_t lc_art_table_switch,lc_art_dty_tbl;
uint16_t lc_art_table_page_s;
uint16_t lc_num_of_bm_part;
uint8_t lc_tele_present_switch;
uint8_t lc_pressure_curve_switch;
uint16_t lc_spi_file_id;
uint16_t lc_duty_group_page_s;
uint16_t lc_duty_group_page_e;
uint16_t lc_hk_description_page_s;
uint16_t lc_hk_description_page_e;
int16_t lc_bm_offset;
int16_t temp_bm_offset;
int16_t temp_head_offset;
int16_t temp_tip_offset;
uint16_t lc_total_duty;
uint16_t lc_default_duty;
uint16_t lc_press_curve_page_s;
uint16_t lc_press_curve_page_e;
uint16_t lc_bm_length_min;
uint16_t lc_bm_length_max;
uint16_t lc_vert_offset;
uint16_t lc_horiz_offset;
uint16_t lc_rampivo_offset;
uint16_t lc_bmcntrline_offset;
uint16_t lc_piston_diameter;
uint16_t lc_rod_diameter;
uint16_t lc_vertical_dist;
uint16_t lc_idex_page_s;
char crane_make[20];
char crane_model[20];
char crane_type[20];
char csv_name[33];
uint8_t csv_dd,csv_mm,csv_hh,csv_mn,csv_ss;
uint16_t csv_yy;
uint32_t lc_csv_id,flash_page_addr,flash_memory_offset,load_ann_tout;

uint16_t ms_delay_cnt;
uint16_t disp_refresh_cnt,hint_refresh_cnt;
uint16_t menu_stat,prv_key,pos_t=0;
uint8_t byt1=0,byt2=0,byt3=0,byt4=0,byt5=0,byt6=0,byt7=0,byt8=0,byt9=0,byt10=0,disp_error=0,dpoint;
char gbuf[100];


//NX360
uint16_t BACount_CAN,BLCount_CAN,P1Count_CAN,P2Count_CAN;
uint8_t  CAN_ERROR_LenAngA2B,CAN_ERROR_P1_P2_SLEW,A2B_CAN,Slew_CAN;
uint8_t SlewMode;





