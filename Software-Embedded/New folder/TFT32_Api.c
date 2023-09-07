
#include "main.h"

//const uint16_t


void system_initialization(void)
{
     int i;
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,5,314,232);
    LCDPutStr("SYSTEM INITIALIZING",27,70, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    for(i=0;i<2;i++){
    //LCDPutStr("PLEASE WAIT",34,100, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    //Delay_1ms(500);
    LCDPutStr("PLEASE WAIT.",34,100, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    Delay_1ms(500);
    LCDPutStr("PLEASE WAIT..",34,100, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    Delay_1ms(500);
    LCDPutStr("PLEASE WAIT...",34,100, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    Delay_1ms(500);
    color_lcd_draw_rectangle(ILI9341_NAVY,164,85,310,220);}  
    
}

void Main_Welcome_Screen(void)
{
    int len=0;
    
     len=strlen(crane_make);
    
    color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,232);
    
    if(memcmp(crane_make,"ESCORTS",len)==0)                        //V1.17.1
    {    
       Display_EscortsLogo_Image(5,49);
       Delay_1ms(2000);
    }
    else if(memcmp(crane_make,"ACE",len)==0)                      //V1.17.1
    {
         Display_ACELogo_Image(5,75);
         Delay_1ms(2000);
    }    
    else
    {
      Display_KAMPLOGO_Image(5,5);
      Delay_1ms(2000); 
    }     
    
    color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,45);
    draw_hollow_rect(ILI9341_BLACK,5,5,315,35);
    draw_hollow_rect(ILI9341_BLACK,6,6,314,34);
    LCDPutStr("SAFE LOAD INDICATOR",50,12,XLARGE,ILI9341_RED,ILI9341_WHITE);
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,45,314,232);
    LCDPutStr("KLUG AVALON",93,76, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("MECHATRONICS PVT. LTD.",27,100, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    Delay_1ms(2000); 
}

void Software_Details(char *soft_ver_buf,char *csv_ver_buf,char *csv_name_buf,char *date_buf)
{
    char siz,l1buf[20],l2buf[20];
    
    color_lcd_draw_rectangle(ILI9341_NAVY,5,45,314,230);
    LCDPutStr("SOFTWARE DETAILS",63,70,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("S/W Ver:",10,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);//25
    LCDPutStr("CSV ID :",10,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("CSV DT :",10,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("CSV NAME:",10,180,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    
    LCDPutStr(soft_ver_buf,110,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(csv_ver_buf,110,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(date_buf,110,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    
    siz = strlen(csv_name_buf);
    if(siz < 16)
    {
        LCDPutStr(csv_name_buf,125,180,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    }
    else
    {
        memset(l1buf,0,sizeof(l1buf));
        memset(l2buf,0,sizeof(l2buf));
        memcpy(l1buf,csv_name_buf,15);
        strcpy(l2buf,csv_name_buf+15);
        LCDPutStr(l1buf,125,180,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
        LCDPutStr(l2buf,100,204,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    }
}

void Crane_Details(char *crane_model_buf,char *crane_make_buf,char *crane_type_buf,char *so_no_buf,char *inst_date_buf)
{
    color_lcd_draw_rectangle(ILI9341_NAVY,5,45,314,230);
    LCDPutStr("CRANE DETAILS",81,70,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("MODEL  :",10,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("MAKE   :",10,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("TYPE   :",10,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("SO NO  :",10,180,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr("INST DT:",10,205,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    
    LCDPutStr(crane_model_buf,110,105,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(crane_make_buf,110,130,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(crane_type_buf,110,155,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(so_no_buf,110,180,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
    LCDPutStr(inst_date_buf,110,205,XLARGE, ILI9341_WHITE, ILI9341_NAVY);    
}


void System_Setup_Screen(void)
{
    color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
    Display_KAMP_QRCode_Image(59,19);
    Delay_1ms(2000);
    color_lcd_draw_rectangle(ILI9341_WHITE,59,19,259,220);
    color_lcd_draw_rectangle(ILI9341_NAVY,6,45,313,195);
    color_lcd_draw_rectangle(ILI9341_WHITE,30,75,295,115);
    LCDPutStr("SYSTEM SETUP",95,90,XLARGE,ILI9341_NAVY, ILI9341_WHITE );
    color_lcd_draw_rectangle( ILI9341_WHITE,30,135,165,175);
    LCDPutStr("ESC:QUIT",50,150,XLARGE,ILI9341_NAVY, ILI9341_WHITE );
    color_lcd_draw_rectangle( ILI9341_WHITE,175,135,295,175);
    LCDPutStr("ENT:SEL",195,150,XLARGE,ILI9341_NAVY, ILI9341_WHITE );
}

void Initial_SPI_Test_Screen(uint8_t sel, uint8_t flag)
{
    if(sel == 1)
    {
        if(flag == 0)
            LCDPutStr("SPI FLASH1 TEST PASSED",27,170,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
        else
        {
            LCDPutStr("SPI FLASH1 TEST FAILED",27,170,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr("PLEASE CHECK SPI FLASH IC",9,195,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
        }
    }
    else
    {
        if(flag == 0)
            LCDPutStr("SPI FLASH2 TEST PASSED",27,170,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
        else
        {
            LCDPutStr("SPI FLASH2 TEST FAILED",27,170,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr("PLEASE CHECK SPI FLASH IC",9,195,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
        }
    }    
}


void TFT32_Crane_Image(uint16_t x, uint16_t y, uint16_t height, uint16_t width)
{
    uint16_t i,j;   //,index=0
    
    Address_set(x,y,x+width-1,y+height-1);
    
    for(i = 0; i < height; i++) 
    {
        for(j = 0; j < width; j++)
        {
//            if(sys.para.Select_System == FORK_LIFT)
//                TFT32_Write_Data16(image_data_Forklift_170x150[index++]);
//            else
//                TFT32_Write_Data16(image_data_PNC_130x210[index++]);
        }
    }
}

void Default_Main_Screen_Outline(void)
{
//    color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
    draw_hollow_rect(ILI9341_BLUE,0,0,319,239);
    draw_hollow_rect(ILI9341_BLUE,1,1,318,238);
    draw_hollow_rect(ILI9341_BLACK,2,2,317,237);
    draw_hollow_rect(ILI9341_BLACK,3,3,316,236);
    draw_hollow_rect(ILI9341_BLACK,4,4,315,235);
}

void Default_Main_Screen_PNC(uint8_t sel,uint16_t dty,uint16_t mlen,uint16_t jlen,int16_t mang,int16_t jang,uint16_t rad,uint16_t aload,uint16_t mload,uint16_t swl, uint16_t wind)
{
    char lbuf[10];
//    float tval;
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
        
//        TFT32_Crane_Image(45,25,210,130);
        Display_Default_PNC_Image(48,25);
        
        draw_hollow_rect(ILI9341_BROWN,8,9,110,31);
        draw_hollow_rect(ILI9341_BROWN,9,10,109,30);
        LCDSetLine(62,11,62,29,ILI9341_BROWN);
        LCDSetLine(63,11,63,29,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,64,11,108,29);//DUTY
        LCDPutStr("DUTY",13,13, XLARGE, ILI9341_BLACK , ILI9341_WHITE);
        if((dty >= 1)&&(dty <= 999))
        {
            sprintf(lbuf,"%03d",dty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        if(sys.para.Select_System == ACE_NX360)
        {
            draw_hollow_rect(ILI9341_BROWN,115,8,193,24);
            color_lcd_draw_rectangle(ILI9341_NAVY,116,9,192,23);
            if(SlewMode == 0)
                LCDPutStr("PNC MODE",128,12,SMALL,ILI9341_MAGENTA, ILI9341_NAVY);
            else
                LCDPutStr("TEL MODE",128,12,SMALL,ILI9341_MAGENTA, ILI9341_NAVY);
        }
           
        draw_hollow_rect(ILI9341_BROWN,198,9,310,31);
        draw_hollow_rect(ILI9341_BROWN,199,10,309,30);
        LCDSetLine(242,11,242,29,ILI9341_BROWN);
        LCDSetLine(243,11,243,29,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY, 244,11,308,29);//swl
        LCDPutStr("SWL",203,13, XLARGE,ILI9341_RED , ILI9341_WHITE);
        if((swl >= 0)&&(swl <= 999))
        {
            sprintf(lbuf,"%04.1fT",((float)swl)/10.0);
            LCDPutStr(lbuf,247,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(swl <= 9999)
        {
            sprintf(lbuf," %03dT",swl/10);
            LCDPutStr(lbuf,247,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        draw_hollow_rect(ILI9341_BROWN,198,38,310,60);
        draw_hollow_rect(ILI9341_BROWN,199,39,309,59);
        LCDSetLine(264,40,264,58,ILI9341_BROWN);
        LCDSetLine(265,40,265,58,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY, 266,40,308,58);//Falls
        LCDPutStr("Falls",203,43, XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(lbuf,"%02d",sys.para.falls_cnt);
        LCDPutStr(lbuf,275,43, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
        
//        draw_hollow_rect(ILI9341_BLUE,8,38,112,86);
//        draw_hollow_rect(ILI9341_BLUE,9,39,111,85);
//        color_lcd_draw_rectangle(ILI9341_NAVY,8,62,112,86);
//        LCDPutStr("Wind",40,44,XLARGE, ILI9341_BLACK , ILI9341_WHITE);
//        
//        if(sys.para.sel_uom_wspd)
//        {
//            tval = (float)wind*3.6;
//            if((tval >= 0)&&(tval <= 999))
//            {
//                sprintf(lbuf,"%04.1fkm/h",tval/10.0);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
//            }
//            else if(tval <= 9999)
//            {
//                tval = tval/10;
//                sprintf(lbuf,"%04dkm/h",(uint16_t)tval);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
//            }
//        }
//        else
//        {
//            if((wind >= 0)&&(wind <= 999))
//            {
//                sprintf(lbuf,"%04.1f m/s",((float)wind)/10.0);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
//            }
//            else if(wind <= 9999)
//            {
//                sprintf(lbuf,"%04d m/s",wind/10);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY); 
//            }
//        }
        
        draw_hollow_rect(ILI9341_BROWN,7,91,87,139);
        draw_hollow_rect(ILI9341_BROWN,8,92,86,138);
        LCDSetLine(9,113,85,113,ILI9341_BROWN);
        LCDSetLine(9,114,85,114,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,9,115,85,137);//LENGTH
        LCDPutStr("Length",12,95,XLARGE, ILI9341_BLACK , ILI9341_WHITE);
        if((mlen >= 0)&&(mlen <= 999))
        {
            sprintf(lbuf,"%04.1fM",((float)mlen)/10.0);
            LCDPutStr(lbuf,15,121, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(mlen <= 9999)
        {
            sprintf(lbuf,"%04dM",mlen/10);
            LCDPutStr(lbuf,15,121, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        draw_hollow_rect(ILI9341_BROWN,215,91,312,150);
        draw_hollow_rect(ILI9341_BROWN,216,92,311,149);
        LCDSetLine(217,113,310,113,ILI9341_BROWN);
        LCDSetLine(217,114,310,114,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,217,115,310,148);
        LCDPutStr("Load",240,96,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
        if((mload >= 0)&&(mload <= 999))
        {
            sprintf(lbuf,"%04.1f",((float)mload)/10.0);
            LCDPutChar(lbuf[0],220,123, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[1],237,123, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[3],271,123, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDSetSolidCircle(262,141,2,ILI9341_WHITE);
        }
        else if(mload <= 9999)
        {
            sprintf(lbuf,"%04d",mload/10);
            LCDPutStr(lbuf,220,123, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
        }
        LCDPutChar('T',297,130, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        
        draw_hollow_rect(ILI9341_BROWN,154,176,312,199);
        draw_hollow_rect(ILI9341_BROWN,155,177,311,198);
        LCDSetLine(240,178,240,197,ILI9341_BROWN);
        LCDSetLine(241,178,241,197,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,242,178,310,197);//Angle
        LCDPutStr("Angle",160,179,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
        
        sprintf(lbuf,"%02d",mang/10);
        LCDPutStr(lbuf,266,181, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        
        Draw_Circle(300,181,2,ILI9341_WHITE);
        
        draw_hollow_rect(ILI9341_BROWN,154,205,312,228);
        draw_hollow_rect(ILI9341_BROWN,155,206,311,227);
        LCDSetLine(240,207,240,226,ILI9341_BROWN);
        LCDSetLine(241,207,241,226,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,242,207,310,226);//radius
        LCDPutStr("Radius",160,208,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
        if((rad >= 0)&&(rad <= 999))
        {
            sprintf(lbuf,"%04.1fM",((float)rad)/10.0);
            LCDPutStr(lbuf,246,210, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(rad <= 9999)
        {
            sprintf(lbuf,"%04dM",rad/10);
            LCDPutStr(lbuf,246,210, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }        
    }
    else
    {
        if((dty >= 1)&&(dty <= 999))
        {
            sprintf(lbuf,"%03d",dty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        if(sys.para.Select_System == ACE_NX360)
        {
            if(SlewMode == 0)
                LCDPutStr("PNC MODE",128,12,SMALL,ILI9341_MAGENTA, ILI9341_NAVY);
            else
                LCDPutStr("TEL MODE",128,12,SMALL,ILI9341_MAGENTA, ILI9341_NAVY);
        }
        
        if(tftprv_swl != swl)   color_lcd_draw_rectangle(ILI9341_NAVY, 247,13,308,29);
        if((swl >= 0)&&(swl <= 999))
        {            
            sprintf(lbuf,"%04.1fT",((float)swl)/10.0);
            LCDPutStr(lbuf,247,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(swl <= 9999)
        {
            sprintf(lbuf," %03dT",swl/10);
            LCDPutStr(lbuf,247,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        tftprv_swl = swl;
        
//        if(tftprv_wind != wind)   LCDPutStr("    ",10,67, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
//        
//        if(sys.para.sel_uom_wspd)
//        {
//            tval = (float)wind*3.6;
//            if((tval >= 0)&&(tval <= 999))
//            {
//                sprintf(lbuf,"%04.1fkm/h",tval/10.0);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
//            }
//            else if(tval <= 9999)
//            {
//                tval = tval/10;
//                sprintf(lbuf,"%04dkm/h",(uint16_t)tval);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
//            }
//        }
//        else
//        {
//            if((wind >= 0)&&(wind <= 999))
//            {
//                sprintf(lbuf,"%04.1f m/s",((float)wind)/10.0);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
//            }
//            else if(wind <= 9999)
//            {
//                sprintf(lbuf,"%04d m/s",wind/10);
//                LCDPutStr(lbuf,12,67, XLARGE, ILI9341_WHITE,ILI9341_NAVY); 
//            }
//        }
//        tftprv_wind = wind;
        
        if(tftprv_mlen != mlen)   color_lcd_draw_rectangle(ILI9341_NAVY,15,121,85,137);
        if((mlen >= 0)&&(mlen <= 999))
        {
            sprintf(lbuf,"%04.1fM",((float)mlen)/10.0);
            LCDPutStr(lbuf,15,121, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(mlen <= 9999)
        {
            sprintf(lbuf,"%04dM",mlen/10);
            LCDPutStr(lbuf,15,121, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        tftprv_mlen = mlen;
        
        if(tftprv_mload != mload)   color_lcd_draw_rectangle(ILI9341_NAVY,220,123,310,148);
        if((mload >= 0)&&(mload <= 999))
        {
            sprintf(lbuf,"%04.1f",((float)mload)/10.0);
            
            if(condition)
            {
                LCDPutChar(lbuf[0],220,123, ASCII_26x16,ILI9341_RED,ILI9341_NAVY);
                LCDPutChar(lbuf[1],237,123, ASCII_26x16,ILI9341_RED,ILI9341_NAVY);
                LCDPutChar(lbuf[3],271,123, ASCII_26x16,ILI9341_RED,ILI9341_NAVY);
                LCDSetSolidCircle(262,141,2,ILI9341_RED);
            }
            else
            {
                LCDPutChar(lbuf[0],220,123, ASCII_26x16,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutChar(lbuf[1],237,123, ASCII_26x16,ILI9341_WHITE,ILI9341_NAVY);
                LCDPutChar(lbuf[3],271,123, ASCII_26x16,ILI9341_WHITE,ILI9341_NAVY);
                LCDSetSolidCircle(262,141,2,ILI9341_WHITE);
            }
        }
        else if(mload <= 9999)
        {
            sprintf(lbuf,"%04d",mload/10);
            if(condition)
                LCDPutStr(lbuf,220,123, ASCII_26x16,ILI9341_RED,ILI9341_NAVY);
            else
                LCDPutStr(lbuf,220,123, ASCII_26x16,ILI9341_WHITE,ILI9341_NAVY);
        }
        LCDPutChar('T',297,130, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        tftprv_mload = mload;
        
        if(tftprv_mang != mang/10)   color_lcd_draw_rectangle(ILI9341_NAVY,266,181,310,197);
        
        sprintf(lbuf,"%02d",mang/10);
        LCDPutStr(lbuf,266,181, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        Draw_Circle(300,181,2,ILI9341_WHITE);
        tftprv_mang = mang/10;
        
        if(tftprv_rad != rad)   color_lcd_draw_rectangle(ILI9341_NAVY,246,210,310,226);
        if((rad >= 0)&&(rad <= 999))
        {
            sprintf(lbuf,"%04.1fM",((float)rad)/10.0);
            LCDPutStr(lbuf,246,210, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(rad <= 9999)
        {
            sprintf(lbuf,"%04dM",rad/10);
            LCDPutStr(lbuf,246,210, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        tftprv_rad = rad;
    }    
}

void Default_Main_Screen_ForkLift(uint8_t sel, uint8_t dty, uint16_t load, uint16_t capa, uint16_t height)
{
    char lbuf[10];
    
    if(sel == 0)
    {
        draw_hollow_rect(ILI9341_BLACK,5,5,315,35);
        draw_hollow_rect(ILI9341_BLACK,6,6,314,34);
        LCDPutStr("SAFE LOAD INDICATOR",50,12,XLARGE,ILI9341_RED,ILI9341_WHITE);
        
        color_lcd_draw_rectangle(ILI9341_WHITE,5,45,314,230);
        
//        TFT32_Crane_Image(20,80,150,170);
        Display_Forklift_Image(20,80);
        
        draw_hollow_rect(ILI9341_BLUE,15,50,172,72);
        draw_hollow_rect(ILI9341_BLUE,16,51,171,71);
        color_lcd_draw_rectangle(ILI9341_NAVY,102,51,172,72);
        LCDPutStr("Height",20,54,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
        if((height >= 0)&&(height <= 999))
        {
            sprintf(lbuf,"%04.1fM",((float)height)/10.0);
            LCDPutStr(lbuf,106,55, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(height <= 9999)
        {
            sprintf(lbuf,"%04dM",height/10);
            LCDPutStr(lbuf,106,55, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        draw_hollow_rect(ILI9341_BLUE,190,50,297,72);
        draw_hollow_rect(ILI9341_BLUE,191,51,296,71);
        color_lcd_draw_rectangle(ILI9341_NAVY,247,51,297,72);
        LCDPutStr("Duty",195,54,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
        if((dty >= 1)&&(dty <= 99))
        {
            sprintf(lbuf,"%02d",dty);
            LCDPutStr(lbuf,259,55, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        draw_hollow_rect(ILI9341_BLUE,195,81,295,140);
        draw_hollow_rect(ILI9341_BLUE,196,82,294,139);
        color_lcd_draw_rectangle(ILI9341_NAVY,196,105,295,140);
        LCDPutStr("Capacity",198,86,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
        if((capa >= 0)&&(capa <= 999))
        {
            sprintf(lbuf,"%04.1f",((float)capa)/10.0);
            LCDPutChar(lbuf[0],200,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[1],217,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[3],251,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDSetSolidCircle(242,131,2,ILI9341_WHITE);
        }
        else if(capa <= 9999)
        {
            sprintf(lbuf,"%04d",capa/10);
            LCDPutStr(lbuf,200,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
        }
        LCDPutChar('T',277,120, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        
        draw_hollow_rect(ILI9341_BLUE,195,151,295,210);
        draw_hollow_rect(ILI9341_BLUE,196,152,294,209);
        color_lcd_draw_rectangle(ILI9341_NAVY,196,175,295,210);
        LCDPutStr("Load",220,158,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
        if((load >= 0)&&(load <= 999))
        {
            sprintf(lbuf,"%04.1f",((float)load)/10.0);
            LCDPutChar(lbuf[0],200,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[1],217,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[3],251,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDSetSolidCircle(242,201,2,ILI9341_WHITE);
        }
        else if(load <= 9999)
        {
            sprintf(lbuf,"%04d",load/10);
            LCDPutStr(lbuf,200,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
        }
        LCDPutChar('T',277,190, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
    }
    else
    {
        if(tftprv_mlen != height)   LCDPutStr("     ",106,55, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
        if((height >= 0)&&(height <= 999))
        {
            sprintf(lbuf,"%04.1fM",((float)height)/10.0);
            LCDPutStr(lbuf,106,55, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(height <= 9999)
        {
            sprintf(lbuf,"%04dM",height/10);
            LCDPutStr(lbuf,106,55, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        tftprv_mlen = height;
        
        if(tftprv_swl != capa)   LCDPutStr("    ",200,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
        if((capa >= 0)&&(capa <= 999))
        {
            sprintf(lbuf,"%04.1f",((float)capa)/10.0);
            LCDPutChar(lbuf[0],200,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[1],217,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[3],251,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDSetSolidCircle(242,131,2,ILI9341_WHITE);
        }
        else if(capa <= 9999)
        {
            sprintf(lbuf,"%04d",capa/10);
            LCDPutStr(lbuf,200,113, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
        }
        tftprv_swl = capa;
        
        if(tftprv_mload != load)   LCDPutStr("    ",200,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
        if((load >= 0)&&(load <= 999))
        {
            sprintf(lbuf,"%04.1f",((float)load)/10.0);
            LCDPutChar(lbuf[0],200,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[1],217,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDPutChar(lbuf[3],251,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
            LCDSetSolidCircle(242,201,2,ILI9341_WHITE);
        }
        else if(load <= 9999)
        {
            sprintf(lbuf,"%04d",load/10);
            LCDPutStr(lbuf,200,183, ASCII_26x16, ILI9341_WHITE , ILI9341_NAVY);
        }
        tftprv_mload = load;
    }
}

void Default_Main_Screen_KnuckleBoom(uint8_t sel)
{
    char lbuf[10];
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
        
        Display_KnuckleBoom_Image(118,85);
        
        draw_hollow_rect(ILI9341_BROWN,8,9,110,31);
        draw_hollow_rect(ILI9341_BROWN,9,10,109,30);
        LCDSetLine(62,11,62,29,ILI9341_BROWN);
        LCDSetLine(63,11,63,29,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,64,11,108,29);//DUTY
        LCDPutStr("DUTY",13,13, XLARGE, ILI9341_BLACK , ILI9341_WHITE);
        
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',0,0);
        
        Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',0,0);
        
        LCDSetLine(225,121,264,108,ILI9341_BROWN);
        LCDSetLine(264,108,302,121,ILI9341_BROWN);
        Draw_Rectangle_Lable_Outlines(225,121,"Load ",DispLoadVal,'T',0,0);
        
        Draw_Rectangle_Lable_Outlines(7,152,"M.Angl",bm_angle,0,0,0);
        Draw_Rectangle_Lable_Outlines(220,35,"K.Angl",Knbm_angle,0,0,0);
        Draw_Rod_Lable_Outlines(118,205,"Radius",Radius1,'M',0,0);
    }
    else
    {
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        if(tftprv_swl == Cap1)
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,0);
        else
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,1);
        tftprv_swl = Cap1;
        
        if(tftprv_mlen == TotalBmLength)
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,0);
        else
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,1);
        tftprv_mlen = TotalBmLength;
        
        if(tftprv_mload == DispLoadVal)
            Draw_Rectangle_Lable_Outlines(225,121,"Load ",DispLoadVal,'T',1,0);
        else
            Draw_Rectangle_Lable_Outlines(225,121,"Load ",DispLoadVal,'T',1,1);
        tftprv_mload = DispLoadVal;
        
        if(tftprv_mang == DispBoomAngle1)
            Draw_Rectangle_Lable_Outlines(7,152,"M.Angl",bm_angle,0,1,0);
        else
            Draw_Rectangle_Lable_Outlines(7,152,"M.Angl",bm_angle,0,1,1);
        tftprv_mang = DispBoomAngle1;
        
        if(tftprv_jang == Knbm_angle/10)
            Draw_Rectangle_Lable_Outlines(220,35,"K.Angl",Knbm_angle,0,1,0);
        else
            Draw_Rectangle_Lable_Outlines(220,35,"K.Angl",Knbm_angle,0,1,1);
        tftprv_jang = Knbm_angle/10;
        
        if(tftprv_rad == Radius1)
            Draw_Rod_Lable_Outlines(118,205,"Radius",Radius1,'M',1,0);
        else
            Draw_Rod_Lable_Outlines(118,205,"Radius",Radius1,'M',1,1);
        tftprv_rad = Radius1;
    }
}


void Default_Main_Screen_PNC_Whiteline(uint8_t sel)
{
    char lbuf[10];
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
        
        Display_PNC_Whiteline_Image(70,75);
        
        draw_hollow_rect(ILI9341_BROWN,8,9,110,31);
        draw_hollow_rect(ILI9341_BROWN,9,10,109,30);
        LCDSetLine(62,11,62,29,ILI9341_BROWN);
        LCDSetLine(63,11,63,29,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,64,11,108,29);//DUTY
        LCDPutStr("DUTY",13,13, XLARGE, ILI9341_BLACK , ILI9341_WHITE);
        
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',0,0);
        
//        Draw_Rod_Lable_Outlines(195,35,"Falls",sys.para.falls_cnt,0xff,0,0);
        draw_hollow_rect(ILI9341_BROWN,198,38,310,60);
        draw_hollow_rect(ILI9341_BROWN,199,39,309,59);
        LCDSetLine(264,40,264,58,ILI9341_BROWN);
        LCDSetLine(265,40,265,58,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY, 266,40,308,58);//Falls
        LCDPutStr("Falls",203,43, XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(lbuf,"%02d",sys.para.falls_cnt);
        LCDPutStr(lbuf,275,43, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
        
        Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',0,0);
        
        Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',0,0);
        
        Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,0,0);
        Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',0,0);
        
        draw_hollow_rect(ILI9341_BROWN,7,151,67,199);
        draw_hollow_rect(ILI9341_BROWN,8,152,66,198);
        LCDSetLine(9,169,65,169,ILI9341_BROWN);
        LCDSetLine(9,170,65,170,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,9,171,65,197);
        LCDPutStr("Fxy Rxy",15,155,SMALL, ILI9341_BLACK , ILI9341_WHITE);
        
        if((TiltAngle_1_X < 10)&&(TiltAngle_1_X > (-10))&&(TiltAngle_2_X < 10)&&(TiltAngle_2_X > (-10)))
        {
            sprintf(lbuf,"X:%02d %02d",TiltAngle_1_X,TiltAngle_2_X);
            LCDPutStr(lbuf,11,173, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
        else
        {
            LCDPutStr("OutOfRg",11,173, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
        if((TiltAngle_1_Y < 10)&&(TiltAngle_1_Y > (-10))&&(TiltAngle_2_Y < 10)&&(TiltAngle_2_Y > (-10)))
        {
            sprintf(lbuf,"Y:%02d %02d",TiltAngle_1_Y,TiltAngle_2_Y);
            LCDPutStr(lbuf,11,185, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
        else
        {
            LCDPutStr("OutOfRg",11,185, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
    }
    else
    {
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }

        if(tftprv_swl == Cap1)
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,0);
        else
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,1);
        tftprv_swl = Cap1;

        if(tftprv_mlen == TotalBmLength)
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,0);
        else
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,1);
        tftprv_mlen = TotalBmLength;

        if(tftprv_mload == DispLoadVal)
            Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',1,0);
        else
            Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',1,1);
        tftprv_mload = DispLoadVal;

        if(tftprv_mang == bm_angle/10)
            Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,1,0);
        else
            Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,1,1);
        tftprv_mang = bm_angle/10;

        if(tftprv_rad == Radius1)
            Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',1,0);
        else
            Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',1,1);
        tftprv_rad = Radius1;
        
        if((tftprv_fx != TiltAngle_1_X)||(tftprv_fy != TiltAngle_1_Y)||
           (tftprv_rx != TiltAngle_2_X)||(tftprv_ry != TiltAngle_2_Y))
            color_lcd_draw_rectangle(ILI9341_NAVY,11,173,65,195);
        
        if((TiltAngle_1_X < 10)&&(TiltAngle_1_X > (-10))&&(TiltAngle_2_X < 10)&&(TiltAngle_2_X > (-10)))
        {
            sprintf(lbuf,"X:%02d %02d",TiltAngle_1_X,TiltAngle_2_X);
            LCDPutStr(lbuf,11,173, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
        else
        {
            LCDPutStr("OutOfRg",11,173, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
        if((TiltAngle_1_Y < 10)&&(TiltAngle_1_Y > (-10))&&(TiltAngle_2_Y < 10)&&(TiltAngle_2_Y > (-10)))
        {
            sprintf(lbuf,"Y:%02d %02d",TiltAngle_1_Y,TiltAngle_2_Y);
            LCDPutStr(lbuf,11,185, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
        else
        {
            LCDPutStr("OutOfRg",11,185, SMALL, ILI9341_WHITE , ILI9341_NAVY);
        }
        tftprv_fx = TiltAngle_1_X;
        tftprv_fy = TiltAngle_1_Y;
        tftprv_rx = TiltAngle_2_X;
        tftprv_ry = TiltAngle_2_Y;
//        if(hint_refresh_cnt == 0)
//        {
//            hint_refresh_cnt = 15000;
//            Display_Duty_Hint_MainScreen();
//        }
    }
}

void Default_Main_Screen_PNC_Manbasket(uint8_t sel)
{
    char lbuf[10];
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
        
        Display_PNCNXP150_Image(48,25);
        
        draw_hollow_rect(ILI9341_BROWN,8,9,110,31);
        draw_hollow_rect(ILI9341_BROWN,9,10,109,30);
        LCDSetLine(62,11,62,29,ILI9341_BROWN);
        LCDSetLine(63,11,63,29,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,64,11,108,29);//DUTY
        LCDPutStr("DUTY",13,13, XLARGE, ILI9341_BLACK , ILI9341_WHITE);
        
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',0,0);
        
//        Draw_Rod_Lable_Outlines(195,35,"Falls",sys.para.falls_cnt,0xff,0,0);
        draw_hollow_rect(ILI9341_BROWN,198,38,310,60);
        draw_hollow_rect(ILI9341_BROWN,199,39,309,59);
        LCDSetLine(264,40,264,58,ILI9341_BROWN);
        LCDSetLine(265,40,265,58,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY, 266,40,308,58);//Falls
        LCDPutStr("Falls",203,43, XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(lbuf,"%02d",sys.para.falls_cnt);
        LCDPutStr(lbuf,275,43, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
        
        Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',0,0);
        
        Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',0,0);
        
        Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,0,0);
        Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',0,0);
    }
    else
    {
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }

        if(tftprv_swl == Cap1)
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,0);
        else
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,1);
        tftprv_swl = Cap1;

        if(tftprv_mlen == TotalBmLength)
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,0);
        else
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,1);
        tftprv_mlen = TotalBmLength;

        if(tftprv_mload == DispLoadVal)
            Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',1,0);
        else
            Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',1,1);
        tftprv_mload = DispLoadVal;

        if(tftprv_mang == bm_angle/10)
            Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,1,0);
        else
            Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,1,1);
        tftprv_mang = bm_angle/10;

        if(tftprv_rad == Radius1)
            Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',1,0);
        else
            Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',1,1);
        tftprv_rad = Radius1;        
    }
}

void Default_Main_Screen_PNC_Fork(uint8_t sel)
{
    char lbuf[10];
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
        
        Display_PNCFork_Image(70,75);
        
        draw_hollow_rect(ILI9341_BROWN,8,9,110,31);
        draw_hollow_rect(ILI9341_BROWN,9,10,109,30);
        LCDSetLine(62,11,62,29,ILI9341_BROWN);
        LCDSetLine(63,11,63,29,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,64,11,108,29);//DUTY
        LCDPutStr("DUTY",13,13, XLARGE, ILI9341_BLACK , ILI9341_WHITE);
        
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',0,0);
        
//        Draw_Rod_Lable_Outlines(195,35,"Falls",sys.para.falls_cnt,0xff,0,0);
        draw_hollow_rect(ILI9341_BROWN,198,38,310,60);
        draw_hollow_rect(ILI9341_BROWN,199,39,309,59);
        LCDSetLine(264,40,264,58,ILI9341_BROWN);
        LCDSetLine(265,40,265,58,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY, 266,40,308,58);//Falls
        LCDPutStr("Falls",203,43, XLARGE,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(lbuf,"%02d",sys.para.falls_cnt);
        LCDPutStr(lbuf,275,43, XLARGE, ILI9341_WHITE,ILI9341_NAVY);
        
        Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',0,0);
        
        Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',0,0);
        
        Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,0,0);
        Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',0,0);
    }
    else
    {
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }

        if(tftprv_swl == Cap1)
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,0);
        else
            Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,1);
        tftprv_swl = Cap1;

        if(tftprv_mlen == TotalBmLength)
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,0);
        else
            Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,1);
        tftprv_mlen = TotalBmLength;

        if(tftprv_mload == DispLoadVal)
            Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',1,0);
        else
            Draw_Rectangle_Lable_Outlines(233,91,"Load ",DispLoadVal,'T',1,1);
        tftprv_mload = DispLoadVal;

        if(tftprv_mang == bm_angle/10)
            Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,1,0);
        else
            Draw_Rectangle_Lable_Outlines(233,152,"Angle",bm_angle,0,1,1);
        tftprv_mang = bm_angle/10;

        if(tftprv_rad == Radius1)
            Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',1,0);
        else
            Draw_Rod_Lable_Outlines(70,205,"Radius",Radius1,'M',1,1);
        tftprv_rad = Radius1;        
    }
}


void Default_Main_Screen_TMC(uint8_t sel)
{
    char lbuf[10];
    
    if(sel == 0)
    {
        color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
        
        Display_TMC_Image(118,85);
        
        draw_hollow_rect(ILI9341_BROWN,8,9,110,31);
        draw_hollow_rect(ILI9341_BROWN,9,10,109,30);
        LCDSetLine(62,11,62,29,ILI9341_BROWN);
        LCDSetLine(63,11,63,29,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,64,11,108,29);//DUTY
        LCDPutStr("DUTY",13,13, XLARGE, ILI9341_BLACK , ILI9341_WHITE);
        
        if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
        {
            sprintf(lbuf,"%03d",sys.para.duty);
            LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        
        Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',0,0);
        
        Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',0,0);
        
        Draw_Rectangle_Lable_Outlines(225,35,"Load ",DispLoadVal,'T',0,0);
        
        Draw_Rectangle_Lable_Outlines(7,152,"Angle",bm_angle,0,0,0);
        Draw_Rod_Lable_Outlines(118,205,"Radius",Radius1,'M',0,0);
    }
    else
    {
        if((can_175_tout > 0)&&(((can_180_tout > 0)&&(sys.para.slave_enable_bit))||((can_201_tout > 0)&&(!sys.para.slave_enable_bit)))&&(can_352_tout > 0))
        {
            if((sys.para.duty >= 1)&&(sys.para.duty <= 999))
            {
                sprintf(lbuf,"%03d",sys.para.duty);
                LCDPutStr(lbuf,70,13, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
            }
            
            if(tftprv_swl == Cap1)
                Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,0);
            else
                Draw_Rod_Lable_Outlines(195,9,"SWL",Cap1,'T',1,1);
            tftprv_swl = Cap1;
            
            if(tftprv_mlen == TotalBmLength)
                Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,0);
            else
                Draw_Rectangle_Lable_Outlines(7,91,"Length",TotalBmLength,'M',1,1);
            tftprv_mlen = TotalBmLength;
            
            if(tftprv_mload == DispLoadVal)
                Draw_Rectangle_Lable_Outlines(225,35,"Load ",DispLoadVal,'T',1,0);
            else
                Draw_Rectangle_Lable_Outlines(225,35,"Load ",DispLoadVal,'T',1,1);
            tftprv_mload = DispLoadVal;
            
            if(tftprv_mang == bm_angle/10)
                Draw_Rectangle_Lable_Outlines(7,152,"Angle",bm_angle,0,1,0);
            else
                Draw_Rectangle_Lable_Outlines(7,152,"Angle",bm_angle,0,1,1);
            tftprv_mang = bm_angle/10;
            
            if(tftprv_rad == Radius1)
                Draw_Rod_Lable_Outlines(118,205,"Radius",Radius1,'M',1,0);
            else
                Draw_Rod_Lable_Outlines(118,205,"Radius",Radius1,'M',1,1);
            tftprv_rad = Radius1;
            
            if(hint_refresh_cnt == 0)
            {
                hint_refresh_cnt = 15000;
                Display_Duty_Hint_MainScreen();
            }
        }
        else if((can_175_tout == 0)||((can_180_tout == 0)||(can_201_tout == 0))||(can_352_tout == 0))
        {
            disp_refresh_cnt = 5000;
            color_lcd_draw_rectangle(ILI9341_NAVY,10,37,131,73);
            
            if((can_352_tout == 0)||((can_180_tout == 0)&&(sys.para.slave_enable_bit))||
               ((can_201_tout == 0)&&(!sys.para.slave_enable_bit)))
            {
                if(can_352_tout == 0)
                    LCDPutStr("CAN Box2 Absent ",12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                else if((can_180_tout == 0)&&(sys.para.slave_enable_bit))
                    LCDPutStr("CAN Slave Absent",12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
                else if((can_201_tout == 0)&&(!sys.para.slave_enable_bit))
                    LCDPutStr("Load CAN Absent ",12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
            }
            else
            {
                LCDPutStr("CAN Box2 Present",12,59,SMALL,ILI9341_WHITE, ILI9341_NAVY);
            }
            if(can_175_tout == 0)
            {
                LCDPutStr("CAN Box1 Absent ",12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
            }
            else
            {
                LCDPutStr("CAN Box1 Present",12,41,SMALL,ILI9341_WHITE, ILI9341_NAVY);
            }
        }
    }
}

void Draw_Rectangle_Lable_Outlines(uint16_t x, uint16_t y, char *lable, int16_t val, char unit_char, uint8_t sel, uint8_t clr)
{
    char lbuf[10],slen1,slen2;
    uint16_t x_offst;
    int16_t temp_val = val;
    int16_t temp_ang;
    
    temp_val = abs(val); 
        
    slen1 = strlen(lable)+1;
    sprintf(lbuf,"%04.1f",((float)val)/10.0);
    slen2 = strlen(lbuf)+1;
    
    if(slen1 > slen2)
    {
        x_offst = x + (slen1*13);
        
        if(sel == 0)
        {
            draw_hollow_rect(ILI9341_BROWN,x,y,x_offst,y+46);
            draw_hollow_rect(ILI9341_BROWN,x+1,y+1,x_offst-1,y+45);
            LCDSetLine(x+2,y+22,x_offst-2,y+22,ILI9341_BROWN);
            LCDSetLine(x+2,y+23,x_offst-2,y+23,ILI9341_BROWN);
            color_lcd_draw_rectangle(ILI9341_NAVY,x+2,y+24,x_offst-2,y+44);
        }
        if(clr)  color_lcd_draw_rectangle(ILI9341_NAVY,x+2,y+24,x_offst-2,y+44);
    }
    else
    {
        x_offst = x + (slen2*13);
        
        if(sel == 0)
        {
            draw_hollow_rect(ILI9341_BROWN,x,y,x_offst,y+46);
            draw_hollow_rect(ILI9341_BROWN,x+1,y+1,x_offst-1,y+45);
            LCDSetLine(x+2,y+22,x_offst-2,y+22,ILI9341_BROWN);
            LCDSetLine(x+2,y+23,x_offst-2,y+23,ILI9341_BROWN);
            color_lcd_draw_rectangle(ILI9341_NAVY,x+2,y+24,x_offst-2,y+44);
        }
        if(clr)  color_lcd_draw_rectangle(ILI9341_NAVY,x+2,y+24,x_offst-2,y+44);
    }
    
    if(sel == 0)    LCDPutStr(lable,x+(((x_offst-x)-((slen1-1)*13))/2)+6,y+4,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
    
    if(unit_char == 0)  //for angle value show only two digits
    {
        temp_ang = val/10;
        
        if(temp_ang >= 0)
        {
            sprintf(lbuf,"%02d",temp_ang);
            LCDPutStr(lbuf,x+((slen1*13)/2)-12,y+28, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            Draw_Circle(x+((slen1*13)/2)+18,y+28,2,ILI9341_WHITE);
//            LCDPutStr(lbuf,x+(((x_offst-x)-((slen2-1)*13))/2)+12,y+28, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
//            Draw_Circle(x+(((x_offst-x)-((slen2-1)*13))/2)+((slen2-1)*13)-8,y+28,2,ILI9341_WHITE);
        }
        else
        {
            LCDPutChar('-',x+((slen1*13)/2)-24,y+28, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
            sprintf(lbuf,"%02d",temp_val/10);
            LCDPutStr(lbuf,x+((slen1*13)/2)-12,y+28, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            Draw_Circle(x+((slen1*13)/2)+18,y+28,2,ILI9341_WHITE);
//            LCDPutStr(lbuf,x+(((x_offst-x)-((slen2-1)*13))/2)+12,y+28, XLARGE, ILI9341_WHITE, ILI9341_NAVY);
//            Draw_Circle(x+(((x_offst-x)-((slen2-1)*13))/2)+((slen2-1)*13)-12,y+28,2,ILI9341_WHITE);
        }
    }
    else
    {
        if((val >= 0)&&(val <= 999))
        {
            sprintf(lbuf,"%04.1f",((float)val)/10.0);
            LCDPutStr(lbuf,x+(((x_offst-x)-((slen2-1)*13))/2),y+28, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if((val > 999)&&(val <= 9999))
        {
            sprintf(lbuf,"%04d",val/10);
            LCDPutStr(lbuf,x+(((x_offst-x)-((slen2-1)*13))/2),y+28, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
        }
        else if(val < 0)
        {
            LCDPutChar('-',x+2,y+28, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
            sprintf(lbuf,"%04.1f",((float)temp_val)/10.0);
            LCDPutStr(lbuf,x+(((x_offst-x)-((slen2-1)*13))/2),y+28, XLARGE, ILI9341_WHITE , ILI9341_NAVY);        
        }
    }
    
    if((unit_char == 'T')||(unit_char == 'K'))      LCDPutChar(unit_char,x+(((x_offst-x)-((slen2-1)*13))/2)+((slen2-1)*13),y+28, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
    else if((unit_char == 'M')||(unit_char == 'F')) LCDPutChar(unit_char,x+(((x_offst-x)-((slen2-1)*13))/2)+((slen2-1)*13),y+28, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
//    else if(unit_char == 0)                         Draw_Circle(x+(((x_offst-x)-((slen2-1)*13))/2)+((slen2-1)*13),y+28,2,ILI9341_WHITE);
}

void Draw_Rod_Lable_Outlines(uint16_t x, uint16_t y, char *lable, int16_t val, char unit_char, uint8_t sel, uint8_t clr)
{
    char lbuf[10],slen1,slen2;
    uint16_t x_offst,l_offst,r_offst;
    
    slen1 = strlen(lable)+1;
    sprintf(lbuf,"%04.1f",((float)val)/10.0);
    slen2 = strlen(lbuf)+1;
    
    l_offst = (slen1*13);
    r_offst = (slen2*13);
    
    x_offst = x + l_offst + r_offst;
    
    if(sel == 0)
    {
        draw_hollow_rect(ILI9341_BROWN,x,y,x_offst,y+23);
        draw_hollow_rect(ILI9341_BROWN,x+1,y+1,x_offst-1,y+22);
        LCDSetLine(x+l_offst-10,y+2,x+l_offst-10,y+21,ILI9341_BROWN);
        LCDSetLine(x+l_offst-9 ,y+2,x+l_offst-9 ,y+21,ILI9341_BROWN);
        color_lcd_draw_rectangle(ILI9341_NAVY,x+l_offst-8,y+2,x_offst-2,y+21);
    }
    if(clr)  color_lcd_draw_rectangle(ILI9341_NAVY,x+(slen1*13),y+2,x_offst-2,y+21);
    
    if(sel == 0)    LCDPutStr(lable,x+6,y+4,XLARGE,ILI9341_BLACK , ILI9341_WHITE);
    
    if(val <= 999)
    {
        sprintf(lbuf,"%04.1f",((float)val)/10.0);
        LCDPutStr(lbuf,x+l_offst-6,y+4, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
    }
    else if((val > 999)&&(val <= 9999))
    {
        sprintf(lbuf,"%04d",val/10);
        LCDPutStr(lbuf,x+l_offst-6,y+4, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
    }
    
    if((unit_char == 'T')||(unit_char == 'K'))      LCDPutChar(unit_char,x_offst-15,y+4, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
    else if((unit_char == 'M')||(unit_char == 'F')) LCDPutChar(unit_char,x_offst-15,y+4, XLARGE, ILI9341_WHITE , ILI9341_NAVY);
    else if(unit_char == 0)                         Draw_Circle(x_offst-15,y+4,2,ILI9341_WHITE);
}


//==================================EOF=========================================

