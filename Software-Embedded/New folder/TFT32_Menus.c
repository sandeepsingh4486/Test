
#include "main.h"

/*============================================================================*/
/*
 * Function      :        Modify_System_Parameter.
 * Description   :        Used to modify system parameters.
 * Parameters    :        digits-Total digits, action-Inc/Dec action, cur_pos-Cursor position and para-Pointer to system parameter.
 * Return        :        None.
*/
/*============================================================================*/
void Modify_System_Parameter(uint8_t digits, uint8_t action, uint8_t cur_pos, uint32_t *para)
{
    mi.data = *para;
    
    mi.cur_digit = cur_pos;
    
    mi.action = action;
    
    mi.total_digits = digits;
    
    Modify_Integer_Value(&mi);
    
    *para = mi.data;
}


/*============================================================================*/
/*
 * Function      :        TFT_Draw_Cursor.
 * Description   :        Used to shift cursor position to left or right to the spacified position.
 * Parameters    :        pos-Number of position to shift, clr_color-clear color and cursor_color.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Draw_Cursor(uint8_t pos, uint16_t clr_color, uint16_t cursor_color)
{
    uint16_t xstart,xend;
    
    //Clear field of cursor
    if(common_byte < 4)
        color_lcd_draw_rectangle(clr_color,cursX-((common_byte+1)*13),cursY,cursX+13,cursY+2);
    else
        color_lcd_draw_rectangle(clr_color,cursX-((common_byte)*13),cursY,cursX+13,cursY+2);
    
    xstart = cursX-(pos*13);
    xend = xstart+13;
    //Draw new cursor
    color_lcd_draw_rectangle(cursor_color,xstart,cursY,xend,cursY+2);
}


/*============================================================================*/
/*
 * Function      :        TFT_Draw_Cursor_Dynam_Width.
 * Description   :        Used to shift cursor position to left or right to the spacified position.
 * Parameters    :        pos-Number of position to shift, width-WIdth of cahracter, clr_color-clear color and cursor_color.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Draw_Cursor_Dynam_Width(uint8_t pos, uint8_t width, uint16_t clr_color, uint16_t cursor_color)
{
    uint16_t xstart,xend;
    
    //Clear field of cursor
    if(common_byte < 4)
        color_lcd_draw_rectangle(clr_color,cursX-((common_byte+1)*width),cursY,cursX+width,cursY+2);
    else
        color_lcd_draw_rectangle(clr_color,cursX-((common_byte)*width),cursY,cursX+width,cursY+2);
    
    xstart = cursX-(pos*width);
    xend = xstart+width;
    //Draw new cursor
    color_lcd_draw_rectangle(cursor_color,xstart,cursY,xend,cursY+2);
}

/*============================================================================*/
/*
 * Function      :  Shift_Cursor_Position.
 * Description   :  Used to shift cursor position to left or right. It can work for one decimal point before last digit
 *                  ie. If 4 digit parameter is the case then acceptable values with no decimal are 0000 to 9999 and with decimal point it will be 000.0 to 999.9.
 * Parameters    :  flag_lr-decison left/right, num_of_dig-Total digits and decimal_pos-Decimal position(0-No decimal and 1-Decimal point before last digit).
 * Return        :  None.
*/
/*============================================================================*/
void TFTShift_Cursor_Position(uint8_t flag_lr, uint8_t num_of_dig,uint8_t decimal_pos)
{
    if(flag_lr == 0)                   //Shift cursor left
    {
        if(pos_t < (num_of_dig-1))
        {
            pos_t++;
            if(decimal_pos == NO_DECIMAL_POINT)
            {
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            }
            else if(decimal_pos == ONE_DECIMAL_POINT)
            {
                if(pos_t >= 1)
                {
                    TFT_Draw_Cursor(pos_t+1,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
            }
        }
        else
        {
            pos_t = 0;
            TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
        }
    }
    else
    {
        if(pos_t > 0)
        {
            pos_t--;
            if(decimal_pos == NO_DECIMAL_POINT)
            {
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            }
            else if(decimal_pos == ONE_DECIMAL_POINT)
            {
                if(pos_t == 0)
                {
                    TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                }
                else
                {
                    TFT_Draw_Cursor(pos_t+1,ILI9341_WHITE,ILI9341_RED);
                }
            }
        }
        else
        {
            pos_t = num_of_dig-1;
            if(decimal_pos == NO_DECIMAL_POINT)
            {
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            }
            else if(decimal_pos == ONE_DECIMAL_POINT)
            {
                TFT_Draw_Cursor(pos_t+1,ILI9341_WHITE,ILI9341_RED);
            }
        }
    }
}



void Set_Codes_Menu_Outlines(void)
{
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    LCDPutStr("SET CODE",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);    
    LCDPutStr("PARAMETERS",95,17,XLARGE,ILI9341_WHITE,ILI9341_BLACK);
    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);   
    
    draw_hollow_rect(ILI9341_WHITE,5,50,55,80);
    draw_hollow_rect(ILI9341_WHITE,65,50,275,80);
    draw_hollow_rect(ILI9341_WHITE,5,85,55,115);
    draw_hollow_rect(ILI9341_WHITE,65,85,275,115);
    draw_hollow_rect(ILI9341_WHITE,5,120,55,150);
    draw_hollow_rect(ILI9341_WHITE,65,120,275,150);
    draw_hollow_rect(ILI9341_WHITE,5,155,55,185);
    draw_hollow_rect(ILI9341_WHITE,65,155,275,185);
    draw_hollow_rect(ILI9341_WHITE,5,190,55,220);
    draw_hollow_rect(ILI9341_WHITE,65,190,275,220);

    draw_hollow_rect(ILI9341_WHITE,280,50,310,80);
    draw_hollow_rect(ILI9341_WHITE,280,85,310,115);
    draw_hollow_rect(ILI9341_WHITE,280,120,310,150);
    draw_hollow_rect(ILI9341_WHITE,280,155,310,185);
    draw_hollow_rect(ILI9341_WHITE,280,190,310,220);
}


void Set_Codes_Outlines(void)
{    
    draw_hollow_rect(ILI9341_WHITE,5,85,55,115);
    draw_hollow_rect(ILI9341_WHITE,5,120,55,150);
    draw_hollow_rect(ILI9341_WHITE,5,155,55,185);
    draw_hollow_rect(ILI9341_WHITE,5,190,55,220);
    
    draw_hollow_rect(ILI9341_WHITE,65,85,275,115);    
    draw_hollow_rect(ILI9341_WHITE,65,120,275,150);    
    draw_hollow_rect(ILI9341_WHITE,65,155,275,185);    
    draw_hollow_rect(ILI9341_WHITE,65,190,275,220);

    draw_hollow_rect(ILI9341_WHITE,280,85,310,115);
    draw_hollow_rect(ILI9341_WHITE,280,120,310,150);
    draw_hollow_rect(ILI9341_WHITE,280,155,310,185);
    draw_hollow_rect(ILI9341_WHITE,280,190,310,220);
}

void TFT_Main_Menu_Outlines(void)
{
    color_lcd_draw_rectangle(ILI9341_BLACK,6,9,313,39);
    LCDPutStr("SYSTEM SETUP",95,17,XLARGE,ILI9341_WHITE,ILI9341_BLACK); //SYSTEM SETUP
    color_lcd_draw_rectangle(ILI9341_NAVY,5,45,315,230);
    
    draw_hollow_rect(ILI9341_WHITE,10,50,275,80);
    draw_hollow_rect(ILI9341_WHITE,10,85,275,115);
    draw_hollow_rect(ILI9341_WHITE,10,120,275,150);
    draw_hollow_rect(ILI9341_WHITE,10,155,275,185);
    draw_hollow_rect(ILI9341_WHITE,10,190,275,220);
    
    draw_hollow_rect(ILI9341_WHITE,280,50,310,80);
    draw_hollow_rect(ILI9341_WHITE,280,85,310,115);
    draw_hollow_rect(ILI9341_WHITE,280,120,310,150);
    draw_hollow_rect(ILI9341_WHITE,280,155,310,185);
    draw_hollow_rect(ILI9341_WHITE,280,190,310,220);
}


/*============================================================================*/
/*
 * Function      :        Highlight_Single_Row.
 * Description   :        Used to select single row.
 * Parameters    :        sel- Highlight row number, 0=INC key pressed and 1=DEC key pressed, row-Row number.
 * Return        :        None.
*/
/*============================================================================*/
void Highlight_Single_Row(uint8_t sel, uint8_t row)
{
    switch(row)
    {
        case 1:
        {            
            if(sel == 0)
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,86,309,114);
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,191,309,219);
            }
            color_lcd_draw_rectangle(ILI9341_WHITE,281,51,309,79);
            LCDPutStr(">>",285,57,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
            break;
        }
        case 2:
        {
            if(sel == 0)
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,121,309,149);
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,51,309,79);
            }
            color_lcd_draw_rectangle(ILI9341_WHITE,281,86,309,114);
            LCDPutStr(">>",285,92,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
            break;
        }    
        case 3:
        {
            if(sel == 0)
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,156,309,184);
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,86,309,114);
            }
            color_lcd_draw_rectangle(ILI9341_WHITE,281,121,309,149);
            LCDPutStr(">>",285,127,XLARGE,ILI9341_NAVY,ILI9341_WHITE);           
            break;
        }
        case 4:
        {
            if(sel == 0)
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,191,309,219);
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,121,309,149);
            }
            color_lcd_draw_rectangle(ILI9341_WHITE,281,156,309,184);
            LCDPutStr(">>",285,162,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
            break;
        }
        case 5:
        {
            if(sel == 0)
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,51,309,79);
            }
            else
            {
                color_lcd_draw_rectangle(ILI9341_NAVY,281,156,309,184);
            }
            color_lcd_draw_rectangle(ILI9341_WHITE,281,191,309,219);
            LCDPutStr(">>",285,197,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
            break;
        }
    }
}



