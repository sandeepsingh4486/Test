
#include "main.h"

/*============================================================================*/
/*
 * Function      :        TFTDisplay_Supervisor_Set_Menu.
 * Description   :        Used to display supervisor menu first page.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Supervisor_Set_Menu(uint8_t page)
{
    uint8_t rcnt;
    
    mv.max = 60;
    mv.min = 1;
    
    Set_Codes_Menu_Outlines();
    
    TFTSupervisor_Setcode_Pages(page);
    
    rcnt = mv.supervisor_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(0,rcnt);
}




/*============================================================================*/
/*
 * Function      :        TFTSelect_Supervisor_Setcode_Menu.
 * Description   :        Used to highlight supervisor menu pages.
 * Parameters    :        sel-highlight row number(1 to 5).
 * Return        :        None.
*/
/*============================================================================*/
void TFTSelect_Supervisor_Setcode_Menu(uint8_t sel)
{
    uint8_t rcnt;
    
    rcnt = mv.supervisor_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(sel,rcnt);
    
    if(((mv.supervisor_set == 1)&&(sel == 1))||((mv.supervisor_set == 5)&&(sel == 0)))        {Clear_Rows();TFTSupervisor_Setcode_Pages(0);}
    else if(((mv.supervisor_set == 6)&&(sel == 1))||((mv.supervisor_set == 10)&&(sel == 0)))  {Clear_Rows();TFTSupervisor_Setcode_Pages(1);}
    else if(((mv.supervisor_set == 11)&&(sel == 1))||((mv.supervisor_set == 15)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(2);}
    else if(((mv.supervisor_set == 16)&&(sel == 1))||((mv.supervisor_set == 20)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(3);}
    else if(((mv.supervisor_set == 21)&&(sel == 1))||((mv.supervisor_set == 25)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(4);}
    else if(((mv.supervisor_set == 26)&&(sel == 1))||((mv.supervisor_set == 30)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(5);}
    else if(((mv.supervisor_set == 31)&&(sel == 1))||((mv.supervisor_set == 35)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(6);}
    else if(((mv.supervisor_set == 36)&&(sel == 1))||((mv.supervisor_set == 40)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(7);}
    else if(((mv.supervisor_set == 41)&&(sel == 1))||((mv.supervisor_set == 45)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(8);}
    else if(((mv.supervisor_set == 46)&&(sel == 1))||((mv.supervisor_set == 50)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(9);}
    else if(((mv.supervisor_set == 51)&&(sel == 1))||((mv.supervisor_set == 55)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(10);}
    else if(((mv.supervisor_set == 56)&&(sel == 1))||((mv.supervisor_set == 60)&&(sel == 0))) {Clear_Rows();TFTSupervisor_Setcode_Pages(11);}
}



/*============================================================================*/
/*
 * Function      :        TFTDisplay_Supervisor_Settings.
 * Description   :        Used to display supervisor setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Supervisor_Settings(void)
{
    char obuf[10],sbuf[10];
    uint8_t slen;
    
    sprintf(obuf,"%03d",mv.supervisor_set+99);
    LCDPutStr(obuf,18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    color_lcd_draw_rectangle(ILI9341_NAVY,75,57,260,75);    //Clear title
    color_lcd_draw_rectangle(ILI9341_WHITE,281,51,309,79);
    LCDPutStr(">>",285,57,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
    
    if(((mv.supervisor_set >= SET_SP1_VALUE)&&(mv.supervisor_set <= SET_SP4_VALUE)))
    {
        if(mv.supervisor_set == SET_SP1_VALUE)
        {
            LCDPutStr("SET MHOOK SP1 VALUE ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.sp1_perc;
        }
        else if(mv.supervisor_set == SET_SP2_VALUE)
        {
            LCDPutStr("SET MHOOK SP2 VALUE ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.sp2_perc;
        }
        else if(mv.supervisor_set == SET_SP3_VALUE)
        {
            LCDPutStr("SET MHOOK SP3 VALUE ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.sp3_perc;
        }
        else if(mv.supervisor_set == SET_SP4_VALUE)
        {
            LCDPutStr("SET MHOOK SP4 VALUE ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.sp4_perc;
        }
        
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
        
        sprintf(obuf,"%03d",prv16_val1);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
            
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutChar('%',valX+50,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutChar('%',valX+50,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        common_byte = 3;
        common_long = prv16_val1;    
        
        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.supervisor_set == SET_DUTY_TYPE)
    {
        if(sys.para.Select_System == FORK_LIFT)
        {
            LCDPutStr("CALIB PRESS MIN     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            byt1 = 0;       //This variable decides the min or max pressure calibration
            prv8_val1 = 1;      //start of point calibration
            
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
            
            if(sys.para.forkcalib_press_min[prv8_val1-1][0] > lc_max_capacity)
            {
                sys.para.forkcalib_press_min[prv8_val1-1][0] = 0;
                sys.para.forkcalib_press_min[prv8_val1-1][1] = 0;
            }
            
            TFT_Forklift_Load_MPoint_Menu();
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            LCDPutStr("CALIB OUT TRIG MIN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            byt1 = 0;       //This variable decides the min or max pressure calibration
            LCDPutStr("P1:",15,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("P2:",15,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);     
            LCDPutStr("P3:",170,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("P4:",170,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);  
            color_lcd_draw_rectangle(ILI9341_WHITE,45,100,145,140);
            draw_hollow_rect(ILI9341_NAVY,47,102,143,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,45,165,145,205); 
            draw_hollow_rect(ILI9341_NAVY,47,167,143,203);
            color_lcd_draw_rectangle(ILI9341_WHITE,200,100,300,140);
            draw_hollow_rect(ILI9341_NAVY,202,102,298,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,200,165,300,205);
            draw_hollow_rect(ILI9341_NAVY,202,167,298,203);
        }
        else
        {
            LCDPutStr("SET DUTY TYPE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            temp_duty_indx = 1;
            sub_menu_flag = 0;
            len_calib_cnt = sys.para.duty_type[temp_duty_indx-1];
            if((len_calib_cnt == 0)||(len_calib_cnt > 5))
            {
                len_calib_cnt = 1;
                sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt;
            }
            
            LCDPutStr("DUTY NUMBER    :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("CALIB. POINTS  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
            draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
            draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
            
            sprintf(obuf,"%02d",temp_duty_indx);
            sprintf(sbuf,"%02d",len_calib_cnt);
            slen = strlen(obuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8; 
            pos_t = 0;
            valX = cursX;
            valY = cursY;
            
            LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            LCDPutStr(sbuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
            common_byte = 2;
            common_long = temp_duty_indx;    
            
            cursX += (common_byte-1)*13;
            cursY += 19;
            TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
        }
    }
    else if(mv.supervisor_set == CALIB_HOOK_LOAD)
    {
        if(sys.para.Select_System == FORK_LIFT)
        {
            LCDPutStr("CALIB PRESS MAX     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            byt1 = 1;       //This variable decides the min or max pressure calibration
            prv8_val1 = 1;  //start of point calibration
            
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
            
            if(sys.para.forkcalib_press_max[prv8_val1-1][0] > lc_max_capacity)
            {
                sys.para.forkcalib_press_max[prv8_val1-1][0] = 0;
                sys.para.forkcalib_press_max[prv8_val1-1][1] = 0;
            }
            
            TFT_Forklift_Load_MPoint_Menu();
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            LCDPutStr("CALIB OUT TRIG MAX  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            press_chann_num = 1;
            byt1 = 1;       //This variable decides the min or max pressure calibration
            LCDPutStr("P1:",15,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("P2:",15,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);     
            LCDPutStr("P3:",170,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("P4:",170,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);  
            color_lcd_draw_rectangle(ILI9341_WHITE,45,100,145,140);
            draw_hollow_rect(ILI9341_NAVY,47,102,143,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,45,165,145,205); 
            draw_hollow_rect(ILI9341_NAVY,47,167,143,203);
            color_lcd_draw_rectangle(ILI9341_WHITE,200,100,300,140);
            draw_hollow_rect(ILI9341_NAVY,202,102,298,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,200,165,300,205);
            draw_hollow_rect(ILI9341_NAVY,202,167,298,203);
        }
        else
        {
            LCDPutStr("CALIB HOOK LOAD     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            temp_duty_indx = sys.para.duty;
            
            LCDPutStr("SELECT DUTY   :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
//            LCDPutStr("ADJUST ANGLE AND LENGTH",60,155,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
            draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
            
//            color_lcd_draw_rectangle(ILI9341_WHITE,180,180,280,220);  
//            draw_hollow_rect(ILI9341_NAVY,182,182,278,218);
//            
//            color_lcd_draw_rectangle(ILI9341_WHITE,45,180,145,220);  
//            draw_hollow_rect(ILI9341_NAVY,47,182,143,218);
            
            sprintf(obuf,"%02d",temp_duty_indx);            
            slen = strlen(obuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8; 
            pos_t = 0;
            valX = cursX;
            valY = cursY;
            
            LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
//            sprintf(obuf,"%04.1f",((float)bm_angle)/10.0); 
//            LCDPutStr(obuf,67,192,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//            Draw_Circle(123,192,2,ILI9341_BLACK);
//            
//            sprintf(obuf,"%04.1fM",((float)TotalBmLength)/10.0); 
//            LCDPutStr(obuf,202,192,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
            common_byte = 2;
            common_long = temp_duty_indx;
            
            cursX += (common_byte-1)*13;
            cursY += 19;
            TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            menu_stat = HOOK_LOAD_CALIB_PAGE1;
        }
    }
    else if((mv.supervisor_set == SET_BOOM_OFFSET)||(mv.supervisor_set == SET_BM_HEAD_OFFSET)||
            (mv.supervisor_set == SET_BM_TIP_OFFSET)||(mv.supervisor_set == LOW_CUTOFF_ANGLE)||
            (mv.supervisor_set == SET_SLEW_OFFSET))
    {
        if(mv.supervisor_set == SET_BOOM_OFFSET)
        {
            LCDPutStr("SET BOOM OFFSET     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.bm_offset;
        }
        else if(mv.supervisor_set == SET_BM_HEAD_OFFSET)
        {
            LCDPutStr("SET BOOM HEAD OFFSET",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.bm_head_offset;
        }
        else if(mv.supervisor_set == SET_BM_TIP_OFFSET)
        {
            LCDPutStr("SET BOOM TIP OFFSET ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.bm_tip_offset;
        }
        else if(mv.supervisor_set == LOW_CUTOFF_ANGLE)
        {
            LCDPutStr("SET LOW CUTOFF ANGLE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.low_cutoff_angl;
        }
        else if(mv.supervisor_set == SET_SLEW_OFFSET)
        {
            LCDPutStr("SET SLEW OFFSET     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_sign_val = sys.para.slew_offset;
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
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        if((mv.supervisor_set == LOW_CUTOFF_ANGLE))
        {
            
        }
        else
        {
            LCDPutChar('M',valX+66,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            LCDPutChar('M',valX+66,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        
        common_byte = 3;
        common_long = prv16_sign_val;   //Take positive number to modify    

        cursX += (common_byte+1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.supervisor_set == SET_HOOK_LOAD)||(mv.supervisor_set == RIG_LOAD_LIMIT)||
            (mv.supervisor_set == RIG_BM_LENGTH_LIMIT)||(mv.supervisor_set == SET_MAX_BOOM_LENGTH)||
            (mv.supervisor_set == SET_ZERO_LOAD_MASKING)||(mv.supervisor_set == SET_HEIGHT_OFFSET))
    {
        if(mv.supervisor_set == SET_HOOK_LOAD)
        {
            LCDPutStr("SET HOOK LOAD       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.hook_load;
        }
        else if(mv.supervisor_set == RIG_LOAD_LIMIT)
        {
            LCDPutStr("RIG LOAD LIMIT      ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.rig_load_lmt;
        }
        else if(mv.supervisor_set == RIG_BM_LENGTH_LIMIT)
        {
            LCDPutStr("RIG BOOM LENGTH LIMT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.rig_bm_len_lmt;
        }
        else if(mv.supervisor_set == SET_MAX_BOOM_LENGTH)
        {
            LCDPutStr("SET BOOM HIGHT LIMIT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.Max_BLength;
        }
        else if(mv.supervisor_set == SET_ZERO_LOAD_MASKING)
        {
            LCDPutStr("SET ZLOAD MASK      ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.zload_mask;
        }
        else if(mv.supervisor_set == SET_HEIGHT_OFFSET)
        {
            LCDPutStr("SET BOOM HIGHT OFSET",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.bm_ht_offset;
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
        
        if((mv.supervisor_set == SET_HOOK_LOAD)||(mv.supervisor_set == RIG_LOAD_LIMIT)||
           (mv.supervisor_set == SET_ZERO_LOAD_MASKING))
        {
            LCDPutChar('T',valX+60,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            LCDPutChar('T',valX+60,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        else
        {
            LCDPutChar('M',valX+60,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            LCDPutChar('M',valX+60,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        common_byte = 3;
        common_long = prv16_val1;    
        
        cursX += common_byte*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.supervisor_set == SET_MAIN_SAMPLE_CNT)||(mv.supervisor_set == RIG_DEFAULT_DUTY)||
            (mv.supervisor_set == HIGH_CUTOFF_ANGLE)||(mv.supervisor_set == RIG_BM_ANGLE_LIMIT)||
            (mv.supervisor_set == SET_MAX_BOOM_ANGLE)||(mv.supervisor_set == NUMOF_CALIB_POINTS)||
            (mv.supervisor_set == NUMOF_MPOINT_LEN_CALIB)||(mv.supervisor_set == FRONT_TILT_CUTOFF)||
            (mv.supervisor_set == REAR_TILT_CUTOFF))
    {
        if(mv.supervisor_set == SET_MAIN_SAMPLE_CNT)
        {
            LCDPutStr("SET MAIN SAMPLE CNTS",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.main_smpl_cnt;
        }
        else if(mv.supervisor_set == RIG_DEFAULT_DUTY)
        {
            LCDPutStr("SET DEFAULT DUTY    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.default_duty;
        }
        else if(mv.supervisor_set == HIGH_CUTOFF_ANGLE)
        {
            LCDPutStr("SET HIGH CUTOFF ANGL",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.hi_cutoff_angl;
        }
        else if(mv.supervisor_set == RIG_BM_ANGLE_LIMIT)
        {
            LCDPutStr("RIG BOOM ANGLE LIMI ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.rig_bm_angl_lmt;
        }
        else if(mv.supervisor_set == SET_MAX_BOOM_ANGLE)
        {
            LCDPutStr("SET BOOM ANGLE LIMIT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.Max_BAngle;
        }
        else if(mv.supervisor_set == NUMOF_CALIB_POINTS)
        {
            if(sys.para.Select_System == FORK_LIFT)
            {
                LCDPutStr("NUMOF LOAD CAL POINT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                menu_absnt_flag = 0;
            }
            else
            {
                LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                menu_absnt_flag = 1;
            }
            prv8_val1 = (uint8_t)sys.para.numof_calib_fork;
        }
        else if(mv.supervisor_set == NUMOF_MPOINT_LEN_CALIB)
        {
            LCDPutStr("NUMOF LEN MPOINT CAL",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = sys.para.numof_len_cal;
        }
        else if(mv.supervisor_set == FRONT_TILT_CUTOFF)
        {
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                LCDPutStr("TILT ANGL CUTOFF    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("FRONT TILT CUTOFF   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = sys.para.Front_tilt_Cutoff;
        }
        else if(mv.supervisor_set == REAR_TILT_CUTOFF)
        {
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("REAR TILT CUTOFF    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = sys.para.Rear_tilt_Cutoff;
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
    else if((mv.supervisor_set == EN_BYPASS_SWITCH)||(mv.supervisor_set == EN_PASSWORD)||
            (mv.supervisor_set == EN_BM_DWN_RLY)||(mv.supervisor_set == EN_BM_UP_RLY)||
            (mv.supervisor_set == EN_HOOTER_RLY)||(mv.supervisor_set == EN_A2B)||
            (mv.supervisor_set == EN_HK_HEIGHT)||(mv.supervisor_set == EN_DUTY_SELECT)||
            (mv.supervisor_set == EN_SNATCH_BLOCK)||(mv.supervisor_set == BYPASS_METHOD)||
            (mv.supervisor_set == EN_ART_DRATE_PERC)||(mv.supervisor_set == EN_ONBOARD_SING_TILT)||
            (mv.supervisor_set == EN_SLAVE_DISPLAY)||(mv.supervisor_set == EN_MPOINT_LEN_CALIB))
    {
        if(mv.supervisor_set == EN_BYPASS_SWITCH)
        {
            LCDPutStr("ENABLE BYPASS SWITCH",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.bpk_enable_bit;
        }
        else if(mv.supervisor_set == EN_PASSWORD)
        {
            LCDPutStr("PASSWORD STATUS     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.pw_stat_bit;
        }
        else if(mv.supervisor_set == EN_BM_DWN_RLY)
        {
            LCDPutStr("BOOM DOWN RELAY STAT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.bmdwn_rly_stat_bit;
        }
        else if(mv.supervisor_set == EN_BM_UP_RLY)
        {
            LCDPutStr("BOOM UP RELAY STAT  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv8_val1 = (uint8_t)sys.para.bmup_rly_stat_bit;
        }
        else if(mv.supervisor_set == EN_HOOTER_RLY)
        {        
            LCDPutStr("HOOTER RELAY STATUS ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.hootr_rly_stat_bit;
        }
        else if(mv.supervisor_set == EN_A2B)
        {
            LCDPutStr("A2B STATUS          ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.a2b_stat_bit;
        }
        else if(mv.supervisor_set == EN_HK_HEIGHT)
        {
            LCDPutStr("HOOK HEIGHT STATUS  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.hk_height_stat_bit;
        }
        else if(mv.supervisor_set == EN_DUTY_SELECT)
        {
            LCDPutStr("DUTY SELECT STATUS  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.duty_select_stat_bit;
        }
        else if(mv.supervisor_set == EN_SNATCH_BLOCK)
        {
            LCDPutStr("ENABLE SNATCH BLOCK ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.snatch_block_stat_bit;
        }
        else if(mv.supervisor_set == BYPASS_METHOD)
        {
            if(sys.para.Select_System == FORK_LIFT)     //Spacial case for SCA forklift
                LCDPutStr("FORKLIFT ART. METHOD",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("BYPASS METHOD       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);      
            prv8_val1 = (uint8_t)sys.para.bpk_method_stat_bit;
        }
        else if(mv.supervisor_set == EN_ART_DRATE_PERC)
        {
            LCDPutStr("EN ART.DRATE SWITCH ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.art_enable_bit;
        }
        else if(mv.supervisor_set == EN_ONBOARD_SING_TILT)
        {
            if(sys.para.Select_System != TMC_MANBASKET2)
                LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("ENABLE ON BOARD TILT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);      
            prv8_val1 = (uint8_t)sys.para.obtilt_enable_bit;
        }
        else if(mv.supervisor_set == EN_SLAVE_DISPLAY)
        {
            if((sys.para.Select_System == TMC_MANBASKET))
                LCDPutStr("ENABLE SLAVE DISPLAY",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);       
            prv8_val1 = (uint8_t)sys.para.slave_enable_bit;
        }
        else if(mv.supervisor_set == EN_MPOINT_LEN_CALIB)
        {
            LCDPutStr("EN MPOINT LENGTH CAL",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);            
            prv8_val1 = (uint8_t)sys.para.mpoint_len_enable_bit;
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
    else if((mv.supervisor_set == CALIB_LENGTH_MIN)||(mv.supervisor_set == CALIB_LENGTH_MAX)||
            (mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX)||
            (mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX))
    {
        if((mv.supervisor_set == CALIB_LENGTH_MIN)||(mv.supervisor_set == CALIB_LENGTH_MAX))
        {
            if(mv.supervisor_set == CALIB_LENGTH_MIN)
            {
                if(sys.para.Select_System == FORK_LIFT)
                {
                    LCDPutStr("CALIB HEIGHT MIN    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    prv16_val1 = sys.para.cal_len_min;
                    prv16_val2 = sys.para.cal_len_min_cnt;
                }
                else
                {
                    if(sys.para.mpoint_len_enable_bit == 0)
                    {
                        LCDPutStr("CALIB LENGTH MIN    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        prv16_val1 = sys.para.cal_len_min;
                        prv16_val2 = sys.para.cal_len_min_cnt;
                        menu_absnt_flag = 0;
                    }
                    else
                    {
                        LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                        menu_absnt_flag = 1;
                    }
                }
            }
            else
            {
                if(sys.para.Select_System == FORK_LIFT)
                {
                    LCDPutStr("CALIB HEIGHT MAX    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    prv16_val1 = sys.para.cal_len_max;
                    prv16_val2 = sys.para.cal_len_max_cnt;
                    menu_absnt_flag = 0;
                }
                else
                {
                    LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                    menu_absnt_flag = 1;
                }
            }
        }
        else if((mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX))
        {
            if(mv.supervisor_set == CALIB_ANGLE_MIN)
            {
                if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                    LCDPutStr("CALIB KNUC ANG MIN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                else
                    LCDPutStr("CALIB ANGLE MIN     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                prv16_val1 = sys.para.cal_angle_min;
                prv16_val2 = sys.para.cal_angle_min_cnt;
            }
            else
            {
                if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
                    LCDPutStr("CALIB KNUC ANG MAX  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                else
                    LCDPutStr("CALIB ANGLE MAX     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                prv16_val1 = sys.para.cal_angle_max;
                prv16_val2 = sys.para.cal_angle_max_cnt;
            }
        }
        else if((mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX))
        {
            if(mv.supervisor_set == CALIB_MANGLE_MIN)
            {
                LCDPutStr("CALIB MANGLE MIN    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                prv16_val1 = sys.para.cal_mangle_min;
                prv16_val2 = sys.para.cal_mangle_min_cnt;
            }
            else
            {
                LCDPutStr("CALIB MANGLE MAX    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                prv16_val1 = sys.para.cal_mangle_max;
                prv16_val2 = sys.para.cal_mangle_max_cnt;
            }
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
        
        if((mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX)||
           (mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX))
        {
            Draw_Circle(valX+57,valY-1,2,ILI9341_BLACK);
            Draw_Circle(valX+57,165+20-9,2,ILI9341_BLACK);
        }
        else
        {
            LCDPutChar('M',valX+50,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            LCDPutChar('M',valX+50,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);        
        
        LCDPutStr(sbuf,countX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(sbuf,countX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        common_byte = 3;
        common_long = prv16_val1;
        
        cursX += common_byte*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.supervisor_set == FRONT_TILT_ANGLE_CALIB)||(mv.supervisor_set == REAR_TILT_ANGLE_CALIB))
    {
        if(mv.supervisor_set == FRONT_TILT_ANGLE_CALIB)
        {
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                LCDPutStr("TILT ANGL CALIB    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("FRONT TILT ANG CALIB  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);//V1.17.1
            prv16_val1 = sys.para.Tilt1_X_MinAdc;
            prv16_val2 = sys.para.Tilt1_Y_MinAdc;
        }
        else
        {
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            else
                LCDPutStr("REAR TILT ANG CALIB   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);//V1.17.1
            prv16_val1 = sys.para.Tilt2_X_MinAdc;
            prv16_val2 = sys.para.Tilt2_Y_MinAdc;
        }
        LCDPutStr("XC:",15,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("XP:",15,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);     
        LCDPutStr("YC:",170,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("YP:",170,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);  
        color_lcd_draw_rectangle(ILI9341_WHITE,45,100,145,140);
        draw_hollow_rect(ILI9341_NAVY,47,102,143,138);
        color_lcd_draw_rectangle(ILI9341_WHITE,45,165,145,205); 
        draw_hollow_rect(ILI9341_NAVY,47,167,143,203);
        color_lcd_draw_rectangle(ILI9341_WHITE,200,100,300,140);
        draw_hollow_rect(ILI9341_NAVY,202,102,298,138);
        color_lcd_draw_rectangle(ILI9341_WHITE,200,165,300,205);
        draw_hollow_rect(ILI9341_NAVY,202,167,298,203);
        
        sprintf(obuf,"%04d",prv16_val1);
        slen = strlen(obuf)*13;
        cursX = 45+((100-slen)/2);
        cursY = 100+20-8;
        LCDPutStr(obuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        sprintf(obuf,"%04d",prv16_val1);
        slen = strlen(obuf)*13;
        cursX = 45+((100-slen)/2);
        cursY = 165+20-8;
        LCDPutStr(obuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        sprintf(obuf,"%04d",prv16_val2);
        slen = strlen(obuf)*13;
        cursX = 200+((100-slen)/2);
        cursY = 100+20-8;
        LCDPutStr(obuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        sprintf(obuf,"%04d",prv16_val2);
        slen = strlen(obuf)*13;
        cursX = 200+((100-slen)/2);
        cursY = 165+20-8;
        LCDPutStr(obuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else if((mv.supervisor_set == CALIB_MANBAS_MIN)||(mv.supervisor_set == CALIB_MANBAS_MAX))
    {
        if(mv.supervisor_set == CALIB_MANBAS_MIN)
        {
            LCDPutStr("CALIB MAIN HOOK MIN ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.manbasket_min;
            prv16_val2 = sys.para.manbasket_min_cnt;                
        }
        else if(mv.supervisor_set == CALIB_MANBAS_MAX)
        {
            LCDPutStr("CALIB MAIN HOOK MAX ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            prv16_val1 = sys.para.manbasket_max;
            prv16_val2 = sys.para.manbasket_max_cnt;
        }

        Current_Prev_Val_Screen(2, ILI9341_WHITE, ILI9341_NAVY);

        sprintf(obuf,"%04.1f",((float)prv16_val1)/10.0);
        sprintf(sbuf,"%05lu",(uint32_t)prv16_val2);
        slen = strlen(obuf)*13;
        cursX = 45+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        slen = strlen(sbuf)*13;
        countX = 200+((100-slen)/2);

        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutChar('T',valX+60,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutChar('T',valX+60,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        LCDPutStr(sbuf,countX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(sbuf,countX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        common_byte = 3;
        common_long = prv16_val1;    

        cursX += common_byte*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.supervisor_set == LOAD_ANNOUNCE_TIMER)
    {
        LCDPutStr("SET LOAD ANN. TIME  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);  //144
        prv16_val1 = sys.para.load_announce_timer;
            
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
        
        sprintf(obuf,"%03d",prv16_val1);
        slen = strlen(obuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8; 
        pos_t = 0;
        valX = cursX;
        valY = cursY;

        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        common_byte = 3;
        common_long = prv16_val1;    

        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if(mv.supervisor_set == EDIT_ENGINE_NUMBER)
    {
        LCDPutStr("EDIT ENGINE NUMBER  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);  //144
        prv32_val1 = sys.para.engine_number;
        
        color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
        
        LCDPutStr("CURR:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("PREV:",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
   
        color_lcd_draw_rectangle(ILI9341_WHITE,100,100,280,140);   
        draw_hollow_rect(ILI9341_NAVY,102,102,278,138);
        color_lcd_draw_rectangle(ILI9341_WHITE,100,165,280,205);  
        draw_hollow_rect(ILI9341_NAVY,102,167,278,203);
        
        sprintf(obuf,"%010lu",prv32_val1);
        slen = strlen(obuf)*13;
        cursX = 100+((180-slen)/2);
        cursY = 100+20-8;
        pos_t = 0;
        valX = cursX;
        valY = cursY;
        
        LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        common_byte = 10;
        common_long = prv32_val1;    
        
        cursX += (common_byte-1)*13;
        cursY += 19;
        TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
    }
    else if((mv.supervisor_set == SNATCH_BLOCK_VALUE)||(mv.supervisor_set == SET_LOADCEL_ADC_OFFST))
    {
        if(mv.supervisor_set == SNATCH_BLOCK_VALUE)
        {
            LCDPutStr("SET SNATCH BLOCK VAL",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);        
            prv16_val1 = sys.para.snatch_block_val;
        }
        else
        {
            LCDPutStr("SET GAIN OFFSET     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);        
            prv16_val1 = sys.para.loadcell_cnt_offst;
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
    else if(mv.supervisor_set == VOICE_LANGUAGE)
    {
        LCDPutStr("VOICE LANGUAGE      ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        prv8_val1 = sys.para.voice_of_language;
        
        Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
        
        slen = strlen("ENGLISH")*12;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8;
        valX = cursX;
        valY = cursY;

        TFTShow_Languages();
        
        if(prv8_val1)
            LCDPutStr("ENGLISH",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        else
            LCDPutStr(" HINDI ",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else if((mv.supervisor_set == MPOINT_LCALIBRATION_MENU))
    {
        LCDPutStr("LENGTH MPOINT CALIB ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
        
        prv8_val1 = 1;      //start of point calibration
        
        if((sys.para.multipt_lcalib[prv8_val1-1][0] != sys.para.bm_length_min)||(sys.para.multipt_lcalib[prv8_val1][0] < sys.para.bm_length_min))
        {
            sys.para.multipt_lcalib[prv8_val1-1][0] = sys.para.bm_length_min;
            sys.para.multipt_lcalib[prv8_val1-1][1] = 500;

            sys.para.multipt_lcalib[prv8_val1][0] = sys.para.bm_length_min+10;
            sys.para.multipt_lcalib[prv8_val1][1] = 1500;
        }
        
        TFT_Length_MPoint_Menu();
    }
    else if((mv.supervisor_set == ARTICULATION_DERATE_PERC))   //change here 25/04/23 v1.16 reserved menu
    {
        LCDPutStr("ALL DUTY ART. DERATE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
    }
    else if((mv.supervisor_set == VIEW_DATA_LOGGED))  //change here 25/04/23 v1.16 reserved menu
    {
        LCDPutStr("VIEW DATA LOGGED    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
    }
    else if((mv.supervisor_set == SEND_DATA_TO_PC)) //change here 25/04/23 v1.16 reserved menu
    {
        LCDPutStr("SEND DATA TO PC     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Length_MPoint_Menu.
 * Description   :        Used to display length multi-point menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Length_MPoint_Menu(void)
{
    char obuf[10],slen;
    
    LCDPutStr("CALIB POINT:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
    prv16_val1 = sys.para.multipt_lcalib[prv8_val1-1][0];       //Length value
    prv16_val2 = sys.para.multipt_lcalib[prv8_val1-1][1];       //Length counts
    
    color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
    draw_hollow_rect(ILI9341_NAVY,182,102,278,138);

    sprintf(obuf,"%02d",prv8_val1);
    slen = strlen(obuf)*13;
    cursX = 180+((100-slen)/2);
    cursY = 100+20-8; 
    pos_t = 0;
    valX = cursX;
    valY = cursY;
    LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    LCDPutStr("LENGTH:",10,177,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("mm:",193,157,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("CNT",193,199,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    color_lcd_draw_rectangle(ILI9341_WHITE,80,167,180,207); 
    draw_hollow_rect(ILI9341_NAVY,82,169,178,205);
    color_lcd_draw_rectangle(ILI9341_WHITE,225,147,305,179);
    draw_hollow_rect(ILI9341_NAVY,227,149,303,177);
    color_lcd_draw_rectangle(ILI9341_WHITE,225,189,305,221);
    draw_hollow_rect(ILI9341_NAVY,227,191,303,219);
    
    if((prv16_val1 > 0)&&(prv16_val1 <= sys.para.bm_length_max))
    {
        sprintf(obuf,"%04.1f",((float)prv16_val1)/10.0);        
        LCDPutStr(obuf,97,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutChar('M',158,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(obuf,"%05lu",(uint32_t)prv16_val2);
        LCDPutStr(obuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

        LCDPutStr(" ----",234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,85,177,170,197);
        LCDPutStr("ADD",115,177,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(" ----",234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    
    menu_stat = LEN_MPOINT_CALIBRATION_PAGE1;
}


/*============================================================================*/
/*
 * Function      :        TFT_Forklift_Load_MPoint_Menu.
 * Description   :        Used to display load multi-point menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Forklift_Load_MPoint_Menu(void)
{
    char obuf[10],slen;
    
    LCDPutStr("CALIB POINT:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
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
    common_short = sys.para.fork_len_region[prv8_val1-1];                //Length value at which load is calibrated
    
    color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
    draw_hollow_rect(ILI9341_NAVY,182,102,278,138);

    sprintf(obuf,"%02d",prv8_val1);
    slen = strlen(obuf)*13;
    cursX = 180+((100-slen)/2);
    cursY = 100+20-8; 
    pos_t = 0;
    valX = cursX;
    valY = cursY;
    LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    LCDPutStr(" LOAD",12,170,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr(" VALUE",12,187,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutChar(':',68,179,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    if(sys.para.bpk_method_stat_bit == 0)
        LCDPutStr("HGT",193,157,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    else
    {
        LCDPutStr("ART",193,150,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr(" IN",193,167,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    LCDPutStr("CNT",193,199,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
    color_lcd_draw_rectangle(ILI9341_WHITE,80,167,180,207); 
    draw_hollow_rect(ILI9341_NAVY,82,169,178,205);
    color_lcd_draw_rectangle(ILI9341_WHITE,225,147,305,179);
    draw_hollow_rect(ILI9341_NAVY,227,149,303,177);
    color_lcd_draw_rectangle(ILI9341_WHITE,225,189,305,221);
    draw_hollow_rect(ILI9341_NAVY,227,191,303,219);
    
    if((prv16_val1 >= 0)&&(prv16_val1 <= lc_max_capacity))
    {
        sprintf(obuf,"%04.1f",((float)prv16_val1)/10.0);
        LCDPutStr(obuf,97,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutChar('T',158,179,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        if(sys.para.bpk_method_stat_bit == 0)
        {
            sprintf(obuf,"%04.1fM",((float)common_short)/10.0);
            LCDPutStr(obuf,234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        else
        {
            sprintf(obuf,"%d",art_ip_bit);
            LCDPutStr(obuf,260,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        
        sprintf(obuf,"%05lu",(uint32_t)prv16_val2);
        LCDPutStr(obuf,234,199,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,85,177,170,197);
        LCDPutStr("ADD",115,177,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        LCDPutStr(" ----",234,157,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    
    menu_stat = FORK_PRESS_MINMAX_PAGE1;
}

/*============================================================================*/
/*
 * Function      :        TFT_Modify_Supervisor_Settings.
 * Description   :        Used to modify operator setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Modify_Supervisor_Settings(void)
{
    if(((mv.supervisor_set >= SET_SP1_VALUE)&&(mv.supervisor_set <= SET_SP4_VALUE)))
    {
        TFT_SetPoints();
    }
    else if((mv.supervisor_set == SET_BOOM_OFFSET)||(mv.supervisor_set == SET_BM_HEAD_OFFSET)||
            (mv.supervisor_set == SET_BM_TIP_OFFSET)||(mv.supervisor_set == LOW_CUTOFF_ANGLE)||
            (mv.supervisor_set == SET_SLEW_OFFSET))
    {
        TFT_Set_Offset();
    }
    else if((mv.supervisor_set == SET_HOOK_LOAD)||(mv.supervisor_set == RIG_LOAD_LIMIT)||
            (mv.supervisor_set == RIG_BM_LENGTH_LIMIT)||(mv.supervisor_set == SET_MAX_BOOM_LENGTH)||
            (mv.supervisor_set == SET_ZERO_LOAD_MASKING)||(mv.supervisor_set == SET_HEIGHT_OFFSET))
    {
        TFT_Set_3Digit1Decimal_Supervisor_Menus();
    }
    else if((mv.supervisor_set == SET_MAIN_SAMPLE_CNT)||(mv.supervisor_set == RIG_DEFAULT_DUTY)||
            (mv.supervisor_set == HIGH_CUTOFF_ANGLE)||(mv.supervisor_set == RIG_BM_ANGLE_LIMIT)||
            (mv.supervisor_set == SET_MAX_BOOM_ANGLE)||(mv.supervisor_set == NUMOF_CALIB_POINTS)||
            (mv.supervisor_set == NUMOF_MPOINT_LEN_CALIB)||(mv.supervisor_set == FRONT_TILT_CUTOFF)||
            (mv.supervisor_set == REAR_TILT_CUTOFF))
    {
        TFT_Set_2Digit_Supervisor_Menus();
    }
    else if((mv.supervisor_set == EN_BYPASS_SWITCH)||(mv.supervisor_set == EN_PASSWORD)||
            (mv.supervisor_set == EN_BM_DWN_RLY)||(mv.supervisor_set == EN_BM_UP_RLY)||
            (mv.supervisor_set == EN_HOOTER_RLY)||(mv.supervisor_set == EN_A2B)||
            (mv.supervisor_set == EN_HK_HEIGHT)||(mv.supervisor_set == EN_DUTY_SELECT)||
            (mv.supervisor_set == EN_SNATCH_BLOCK)||(mv.supervisor_set == BYPASS_METHOD)||
            (mv.supervisor_set == EN_ART_DRATE_PERC)||(mv.supervisor_set == EN_ONBOARD_SING_TILT)||
            (mv.supervisor_set == EN_SLAVE_DISPLAY)||(mv.supervisor_set == EN_MPOINT_LEN_CALIB))
    {
        TFT_Enable_Disable_Supervisor_Menu();
    }
    else if((mv.supervisor_set == CALIB_LENGTH_MIN)||(mv.supervisor_set == CALIB_LENGTH_MAX)||
            (mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX)||
            (mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX))
    {
        TFT_Calibrate_LenAngles();
    }
    else if(mv.supervisor_set == SET_DUTY_TYPE)
    {
        if(sys.para.Select_System == FORK_LIFT)
        {
            
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            TFT_TMC_MinMax_Press_Menu();
        }
        else
        {
            TFT_Set_Duty_Type();
        }        
    }
    else if(mv.supervisor_set == CALIB_HOOK_LOAD)
    {
        if(sys.para.Select_System == FORK_LIFT)
        {
            
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            TFT_TMC_MinMax_Press_Menu();
        }
        else
        {
            //Handled in GUI pages
        }
    }
    else if((mv.supervisor_set == SNATCH_BLOCK_VALUE)||(mv.supervisor_set == SET_LOADCEL_ADC_OFFST))
    {
        TFT_Set_4Digit_Supervisor_Menu();
    }
    else if((mv.supervisor_set == FRONT_TILT_ANGLE_CALIB)||(mv.supervisor_set == REAR_TILT_ANGLE_CALIB))
    {
        TFT_Tilt_Calibration_Menu();
    }
    else if(mv.supervisor_set == VOICE_LANGUAGE)
    {
        TFT_Choose_Language_Supervisor_Menu();
    }
    else if((mv.supervisor_set == CALIB_MANBAS_MIN)||(mv.supervisor_set == CALIB_MANBAS_MAX))
    {
        TFT_2PCalibrate_Load();
    }
    else if(mv.supervisor_set == LOAD_ANNOUNCE_TIMER)
    {
        TFT_Set_3Digit_Supervisor_Menu();
    }
    else if(mv.supervisor_set == EDIT_ENGINE_NUMBER)
    {
        TFT_Set_10Digit_Supervisor_Menu();
    }
    else if((mv.supervisor_set == ARTICULATION_DERATE_PERC)||(mv.supervisor_set == VIEW_DATA_LOGGED)||(mv.supervisor_set == SEND_DATA_TO_PC))  //change here 25/04/23 v1.16 reserved   
    {
      TFT_Set_Reserved_Supervisor_Menu();  
    }
}

/*============================================================================*/
/*
 * Function      :        TFTCommon_Supervisor_Escape_Function.
 * Description   :        Used to take escape from supervisor menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTCommon_Supervisor_Escape_Function(void)
{
    if((mv.supervisor_set >= 1)&&(mv.supervisor_set <= 5))        TFTDisplay_Supervisor_Set_Menu(0);
    else if((mv.supervisor_set >= 6)&&(mv.supervisor_set <= 10))  TFTDisplay_Supervisor_Set_Menu(1);
    else if((mv.supervisor_set >= 11)&&(mv.supervisor_set <= 15)) TFTDisplay_Supervisor_Set_Menu(2);
    else if((mv.supervisor_set >= 16)&&(mv.supervisor_set <= 20)) TFTDisplay_Supervisor_Set_Menu(3);
    else if((mv.supervisor_set >= 21)&&(mv.supervisor_set <= 25)) TFTDisplay_Supervisor_Set_Menu(4);
    else if((mv.supervisor_set >= 26)&&(mv.supervisor_set <= 30)) TFTDisplay_Supervisor_Set_Menu(5);
    else if((mv.supervisor_set >= 31)&&(mv.supervisor_set <= 35)) TFTDisplay_Supervisor_Set_Menu(6);
    else if((mv.supervisor_set >= 36)&&(mv.supervisor_set <= 40)) TFTDisplay_Supervisor_Set_Menu(7);
    else if((mv.supervisor_set >= 41)&&(mv.supervisor_set <= 45)) TFTDisplay_Supervisor_Set_Menu(8);
    else if((mv.supervisor_set >= 46)&&(mv.supervisor_set <= 50)) TFTDisplay_Supervisor_Set_Menu(9);
    else if((mv.supervisor_set >= 51)&&(mv.supervisor_set <= 55)) TFTDisplay_Supervisor_Set_Menu(10);
    else if((mv.supervisor_set >= 56)&&(mv.supervisor_set <= 60)) TFTDisplay_Supervisor_Set_Menu(11);
}


/*============================================================================*/
/*
 * Function      :        TFT_Master_Reset.
 * Description   :        Used to do master reset.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Master_Reset(void)
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

            TFTShow_YESNO_Confirmation();

            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
//            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
//            
//            sys.para.duty = prv16_val1;
//            sys.para.curr_len_indx = 1;
//            
//            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
//            
//            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
//            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
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
}


/*============================================================================*/
/*
 * Function      :        TFT_SetPoints.
 * Description   :        Used to change set point value.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_SetPoints(void)
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == SET_SP1_VALUE)
                sys.para.sp1_perc = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_SP2_VALUE)
                sys.para.sp2_perc = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_SP3_VALUE)
                sys.para.sp3_perc = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_SP4_VALUE)
                sys.para.sp4_perc = (uint16_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_3Digit_Menu();
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Set_Offset.
 * Description   :        Used to change boom offset value.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Offset(void)
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                 
            if(mv.supervisor_set == SET_BOOM_OFFSET)
                sys.para.bm_offset = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_BM_HEAD_OFFSET)
                sys.para.bm_head_offset = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_BM_TIP_OFFSET)
                sys.para.bm_tip_offset = (uint16_t)common_long;
            else if(mv.supervisor_set == LOW_CUTOFF_ANGLE)
                sys.para.low_cutoff_angl = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_SLEW_OFFSET)
                sys.para.slew_offset = (uint16_t)common_long;
            
            if(value_sign_flag)
            {
                if(mv.supervisor_set == SET_BOOM_OFFSET)
                    sys.para.bm_offset = sys.para.bm_offset*(-1);
                else if(mv.supervisor_set == SET_BM_HEAD_OFFSET)
                    sys.para.bm_head_offset = sys.para.bm_head_offset*(-1);
                else if(mv.supervisor_set == SET_BM_TIP_OFFSET)
                    sys.para.bm_tip_offset = sys.para.bm_tip_offset*(-1);
                else if(mv.supervisor_set == LOW_CUTOFF_ANGLE)
                    sys.para.low_cutoff_angl = sys.para.low_cutoff_angl*(-1);
                else if(mv.supervisor_set == SET_SLEW_OFFSET)
                    sys.para.slew_offset = sys.para.slew_offset*(-1);
            }
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_3Digit1Decimal_Supervisor_Menus.
 * Description   :        Used to set 3 digit menus with one decimal point like hook load.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_3Digit1Decimal_Supervisor_Menus(void)
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == SET_HOOK_LOAD)
                sys.para.hook_load = (uint16_t)common_long;
            else if(mv.supervisor_set == RIG_LOAD_LIMIT)
                sys.para.rig_load_lmt = (uint16_t)common_long;
            else if(mv.supervisor_set == RIG_BM_LENGTH_LIMIT)
                sys.para.rig_bm_len_lmt = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_MAX_BOOM_LENGTH)
                sys.para.Max_BLength = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_ZERO_LOAD_MASKING)
                sys.para.zload_mask = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_HEIGHT_OFFSET)
                sys.para.bm_ht_offset = (uint16_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_2Digit_Supervisor_Menus.
 * Description   :        Used to set 2 digit menus like main sample counts.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_2Digit_Supervisor_Menus(void)
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == SET_MAIN_SAMPLE_CNT)
                sys.para.main_smpl_cnt = (uint16_t)common_long;
            else if(mv.supervisor_set == RIG_DEFAULT_DUTY)
                sys.para.default_duty = (uint8_t)common_long;
            else if(mv.supervisor_set == HIGH_CUTOFF_ANGLE)
                sys.para.hi_cutoff_angl = (uint16_t)common_long;
            else if(mv.supervisor_set == RIG_BM_ANGLE_LIMIT)
                sys.para.rig_bm_angl_lmt = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_MAX_BOOM_ANGLE)
                sys.para.Max_BAngle = (uint16_t)common_long;
            else if(mv.supervisor_set == NUMOF_CALIB_POINTS)
                sys.para.numof_calib_fork = (uint8_t)common_long;
            else if(mv.supervisor_set == NUMOF_MPOINT_LEN_CALIB)
                sys.para.numof_len_cal = (uint8_t)common_long;
            else if(mv.supervisor_set == FRONT_TILT_CUTOFF)
                sys.para.Front_tilt_Cutoff = (uint8_t)common_long;
            else if(mv.supervisor_set == REAR_TILT_CUTOFF)
                sys.para.Rear_tilt_Cutoff = (uint8_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_Duty_Type.
 * Description   :        Used to set duty type, number of pcurve calibrations.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Duty_Type(void)
{
    char dbuf[5],slen;
    
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
            key.enter = 0;
            if((common_long >= 1)&&(common_long <= lc_total_duty))
            {
                temp_duty_indx = (uint8_t)common_long;
                
                sub_menu_flag = 1;
                
                if(common_byte < 4)
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte+1)*13),cursY,cursX+13,cursY+2);
                else
                    color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*13),cursY,cursX+13,cursY+2);
                
                sprintf(dbuf,"%02d",len_calib_cnt);
                slen = strlen(dbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 165+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                common_byte = 2;
                common_long = len_calib_cnt;
                
                cursX += (common_byte-1)*13;
                cursY += 19;
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                
                TFT_Set_Duty_Type_NumofLength();
                break;
            }
        }
        else if((key.bypass == 1)||(key.duty == 1))
        {
            if(key.duty == 1) TFTShift_Cursor_Position(0,common_byte,NO_DECIMAL_POINT);
            else              TFTShift_Cursor_Position(1,common_byte,NO_DECIMAL_POINT);
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

                    sprintf(dbuf,"%02d",(uint8_t)common_long);
                    LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    if((common_long >= 1)&&(common_long <= lc_total_duty))
                    {
                        len_calib_cnt = sys.para.duty_type[common_long-1];
                        sprintf(dbuf,"%02d",(uint8_t)len_calib_cnt);
                        LCDPutStr(dbuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    }
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);

                    sprintf(dbuf,"%02d",(uint8_t)common_long);
                    LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    
                    if((common_long >= 1)&&(common_long <= lc_total_duty))
                    {
                        len_calib_cnt = sys.para.duty_type[common_long-1];
                        if((len_calib_cnt == 0)||(len_calib_cnt > 5))
                        {
                            len_calib_cnt = 1;
                        }
                        sprintf(dbuf,"%02d",(uint8_t)len_calib_cnt);
                        LCDPutStr(dbuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                    }
                    Delay_1ms(500);
                }
            }
            key.increment = 0;
            key.decrement = 0;
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Set_Duty_Type_NumofLength.
 * Description   :        Used to set number of length points.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Duty_Type_NumofLength(void)
{
    char lbuf[10],sbuf[10],slen;
    
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            if(common_byte < 4)
                color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte+1)*13),cursY,cursX+13,cursY+2);
            else
                color_lcd_draw_rectangle(ILI9341_WHITE,cursX-((common_byte)*13),cursY,cursX+13,cursY+2);
            
            sub_menu_flag = 0;
            
            sprintf(lbuf,"%02d",temp_duty_indx);
            sprintf(sbuf,"%02d",len_calib_cnt);
            slen = strlen(lbuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8; 
            pos_t = 0;
            valX = cursX;
            valY = cursY;
            
            LCDPutStr(lbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            LCDPutStr(sbuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
            common_byte = 2;
            common_long = temp_duty_indx;    
            
            cursX += (common_byte-1)*13;
            cursY += 19;
            TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            Delay_1ms(500);
            key.function = 0;
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            key.enter = 0;
            if((common_long >= 1)&&(common_long <= 5))
            {
                len_calib_cnt = (uint8_t)common_long;
                
                color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
                SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
                
                sys.para.duty_type[temp_duty_indx-1] = len_calib_cnt;
                
                memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
                
                Sector_Erase(SYSTEM_DEFAULT_SECTOR);
                SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
                
                LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
                Delay_1ms(1500);
                color_lcd_draw_rectangle(ILI9341_NAVY,100,127,180,150);
                
                sub_menu_flag = 1;
                
                LCDPutStr("CALIB. POINTS  :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("CALIB. LENGTH  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                
                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
                len_calib_pt = 1;
                sprintf(lbuf,"%02d",len_calib_pt);                
                slen = strlen(lbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 100+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;                
                LCDPutStr(lbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                length_array_ptr = ((temp_duty_indx-1)*5);
                prv16_val1 = sys.para.length_array[length_array_ptr];
                
                if((prv16_val1 == 0)||(prv16_val1 > 600))
                {
                    prv16_val1 = lc_bm_length_min;
                }
                sprintf(sbuf,"%04.1fM",((float)prv16_val1)/10.0);
                slen = strlen(sbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 165+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                LCDPutStr(sbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                common_byte = 3;
                common_long = prv16_val1;    
                
                cursX += common_byte*13;
                cursY += 19;
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                
                TFT_Set_Duty_Type_Length_Val();
                break;
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
 * Function      :        TFT_Set_Duty_Type_Length_Val.
 * Description   :        Used to set length value.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Duty_Type_Length_Val(void)
{
    char lbuf[10],sbuf[10],slen;
    
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            LCDPutStr("DUTY NUMBER    :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("CALIB. POINTS  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
            draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
            draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
            
            sub_menu_flag = 0;
            
            sprintf(lbuf,"%02d",temp_duty_indx);
            sprintf(sbuf,"%02d",len_calib_cnt);
            slen = strlen(lbuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8;
            pos_t = 0;
            valX = cursX;
            valY = cursY;
            
            LCDPutStr(lbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            LCDPutStr(sbuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
            common_byte = 2;
            common_long = temp_duty_indx;    
            
            cursX += (common_byte-1)*13;
            cursY += 19;
            TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            Delay_1ms(500);
            key.function = 0;
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            key.enter = 0;
            
            prv16_val1 = (uint16_t)common_long;
            
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
                
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);

            sys.para.length_array[length_array_ptr] = prv16_val1;

            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);

            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            color_lcd_draw_rectangle(ILI9341_NAVY,100,127,180,150);
                
            if((len_calib_cnt == 1)||(len_calib_pt == len_calib_cnt)) //if only one length point or all length points saved
            {
                LCDPutStr("DUTY NUMBER    :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("CALIB. POINTS  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                draw_hollow_rect(ILI9341_NAVY,182,167,278,203);

                sub_menu_flag = 0;

                sprintf(lbuf,"%02d",temp_duty_indx);
                sprintf(sbuf,"%02d",len_calib_cnt);
                slen = strlen(lbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 100+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;

                LCDPutStr(lbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                LCDPutStr(sbuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                common_byte = 2;
                common_long = temp_duty_indx;    

                cursX += (common_byte-1)*13;
                cursY += 19;
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                Delay_1ms(500);
                key.function = 0;
                break;
            }
            else if((len_calib_cnt > 1)&&(len_calib_pt < len_calib_cnt))
            {
                LCDPutStr("CALIB. POINTS  :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("CALIB. LENGTH  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                
                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
                len_calib_pt++;
                sprintf(lbuf,"%02d",len_calib_pt);                
                slen = strlen(lbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 100+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;                
                LCDPutStr(lbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                length_array_ptr++;
                prv16_val1 = sys.para.length_array[length_array_ptr];
                if((prv16_val1 == 0)||(prv16_val1 > 600))
                {
                    prv16_val1 = sys.para.length_array[length_array_ptr-1];
                }
                sprintf(sbuf,"%04.1fM",((float)prv16_val1)/10.0);
                slen = strlen(sbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 165+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                LCDPutStr(sbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                common_byte = 3;
                common_long = prv16_val1;    
                
                cursX += common_byte*13;
                cursY += 19;
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            }
        }
        else
        {
            Inc_Dec_3Digit_1Decimal_Menu();
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_TMC_MinMax_Press_Menu.
 * Description   :        Used to calibrate Out triggers of TMC crane.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_TMC_MinMax_Press_Menu(void)
{
    char lbuf[10],slen;
    
    while(1)
    {
        Analog_Data_Read();
        
        if(disp_refresh_cnt == 0)
        {
            disp_refresh_cnt = 500;
            sprintf(lbuf,"%04d",can_p1_cnt);
            slen = strlen(lbuf)*13;
            cursX = 45+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",can_p2_cnt);
            slen = strlen(lbuf)*13;
            cursX = 45+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",can_p3_cnt);
            slen = strlen(lbuf)*13;
            cursX = 200+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",can_p4_cnt);
            slen = strlen(lbuf)*13;
            cursX = 200+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            if(byt1 == 0)
            {
                sys.para.forkcalib_press_min[0][1] = can_p1_cnt;
                sys.para.forkcalib_press_min[1][1] = can_p2_cnt;
                sys.para.forkcalib_press_min[2][1] = can_p3_cnt;
                sys.para.forkcalib_press_min[3][1] = can_p4_cnt;
            }
            else
            {
                sys.para.forkcalib_press_max[0][1] = can_p1_cnt;
                sys.para.forkcalib_press_max[1][1] = can_p2_cnt;
                sys.para.forkcalib_press_max[2][1] = can_p3_cnt;
                sys.para.forkcalib_press_max[3][1] = can_p4_cnt;
            }
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            key.increment = 0;
            key.decrement = 0;
            key.duty = 0;
            key.bypass = 0;
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Select_Duty_HkLoad_Calib.
 * Description   :        Used to select which duty need to be calibrated.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Select_Duty_HkLoad_Calib(void)
{
    char lbuf[10],slen;
    
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
            if((common_long >= 1)&&(common_long <= 5))
            {
                temp_duty_indx = (uint8_t)common_long;
                
                sys.para.duty = temp_duty_indx;
                length_array_ptr = ((temp_duty_indx-1)*5);
                
                if(sys.para.duty_type[temp_duty_indx-1] > 5)
                {
                    sys.para.duty_type[temp_duty_indx-1] = 1;
                }
                
                mv.max = (length_array_ptr + (sys.para.duty_type[temp_duty_indx-1]-1));
                mv.min = length_array_ptr;
                
                LCDPutStr("SEL CALIB. LEN:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("CALIB. POINTS  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                
                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                draw_hollow_rect(ILI9341_NAVY,182,167,278,203);

                sprintf(lbuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                slen = strlen(lbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 100+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                LCDPutStr(lbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                sprintf(lbuf,"%02d",len_calib_cnt);
                slen = strlen(lbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 165+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                LCDPutStr(lbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                key.enter = 0;
                
                TFT_Select_Calib_Length();
                break;
            }
            key.enter = 0;
        }
        else
        {
            Inc_Dec_2Digit_Menu();
        }
    }
}

void TFT_Select_Calib_Length(void)
{
    char cbuf[10],slen;
    
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
                    if((sys.para.duty_type[length_array_ptr-1] >= 1) && (sys.para.duty_type[length_array_ptr-1] < 6))
                    {
                        sprintf(cbuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                        LCDPutStr(cbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
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
                    if((sys.para.duty_type[length_array_ptr-1] >= 1) && (sys.para.duty_type[length_array_ptr-1] < 6))
                    {
                        sprintf(cbuf,"%04.1fM",((float)sys.para.length_array[length_array_ptr])/10.0);
                        LCDPutStr(cbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
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
            
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
            {
//                Lcd16x2_Out(1,1,"KBL:            ");
//                Lcd16x2_Out(2,1,"MBA:    KBA:    ");
            }
            else
            {
                LCDPutStr("CURRENT LENGTH:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutStr("CURRENT ANGLE :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                
                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
                draw_hollow_rect(ILI9341_NAVY,182,167,278,203);
                
                sprintf(cbuf,"%04.1f",((float)TotalBmLength)/10.0);           
                slen = strlen(cbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 100+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;            
                LCDPutStr(cbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                
                sprintf(cbuf,"%04.1fM",((float)bm_angle)/10.0);           
                slen = strlen(cbuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 165+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;            
                LCDPutStr(cbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            }
            key.enter = 0;
            menu_stat = HOOK_LOAD_CALIB_PAGE1;
            break;
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Enable_Disable_Supervisor_Menu.
 * Description   :        Used to enable/disable menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Enable_Disable_Supervisor_Menu(void)
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
            
            if(mv.supervisor_set == EN_BYPASS_SWITCH)
                sys.para.bpk_enable_bit = prv8_val1;
            else if(mv.supervisor_set == EN_PASSWORD)
                sys.para.pw_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_BM_DWN_RLY)
                sys.para.bmdwn_rly_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_BM_UP_RLY)
                sys.para.bmup_rly_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_HOOTER_RLY)
                sys.para.hootr_rly_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_A2B)
                sys.para.a2b_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_HK_HEIGHT)
                sys.para.hk_height_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_DUTY_SELECT)
                sys.para.duty_select_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_SNATCH_BLOCK)
                sys.para.fail_safe_stat_bit = prv8_val1;
            else if(mv.supervisor_set == BYPASS_METHOD)
                sys.para.bpk_method_stat_bit = prv8_val1;
            else if(mv.supervisor_set == EN_SLAVE_DISPLAY)
                sys.para.slave_enable_bit = prv8_val1;
            else if(mv.supervisor_set == EN_MPOINT_LEN_CALIB)
                sys.para.mpoint_len_enable_bit = prv8_val1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
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
}


/*============================================================================*/
/*
 * Function      :        TFT_Choose_Language_Supervisor_Menu.
 * Description   :        Used to choose languages.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Choose_Language_Supervisor_Menu(void)
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

            TFTShow_Languages();

            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.voice_of_language = prv8_val1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
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
}

/*============================================================================*/
/*
 * Function      :        TFT_Calibrate_LenAngle.
 * Description   :        Used to calibrate length and angles.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Calibrate_LenAngles(void)
{
    char sbuf[10];
    uint16_t temp_len;
    
    while(1)
    {
        Analog_Data_Read();
        
        if((mv.supervisor_set == CALIB_ANGLE_MIN)||(mv.supervisor_set == CALIB_ANGLE_MAX))
            sprintf(sbuf,"%05d",ang_adc_cnt);
        else if((mv.supervisor_set == CALIB_MANGLE_MIN)||(mv.supervisor_set == CALIB_MANGLE_MAX))
            sprintf(sbuf,"%05d",Main_ang_adc_cnt);
        if((mv.supervisor_set == CALIB_LENGTH_MIN)||(mv.supervisor_set == CALIB_LENGTH_MAX))
            sprintf(sbuf,"%05d",len_adc_cnt);
        
        LCDPutStr(sbuf,countX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == CALIB_ANGLE_MIN)
            {
                sys.para.cal_angle_min = (uint16_t)common_long;
                sys.para.cal_angle_min_cnt = ang_adc_cnt;
            }
            else if(mv.supervisor_set == CALIB_ANGLE_MAX)
            {
                sys.para.cal_angle_max = (uint16_t)common_long;
                sys.para.cal_angle_max_cnt = ang_adc_cnt;
            }
            else if(mv.supervisor_set == CALIB_MANGLE_MIN)
            {
                sys.para.cal_mangle_min = (uint16_t)common_long;
                sys.para.cal_mangle_min_cnt = Main_ang_adc_cnt;
            }
            else if(mv.supervisor_set == CALIB_MANGLE_MAX)
            {
                sys.para.cal_mangle_max = (uint16_t)common_long;
                sys.para.cal_mangle_max_cnt = Main_ang_adc_cnt;
            }
            else if(mv.supervisor_set == CALIB_LENGTH_MIN)
            {
                sys.para.cal_len_min = (uint16_t)common_long;
                sys.para.bm_length_min = sys.para.cal_len_min;
                
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
            }
            else if(mv.supervisor_set == CALIB_LENGTH_MAX)
            {
                sys.para.cal_len_max = (uint16_t)common_long;
                sys.para.cal_len_max_cnt = len_adc_cnt;
            }
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_4Digit_Supervisor_Menu.
 * Description   :        Used to set 4 digit menus.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_4Digit_Supervisor_Menu(void)
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == SNATCH_BLOCK_VALUE)
                sys.para.snatch_block_val = (uint16_t)common_long;
            else if(mv.supervisor_set == SET_LOADCEL_ADC_OFFST)
                sys.para.loadcell_cnt_offst = (uint16_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
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
 * Function      :        TFT_Tilt_Calibration_Menu.
 * Description   :        Used to calibrate tilt angles.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Tilt_Calibration_Menu(void)
{
    char lbuf[10],slen;
    
    while(1)
    {
        Analog_Data_Read();
        
        if(disp_refresh_cnt == 0)
        {
            disp_refresh_cnt = 500;
            
            if(mv.supervisor_set == FRONT_TILT_ANGLE_CALIB)
                sprintf(lbuf,"%04d",Tilt_1_X_cnt);
            else
                sprintf(lbuf,"%04d",Tilt_2_X_cnt);
            slen = strlen(lbuf)*13;
            cursX = 45+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
            if(mv.supervisor_set == FRONT_TILT_ANGLE_CALIB)
                sprintf(lbuf,"%04d",Tilt_1_Y_cnt);
            else
                sprintf(lbuf,"%04d",Tilt_2_Y_cnt);
            slen = strlen(lbuf)*13;
            cursX = 200+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == FRONT_TILT_ANGLE_CALIB)
            {
                sys.para.Tilt1_X_MinAdc = Tilt_1_X_cnt;
                sys.para.Tilt1_Y_MinAdc = Tilt_1_Y_cnt;
            }
            else
            {
                sys.para.Tilt2_X_MinAdc = Tilt_2_X_cnt;
                sys.para.Tilt2_Y_MinAdc = Tilt_2_Y_cnt;
            }
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            key.increment = 0;
            key.decrement = 0;
            key.duty = 0;
            key.bypass = 0;
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_2PCalibrate_Load.
 * Description   :        Used to 2 point calibrate load.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_2PCalibrate_Load(void)
{
    char sbuf[10];
    
    while(1)
    {
        Analog_Data_Read();
        
        if((mv.supervisor_set == CALIB_MANBAS_MIN)||(mv.supervisor_set == CALIB_MANBAS_MAX))
            sprintf(sbuf,"%05lu",(uint32_t)can_loadcell_cnt);
        
        LCDPutStr(sbuf,countX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == CALIB_MANBAS_MIN)
            {
                sys.para.manbasket_min = (uint16_t)common_long;
                sys.para.manbasket_min_cnt = can_loadcell_cnt;
            }
            else if(mv.supervisor_set == CALIB_MANBAS_MAX)
            {
                sys.para.manbasket_max = (uint16_t)common_long;
                sys.para.manbasket_max_cnt = can_loadcell_cnt;
            }
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_3Digit_Supervisor_Menu.
 * Description   :        Used to change set load compansation value.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_3Digit_Supervisor_Menu(void)
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            if(mv.supervisor_set == LOAD_ANNOUNCE_TIMER)
                sys.para.load_announce_timer = (uint16_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_3Digit_Menu();
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Set_10Digit_Supervisor_Menu.
 * Description   :        Used to change engine number.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_10Digit_Supervisor_Menu(void)
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
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.engine_number = (uint32_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else
        {
            Inc_Dec_10Digit_Menu();
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFT_Multipoint_Calibration_Menu.
 * Description   :        Used to do multi-point calibrations.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Multipoint_Calibration_Menu(void)
{
//    char obuf[50];
//    uint8_t slen;
//    
//    if(sys.para.Select_System == CRAWLER1_SYSTEM)
//    {
//        
//    }
//    else if(sys.para.Select_System == CRAWLER2_SYSTEM)
//    {
//        while(1)
//        {
//            if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
//            {
//                TFTCommon_Supervisor_Escape_Function();
//                
//                menu_stat = SUPERVISOR_SET_CODE_PAGE;
//                key.function = 0;
//                Delay_1ms(500);
//                break;
//            }
//            else if(key.enter == 1)        // ENTR Key
//            {
//                calib_load_val = (uint16_t)common_long;
//                
////                color_lcd_draw_rectangle(ILI9341_NAVY,15,100,245,135);    //Clear Setting page
//                
//                prv16_val1 = sys.para.duty;
//                LCDPutStr("SELECT DUTY:",15,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
//                color_lcd_draw_rectangle(ILI9341_WHITE,130,100,230,135);
//
//                sprintf(obuf,"%03d",prv16_val1);
//                slen = strlen(obuf)*13;
//                cursX = 130+((100-slen)/2);
//                cursY = 100+20-8; 
//                pos_t = 0;
//                valX = cursX;
//                valY = cursY;
//
//                LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//
//                common_byte = 3;
//                common_long = prv16_val1;    
//                
//                cursX += (common_byte-1)*13;
//                cursY += 19;
//                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);  
//                key.enter = 0;
//                menu_stat = HOOK_LOAD_CALIB_PAGE1;
//                break;
//            }
//            else
//            {
//                Inc_Dec_4Digit_1Decimal_Menu();
//            }
//        }
//    }
}


void TFT_Set_Reserved_Supervisor_Menu(void)
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
            TFTCommon_Supervisor_Escape_Function();
            
            menu_stat = SUPERVISOR_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
    
}