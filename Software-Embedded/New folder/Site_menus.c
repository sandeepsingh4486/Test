/*
        Created by                      :        Santosh Katke
        Date                            :        04 Nov T20.
        Software Version                :        v1.0
        Note                            :        This is the source file for GUI menus.
        MicroController                 :        dsPIC33EP512MU810
        Operation Frequency (Crystal)   :        XT oscillator (8MHz) with PLL-140MHz
        Interface                       :        NA.
        Software IDE                    :        MicroC Pro for dsPIC IDE
        Software IDE Version            :        v7.1.0
        Compiler                        :        MicroC
        Compiler Version                :        v7.1.0
        OS                              :        FreeRTOS v9.0.0

Description:
  Task to handle GUI.

//============================================================================

Version 1.0 is used as a major milestone, indicating that the software is "complete",
that it has all major features, and is considered reliable enough for general release.

Any minor change in code , increment right side number after decimal point.

Any major change in code , increment Left side number before decimal point.

//============================================================================
Special Notes if any:


Pin details: NA

//============================================================================
Version History
//============================================================================
S.Ver: 01.00        Date: 100220
//============================================================================
Functions effected                        :
Problem description                        :

Current Status                                 :
Keyword to search                         :
//============================================================================
List of Functions used :
   Gui_Task()
   ADC1_Get_Sample()
   ECAN1Write()
   UART1_String()
   WordToStr()
   vTaskDelay()

//============================================================================
Naming Procedure:

All variables to be defined as [ "datatype"_Variable name] in lowercase
For Function naming First Character of each word to be in Capital [ Transmit_Data]
For Macros naming All Character of each word to be in Capital [ TRANSMIT_DATA]

==============================================================================
*/
#include "main.h"