/*============================================================================*/
/*
 * Function      :        Clear_Rows.
 * Description   :        Used to clear menu rows.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Clear_Rows(void)
{
    LCDPutStr("                ",75,57,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("                ",75,92,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("                ",75,127,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("                ",75,162,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("                ",75,197,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
}

/*============================================================================*/
/*
 * Function      :        Display_Main_Menu.
 * Description   :        Used to display main menus of all users.
 * Parameters    :        sel- Highlight row number, 0=INC key pressed and 1=DEC key pressed.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Main_Menu(void)
{
    uint8_t rcnt;
    
    mv.max = 5;
    mv.min = 1;
    
    TFT_Main_Menu_Outlines();
    
    LCDPutStr("OPERATOR VIEW",30,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("OPERATOR SETTINGS",30,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SUPERVISOR SETTINGS",30,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SITE SETTINGS",30,163,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("FACTORY SETTINGS",30,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
    rcnt = mv.menu_cnt%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(0,rcnt);
}

/*============================================================================*/
/*
 * Function      :        TFTShow_YESNO_Confirmation.
 * Description   :        Used to enable disable option.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTShow_YESNO_Confirmation(void)
{
    if(prv8_val1)
        LCDPutStr("  YES  ",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    else
        LCDPutStr("  NO   ",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
}


/*============================================================================*/
/*
 * Function      :        TFTShow_Enable_Disable.
 * Description   :        Used to enable disable option.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTShow_Enable_Disable(void)
{
    if(prv8_val1)
        LCDPutStr("ENABLE ",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    else
        LCDPutStr("DISABLE",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
}

/*============================================================================*/
/*
 * Function      :        TFTShow_Languages.
 * Description   :        Used to choose languages.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTShow_Languages(void)
{
    if(prv8_val1)
        LCDPutStr("ENGLISH",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    else
        LCDPutStr(" HINDI ",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
}


/*============================================================================*/
/*
 * Function      :        TFTShow_Load_UOM.
 * Description   :        Used to enable disable option.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTShow_Load_UOM(void)
{
    if(prv8_val1)
        LCDPutStr("Tn & M",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    else
        LCDPutStr("Kp & F",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
}

/*============================================================================*/
/*
 * Function      :        TFTShow_WindSpeed_UOM.
 * Description   :        Used to enable disable option.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTShow_WindSpeed_UOM(void)
{
    if(prv8_val1)
        LCDPutStr("kmph",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    else
        LCDPutStr("mps ",valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
}


/*============================================================================*/
/*
 * Function      :        Enable_Disable_Menu.
 * Description   :        Used to modify two digit menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Enable_Disable_Menu(void)
{
    if((key.increment == 1)||(key.decrement == 1))
    {
        prv8_val1 = !prv8_val1;
        
        TFTShow_Enable_Disable();
        
        key.increment = 0;
        key.decrement = 0;
    }
}


/*============================================================================*/
/*
 * Function      :        Current_Prev_Val_Screen.
 * Description   :        Used to display back screen for setting parameter single or double
 * Parameters    :        para-select single parameter or double
 * Return        :        None.
*/
/*============================================================================*/
void Current_Prev_Val_Screen(uint8_t para, uint16_t fg_color, uint16_t bg_color)
{
    color_lcd_draw_rectangle(bg_color,5,85,310,220);
    
    if(para == 1)
    {
        LCDPutStr("CURRENT VALUE   :",35,110,MEDIUM,fg_color,bg_color);
        LCDPutStr("PREVIOUSE VALUE :",35,175,MEDIUM,fg_color,bg_color);
   
        color_lcd_draw_rectangle(fg_color,180,100,280,140);   
        draw_hollow_rect(bg_color,182,102,278,138);
        color_lcd_draw_rectangle(fg_color,180,165,280,205);  
        draw_hollow_rect(bg_color,182,167,278,203);
    }
    else if(para == 2)
    {
        LCDPutStr("CV:",15,110,MEDIUM,fg_color,bg_color);
        LCDPutStr("PV:",15,175,MEDIUM,fg_color,bg_color);     
        LCDPutStr("CC:",170,110,MEDIUM,fg_color,bg_color);
        LCDPutStr("PC:",170,175,MEDIUM,fg_color,bg_color);  
        color_lcd_draw_rectangle(fg_color,45,100,145,140);
        draw_hollow_rect(bg_color,47,102,143,138);
        color_lcd_draw_rectangle(fg_color,45,165,145,205); 
        draw_hollow_rect(bg_color,47,167,143,203);
        color_lcd_draw_rectangle(fg_color,200,100,300,140);
        draw_hollow_rect(bg_color,202,102,298,138);
        color_lcd_draw_rectangle(fg_color,200,165,300,205);
        draw_hollow_rect(bg_color,202,167,298,203);    
    }    
}


