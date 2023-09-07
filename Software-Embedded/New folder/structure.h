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


#include <stdint.h>



//===============GUI structures============
struct MENU_VARIABLES
{
  uint16_t menu_cnt;
  uint16_t operator_view;
  uint16_t operator_set;
  uint16_t supervisor_set;
  uint16_t site_set;
  uint16_t site_sub_set;
  uint16_t factory_set;
  uint8_t min;
  uint8_t max;
};

extern struct MENU_VARIABLES mv;
//===============GUI structures end========

struct CAN_PARA
{
  uint8_t frame_number;
  uint8_t data_buf[10][8];
};

extern struct CAN_PARA cp;


//===============Password structures============
struct USER_PASSWORDS
{
  uint8_t operatr[16];
  uint8_t supervisor[16];
  uint8_t site_engg[16];
  uint8_t factory[16];
};

extern struct USER_PASSWORDS user;
//===============Password structures end========


typedef struct KEYPOLLING
{
    uint16_t duty_ftp:1;
    uint16_t duty:1;
    uint16_t func_ftp:1;
    uint16_t function:1;
    uint16_t inc_ftp:1;
    uint16_t increment:1;
    uint16_t dec_ftp:1;
    uint16_t decrement:1;
    uint16_t entr_ftp:1;
    uint16_t enter:1;
    uint16_t bpk_ftp:1;
    uint16_t bypass:1;
    uint16_t res:4;
}KEYPOLLING;

extern KEYPOLLING key;

//===============Sys para structures============

struct SYS_PARA_BITS
{
  //system status bits
  uint8_t bpk_stat;              //bypass key status
  uint8_t bpk_enable;            //bypass key enable/disable
  uint8_t bpk_det;               //bypass key detection bit, detected or released
  uint8_t hooter_mute_unmute;    //Hooter mute select
  uint8_t hooter_astable;        //Hooter asble multivibrator mode
  uint8_t file_status_bit;       //csv file status
//  uint8_t rigdutyflag;
};

extern struct SYS_PARA_BITS spbit;

//===============Sys para structures============

