
#include "main.h"



/*============================================================================*/
/*
 * Function      :        Display_Operator_View_Menu.
 * Description   :        Used to display operator menu first page.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Operator_View_Menu(uint8_t page)
{
    uint8_t rcnt;
    
    mv.max = 15;
    mv.min = 1;
    
    Set_Codes_Menu_Outlines();
    
    TFTOperator_View_Pages(page);
    
    rcnt = mv.operator_view%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(0,rcnt);
}


/*============================================================================*/
/*
 * Function      :        TFTSelect_Operator_View_Menu.
 * Description   :        Used to highlight operator menu pages.
 * Parameters    :        sel-highlight row number(1 to 5).
 * Return        :        None.
*/
/*============================================================================*/
void TFTSelect_Operator_View_Menu(uint8_t sel)
{
    uint8_t rcnt;
    
    rcnt = mv.operator_view%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(sel,rcnt);
    
    if(((mv.operator_view == 1)&&(sel == 1))||((mv.operator_view == 5)&&(sel == 0)))        {Clear_Rows();TFTOperator_View_Pages(0);}
    else if(((mv.operator_view == 6)&&(sel == 1))||((mv.operator_view == 10)&&(sel == 0)))   {Clear_Rows();TFTOperator_View_Pages(1);}
     else if(((mv.operator_view == 11)&&(sel == 1))||((mv.operator_view == 15)&&(sel == 0)))  {Clear_Rows();TFTOperator_View_Pages(2);}
}