/*============================================================================*/
/*
 * Function      :        Inc_Dec_2Digit_Menu.
 * Description   :        Used to modify two digit menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_2Digit_Menu(void)
{
    char dbuf[5];
    
    if((key.bypass == 1)||(key.duty == 1))
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
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}


/*============================================================================*/
/*
 * Function      :        Inc_Dec_3Digit_Menu.
 * Description   :        Used to modify three digit menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_3Digit_Menu(void)
{
    char dbuf[5];
    
    if((key.bypass == 1)||(key.duty == 1))
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

                sprintf(dbuf,"%03d",(uint16_t)common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        else
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%03d",(uint16_t)common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}


/*============================================================================*/
/*
 * Function      :        Inc_Dec_4Digit_Menu.
 * Description   :        Used to modify four digit menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_4Digit_Menu(void)
{
    char dbuf[5];
    
    if((key.bypass == 1)||(key.duty == 1))
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

                sprintf(dbuf,"%04d",(uint16_t)common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        else
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%04d",(uint16_t)common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}

/*============================================================================*/
/*
 * Function      :        Inc_Dec_5Digit_Menu.
 * Description   :        Used to modify five digit menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_5Digit_Menu(void)
{
    char dbuf[5];
    
    if((key.bypass == 1)||(key.duty == 1))
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

                sprintf(dbuf,"%05lu",common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        else
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%05lu",common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}

/*============================================================================*/
/*
 * Function      :        Inc_Dec_10Digit_Menu.
 * Description   :        Used to modify ten digit menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_10Digit_Menu(void)
{
    char dbuf[15];
    
    if((key.bypass == 1)||(key.duty == 1))
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

                sprintf(dbuf,"%010lu",common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        else
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%010lu",common_long);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}

/*============================================================================*/
/*
 * Function      :        Inc_Dec_3Digit_1Decimal_Menu.
 * Description   :        Used to modify three digit with one decimal menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_3Digit_1Decimal_Menu(void)
{
    char dbuf[5];
    
    if((key.bypass == 1)||(key.duty == 1))
    {
        if(key.duty == 1) TFTShift_Cursor_Position(0,common_byte,ONE_DECIMAL_POINT);
        else              TFTShift_Cursor_Position(1,common_byte,ONE_DECIMAL_POINT);
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

                sprintf(dbuf,"%04.1f",((float)common_long)/10.0);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        else
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%04.1f",((float)common_long)/10.0);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}


/*============================================================================*/
/*
 * Function      :        Inc_Dec_4Digit_1Decimal_Menu.
 * Description   :        Used to modify four digit with one decimal menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_4Digit_1Decimal_Menu(void)
{
    char dbuf[5];
    
    if((key.bypass == 1)||(key.duty == 1))
    {
        if(key.duty == 1) TFTShift_Cursor_Position(0,common_byte,ONE_DECIMAL_POINT);
        else              TFTShift_Cursor_Position(1,common_byte,ONE_DECIMAL_POINT);
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

                sprintf(dbuf,"%05.1f",((float)common_long)/10.0);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        else
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                sprintf(dbuf,"%05.1f",((float)common_long)/10.0);
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}


/*============================================================================*/
/*
 * Function      :        Inc_Dec_3Digit_1Decimal_WSign_Menu.
 * Description   :        Used to modify three digit with one decimal with (+/-)sign menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void Inc_Dec_3Digit_1Decimal_WSign_Menu(void)
{
    char dbuf[5];
    
    if((key.bypass == 1)||(key.duty == 1))
    {
        if(key.duty == 1) TFTShift_Cursor_Position(0,common_byte+1,ONE_DECIMAL_POINT);      //+1 for (+/-)Sign
        else              TFTShift_Cursor_Position(1,common_byte+1,ONE_DECIMAL_POINT);
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
                
                if(pos_t == 3)  value_sign_flag = !value_sign_flag;
                
                if(value_sign_flag) sprintf(dbuf,"-%04.1f",((float)common_long)/10.0);
                else                sprintf(dbuf,"+%04.01f",((float)common_long)/10.0);
                
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        else
        {
            while(key.dec_ftp == 1)
            {
                Modify_System_Parameter(common_byte,DEC_DATA,pos_t,&common_long);
                
                if(pos_t == 3)  value_sign_flag = !value_sign_flag;
                
                if(value_sign_flag) sprintf(dbuf,"-%04.1f",((float)common_long)/10.0);
                else                sprintf(dbuf,"+%04.01f",((float)common_long)/10.0);
                
                LCDPutStr(dbuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
                Delay_1ms(500);
            }
        }
        key.increment = 0;
        key.decrement = 0;
    }
}


/*============================================================================*/
/*
 * Function      :        TFTOperator_View_Pages.
 * Description   :        Used to display pages.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_View_Pages(uint8_t page)
{
    if(page == 0)
    {
        LCDPutStr("001",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("VIEW PR-LEN-ANG CNTS",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("002",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VIEW TILT ADC COUNTS",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("003",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("VIEW OUT TRIG COUNTS",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("004",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VIEW LOADCELL COUNTS",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("005",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VIEW OFFSETS        ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 1)
    {
        LCDPutStr("006",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("VIEW SET POINTS     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("007",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            LCDPutStr("VIEW OUT TRIG CALIB.",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("NOT APPLICABLE      ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("008",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if(sys.para.Select_System == FORK_LIFT)
            LCDPutStr("VIEW PRESS CAL POINT",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("VW ZLOAD PRESS CURVE",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("009",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VIEW CRANE DETAILS: ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("010",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("VIEW CRANE-DIMENSION",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
   else if(page == 2)
    {
        LCDPutStr("011",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("VIEW SERIAL NUMBER",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("012",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VIEW GPS PARAMETER",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("013",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("014",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("015",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }   
}



/*============================================================================*/
/*
 * Function      :        TFTOperator_Setcode_Pages.
 * Description   :        Used to display pages.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_Setcode_Pages(uint8_t page)
{
    LCDPutStr("051",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SET DUTY            ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    LCDPutStr("052",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
    LCDPutStr("SET MAIN HOOK FALLS ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    LCDPutStr("053",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SET UOM             ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    LCDPutStr("054",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
    LCDPutStr("RESERVED            ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    LCDPutStr("055",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
    LCDPutStr("RESERVED            ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
}


/*============================================================================*/
/*
 * Function      :        TFTSupervisor_Setcode_Pages.
 * Description   :        Used to display pages.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTSupervisor_Setcode_Pages(uint8_t page)
{
    if(page == 0)
    {
        LCDPutStr("100",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("ENABLE BYPASS SWITCH",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("101",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LOAD SP1 VALUE  ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("102",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET LOAD SP2 VALUE  ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("103",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LOAD SP3 VALUE  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("104",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LOAD SP4 VALUE  ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 1)
    {
        LCDPutStr("105",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET BOOM OFFSET     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("106",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET BOOM HEAD OFFSET",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("107",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET BOOM TIP OFFSET ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("108",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET MAIN SAMPLE CNTS",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("109",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET HOOK LOAD       ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 2)
    {
        LCDPutStr("110",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if(sys.para.Select_System == FORK_LIFT)
        {
            LCDPutStr("CALIB HEIGHT MIN    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        }
        else
        {
            if(sys.para.mpoint_len_enable_bit == 0)
            {
                LCDPutStr("CALIB LENGTH MIN    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                menu_absnt_flag = 0;
            }
            else
            {
                LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                menu_absnt_flag = 1;
            }
        }

        LCDPutStr("111",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if(sys.para.Select_System == FORK_LIFT)
            LCDPutStr("CALIB HEIGHT MAX    ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
        {
            LCDPutStr("NOT AVAILABLE       ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            menu_absnt_flag = 1;
        }

        LCDPutStr("112",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
            LCDPutStr("CALIB KNUC ANG MIN  ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("CALIB ANGLE MIN     ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("113",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
            LCDPutStr("CALIB KNUC ANG MAX  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("CALIB ANGLE MAX     ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("114",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("CALIB MANGLE MIN    ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 3)
    {
        LCDPutStr("115",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("CALIB MANGLE MAX    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("116",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if(sys.para.Select_System == FORK_LIFT)
        {
            LCDPutStr("NUMOF LOAD CAL POINT",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            menu_absnt_flag = 0;
        }
        else
        {
            LCDPutStr("NOT AVAILABLE       ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            menu_absnt_flag = 1;
        }
        
        LCDPutStr("117",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if(sys.para.Select_System == FORK_LIFT)
            LCDPutStr("CALIB PRESS MIN     ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            LCDPutStr("CALIB OUT TRIG MIN  ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("SET DUTY TYPE       ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("118",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if(sys.para.Select_System == FORK_LIFT)
            LCDPutStr("CALIB PRESS MAX     ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            LCDPutStr("CALIB OUT TRIG MAX  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("CALIB HOOK LOAD     ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("119",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("PASSWORD STATUS     ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 4)
    {
        LCDPutStr("120",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("BOOM DOWN RELAY STAT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("121",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("BOOM UP RELAY STAT  ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("122",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("HOOTER RELAY STATUS ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("123",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("A2B STATUS          ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("124",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("HOOK HEIGHT STATUS  ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 5)
    {
        LCDPutStr("125",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RIG LOAD LIMIT      ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("126",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RIG BOOM ANGLE LIMI ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("127",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RIG BOOM LENGTH LIMT",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("128",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET DEFAULT DUTY    ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("129",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("EDIT ENGINE NUMBER  ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 6)
    {
        LCDPutStr("130",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("ALL DUTY ART. DERATE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("131",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VIEW DATA LOGGED    ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("132",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SEND DATA TO PC     ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("133",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LOW CUTOFF ANGLE",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("134",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET HIGH CUTOFF ANGL",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 7)
    {
        LCDPutStr("135",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("DUTY SELECT STATUS  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("136",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("ENABLE SNATCH BLOCK ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("137",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET SNATCH BLOCK VAL",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("138",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if(sys.para.Select_System == FORK_LIFT)     //Spacial case for SCA forklift
            LCDPutStr("FORKLIFT ART. METHOD",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("BYPASS METHOD       ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("139",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
           (sys.para.Select_System == TELESCOPIC_RT40))
            LCDPutStr("CALIB TILT ANGLE    ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("FRONT TILT ANG CALIB",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 8)
    {
        LCDPutStr("140",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
           (sys.para.Select_System == TELESCOPIC_RT40))
            LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("REAR TILT ANG CALIB ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("141",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
           (sys.para.Select_System == TELESCOPIC_RT40))
            LCDPutStr("TILT ANGL CUTOFF    ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("FRONT TILT CUTOFF   ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("142",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||
           (sys.para.Select_System == TELESCOPIC_RT40))
            LCDPutStr("NOT AVAILABLE       ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("REAR TILT CUTOFF    ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("143",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VOICE LANGUAGE      ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("144",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET ZLOAD MASK      ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 9)
    {
        LCDPutStr("145",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET LOAD ANN. TIME  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("146",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET BOOM HIGHT LIMIT",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("147",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET BOOM ANGLE LIMIT",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("148",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET BOOM HIGHT OFSET",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("149",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET GAIN OFFSET     ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 10)
    {
        LCDPutStr("150",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("CALIB MANBAS MIN    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("151",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("CALIB MANBAS MAX    ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("152",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("EN ART.DRATE SWITCH ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("153",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if(sys.para.art_enable_bit)
            LCDPutStr("SET ART.DERATE VAL  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("NOT AVAILABLE       ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("154",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET SLEW OFFSET     ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 11)
    {
        LCDPutStr("155",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if((sys.para.Select_System != TMC_MANBASKET2)&&(sys.para.Select_System != TELESCOPIC_RT40))
            LCDPutStr("NOT AVAILABLE       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("ENABLE ON BOARD TILT",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("156",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if((sys.para.Select_System == TMC_MANBASKET))
            LCDPutStr("ENABLE SLAVE DISPLAY",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("NOT AVAILABLE       ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("157",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("EN MPOINT LENGTH CAL",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("158",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("NUMOF LEN MPOINT CAL",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("159",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        if(sys.para.mpoint_len_enable_bit)
            LCDPutStr("LENGTH MPOINT CALIB ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("NOT AVAILABLE       ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);        
    }
}


/*============================================================================*/
/*
 * Function      :        TFTSite_Setcode_Pages.
 * Description   :        Used to display pages.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTSite_Setcode_Pages(uint8_t page)
{
    if(page == 0)
    {
        LCDPutStr("200",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET MIN BOOM LENGTH ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("201",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET MAX BOOM LENGTH ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("202",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET PRESS P1 CHANN  ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("203",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET PRESS P2 CHANN  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("204",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LENGTH CHANN    ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 1)
    {
        LCDPutStr("205",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
            LCDPutStr("SET KNUCKLE ANG CHAN",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("SET BOOM ANGLE CHANN",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("206",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);        
        LCDPutStr("SET MAIN ANG CHANN  ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("207",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET LOW ERR COUNTS  ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("208",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET HIGH ERR COUNTS ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("209",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET CAL SAMPLE COUNT",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 2)
    {
        LCDPutStr("210",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("LOAD CORR FACTOR    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("211",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("LOAD CORR LIMIT     ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("212",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("COPY ZERO CALIB     ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("213",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET DATE & TIME     ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("214",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("EDIT LENGTH COUNTS  ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 3)
    {
        LCDPutStr("215",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("BOOM LENGTH CORR-1  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("216",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("BOOM LENGTH CORR-2  ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("217",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("BOOM LENGTH CORR-3  ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("218",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("BOOM LENGTH CORR-4  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("219",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("FAIL SAFE STATUS    ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 4)
    {
        LCDPutStr("220",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if(sys.para.Select_System == TIL_PIXEF_TELE_PNC)
            LCDPutStr("SET LD CORR(0.2-2T) ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("SET LD CORR(0.6-2T) ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("221",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LD CORR(2-4T)   ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("222",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET LD CORR(4-9T)   ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("223",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LD CORR(9-12T)  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("224",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET LD CORR(>12T)   ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 5)
    {
        LCDPutStr("225",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);        
        LCDPutStr("LENGTH FACTORS      ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("226",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("PRESSURE FACTOR     ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("227",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("COPY NO LOAD PCURVE ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("228",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("EN PNH SWITCH       ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("229",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET PNH THRESHOLD   ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 6)
    {
        LCDPutStr("230",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);        
        LCDPutStr("NUM OF BOOM PARTS   ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("231",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("VIEW DUTY TABLE     ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("232",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("ENBLE ANGLE FRZ LOAD",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("233",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("234",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
}


/*============================================================================*/
/*
 * Function      :        TFTFactory_Setcode_Pages.
 * Description   :        Used to display pages.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTFactory_Setcode_Pages(uint8_t page)
{
    if(page == 0)
    {
        LCDPutStr("300",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("CALIB PRESS P1 MIN  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("301",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("CALIB PRESS P1 MAX  ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("302",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("CALIB PRESS P2 MIN  ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("303",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("CALIB PRESS P2 MAX  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("304",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("LOAD AVERAGING VALUE",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 1)
    {
        LCDPutStr("305",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("WINDOW SAMPLE SIZE  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("306",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("NUM OF LUFF CYLINDER",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("307",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("WRITE CSV TO MEMORY ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("308",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("ENTER CRANE DIMENSION ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("309",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET BOOM ANGLE MIN  ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 2)
    {
        LCDPutStr("310",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET BOOM ANGLE MAX  ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("311",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET BOOM LENGTH MIN ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("312",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET BOOM LENGTH MAX ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("313",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SELECT CRANE MODEL  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("314",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET BAUDRATE        ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 3)
    {
        LCDPutStr("315",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("ERASE DATA LOGS     ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("316",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SELECT SENSOR       ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("317",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("DEFLT BM LEN ADC CNT",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("318",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("WINDOW SAMPLE SIZE1 ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("319",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SELECT STICKER TYPE ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 4)
    {
        LCDPutStr("320",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET INSALLATION DATE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("321",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET PERCENT STATUS  ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("322",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SET CORR. LOAD      ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("323",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("EN NUM OF CALIB     ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        
        LCDPutStr("324",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET SO NUMBER       ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 5)
    {
        LCDPutStr("325",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("P1P2 TO RS232 PC    ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("326",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET RADIUS CUTOFF   ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                
        LCDPutStr("327",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        if(sys.para.Select_System == PNC_FORK)
            LCDPutStr("SET FORK DUTY       ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else if(sys.para.Select_System == ACE_MANBASKET_HXP)
            LCDPutStr("SET MANBAS DUTY     ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        else
            LCDPutStr("NOT AVAILABLE       ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("328",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SET MANBASKET CHAN  ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("329",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("SELECT LENGTH DRUM  ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 6)
    {
        LCDPutStr("330",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("SELECT SYSTEM       ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("331",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("NOT AVAILABLE       ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("332",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("NOT AVAILABLE       ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("333",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("NOT AVAILABLE       ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("334",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("NOT AVAILABLE       ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
    else if(page == 7)
    {
        LCDPutStr("335",18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("MASTER RESET        ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("336",18,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("337",18,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("RESERVED            ",75,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("338",18,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        LCDPutStr("339",18,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY); 
        LCDPutStr("RESERVED            ",75,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    }
}