typedef struct SYS_PARAMETERS
{
    uint32_t bpk_stat_bit:1;
    uint32_t bpk_enable_bit:1;
    uint32_t bpk_method_stat_bit:1;
    uint32_t pw_stat_bit:1;
    uint32_t bmdwn_rly_stat_bit:1;
    uint32_t bmup_rly_stat_bit:1;
    uint32_t hootr_rly_stat_bit:1;
    uint32_t a2b_stat_bit:1;
    uint32_t hk_height_stat_bit:1;
    uint32_t duty_select_stat_bit:1;
    uint32_t snatch_block_stat_bit:1;    
    uint32_t calib_stat_bit:1;
    uint32_t fail_safe_stat_bit:1;
    uint32_t load_avg_stat_bit:1;
    uint32_t perc_fact_stat_bit:1;
    uint32_t rig_duty_bit:1;
    uint32_t peaknhold_stat_bit:1;
    uint32_t art_enable_bit:1;
    uint32_t obtilt_enable_bit:1;    
    uint32_t slave_enable_bit:1;
    uint32_t mpoint_len_enable_bit:1;
    uint32_t frz_load_angl_bit:1;    
    uint32_t res1:10;
    
    uint8_t duty,falls_cnt,sel_uom,default_duty;
    
    uint16_t sp1_perc,sp2_perc;
    uint16_t sp3_perc,sp4_perc;
    int16_t bm_offset,bm_head_offset;
    int16_t bm_tip_offset,main_smpl_cnt;
    uint16_t cal_len_min,cal_len_max;        
    uint16_t cal_len_min_cnt,cal_len_max_cnt;
    uint16_t cal_angle_min,cal_angle_max;        
    uint16_t cal_angle_min_cnt,cal_angle_max_cnt;
    int16_t min_angle,max_angle;
    
    uint16_t hook_load,rig_load_lmt;
    uint16_t rig_bm_angl_lmt,rig_bm_len_lmt;  
    uint32_t engine_number;
    
    uint16_t art_derate_perc,snatch_block_val;
    int16_t low_cutoff_angl,hi_cutoff_angl;
    uint16_t bm_length_min,bm_length_max;    
    uint8_t pressure_p1_chann,pressure_p2_chann,bm_length_chann,bm_angle_chann;
    
    uint16_t low_err_cnt,high_err_cnt;
    uint16_t cal_smpl_cnt,load_corr_factor;
    uint16_t load_corr_limit,load_avg_val;
    int16_t bm_length_corr1,bm_length_corr2;
    int16_t bm_length_corr3,bm_length_corr4;
    int16_t load_corr1,load_corr2;
    int16_t load_corr3,load_corr4;
    int16_t load_corr5,sel_sensor;
    
    uint32_t cust_care_num;
    
    uint16_t calib_pressure1_min,calib_pressure1_max;
    uint16_t calib_P1LowAdcCount,calib_P1HighAdcCount;
    uint16_t calib_pressure2_min,calib_pressure2_max;
    uint16_t calib_P2LowAdcCount,calib_P2HighAdcCount;      //100 size
    
    uint8_t window_sample_size,window_sample_size1,num_of_cylinders,baudrate;    
    uint16_t sticker_type,fact;
    uint16_t correction_load,num_cal;
    
    uint32_t so_number;
    
    uint8_t insta_dd,insta_mm;
    uint16_t insta_yy;
    
    uint16_t Radius_Cutoff,data_log_cntr;              
    
    uint16_t group_duty_s,group_duty_e;
    uint16_t vertical_offset,horizontal_offset;
    uint16_t rampivot_offset,bm_cntr_line_offset;
    uint16_t piston_diameter,rod_diameter;
    uint16_t Select_System,crane_page_index;
    
    uint16_t Tilt1_X_MinAdc,Tilt1_Y_MinAdc;
    uint16_t Tilt2_X_MinAdc,Tilt2_Y_MinAdc;
    
    uint8_t voice_of_language,Front_tilt_Cutoff;
    uint8_t Rear_tilt_Cutoff,Tilt_En_Dis;
    
    uint8_t Set_Audio_Module,Load_fix_Angle,fork_numof_presscal,numof_calib_fork;
    uint16_t Max_BLength,Max_BAngle;
    uint16_t forkcalib_press_min[8][2];     //Pressure value and counts, maximum 8 points
    uint16_t forkcalib_press_max[8][2];
    uint16_t fork_len_region[8];
    
    uint16_t load_threshold,res2;
    uint16_t manbasket_min,manbasket_min_cnt;
    uint16_t manbasket_max,manbasket_max_cnt;
    uint16_t loadcell_cnt_offst,res8;
    uint16_t cal_mangle_min,cal_mangle_max;        
    uint16_t cal_mangle_min_cnt,cal_mangle_max_cnt;
    uint16_t zload_mask,load_announce_timer;
    int16_t slew_offset,bm_ht_offset;
    uint16_t res17,res18;
    uint16_t res19,res20;
    
    uint8_t manbas_duty,manbas_chann,sel_len_drum,fork_duty;
    uint8_t main_ang_chann,numof_len_cal,boom_parts,set_angle_frz_lod;
    uint8_t res29,res30,res31,res32;
    
    uint16_t duty_type[20];
    uint16_t length_array[100];
    int16_t ld_corr_bmup[10];
    uint16_t bl_adc_cnt[8];
    uint16_t bl_fact[6];
    uint8_t indopower_art_derate[12];
    
    uint16_t multipt_lcalib[16][2];
    
    
}SYS_PARAMETERS;

typedef union SYS_PARAMETERS_U
{
    SYS_PARAMETERS para;
    uint8_t buf[sizeof(SYS_PARAMETERS)];
}SYS_PARAMETERS_U;


extern SYS_PARAMETERS_U sys;


#define OUTPUT_ON       1
#define OUTPUT_OFF      2
#define OUTPUT_BLINK    3

typedef struct OP_HANDLE
{
    uint16_t relay1action:2;
    uint16_t redledaction:2;
    uint16_t greenledaction:2;
    uint16_t artledaction:2;
    uint16_t nlzledaction:2;
    uint16_t a2bledaction:2;
    uint16_t errledaction:2;
    uint16_t buzzaction:2;
    
    uint8_t hooteraction:2;
    uint8_t artled_bit:1;
    uint8_t nlzled_bit:1;
    uint8_t a2bled_bit:1;
    uint8_t errled_bit:1;
    uint8_t buzz_bit:1;
    uint8_t over_tilt_bit:1;    
    uint8_t buzztout;
    
    uint8_t artledtout;
    uint8_t nlzledtout;
    uint8_t a2bledtout;
    uint8_t errledtout;
}OP_HANDLE;

extern OP_HANDLE op;

