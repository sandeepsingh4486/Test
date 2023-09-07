
#include "main.h"


/*============================================================================*/
/*
 * Function      : Display_Duty_Hint_MainScreen.
 * Description   : Used to display duty hint on display.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Duty_Hint_MainScreen(void)
{
    char Line_1[20],Line_2[20];
    uint16_t TempCount,TempCount1;
    
    flash_page_addr = ((uint32_t)lc_duty_hint_page_s-1)*256 + (((uint32_t)sys.para.duty-1)*32) + flash_memory_offset;
    
    memset(Line_1,0,sizeof(Line_1));
    memset(Line_2,0,sizeof(Line_2));
    for(TempCount=0; TempCount<16; TempCount++)
    {
        Line_1[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
    }
    
    for(TempCount1=0, TempCount=16; TempCount<32;TempCount1++,TempCount++)
    {
        Line_2[TempCount1] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
    }
    
    draw_hollow_rect(ILI9341_BROWN,8,35,133,75);
    draw_hollow_rect(ILI9341_BROWN,9,36,132,74);
    color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
    
    LCDPutStr(Line_1,12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(Line_2,12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
}


/*============================================================================*/
/*
 * Function      : change_Mode.
 * Description   : Used to change mode for NX360 crane.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void change_Mode(void)
{
    color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
    if(SlewMode == 0)
	{
        LCDPutStr("PICK&CARRY MODE",12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
	}
	else if(SlewMode == 1)
	{
        LCDPutStr("   SLEW MODE   ",12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
	}
	else
	{
        
	}
    
    LCDPutStr("SLEW PIN:",25,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
    
    if(!Slew_CAN)
    {
        LCDPutChar('0',100,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
    }
	else
	{
        LCDPutChar('1',100,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
    }
    Delay_1ms(1500);
}

/*============================================================================*/
/*
 * Function      : TFT32_Gui.
 * Description   : Used to handle GUI.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void TFT32_Gui(void)
{
    uint16_t Page_count=0,TotalNoPageRecive=0,TempCount,temp_data3,temp_data4;
    uint8_t password=0,pw_fail=0,slen=0,chk_arr,ang,unique_cntr;
    char ubuf[50];
    uint32_t _add=ONE_SECTOR_SIZE;
    
    switch(menu_stat)
    {
        case DEFAULT_PAGE:
        {
            if((key.function == 1)||(key.func_ftp == 1))
            {
                System_Setup_Screen();
                menu_stat = SYSTEM_SETUP_PAGE;
                key.function = 0;
                calib_mode = 1;
                ui_key = 1;
                Delay_1ms(500); 
            }
//            else if((key.bypass == 1)&&(condition))
//            {
//                LCDPutStr("  Bypass Mode   ",12,41,SMALL,ILI9341_RED, ILI9341_NAVY);
//                LCDPutStr("   Activated    ",12,59,SMALL,ILI9341_RED, ILI9341_NAVY);
//                Delay_1ms(1500);
//                Display_Duty_Hint_MainScreen();
//            }
            else if((key.duty == 1)&&(sys.para.duty_select_stat_bit))
            {
                if(sys.para.rig_duty_bit == 0)  prv_duty = sys.para.duty;
                
                while(key.duty_ftp == 1)
                {
                    if((sys.para.Select_System != PALFINGER_KNUCKLE_BOOM)&&(sys.para.Select_System != FORK_LIFT)&&
                       (sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
                    {
                        if(prv_duty <= lc_total_duty)
                        {
                            sys.para.rig_duty_bit = 0;
                            prv_duty++;
                            
                            if(prv_duty == 1)
                            {
                                sys.para.duty = prv_duty;
                                
                                Default_Main_Screen_Display();
                            }
                            else if(prv_duty <= lc_total_duty)
                            {
                                sprintf(ubuf,"%03d",prv_duty);
                                LCDPutStr(ubuf,70,13, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
                                sys.para.duty = prv_duty;
                                Display_Duty_Hint_MainScreen();
                                Delay_1ms(1000);
                            }
                            else
                            {
                                sys.para.rig_duty_bit = 1;                                
                                sprintf(ubuf,"%03d",prv_duty);
                                LCDPutStr(ubuf,70,13, XLARGE, ILI9341_RED, ILI9341_NAVY);
                                Delay_1ms(1500);
                                
                                prv_duty = 0;
                                color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
                                color_lcd_draw_rectangle(ILI9341_NAVY,6,45,313,195);
                                LCDPutStr("SLI INACTIVE",95,90,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
                                LCDPutStr("RIGGING DUTY",95,150,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
                                Delay_1ms(1500);
                            }
                        }
                    }
                    else if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                    {
                        color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
//                        sprintf(ubuf,"K.Angle=%02d",(Knbm_angle/10));
                        LCDPutStr("Fixed Len:",15,39,MEDIUM,ILI9341_WHITE, ILI9341_NAVY);
                        sprintf(ubuf,"%04.1fM",((float)JibLength)/10.0); 
                        LCDPutStr(ubuf,36,57,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                        Delay_1ms(2000);
                        Display_Duty_Hint_MainScreen();
                    }
                }
            }
            else if(key.increment == 1)
            {
                if((sys.para.Select_System==REGULAR_SYSTEM)||(sys.para.Select_System==FORK_LIFT)||(sys.para.Select_System==TMC_MANBASKET)||
                   (sys.para.Select_System==TMC_MANBASKET2)||(sys.para.Select_System==PALFINGER_KNUCKLE_BOOM)||(sys.para.Select_System== ACE_NX360)||
                   (sys.para.Select_System==TIL_PIXEF_TELE_PNC)||(sys.para.Select_System==PNC_FORK)||(sys.para.Select_System==WHITELINE_ESCORTS))
                {
                    color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
                    if(art_ip_bit)
                    {
                        if(sys.para.Select_System == ACE_NX360)
                            sprintf(ubuf,"Table No:%04d",duty_table);
                        else 
                            sprintf(ubuf,"Table No:%04d",lc_art_dty_tbl+duty_table-1);
                    }
                    else
                    {
//                        art_dty_tbl = 0;
                        sprintf(ubuf,"Table No:%04d",duty_table);
                    }
                    LCDPutStr(ubuf,12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    sprintf(ubuf,"LNL=%03d HNLZ=%03d",LowNlzRad,HighNlzRad);
                    LCDPutStr(ubuf,12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(2000);
                    Display_Duty_Hint_MainScreen();
                }
            }
            else if(key.decrement == 1)
            {
                if(sys.para.Select_System==WHITELINE_ESCORTS)
                {
                    color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
                    sprintf(ubuf,"F.Tilt X:%02d Y:%02d",TiltAngle_1_X,TiltAngle_1_Y);
                    LCDPutStr(ubuf,12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    
                    sprintf(ubuf,"R.Tilt X:%02d Y:%02d",TiltAngle_2_X,TiltAngle_2_Y);
                    LCDPutStr(ubuf,12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(2000);
                    Display_Duty_Hint_MainScreen();
                }
                else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                {
                    color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
                    sprintf(ubuf,"   TILTX=%02d     ",TiltAngle_1_X);
                    LCDPutStr(ubuf,12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    sprintf(ubuf,"   TILTY=%02d     ",TiltAngle_1_Y);
                    LCDPutStr(ubuf,12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(2000);
                    Display_Duty_Hint_MainScreen();                   
                }
            }
            else if(key.enter == 1)
            {
                if(sys.para.Select_System == ACE_NX360)
                {
                    SlewMode = !SlewMode;
                    change_Mode();
                    while(key.entr_ftp == 1) 
                    {
//                        CAN_Receive();
                        if(!Slew_CAN)
                            LCDPutChar('0',100,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                        else
                            LCDPutChar('1',100,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                        Delay_1ms(500);
                    }
                    Delay_1ms(2000);
                    Display_Duty_Hint_MainScreen();
                }
                else if((sys.para.Select_System == WHITELINE_ESCORTS)||(sys.para.Select_System == TMC_MANBASKET)||
                        (sys.para.Select_System == TMC_MANBASKET2))
                {
                    color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
                    sprintf(ubuf,"  HEIGHT:%04.1fM  ",((float)(HookHight))/10.0);                    
                    LCDPutStr(ubuf,12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    sprintf(ubuf,"HEIGHT LMT:%04.1fM",((float)sys.para.Max_BLength)/10.0);
                    LCDPutStr(ubuf,12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(2000);
                    Display_Duty_Hint_MainScreen();
                }
                else if(sys.para.Select_System == FORK_LIFT)
                {
                    color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
                    sprintf(ubuf,"MN:%04.1f  MC:%04d",((float)sys.para.cal_len_min)/10.0,sys.para.cal_len_min_cnt);
                    LCDPutStr(ubuf,12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    sprintf(ubuf,"MX:%04.1f  XC:%04d",((float)sys.para.cal_len_max)/10.0,sys.para.cal_len_max_cnt);
                    LCDPutStr(ubuf,12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(2000);
                    Display_Duty_Hint_MainScreen();
                }
            }
            key.duty = 0;
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
                color_lcd_draw_rectangle(ILI9341_GREEN,30,135,165,175);
                LCDPutStr("ESC:QUIT",50,150,XLARGE,ILI9341_WHITE, ILI9341_GREEN);
                menu_stat = DEFAULT_PAGE;
                
                Default_Main_Screen_Display();
                
                if((disp_error&0x02) == 0)  Calc_Parameter_Factors();
                key.function = 0;
                calib_mode = 0;
                ui_key = 0;
                Delay_1ms(500);
            }
            else if(key.enter == 1)
            {
                color_lcd_draw_rectangle(ILI9341_GREEN,175,135,295,175);
                LCDPutStr("ENT:SEL",195,150,XLARGE,ILI9341_WHITE, ILI9341_GREEN);
                Delay_1ms(200);
                
                mv.menu_cnt = 1;
                TFTDisplay_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.enter = 0;
            }
            key.duty = 0;
            key.increment = 0;
            key.decrement = 0;
            key.bypass = 0;
            break;
        }
        case SELECT_MENU_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                key.increment = 0;
                while(key.inc_ftp == 1)
                {
                    mv.menu_cnt--;
                    if(mv.menu_cnt < mv.min)  mv.menu_cnt = mv.max;
                    
                    Highlight_Single_Row(0,mv.menu_cnt);
                    Delay_1ms(600);
                }
            }
            else if(key.decrement == 1)        // DEC Key
            {                
                key.decrement = 0;
                while(key.dec_ftp == 1)
                {
                    mv.menu_cnt++;
                    if(mv.menu_cnt > mv.max)  mv.menu_cnt = mv.min;
                    
                    Highlight_Single_Row(1,mv.menu_cnt);
                    Delay_1ms(600);
                }
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((mv.menu_cnt == OPERATOR_VIEW_MENU)||(mv.menu_cnt == OPERATOR_SET_MENU))
                {
                    if(mv.menu_cnt == OPERATOR_VIEW_MENU)
                    {
                        mv.operator_view = 1;
                        TFTDisplay_Operator_View_Menu(0);
                        menu_stat = OPERATOR_VIEW_PAGE;
                    }
                    else
                    {
                        mv.operator_set = 1;
                        TFTDisplay_Operator_Setcode_Menu(0);
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
                        common_byte = 2;
                        common_long = password;
                        sprintf(ubuf,"%02d",password);
                        slen = strlen(ubuf)*13;
                        cursX = 230;
                        
                        if(mv.menu_cnt == SUPERVISOR_SET_MENU)
                        {
                            cursY = 127;                        
                            valX = cursX;
                            valY = cursY;

                            LCDPutStr(ubuf,valX,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        }
                        else if(mv.menu_cnt == SITE_SET_MENU)
                        {
                            cursY = 163;                        
                            valX = cursX;
                            valY = cursY;

                            LCDPutStr(ubuf,valX,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        }
                        else if(mv.menu_cnt == FACTORY_SET_MENU)
                        {
                            cursY = 197;                        
                            valX = cursX;
                            valY = cursY;

                            LCDPutStr(ubuf,valX,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        }
                        color_lcd_draw_rectangle(ILI9341_WHITE,cursX+7,cursY+11,cursX+14,cursY+12);
                        						
                        menu_stat = PASSWORD_PAGE;
                    }
                    else if(mv.menu_cnt == SUPERVISOR_SET_MENU)
                    {
                        mv.supervisor_set = 1;
                        TFTDisplay_Supervisor_Set_Menu(0);                        
                        menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    }
                    else if(mv.menu_cnt == SITE_SET_MENU)
                    {
                        mv.site_set = 1;
                        TFTDisplay_Site_Set_Menu(0);
                        menu_stat = SITE_SET_CODE_PAGE;
                    }
                    else if(mv.menu_cnt == FACTORY_SET_MENU)
                    {
                        mv.factory_set = 1;
                        TFTDisplay_Factory_Set_Menu(0);
                        menu_stat = FACTORY_SET_CODE_PAGE;
                    }
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                System_Setup_Screen();
                menu_stat = SYSTEM_SETUP_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            key.duty = 0;            
            key.bypass = 0;
            break;
        }
        case PASSWORD_PAGE:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,cursX,cursY+11,cursX+14,cursY+12);
                if(pos_t == 0) {pos_t = 1;color_lcd_draw_rectangle(ILI9341_WHITE,cursX,cursY+11,cursX+7,cursY+12);}
                else           {pos_t = 0;color_lcd_draw_rectangle(ILI9341_WHITE,cursX+7,cursY+11,cursX+14,cursY+12);}
                
                key.duty = 0;            
                key.bypass = 0;
            }
            else if((key.increment == 1)||(key.decrement == 1))
            {
                if(key.increment == 1)  Modify_System_Parameter(2,INC_DATA,pos_t,&common_long);
                else                    Modify_System_Parameter(2,DEC_DATA,pos_t,&common_long);
                
                sprintf(ubuf,"%02d",(uint8_t)common_long);
                LCDPutStr(ubuf,valX,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                
                key.increment = 0;            
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                password = (uint8_t)common_long;
                if(mv.menu_cnt == SUPERVISOR_SET_MENU)
                {
                    if(password == 11)
                    {
                        pw_fail = 0;
                        mv.supervisor_set = 1;
                        TFTDisplay_Supervisor_Set_Menu(0);
                        menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    }
                    else
                    {
                        pw_fail = 1;
                        LCDPutStr("FAIL",valX-7,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        color_lcd_draw_rectangle(ILI9341_NAVY,cursX-14,cursY+11,cursX+21,cursY+12);
                        Delay_1ms(1000);
                        LCDPutStr("    ",valX-7,valY,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        LCDPutStr(" 00 ",valX-7,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        password = 0;                        
                        color_lcd_draw_rectangle(ILI9341_WHITE,cursX+7,cursY+11,cursX+14,cursY+12);
                    }
                }
                else if(mv.menu_cnt == SITE_SET_MENU)
                {
                    if(password == 22)
                    {
                        pw_fail = 0;
                        mv.site_set = 1;
                        TFTDisplay_Site_Set_Menu(0);
                        menu_stat = SITE_SET_CODE_PAGE;
                    }
                    else
                    {
                        pw_fail = 1;
                        LCDPutStr("FAIL",valX-7,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        color_lcd_draw_rectangle(ILI9341_NAVY,cursX-14,cursY+11,cursX+21,cursY+12);
                        Delay_1ms(1000);
                        LCDPutStr("    ",valX-7,valY,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        LCDPutStr(" 00 ",valX-7,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        password = 0;                        
                        color_lcd_draw_rectangle(ILI9341_WHITE,cursX+7,cursY+11,cursX+14,cursY+12);
                    }
                }
                else if(mv.menu_cnt == FACTORY_SET_MENU)
                {
                    if(password == 84)
                    {
                        pw_fail = 0;
                        mv.factory_set = 1;
                        TFTDisplay_Factory_Set_Menu(0);
                        menu_stat = FACTORY_SET_CODE_PAGE;
                    }
                    else
                    {
                        pw_fail = 1;
                        LCDPutStr("FAIL",valX-7,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        color_lcd_draw_rectangle(ILI9341_NAVY,cursX-14,cursY+11,cursX+21,cursY+12);
                        Delay_1ms(1000);
                        LCDPutStr("    ",valX-7,valY,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        LCDPutStr(" 00 ",valX-7,valY,SMALL,ILI9341_WHITE,ILI9341_NAVY);
                        password = 0;                        
                        color_lcd_draw_rectangle(ILI9341_WHITE,cursX+7,cursY+11,cursX+14,cursY+12);
                    }
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTDisplay_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPERATOR_VIEW_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                key.increment = 0;
                while(key.inc_ftp == 1)
                {
                    mv.operator_view--;
                    if(mv.operator_view < mv.min)  mv.operator_view = mv.max;
                    
                    TFTSelect_Operator_View_Menu(0);
                    Delay_1ms(600);
                }
            }
            else if(key.decrement == 1)        // DEC Key
            {                
                key.decrement = 0;
                while(key.dec_ftp == 1)
                {
                    mv.operator_view++;
                    if(mv.operator_view > mv.max)  mv.operator_view = mv.min;
                    
                    TFTSelect_Operator_View_Menu(1);
                    Delay_1ms(600);
                }
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((mv.operator_view >= 1)&&(mv.operator_view <= 15))       //V1.17.3
                {
                    TFTOperator_Viewing();
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTDisplay_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPERATOR_VIEW_PAGE2:
        {
            if(mv.operator_view == 1)
                TFTOperator_View_Pres_Len_Ang_Cnts(sys.para.pressure_p1_chann,sys.para.pressure_p2_chann,sys.para.bm_length_chann,sys.para.main_ang_chann,sys.para.bm_angle_chann,p1_pressure_cnt,p2_pressure_cnt,len_adc_cnt,Main_ang_adc_cnt,ang_adc_cnt,1);
            else if(mv.operator_view == 2)
                TFTOperator_View_Tilt_ADC_Cnts(1);
            else if(mv.operator_view == 3)
                TFTOperator_View_OTG_ADC_Cnts(1);
            else if(mv.operator_view == 4)
                TFTOperator_View_Loadcell_Cnts(1);
            
            if(key.enter == 1)        // ENTR Key         V1.17.1
            {
                if((mv.operator_view ==10))
                {
                    TFTOperator_View_CraneDimensions(1);                        //V1.17.1
                }
                key.enter = 0;
            }
            
            if((key.function == 1)||(key.func_ftp == 1))         // FUNC Key
            {
                TFTCommon_OperatorVw_Escape_Function();
                menu_stat = OPERATOR_VIEW_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            key.duty = 0;
            key.bypass = 0;
            key.increment = 0;
            key.decrement = 0;
            key.enter = 0;
            break;
        }
        case VIEW_PC_PAGE1:
        {
            if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTCommon_OperatorVw_Escape_Function();
                menu_stat = OPERATOR_VIEW_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            else if(key.enter == 1)        // ENTR Key
            {
                temp_duty_indx = (uint8_t)common_long;
                
                if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
                {
                    length_array_ptr = ((temp_duty_indx-1)*5);
                    
                    mv.max = (length_array_ptr + (sys.para.duty_type[temp_duty_indx-1]-1));
                    mv.min = length_array_ptr;
                    
                    LCDPutStr("SEL CALIB. LEN:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    LCDPutStr("TOTAL CAL POINT",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                    draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                    color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                    draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
                    
                    len_calib_cnt = sys.para.duty_type[temp_duty_indx-1];
                    sprintf(ubuf,"%02d",len_calib_cnt);
                    slen = strlen(ubuf)*13;
                    cursX = 180+((100-slen)/2);
                    cursY = 165+20-8; 
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                    slen = strlen(ubuf)*13;
                    cursX = 180+((100-slen)/2);
                    cursY = 100+20-8; 
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
//                    sprintf(ubuf,"%02d %02d",mv.min,mv.max);
//                    LCDPutStr(ubuf,180,207,MEDIUM,ILI9341_BLACK,ILI9341_NAVY);
                    menu_stat = VIEW_PC_PAGE2;
                }
                key.enter = 0;
            }
            else
            {
                Inc_Dec_3Digit_Menu();
            }
            break;
        }
        case VIEW_PC_PAGE2:
        {
            if((key.bypass == 1)||(key.duty == 1))
            {
                key.bypass = 0;
                key.duty = 0;                
            }
            else if((key.increment == 1)||(key.decrement == 1))
            {
                if(key.increment == 1)
                {
                    while(key.inc_ftp == 1)
                    {
                        if(length_array_ptr < mv.max)
                        {
                            length_array_ptr++;
                        }
                        else
                        {
                            length_array_ptr = mv.min;
                        }  
                        if((len_calib_cnt >= 1) && (len_calib_cnt < 6))
                        {
                            sprintf(ubuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                            LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                        }
                        Delay_1ms(500);
                    }
                }
                else
                {
                    while(key.dec_ftp == 1)
                    {
                        if(length_array_ptr > mv.min)
                        {
                            length_array_ptr--;
                        }
                        else
                        {
                            length_array_ptr = mv.max;
                        }
                        if((len_calib_cnt >= 1) && (len_calib_cnt < 6))
                        {
                            sprintf(ubuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                            LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                        }
                        Delay_1ms(500);
                    }
                }
//                sprintf(ubuf,"%02d",length_array_ptr);
//                LCDPutStr(ubuf,100,207,MEDIUM,ILI9341_BLACK,ILI9341_NAVY);
                key.increment = 0;
                key.decrement = 0;
            }
            else if(key.enter == 1)
            {
                prv16_val1 = sys.para.length_array[length_array_ptr];    //Length
                //Take the length pointer at which calibration need to be done
                csv_ref_len = length_array_ptr%5;  //for calib lenth number 0 to 5
                
                pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + (((uint32_t)temp_duty_indx-1)*10*256) + csv_ref_len*512 + flash_memory_offset;
                
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
                
                CrtBoomAngle = 1;
                p1_cnt = pc_buf[0][0];
                p2_cnt = pc_buf[1][0];
                
//                Lcd_Cmd(LCD_CLEAR);
//                sprintf(ubuf,"P1:%04d   BA:%02dß",p1_cnt,CrtBoomAngle);
//                Lcd_Out(1,1,ubuf);
//                sprintf(ubuf,"P2:%04d         ",p2_cnt);
//                Lcd_Out(2,1,ubuf);

                color_lcd_draw_rectangle(ILI9341_NAVY,15,100,305,220);    //Clear Setting page
                    
                LCDPutStr("DUTY",10,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("P1 ADC",10,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);    
                LCDPutStr("P2 ADC",10,189,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

                LCDPutStr("LENGTH",163,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("BM ANG",163,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
//                LCDPutStr("P2 ADC",160,189,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

                color_lcd_draw_rectangle(ILI9341_WHITE,68,95,148,127);
                draw_hollow_rect(ILI9341_NAVY,70,97,146,125);
                color_lcd_draw_rectangle(ILI9341_WHITE,68,137,148,169); 
                draw_hollow_rect(ILI9341_NAVY,70,139,146,167);
                color_lcd_draw_rectangle(ILI9341_WHITE,68,179,148,211); 
                draw_hollow_rect(ILI9341_NAVY,70,167,146,209);

                color_lcd_draw_rectangle(ILI9341_WHITE,225,95,305,127);
                draw_hollow_rect(ILI9341_NAVY,227,97,303,125);
                color_lcd_draw_rectangle(ILI9341_WHITE,225,137,305,169);
                draw_hollow_rect(ILI9341_NAVY,227,139,303,167);
//                color_lcd_draw_rectangle(ILI9341_WHITE,225,179,305,211);
//                draw_hollow_rect(ILI9341_NAVY,227,181,303,209);

                sprintf(ubuf,"%03d",temp_duty_indx);
                LCDPutStr(ubuf,88,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                sprintf(ubuf,"%04d",p1_cnt);
                LCDPutStr(ubuf,83,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                sprintf(ubuf,"%04d",p2_cnt);
                LCDPutStr(ubuf,83,189,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                sprintf(ubuf,"%04.1fM",((float)prv16_val1)/10.0);
                LCDPutStr(ubuf,232,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);                
                sprintf(ubuf,"%02d",CrtBoomAngle);
                LCDPutStr(ubuf,245,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Draw_Circle(275,147,2,ILI9341_NAVY);
                menu_stat = VIEW_PC_PAGE3;
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTCommon_OperatorVw_Escape_Function();
                menu_stat = OPERATOR_VIEW_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case VIEW_PC_PAGE3:
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
                    if(CrtBoomAngle < 90) CrtBoomAngle++;
                    else                  CrtBoomAngle = 1;
                    
//                    color_lcd_draw_rectangle(ILI9341_WHITE,71,140,145,166);                     
//                    color_lcd_draw_rectangle(ILI9341_WHITE,71,182,145,208);
                    sprintf(ubuf,"%04d",pc_buf[0][CrtBoomAngle-1]);
                    LCDPutStr(ubuf,83,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    sprintf(ubuf,"%04d",pc_buf[1][CrtBoomAngle-1]);
                    LCDPutStr(ubuf,83,189,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    sprintf(ubuf,"%02d",CrtBoomAngle);
                    LCDPutStr(ubuf,245,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(400);
                }
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                while(key.dec_ftp == 1)
                {
                    if(CrtBoomAngle > 1) CrtBoomAngle--;
                    else                 CrtBoomAngle = 90;
                    
//                    color_lcd_draw_rectangle(ILI9341_WHITE,71,140,145,166);                     
//                    color_lcd_draw_rectangle(ILI9341_WHITE,71,182,145,208);
                    sprintf(ubuf,"%04d",pc_buf[0][CrtBoomAngle-1]);
                    LCDPutStr(ubuf,83,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    sprintf(ubuf,"%04d",pc_buf[1][CrtBoomAngle-1]);
                    LCDPutStr(ubuf,83,189,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    sprintf(ubuf,"%02d",CrtBoomAngle);
                    LCDPutStr(ubuf,245,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(400);
                }
                key.decrement = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTCommon_OperatorVw_Escape_Function();
                menu_stat = OPERATOR_VIEW_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPERATOR_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                key.increment = 0;
                while(key.inc_ftp == 1)
                {
                    mv.operator_set--;
                    if(mv.operator_set < mv.min)  mv.operator_set = mv.max;
                    
                    TFTSelect_Operator_Setcode_Menu(0);
                    Delay_1ms(600);
                }
            }
            else if(key.decrement == 1)        // DEC Key
            {
                key.decrement = 0;
                while(key.dec_ftp == 1)
                {
                    mv.operator_set++;
                    if(mv.operator_set > mv.max)  mv.operator_set = mv.min;
                    
                    TFTSelect_Operator_Setcode_Menu(1);
                    Delay_1ms(600);
                }
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((mv.operator_set >= 1)&&(mv.operator_set <= 3))
                {
                    menu_stat = OPERATOR_SET_PAGE;
                    TFTDisplay_Operator_Settings();
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTDisplay_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case OPERATOR_SET_PAGE:
        {
            TFT_Modify_Operator_Settings();
            break;
        }
        case SUPERVISOR_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                key.increment = 0;
                while(key.inc_ftp == 1)
                {
                    mv.supervisor_set--;
                    if(mv.supervisor_set < mv.min)  mv.supervisor_set = mv.max;
                    
                    TFTSelect_Supervisor_Setcode_Menu(0);
                    Delay_1ms(600);
                }
            }
            else if(key.decrement == 1)        // DEC Key
            {
                key.decrement = 0;
                while(key.dec_ftp == 1)
                {
                    mv.supervisor_set++;
                    if(mv.supervisor_set > mv.max)  mv.supervisor_set = mv.min;
                    
                    TFTSelect_Supervisor_Setcode_Menu(1);
                    Delay_1ms(600);
                }
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((mv.supervisor_set >= 1)&&(mv.supervisor_set <= 60))
                {
                    menu_stat = SUPERVISOR_SET_PAGE;
                    TFTDisplay_Supervisor_Settings();
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTDisplay_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SUPERVISOR_SET_PAGE:
        {
            TFT_Modify_Supervisor_Settings();
            break;
        }
        case HOOK_LOAD_CALIB_PAGE1:         //Select duty
        {
//            if(disp_refresh_cnt == 0)
//            {
//                disp_refresh_cnt = 500;
//                
//                sprintf(ubuf,"%04.1f",((float)TotalBmLength)/10.0);           
//                slen = strlen(ubuf)*13;
//                cursX = 180+((100-slen)/2);
//                cursY = 100+20-8; 
//                pos_t = 0;
//                valX = cursX;
//                valY = cursY;            
//                LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//                
//                sprintf(ubuf,"%04.1fM",((float)bm_angle)/10.0);           
//                slen = strlen(ubuf)*13;
//                cursX = 180+((100-slen)/2);
//                cursY = 165+20-8; 
//                pos_t = 0;
//                valX = cursX;
//                valY = cursY;            
//                LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//            }
//            if(key.enter == 1)        // ENTR Key
//            {
//                Display_Min_Calib_Angle_Menu();
//                menu_stat = HOOK_LOAD_CALIB_PAGE2;
//                key.enter = 0;
//            }
//            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
//            {
//                menu_stat = HOOK_LOAD_CALIB_PAGE1;
//                Display_Calib_Hook_Load_Menu();
//                Calib_Hook_Load_Cursor_Position();
//                key.function = 0;
//                Delay_1ms(500);
//            }
            while(1)
            {
                if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFTCommon_Supervisor_Escape_Function();

                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    Delay_1ms(500);
                    break;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                    temp_duty_indx = (uint8_t)common_long;
                    
                    if((temp_duty_indx <= lc_total_duty)&&(temp_duty_indx > 0))
                    {
                        sys.para.duty = temp_duty_indx;
                        
                        length_array_ptr = ((temp_duty_indx-1)*5);

                        if(sys.para.duty_type[temp_duty_indx-1] > 5)
                        {
                            sys.para.duty_type[temp_duty_indx-1] = 1;
                        }
                        
                        mv.max = (length_array_ptr + (sys.para.duty_type[temp_duty_indx-1]-1));
                        mv.min = length_array_ptr;
                        
                        LCDPutStr("SEL CALIB. LEN:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        LCDPutStr("TOTAL CAL POINT",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        
                        color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                        draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                        color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                        draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
                        
                        len_calib_cnt = sys.para.duty_type[temp_duty_indx-1];
                        sprintf(ubuf,"%02d",len_calib_cnt);
                        slen = strlen(ubuf)*13;
                        cursX = 180+((100-slen)/2);
                        cursY = 165+20-8; 
                        pos_t = 0;
                        valX = cursX;
                        valY = cursY;
                        LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                        
                        sprintf(ubuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                        slen = strlen(ubuf)*13;
                        cursX = 180+((100-slen)/2);
                        cursY = 100+20-8; 
                        pos_t = 0;
                        valX = cursX;
                        valY = cursY;
                        LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                        
                        menu_stat = HOOK_LOAD_CALIB_PAGE2;
                        key.enter = 0;
                        break;
                    }
                }
                else
                {
                    Inc_Dec_2Digit_Menu();
                }
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE2:         //Select length
        {
            while(1)
            {
                if((key.bypass == 1)||(key.duty == 1))
                {
                    key.bypass = 0;
                    key.duty = 0;                
                }
                else if((key.increment == 1)||(key.decrement == 1))
                {
                    if(key.increment == 1)
                    {
                        while(key.inc_ftp == 1)
                        {
                            if(length_array_ptr < mv.max)
                            {
                                length_array_ptr++;
                            }
                            else
                            {
                                length_array_ptr = mv.min;
                            }  
                            if((len_calib_cnt >= 1) && (len_calib_cnt < 6))
                            {
                                sprintf(ubuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                                LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            Delay_1ms(500);
                        }
                    }
                    else
                    {
                        while(key.dec_ftp == 1)
                        {
                            if(length_array_ptr > mv.min)
                            {
                                length_array_ptr--;
                            }
                            else
                            {
                                length_array_ptr = mv.max;
                            }
                            if((len_calib_cnt >= 1) && (len_calib_cnt < 6))
                            {
                                sprintf(ubuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                                LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            Delay_1ms(500);
                        }
                    }
                    key.increment = 0;
                    key.decrement = 0;
                }
                else if(key.enter == 1)
                {
                    sys.para.duty = temp_duty_indx;
                    //Take the length pointer at which calibration need to be done
                    csv_ref_len = length_array_ptr%5;  //for calib lenth number 0 to 5

                    pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + (((uint32_t)temp_duty_indx-1)*10*256) + csv_ref_len*512 + flash_memory_offset;

                    pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                    pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector

                    pc_sector = pc_sector_quotient;
                    pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15
                    
                    sys.para.min_angle = 0;
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,15,100,280,210);    //Clear Setting page
                    
                    LCDPutStr("ENTER MIN ANGLE:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                    draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                    
                    sprintf(ubuf,"%02d",sys.para.min_angle);
                    slen = strlen(ubuf)*13;
                    cursX = 180+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;

                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    common_byte = 2;
                    common_long = sys.para.min_angle;    

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                    
                    key.enter = 0;
                    menu_stat = HOOK_LOAD_CALIB_PAGE3;
                    break;
                }
                else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFTCommon_Supervisor_Escape_Function();
                    
                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    Delay_1ms(500);
                    break;
                }
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE3:         //Set minimum angle
        {
            while(1)
            {
                if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFTCommon_Supervisor_Escape_Function();
                    
                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    Delay_1ms(500);
                    break;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                    sys.para.min_angle = (uint8_t)common_long;;
                    
                    sys.para.max_angle = 70;
                    
                    LCDPutStr("ENTER MAX ANGLE:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                    draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                    
                    sprintf(ubuf,"%02d",sys.para.max_angle);
                    slen = strlen(ubuf)*13;
                    cursX = 180+((100-slen)/2);
                    cursY = 100+20-8;
                    cursY = 100+20-8; 
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    
                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 2;
                    common_long = sys.para.max_angle;    
                    
                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                    
                    menu_stat = HOOK_LOAD_CALIB_PAGE4;
                    key.enter = 0;
                    break;
                }
                else
                {
                    Inc_Dec_2Digit_Menu();
                }
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE4:         //Set maximum angle
        {
            while(1)
            {
                Analog_Data_Read();
                
                if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFTCommon_Supervisor_Escape_Function();
                    
                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    Delay_1ms(500);
                    break;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                    sys.para.max_angle = (uint8_t)common_long;
                    color_lcd_draw_rectangle(ILI9341_NAVY,15,100,280,150);    //Clear Setting page
                    
                    if(bm_angle < ((sys.para.min_angle)*10))
                    {
                        LCDPutStr("PLEASE PRESS ENTR KEY TO",15,110,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                        LCDPutStr("START CALIBRTION!!!",48,140,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                        Delay_1ms(1000);
                        menu_stat = HOOK_LOAD_CALIB_PAGE6;
                    }
                    else
                    {
                        LCDPutStr("BRING THE BOOM DOWN TO",30,110,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                        LCDPutStr("START CALIBRTION!!!",48,140,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                        LCDPutStr("ANGLE:",75,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        color_lcd_draw_rectangle(ILI9341_WHITE,145,165,215,197);
                        draw_hollow_rect(ILI9341_NAVY,147,167,213,195);
                        Draw_Circle(208,175,2,ILI9341_NAVY);
                        Delay_1ms(1000);
                        menu_stat = HOOK_LOAD_CALIB_PAGE5;
                    }                    
                    key.enter = 0;
                    break;
                }
                else
                {
                    Inc_Dec_2Digit_Menu();
                }
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE5:         //Bring the boom down
        {
            while(1)
            {
                Analog_Data_Read();
                
                if((key.bypass == 1)||(key.duty == 1)||(key.increment == 1)||(key.decrement == 1)||(key.enter == 1))
                {
                    key.bypass = 0;
                    key.duty = 0;
                    key.increment = 0;
                    key.decrement = 0;
                    key.enter = 0;
                    key.function = 0;
                }
                else if(key.function == 1)
                {
                    TFTCommon_Supervisor_Escape_Function();
                    
                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    break;
                }
                if(disp_refresh_cnt == 0)
                {
                    disp_refresh_cnt = 500;
                    sprintf(ubuf,"%04.1f",((float)bm_angle)/10.0);
                    LCDPutStr(ubuf,153,175,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                }
                if(bm_angle < ((sys.para.min_angle)*10))
                {
                    LCDPutStr("PLEASE PRESS ENTR KEY TO",15,110,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    LCDPutStr("START CALIBRTION!!!",48,140,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    color_lcd_draw_rectangle(ILI9341_GREEN,145,165,215,197);
                    draw_hollow_rect(ILI9341_NAVY,147,167,213,195);
                    sprintf(ubuf,"%04.1f",((float)bm_angle)/10.0);
                    LCDPutStr(ubuf,153,175,XLARGE,ILI9341_WHITE,ILI9341_GREEN);
                    Delay_1ms(1000);
                    menu_stat = HOOK_LOAD_CALIB_PAGE6;
                    break;
                }
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE6:         //Press enter key to start calibration
        {
            while(1)
            {
                if((key.bypass == 1)||(key.duty == 1)||(key.increment == 1)||(key.decrement == 1)||(key.function == 1))
                {
                    key.bypass = 0;
                    key.duty = 0;
                    key.increment = 0;
                    key.decrement = 0;
                    key.function = 0;
                }
                else if(key.function == 1)
                {
                    TFTCommon_Supervisor_Escape_Function();
                    
                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    break;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                    color_lcd_draw_rectangle(ILI9341_NAVY,15,100,305,220);    //Clear Setting page
                    
                    LCDPutStr("DUTY",10,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    LCDPutStr("RANGE",10,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);    
                    LCDPutStr("ANGLE",10,189,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    
                    LCDPutStr("LENGTH",160,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    LCDPutStr("P1 ADC",160,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
                    LCDPutStr("P2 ADC",160,189,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,65,95,145,127);
                    draw_hollow_rect(ILI9341_NAVY,67,97,143,125);
                    color_lcd_draw_rectangle(ILI9341_WHITE,65,137,145,169); 
                    draw_hollow_rect(ILI9341_NAVY,67,139,143,167);
                    color_lcd_draw_rectangle(ILI9341_WHITE,65,179,145,211); 
                    draw_hollow_rect(ILI9341_NAVY,67,167,143,209);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,225,95,305,127);
                    draw_hollow_rect(ILI9341_NAVY,227,97,303,125);
                    color_lcd_draw_rectangle(ILI9341_WHITE,225,137,305,169);
                    draw_hollow_rect(ILI9341_NAVY,227,139,303,167);
                    color_lcd_draw_rectangle(ILI9341_WHITE,225,179,305,211);
                    draw_hollow_rect(ILI9341_NAVY,227,181,303,209);
                    
                    sprintf(ubuf,"%03d",temp_duty_indx);
                    LCDPutStr(ubuf,85,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    sprintf(ubuf,"%02d-%02d",sys.para.min_angle,sys.para.max_angle);
                    LCDPutStr(ubuf,72,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Draw_Circle(101,147,2,ILI9341_NAVY);
                    Draw_Circle(138,147,2,ILI9341_NAVY);
                    sprintf(ubuf,"%04.1f",((float)bm_angle)/10.0);
                    LCDPutStr(ubuf,80,189,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Draw_Circle(135,189,2,ILI9341_NAVY);
                    
                    sprintf(ubuf,"%04.1fM",((float)TotalBmLength)/10.0);
                    LCDPutStr(ubuf,232,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04d",p1_pressure_cnt);
                    LCDPutStr(ubuf,234,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04d",p2_pressure_cnt);
                    LCDPutStr(ubuf,234,189,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    key.enter = 0;
                    CrtBoomAngle = 0;
                    PrevBoomAngle = 0;
                    calib_stat_bit = 0;
                    test_cntr = 0;
                    memset(data_log_arr,0,sizeof(data_log_arr));
                    menu_stat = HOOK_LOAD_CALIB_PAGE7;
                    break;
                }
            }
            break;
        }
        case HOOK_LOAD_CALIB_PAGE7:         //Calibration started
        {
            while(1)
            {
                Analog_Data_Read();
                
                Calculate_Len_Radius();
                
                if(bm_angle >= ((sys.para.min_angle*10) + 4))
                {
                    CrtBoomAngle = (bm_angle/10);
                    
                    if(CrtBoomAngle >= PrevBoomAngle)
                    {
                        if((CrtBoomAngle-PrevBoomAngle) >= 1)
                        {
                            data_log_arr[CrtBoomAngle] = 1;
                            pc_buf[0][CrtBoomAngle] = p1_pressure_cnt;
                            pc_buf[1][CrtBoomAngle] = p2_pressure_cnt;
                            
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
                                
                                // True if DataLogArr[TestCntr] == 0 ....
                                while(!data_log_arr[test_cntr])
                                {
                                    test_cntr++;
                                }
                                min_log_angle = 0;
                                min_log_angle = test_cntr;
                                
                                color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
                                
                                LCDPutStr("MIN LOG ANGLE   :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                LCDPutStr("MAX LOG ANGLE   :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                
                                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                                color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                                draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
                                
                                sprintf(ubuf,"%03d",min_log_angle);
                                
                                slen = strlen(ubuf)*13;
                                cursX = 180+((100-slen)/2);
                                cursY = 100+20-8; 
                                pos_t = 0;
                                valX = cursX;
                                valY = cursY;

                                LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);                                
                                
                                test_cntr = 0;
                                test_cntr = sys.para.max_angle;
                                // True if DataLogArr[TestCntr] == 0 ....
                                while(!data_log_arr[test_cntr])
                                {
                                    test_cntr--;
                                }
                                max_log_angle = 0;
                                max_log_angle = test_cntr;
                                
                                sprintf(ubuf,"%03d",max_log_angle);
                                LCDPutStr(ubuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);                                
                                Delay_1ms(2000);
                                
                                // Can be Converted to Float ...............................
                                temp_data3 = pc_buf[0][min_log_angle];
                                temp_data4 = pc_buf[0][max_log_angle];

                                if((temp_data3 > temp_data4))
                                {
                                    f1 = ((temp_data3 - temp_data4)*1.0)/((max_log_angle - min_log_angle)*1.0);
                                }
                                else
                                {
                                    f1 = 0.0;
                                }

                                count_step_val_P1 = f1;                        //Float to integer
                                
                                if((f1-count_step_val_P1) > 0.6)        // Compaire after decimal value
                                {
                                    count_step_val_P1++;
                                }
                                
                                color_lcd_draw_rectangle(ILI9341_NAVY,5,100,310,210);
                                LCDPutStr("P1 STEP VALUE   :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                                
                                sprintf(ubuf,"%03d",count_step_val_P1);
                                slen = strlen(ubuf)*13;
                                cursX = 180+((100-slen)/2);
                                cursY = 100+20-8; 
                                pos_t = 0;
                                valX = cursX;
                                valY = cursY;
                                LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                Delay_1ms(2000);

                                if(sys.para.min_angle > 1)
                                {
                                    color_lcd_draw_rectangle(ILI9341_NAVY,5,100,310,150);
                                    // Filling Data For Angles between MinLogAngle & ZeroAngle.
                                    test_cntr = min_log_angle;
                                    
                                    if(test_cntr > 0)
                                    {
                                        color_lcd_draw_rectangle(ILI9341_WHITE,45,100,145,140);   
                                        draw_hollow_rect(ILI9341_NAVY,47,102,143,138);
                                        
                                        color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                                        draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                                        
                                        color_lcd_draw_rectangle(ILI9341_WHITE,45,180,145,220);  
                                        draw_hollow_rect(ILI9341_NAVY,47,182,143,218);
                                        
                                        color_lcd_draw_rectangle(ILI9341_WHITE,180,180,280,220);  
                                        draw_hollow_rect(ILI9341_NAVY,182,182,278,218);
                                    }
                                    while(test_cntr > 0)
                                    {
                                        p1_pressure_cnt = (pc_buf[0][test_cntr] + count_step_val_P1);
                                        p2_pressure_cnt = pc_buf[1][test_cntr];
                                        
                                        pc_buf[0][test_cntr-1] = p1_pressure_cnt;
                                        pc_buf[1][test_cntr-1] = p2_pressure_cnt;
                                        
                                        sprintf(ubuf,"P1:%04d",p1_pressure_cnt);
                                        LCDPutStr(ubuf,50,110,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        
                                        sprintf(ubuf,"P2:%04d",p2_pressure_cnt);
                                        LCDPutStr(ubuf,185,110,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        
                                        sprintf(ubuf,"BA:%03d",test_cntr);
                                        LCDPutStr(ubuf,50,190,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        
                                        LCDPutStr("=> 0 Deg",185,190,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        Delay_1ms(1500);
                                        
                                        test_cntr--;
                                    }
                                }
                                else
                                {
                                    LCDPutStr("NoDataMissed For ",35,150,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                    LCDPutStr("Low Angles       ",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                    Delay_1ms(2500);
                                }
                                
                                // Filling Data For Angles between MaxLogAngle & 90 Degrees.
                                if(sys.para.max_angle < 90)
                                {
                                    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
                                    
                                    test_cntr = max_log_angle;
                                    
                                    if(test_cntr < 90)
                                    {
                                        LCDPutStr("REMAINING ANGLES",56,70,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                                        color_lcd_draw_rectangle(ILI9341_WHITE,45,100,145,140);   
                                        draw_hollow_rect(ILI9341_NAVY,47,102,143,138);
                                        
                                        color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                                        draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                                        
                                        color_lcd_draw_rectangle(ILI9341_WHITE,45,180,145,220);  
                                        draw_hollow_rect(ILI9341_NAVY,47,182,143,218);
                                        
                                        color_lcd_draw_rectangle(ILI9341_WHITE,180,180,280,220);  
                                        draw_hollow_rect(ILI9341_NAVY,182,182,278,218);
                                    }
                                    while(test_cntr < 90)
                                    {
                                        p1_pressure_cnt = (pc_buf[0][test_cntr] - count_step_val_P1);
                                        p2_pressure_cnt = pc_buf[1][test_cntr];

                                        pc_buf[0][test_cntr+1] = p1_pressure_cnt;
                                        pc_buf[1][test_cntr+1] = p2_pressure_cnt;
                                        
                                        sprintf(ubuf,"P1:%04d",p1_pressure_cnt);
                                        LCDPutStr(ubuf,50,110,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        
                                        sprintf(ubuf,"P2:%04d",p2_pressure_cnt);
                                        LCDPutStr(ubuf,185,110,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        
                                        sprintf(ubuf,"BA:%03d",test_cntr);
                                        LCDPutStr(ubuf,50,190,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        
                                        LCDPutStr("=>90 Deg",185,190,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                                        Delay_1ms(150);
                                        
                                        test_cntr++;
                                    }
                                }
                                
                                color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
                                
                                LCDPutStr("Data Not Missed  ",35,100,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                LCDPutStr("For Any Angle... ",35,130,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

                                LCDPutStr("Calibration Done ",35,150,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                LCDPutStr("Successfully.1.. ",35,170,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                                Delay_1ms(2000);
                                
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
                                
                                //Save min and max angle to SPI Flash
                                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                                
                                TFTCommon_Supervisor_Escape_Function();
                                menu_stat = SUPERVISOR_SET_CODE_PAGE;
                                break;
                            }
                        }
                    }
                }
                if((calib_stat_bit == 0)&&(disp_refresh_cnt == 0))
                {
                    disp_refresh_cnt = 500;
                    sprintf(ubuf,"%04.1f",((float)bm_angle)/10.0);
                    LCDPutStr(ubuf,80,189,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04d",p1_pressure_cnt);
                    LCDPutStr(ubuf,234,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04.1fM",((float)TotalBmLength)/10.0);
                    LCDPutStr(ubuf,232,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04d",p2_pressure_cnt);
                    LCDPutStr(ubuf,234,189,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                }
                if((key.bypass == 1)||(key.duty == 1)||(key.increment == 1)||(key.decrement == 1)||(key.enter == 1))
                {
                    key.bypass = 0;
                    key.duty = 0;
                    key.increment = 0;
                    key.decrement = 0;
                    key.enter = 0;
                }
                else if(key.function == 1)
                {
                    TFTCommon_Supervisor_Escape_Function();
                    
                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    break;
                }
            }
            break;
        }
        case LEN_MPOINT_CALIBRATION_PAGE1:
        {
            while(1)
            {
                if((key.bypass == 1)||(key.duty == 1))
                {
                    key.bypass = 0;
                    key.duty = 0;
                }
                else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFTCommon_Supervisor_Escape_Function();

                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    Delay_1ms(500);
                    break;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                    LCDPutStr("EDIT POINT: ",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    
                    sprintf(ubuf,"%04.1f",((float)prv16_val1)/10.0);
                    slen = strlen(ubuf)*13;
                    cursX = 80+((100-slen)/2);
                    cursY = 167+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    pos_t = 0;
                    common_byte = 3;
                    common_long = prv16_val1;
                    cursX += common_byte*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                    menu_stat = LEN_MPOINT_CALIBRATION_PAGE2;
                    
                    key.enter = 0;
                    break;
                }
                else if((key.increment == 1)||(key.decrement == 1))
                {
                    if(key.increment == 1)
                    {
                        while(key.inc_ftp == 1)
                        {
                            if(prv8_val1 < sys.para.numof_len_cal)  prv8_val1++;
                            else                                    prv8_val1 = 1;
                            prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
                            prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
                            sprintf(ubuf,"%02d",prv8_val1);
                            LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            color_lcd_draw_rectangle(ILI9341_WHITE,85,177,150,197);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,157,297,176);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,199,297,218);
                            
                            if((prv16_val1 >= sys.para.bm_length_min)&&(prv16_val1 <= sys.para.bm_length_max))
                            {
                                sprintf(ubuf,"%04.1f",((float)prv16_val1)/10.0);
                                LCDPutStr(ubuf,97,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                                sprintf(ubuf,"%05lu",(uint32_t)prv16_val2);
                                LCDPutStr(ubuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                
                                LCDPutStr(" ----",234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            else
                            {
                                prv16_val1 = 0;
                                prv16_val2 = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][0] = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][1] = 0;
                                
                                LCDPutStr("ADD",115,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }                            
                            Delay_1ms(500);
                        }
                    }
                    else
                    {
                        while(key.dec_ftp == 1)
                        {
                            if(prv8_val1 > 1)   prv8_val1--;
                            else                prv8_val1 = sys.para.numof_len_cal;
                            prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
                            prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
                            sprintf(ubuf,"%02d",prv8_val1);                            
                            LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            color_lcd_draw_rectangle(ILI9341_WHITE,85,177,150,197);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,157,297,176);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,199,297,218);
                            if((prv16_val1 >= sys.para.bm_length_min)&&(prv16_val1 <= sys.para.bm_length_max))
                            {
                                sprintf(ubuf,"%04.1f",((float)prv16_val1)/10.0);
                                LCDPutStr(ubuf,97,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                                sprintf(ubuf,"%05lu",(uint32_t)prv16_val2);
                                LCDPutStr(ubuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                
                                LCDPutStr(" ----",234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            else
                            {
                                prv16_val1 = 0;
                                prv16_val2 = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][0] = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][1] = 0;
                                LCDPutStr("ADD",115,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            Delay_1ms(500);
                        }
                    }
                    key.increment = 0;
                    key.decrement = 0;
                }
            }
            break;
        }
        case LEN_MPOINT_CALIBRATION_PAGE2:
        {
            while(1)
            {
//                CAN_Receive();
                
                if((sys.para.Select_System != ACE_NX360)||(sys.para.Select_System != TMC_MANBASKET)||
                   (sys.para.Select_System != TMC_MANBASKET2))
                {
                    Parse_Uart_Data();
                }
                
                if(len_adc_cnt >= 600)
                    mm_len = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)*100;
                else
                    mm_len = 0;
                
                if(disp_refresh_cnt == 0)
                {
                    disp_refresh_cnt = 500;
                    color_lcd_draw_rectangle(ILI9341_WHITE,85,177,150,197);
                    color_lcd_draw_rectangle(ILI9341_WHITE,230,157,297,176);
                    color_lcd_draw_rectangle(ILI9341_WHITE,230,199,297,218);
                    
                    sprintf(ubuf,"%04.1f",((float)common_long)/10.0);
                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%05lu",(uint32_t)mm_len);
                    LCDPutStr(ubuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04d",len_adc_cnt);
                    LCDPutStr(ubuf,240,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                }
                
                if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFT_Length_MPoint_Menu();
                    
                    key.function = 0;
                    Delay_1ms(500);
                    break;
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
                        else
                        {
                            Do_Len_MPoint_Sorting(prv8_val1);
                        }
                        
                        SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

                        memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

                        Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                        SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                        
                        color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,221);    //Clear Setting page
                        LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                        Delay_1ms(1500);
                        color_lcd_draw_rectangle(ILI9341_NAVY,100,127,250,150);
                        
                        TFT_Length_MPoint_Menu();
                    }
                    key.enter = 0;
                    break;
                }
                else
                {
                    Inc_Dec_3Digit_1Decimal_Menu();
                }
            }
            break;
        }
        case FORK_PRESS_MINMAX_PAGE1:
        {
            while(1)
            {
                if((key.bypass == 1)||(key.duty == 1))
                {
                    key.bypass = 0;
                    key.duty = 0;
                }
                else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFTCommon_Supervisor_Escape_Function();

                    menu_stat = SUPERVISOR_SET_CODE_PAGE;
                    key.function = 0;
                    Delay_1ms(500);
                    break;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                    LCDPutStr("EDIT POINT: ",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    
                    sprintf(ubuf,"%04.1f",((float)prv16_val1)/10.0);
                    slen = strlen(ubuf)*13;
                    cursX = 80+((100-slen)/2);
                    cursY = 167+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    pos_t = 0;
                    common_byte = 3;
                    common_long = prv16_val1;
                    cursX += common_byte*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                    menu_stat = FORK_PRESS_MINMAX_PAGE2;
                    
                    key.enter = 0;
                    break;
                }
                else if((key.increment == 1)||(key.decrement == 1))
                {
                    if(key.increment == 1)
                    {
                        while(key.inc_ftp == 1)
                        {
                            if(prv8_val1 < sys.para.numof_calib_fork)  prv8_val1++;
                            else                                       prv8_val1 = 1;
                            
                            if(byt1 == 0)
                            {
                                prv16_val1 = sys.para.forkcalib_press_min[prv8_val1-1][0];       //Load value
                                prv16_val2 = sys.para.forkcalib_press_min[prv8_val1-1][1];       //Load counts
                            }
                            else
                            {
                                prv16_val1 = sys.para.forkcalib_press_max[prv8_val1-1][0];       //Load value
                                prv16_val2 = sys.para.forkcalib_press_max[prv8_val1-1][1];       //Load counts
                            }
                            common_short = sys.para.fork_len_region[prv8_val1-1];
                            
                            sprintf(ubuf,"%02d",prv8_val1);
                            LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            color_lcd_draw_rectangle(ILI9341_WHITE,85,177,150,197);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,157,297,176);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,199,297,218);
                            
                            if((prv16_val1 >= 0)&&(prv16_val1 <= lc_max_capacity))
                            {
                                sprintf(ubuf,"%04.1f",((float)prv16_val1)/10.0);
                                LCDPutStr(ubuf,97,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutChar('T',158,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                                if(sys.para.bpk_method_stat_bit == 0)
                                {
                                    sprintf(ubuf,"%04.1fM",((float)common_short)/10.0);
                                    LCDPutStr(ubuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                }
                                else
                                {
                                    sprintf(ubuf,"%d",art_ip_bit);
                                    LCDPutStr(ubuf,260,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                }

                                sprintf(ubuf,"%05lu",(uint32_t)prv16_val2);
                                LCDPutStr(ubuf,234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            else
                            {
                                prv16_val1 = 0;
                                prv16_val2 = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][0] = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][1] = 0;
                                
                                LCDPutStr("ADD",115,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }                            
                            Delay_1ms(500);
                        }
                    }
                    else
                    {
                        while(key.dec_ftp == 1)
                        {
                            if(prv8_val1 > 1)   prv8_val1--;
                            else                prv8_val1 = sys.para.numof_calib_fork;
                            
                            if(byt1 == 0)
                            {
                                prv16_val1 = sys.para.forkcalib_press_min[prv8_val1-1][0];       //Load value
                                prv16_val2 = sys.para.forkcalib_press_min[prv8_val1-1][1];       //Load counts
                            }
                            else
                            {
                                prv16_val1 = sys.para.forkcalib_press_max[prv8_val1-1][0];       //Load value
                                prv16_val2 = sys.para.forkcalib_press_max[prv8_val1-1][1];       //Load counts
                            }
                            common_short = sys.para.fork_len_region[prv8_val1-1];
                            
                            sprintf(ubuf,"%02d",prv8_val1);
                            LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            color_lcd_draw_rectangle(ILI9341_WHITE,85,177,150,197);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,157,297,176);
                            color_lcd_draw_rectangle(ILI9341_WHITE,230,199,297,218);
                            
                            if((prv16_val1 >= 0)&&(prv16_val1 <= lc_max_capacity))
                            {
                                sprintf(ubuf,"%04.1f",((float)prv16_val1)/10.0);
                                LCDPutStr(ubuf,97,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutChar('T',158,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                if(sys.para.bpk_method_stat_bit == 0)
                                {
                                    sprintf(ubuf,"%04.1fM",((float)common_short)/10.0);
                                    LCDPutStr(ubuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                }
                                else
                                {
                                    sprintf(ubuf,"%d",art_ip_bit);
                                    LCDPutStr(ubuf,260,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                }

                                sprintf(ubuf,"%05lu",(uint32_t)prv16_val2);
                                LCDPutStr(ubuf,234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            else
                            {
                                prv16_val1 = 0;
                                prv16_val2 = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][0] = 0;
                                sys.para.multipt_lcalib[prv8_val1-1][1] = 0;
                                
                                LCDPutStr("ADD",115,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                                LCDPutStr(" ----",234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                            }
                            Delay_1ms(500);
                        }
                    }
                    key.increment = 0;
                    key.decrement = 0;
                }
            }
            break;
        }
        case FORK_PRESS_MINMAX_PAGE2:
        {
            while(1)
            {
                Parse_Uart_Data();
                
                Fork_Height();
                
                if(disp_refresh_cnt == 0)
                {
                    disp_refresh_cnt = 500;
                    color_lcd_draw_rectangle(ILI9341_WHITE,85,177,150,197);
                    color_lcd_draw_rectangle(ILI9341_WHITE,230,157,297,176);
                    color_lcd_draw_rectangle(ILI9341_WHITE,230,199,297,218);
                    
                    sprintf(ubuf,"%04.1f",((float)common_long)/10.0);
                    LCDPutStr(ubuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    if(sys.para.bpk_method_stat_bit == 0)
                    {
                        sprintf(ubuf,"%04.1fM",((float)TotalBmLength)/10.0);
                        LCDPutStr(ubuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    }
                    else
                    {
                        sprintf(ubuf,"%d",art_ip_bit);
                        LCDPutStr(ubuf,260,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    }

                    sprintf(ubuf,"%05lu",(uint32_t)p1_pressure_cnt);
                    LCDPutStr(ubuf,234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                }
                
                if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    TFT_Forklift_Load_MPoint_Menu();
                    
                    key.function = 0;
                    Delay_1ms(500);
                    break;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                    if(common_long <= lc_max_capacity)
                    {
                        if(byt1 == 0)
                        {
                            sys.para.forkcalib_press_min[prv8_val1-1][0] = (uint16_t)common_long;
                            sys.para.forkcalib_press_min[prv8_val1-1][1] = p1_pressure_cnt; 
                            sys.para.fork_len_region[prv8_val1-1] = TotalBmLength;
                        }
                        else
                        {
                            sys.para.forkcalib_press_max[prv8_val1-1][0] = (uint16_t)common_long;
                            sys.para.forkcalib_press_max[prv8_val1-1][1] = p1_pressure_cnt;
                        }
                        
                        SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

                        memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

                        Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                        SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                        
                        color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,221);    //Clear Setting page
                        LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                        Delay_1ms(1500);
                        color_lcd_draw_rectangle(ILI9341_NAVY,100,127,250,150);
                        
                        TFT_Forklift_Load_MPoint_Menu();
                    }
                    key.enter = 0;
                    break;
                }
                else
                {
                    Inc_Dec_3Digit_1Decimal_Menu();
                }
            }
            break;
        }
        case SITE_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                key.increment = 0;
                while(key.inc_ftp == 1)
                {
                    mv.site_set--;
                    if(mv.site_set < mv.min)  mv.site_set = mv.max;
                    
                    TFTSelect_Site_Setcode_Menu(0);
                    Delay_1ms(600);
                }
            }
            else if(key.decrement == 1)        // DEC Key
            {
                key.decrement = 0;
                while(key.dec_ftp == 1)
                {
                    mv.site_set++;
                    if(mv.site_set > mv.max)  mv.site_set = mv.min;
                    
                    TFTSelect_Site_Setcode_Menu(1);
                    Delay_1ms(600);
                }
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((mv.site_set >= 1)&&(mv.site_set <= 33))
                {
                    menu_stat = SITE_SET_PAGE;
                    TFTDisplay_Site_Settings();
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTDisplay_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case SITE_SET_PAGE:
        {
            TFT_Modify_Site_Settings();
            break;
        }
        case VIEW_DUTY_TABLE_PAGE1:
        {
            while(1)
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
                    LCDPutStr(ubuf,92,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Get_Radius_Capacity(prv16_val1,common_byte-1);
                    
                    sprintf(ubuf,"%04.1fM",((float)vrad)/10.0);
                    LCDPutStr(ubuf,233,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    sprintf(ubuf,"%04.1fT",((float)vcapa)/10.0);
                    LCDPutStr(ubuf,233,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    key.increment = 0;
                    key.decrement = 0;
                }
                else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
                    
                    TFT_View_Duty_Table_Menu();
                    
                    menu_stat = SITE_SET_PAGE;

                    Delay_1ms(500);
                    key.function = 0;
                    break;
                }
                key.bypass = 0;
                key.duty = 0;
                key.enter = 0;
            }
            break;
        }
        case FACTORY_SET_CODE_PAGE:
        {
            if(key.increment == 1)        // INC Key
            {
                key.increment = 0;
                while(key.inc_ftp == 1)
                {
                    mv.factory_set--;
                    if(mv.factory_set < mv.min)  mv.factory_set = mv.max;
                    
                    TFTSelect_Factory_Setcode_Menu(0);
                    Delay_1ms(600);
                }
            }
            else if(key.decrement == 1)        // DEC Key
            {
                key.decrement = 0;
                while(key.dec_ftp == 1)
                {
                    mv.factory_set++;
                    if(mv.factory_set > mv.max)  mv.factory_set = mv.min;
                    
                    TFTSelect_Factory_Setcode_Menu(1);
                    Delay_1ms(600);
                }
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if((mv.factory_set >= 1)&&(mv.factory_set <= 36))
                {
                    menu_stat = FACTORY_SET_PAGE;
                    TFTDisplay_Factory_Settings();
                }
                key.enter = 0;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                TFTDisplay_Main_Menu();
                menu_stat = SELECT_MENU_PAGE;
                key.function = 0;
                Delay_1ms(500);
            }
            break;
        }
        case FACTORY_SET_PAGE:
        {
            TFT_Modify_Factory_Settings();
            break;
        }
        case WRITE_TO_MEMORY_PAGE2:
        {
            if(key.increment == 1)        // INC Key
            {
                LCDPutStr("YES",152,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE); 
                common_byte = 1;
                key.increment = 0;
            }
            else if(key.decrement == 1)        // DEC Key
            {
                LCDPutStr("NO ",152,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                common_byte = 0;
                key.decrement = 0;
            }
            else if(key.enter == 1)        // ENTR Key
            {
                if(common_byte == 1)
                {
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);        //read first sector for preservation of calibration data
                    memcpy(sys.buf,flash.buf+SYS_PARA_MEM_BASE_ADDR,sizeof(sys.buf));
                    Delay_1ms(100);
                    SPI_WriteBlockProtection();
                    SPI_Flash_Chip_Erase();
                    LCDPutStr("CHIP ERASED",100,200,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                    Delay_1ms(1500);
                    LCDPutStr("           ",100,200,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                    LCDPutStr("PRESS ENTR TO START PC COMM",50,200,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    menu_stat = WRITE_TO_MEMORY_PAGE3;
                }
                else
                {
                   LCDPutStr("CANCELLED FLASH WRITE OPERATION",29,200,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);  //V1.17.1 
                    Delay_1ms(1500);
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
                    TFTCommon_Factory_Escape_Function();
                    menu_stat = FACTORY_SET_CODE_PAGE;
                }
                key.enter = 0;
                break;
            }
            else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
            {
                LCDPutStr("                      ",30,110,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("                      ",30,200,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("SET BAUDRATE:",120,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                color_lcd_draw_rectangle(ILI9341_WHITE,125,155,215,187);
                
                prv8_val1 = 0;
                LCDPutStr("       ",125,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                sprintf(ubuf,"%lu",baud[prv8_val1]);
                LCDPutStr(ubuf,130,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                key.function = 0;
                Delay_1ms(500);
                menu_stat = FACTORY_SET_PAGE;
            }
            break;
        }
        case WRITE_TO_MEMORY_PAGE3:       //Wait to start operation
        {
            if(key.enter == 1)        // ENTR Key
            {
                LCDPutStr("                      ",30,110,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("                      ",30,200,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("WAITING FOR REPLY",100,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("   ",152,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                LCDPutStr("COMMUNICATION STARTED...!!",65,200,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                
                Delay_1ms(1500);
                NewCSVFlag = 1;
                RxStart_flag = 0;
                _add = ONE_SECTOR_SIZE;
                
                UART3_Write(0x02);
                
                while(!RxStart_flag)
                {}
                LCDPutStr("                      ",30,110,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                sprintf(ubuf,"TOTAL PAGES:%05d",TotalNoPageRecive);
                LCDPutStr(ubuf,92,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                sprintf(ubuf,"%05d",Page_count);
                LCDPutStr("PAGE COUNTS",92,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr(ubuf,137,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                menu_stat = WRITE_TO_MEMORY_PAGE4;
                key.enter = 0;
            }
            key.bypass = 0;
            key.duty = 0;
            key.function = 0;
            key.increment = 0;
            key.decrement = 0;
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
                    sprintf(ubuf,"%05d",Page_count);
                    LCDPutStr(ubuf,137,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    
                    
//                    for(TempCount=0; TempCount<256; TempCount++)
//                    {
//                        sprintf(ubuf,"%d)=%d\r\n",TempCount+1,flash.sector.page[0][TempCount]);
//                    }
                    Page_done = 0;
                    pw_fail = 0;
                    Delay_1ms(50);
                    UART3_Write(0x06);
                }
                else if((NewCSVFlag==1)&&(Page_done==1))
                {
                    TotalNoPageRecive = (Serial_buff[0]*256)+Serial_buff[1];
                    sprintf(ubuf,"TOTAL PAGES:%05d",TotalNoPageRecive);
                    LCDPutStr(ubuf,92,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    Page_done = 0;
                    NewCSVFlag = 0;
                    pw_fail = 0;
                    UART3_Write(0x06);
                }
                else
                {
                    continue;
                }
            }
            if(pw_fail == 0)
            {
                flash_page_addr = ONE_SECTOR_SIZE+18; //start page address of first cane//Default crane ID is 1
                sys.para.crane_page_index = (SPIFlash_Read_Byte(flash_page_addr)*256)+SPIFlash_Read_Byte(flash_page_addr+1);

                Read_Startup_SPIFlash();
                //Factory_Default_Reset();
                LCDPutStr("                      ",30,200,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("DATA TRANSFER COMPLETED...!!",48,200,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                Delay_1ms(1500);
                 /****************************************************************/
                color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);  
                LCDPutStr("  WANT TO MASTER RESET:",50,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                color_lcd_draw_rectangle(ILI9341_WHITE,120,150,220,190);
                draw_hollow_rect(ILI9341_NAVY,122,152,218,188);
        
                prv8_val1 = 0;
                if(prv8_val1==0)  LCDPutStr("NO ",150,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                else              LCDPutStr("YES",150,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                               
               while(1)
                {
                if((key.bypass == 1)||(key.duty == 1))
                {
                    key.bypass = 0;
                    key.duty = 0;                
                }
                else if((key.increment == 1)||(key.decrement == 1))
                {
                    prv8_val1 = !prv8_val1;

                    if(prv8_val1==0)  LCDPutStr("NO ",150,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    else              LCDPutStr("YES",150,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    key.increment = 0;
                    key.decrement = 0;
                }
                else if(key.enter == 1)        // ENTR Key
                {
                 if(prv8_val1==1)
                {
                    Factory_Default_Reset();
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
                    LCDPutStr("COMPLETED...!",40,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(3000);
                    key.enter = 0;
                     break;
                }
                else if(prv8_val1==0)
                {
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
                    LCDPutStr("CAL DATA PRESERVED",40,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(3000);
                    break;
                }                       
                }
                else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
                {            
                    key.function = 0;
                }
                }
                
                Read_System_Parameters();
                
                Power_ON_Display();
                
                Calc_Parameter_Factors(); 
                
                Default_Main_Screen_Display();
            }
            menu_stat = DEFAULT_PAGE;
            key.bypass = 0;
            key.duty = 0;
            key.increment = 0;
            key.decrement = 0;
            key.enter = 0;
            key.function = 0;
            ui_key = 0;
            break;
        }
    }
}











