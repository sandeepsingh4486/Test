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
 * Function      :        Display_Operator_View_Menu.
 * Description   :        Used to display operator's view menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Operator_View_Menu(void)
{
    mv.max = 13;
    mv.min = 1;
    
    Lcd16x2_Cmd(LCD_CLEAR);
    
    Select_Operator_View_Menu();
}

/*============================================================================*/
/*
 * Function      : Select_Operator_View_Menu.
 * Description   : Used to select operator's view menus.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Select_Operator_View_Menu(void)
{
    char lbuf[20];

    sprintf(lbuf,"SET CODE: %03d   ",mv.operator_view-1);
    Lcd16x2_Out(1,1,lbuf);

    switch(mv.operator_view)
    {
        case PRESS1_COUNT:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                Lcd16x2_Out(2,1,"PRESSURE COUNTS:");
            }
            else
            {
                Lcd16x2_Out(2,1,"PRESSURE P1 CNT:");
            }
        break;
        case PRESS2_COUNT:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                Lcd16x2_Out(2,1,"TILT ANGLE CNT: ");
            }
            else
            {
                Lcd16x2_Out(2,1,"PRESSURE P2 CNT:");
            }
        break;
        case BMLEN_COUNT:
        Lcd16x2_Out(2,1,"BOOM LEN CNT:   ");
        break;
        case BMANGL_COUNT:
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                Lcd16x2_Out(2,1,"KNUC ANG COUNT: ");
            else
                Lcd16x2_Out(2,1,"BOOM ANG CNT:   ");
        break;
        case BM_MANGL_COUNT:
        Lcd16x2_Out(2,1,"BOOM MANG CNT:  ");
        break;
        case SET_POINTS:
        Lcd16x2_Out(2,1,"SP SETTING:     ");
        break;
        case VIEW_BM_OFFSET:
        Lcd16x2_Out(2,1,"BOOM OFFSET:    ");
        break;
        case VIEW_HD_OFFSET:
        Lcd16x2_Out(2,1,"BM HEAD OFFSET: ");
        break;
        case VIEW_ALL_PRESS_CNTS:
            Lcd16x2_Out(2,1,"PRESSURE CNT:   ");
        break;
        case VIEW_DT_TM:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                Lcd16x2_Out(2,1,"VIEW OTG CAL MIN");
            }
            else
            {
                Lcd16x2_Out(2,1," NOT APPLICABLE ");
            }
        break;
        case VIEW_LOADCELL_CNTS:
            if((sys.para.Select_System == ACE_MANBASKET_HXP)||(sys.para.Select_System == TMC_MANBASKET)||
               (sys.para.Select_System == TMC_MANBASKET2))
                Lcd16x2_Out(2,1,"LOADCELL COUNTS:");
            else
                Lcd16x2_Out(2,1," NOT APPLICABLE ");
        break;
        case VIEW_GPS_TIME:
            Lcd16x2_Out(2,1,"GPS DATE & TIME:");
        break;
        case VIEW_ZLD_PCURVE:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(2,1,"VIEW CALIB POINT");
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                Lcd16x2_Out(2,1,"VIEW OTG CAL MAX");
            }
            else
            {
                Lcd16x2_Out(2,1,"VIEW ZLOAD CURVE");
            }        
        break;
//        case 11:
//        Lcd16x2_Out(2,1,"VIEW TEMPERATURE");
//        break;
//        case 12:
//        Lcd16x2_Out(2,1,"SAVE LIFTED P1P2");
//        break;
//        case 13:
//        Lcd16x2_Out(2,1,"VIEW LIFTED P1P2");
//        break;
    }
}

/*============================================================================*/
/*
 * Function      : Operator_Viewing.
 * Description   : Used to view settings.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Operator_Viewing(void)
{
    char lbuf[20];
    uint16_t temp_len;

    switch(mv.operator_view)
    {
        case PRESS1_COUNT:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sprintf(lbuf,"P1:%04d  P2:%04d",can_p1_cnt,can_p2_cnt);
                Lcd16x2_Out(1,1,lbuf);
                sprintf(lbuf,"P3:%04d  P4:%04d",can_p3_cnt,can_p4_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
            else
            {
                Lcd16x2_Out(1,1,"PRESSURE P1 CNT:");
                sprintf(lbuf,"      %04d      ",p1_pressure_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
        break;
        case PRESS2_COUNT:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                Lcd16x2_Out(1,1,"TILT ANGLE CNT: ");
                sprintf(lbuf,"X:%04d    Y:%04d",Tilt_1_X_cnt,Tilt_1_Y_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
            else
            {
                Lcd16x2_Out(1,1,"PRESSURE P2 CNT:");
                sprintf(lbuf,"      %04d      ",p2_pressure_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
        break;
        case BMLEN_COUNT:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(1,1,"FORK HIGHT CNT: ");
                sprintf(lbuf,"      %04d      ",len_adc_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
            else
            {
                Lcd16x2_Out(1,1,"LEN CNT   BM LEN");
                temp_len = bm_length-sys.para.bm_length_min;
                sprintf(lbuf,"  %04d     %.1fM ",len_adc_cnt,((float)temp_len)/10.0);
                Lcd16x2_Out(2,1,lbuf);
            }
        break;
        case BMANGL_COUNT:
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                Lcd16x2_Out(2,1,"KNUC ANG COUNT: ");
            else
                Lcd16x2_Out(1,1,"BOOM ANG CNT:   ");
            sprintf(lbuf,"      %04d      ",ang_adc_cnt);
            Lcd16x2_Out(2,1,lbuf);
        break;
        case BM_MANGL_COUNT:
            Lcd16x2_Out(1,1,"BOOM MANG CNT:  ");
            sprintf(lbuf,"      %04d      ",Main_ang_adc_cnt);
            Lcd16x2_Out(2,1,lbuf);
        break;
        case SET_POINTS:
            sprintf(lbuf,"1:%03d     ",sys.para.sp1_perc);
            Lcd16x2_Out(1,1,lbuf);
            Lcd16x2_Chr(1,6, '%');
            sprintf(lbuf,"2:%03d",sys.para.sp2_perc);
            Lcd16x2_Out(1,11,lbuf);
            Lcd16x2_Chr(1,16, '%');
            sprintf(lbuf,"3:%03d     ",sys.para.sp3_perc);
            Lcd16x2_Out(2,1,lbuf);
            Lcd16x2_Chr(2,6, '%');
            sprintf(lbuf,"4:%03d",sys.para.sp4_perc);
            Lcd16x2_Out(2,11,lbuf);
            Lcd16x2_Chr(2,16, '%');
        break;
        case VIEW_BM_OFFSET:
            Lcd16x2_Out(1,1,"BOOM OFFSET:    ");
            sprintf(lbuf,"     %.01f       ",((float)sys.para.bm_offset)/10.0);
            Lcd16x2_Out(2,1,lbuf);
        break;
        case VIEW_HD_OFFSET:
            Lcd16x2_Out(1,1,"BM HEAD OFFSET: ");
            sprintf(lbuf,"     %.01f       ",((float)sys.para.bm_head_offset)/10.0);
            Lcd16x2_Out(2,1,lbuf);
        break;
        case VIEW_ALL_PRESS_CNTS:            
            Lcd16x2_Out(1,1,"P1:     BA:  ﬂ  ");
            Lcd16x2_Out(2,1,"P2:     BL:     ");
        break;
        case VIEW_DT_TM:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sprintf(lbuf,"P1:%04d  P2:%04d",sys.para.forkcalib_press_min[0][1],sys.para.forkcalib_press_min[1][1]);
                Lcd16x2_Out(1,1,lbuf);
                sprintf(lbuf,"P3:%04d  P4:%04d",sys.para.forkcalib_press_min[2][1],sys.para.forkcalib_press_min[3][1]);
                Lcd16x2_Out(2,1,lbuf);
            }
            else
            {
                Lcd16x2_Out(1,1,"DATE & TIME:    ");
                sprintf(lbuf,"%02d/%02d/%02d   %02d:%02d",day,month,year%100,hour,minute);
                Lcd16x2_Out(2,1,lbuf);
            }
        break;
        case VIEW_LOADCELL_CNTS:
            Lcd16x2_Out(1,1,"LOADCELL COUNTS:");
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                sprintf(lbuf,"      %05lu     ",(uint32_t)can_loadcell_cnt);
            else
                sprintf(lbuf,"      %05d     ",loadcell_cnt);
            Lcd16x2_Out(2,1,lbuf);
        break;
        case VIEW_GPS_TIME:
            Lcd16x2_Out(1,1,"GPS DATE & TIME:");
            sprintf(lbuf,"%02d/%02d/%02d   %02d:%02d",day,month,year%100,hour,minute);
            Lcd16x2_Out(2,1,lbuf);
        break;
        case VIEW_ZLD_PCURVE:
            if(sys.para.Select_System == FORK_LIFT)
            {
                temp_duty_indx = 1;
                Display_MinMax_Option_Menu();
                menu_stat = VIEW_PRESS_CALIB_POINT_PAGE1;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sprintf(lbuf,"P1:%04d  P2:%04d",sys.para.forkcalib_press_max[0][1],sys.para.forkcalib_press_max[1][1]);
                Lcd16x2_Out(1,1,lbuf);
                sprintf(lbuf,"P3:%04d  P4:%04d",sys.para.forkcalib_press_max[2][1],sys.para.forkcalib_press_max[3][1]);
                Lcd16x2_Out(2,1,lbuf);
            }
            else
            {
                temp_duty_indx = sys.para.duty;
                Display_Calib_Hook_Load_Menu();
                Calib_Hook_Load_Cursor_Position();
                menu_stat = VIEW_PC_PAGE1;
            }            
        break;
//        case 11:
//            Lcd16x2_Cmd(LCD_CLEAR);
//            Lcd16x2_Out(1,1,"  TEMPERATURE:  ");
//        break;
//        case 12:
//            temp_duty_indx = 4;
//            Display_Dummy_Calib_Length_Menu();
//            menu_stat = OPER_DUMMY_LOAD_CALIB_PAGE1;
//        break;
//        case 13:
//            Display_Dummy_Calib_Length_Menu();
//            menu_stat = VIEW_LIFTED_PC_PAGE1;
//        break;
    }
}

void Display_MinMax_Option_Menu(void)
{
    if(temp_duty_indx == 1)
    {
        Lcd16x2_Out(1,1,"PRESS CALIB MIN<");
        Lcd16x2_Out(2,1,"PRESS CALIB MAX:");
    }
    else
    {
        Lcd16x2_Out(1,1,"PRESS CALIB MIN:");
        Lcd16x2_Out(2,1,"PRESS CALIB MAX<");
    }
}

void Display_Fork_MinMax_Press_View(uint8_t pindex, uint8_t minmax)
{
    char lbuf[20];
    
    if(minmax == 0)
    {
        sprintf(lbuf,"Calib Pres Min %01d",pindex+1);
        Lcd16x2_Out(1,1,lbuf);

        prv16_val1 = sys.para.forkcalib_press_min[pindex][0];   //Pressure value
        prv16_val2 = sys.para.forkcalib_press_min[pindex][1];   //Pressure count        
    }
    else
    {
        sprintf(lbuf,"Calib Pres Max %01d",pindex+1);
        Lcd16x2_Out(1,1,lbuf);

        prv16_val1 = sys.para.forkcalib_press_max[pindex][0];   //Pressure value
        prv16_val2 = sys.para.forkcalib_press_max[pindex][1];   //Pressure count
    }
    
    sprintf(lbuf,"%04.1fT %04d %04.1fM",((float)prv16_val1)/10.0,prv16_val2,((float)sys.para.fork_len_region[pindex])/10.0);
    Lcd16x2_Out(2,1,lbuf);
}

/*============================================================================*/
/*
 * Function      : Display_Dummy_Calib_Length_Menu.
 * Description   : Used to display select length to be calibrated.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Dummy_Calib_Length_Menu(void)
{
  char cbuf[50];

  length_array_ptr = ((temp_duty_indx-1)*5);
  mv.max = (length_array_ptr + (sys.para.duty_type[temp_duty_indx-1]-1));
  mv.min = length_array_ptr;
  #ifdef DEBUG_MSG
  sprintf(cbuf,"pointer=%d min=%d max=%d\r\n",length_array_ptr,mv.min,mv.max);
  //UART_Send_String(UART_MODULE1,cbuf);
  #endif
  Lcd16x2_Cmd(LCD_CURSOR_OFF);
  if((sys.para.duty_type[temp_duty_indx-1] >= 1) && (sys.para.duty_type[temp_duty_indx-1] < 6))
  {
    Lcd16x2_Cmd(LCD_CLEAR);
    Lcd16x2_Out(1,1,"SEL CALIB.LENGTH");

    if(sys.para.length_array[length_array_ptr]>99)
      sprintf(cbuf,"%.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
    else
      sprintf(cbuf,"0%.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
    Lcd16x2_Out(2,7,cbuf);
  }
}


/*============================================================================*/
/*
 * Function      : Display_Pressure_Counts.
 * Description   : Used to view stored pressure curve P1 and P2 counts for perticular angle.
 * Parameters    : flag_id-increment/decrement flag.
 * Return        : None.
*/
/*============================================================================*/
void Display_Pressure_Curve_Counts(uint8_t flag_id)
{
    char pbuf[20];

    if(flag_id == 0)                   //Increment
    {
      if(CrtBoomAngle < 90) CrtBoomAngle++;
      else                  CrtBoomAngle = 1;
    }
    else
    {
      if(CrtBoomAngle > 1) CrtBoomAngle--;
      else                 CrtBoomAngle = 90;
    }
    sprintf(pbuf,"%04d",pc_buf[0][CrtBoomAngle-1]);
    Lcd16x2_Out(1,4,pbuf);
    sprintf(pbuf,"%02dﬂ",CrtBoomAngle);
    Lcd16x2_Out(1,14,pbuf);
    sprintf(pbuf,"%04d",pc_buf[1][CrtBoomAngle-1]);
    Lcd16x2_Out(2,4,pbuf);
}

