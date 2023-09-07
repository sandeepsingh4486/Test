
#include "main.h"

/*============================================================================*/
/*
 * Function      :        TFTDisplay_Site_Set_Menu.
 * Description   :        Used to display site menu first page.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Site_Set_Menu(uint8_t page)
{
    uint8_t rcnt;
    
    mv.max = 35;
    mv.min = 1;
    
    Set_Codes_Menu_Outlines();
    
    TFTSite_Setcode_Pages(page);
    
    rcnt = mv.site_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(0,rcnt);
}



/*============================================================================*/
/*
 * Function      :        TFTSelect_Site_Setcode_Menu.
 * Description   :        Used to highlight Site menu pages.
 * Parameters    :        sel-highlight row number(1 to 5).
 * Return        :        None.
*/
/*============================================================================*/
void TFTSelect_Site_Setcode_Menu(uint8_t sel)
{
    uint8_t rcnt;
    
    rcnt = mv.site_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(sel,rcnt);
    
    if(((mv.site_set == 1)&&(sel == 1))||((mv.site_set == 5)&&(sel == 0)))        {Clear_Rows();TFTSite_Setcode_Pages(0);}
    else if(((mv.site_set == 6)&&(sel == 1))||((mv.site_set == 10)&&(sel == 0)))  {Clear_Rows();TFTSite_Setcode_Pages(1);}
    else if(((mv.site_set == 11)&&(sel == 1))||((mv.site_set == 15)&&(sel == 0))) {Clear_Rows();TFTSite_Setcode_Pages(2);}
    else if(((mv.site_set == 16)&&(sel == 1))||((mv.site_set == 20)&&(sel == 0))) {Clear_Rows();TFTSite_Setcode_Pages(3);}
    else if(((mv.site_set == 21)&&(sel == 1))||((mv.site_set == 25)&&(sel == 0))) {Clear_Rows();TFTSite_Setcode_Pages(4);}
    else if(((mv.site_set == 26)&&(sel == 1))||((mv.site_set == 30)&&(sel == 0))) {Clear_Rows();TFTSite_Setcode_Pages(5);}
    else if(((mv.site_set == 31)&&(sel == 1))||((mv.site_set == 35)&&(sel == 0))) {Clear_Rows();TFTSite_Setcode_Pages(6);}
}



