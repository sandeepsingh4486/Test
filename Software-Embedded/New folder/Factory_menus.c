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
 * Function      :        Display_Factory_Set_Menu.
 * Description   :        Used to display factory's setting menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Factory_Set_Menu(void)
{
  mv.max = 39;
  mv.min = 1;

  Lcd16x2_Cmd(LCD_CLEAR);

  Select_Factory_Set_Menu();
}

/*============================================================================*/
/*
 * Function      :        Select_Factory_Set_Menu.
 * Description   :        Used to select factory setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Select_Factory_Set_Menu(void)
{
  char lbuf[20];

  sprintf(lbuf,"SET CODE: %03d   ",mv.factory_set+299);
  Lcd16x2_Out(1,1,lbuf);

  switch(mv.factory_set)
  {
    case CALIB_PRESSURE_P1_MIN:
    Lcd16x2_Out(2,1,"CAL PRESS P1 MIN");
    prv16_val1 = sys.para.calib_pressure1_min;
    prv16_val2 = sys.para.calib_P1LowAdcCount;
    break;
    case CALIB_PRESSURE_P1_MAX:
    Lcd16x2_Out(2,1,"CAL PRESS P1 MAX");
    prv16_val1 = sys.para.calib_pressure1_max;
    prv16_val2 = sys.para.calib_P1HighAdcCount;
    break;
    case CALIB_PRESSURE_P2_MIN:
    Lcd16x2_Out(2,1,"CAL PRESS P2 MIN");
    prv16_val1 = sys.para.calib_pressure2_min;
    prv16_val2 = sys.para.calib_P2LowAdcCount;
    break;
    case CALIB_PRESSURE_P2_MAX:
    Lcd16x2_Out(2,1,"CAL PRESS P2 MAX");
    prv16_val1 = sys.para.calib_pressure2_max;
    prv16_val2 = sys.para.calib_P2HighAdcCount;
    break;
    case EN_LOAD_AVERAGING_VALUE:
    Lcd16x2_Out(2,1,"LOAD AVRGING VAL");
    prv8_val1 = sys.para.load_avg_stat_bit;
    break;
    case WINDOW_SAMPLES_SIZE:
    Lcd16x2_Out(2,1,"WINDOW SMPL SIZE");
    prv16_val1 = sys.para.window_sample_size;
    break;
    case NUM_OF_CYLINDERS:
    Lcd16x2_Out(2,1,"NUM OF LUFF. CYL");
    prv16_val1 = sys.para.num_of_cylinders;
    break;
    case WRITE_TO_MEMORY:
    Lcd16x2_Out(2,1,"WRITE TO MEMORY:");
    //PC to SPI flash
    break;
    case CRANE_DETAILS:
    Lcd16x2_Out(2,1,"CRANE DETAILS:  ");
    
    break;
    case SET_BM_ANGLE_MIN:
    Lcd16x2_Out(2,1,"SET BM ANGLE MIN");
    prv16_val1 = sys.para.cal_angle_min;
    prv16_val2 = sys.para.cal_angle_min_cnt;
    break;
    case SET_BM_ANGLE_MAX:
    Lcd16x2_Out(2,1,"SET BM ANGLE MAX");
    prv16_val1 = sys.para.cal_angle_max;
    prv16_val2 = sys.para.cal_angle_max_cnt;
    break;
    case SET_BM_LENGTH_MIN:
    Lcd16x2_Out(2,1,"SET BM LEN MIN: ");
    prv16_val1 = sys.para.cal_len_min;
    prv16_val2 = sys.para.cal_len_min_cnt;
    break;
    case SET_BM_LENGTH_MAX:
    Lcd16x2_Out(2,1,"SET BM LEN MAX: ");
    prv16_val1 = sys.para.cal_len_max;
    prv16_val2 = sys.para.cal_len_max_cnt;
    break;
    /*
    case SET_CALIB_DATE_TIME:
    Lcd16x2_Out(2,1,"SET CALIB DATE: ");

    break;
    */
    case SET_CRANE_MODEL:
    Lcd16x2_Out(2,1,"SET CRANE MODEL:");

    break;
    case SET_BAUDRATE:
    Lcd16x2_Out(2,1,"SET BAUDRATE:   ");
    prv16_val1 = sys.para.baudrate;
    break;
    case ERASE_DATA_LOGS:
    Lcd16x2_Out(2,1,"ERASE DATA LOGS:");
//    prv16_val1 = sys.para.data_log_cntr;
    break;
    case SELECT_SENSOR:
    Lcd16x2_Out(2,1,"SELECT SENSOR:  ");
    sensor_cnt = sys.para.sel_sensor;
    break;
    case DEFAULT_BL_ADC_COUNT:
    Lcd16x2_Out(2,1,"DEFLT BL ADC CNT");
    
    break;
    case WINDOW_SAMPLES_SIZE1:
    Lcd16x2_Out(2,1,"WINDOW SMPL SIZ1");
    prv16_val1 = sys.para.window_sample_size1;
    break;
    case STICKER_TYPE:
    Lcd16x2_Out(2,1,"STICKER TYPE:   ");
    prv16_val1 = sys.para.sticker_type;
    break;
    case SET_INSALLATION_DATE:
    Lcd16x2_Out(2,1,"INSALLATION DATE");
    
    break;
    case SET_PERCENTAGE_STATUS:
    Lcd16x2_Out(2,1,"SET PERCENT STAT");
    prv8_val1 = sys.para.perc_fact_stat_bit;
    break;
    case SET_CORRECTION_LOAD:
    Lcd16x2_Out(2,1,"SET CORR. LOAD: ");
    prv16_val1 = sys.para.correction_load;
    break;
    case EN_NUMBER_OF_CALIB:
    Lcd16x2_Out(2,1,"EN NUM OF CALIB:");
    prv8_val1 = sys.para.num_cal;
    break;
    case SET_SO_NUMBER:
        Lcd16x2_Out(2,1,"SET SO NUMBER:  ");
        prv32_val1 = sys.para.so_number;
    break;
    case P1P2_TO_RS232_PC:
        Lcd16x2_Out(2,1,"P1P2 TO RS232 PC");
    
    break;
    case SET_RADIUS_CUTOFF:
        Lcd16x2_Out(2,1,"SET RADIUS CUTOFF");
        prv16_val1 = sys.para.Radius_Cutoff;
    break;
    case SET_MANBASKET_DUTY:
        if(sys.para.Select_System == PNC_FORK)
        {
            Lcd16x2_Out(2,1,"SET FORK DUTY:  ");
            prv16_val1 = sys.para.fork_duty;
        }
        else if(sys.para.Select_System == ACE_MANBASKET_HXP)
        {
            Lcd16x2_Out(2,1,"SET MANBAS DUTY:");
            prv16_val1 = sys.para.manbas_duty;
        }
        else
        {
            Lcd16x2_Out(2,1," NOT AVAILABLE  ");
        }
    break;
    case SET_MANBASKET_CHANN:
        Lcd16x2_Out(2,1,"SET MANBAS CHAN:");
        prv16_val1 = sys.para.manbas_chann;
    break;
    case NO_LOAD_PRESSURE_CURVE_UP:
        Lcd16x2_Out(2,1,"NOLOAD PCURVE UP");
        pcurve_up_dn_flag = 1;
        min_max_pcurve_flag = 0;
    break;
    case NO_LOAD_PRESSURE_CURVE_DN:
        Lcd16x2_Out(2,1,"NOLOAD PCURVE DN");
        pcurve_up_dn_flag = 2;
        min_max_pcurve_flag = 0;
    break;
    case WITH_LOAD_PRESSURE_CURVE_UP:
        Lcd16x2_Out(2,1,"WITH LOAD PC UP ");
        pcurve_up_dn_flag = 1;
        min_max_pcurve_flag = 1;
    break;
    case WITH_LOAD_PRESSURE_CURVE_DN:
        Lcd16x2_Out(2,1,"WITH LOAD PC DN ");
        pcurve_up_dn_flag = 2;
        min_max_pcurve_flag = 1;
    break;
    case VIEW_NO_LOAD_PRESSURE_CURVE_UP:
        Lcd16x2_Out(2,1,"VIEW NOLOAD PCUP");
        
    break;
    case VIEW_NO_LOAD_PRESSURE_CURVE_DN:
        Lcd16x2_Out(2,1,"VIEW NOLOAD PCDN");
        
    break;
    case VIEW_WITH_LOAD_PRESSURE_CURVE_UP:
        Lcd16x2_Out(2,1,"VIEW WITH LD PCU");
        
    break;
    case VIEW_WITH_LOAD_PRESSURE_CURVE_DN:
        Lcd16x2_Out(2,1,"VIEW WITH LD PCD");
        
    break;
    case SELECT_LENGTH_DRUM:
        Lcd16x2_Out(2,1,"SELECT LEN DRUM:");
        prv8_val1 = sys.para.sel_len_drum;
    break;
    case SELECT_SYSTEM :
        Lcd16x2_Out(2,1,"SELECT SYSTEM    ");
        prv16_val1 = sys.para.Select_System;
    break;       
  }
}



