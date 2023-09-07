
#include "main.h"

/*============================================================================*/
/*
 * Function      :        TFTDisplay_Factory_Set_Menu.
 * Description   :        Used to display site menu first page.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Factory_Set_Menu(uint8_t page)
{
    uint8_t rcnt;
    
    mv.max = 40;
    mv.min = 1;
    
    Set_Codes_Menu_Outlines();
    
    TFTFactory_Setcode_Pages(page);
    
    rcnt = mv.factory_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(0,rcnt);
}



/*============================================================================*/
/*
 * Function      :        TFTSelect_Factory_Setcode_Menu.
 * Description   :        Used to highlight Site menu pages.
 * Parameters    :        sel-highlight row number(1 to 5).
 * Return        :        None.
*/
/*============================================================================*/
void TFTSelect_Factory_Setcode_Menu(uint8_t sel)
{
    uint8_t rcnt;
    
    rcnt = mv.factory_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(sel,rcnt);
    
    if(((mv.factory_set == 1)&&(sel == 1))||((mv.factory_set == 5)&&(sel == 0)))        {Clear_Rows();TFTFactory_Setcode_Pages(0);}
    else if(((mv.factory_set == 6)&&(sel == 1))||((mv.factory_set == 10)&&(sel == 0)))  {Clear_Rows();TFTFactory_Setcode_Pages(1);}
    else if(((mv.factory_set == 11)&&(sel == 1))||((mv.factory_set == 15)&&(sel == 0))) {Clear_Rows();TFTFactory_Setcode_Pages(2);}
    else if(((mv.factory_set == 16)&&(sel == 1))||((mv.factory_set == 20)&&(sel == 0))) {Clear_Rows();TFTFactory_Setcode_Pages(3);}
    else if(((mv.factory_set == 21)&&(sel == 1))||((mv.factory_set == 25)&&(sel == 0))) {Clear_Rows();TFTFactory_Setcode_Pages(4);}
    else if(((mv.factory_set == 26)&&(sel == 1))||((mv.factory_set == 30)&&(sel == 0))) {Clear_Rows();TFTFactory_Setcode_Pages(5);}
    else if(((mv.factory_set == 31)&&(sel == 1))||((mv.factory_set == 35)&&(sel == 0))) {Clear_Rows();TFTFactory_Setcode_Pages(6);}
    else if(((mv.factory_set == 36)&&(sel == 1))||((mv.factory_set == 40)&&(sel == 0))) {Clear_Rows();TFTFactory_Setcode_Pages(7);}
}



