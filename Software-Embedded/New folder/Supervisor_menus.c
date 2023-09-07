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
 * Function      : Display_Select_Calib_Length_Menu.
 * Description   : Used to display select length to be calibrated.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Select_Calib_Length_Menu(void)
{
    char cbuf[50];

    sys.para.duty = temp_duty_indx;
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

        sprintf(cbuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
        Lcd16x2_Out(2,7,cbuf);    
    }
}

/*============================================================================*/
/*
 * Function      : Select_Calib_Length_Menu.
 * Description   : Used to select length to be calibrated.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Select_Calib_Length_Menu(uint8_t flag_id)
{
  char cbuf[50];
  
  if(flag_id == 0)
  {
    if(length_array_ptr < mv.max)
    {
      length_array_ptr++;
    }
    else
    {
      length_array_ptr = mv.min;
    }
  }
  else
  {
    if(length_array_ptr > mv.min)
    {
      length_array_ptr--;
    }
    else
    {
      length_array_ptr = mv.max;
    }
  }
  if((sys.para.duty_type[temp_duty_indx-1] >= 1) && (sys.para.duty_type[temp_duty_indx-1] < 6))
  {
//    if(sys.para.length_array[length_array_ptr]>99)
//      sprintf(cbuf,"%.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
//    else
      sprintf(cbuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
    Lcd16x2_Out(2,7,cbuf);
  }
}

/*============================================================================*/
/*
 * Function      : Display_Min_Calib_Angle_Menu.
 * Description   : Used to display angle to be calibrated.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Min_Calib_Angle_Menu(void)
{
  char cbuf[20];
  
  angle_calib_pt = sys.para.min_angle;
  mv.max = 65;
  mv.min = 1;

  Lcd16x2_Cmd(LCD_CLEAR);
  Lcd16x2_Out(1,1,"ENTER MIN ANGLE ");
  
  byt1 = angle_calib_pt/100;
  byt2 = (angle_calib_pt%100)/10;
  byt3 = angle_calib_pt%10;
  
  sprintf(cbuf,"%03d",angle_calib_pt);
  Lcd16x2_Out(2,7,cbuf);
  Move_Cursor_Left(1);
  Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      : Calib_Angle_Shift_Cursor.
 * Description   : Used to cursor left/right.
 * Parameters    : flag_lr-left/right flag.
 * Return        : None.
*/
/*============================================================================*/
void Calib_Angle_Shift_Cursor(uint8_t flag_lr)
{
  if(flag_lr == 0)
  {
    if(pos_t < 2)
    {
      pos_t++;
      Move_Cursor_Left(1);
    }
    else
    {
      pos_t = 0;
      Move_Cursor_Right(2);
    }
  }
  else
  {
    if(pos_t > 0)
    {
      pos_t--;
      Move_Cursor_Right(1);
    }
    else
    {
      pos_t = 2;
      Move_Cursor_Left(2);
    }
  }
}

/*============================================================================*/
/*
 * Function      : Calib_Angle_Change_Parameter_Value.
 * Description   : Used to change value.
 * Parameters    : flag_id-increment/decrement flag.
 * Return        : None.
*/
/*============================================================================*/
void Calib_Angle_Change_Parameter_Value(uint8_t flag_id)
{
  char sbuf[20];

  if(flag_id == 0)
  {
    if(pos_t == 0)
    {
      if(byt3 < 9) byt3++;
      else         byt3 = 1;
    }
    else if(pos_t == 1)
    {
      if(byt2 < 9) byt2++;
      else         byt2 = 0;
    }
    else if(pos_t == 2)
    {
      if(byt1 < 9) byt1++;
      else         byt1 = 0;
    }
  }
  else
  {
    if(pos_t == 0)
    {
      if(byt3 > 0) byt3--;
      else         byt3 = 9;
    }
    else if(pos_t == 1)
    {
      if(byt2 > 0) byt2--;
      else         byt2 = 9;
    }
    else if(pos_t == 2)
    {
      if(byt1 > 0) byt1--;
      else         byt1 = 9;
    }
  }
  angle_calib_pt = byt1*100 + byt2*10 + byt3;
  if(angle_calib_pt <= mv.max)        //mv.max=90
  {
    sprintf(sbuf,"%03d",angle_calib_pt);
    Lcd16x2_Out(2,7,sbuf);

    if(pos_t == 0)
    {
      Move_Cursor_Left(1);
    }
    else if(pos_t == 1)
    {
      Move_Cursor_Left(2);
    }
    else if(pos_t == 2)
    {
      Move_Cursor_Left(3);
    }
  }
  else
  {
    sprintf(sbuf,"MAX BM ANGLE=%03d",mv.max);
    Lcd16x2_Out(2,1,sbuf);
    Delay_1ms(1500);
    angle_calib_pt = mv.min;
    pos_t = 0;
    byt1 = angle_calib_pt/100;
    byt2 = (angle_calib_pt%100)/10;
    byt3 = angle_calib_pt%10;
    Lcd16x2_Out(2,1,"                ");
    sprintf(sbuf,"%03d",angle_calib_pt);
    Lcd16x2_Out(2,7,sbuf);
    Move_Cursor_Left(1);
  }
}

/*============================================================================*/
/*
 * Function      : Display_Max_Calib_Angle_Menu.
 * Description   : Used to display angle to be calibrated.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Max_Calib_Angle_Menu(void)
{
    char cbuf[20];

    angle_calib_pt = sys.para.max_angle;
    mv.max = 90;
    mv.min = 1;

    Lcd16x2_Cmd(LCD_CLEAR);
    Lcd16x2_Out(1,1,"ENTER MAX ANGLE ");

    byt1 = angle_calib_pt/100;
    byt2 = (angle_calib_pt%100)/10;
    byt3 = angle_calib_pt%10;

    sprintf(cbuf,"%03d",angle_calib_pt);
    Lcd16x2_Out(2,7,cbuf);
    Move_Cursor_Left(1);
    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}


/*============================================================================*/
/*
 * Function      : Display_Length_Calib_Menu.
 * Description   : Used to display length at which calibration is to be done.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Length_Calib_Menu(void)
{
    Lcd16x2_Cmd(LCD_CLEAR);
    Lcd16x2_Out(1,1,"CALIB.POINT:    ");
    Lcd16x2_Out(2,1,"  LENGTH:       ");
}

/*============================================================================*/
/*
 * Function      : Length_Calib_Cursor_Position.
 * Description   : Used to display values and set cursor position.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Length_Calib_Cursor_Position(void)
{
    char cbuf[10];

    sprintf(cbuf,"%02d",len_calib_pt);
    Lcd16x2_Out(1,13,cbuf);

    length_array_ptr = ((temp_duty_indx-1)*5) + (len_calib_pt-1);

    if(sys.para.length_array[length_array_ptr] > 999)
    {
        sys.para.length_array[length_array_ptr] = 0;
    }

    length_array_val = sys.para.length_array[length_array_ptr];

    pos_t = 0;
    byt1 = length_array_val/100;
    byt2 = (length_array_val%100)/10;
    byt3 = length_array_val%10;
  //  if(length_array_val > 99)
  //  sprintf(cbuf,"%.01f",((float)length_array_val)/10.0);
  //  else
    sprintf(cbuf,"%04.1f",((float)length_array_val)/10.0);
    Lcd16x2_Out(2,10,cbuf);
    Move_Cursor_Left(1);
    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      : Length_Calib_Shift_Cursor.
 * Description   : Used to cursor left/right.
 * Parameters    : flag_lr-left/right flag.
 * Return        : None.
*/
/*============================================================================*/
void Length_Calib_Shift_Cursor(uint8_t flag_lr)
{
  if(flag_lr == 0)
  {
    if(pos_t < 2)
    {
      pos_t++;

      if(pos_t == 1)
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
      Move_Cursor_Right(3);
    }
  }
  else
  {
    if(pos_t > 0)
    {
      pos_t--;
      if(pos_t == 0)
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
      pos_t = 2;
      Move_Cursor_Left(3);
    }
  }
}