/*============================================================================*/
/*
 * Function      : Show_Live_ADC_Count.
 * Description   : Used to show live values in operator view setting.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Show_Live_ADC_Count(void)
{
    char lbuf[20];
    uint16_t temp_len;

    switch(mv.operator_view)
    {
        case PRESS1_COUNT:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sprintf(lbuf,"%04d",can_p1_cnt);
                Lcd16x2_Out(1,4,lbuf);
                sprintf(lbuf,"%04d",can_p2_cnt);
                Lcd16x2_Out(1,13,lbuf);
                sprintf(lbuf,"%04d",can_p3_cnt);
                Lcd16x2_Out(2,4,lbuf);
                sprintf(lbuf,"%04d",can_p4_cnt);
                Lcd16x2_Out(2,13,lbuf);
            }
            else
            {
                sprintf(lbuf,"%04d",p1_pressure_cnt);
                Lcd16x2_Out(2,7,lbuf);
            }
        break;
        case PRESS2_COUNT:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sprintf(lbuf,"X:%04d    Y:%04d",Tilt_1_X_cnt,Tilt_1_Y_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
            else
            {
                sprintf(lbuf,"%04d",p2_pressure_cnt);
                Lcd16x2_Out(2,7,lbuf);
            }
        break;
        case BMLEN_COUNT:
            if(sys.para.Select_System == FORK_LIFT)
            {
                sprintf(lbuf,"%04d",len_adc_cnt);
                Lcd16x2_Out(2,7,lbuf);
            }
            else
            {
                sprintf(lbuf,"%04d",len_adc_cnt);
                Lcd16x2_Out(2,3,lbuf);
                
                temp_len = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt);
                
                if(temp_len<100)    sprintf(lbuf,"0%.1fM",((float)temp_len)/10.0);
                else                sprintf(lbuf,"%.1fM",((float)temp_len)/10.0);    
                Lcd16x2_Out(2,12,lbuf);
            }
        break;
        case BMANGL_COUNT:
            sprintf(lbuf,"%04d",ang_adc_cnt);
            Lcd16x2_Out(2,7,lbuf);
        break;
        case BM_MANGL_COUNT:
            sprintf(lbuf,"%04d",Main_ang_adc_cnt);
            Lcd16x2_Out(2,7,lbuf);
        break;
        case VIEW_ALL_PRESS_CNTS:
            
            sprintf(lbuf,"%04d",p1_pressure_cnt);
            Lcd16x2_Out(1,4,lbuf);
            
            TempDispBoomAngle = (bm_angle/10);
            sprintf(lbuf,"%02dﬂ ",TempDispBoomAngle);
            Lcd16x2_Out(1,13,lbuf);
            
            sprintf(lbuf,"%04d",p2_pressure_cnt);
            Lcd16x2_Out(2,4,lbuf);

            if(TotalBmLength > 999)
            {
              sprintf(lbuf,"%.1f",((float)TotalBmLength)/10.0);
              Lcd16x2_Out(2,12,lbuf);
            }
            else if((TotalBmLength < 1000)&&(TotalBmLength > 99))
            {
              sprintf(lbuf,"%.1fM",((float)TotalBmLength)/10.0);
              Lcd16x2_Out(2,12,lbuf);
            }
            else if(TotalBmLength < 100)
            {
              sprintf(lbuf,"0%.1fM",((float)TotalBmLength)/10.0);
              Lcd16x2_Out(2,12,lbuf);
            }
        break;
        case VIEW_LOADCELL_CNTS:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sprintf(lbuf,"      %05lu    ",(uint32_t)can_loadcell_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
            else
            {
                sprintf(lbuf,"      %05d     ",loadcell_cnt);
                Lcd16x2_Out(2,1,lbuf);
            }
        break;
        case VIEW_GPS_TIME:
            sprintf(lbuf,"%02d/%02d/%02d   %02d:%02d",day,month,year%100,hour,minute);
            Lcd16x2_Out(2,1,lbuf);
        break;
//        case 15:
//            if(temp_interval_cnt == 0)
//            {
//              temp_interval_cnt = 200;
//            }
//        break;
    }
}

/*============================================================================*/
/*
 * Function      :        Display_Operator_Set_Menu.
 * Description   :        Used to display operator setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Operator_Set_Menu(void)
{
    mv.max = 3;
    mv.min = 1;

    Lcd16x2_Cmd(LCD_CLEAR);

    Select_Operator_Set_Menu();
}

/*============================================================================*/
/*
 * Function      :        Select_Operator_Set_Menu.
 * Description   :        Used to select operator setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Select_Operator_Set_Menu(void)
{
    char lbuf[20];

    sprintf(lbuf,"SET CODE: %03d   ",mv.operator_set+49);
    Lcd16x2_Out(1,1,lbuf);

    switch(mv.operator_set)
    {
        case SET_DUTY:
            Lcd16x2_Out(2,1,"SET DUTY:       ");
            if(sys.para.duty == 0) sys.para.duty = 1;
        break;
        case SET_FALLS:
            Lcd16x2_Out(2,1,"SET FALLS:      ");
            prv8_val1 = sys.para.falls_cnt;
        break;
        case SET_UOM:
            Lcd16x2_Out(2,1,"SET UOM:        ");
            prv8_val1 = sys.para.sel_uom;
        break;
    }
}

/*============================================================================*/
/*
 * Function      :        Operator_Change_Parameter_Value.
 * Description   :        Used to change(inc/dec) values.
 * Parameters    :        flag_id-increment/decrement flag.
 * Return        :        None.
*/
/*============================================================================*/
void Operator_Change_Parameter_Value(uint8_t flag_id)
{
    char ubuf[20];
    
    switch(mv.operator_set)
    {
        case SET_DUTY:
            if(flag_id == 0)
            {
              sys.para.duty++;
              if(sys.para.duty> lc_total_duty+1)  sys.para.duty= 1;         //For marching duty
            }
            else
            {
              sys.para.duty--;
              if(sys.para.duty< 1)  sys.para.duty = lc_total_duty+1;
            }
            Choose_Duty();
        break;
        case SET_FALLS:
            if(flag_id == 0)    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
            else                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
            sprintf(ubuf,"%02d",(uint8_t)common_long);
            Lcd16x2_Out(2,4,ubuf);
            Move_Cursor_Left(pos_t+1);
        break;
        case SET_UOM:
            prv8_val1 = !prv8_val1;
            Choose_UOM();
        break;
    }
}