/*============================================================================*/
/*
 * Function      :        TFTDisplay_Factory_Settings.
 * Description   :        Used to display Site setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Factory_Settings(void)
{
    char obuf[20], sbuf[50];
    uint16_t slen;
    uint16_t TempCount,id_cnt,temp_max;
    
    sprintf(obuf,"%03d",mv.factory_set+299);
    LCDPutStr(obuf,18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    color_lcd_draw_rectangle(ILI9341_NAVY,75,57,260,75);    //Clear title
    color_lcd_draw_rectangle(ILI9341_WHITE,281,51,309,79);
    LCDPutStr(">>",285,57,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
    
    if((mv.factory_set == CALIB_PRESSURE_P1_MIN)||(mv.factory_set == CALIB_PRESSURE_P2_MIN)||
       (mv.factory_set == CALIB_PRESSURE_P1_MAX)||(mv.factory_set == CALIB_PRESSURE_P2_MAX))
    {        
        if(mv.factory_set == CALIB_PRESSURE_P1_MIN)
        {
            LCDPutStr("CALIB PRESS P1 MIN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.calib_pressure1_min;
            prv16_val2 = sys.para.calib_P1LowAdcCount;            
        }
        else if(mv.factory_set == CALIB_PRESSURE_P1_MAX)
        {
            LCDPutStr("CALIB PRESS P1 MAX  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.calib_pressure1_max;
            prv16_val2 = sys.para.calib_P1HighAdcCount;
        }
        else if(mv.factory_set == CALIB_PRESSURE_P2_MIN)
        {
            LCDPutStr("CALIB PRESS P2 MIN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.calib_pressure2_min;
            prv16_val2 = sys.para.calib_P2LowAdcCount;
        }
        else if(mv.factory_set == CALIB_PRESSURE_P2_MAX)
        {
            LCDPutStr("CALIB PRESS P2 MAX  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.calib_pressure2_max;
            prv16_val2 = sys.para.calib_P2HighAdcCount;
        }
        Current_Prev_Val_Screen(2, ILI9341_WHITE, ILI9341_NAVY);
        
        sprintf(obuf,"%04d",prv16_val1);
        sprintf(sbuf,"%04d",prv16_val2);
        slen = strlen(obuf)*13;
        cursX = 45+((100-slen)/2);
        cursY = 100+20-8;
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        slen = strlen(sbuf)*13;
        countX = 200+((100-slen)/2);        
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);        
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);        
        
        LCDPutStr(sbuf,countX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(sbuf,countX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        prv8_val1 = 1;          //Value edit
        common_byte = 4;
        common_long = prv16_val1;
        
        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.factory_set == WINDOW_SAMPLES_SIZE)||(mv.factory_set == WINDOW_SAMPLES_SIZE1)||
            (mv.factory_set == NUM_OF_CYLINDERS)||(mv.factory_set == HIGH_CUTOFF_ANGLE)||
            (mv.factory_set == SET_BAUDRATE)||(mv.factory_set == SET_MANBASKET_DUTY)||
            (mv.factory_set == SET_MANBASKET_CHANN))
    {
        if(mv.factory_set == WINDOW_SAMPLES_SIZE)
        {
            LCDPutStr("WINDOW SAMPLE SIZE  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.window_sample_size;
        }
        else if(mv.factory_set == WINDOW_SAMPLES_SIZE1)
        {
            LCDPutStr("WINDOW SAMPLE SIZE1 ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.window_sample_size1;
        }
        else if(mv.factory_set == NUM_OF_CYLINDERS)
        {
            LCDPutStr("NUM OF LUFF CYLINDER",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.num_of_cylinders;
        }
//        else if(mv.factory_set == HIGH_CUTOFF_ANGLE)
//        {
//            LCDPutStr("WINDOW DSPBOOM ANGLE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
//            prv8_val1 = (uint8_t)sys.para.window_sample_size1;
//        }
        else if(mv.factory_set == SET_BAUDRATE)
        {
            LCDPutStr("SET BAUDRATE        ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.baudrate;
        }
        else if(mv.factory_set == SET_MANBASKET_DUTY)
        {
            if(sys.para.Select_System == PNC_FORK)
            {
                LCDPutStr("SET FORK DUTY       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                prv8_val1 = sys.para.fork_duty;
            }
            else if(sys.para.Select_System == ACE_MANBASKET_HXP)
            {
                LCDPutStr("SET MANBAS DUTY     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                prv8_val1 = (uint8_t)sys.para.manbas_duty;
            }
            else
                LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        }
        else if(mv.factory_set == SET_MANBASKET_CHANN)
        {
            LCDPutStr("SET MANBASKET CHAN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.manbas_chann;
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
    else if((mv.factory_set == SET_BM_ANGLE_MIN)||(mv.factory_set == SET_BM_LENGTH_MIN)||
            (mv.factory_set == SET_BM_ANGLE_MAX)||(mv.factory_set == SET_BM_LENGTH_MAX))
    {
        if(mv.factory_set == SET_BM_ANGLE_MIN)
        {
            LCDPutStr("SET BOOM ANGLE MIN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.cal_angle_min;
            prv16_val2 = sys.para.cal_angle_min_cnt;            
        }
        else if(mv.factory_set == SET_BM_ANGLE_MAX)
        {
            LCDPutStr("SET BOOM ANGLE MAX  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.cal_angle_max;
            prv16_val2 = sys.para.cal_angle_max_cnt;
        }
        else if(mv.factory_set == SET_BM_LENGTH_MIN)
        {
            LCDPutStr("SET BOOM LENGTH MIN ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.cal_len_min;
            prv16_val2 = sys.para.cal_len_min_cnt;
        }
        else if(mv.factory_set == SET_BM_LENGTH_MAX)
        {
            LCDPutStr("SET BOOM LENGTH MAX ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.cal_len_max;
            prv16_val2 = sys.para.cal_len_max_cnt;
        }
        Current_Prev_Val_Screen(2, ILI9341_WHITE, ILI9341_NAVY);
        
        sprintf(obuf,"%04.1f",((float)prv16_val1)/10.0);
        sprintf(sbuf,"%04d",prv16_val2);
        slen = strlen(obuf)*13;
        cursX = 45+((100-slen)/2);
        cursY = 100+20-8;
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        slen = strlen(sbuf)*13;
        countX = 200+((100-slen)/2);        
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);        
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);        
        
        LCDPutStr(sbuf,countX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(sbuf,countX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        prv8_val1 = 1;          //Value edit
        common_byte = 3;
        common_long = prv16_val1;
        
        cursX += common_byte*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.factory_set == SELECT_SENSOR)
    {
        LCDPutStr("SELECT SENSOR       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        prv8_val1 = (uint8_t)sys.para.sel_sensor;
        
        LCDPutStr("CURRENT SENSOR",15,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("PREV SENSOR   ",15,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,150,100,290,140);
        draw_hollow_rect(ILI9341_NAVY,152,102,288,138);
        color_lcd_draw_rectangle(ILI9341_WHITE,150,165,290,205);  
        draw_hollow_rect(ILI9341_NAVY,152,167,288,203);
        
        slen = strlen(sensor_sel[prv8_val1-1])*13;
        cursX = 150+((140-slen)/2);
        cursY = 100+20-8;
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        LCDPutStr((char *)sensor_sel[prv8_val1-1],valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);        
        LCDPutStr((char *)sensor_sel[prv8_val1-1],valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
//    else if(mv.factory_set == STICKER_TYPE)
//    {
//        
//    }
    else if(mv.factory_set == SET_INSALLATION_DATE)
    {
        LCDPutStr("SET INSALLATION DATE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,85,100,235,140);   
        draw_hollow_rect(ILI9341_NAVY,87,102,233,138);
        
        sprintf(obuf,"%02d/%02d/%04d",sys.para.insta_dd,sys.para.insta_mm,sys.para.insta_yy);
        slen = strlen(obuf)*13;
        cursX = 85+((150-slen)/2);
        cursY = 100+20-8;
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        pos_t = 0;
        common_byte = 8;
        sprintf(obuf,"%02d%02d%04d",sys.para.insta_dd,sys.para.insta_mm,sys.para.insta_yy);
        common_long = atol(obuf);        
        
        cursX += (common_byte+1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.factory_set == SET_PERCENTAGE_STATUS)
    {
        LCDPutStr("SET PERCENT STATUS  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
        prv8_val1 = sys.para.perc_fact_stat_bit;
        
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
    else if(mv.factory_set == EN_NUMBER_OF_CALIB)
    {
        LCDPutStr("EN NUM OF CALIB     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        prv8_val1 = (uint8_t)sys.para.num_cal;
        
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
        
        if(sys.para.num_cal == 0)
        {
            sprintf(obuf,"CASE1");
        }
        else
        {
            sprintf(obuf,"CASE2");
        }
        
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else if(mv.factory_set == SET_SO_NUMBER)
    {
        LCDPutStr("SET SO NUMBER       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        prv32_val1 = sys.para.so_number;
        
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
        
        sprintf(obuf,"%05lu",prv32_val1);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        common_byte = 5;
        common_long = prv32_val1;    
        
        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.factory_set == SET_RADIUS_CUTOFF)||(mv.factory_set == SET_CORRECTION_LOAD))
    {
        if(mv.factory_set == SET_RADIUS_CUTOFF)
        {
            LCDPutStr("SET RADIUS CUTOFF   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.Radius_Cutoff;
        }
        else if(mv.factory_set == SET_CORRECTION_LOAD)
        {
            LCDPutStr("SET CORR. LOAD      ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.correction_load;
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
        
        if(mv.factory_set == SET_RADIUS_CUTOFF) 
            LCDPutChar('M',valX+60,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        if(mv.factory_set == SET_RADIUS_CUTOFF) 
            LCDPutChar('M',valX+60,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        common_byte = 3;
        common_long = prv16_val1;
        
        cursX += common_byte*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.factory_set == WRITE_TO_MEMORY)
    {
        LCDPutStr("UPLOAD CSV TO MEMORY",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        
        LCDPutStr("SET BAUDRATE:",120,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        color_lcd_draw_rectangle(ILI9341_WHITE,120,150,220,190);
        draw_hollow_rect(ILI9341_NAVY,122,152,218,188);
        
        prv8_val1 = 0;
        sprintf(obuf,"%lu",baud[prv8_val1]);
        LCDPutStr(obuf,130,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else if(mv.factory_set == CRANE_DETAILS)
    {
        LCDPutStr("ENTER CRANE DIMENSION ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        crane_detail_cnt = 1;
        
        mv.max = 6;
        mv.min = crane_detail_cnt;
        
        LCDPutStr("VRT.OFST",5,95,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("HRZ.OFST",5,145,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RAM PVOT",5,195,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("BCL.OFST",162,95,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("PSTN DIA",162,145,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr(" ROD DIA",162,195,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,80,90,155,120);
        draw_hollow_rect(ILI9341_NAVY,82,92,153,118);
        color_lcd_draw_rectangle(ILI9341_WHITE,80,140,155,170);
        draw_hollow_rect(ILI9341_NAVY,82,142,153,168);
        color_lcd_draw_rectangle(ILI9341_WHITE,80,190,155,220);
        draw_hollow_rect(ILI9341_NAVY,82,192,153,218);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,235,90,310,120);
        draw_hollow_rect(ILI9341_NAVY,237,92,308,118);
        color_lcd_draw_rectangle(ILI9341_WHITE,235,140,310,170);
        draw_hollow_rect(ILI9341_NAVY,237,142,308,168);
        color_lcd_draw_rectangle(ILI9341_WHITE,235,190,310,220);
        draw_hollow_rect(ILI9341_NAVY,237,192,308,218);
        
        sprintf(obuf,"%05.3fM",((float)sys.para.vertical_offset)/1000.0);
        slen = strlen(obuf)*9;
        cursX = 80+((75-slen)/2);
        cursY = 90+15-8; 
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05.3fM",((float)sys.para.horizontal_offset)/1000.0);
        slen = strlen(obuf)*9;
        cursX = 80+((75-slen)/2);
        cursY = 140+15-8; 
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05.3fM",((float)sys.para.rampivot_offset)/1000.0);
        slen = strlen(obuf)*9;
        cursX = 80+((75-slen)/2);
        cursY = 190+15-8; 
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05.3fM",((float)sys.para.bm_cntr_line_offset)/1000.0);
        slen = strlen(obuf)*9;
        cursX = 235+((75-slen)/2);
        cursY = 90+15-8; 
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05.3fM",((float)sys.para.piston_diameter)/1000.0);
        slen = strlen(obuf)*9;
        cursX = 235+((75-slen)/2);
        cursY = 140+15-8; 
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05.3fM",((float)sys.para.rod_diameter)/1000.0);
        slen = strlen(obuf)*9;
        cursX = 235+((75-slen)/2);
        cursY = 190+15-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05.3fM",((float)sys.para.vertical_offset)/1000.0);       //Second time for cursor purpose
        slen = strlen(obuf)*9;
        cursX = 80+((75-slen)/2);
        cursY = 90+15-8; 
        valX = cursX;
        valY = cursY;
        LCDPutStr(obuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        common_byte = 4;
        common_long = sys.para.vertical_offset;
        
        cursX += common_byte*9;
        cursY += 17;
        TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
    }
    else if(mv.factory_set == EN_LOAD_AVERAGING_VALUE)
    {
        if(mv.factory_set == EN_LOAD_AVERAGING_VALUE)
        {
            LCDPutStr("LOAD AVERAGING VALUE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.load_avg_stat_bit;
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
    else if(mv.factory_set == SET_CRANE_MODEL)
    {
        LCDPutStr("SELECT CRANE MODEL  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
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
        
        flash_page_addr = ONE_SECTOR_SIZE+2+(crane_id-1)*32;//skip 2 bytes of id
  
        for(TempCount=0;TempCount<16;TempCount++)
        {
            crane_make[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
        }
        
        LCDPutStr("CRANE ID NUMBER:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
        draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,40,165,280,205);                  //V1.17.1
        draw_hollow_rect(ILI9341_NAVY,42,167,278,203);
        
        slen = strlen(crane_make)*8;
        cursX = 40+((240-slen)/2);
        cursY = 165+20-8;
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        LCDPutStr(crane_make,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05d",crane_ids[crane_id-1]);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;

        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
//        common_byte = 5;
//        common_long = crane_ids[crane_id-1];
//
//        cursX += (common_byte-1)*13;
//        cursY += 19;
//        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.factory_set == P1P2_TO_RS232_PC)
    {
        LCDPutStr("P1P2 TO RS232 PC    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,10,90,310,210);
        
        LCDPutStr("DEVICE IS CONNECTED TO",18,116,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
        LCDPutStr("IOT MODULE PLEASE PRESS",12,142,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
        LCDPutStr("ENTER KEY TO START...",24,168,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
        
        sprintf(obuf,"{,PC,%d,}",lc_total_duty*10);
        UART_Send_String(UART_MODULE3,obuf);
//        memset(esp_buf,0,sizeof(esp_buf));
//        esp_sbyte = 0;
//        esp_index = 0;
//        esp_frame_flag = 0;
    }
    else if(mv.factory_set == SELECT_LENGTH_DRUM)
    {
        LCDPutStr("SELECT LENGTH DRUM  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        prv8_val1 = sys.para.sel_len_drum;
        
        LCDPutStr("LENGTH DRUM:  ",15,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("TYPE:",15,140,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,145,97,190,129);
        color_lcd_draw_rectangle(ILI9341_WHITE,10,165,310,210);
        
        sprintf(obuf,"%02d",prv8_val1);
        LCDPutStr(obuf,156,107,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
        
        slen = strlen(len_drum[prv8_val1])*12;
        cursX = 10+((300-slen)/2);
        LCDPutStr((char *)len_drum[prv8_val1],cursX,180,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
    }
    else if(mv.factory_set == SELECT_SYSTEM)
    {
        LCDPutStr("SELECT SYSTEM       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        prv16_val1 = (uint8_t)sys.para.Select_System;
        
        LCDPutStr("SYSTEM NUMBER:",15,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); //SELECT SYSTEM
        LCDPutStr("TYPE:",15,140,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,145,97,190,129);
        color_lcd_draw_rectangle(ILI9341_WHITE,10,165,310,210);
        
        sprintf(obuf,"%02d",prv16_val1);
        LCDPutStr(obuf,156,107,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
        
        slen = strlen(sys_sel[prv16_val1])*12;
        cursX = 10+((300-slen)/2);
        LCDPutStr((char *)sys_sel[prv16_val1],cursX,180,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
    }
    else if(mv.factory_set == ERASE_DATA_LOGS)  //change here 25/04/23 v1.16 reserved
    {
        LCDPutStr("ERASE DATA LOGS     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
    }
    else if(mv.factory_set == DEFAULT_BL_ADC_COUNT)  //change here 25/04/23 v1.16 reserved
    {
        LCDPutStr("DEFLT BM LEN ADC CNT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
    }
    else if(mv.factory_set == STICKER_TYPE)  //change here 25/04/23 v1.16 reserved
    {
       LCDPutStr("SELECT STICKER TYPE ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
    }
    else if(mv.factory_set == MASTER_RESET)   //change here 26/04/23 added master reset v1.16
    {
        LCDPutStr("MASTER RESET        ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);         
        color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);        
        color_lcd_draw_rectangle(ILI9341_WHITE,100,130,200,170);   
        draw_hollow_rect(ILI9341_NAVY,102,132,198,168);
        prv8_val1 = 0;
        if(prv8_val1==0)  LCDPutStr("NO ",130,140,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        else              LCDPutStr("YES",130,140,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    }
 
}


/*============================================================================*/
/*
 * Function      :        TFT_Modify_Factory_Settings.
 * Description   :        Used to modify Factory setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Modify_Factory_Settings(void)
{
    if((mv.factory_set == CALIB_PRESSURE_P1_MIN)||(mv.factory_set == CALIB_PRESSURE_P2_MIN)||
       (mv.factory_set == CALIB_PRESSURE_P1_MAX)||(mv.factory_set == CALIB_PRESSURE_P2_MAX))
    {
        TFT_Set_Calib_Pressure_Values();
    }
    else if((mv.factory_set == WINDOW_SAMPLES_SIZE)||(mv.factory_set == WINDOW_SAMPLES_SIZE1)||
            (mv.factory_set == NUM_OF_CYLINDERS)||(mv.factory_set == HIGH_CUTOFF_ANGLE)||
            (mv.factory_set == SET_BAUDRATE)||(mv.factory_set == SET_MANBASKET_DUTY)||
            (mv.factory_set == SET_MANBASKET_CHANN))
    {
        TFT_Edit_2Digit_Factory_Menu();
    }
    else if(mv.factory_set == WRITE_TO_MEMORY)
    {
        Upload_CSV_File();
    }
    else if(mv.factory_set == CRANE_DETAILS)
    {
        TFT_Set_Crane_Details();
    }
    else if((mv.factory_set == SET_BM_ANGLE_MIN)||(mv.factory_set == SET_BM_LENGTH_MIN)||
            (mv.factory_set == SET_BM_ANGLE_MAX)||(mv.factory_set == SET_BM_LENGTH_MAX))
    {
        TFT_Set_Calib_LenAngle_Values();
    }
    else if(mv.factory_set == SET_CRANE_MODEL)
    {
        TFT_Set_Crane_Model();
    }
    else if(mv.factory_set == SELECT_SENSOR)
    {
        TFT_Select_Sensor_Type();
    }
//    else if(mv.factory_set == STICKER_TYPE)
//    {
//        
//    }
    else if(mv.factory_set == SET_INSALLATION_DATE)
    {
        TFT_Set_Install_Date();
    }
    else if((mv.factory_set == EN_LOAD_AVERAGING_VALUE)||(mv.factory_set == SET_PERCENTAGE_STATUS))
    {
        TFT_Enable_Disable_Factory_Menu();
    }
    else if(mv.factory_set == EN_NUMBER_OF_CALIB)       //Two cases
    {
        TFT_Select_Cal_Case_Factory_Menu();
    }
    else if(mv.factory_set == SET_SO_NUMBER)
    {
        TFT_Set_SO_Number();
    }
    else if(mv.factory_set == P1P2_TO_RS232_PC)
    {
        TFT_Send_Pressure_Curve();
    }
    else if((mv.factory_set == SET_RADIUS_CUTOFF)||(mv.factory_set == SET_CORRECTION_LOAD))
    {
        TFT_Edit_3Digit1Decimal_Factory_Menu();
    }
    else if(mv.factory_set == SELECT_LENGTH_DRUM)
    {
        TFT_Select_Length_Drum();
    }
    else if(mv.factory_set == SELECT_SYSTEM)
    {
        TFT_Select_System();
    }
    else if((mv.factory_set == ERASE_DATA_LOGS)||(mv.factory_set == DEFAULT_BL_ADC_COUNT)||(mv.factory_set == STICKER_TYPE)) //change here 25/04/23 v1.16 reserved
    {
        TFT_Set_Reserved_Factory_Menu();
    }
    else if(mv.factory_set == MASTER_RESET)   //change here 26/04/23 added master rest v1.16
    {
        TFT_Factory_Reset_Factory_Menu();
    }
}
/*============================================================================*/
/*
 * Function      : TFT_Factory_Reset_Factory_Menu
 * Description   : Used for master reset
 * Parameters    : None.
 * Return        : None.
*////added function here 26/04/23 added master rest
/*============================================================================*/
void TFT_Factory_Reset_Factory_Menu(void)  
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
            prv8_val1 = !prv8_val1;

            if(prv8_val1==0)  LCDPutStr("NO ",130,140,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            else              LCDPutStr("YES",130,140,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            if(prv8_val1==1) 
            {
            Factory_Default_Reset();//Reset_System_Parameters();
            Read_System_Parameters();
            }
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
            key.enter =0;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}
/*============================================================================*/
/*
 * Function      :        TFTCommon_Factory_Escape_Function.
 * Description   :        Used to take escape from Site menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTCommon_Factory_Escape_Function(void)
{
    if((mv.factory_set >= 1)&&(mv.factory_set <= 5))        TFTDisplay_Factory_Set_Menu(0);
    else if((mv.factory_set >= 6)&&(mv.factory_set <= 10))  TFTDisplay_Factory_Set_Menu(1);
    else if((mv.factory_set >= 11)&&(mv.factory_set <= 15)) TFTDisplay_Factory_Set_Menu(2);
    else if((mv.factory_set >= 16)&&(mv.factory_set <= 20)) TFTDisplay_Factory_Set_Menu(3);
    else if((mv.factory_set >= 21)&&(mv.factory_set <= 25)) TFTDisplay_Factory_Set_Menu(4);
    else if((mv.factory_set >= 26)&&(mv.factory_set <= 30)) TFTDisplay_Factory_Set_Menu(5);
    else if((mv.factory_set >= 31)&&(mv.factory_set <= 35)) TFTDisplay_Factory_Set_Menu(6);
    else if((mv.factory_set >= 36)&&(mv.factory_set <= 40)) TFTDisplay_Factory_Set_Menu(7);
}


/*============================================================================*/
/*
 * Function      :        TFT_Set_Calib_Pressure_Values.
 * Description   :        Used to set calibration pressure values and counts.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Calib_Pressure_Values(void)
{
    char pbuf[10],slen;
    
    while(1)
    {
        if((key.function == 1))        // FUNC Key
        {
            if(prv8_val1 == 1)
            {
                TFTCommon_Factory_Escape_Function();

                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
                break;
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*13),cursY,cursX+13,cursY+2);
                
                if(mv.factory_set == CALIB_PRESSURE_P1_MIN)   
                {
                    prv16_val1 = sys.para.calib_pressure1_min;
                    sprintf(pbuf,"%04d",prv16_val1);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 4;
                    common_long = prv16_val1;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else if(mv.factory_set == CALIB_PRESSURE_P1_MAX)   
                {
                    prv16_val1 = sys.para.calib_pressure1_max;
                    sprintf(pbuf,"%04d",prv16_val1);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 4;
                    common_long = prv16_val1;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else if(mv.factory_set == CALIB_PRESSURE_P2_MIN)   
                {
                    prv16_val1 = sys.para.calib_pressure2_min;
                    sprintf(pbuf,"%04d",prv16_val1);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 4;
                    common_long = prv16_val1;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else if(mv.factory_set == CALIB_PRESSURE_P2_MAX)   
                {
                    prv16_val1 = sys.para.calib_pressure2_max;
                    sprintf(pbuf,"%04d",prv16_val1);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 4;
                    common_long = prv16_val1;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                key.function = 0;
            }
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*13),cursY,cursX+13,cursY+2);
            
            if(mv.factory_set == CALIB_PRESSURE_P1_MIN)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.calib_pressure1_min = (uint16_t)common_long;
                    
                    prv16_val2 = sys.para.calib_P1LowAdcCount;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.calib_P1LowAdcCount = (uint16_t)common_long;
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            else if(mv.factory_set == CALIB_PRESSURE_P1_MAX)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.calib_pressure1_max = (uint8_t)common_long;
                    
                    prv16_val2 = sys.para.calib_P1HighAdcCount;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.calib_P1HighAdcCount = (uint8_t)common_long; 
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            else if(mv.factory_set == CALIB_PRESSURE_P2_MIN)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.calib_pressure2_min = (uint8_t)common_long;
                
                    prv16_val2 = sys.para.calib_P2LowAdcCount;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.calib_P2LowAdcCount = (uint16_t)common_long;
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            else if(mv.factory_set == CALIB_PRESSURE_P2_MAX)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.calib_pressure2_max = (uint8_t)common_long;
                    
                    prv16_val2 = sys.para.calib_P2HighAdcCount;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.calib_P2HighAdcCount = (uint16_t)common_long;
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            key.enter = 0;            
        }
        else
        {
            Inc_Dec_4Digit_Menu();
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Set_Calib_LenAngle_Values.
 * Description   :        Used to set calibration length-angle values and counts.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Calib_LenAngle_Values(void)
{
    char pbuf[10],slen;
    
    while(1)
    {
        if((key.function == 1))        // FUNC Key
        {
            if(prv8_val1 == 1)
            {
                TFTCommon_Factory_Escape_Function();

                menu_stat = FACTORY_SET_CODE_PAGE;
                key.function = 0;
                Delay_1ms(500);
                break;
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*13),cursY,cursX+13,cursY+2);
                
                if(mv.factory_set == SET_BM_ANGLE_MIN)   
                {
                    prv16_val1 = sys.para.cal_angle_min;
                    sprintf(pbuf,"%04.1f",((float)prv16_val1)/10.0);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 3;
                    common_long = prv16_val1;

                    cursX += common_byte*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else if(mv.factory_set == SET_BM_ANGLE_MAX)   
                {
                    prv16_val1 = sys.para.cal_angle_max;
                    sprintf(pbuf,"%04.1f",((float)prv16_val1)/10.0);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 3;
                    common_long = prv16_val1;

                    cursX += common_byte*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else if(mv.factory_set == SET_BM_LENGTH_MIN)   
                {
                    prv16_val1 = sys.para.cal_len_min;
                    sprintf(pbuf,"%04.1f",((float)prv16_val1)/10.0);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 3;
                    common_long = prv16_val1;

                    cursX += common_byte*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else if(mv.factory_set == SET_BM_LENGTH_MAX)   
                {
                    prv16_val1 = sys.para.cal_len_max;
                    sprintf(pbuf,"%04.1f",((float)prv16_val1)/10.0);
                    slen = strlen(pbuf)*13;
                    cursX = 45+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 1;          //Edit value
                    common_byte = 3;
                    common_long = prv16_val1;

                    cursX += common_byte*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                key.function = 0;
            }
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*13),cursY,cursX+13,cursY+2);
            
            if(mv.factory_set == SET_BM_ANGLE_MIN)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.cal_angle_min = (uint16_t)common_long;
                    
                    prv16_val2 = sys.para.cal_angle_min_cnt;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.cal_angle_min_cnt = (uint16_t)common_long;
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            else if(mv.factory_set == SET_BM_ANGLE_MAX)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.cal_angle_max = (uint16_t)common_long;
                    
                    prv16_val2 = sys.para.cal_angle_max_cnt;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.cal_angle_max_cnt = (uint16_t)common_long; 
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            else if(mv.factory_set == SET_BM_LENGTH_MIN)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.cal_len_min = (uint16_t)common_long;
                
                    prv16_val2 = sys.para.cal_len_min_cnt;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.cal_len_min_cnt = (uint16_t)common_long;
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            else if(mv.factory_set == SET_BM_LENGTH_MAX)   
            {
                if(prv8_val1 == 1)
                {
                    sys.para.cal_len_max = (uint16_t)common_long;
                    
                    prv16_val2 = sys.para.cal_len_max_cnt;
                    sprintf(pbuf,"%04d",prv16_val2);
                    slen = strlen(pbuf)*13;
                    cursX = 200+((100-slen)/2);
                    cursY = 100+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(pbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                    prv8_val1 = 2;          //Edit counts
                    common_byte = 4;
                    common_long = prv16_val2;

                    cursX += (common_byte-1)*13;
                    cursY += 19;
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    sys.para.cal_len_max_cnt = (uint16_t)common_long;
                    
                    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                    
                    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                    LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                    Delay_1ms(1500);

                    TFTCommon_Factory_Escape_Function();

                    menu_stat = FACTORY_SET_CODE_PAGE;
                    break;
                }
            }
            key.enter = 0;
        }
        else
        {
            if(prv8_val1 == 1)
                Inc_Dec_3Digit_1Decimal_Menu();
            else
                Inc_Dec_4Digit_Menu();
        }
    }
}

/*============================================================================*/
/*
 * Function      :        Upload_CSV_File.
 * Description   :        Used to upload csv file to SPI flash.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Upload_CSV_File(void)
{
    char cbuf[10];
    
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
                    prv8_val1++;
                    if(prv8_val1 > 2)  prv8_val1 = 0;
                    
                    LCDPutStr("       ",125,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    sprintf(cbuf,"%lu",baud[prv8_val1]);
                    LCDPutStr(cbuf,130,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    if(prv8_val1 > 0)   prv8_val1--;
                    else                prv8_val1 = 2;
                    LCDPutStr("       ",125,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    sprintf(cbuf,"%lu",baud[prv8_val1]);
                    LCDPutStr(cbuf,130,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            GPIO_Function(GPIO_PORTF,U3_TELE_RX_F0,GPIO_INPUT,0,DIGITAL_INPUT);
            GPIO_Function(GPIO_PORTF,U3_TELE_TX_F1,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
            PORTFbits.RF1 = 1;
            PPS_Mapping(RPI96_MAPPING,PPS_INPUT,UART3Rx);
            PPS_Mapping(RP97_MAPPING,PPS_OUTPUT,UART3Tx);
            UART_Initialize(UART_MODULE3,baud[prv8_val1],1);
            
            LCDPutStr("SPI FLASH ERASE:",110,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            color_lcd_draw_rectangle(ILI9341_WHITE,130,155,215,187);
            LCDPutStr("NO ",152,163,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            menu_stat = WRITE_TO_MEMORY_PAGE2;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            break;
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Enable_Disable_Factory_Menu.
 * Description   :        Used to do enable disable menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Enable_Disable_Factory_Menu(void)
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
            prv8_val1 = !prv8_val1;

            TFTShow_Enable_Disable();

            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.factory_set == EN_LOAD_AVERAGING_VALUE)
                sys.para.load_avg_stat_bit = prv8_val1;
            else if(mv.factory_set == SET_PERCENTAGE_STATUS)
                sys.para.perc_fact_stat_bit = prv8_val1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}



/*============================================================================*/
/*
 * Function      :        TFT_Edit_2Digit_Factory_Menu.
 * Description   :        Used to set two digit menus of factory settings.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Edit_2Digit_Factory_Menu(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
//            ((mv.factory_set == WINDOW_SAMPLES_SIZE)||(mv.factory_set == WINDOW_SAMPLES_SIZE1)||
//            (mv.factory_set == NUM_OF_CYLINDERS)||(mv.factory_set == HIGH_CUTOFF_ANGLE)||
//            (mv.factory_set == SET_BAUDRATE)||(mv.factory_set == SET_MANBASKET_DUTY)||
//            (mv.factory_set == SET_MANBASKET_CHANN))
            
            if(mv.factory_set == WINDOW_SAMPLES_SIZE)          
                sys.para.window_sample_size = (uint8_t)common_long;
            else if(mv.factory_set == WINDOW_SAMPLES_SIZE1)
                sys.para.window_sample_size1 = (uint8_t)common_long;
            else if(mv.factory_set == NUM_OF_CYLINDERS)
                sys.para.num_of_cylinders = (uint8_t)common_long;
            else if(mv.factory_set == SET_BAUDRATE)
                sys.para.baudrate = (uint8_t)common_long;
            else if(mv.factory_set == SET_MANBASKET_DUTY)
            {
                if(sys.para.Select_System == PNC_FORK)
                    sys.para.fork_duty = (uint8_t)common_long;
                else if(sys.para.Select_System == ACE_MANBASKET_HXP)
                    sys.para.manbas_duty = (uint8_t)common_long;
            }
            else if(mv.factory_set == SET_MANBASKET_CHANN)
                sys.para.manbas_chann = (uint8_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_Crane_Details.
 * Description   :        Used to set crane details.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Crane_Details(void)
{
    char dbuf[10],slen;
    
    while(1)
    {
        if((key.bypass == 1)||(key.duty == 1))
        {
            if(key.duty == 1) 
            {
                if(pos_t < 3)
                {
                    pos_t++;
                    if(pos_t >= 3)
                    {
                        TFT_Draw_Cursor_Dynam_Width(pos_t+1, 9, ILI9341_WHITE, ILI9341_RED);
                    }
                    else
                    {
                        TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                    }
                }
                else
                {
                    pos_t = 0;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
            }
            else
            {
                if(pos_t > 0)
                {
                    pos_t--;  
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else
                {
                    pos_t = 3;                    
                    TFT_Draw_Cursor_Dynam_Width(pos_t+1, 9, ILI9341_WHITE, ILI9341_RED);
                }
            }
            key.bypass = 0;
            key.duty = 0;
        }
        else if(key.increment == 1)
        {
            while(key.inc_ftp == 1)
            {
                Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%05.3f",((float)common_long)/1000.0);
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }  
            key.increment = 0;
        }
        else if(key.decrement == 1)
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%05.3f",((float)common_long)/1000.0);
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }       
            key.decrement = 0;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            if(crane_detail_cnt > 1)
            {
                crane_detail_cnt--;
                
                if(crane_detail_cnt == 1)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.vertical_offset)/1000.0);       //Second time for cursor purpose
                    slen = strlen(dbuf)*9;
                    cursX = 80+((75-slen)/2);
                    cursY = 90+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);

                    common_byte = 4;
                    common_long = sys.para.vertical_offset;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 2)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.horizontal_offset)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 80+((75-slen)/2);
                    cursY = 140+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.horizontal_offset;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 3)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.rampivot_offset)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 80+((75-slen)/2);
                    cursY = 190+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.rampivot_offset;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 4)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.bm_cntr_line_offset)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 235+((75-slen)/2);
                    cursY = 90+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.bm_cntr_line_offset;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 5)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.piston_diameter)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 235+((75-slen)/2);
                    cursY = 140+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
        
                    common_byte = 4;
                    common_long = sys.para.piston_diameter;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
            }
            else if(crane_detail_cnt == 1)
            {
                TFTCommon_Factory_Escape_Function();

                menu_stat = FACTORY_SET_CODE_PAGE;
            }
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            if(crane_detail_cnt == 1)
                sys.para.vertical_offset = (uint16_t)common_long;
            else if(crane_detail_cnt == 2)
                sys.para.horizontal_offset = (uint16_t)common_long;
            else if(crane_detail_cnt == 3)
                sys.para.rampivot_offset = (uint16_t)common_long;
            else if(crane_detail_cnt == 4)
                sys.para.bm_cntr_line_offset = (uint16_t)common_long;
            else if(crane_detail_cnt == 5)
                sys.para.piston_diameter = (uint16_t)common_long;
            else if(crane_detail_cnt == 6)
                sys.para.rod_diameter = (uint16_t)common_long;
            
            if(crane_detail_cnt < 6)
            {
                crane_detail_cnt++;
                
                if(crane_detail_cnt == 2)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.horizontal_offset)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 80+((75-slen)/2);
                    cursY = 140+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.horizontal_offset;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 3)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.rampivot_offset)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 80+((75-slen)/2);
                    cursY = 190+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.rampivot_offset;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 4)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.bm_cntr_line_offset)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 235+((75-slen)/2);
                    cursY = 90+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.bm_cntr_line_offset;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 5)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.piston_diameter)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 235+((75-slen)/2);
                    cursY = 140+15-8; 
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.piston_diameter;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
                else if(crane_detail_cnt == 6)
                {
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*9),cursY,cursX+9,cursY+2);//Clear cursor position
                    
                    sprintf(dbuf,"%05.3fM",((float)sys.para.rod_diameter)/1000.0);
                    slen = strlen(dbuf)*9;
                    cursX = 235+((75-slen)/2);
                    cursY = 190+15-8; 
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    
                    common_byte = 4;
                    common_long = sys.para.rod_diameter;

                    cursX += common_byte*9;
                    cursY += 17;
                    TFT_Draw_Cursor_Dynam_Width(pos_t, 9, ILI9341_WHITE, ILI9341_RED);
                }
            }
            else if(crane_detail_cnt == 6)
            {
                //Save data to Flash
                f11 = (sys.para.vertical_offset*1.0);        // (a) x.xxx
                f11 = (f11/1000.0);
                    
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
                }
                
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
                }
                
                f11 = (sys.para.piston_diameter*1.0);        // x.xxx
                f11 = (f11/2000.0);

                PistonArea_Int = (uint32_t)(PI*f11*f11*100000.0);
                
                f11 = (sys.para.rod_diameter*1.0);        // x.xxx
                f11 = (f11/2000.0);

                RodArea_Int = (uint32_t)(PI*f11*f11*100000.0);

                DiffArea_Int = (PistonArea_Int - RodArea_Int);
                
                LCDPutStr("GammaRad",5,95,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("SinG Rad",5,145,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("CosG Rad",5,195,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("Const K:",162,95,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("PSTON Ap",162,145,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr(" ROD Ar:",162,195,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

                color_lcd_draw_rectangle(ILI9341_WHITE,80,90,155,120);
                draw_hollow_rect(ILI9341_NAVY,82,92,153,118);
                color_lcd_draw_rectangle(ILI9341_WHITE,80,140,155,170);
                draw_hollow_rect(ILI9341_NAVY,82,142,153,168);
                color_lcd_draw_rectangle(ILI9341_WHITE,80,190,155,220);
                draw_hollow_rect(ILI9341_NAVY,82,192,153,218);

                color_lcd_draw_rectangle(ILI9341_WHITE,235,90,310,120);
                draw_hollow_rect(ILI9341_NAVY,237,92,308,118);
                color_lcd_draw_rectangle(ILI9341_WHITE,235,140,310,170);
                draw_hollow_rect(ILI9341_NAVY,237,142,308,168);
                color_lcd_draw_rectangle(ILI9341_WHITE,235,190,310,220);
                draw_hollow_rect(ILI9341_NAVY,237,192,308,218);

                sprintf(dbuf,"%05.3f",((float)Gamma_Int_Rad)/1000.0);
                slen = strlen(dbuf)*9;
                cursX = 80+((75-slen)/2);
                cursY = 90+15-8; 
                valX = cursX;
                valY = cursY;
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);

                sprintf(dbuf,"%05.3f",((float)sin_Gamma_Int)/1000.0);
                slen = strlen(dbuf)*9;
                cursX = 80+((75-slen)/2);
                cursY = 140+15-8; 
                valX = cursX;
                valY = cursY;
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);

                sprintf(dbuf,"%05.3f",((float)cos_Gamma_Int)/1000.0);
                slen = strlen(dbuf)*9;
                cursX = 80+((75-slen)/2);
                cursY = 190+15-8; 
                valX = cursX;
                valY = cursY;
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);

                sprintf(dbuf,"%05.3f",((float)constK_Int)/1000.0);
                slen = strlen(dbuf)*9;
                cursX = 235+((75-slen)/2);
                cursY = 90+15-8; 
                valX = cursX;
                valY = cursY;
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);

                sprintf(dbuf,"%07.5f",((float)PistonArea_Int)/100000.0);
                slen = strlen(dbuf)*9;
                cursX = 235+((75-slen)/2);
                cursY = 140+15-8; 
                valX = cursX;
                valY = cursY;
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);

                sprintf(dbuf,"%07.5f",((float)RodArea_Int)/100000.0);
                slen = strlen(dbuf)*9;
                cursX = 235+((75-slen)/2);
                cursY = 190+15-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                LCDPutStr(dbuf,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(3000);
                
                color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
                
                LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                Delay_1ms(1500);
                
                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                
                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                
                TFTCommon_Factory_Escape_Function();
                menu_stat = FACTORY_SET_CODE_PAGE;
            }
            
            key.enter = 0;
            break;
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Edit_3Digit_Factory_Menu.
 * Description   :        Used to set three digit menus of factory settings.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Edit_3Digit_Factory_Menu(void)
{
    while(1)
    {
//        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
//        {
//            TFTCommon_Factory_Escape_Function();
//            
//            menu_stat = FACTORY_SET_CODE_PAGE;
//            key.function = 0;
//            Delay_1ms(500);
//            break;
//        }
//        else if(key.enter == 1)        // ENTR Key
//        {
//            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
//            
//            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
//            
//            if(mv.factory_set == REVRSE_DUTY_LOW)          
//                sys.para.revrs_duty_low = (uint16_t)common_long;
//            else if(mv.factory_set == REVRSE_DUTY_HIGH)
//                sys.para.revrs_duty_hi = (uint16_t)common_long;
//            else if(mv.factory_set == RUNNER_DUTY_LOW)
//                sys.para.runner_duty_low = (uint16_t)common_long;
//            else if(mv.factory_set == RUNNER_DUTY_HIGH)
//                sys.para.runner_duty_hi = (uint16_t)common_long;
//            
//            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
//            
//            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
//            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
//            
//            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
//            Delay_1ms(1500);
//            
//            TFTCommon_Factory_Escape_Function();
//            
//            menu_stat = FACTORY_SET_CODE_PAGE;
//            key.enter = 0;
//            break;
//        }
//        else
//        {
//            Inc_Dec_3Digit_Menu();
//        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Select_Cal_Case_Factory_Menu.
 * Description   :        Used to set calculation case.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Select_Cal_Case_Factory_Menu(void)
{
    char obuf[10];
    
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
            
            if(prv8_val1 == 0)
            {
                sprintf(obuf,"CASE1");
            }
            else
            {
                sprintf(obuf,"CASE2");
            }
            
            LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.num_cal = prv8_val1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Set_SO_Number.
 * Description   :        Used to set Sales order number.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_SO_Number(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.so_number = common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_5Digit_Menu();
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Send_Pressure_Curve.
 * Description   :        Used to send pressure curve data to PC/ESP32-IOT.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Send_Pressure_Curve(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_WHITE,10,90,310,210);
            LCDPutStr("SENDING DATA TO IOT",36,116,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
            LCDPutStr("MODULE PLEASE WAIT...!!",12,142,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
            Send_Pressure_Curve_Uart();
            LCDPutStr("COMPLETED",24,168,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
            Delay_1ms(1500);
            TFTCommon_Factory_Escape_Function();
            key.enter = 0;
            menu_stat = FACTORY_SET_CODE_PAGE;
            break;
        }
    }    
}

/*============================================================================*/
/*
 * Function      :        TFT_Edit_3Digit1Decimal_Factory_Menu.
 * Description   :        Used to set 3 digit with 1 decimal point menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Edit_3Digit1Decimal_Factory_Menu(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.factory_set == SET_RADIUS_CUTOFF)
                sys.para.Radius_Cutoff = (uint16_t)common_long;
            else if(mv.factory_set == SET_CORRECTION_LOAD)
                sys.para.correction_load = (uint16_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_Install_Date.
 * Description   :        Used to set on site installation date.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Install_Date(void)
{
    char dbuf[15],lbuf[10];
    
    while(1)
    {
        if((key.bypass == 1)||(key.duty == 1))
        {
            if(key.duty == 1) 
            {
                if(pos_t < 7)
                {
                    pos_t++;
                    if((pos_t==4)||(pos_t==5))      TFT_Draw_Cursor(pos_t+1,ILI9341_WHITE,ILI9341_RED);
                    else if((pos_t==6)||(pos_t==7)) TFT_Draw_Cursor(pos_t+2,ILI9341_WHITE,ILI9341_RED);
                    else                            TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    TFT_Draw_Cursor(pos_t+2,ILI9341_WHITE,ILI9341_WHITE);
                    pos_t = 0;                    
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
            }
            else
            {
                if(pos_t > 0)
                {
                    pos_t--;
                    if((pos_t>=0)&&(pos_t<=3))      TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                    else if((pos_t==5)||(pos_t==4)) TFT_Draw_Cursor(pos_t+1,ILI9341_WHITE,ILI9341_RED);
                    else
                    {
                        TFT_Draw_Cursor(9,ILI9341_WHITE,ILI9341_WHITE);
                        TFT_Draw_Cursor(pos_t+2,ILI9341_WHITE,ILI9341_RED);
                    }
                }
                else
                {
                    TFT_Draw_Cursor(0,ILI9341_WHITE,ILI9341_RED);
                    pos_t = 7;
                    TFT_Draw_Cursor(pos_t+2,ILI9341_WHITE,ILI9341_RED);
                }
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
                    Modify_System_Parameter(common_byte,INC_DATA,pos_t,&common_long);

                    sprintf(lbuf,"%08lu",common_long);
                    sprintf(dbuf,"%c%c/%c%c/%c%c%c%c",lbuf[0],lbuf[1],lbuf[2],lbuf[3],lbuf[4],lbuf[5],lbuf[6],lbuf[7]);
                    LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);

                    sprintf(lbuf,"%08lu",common_long);
                    sprintf(dbuf,"%c%c/%c%c/%c%c%c%c",lbuf[0],lbuf[1],lbuf[2],lbuf[3],lbuf[4],lbuf[5],lbuf[6],lbuf[7]);
                    LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sprintf(lbuf,"%08lu",common_long);
            
            sys.para.insta_dd = ((lbuf[0]-0x30)*10) + (lbuf[1]-0x30);
            sys.para.insta_mm = ((lbuf[2]-0x30)*10) + (lbuf[3]-0x30);
            sys.para.insta_yy = (((uint16_t)(lbuf[4]-0x30))*1000) + (((uint16_t)(lbuf[5]-0x30))*100) + ((lbuf[6]-0x30)*10) + (lbuf[7]-0x30);
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Set_Crane_Model.
 * Description   :        Used to select crane model.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Crane_Model(void)
{
    char obuf[50];
    uint8_t slen;
    uint16_t TempCount;
    
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
                    if(crane_id < mv.max)   crane_id++;  
                    else                    crane_id = mv.min;
                    
                    sprintf(obuf,"%05d",crane_ids[crane_id-1]);
                    slen = strlen(obuf)*13;
                    cursX = 180+((100-slen)/2);
                    cursY = 100+20-8; 
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    //LCDPutStr("                    ",valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    flash_page_addr = ONE_SECTOR_SIZE+2+(crane_id-1)*32;//skip 2 bytes of id
                    for(TempCount=0; TempCount<16; TempCount++)
                    {
                        crane_make[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
                    }
                    slen = strlen(crane_make)*8;
                    cursX = 40+((240-slen)/2);
                    cursY = 165+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    color_lcd_draw_rectangle(ILI9341_WHITE,40,165,280,205);   
                    draw_hollow_rect(ILI9341_NAVY,42,167,278,203);
                    LCDPutStr(crane_make,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    if(crane_id > mv.min) crane_id--;
                    else                  crane_id = mv.max;
                    
                    sprintf(obuf,"%05d",crane_ids[crane_id-1]);
                    slen = strlen(obuf)*13;
                    cursX = 180+((100-slen)/2);
                    cursY = 100+20-8; 
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    flash_page_addr = ONE_SECTOR_SIZE+2+(crane_id-1)*32;//skip 2 bytes of id
                    for(TempCount=0; TempCount<16; TempCount++)
                    {
                        crane_make[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
                    }
                    slen = strlen(crane_make)*8;
                    cursX = 40+((240-slen)/2);
                    cursY = 165+20-8;
                    pos_t = 0;
                    valX = cursX;
                    valY = cursY;
                    color_lcd_draw_rectangle(ILI9341_WHITE,40,165,280,205);   
                    draw_hollow_rect(ILI9341_NAVY,42,167,278,203);
                    LCDPutStr(crane_make,valX,valY,MEDIUM,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            flash_page_addr = ONE_SECTOR_SIZE+18 + (crane_id-1)*32;
            sys.para.crane_page_index = (SPIFlash_Read_Byte(flash_page_addr)*256)+SPIFlash_Read_Byte(flash_page_addr+1);
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            Read_Startup_SPIFlash();
            Update_System_Parameters();
            color_lcd_draw_rectangle(ILI9341_NAVY,5,45,314,230);
            LCDPutStr("CRANE DETAILS",81,70,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr("MODEL  :",10,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr("MAKE   :",10,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr("TYPE   :",10,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            
            LCDPutStr(crane_model,110,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr(crane_make,110,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr(crane_type,110,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(2000);
            
            color_lcd_draw_rectangle(ILI9341_NAVY,5,70,310,220);    //Clear Setting page
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Select_Sensor_Type.
 * Description   :        Used to select sensor type.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Select_Sensor_Type(void)
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
                    if(prv8_val1 < 3)  prv8_val1++;  
                    else               prv8_val1 = 1;
                    
                    LCDPutStr((char *)sensor_sel[prv8_val1-1],valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    if(prv8_val1 > 1)   prv8_val1--;
                    else                prv8_val1 = 3;
                    
                    LCDPutStr((char *)sensor_sel[prv8_val1-1],valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            if(prv8_val1 == 1)
            {
                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                sys.para.sel_sensor = prv8_val1;
                PRCHN = 1.556224;
                sys.para.calib_pressure1_min = 0;
                sys.para.calib_P1LowAdcCount = 655;
                sys.para.calib_pressure1_max = 400;
                sys.para.calib_P1HighAdcCount = 3276;

                sys.para.calib_pressure2_min = 0;
                sys.para.calib_P2LowAdcCount = 655;
                sys.para.calib_pressure2_max = 400;
                sys.para.calib_P2HighAdcCount = 3276;
                
                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                Delay_1ms(1500);
            }
            else if(prv8_val1 == 2)
            {
                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                
                sys.para.sel_sensor = prv8_val1;
                
                PRCHN = 1.073060;
                sys.para.calib_pressure1_min = 0;
                sys.para.calib_P1LowAdcCount = 390;
                sys.para.calib_pressure1_max = 344;
                sys.para.calib_P1HighAdcCount = 3685;

                sys.para.calib_pressure2_min = 0;
                sys.para.calib_P2LowAdcCount = 390;
                sys.para.calib_pressure2_max = 344;
                sys.para.calib_P2HighAdcCount = 3685;
                
                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                Delay_1ms(1500);
            }
            else if(prv8_val1 == 3)
            {
                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                
                sys.para.sel_sensor = prv8_val1;
                
                PRCHN = 1.329486;
                sys.para.calib_pressure1_min = 0;
                sys.para.calib_P1LowAdcCount = 410;
                sys.para.calib_pressure1_max = 400;
                sys.para.calib_P1HighAdcCount = 3685;

                sys.para.calib_pressure2_min = 0;
                sys.para.calib_P2LowAdcCount = 410;
                sys.para.calib_pressure2_max = 400;
                sys.para.calib_P2HighAdcCount = 3686;
                
                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

                LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                Delay_1ms(1500);
            }  
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Select_Length_Drum.
 * Description   :        Used to select length drum.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Select_Length_Drum(void)
{
    char obuf[50];
    uint8_t slen;
    
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
                    if(prv8_val1 < LEN_DRUM_MAX)    prv8_val1++;  
                    else                            prv8_val1 = 0;
                    
                    sprintf(obuf,"%02d",prv8_val1);
                    LCDPutStr(obuf,156,107,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,75,180,260,200);
                    slen = strlen(len_drum[prv8_val1])*12;
                    cursX = 10+((300-slen)/2);
                    LCDPutStr((char *)len_drum[prv8_val1],cursX,180,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    if(prv8_val1 > 0)   prv8_val1--;
                    else                prv8_val1 = LEN_DRUM_MAX;
                    
                    sprintf(obuf,"%02d",prv8_val1);
                    LCDPutStr(obuf,156,107,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,75,180,260,200);
                    slen = strlen(len_drum[prv8_val1])*12;
                    cursX = 10+((300-slen)/2);
                    LCDPutStr((char *)len_drum[prv8_val1],cursX,180,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.sel_len_drum = prv8_val1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Select_System.
 * Description   :        Used to select system.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Select_System(void)
{
    char obuf[50];
    uint8_t slen;
    
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
                    if(prv16_val1 < MAX_SEL_SYSTEM) prv16_val1++;  
                    else                            prv16_val1 = 0;
                    
                    sprintf(obuf,"%02d",prv16_val1);
                    LCDPutStr(obuf,156,107,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,75,180,260,200);
                    slen = strlen(sys_sel[prv16_val1])*12;
                    cursX = 10+((300-slen)/2);
                    LCDPutStr((char *)sys_sel[prv16_val1],cursX,180,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    if(prv16_val1 > 0)  prv16_val1--;
                    else                prv16_val1 = MAX_SEL_SYSTEM;
                    
                    sprintf(obuf,"%02d",prv16_val1);
                    LCDPutStr(obuf,156,107,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    
                    color_lcd_draw_rectangle(ILI9341_WHITE,75,180,260,200);
                    slen = strlen(sys_sel[prv16_val1])*12;
                    cursX = 10+((300-slen)/2);
                    LCDPutStr((char *)sys_sel[prv16_val1],cursX,180,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
                    Delay_1ms(500);
                }
            }
            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.Select_System = prv16_val1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}

void TFT_Set_Reserved_Factory_Menu(void)
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
            TFTCommon_Factory_Escape_Function();
            
            menu_stat = FACTORY_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
    
}







