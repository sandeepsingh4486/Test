#include "main.h"


/*============================================================================*/
/*
 * Function      :        Move_Cursor_Left.
 * Description   :        Used to shift cursor position to left.
 * Parameters    :        pos-Number of position to shift.
 * Return        :        None.
*/
/*============================================================================*/
void Move_Cursor_Left(uint8_t pos)
{
  uint8_t shift=0;
  
  if(pos <= 15)
  {
    for(shift=0; shift<pos; shift++)
    {
      Lcd16x2_Cmd(LCD_MOVE_CURSOR_LEFT);
    }
  }
}

/*============================================================================*/
/*
 * Function      :        Move_Cursor_Right.
 * Description   :        Used to shift cursor position to right.
 * Parameters    :        pos-Number of position to shift.
 * Return        :        None.
*/
/*============================================================================*/
void Move_Cursor_Right(uint8_t pos)
{
  uint8_t shift=0;

  if(pos <= 15)
  {
    for(shift=0; shift<pos; shift++)
    {
      Lcd16x2_Cmd(LCD_MOVE_CURSOR_RIGHT);
    }
  }
}


/*============================================================================*/
/*
 * Function      :  Shift_Cursor_Position_4Digits.
 * Description   :  Used to shift cursor position to left or right. It can work for one decimal point before last digit
 *                  ie. If 4 digit parameter is the case then acceptable values with no decimal are 0000 to 9999 and with decimal point it will be 000.0 to 999.9.
 * Parameters    :  flag_lr-decison left/right, num_of_dig-Total digits and decimal_pos-Decimal position(0-No decimal and 1-Decimal point before last digit).
 * Return        :  None.
*/
/*============================================================================*/
void Shift_Cursor_Position(uint8_t flag_lr, uint8_t num_of_dig,uint8_t decimal_pos)
{
    if(flag_lr == 0)                   //Shift cursor left
    {
        if(pos_t < (num_of_dig-1))
        {
            pos_t++;
            if(decimal_pos == NO_DECIMAL_POINT) 
            {
                Move_Cursor_Left(1);
            }
            else if(decimal_pos == ONE_DECIMAL_POINT)
            {
                if(pos_t == 1)
                {
                    Move_Cursor_Left(2);
                }
                else
                {
                    Move_Cursor_Left(1);
                }
            }
        }
        else
        {
            pos_t = 0;
            if(decimal_pos == NO_DECIMAL_POINT)         Move_Cursor_Right(num_of_dig-1);
            else if(decimal_pos == ONE_DECIMAL_POINT)   Move_Cursor_Right(num_of_dig);
        }
    }
    else
    {
        if(pos_t > 0)
        {
            pos_t--;
            if(decimal_pos == NO_DECIMAL_POINT)
            {
                Move_Cursor_Right(1);
            }
            else if(decimal_pos == ONE_DECIMAL_POINT)
            {
                if(pos_t == 0)
                {
                    Move_Cursor_Right(2);
                }
                else
                {
                    Move_Cursor_Right(1);
                }
            }
        }
        else
        {
            pos_t = num_of_dig-1;
            if(decimal_pos == NO_DECIMAL_POINT)         Move_Cursor_Left(num_of_dig-1);
            else if(decimal_pos == ONE_DECIMAL_POINT)   Move_Cursor_Left(num_of_dig);
        }
    }
}

/*============================================================================*/
/*
 * Function      : Show_Enable_Disable_String.
 * Description   : Used to show currunt and previous status of enable/disable .
 * Parameters    : curr-current value .
 * Return        : None.
*/
/*============================================================================*/
void Show_Enable_Disable_String(uint8_t curr)
{
  if(curr == 1)
    Lcd16x2_Out(2,1,"CV:Enb    PV:Enb");
  else
    Lcd16x2_Out(2,1,"CV:Dis    PV:Dis");
}

/*============================================================================*/
/*
 * Function      : Show_Enable_Disable_Stat.
 * Description   : Used to show currunt status.
 * Parameters    : curr-current value.
 * Return        : None.
*/
/*============================================================================*/
void Show_Enable_Disable_Stat(uint8_t curr)
{
  if(curr == 0)
  Lcd16x2_Out(2,4,"Dis");
  else
  Lcd16x2_Out(2,4,"Enb");
}

/*============================================================================*/
/*
 * Function      : Show_Yes_No_Stat.
 * Description   : Used to show currunt status.
 * Parameters    : curr-current value.
 * Return        : None.
*/
/*============================================================================*/
void Show_Yes_No_Stat(uint8_t curr)
{
  if(curr == 0)
  Lcd16x2_Out(2,4,"Dis");
  else
  Lcd16x2_Out(2,4,"Enb");
}


/*============================================================================*/
/*
 * Function      : Show_Case_Stat.
 * Description   : Used to show currunt case status.
 * Parameters    : curr-case no .
 * Return        : None.
*/
/*============================================================================*/
void Show_Case_Stat(uint8_t curr)
{
  if(curr == 0)
  Lcd16x2_Out(2,3,"CASE1  ");
  else
  Lcd16x2_Out(2,3,"CASE2  ");
}