/*============================================================================*/
/*
 * Function      : Length_Calib_Change_Parameter_Value.
 * Description   : Used to change value.
 * Parameters    : flag_id-increment/decrement flag.
 * Return        : None.
*/
/*============================================================================*/
void Length_Calib_Change_Parameter_Value(uint8_t flag_id)
{
//  char sbuf[20];
//  uint16_t temp_val;

  if(flag_id == 0)
  {
    if(pos_t == 0)
    {
      if(byt3 < 9) byt3++;
      else         byt3 = 1;
      Lcd16x2_Chr(2,13, byt3+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 1)
    {
      if(byt2 < 9) byt2++;
      else         byt2 = 0;
      Lcd16x2_Chr(2,11, byt2+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 2)
    {
      if(byt1 < 9) byt1++;
      else         byt1 = 0;
      Lcd16x2_Chr(2,10, byt1+0x30);
      Move_Cursor_Left(1);
    }
  }
  else
  {
    if(pos_t == 0)
    {
      if(byt3 > 0) byt3--;
      else         byt3 = 9;
      Lcd16x2_Chr(2,13, byt3+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 1)
    {
      if(byt2 > 0) byt2--;
      else         byt2 = 9;
      Lcd16x2_Chr(2,11, byt2+0x30);
      Move_Cursor_Left(1);
    }
    else if(pos_t == 2)
    {
      if(byt1 > 0) byt1--;
      else         byt1 = 9;
      Lcd16x2_Chr(2,10, byt1+0x30);
      Move_Cursor_Left(1);
    }
  }
}

/*============================================================================*/
/*
 * Function      : Display_Calib_Hook_Load_Menu.
 * Description   : Used to display calibration hook load menu.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Calib_Hook_Load_Menu(void)
{
    Lcd16x2_Cmd(LCD_CLEAR);
    
    Lcd16x2_Out(1,1,"SELECT DUTY:    ");
}

/*============================================================================*/
/*
 * Function      : Calib_Hook_Load_Cursor_Position.
 * Description   : Used to display values and set cursor position.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Calib_Hook_Load_Cursor_Position(void)
{
  char cbuf[10];

  sprintf(cbuf,"%02d",temp_duty_indx);
  Lcd16x2_Out(1,13,cbuf);
  
  pos_t = 0;
  byt1 = temp_duty_indx/10;
  byt2 = temp_duty_indx%10;

  Move_Cursor_Left(1);
  Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      : Calib_Hook_Load_Shift_Cursor.
 * Description   : Used to cursor left/right.
 * Parameters    : flag_lr-left/right flag.
 * Return        : None.
*/
/*============================================================================*/
void Calib_Hook_Load_Shift_Cursor(uint8_t flag_lr)
{
  pos_t = !pos_t;
  if(pos_t) Move_Cursor_Left(1);
  else      Move_Cursor_Right(1);
}


/*============================================================================*/
/*
 * Function      : Calib_Hook_Load_Change_Parameter_Value.
 * Description   : Used to change value.
 * Parameters    : flag_id-increment/decrement flag.
 * Return        : None.
*/
/*============================================================================*/
void Calib_Hook_Load_Change_Parameter_Value(uint8_t flag_id)
{
    char sbuf[20];

    if(flag_id == 0)
    {
      if(pos_t == 0)
      {
        if(byt2 < 9) byt2++;
        else         byt2 = 0;
      }
      else
      {
        if(byt1 < 9) byt1++;
        else         byt1 = 0;
      }
    }
    else
    {
      if(pos_t == 0)
      {
        if(byt2 > 0) byt2--;
        else         byt2 = 9;
      }
      else
      {
        if(byt1 > 0) byt1--;
        else         byt1 = 9;
      }
    }
    temp_duty_indx = byt1*10 + byt2;
    sprintf(sbuf,"%02d",temp_duty_indx);
    Lcd16x2_Out(1,13,sbuf);

    if(pos_t == 0)
    {
      Move_Cursor_Left(1);
    }
    else
    {
      Move_Cursor_Left(2);
    }
//    if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
//    {
//
//    }
//    else
//    {
//      sprintf(sbuf," TOTAL DUTY=%02d  ",lc_total_duty);
//      Lcd16x2_Out(1,1,sbuf);
//      Delay_1ms(1500);
//      temp_duty_indx = 1;
//      byt1 = temp_duty_indx/10;
//      byt2 = temp_duty_indx%10;
//      sprintf(sbuf,"SELECT DUTY:%02d  ",temp_duty_indx);
//      Lcd16x2_Out(1,1,sbuf);
//      if(pos_t == 0)
//      {
//        Move_Cursor_Left(3);
//      }
//      else
//      {
//        Move_Cursor_Left(4);
//      }
//    }
}


/*============================================================================*/
/*
 * Function      : Display_Calib_Length_Angle.
 * Description   : Used to display Boom length and angle live.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Calib_Length_Angle(void)
{
    Lcd16x2_Cmd(LCD_CLEAR);
    if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
    {
        Lcd16x2_Out(1,1,"KBL:            ");
        Lcd16x2_Out(2,1,"MBA:    KBA:    ");
    }
    else
    {
        Lcd16x2_Out(1,1,"BL:             ");
        Lcd16x2_Out(2,1,"BA:             ");
    }
    Lcd16x2_Cmd(LCD_CURSOR_OFF);
}


/*============================================================================*/
/*
 * Function      : Display_Duty_Type_Menu.
 * Description   : Used to display duty type menus.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Duty_Type_Menu(void)
{
  Lcd16x2_Cmd(LCD_CLEAR);

  Lcd16x2_Out(1,1,"DUTY NO. :      ");
  Lcd16x2_Out(2,1,"CALIB.Pts:      ");
}


/*============================================================================*/
/*
 * Function      : Duty_Type_Cursor_Position.
 * Description   : Used to display values and set cursor position.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Duty_Type_Cursor_Position(void)
{
  char dbuf[20];
  
  len_calib_cnt = sys.para.duty_type[temp_duty_indx-1];
  
  if(menu_stat >= DUTY_TYPE_INDEX_PAGE)
  {
    if((len_calib_cnt == 0)||(len_calib_cnt > 5))
    {
      len_calib_cnt = 1;
      sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt;
    }
    sprintf(dbuf,"%03d",len_calib_cnt);
    Lcd16x2_Out(2,11,dbuf);
    sprintf(dbuf,"%02d",temp_duty_indx);
    Lcd16x2_Out(1,11,dbuf);
    Move_Cursor_Left(1);

    pos_t = 0;
    byt1 = temp_duty_indx/10;
    byt2 = temp_duty_indx%10;
  }
  else
  {
    sprintf(dbuf,"%02d",temp_duty_indx);
    Lcd16x2_Out(1,11,dbuf);
    sprintf(dbuf,"%03d",len_calib_cnt);
    Lcd16x2_Out(2,11,dbuf);
    Move_Cursor_Left(1);
    
    pos_t = 0;
    byt3 = len_calib_cnt/100;
    byt4 = (len_calib_cnt%100)/10;
    byt5 = len_calib_cnt%10;
  }
  Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      : Duty_Type_Shift_Cursor.
 * Description   : Used to cursor left/right.
 * Parameters    : flag_lr-left/right flag.
 * Return        : None.
*/
/*============================================================================*/
void Duty_Type_Shift_Cursor(uint8_t flag_lr)
{
  if(menu_stat >= DUTY_TYPE_INDEX_PAGE)
  {
    pos_t = !pos_t;
    if(pos_t) Move_Cursor_Left(1);
    else      Move_Cursor_Right(1);
  }
  else
  {
    if(flag_lr == 0)
    {
      if(pos_t < 2)
      {
        pos_t++;
        Move_Cursor_Left(1);
      }
      else
      {
        pos_t = 0;
        Move_Cursor_Right(2);
      }
    }
    else
    {
      if(pos_t > 0)
      {
        pos_t--;
        Move_Cursor_Right(1);
      }
      else
      {
        pos_t = 2;
        Move_Cursor_Left(2);
      }
    }
  }
}


/*============================================================================*/
/*
 * Function      : Duty_Type_Change_Parameter_Value.
 * Description   : Used to change value.
 * Parameters    : flag_id-increment/decrement flag.
 * Return        : None.
*/
/*============================================================================*/
void Duty_Type_Change_Parameter_Value(uint8_t flag_id)
{
  char sbuf[50];
  
  if(menu_stat >= DUTY_TYPE_INDEX_PAGE)
  {
    if(flag_id == 0)
    {
      if(pos_t == 0)
      {
        if(byt2 < 9) byt2++;
        else         byt2 = 0;
      }
      else
      {
        if(byt1 < 9) byt1++;
        else         byt1 = 0;
      }
    }
    else
    {
        if(pos_t == 0)
        {
            if(byt2 > 0) byt2--;
            else         byt2 = 9;
        }
        else
        {
            if(byt1 > 0) byt1--;
            else         byt1 = 9;
        }
    }
    temp_duty_indx = byt1*10 + byt2;
    
    if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
    {
        len_calib_cnt = sys.para.duty_type[temp_duty_indx-1];
        if((len_calib_cnt == 0)||(len_calib_cnt>5))
        {
          len_calib_cnt = 1;
          sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt;
        }
        sprintf(sbuf,"%03d",len_calib_cnt);
        Lcd16x2_Out(2,11,sbuf);
    }
    
    sprintf(sbuf,"%02d",temp_duty_indx);
    Lcd16x2_Out(1,11,sbuf);
    if(pos_t == 0)
    {
      Move_Cursor_Left(1);
    }
    else
    {
      Move_Cursor_Left(2);
    }
//    if(temp_duty_indx <= lc_total_duty)
//    {
//      len_calib_cnt = sys.para.duty_type[temp_duty_indx-1];
//      if((len_calib_cnt == 0)||(len_calib_cnt>5))
//      {
//        len_calib_cnt = 1;
//        sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt;
//      }
//      sprintf(sbuf,"%03d",len_calib_cnt);
//      Lcd16x2_Out(2,11,sbuf);
//      sprintf(sbuf,"%02d",temp_duty_indx);
//      Lcd16x2_Out(1,11,sbuf);
//      #ifdef DEBUG_MSG
//      sprintf(sbuf,"index=%02d cnt=%d",temp_duty_indx,len_calib_cnt);
//      //UART_Send_String(UART_MODULE1,sbuf);
//      #endif
//      
//      if(pos_t == 0)
//      {
//        Move_Cursor_Left(1);
//      }
//      else
//      {
//        Move_Cursor_Left(2);
//      }
//    }
//    else
//    {
//      sprintf(sbuf," TOTAL DUTY=%02d  ",lc_total_duty);
//      Lcd16x2_Out(1,1,sbuf);
//      Delay_1ms(1500);
//      temp_duty_indx = lc_total_duty;
//      byt1 = temp_duty_indx/10;
//      byt2 = temp_duty_indx%10;
//      sprintf(sbuf,"DUTY NO. :%02d    ",temp_duty_indx);
//      Lcd16x2_Out(1,1,sbuf);
//      if(pos_t == 0)
//      {
//        Move_Cursor_Left(5);
//      }
//      else
//      {
//        Move_Cursor_Left(6);
//      }
//    }
  }
  else
  {
    if(flag_id == 0)
    {
      if(pos_t == 0)
      {
        if(byt5 < 9) byt5++;
        else         byt5 = 1;
      }
      else if(pos_t == 1)
      {
        if(byt4 < 9) byt4++;
        else         byt4 = 0;
      }
      else if(pos_t == 2)
      {
        if(byt3 < 9) byt3++;
        else         byt3 = 0;
      }
    }
    else
    {
      if(pos_t == 0)
      {
        if(byt5 > 1) byt5--;
        else         byt5 = 9;
      }
      else if(pos_t == 1)
      {
        if(byt4 > 0) byt4--;
        else         byt4 = 9;
      }
      else if(pos_t == 2)
      {
        if(byt3 > 0) byt3--;
        else         byt3 = 9;
      }
    }
    len_calib_cnt = byt3*100 + byt4*10 + byt5;
    if(len_calib_cnt <= MAX_LENGTH_CALIB_PT)
    {
      sprintf(sbuf,"%03d",len_calib_cnt);
      Lcd16x2_Out(2,11,sbuf);
      if(pos_t == 0)
      {
        Move_Cursor_Left(1);
      }
      else if(pos_t == 1)
      {
        Move_Cursor_Left(2);
      }
      else if(pos_t == 2)
      {
        Move_Cursor_Left(3);
      }
    }
    else
    {
      sprintf(sbuf," MAX POINTS=%02d  ",MAX_LENGTH_CALIB_PT);
      Lcd16x2_Out(2,1,sbuf);
      Delay_1ms(1500);
      len_calib_cnt = MAX_LENGTH_CALIB_PT;
      byt3 = len_calib_cnt/100;
      byt4 = (len_calib_cnt%100)/10;
      byt5 = len_calib_cnt%10;
      sprintf(sbuf,"CALIB.Pts:%03d   ",len_calib_cnt);
      Lcd16x2_Out(2,1,sbuf);
      if(pos_t == 0)
      {
        Move_Cursor_Left(4);
      }
      else if(pos_t == 1)
      {
        Move_Cursor_Left(5);
      }
      else if(pos_t == 2)
      {
        Move_Cursor_Left(6);
      }
    }
  }
}

/*============================================================================*/
/*
 * Function      : Display_ArtDerate_Menu.
 * Description   : Used to display art derate menus.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_ArtDerate_Menu(void)
{
    Lcd16x2_Cmd(LCD_CLEAR);

    Lcd16x2_Out(1,1,"DUTY NO. :      ");
    Lcd16x2_Out(2,1,"ART.DRATE:      ");
    Lcd16x2_Chr(2,14, '%');
}

/*============================================================================*/
/*
 * Function      : ArtDerate_Cursor_Position.
 * Description   : Used to display values and set cursor position.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void ArtDerate_Cursor_Position(void)
{
    char dbuf[20];

    len_calib_cnt = sys.para.indopower_art_derate[temp_duty_indx-1];

    if(menu_stat == SET_ART_DRATE_PERCENTAGE1)
    {
        if(len_calib_cnt > 100)
        {
            len_calib_cnt = 0;
            sys.para.indopower_art_derate[temp_duty_indx-1] = len_calib_cnt;
        }
        sprintf(dbuf,"%03d",len_calib_cnt);
        Lcd16x2_Out(2,11,dbuf);
        sprintf(dbuf,"%02d",temp_duty_indx);
        Lcd16x2_Out(1,11,dbuf);

        pos_t = 0;
        common_byte = 2;
        common_long = temp_duty_indx;
    }
    else
    {
        sprintf(dbuf,"%02d",temp_duty_indx);
        Lcd16x2_Out(1,11,dbuf);
        sprintf(dbuf,"%03d",len_calib_cnt);
        Lcd16x2_Out(2,11,dbuf);

        pos_t = 0;
        common_byte = 3;
        common_long = len_calib_cnt;
    }
    Move_Cursor_Left(1);
    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      :        Display_Supervisor_Set_Menu.
 * Description   :        Used to display supervisor's setting menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Supervisor_Set_Menu(void)
{
    mv.max = 60;
    mv.min = 1;
    
    Lcd16x2_Cmd(LCD_CLEAR);

    Supervisor_Setcode_Menu();
}

/*============================================================================*/
/*
 * Function      :        Supervisor_Setcode_Menu.
 * Description   :        Used to select supervisor setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Supervisor_Setcode_Menu(void)
{
    char lbuf[20];
    
    sprintf(lbuf,"SET CODE: %03d   ",mv.supervisor_set+99);
    Lcd16x2_Out(1,1,lbuf);
    
    switch(mv.supervisor_set)
    {
        case EN_BYPASS_SWITCH:
            Lcd16x2_Out(2,1,"EN BYPASS SWITCH");
            prv8_val1 = sys.para.bpk_enable_bit;
        break;
        case SET_SP1_VALUE:
            Lcd16x2_Out(2,1,"SET SP1 VALUE:  ");
            prv16_val1 = sys.para.sp1_perc;
        break;
        case SET_SP2_VALUE:
            Lcd16x2_Out(2,1,"SET SP2 VALUE:  ");
            prv16_val1 = sys.para.sp2_perc;
        break;
        case SET_SP3_VALUE:
            Lcd16x2_Out(2,1,"SET SP3 VALUE:  ");
            prv16_val1 = sys.para.sp3_perc;
        break;
        case SET_SP4_VALUE:
            Lcd16x2_Out(2,1,"SET SP4 VALUE:  ");
            prv16_val1 = sys.para.sp4_perc;
        break;
        case SET_BOOM_OFFSET:
            Lcd16x2_Out(2,1,"SET BOOM OFFSET:");
            temp_bm_offset = sys.para.bm_offset;
            prv16_sign_val = sys.para.bm_offset;
        break;
        case SET_BM_HEAD_OFFSET:
            Lcd16x2_Out(2,1,"SET BM HEAD OFF.");
            temp_head_offset = sys.para.bm_head_offset;
            prv16_sign_val = sys.para.bm_head_offset;
        break;
        case SET_BM_TIP_OFFSET:
            Lcd16x2_Out(2,1,"SET BM TIP OFF.:");
            temp_tip_offset = sys.para.bm_tip_offset;
            prv16_sign_val = sys.para.bm_tip_offset;
        break;
        case SET_MAIN_SAMPLE_CNT:
            Lcd16x2_Out(2,1,"SET MAIN SMP CNT");
            prv16_val1 = sys.para.main_smpl_cnt;
        break;
        case SET_HOOK_LOAD:
            Lcd16x2_Out(2,1,"SET HOOK LOAD:  ");
            prv16_val1 = sys.para.hook_load;
        break;
        case CALIB_LENGTH_MIN:
            if(sys.para.mpoint_len_enable_bit == 0)
            {
                Lcd16x2_Out(2,1,"CALIB LENGTH MIN");
                prv16_val1 = sys.para.cal_len_min;
                prv16_val2 = sys.para.cal_len_min_cnt;
            }
            else
            {
                Lcd16x2_Out(2,1," NOT AVAILABLE  ");
            }
        break;
        case CALIB_LENGTH_MAX:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(2,1,"CALIB LENGTH MAX");
                prv16_val1 = sys.para.cal_len_max;
                prv16_val2 = sys.para.cal_len_max_cnt;
            }
            else
            {
                Lcd16x2_Out(2,1," NOT AVAILABLE  ");
            }
        break;
        case CALIB_ANGLE_MIN:
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                Lcd16x2_Out(2,1,"CAL KNUC ANG MIN");
            else
                Lcd16x2_Out(2,1,"CALIB ANGLE MIN:");
            prv16_val1 = sys.para.cal_angle_min;
            prv16_val2 = sys.para.cal_angle_min_cnt;
        break;
        case CALIB_ANGLE_MAX:
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                Lcd16x2_Out(2,1,"CAL KNUC ANG MAX");
            else
                Lcd16x2_Out(2,1,"CALIB ANGLE MAX:");
            prv16_val1 = sys.para.cal_angle_max;
            prv16_val2 = sys.para.cal_angle_max_cnt;
        break;
        case CALIB_MANGLE_MIN:
            Lcd16x2_Out(2,1,"CALIB MANGLE MIN");
            prv16_val1 = sys.para.cal_mangle_min;
            prv16_val2 = sys.para.cal_mangle_min_cnt;
        break;
        case CALIB_MANGLE_MAX:
            Lcd16x2_Out(2,1,"CALIB MANGLE MAX");
            prv16_val1 = sys.para.cal_mangle_max;
            prv16_val2 = sys.para.cal_mangle_max_cnt;
        break;
        case NUMOF_CALIB_POINTS:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(2,1,"NUMOF CAL POINT:");
                prv16_val1 = sys.para.numof_calib_fork;
            }
            else
            {
                Lcd16x2_Out(2,1," NOT AVAILABLE  ");
            }
        break;
        case SET_DUTY_TYPE:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(2,1,"CALIB PRESS MIN:");
                prv16_val1 = sys.para.calib_pressure1_min;
                prv16_val2 = sys.para.calib_P1LowAdcCount;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                Lcd16x2_Out(2,1,"CALIB OTG MIN:  ");
                press_chann_num = 1;
            }
            else
            {
                Lcd16x2_Out(2,1,"SET DUTY TYPE:  ");
            }
        break;
        case CALIB_HOOK_LOAD:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(2,1,"CALIB PRESS MAX:");
                prv16_val1 = sys.para.calib_pressure1_max;
                prv16_val2 = sys.para.calib_P1HighAdcCount;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                Lcd16x2_Out(2,1,"CALIB OTG MAX:  ");
                press_chann_num = 1;
            }
            else
            {
                Lcd16x2_Out(2,1,"CALIB HOOK LOAD:");
            }
        break;
        case EN_PASSWORD:
            Lcd16x2_Out(2,1,"PASSWORD STATUS:");
            prv8_val1 = sys.para.pw_stat_bit;
        break;
        case EN_BM_DWN_RLY:
            Lcd16x2_Out(2,1,"BM DWN RLY STAT:");
            prv8_val1 = sys.para.bmdwn_rly_stat_bit;
        break;
        case EN_BM_UP_RLY:
            Lcd16x2_Out(2,1,"BM UP RLY STAT: ");
            prv8_val1 = sys.para.bmup_rly_stat_bit;
        break;
        case EN_HOOTER_RLY:
            Lcd16x2_Out(2,1,"HOOTR RLY STATUS");
            prv8_val1 = sys.para.hootr_rly_stat_bit;
        break;
        case EN_A2B:
            Lcd16x2_Out(2,1,"A2B STATUS:     ");
            prv8_val1 = sys.para.a2b_stat_bit;
        break;
        case EN_HK_HEIGHT:
            Lcd16x2_Out(2,1,"HK_HEIGHT STATUS");
            prv8_val1 = sys.para.hk_height_stat_bit;
        break;
        case RIG_LOAD_LIMIT:
            Lcd16x2_Out(2,1,"RIG LOAD LIMIT: ");
            prv16_val1 = sys.para.rig_load_lmt;
        break;
        case RIG_BM_ANGLE_LIMIT:
            Lcd16x2_Out(2,1,"RIG BM ANG LMT: ");
            prv16_val1 = sys.para.rig_bm_angl_lmt;
        break;
        case RIG_BM_LENGTH_LIMIT:
            Lcd16x2_Out(2,1,"RIG BM LEN LIMIT");
            prv16_val1 = sys.para.rig_bm_len_lmt;
        break;
        case RIG_DEFAULT_DUTY:
            Lcd16x2_Out(2,1,"  DEFAULT DUTY  ");
            prv16_val1 = sys.para.default_duty;
        break;
        case EDIT_ENGINE_NUMBER:
            Lcd16x2_Out(2,1,"EDIT ENGINE NO: ");
            prv32_val1 = sys.para.engine_number;
        break;
        case ARTICULATION_DERATE_PERC:              //All duty art. derate percentage
            Lcd16x2_Out(2,1,"AL DTY ART.DRATE");
            prv16_val1 = sys.para.art_derate_perc;
        break;
        case VIEW_DATA_LOGGED:
            Lcd16x2_Out(2,1,"VIEW DATA LOGGED");
        break;
        case SEND_DATA_TO_PC:
            Lcd16x2_Out(2,1,"SEND DATA TO PC:");
        break;
        case LOW_CUTOFF_ANGLE:
            Lcd16x2_Out(2,1,"LOW CUTOFF ANGLE");
            temp_low_cutoff_angl = sys.para.low_cutoff_angl;
            prv16_sign_val = sys.para.low_cutoff_angl;
        break;
        case HIGH_CUTOFF_ANGLE:
            Lcd16x2_Out(2,1,"HI CUTOFF ANGLE:");
            prv16_val1 = sys.para.hi_cutoff_angl;
        break;
        case EN_DUTY_SELECT:
            Lcd16x2_Out(2,1,"DUTY SEL STATUS:");
            prv8_val1 = sys.para.duty_select_stat_bit;
        break;
        case EN_SNATCH_BLOCK:
            Lcd16x2_Out(2,1,"EN SNATCH BLOCK:");
            prv8_val1 = sys.para.snatch_block_stat_bit;
        break;
        case SNATCH_BLOCK_VALUE:
            Lcd16x2_Out(2,1,"SNATCH BLOCK VAL");
            prv16_val1 = sys.para.snatch_block_val;
        break;
        case BYPASS_METHOD:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(2,1,"ARTICULTN METHOD");    //Spacial case for SCA forklift
            }
            else
            {
                Lcd16x2_Out(2,1,"BYPASS METHOD:  ");
            }
            
            prv8_val1 = sys.para.bpk_method_stat_bit;
        break;            
        case FRONT_TILT_ANGLE_CALIB :
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
               (sys.para.Select_System == TELESCOPIC_RT40))
            {
                Lcd16x2_Out(2,1,"CALIB TILT ANGLE");
            }
            else
            {                
                Lcd16x2_Out(2,1,"F.TILT ANG CALIB");
            }
            prv16_val1 = sys.para.Tilt1_X_MinAdc;
            prv16_val2 = sys.para.Tilt1_Y_MinAdc;
        break;
        
        case REAR_TILT_ANGLE_CALIB :   
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
               (sys.para.Select_System == TELESCOPIC_RT40))
            {
                Lcd16x2_Out(2,1," NOT APPLICABLE ");
            }
            else
            {  
                Lcd16x2_Out(2,1,"R.TILT ANG CALIB");
            }
            prv16_val1 = sys.para.Tilt2_X_MinAdc;
            prv16_val2 = sys.para.Tilt2_Y_MinAdc;
            break;
        case FRONT_TILT_CUTOFF :
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
               (sys.para.Select_System == TELESCOPIC_RT40))
            {
                Lcd16x2_Out(2,1,"TILT ANGL CUTOFF");
            }
            else
            { 
                Lcd16x2_Out(2,1,"FR. TILT CUTOFF:");
            }
            prv8_val1= sys.para.Front_tilt_Cutoff;
            break;
             
        case REAR_TILT_CUTOFF:
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
               (sys.para.Select_System == TELESCOPIC_RT40))
            {
                Lcd16x2_Out(2,1," NOT APPLICABLE ");
            }
            else
            {
                Lcd16x2_Out(2,1,"RE. TILT CUTOFF:");
            }
            prv8_val1=sys.para.Rear_tilt_Cutoff;
            break;
        case VOICE_LANGUAGE:
            Lcd16x2_Out(2,1,"VOICE LANGUAGE: ");
            prv8_val1=sys.para.voice_of_language;   
            break;
        case SET_ZERO_LOAD_MASKING:
            Lcd16x2_Out(2,1,"SET ZLOAD MASK: ");
            prv16_val1 = sys.para.zload_mask;
        break;
        case LOAD_ANNOUNCE_TIMER:
            Lcd16x2_Out(2,1,"SET LD ANN. TIME");
            prv16_val1 = sys.para.load_announce_timer;
        break;
        case SET_MAX_BOOM_LENGTH:
            Lcd16x2_Out(2,1,"BOOM HIGHT LIMIT");
            prv16_val1 = sys.para.Max_BLength;
        break;              
        case SET_MAX_BOOM_ANGLE:
            Lcd16x2_Out(2,1,"BOOM ANGLE LIMIT");
            prv16_val1=sys.para.Max_BAngle;
        break;        
        case SET_HEIGHT_OFFSET:            //Required for TMC crane
            Lcd16x2_Out(2,1,"BOOM HIGHT OFSET");
            prv16_val1 = sys.para.bm_ht_offset;
        break;  
        case SET_LOADCEL_ADC_OFFST:
            Lcd16x2_Out(2,1,"SET GAIN OFFSET:");
            prv16_val1 = sys.para.loadcell_cnt_offst;
        break;
        case CALIB_MANBAS_MIN:
            Lcd16x2_Out(2,1,"CALIB MANBAS MIN");
            prv16_val1 = sys.para.manbasket_min;
            prv16_val2 = sys.para.manbasket_min_cnt;
        break;
        case CALIB_MANBAS_MAX:
            Lcd16x2_Out(2,1,"CALIB MANBAS MAX");
            prv16_val1 = sys.para.manbasket_max;
            prv16_val2 = sys.para.manbasket_max_cnt;
        break;
        
        case EN_ART_DRATE_PERC:
            Lcd16x2_Out(2,1,"EN ART.DRATE SW:");
            prv8_val1 = sys.para.art_enable_bit;
        break;
        case ART_DRATE_PERC_VALUE:
            if(sys.para.art_enable_bit)
                Lcd16x2_Out(2,1,"ART.DERATE VAL: ");
            else
                Lcd16x2_Out(2,1," NOT APPLICABLE ");
        break;
        case SET_SLEW_OFFSET:
            Lcd16x2_Out(2,1,"SET SLEW OFFSET:");
            temp_bm_offset = sys.para.slew_offset;
            prv16_sign_val = sys.para.slew_offset;
        break;
        case EN_ONBOARD_SING_TILT:
            if((sys.para.Select_System != TMC_MANBASKET2)&&(sys.para.Select_System != TELESCOPIC_RT40))
            {
                Lcd16x2_Out(2,1," NOT APPLICABLE ");
                menu_absnt_flag = 1;
            }
            else
            {
                Lcd16x2_Out(2,1,"EN ONBOARD TILT:");
                prv8_val1 = sys.para.obtilt_enable_bit;
            }
        break;
        case EN_SLAVE_DISPLAY:
            Lcd16x2_Out(2,1,"EN SLAVE DISPLAY");
            prv8_val1 = sys.para.slave_enable_bit;
        break;
        case EN_MPOINT_LEN_CALIB:
            Lcd16x2_Out(2,1,"EN MPOINT LCALIB");
            prv8_val1 = sys.para.mpoint_len_enable_bit;
        break;
        case NUMOF_MPOINT_LEN_CALIB:
            Lcd16x2_Out(2,1,"NUMOF LEN MP CAL");
            prv16_val1 = sys.para.numof_len_cal;
        break;
        case MPOINT_LCALIBRATION_MENU:
            if(sys.para.mpoint_len_enable_bit)
            {
                Lcd16x2_Out(2,1,"LEN MPOINT CALIB");
            }
            else
            {
                Lcd16x2_Out(2,1," NOT APPLICABLE ");
                menu_absnt_flag = 1;
            }
        break;
        case MASTER_RESET_DEFAULT:
            Lcd16x2_Out(2,1,"MASTER RESET    ");
        break;
    }
}


/*============================================================================*/
/*
 * Function      :        Supervisor_Parametere_Value.
 * Description   :        Used to update the supervisor setting display values.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Supervisor_Parametere_Value(void)
{
    char lbuf[20];
    
    Lcd16x2_Out(2,1,"                ");
    if((mv.supervisor_set == SET_SP1_VALUE)||(mv.supervisor_set == SET_SP2_VALUE)||
       (mv.supervisor_set == SET_SP3_VALUE)||(mv.supervisor_set == SET_SP4_VALUE)||
       (mv.supervisor_set == ARTICULATION_DERATE_PERC))
    {
        sprintf(lbuf,"PV:%03d",prv16_val1);
        Lcd16x2_Out(2,10,lbuf);
        Lcd16x2_Chr(2,16, '%');        
        sprintf(lbuf,"CV:%03d  ",prv16_val1);
        Lcd16x2_Out(2,1,lbuf);
        Lcd16x2_Chr(2,7, '%');

        pos_t = 0;
        common_byte = 3;
        common_long = prv16_val1;
        Move_Cursor_Left(2);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if((mv.supervisor_set == SET_BOOM_OFFSET)||(mv.supervisor_set == SET_BM_HEAD_OFFSET)||
            (mv.supervisor_set == SET_BM_TIP_OFFSET)||(mv.supervisor_set == LOW_CUTOFF_ANGLE)||
            (mv.supervisor_set == SET_SLEW_OFFSET))
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
    else if((mv.supervisor_set == SET_MAIN_SAMPLE_CNT)||(mv.supervisor_set == RIG_DEFAULT_DUTY)||
            (mv.supervisor_set == HIGH_CUTOFF_ANGLE)||(mv.supervisor_set == RIG_BM_ANGLE_LIMIT)||
            (mv.supervisor_set == SET_MAX_BOOM_ANGLE)||(mv.supervisor_set == NUMOF_CALIB_POINTS)||
            (mv.supervisor_set == NUMOF_MPOINT_LEN_CALIB))
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
    else if((mv.supervisor_set == SET_HOOK_LOAD)||(mv.supervisor_set == RIG_LOAD_LIMIT)||
            (mv.supervisor_set == RIG_BM_LENGTH_LIMIT)||(mv.supervisor_set == SET_MAX_BOOM_LENGTH)||
            (mv.supervisor_set == SET_ZERO_LOAD_MASKING)||(mv.supervisor_set == SET_HEIGHT_OFFSET))
    {
        sprintf(lbuf,"PV:%04.1f",((float)prv16_val1)/10.0);    
        Lcd16x2_Out(2,10,lbuf);
        pos_t = 0;
        common_byte = 3;
        common_long = prv16_val1;
        sprintf(lbuf,"CV:%04.1f",((float)prv16_val1)/10.0);
        Lcd16x2_Out(2,1,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON); 
    }
    else if((mv.supervisor_set == CALIB_LENGTH_MIN)||(mv.supervisor_set == CALIB_LENGTH_MAX)||
            (mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX)||
            (mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX)||
            (((mv.supervisor_set == SET_DUTY_TYPE)||(mv.supervisor_set == CALIB_HOOK_LOAD))&&(sys.para.Select_System == FORK_LIFT)))
    {
        if((mv.supervisor_set == CALIB_LENGTH_MIN)||(mv.supervisor_set == CALIB_LENGTH_MAX))
        {
            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,len_adc_cnt);
        }
        else if(((mv.supervisor_set == SET_DUTY_TYPE)||(mv.supervisor_set == CALIB_HOOK_LOAD))&&(sys.para.Select_System == FORK_LIFT))
        {
            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,p1_pressure_cnt);
        }
//        else if(((mv.supervisor_set == SET_DUTY_TYPE)||(mv.supervisor_set == CALIB_HOOK_LOAD))&&(sys.para.Select_System == TMC_MANBASKET))
//        {
//            if(press_chann_num == 1)
//                sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p1_cnt); 
//            else if(press_chann_num == 2)
//                sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p2_cnt);
//            else if(press_chann_num == 3)
//                sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p3_cnt);
//            else if(press_chann_num == 4)
//                sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p4_cnt);
//        }
        else if((mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX))
        {
            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,ang_adc_cnt);
        }
        else if((mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX))
        {
            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,Main_ang_adc_cnt);
        }
        Lcd16x2_Out(1,1,lbuf);
        
        sprintf(lbuf,"PV:%04.1f  PC:%04d",((float)prv16_val1)/10.0,prv16_val2);
        Lcd16x2_Out(2,1,lbuf);
        
        pos_t = 0;
        common_byte = 3; 
        common_long = prv16_val1;
        sprintf(lbuf,"%04.1f",((float)prv16_val1)/10.0);
        Lcd16x2_Out(1,4,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.supervisor_set == EDIT_ENGINE_NUMBER)
    {
        pos_t = 0;
        common_byte = 10; 
        common_long = sys.para.engine_number;
        sprintf(lbuf,"%010lu",common_long);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.supervisor_set == SNATCH_BLOCK_VALUE)
    {
        sprintf(lbuf,"PV:%04d",prv16_val1);    
        Lcd16x2_Out(2,10,lbuf);
        pos_t = 0;
        common_byte = 4; 
        common_long = prv16_val1;
        sprintf(lbuf,"CV:%04d",prv16_val1);
        Lcd16x2_Out(2,1,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if(mv.supervisor_set == FRONT_TILT_ANGLE_CALIB)
    {
        sprintf(lbuf,"PV:%04d",prv16_val1);    
        Lcd16x2_Out(1,9,lbuf);
        sprintf(lbuf,"PV:%04d",prv16_val2);    
        Lcd16x2_Out(2,9,lbuf);
    }
    else if((mv.supervisor_set == REAR_TILT_ANGLE_CALIB)&&(sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
    {
        sprintf(lbuf,"PV:%04d",prv16_val1);    
        Lcd16x2_Out(1,9,lbuf);
        sprintf(lbuf,"PV:%04d",prv16_val2);    
        Lcd16x2_Out(2,9,lbuf);
    }
    else if(mv.supervisor_set == VOICE_LANGUAGE )
    {
        if(sys.para.voice_of_language==1)      
        {
           Lcd16x2_Out(2,1,"PV:ENGLISH       "); 
           Lcd16x2_Out(1,1,"CV:ENGLISH       ");   
        }
        else if(sys.para.voice_of_language==0) 
        {
           Lcd16x2_Out(2,1,"PV:HINDI         ");
           Lcd16x2_Out(1,1,"CV:HINDI         "); 
        }
    }
    else if(mv.supervisor_set == LOAD_ANNOUNCE_TIMER )
    {
        sprintf(lbuf,"PV:%03d",prv16_val1);    
        Lcd16x2_Out(2,11,lbuf);
        pos_t = 0;
        common_byte = 3; 
        common_long = prv16_val1;
        sprintf(lbuf,"CV:%03d",prv16_val1);
        Lcd16x2_Out(2,1,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if((mv.supervisor_set == FRONT_TILT_CUTOFF)||((mv.supervisor_set == REAR_TILT_CUTOFF)&&
            (sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2)))
    {
       Lcd16x2_Out(1,1,"TILT CUTOFF ANGLE: ");

       sprintf(lbuf,"PV:%01d",prv8_val1);
       Lcd16x2_Out(2,12,lbuf);

       sprintf(lbuf,"CV:%01d",prv8_val1);
       Lcd16x2_Out(2,1,lbuf);

       pos_t = 0;
       common_byte = 1;
       common_long = prv8_val1;
       Move_Cursor_Left(1);
       Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);  
    }
    else if((mv.supervisor_set == SET_LOADCEL_ADC_OFFST))
    {
        sprintf(lbuf,"P:%05d",prv16_val1);    
        Lcd16x2_Out(2,10,lbuf);
        pos_t = 0;
        common_byte = 5; 
        common_long = prv16_val1;
        sprintf(lbuf,"C:%05d",prv16_val1);
        Lcd16x2_Out(2,1,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
    else if((mv.supervisor_set == CALIB_MANBAS_MIN) || (mv.supervisor_set == CALIB_MANBAS_MAX))
    {
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            sprintf(lbuf,"CV:%04d CC:%05lu",prv16_val1,(uint32_t)can_loadcell_cnt);
        else if(sys.para.Select_System == ACE_MANBASKET_HXP)
            sprintf(lbuf,"CV:%04d CC:%05d",prv16_val1,loadcell_cnt);
        Lcd16x2_Out(1,1,lbuf);
        
        sprintf(lbuf,"PV:%04d PC:%05lu",prv16_val1,(uint32_t)prv16_val2);
        Lcd16x2_Out(2,1,lbuf);

        pos_t = 0;
        common_byte = 4; 
        common_long = prv16_val1;
        sprintf(lbuf,"%04d",prv16_val1);
        Lcd16x2_Out(1,4,lbuf);
        Move_Cursor_Left(1);
        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
    }
}

void Display_TMC_MinMax_Press_Menu(void)
{
    char lbuf[20];
    
    sprintf(lbuf,"P1:%04d  P2:%04d",can_p1_cnt,can_p2_cnt);
    Lcd16x2_Out(1,1,lbuf);
    sprintf(lbuf,"P3:%04d  P4:%04d",can_p3_cnt,can_p4_cnt);
    Lcd16x2_Out(2,1,lbuf);
    
//        sprintf(lbuf,"CALIB OTG P%01d MIN",press_chann_num);
//        Lcd16x2_Out(1,1,lbuf);
//
//        prv16_val1 = sys.para.forkcalib_press_min[pindex][0];   //Pressure value
//        prv16_val2 = sys.para.forkcalib_press_min[pindex][1];   //Pressure count
//    }
//    else
//    {
//        sprintf(lbuf,"CALIB OTG P%01d MAX",press_chann_num);
//        Lcd16x2_Out(1,1,lbuf);
//
//        prv16_val1 = sys.para.forkcalib_press_max[pindex][0];   //Pressure value
//        prv16_val2 = sys.para.forkcalib_press_max[pindex][1];   //Pressure count
//    }
//    
//    sprintf(lbuf,"PV:%04.1f  PC:%04d",((float)prv16_val1)/10.0,prv16_val2);
//    Lcd16x2_Out(2,1,lbuf);
}

void Display_Fork_MinMax_Press_Menu(uint8_t pindex, uint8_t minmax)
{
    char lbuf[20];
    
    press_chann_num = pindex+1;
    if(minmax == 0)
    {
        sprintf(lbuf,"CALIB PRES MIN %01d",press_chann_num);
        Lcd16x2_Out(1,1,lbuf);

        prv16_val1 = sys.para.forkcalib_press_min[pindex][0];   //Pressure value
        prv16_val2 = sys.para.forkcalib_press_min[pindex][1];   //Pressure count        
    }
    else
    {
        sprintf(lbuf,"CALIB PRES MAX %01d",press_chann_num);
        Lcd16x2_Out(1,1,lbuf);

        prv16_val1 = sys.para.forkcalib_press_max[pindex][0];   //Pressure value
        prv16_val2 = sys.para.forkcalib_press_max[pindex][1];   //Pressure count
    }
    
    sprintf(lbuf,"PV:%04.1f  PC:%04d",((float)prv16_val1)/10.0,prv16_val2);
    Lcd16x2_Out(2,1,lbuf);
}

void Display_Fork_MinMax_Press_Menu_Cursor(void)
{
    char lbuf[20];
    
//    if(sys.para.Select_System == TMC_MANBASKET)
//    {
//        if(press_chann_num == 1)
//            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p1_cnt); 
//        else if(press_chann_num == 2)
//            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p2_cnt);
//        else if(press_chann_num == 3)
//            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p3_cnt);
//        else if(press_chann_num == 4)
//            sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,can_p4_cnt);
//    }
//    else if(sys.para.Select_System == FORK_LIFT)
//    {
        sprintf(lbuf,"CV:%04.1f  CC:%04d",((float)prv16_val1)/10.0,p1_pressure_cnt);        
//    }
    Lcd16x2_Out(1,1,lbuf);
    
    sprintf(lbuf,"P:%04.1f      %04d",((float)prv16_val1)/10.0,prv16_val2);
    Lcd16x2_Out(2,1,lbuf);
    
    pos_t = 0;
    common_byte = 3; 
    common_long = prv16_val1;
    sprintf(lbuf,"%04.1f",((float)prv16_val1)/10.0);
    Lcd16x2_Out(1,4,lbuf);
    Move_Cursor_Left(1);
    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
}

/*============================================================================*/
/*
 * Function      :        Supervisor_Setting.
 * Description   :        Used to init cursor position and cursor blinking if neccessary.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Supervisor_Setting(void)
{
    char sbuf[20];
    
    switch(mv.supervisor_set)
    {
        case EN_BYPASS_SWITCH:
            //Cursor position not required
            Lcd16x2_Out(1,1," BYPASS SWITCH: ");
            Show_Enable_Disable_String(sys.para.bpk_enable_bit);
        break;
        case SET_SP1_VALUE:            
            Lcd16x2_Out(1,1,"  SET POINT-1:  ");
            Supervisor_Parametere_Value();
        break;
        case SET_SP2_VALUE:            
            Lcd16x2_Out(1,1,"  SET POINT-2:  ");
            Supervisor_Parametere_Value();
        break;
        case SET_SP3_VALUE:
            Lcd16x2_Out(1,1,"  SET POINT-3:  ");
            Supervisor_Parametere_Value();
        break;
        case SET_SP4_VALUE:
            Lcd16x2_Out(1,1,"  SET POINT-4:  ");
            Supervisor_Parametere_Value();
        break;
        case SET_BOOM_OFFSET:
            Lcd16x2_Out(1,1,"SET BOOM OFFSET:");
            Supervisor_Parametere_Value();            
        break;
        case SET_BM_HEAD_OFFSET:    //temp_head_offset            
            Lcd16x2_Out(1,1,"SET BM HEAD OFF.");
            Supervisor_Parametere_Value();
        break;
        case SET_BM_TIP_OFFSET:     //temp_tip_offset
            Lcd16x2_Out(1,1,"SET BM TIP OFF.:");
            Supervisor_Parametere_Value();
        break;
        case SET_MAIN_SAMPLE_CNT:
            Lcd16x2_Out(1,1,"SET MAIN SMP CNT");
            Supervisor_Parametere_Value();
        break;
        case SET_HOOK_LOAD:        
            Lcd16x2_Out(1,1,"SET HOOK LOAD:  ");
            Supervisor_Parametere_Value();
        break;
        case CALIB_LENGTH_MIN:  
            Supervisor_Parametere_Value();
        break;
        case CALIB_LENGTH_MAX:  
            if(sys.para.Select_System == FORK_LIFT)
                Supervisor_Parametere_Value();
        break;
        case CALIB_ANGLE_MIN:
            Supervisor_Parametere_Value();
        break;
        case CALIB_ANGLE_MAX:
            Supervisor_Parametere_Value();
        break;
        case CALIB_MANGLE_MIN:
            Supervisor_Parametere_Value();
        break;
        case CALIB_MANGLE_MAX:
            Supervisor_Parametere_Value();
        break;
        case NUMOF_CALIB_POINTS:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(1,1,"NUMOF CAL POINT:");
                Supervisor_Parametere_Value();
            }
            else
            {
                Lcd16x2_Out(2,1," NOT AVAILABLE  ");
            }
        break;
        case SET_DUTY_TYPE:
            if(sys.para.Select_System == FORK_LIFT)
            {
                common_short = 1;
                byt1 = 0;       //This variable decides the min or max pressure calibration
                
                Display_Fork_MinMax_Press_Menu(common_short-1,byt1);
                menu_stat = FORK_PRESS_MINMAX_PAGE1;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                byt1 = 0;       //This variable decides the min or max pressure calibration
                Display_TMC_MinMax_Press_Menu();
                menu_stat = TMC_PRESS_MINMAX_PAGE;
            }
            else
            {
                temp_duty_indx = 1;
                Display_Duty_Type_Menu();
                menu_stat = DUTY_TYPE_INDEX_PAGE;
                Duty_Type_Cursor_Position();
            }
        break;        
        case CALIB_HOOK_LOAD:
            if(sys.para.Select_System == FORK_LIFT)
            {
                common_short = 1;
                byt1 = 1;       //This variable decides the min=0 or max=1 pressure calibration
//                if(sys.para.Select_System == TMC_MANBASKET)
//                    Display_TMC_MinMax_Press_Menu(common_short-1,byt1);
//                else
                Display_Fork_MinMax_Press_Menu(common_short-1,byt1);
                menu_stat = FORK_PRESS_MINMAX_PAGE1;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                byt1 = 1;       //This variable decides the min or max pressure calibration
                Display_TMC_MinMax_Press_Menu();
                menu_stat = TMC_PRESS_MINMAX_PAGE;
            }
            else
            {
                temp_duty_indx = sys.para.duty;
                Display_Calib_Hook_Load_Menu();
                menu_stat = HOOK_LOAD_CALIB_PAGE1;
                Calib_Hook_Load_Cursor_Position();
            }
        break;
        case EN_PASSWORD:
            //Cursor position not required
            Lcd16x2_Out(1,1,"PASSWORD STATUS:");
            Show_Enable_Disable_String(sys.para.pw_stat_bit);
        break;
        case EN_BM_DWN_RLY:
            //Cursor position not required
            Lcd16x2_Out(1,1,"BOOM DWN RELAY: ");
            Show_Enable_Disable_String(sys.para.bmdwn_rly_stat_bit);
        break;
        case EN_BM_UP_RLY:
            //Cursor position not required
            Lcd16x2_Out(1,1," BOOM UP RELAY: ");
            Show_Enable_Disable_String(sys.para.bmup_rly_stat_bit);
        break;
        case EN_HOOTER_RLY:
            //Cursor position not required
            Lcd16x2_Out(1,1," HOOTER RELAY:  ");
            Show_Enable_Disable_String(sys.para.hootr_rly_stat_bit);
        break;
        case EN_A2B:
        //Cursor position not required
            Lcd16x2_Out(1,1,"  A2B SWITCH:   ");
            Show_Enable_Disable_String(sys.para.a2b_stat_bit);
        break;
        case EN_HK_HEIGHT:
        //Cursor position not required
            Lcd16x2_Out(1,1,"  HOOK HEIGHT:  ");
            Show_Enable_Disable_String(sys.para.hk_height_stat_bit);
        break;
        case RIG_LOAD_LIMIT:
            Lcd16x2_Out(1,1,"RIG LOAD LIMIT: ");
            Supervisor_Parametere_Value();
        break;
        case RIG_BM_ANGLE_LIMIT:
            Lcd16x2_Out(1,1,"RIG BM ANG LMT: ");
            Supervisor_Parametere_Value();
        break;
        case RIG_BM_LENGTH_LIMIT:
            Lcd16x2_Out(1,1,"RIG BM LEN LIMIT");
            Supervisor_Parametere_Value();
        break;
        case RIG_DEFAULT_DUTY:
            Lcd16x2_Out(1,1,"  DEFAULT DUTY  ");
            Supervisor_Parametere_Value();
        break;
        case EDIT_ENGINE_NUMBER:
            Lcd16x2_Out(1,1,"EDIT ENGINE NO: ");
            Supervisor_Parametere_Value();
        break;
        case ARTICULATION_DERATE_PERC:
            Lcd16x2_Out(1,1,"AL DTY ART.DRATE");
            Supervisor_Parametere_Value();
        break;
        case VIEW_DATA_LOGGED:
            Lcd16x2_Out(1,1,"VIEW DATA LOGGED");
        break;
        case SEND_DATA_TO_PC:
            Lcd16x2_Out(1,1,"SEND DATA TO PC:");
        break;
        case LOW_CUTOFF_ANGLE:
            Lcd16x2_Out(1,1,"LOW CUTOFF ANGLE");
            Supervisor_Parametere_Value();
        break;
        case HIGH_CUTOFF_ANGLE:
            Lcd16x2_Out(1,1,"HI CUTOFF ANGLE:");
            Supervisor_Parametere_Value();
        break;
        case EN_DUTY_SELECT:
            //Cursor position not required
            Lcd16x2_Out(1,1,"DUTY SEL STATUS:");
            Show_Enable_Disable_String(sys.para.duty_select_stat_bit);
        break;
        case EN_SNATCH_BLOCK:
            //Cursor position not required
            Lcd16x2_Out(1,1," SNATCH BLOCK:  ");
            Show_Enable_Disable_String(sys.para.snatch_block_stat_bit);
        break;
        case SNATCH_BLOCK_VALUE:
            Lcd16x2_Out(1,1,"SNATCH BLOCK VAL");
            Supervisor_Parametere_Value();
        break;
        case BYPASS_METHOD:
            if(sys.para.Select_System == FORK_LIFT)
            {
                Lcd16x2_Out(1,1,"ARTICULTN METHOD");    //Spacial case for SCA forklift
            }
            else
            {
                Lcd16x2_Out(1,1,"BYPASS METHOD:  ");
            }
            Show_Enable_Disable_String(sys.para.bpk_method_stat_bit);
        break;        
        case FRONT_TILT_ANGLE_CALIB:
            Supervisor_Parametere_Value();
        break;        
        case REAR_TILT_ANGLE_CALIB:
            Supervisor_Parametere_Value();
        break;             
        case VOICE_LANGUAGE:
            Supervisor_Parametere_Value();
        break;
        case SET_ZERO_LOAD_MASKING:        
            Lcd16x2_Out(1,1,"SET ZLOAD MASK: ");
            Supervisor_Parametere_Value();
        break;
        case LOAD_ANNOUNCE_TIMER:
            Lcd16x2_Out(1,1,"SET LD ANN. TIME");
            Supervisor_Parametere_Value();
        break;
        case FRONT_TILT_CUTOFF:
            Supervisor_Parametere_Value();
        break;             
        case REAR_TILT_CUTOFF:
            Supervisor_Parametere_Value();
        break;             
        case SET_MAX_BOOM_LENGTH :
            Lcd16x2_Out(1,1,"BOOM HIGHT LIMIT");
            Supervisor_Parametere_Value();
        break;      
        case SET_MAX_BOOM_ANGLE :
            Lcd16x2_Out(1,1,"BOOM ANGLE LIMIT");
            Supervisor_Parametere_Value();
        break;             
        case SET_HEIGHT_OFFSET:
            Lcd16x2_Out(1,1,"BOOM HIGHT OFSET");
            Supervisor_Parametere_Value();
        break;
        case SET_LOADCEL_ADC_OFFST:
            Lcd16x2_Out(1,1,"SET GAIN OFFSET:");
            Supervisor_Parametere_Value();
        break;
        case CALIB_MANBAS_MIN:
//            Lcd16x2_Out(1,1,"CALIB MANBAS MIN");
            Supervisor_Parametere_Value();
        break;
        case CALIB_MANBAS_MAX:
//            Lcd16x2_Out(1,1,"CALIB MANBAS MAX");
            Supervisor_Parametere_Value();
        break;
        case EN_ART_DRATE_PERC:
            //Cursor position not required
            Lcd16x2_Out(1,1,"EN ART.DRATE SW:");
            Show_Enable_Disable_String(sys.para.art_enable_bit);
        break;
        case ART_DRATE_PERC_VALUE:
            if(sys.para.art_enable_bit)
            {
                temp_duty_indx = 1; 
                Display_ArtDerate_Menu();                
                menu_stat = SET_ART_DRATE_PERCENTAGE1; 
                ArtDerate_Cursor_Position();
            }
        break;
        case SET_SLEW_OFFSET:
            Lcd16x2_Out(1,1,"SET SLEW OFFSET:");
            Supervisor_Parametere_Value();            
        break;
        case EN_ONBOARD_SING_TILT:
            //Cursor position not required
            Lcd16x2_Out(1,1,"EN ONBOARD TILT:");
            Show_Enable_Disable_String(sys.para.obtilt_enable_bit);
        break;
        case EN_SLAVE_DISPLAY:
            //Cursor position not required
            Lcd16x2_Out(1,1,"EN SLAVE DISPLAY");
            Show_Enable_Disable_String(sys.para.slave_enable_bit);
        break;
        case EN_MPOINT_LEN_CALIB:
            //Cursor position not required
            Lcd16x2_Out(1,1,"EN MPOINT LCALIB");
            Show_Enable_Disable_String(sys.para.mpoint_len_enable_bit);
        break;
        case NUMOF_MPOINT_LEN_CALIB:
            Lcd16x2_Out(1,1,"NUMOF LEN MP CAL");
            Supervisor_Parametere_Value();
        break;
        case MPOINT_LCALIBRATION_MENU:
            Lcd16x2_Out(1,1,"CALIB POINT: 01 ");
            prv8_val1 = 1;      //start of point calibration
            
            if((sys.para.multipt_lcalib[prv8_val1-1][0] != sys.para.bm_length_min)||(sys.para.multipt_lcalib[prv8_val1][0] < sys.para.bm_length_min))
            {
                sys.para.multipt_lcalib[prv8_val1-1][0] = sys.para.bm_length_min;
                sys.para.multipt_lcalib[prv8_val1-1][1] = 500;
                
                sys.para.multipt_lcalib[prv8_val1][0] = sys.para.bm_length_min+10;
                sys.para.multipt_lcalib[prv8_val1][1] = 1500;
//                UART_Send_String(UART_MODULE1,"Value not matched to bm_length_min\r\n");
            }
            prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
            prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
            
            if(prv16_val1 > 0)
            {
                sprintf(sbuf,"LV:%04.1f mm:%05lu",((float)prv16_val1)/10.0,(uint32_t)prv16_val2);
                Lcd16x2_Out(2,1,sbuf);
            }
            else
            {
                prv16_val1 = 0;
                prv16_val2 = 0;
                Lcd16x2_Out(2,1,"ADD NEW CALIB.  ");
            }
            menu_stat = LEN_MPOINT_CALIBRATION_PAGE1;
//            pos_t = 0;
//            common_byte = 3;
//            common_long = prv16_val1;
//            Move_Cursor_Left(10);
//            Lcd_Cmd(LCD_BLINK_CURSOR_ON);
        break;
        case MASTER_RESET_DEFAULT:
            Lcd16x2_Out(1,1,"MASTER RESET    ");
            Lcd16x2_Out(2,1,"ACTION:YES      ");
            prv8_val1 = 0;
        break;            
    }
}


void Choose_Yes_No(void)
{
    if(!prv8_val1)  Lcd16x2_Out(2,8,"YES");
    else            Lcd16x2_Out(2,8,"YES");
}

/*============================================================================*/
/*
 * Function      :        Supervisor_Shift_Cursor.
 * Description   :        Used to cursor left/right.
 * Parameters    :        flag_lr-left/right flag.
 * Return        :        None.
*/
/*============================================================================*/
void Supervisor_Shift_Cursor(uint8_t flag_lr)
{
    if((mv.supervisor_set == SET_SP1_VALUE)||(mv.supervisor_set == SET_SP2_VALUE)||
       (mv.supervisor_set == SET_SP3_VALUE)||(mv.supervisor_set == SET_SP4_VALUE)||
       (mv.supervisor_set == ARTICULATION_DERATE_PERC)||(mv.supervisor_set == LOAD_ANNOUNCE_TIMER)||
       ((mv.supervisor_set == ART_DRATE_PERC_VALUE)&&(menu_stat == SET_ART_DRATE_PERCENTAGE2)))
    {
        Shift_Cursor_Position(flag_lr,3,NO_DECIMAL_POINT);
    }
    else if((mv.supervisor_set == SET_MAIN_SAMPLE_CNT)||(mv.supervisor_set == RIG_DEFAULT_DUTY)||
            (mv.supervisor_set == HIGH_CUTOFF_ANGLE)||(mv.supervisor_set == RIG_BM_ANGLE_LIMIT)||
            (mv.supervisor_set == SET_MAX_BOOM_ANGLE)||(mv.supervisor_set == NUMOF_CALIB_POINTS)||
            ((mv.supervisor_set == ART_DRATE_PERC_VALUE)&&(menu_stat == SET_ART_DRATE_PERCENTAGE1))||
            (mv.supervisor_set == NUMOF_MPOINT_LEN_CALIB))
    {
         Shift_Cursor_Position(flag_lr,2,NO_DECIMAL_POINT);
    }    
    else if((mv.supervisor_set == SET_HOOK_LOAD)||(mv.supervisor_set == CALIB_LENGTH_MIN)||
            (mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX)||
            (mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX)||
            (mv.supervisor_set == RIG_LOAD_LIMIT)||(mv.supervisor_set == RIG_BM_LENGTH_LIMIT)||
            (mv.supervisor_set == SET_MAX_BOOM_LENGTH)||(mv.supervisor_set == CALIB_LENGTH_MAX)||
            (((mv.supervisor_set == SET_DUTY_TYPE)||(mv.supervisor_set == CALIB_HOOK_LOAD))&&(sys.para.Select_System == FORK_LIFT))||
            (mv.supervisor_set == SET_HEIGHT_OFFSET)||(mv.supervisor_set == SET_ZERO_LOAD_MASKING))
    {
        Shift_Cursor_Position(flag_lr,3,ONE_DECIMAL_POINT);
    }
    else if((mv.supervisor_set == SET_BOOM_OFFSET)||(mv.supervisor_set == SET_BM_HEAD_OFFSET)||
            (mv.supervisor_set == SET_BM_TIP_OFFSET)||(mv.supervisor_set == LOW_CUTOFF_ANGLE)||
            (mv.supervisor_set == SET_SLEW_OFFSET))
    {
        Shift_Cursor_Position(flag_lr,4,ONE_DECIMAL_POINT);
    }
    else if(mv.supervisor_set == EDIT_ENGINE_NUMBER)
    {
        Shift_Cursor_Position(flag_lr,10,NO_DECIMAL_POINT);
    }
    else if((mv.supervisor_set == SNATCH_BLOCK_VALUE)||(mv.supervisor_set == CALIB_MANBAS_MIN)||(mv.supervisor_set == CALIB_MANBAS_MAX))
    {
        Shift_Cursor_Position(flag_lr,4,NO_DECIMAL_POINT);
    }
    else if(mv.supervisor_set == SET_LOADCEL_ADC_OFFST)
    {
        Shift_Cursor_Position(flag_lr,5,NO_DECIMAL_POINT);
    }
}


/*============================================================================*/
/*
 * Function      :        Supervisor_Change_Parameter_Value.
 * Description   :        Used to change(inc/dec) values.
 * Parameters    :        flag_id-increment/decrement flag.
 * Return        :        None.
*/
/*============================================================================*/
void Supervisor_Change_Parameter_Value(uint8_t flag_id)
{
    char lbuf[20];
    
    if(flag_id == 0)    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
    else                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
    
    if((mv.supervisor_set == EN_BYPASS_SWITCH)||(mv.supervisor_set == EN_PASSWORD)||
       (mv.supervisor_set == EN_BM_DWN_RLY)||(mv.supervisor_set == EN_BM_UP_RLY)||
       (mv.supervisor_set == EN_HOOTER_RLY)||(mv.supervisor_set == EN_A2B)||
       (mv.supervisor_set == EN_HK_HEIGHT)||(mv.supervisor_set == EN_DUTY_SELECT)||
       (mv.supervisor_set == EN_SNATCH_BLOCK)||(mv.supervisor_set == BYPASS_METHOD)||
       (mv.supervisor_set == EN_ART_DRATE_PERC)||(mv.supervisor_set == EN_SLAVE_DISPLAY)||
       (mv.supervisor_set == EN_MPOINT_LEN_CALIB)||(mv.supervisor_set == EN_ONBOARD_SING_TILT))
    {
        prv8_val1 = !prv8_val1;
        Show_Enable_Disable_Stat(prv8_val1);
    }
    else if((mv.supervisor_set == SET_SP1_VALUE)||(mv.supervisor_set == SET_SP2_VALUE)||
            (mv.supervisor_set == SET_SP3_VALUE)||(mv.supervisor_set == SET_SP4_VALUE)||
            (mv.supervisor_set == ARTICULATION_DERATE_PERC)||
            ((mv.supervisor_set == ART_DRATE_PERC_VALUE)&&(menu_stat == SET_ART_DRATE_PERCENTAGE2)))
    {
        sprintf(lbuf,"%03d",(uint16_t)common_long);
        if((mv.supervisor_set == ART_DRATE_PERC_VALUE)&&(menu_stat == SET_ART_DRATE_PERCENTAGE2))
        {
            Lcd16x2_Out(2,11,lbuf);
        }
        else
        {
            Lcd16x2_Out(2,4,lbuf);
        }
        
        Move_Cursor_Left(pos_t+1);
    }
    else if((mv.supervisor_set == SET_MAIN_SAMPLE_CNT)||(mv.supervisor_set == RIG_DEFAULT_DUTY)||
            (mv.supervisor_set == HIGH_CUTOFF_ANGLE)||(mv.supervisor_set == RIG_BM_ANGLE_LIMIT)||
            (mv.supervisor_set ==SET_MAX_BOOM_ANGLE)||(mv.supervisor_set == NUMOF_CALIB_POINTS)||
            ((mv.supervisor_set == ART_DRATE_PERC_VALUE)&&(menu_stat == SET_ART_DRATE_PERCENTAGE1))||
            (mv.supervisor_set == NUMOF_MPOINT_LEN_CALIB))
    {        
        if((mv.supervisor_set == ART_DRATE_PERC_VALUE)&&(menu_stat == SET_ART_DRATE_PERCENTAGE1))
        {
            sprintf(lbuf,"%03d",sys.para.indopower_art_derate[(uint8_t)common_long-1]);
            Lcd16x2_Out(2,11,lbuf);
            sprintf(lbuf,"%02d",(uint8_t)common_long);
            Lcd16x2_Out(1,11,lbuf);
        }
        else
        {
            sprintf(lbuf,"%02d",(uint8_t)common_long);
            Lcd16x2_Out(2,4,lbuf);
        }
        Move_Cursor_Left(pos_t+1);
    }
    else if((mv.supervisor_set == SET_BOOM_OFFSET)||(mv.supervisor_set == SET_BM_HEAD_OFFSET)||
            (mv.supervisor_set == SET_BM_TIP_OFFSET)||(mv.supervisor_set == LOW_CUTOFF_ANGLE)||
            (mv.supervisor_set == SET_SLEW_OFFSET))
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
    else if((mv.supervisor_set == SET_HOOK_LOAD)||(mv.supervisor_set == CALIB_LENGTH_MIN)||
            (mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX)||
            (mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX)||
            (mv.supervisor_set == RIG_LOAD_LIMIT)||(mv.supervisor_set == RIG_BM_LENGTH_LIMIT)||
            (mv.supervisor_set == SET_MAX_BOOM_LENGTH)||(mv.supervisor_set == CALIB_LENGTH_MAX)||
            (((mv.supervisor_set == SET_DUTY_TYPE)||(mv.supervisor_set == CALIB_HOOK_LOAD))&&(sys.para.Select_System == FORK_LIFT))||
            (mv.supervisor_set == SET_HEIGHT_OFFSET)||(mv.supervisor_set == SET_ZERO_LOAD_MASKING))
    {
        sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
        if((mv.supervisor_set == SET_HOOK_LOAD)||(mv.supervisor_set == RIG_LOAD_LIMIT)||
           (mv.supervisor_set == RIG_BM_LENGTH_LIMIT)||(mv.supervisor_set ==SET_MAX_BOOM_LENGTH)||
           (mv.supervisor_set == SET_HEIGHT_OFFSET)||(mv.supervisor_set == SET_ZERO_LOAD_MASKING))
            Lcd16x2_Out(2,4,lbuf);
        else
            Lcd16x2_Out(1,4,lbuf);
        if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
        else            Move_Cursor_Left(pos_t+1);
    }
    else if(mv.supervisor_set == EDIT_ENGINE_NUMBER)
    {
      sprintf(lbuf,"%010lu",common_long);
      Lcd16x2_Out(2,4,lbuf);
      Move_Cursor_Left(pos_t+1);
    }
    else if(mv.supervisor_set == VIEW_DATA_LOGGED)
    {
        
    }
    else if(mv.supervisor_set == SEND_DATA_TO_PC)
    {

    }
    else if(mv.supervisor_set == SNATCH_BLOCK_VALUE)
    {
      sprintf(lbuf,"%04d",(uint16_t)common_long);
      Lcd16x2_Out(2,4,lbuf);
      Move_Cursor_Left(pos_t+1);
    }
    else if(mv.supervisor_set == VOICE_LANGUAGE)
    {
       prv8_val1 = !prv8_val1;
       Lcd16x2_Out(1,4,(char *)Voice_Language[prv8_val1]);  
    }
    else if(mv.supervisor_set == FRONT_TILT_CUTOFF ||(mv.supervisor_set == REAR_TILT_CUTOFF))
    {        
        sprintf(lbuf,"%01d",(uint8_t)common_long);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
    else if(mv.supervisor_set == LOAD_ANNOUNCE_TIMER)
    {
//        if(common_long < 5) common_long = 5;
        sprintf(lbuf,"%03d",(uint8_t)common_long);
        Lcd16x2_Out(2,4,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
    else if(mv.supervisor_set == SET_LOADCEL_ADC_OFFST)
    {
        sprintf(lbuf,"%05d",(uint16_t)common_long);
        Lcd16x2_Out(2,3,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
    else if((mv.supervisor_set == CALIB_MANBAS_MIN)||(mv.supervisor_set == CALIB_MANBAS_MAX))
    {
        sprintf(lbuf,"%04d",(uint16_t)common_long);
        Lcd16x2_Out(1,4,lbuf);
        Move_Cursor_Left(pos_t+1);
    }
    else if(mv.supervisor_set == MASTER_RESET_DEFAULT)
    {
        prv8_val1 = !prv8_val1;
        Choose_Yes_No();
    }
}

void Supervisor_Show_Live_Adc(void)
{
    char lbuf[20];
    float Alpha2;

    if(disp_refresh_cnt == 0)
    {
        disp_refresh_cnt = 500;
        if((mv.supervisor_set == CALIB_LENGTH_MIN)||(mv.supervisor_set == CALIB_LENGTH_MAX))
        {
            sprintf(lbuf,"%04d",len_adc_cnt);
            Lcd16x2_Out(1,13,lbuf);
            sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
            Lcd16x2_Out(1,4,lbuf);
            if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
            else            Move_Cursor_Left(pos_t+1);
        }
        else if((((mv.supervisor_set == SET_DUTY_TYPE)||(mv.supervisor_set == CALIB_HOOK_LOAD))&&
                ((sys.para.Select_System == FORK_LIFT)||(sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))))
        {
            if(sys.para.Select_System == FORK_LIFT)
            {
                complimnt_flag = !complimnt_flag;
                sprintf(lbuf,"%04d",p1_pressure_cnt);
                Lcd16x2_Out(1,13,lbuf);
                
                if(complimnt_flag)
                {
                    if(sys.para.bpk_method_stat_bit)
                    {   //Spacial case for SCA fork lift were articulation input is used for MAST change
                        sprintf(lbuf," %d  ",art_ip_bit);
                    }
                    else
                    {
                        sprintf(lbuf,"%04.1f",((float)TotalBmLength)/10.0);
                    }
                    Lcd16x2_Out(2,8,lbuf);
                }
                else
                {
                    Lcd16x2_Out(2,8,"    ");
                }
                sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
                Lcd16x2_Out(1,4,lbuf);
                if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
                else            Move_Cursor_Left(pos_t+1);
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
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
        }
        else if((mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX)||
                (mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX))
        {
            if((mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX))
                sprintf(lbuf,"%04d",ang_adc_cnt);
            else
                sprintf(lbuf,"%04d",Main_ang_adc_cnt);
            Lcd16x2_Out(1,13,lbuf);
            sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
            Lcd16x2_Out(1,4,lbuf);
            if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
            else            Move_Cursor_Left(pos_t+1);
        }
        else if(mv.supervisor_set== FRONT_TILT_ANGLE_CALIB )
        {
              sprintf(lbuf,"LA:%04d",Tilt_1_X_cnt);
              Lcd16x2_Out(1,1,lbuf);
              sprintf(lbuf,"LO:%04d",Tilt_1_Y_cnt);
              Lcd16x2_Out(2,1,lbuf);
        }
        else if(mv.supervisor_set== REAR_TILT_ANGLE_CALIB )
        {
              sprintf(lbuf,"LA:%04d",Tilt_2_X_cnt);
              Lcd16x2_Out(1,1,lbuf);
              sprintf(lbuf,"LO:%04d",Tilt_2_Y_cnt);
              Lcd16x2_Out(2,1,lbuf);
        }
        else if((mv.supervisor_set == CALIB_MANBAS_MIN)||(mv.supervisor_set == CALIB_MANBAS_MAX))
        {
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                sprintf(lbuf,"%05lu",(uint32_t)can_loadcell_cnt);
            else if(sys.para.Select_System == ACE_MANBASKET_HXP)
                sprintf(lbuf,"%05d",loadcell_cnt);
            Lcd16x2_Out(1,12,lbuf);
            sprintf(lbuf,"%04d",(uint16_t)common_long);
            Lcd16x2_Out(1,4,lbuf);
            Move_Cursor_Left(pos_t+1);
        }
        else if(mv.supervisor_set == MPOINT_LCALIBRATION_MENU)
        {
            if(len_adc_cnt >= 600)
            {
                Alpha2 = Flot_Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)*100;
                Alpha2 = RoundOff(Alpha2);
                mm_len = (uint16_t)Alpha2;
//                mm_len = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)*100;
            }
            else
                mm_len = 0;
            sprintf(lbuf,"%05lu",(uint32_t)mm_len);
            Lcd16x2_Out(2,12,lbuf);
            sprintf(lbuf,"%04.1f",((float)common_long)/10.0);
            Lcd16x2_Out(2,4,lbuf);
            if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
            else            Move_Cursor_Left(pos_t+1);
        }
    }
}


/*============================================================================*/
/*
 * Function      :        Supervisor_Save_Settings.
 * Description   :        Used to update the supervisor setting variables value.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Supervisor_Save_Settings(void)
{
    uint16_t temp_len;
    uint16_t RestoreCntr;
    
    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

    switch(mv.supervisor_set)
    {
        case EN_BYPASS_SWITCH:
            sys.para.bpk_enable_bit = prv8_val1;
            TempBypassEnbFlag = 1;
        break;
        case SET_SP1_VALUE:
            sys.para.sp1_perc = (uint16_t)common_long;
        break;
        case SET_SP2_VALUE:
            sys.para.sp2_perc = (uint16_t)common_long;
        break;
        case SET_SP3_VALUE:
            sys.para.sp3_perc = (uint16_t)common_long;
        break;
        case SET_SP4_VALUE:
            sys.para.sp4_perc = (uint16_t)common_long;
        break;
        case SET_BOOM_OFFSET:
            sys.para.bm_offset = (uint16_t)common_long;
            if(value_sign_flag) sys.para.bm_offset = sys.para.bm_offset*(-1);
        break;
        case SET_BM_HEAD_OFFSET:
            sys.para.bm_head_offset = (uint16_t)common_long;
            if(value_sign_flag) sys.para.bm_head_offset = sys.para.bm_head_offset*(-1);
        break;
        case SET_BM_TIP_OFFSET:
            sys.para.bm_tip_offset = (uint16_t)common_long;
            if(value_sign_flag) sys.para.bm_tip_offset = sys.para.bm_tip_offset*(-1);
        break;
        case SET_MAIN_SAMPLE_CNT:
            sys.para.main_smpl_cnt = (uint16_t)common_long;
        break;
        case SET_HOOK_LOAD:
            sys.para.hook_load = (uint16_t)common_long;
        break;
        case CALIB_LENGTH_MIN:
            sys.para.cal_len_min = (uint16_t)common_long;
            if((sys.para.Select_System != FORK_LIFT)&&(sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
            {
                temp_len = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt);
                
              if(temp_len <= sys.para.cal_len_min)    sys.para.bl_adc_cnt[1] = sys.para.cal_len_min-temp_len;
              else                                    sys.para.bl_adc_cnt[1] = temp_len-sys.para.cal_len_min;
              sys.para.cal_len_min_cnt = len_adc_cnt;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                temp_len = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt);
                
                if(temp_len <= sys.para.cal_len_min)    sys.para.bl_adc_cnt[1] = sys.para.cal_len_min-temp_len;
                else                                    sys.para.bl_adc_cnt[1] = temp_len-sys.para.cal_len_min;
                sys.para.cal_len_min_cnt = len_adc_cnt;
            }
            else if(sys.para.Select_System == FORK_LIFT)
            {
                sys.para.cal_len_min_cnt = len_adc_cnt;
            }
        break;
        case CALIB_LENGTH_MAX:
            sys.para.cal_len_max = (uint16_t)common_long;
            sys.para.cal_len_max_cnt = len_adc_cnt;
        break;
        case CALIB_ANGLE_MIN:
            sys.para.cal_angle_min = (uint16_t)common_long;    
            sys.para.cal_angle_min_cnt = ang_adc_cnt;
        break;
        case CALIB_ANGLE_MAX:
            sys.para.cal_angle_max = (uint16_t)common_long;
            sys.para.cal_angle_max_cnt = ang_adc_cnt;
        break;
        case CALIB_MANGLE_MIN:
            sys.para.cal_mangle_min = (uint16_t)common_long;    
            sys.para.cal_mangle_min_cnt = Main_ang_adc_cnt;
        break;
        case CALIB_MANGLE_MAX:
            sys.para.cal_mangle_max = (uint16_t)common_long;
            sys.para.cal_mangle_max_cnt = Main_ang_adc_cnt;
        break;
        case NUMOF_CALIB_POINTS:
            sys.para.numof_calib_fork = (uint8_t)common_long;
        break;
        case SET_DUTY_TYPE:
            if(sys.para.Select_System == FORK_LIFT)       //Pressure P1 min
            {
                sys.para.forkcalib_press_min[common_short-1][0] = (uint16_t)common_long;
                sys.para.forkcalib_press_min[common_short-1][1] = p1_pressure_cnt;
                sys.para.fork_len_region[common_short-1] = TotalBmLength;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sys.para.forkcalib_press_min[0][1] = can_p1_cnt;
                sys.para.forkcalib_press_min[1][1] = can_p2_cnt;
                sys.para.forkcalib_press_min[2][1] = can_p3_cnt;
                sys.para.forkcalib_press_min[3][1] = can_p4_cnt;
            }
        break;
        case CALIB_HOOK_LOAD:
            if(sys.para.Select_System == FORK_LIFT)       //Pressure P1 max
            {
                sys.para.forkcalib_press_max[common_short-1][0] = (uint16_t)common_long;
                sys.para.forkcalib_press_max[common_short-1][1] = p1_pressure_cnt;
            }
            else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                sys.para.forkcalib_press_max[0][1] = can_p1_cnt;
                sys.para.forkcalib_press_max[1][1] = can_p2_cnt;
                sys.para.forkcalib_press_max[2][1] = can_p3_cnt;
                sys.para.forkcalib_press_max[3][1] = can_p4_cnt;
            }
        break;
        case EN_PASSWORD:
            sys.para.pw_stat_bit = prv8_val1;
        break;
        case EN_BM_DWN_RLY:
            sys.para.bmdwn_rly_stat_bit = prv8_val1;
        break;
        case EN_BM_UP_RLY:
            sys.para.bmup_rly_stat_bit = prv8_val1;
        break;
        case EN_HOOTER_RLY:
            sys.para.hootr_rly_stat_bit = prv8_val1;
        break;
        case EN_A2B:
            sys.para.a2b_stat_bit = prv8_val1;
        break;
        case EN_HK_HEIGHT:
            sys.para.hk_height_stat_bit = prv8_val1;
        break;
        case RIG_LOAD_LIMIT:
            sys.para.rig_load_lmt = (uint16_t)common_long;
        break;
        case RIG_BM_ANGLE_LIMIT:
            sys.para.rig_bm_angl_lmt = (uint16_t)common_long;
        break;
        case RIG_BM_LENGTH_LIMIT:
            sys.para.rig_bm_len_lmt = (uint16_t)common_long;
        break;
        case RIG_DEFAULT_DUTY:
            sys.para.default_duty = (uint16_t)common_long;
        break;
        case EDIT_ENGINE_NUMBER:
            sys.para.engine_number = common_long;
        break;
        case ARTICULATION_DERATE_PERC:
        sys.para.art_derate_perc = (uint16_t)common_long;
        break;
        case VIEW_DATA_LOGGED:
        break;
        case SEND_DATA_TO_PC:
        break;
        case LOW_CUTOFF_ANGLE:
            sys.para.low_cutoff_angl = (uint16_t)common_long;
            if(value_sign_flag) sys.para.low_cutoff_angl = sys.para.low_cutoff_angl*(-1);
        break;
        case HIGH_CUTOFF_ANGLE:
            sys.para.hi_cutoff_angl = (uint16_t)common_long;
        break;
        case EN_DUTY_SELECT:
            sys.para.duty_select_stat_bit = prv8_val1;
        break;
        case EN_SNATCH_BLOCK:
            sys.para.snatch_block_stat_bit = prv8_val1;
        break;
        case SNATCH_BLOCK_VALUE:
            sys.para.snatch_block_val = (uint16_t)common_long;
        break;
        case BYPASS_METHOD:
            sys.para.bpk_method_stat_bit = prv8_val1;
        break;
        case FRONT_TILT_ANGLE_CALIB : 
              sys.para.Tilt1_X_MinAdc=Tilt_1_X_cnt;//
              sys.para.Tilt1_Y_MinAdc=Tilt_1_Y_cnt;
              break;

        case REAR_TILT_ANGLE_CALIB :  
            sys.para.Tilt2_X_MinAdc=Tilt_2_X_cnt;//
            sys.para.Tilt2_Y_MinAdc=Tilt_2_Y_cnt;
        break;
        case VOICE_LANGUAGE :
            sys.para.voice_of_language=prv8_val1;
        break;
        case SET_ZERO_LOAD_MASKING:
            sys.para.zload_mask = (uint16_t)common_long;
        break;
        case LOAD_ANNOUNCE_TIMER:
            sys.para.load_announce_timer = (uint16_t)common_long;
        break;
        case FRONT_TILT_CUTOFF :  
              sys.para.Front_tilt_Cutoff=(uint8_t)common_long;
              break;
        case REAR_TILT_CUTOFF :  
             sys.para.Rear_tilt_Cutoff=(uint8_t)common_long;
             break;
        case SET_MAX_BOOM_LENGTH :
            sys.para.Max_BLength  =(uint16_t)common_long;
        break;
        case SET_MAX_BOOM_ANGLE :
            sys.para.Max_BAngle  = (uint16_t)common_long;
        break;  
        case SET_HEIGHT_OFFSET:
            sys.para.bm_ht_offset  = (uint16_t)common_long;
        break;
        case SET_LOADCEL_ADC_OFFST :
            sys.para.loadcell_cnt_offst  = (uint16_t)common_long;
        break;  
        case CALIB_MANBAS_MIN:
            sys.para.manbasket_min = (uint16_t)common_long;
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                sys.para.manbasket_min_cnt = (uint16_t)can_loadcell_cnt;
            else if(sys.para.Select_System == ACE_MANBASKET_HXP)
                sys.para.manbasket_min_cnt = loadcell_cnt;
        break;
        case CALIB_MANBAS_MAX:
            sys.para.manbasket_max = (uint16_t)common_long;
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                sys.para.manbasket_max_cnt = (uint16_t)can_loadcell_cnt;
            else if(sys.para.Select_System == ACE_MANBASKET_HXP)
                sys.para.manbasket_max_cnt = loadcell_cnt;
        break;
        case EN_ART_DRATE_PERC:
            sys.para.art_enable_bit = prv8_val1;
        break;
        case SET_SLEW_OFFSET:
            sys.para.slew_offset = (uint16_t)common_long;
            if(value_sign_flag) sys.para.slew_offset = sys.para.slew_offset*(-1);
        break;
        case EN_ONBOARD_SING_TILT:
            sys.para.obtilt_enable_bit = prv8_val1;
        break;
        case EN_SLAVE_DISPLAY:
            sys.para.slave_enable_bit = prv8_val1;
        break;
        case EN_MPOINT_LEN_CALIB:
            sys.para.mpoint_len_enable_bit = prv8_val1;
        break;
        case NUMOF_MPOINT_LEN_CALIB:
            if((common_long >= 2)&&(common_long <= 15))
                sys.para.numof_len_cal = (uint8_t)common_long;
        break;
        case MASTER_RESET_DEFAULT:
        {
//            sys.para.crane_page_index = 1; 
            
            Read_Startup_SPIFlash();//Read again for default crane id-1
            
            flash.buf[FACTORY_DEFAULT_RESET] = 'W';

            sys.para.Radius_Cutoff = 0;

            sys.para.data_log_cntr = 0;

            sys.para.main_smpl_cnt = 20;

            sys.para.num_of_cylinders = 2;

            sys.para.cal_smpl_cnt = 30;

            sys.para.falls_cnt = lc_max_falls;

            sys.para.sel_uom = 1;

            sys.para.sp1_perc = 93;

            sys.para.sp2_perc = 98;

            sys.para.sp3_perc = 103;

            sys.para.sp4_perc = 110;

            sys.para.bm_offset = lc_bm_offset;

            sys.para.bm_head_offset = 0;

            sys.para.bm_tip_offset = 0;

            sys.para.baudrate = 1;

            sys.para.art_derate_perc = 0;

            sys.para.load_corr_limit = 0;//30
        
            //Read duty type - Number of length calibration points
            for(RestoreCntr=0; RestoreCntr<lc_total_duty; RestoreCntr++)
            {
                flash_page_addr =(((uint32_t)lc_press_curve_page_s-1)*256)+((RestoreCntr*10)*256)+flash_memory_offset;
                if(RestoreCntr < 20)
                {
                    sys.para.duty_type[RestoreCntr] = SPIFlash_Read_Byte(flash_page_addr+4)*256 + SPIFlash_Read_Byte(flash_page_addr+5); //read two byte --> 4+5

                    #ifdef DEBUG_MSG
                    sprintf(lbuf," sys.para.duty_type[%d]=%d\r\n",RestoreCntr,sys.para.duty_type[RestoreCntr]);
                    //UART_Send_String(UART_MODULE1,lbuf);
                    #endif
                }
                else break;
            }

            //Read duty type - length calibration values
     
            for(RestoreCntr=0; RestoreCntr<(lc_total_duty*5); RestoreCntr++)
            {
                flash_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256)+((RestoreCntr*2)*256)+flash_memory_offset;
                if(RestoreCntr < 60)
                {
                    sys.para.length_array[RestoreCntr] = SPIFlash_Read_Byte(flash_page_addr+2)*256 + SPIFlash_Read_Byte(flash_page_addr+3);

                    #ifdef DEBUG_MSG
                    sprintf(lbuf,"sys.para.length_array[%d]=%d\r\n",RestoreCntr,sys.para.length_array[RestoreCntr]);
                    //UART_Send_String(UART_MODULE1,lbuf);
                    #endif
                }
                else break;
            }

            for(RestoreCntr=0;RestoreCntr<6;RestoreCntr++)
            {
              sys.para.ld_corr_bmup[RestoreCntr] = 0;
            }

            sys.para.sel_sensor = 1;

            sys.para.calib_pressure1_min = 0;

            if(sys.para.sel_sensor == 1)
            {
              sys.para.calib_P1LowAdcCount = 655;
            }
            else
            {
              sys.para.calib_P1LowAdcCount = 390;
            }

            if(sys.para.sel_sensor == 1)
            {
              sys.para.calib_pressure1_max = 400;
            }
            else
            {
              sys.para.calib_pressure1_max = 344;
            }

            if(sys.para.sel_sensor == 1)
            {
              sys.para.calib_P1HighAdcCount = 3276;
            }
            else
            {
              sys.para.calib_P1HighAdcCount = 3685;
            }

            sys.para.calib_pressure2_min = 0;

            if(sys.para.sel_sensor == 1)
            {
              sys.para.calib_P2LowAdcCount = 655;
            }
            else
            {
              sys.para.calib_P2LowAdcCount = 390;
            }

            if(sys.para.sel_sensor == 1)
            {
              sys.para.calib_pressure2_max = 400;
            }
            else
            {
              sys.para.calib_pressure2_max = 344;
            }
            if(sys.para.sel_sensor == 1)
            {
              sys.para.calib_P2HighAdcCount = 3276;
            }
            else
            {
              sys.para.calib_P2HighAdcCount = 3685;
            }

            sys.para.cal_angle_min = 0;

            sys.para.cal_angle_min_cnt = 3500;

            sys.para.cal_angle_max = 600;

            sys.para.cal_angle_max_cnt = 1300;

            sys.para.bm_length_min = lc_bm_length_min;

            sys.para.bm_length_max = lc_bm_length_max;

            sys.para.cal_len_min = sys.para.bm_length_min;

            sys.para.bl_adc_cnt[1] = 0;

            sys.para.bl_adc_cnt[2] = 3000;

            sys.para.bl_adc_cnt[3] = 6000;

            sys.para.bl_adc_cnt[4] = 9000;

            sys.para.bl_adc_cnt[5] = 12000;

            sys.para.bl_adc_cnt[6] = 15000;
            
            sys.para.bl_adc_cnt[7] = 18000;

            sys.para.cal_len_max = sys.para.bm_length_max;

            sys.para.cal_len_max_cnt = 1400;

            sys.para.bpk_enable_bit = 1;

            sys.para.hk_height_stat_bit = 0;

            sys.para.low_err_cnt =0;

            sys.para.high_err_cnt = 4095;

            sys.para.pressure_p1_chann = 1;

            sys.para.pressure_p2_chann = 2;

            sys.para.bm_length_chann = 3;

            sys.para.bm_angle_chann = 4;

            sys.para.min_angle = 1;

            sys.para.max_angle = 65;

            sys.para.default_duty = lc_default_duty;

            sys.para.rig_duty_bit = 0;

            sys.para.rig_load_lmt = 10;

            sys.para.rig_bm_len_lmt = 10;

            sys.para.rig_bm_angl_lmt = 5;

            sys.para.pw_stat_bit = 0;

            sys.para.bmdwn_rly_stat_bit = 1;

            sys.para.bmup_rly_stat_bit = 1;

            sys.para.hootr_rly_stat_bit = 1;

            sys.para.a2b_stat_bit = 1;

            sys.para.load_avg_stat_bit = 1;

            sys.para.load_avg_val = 3;

            sys.para.window_sample_size = 4;

            sys.para.window_sample_size1 = 3;

            sys.para.hook_load = 0;

            sys.para.group_duty_s = 1;

            sys.para.group_duty_e = lc_total_duty;

            sys.para.vertical_offset = lc_vert_offset;

            sys.para.horizontal_offset = lc_horiz_offset;

            sys.para.rampivot_offset = lc_rampivo_offset;

            sys.para.bm_cntr_line_offset = lc_bmcntrline_offset;

            sys.para.piston_diameter = lc_piston_diameter;

            sys.para.rod_diameter = lc_rod_diameter;

            sys.para.bm_length_corr1 = 0;

            sys.para.bm_length_corr2 = 0;

            sys.para.bm_length_corr3 = 0;

            sys.para.bm_length_corr4 = 0;

            sys.para.fail_safe_stat_bit = 0;

            sys.para.hi_cutoff_angl = 63;

            sys.para.low_cutoff_angl = -30;

            sys.para.duty_select_stat_bit = 1;

            sys.para.snatch_block_stat_bit = 1;

            sys.para.snatch_block_val = 5;

            sys.para.sticker_type = NEW;

            sys.para.bpk_method_stat_bit = 1;

            sys.para.load_corr_factor = 0;

            sys.para.load_corr1 = 0;

            sys.para.load_corr2 = 0;

            sys.para.load_corr3 = 0;

            sys.para.load_corr4 = 0;

            sys.para.load_corr5 = 0;

            sys.para.fact = 33;

            sys.para.perc_fact_stat_bit = 0;

            sys.para.correction_load = 0;

            sys.para.num_cal = 0;

            sys.para.duty = lc_default_duty;

            sys.para.insta_dd = 1;
            sys.para.insta_mm = 1;
            sys.para.insta_yy = 2021;

            sys.para.engine_number = 0;

            sys.para.so_number = 0;

            sys.para.bl_fact[0] = 127;

            sys.para.bl_fact[1] = 129;

            sys.para.bl_fact[2] = 124;

            sys.para.bl_fact[3] = 120;

            sys.para.bl_fact[4] = 115;

//            sys.para.Select_System = 0;

            sys.para.Tilt1_X_MinAdc = 2020;
            sys.para.Tilt1_Y_MinAdc = 2020;
            
            sys.para.Max_BLength  = 100;
            sys.para.Max_BAngle  = 60;
            sys.para.Front_tilt_Cutoff = 5;
            sys.para.Rear_tilt_Cutoff = 5;

            sys.para.forkcalib_press_min[0][0] = 0;
            sys.para.forkcalib_press_min[0][1] = 750;
            sys.para.forkcalib_press_min[1][0] = 0;
            sys.para.forkcalib_press_min[1][1] = 750;
            sys.para.forkcalib_press_min[2][0] = 0;
            sys.para.forkcalib_press_min[2][1] = 750;
            sys.para.forkcalib_press_min[3][0] = 0;
            sys.para.forkcalib_press_min[3][1] = 750;
            sys.para.forkcalib_press_min[4][0] = 0;
            sys.para.forkcalib_press_min[4][1] = 750;
            sys.para.forkcalib_press_min[5][0] = 0;
            sys.para.forkcalib_press_min[5][1] = 750;
            sys.para.forkcalib_press_min[6][0] = 0;
            sys.para.forkcalib_press_min[6][1] = 750;
            sys.para.forkcalib_press_min[7][0] = 0;
            sys.para.forkcalib_press_min[7][1] = 750;

            sys.para.forkcalib_press_max[0][0] = 0;
            sys.para.forkcalib_press_max[0][1] = 1500;
            sys.para.forkcalib_press_max[1][0] = 0;
            sys.para.forkcalib_press_max[1][1] = 1500;
            sys.para.forkcalib_press_max[2][0] = 0;
            sys.para.forkcalib_press_max[2][1] = 1500;
            sys.para.forkcalib_press_max[3][0] = 0;
            sys.para.forkcalib_press_max[3][1] = 1500;
            sys.para.forkcalib_press_max[4][0] = 0;
            sys.para.forkcalib_press_max[4][1] = 1500;
            sys.para.forkcalib_press_max[5][0] = 0;
            sys.para.forkcalib_press_max[5][1] = 1500;
            sys.para.forkcalib_press_max[6][0] = 0;
            sys.para.forkcalib_press_max[6][1] = 1500;
            sys.para.forkcalib_press_max[7][0] = 0;
            sys.para.forkcalib_press_max[7][1] = 1500;

            sys.para.fork_len_region[0] = 0;
            sys.para.fork_len_region[1] = 20;
            sys.para.fork_len_region[2] = 40;
            sys.para.fork_len_region[3] = 60;
            sys.para.fork_len_region[4] = 80;
            sys.para.fork_len_region[5] = 100;
            sys.para.fork_len_region[6] = 120;
            sys.para.fork_len_region[7] = 140;
            
            sys.para.numof_calib_fork = 1;
            
            sys.para.peaknhold_stat_bit = 0;
            sys.para.load_threshold = 2;
            sys.para.loadcell_cnt_offst = 7000;
            sys.para.manbasket_min = 0;
            sys.para.manbasket_max = 200;
            
            sys.para.manbas_duty = 6;       //Only for ACE NXP150
            
            sys.para.main_ang_chann = 5;
            sys.para.cal_mangle_min = 0;
            sys.para.cal_mangle_min_cnt = 3500;
            sys.para.cal_mangle_max = 600;
            sys.para.cal_mangle_max_cnt = 1300;
            sys.para.zload_mask = 3;
            sys.para.load_announce_timer = 5;
            sys.para.voice_of_language = 0;
            
            sys.para.art_enable_bit = 0;
            memset(sys.para.indopower_art_derate,0,12);    
            
            sys.para.sel_len_drum = 0;            
            sys.para.slew_offset = -13;
            sys.para.bm_ht_offset = 0;      //TMC crane
            break;
        }
    }
    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

    Lcd16x2_Cmd(LCD_CLEAR);
    Lcd16x2_Out(1,1,"   DATA SAVED   ");
    Delay_1ms(1500);
}

//==================================EOF=======================================