/*============================================================================*/
/*
 * Function      :        TFTDisplay_Site_Settings.
 * Description   :        Used to display Site setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Site_Settings(void)
{
    char obuf[10],slen;
    
    sprintf(obuf,"%03d",mv.site_set+199);
    LCDPutStr(obuf,18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    color_lcd_draw_rectangle(ILI9341_NAVY,75,57,260,75);    //Clear title
    color_lcd_draw_rectangle(ILI9341_WHITE,281,51,309,79);
    LCDPutStr(">>",285,57,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
    
    if((mv.site_set == MIN_BOOM_LEGTH)||(mv.site_set == MAX_BOOM_LEGTH)||
       (mv.site_set == LOAD_CORR_FACTOR)||(mv.site_set == LOAD_CORR_LIMIT)||
       (mv.site_set == ENTR_LOAD_THRESHOLD))
    {
        if(mv.site_set == MIN_BOOM_LEGTH)
        {
            LCDPutStr("SET MIN BOOM LEGTH  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.bm_length_min;
        }
        else if(mv.site_set == MAX_BOOM_LEGTH)
        {
            LCDPutStr("SET MAX BOOM LEGTH  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.bm_length_max;
        }
        else if(mv.site_set == LOAD_CORR_FACTOR)
        {
            LCDPutStr("LOAD CORR FACTOR    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.load_corr_factor;
        }
        else if(mv.site_set == LOAD_CORR_LIMIT)
        {
            LCDPutStr("LOAD CORR LIMIT     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.load_corr_limit;
        }
        else if(mv.site_set == ENTR_LOAD_THRESHOLD)
        {
            LCDPutStr("SET PNH THRESHOLD   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.load_threshold;
        }
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
        
        sprintf(obuf,"%04.1f",((float)prv16_val1)/10.0);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;

        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//        LCDPutChar('T',valX+60,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//        LCDPutChar('T',valX+60,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        common_byte = 3;
        common_long = prv16_val1;    

        cursX += common_byte*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.site_set == SET_LOW_ERR_COUNT)||(mv.site_set == SET_HIGH_ERR_COUNT))
    {
        if(mv.site_set == SET_LOW_ERR_COUNT)
        {
            LCDPutStr("SET LOW ERROR COUNTS",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
            prv16_val1 = sys.para.low_err_cnt;
        }
        else if(mv.site_set == SET_HIGH_ERR_COUNT)
        {
            LCDPutStr("SET HI ERROR COUNTS ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
            prv16_val1 = sys.para.high_err_cnt;
        }
        
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);            
        
        sprintf(obuf,"%04d",prv16_val1);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE); 
        
        common_byte = 4;
        common_long = prv16_val1;    

        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.site_set == SET_PRESS_P1_CHANNEL)||(mv.site_set == SET_PRESS_P2_CHANNEL)||
            (mv.site_set == SET_LENGTH_CHANNEL)||(mv.site_set == SET_ANGLE_CHANNEL)||
            (mv.site_set == SET_CAL_SAMPLE_COUNT)||(mv.site_set == SET_MANGLE_CHANNEL)||
            (mv.site_set == SET_NUMOF_BM_PARTS))
    {
        if(mv.site_set == SET_PRESS_P1_CHANNEL)
        {
            LCDPutStr("SET PRESS P1 CHANN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.pressure_p1_chann;
        }
        else if(mv.site_set == SET_PRESS_P2_CHANNEL)
        {
            LCDPutStr("SET PRESS P2 CHANN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.pressure_p2_chann;
        }
        else if(mv.site_set == SET_LENGTH_CHANNEL)
        {
            LCDPutStr("SET LENGTH CHANN    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.bm_length_chann;
        }
        else if(mv.site_set == SET_ANGLE_CHANNEL)
        {
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                LCDPutStr("SET KNUCKLE ANG CHAN",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("SET BOOM ANGLE CHANN",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.bm_angle_chann;
        }
        else if(mv.site_set == SET_CAL_SAMPLE_COUNT)
        {
            LCDPutStr("SET CAL SAMPLE COUNT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.cal_smpl_cnt;
        }
        else if(mv.site_set == SET_MANGLE_CHANNEL)
        {
            LCDPutStr("SET MAIN ANG CHANN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.main_ang_chann;
        }
        else if(mv.site_set == SET_NUMOF_BM_PARTS)
        {
            LCDPutStr("NUM OF BOOM PARTS   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = sys.para.boom_parts;
        }
        
        
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);            
        
        sprintf(obuf,"%02d",prv8_val1);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE); 
        
        common_byte = 2;
        common_long = prv8_val1;    

        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.site_set == BM_LENGTH_CORR_1)||(mv.site_set == BM_LENGTH_CORR_2)||
            (mv.site_set == BM_LENGTH_CORR_3)||(mv.site_set == BM_LENGTH_CORR_4)||(mv.site_set == LOAD_CORR_1)||
            (mv.site_set == LOAD_CORR_2)||(mv.site_set == LOAD_CORR_3)||
            (mv.site_set == LOAD_CORR_4)||(mv.site_set == LOAD_CORR_5))
    {
        if(mv.site_set == BM_LENGTH_CORR_1)
        {            
            LCDPutStr("BOOM LENGTH CORR-1  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.bm_length_corr1;
        }
        else if(mv.site_set == BM_LENGTH_CORR_2)
        {            
            LCDPutStr("BOOM LENGTH CORR-2  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.bm_length_corr2;
        }
        else if(mv.site_set == BM_LENGTH_CORR_3)
        {            
            LCDPutStr("BOOM LENGTH CORR-3  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.bm_length_corr3;
        }
        else if(mv.site_set == BM_LENGTH_CORR_4)
        {            
            LCDPutStr("BOOM LENGTH CORR-4  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.bm_length_corr4;
        }
        else if(mv.site_set == LOAD_CORR_1)
        {
            if(sys.para.Select_System == TIL_PIXEF_TELE_PNC)
                LCDPutStr("SET LD CORR(0.2-2T) ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("SET LD CORR(0.6-2T) ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.load_corr1;
        }
        else if(mv.site_set == LOAD_CORR_2)
        {
            LCDPutStr("SET LD CORR(2-4T)   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.load_corr2;
        }
        else if(mv.site_set == LOAD_CORR_3)
        {
            LCDPutStr("SET LD CORR(4-9T)   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.load_corr3;
        }
        else if(mv.site_set == LOAD_CORR_4)
        {
            LCDPutStr("SET LD CORR(9-12T)  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.load_corr4;
        }
        else if(mv.site_set == LOAD_CORR_5)
        {
            LCDPutStr("SET LD CORR(>12T)   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.load_corr5;
        }
        
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
        
        value_sign_flag = 0;
        if(prv16_sign_val < 0)
        {
            sprintf(obuf,"%05.1f",((float)prv16_sign_val)/10.0);
            value_sign_flag = 1;
            prv16_sign_val = prv16_sign_val*(-1); //make it positive for edit
        }
        else
        {
            sprintf(obuf,"+%04.1f",((float)prv16_sign_val)/10.0);
            value_sign_flag = 0;
        }

        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;

        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//        LCDPutChar('M',valX+66,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//        LCDPutChar('M',valX+66,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        common_byte = 3;
        common_long = prv16_sign_val;   //Take positive number to modify    

        cursX += (common_byte+1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.site_set == FAIL_SAFE_STATUS_CASE))
    {
        if(mv.site_set == FAIL_SAFE_STATUS_CASE)
        {
            LCDPutStr("FAIL SAFE STATUS    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.fail_safe_stat_bit;
        }
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);

        slen = strlen("DISABLE")*12;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8;
        valX = cursX;
        valY = cursY;

        TFTShow_Enable_Disable();

        if(prv8_val1)
            LCDPutStr("ENABLE ",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        else
            LCDPutStr("DISABLE",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else if(mv.site_set == COPY_ZLOAD_PCURVE)
    {
        LCDPutStr("COPY NO LOAD PCURVE ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        start_cpy_dty = 1;
        end_cpy_dty = 2;
        prv16_val1 = start_cpy_dty;
        prv16_val2 = end_cpy_dty;
        prv8_val1 = 0;      //edit from duty
        
        LCDPutStr("COPY FROM DUTY:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("COPY TO DUTY  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
        draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
        color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
        draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
        
        sprintf(obuf,"%02d",prv16_val2);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 165+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        sprintf(obuf,"%02d",prv16_val1);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        common_byte = 2;
        common_long = prv16_val1;

        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.site_set == VIEW_DUTY_TABLE)
    {
        LCDPutStr("VIEW DUTY TABLE     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        TFT_View_Duty_Table_Menu();
    }
    else if(mv.site_set == COPY_ZERO_CALIB) //change here 25/04/23 v1.16 reserved
    {
        LCDPutStr("COPY ZERO CALIB     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(mv.site_set == SET_DATE_TIME)  //change here 25/04/23 v1.16 reserved
    {
        LCDPutStr("SET DATE & TIME     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(mv.site_set == EDIT_LENGTH_COUNT)
    {
        LCDPutStr("EDIT LENGTH COUNTS  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(mv.site_set == LENGTH_FACTORS)  //change here 25/04/23 v1.16 reserved
    {
        LCDPutStr("LENGTH FACTORS      ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(mv.site_set == PRESSURE_FACTOR)  //change here 25/04/23 v1.16 reserved
    {
        LCDPutStr("PRESSURE FACTOR     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(mv.site_set == EN_PEAKNHOLD_OPTION)  //change here 25/04/23 v1.16 reserved
    {
        LCDPutStr("EN PNH SWITCH       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(mv.site_set == FREEZE_LD_ABOVE_ANGLE)  //V1.17.1
    {
        LCDPutStr("ENBLE ANGLE FRZ LOAD",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); //change here 25/04/23 v1.16 reserved
        //if(mv.site_set == FREEZE_LD_ABOVE_ANGLE)
        //{
            //LCDPutStr("ENBLE ANGLE FRZ LOAD",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.frz_load_angl_bit;
        //}
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);         //V1.17.1

        slen = strlen("DISABLE")*12;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8;
        valX = cursX;
        valY = cursY;

        TFTShow_Enable_Disable();                                          //V1.17.1

        if(prv8_val1)
            LCDPutStr("ENABLE ",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        else
            LCDPutStr("DISABLE",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    
}



 
/*============================================================================*/
/*
 * Function      :        TFT_View_Duty_Table_Menu.
 * Description   :        Used to view Duty table menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_View_Duty_Table_Menu(void)
{
    char obuf[10],slen;
    DCT dt;
    
    LCDPutStr("DUTY TABLE NUM:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("TOTL DTY TABLE:",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
    draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
    color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
    draw_hollow_rect(ILI9341_NAVY,182,167,278,203);

    if(lc_art_table_switch)
        dt.dty = lc_total_duty*2;
    else
        dt.dty = lc_total_duty;

    dt.dc_page_s = lc_duty_cycle_page_s;
    dt.mem_offset = flash_memory_offset;
    total_dty_tables = Duty_Table(DT_END,dt);

    sprintf(obuf,"%05d",total_dty_tables);
    slen = strlen(obuf)*13;
    cursX = 180+((100-slen)/2);
    cursY = 165+20-8; 
    pos_t = 0;
    valX = cursX;
    valY = cursY;
    LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    prv16_val1 = 1;        
    sprintf(obuf,"%04d",prv16_val1);
    slen = strlen(obuf)*13;
    cursX = 180+((100-slen)/2);
    cursY = 100+20-8; 
    pos_t = 0;
    valX = cursX;
    valY = cursY;
    LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    common_byte = 4;
    common_long = prv16_val1;    

    cursX += (common_byte-1)*13;
    cursY += 19;
    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
}

/*============================================================================*/
/*
 * Function      :        TFT_Modify_Site_Settings.
 * Description   :        Used to modify operator setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Modify_Site_Settings(void)
{
    if((mv.site_set == MIN_BOOM_LEGTH)||(mv.site_set == MAX_BOOM_LEGTH)||
       (mv.site_set == LOAD_CORR_FACTOR)||(mv.site_set == LOAD_CORR_LIMIT)||
       (mv.site_set == ENTR_LOAD_THRESHOLD))
    {
        TFT_Set_3Digit1Decimal_Site_Menus();
    }
    else if((mv.site_set == SET_LOW_ERR_COUNT)||(mv.site_set == SET_HIGH_ERR_COUNT))
    {
        TFT_Edit_4Digit_Site_Menu();
    }
    else if((mv.site_set == SET_PRESS_P1_CHANNEL)||(mv.site_set == SET_PRESS_P2_CHANNEL)||
            (mv.site_set == SET_LENGTH_CHANNEL)||(mv.site_set == SET_ANGLE_CHANNEL)||
            (mv.site_set == SET_CAL_SAMPLE_COUNT)||(mv.site_set == SET_MANGLE_CHANNEL)||
            (mv.site_set == SET_NUMOF_BM_PARTS ))
    {
        TFT_Edit_2Digit_Site_Menu();
    }
    else if((mv.site_set == BM_LENGTH_CORR_1)||(mv.site_set == BM_LENGTH_CORR_2)||
            (mv.site_set == BM_LENGTH_CORR_3)||(mv.site_set == BM_LENGTH_CORR_4)||(mv.site_set == LOAD_CORR_1)||
            (mv.site_set == LOAD_CORR_2)||(mv.site_set == LOAD_CORR_3)||
            (mv.site_set == LOAD_CORR_4)||(mv.site_set == LOAD_CORR_5))
    {
        TFT_Set_Site_Factors_menu();
    }
    else if((mv.site_set == FAIL_SAFE_STATUS_CASE))
    {
        TFT_Enable_Disable_Site_Menu();
    }
    else if(mv.site_set == COPY_ZLOAD_PCURVE)
    {
        TFT_Copy_ZLoad_PCurve();
    }
    else if(mv.site_set == VIEW_DUTY_TABLE)
    {
        TFT_View_Duty_Tables();
    }
     else if(mv.site_set == FREEZE_LD_ABOVE_ANGLE)
    {
         TFT_Enable_Disable_Site_Menu();                        //V1.17.1
         TFT_Edit_2Digit_Site_Menu();
    }
    else if((mv.site_set == COPY_ZERO_CALIB)||(mv.site_set == EN_PEAKNHOLD_OPTION)||(mv.site_set == PRESSURE_FACTOR)||(mv.site_set == LENGTH_FACTORS)||(mv.site_set == EDIT_LENGTH_COUNT)||(mv.site_set == SET_DATE_TIME)) //change here 25/04/23 v1.16 reserved
    {
       TFT_Set_Reserved_Site_Menu();   
    }
}

/*============================================================================*/
/*
 * Function      :        TFTCommon_Site_Escape_Function.
 * Description   :        Used to take escape from Site menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTCommon_Site_Escape_Function(void)
{
    if((mv.site_set >= 1)&&(mv.site_set <= 5))        TFTDisplay_Site_Set_Menu(0);
    else if((mv.site_set >= 6)&&(mv.site_set <= 10))  TFTDisplay_Site_Set_Menu(1);
    else if((mv.site_set >= 11)&&(mv.site_set <= 15)) TFTDisplay_Site_Set_Menu(2);
    else if((mv.site_set >= 16)&&(mv.site_set <= 20)) TFTDisplay_Site_Set_Menu(3);
    else if((mv.site_set >= 21)&&(mv.site_set <= 25)) TFTDisplay_Site_Set_Menu(4);
    else if((mv.site_set >= 26)&&(mv.site_set <= 30)) TFTDisplay_Site_Set_Menu(5);
    else if((mv.site_set >= 31)&&(mv.site_set <= 35)) TFTDisplay_Site_Set_Menu(6);
}


/*============================================================================*/
/*
 * Function      :        TFT_Set_3Digit1Decimal_Site_Menus.
 * Description   :        Used to set 3 digit site menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_3Digit1Decimal_Site_Menus(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.site_set == MIN_BOOM_LEGTH)          
                sys.para.bm_length_min = (uint8_t)common_long;
            else if(mv.site_set == MAX_BOOM_LEGTH)
                sys.para.bm_length_max = (uint8_t)common_long;
            else if(mv.site_set == LOAD_CORR_FACTOR)
                sys.para.load_corr_factor = (uint8_t)common_long;
            else if(mv.site_set == LOAD_CORR_LIMIT)
                sys.para.load_corr_limit = (uint8_t)common_long;
            else if(mv.site_set == ENTR_LOAD_THRESHOLD)
                sys.para.load_threshold = (uint8_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_3Digit_1Decimal_Menu();
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Edit_4Digit_Site_Menu.
 * Description   :        Used to set four digit site menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Edit_4Digit_Site_Menu(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.site_set == SET_LOW_ERR_COUNT)          
                sys.para.low_err_cnt = (uint16_t)common_long;
            else if(mv.site_set == SET_HIGH_ERR_COUNT)
                sys.para.high_err_cnt = (uint16_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_4Digit_Menu();
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Edit_2Digit_Site_Menu.
 * Description   :        Used to set Two digit site menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Edit_2Digit_Site_Menu(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.site_set == SET_PRESS_P1_CHANNEL)          
                sys.para.pressure_p1_chann = (uint8_t)common_long;
            else if(mv.site_set == SET_PRESS_P2_CHANNEL)
                sys.para.pressure_p2_chann = (uint8_t)common_long;
            else if(mv.site_set == SET_LENGTH_CHANNEL)
                sys.para.bm_length_chann = (uint8_t)common_long;
            else if(mv.site_set == SET_ANGLE_CHANNEL)
                sys.para.bm_angle_chann = (uint8_t)common_long;
            else if(mv.site_set == SET_MANGLE_CHANNEL)
                sys.para.main_ang_chann = (uint8_t)common_long;
            else if(mv.site_set == SET_CAL_SAMPLE_COUNT)
                sys.para.cal_smpl_cnt = (uint8_t)common_long;
            else if(mv.site_set == SET_NUMOF_BM_PARTS)
                sys.para.boom_parts = (uint8_t)common_long;
            else if(mv.site_set == FREEZE_LD_ABOVE_ANGLE)                       //V1.17.1
                sys.para.set_angle_frz_lod = (uint8_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_2Digit_Menu();
        }
    }
}



/*============================================================================*/
/*
 * Function      :        TFT_Set_Site_Factors_menu.
 * Description   :        Used to change correction factors.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Site_Factors_menu(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.site_set == BM_LENGTH_CORR_1)
                sys.para.bm_length_corr1 = (uint16_t)common_long;
            else if(mv.site_set == BM_LENGTH_CORR_2)
                sys.para.bm_length_corr2 = (uint16_t)common_long;
            else if(mv.site_set == BM_LENGTH_CORR_3)
                sys.para.bm_length_corr3 = (uint16_t)common_long;
            else if(mv.site_set == BM_LENGTH_CORR_4)
                sys.para.bm_length_corr4 = (uint16_t)common_long;
            else if(mv.site_set == LOAD_CORR_1)
                sys.para.load_corr1 = (uint16_t)common_long;
            else if(mv.site_set == LOAD_CORR_2)
                sys.para.load_corr2 = (uint16_t)common_long;
            else if(mv.site_set == LOAD_CORR_3)
                sys.para.load_corr3 = (uint16_t)common_long;
            else if(mv.site_set == LOAD_CORR_4)
                sys.para.load_corr4 = (uint16_t)common_long;
            else if(mv.site_set == LOAD_CORR_5)
                sys.para.load_corr5 = (uint16_t)common_long;
            
            if(value_sign_flag)
            {
                if(mv.site_set == BM_LENGTH_CORR_1)
                    sys.para.bm_length_corr1 = sys.para.bm_length_corr1*(-1);
                else if(mv.site_set == BM_LENGTH_CORR_2)
                    sys.para.bm_length_corr2 = sys.para.bm_length_corr2*(-1);
                else if(mv.site_set == BM_LENGTH_CORR_3)
                    sys.para.bm_length_corr3 = sys.para.bm_length_corr3*(-1);
                else if(mv.site_set == BM_LENGTH_CORR_4)
                    sys.para.bm_length_corr4 = sys.para.bm_length_corr4*(-1);
                else if(mv.site_set == LOAD_CORR_1)
                    sys.para.load_corr1 = sys.para.load_corr1*(-1);
                else if(mv.site_set == LOAD_CORR_2)
                    sys.para.load_corr2 = sys.para.load_corr2*(-1);
                else if(mv.site_set == LOAD_CORR_3)
                    sys.para.load_corr3 = sys.para.load_corr3*(-1);
                else if(mv.site_set == LOAD_CORR_4)
                    sys.para.load_corr4 = sys.para.load_corr4*(-1);
                else if(mv.site_set == LOAD_CORR_5)
                    sys.para.load_corr5 = sys.para.load_corr5*(-1);
            }
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_3Digit_1Decimal_WSign_Menu();
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Enable_Disable_Site_Menu.
 * Description   :        Used to enable disable site menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Enable_Disable_Site_Menu(void)
{
    char obuf[50],slen;
    
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
            
            TFTShow_Enable_Disable();
            
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            if(mv.site_set == FAIL_SAFE_STATUS_CASE)
            {
                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

                sys.para.fail_safe_stat_bit = prv8_val1;

                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                Delay_1ms(1500);

                TFTCommon_Site_Escape_Function();

                menu_stat = SITE_SET_CODE_PAGE;
            }
              else if(mv.site_set == FREEZE_LD_ABOVE_ANGLE)               //V1.17.1
            {
                if(prv8_val1)
                {
                    sys.para.frz_load_angl_bit = 1;
                    prv16_val1 = sys.para.set_angle_frz_lod;
                    
                    //Now set angle value
                    //LCDPutStr("CURRENT VALUE   :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    //LCDPutStr("PREVIOUSE VALUE :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                     Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
                     
                     sprintf(obuf,"%02d",prv16_val1);
                     slen = strlen(obuf)*13;
                     cursX = 180+((100-slen)/2);
                     cursY = 100+20-8; 
                     pos_t = 0;
                     valX = cursX;
                     valY = cursY;
                     LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                     
                     LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
                     common_byte = 2;
                     common_long = prv16_val1;  //prv8_val1;    
            
                     cursX += (common_byte-1)*13;
                     cursY += 19;
                     TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                    
                    //color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                    //draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                    //color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                    //draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
                    //menu_stat = FREEZE_LOAD_ABOVE_ANGLE;
                     //Delay_1ms(1500);
                     //TFTCommon_Site_Escape_Function();
                     //menu_stat = SITE_SET_PAGE;
                     //menu_stat = SITE_SET_CODE_PAGE;
                }
                else
               {
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

                    sys.para.frz_load_angl_bit = 0;

                   memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Site_Escape_Function();

                    menu_stat = SITE_SET_CODE_PAGE;
                }
            }
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Site_Escape_Function();
            
            menu_stat = SITE_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Copy_ZLoad_PCurve.
 * Description   :        Used to copy pressure curve from one duty to another duty.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Copy_ZLoad_PCurve(void)
{
    char obuf[10],slen;
    uint8_t ang;
    
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            if(prv8_val1 == 0)
            {
                TFTCommon_Site_Escape_Function();
                menu_stat = SITE_SET_CODE_PAGE;
                break;
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte+1)*13),cursY,cursX+13,cursY+2);
                
                sprintf(obuf,"%02d",prv16_val1);
                slen = strlen(obuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 100+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                prv8_val1 = 0;
                common_byte = 2;
                common_long = prv16_val1;
                
                cursX += (common_byte-1)*13;
                cursY += 19;
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            }
            key.function = 0;
            Delay_1ms(500);
        }
        else if(key.enter == 1)        // ENTR Key
        {
            key.enter = 0;
            if(prv8_val1 == 0)
            {
                prv16_val1 = (uint16_t)common_long;     //Get the start duty
                start_cpy_dty = (uint8_t)prv16_val1;
                
                if((prv16_val1 > 0)&&(prv16_val1 < lc_total_duty))  //should be less than lc_total_duty
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte+1)*13),cursY,cursX+13,cursY+2);
                    
                    sprintf(obuf,"%02d",prv16_val2);
                    slen = strlen(obuf)*13;
                    cursX = 180+((100-slen)/2);
                    cursY = 165+20-8; 
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    prv8_val1 = 1;      //Now edit end duty
                    common_byte = 2;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
            }
            else
            {
                prv16_val2 = (uint16_t)common_long;     //Get the to duty
                end_cpy_dty = (uint8_t)prv16_val2;
                
                prv8_val1 = 0;
                color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
                LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                Delay_1ms(1500);
                
                if((prv16_val2 > 0)&&(prv16_val2 <= lc_total_duty))
                {
                    for(length_array_ptr=0; length_array_ptr<5; length_array_ptr++)
                    {
                        csv_ref_len = length_array_ptr%5;
                        pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + (((uint32_t)start_cpy_dty-1)*10*256) + csv_ref_len*512 + flash_memory_offset;
                        
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
                        
                        csv_ref_len = length_array_ptr%5;
                        pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + (((uint32_t)end_cpy_dty-1)*10*256) + csv_ref_len*512 + flash_memory_offset;
                        
                        pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
                        pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector
                        
                        pc_sector = pc_sector_quotient;
                        pc_page = pc_sector_remainder;//Pressure curve start page & need to check if its greater than 15
                        
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
                            }
                            Sector_Erase(pc_sector);
                            SPIFlash_Write_Sector(pc_sector);
                        }
                        else
                        {
                            for(ang=0; ang<90; ang++)
                            {
                                flash.sector.page[pc_page+1][(ang*2)+16] = pc_buf[1][ang]/256;
                                flash.sector.page[pc_page+1][(ang*2)+17] = pc_buf[1][ang]%256;
                            }
                            Sector_Erase(pc_sector);
                            SPIFlash_Write_Sector(pc_sector);                            
                        }
                        
                    }
                    TFTCommon_Site_Escape_Function();

                    menu_stat = SITE_SET_CODE_PAGE;
                    break;
                }
            }         
        }
        else
        {
            Inc_Dec_2Digit_Menu();
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_View_Duty_Tables.
 * Description   :        Used to set two digit menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_View_Duty_Tables(void)
{
    char ubuf[10];
    
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Site_Escape_Function();            
            menu_stat = SITE_SET_CODE_PAGE;                
            key.function = 0;
            Delay_1ms(500); 
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            prv16_val1 = (uint16_t)common_long;
            common_byte = 1;
            key.enter = 0;
            if((prv16_val1 > 0)&&(prv16_val1 <= total_dty_tables))
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,15,100,305,220);    //Clear Setting page
                    
                LCDPutStr("TABLE",10,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("COUNT",10,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);    
                
                LCDPutStr("RAD.",160,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("CAP.",160,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
                
                color_lcd_draw_rectangle(ILI9341_WHITE,65,95,145,127);
                draw_hollow_rect(ILI9341_NAVY,67,97,143,125);
                color_lcd_draw_rectangle(ILI9341_WHITE,65,137,145,169); 
                draw_hollow_rect(ILI9341_NAVY,67,139,143,167);

                color_lcd_draw_rectangle(ILI9341_WHITE,225,95,305,127);
                draw_hollow_rect(ILI9341_NAVY,227,97,303,125);
                color_lcd_draw_rectangle(ILI9341_WHITE,225,137,305,169);
                draw_hollow_rect(ILI9341_NAVY,227,139,303,167);
                
                flash_page_addr = (((uint32_t)lc_duty_table_page_s-1)*256)+(((uint32_t)prv16_val1-1)*256)+2+flash_memory_offset;
                vradcntr = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
                
                Get_Radius_Capacity(prv16_val1,common_byte-1);
                
                sprintf(ubuf,"%02d",prv16_val1);
                LCDPutStr(ubuf,92,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                sprintf(ubuf,"%02d",common_byte);
                LCDPutStr(ubuf,92,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                sprintf(ubuf,"%04.1fM",((float)vrad)/10.0);
                LCDPutStr(ubuf,233,105,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                sprintf(ubuf,"%04.1fT",((float)vcapa)/10.0);
                LCDPutStr(ubuf,233,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                menu_stat = VIEW_DUTY_TABLE_PAGE1;
                break;
            }                                 
        }
        else
        {
            Inc_Dec_4Digit_Menu();
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Set_2Digit_Site_Menus.
 * Description   :        Used to set two digit menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_2Digit_Site_Menus(void)
{
    
}

/*============================================================================*/
/*
 * Function      :        Main_Aux_Total_Falls_Menu.
 * Description   :        Used to select main or aux total falls .
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Total_Falls_Menu(void)
{
//    Lcd_Out(1,1,"SELECT HOOK:    ");
//    
//    if(sel_main_aux == 0)    
//    {
//        Lcd_Out(2,1,"MHK TOTAL FALLS:");
//        prv16_val1 = sys.para.mtotal_falls;
//    }
//    else
//    {
//        Lcd_Out(2,1,"AHK TOTAL FALLS:");
//        prv16_val1 = sys.para.atotal_falls;
//    }
}
 void TFT_Set_Reserved_Site_Menu(void)
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

            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
           key.enter =0;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Site_Escape_Function();            
            menu_stat = SITE_SET_CODE_PAGE;     
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
 }

//==================================EOF=========================================