/*============================================================================*/
/*
 * Function      :        Factory_Parametere_Value.
 * Description   :        Used to update the supervisor setting display values.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Factory_Parametere_Value(void)
{
    char lbuf[20];
    
    if((mv.factory_set == CALIB_PRESSURE_P1_MIN)||(mv.factory_set == CALIB_PRESSURE_P2_MIN)||
       (mv.factory_set == CALIB_PRESSURE_P1_MAX)||(mv.factory_set == CALIB_PRESSURE_P2_MAX))
    {
        sprintf(lbuf,"CV:%04d  CC:%04d",prv16_val1,prv16_val2);
        Lcd16x2_Out(1,1,lbuf);
        sprintf(lbuf,"PV:%04d  PC:%04d",prv16_val1,prv16_val2);
        Lcd16x2_Out(2,1,lbuf);
        pos_t = 0;
        byt1 = (uint8_t)(prv16_val1/1000);
        byt2 = (uint8_t)((prv16_val1%1000)/100);
        byt3 = (uint8_t)((prv16_val1%100)/10);
        byt4 = (uint8_t)(prv16_val1%10);
        
        byt5 = (uint8_t)(prv16_val2/1000);
        byt6 = (uint8_t)((prv16_val2%1000)/100);
        byt7 = (uint8_t)((prv16_val2%100)/10);
        byt8 = (uint8_t)(prv16_val2%10);
        
        sprintf(lbuf,"%04d",prv16_val1);
        Lcd16x2_Out(1,4,lbuf);
        sprintf(lbuf,"%04d",prv16_val2);
        Lcd16x2_Out(1,13,lbuf);

        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if((mv.factory_set == WINDOW_SAMPLES_SIZE)||(mv.factory_set == WINDOW_SAMPLES_SIZE1)||
            (mv.factory_set == NUM_OF_CYLINDERS)||(mv.factory_set == HIGH_CUTOFF_ANGLE)||
            (mv.factory_set == SET_BAUDRATE)||(mv.factory_set == SET_MANBASKET_DUTY)||(mv.factory_set == SET_MANBASKET_CHANN))
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
    else if((mv.factory_set == SET_BM_ANGLE_MIN)||(mv.factory_set == SET_BM_LENGTH_MIN)||
            (mv.factory_set == SET_BM_ANGLE_MAX)||(mv.factory_set == SET_BM_LENGTH_MAX))
    {
        sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,prv16_val2);
        Lcd16x2_Out(1,1,lbuf);
        sprintf(lbuf,"PV:%04.1f  PC:%04d",((float)prv16_val1)/10.0,prv16_val2);
        Lcd16x2_Out(2,1,lbuf);
        pos_t = 0;
        byt1 = (uint8_t)(prv16_val1/100);
        byt2 = (uint8_t)((prv16_val1%100)/10);
        byt3 = (uint8_t)(prv16_val1%10);

        byt4 = (uint8_t)(prv16_val2/1000);
        byt5 = (uint8_t)((prv16_val2%1000)/100);
        byt6 = (uint8_t)((prv16_val2%100)/10);
        byt7 = (uint8_t)(prv16_val2%10);
        
        sprintf(lbuf,"%04d",prv16_val2);
        Lcd16x2_Out(1,13,lbuf);
        
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.factory_set == SET_CORRECTION_LOAD)
    {
        sprintf(lbuf,"C:%05.1f  P:%05.1f",((float)prv16_val1)/10.0,((float)prv16_val1)/10.0);        
        Lcd16x2_Out(2,1,lbuf);
        
        pos_t = 0;
        common_byte = 4;
        common_long = prv16_val1;
        sprintf(lbuf,"%05.1f",((float)prv16_val1)/10.0);
        Lcd16x2_Out(2,3,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.factory_set == SET_SO_NUMBER)
    {
        pos_t = 0;
        common_byte = 6; 
        common_long = prv32_val1;
        sprintf(lbuf,"%06lu",common_long);
        Lcd16x2_Out(2,6,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.factory_set == SET_RADIUS_CUTOFF)
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
    else if((mv.factory_set == NO_LOAD_PRESSURE_CURVE_UP)||(mv.factory_set == NO_LOAD_PRESSURE_CURVE_DN))
    {
        Display_Min_Calib_Angle_Menu();
        menu_stat = SET_MIN_ANGLE_PCURVE_PAGE;
    }
    else if((mv.factory_set == WITH_LOAD_PRESSURE_CURVE_UP)||(mv.factory_set == WITH_LOAD_PRESSURE_CURVE_DN))
    {
        Lcd16x2_Cmd(LCD_CLEAR);
        Lcd16x2_Out(1,1,"ENTER KNOWN LOAD");
        prv16_val1 = known_load_pcurve;
        sprintf(lbuf,"CV:%04.1f  PV:%04.1f",((float)prv16_val1)/10.0,((float)prv16_val1)/10.0);        
        Lcd16x2_Out(2,1,lbuf);
        
        pos_t = 0;
        common_byte = 3;
        common_long = prv16_val1;
        sprintf(lbuf,"%04.1f",((float)prv16_val1)/10.0);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
        menu_stat = SET_KNOWN_LOAD_PCURVE_PAGE;
    }
    else if(mv.factory_set == SELECT_SYSTEM)
    {
        Lcd16x2_Out(2,7,(char *)sys_sel[prv16_val1]);
        sprintf(lbuf,"CV:%02d",prv16_val1);
        Lcd16x2_Out(2,1,lbuf);

        pos_t = 0;
        common_byte = 2;
        common_long = prv16_val1;
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.factory_set == SELECT_LENGTH_DRUM)
    {
        Lcd16x2_Out(2,4,(char *)len_drum[prv8_val1]);
    }
}

/*============================================================================*/
/*
 * Function      : Factory_Setting.
 * Description   : Used to update the factory setting display values.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Factory_Setting(void)
{
  char lbuf[20];
  
  Lcd16x2_Out(2,1,"                ");  
  switch(mv.factory_set)
  {
    case CALIB_PRESSURE_P1_MIN:
        Factory_Parametere_Value();
    break;
    case CALIB_PRESSURE_P1_MAX:
        Factory_Parametere_Value();
    break;
    case CALIB_PRESSURE_P2_MIN:
        Factory_Parametere_Value();
    break;
    case CALIB_PRESSURE_P2_MAX:
        Factory_Parametere_Value();
    break;
    case EN_LOAD_AVERAGING_VALUE:
        Lcd16x2_Out(1,1,"LOAD AVRGING VAL");
        Show_Enable_Disable_String(sys.para.load_avg_stat_bit);
    break;
    case WINDOW_SAMPLES_SIZE:
        Lcd16x2_Out(1,1,"WINDOW SMPL SIZE");
        Factory_Parametere_Value();
    break;
    case NUM_OF_CYLINDERS:
        Lcd16x2_Out(1,1,"NUM OF CYLINDERS");
        Factory_Parametere_Value();
    break;
    case WRITE_TO_MEMORY:
        common_byte = 0;
        Lcd16x2_Out(2,1,"                "); 
        Lcd16x2_Out(1,1,"SET BAUDRATE:   ");
        sprintf(lbuf,"SPEED:%lu",baud[common_byte]);
        Lcd16x2_Out(2,1,lbuf);    
        menu_stat = WRITE_TO_MEMORY_PAGE1;
    break;
    case CRANE_DETAILS:
        crane_detail_cnt = 1;

        mv.max = 6;
        mv.min = crane_detail_cnt;

        Display_Crane_Details_Menu();
        menu_stat = SET_CRANE_DETAILS_PAGE;
    break;
    case SET_BM_ANGLE_MIN:
        Factory_Parametere_Value();
    break;
    case SET_BM_ANGLE_MAX:
        Factory_Parametere_Value();
    break;
    case SET_BM_LENGTH_MIN:
        Factory_Parametere_Value();
    break;
    case SET_BM_LENGTH_MAX:
        Factory_Parametere_Value();
    break;
    /*
    case SET_CALIB_DATE_TIME:
    Lcd16x2_Out(1,1,"SET CALIB. DATE:");

    break;
    */
    case SET_CRANE_MODEL:
        Display_Crane_Models_Menu();
        menu_stat = SELECT_CRANE_MODEL_PAGE;
    break;
    case SET_BAUDRATE:
        Lcd16x2_Out(1,1,"SET BAUDRATE:   ");
        Factory_Parametere_Value();
    break;
    case ERASE_DATA_LOGS:
        Lcd16x2_Out(1,1,"ERASE DATA LOGS:");
        Lcd16x2_Out(2,1,"ESC:NO   ENT:YES");
    break;
    case SELECT_SENSOR:
        Lcd16x2_Out(1,1,"SELECT SENSOR:  ");
        Select_Sensor_Type();
    break;
    case DEFAULT_BL_ADC_COUNT:
        Lcd16x2_Out(1,1,"DEFLT BL ADC CNT");
        Lcd16x2_Out(2,1,"ESC:NO   ENT:YES");
    break;
    case WINDOW_SAMPLES_SIZE1:
        Lcd16x2_Out(1,1,"WINDOW SMPL SIZ1");
        Factory_Parametere_Value();
    break;
    case STICKER_TYPE:
        Lcd16x2_Out(1,1,"STICKER TYPE:   ");
        if(sys.para.sticker_type == 1)
            Lcd16x2_Out(2,1,"CV:OLD    PV:OLD");
        else
            Lcd16x2_Out(2,1,"CV:NEW    PV:NEW");
    break;
    case SET_INSALLATION_DATE:
        Lcd16x2_Out(1,1,"INSALLATION DATE");
        Lcd16x2_Out(2,1,"DATE:           ");
        pos_t = 0;
        byt1 = sys.para.insta_dd/10;
        byt2 = sys.para.insta_dd%10;
        byt3 = sys.para.insta_mm/10;
        byt4 = sys.para.insta_mm%10;
        byt5 = (uint8_t)(sys.para.insta_yy/1000);
        byt6 = (uint8_t)((sys.para.insta_yy%1000)/100);
        byt7 = (uint8_t)((sys.para.insta_yy%100)/10);
        byt8 = (uint8_t)(sys.para.insta_yy%10);
        sprintf(lbuf,"%02d/%02d/%04d",sys.para.insta_dd,sys.para.insta_mm,sys.para.insta_yy);
        Lcd16x2_Out(2,6,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    break;
    case SET_PERCENTAGE_STATUS:
        Lcd16x2_Out(1,1,"SET PERCENT STAT");
        Show_Enable_Disable_String(sys.para.perc_fact_stat_bit);
        menu_stat = SET_PERC_STATUS_PAGE;
    break;
    case SET_CORRECTION_LOAD:
        Lcd16x2_Out(1,1,"SET CORR. LOAD: ");
        Factory_Parametere_Value();
    break;
    case EN_NUMBER_OF_CALIB:
        Lcd16x2_Out(1,1,"EN NUM OF CALIB:");
        if(sys.para.num_cal == 0)
          Lcd16x2_Out(2,1,"C:CASE1  P:CASE1");
        else
          Lcd16x2_Out(2,1,"C:CASE2  P:CASE2");
    break;
    case SET_SO_NUMBER:
        Lcd16x2_Out(1,1,"SET SO NUMBER:  ");
        Factory_Parametere_Value();
    break;
    case P1P2_TO_RS232_PC:
        complimnt_flag = 0;
        sprintf(lbuf,"{,PC,%d,}",lc_total_duty*10);
        memset(esp_buf,0,sizeof(esp_buf));
        esp_sbyte = 0;
        esp_index = 0;
        esp_frame_flag = 0;
        UART_Send_String(UART_MODULE3,lbuf);
        menu_stat = PRESSURE_CURVE_SEND_PAGE;
    break;
    case SET_RADIUS_CUTOFF:
        Lcd16x2_Out(1,1,"SET RADIUS CUTOF");
        Factory_Parametere_Value();   
    break;
    case SET_MANBASKET_DUTY:
        if(sys.para.Select_System == PNC_FORK)
            Lcd16x2_Out(1,1,"SET FORK DUTY:  ");
        else
            Lcd16x2_Out(1,1,"SET MANBAS DUTY:");
        Factory_Parametere_Value();
    break; 
    case SET_MANBASKET_CHANN:
        Lcd16x2_Out(1,1,"SET MANBAS CHAN:");
        Factory_Parametere_Value();
    break;  
    case NO_LOAD_PRESSURE_CURVE_UP:
        Factory_Parametere_Value();
    break;  
    case NO_LOAD_PRESSURE_CURVE_DN:
        Factory_Parametere_Value();
    break;  
    case WITH_LOAD_PRESSURE_CURVE_UP:
        Factory_Parametere_Value();
    break;  
    case WITH_LOAD_PRESSURE_CURVE_DN:
        Factory_Parametere_Value();
    break; 
    case VIEW_NO_LOAD_PRESSURE_CURVE_UP:
        memcpy(pc_buf[0],p1_pcurve_min_up,sizeof(pc_buf[0]));
        memcpy(pc_buf[1],p2_pcurve_min_up,sizeof(pc_buf[0]));
        CrtBoomAngle = 1;
        p1_cnt = pc_buf[0][1];
        p2_cnt = pc_buf[1][1];
        Lcd16x2_Cmd(LCD_CLEAR);
        sprintf(lbuf,"P1:%04d   BA:%02dﬂ",p1_cnt,CrtBoomAngle);
        Lcd16x2_Out(1,1,lbuf);
        sprintf(lbuf,"P2:%04d LD:00.0T",p2_cnt);
        Lcd16x2_Out(2,1,lbuf);

        Delay_1ms(1000);
        Lcd16x2_Cmd(LCD_CURSOR_OFF);
        menu_stat = VIEW_PCURVE_PAGE;
    break;
    case VIEW_NO_LOAD_PRESSURE_CURVE_DN:
        memcpy(pc_buf[0],p1_pcurve_min_dn,sizeof(pc_buf[0]));
        memcpy(pc_buf[1],p2_pcurve_min_dn,sizeof(pc_buf[0]));
        CrtBoomAngle = 1;
        p1_cnt = pc_buf[0][1];
        p2_cnt = pc_buf[1][1];
        Lcd16x2_Cmd(LCD_CLEAR);
        sprintf(lbuf,"P1:%04d   BA:%02dﬂ",p1_cnt,CrtBoomAngle);
        Lcd16x2_Out(1,1,lbuf);
        sprintf(lbuf,"P2:%04d LD:00.0T",p2_cnt);
        Lcd16x2_Out(2,1,lbuf);

        Delay_1ms(1000);
        Lcd16x2_Cmd(LCD_CURSOR_OFF);
        menu_stat = VIEW_PCURVE_PAGE;
    break;
    case VIEW_WITH_LOAD_PRESSURE_CURVE_UP:
        memcpy(pc_buf[0],p1_pcurve_max_up,sizeof(pc_buf[0]));
        memcpy(pc_buf[1],p2_pcurve_max_up,sizeof(pc_buf[0]));
        CrtBoomAngle = 1;
        p1_cnt = pc_buf[0][1];
        p2_cnt = pc_buf[1][1];
        Lcd16x2_Cmd(LCD_CLEAR);
        sprintf(lbuf,"P1:%04d   BA:%02dﬂ",p1_cnt,CrtBoomAngle);
        Lcd16x2_Out(1,1,lbuf);
        sprintf(lbuf,"P2:%04d LD:%04.1fT",p2_cnt,((float)known_load_pcurve)/10.0);
        Lcd16x2_Out(2,1,lbuf);

        Delay_1ms(1000);
        Lcd16x2_Cmd(LCD_CURSOR_OFF);
        menu_stat = VIEW_PCURVE_PAGE;
    break;
    case VIEW_WITH_LOAD_PRESSURE_CURVE_DN:        
        memcpy(pc_buf[0],p1_pcurve_max_dn,sizeof(pc_buf[0]));
        memcpy(pc_buf[1],p2_pcurve_max_dn,sizeof(pc_buf[0]));
        CrtBoomAngle = 1;
        p1_cnt = pc_buf[0][1];
        p2_cnt = pc_buf[1][1];
        Lcd16x2_Cmd(LCD_CLEAR);
        sprintf(lbuf,"P1:%04d   BA:%02dﬂ",p1_cnt,CrtBoomAngle);
        Lcd16x2_Out(1,1,lbuf);
        sprintf(lbuf,"P2:%04d LD:%04.1fT",p2_cnt,((float)known_load_pcurve)/10.0);
        Lcd16x2_Out(2,1,lbuf);

        Delay_1ms(1000);
        Lcd16x2_Cmd(LCD_CURSOR_OFF);
        menu_stat = VIEW_PCURVE_PAGE;
    break;             
    case SELECT_LENGTH_DRUM :      
        Lcd16x2_Out(1,1,"SELECT LEN DRUM:");
        Factory_Parametere_Value();
    break;       
    case SELECT_SYSTEM :      
        Lcd16x2_Out(1,1,"SET SYSTEM NUM  ");
        Factory_Parametere_Value();
    break;
  }
}