/*============================================================================*/
/*
 * Function      : Choose_Duty.
 * Description   : Used to choose duty.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Choose_Duty(void)
{
    if(sys.para.duty <= lc_total_duty)
    {
        Duty_Hint(sys.para.duty);
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            op.relay1action = OUTPUT_OFF;
//            op.relay2action = OUTPUT_OFF;
            op.hooteraction = OUTPUT_OFF;
            
            op.buzzaction = OUTPUT_OFF;
            can_buzz_stat = OUTPUT_OFF;
        }
    }
    else if(sys.para.duty == lc_total_duty+1)
    {
        Lcd16x2_Out(1,1,"  SLI Inactive  ");
        Lcd16x2_Out(2,1,"  Rigging Duty  ");
        
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            if(sys.para.fail_safe_stat_bit == 0)
            {
                op.relay1action = OUTPUT_ON;
//                op.relay2action = OUTPUT_ON;
            }
            else
            {
                op.relay1action = OUTPUT_OFF;
//                op.relay2action = OUTPUT_OFF;
            }
            op.buzzaction = OUTPUT_BLINK;
            can_buzz_stat = OUTPUT_BLINK;
        }
    }
}

/*============================================================================*/
/*
 * Function      : Choose_UOM.
 * Description   : Used to choose unit of measurement.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Choose_UOM(void)
{
    if(prv8_val1 == 1)
    {
        Lcd16x2_Out(2,1,"CV:T M   ");
    }
    else
    {
        if((sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
            Lcd16x2_Out(2,1,"CV:K F   ");
        else
            Lcd16x2_Out(2,1,"CV:K M   ");
    }
}

/*============================================================================*/
/*
 * Function      : Operator_Setting.
 * Description   : Used to update the operator setting display values.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Operator_Setting(void)
{
    char lbuf[20];

    switch(mv.operator_set)
    {
        case SET_DUTY:
            if(sys.para.duty <= lc_total_duty)
            {
                Duty_Hint(sys.para.duty);
            }
            else
            {
                Lcd16x2_Out(1,1,"  SLI Inactive  ");
                Lcd16x2_Out(2,1,"  Rigging Duty  ");
            }
        break;
        case SET_FALLS:
            Lcd16x2_Out(1,1,"   SET FALLS:   ");
            sprintf(lbuf,"CV:%02d      PV:%02d",prv8_val1,prv8_val1);
            Lcd16x2_Out(2,1,lbuf);
            pos_t = 0;
            common_byte = 2;             
            common_long = prv8_val1;
            sprintf(lbuf,"%02d",prv8_val1);
            Lcd16x2_Out(2,4,lbuf);
            Move_Cursor_Left(1);
            Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);    
        break;
        case SET_UOM:
            Lcd16x2_Out(1,1,"    SET UOM:    ");
            if(prv8_val1 == 1)
                Lcd16x2_Out(2,1,"CV:T M    ");
            else
            {
                if((sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
                    Lcd16x2_Out(2,1,"CV:K F   ");
                else
                    Lcd16x2_Out(2,1,"CV:K M   ");
            }

            if(prv8_val1 == 1)
                Lcd16x2_Out(2,11,"PV:T M");
            else
            {
                if((sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
                    Lcd16x2_Out(2,1,"CV:K F   ");
                else
                    Lcd16x2_Out(2,1,"CV:K M   ");
            }
        break;
    }
}

/*============================================================================*/
/*
 * Function      : Duty_Hint.
 * Description   : Used to select duty hint.
 * Parameters    : Duty_no- Duty number to select duty hint.
 * Return        : None.
*/
/*============================================================================*/
void Duty_Hint(uint16_t Duty_no)
{
    uint16_t TempCount,TempCount1;
    char Line_1[20],Line_2[20];

    flash_page_addr = (lc_duty_hint_page_s-1)*256 + ((Duty_no-1)*32) + flash_memory_offset;

    for(TempCount=0;TempCount<16;TempCount++)
    {
        Line_1[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
    }

    for(TempCount1=0,TempCount=16;TempCount<32;TempCount1++,TempCount++)
    {
        Line_2[TempCount1] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
    }

    Lcd16x2_Out(1,1,Line_1);
    Lcd16x2_Out(2,1,Line_2);
    Delay_1ms(1000);
}

/*============================================================================*/
/*
 * Function      :        Operator_Save_Settings.
 * Description   :        Used to update the operator setting variables value.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Operator_Save_Settings(void)
{
    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
    
    switch(mv.operator_set)
    {
        case SET_DUTY:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                if(sys.para.duty > lc_total_duty)
                {
                    if(sys.para.fail_safe_stat_bit == 0)
                    {
                        op.relay1action = OUTPUT_ON;
//                        op.relay2action = OUTPUT_ON;
                        op.hooteraction = OUTPUT_ON;
                    }
                    else
                    {
                        op.relay1action = OUTPUT_OFF;
//                        op.relay2action = OUTPUT_OFF;
                        op.hooteraction = OUTPUT_OFF;
                    }
                }
                else
                {
                    if(sys.para.fail_safe_stat_bit == 0)
                    {
                        op.relay1action = OUTPUT_OFF;
//                        op.relay2action = OUTPUT_OFF;
                        op.hooteraction = OUTPUT_OFF;
                    }
                    else
                    {
                        op.relay1action = OUTPUT_ON;
//                        op.relay2action = OUTPUT_ON;
                        op.hooteraction = OUTPUT_ON;
                    }
                }
            }
        break;
        case SET_FALLS:
            sys.para.falls_cnt = (uint8_t)common_long;
        break;
        case SET_UOM:
            sys.para.sel_uom = prv8_val1;
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