/*============================================================================*/
/*
 * Function      :        TFTCommon_OperatorVw_Escape_Function.
 * Description   :        Used to take escape from operator view menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTCommon_OperatorVw_Escape_Function(void)
{
    if((mv.operator_view >= 1)&&(mv.operator_view <= 5))        TFTDisplay_Operator_View_Menu(0);
    else if((mv.operator_view >= 6)&&(mv.operator_view <= 10))  TFTDisplay_Operator_View_Menu(1);
    else if((mv.operator_view >= 11)&&(mv.operator_view <= 15))  TFTDisplay_Operator_View_Menu(2);
}


/*============================================================================*/
/*
 * Function      :        TFTOperator_Viewing.
 * Description   :        Used to view settings.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_Viewing(void)
{
    char obuf[20],slen;
    
    switch(mv.operator_view)
    {
        case 1:
        {
            TFTOperator_View_Pres_Len_Ang_Cnts(sys.para.pressure_p1_chann,sys.para.pressure_p2_chann,sys.para.bm_length_chann,sys.para.main_ang_chann,sys.para.bm_angle_chann,32000,32000,800,700,400,0);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 2:
        {
            TFTOperator_View_Tilt_ADC_Cnts(0);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 3:
        {
            TFTOperator_View_OTG_ADC_Cnts(0);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 4:
        {
            TFTOperator_View_Loadcell_Cnts(0);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 5:
        {
            TFTView_Offset(sys.para.bm_offset,sys.para.bm_head_offset,sys.para.bm_tip_offset,sys.para.slew_offset,sys.para.bm_ht_offset);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 6:
        {
            TFTView_Set_Points(sys.para.sp1_perc,sys.para.sp2_perc,sys.para.sp3_perc,sys.para.sp4_perc);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 7:
        {
            TFTOperator_View_OTG_Calibration();
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 8:
        {
            if(sys.para.Select_System == FORK_LIFT)
            {
                temp_duty_indx = 1;
//                Display_MinMax_Option_Menu();
                menu_stat = VIEW_PRESS_CALIB_POINT_PAGE1;
            }
            else
            {
//                temp_duty_indx = sys.para.duty;
                sprintf(obuf,"%03d",mv.operator_view);
                LCDPutStr(obuf,18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                color_lcd_draw_rectangle(ILI9341_NAVY,75,57,260,75);    //Clear title
                color_lcd_draw_rectangle(ILI9341_WHITE,281,51,309,79);
                LCDPutStr(">>",285,57,XLARGE,ILI9341_NAVY,ILI9341_WHITE);

                color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
                
                LCDPutStr("VW ZLOAD PRESS CURVE",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                if(sys.para.Select_System == TMC_MANBASKET || sys.para.Select_System == TMC_MANBASKET2)  //V1.17.1
                 {    
                   color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);
                   LCDPutStr("RESERVED",125,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                 }
                else
                {
                prv16_val1 = sys.para.duty;
                LCDPutStr("SELECT DUTY:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
                
                color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
                draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
                
                sprintf(obuf,"%03d",prv16_val1);
                slen = strlen(obuf)*13;
                cursX = 180+((100-slen)/2);
                cursY = 100+20-8; 
                pos_t = 0;
                valX = cursX;
                valY = cursY;
                
                LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

                common_byte = 3;
                common_long = prv16_val1;    

                cursX += (common_byte-1)*13;
                cursY += 19;
                TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
                menu_stat = VIEW_PC_PAGE1;
                }
            }
            break;
        }
        case 9:    
        {
            char l1buf[20],l2buf[20];//change here 26/04/23 v1.16 operator  view crane details   
            sprintf(l1buf,"%02d/%02d/%04d",sys.para.insta_dd,sys.para.insta_mm,sys.para.insta_yy);
            sprintf(l2buf,"%05lu",sys.para.so_number);
            Crane_Details_Operator_View(crane_model,crane_make,crane_type,l2buf,l1buf);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
         case 10:    
        {
            TFTOperator_View_CraneDimensions(0); //V1.17.1 
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 11:    
        {
            char sbuf[50];
            
            sprintf(sbuf,"%s","KAMPL_KIOT_");
           // sprintf(sys_sr_no,"%05d",sys_sr_no);
            //UART_Send_String(UART_MODULE2,sys_sr_no);
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            LCDPutStr(sbuf,70,127, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr(sys_sr_no,205,127, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
        case 12:    
        {
            view_gps_parameter(); //V1.17.1 
            menu_stat = OPERATOR_VIEW_PAGE2;
            break;
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFTOperator_View_Pres_Len_Ang_Cnts.
 * Description   :        Used to view live adc counts.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_View_Pres_Len_Ang_Cnts(uint8_t p1_chn, uint8_t p2_chn, uint8_t len_chn, uint8_t mang_chn, uint8_t kang_chn, uint16_t p1_cnt, uint16_t p2_cnt, uint16_t len_cnt, uint16_t mang_cnt, uint16_t kang_cnt, uint8_t Select_screen)
{
    char sbuf[10];
    
    if(Select_screen == 0)
    {
        color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
        LCDPutStr("PARAMETER",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);
        LCDPutStr("CHAN",150,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
        LCDPutStr("COUNTS",220,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
        
        color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
        LCDPutStr("P1 PRESSURE:",15,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("P2 PRESSURE:",15,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("BOOM LENGTH:",15,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("MBOOM ANGLE:",15,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("KBOOM ANGLE:",15,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
        color_lcd_draw_rectangle(ILI9341_WHITE,140,50,190,80);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,85,190,115);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,120,190,150);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,155,190,185);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,190,190,220);
    
        color_lcd_draw_rectangle(ILI9341_WHITE,195,50,310,80);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,85,310,115);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,120,310,150);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,155,310,185);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,190,310,220);
    }
    else if(Select_screen == 1)
    {
        sprintf(sbuf,"%03d",p1_chn);
        LCDPutStr(sbuf,145,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(sbuf,"%03d",p2_chn);
        LCDPutStr(sbuf,145,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(sbuf,"%03d",len_chn);
        LCDPutStr(sbuf,145,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
        {
            sprintf(sbuf,"%03d",mang_chn);
            LCDPutStr(" NA",145,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf( sbuf,"%03d",kang_chn);
            LCDPutStr(sbuf,145,197,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        else
        {
            sprintf(sbuf,"%03d",kang_chn);
            LCDPutStr(sbuf,145,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf( sbuf,"%03d",mang_chn);
            LCDPutStr(" NA",145,197,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
    
        sprintf(sbuf,"%05lu",(uint32_t)p1_cnt);
        LCDPutStr(sbuf,205,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        sprintf(sbuf,"%05lu",(uint32_t)p2_cnt);
        LCDPutStr(sbuf,205,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        sprintf(sbuf,"%05lu",(uint32_t)len_cnt);
        LCDPutStr(sbuf,205,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
        {
            sprintf(sbuf,"%05lu",(uint32_t)mang_cnt);
            LCDPutStr(sbuf,205,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            sprintf(sbuf,"%05lu",(uint32_t)kang_cnt);
            LCDPutStr(sbuf,205,197,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        else
        {
            sprintf(sbuf,"%05lu",(uint32_t)kang_cnt);
            LCDPutStr(sbuf,205,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//            sprintf(sbuf,"%05lu",(uint32_t)mang_cnt);
            LCDPutStr("UNAVAILBL",200,197,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
    }        
}


/*============================================================================*/
/*
 * Function      :        TFTOperator_View_Tilt_ADC_Cnts.
 * Description   :        Used to view Tilt angle calibration values.
 * Parameters    :        sel: select lables or values.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_View_Tilt_ADC_Cnts(uint8_t sel)
{
    char lbuf[10];
    uint8_t slen;
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
        slen = strlen("TILT SENSOR COUNTS")*9;
        
        slen = ((320-slen)/2);
        LCDPutStr("TILT SENSOR COUNTS",slen,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK);

        color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);

        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            LCDPutStr("TILT X VALUE  :",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("TILT Y VALUE  :",35,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

            color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
            draw_hollow_rect(ILI9341_NAVY,182,102,278,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,180,165,280,205);  
            draw_hollow_rect(ILI9341_NAVY,182,167,278,203);

            sprintf(lbuf,"%04d",Tilt_1_X_cnt);
            slen = strlen(lbuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_1_Y_cnt);
            slen = strlen(lbuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        else
        {
            LCDPutStr("FX:",15,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);      //Front X
            LCDPutStr("FY:",15,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);      //Front Y 
            LCDPutStr("RX:",170,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);     //Rear X 
            LCDPutStr("RY:",170,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);     //Rear Y 
            color_lcd_draw_rectangle(ILI9341_WHITE,45,100,145,140);
            draw_hollow_rect(ILI9341_NAVY,47,102,143,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,45,165,145,205); 
            draw_hollow_rect(ILI9341_NAVY,47,167,143,203);
            color_lcd_draw_rectangle(ILI9341_WHITE,200,100,300,140);
            draw_hollow_rect(ILI9341_NAVY,202,102,298,138);
            color_lcd_draw_rectangle(ILI9341_WHITE,200,165,300,205);
            draw_hollow_rect(ILI9341_NAVY,202,167,298,203);

            sprintf(lbuf,"%04d",Tilt_1_X_cnt);
            slen = strlen(lbuf)*13;
            cursX = 45+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_1_Y_cnt);
            slen = strlen(lbuf)*13;
            cursX = 45+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_2_X_cnt);
            slen = strlen(lbuf)*13;
            cursX = 200+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_2_Y_cnt);
            slen = strlen(lbuf)*13;
            cursX = 200+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
    }
    else
    {
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            sprintf(lbuf,"%04d",Tilt_1_X_cnt);
            slen = strlen(lbuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_1_Y_cnt);
            slen = strlen(lbuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
        else
        {
            sprintf(lbuf,"%04d",Tilt_1_X_cnt);
            slen = strlen(lbuf)*13;
            cursX = 45+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_1_Y_cnt);
            slen = strlen(lbuf)*13;
            cursX = 45+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_2_X_cnt);
            slen = strlen(lbuf)*13;
            cursX = 200+((100-slen)/2);
            cursY = 100+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

            sprintf(lbuf,"%04d",Tilt_2_Y_cnt);
            slen = strlen(lbuf)*13;
            cursX = 200+((100-slen)/2);
            cursY = 165+20-8;
            LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        }
    }
}

/*============================================================================*/
/*
 * Function      :        TFTOperator_View_OTG_ADC_Cnts.
 * Description   :        Used to view out trigger calibration values.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_View_OTG_ADC_Cnts(uint8_t sel)
{
    char lbuf[10];
    uint8_t slen;
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
        slen = strlen("OTG PRESSURE VALUES")*9;
        slen = ((320-slen)/2);
        LCDPutStr("OTG PRESSURE VALUES",slen,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK);

        color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
        LCDPutStr("P1:",15,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);      //Front X
        LCDPutStr("P2:",15,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);      //Front Y 
        LCDPutStr("P3:",170,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);     //Rear X 
        LCDPutStr("P4:",170,175,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);     //Rear Y 
        color_lcd_draw_rectangle(ILI9341_WHITE,45,100,145,140);
        draw_hollow_rect(ILI9341_NAVY,47,102,143,138);
        color_lcd_draw_rectangle(ILI9341_WHITE,45,165,145,205); 
        draw_hollow_rect(ILI9341_NAVY,47,167,143,203);
        color_lcd_draw_rectangle(ILI9341_WHITE,200,100,300,140);
        draw_hollow_rect(ILI9341_NAVY,202,102,298,138);
        color_lcd_draw_rectangle(ILI9341_WHITE,200,165,300,205);
        draw_hollow_rect(ILI9341_NAVY,202,167,298,203);

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
    else
    {
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
}


/*============================================================================*/
/*
 * Function      :        TFTOperator_View_OTG_Calibration.
 * Description   :        Used to view OTG calibration.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_View_OTG_Calibration(void)
{
    char sbuf[10];
    
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    LCDPutStr("OTG PRESSURE",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);
    LCDPutStr("MIN",120,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
    LCDPutStr("MAX",235,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 

    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
    LCDPutStr("P1 PRESS:",10,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("P2 PRESS:",10,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("P3 PRESS:",10,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("P4 PRESS:",10,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    color_lcd_draw_rectangle(ILI9341_WHITE,100,50,185,80);
    color_lcd_draw_rectangle(ILI9341_WHITE,100,85,185,115);
    color_lcd_draw_rectangle(ILI9341_WHITE,100,120,185,150);
    color_lcd_draw_rectangle(ILI9341_WHITE,100,155,185,185);

    color_lcd_draw_rectangle(ILI9341_WHITE,210,50,295,80);
    color_lcd_draw_rectangle(ILI9341_WHITE,210,85,295,115);
    color_lcd_draw_rectangle(ILI9341_WHITE,210,120,295,150);
    color_lcd_draw_rectangle(ILI9341_WHITE,210,155,295,185);

    sprintf(sbuf,"%04d",sys.para.forkcalib_press_min[0][1]);
    LCDPutStr(sbuf,116,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04d",sys.para.forkcalib_press_min[1][1]);
    LCDPutStr(sbuf,116,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04d",sys.para.forkcalib_press_min[2][1]);
    LCDPutStr(sbuf,116,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf( sbuf,"%04d",sys.para.forkcalib_press_min[3][1]);
    LCDPutStr(sbuf,116,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04d",sys.para.forkcalib_press_max[0][1]);
    LCDPutStr(sbuf,226,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04d",sys.para.forkcalib_press_max[1][1]);
    LCDPutStr(sbuf,226,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04d",sys.para.forkcalib_press_max[2][1]);
    LCDPutStr(sbuf,226,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04d",sys.para.forkcalib_press_max[3][1]);
    LCDPutStr(sbuf,226,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE); 
}


/*============================================================================*/
/*
 * Function      :        TFTOperator_View_Loadcell_Cnts.
 * Description   :        Used to view Loadcell adc counts.
 * Parameters    :        sel: Lables or values.
 * Return        :        None.
*/
/*============================================================================*/
void TFTOperator_View_Loadcell_Cnts(uint8_t sel)
{
    char lbuf[10];
    uint8_t slen;
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
        slen = strlen("LOAD SENSOR COUNTS")*9;
        
        slen = ((320-slen)/2);
        LCDPutStr("LOAD SENSOR COUNTS",slen,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK);

        color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);

        LCDPutStr("LOADCELL COUNTS:",35,110,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

        color_lcd_draw_rectangle(ILI9341_WHITE,180,100,280,140);   
        draw_hollow_rect(ILI9341_NAVY,182,102,278,138);

        sprintf(lbuf,"%05lu",(uint32_t)can_loadcell_cnt);
        slen = strlen(lbuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8;
        LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
    else
    {
        sprintf(lbuf,"%05lu",(uint32_t)can_loadcell_cnt);
        slen = strlen(lbuf)*13;
        cursX = 180+((100-slen)/2);
        cursY = 100+20-8;
        LCDPutStr(lbuf,cursX,cursY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    }
}

/*============================================================================*/
/*
 * Function      :        TFTView_Set_Points.
 * Description   :        Used to view setpoints.
 * Parameters    :        M_sp1 to M_sp4: Main set points and A_sp1 to A_sp4: Aux set points.
 * Return        :        None.
*/
/*============================================================================*/
void TFTView_Set_Points(uint8_t M_sp1,uint8_t M_sp2,uint8_t M_sp3,uint8_t M_sp4)
{
    char sbuf[10];
    
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    LCDPutStr("SET POINTS  ",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);
    LCDPutStr("MAIN",120,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
    LCDPutStr("AUX",235,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
    LCDPutStr("SP1 VALUE:",10,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SP2 VALUE:",10,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SP3 VALUE:",10,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SP4 VALUE:",10,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    color_lcd_draw_rectangle(ILI9341_WHITE,100,50,185,80);
    color_lcd_draw_rectangle(ILI9341_WHITE,100,85,185,115);
    color_lcd_draw_rectangle(ILI9341_WHITE,100,120,185,150);
    color_lcd_draw_rectangle(ILI9341_WHITE,100,155,185,185);

    color_lcd_draw_rectangle(ILI9341_WHITE,210,50,295,80);
    color_lcd_draw_rectangle(ILI9341_WHITE,210,85,295,115);
    color_lcd_draw_rectangle(ILI9341_WHITE,210,120,295,150);
    color_lcd_draw_rectangle(ILI9341_WHITE,210,155,295,185);

    sprintf(sbuf,"%03d",M_sp1);
    LCDPutStr(sbuf,130,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    LCDPutChar('%',170,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%03d",M_sp2);
    LCDPutStr(sbuf,130,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    LCDPutChar('%',170,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%03d",M_sp3);
    LCDPutStr(sbuf,130,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    LCDPutChar('%',170,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf( sbuf,"%03d",M_sp4);
    LCDPutStr(sbuf,130,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    LCDPutChar('%',170,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

//    sprintf(sbuf,"%03d",A_sp1);
    LCDPutStr("000",240,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    LCDPutChar('%',280,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//    sprintf(sbuf,"%03d",A_sp2);
    LCDPutStr("000",240,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    LCDPutChar('%',280,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//    sprintf(sbuf,"%03d",A_sp3);
    LCDPutStr("000",240,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    LCDPutChar('%',280,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
//    sprintf(sbuf,"%03d",A_sp4);
    LCDPutStr("000",240,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);  
    LCDPutChar('%',280,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
}




/*============================================================================*/
/*
 * Function      :        TFTView_Offset.
 * Description   :        Used to view all offsets.
 * Parameters    :        All offsets.
 * Return        :        None.
*/
/*============================================================================*/
void TFTView_Offset(int16_t B_ofst,int16_t B_hofst,int16_t B_tip, int16_t s_ofst, int16_t h_ofst)
{ 
    char sbuf[10];
    
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    LCDPutStr("PARAMETER",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);
    LCDPutStr("OFFSET VALUE",190,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
    LCDPutStr("BOOM OFFSET      :",10,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("BOOM HEAD OFFSET :",10,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("BOOM TIP OFFSET  :",10,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("SLEW OFFSET      :",10,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("BM HIEGHT OFFSET :",10,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
    color_lcd_draw_rectangle(ILI9341_WHITE,195,50,305,80);
    color_lcd_draw_rectangle(ILI9341_WHITE,195,85,305,115);
    color_lcd_draw_rectangle(ILI9341_WHITE,195,120,305,150);
    color_lcd_draw_rectangle(ILI9341_WHITE,195,155,305,185);
    color_lcd_draw_rectangle(ILI9341_WHITE,195,190,305,220);

    sprintf(sbuf,"%05.1f M",((float)B_ofst)/10.0);
    LCDPutStr(sbuf,205,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%05.1f M",((float)B_hofst)/10.0);
    LCDPutStr(sbuf,205,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%05.1f M",((float)B_tip)/10.0);
    LCDPutStr(sbuf,205,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%05.1f M",((float)s_ofst)/10.0);
    LCDPutStr(sbuf,205,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%05.1f M",((float)h_ofst)/10.0);
    LCDPutStr(sbuf,205,197,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
}



/*============================================================================*/
/*
 * Function      :        TFTError_Count.
 * Description   :        Used to view low and high error counts limits.
 * Parameters    :        All Low_er_cnt and High_er_cnt.
 * Return        :        None.
*/
/*============================================================================*/
void TFTError_Count(uint16_t Low_er_cnt, uint16_t High_er_cnt)
{
    char sbuf[10];
    uint8_t slen;
    
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    slen = strlen("ERROR COUNTS")*13;
    slen = ((320-slen)/2);
    LCDPutStr("ERROR COUNTS",slen,17,XLARGE,ILI9341_WHITE,ILI9341_BLACK);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
    LCDPutStr("LOW ERROR COUNTS  :",15,85,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("HIGH ERROR COUNTS :",15,145,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);   
    
    color_lcd_draw_rectangle( ILI9341_WHITE,195,77,310,115);
    color_lcd_draw_rectangle( ILI9341_WHITE,195,137,310,175);

    sprintf(sbuf,"%05d",Low_er_cnt);
    LCDPutStr(sbuf,205,90,XLARGE,ILI9341_BLACK, ILI9341_WHITE );

    sprintf( sbuf,"%05d",High_er_cnt); 
    LCDPutStr(sbuf,205,150,XLARGE,ILI9341_BLACK, ILI9341_WHITE );  
}




/*============================================================================*/
/*
 * Function      :        TFTRelay_Status.
 * Description   :        Used to view low and high error counts limits.
 * Parameters    :        Relay_1 to Relay_3 and buzzer status.
 * Return        :        None.
*/
/*============================================================================*/
void TFTRelay_Status(uint8_t Relay_1,uint8_t Relay_2,uint8_t Relay_3,uint8_t Buzzer)
{
    uint8_t slen;
    
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    slen = strlen("RELAY STATUS")*13;
    slen = ((320-slen)/2);
    LCDPutStr("RELAY STATUS",slen,17,XLARGE,ILI9341_WHITE,ILI9341_BLACK); 
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
    LCDPutStr("RELAY1 :",60,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("RELAY2 :",60,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("RELAY3 :",60,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("BUZZER :",60,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
    color_lcd_draw_rectangle(ILI9341_WHITE,135,50,250,80);
    color_lcd_draw_rectangle(ILI9341_WHITE,135,85,250,115);
    color_lcd_draw_rectangle(ILI9341_WHITE,135,120,250,150);
    color_lcd_draw_rectangle(ILI9341_WHITE,135,155,250,185);
    
    if(Relay_1 == 0)      LCDPutStr("ENABLE",145,57,XLARGE,ILI9341_GREEN,ILI9341_WHITE);
    else if(Relay_1 == 1) LCDPutStr("DISABLE",145,57,XLARGE,ILI9341_RED,ILI9341_WHITE);
    
    if(Relay_2 == 0)      LCDPutStr("ENABLE",145,92,XLARGE,ILI9341_GREEN,ILI9341_WHITE);
    else if(Relay_2 == 1) LCDPutStr("DISABLE",145,92,XLARGE,ILI9341_RED,ILI9341_WHITE);
    
    if(Relay_3 == 0)      LCDPutStr("ENABLE",145,127,XLARGE,ILI9341_GREEN,ILI9341_WHITE);
    else if(Relay_2 == 1) LCDPutStr("DISABLE",145,127,XLARGE,ILI9341_RED,ILI9341_WHITE);
    
    if(Buzzer == 0)       LCDPutStr("ENABLE",145,162,XLARGE,ILI9341_GREEN,ILI9341_WHITE);
    else if(Buzzer == 1)  LCDPutStr("DISABLE",145,162,XLARGE,ILI9341_RED,ILI9341_WHITE);
}


/*============================================================================*/
/*
 * Function      :        Crane_Details_Operator_View
 * Description   :        Used to view Crane details.
 * Parameters    :        min and max values.
 * Return        :        None.
*///26/04/23 v1.16 operator  view crane details   RRP
/*============================================================================*/
void Crane_Details_Operator_View(char *crane_model_buf,char *crane_make_buf,char *crane_type_buf,char *so_no_buf,char *inst_date_buf)
{
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    LCDPutStr("CRANE DETAILS",90,20,XLARGE,ILI9341_WHITE,ILI9341_BLACK);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,45,314,230);
   // LCDPutStr("CRANE DETAILS",81,70,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("MODEL  :",10,81,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("MAKE   :",10,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("TYPE   :",10,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("SO NO  :",10,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("INST DT:",10,180,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    
    LCDPutStr(crane_model_buf,110,81,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(crane_make_buf,110,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(crane_type_buf,110,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(so_no_buf,110,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(inst_date_buf,110,180,XLARGE, ILI9341_WHITE, ILI9341_NAVY);    
}

/*============================================================================*/
/*
 * Function      :        TFTOperator_View_CraneDimensions.
 * Description   :        Used to view Crane details.
 * Parameters    :        min and max values.
 * Return        :        None.
*///26/04/23 v1.16 operator  view crane dimensions   RRP
/*============================================================================*/
void TFTOperator_View_CraneDimensions(uint8_t cnt)                              //V1.17.1
{
    char obuf[20], sbuf[50],dbuf[50];
    uint16_t slen;
    
    if(cnt == 0)
    {  
        color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
        LCDPutStr("CRANE DIMENSIONS",70,20,XLARGE,ILI9341_WHITE,ILI9341_BLACK);   
        color_lcd_draw_rectangle(ILI9341_NAVY,5,45,314,230);       
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
    }  
    else
    {
        color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);                   //V1.17.1
        LCDPutStr("CRANE DIMENSIONS",70,20,XLARGE,ILI9341_WHITE,ILI9341_BLACK); 
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
        
    }    
    
}
/*============================================================================*/
/*
 * Function      :        TFTView_Hook_Calibration.
 * Description   :        Used to view hook calibration values.
 * Parameters    :        min and max values.
 * Return        :        None.
*/
/*============================================================================*/
void TFTView_Hook_Calibration(uint16_t M_min_val,uint16_t M_min_cnt,uint16_t M_max_val,uint16_t M_max_cnt,uint16_t A_min_val,uint16_t A_min_cnt,uint16_t A_max_val,uint16_t A_max_cnt)
{
    char sbuf[10];
    
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    LCDPutStr(" LOAD VALUE",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);
    LCDPutStr(" MAIN HOOK    AUX HOOK",110,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK);

    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);    
    LCDPutStr("MIN VALUE:",10,77,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("MIN COUNT:",10,112,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("MAX VALUE:",10,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("MAX COUNT:",10,182,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    color_lcd_draw_rectangle(ILI9341_WHITE,110,70,200,100);
    color_lcd_draw_rectangle(ILI9341_WHITE,110,105,200,135);
    color_lcd_draw_rectangle(ILI9341_WHITE,110,140,200,170);
    color_lcd_draw_rectangle(ILI9341_WHITE,110,175,200,205);

    color_lcd_draw_rectangle(ILI9341_WHITE,215,70,305,100);
    color_lcd_draw_rectangle(ILI9341_WHITE,215,105,305,135);
    color_lcd_draw_rectangle(ILI9341_WHITE,215,140,305,170);
    color_lcd_draw_rectangle(ILI9341_WHITE,215,175,305,205);

    sprintf(sbuf,"%04.1f T",((float)M_min_val)/10.0);
    LCDPutStr(sbuf,115,77,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%05d",M_min_cnt);
    LCDPutStr(sbuf,115,112,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%04.1f T",((float)M_max_val)/10.0);
    LCDPutStr(sbuf,115,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf( sbuf,"%05d",M_max_cnt);
    LCDPutStr(sbuf,115,182,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04.1f T",((float)A_min_val)/10.0);
    LCDPutStr(sbuf,220,77,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%05d",A_min_cnt);
    LCDPutStr(sbuf,220,112,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%04.1f T",((float)A_max_val)/10.0);
    LCDPutStr(sbuf,220,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%05d",A_max_cnt);
    LCDPutStr(sbuf,220,182,XLARGE,ILI9341_BLACK,ILI9341_WHITE);       
}


/*============================================================================*/
/*
 * Function      :        TFTView_Boom_Luff_Angle_Calibration.
 * Description   :        Used to view boom angle calibration values.
 * Parameters    :        min and max values.
 * Return        :        None.
*/
/*============================================================================*/
void TFTView_Boom_Luff_Angle_Calibration(uint16_t B_min_val,uint16_t B_min_cnt,uint16_t B_max_val,uint16_t B_max_cnt,uint16_t L_min_val,uint16_t L_min_cnt,uint16_t L_max_val,uint16_t L_max_cnt)
{
    char sbuf[10];
    
    color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
    LCDPutStr("ANGLE VALUE",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);
    LCDPutStr(" MAIN BOOM    AUX BOOM",110,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);    
    LCDPutStr("MIN VALUE:",10,77,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("MIN COUNT:",10,112,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("MAX VALUE:",10,147,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    LCDPutStr("MAX COUNT:",10,182,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);

    color_lcd_draw_rectangle(ILI9341_WHITE,110,70,200,100);
    color_lcd_draw_rectangle(ILI9341_WHITE,110,105,200,135);
    color_lcd_draw_rectangle(ILI9341_WHITE,110,140,200,170);
    color_lcd_draw_rectangle(ILI9341_WHITE,110,175,200,205);

    color_lcd_draw_rectangle(ILI9341_WHITE,215,70,305,100);
    color_lcd_draw_rectangle(ILI9341_WHITE,215,105,305,135);
    color_lcd_draw_rectangle(ILI9341_WHITE,215,140,305,170);
    color_lcd_draw_rectangle(ILI9341_WHITE,215,175,305,205);
    
    sprintf(sbuf,"%04.1f",((float)B_min_val)/10.0);
    LCDPutStr(sbuf,115,77,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%04d",B_min_cnt);
    LCDPutStr(sbuf,115,112,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%04.1f",((float)B_max_val)/10.0);
    LCDPutStr(sbuf,115,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf( sbuf,"%04d",B_max_cnt);
    LCDPutStr(sbuf,115,182,XLARGE,ILI9341_BLACK,ILI9341_WHITE);

    sprintf(sbuf,"%04.1f",((float)L_min_val)/10.0);
    LCDPutStr(sbuf,220,77,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%04d",L_min_cnt);
    LCDPutStr(sbuf,220,112,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%04.1f",((float)L_max_val)/10.0);
    LCDPutStr(sbuf,220,147,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(sbuf,"%04d",L_max_cnt);
    LCDPutStr(sbuf,220,182,XLARGE,ILI9341_BLACK,ILI9341_WHITE); 
}

/*============================================================================*/
/*
 * Function      :        TFTDisplay_Operator_GPS Parameter.
 * Description   :        Used to display operator menu first page.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/

void view_gps_parameter()
{
        char sbuf[100];
        char lati=0,logi=0,time=0,date=0;
        int sr_no = 1;
        
       
        color_lcd_draw_rectangle(ILI9341_BLACK,10,17,300,34);
        LCDPutStr("GPS PARAMETER",10,20,SMALL,ILI9341_WHITE,ILI9341_BLACK);
        LCDPutStr("SR No",150,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
        LCDPutStr("GPS READING",210,17,MEDIUM,ILI9341_WHITE,ILI9341_BLACK); 
        
        color_lcd_draw_rectangle(ILI9341_NAVY,5,50,310,230);
        LCDPutStr("LATITUDE:",15,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("LONGITUDE:",15,92,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("GPS DATE:",15,127,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("GPS TIME:",15,162,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
        LCDPutStr("          ",15,197,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    
        color_lcd_draw_rectangle(ILI9341_WHITE,140,50,190,80);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,85,190,115);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,120,190,150);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,155,190,185);
        color_lcd_draw_rectangle(ILI9341_WHITE,140,190,190,220);
    
        color_lcd_draw_rectangle(ILI9341_WHITE,195,50,310,80);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,85,310,115);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,120,310,150);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,155,310,185);
        color_lcd_draw_rectangle(ILI9341_WHITE,195,190,310,220); 
        
         sprintf(sbuf,"%03d",sr_no);
         LCDPutStr(sbuf,145,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
         sprintf(sbuf,"%03d",++sr_no);
         LCDPutStr(sbuf,145,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
         sprintf(sbuf,"%03d",++sr_no);
         LCDPutStr(sbuf,145,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
         sprintf(sbuf,"%03d",++sr_no);
         LCDPutStr(sbuf,145,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
         
         sprintf(sbuf,"%05d",lati);
         LCDPutStr(sbuf,205,57,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
         sprintf(sbuf,"%05d",logi);
         LCDPutStr(sbuf,205,92,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
         sprintf(sbuf,"%05d",date);
         LCDPutStr(sbuf,205,127,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
         sprintf(sbuf,"%05d",time);
         LCDPutStr(sbuf,205,162,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
         
         
    
}


/*============================================================================*/
/*
 * Function      :        TFTDisplay_Operator_Setcode_Menu.
 * Description   :        Used to display operator menu first page.
 * Parameters    :        page-Page number.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Operator_Setcode_Menu(uint8_t page)
{
    uint8_t rcnt;
    
    mv.max = 5;
    mv.min = 1;
    
    Set_Codes_Menu_Outlines();
    
    TFTOperator_Setcode_Pages(page);
    
    rcnt = mv.operator_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(0,rcnt);
}


/*============================================================================*/
/*
 * Function      :        TFTSelect_Operator_Setcode_Menu.
 * Description   :        Used to highlight operator menu pages.
 * Parameters    :        sel-highlight row number(1 to 5).
 * Return        :        None.
*/
/*============================================================================*/
void TFTSelect_Operator_Setcode_Menu(uint8_t sel)
{
    uint8_t rcnt;
    
    rcnt = mv.operator_set%5;
    if(rcnt == 0) rcnt = 5;
    
    Highlight_Single_Row(sel,rcnt);
    
//    if(((mv.operator_set == 1)&&(sel == 1))||((mv.operator_set == 5)&&(sel == 0)))        TFTOperator_Setcode_Pages(0);
//    else if(((mv.operator_set == 6)&&(sel == 1))||((mv.operator_set == 10)&&(sel == 0)))  TFTOperator_Setcode_Pages(1);
//    else if(((mv.operator_set == 11)&&(sel == 1))||((mv.operator_set == 15)&&(sel == 0))) TFTOperator_Setcode_Pages(2);
}


/*============================================================================*/
/*
 * Function      : TFTDuty_Hint.
 * Description   : Used to select duty hint.
 * Parameters    : Duty_no- Duty number to select duty hint.
 * Return        : None.
*/
/*============================================================================*/
void TFTDuty_Hint(uint16_t Duty_no)
{
	uint16_t TempCount,TempCount1;
    char Line_1[20],Line_2[20],lbuf[50];
    
    sprintf(lbuf,"%03d",Duty_no);
    LCDPutStr(lbuf,130,110,XLARGE,ILI9341_BLACK, ILI9341_WHITE);

    flash_page_addr = ((uint32_t)lc_duty_hint_page_s-1)*256 + (((uint32_t)Duty_no-1)*32) + flash_memory_offset;

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
    memset(lbuf,0,sizeof(lbuf));
    sprintf(lbuf,"%s%s",Line_1,Line_2);
    memset(Line_1,0,sizeof(Line_1));
    memset(Line_2,0,sizeof(Line_2));
    memcpy(Line_1,lbuf,16);
    memcpy(Line_2,lbuf+16,16);
    
    color_lcd_draw_rectangle(ILI9341_WHITE,50,170,270,210);
    LCDPutStr(Line_1,56,170,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
    LCDPutStr(Line_2,56,190,XLARGE,ILI9341_BLACK, ILI9341_WHITE);
}


/*============================================================================*/
/*
 * Function      :        TFTDisplay_Operator_Settings.
 * Description   :        Used to display operator setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTDisplay_Operator_Settings(void)
{
    char obuf[10],slen;
    
    sprintf(obuf,"%03d",mv.operator_set+50);
    LCDPutStr(obuf,18,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
    color_lcd_draw_rectangle(ILI9341_WHITE,281,51,309,79);
    LCDPutStr(">>",285,57,XLARGE,ILI9341_NAVY,ILI9341_WHITE);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
    
    switch(mv.operator_set)
    {
        case SET_DUTY:
        {
            LCDPutStr("SET DUTY            ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            prv16_val1 = sys.para.duty;
            LCDPutStr("DUTY NUMBER:",15,105,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            LCDPutStr("HINT:",15,140,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            color_lcd_draw_rectangle(ILI9341_WHITE,125,100,170,132);
            color_lcd_draw_rectangle(ILI9341_WHITE,10,165,310,210);
            
            TFTDuty_Hint(prv16_val1);
            break; 
        }
        case SET_FALLS:
        {
            LCDPutStr("SET MAIN HOOK FALLS ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
            
            prv8_val1 = (uint8_t)sys.para.falls_cnt;
            sprintf(obuf,"%02d",prv8_val1);
            slen = strlen(obuf)*13;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8;  
            pos_t = 0;
            valX = cursX;
            valY = cursY;
            LCDPutStr(obuf,valX,valY,XLARGE,ILI9341_BLACK,ILI9341_WHITE);      //217,112
            LCDPutStr(obuf,valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            
            common_byte = 2;
            common_long = prv8_val1;    
            
            cursX += (common_byte-1)*13;
            cursY += 19;
            TFT_Draw_Cursor(pos_t,ILI9341_WHITE,ILI9341_RED);
            break;
        }
        case SET_UOM:
        {
            LCDPutStr("SET UOM             ",75,57,MEDIUM,ILI9341_WHITE,ILI9341_NAVY);
            
            prv8_val1 = sys.para.sel_uom;
            
            Current_Prev_Val_Screen(1, ILI9341_WHITE, ILI9341_NAVY);
            
            slen = strlen("Tn & M")*12;
            cursX = 180+((100-slen)/2);
            cursY = 100+20-8;
            valX = cursX;
            valY = cursY;
            
            TFTShow_Load_UOM();
            
            if(prv8_val1)
                LCDPutStr("Tn & M",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            else
                LCDPutStr("Kp & F",valX,165+20-8,XLARGE,ILI9341_BLACK,ILI9341_WHITE);
            break;
        }
    }    
}

/*============================================================================*/
/*
 * Function      :        TFT_Modify_Operator_Settings.
 * Description   :        Used to modify operator setcode menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Modify_Operator_Settings(void)
{
    switch(mv.operator_set)
    {
        case SET_DUTY:
        {
            TFT_Choose_Duty();
            break; 
        }
        case SET_FALLS:
        {
            TFT_Change_Main_Falls();
            break;
        }
        case SET_UOM:
        {
            TFT_Set_Load_UOM();
            break;
        }
    }    
}


/*============================================================================*/
/*
 * Function      :        TFTCommon_Opertr_Escape_Function.
 * Description   :        Used to take escape from operator menu.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFTCommon_Opertr_Escape_Function(void)
{
    if((mv.operator_set >= 1)&&(mv.operator_set <= 5))        TFTDisplay_Operator_Setcode_Menu(0);
    else if((mv.operator_set >= 6)&&(mv.operator_set <= 10))  TFTDisplay_Operator_Setcode_Menu(1);
    else if((mv.operator_set >= 11)&&(mv.operator_set <= 15)) TFTDisplay_Operator_Setcode_Menu(2);
}

/*============================================================================*/
/*
 * Function      :        TFT_Choose_Duty.
 * Description   :        Used to select working duty.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Choose_Duty(void)
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
                    prv16_val1++;
                    if(prv16_val1 > lc_total_duty)  prv16_val1 = 1;     
                    
                    TFTDuty_Hint(prv16_val1);
                    Delay_1ms(500);
                }
            }
            else
            {
                while(key.dec_ftp == 1)
                {
                    prv16_val1--;
                    if(prv16_val1 < 1)  prv16_val1 = lc_total_duty;     
                    
                    TFTDuty_Hint(prv16_val1);
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
            
            sys.para.duty = prv16_val1;
//            sys.para.curr_len_indx = 1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Opertr_Escape_Function();
            
            menu_stat = OPERATOR_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Opertr_Escape_Function();
            
            menu_stat = OPERATOR_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}


/*============================================================================*/
/*
 * Function      :        TFT_Change_Main_Falls.
 * Description   :        Used to change main falls settings.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Change_Main_Falls(void)
{
    while(1)
    {
        if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Opertr_Escape_Function();
            
            menu_stat = OPERATOR_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.falls_cnt = (uint8_t)common_long;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Opertr_Escape_Function();
            
            menu_stat = OPERATOR_SET_CODE_PAGE;
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
 * Function      :        TFT_Set_Load_UOM.
 * Description   :        Used to change unit of measurement of load.
 * Parameters    :        None.
 * Return        :        None.
*/
/*============================================================================*/
void TFT_Set_Load_UOM(void)
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

            TFTShow_Load_UOM();

            key.increment = 0;
            key.decrement = 0;
        }
        else if(key.enter == 1)        // ENTR Key
        {
            color_lcd_draw_rectangle(ILI9341_NAVY,5,85,310,220);    //Clear Setting page
            
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            
            sys.para.sel_uom = prv8_val1;
            
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
            
            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            LCDPutStr("DATA SAVED",100,127,XLARGE,ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(1500);
            
            TFTCommon_Opertr_Escape_Function();
            
            menu_stat = OPERATOR_SET_CODE_PAGE;
            key.enter = 0;
            break;
        }
        else if((key.function == 1)||(key.func_ftp == 1))        // FUNC Key
        {
            TFTCommon_Opertr_Escape_Function();
            
            menu_stat = OPERATOR_SET_CODE_PAGE;
            key.function = 0;
            Delay_1ms(500);
            break;
        }
    }
}
//=================================EOF==========================================