/*============================================================================*/
/*
 * Function      :        Factory_Change_Parameter_Value.
 * Description   :        Used to change(inc/dec) values.
 * Parameters    :        flag_id-increment/decrement flag.
 * Return        :        None.
*/
/*============================================================================*/
void Factory_Change_Parameter_Value(uint8_t flag_id)
{
    char lbuf[20];
    
    if(flag_id == 0)    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
    else                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
  
    if((mv.factory_set == EN_LOAD_AVERAGING_VALUE)||(mv.factory_set == SET_PERCENTAGE_STATUS)||
       (mv.factory_set == EN_NUMBER_OF_CALIB))
    {
        prv8_val1 = !prv8_val1;
        if(mv.factory_set == EN_NUMBER_OF_CALIB)        Show_Case_Stat(prv8_val1);
        else                                            Show_Enable_Disable_Stat(prv8_val1);
    }
    else if((mv.factory_set==CALIB_PRESSURE_P1_MIN)||(mv.factory_set==CALIB_PRESSURE_P2_MIN)||
            (mv.factory_set==CALIB_PRESSURE_P1_MAX)||(mv.factory_set==CALIB_PRESSURE_P2_MAX))
    {
        if(flag_id == 0)
        {
            if(pos_t == 0)
            {
                if(byt8 < 9) byt8++;
                else         byt8 = 0;
                Lcd16x2_Chr(1,16, byt8+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt7 < 9) byt7++;
                else         byt7 = 0;
                Lcd16x2_Chr(1,15, byt7+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt6 < 9) byt6++;
                else         byt6 = 0;
                Lcd16x2_Chr(1,14, byt6+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt5 < 9) byt5++;
                else         byt5 = 0;
                Lcd16x2_Chr(1,13, byt5+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt4 < 9) byt4++;
                else         byt4 = 0;
                Lcd16x2_Chr(1,7, byt4+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt3 < 9) byt3++;
                else         byt3 = 0;
                Lcd16x2_Chr(1,6, byt3+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt2 < 9) byt2++;
                else         byt2 = 0;
                Lcd16x2_Chr(1,5, byt2+0x30);
            }
            else if(pos_t == 7)
            {
                if(byt1 < 9) byt1++;
                else         byt1 = 0;
                Lcd16x2_Chr(1,4, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
        else
        {
            if(pos_t == 0)
            {
                if(byt8 > 0) byt8--;
                else         byt8 = 9;
                Lcd16x2_Chr(1,16, byt8+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt7 > 0) byt7--;
                else         byt7 = 9;
                Lcd16x2_Chr(1,15, byt7+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt6 > 0) byt6--;
                else         byt6 = 9;
                Lcd16x2_Chr(1,14, byt6+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt5 > 0) byt5--;
                else         byt5 = 9;
                Lcd16x2_Chr(1,13, byt5+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt4 > 0) byt4--;
                else         byt4 = 9;
                Lcd16x2_Chr(1,7, byt4+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt3 > 0) byt3--;
                else         byt3 = 9;
                Lcd16x2_Chr(1,6, byt3+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt2 > 0) byt2--;
                else         byt2 = 9;
                Lcd16x2_Chr(1,5, byt2+0x30);
            }
            else if(pos_t == 7)
            {
                if(byt1 > 0) byt1--;
                else         byt1 = 9;
                Lcd16x2_Chr(1,4, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
    }
    else if((mv.factory_set == WINDOW_SAMPLES_SIZE)||(mv.factory_set==WINDOW_SAMPLES_SIZE1)||
            (mv.factory_set == NUM_OF_CYLINDERS)||(mv.factory_set == SET_BAUDRATE)||
            (mv.factory_set == SELECT_SYSTEM)||(mv.factory_set == SET_MANBASKET_DUTY)||(mv.factory_set == SET_MANBASKET_CHANN))
    {
        if(mv.factory_set == SELECT_SYSTEM)
        {
            if(common_long < MAX_SEL_SYSTEM)
                Lcd16x2_Out(2,7,(char *)sys_sel[(uint8_t)common_long]);
            else
                Lcd16x2_Out(2,7,"RESERVED  ");
        }
        sprintf(lbuf,"%02d",(uint8_t)common_long);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
    else if((mv.factory_set==SET_BM_ANGLE_MIN)||(mv.factory_set==SET_BM_ANGLE_MAX)||
            (mv.factory_set==SET_BM_LENGTH_MIN)||(mv.factory_set==SET_BM_LENGTH_MAX))
    {
        if(flag_id == 0)
        {
            if(pos_t == 0)
            {
                if(byt7 < 9) byt7++;
                else         byt7 = 0;
                Lcd16x2_Chr(1,16, byt7+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt6 < 9) byt6++;
                else         byt6 = 0;
                Lcd16x2_Chr(1,15, byt6+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt5 < 9) byt5++;
                else         byt5 = 0;
                Lcd16x2_Chr(1,14, byt5+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt4 < 9) byt4++;
                else         byt4 = 0;
                Lcd16x2_Chr(1,13, byt4+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt3 < 9) byt3++;
                else         byt3 = 0;
                Lcd16x2_Chr(1,7, byt3+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt2 < 9) byt2++;
                else         byt2 = 0;
                Lcd16x2_Chr(1,5, byt2+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt1 < 9) byt1++;
                else         byt1 = 0;
                Lcd16x2_Chr(1,4, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
        else
        {
            if(pos_t == 0)
            {
                if(byt7 > 0) byt7--;
                else         byt7 = 9;
                Lcd16x2_Chr(1,16, byt7+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt6 > 0) byt6--;
                else         byt6 = 9;
                Lcd16x2_Chr(1,15, byt6+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt5 > 0) byt5--;
                else         byt5 = 9;
                Lcd16x2_Chr(1,14, byt5+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt4 > 0) byt4--;
                else         byt4 = 9;
                Lcd16x2_Chr(1,13, byt4+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt3 > 0) byt3--;
                else         byt3 = 9;
                Lcd16x2_Chr(1,7, byt3+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt2 > 0) byt2--;
                else         byt2 = 9;
                Lcd16x2_Chr(1,5, byt2+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt1 > 0) byt1--;
                else         byt1 = 9;
                Lcd16x2_Chr(1,4, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
    }
    else if(mv.factory_set==SELECT_SENSOR)
    {
        if(flag_id == 0)
        {
            if(sensor_cnt < MAX_SENSOR_OPTIONS) sensor_cnt++;
            else                                sensor_cnt = 1;
        }
        else
        {
            if(sensor_cnt > 1) sensor_cnt--;
            else               sensor_cnt = MAX_SENSOR_OPTIONS;
        }
        Select_Sensor_Type();
    }
    else if(mv.factory_set == STICKER_TYPE)
    {
        if(flag_id == 0)
        {
            if(prv16_val1 < NEW) prv16_val1++;
            else                 prv16_val1 = OLD;
        }
        else
        {
            if(prv16_val1 > OLD) prv16_val1--;
            else                 prv16_val1 = NEW;
        }
        Select_Sticker_Type();
    }
    else if(mv.factory_set == SET_INSALLATION_DATE)
    {
        if(flag_id == 0)
        {
            if(pos_t == 0)
            {
                if(byt8 < 9) byt8++;
                else         byt8 = 0;
                Lcd16x2_Chr(2,15, byt8+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt7 < 9) byt7++;
                else         byt7 = 0;
                Lcd16x2_Chr(2,14, byt7+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt6 < 9) byt6++;
                else         byt6 = 0;
                Lcd16x2_Chr(2,13, byt6+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt5 < 9) byt5++;
                else         byt5 = 0;
                Lcd16x2_Chr(2,12, byt5+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt4 < 9) byt4++;
                else         byt4 = 0;
                Lcd16x2_Chr(2,10, byt4+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt3 < 9) byt3++;
                else         byt3 = 0;
                Lcd16x2_Chr(2,9, byt3+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt2 < 9) byt2++;
                else         byt2 = 0;
                Lcd16x2_Chr(2,7, byt2+0x30);
            }
            else if(pos_t == 7)
            {
                if(byt1 < 9) byt1++;
                else         byt1 = 0;
                Lcd16x2_Chr(2,6, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
        else
        {
            if(pos_t == 0)
            {
                if(byt8 > 0) byt8--;
                else         byt8 = 9;
                Lcd16x2_Chr(2,15, byt8+0x30);
            }
            else if(pos_t == 1)
            {
                if(byt7 > 0) byt7--;
                else         byt7 = 9;
                Lcd16x2_Chr(2,14, byt7+0x30);
            }
            else if(pos_t == 2)
            {
                if(byt6 > 0) byt6--;
                else         byt6 = 9;
                Lcd16x2_Chr(2,13, byt6+0x30);
            }
            else if(pos_t == 3)
            {
                if(byt5 > 0) byt5--;
                else         byt5 = 9;
                Lcd16x2_Chr(2,12, byt5+0x30);
            }
            else if(pos_t == 4)
            {
                if(byt4 > 0) byt4--;
                else         byt4 = 9;
                Lcd16x2_Chr(2,10, byt4+0x30);
            }
            else if(pos_t == 5)
            {
                if(byt3 > 0) byt3--;
                else         byt3 = 9;
                Lcd16x2_Chr(2,9, byt3+0x30);
            }
            else if(pos_t == 6)
            {
                if(byt2 > 0) byt2--;
                else         byt2 = 9;
                Lcd16x2_Chr(2,7, byt2+0x30);
            }
            else if(pos_t == 7)
            {
                if(byt1 > 0) byt1--;
                else         byt1 = 9;
                Lcd16x2_Chr(2,6, byt1+0x30);
            }
            Move_Cursor_Left(1);
        }
    }
    else if(mv.factory_set == SET_CORRECTION_LOAD)
    {      
        sprintf(lbuf,"%05.1f",((float)common_long)/10.0);
        Lcd16x2_Out(2,3,lbuf);
        if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
        else            Move_Cursor_Left(pos_t+1);
    }
    else if(mv.factory_set == SET_SO_NUMBER)
    {
        sprintf(lbuf,"%06lu",common_long);
        Lcd16x2_Out(2,6,lbuf);
        Move_Cursor_Left(pos_t+1);      
    }
    else if(mv.factory_set == SET_RADIUS_CUTOFF)
    {      
        sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
        Lcd16x2_Out(2,4,lbuf);
        if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
        else            Move_Cursor_Left(pos_t+1);
    }
    else if(mv.factory_set == SELECT_LENGTH_DRUM)
    {
        if(flag_id == 0)
        {
            if(prv8_val1 < LEN_DRUM_MAX)    prv8_val1++;
            else                            prv8_val1 = 0;
        }
        else
        {
            if(prv8_val1 > 0)   prv8_val1--;
            else                prv8_val1 = LEN_DRUM_MAX;
        }
        Lcd16x2_Out(2,4,(char *)len_drum[prv8_val1]);
    }
}


/*============================================================================*/
/*
 * Function      : Factory_Shift_Cursor.
 * Description   : Used to cursor left/right.
 * Parameters    : flag_lr-left/right flag.
 * Return        : None.
*/
/*============================================================================*/
void Factory_Shift_Cursor(uint8_t flag_lr)
{
    if((mv.factory_set==CALIB_PRESSURE_P1_MIN)||(mv.factory_set==CALIB_PRESSURE_P2_MIN)||
       (mv.factory_set==CALIB_PRESSURE_P1_MAX)||(mv.factory_set==CALIB_PRESSURE_P2_MAX))
    {
        if(flag_lr == 0)                   //Shift cursor left
        {
          if(pos_t < 7)
          {
            pos_t++;
            if(pos_t == 4)
            {
              Move_Cursor_Left(6);
            }
            else
            {
              Move_Cursor_Left(1);
            }
          }
          else
          {
            pos_t = 0;
            Move_Cursor_Right(12);
          }
        }
        else
        {
            if(pos_t > 0)
            {
                pos_t--;
                if(pos_t == 3)
                {
                    Move_Cursor_Right(6);
                }
                else
                {
                    Move_Cursor_Right(1);
                }
            }
            else
            {
                pos_t = 7;
                Move_Cursor_Left(12);
            }
        }
    }
    else if((mv.factory_set==WINDOW_SAMPLES_SIZE)||(mv.factory_set==WINDOW_SAMPLES_SIZE1)||
            (mv.factory_set == NUM_OF_CYLINDERS)||(mv.factory_set == SET_BAUDRATE)||
            (mv.factory_set == SELECT_SYSTEM)||(mv.factory_set == SET_MANBASKET_DUTY)||
            (mv.factory_set == SET_MANBASKET_CHANN))
    {
        Shift_Cursor_Position(flag_lr,2,NO_DECIMAL_POINT);
    }
    else if((mv.factory_set==SET_BM_ANGLE_MIN)||(mv.factory_set==SET_BM_ANGLE_MAX)||
            (mv.factory_set==SET_BM_LENGTH_MIN)||(mv.factory_set==SET_BM_LENGTH_MAX))
    {
        if(flag_lr == 0)                   //Shift cursor left
        {
            if(pos_t < 6)
            {
                pos_t++;
                if(pos_t == 4)
                {
                    Move_Cursor_Left(6);
                }
                else if(pos_t == 5)
                {
                    Move_Cursor_Left(2);
                }
                else
                {
                    Move_Cursor_Left(1);
                }
            }
            else
            {
                pos_t = 0;
                Move_Cursor_Right(12);
            }
        }
        else
        {
            if(pos_t > 0)
            {
                pos_t--;
                if(pos_t == 3)
                {
                    Move_Cursor_Right(6);
                }
                else if(pos_t == 4)
                {
                    Move_Cursor_Right(2);
                }
                else
                {
                    Move_Cursor_Right(1);
                }
            }
            else
            {
                pos_t = 6;
                Move_Cursor_Left(12);
            }
        }
    }
    else if(mv.factory_set == SET_INSALLATION_DATE)
    {
        if(flag_lr == 0)
        {
            if(pos_t < 7)
            {
                pos_t++;
                if((pos_t==4)||(pos_t==6))      Move_Cursor_Left(2);
                else                            Move_Cursor_Left(1);
            }
            else
            {
                pos_t = 0;
                Move_Cursor_Right(9);
            }
        }
        else
        {
            if(pos_t > 0)
            {
                pos_t--;
                if((pos_t==5)||(pos_t==3)) Move_Cursor_Right(2);
                else                       Move_Cursor_Right(1);
            }
            else
            {
                pos_t = 7;
                Move_Cursor_Left(9);
            }
        }
    }
    else if(mv.factory_set == SET_CORRECTION_LOAD)
    {
        Shift_Cursor_Position(flag_lr,4,ONE_DECIMAL_POINT);
    }
    else if(mv.factory_set == SET_SO_NUMBER)
    {
        Shift_Cursor_Position(flag_lr,6,NO_DECIMAL_POINT);
    }
    else if(mv.factory_set == SET_RADIUS_CUTOFF)
    {
        Shift_Cursor_Position(flag_lr,3,ONE_DECIMAL_POINT);
    }
}

/*============================================================================*/
/*
 * Function      : Select_Sensor_Type.
 * Description   : Used to select sensor type.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Select_Sensor_Type(void)
{
  char lbuf[20];
  
  switch(sensor_cnt)
  {
    case 1:
      Lcd16x2_Out(2,1,"     Hydac      ");
//      PRCHN = 1.401189;     //1.279844(PCB332R1) //1.556224(6723)
//      sys.para.calib_pressure1_min = 0;
//      sys.para.calib_P1LowAdcCount = 744;
//      sys.para.calib_pressure1_max = 400;
//      sys.para.calib_P1HighAdcCount = 3655;
//
//      sys.para.calib_pressure2_min = 0;
//      sys.para.calib_P2LowAdcCount = 744;
//      sys.para.calib_pressure2_max = 400;
//      sys.para.calib_P2HighAdcCount = 3655;
      
        PRCHN = 1.556224;
        sys.para.calib_pressure1_min = 0;
        sys.para.calib_P1LowAdcCount = 655;
        sys.para.calib_pressure1_max = 400;
        sys.para.calib_P1HighAdcCount = 3276;

        sys.para.calib_pressure2_min = 0;
        sys.para.calib_P2LowAdcCount = 655;
        sys.para.calib_pressure2_max = 400;
        sys.para.calib_P2HighAdcCount = 3276;
    break;

    case 2: 
      Lcd16x2_Out(2,1,"    Honeywell   ");

      PRCHN = 1.073060;
      sys.para.calib_pressure1_min = 0;
      sys.para.calib_P1LowAdcCount = 390;
      sys.para.calib_pressure1_max = 344;
      sys.para.calib_P1HighAdcCount = 3685;

      sys.para.calib_pressure2_min = 0;
      sys.para.calib_P2LowAdcCount = 390;
      sys.para.calib_pressure2_max = 344;
      sys.para.calib_P2HighAdcCount = 3685;
    break;

    case 3: 
      Lcd16x2_Out(2,1,"    Hydac 12v   ");

      PRCHN = 1.329486;
      sys.para.calib_pressure1_min = 0;
      sys.para.calib_P1LowAdcCount = 410;
      sys.para.calib_pressure1_max = 400;
      sys.para.calib_P1HighAdcCount = 3685;

      sys.para.calib_pressure2_min = 0;
      sys.para.calib_P2LowAdcCount = 410;
      sys.para.calib_pressure2_max = 400;
      sys.para.calib_P2HighAdcCount = 3686;
    break;
    default:break;
  }
  sprintf(lbuf,"%d",sensor_cnt);
  Lcd16x2_Out(1,15,lbuf);
}


/*============================================================================*/
/*
 * Function      : Display_Factor_Menu.
 * Description   : Used to display factor value.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Factor_Menu(void)
{
  char fbuf[20];
  
  mv.max = 50;
  mv.min = 1;
  
  pos_t = 0;
  byt1 = sys.para.fact/10;
  byt2 = sys.para.fact%10;
  
  Lcd16x2_Cmd(LCD_CLEAR);
  Lcd16x2_Out(1,1,"  SET FACT    ");
  Lcd16x2_Out(2,9,"%");
  sprintf(fbuf,"%02d",sys.para.fact);
  Lcd16x2_Out(2,7,fbuf);
  Move_Cursor_Left(1);
  Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      : Factor_Shift_Cursor.
 * Description   : Used to cursor left/right.
 * Parameters    : flag_lr-left/right flag.
 * Return        : None.
*/
/*============================================================================*/
void Factor_Shift_Cursor(void)
{
  pos_t = !pos_t;
  if(pos_t) Move_Cursor_Left(1);
  else      Move_Cursor_Right(1);
}

/*============================================================================*/
/*
 * Function      : Factor_Change_Parameter_Value.
 * Description   : Used to cursor left/right.
 * Parameters    : flag_id-increment/decrement flag.
 * Return        : None.
*/
/*============================================================================*/
void Factor_Change_Parameter_Value(uint8_t flag_id)
{
  if(flag_id == 0)
  {
    if(pos_t == 0)
    {
      if(byt2 < 9) byt2++;
      else         byt2 = 0;
      Lcd16x2_Chr(2,8, byt2+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 1)
    {
      if(byt1 < 9) byt1++;
      else         byt1 = 0;
      Lcd16x2_Chr(2,7, byt1+0x30);
      Move_Cursor_Left(1);
    }
  }
  else
  {
    if(pos_t == 0)
    {
      if(byt2 > 0) byt2--;
      else         byt2 = 9;
      Lcd16x2_Chr(2,8, byt2+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 1)
    {
      if(byt1 > 0) byt1--;
      else         byt1 = 9;
      Lcd16x2_Chr(2,7, byt1+0x30);
      Move_Cursor_Left(1);
    }
  }
}

/*============================================================================*/
/*
 * Function      : Display_Crane_Details_Menu.
 * Description   : Used to display crane parameter.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Crane_Details_Menu(void)
{
  Lcd16x2_Cmd(LCD_CLEAR);
  Select_Crane_Details_menu();
}

/*============================================================================*/
/*
 * Function      : Select_Crane_Details_menu.
 * Description   : Used to select crane parameter.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Select_Crane_Details_menu(void)
{
  char lbuf[20];
  
  switch(crane_detail_cnt)
  {
    case 1:
    Lcd16x2_Out(1,1,"Vertical Offset ");
    Lcd16x2_Out(2,1,"C:     m P:     ");

    pos_t = 0;
    byt1 = (uint8_t)(sys.para.vertical_offset/1000);
    byt2 = (uint8_t)((sys.para.vertical_offset%1000)/100);
    byt3 = (uint8_t)((sys.para.vertical_offset%100)/10);
    byt4 = (uint8_t)(sys.para.vertical_offset%10);

    sprintf(lbuf,"%.3f",((float)sys.para.vertical_offset)/1000.0);
    Lcd16x2_Out(2,12,lbuf);
    sprintf(lbuf,"%.3f",((float)sys.para.vertical_offset)/1000.0);
    Lcd16x2_Out(2,3,lbuf);
    break;
    case 2:
    Lcd16x2_Out(1,1,"Horizontal Ofset");
    Lcd16x2_Out(2,1,"C:     m P:     ");

    pos_t = 0;
    byt1 = (uint8_t)(sys.para.horizontal_offset/1000);
    byt2 = (uint8_t)((sys.para.horizontal_offset%1000)/100);
    byt3 = (uint8_t)((sys.para.horizontal_offset%100)/10);
    byt4 = (uint8_t)(sys.para.horizontal_offset%10);

    sprintf(lbuf,"%.3f",((float)sys.para.horizontal_offset)/1000.0);
    Lcd16x2_Out(2,12,lbuf);
    sprintf(lbuf,"%.3f",((float)sys.para.horizontal_offset)/1000.0);
    Lcd16x2_Out(2,3,lbuf);
    break;
    case 3:
    Lcd16x2_Out(1,1,"BmFtPin-RamPivot");
    Lcd16x2_Out(2,1,"C:     m P:     ");

    pos_t = 0;
    byt1 = (uint8_t)(sys.para.rampivot_offset/1000);
    byt2 = (uint8_t)((sys.para.rampivot_offset%1000)/100);
    byt3 = (uint8_t)((sys.para.rampivot_offset%100)/10);
    byt4 = (uint8_t)(sys.para.rampivot_offset%10);

    sprintf(lbuf,"%.3f",((float)sys.para.rampivot_offset)/1000.0);
    Lcd16x2_Out(2,12,lbuf);
    sprintf(lbuf,"%.3f",((float)sys.para.rampivot_offset)/1000.0);
    Lcd16x2_Out(2,3,lbuf);
    break;
    case 4:
    Lcd16x2_Out(1,1,"Bm Cntr Line Ofs");
    Lcd16x2_Out(2,1,"C:     m P:     ");

    pos_t = 0;
    byt1 = (uint8_t)(sys.para.bm_cntr_line_offset/1000);
    byt2 = (uint8_t)((sys.para.bm_cntr_line_offset%1000)/100);
    byt3 = (uint8_t)((sys.para.bm_cntr_line_offset%100)/10);
    byt4 = (uint8_t)(sys.para.bm_cntr_line_offset%10);

    sprintf(lbuf,"%.3f",((float)sys.para.bm_cntr_line_offset)/1000.0);
    Lcd16x2_Out(2,12,lbuf);
    sprintf(lbuf,"%.3f",((float)sys.para.bm_cntr_line_offset)/1000.0);
    Lcd16x2_Out(2,3,lbuf);
    break;
    case 5:
    Lcd16x2_Out(1,1,"Piston Diameter ");
    Lcd16x2_Out(2,1,"C:     m P:     ");

    pos_t = 0;
    byt1 = (uint8_t)(sys.para.piston_diameter/1000);
    byt2 = (uint8_t)((sys.para.piston_diameter%1000)/100);
    byt3 = (uint8_t)((sys.para.piston_diameter%100)/10);
    byt4 = (uint8_t)(sys.para.piston_diameter%10);

    sprintf(lbuf,"%.3f",((float)sys.para.piston_diameter)/1000.0);
    Lcd16x2_Out(2,12,lbuf);
    sprintf(lbuf,"%.3f",((float)sys.para.piston_diameter)/1000.0);
    Lcd16x2_Out(2,3,lbuf);
    break;
    case 6:
    Lcd16x2_Out(1,1,"  Rod Diameter  ");
    Lcd16x2_Out(2,1,"C:     m P:     ");

    pos_t = 0;
    byt1 = (uint8_t)(sys.para.rod_diameter/1000);
    byt2 = (uint8_t)((sys.para.rod_diameter%1000)/100);
    byt3 = (uint8_t)((sys.para.rod_diameter%100)/10);
    byt4 = (uint8_t)(sys.para.rod_diameter%10);

    sprintf(lbuf,"%.3f",((float)sys.para.rod_diameter)/1000.0);
    Lcd16x2_Out(2,12,lbuf);
    sprintf(lbuf,"%.3f",((float)sys.para.rod_diameter)/1000.0);
    Lcd16x2_Out(2,3,lbuf);
    break;
  }
  Move_Cursor_Left(1);
  Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      :        Crane_Detail_Shift_Cursor.
 * Description   :        Used to cursor left/right.
 * Parameters    :        flag_lr-left/right flag.
 * Return        :        None.
*/
/*============================================================================*/
void Crane_Detail_Shift_Cursor(uint8_t flag_lr)
{
  if(flag_lr == 0)                   //Shift cursor left
  {
    if(pos_t < 3)
    {
      pos_t++;
      if(pos_t == 3) Move_Cursor_Left(2);
      else           Move_Cursor_Left(1);
    }
    else
    {
      pos_t = 0;
      Move_Cursor_Right(4);
    }
  }
  else
  {
    if(pos_t > 0)
    {
      pos_t--;
      if(pos_t == 2) Move_Cursor_Right(2);
      else           Move_Cursor_Right(1);
    }
    else
    {
      pos_t = 3;
      Move_Cursor_Left(4);
    }
  }
}

/*============================================================================*/
/*
 * Function      :        Crane_Detail_Parameter_Value.
 * Description   :        Used to change(inc/dec) values.
 * Parameters    :        flag_id-increment/decrement flag.
 * Return        :        None.
*/
/*============================================================================*/
void Crane_Detail_Parameter_Value(uint8_t flag_id)
{
  if(flag_id == 0)
  {
    if(pos_t == 0)
    {
      if(byt4 < 9) byt4++;
      else         byt4 = 0;
      Lcd16x2_Chr(2,7, byt4+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 1)
    {
      if(byt3 < 9) byt3++;
      else         byt3 = 0;
      Lcd16x2_Chr(2,6, byt3+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 2)
    {
      if(byt2 < 9) byt2++;
      else         byt2 = 0;
      Lcd16x2_Chr(2,5, byt2+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 3)
    {
      if(byt1 < 9) byt1++;
      else         byt1 = 0;
      Lcd16x2_Chr(2,3, byt1+0x30);
      Move_Cursor_Left(1);
    }
  }
  else
  {
    if(pos_t == 0)
    {
      if(byt4 > 0) byt4--;
      else         byt4 = 9;
      Lcd16x2_Chr(2,7, byt4+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 1)
    {
      if(byt3 > 0) byt3--;
      else         byt3 = 9;
      Lcd16x2_Chr(2,6, byt3+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 2)
    {
      if(byt2 > 0) byt2--;
      else         byt2 = 9;
      Lcd16x2_Chr(2,5, byt2+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 3)
    {
      if(byt1 > 0) byt1--;
      else         byt1 = 9;
      Lcd16x2_Chr(2,3, byt1+0x30);
      Move_Cursor_Left(1);
    }
  }
}

/*============================================================================*/
/*
 * Function      : Update_Crane_Details.
 * Description   : Used to calculate crane parameters.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Update_Crane_Details(void)
{
  char lbuf[20];
  
  switch(crane_detail_cnt-1)
  {
    case 1:
    sys.para.vertical_offset = byt1*1000 + byt2*100 + byt3*10 + byt4;
    
    f11 = (sys.para.vertical_offset*1.0);        // (a) x.xxx
    f11 = (f11/1000.0);
    break;
    case 2:
    sys.para.horizontal_offset = byt1*1000 + byt2*100 + byt3*10 + byt4;
    
    f12 = (sys.para.horizontal_offset*1.0);        // (b) x.xxx
    f12 = (f12/1000.0);
    
    if(sys.para.horizontal_offset !=0)
    {
      f13 = atan(f11/f12);
      Gamma_Int_Rad = (uint16_t)(f13*1000);        // Rad

      f13 = sin(Gamma_Int_Rad/1000.0);
      sin_Gamma_Int = (f13*1000);

      f13 = cos(Gamma_Int_Rad/1000.0);
      cos_Gamma_Int = (f13*1000);

      Lcd16x2_Cmd(LCD_CLEAR);
      Lcd16x2_Out(1,1,"  Gamma_Rad     ");
      sprintf(lbuf,"     %.3f      ",((float)Gamma_Int_Rad)/1000.0);
      Lcd16x2_Out(2,1,lbuf);
      Delay_1ms(2000);
      
      Lcd16x2_Cmd(LCD_CLEAR);
      Lcd16x2_Out(1,1,"  SinGamma_Rad  ");
      sprintf(lbuf,"     %.3f      ",((float)sin_Gamma_Int)/1000.0);
      Lcd16x2_Out(2,1,lbuf);
      Delay_1ms(2000);

      Lcd16x2_Cmd(LCD_CLEAR);
      Lcd16x2_Out(1,1,"  CosGamma_Rad  ");
      sprintf(lbuf,"     %.3f      ",((float)cos_Gamma_Int)/1000.0);
      Lcd16x2_Out(2,1,lbuf);
      Delay_1ms(2000);
    }
    break;
    case 3:
    sys.para.rampivot_offset = byt1*1000 + byt2*100 + byt3*10 + byt4;
    
    f11 = ((float)sys.para.rampivot_offset*1.0);        // x.xxx
    f11 = (f11/1000.0);

    f12 = ((float)sys.para.vertical_offset*1.0);        // x.xxx
    f12 = (f12/1000.0);

    f13 = ((float)sys.para.horizontal_offset*1.0);        // x.xxx
    f13 = (f13/1000.0);

    Den_Float = sqrt((f12*f12)+(f13*f13));

    if(Den_Float != 0)
    {
      f12 = (f11)*(1/Den_Float);
      constK_Int = (uint16_t)(f12*1000);

      Lcd16x2_Cmd(LCD_CLEAR);
      Lcd16x2_Out(1,1,"   K=          ");
      sprintf(lbuf,"     %.3f      ",((float)constK_Int)/1000.0);
      Lcd16x2_Out(2,1,lbuf);
      Delay_1ms(2000);
    }
    break;
    case 4:
    sys.para.bm_cntr_line_offset = byt1*1000 + byt2*100 + byt3*10 + byt4;

    break;
    case 5:
    sys.para.piston_diameter = byt1*1000 + byt2*100 + byt3*10 + byt4;

    f11 = (sys.para.piston_diameter*1.0);        // x.xxx
    f11 = (f11/2000.0);

    PistonArea_Int = (uint32_t)(PI*f11*f11*100000.0);

    Lcd16x2_Cmd(LCD_CLEAR);
    Lcd16x2_Out(1,1,"   PistonArea   ");
    sprintf(lbuf,"    %.5f     ",((float)PistonArea_Int)/100000.0);
    Lcd16x2_Out(2,1,lbuf);
    Delay_1ms(2000);
    break;
    case 6:
    sys.para.rod_diameter = byt1*1000 + byt2*100 + byt3*10 + byt4;
    
    f11 = (sys.para.rod_diameter*1.0);        // x.xxx
    f11 = (f11/2000.0);

    RodArea_Int = (uint32_t)(PI*f11*f11*100000.0);

    DiffArea_Int = (PistonArea_Int - RodArea_Int);

    Lcd16x2_Cmd(LCD_CLEAR);
    Lcd16x2_Out(1,1,"    RodArea     ");
    sprintf(lbuf,"    %.5f     ",((float)RodArea_Int)/100000.0);
    Lcd16x2_Out(2,1,lbuf);
    Delay_1ms(2000);
    break;
  }
  Lcd16x2_Cmd(LCD_CLEAR);
  Lcd16x2_Out(1,1,"   DATA SAVED   ");
  Delay_1ms(2000);
}

/*============================================================================*/
/*
 * Function      : Display_Crane_Models_Menu.
 * Description   : Used to display crane model menu.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Crane_Models_Menu(void)
{
  uint16_t TempCount,id_cnt,temp_max;
  char lbuf[50];
  
  flash_page_addr = ONE_SECTOR_SIZE+18; //start page address of first cane
  sys.para.crane_page_index = (SPIFlash_Read_Byte(flash_page_addr)*256)+SPIFlash_Read_Byte(flash_page_addr+1);
  
  //Find out maximum no. of cranes. Number 8 indicates that each directory page have maximum 8 cranes
  temp_max = 8*sys.para.crane_page_index;      //8*1=8  8*2=16  8*3=24 like wise
  for(id_cnt=0; id_cnt<temp_max; id_cnt++)
  {
    flash_page_addr = ONE_SECTOR_SIZE+(id_cnt*32);
    crane_ids[id_cnt] = (SPIFlash_Read_Byte(flash_page_addr)*256) + SPIFlash_Read_Byte(flash_page_addr+1);
    
    if(crane_ids[id_cnt] == 0) break;
  }
  
  mv.max = id_cnt;
  mv.min = 1;
  crane_id = 1;
  
  sprintf(lbuf,"id_cnt=%02d index_start=%d\r\n",id_cnt,sys.para.crane_page_index);
//  UART_Send_String(UART_MODULE1,lbuf);
  
  flash_page_addr = ONE_SECTOR_SIZE+2+(crane_id-1)*32;//skip 2 bytes of id
  
  for(TempCount=0;TempCount<16;TempCount++)
  {
   crane_make[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
  }
  Lcd16x2_Cmd(LCD_CLEAR);
  sprintf(lbuf,"CRANE ID: %02d",crane_ids[crane_id-1]);
  Lcd16x2_Out(1,1,lbuf);
  Lcd16x2_Out(2,1,crane_make);
}

/*============================================================================*/
/*
 * Function      : Select_Crane_Model.
 * Description   : Used to select crane model.
 * Parameters    : flag_id-change crane model.
 * Return        : None.
*/
/*============================================================================*/
void Select_Crane_Model(uint8_t flag_id)
{
  uint16_t TempCount;
  char lbuf[20];

  if(flag_id == 0)
  {
    if(crane_id < mv.max) crane_id++;
    else                  crane_id = mv.min;
  }
  else
  {
    if(crane_id > mv.min) crane_id--;
    else                  crane_id = mv.max;
  }
  
  sprintf(lbuf,"%02d    ",crane_ids[crane_id-1]);
  Lcd16x2_Out(1,11,lbuf);
  
  flash_page_addr = ONE_SECTOR_SIZE+2+(crane_id-1)*32;//skip 2 bytes of id
  
  for(TempCount=0;TempCount<16;TempCount++)
  {
   crane_make[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
  }
  Lcd16x2_Out(2,1,crane_make);
}

void Select_Sticker_Type(void)
{
  if(prv16_val1 == NEW)
  {
    Lcd16x2_Out(2,4,"NEW");
  }
  else
  {
    Lcd16x2_Out(2,4,"OLD");
  }
}


void Display_Min_Max_PCurve_Menu(void)
{
    min_max_pcurve_flag = 0;         //0 for min and 1 for known load calibration
    Lcd16x2_Out(1,1,"NO LOAD PCURVE <");
    Lcd16x2_Out(2,1,"KNOWN LD PCURVE ");
}


void Select_Min_Max_PCurve_Menu(void)
{
    if(min_max_pcurve_flag == 0)
    {
        Lcd16x2_Out(1,1,"NO LOAD PCURVE <");
        Lcd16x2_Out(2,1,"KNOWN LD PCURVE ");
    }
    else
    {
        Lcd16x2_Out(1,1,"NO LOAD PCURVE  ");
        Lcd16x2_Out(2,1,"KNOWN LD PCURVE<");
    }
}

void Display_Known_Load_Value(void)
{
    char lbuf[20];
    
    prv16_val1 = known_load_pcurve; //sys.para.known_load_calib
    
    Lcd16x2_Out(1,1,"KNWN LOAD PCURVE");
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

/*============================================================================*/
/*
 * Function      : Factory_Save_Settings.
 * Description   : Used to update the site setting values in SPI flash.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Factory_Save_Settings(void)
{  
  SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

  switch(mv.factory_set)
  {
    case CALIB_PRESSURE_P1_MIN:
        sys.para.calib_pressure1_min = byt1*1000 + byt2*100 + byt3*10 + byt4;
        sys.para.calib_P1LowAdcCount = byt5*1000 + byt6*100 + byt7*10 + byt8;
    break;
    case CALIB_PRESSURE_P1_MAX:
        sys.para.calib_pressure1_max = byt1*1000 + byt2*100 + byt3*10 + byt4;
        sys.para.calib_P1HighAdcCount = byt5*1000 + byt6*100 + byt7*10 + byt8;
    break;
    case CALIB_PRESSURE_P2_MIN:
        sys.para.calib_pressure2_min = byt1*1000 + byt2*100 + byt3*10 + byt4;
        sys.para.calib_P2LowAdcCount = byt5*1000 + byt6*100 + byt7*10 + byt8;
    break;
    case CALIB_PRESSURE_P2_MAX:
        sys.para.calib_pressure2_max = byt1*1000 + byt2*100 + byt3*10 + byt4;
        sys.para.calib_P2HighAdcCount = byt5*1000 + byt6*100 + byt7*10 + byt8;
    break;
    case EN_LOAD_AVERAGING_VALUE:
        sys.para.load_avg_stat_bit = prv8_val1;
    break;
    case WINDOW_SAMPLES_SIZE:
        sys.para.window_sample_size = (uint8_t)common_long;
    break;
    case NUM_OF_CYLINDERS:
        sys.para.num_of_cylinders = (uint8_t)common_long;
    break;
    case WRITE_TO_MEMORY:
    break;
    case CRANE_DETAILS:
    break;
    case SET_BM_ANGLE_MIN:
        sys.para.cal_angle_min = byt1*100 + byt2*10 + byt3;
        sys.para.cal_angle_min_cnt = byt4*1000 + byt5*100 + byt6*10 + byt7;
    break;
    case SET_BM_ANGLE_MAX:
        sys.para.cal_angle_max = byt1*100 + byt2*10 + byt3;
        sys.para.cal_angle_max_cnt = byt4*1000 + byt5*100 + byt6*10 + byt7;
    break;
    case SET_BM_LENGTH_MIN:
        sys.para.cal_len_min = byt1*100 + byt2*10 + byt3;
        sys.para.cal_len_min_cnt = byt4*1000 + byt5*100 + byt6*10 + byt7;
        sys.para.bl_adc_cnt[1] = sys.para.cal_len_min_cnt;
    break;
    case SET_BM_LENGTH_MAX:
        sys.para.cal_len_max = byt1*100 + byt2*10 + byt3;
        sys.para.cal_len_max_cnt = byt4*1000 + byt5*100 + byt6*10 + byt7;
    break;
    /*
    case SET_CALIB_DATE_TIME:

    break;
    */
    case SET_CRANE_MODEL:
        flash_page_addr = ONE_SECTOR_SIZE+18 + (crane_id-1)*32;
        sys.para.crane_page_index = (SPIFlash_Read_Byte(flash_page_addr)*256)+SPIFlash_Read_Byte(flash_page_addr+1);
        
        Lcd16x2_Cmd(LCD_CLEAR);
        Read_Startup_SPIFlash();
        Update_System_Parameters();

        Lcd16x2_Out(1,1,"   Crane Make   "); //crane_make
        Lcd16x2_Out(2,1,crane_make);
        Delay_1ms(2000);

        Lcd16x2_Out(1,1,"   Crane Model  "); //crane_model
        Lcd16x2_Out(2,1,crane_model);
        Delay_1ms(2000);

        Lcd16x2_Out(1,1,"   Crane Type   ");//crane_type
        Lcd16x2_Out(2,1,crane_type);
        Delay_1ms(2000);
    break;
    case SET_BAUDRATE:
        sys.para.baudrate = (uint8_t)common_long;
    break;
    case ERASE_DATA_LOGS:
        sys.para.data_log_cntr = 0;
    break;
    case SELECT_SENSOR:
        sys.para.sel_sensor = sensor_cnt;
    break;
    case DEFAULT_BL_ADC_COUNT:
        Lcd16x2_Out(1,1,"Default BLCnt   ");
        Lcd16x2_Out(2,1,"Set in Progress.");

        sys.para.bl_adc_cnt[2] = 1607;

        sys.para.bl_adc_cnt[3] = 1994;

        sys.para.bl_adc_cnt[4] = 2122;

        sys.para.bl_adc_cnt[5] = 2246;

        sys.para.bl_adc_cnt[6] = 2366;
        Delay_1ms(2000);
    break;
    case WINDOW_SAMPLES_SIZE1:
        sys.para.window_sample_size1 = (uint8_t)common_long;
    break;
    case STICKER_TYPE:
        sys.para.sticker_type = prv16_val1;
    break;
    case SET_INSALLATION_DATE:
        sys.para.insta_dd = byt1*10 + byt2;
        sys.para.insta_mm = byt3*10 + byt4;
        sys.para.insta_yy = (uint16_t)byt5*1000 + byt6*100 +byt7*10 + byt8;
    break;
    case SET_PERCENTAGE_STATUS:
        sys.para.perc_fact_stat_bit = prv8_val1;    
        sys.para.fact = byt1*10 + byt2;
    break;
    case SET_CORRECTION_LOAD:
        sys.para.correction_load = byt1*1000 + byt2*100 + byt3*10 + byt4;
    break;
    case EN_NUMBER_OF_CALIB:
        sys.para.num_cal = prv8_val1;
    break;
    case SET_SO_NUMBER:
        sys.para.so_number = common_long;
    break;
    case P1P2_TO_RS232_PC:
    break;
    case SET_RADIUS_CUTOFF:
        sys.para.Radius_Cutoff = (uint8_t)common_long;  
    break;
    case SET_MANBASKET_DUTY:
        if(sys.para.Select_System == PNC_FORK)
            sys.para.fork_duty = (uint8_t)common_long;
        else
            sys.para.manbas_duty = (uint8_t)common_long;  
    break;    
    case SET_MANBASKET_CHANN:
        sys.para.manbas_chann = (uint8_t)common_long;  
    break; 
    case SELECT_LENGTH_DRUM:
        sys.para.sel_len_drum = prv8_val1;
    break;
    case SELECT_SYSTEM:
        disp_error = 0;
        sys.para.Select_System = (uint16_t)common_long;  
        Clear_System_Flags();
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