/*============================================================================*/
/*
 * Function      :        Display_Site_Set_Menu.
 * Description   :        Used to display site enggr's setting menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Site_Set_Menu(void)
{
  mv.max = 31;
  mv.min = 1;

  Lcd16x2_Cmd(LCD_CLEAR);

  Select_Site_Set_Menu();
}

/*============================================================================*/
/*
 * Function      :        Select_Site_Set_Menu.
 * Description   :        Used to select site setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Select_Site_Set_Menu(void)
{
  char lbuf[20];

  sprintf(lbuf,"SET CODE: %03d   ",mv.site_set+199);
  Lcd16x2_Out(1,1,lbuf);

  switch(mv.site_set)
  {
    case MIN_BOOM_LEGTH:
    Lcd16x2_Out(2,1,"MIN BOOM LEGTH: ");
    prv16_val1 = sys.para.bm_length_min;
    break;
    case MAX_BOOM_LEGTH:
    Lcd16x2_Out(2,1,"MAX BOOM LEGTH: ");
    prv16_val1 = sys.para.bm_length_max;
    break;
    case SET_PRESS_P1_CHANNEL:
    Lcd16x2_Out(2,1,"SET PRESS P1 CHN");
    prv16_val1 = sys.para.pressure_p1_chann;
    break;
    case SET_PRESS_P2_CHANNEL:
    Lcd16x2_Out(2,1,"SET PRESS P2 CHN");
    prv16_val1 = sys.para.pressure_p2_chann;
    break;
    case SET_LENGTH_CHANNEL:
    Lcd16x2_Out(2,1,"SET LENGTH CHN: ");
    prv16_val1 = sys.para.bm_length_chann;
    break;
    case SET_ANGLE_CHANNEL:
    if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
        Lcd16x2_Out(2,1,"SET KNUC ANG CHN");
    else
        Lcd16x2_Out(2,1,"SET BOOM ANG CHN");
    prv16_val1 = sys.para.bm_angle_chann;
    break;
    case SET_MANGLE_CHANNEL:
    Lcd16x2_Out(2,1,"SET MAIN ANG CHN");
    prv16_val1 = sys.para.main_ang_chann;
    break;
    case SET_LOW_ERR_COUNT:
    Lcd16x2_Out(2,1,"SET LOW ERR CNT:");
    prv16_val1 = sys.para.low_err_cnt;
    break;
    case SET_HIGH_ERR_COUNT:
    Lcd16x2_Out(2,1,"SET HI ERR CNT: ");
    prv16_val1 = sys.para.high_err_cnt;
    break;
    case SET_CAL_SAMPLE_COUNT:
    Lcd16x2_Out(2,1,"SET CAL SMPL CNT");
    prv16_val1 = sys.para.cal_smpl_cnt;
    break;
    case LOAD_CORR_FACTOR:
    Lcd16x2_Out(2,1,"LOAD CORR FACTOR");
    prv16_val1 = sys.para.load_corr_factor;
    break;
    case LOAD_CORR_LIMIT:
    Lcd16x2_Out(2,1,"LOAD CORR LIMIT:");
    prv16_val1 = sys.para.load_corr_limit;
    break;
    case COPY_ZERO_CALIB:
    Lcd16x2_Out(2,1,"COPY ZERO CALIB:");

    break;
    case SET_DATE_TIME: //calibration date and time
    Lcd16x2_Out(2,1,"SET DATE & TIME:");
    break;
    case EDIT_LENGTH_COUNT:
    Lcd16x2_Out(2,1,"EDIT LENGTH CNT:");
    prv16_val1 = length_cnt;
    break;
    case BM_LENGTH_CORR_1:
    Lcd16x2_Out(2,1,"BM_LENGTH_CORR_1");
    temp_bm_len_corr1 = sys.para.bm_length_corr1;
    prv16_sign_val = sys.para.bm_length_corr1;
    break;
    case BM_LENGTH_CORR_2:
    Lcd16x2_Out(2,1,"BM_LENGTH_CORR_2");
    temp_bm_len_corr2 = sys.para.bm_length_corr2;
    prv16_sign_val = sys.para.bm_length_corr2;
    break;
    case BM_LENGTH_CORR_3:
    Lcd16x2_Out(2,1,"BM_LENGTH_CORR_3");
    temp_bm_len_corr3 = sys.para.bm_length_corr3;
    prv16_sign_val = sys.para.bm_length_corr3;
    break;
    case BM_LENGTH_CORR_4:
    Lcd16x2_Out(2,1,"BM_LENGTH_CORR_4");
    temp_bm_len_corr4 = sys.para.bm_length_corr4;
    prv16_sign_val = sys.para.bm_length_corr4;
    break;
    case FAIL_SAFE_STATUS_CASE:
    Lcd16x2_Out(2,1,"FAIL SAFE STATUS");
    prv8_val1 = sys.para.fail_safe_stat_bit;
    break;
    case LOAD_CORR_1:
    if(sys.para.Select_System == TIL_PIXEF_TELE_PNC)
        Lcd16x2_Out(2,1,"LD_CORR(0.2-2T) ");
    else
        Lcd16x2_Out(2,1,"LD_CORR(0.6-2T) ");
    temp_load_corr1 = sys.para.load_corr1;
    prv16_sign_val = sys.para.load_corr1;
    break;
    case LOAD_CORR_2:
    Lcd16x2_Out(2,1,"LD_CORR(2-4T)   ");
    temp_load_corr2 = sys.para.load_corr2;
    prv16_sign_val = sys.para.load_corr2;
    break;
    case LOAD_CORR_3:
    Lcd16x2_Out(2,1,"LD_CORR(4-9T)   ");
    temp_load_corr3 = sys.para.load_corr3;
    prv16_sign_val = sys.para.load_corr3;
    break;
    case LOAD_CORR_4:
    Lcd16x2_Out(2,1,"LD_CORR(9-12T)  ");
    temp_load_corr4 = sys.para.load_corr4;
    prv16_sign_val = sys.para.load_corr4;
    break;
    case LOAD_CORR_5:
    Lcd16x2_Out(2,1,"LD_CORR(>12T)   ");
    temp_load_corr5 = sys.para.load_corr5;
    prv16_sign_val = sys.para.load_corr5;
    break;
    case LENGTH_FACTORS:
    Lcd16x2_Out(2,1," LENGTH FACTORS ");
    break;
    case PRESSURE_FACTOR:
    Lcd16x2_Out(2,1,"PRESSURE FACTOR ");
    break;
    case COPY_ZLOAD_PCURVE:
    Lcd16x2_Out(2,1,"COPY LOAD PCURVE");
    break;
    case EN_PEAKNHOLD_OPTION:
    Lcd16x2_Out(2,1,"EN PNH SWITCH:  ");
    prv8_val1 = sys.para.peaknhold_stat_bit;
    break;
    case ENTR_LOAD_THRESHOLD:
    Lcd16x2_Out(2,1,"LOAD THRESHOLD: ");
    prv16_val1 = sys.para.load_threshold;
    break;
    case VIEW_DUTY_TABLE:
        Lcd16x2_Out(2,1,"VIEW DUTY TABLE:");
    break;
    
    case CUSTOMER_CARE_NUM:
    Lcd16x2_Out(2,1," CUSTOMER CARE  ");
    break;
  }
}



void Display_Customer_Care_Num(void)
{
    char lbuf[20];
    
    common_long = cust_care_num;
    byt1  = (uint8_t)(common_long/1000000000);
    byt2  = (uint8_t)((common_long%1000000000)/100000000);
    byt3  = (uint8_t)((common_long%100000000)/10000000);
    byt4  = (uint8_t)((common_long%10000000)/1000000);
    byt5  = (uint8_t)((common_long%1000000)/100000);
    byt6  = (uint8_t)((common_long%100000)/10000);
    byt7  = (uint8_t)((common_long%10000)/1000);
    byt8  = (uint8_t)((common_long%1000)/100);
    byt9  = (uint8_t)((common_long%100)/10);
    byt10 = (uint8_t)((common_long%10)/1);
    pos_t = 0;
    Lcd16x2_Out(1,1," CUSTOMER CARE  ");
    Lcd16x2_Out(2,1,"                ");
    sprintf(lbuf,"%010lu",common_long);
    Lcd16x2_Out(2,5,lbuf);
    Move_Cursor_Left(1);
    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

void Display_Length_Factor_Value(void)
{
  char lbuf[20];

  sprintf(lbuf,"LENGTH FACTOR:%d",length_cnt);
  Lcd16x2_Out(1,1,lbuf);
  sprintf(lbuf,"      %03d       ",sys.para.bl_fact[length_cnt-1]);
  Lcd16x2_Out(2,1,lbuf);
}

void Display_Pressure_Factor_Value(void)
{
    char lbuf[20];
    
    common_long = common_flot*1000000;
    byt1  = (uint8_t)((common_long%10000000)/1000000);
    byt2  = (uint8_t)((common_long%1000000)/100000);
    byt3  = (uint8_t)((common_long%100000)/10000);
    byt4  = (uint8_t)((common_long%10000)/1000);
    byt5  = (uint8_t)((common_long%1000)/100);
    byt6  = (uint8_t)((common_long%100)/10);
    byt7 = (uint8_t)((common_long%10)/1);
    pos_t = 0;
    Lcd16x2_Out(1,1,"PRESSURE FACTOR ");
    Lcd16x2_Out(2,1,"                ");
    sprintf(lbuf,"%.6f",(double)common_flot);
    Lcd16x2_Out(2,5,lbuf);
    Move_Cursor_Left(1);
    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

void Select_Length_Factor_Menu(uint8_t flag_id)
{
  char lbuf[20];

  if(flag_id == 0)
  {
    if(length_cnt < 5) length_cnt++;
    else               length_cnt = 1;
  }
  else
  {
    if(length_cnt > 1) length_cnt--;
    else               length_cnt = 5;
  }
  sprintf(lbuf,"%d",length_cnt);
  Lcd16x2_Out(1,15,lbuf);
  sprintf(lbuf,"      %03d       ",sys.para.bl_fact[length_cnt-1]);
  Lcd16x2_Out(2,1,lbuf);
}

void Display_Length_Factor_Cursor(void)
{
  pos_t = 0;
  byt1 = (sys.para.bl_fact[length_cnt-1]%1000)/100;
  byt2 = (sys.para.bl_fact[length_cnt-1]%100)/10;
  byt3 = sys.para.bl_fact[length_cnt-1]%10;
  Move_Cursor_Left(11);
  Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

void Select_Length_Count_Menu(uint8_t flag_id)
{
  char lbuf[20];
  
  if(flag_id == 0)
  {
    if(length_cnt < 6) length_cnt++;
    else               length_cnt = 2;
  }
  else
  {
    if(length_cnt > 2) length_cnt--;
    else               length_cnt = 6;
  }
  sprintf(lbuf,"%d",length_cnt);
  Lcd16x2_Out(1,14,lbuf);
  sprintf(lbuf,"      %04d      ",sys.para.bl_adc_cnt[length_cnt]);
  Lcd16x2_Out(2,1,lbuf);
}


void Display_Length_Count_Value(void)
{
  char lbuf[20];
  
  sprintf(lbuf,"LENGTH COUNT:%d",length_cnt);
  Lcd16x2_Out(1,1,lbuf);
  sprintf(lbuf,"      %04d      ",sys.para.bl_adc_cnt[length_cnt]);
  Lcd16x2_Out(2,1,lbuf);
}


void Display_Length_Count_Cursor(void)
{
    char lbuf[20];
    
    pos_t = 0;
    common_byte = 4;
    common_long = sys.para.bl_adc_cnt[length_cnt];
    
    sprintf(lbuf,"%04d",sys.para.bl_adc_cnt[length_cnt]);
    Lcd16x2_Out(2,4,lbuf);
    
    Move_Cursor_Left(1);
    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    byt1 = sys.para.bl_adc_cnt[length_cnt]/1000;
    byt2 = (sys.para.bl_adc_cnt[length_cnt]%1000)/100;
    byt3 = (sys.para.bl_adc_cnt[length_cnt]%100)/10;
    byt4 = sys.para.bl_adc_cnt[length_cnt]%10;
}

/*============================================================================*/
/*
 * Function      :        Site_Parametere_Value.
 * Description   :        Used to update the supervisor setting display values.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Site_Parametere_Value(void)
{
    char lbuf[20];
    DCT dt;
    
    if((mv.site_set == MIN_BOOM_LEGTH)||(mv.site_set == MAX_BOOM_LEGTH)||
       (mv.site_set == LOAD_CORR_FACTOR)||(mv.site_set == LOAD_CORR_LIMIT)||
       (mv.site_set == ENTR_LOAD_THRESHOLD))
    {
        sprintf(lbuf,"CV:%04.1f  PV:%04.1f",((float)prv16_val1)/10.0,((float)prv16_val1)/10.0);        
        Lcd16x2_Out(2,1,lbuf);

        pos_t = 0;
        common_byte = 3;
        common_long = prv16_val1;
        sprintf(lbuf,"%04.1f",((float)prv16_val1)/10.0);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if((mv.site_set == SET_PRESS_P1_CHANNEL)||(mv.site_set == SET_PRESS_P2_CHANNEL)||
            (mv.site_set == SET_LENGTH_CHANNEL)||(mv.site_set == SET_ANGLE_CHANNEL)||
            (mv.site_set == SET_CAL_SAMPLE_COUNT)||(mv.site_set == SET_MANGLE_CHANNEL))
    {
        sprintf(lbuf,"PV:%02d",prv16_val1);
        Lcd16x2_Out(2,12,lbuf);
        sprintf(lbuf,"CV:%02d",prv16_val1);
        Lcd16x2_Out(2,1,lbuf);

        pos_t = 0;
        common_byte = 2;
        common_long = prv16_val1;
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if((mv.site_set == SET_LOW_ERR_COUNT)||(mv.site_set == SET_HIGH_ERR_COUNT))
    {
        sprintf(lbuf,"PV:%04d",prv16_val1);
        Lcd16x2_Out(2,10,lbuf);
        sprintf(lbuf,"CV:%04d",prv16_val1);
        Lcd16x2_Out(2,1,lbuf);

        pos_t = 0;
        common_byte = 4;
        common_long = prv16_val1;
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if((mv.site_set == BM_LENGTH_CORR_1)||(mv.site_set == BM_LENGTH_CORR_2)||
            (mv.site_set == BM_LENGTH_CORR_3)||(mv.site_set == BM_LENGTH_CORR_4)||(mv.site_set == LOAD_CORR_1)||
            (mv.site_set == LOAD_CORR_2)||(mv.site_set == LOAD_CORR_3)||
            (mv.site_set == LOAD_CORR_4)||(mv.site_set == LOAD_CORR_5))
    {
        value_sign_flag = 0;
        if(prv16_sign_val<0)
        {
            sprintf(lbuf,"P:%05.1f",((float)prv16_sign_val)/10.0);
            value_sign_flag = 1;
            prv16_sign_val = prv16_sign_val*(-1); //make it positive for edit
        }
        else
        {
            sprintf(lbuf,"P: %04.1f",((float)prv16_sign_val)/10.0);
            value_sign_flag = 0;
        }
        Lcd16x2_Out(2,10,lbuf);
        
        pos_t = 0;
        common_byte = 3;
        common_long = prv16_sign_val;   //Take positive number to modify
        
        if(value_sign_flag) sprintf(lbuf,"C:-%04.1f",((float)prv16_sign_val)/10.0);
        else                sprintf(lbuf,"C:+%04.01f",((float)prv16_sign_val)/10.0);

        Lcd16x2_Out(2,1,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.site_set == COPY_ZLOAD_PCURVE)
    {
        sprintf(lbuf,"%02d",prv16_val1);
        Lcd16x2_Out(1,11,lbuf);
        pos_t = 0;
        common_byte = 2;
        common_long = prv16_val1;
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.site_set == VIEW_DUTY_TABLE)
    {
        prv16_val1 = 1;            
        pos_t = 0;
        common_byte = 4;
        common_long = prv16_val1;
        sprintf(lbuf,"%04d",prv16_val1);
        Lcd16x2_Out(2,7,lbuf);
        Move_Cursor_Left(1);
        
        if(lc_art_table_switch)
            dt.dty = lc_total_duty*2;
        else
            dt.dty = lc_total_duty;
        dt.dc_page_s = lc_duty_cycle_page_s;
        dt.mem_offset = flash_memory_offset;
        total_dty_tables = Duty_Table(DT_END,dt);            
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
        menu_stat = VIEW_DUTY_TABLE_PAGE1;
    }
}
/*============================================================================*/
/*
 * Function      :        Site_Setting.
 * Description   :        Used to update the site setting display values.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Site_Setting(void)
{
    char lbuf[20];
    
    Lcd16x2_Out(2,1,"                ");
    switch(mv.site_set)
    {
        case MIN_BOOM_LEGTH:
            Lcd16x2_Out(1,1,"MIN BOOM LEGTH: ");
            Site_Parametere_Value();
        break;
        case MAX_BOOM_LEGTH:
            Lcd16x2_Out(1,1,"MAX BOOM LEGTH: ");
            Site_Parametere_Value();
        break;
        case SET_PRESS_P1_CHANNEL:
            Lcd16x2_Out(1,1,"SET PRESS P1 CHN");
            Site_Parametere_Value();
        break;
        case SET_PRESS_P2_CHANNEL:
            Lcd16x2_Out(1,1,"SET PRESS P2 CHN");
            Site_Parametere_Value();
        break;
        case SET_LENGTH_CHANNEL:
            Lcd16x2_Out(1,1,"SET LENGTH CHN: ");
            Site_Parametere_Value();
        break;
        case SET_ANGLE_CHANNEL:
            Lcd16x2_Out(1,1,"SET KNUC ANG CHN");
            Site_Parametere_Value();
        break;
        case SET_MANGLE_CHANNEL:
            Lcd16x2_Out(1,1,"SET MAIN ANG CHN");
            Site_Parametere_Value();
        break;
        case SET_LOW_ERR_COUNT:
            Lcd16x2_Out(1,1,"SET LOW ERR CNT:");
            Site_Parametere_Value();
        break;
        case SET_HIGH_ERR_COUNT:
            Lcd16x2_Out(1,1,"SET HI ERR CNT: ");
            Site_Parametere_Value();
        break;
        case SET_CAL_SAMPLE_COUNT:
            Lcd16x2_Out(1,1,"SET CAL SMPL CNT");
            Site_Parametere_Value();
        break;
        case LOAD_CORR_FACTOR:
            Lcd16x2_Out(1,1,"LOAD CORR FACTOR");
            Site_Parametere_Value();
        break;
        case LOAD_CORR_LIMIT:
            Lcd16x2_Out(1,1,"LOAD CORR LIMIT:");
            Site_Parametere_Value();
        break;
        case COPY_ZERO_CALIB:
            Lcd16x2_Out(1,1,"COPY ZERO CALIB:");

        break;
        case SET_DATE_TIME:
            Lcd16x2_Out(1,1,"SET DATE & TIME:");
            sprintf(lbuf,"%02d/%02d/%02d   %02d:%02d",day,month,year%100,hour,minute);
            Lcd16x2_Out(2,1,lbuf);
        break;
        case EDIT_LENGTH_COUNT:
            length_cnt = 2;
            Display_Length_Count_Value();
            menu_stat = SELECT_LEN_COUNT_PAGE;
        break;
        case BM_LENGTH_CORR_1:
            Lcd16x2_Out(1,1,"BM_LENGTH_CORR_1");
            Site_Parametere_Value();
        break;
        case BM_LENGTH_CORR_2:
            Lcd16x2_Out(1,1,"BM_LENGTH_CORR_2");
            Site_Parametere_Value();
        break;
        case BM_LENGTH_CORR_3:
            Lcd16x2_Out(1,1,"BM_LENGTH_CORR_3");
            Site_Parametere_Value();
        break;
        case BM_LENGTH_CORR_4:
            Lcd16x2_Out(1,1,"BM_LENGTH_CORR_4");
            Site_Parametere_Value();
        break;
        case FAIL_SAFE_STATUS_CASE:
            Lcd16x2_Out(1,1,"FAIL SAFE STATUS");
            Show_Enable_Disable_String(sys.para.fail_safe_stat_bit);
        break;
        case LOAD_CORR_1:
            Lcd16x2_Out(1,1,"LD_CORR(0.6-2T) ");
            Site_Parametere_Value();
        break;
        case LOAD_CORR_2:
            Lcd16x2_Out(1,1,"LD_CORR(2-4T)   ");
            Site_Parametere_Value();
        break;
        case LOAD_CORR_3:
            Lcd16x2_Out(1,1,"LD_CORR(4-9T)   ");
            Site_Parametere_Value();
        break;
        case LOAD_CORR_4:
            Lcd16x2_Out(1,1,"LD_CORR(9-12T)  ");
            Site_Parametere_Value();
        break;
        case LOAD_CORR_5:
            Lcd16x2_Out(1,1,"LD_CORR(>12T)   ");
            Site_Parametere_Value();
        break;
        case LENGTH_FACTORS:
            length_cnt = 1;
            Display_Length_Factor_Value();
            menu_stat = SELECT_LENGTH_FACTOR_PAGE;
        break;
        case PRESSURE_FACTOR:
            common_flot = PRCHN;
            Display_Pressure_Factor_Value();
        break;
        case COPY_ZLOAD_PCURVE:
            start_cpy_dty = 1;
            end_cpy_dty = 2;
            prv16_val1 = start_cpy_dty;
            prv16_val2 = end_cpy_dty;
            sprintf(lbuf,"FROM DUTY:%02d    ",start_cpy_dty);
            Lcd16x2_Out(1,1,lbuf);
            sprintf(lbuf,"TO DUTY:%02d      ",end_cpy_dty);
            Lcd16x2_Out(2,1,lbuf);
            Site_Parametere_Value();
            menu_stat = START_COPY_DUTY_PAGE;
        break;
        case EN_PEAKNHOLD_OPTION:
            //Cursor position not required
            Lcd16x2_Out(1,1," EN PNH SWITCH: ");
            Show_Enable_Disable_String(sys.para.peaknhold_stat_bit);
        break;
        case ENTR_LOAD_THRESHOLD:
            Lcd16x2_Out(1,1,"LOAD THRESHOLD: ");
            Site_Parametere_Value();
        break;
        case VIEW_DUTY_TABLE: 
            Lcd16x2_Out(1,1,"ENTER TABLE NO: ");
            Site_Parametere_Value();
        break;            
        case CUSTOMER_CARE_NUM:
            common_flot = PRCHN;
            Display_Customer_Care_Num();
        break;
    }
}


/*============================================================================*/
/*
 * Function      :        Site_Change_Parameter_Value.
 * Description   :        Used to change(inc/dec) values.
 * Parameters    :        flag_id-increment/decrement flag.
 * Return        :        None.
*/
/*============================================================================*/
void Site_Change_Parameter_Value(uint8_t flag_id)
{
    char lbuf[20];
    
    if(flag_id == 0)    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
    else                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
  
    if((mv.site_set == MIN_BOOM_LEGTH)||(mv.site_set == MAX_BOOM_LEGTH)||
       (mv.site_set == LOAD_CORR_FACTOR)||(mv.site_set == LOAD_CORR_LIMIT)||
       (mv.site_set == ENTR_LOAD_THRESHOLD))
    {
        sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
        Lcd16x2_Out(2,4,lbuf);
        if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
        else            Move_Cursor_Left(pos_t+1);
    }
    else if((mv.site_set == SET_PRESS_P1_CHANNEL)||(mv.site_set == SET_PRESS_P2_CHANNEL)||
            (mv.site_set == SET_LENGTH_CHANNEL)||(mv.site_set == SET_ANGLE_CHANNEL)||
            (mv.site_set == SET_CAL_SAMPLE_COUNT)||(mv.site_set == SET_MANGLE_CHANNEL))
    {
        sprintf(lbuf,"%02d",(uint8_t)common_long);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
    else if((mv.site_set == BM_LENGTH_CORR_1)||(mv.site_set == BM_LENGTH_CORR_2)||
            (mv.site_set == BM_LENGTH_CORR_3)||(mv.site_set == BM_LENGTH_CORR_4)||
            (mv.site_set == LOAD_CORR_1)||(mv.site_set == LOAD_CORR_2)||
            (mv.site_set == LOAD_CORR_3)||(mv.site_set == LOAD_CORR_4)||
            (mv.site_set == LOAD_CORR_5))
    {
      if((flag_id == 0)&&(pos_t == 3))
      {
          value_sign_flag = !value_sign_flag;
          if(value_sign_flag) Lcd16x2_Chr(2,3, '-');
          else                Lcd16x2_Chr(2,3, '+');
          Move_Cursor_Left(1);
      }
      else if((flag_id == 1)&&(pos_t == 3))
      {
          value_sign_flag = !value_sign_flag;
          if(value_sign_flag) Lcd16x2_Chr(2,3, '-');
          else                Lcd16x2_Chr(2,3, '+');
          Move_Cursor_Left(1);
      }
      sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
      Lcd16x2_Out(2,4,lbuf);
      if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
      else            Move_Cursor_Left(pos_t+1);
    }
    else if((mv.site_set == SET_LOW_ERR_COUNT)||(mv.site_set == SET_HIGH_ERR_COUNT)||
            (mv.site_set == EDIT_LENGTH_COUNT))
    {
        sprintf(lbuf,"%04d",(uint16_t)common_long);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
    else if(mv.site_set == FAIL_SAFE_STATUS_CASE)
    {
      prv8_val1 = !prv8_val1;
      Show_Enable_Disable_Stat(prv8_val1);
    }
    else if(mv.site_set == LENGTH_FACTORS)
    {
      if(flag_id == 0)
      {
        if(pos_t == 0)
        {
          if(byt3 < 9) byt3++;
          else         byt3 = 0;
          Lcd16x2_Chr(2,6, byt3+0x30);
          Move_Cursor_Left(1);
        }
        else if(pos_t == 1)
        {
          if(byt2 < 9) byt2++;
          else         byt2 = 0;
          Lcd16x2_Chr(2,5, byt2+0x30);
          Move_Cursor_Left(1);
        }
        else if(pos_t == 2)
        {
          if(byt1 < 9) byt1++;
          else         byt1 = 0;
          Lcd16x2_Chr(2,4, byt1+0x30);
          Move_Cursor_Left(1);
        }
      }
      else
      {
        if(pos_t == 0)
        {
          if(byt3 > 0) byt3--;
          else         byt3 = 9;
          Lcd16x2_Chr(2,6, byt3+0x30);
          Move_Cursor_Left(1);
        }
        else if(pos_t == 1)
        {
          if(byt2 > 0) byt2--;
          else         byt2 = 9;
          Lcd16x2_Chr(2,5, byt2+0x30);
          Move_Cursor_Left(1);
        }
        else if(pos_t == 2)
        {
          if(byt1 > 0) byt1--;
          else         byt1 = 9;
          Lcd16x2_Chr(2,4, byt1+0x30);
          Move_Cursor_Left(1);
        }
      }
    }
    else if(mv.site_set == PRESSURE_FACTOR)
    {
        if(flag_id == 0)
        {
            if(pos_t == 0)
            {
                if(byt7 < 9) byt7++;
                else         byt7 = 0;
                Lcd16x2_Chr(2,12, byt7+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt6 < 9) byt6++;
                else         byt6 = 0;
                Lcd16x2_Chr(2,11, byt6+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt5 < 9) byt5++;
                else         byt5 = 0;
                Lcd16x2_Chr(2,10, byt5+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt4 < 9) byt4++;
                else         byt4 = 0;
                Lcd16x2_Chr(2,9, byt4+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt3 < 9) byt3++;
                else         byt3 = 0;
                Lcd16x2_Chr(2,8, byt3+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt2 < 9) byt2++;
                else         byt2 = 0;
                Lcd16x2_Chr(2,7, byt2+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt1 < 9) byt1++;
                else         byt1 = 0;
                Lcd16x2_Chr(2,5, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
        else
        {
            if(pos_t == 0)
            {
                if(byt7 > 0) byt7--;
                else         byt7 = 9;
                Lcd16x2_Chr(2,12, byt7+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt6 > 0) byt6--;
                else         byt6 = 9;
                Lcd16x2_Chr(2,11, byt6+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt5 > 0) byt5--;
                else         byt5 = 9;
                Lcd16x2_Chr(2,10, byt5+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt4 > 0) byt4--;
                else         byt4 = 9;
                Lcd16x2_Chr(2,9, byt4+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt3 > 0) byt3--;
                else         byt3 = 9;
                Lcd16x2_Chr(2,8, byt3+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt2 > 0) byt2--;
                else         byt2 = 9;
                Lcd16x2_Chr(2,7, byt2+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt1 > 0) byt1--;
                else         byt1 = 9;
                Lcd16x2_Chr(2,5, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
    }
    else if(mv.site_set == EN_PEAKNHOLD_OPTION)
    {
        prv8_val1 = !prv8_val1;
        Show_Enable_Disable_Stat(prv8_val1);
    }
    else if(mv.site_set == VIEW_DUTY_TABLE)
    {
        sprintf(lbuf,"%04d",(uint16_t)common_long);
        Lcd16x2_Out(2,7,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
}



/*============================================================================*/
/*
 * Function      :        Site_Shift_Cursor.
 * Description   :        Used to cursor left/right.
 * Parameters    :        flag_lr-left/right flag.
 * Return        :        None.
*/
/*============================================================================*/
void Site_Shift_Cursor(uint8_t flag_lr)
{
    if((mv.site_set == MIN_BOOM_LEGTH)||(mv.site_set == MAX_BOOM_LEGTH)||
       (mv.site_set == LOAD_CORR_FACTOR)||(mv.site_set == LOAD_CORR_LIMIT)||
       (mv.site_set == ENTR_LOAD_THRESHOLD))
    {
      Shift_Cursor_Position(flag_lr,3,ONE_DECIMAL_POINT);
    }
    else if((mv.site_set == SET_PRESS_P1_CHANNEL)||(mv.site_set == SET_PRESS_P2_CHANNEL)||
            (mv.site_set == SET_LENGTH_CHANNEL)||(mv.site_set == SET_ANGLE_CHANNEL)||
            (mv.site_set == SET_CAL_SAMPLE_COUNT)||(mv.site_set == SET_MANGLE_CHANNEL))
    {
        Shift_Cursor_Position(flag_lr,2,NO_DECIMAL_POINT);
    }    
    else if((mv.site_set == BM_LENGTH_CORR_1)||(mv.site_set == BM_LENGTH_CORR_2)||
            (mv.site_set == BM_LENGTH_CORR_3)||(mv.site_set == BM_LENGTH_CORR_4)||
            (mv.site_set == LOAD_CORR_1)||(mv.site_set == LOAD_CORR_2)||
            (mv.site_set == LOAD_CORR_3)||(mv.site_set == LOAD_CORR_4)||
            (mv.site_set == LOAD_CORR_5))
    {
      Shift_Cursor_Position(flag_lr,4,ONE_DECIMAL_POINT);
    }
    else if((mv.site_set == SET_LOW_ERR_COUNT)||(mv.site_set == SET_HIGH_ERR_COUNT)||
            (mv.site_set == EDIT_LENGTH_COUNT))
    {
      Shift_Cursor_Position(flag_lr,4,NO_DECIMAL_POINT);
    }
    else if(mv.site_set == LENGTH_FACTORS)
    {
        Shift_Cursor_Position(flag_lr,3,NO_DECIMAL_POINT);
    }
    else if(mv.site_set == PRESSURE_FACTOR)
    {
        if(flag_lr == 0)                   //Shift cursor left
        {
            if(pos_t < 6)
            {
                pos_t++;
                if(pos_t == 6) Move_Cursor_Left(2);
                else           Move_Cursor_Left(1);
            }
            else
            {
                pos_t = 0;
                Move_Cursor_Right(7);
            }
        }
        else
        {
            if(pos_t > 0)
            {
                pos_t--;
                if(pos_t == 5) Move_Cursor_Right(2);
                else           Move_Cursor_Right(1);
            }
            else
            {
                pos_t = 6;
                Move_Cursor_Left(7);
            }
        }
    }
    else if(mv.site_set == VIEW_DUTY_TABLE)
    {
        Shift_Cursor_Position(flag_lr,4,NO_DECIMAL_POINT);
    }
}



/*============================================================================*/
/*
 * Function      : USB_Mass_Storage_Options.
 * Description   : Options for USB operations.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void USB_Mass_Storage_Options(void)
{
  switch(mv.site_sub_set)
  {
    case MOVE_SYSTEM_SETTINGS:
    Lcd16x2_Out(2,1,"MOVE SYSTEM SET ");
    break;
    case MOVE_PRESSURE_CURVE:
    Lcd16x2_Out(2,1,"MOVE PRESS CURVE");
    break;
    case MOVE_WHOLE_CSV:
    Lcd16x2_Out(2,1,"    MOVE CSV    ");
    break;
  }
}

/*============================================================================*/
/*
 * Function      : Select_USB_Options.
 * Description   : Select Options for USB operations.
 * Parameters    : flag_id-Inc/Dec menu.
 * Return        : None.
*/
/*============================================================================*/
void Select_USB_Options(uint8_t flag_id)
{
  if(flag_id == 0)
  {
    mv.site_sub_set++;
    if(mv.site_sub_set > mv.max) mv.site_sub_set = mv.min;
  }
  else
  {
    mv.site_sub_set--;
    if(mv.site_sub_set < mv.min) mv.site_sub_set = mv.max;
  }
  USB_Mass_Storage_Options();
}

void Display_Move_Option(void)
{
  if(usb_menu_cnt == 0)
  {
    Lcd16x2_Out(2,1,"  FLASH TO USB  ");
  }
  else
  {
    Lcd16x2_Out(2,1,"  USB TO FLASH  ");
  }
}

/*============================================================================*/
/*
 * Function      : Select_USB_Mass_Storage_Options.
 * Description   : Options for USB operations.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Select_USB_Mass_Storage_Options(void)
{
  switch(mv.site_sub_set)
  {
    case MOVE_SYSTEM_SETTINGS:
    Lcd16x2_Out(1,1,"MOVE SYSTEM SET ");
    break;
    case MOVE_PRESSURE_CURVE:
    Lcd16x2_Out(1,1,"MOVE PRESS CURVE");
    break;
    case MOVE_WHOLE_CSV:
    Lcd16x2_Out(1,1,"    MOVE CSV    ");
    break;
  }
}

/*============================================================================*/
/*
 * Function      : Site_Save_Settings.
 * Description   : Save site settings to SPI flash.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Site_Save_Settings(void)
{
    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

    switch(mv.site_set)
    {
        case MIN_BOOM_LEGTH:
            sys.para.bm_length_min = (uint16_t)common_long;
            sys.para.cal_len_min = sys.para.bm_length_min;
        break;
        case MAX_BOOM_LEGTH:
            sys.para.bm_length_max = (uint16_t)common_long;
            sys.para.cal_len_max = sys.para.bm_length_max;
        break;
        case SET_PRESS_P1_CHANNEL:
            sys.para.pressure_p1_chann = (uint8_t)common_long;
        break;
        case SET_PRESS_P2_CHANNEL:
            sys.para.pressure_p2_chann = (uint8_t)common_long;
        break;
        case SET_LENGTH_CHANNEL:
            sys.para.bm_length_chann = (uint8_t)common_long;
        break;
        case SET_ANGLE_CHANNEL:
            sys.para.bm_angle_chann = (uint8_t)common_long;
        break;
        case SET_MANGLE_CHANNEL:
            sys.para.main_ang_chann = (uint8_t)common_long;
        break;
        case SET_LOW_ERR_COUNT:
            sys.para.low_err_cnt = (uint16_t)common_long;
        break;
        case SET_HIGH_ERR_COUNT:
            sys.para.high_err_cnt = (uint16_t)common_long;
        break;
        case SET_CAL_SAMPLE_COUNT:
            sys.para.cal_smpl_cnt = (uint16_t)common_long;
        break;
        case LOAD_CORR_FACTOR:
            sys.para.load_corr_factor = (uint16_t)common_long;
        break;
        case LOAD_CORR_LIMIT:
            sys.para.load_corr_limit = (uint16_t)common_long;
        break;
        case COPY_ZERO_CALIB:
            Lcd16x2_Out(2,1,"COPY ZERO CALIB:");
        break;
        case SET_DATE_TIME: //RTC
            Lcd16x2_Out(2,1,"SET DATE & TIME:");
        break;
        case EDIT_LENGTH_COUNT:
            sys.para.bl_adc_cnt[length_cnt] = byt1*1000 + byt2*100 + byt3*10 + byt4;
        break;
        case BM_LENGTH_CORR_1:
            sys.para.bm_length_corr1 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.bm_length_corr1 = sys.para.bm_length_corr1*(-1);
        break;
        case BM_LENGTH_CORR_2:
            sys.para.bm_length_corr2 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.bm_length_corr2 = sys.para.bm_length_corr2*(-1);
        break;
        case BM_LENGTH_CORR_3:
            sys.para.bm_length_corr3 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.bm_length_corr3 = sys.para.bm_length_corr3*(-1);
        break;
        case BM_LENGTH_CORR_4:
            sys.para.bm_length_corr4 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.bm_length_corr4 = sys.para.bm_length_corr4*(-1);
        break;
        case FAIL_SAFE_STATUS_CASE:
            sys.para.fail_safe_stat_bit = prv8_val1;
            flash.buf[FAIL_SAFE_STATUS] = sys.para.fail_safe_stat_bit;
        break;
        case LOAD_CORR_1:
            sys.para.load_corr1 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.load_corr1 = sys.para.load_corr1*(-1);
        break;
        case LOAD_CORR_2:
            sys.para.load_corr2 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.load_corr2 = sys.para.load_corr2*(-1);
        break;
        case LOAD_CORR_3:
            sys.para.load_corr3 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.load_corr3 = sys.para.load_corr3*(-1);
        break;
        case LOAD_CORR_4:
            sys.para.load_corr4 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.load_corr4 = sys.para.load_corr4*(-1);
        break;
        case LOAD_CORR_5:
            sys.para.load_corr5 = (uint16_t)common_long;
            if(value_sign_flag) sys.para.load_corr5 = sys.para.load_corr5*(-1);
        break;
        case USB_MASS_STORAGE:
            Lcd16x2_Out(2,1,"USB MASS STORAGE");
        break;
        case LENGTH_FACTORS:
            sys.para.bl_fact[length_cnt-1] = byt1*100 + byt2*10 + byt3;
        break;
        case PRESSURE_FACTOR:
            common_long = (uint32_t)byt1*1000000 + (uint32_t)byt2*100000 + (uint16_t)byt3*10000 + byt4*1000 + byt5*100 + byt6*10 + byt7;
            PRCHN = ((float)common_long)/1000000;
        break;
        case EN_PEAKNHOLD_OPTION:
            sys.para.peaknhold_stat_bit = prv8_val1;
        break;
        case ENTR_LOAD_THRESHOLD:
            sys.para.load_threshold = (uint16_t)common_long;
        break;
    }
    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

    Lcd16x2_Cmd(LCD_CLEAR);
    Lcd16x2_Out(1,1,"   DATA SAVED   ");
    Delay_1ms(1500);
}

//==================================EOF=======================================