/*============================================================================*/
/*
 * Function      :        Display_Main_Menu.
 * Description   :        Used to display main menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Main_Menu(void)
{
  mv.max = 5;
  mv.min = 1;

  Lcd16x2_Cmd(LCD_CLEAR);

  Main_Menus();
}

/*============================================================================*/
/*
 * Function      :        Main_Menus.
 * Description   :        Used to choose main menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Main_Menus(void)
{
  switch(mv.menu_cnt)
  {
    case 1:
    Lcd16x2_Out(1,1,"OPERATOR VIEW: <");
    Lcd16x2_Out(2,1,"OPERATOR SET:   ");
    break;
    case 2:
    Lcd16x2_Out(1,1,"OPERATOR SET:  <");
    Lcd16x2_Out(2,1,"SUPERVISOR SET: ");
    break;
    case 3:
    Lcd16x2_Out(1,1,"SUPERVISOR SET:<");
    Lcd16x2_Out(2,1,"SITE SET:       ");
    break;
    case 4:
    Lcd16x2_Out(1,1,"SITE SET:      <");
    Lcd16x2_Out(2,1,"FACTORY SET:    ");
    break;
    case 5:
    Lcd16x2_Out(1,1,"FACTORY SET:   <");
    Lcd16x2_Out(2,1,"OPERATOR VIEW:  ");
    break;
  }
}


/*============================================================================*/
/*
 * Function      :        Gui_Task.
 * Description   :        This is the task to handle GUIs.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Gui(void)
{
    int16_t ang=0;
    uint16_t temp_data3,temp_data4,Page_count=0,TotalNoPageRecive=0;
    uint8_t password=0,pw_fail=0,chk_arr,unique_cntr;
    char ubuf[100];
    uint32_t _add=ONE_SECTOR_SIZE;
    static uint8_t temp_SlewMode=0;
    static uint8_t TempCounter=0;
    switch(menu_stat)
    {
        case DEFAULT_PAGE:
        {
            if((key.function == 1)||(key.func_ftp == 1))
            {
                Lcd16x2_Out(1,1,"  SYSTEM SETUP  ");
                Lcd16x2_Out(2,1,"ESC:Quit ENT:Sel");
                menu_stat = SYSTEM_SETUP_PAGE;
                calib_mode = 1;
                key.function = 0;
                Delay_1ms(500);
            }
            else if((key.duty == 1)&&(sys.para.duty_select_stat_bit))
            {
                while(key.duty_ftp == 1)
                {
                    if((sys.para.Select_System != PALFINGER_KNUCKLE_BOOM)&&(sys.para.Select_System != FORK_LIFT)&&
                       (sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
                    {
                        if(prv_duty<=lc_total_duty)
                        {
                            sys.para.rig_duty_bit = 0;
                            prv_duty++;
                            if(prv_duty<=lc_total_duty)
                            {
                                Duty_Hint(prv_duty);
                                sys.para.duty = prv_duty;
//                                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
//                                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
//
//                                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
//                                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                            }
                            else
                            {
                                sys.para.rig_duty_bit = 1;
                                prv_duty = 0;
                                Lcd16x2_Out(1,1,"  SLI Inactive  ");
                                Lcd16x2_Out(2,1,"  Rigging Duty  ");
                                Delay_1ms(1500);
                            }
                        }
                    }
                    else if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                    {
                        sprintf(ubuf,"K.Angle=%02dﬂ     ",(Knbm_angle/10));
                        Lcd16x2_Out(1,1,ubuf);
                        sprintf(ubuf,"FixLength=%04.1fM ",((float)JibLength)/10.0); 
                        Lcd16x2_Out(2,1,ubuf);
                        Delay_1ms(2000);
                    }
                    else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                    {
                        if((can_p1_cnt > sys.para.forkcalib_press_max[0][1]-p1_hyst))
                            Lcd16x2_Out(1,1,"P1:WIR  ");
                        else
                            Lcd16x2_Out(1,1,"P1:OOR  ");
                        if((can_p2_cnt > sys.para.forkcalib_press_max[1][1]-p2_hyst))
                            Lcd16x2_Out(1,9,"  P2:WIR");
                        else
                            Lcd16x2_Out(1,9,"  P2:OOR");
                        if((can_p3_cnt > sys.para.forkcalib_press_max[2][1]-p3_hyst))
                            Lcd16x2_Out(2,1,"P3:WIR  ");
                        else
                            Lcd16x2_Out(2,1,"P3:OOR  ");
                        if((can_p4_cnt > sys.para.forkcalib_press_max[3][1]-p4_hyst))
                            Lcd16x2_Out(2,9,"  P4:WIR");
                        else
                            Lcd16x2_Out(2,9,"  P4:OOR");
                        Delay_1ms(2000);
                    }
                }
                key.duty = 0;                
            }
            else if(key.increment == 1)
            {
                if((sys.para.Select_System==REGULAR_SYSTEM)||(sys.para.Select_System==FORK_LIFT)||(sys.para.Select_System==TMC_MANBASKET)||
                   (sys.para.Select_System==TMC_MANBASKET2)||(sys.para.Select_System==PALFINGER_KNUCKLE_BOOM)||(sys.para.Select_System== ACE_NX360)||
                   (sys.para.Select_System==TIL_PIXEF_TELE_PNC)||(sys.para.Select_System==PNC_FORK))
                {
                    if(art_ip_bit)
                    {
//                        page_addr = (((uint32_t)lc_duty_cycle_page_s-1)*256)+((lc_art_table_page_s-1)*2)+flash_memory_offset;        
//                        art_dty_tbl = SPIFlash_Read_Byte(page_addr)*256 + SPIFlash_Read_Byte(page_addr+1);
                        sprintf(ubuf,"Tbl No:%04d  %03d",lc_art_dty_tbl+duty_table-1,Radius1);
                    }
                    else
                    {
//                        art_dty_tbl = 0;
                        sprintf(ubuf,"Tbl No:%04d  %03d",duty_table,Radius1);
                    }                    
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"LNL=%03d HNLZ=%03d",LowNlzRad,HighNlzRad);
                    Lcd16x2_Out(2,1,ubuf);
                    Delay_1ms(2000);
                }
                else if(sys.para.Select_System==WHITELINE_ESCORTS)
                {
                    //Display --> Tilt Angle LA--> Lateral and LO --> Longitudinal......

                    //Tilt Angle 1 =>
                    Lcd16x2_Cmd(LCD_CLEAR);
                    sprintf(ubuf,"LA=%dﬂ",TiltAngle_1_X);
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"LO=%dﬂ",TiltAngle_1_Y);
                    Lcd16x2_Out(2,1,ubuf);
                      //Tilt Angle 2 =>
                    sprintf(ubuf,"LA=%dﬂ",TiltAngle_2_X);
                    Lcd16x2_Out(1,9,ubuf);
                    sprintf(ubuf,"LO=%dﬂ",TiltAngle_2_Y);
                    Lcd16x2_Out(2,9,ubuf);
                    Delay_1ms(2000);
                }
                else if (sys.para.Select_System==PALFINGER_KNUCKLE_BOOM)
                {
                    
                }
                else if(sys.para.Select_System==ACE_MANBASKET_HXP )
                {
                    
                }
                else
                {
                  
                }
                key.increment=0;
            }
            else if(key.decrement == 1)
            {
                if(sys.para.Select_System==REGULAR_SYSTEM)
                {
//                    sprintf(ubuf,"LNL=%03d HNLZ=%03d",LowNlzRad,HighNlzRad);
//                    Lcd16x2_Out(1,1,ubuf);
//                    sprintf(ubuf,"RAD=%03d CANG=%03d",Radius1,cap_angle);
//                    Lcd16x2_Out(2,1,ubuf);
//                    Delay_1ms(2000); 
                }
                else if(sys.para.Select_System==WHITELINE_ESCORTS)
                {
                    Lcd16x2_Cmd(LCD_CLEAR);
                    sprintf(ubuf,"LA=%dﬂ",TiltAngle_1_X);
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"LO=%dﬂ",TiltAngle_1_Y);
                    Lcd16x2_Out(2,1,ubuf);

                    sprintf(ubuf,"LA=%dﬂ",TiltAngle_2_X);
                    Lcd16x2_Out(1,9,ubuf);
                    sprintf(ubuf,"LO=%dﬂ",TiltAngle_2_Y);
                    Lcd16x2_Out(2,9,ubuf);
                    Delay_1ms(2000);
                }
                else if(sys.para.Select_System==FORK_LIFT)
                {
                    sprintf(ubuf,"MN:%04.1f  MC:%04d",((float)sys.para.cal_len_min)/10.0,sys.para.cal_len_min_cnt);
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"MX:%04.1f  XC:%04d",((float)sys.para.cal_len_max)/10.0,sys.para.cal_len_max_cnt);
                    Lcd16x2_Out(2,1,ubuf);
                    Delay_1ms(2000);
                }
                else if (sys.para.Select_System== ACE_NX360)
                {
                    
                }
                else if (sys.para.Select_System==PALFINGER_KNUCKLE_BOOM)
                {
                    
                }
                else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                {
                    Lcd16x2_Cmd(LCD_CLEAR);
                    sprintf(ubuf,"   TILTX=%02dﬂ    ",TiltAngle_1_X);
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"   TILTY=%02dﬂ    ",TiltAngle_1_Y);
                    Lcd16x2_Out(2,1,ubuf);
                    Delay_1ms(2000);                    
                }
                else
                {
                  
                } 
                key.decrement=0;
            }
            else if(key.entr_ftp == 1)
            {
                if(sys.para.Select_System == ACE_NX360)
                {
                    Lcd16x2_Cmd(LCD_CLEAR);
                    
                    if(temp_SlewMode <= 1)
                    {
                        change_Mode(temp_SlewMode);
                        TempCounter++;
                        if(TempCounter == 2)
                        {
                            temp_SlewMode++;  TempCounter=0;
                        }
                        SlewMode = temp_SlewMode;
                    }
                    else
                    {
                      temp_SlewMode = 0;
                    }
                }
                else if((sys.para.Select_System == WHITELINE_ESCORTS)||(sys.para.Select_System == TMC_MANBASKET)||
                        (sys.para.Select_System == TMC_MANBASKET2))
                {
                    sprintf(ubuf,"  HEIGHT:%04.1fM  ",((float)(HookHight))/10.0);
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"HEIGHT LMT:%04.1fM",((float)sys.para.Max_BLength)/10.0);
                    Lcd16x2_Out(2,1,ubuf);
                    Delay_1ms(2000);
                }
                else if(sys.para.Select_System == FORK_LIFT)
                {
                    sprintf(ubuf,"MN:%04.1f  MC:%04d",((float)sys.para.cal_len_min)/10.0,sys.para.cal_len_min_cnt);
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"MX:%04.1f  XC:%04d",((float)sys.para.cal_len_max)/10.0,sys.para.cal_len_max_cnt);
                    Lcd16x2_Out(2,1,ubuf);
                    Delay_1ms(2000);
                }
                key.enter = 0;
            }
            else if(key.bypass == 1)
            {
                //Playback_Number(ESCORTS_WELCOME_HINDI_MP3);
                
                //UART4_Array(mp3_buf,10);
                key.bypass = 0;
//                if(disp_error)
//                {
//                    Lcd16x2_Out(1,1," Customer Care: ");
//                    Lcd16x2_Out(2,1,"  084484 48772  ");
//                    Delay_1ms(3000);
//                }
            }
            else
            {
               TempCounter=0; 
            }
            key.duty = 0;
            key.function = 0;
            key.increment = 0;
            key.decrement = 0;
            key.enter = 0;
            key.bypass = 0;
            break;
        }
        case SYSTEM_SETUP_PAGE:
        {
          if((key.function == 1)||(key.func_ftp == 1))
          {
            menu_stat = DEFAULT_PAGE;
            
            Lcd16x2_Cmd(LCD_CLEAR);
            key.function = 0;
            calib_mode = 0;
            Display_Main_Screen();
            Delay_1ms(1000);
            Lcd16x2_Cmd(LCD_CURSOR_OFF);
          }
          else if(key.enter == 1)
          {
            mv.menu_cnt = 1;
            Display_Main_Menu();
            menu_stat = SELECT_MENU_PAGE;
            key.enter = 0;
          }
          break;
        }
        case SELECT_MENU_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    mv.menu_cnt++;
                    if(mv.menu_cnt > mv.max)  mv.menu_cnt = mv.min;
                    Main_Menus();
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    mv.menu_cnt--;
                    if(mv.menu_cnt < mv.min)  mv.menu_cnt = mv.max;
                    Main_Menus();
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((mv.menu_cnt == OPERATOR_VIEW_MENU)||(mv.menu_cnt == OPERATOR_SET_MENU))
                {
                    if(mv.menu_cnt == OPERATOR_VIEW_MENU)
                    {
                        mv.operator_view = 1;
                        Display_Operator_View_Menu();
                        menu_stat = OPERATOR_MENU_PAGE;
                    }
                    else
                    {
                        mv.operator_set = 1;
                        Display_Operator_Set_Menu();
                        menu_stat = OPERATOR_SET_CODE_PAGE;
                    }
                }
                else
                {
                    if(sys.para.pw_stat_bit == 1)
                    {
                        password = 0;
                        pw_fail = 0;
                        pos_t = 0;              
                        common_long = password;
                        Lcd16x2_Out(1,1,"Enter Password: ");
                        Lcd16x2_Out(2,1,"               ");
                        sprintf(ubuf,"%02d",password);
                        Lcd16x2_Out(2,8,ubuf);

                        Move_Cursor_Left(1);
                        Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
                        menu_stat = PASSWORD_PAGE;
                    }
                    else if(mv.menu_cnt == SUPERVISOR_SET_MENU)
                    {
                        mv.supervisor_set = 1;
                        Display_Supervisor_Set_Menu();
                        menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    }
                    else if(mv.menu_cnt == SITE_SET_MENU)
                    {
                        mv.site_set = 1;
                        Display_Site_Set_Menu();
                        menu_stat = SITE_SET_CODE_PAGE;
                    }
                    else if(mv.menu_cnt == FACTORY_SET_MENU)
                    {
                        mv.factory_set = 1;
                        Display_Factory_Set_Menu();
                        menu_stat = FACTORY_SET_CODE_PAGE;
                    }
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Out(1,1,"  SYSTEM SETUP  ");
                Lcd16x2_Out(2,1,"ESC:Quit ENT:Sel");
                menu_stat = SYSTEM_SETUP_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case PASSWORD_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(pos_t == 0) pos_t = 1;
                else           pos_t = 0;
                if(pos_t) Move_Cursor_Left(1);
                else      Move_Cursor_Right(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if((key.increment == 1)||(key.decrement == 1))
            {
                if(key.increment == 1)  Modify_System_Parameter(2,INC_DATA,pos_t,&common_long);
                else                    Modify_System_Parameter(2,DEC_DATA,pos_t,&common_long);
                
                sprintf(ubuf,"%02d",(uint8_t)common_long);
                Lcd16x2_Out(2,8,ubuf);
                Move_Cursor_Left(pos_t+1);
                key.increment = 0;
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
              Lcd16x2_Cmd(LCD_CURSOR_OFF);
              password = (uint8_t)common_long;
              if(mv.menu_cnt == SUPERVISOR_SET_MENU)
              {
                if(password == 11)
                {
                  pw_fail = 0;
                  mv.supervisor_set = 1;
                  Display_Supervisor_Set_Menu();
                  menu_stat = SUPERVISOR_SET_CODE_PAGE;
        //                Lcd16x2_Out(2,1,"Welcome Suprvisr");
                }
                else
                {
                  pw_fail = 1;
                  Lcd16x2_Out(2,1,"Password Failed ");
                }
              }
              else if(mv.menu_cnt == SITE_SET_MENU)
              {
                if(password == 22)
                {
                  pw_fail = 0;
                  mv.site_set = 1;
                  Display_Site_Set_Menu();
                  menu_stat = SITE_SET_CODE_PAGE;
                }
                else
                {
                  pw_fail = 1;
                  Lcd16x2_Out(2,1,"Password Failed ");
                }
              }
              else if(mv.menu_cnt == FACTORY_SET_MENU)
              {
                if(password == 84)
                {
                  pw_fail = 0;
                  mv.factory_set = 1;
                  Display_Factory_Set_Menu();
                  menu_stat = FACTORY_SET_CODE_PAGE;
                }
                else
                {
                  pw_fail = 1;
                  Lcd16x2_Out(2,1,"Password Failed ");
                }
              }
              Delay_1ms(1000);
              if(pw_fail == 1)
              {
                pos_t = 0;
                Lcd16x2_Out(2,1,"               ");
                sprintf(ubuf,"%02d",password);
                Lcd16x2_Out(2,8,ubuf);
                Lcd16x2_Cmd(LCD_MOVE_CURSOR_LEFT);
                Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
              }
              key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
              Display_Main_Menu();
              menu_stat = SELECT_MENU_PAGE;
              key.function = 0;
              Delay_1ms(500);
            }
            break;
        }
        case OPERATOR_MENU_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {                
                while(key.inc_ftp == 1)
                {
                    mv.operator_view++;
                    if(mv.operator_view > mv.max)  mv.operator_view = mv.min;
                    Select_Operator_View_Menu();
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    mv.operator_view--;
                    if(mv.operator_view < mv.min)  mv.operator_view = mv.max;
                    Select_Operator_View_Menu();
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                menu_stat = OPERATOR_VIEW_PAGE;
                Operator_Viewing();
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPERATOR_VIEW_PAGE:
        {
            Show_Live_ADC_Count();

            if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case VIEW_PRESS_CALIB_POINT_PAGE1:
        {
            if(key.increment == 1)        // INC Key
            {
                temp_duty_indx = 2;
                Display_MinMax_Option_Menu();
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                temp_duty_indx = 1;
                Display_MinMax_Option_Menu();
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                common_byte = 0;
                if(temp_duty_indx == 1)
                {
                    Display_Fork_MinMax_Press_View(common_byte,0);
                }
                else
                {
                    Display_Fork_MinMax_Press_View(common_byte,1);
                }
                menu_stat = VIEW_PRESS_CALIB_POINT_PAGE2;
                key.enter = 0;
                Delay_1ms(500);
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case VIEW_PRESS_CALIB_POINT_PAGE2:
        {
            if(key.increment == 1)        // INC Key
            {
                if(common_byte < sys.para.numof_calib_fork-1)   common_byte++;
                else                                            common_byte = 0;
                if(temp_duty_indx == 1)
                {
                    Display_Fork_MinMax_Press_View(common_byte,0);
                }
                else
                {
                    Display_Fork_MinMax_Press_View(common_byte,1);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                if(common_byte > 0) common_byte--;
                else                common_byte = sys.para.numof_calib_fork-1;
                if(temp_duty_indx == 1)
                {
                    Display_Fork_MinMax_Press_View(common_byte,0);
                }
                else
                {
                    Display_Fork_MinMax_Press_View(common_byte,1);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_MinMax_Option_Menu();
                menu_stat = VIEW_PRESS_CALIB_POINT_PAGE1;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case VIEW_PC_PAGE1:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Calib_Hook_Load_Shift_Cursor(0);
                else              Calib_Hook_Load_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                Calib_Hook_Load_Change_Parameter_Value(0);
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                Calib_Hook_Load_Change_Parameter_Value(1);
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
                {
                    sprintf(ubuf,"%02d",temp_duty_indx);
                    Lcd16x2_Out(1,13,ubuf);

                    if(pos_t == 0)
                    {
                      Move_Cursor_Left(1);
                    }
                    else
                    {
                      Move_Cursor_Left(2);
                    }
                  
                    Lcd16x2_Cmd(LCD_CURSOR_OFF);
                    Display_Select_Calib_Length_Menu();
                    menu_stat = VIEW_PC_PAGE2;
                }
                else
                {
//                  sprintf(ubuf," TOTAL DUTY=%02d  ",lc_total_duty);
                  Lcd16x2_Out(1,1,"DTY:NOT IN RANGE");
                  Delay_1ms(1500);
                  temp_duty_indx = 1;
                  byt1 = temp_duty_indx/10;
                  byt2 = temp_duty_indx%10;
                  sprintf(ubuf,"SELECT DUTY:%02d  ",temp_duty_indx);
                  Lcd16x2_Out(1,1,ubuf);
                  if(pos_t == 0)
                  {
                    Move_Cursor_Left(3);
                  }
                  else
                  {
                    Move_Cursor_Left(4);
                  }
                }
                
                key.enter = 0;
                Delay_1ms(500);
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case VIEW_PC_PAGE2:
        {
            if(key.increment == 1)        // INC Key
            {
                Select_Calib_Length_Menu(0);
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                Select_Calib_Length_Menu(1);
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                //UART_Send_String(UART_MODULE1,"Pressure curve Start...!!\r\n");
                //UART_Send_String(UART_MODULE1,"Zero load calibration Pressure curve data:\r\n");
//                sprintf(ubuf,"  Duty=%d Length=%.1fM\r\n",temp_duty_indx,((float)length_array[length_array_ptr])/10.0);
//                UART_Send_String(UART_MODULE1,ubuf);
                //Take the length pointer at which calibration need to be done
                csv_ref_len = length_array_ptr%5;  //for calib lenth number 0 to 5

                pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + ((temp_duty_indx-1)*10*256) + csv_ref_len*512 + flash_memory_offset;
                #ifdef DEBUG_MSG
                sprintf(ubuf,"Page address=%.00f Page offset=%.00f\r\n",(float)pc_page_addr,(float)flash_memory_offset);
                //UART_Send_String(UART_MODULE1,ubuf);
                #endif
                pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector

                pc_sector = pc_sector_quotient;
                pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15
                #ifdef DEBUG_MSG
                sprintf(ubuf,"Duty-%02d PC_S-%03d ref_len-%02d\r\n",temp_duty_indx,lc_press_curve_page_s,csv_ref_len);
                //UART_Send_String(UART_MODULE1,ubuf);
                sprintf(ubuf,"sector-%02d page-%02d\r\n",pc_sector,pc_page);
                //UART_Send_String(UART_MODULE1,ubuf);
                #endif

                SPIFlash_Read_Sector(pc_sector);
                for(ang=0; ang<90; ang++)
                {
                  pc_buf[0][ang] = (flash.sector.page[pc_page][(ang*2)+16]*256)+flash.sector.page[pc_page][(ang*2)+17];
                }

                if(pc_page == 15)
                {
          //          //UART_Send_String(UART_MODULE1,"Sector incremented\r\n");
                  pc_sector++;
                  SPIFlash_Read_Sector(pc_sector);
                  for(ang=0; ang<90; ang++)
                  {
                    pc_buf[1][ang] = (flash.sector.page[0][(ang*2)+16]*256)+flash.sector.page[0][(ang*2)+17];
                  }
    //              sprintf(ubuf,"%02d",pc_sector);
    //              Lcd16x2_Out(2,12,ubuf);
                }
                else
                {
          //          //UART_Send_String(UART_MODULE1,"Sector increment not required\r\n");
                  for(ang=0; ang<90; ang++)
                  {
                    pc_buf[1][ang] = (flash.sector.page[pc_page+1][(ang*2)+16]*256)+flash.sector.page[pc_page+1][(ang*2)+17];
                  }
                }
                for(ang=0; ang<90; ang++)
                {
                    sprintf(ubuf,"Angle = %02d P1 = %04d P2 = %04d\r\n",ang+1,pc_buf[0][ang],pc_buf[1][ang]);
                    //UART_Send_String(UART_MODULE1,ubuf);
                }
                //UART_Send_String(UART_MODULE1,"Pressure curve End...!!\r\n");
                CrtBoomAngle = 1;
                p1_cnt = pc_buf[0][0];
                p2_cnt = pc_buf[1][0];
                Lcd16x2_Cmd(LCD_CLEAR);
                sprintf(ubuf,"P1:%04d   BA:%02dﬂ",p1_cnt,CrtBoomAngle);
                Lcd16x2_Out(1,1,ubuf);
                sprintf(ubuf,"P2:%04d         ",p2_cnt);
                Lcd16x2_Out(2,1,ubuf);

                Delay_1ms(1000);
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                menu_stat = VIEW_PC_PAGE3;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case VIEW_PC_PAGE3:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Display_Pressure_Curve_Counts(0);
                    Delay_1ms(400);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Display_Pressure_Curve_Counts(1);
                    Delay_1ms(400);
                }
                key.decrement = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Calib_Hook_Load_Menu();
                Calib_Hook_Load_Cursor_Position();
                menu_stat = VIEW_PC_PAGE1;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        /*
        case OPER_DUMMY_LOAD_CALIB_PAGE: //Show live values of boom length and angle
        {
            //Show live values of boom length and angle
            if(disp_refresh_cnt == 0)
            {
                disp_refresh_cnt = 500;
                if(bm_length > 99)
                sprintf(ubuf,"%.01fM ",((float)bm_length)/10.0);
                else
                sprintf(ubuf,"0%.01fM ",((float)bm_length)/10.0);
                Lcd16x2_Out(1,4,ubuf);

                TempDispBoomAngle = (bm_angle/10);
                sprintf(ubuf,"%02dﬂ ",TempDispBoomAngle);
                Lcd16x2_Out(2,4,ubuf);
            }
            if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Out(1,1,"P1:       BA:  ﬂ");
                Lcd16x2_Out(2,1,"P2:             ");
                Delay_1ms(1000);
                CrtBoomAngle = 0;
                PrevBoomAngle = 0;
                test_cntr = 0;
                calib_stat_bit = 0;
                menu_stat = OPER_DUMMY_LOAD_CALIB_PAGE2;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPER_DUMMY_LOAD_CALIB_PAGE1:  //Select boom length at which Press curve need to be saved
        {
            if(key.increment == 1)        // INC Key
            {
                Select_Calib_Length_Menu(0);
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                Select_Calib_Length_Menu(1);
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                //Take the length pointer at which calibration need to be done
                csv_ref_len = length_array_ptr%5;  //for calib lenth number 0 to 5
          //        csv_ref_nol = (mv.max-mv.min)+1;    //Total number of lengths
                pc_page_addr = (uint32_t)490*4096 + csv_ref_len*512;
                #ifdef DEBUG_MSG
                sprintf(ubuf,"Page address=%.00f\r\n",(float)pc_page_addr);
                //UART_Send_String(UART_MODULE1,ubuf);
                #endif
                pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector

                pc_sector = pc_sector_quotient;
                pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15

                #ifdef DEBUG_MSG
                sprintf(ubuf,"p_curv_s=%d csv_ref_len=%d duty_index=%d \r\n",lc_press_curve_page_s,csv_ref_len,temp_duty_indx);
                //UART_Send_String(UART_MODULE1,ubuf);
                sprintf(ubuf,"pc_sector=%d pc_page=%d\r\n",pc_sector,pc_page);
                //UART_Send_String(UART_MODULE1,ubuf);
                #endif
                sprintf(ubuf,"Duty-04         ");
                Lcd16x2_Out(1,1,ubuf);
                sprintf(ubuf,"Sec-%04d Page-%02d",pc_sector,pc_page);
                Lcd16x2_Out(2,1,ubuf);
                Delay_1ms(1500);
                Display_Calib_Length_Angle();
                menu_stat = OPER_DUMMY_LOAD_CALIB_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPER_DUMMY_LOAD_CALIB_PAGE2:           //Aquire data of P1 & P2
        {
            if(bm_angle >= 14)
            {
                CrtBoomAngle = (bm_angle/10);

                if(CrtBoomAngle >= PrevBoomAngle)        // Will definitely execute once ....
                {
                    if((CrtBoomAngle - PrevBoomAngle) >= (1))
                    {
                        PrevBoomAngle = (CrtBoomAngle);
                        data_log_arr[CrtBoomAngle] = 1;
                        pc_buf[0][CrtBoomAngle] = p1_pressure_cnt;
                        pc_buf[1][CrtBoomAngle] = p2_pressure_cnt;
                        #ifdef DEBUG_MSG
                        sprintf(gbuf,"1)pc_buf[0][%d]=%d pc_buf[1][%d]=%d\r\n",CrtBoomAngle,p1_pressure_cnt,CrtBoomAngle,p2_pressure_cnt);
                        //UART_Send_String(UART_MODULE1,gbuf);
                        #endif
                        test_cntr++;
                        if(bm_angle >= (600))
                        {
                          calib_stat_bit = 1;

                          //Save pressure curve to SPI flash
                          SPIFlash_Read_Sector(pc_sector);
                          Sector_Erase(pc_sector);
                          for(ang=0; ang<90; ang++)
                          {
                            flash.sector.page[pc_page][(ang*2)+16] = pc_buf[0][ang+1]/256;
                            flash.sector.page[pc_page][(ang*2)+17] = pc_buf[0][ang+1]%256;
                          }

                          if(pc_page == 15) //if page number for P1 curve is last page number then change sector number and write data to first page
                          {
                            SPIFlash_Write_Sector(pc_sector);
                            pc_sector++;
                            SPIFlash_Read_Sector(pc_sector);
                            Sector_Erase(pc_sector);
                            for(ang=0; ang<90; ang++)
                            {
                              flash.sector.page[0][(ang*2)+16] = pc_buf[1][ang+1]/256; //flash.sector.page[0] is because new sectors first page is always 0
                              flash.sector.page[0][(ang*2)+17] = pc_buf[1][ang+1]%256;
                            }
                          }
                          else       //Write both pages of P1 and P2 in same sector
                          {
                            for(ang=0; ang<90; ang++)
                            {
                              flash.sector.page[pc_page+1][(ang*2)+16] = pc_buf[1][ang+1]/256;
                              flash.sector.page[pc_page+1][(ang*2)+17] = pc_buf[1][ang+1]%256;
                            }
                          }
                          SPIFlash_Write_Sector(pc_sector);

                          Lcd16x2_Cmd(LCD_CLEAR);
                          Lcd16x2_Out(1,1,"   DATA SAVED   ");
                          Delay_1ms(1500);
                          Display_Operator_View_Menu();
                          menu_stat = OPERATOR_MENU_PAGE;
                        }
                    }
                }
            }
            if((calib_stat_bit == 0)&&(disp_refresh_cnt == 0))
            {
                disp_refresh_cnt = 500;
                sprintf(ubuf,"%04d",p1_pressure_cnt);
                Lcd16x2_Out(1,4,ubuf);                // P1
                sprintf(ubuf,"%04d",p2_pressure_cnt);
                Lcd16x2_Out(2,4,ubuf);                // P2
                TempDispBoomAngle = (bm_angle/10);
                sprintf(ubuf,"%02dﬂ",TempDispBoomAngle);
                Lcd16x2_Out(1,14,ubuf);
                sprintf(ubuf,"%03d ",test_cntr);
                Lcd16x2_Out(2,13,ubuf);
            }
            if((key.function == 1)||(key.func_ftp == 1))
            {
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }                                // BL
            break;
        }
        case VIEW_LIFTED_PC_PAGE1:
        {
            if(key.increment == 1)        // INC Key
            {
                Select_Calib_Length_Menu(0);
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                Select_Calib_Length_Menu(1);
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                //Take the length pointer at which calibration need to be done
                csv_ref_len = length_array_ptr%5;  //for calib lenth number 0 to 5
                
                pc_page_addr = (uint32_t)490*4096 + csv_ref_len*512;

                pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector

                pc_sector = pc_sector_quotient;
                pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15

                SPIFlash_Read_Sector(pc_sector);
                for(ang=0; ang<90; ang++)
                {
                  pc_buf[0][ang] = (flash.sector.page[pc_page][(ang*2)+16]*256)+flash.sector.page[pc_page][(ang*2)+17];
                }
                if(pc_page == 15)
                {
          //          //UART_Send_String(UART_MODULE1,"Sector incremented\r\n");
                  pc_sector++;
                  SPIFlash_Read_Sector(pc_sector);
                  for(ang=0; ang<90; ang++)
                  {
                    pc_buf[1][ang] = (flash.sector.page[0][(ang*2)+16]*256)+flash.sector.page[0][(ang*2)+17];
                  }
                  sprintf(ubuf,"%02d",pc_sector);
                  Lcd16x2_Out(2,12,ubuf);
                }
                else
                {
          //          //UART_Send_String(UART_MODULE1,"Sector increment not required\r\n");
                  for(ang=0; ang<90; ang++)
                  {
                    pc_buf[1][ang] = (flash.sector.page[pc_page+1][(ang*2)+16]*256)+flash.sector.page[pc_page+1][(ang*2)+17];
                  }
                }
                CrtBoomAngle = 1;
                p1_cnt = pc_buf[0][0];
                p2_cnt = pc_buf[1][0];
                sprintf(ubuf,"P1:%04d   BA:%02dﬂ",p1_cnt,CrtBoomAngle);
                Lcd16x2_Out(1,1,ubuf);
                sprintf(ubuf,"P2:%04d           ",p2_cnt);
                Lcd16x2_Out(2,1,ubuf);
                Delay_1ms(1000);
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                menu_stat = VIEW_LIFTED_PC_PAGE2;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Operator_View_Menu();
                menu_stat = OPERATOR_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case VIEW_LIFTED_PC_PAGE2:
        {
          if(key.increment == 1)        // INC Key
          {
      //        all_keys_released = 1;
            Display_Pressure_Curve_Counts(0);
            key.increment = 0;
      //        vTaskDelay(pdMS_TO_TICKS(500));
          }
          else if(key.decrement == 1)        // DEC Key
          {
      //        all_keys_released = 1;
            Display_Pressure_Curve_Counts(1);
            key.decrement = 0;
      //        vTaskDelay(pdMS_TO_TICKS(500));
          }
          else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
          {
            Display_Dummy_Calib_Length_Menu();
            menu_stat = VIEW_LIFTED_PC_PAGE1;
            key.function = 0;
            Delay_1ms(500);
          }
          break;
        }*/
        case OPERATOR_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    mv.operator_set++;
                    if(mv.operator_set > mv.max)  mv.operator_set = mv.min;
                    Select_Operator_Set_Menu();
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    mv.operator_set--;
                    if(mv.operator_set < mv.min)  mv.operator_set = mv.max;
                    Select_Operator_Set_Menu();
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                Operator_Setting();
                menu_stat = OPERATOR_SET_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPERATOR_SET_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(mv.operator_set == SET_FALLS)
                {
                    if(pos_t == 0) pos_t = 1;
                    else           pos_t = 0;

                    if(pos_t) Move_Cursor_Left(1);
                    else      Move_Cursor_Right(1);
                }
                key.bypass = 0;
                key.duty = 0;
            }          
            else if((key.increment == 1)||(key.decrement == 1))
            {
                if(key.increment == 1)
                {
                    while(key.inc_ftp == 1)
                    {
                        Operator_Change_Parameter_Value(0);
                        Delay_1ms(600);
                    }
                }
                else
                {
                    while(key.dec_ftp == 1)
                    {
                        Operator_Change_Parameter_Value(1);
                        Delay_1ms(600);
                    }
                }
                key.increment = 0;
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Operator_Save_Settings();
                Display_Operator_Set_Menu();
                menu_stat = OPERATOR_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Operator_Set_Menu();
                menu_stat = OPERATOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SUPERVISOR_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                key.increment = 0;
                while(key.inc_ftp == 1)
                {
                    mv.supervisor_set++;
                    if(mv.supervisor_set > mv.max)  mv.supervisor_set = mv.min;
                    Supervisor_Setcode_Menu();
                    Delay_1ms(600);
                }
            }
            else if(key.decrement == 1)        // DEC Key
            {
                key.decrement = 0;
                while(key.dec_ftp == 1)
                {
                    mv.supervisor_set--;
                    if(mv.supervisor_set < mv.min)  mv.supervisor_set = mv.max;
                    Supervisor_Setcode_Menu();
                    Delay_1ms(600);
                }
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                menu_stat = SUPERVISOR_SET_PAGE;
                Supervisor_Setting();
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SUPERVISOR_SET_PAGE:
        {
            Supervisor_Show_Live_Adc();
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1)   Supervisor_Shift_Cursor(0);
                else                Supervisor_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Supervisor_Save_Settings();
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case LEN_MPOINT_CALIBRATION_PAGE1:      //View
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    if(prv8_val1 < sys.para.numof_len_cal)  prv8_val1++;
                    else                                    prv8_val1 = 1;
                    prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
                    prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
                    sprintf(ubuf,"%02d",prv8_val1);
                    Lcd16x2_Out(1,14,ubuf);
                    if(prv16_val1 <= sys.para.bm_length_max)
                    {
                        sprintf(ubuf,"LV:%04.1f mm:%05lu",((float)prv16_val1)/10.0,(uint32_t)prv16_val2);
                        Lcd16x2_Out(2,1,ubuf);
                    }
                    else
                    {
                        prv16_val1 = 0;
                        prv16_val2 = 0;
                        sys.para.multipt_lcalib[prv8_val1-1][0] = 0;
                        sys.para.multipt_lcalib[prv8_val1-1][1] = 0;
                        Lcd16x2_Out(2,1,"ADD NEW CALIB.  ");
                    }
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    if(prv8_val1 > 1)   prv8_val1--;
                    else                prv8_val1 = sys.para.numof_len_cal;
                    prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
                    prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
                    sprintf(ubuf,"%02d",prv8_val1);
                    Lcd16x2_Out(1,14,ubuf);
                    if(prv16_val1 <= sys.para.bm_length_max)
                    {
                        sprintf(ubuf,"LV:%04.1f mm:%05lu",((float)prv16_val1)/10.0,(uint32_t)prv16_val2);
                        Lcd16x2_Out(2,1,ubuf);
                    }
                    else
                    {
                        prv16_val1 = 0;
                        prv16_val2 = 0;
                        sys.para.multipt_lcalib[prv8_val1-1][0] = 0;
                        sys.para.multipt_lcalib[prv8_val1-1][1] = 0;
                        Lcd16x2_Out(2,1,"ADD NEW CALIB.  ");
                    }
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                //Watch out previous calibration, should not be zero
                if((prv8_val1 >= 2)&&(sys.para.multipt_lcalib[prv8_val1-2][0] > 0)&&(sys.para.multipt_lcalib[prv8_val1-2][0] <= sys.para.bm_length_max))
                {
                    Lcd16x2_Out(1,1,"EDIT POINT :    ");
                    sprintf(ubuf,"%02d",prv8_val1);
                    Lcd16x2_Out(1,14,ubuf);
                    sprintf(ubuf,"LV:%04.1f mm:%05lu",((float)prv16_val1)/10.0,(uint32_t)prv16_val2);
                    Lcd16x2_Out(2,1,ubuf);
                    pos_t = 0;
                    common_byte = 3;
                    common_long = prv16_val1;
                    Move_Cursor_Left(10);
                    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
                    menu_stat = LEN_MPOINT_CALIBRATION_PAGE2;
                }
                else if(prv8_val1 == 1)     //Minimum boom length
                {
                    Lcd16x2_Out(1,1,"EDIT POINT :    ");
                    sprintf(ubuf,"%02d",prv8_val1);
                    Lcd16x2_Out(1,14,ubuf);
                    sprintf(ubuf,"LV:%04.1f mm:%05lu",((float)prv16_val1)/10.0,(uint32_t)prv16_val2);
                    Lcd16x2_Out(2,1,ubuf);
                    pos_t = 0;
                    common_byte = 3;
                    common_long = prv16_val1;
                    Move_Cursor_Left(10);
                    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
                    menu_stat = LEN_MPOINT_CALIBRATION_PAGE2;
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case LEN_MPOINT_CALIBRATION_PAGE2:      //Save
        {
            Supervisor_Show_Live_Adc();
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.bypass == 1)
                    Shift_Cursor_Position(1,3,ONE_DECIMAL_POINT);
                else
                    Shift_Cursor_Position(0,3,ONE_DECIMAL_POINT);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
                    sprintf(ubuf,"%04.1f",((float)common_long)/10.0);
                    Lcd16x2_Out(2,4,ubuf);
                    if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
                    else            Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);                    
                    sprintf(ubuf,"%04.1f",((float)common_long)/10.0);
                    Lcd16x2_Out(2,4,ubuf);
                    if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
                    else            Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if(common_long <= sys.para.bm_length_max)
                {
                    sys.para.multipt_lcalib[prv8_val1-1][0] = (uint16_t)common_long;
                    sys.para.multipt_lcalib[prv8_val1-1][1] = mm_len;
                    
                    if(prv8_val1 == 1)  //minimum boom length
                    {
                        sys.para.bm_length_min = (uint16_t)common_long;
                        sys.para.cal_len_min = sys.para.bm_length_min;
                    }
                    
                    Do_Len_MPoint_Sorting(prv8_val1);
                    
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
                    
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    Lcd16x2_Cmd(LCD_CLEAR);
                    Lcd16x2_Out(1,1,"   DATA SAVED   ");
                    Delay_1ms(1500);
                    
                    Lcd16x2_Out(1,1,"CALIB POINT:    ");
                    sprintf(ubuf,"%02d",prv8_val1);
                    Lcd16x2_Out(1,14,ubuf);
                    prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
                    prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
                    
                    if(prv16_val1 > 0)
                    {
                        sprintf(gbuf,"LV:%04.1f mm:%05lu",((float)prv16_val1)/10.0,(uint32_t)prv16_val2);
                        Lcd16x2_Out(2,1,gbuf);
                    }
                    else
                    {
                        prv16_val1 = 0;
                        prv16_val2 = 0;
                        Lcd16x2_Out(2,1,"ADD NEW CALIB.  ");
                    }
                    menu_stat = LEN_MPOINT_CALIBRATION_PAGE1;
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Lcd16x2_Out(1,1,"CALIB POINT:    ");
                sprintf(ubuf,"%02d",prv8_val1);
                Lcd16x2_Out(1,14,ubuf);
                prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
                prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
                
                if(prv16_val1 > 0)
                {
                    sprintf(gbuf,"LV:%04.1f mm:%05lu",((float)prv16_val1)/10.0,(uint32_t)prv16_val2);
                    Lcd16x2_Out(2,1,gbuf);
                }
                else
                {
                    prv16_val1 = 0;
                    prv16_val2 = 0;
                    Lcd16x2_Out(2,1,"ADD NEW CALIB.  ");
                }
                menu_stat = LEN_MPOINT_CALIBRATION_PAGE1;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case FORK_PRESS_MINMAX_PAGE1:      //Display only minimum/maximum pressure values
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {                    
//                    if(sys.para.Select_System == TMC_MANBASKET)
//                    {
//                        if(common_short < 4)  common_short++;
//                        else                  common_short = 1;
//                        Display_TMC_MinMax_Press_Menu(common_short-1,byt1);
//                    }
//                    else
//                    {
                        if(common_short < sys.para.numof_calib_fork)  common_short++;
                        else                                          common_short = 1;
                        Display_Fork_MinMax_Press_Menu(common_short-1,byt1);
//                    }
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
//                    if(sys.para.Select_System == TMC_MANBASKET)
//                    {
//                        if(common_short > 1) common_short--;
//                        else                 common_short = 4;
//                        Display_TMC_MinMax_Press_Menu(common_short-1,byt1);
//                    }
//                    else
//                    {
                        if(common_short > 1) common_short--;
                        else                 common_short = sys.para.numof_calib_fork;
                        Display_Fork_MinMax_Press_Menu(common_short-1,byt1);
//                    }
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                complimnt_flag = 0;
                menu_stat = FORK_PRESS_MINMAX_PAGE2;
                Display_Fork_MinMax_Press_Menu_Cursor();
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case FORK_PRESS_MINMAX_PAGE2:      //Edit minimum/Maximum pressure values
        {
            Fork_Height();
            Supervisor_Show_Live_Adc();
            
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Supervisor_Shift_Cursor(0);
                else              Supervisor_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Supervisor_Save_Settings();
//                if(sys.para.Select_System == TMC_MANBASKET)
//                {
//                    Display_TMC_MinMax_Press_Menu(common_short-1,byt1);
//                }
//                else
//                {
                    Display_Fork_MinMax_Press_Menu(common_short-1,byt1);
//                }
                menu_stat = FORK_PRESS_MINMAX_PAGE1;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                
//                if(sys.para.Select_System == TMC_MANBASKET)
//                {
//                    Display_TMC_MinMax_Press_Menu(common_short-1,byt1);
//                }
//                else
//                {
                    Display_Fork_MinMax_Press_Menu(common_short-1,byt1);
//                }
                menu_stat = FORK_PRESS_MINMAX_PAGE1;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case TMC_PRESS_MINMAX_PAGE:
        {
            Supervisor_Show_Live_Adc();
            if(key.enter == 1)        // ENTR Key
            {
                if(byt1 == 0)
                {
                    
                }
                else if(byt1 == 1)
                {
                    
                }
                Supervisor_Save_Settings();
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_ART_DRATE_PERCENTAGE1:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Supervisor_Shift_Cursor(0);
                else              Supervisor_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                temp_duty_indx = (uint8_t)common_long;
                
                if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
                {
                    len_calib_cnt = sys.para.indopower_art_derate[temp_duty_indx-1];
                    if(len_calib_cnt > 100)
                    {
                      len_calib_cnt = 0;
                      sys.para.indopower_art_derate[temp_duty_indx-1] = len_calib_cnt;
                    }
                    sprintf(ubuf,"%03d",len_calib_cnt);
                    Lcd16x2_Out(2,11,ubuf);
                    sprintf(ubuf,"%02d",temp_duty_indx);
                    Lcd16x2_Out(1,11,ubuf);
                    
                    if(pos_t == 0)
                    {
                      Move_Cursor_Left(1);
                    }
                    else
                    {
                      Move_Cursor_Left(2);
                    }
                    menu_stat = SET_ART_DRATE_PERCENTAGE2;
                    ArtDerate_Cursor_Position();
                }
                else
                {
                    Lcd16x2_Out(1,1,"DTY:NOT IN RANGE");
                    Delay_1ms(1500);
                    
                    temp_duty_indx = 1;
                    len_calib_cnt = sys.para.indopower_art_derate[temp_duty_indx-1];
                    sprintf(ubuf,"%03d",len_calib_cnt);
                    Lcd16x2_Out(2,11,ubuf);
                    pos_t = 0;
                    common_byte = 2;
                    common_long = temp_duty_indx;
                    sprintf(ubuf,"DUTY NO. :%02d    ",temp_duty_indx);
                    Lcd16x2_Out(1,1,ubuf);
                    Move_Cursor_Left(5);
                }                
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_ART_DRATE_PERCENTAGE2:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Supervisor_Shift_Cursor(0);
                else              Supervisor_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Supervisor_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                len_calib_cnt = (uint16_t)common_long;
                
                if(len_calib_cnt <= 100)
                {
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    sys.para.indopower_art_derate[temp_duty_indx-1] = len_calib_cnt;
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
                    
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    Lcd16x2_Cmd(LCD_CLEAR);
                    Lcd16x2_Out(1,1,"   DATA SAVED   ");
                    Delay_1ms(1500);
                    
                    Display_ArtDerate_Menu();
                    
                    menu_stat = SET_ART_DRATE_PERCENTAGE1;
                    ArtDerate_Cursor_Position();
                }
                else
                {
//                    sprintf(ubuf,"  NOT IN RANGE  ",lc_total_duty);
                    Lcd16x2_Out(2,1,"  NOT IN RANGE  ");
                    Delay_1ms(1500);
                    
                    Lcd16x2_Out(2,1,"ART.DRATE:      ");
                    Lcd16x2_Chr(2,14, '%');
                    
                    ArtDerate_Cursor_Position();
                }                
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);                   
                menu_stat = SET_ART_DRATE_PERCENTAGE1;
                ArtDerate_Cursor_Position();
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case DUTY_TYPE_INDEX_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Duty_Type_Shift_Cursor(0);
                else              Duty_Type_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Duty_Type_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Duty_Type_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
                {
                    len_calib_cnt = sys.para.duty_type[temp_duty_indx-1];
                    if((len_calib_cnt == 0)||(len_calib_cnt>5))
                    {
                      len_calib_cnt = 1;
                      sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt;
                    }
                    sprintf(ubuf,"%03d",len_calib_cnt);
                    Lcd16x2_Out(2,11,ubuf);
                    sprintf(ubuf,"%02d",temp_duty_indx);
                    Lcd16x2_Out(1,11,ubuf);

                    if(pos_t == 0)
                    {
                      Move_Cursor_Left(1);
                    }
                    else
                    {
                      Move_Cursor_Left(2);
                    }
                    menu_stat = SET_DT_CALIB_LEN_PAGE;
                    Duty_Type_Cursor_Position();
                }
                else
                {
                  Lcd16x2_Out(1,1,"DTY:NOT IN RANGE");
                  Delay_1ms(1500);
                  temp_duty_indx = 1;
                  byt1 = temp_duty_indx/10;
                  byt2 = temp_duty_indx%10;
                  sprintf(ubuf,"DUTY NO. :%02d    ",temp_duty_indx);
                  Lcd16x2_Out(1,1,ubuf);
                  if(pos_t == 0)
                  {
                    Move_Cursor_Left(5);
                  }
                  else
                  {
                    Move_Cursor_Left(6);
                  }
                }
                
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_DT_CALIB_LEN_PAGE://Set number of length calibration points
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Duty_Type_Shift_Cursor(0);
                else              Duty_Type_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Duty_Type_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Duty_Type_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if(len_calib_cnt >= 1)
                {
                    sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt; //Store number of length calibration points
                    len_calib_pt = 1;
                    Display_Length_Calib_Menu();
                    Length_Calib_Cursor_Position();
                    menu_stat = LEN_CALIB_POINTS_PAGE;
                }
                else
                {
                    sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt;
                    if(temp_duty_indx <= (lc_total_duty-1))
                    {
                        temp_duty_indx++;
                        menu_stat = DUTY_TYPE_INDEX_PAGE;
                        Display_Duty_Type_Menu();
                        Duty_Type_Cursor_Position();
                    }
                    else
                    {
                        Lcd16x2_Cmd(LCD_CLEAR);
                        Lcd16x2_Out(1,1,"   DATA SAVED   ");
                        Delay_1ms(1500);
                        Lcd16x2_Cmd(LCD_CURSOR_OFF);
                        Display_Supervisor_Set_Menu();
                        menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    }
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case LEN_CALIB_POINTS_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Length_Calib_Shift_Cursor(0);
                else              Length_Calib_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Length_Calib_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Length_Calib_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if(len_calib_pt < len_calib_cnt)
                {
                    length_array_val = byt1*100 + byt2*10 + byt3;
                    sys.para.length_array[length_array_ptr] = length_array_val;

                    Lcd16x2_Cmd(LCD_CLEAR);
                    Lcd16x2_Out(1,1,"   DATA SAVED   ");
                    Delay_1ms(1500);

                    len_calib_pt++;
                    Display_Length_Calib_Menu();
                    Length_Calib_Cursor_Position();
                }
                else //save last one
                {
                    length_array_val = byt1*100 + byt2*10 + byt3;
                    sys.para.length_array[length_array_ptr]= length_array_val;
                    
                    Supervisor_Save_Settings();
                    menu_stat = DUTY_TYPE_INDEX_PAGE;
                    Display_Duty_Type_Menu();
                    Duty_Type_Cursor_Position();
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                menu_stat = SET_DT_CALIB_LEN_PAGE;
                Display_Duty_Type_Menu();
                Duty_Type_Cursor_Position();
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE1:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Calib_Hook_Load_Shift_Cursor(0);
                else              Calib_Hook_Load_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Calib_Hook_Load_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Calib_Hook_Load_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
                {
                    sprintf(ubuf,"%02d",temp_duty_indx);
                    Lcd16x2_Out(1,13,ubuf);

                    if(pos_t == 0)
                    {
                      Move_Cursor_Left(1);
                    }
                    else
                    {
                      Move_Cursor_Left(2);
                    }
                    Lcd16x2_Cmd(LCD_CURSOR_OFF);
                    Display_Select_Calib_Length_Menu();
                    menu_stat = HOOK_LOAD_CALIB_PAGE3;
                }
                else
                {
                  Lcd16x2_Out(1,1,"DTY:NOT IN RANGE");
                  Delay_1ms(1500);
                  temp_duty_indx = 1;
                  byt1 = temp_duty_indx/10;
                  byt2 = temp_duty_indx%10;
                  sprintf(ubuf,"SELECT DUTY:%02d  ",temp_duty_indx);
                  Lcd16x2_Out(1,1,ubuf);
                  if(pos_t == 0)
                  {
                    Move_Cursor_Left(3);
                  }
                  else
                  {
                    Move_Cursor_Left(4);
                  }
                }                
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE2: //Show live values of boom length and angle
        {
            //Show live values of boom length and angle
            if(disp_refresh_cnt == 0)
            {
                disp_refresh_cnt = 500;
                
                if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                {
                    sprintf(ubuf,"%04.1fM",((float)TotalBmLength)/10.0);
                    Lcd16x2_Out(1,5,ubuf);

                    TempDispBoomAngle = (bm_angle/10);
                    sprintf(ubuf,"%02.0fﬂ ",((float)bm_angle)/10.0);
                    Lcd16x2_Out(2,5,ubuf);
                    sprintf(ubuf,"%02.0fﬂ ",((float)Knbm_angle)/10.0);
                    Lcd16x2_Out(2,13,ubuf);
                }
                else
                {
                    sprintf(ubuf,"%04.1fM",((float)TotalBmLength)/10.0);
                    Lcd16x2_Out(1,4,ubuf);

                    TempDispBoomAngle = (bm_angle/10);
                    sprintf(ubuf,"%04.1fﬂ ",((float)bm_angle)/10.0);
                    Lcd16x2_Out(2,4,ubuf);
                }
            }
            if(key.enter == 1)        // ENTR Key
            {
            //        Display_Select_Calib_Length_Menu();
            //        menu_stat = HOOK_LOAD_CALIB_PAGE3;
                  Display_Min_Calib_Angle_Menu();
                  menu_stat = HOOK_LOAD_CALIB_PAGE4;
                  key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                menu_stat = HOOK_LOAD_CALIB_PAGE1;
                Display_Calib_Hook_Load_Menu();
                Calib_Hook_Load_Cursor_Position();
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE3:  //Select boom length at which calibration need to be done
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Select_Calib_Length_Menu(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Select_Calib_Length_Menu(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                Lcd16x2_Out(1,1,"   DATA SAVED   ");
                Delay_1ms(1500);
                
                //Take the length pointer at which calibration need to be done
                csv_ref_len = length_array_ptr%5;  //for calib lenth number 0 to 5
                
                pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + (((uint32_t)temp_duty_indx-1)*10*256) + csv_ref_len*512 + flash_memory_offset;
                
                pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector
                
                pc_sector = pc_sector_quotient;
                pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15
                
                Display_Calib_Length_Angle();
                menu_stat = HOOK_LOAD_CALIB_PAGE2;
                
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                menu_stat = HOOK_LOAD_CALIB_PAGE1;
                Display_Calib_Hook_Load_Menu();
                Calib_Hook_Load_Cursor_Position();
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE4:  //Select min boom angle at which calibration need to be done
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Calib_Angle_Shift_Cursor(0);
                else              Calib_Angle_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                Lcd16x2_Out(1,1,"   DATA SAVED   ");
                Delay_1ms(1500);
                sys.para.min_angle = angle_calib_pt;

                Display_Max_Calib_Angle_Menu();
                menu_stat = HOOK_LOAD_CALIB_PAGE5;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                menu_stat = HOOK_LOAD_CALIB_PAGE1;
                Display_Calib_Hook_Load_Menu();
                Calib_Hook_Load_Cursor_Position();
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE5:  //Select max boom angle at which calibration need to be done
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Calib_Angle_Shift_Cursor(0);
                else                    Calib_Angle_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                Lcd16x2_Out(1,1,"   DATA SAVED   ");
                Delay_1ms(1500);
                sys.para.max_angle = angle_calib_pt;

                if(bm_angle <= sys.para.min_angle*10)
                {
                  Lcd16x2_Out(1,1,"Press ENT Key to");
                  Lcd16x2_Out(2,1,"Start BmUp HkCal");
                  Delay_1ms(1000);
                  menu_stat = HOOK_LOAD_CALIB_PAGE7;
                  calib_stat_bit = 0;
                }
                else
                {
                  Lcd16x2_Out(1,1,"To StrtCal Bring");
                  Lcd16x2_Out(2,1,"the Boom Down   ");
                  Delay_1ms(1000);
                  menu_stat = HOOK_LOAD_CALIB_PAGE6;
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                menu_stat = HOOK_LOAD_CALIB_PAGE1;
                Display_Calib_Hook_Load_Menu();
                Calib_Hook_Load_Cursor_Position();
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE6:           //Wait to bring boom down
        {
            if(bm_angle <= sys.para.min_angle*10)
            {
                Lcd16x2_Out(1,1,"Press ENT Key to");
                Lcd16x2_Out(2,1,"Start BmUp HkCal");
                Delay_1ms(1000);
                menu_stat = HOOK_LOAD_CALIB_PAGE7;
                calib_stat_bit = 0;
            }
            if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                menu_stat = HOOK_LOAD_CALIB_PAGE1;
                Display_Calib_Hook_Load_Menu();
                Calib_Hook_Load_Cursor_Position();
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE7:           //Wait to start calibration
        {
            if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Out(1,1,"P1:     BA:    ﬂ");
                Lcd16x2_Out(2,1,"P2:             ");
                Delay_1ms(1000);
                CrtBoomAngle = 0;
                PrevBoomAngle = 0;
                test_cntr = 0;
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                menu_stat = HOOK_LOAD_CALIB_PAGE8;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE8:           //Calibration started
        {
          if(bm_angle >= ((sys.para.min_angle*10) + 4))
          {
            CrtBoomAngle = (bm_angle/10);

            if(CrtBoomAngle >= PrevBoomAngle)        // Will definitely execute once ....
            {
              if((CrtBoomAngle-PrevBoomAngle) >= (1))
              {
                data_log_arr[CrtBoomAngle] = 1;
                pc_buf[0][CrtBoomAngle] = p1_pressure_cnt;
                pc_buf[1][CrtBoomAngle] = p2_pressure_cnt;
                
//                sprintf(gbuf,"1)pc_buf[0][%d]=%d pc_buf[1][%d]=%d\r\n",CrtBoomAngle,p1_pressure_cnt,CrtBoomAngle,p2_pressure_cnt);
//                UART_Send_String(UART_MODULE1,gbuf);
                               
                test_cntr++;
                for(chk_arr=PrevBoomAngle+1; chk_arr<CrtBoomAngle; chk_arr++)
                {
                  data_log_arr[chk_arr] = 1;
                  pc_buf[0][chk_arr] = p1_pressure_cnt;
                  pc_buf[1][chk_arr] = p2_pressure_cnt;
                  test_cntr++;
                }

                PrevBoomAngle = (CrtBoomAngle);

                if(bm_angle >= (sys.para.max_angle*10))
                {
                  unique_cntr=0;
                  for(chk_arr=sys.para.min_angle; chk_arr<=sys.para.max_angle; chk_arr++)
                  {
                    if(data_log_arr[chk_arr] == 1)
                    {
                      unique_cntr++;
                    }
                  }
                  // Do Not Put MinAngle == 0 ...............................
                  test_cntr = 0;
                  test_cntr = sys.para.min_angle;
                  
//                  sprintf(gbuf,"2)unique_cntr=%d and min_angle=%d\r\n",unique_cntr,sys.para.min_angle);
//                  UART_Send_String(UART_MODULE1,gbuf);
                  
                  // True if DataLogArr[TestCntr] == 0 ....
                  while(!data_log_arr[test_cntr])
                  {
                    test_cntr++;
                  }
                  min_log_angle = 0;
                  min_log_angle = test_cntr;
                  
//                  sprintf(gbuf,"3)min_log_angle=%d\r\n",min_log_angle);
//                  UART_Send_String(UART_MODULE1,gbuf);
                 
                  Lcd16x2_Cmd(LCD_CLEAR);
                  Lcd16x2_Out(1,1,"  MinLogAngle   ");
                  sprintf(ubuf,"%03d",min_log_angle);
                  Lcd16x2_Out(2,7,ubuf);
                  Delay_1ms(2000);

                  test_cntr = 0;
                  test_cntr = sys.para.max_angle;
                  // True if DataLogArr[TestCntr] == 0 ....
                  while(!data_log_arr[test_cntr])
                  {
                    test_cntr--;
                  }
                  max_log_angle = 0;
                  max_log_angle = test_cntr;
                  
//                  sprintf(gbuf,"4)max_log_angle=%d\r\n",max_log_angle);
//                  UART_Send_String(UART_MODULE1,gbuf);
                  
                  Lcd16x2_Cmd(LCD_CLEAR);
                  Lcd16x2_Out(1,1,"  MaxLogAngle   ");
                  sprintf(ubuf,"%03d",max_log_angle);
                  Lcd16x2_Out(2,7,ubuf);
                  Delay_1ms(2000);

                  // Can be Converted to Float ...............................
                  temp_data3 = pc_buf[0][min_log_angle];
                  temp_data4 = pc_buf[0][max_log_angle];

                  if((temp_data3 > temp_data4))
                  {
                    f1= ((temp_data3 - temp_data4)*1.0)/((max_log_angle - min_log_angle)*1.0);
                  }
                  else
                  {
                    f1=0.0;
                  }

                  count_step_val_P1 = f1;                        //Float to integer
                  
//                  sprintf(gbuf,"5)f1=%0.03f\r\n",f1);
//                  UART_Send_String(UART_MODULE1,gbuf);
                  
                  if((f1-count_step_val_P1) > 0.6)        // Compaire after decimal value
                  {
                    count_step_val_P1++;
                  }
                  
//                  sprintf(gbuf,"6)count_step_val_P1=%d\r\n",count_step_val_P1);
//                  UART_Send_String(UART_MODULE1,gbuf);
                  
                  Lcd16x2_Cmd(LCD_CLEAR);
                  Lcd16x2_Out(1,1,"  P1_StepVal    ");
                  sprintf(ubuf,"%03d",count_step_val_P1);
                  Lcd16x2_Out(2,7,ubuf);
                  Delay_1ms(2000);

                  if(sys.para.min_angle > 1)
                  {
                    Lcd16x2_Cmd(LCD_CLEAR);
                    // Filling Data For Angles between MinLogAngle & ZeroAngle.
                    test_cntr = min_log_angle;
                    #ifdef DEBUG_MSG
                    sprintf(gbuf,"7)min_log_angle=%d\r\n",min_log_angle);
                    //UART_Send_String(UART_MODULE1,gbuf);
                    #endif
                    while(test_cntr > 0)
                    {
                      p1_pressure_cnt = (pc_buf[0][test_cntr] + count_step_val_P1);
                      p2_pressure_cnt = pc_buf[1][test_cntr];
                      #ifdef DEBUG_MSG
                      sprintf(gbuf,"  %d) P1=%d P2=%d\r\n",test_cntr,p1_pressure_cnt,p2_pressure_cnt);
                      //UART_Send_String(UART_MODULE1,gbuf);
                      #endif

                      pc_buf[0][test_cntr-1] = p1_pressure_cnt;
                      pc_buf[1][test_cntr-1] = p2_pressure_cnt;

                      Lcd16x2_Out(1,1,"P1:     P2:     ");
                      Lcd16x2_Out(2,1,"BA:     => 0 Deg");

                      sprintf(ubuf,"%04d",p1_pressure_cnt);
                      Lcd16x2_Out(1,4,ubuf);
                      sprintf(ubuf,"%04d",p2_pressure_cnt);
                      Lcd16x2_Out(1,12,ubuf);
                      sprintf(ubuf,"%03d",test_cntr);
                      Lcd16x2_Out(2,4,ubuf);
                      Delay_1ms(1500);

                      test_cntr--;
                    }
                  }
                  else
                  {
                    Lcd16x2_Cmd(LCD_CLEAR);
                    Lcd16x2_Out(1,1,"NoDataMissed For");
                    Lcd16x2_Out(2,1,"Low Angles      ");
                    #ifdef DEBUG_MSG
                    //UART_Send_String(UART_MODULE1,"8)NoDataMissed\r\n");
                    #endif
                    Delay_1ms(2500);
                  }

                  // Filling Data For Angles between MaxLogAngle & 90 Degrees.
                  if(sys.para.max_angle < 90)
                  {
                    Lcd16x2_Cmd(LCD_CLEAR);

                    test_cntr = max_log_angle;
                    #ifdef DEBUG_MSG
                    sprintf(gbuf,"9)max_log_angle=%d\r\n",max_log_angle);
                    //UART_Send_String(UART_MODULE1,gbuf);
                    #endif
                    while(test_cntr < 90)
                    {
                      p1_pressure_cnt = (pc_buf[0][test_cntr] - count_step_val_P1);
                      p2_pressure_cnt = pc_buf[1][test_cntr];

                      pc_buf[0][test_cntr+1] = p1_pressure_cnt;
                      pc_buf[1][test_cntr+1] = p2_pressure_cnt;
                      
//                      sprintf(gbuf,"  %d) P1=%d P2=%d\r\n",test_cntr,p1_pressure_cnt,p2_pressure_cnt);
//                      UART_Send_String(UART_MODULE1,gbuf);
                      
                      Lcd16x2_Out(1,1,"P1:     P2:     ");
                      Lcd16x2_Out(2,1,"BA:     =>90 Deg");
                      
                      sprintf(ubuf,"%04d",p1_pressure_cnt);
                      Lcd16x2_Out(1,4,ubuf);
                      sprintf(ubuf,"%04d",p2_pressure_cnt);
                      Lcd16x2_Out(1,12,ubuf);
                      sprintf(ubuf,"%03d",test_cntr);
                      Lcd16x2_Out(2,4,ubuf);
                      Delay_1ms(150);

                      test_cntr++;
                    }
                  }

                    if(unique_cntr == ((sys.para.max_angle-sys.para.min_angle)+1))
                    {
                        Lcd16x2_Cmd(LCD_CLEAR);
                        Lcd16x2_Out(1,1,"Data Not Missed ");
                        Lcd16x2_Out(2,1,"For Any Angle...");
                        Delay_1ms(2000);

                        Lcd16x2_Cmd(LCD_CLEAR);
                        Lcd16x2_Out(1,1,"Calibration Done");
                        Lcd16x2_Out(2,1,"Successfully.1..");
                        Delay_1ms(2000);
                        #ifdef DEBUG_MSG
                        //UART_Send_String(UART_MODULE1,"10)Data Not Missed\r\n");
                        #endif
                    }
                    else
                    {
                        Lcd16x2_Cmd(LCD_CLEAR);
                        Lcd16x2_Out(1,1,"Data Missed For ");
                        Lcd16x2_Out(2,1,"Inter. Angles...");
                        Delay_1ms(2000);

                        Lcd16x2_Cmd(LCD_CLEAR);
                        Lcd16x2_Out(1,1,"Auto Calibration");
                        Lcd16x2_Out(2,1,"in Progress ....");
                        Delay_1ms(2000);

                        //=========================================================

                        Lcd16x2_Cmd(LCD_CLEAR);
                        // Filling Data Missed, for Angles between MinLogAngle & MaxLogAngle.
                        test_cntr = (min_log_angle+1);
                        #ifdef DEBUG_MSG
                        sprintf(gbuf,"11)test_cntr=%d\r\n",test_cntr);
                        //UART_Send_String(UART_MODULE1,gbuf);
                        #endif
                        while(test_cntr < max_log_angle)
                        {
                            if(data_log_arr[test_cntr] == 0)
                            {
                                p1_pressure_cnt = (pc_buf[0][test_cntr-1] - count_step_val_P1);
                                p2_pressure_cnt = pc_buf[1][test_cntr-1];

                                pc_buf[0][test_cntr+1] = p1_pressure_cnt;
                                pc_buf[1][test_cntr+1] = p2_pressure_cnt;
                                #ifdef DEBUG_MSG
                                sprintf(gbuf,"  %d) P1=%d P2=%d\r\n",test_cntr,p1_pressure_cnt,p2_pressure_cnt);
                                //UART_Send_String(UART_MODULE1,gbuf);
                                #endif

                                Lcd16x2_Out(1,1,"P1:     P2:     ");
                                Lcd16x2_Out(2,1,"BA:     Missed  ");

                                sprintf(ubuf,"%04d",p1_pressure_cnt);
                                Lcd16x2_Out(1,4,ubuf);
                                sprintf(ubuf,"%04d",p2_pressure_cnt);
                                Lcd16x2_Out(1,12,ubuf);
                                sprintf(ubuf,"%03d",test_cntr);
                                Lcd16x2_Out(2,4,ubuf);
                                Delay_1ms(800);
                            }
                            test_cntr++;
                        }

                        Lcd16x2_Cmd(LCD_CLEAR);
                        Lcd16x2_Out(1,1,"Calibration     ");
                        Lcd16x2_Out(2,1,"Done Success..2.");
                        Delay_1ms(2000);
                        #ifdef DEBUG_MSG
                        //UART_Send_String(UART_MODULE1,"12)Done Success..2\r\n");
                        #endif
                    }
                  
                    calib_stat_bit = 1;

                    //Save pressure curve to SPI flash
                    SPIFlash_Read_Sector(pc_sector);
                    Sector_Erase(pc_sector);
                    
                    flash.sector.page[pc_page][0] = sys.para.duty/256;
                    flash.sector.page[pc_page][1] = sys.para.duty%256;
                    flash.sector.page[pc_page][2] = sys.para.length_array[length_array_ptr]/256;
                    flash.sector.page[pc_page][3] = sys.para.length_array[length_array_ptr]%256;
                    flash.sector.page[pc_page][4] = sys.para.duty_type[sys.para.duty-1]/256;
                    flash.sector.page[pc_page][5] = sys.para.duty_type[sys.para.duty-1]%256;
                    
                    for(ang=0; ang<90; ang++)
                    {
                        flash.sector.page[pc_page][(ang*2)+16] = pc_buf[0][ang+1]/256;
                        flash.sector.page[pc_page][(ang*2)+17] = pc_buf[0][ang+1]%256;
                    }
  //                  sprintf(gbuf,"pc_sector=%d pc_page=%d\r\n",pc_sector,pc_page);
  //                  UART_Send_String(UART_MODULE1,gbuf);
                    if(pc_page == 15) //if page number for P1 curve is last page number then change sector number and write data to first page
                    {
                        SPIFlash_Write_Sector(pc_sector);
                        pc_sector++;
                        SPIFlash_Read_Sector(pc_sector);
                        Sector_Erase(pc_sector);
                        
                        flash.sector.page[0][0] = sys.para.duty/256;
                        flash.sector.page[0][1] = sys.para.duty%256;
                        flash.sector.page[0][2] = sys.para.length_array[length_array_ptr]/256;
                        flash.sector.page[0][3] = sys.para.length_array[length_array_ptr]%256;
                        flash.sector.page[0][4] = sys.para.duty_type[sys.para.duty-1]/256;
                        flash.sector.page[0][5] = sys.para.duty_type[sys.para.duty-1]%256;
                        
                        for(ang=0; ang<90; ang++)
                        {
                            flash.sector.page[0][(ang*2)+16] = pc_buf[1][ang+1]/256; //flash.sector.page[0] is because new sectors first page is always 0
                            flash.sector.page[0][(ang*2)+17] = pc_buf[1][ang+1]%256;
                        }
                    }
                    else       //Write both pages of P1 and P2 in same sector
                    {
                        flash.sector.page[pc_page+1][0] = sys.para.duty/256;
                        flash.sector.page[pc_page+1][1] = sys.para.duty%256;
                        flash.sector.page[pc_page+1][2] = sys.para.length_array[length_array_ptr]/256;
                        flash.sector.page[pc_page+1][3] = sys.para.length_array[length_array_ptr]%256;
                        flash.sector.page[pc_page+1][4] = sys.para.duty_type[sys.para.duty-1]/256;
                        flash.sector.page[pc_page+1][5] = sys.para.duty_type[sys.para.duty-1]%256;
                        
                        for(ang=0; ang<90; ang++)
                        {
                            flash.sector.page[pc_page+1][(ang*2)+16] = pc_buf[1][ang+1]/256;
                            flash.sector.page[pc_page+1][(ang*2)+17] = pc_buf[1][ang+1]%256;
                        }
                    }
                    SPIFlash_Write_Sector(pc_sector);
  //                  for(ang=0; ang<90; ang++)
  //                  {
  //                    sprintf(gbuf,"pc_buf[0][%d]=%d pc_buf[1][%d]=%d\r\n",ang,pc_buf[0][ang+1],ang,pc_buf[1][ang+1]);
  //                    UART_Send_String(UART_MODULE1,gbuf);
  //                  }
                    Lcd16x2_Cmd(LCD_CURSOR_OFF);

                    Supervisor_Save_Settings();//Save min and max angle to SPI Flash

                    Display_Supervisor_Set_Menu();
                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                }
              }
            }
          }
            if((calib_stat_bit == 0)&&(disp_refresh_cnt == 0))
            {
                disp_refresh_cnt = 500;
                sprintf(ubuf,"%04d",p1_pressure_cnt);
                Lcd16x2_Out(1,4,ubuf);                // P1
                sprintf(ubuf,"%04d",p2_pressure_cnt);
                Lcd16x2_Out(2,4,ubuf);                // P2
                TempDispBoomAngle = (bm_angle/10);
    //            if(bm_angle > 99)   sprintf(ubuf,"%.1fﬂ ",((float)bm_angle)/10.0);
    //            else                sprintf(ubuf,"0%.1fﬂ ",((float)bm_angle)/10.0);
                sprintf(ubuf,"%04.1fﬂ ",((float)bm_angle)/10.0);
    //            sprintf(ubuf,"%02dﬂ",TempDispBoomAngle);
                Lcd16x2_Out(1,12,ubuf);
                sprintf(ubuf,"%03d ",test_cntr);
                Lcd16x2_Out(2,13,ubuf);
            }
            if(key.function == 1)
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Supervisor_Set_Menu();
                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                key.function = 0;
            }                                // BL
            break;
        }
        case SITE_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    mv.site_set++;
                    if(mv.site_set > mv.max)  mv.site_set = mv.min;
                    Select_Site_Set_Menu();
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    mv.site_set--;
                    if(mv.site_set < mv.min)  mv.site_set = mv.max;
                    Select_Site_Set_Menu();
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                menu_stat = SITE_SET_PAGE;
                Site_Setting();
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SITE_SET_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Site_Shift_Cursor(0);
                else              Site_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Site_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Site_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Site_Save_Settings();
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
            }
            break;
        }
        case START_COPY_DUTY_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Shift_Cursor_Position(0,2,NO_DECIMAL_POINT);
                else              Shift_Cursor_Position(1,2,NO_DECIMAL_POINT);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
                    sprintf(ubuf,"%02d",(uint8_t)common_long);
                    Lcd16x2_Out(1,11,ubuf);
                    Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                    sprintf(ubuf,"%02d",(uint8_t)common_long);
                    Lcd16x2_Out(1,11,ubuf);
                    Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((common_long <= lc_total_duty)&&(common_long > 0))
                {
                    start_cpy_dty = (uint8_t)common_long;
                    prv16_val2 = end_cpy_dty;
                    sprintf(ubuf,"%02d",prv16_val2);
                    Lcd16x2_Out(2,9,ubuf);
                    pos_t = 0;
                    common_byte = 2;
                    common_long = prv16_val2;
                    Move_Cursor_Left(1);
                    menu_stat = END_COPY_DUTY_PAGE;
                }
                else if(common_long > lc_total_duty)
                {
                    common_long = 1;
                    sprintf(ubuf,"TOTAL DUTY:%02d   ",lc_total_duty);
                    Lcd16x2_Out(1,1,ubuf);
                    Delay_1ms(1000);
                    sprintf(ubuf,"FROM DUTY:%02d    ",(uint8_t)common_long);
                    Lcd16x2_Out(1,1,ubuf);
                    sprintf(ubuf,"%02d",(uint8_t)common_long);
                    Lcd16x2_Out(1,11,ubuf);
                    Move_Cursor_Left(1);
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;              
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case END_COPY_DUTY_PAGE:
        {
          if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Shift_Cursor_Position(0,2,NO_DECIMAL_POINT);
                else              Shift_Cursor_Position(1,2,NO_DECIMAL_POINT);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
                    sprintf(ubuf,"%02d",(uint8_t)common_long);
                    Lcd16x2_Out(2,9,ubuf);
                    Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                    sprintf(ubuf,"%02d",(uint8_t)common_long);
                    Lcd16x2_Out(2,9,ubuf);
                    Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((common_long <= lc_total_duty)&&(common_long > 0))
                {
                    Lcd16x2_Out(1,1,"IN PROGRESS...  ");
                    Lcd16x2_Out(2,1,"PLEASE WAIT...! ");
                    Delay_1ms(2000);
                    end_cpy_dty = (uint8_t)common_long;
                    
                    for(length_array_ptr=0; length_array_ptr<5; length_array_ptr++)
                    {
                        csv_ref_len = length_array_ptr%5;
                        pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + (((uint32_t)start_cpy_dty-1)*10*256) + csv_ref_len*512 + flash_memory_offset;
                        
//                        sprintf(ubuf,"Page address=%.00f Page offset=%.00f\r\n",(float)pc_page_addr,(float)flash_memory_offset);
//                        UART_Send_String(UART_MODULE1,ubuf);
                        
                        pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                        pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector
                        
                        pc_sector = pc_sector_quotient;
                        pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15
                        
//                        sprintf(ubuf,"start_cpy_dty-%02d PC_S-%03d ref_len-%02d\r\n",start_cpy_dty,lc_press_curve_page_s,csv_ref_len);
//                        UART_Send_String(UART_MODULE1,ubuf);
//                        sprintf(ubuf,"sector-%02d page-%02d\r\n",pc_sector,pc_page);
//                        UART_Send_String(UART_MODULE1,ubuf);
                        
                        SPIFlash_Read_Sector(pc_sector);
                        for(ang=0; ang<90; ang++)
                        {
                            pc_buf[0][ang] = (flash.sector.page[pc_page][(ang*2)+16]*256)+flash.sector.page[pc_page][(ang*2)+17];
                        }
                        
                        if(pc_page == 15)
                        {
                            pc_sector++;
                            SPIFlash_Read_Sector(pc_sector);
                            for(ang=0; ang<90; ang++)
                            {
                                pc_buf[1][ang] = (flash.sector.page[0][(ang*2)+16]*256)+flash.sector.page[0][(ang*2)+17];
                            }                      
                        }
                        else
                        {
                            for(ang=0; ang<90; ang++)
                            {
                                pc_buf[1][ang] = (flash.sector.page[pc_page+1][(ang*2)+16]*256)+flash.sector.page[pc_page+1][(ang*2)+17];
                            }
                        }
//                        for(ang=0; ang<90; ang++)
//                        {
//                            sprintf(ubuf,"Angle = %02d P1 = %04d P2 = %04d\r\n",ang+1,pc_buf[0][ang],pc_buf[1][ang]);
//                            UART_Send_String(UART_MODULE1,ubuf);
//                        }
                        //UART_Send_String(UART_MODULE1,"Pressure curve End...!!\r\n");
                        
                        csv_ref_len = length_array_ptr%5;
                        pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + (((uint32_t)end_cpy_dty-1)*10*256) + csv_ref_len*512 + flash_memory_offset;
                        
//                        sprintf(ubuf,"Page address=%.00f Page offset=%.00f\r\n",(float)pc_page_addr,(float)flash_memory_offset);
//                        UART_Send_String(UART_MODULE1,ubuf);
                        
                        pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                        pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector
                        
                        pc_sector = pc_sector_quotient;
                        pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15
                        
//                        sprintf(ubuf,"end_cpy_dty-%02d PC_S-%03d ref_len-%02d\r\n",end_cpy_dty,lc_press_curve_page_s,csv_ref_len);
//                        UART_Send_String(UART_MODULE1,ubuf);
//                        sprintf(ubuf,"sector-%02d page-%02d\r\n",pc_sector,pc_page);
//                        UART_Send_String(UART_MODULE1,ubuf);
                        
                        SPIFlash_Read_Sector(pc_sector);
                        for(ang=0; ang<90; ang++)
                        {
                            flash.sector.page[pc_page][(ang*2)+16] = pc_buf[0][ang]/256;
                            flash.sector.page[pc_page][(ang*2)+17] = pc_buf[0][ang]%256;
                        }
                        
                        if(pc_page == 15)
                        {
                            Sector_Erase(pc_sector);
                            SPIFlash_Write_Sector(pc_sector);
                            pc_sector++;
                            SPIFlash_Read_Sector(pc_sector);
                            for(ang=0; ang<90; ang++)
                            {
                                flash.sector.page[0][(ang*2)+16] = pc_buf[1][ang]/256;
                                flash.sector.page[0][(ang*2)+17] = pc_buf[1][ang]%256;
//                                pc_buf[1][ang] = (flash.sector.page[0][(ang*2)+16]*256)+flash.sector.page[0][(ang*2)+17];
                            }
                            Sector_Erase(pc_sector);
                            SPIFlash_Write_Sector(pc_sector);
//                            sprintf(ubuf,"Changed sector-%02d page-%02d\r\n",pc_sector,pc_page);
//                            UART_Send_String(UART_MODULE1,ubuf);
                        }
                        else
                        {
                            for(ang=0; ang<90; ang++)
                            {
                                flash.sector.page[pc_page+1][(ang*2)+16] = pc_buf[1][ang]/256;
                                flash.sector.page[pc_page+1][(ang*2)+17] = pc_buf[1][ang]%256;
//                                pc_buf[1][ang] = (flash.sector.page[pc_page+1][(ang*2)+16]*256)+flash.sector.page[pc_page+1][(ang*2)+17];
                            }
                            Sector_Erase(pc_sector);
                            SPIFlash_Write_Sector(pc_sector);                            
                        }
                        
                    }
                    Lcd16x2_Cmd(LCD_CLEAR);
                    Lcd16x2_Out(1,1,"  DATA COPIED   ");
                    Delay_1ms(1000);
                    Lcd16x2_Cmd(LCD_CURSOR_OFF);              
                    Display_Site_Set_Menu();
                    menu_stat = SITE_SET_CODE_PAGE;
                }
                else if(common_long > lc_total_duty)
                {
                    common_long = 1;
                    sprintf(ubuf,"TOTAL DUTY:%02d   ",lc_total_duty);
                    Lcd16x2_Out(1,1,ubuf);
                    Delay_1ms(1000);
                    sprintf(ubuf,"TO DUTY:%02d      ",(uint8_t)common_long);
                    Lcd16x2_Out(2,1,ubuf);
                    sprintf(ubuf,"%02d",(uint8_t)common_long);
                    Lcd16x2_Out(2,9,ubuf);
                    Move_Cursor_Left(1);
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
              Display_Site_Set_Menu();
              menu_stat = SITE_SET_CODE_PAGE;              
              key.function = 0;
              Delay_1ms(500);
            }
          break;
        }
        case SELECT_LENGTH_FACTOR_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Select_Length_Factor_Menu(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Select_Length_Factor_Menu(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                sprintf(ubuf,"CV:%03d    PV:%03d",bl_fact[length_cnt-1],bl_fact[length_cnt-1]);
                Lcd16x2_Out(2,1,ubuf);
                Display_Length_Factor_Cursor();
                menu_stat = EDIT_LEN_FACTOR_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case EDIT_LEN_FACTOR_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Site_Shift_Cursor(0);
                else                    Site_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Site_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Site_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Site_Save_Settings();
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SELECT_LEN_COUNT_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Select_Length_Count_Menu(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Select_Length_Count_Menu(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                sprintf(ubuf,"CV:%04d  PV:%04d",sys.para.bl_adc_cnt[length_cnt],sys.para.bl_adc_cnt[length_cnt]);
                Lcd16x2_Out(2,1,ubuf);
                Display_Length_Count_Cursor();
                menu_stat = EDIT_LEN_COUNTS_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case EDIT_LEN_COUNTS_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Site_Shift_Cursor(0);
                else              Site_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Site_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Site_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Site_Save_Settings();
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case FACTORY_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    mv.factory_set++;
                    if(mv.factory_set > mv.max)  mv.factory_set = mv.min;
                    Select_Factory_Set_Menu();
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    mv.factory_set--;
                    if(mv.factory_set < mv.min)  mv.factory_set = mv.max;
                    Select_Factory_Set_Menu();
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                menu_stat = FACTORY_SET_PAGE;
                Factory_Setting();
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case FACTORY_SET_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Factory_Shift_Cursor(0);
                else              Factory_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Factory_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Factory_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Factory_Save_Settings();
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case PRESSURE_CURVE_SEND_PAGE:
        {
            if(pc_tout == 0)
            {
                complimnt_flag = !complimnt_flag;
                if(complimnt_flag)
                {
                    Lcd16x2_Out(1,1,"PLEASE CONNECT  ");
                    Lcd16x2_Out(2,1,"RS232 TO PC AND ");
                }
                else
                {
                    Lcd16x2_Out(1,1,"PRESS ENTER KEY ");
                    Lcd16x2_Out(2,1,"TO START COMM.  ");
                }
                pc_tout = 2500;                
            }
            if(key.enter == 1)
            {
                Lcd16x2_Out(1,1,"SENDING DATA..!!");
                Lcd16x2_Out(2,1,"PLEASE WAIT...  ");
                Send_Pressure_Curve_Uart();
                Lcd16x2_Out(2,1,"   COMPLETED    ");
                Delay_1ms(1500);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.enter = 0;
            }
            break;
        }
        case SET_PERC_STATUS_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Factory_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Factory_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if(prv8_val1 == 1)
                {
                  Display_Factor_Menu();
                  menu_stat = SET_PERC_FACTOR_PAGE;
                }
                else
                {
                  Factory_Save_Settings();
                  Lcd16x2_Cmd(LCD_CURSOR_OFF);
                  Display_Factory_Set_Menu();
                  menu_stat = FACTORY_SET_CODE_PAGE;
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_PERC_FACTOR_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Factor_Shift_Cursor();
                else                    Factor_Shift_Cursor();
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Factor_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Factor_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Factory_Save_Settings();
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_CRANE_DETAILS_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Crane_Detail_Shift_Cursor(0);
                else                    Crane_Detail_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Crane_Detail_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Crane_Detail_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                crane_detail_cnt++;
                if(crane_detail_cnt > mv.max)
                {
                  Update_Crane_Details();
                  Factory_Save_Settings();
                  Lcd16x2_Cmd(LCD_CURSOR_OFF);
                  Display_Factory_Set_Menu();
                  menu_stat = FACTORY_SET_CODE_PAGE;
                }
                else
                {
                  Update_Crane_Details();
                  Display_Crane_Details_Menu();
                }
                key.enter = 0;
            }
            break;
        }
        case SELECT_CRANE_MODEL_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Select_Crane_Model(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Select_Crane_Model(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Factory_Save_Settings();
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case WRITE_TO_MEMORY_PAGE1:       //Select baudrate
        {
            if(key.increment == 1)        // INC Key
            {
                if(common_byte < 2) common_byte++;
                else                common_byte = 0;
                
                Lcd16x2_Out(2,7,"          ");
                sprintf(ubuf,"%lu",baud[common_byte]);
                Lcd16x2_Out(2,7,ubuf);
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                if(common_byte > 0) common_byte--;
                else                common_byte = 2;
                
                Lcd16x2_Out(2,7,"          ");
                sprintf(ubuf,"%lu",baud[common_byte]);
                Lcd16x2_Out(2,7,ubuf);
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                GPIO_Function(GPIO_PORTF,U3_TELE_RX_F0,GPIO_INPUT,0,DIGITAL_INPUT);
                GPIO_Function(GPIO_PORTF,U3_TELE_TX_F1,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
                PORTFbits.RF1 = 1;
                PPS_Mapping(RPI96_MAPPING,PPS_INPUT,UART3Rx);
                PPS_Mapping(RP97_MAPPING,PPS_OUTPUT,UART3Tx);
                UART_Initialize(UART_MODULE3,baud[common_byte],1);
                
//                GPIO_Function(GPIO_PORTD,U1_DEBUG_RX_D12,GPIO_INPUT,0,DIGITAL_INPUT);
//                GPIO_Function(GPIO_PORTD,U1_DEBUG_TX_D5,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
//                PORTDbits.RD5 = 1;
//                PPS_Mapping(RPI76_MAPPING,PPS_INPUT,UART1Rx);
//                PPS_Mapping(RP69_MAPPING,PPS_OUTPUT,UART1Tx);
//                
//                UART_Initialize(UART_MODULE1,baud[common_byte],1);
                
                Lcd16x2_Out(1,1,"SPI FLASH:      ");
                Lcd16x2_Out(2,1,"ERASE: NO       ");
                common_byte = 0;
                menu_stat = WRITE_TO_MEMORY_PAGE2;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case WRITE_TO_MEMORY_PAGE2:       //Flash erase option
        {
            if(key.increment == 1)        // INC Key
            {
                Lcd16x2_Out(2,8,"         "); 
                Lcd16x2_Out(2,8,"YES      "); 
                common_byte = 1;
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                Lcd16x2_Out(2,8,"         "); 
                Lcd16x2_Out(2,8,"NO       ");
                common_byte = 0;
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if(common_byte)
                {
                    SPI_WriteBlockProtection();
                    SPI_Flash_Chip_Erase();
                    Lcd16x2_Out(1,1,"CHIP ERASE IS:  ");
                    Lcd16x2_Out(2,1,"COMPLETED...!!  "); 
                    Delay_1ms(1500);
                    Lcd16x2_Out(1,1,"PRESS ENTR TO:  ");
                    Lcd16x2_Out(2,1,"START PC COMM..."); 
                    menu_stat = WRITE_TO_MEMORY_PAGE3;
                }
                else
                {
                    Lcd16x2_Out(1,1,"CANCELLED FLASH ");
                    Lcd16x2_Out(2,1,"WRITE OPERATION ");
                    Delay_1ms(1500);
                    Display_Factory_Set_Menu();
                    menu_stat = FACTORY_SET_CODE_PAGE;
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                common_byte = 0;
                Lcd16x2_Out(2,1,"                "); 
                Lcd16x2_Out(1,1,"SET BAUDRATE:   ");
                sprintf(ubuf,"SPEED:%lu",baud[common_byte]);
                Lcd16x2_Out(2,1,ubuf);    
                menu_stat = WRITE_TO_MEMORY_PAGE1;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case WRITE_TO_MEMORY_PAGE3:       //Wait to start operation
        {
            if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Out(1,1,"PC COMMUNIACTION");
                Lcd16x2_Out(2,1,"STARTED...!!    "); 
                Delay_1ms(1500);
                NewCSVFlag = 1;
                RxStart_flag = 0;
//                UART1_Write(0x02);
                UART3_Write(0x02);
                
                while(!RxStart_flag);                 //check zero
                sprintf(ubuf,"TOTAL PAGES:%04d",TotalNoPageRecive);
                Lcd16x2_Out(1,1,ubuf);
                sprintf(ubuf,"PAGE COUNTS:%04d",Page_count);
                Lcd16x2_Out(2,1,ubuf);
                menu_stat = WRITE_TO_MEMORY_PAGE4;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case WRITE_TO_MEMORY_PAGE4:       //PC communication and SPI write operation is in progress
        {
            while(!DataRxdOver)            //check zero
            {
                if((NewCSVFlag==0)&&(Page_done==1))
                {
                    memcpy(flash.sector.page[0],Serial_buff,256);
                    SPIFlash_Write_Page(_add,0);
                    _add = _add + 256;
                    Page_count++;
                    sprintf(ubuf,"%04d",Page_count);
                    Lcd16x2_Out(2,13,ubuf);
                    Delay_1ms(50);
//                    UART1_Write(0x06);
                    UART3_Write(0x06);
                    Page_done =0;	
                }
                else if((NewCSVFlag==1)&&(Page_done==1))
                {
                    TotalNoPageRecive = (Serial_buff[0]*256)+Serial_buff[1];
                    sprintf(ubuf,"%04d",TotalNoPageRecive);
                    Lcd16x2_Out(1,13,ubuf);
                    
//                    UART1_Write(0x06);
                    UART3_Write(0x06);
                    Page_done =0;
                    NewCSVFlag = 0;
                }
                else
                {
                    continue;
                }
            }
            flash_page_addr = ONE_SECTOR_SIZE+18; //start page address of first cane//Default crane ID is 1
            sys.para.crane_page_index = (SPIFlash_Read_Byte(flash_page_addr)*256)+SPIFlash_Read_Byte(flash_page_addr+1);
            
            Read_Startup_SPIFlash();
            
            Factory_Default_Reset();
            
            Read_System_Parameters();
            
            Calc_CranePara();
            Calc_Parameter_Factors();
            Lcd16x2_Out(1,1,"DATA TRANSFER   ");
            Lcd16x2_Out(2,1,"COMPLETED...!!  ");
            Delay_1ms(1500);
            
            menu_stat = DEFAULT_PAGE;
            break;
        }
        case VIEW_DUTY_TABLE_PAGE1:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Site_Shift_Cursor(0);
                else              Site_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                Site_Change_Parameter_Value(0);
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                Site_Change_Parameter_Value(1);
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                common_byte = 1;
                prv16_val1 = (uint8_t)common_long;
                if(prv16_val1 <= total_dty_tables)
                {
                    sprintf(ubuf,"TABL:%04d CNT:%02d",prv16_val1,common_byte);
                    Lcd16x2_Out(1,1,ubuf);
                    flash_page_addr = (((uint32_t)lc_duty_table_page_s-1)*256)+((prv16_val1-1)*256)+2+flash_memory_offset;
                    vradcntr = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
                    
                    Get_Radius_Capacity(prv16_val1,common_byte-1);                
                    sprintf(ubuf,"R:%05.1f  C:%05.1f",((float)vrad)/10.0,((float)vcapa)/10.0);                
                    Lcd16x2_Out(2,1,ubuf);
                    menu_stat = VIEW_DUTY_TABLE_PAGE2;
                }
                else
                {
                    sprintf(ubuf," MAX TABLE:%04d ",total_dty_tables);
                    Lcd16x2_Out(1,1,ubuf);
                    Delay_1ms(1500);
                    Lcd16x2_Out(1,1,"ENTER TABLE NO: ");
                    sprintf(ubuf,"%04d",prv16_val1);
                    Lcd16x2_Out(2,7,ubuf);
                    Move_Cursor_Left(1);
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Site_Set_Menu();
                menu_stat = SITE_SET_CODE_PAGE;
                Delay_1ms(500);
                key.function = 0;
            }
            break;
        }
        case VIEW_DUTY_TABLE_PAGE2:
        {
            if((key.increment == 1)||(key.decrement == 1))
            {
                if(key.increment == 1)
                {
                    common_byte++;
                    if(common_byte > vradcntr)  common_byte = 1;
                }
                else
                {
                    common_byte--;
                    if(common_byte < 1)  common_byte = vradcntr;
                }
                sprintf(ubuf,"%02d",common_byte);
                Lcd16x2_Out(1,15,ubuf);
                Get_Radius_Capacity(prv16_val1,common_byte-1); 
                sprintf(ubuf,"R:%05.1f  C:%05.1f",((float)vrad)/10.0,((float)vcapa)/10.0);
                Lcd16x2_Out(2,1,ubuf);
                key.increment = 0;
                key.decrement = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Out(2,1,"                ");
                Lcd16x2_Out(1,1,"ENTER TABLE NO: ");
                pos_t = 0;
                common_byte = 4;
                common_long = prv16_val1;
                sprintf(ubuf,"%04d",prv16_val1);
                Lcd16x2_Out(2,7,ubuf);
                Move_Cursor_Left(1);
                Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
                menu_stat = VIEW_DUTY_TABLE_PAGE1;
                
                Delay_1ms(500);
                key.function = 0;
            }
            key.bypass = 0;
            key.duty = 0;
            key.enter = 0;
            break;
        }
        case SELECT_MIN_MAX_PCURVE_PAGE:
        {
            if(key.increment == 1)
            {
                min_max_pcurve_flag = !min_max_pcurve_flag;
                Select_Min_Max_PCurve_Menu();
                key.increment = 0;
            }
            else if(key.decrement == 1)
            {
                min_max_pcurve_flag = !min_max_pcurve_flag;
                Select_Min_Max_PCurve_Menu();
                key.decrement = 0;
            }
            else if(key.enter == 1)
            {
                if(min_max_pcurve_flag == 0)
                {
                    Display_Min_Calib_Angle_Menu();
                    menu_stat = SET_MIN_ANGLE_PCURVE_PAGE;
                }
                else
                {
                    Lcd16x2_Cmd(LCD_CLEAR);
                    Lcd16x2_Out(1,1,"ENTER KNOWN LOAD");
                    prv16_val1 = known_load_pcurve;
                    sprintf(ubuf,"CV:%04.1f  PV:%04.1f",((float)prv16_val1)/10.0,((float)prv16_val1)/10.0);        
                    Lcd16x2_Out(2,1,ubuf);
                    
                    pos_t = 0;
                    common_byte = 3;
                    common_long = prv16_val1;
                    sprintf(ubuf,"%04.1f",((float)prv16_val1)/10.0);
                    Lcd16x2_Out(2,4,ubuf);
                    Move_Cursor_Left(1);
                    Lcd16x2_Cmd(LCD_BLINK_CURSOR_ON);
                    menu_stat = SET_KNOWN_LOAD_PCURVE_PAGE;
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_KNOWN_LOAD_PCURVE_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Shift_Cursor_Position(0,3,ONE_DECIMAL_POINT);
                else              Shift_Cursor_Position(1,3,ONE_DECIMAL_POINT);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
                    sprintf(ubuf,"%04.1f",((float)common_long)/10.0);
                    Lcd16x2_Out(2,4,ubuf);
                    if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
                    else            Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                    sprintf(ubuf,"%04.1f",((float)common_long)/10.0);
                    Lcd16x2_Out(2,4,ubuf);
                    if(pos_t > 0)   Move_Cursor_Left(pos_t+2);
                    else            Move_Cursor_Left(pos_t+1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                known_load_pcurve = (uint16_t)common_long;
                Lcd16x2_Cmd(LCD_CLEAR);
                Lcd16x2_Out(1,1,"   DATA SAVED   ");
                Delay_1ms(1500);
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Min_Calib_Angle_Menu();
                menu_stat = SET_MIN_ANGLE_PCURVE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Select_Min_Max_PCurve_Menu();
                menu_stat = SELECT_MIN_MAX_PCURVE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_MIN_ANGLE_PCURVE_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Calib_Angle_Shift_Cursor(0);
                else              Calib_Angle_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                Lcd16x2_Out(1,1,"   DATA SAVED   ");
                Delay_1ms(1500);
                sys.para.min_angle = angle_calib_pt;
                
                Display_Max_Calib_Angle_Menu();
                menu_stat = SET_MAX_ANGLE_PCURVE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Select_Min_Max_PCurve_Menu();
                menu_stat = SELECT_MIN_MAX_PCURVE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_MAX_ANGLE_PCURVE_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                if(key.duty == 1) Calib_Angle_Shift_Cursor(0);
                else                    Calib_Angle_Shift_Cursor(1);
                key.bypass = 0;
                key.duty = 0;
            }
            else if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(0);
                    Delay_1ms(600);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Calib_Angle_Change_Parameter_Value(1);
                    Delay_1ms(600);
                }
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CLEAR);
                Lcd16x2_Out(1,1,"   DATA SAVED   ");
                Delay_1ms(1500);
                sys.para.max_angle = angle_calib_pt;
                
                Display_Calib_Length_Angle();
                menu_stat = SET_LIVE_LEN_ANGLE_PCURVE_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Min_Calib_Angle_Menu();
                menu_stat = SET_MIN_ANGLE_PCURVE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SET_LIVE_LEN_ANGLE_PCURVE_PAGE: 
        {
            //Show live values of boom length and angle
            if(disp_refresh_cnt == 0)
            {
                disp_refresh_cnt = 500;
                sprintf(ubuf,"%04.1fM ",((float)TotalBmLength)/10.0);
                Lcd16x2_Out(1,4,ubuf);

                TempDispBoomAngle = (bm_angle/10);
                sprintf(ubuf,"%04.1fﬂ ",((float)bm_angle)/10.0);
                Lcd16x2_Out(2,4,ubuf);
            }
            if(key.enter == 1)        // ENTR Key
            {
                if(pcurve_up_dn_flag == 1)
                {
                    Lcd16x2_Out(1,1,"Press ENT Key to");
                    Lcd16x2_Out(2,1,"Start BmUp Read ");
                    Delay_1ms(1000);
                    menu_stat = ENTRKEY_BOOM_UP_PCURVE_PAGE;
                }
                else if(pcurve_up_dn_flag == 2)
                {
                    Lcd16x2_Out(1,1,"Press ENT Key to");
                    Lcd16x2_Out(2,1,"Start BmDn Read ");
                    Delay_1ms(1000);
                    menu_stat = ENTRKEY_BOOM_DN_PCURVE_PAGE;
                }
                calib_stat_bit = 0;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Display_Max_Calib_Angle_Menu();
                menu_stat = SET_MAX_ANGLE_PCURVE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case ENTRKEY_BOOM_UP_PCURVE_PAGE:           //Wait to start calibration
        {
            if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Lcd16x2_Out(1,1,"P1:     BA:    ﬂ");
                Lcd16x2_Out(2,1,"P2:             ");
                Delay_1ms(1000);
                CrtBoomAngle = 0;
                PrevBoomAngle = 0;
                test_cntr = 0;
                menu_stat = TAKE_P1P2_PCURVE_UP_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))
            {
                Display_Max_Calib_Angle_Menu();
                menu_stat = SET_MAX_ANGLE_PCURVE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case ENTRKEY_BOOM_DN_PCURVE_PAGE:           //Wait to start calibration
        {
            if(key.enter == 1)        // ENTR Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Lcd16x2_Out(1,1,"P1:     BA:    ﬂ");
                Lcd16x2_Out(2,1,"P2:             ");
                Delay_1ms(1000);
                CrtBoomAngle = 0;
                PrevBoomAngle = sys.para.max_angle;
                test_cntr = 0;
                
                menu_stat = TAKE_P1P2_PCURVE_DN_PAGE;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))
            {
                Display_Max_Calib_Angle_Menu();
                menu_stat = SET_MAX_ANGLE_PCURVE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case TAKE_P1P2_PCURVE_UP_PAGE:
        {
            if(bm_angle >= ((sys.para.min_angle*10) + 4))
            {
                CrtBoomAngle = (bm_angle/10);
                
                if(CrtBoomAngle >= PrevBoomAngle)        // Will definitely execute once ....
                {
                    if((CrtBoomAngle-PrevBoomAngle) >= (1))
                    {
                        pc_buf[0][CrtBoomAngle] = p1_pressure_cnt;
                        pc_buf[1][CrtBoomAngle] = p2_pressure_cnt;
                        
                        for(chk_arr=PrevBoomAngle+1; chk_arr<CrtBoomAngle; chk_arr++)
                        {
                            pc_buf[0][chk_arr] = p1_pressure_cnt;
                            pc_buf[1][chk_arr] = p2_pressure_cnt;
                            test_cntr++;
                        }
                        
                        PrevBoomAngle = (CrtBoomAngle);
                        
                        if(bm_angle >= (sys.para.max_angle*10))
                        {
                            Lcd16x2_Cmd(LCD_CLEAR);
                            Lcd16x2_Out(1,1,"NoDataMissed For");
                            Lcd16x2_Out(2,1,"Low Angles      ");

                            Delay_1ms(1500);
                            // Filling Data For Angles between MaxLogAngle & 90 Degrees.
                            if(sys.para.max_angle < 90)
                            {
                                Lcd16x2_Cmd(LCD_CLEAR);
                                
                                test_cntr = sys.para.max_angle;
                                
                                while(test_cntr < 90)
                                {
                                    pc_buf[0][test_cntr+1] = p1_pressure_cnt;
                                    pc_buf[1][test_cntr+1] = p2_pressure_cnt;

//                                    Lcd16x2_Out(1,1,"P1:     P2:     ");
//                                    Lcd16x2_Out(2,1,"BA:     =>90 Deg");
//
//                                    sprintf(ubuf,"%04d",p1_pressure_cnt);
//                                    Lcd16x2_Out(1,4,ubuf);
//                                    sprintf(ubuf,"%04d",p2_pressure_cnt);
//                                    Lcd16x2_Out(1,12,ubuf);
//                                    sprintf(ubuf,"%03d",test_cntr);
//                                    Lcd16x2_Out(2,4,ubuf);
//                                    Delay_1ms(250);

                                    test_cntr++;
                                }
                            }                            
                            calib_stat_bit = 1;
                            
                            //Save pressure curve to SPI flash                            
                            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                            
                            for(ang=0; ang<90; ang++)
                            {
                                if(min_max_pcurve_flag == 0)
                                {
                                    p1_pcurve_min_up[ang] = pc_buf[0][ang+1];
                                    p2_pcurve_min_up[ang] = pc_buf[1][ang+1];
                                }
                                else
                                {
                                    p1_pcurve_max_up[ang] = pc_buf[0][ang+1];
                                    p2_pcurve_max_up[ang] = pc_buf[1][ang+1];
                                }
                            }
                            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
                            
                            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                            Lcd16x2_Cmd(LCD_CURSOR_OFF);
                            
                            Display_Factory_Set_Menu();
                            menu_stat = FACTORY_SET_CODE_PAGE;
                        }
                    }
                }
            }
            if((calib_stat_bit == 0)&&(disp_refresh_cnt == 0))
            {
                disp_refresh_cnt = 500;
                sprintf(ubuf,"%04d",p1_pressure_cnt);
                Lcd16x2_Out(1,4,ubuf);                // P1
                sprintf(ubuf,"%04d",p2_pressure_cnt);
                Lcd16x2_Out(2,4,ubuf);                // P2
                TempDispBoomAngle = (bm_angle/10);

                sprintf(ubuf,"%04.1fﬂ ",((float)bm_angle)/10.0);
                Lcd16x2_Out(1,12,ubuf);
//                sprintf(ubuf,"%03d ",test_cntr);
//                Lcd16x2_Out(2,13,ubuf);
            }
            if(key.function == 1)
            {
                Display_Max_Calib_Angle_Menu();
                menu_stat = SET_MAX_ANGLE_PCURVE_PAGE;
                key.function = 0;
            } 
            break;
        }
        case TAKE_P1P2_PCURVE_DN_PAGE:
        {
            if(bm_angle <= ((sys.para.max_angle*10) - 4))
            {
                CrtBoomAngle = (bm_angle/10);
                
                if(CrtBoomAngle <= PrevBoomAngle)        // Will definitely execute once ....
                {
                    if((PrevBoomAngle-CrtBoomAngle) >= (1))
                    {
                        pc_buf[0][CrtBoomAngle] = p1_pressure_cnt;
                        pc_buf[1][CrtBoomAngle] = p2_pressure_cnt;
                        
                        if((PrevBoomAngle-CrtBoomAngle) > (1))
                        {
                            for(chk_arr=PrevBoomAngle; chk_arr>CrtBoomAngle; chk_arr--)
                            {
                                pc_buf[0][chk_arr] = p1_pressure_cnt;
                                pc_buf[1][chk_arr] = p2_pressure_cnt;
                            }
                        }
                        
                        PrevBoomAngle = CrtBoomAngle;
                        
                        if(bm_angle <= (sys.para.min_angle*10))
                        {
                            Lcd16x2_Cmd(LCD_CLEAR);
                            Lcd16x2_Out(1,1,"NoDataMissed For");
                            Lcd16x2_Out(2,1,"High Angles     ");
                            
                            Delay_1ms(1500);
                            
                            // Filling Data For Angles between MaxLogAngle & 90 Degrees.
                            if(sys.para.max_angle < 90)
                            {
                                Lcd16x2_Cmd(LCD_CLEAR);
                                
                                test_cntr = sys.para.max_angle;
                                
                                while(test_cntr < 90)
                                {
                                    pc_buf[0][test_cntr+1] = pc_buf[0][sys.para.max_angle-2];
                                    pc_buf[1][test_cntr+1] = pc_buf[1][sys.para.max_angle-2];

//                                    Lcd16x2_Out(1,1,"P1:     P2:     ");
//                                    Lcd16x2_Out(2,1,"BA:     =>90 Deg");
//
//                                    sprintf(ubuf,"%04d",pc_buf[0][test_cntr+1]);
//                                    Lcd16x2_Out(1,4,ubuf);
//                                    sprintf(ubuf,"%04d",pc_buf[1][test_cntr+1]);
//                                    Lcd16x2_Out(1,12,ubuf);
//                                    sprintf(ubuf,"%03d",test_cntr);
//                                    Lcd16x2_Out(2,4,ubuf);
//                                    Delay_1ms(250);

                                    test_cntr++;
                                }
                            }
                            
                            calib_stat_bit = 1;
                            
                            //Save pressure curve to SPI flash                            
                            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                            
                            for(ang=0; ang<90; ang++)
                            {
                                if(min_max_pcurve_flag == 0)
                                {
                                    p1_pcurve_min_dn[ang] = pc_buf[0][ang+1];
                                    p2_pcurve_min_dn[ang] = pc_buf[1][ang+1];
                                }
                                else
                                {
                                    p1_pcurve_max_dn[ang] = pc_buf[0][ang+1];
                                    p2_pcurve_max_dn[ang] = pc_buf[1][ang+1];
                                }
                            }
                            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

                            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                            Lcd16x2_Cmd(LCD_CURSOR_OFF);

                            Display_Factory_Set_Menu();
                            menu_stat = FACTORY_SET_CODE_PAGE;
                        }
                    }
                }
            }
            if((calib_stat_bit == 0)&&(disp_refresh_cnt == 0))
            {
                disp_refresh_cnt = 500;
                sprintf(ubuf,"%04d",p1_pressure_cnt);
                Lcd16x2_Out(1,4,ubuf);                // P1
                sprintf(ubuf,"%04d",p2_pressure_cnt);
                Lcd16x2_Out(2,4,ubuf);                // P2
                TempDispBoomAngle = (bm_angle/10);

                sprintf(ubuf,"%04.1fﬂ ",((float)bm_angle)/10.0);
                Lcd16x2_Out(1,12,ubuf);
//                sprintf(ubuf,"%03d ",test_cntr);
//                Lcd16x2_Out(2,13,ubuf);
            }
            if(key.function == 1)
            {
                Display_Max_Calib_Angle_Menu();
                menu_stat = SET_MAX_ANGLE_PCURVE_PAGE;
                key.function = 0;
            } 
            break;
        }
        case VIEW_PCURVE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                while(key.inc_ftp == 1)
                {
                    Display_Pressure_Curve_Counts(0);
                    Delay_1ms(400);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    Display_Pressure_Curve_Counts(1);
                    Delay_1ms(400);
                }
                key.decrement = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                Lcd16x2_Cmd(LCD_CURSOR_OFF);
                Display_Factory_Set_Menu();
                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
    }
}




