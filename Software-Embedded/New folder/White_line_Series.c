/*
 * File:   White_line_Series.c
 * Author: Nitin Shankar 
 *
 * Created on 30 November, 2021, 10:24 AM
 */


#include "main.h"

uint32_t Track_Counter;

uint16_t Tilt_1_X_cnt,Tilt_1_Y_cnt;              //ADC Count tilt 1  Angle Sensor 
uint16_t Tilt_2_X_cnt,Tilt_2_Y_cnt;              //ADC Count tilt 2  Angle Sensor 
int16_t TiltAngle_1_X,TiltAngle_1_Y;
int16_t TiltAngle_2_X,TiltAngle_2_Y;
uint16_t Tele_Counter;

uint16_t temp_Tilt1X=0;
uint16_t temp_Tilt1Y=0;
uint16_t temp_Tilt2X=0;
uint16_t temp_Tilt2Y=0;

volatile uint8_t OTG_status,Dummy_status;
volatile uint8_t Current_Track,Previous_Track;
uint8_t Start_Loop,Track_Flag,otg_once_flag,height_once_flag,load_once_flag;

uint8_t _3TimeValue,_3TimeFlag;
uint8_t TxdBuff[50];

static uint8_t Sign1X=0,Sign1Y=0,Sign2X=0,Sign2Y=0;

const  char Voice_Language[3][13] =
{
    "HINDI        ",
    "ENGLISH      "
};

//===============================================

void White_line_Logic_Handler(void)
{
    ANGLE_STR ang;
    
    //============================================
    ang.LowBmAngle = 0;
    ang.HighBmAngle = 10;
    ang.BAHighAdcCount = 4075;
    //=========================================
    ang.Adccnt = Tilt_1_X_cnt;
    ang.BALowAdcCount = sys.para.Tilt1_X_MinAdc;
    TiltAngle_1_X = Calculate_Boom_Angle(ang);
    //==========================================
    ang.Adccnt = Tilt_1_Y_cnt; 
    ang.BALowAdcCount = sys.para.Tilt1_Y_MinAdc;
    TiltAngle_1_Y = Calculate_Boom_Angle(ang);
    //===========================================
    ang.Adccnt = Tilt_2_X_cnt;
    ang.BALowAdcCount = sys.para.Tilt1_X_MinAdc;
    TiltAngle_2_X = Calculate_Boom_Angle(ang);
    //==========================================
    ang.Adccnt = Tilt_2_Y_cnt; 
    ang.BALowAdcCount = sys.para.Tilt1_Y_MinAdc;
    TiltAngle_2_Y = Calculate_Boom_Angle(ang);
    //===========================================
    //Find out sign Angle
    if(TiltAngle_1_X<0)  Sign1X=1;
    else                 Sign1X=0;  
    
    if(TiltAngle_1_Y<0)  Sign1Y=1;
    else                 Sign1Y=0;      
    
    if(TiltAngle_2_X<0)  Sign2X=1;
    else                 Sign2X=0;
    
    if(TiltAngle_2_Y<0)  Sign2Y=1;
    else                 Sign2Y=0;
    
    //Nigative to positive Number
    temp_Tilt1X = abs(TiltAngle_1_X);
    temp_Tilt1Y = abs(TiltAngle_1_Y);
    temp_Tilt2X = abs(TiltAngle_2_X);
    temp_Tilt2Y = abs(TiltAngle_2_Y);
    
    if((temp_Tilt1X >= sys.para.Front_tilt_Cutoff)||(temp_Tilt1Y >= sys.para.Front_tilt_Cutoff))
    {
        if(temp_Tilt1X >= sys.para.Front_tilt_Cutoff)   tilt1X_ok_flag = 1;
        else                                            tilt1Y_ok_flag = 1;
        if(sys.para.fail_safe_stat_bit == 0)
            op.hooteraction = OUTPUT_ON;
        else 
            op.hooteraction = OUTPUT_OFF;
        op.over_tilt_bit = 1;
        Delay_1ms(200);
    }
    else if((temp_Tilt2X >= sys.para.Rear_tilt_Cutoff)||(temp_Tilt2Y >= sys.para.Rear_tilt_Cutoff))
    {
        if(temp_Tilt2X >= sys.para.Rear_tilt_Cutoff)   tilt2X_ok_flag = 1;
        else                                           tilt2Y_ok_flag = 1;
        if(sys.para.fail_safe_stat_bit == 0)
            op.hooteraction = OUTPUT_ON;
        else
            op.hooteraction = OUTPUT_OFF;
        op.over_tilt_bit = 1;
        Delay_1ms(200);
    }
    else
    {
        if(temp_Tilt1X < sys.para.Front_tilt_Cutoff)   tilt1X_ok_flag = 0;
        if(temp_Tilt1Y < sys.para.Front_tilt_Cutoff)   tilt1Y_ok_flag = 0;
        if(temp_Tilt2X < sys.para.Front_tilt_Cutoff)   tilt2X_ok_flag = 0;
        if(temp_Tilt2Y < sys.para.Front_tilt_Cutoff)   tilt2Y_ok_flag = 0;
        op.over_tilt_bit = 0;
    }    
}

//==============================================================================
void Play_track_Logic(void)
{
    uint8_t mp3_buf[50];
    
//    mp3_buf[0] = 0x7e;mp3_buf[1] = 0xff;
//    mp3_buf[2] = 0x06;mp3_buf[3] = 0x03;
//    mp3_buf[4] = 0x00;mp3_buf[5] = 0x00;           
//    mp3_buf[7] = 0xef;mp3_buf[8] = 0x00;
//    mp3_buf[9] = 0x00;
//    
//    mp3_buf[6] = Current_Track;
    
    if(Current_Track > 0)
    {
        if((Track_Counter == 0)&&(_3TimeFlag == 0))
        {
            if(_3TimeValue < CONSECUITIVE)
            {
                _3TimeValue++;
                Track_Flag = 1;
                while(pic25k80_tout);
                
                Track_Counter = DELAY1_BETWEEN_TWO_TRACKS;
                track_change_tout = DELAY3_SENSE_DEBAUNCE;
                
                memset(mp3_buf, 0, sizeof(mp3_buf));
                sprintf((char *)mp3_buf,"{,OD,%d,1,%d,}\r\n",digital_output_status,Current_Track);
                UART_Send_String(UART_MODULE4,(char *)mp3_buf);
                digital_output_status = 0;
                pic25k80_tout = 500;
//                UART4_Array(mp3_buf,10);
            }
            else
            {
                _3TimeFlag = 1;
                _3TimeValue = 0;
                Track_Counter = DELAY2_BETWEEN_TWO_TRACKS;
                track_change_tout = DELAY3_SENSE_DEBAUNCE;
            }
        }
        else if((Track_Counter == 0)&&(_3TimeFlag == 1))
        {
            Track_Flag = 2;            
            while(pic25k80_tout);
            
            Track_Counter = DELAY2_BETWEEN_TWO_TRACKS;
            memset(mp3_buf, 0, sizeof(mp3_buf));
            sprintf((char *)mp3_buf,"{,OD,%d,1,%d,}\r\n",digital_output_status,Current_Track);
            UART_Send_String(UART_MODULE4,(char *)mp3_buf);
            digital_output_status = 0;
            pic25k80_tout = 500;            
//            UART4_Array(mp3_buf,10);
        }
    }
}

/*============================================================================*/
/*
 * Function      : Voice_Announcement_Handler.
 * Description   : Used to handle voice announcement module.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Voice_Announcement_Handler(void)
{
   //OTG singal Present and Load Non zero
    if((OTG_status == 1))//&& (DispLoadVal>=0) &&(track_change_tout == 0)
    {
        if(otg_once_flag == 0)
        {
            otg_once_flag = 1;
            height_once_flag = 0;
            load_once_flag = 0;
            
            Current_Track = 4;
//            track_change_tout = DELAY3_SENSE_DEBAUNCE;
            if(sys.para.voice_of_language == 1)   
            {
                Current_Track += 4;
            }
            load_ann_timer_case = 0;
        }
        if(por_mp3_flag == 1)
        {
            por_mp3_flag = 0;
            Previous_Track = Current_Track;
        }
    }
    //======================================================================
    else if((TempDispBoomAngle > sys.para.Max_BAngle)&&(HookHight > sys.para.Max_BLength)&&(OTG_status == 0)) //&&(track_change_tout == 0)
    {
        if(height_once_flag == 0)
        {
            otg_once_flag = 0;
            height_once_flag = 1;
            load_once_flag = 0;
            
            Current_Track = 2;
//            track_change_tout = DELAY3_SENSE_DEBAUNCE;
            if(sys.para.voice_of_language == 1)   
            {
                Current_Track += 4;
            }
            load_ann_timer_case = 0;
        }
        if(por_mp3_flag == 1)
        {
            por_mp3_flag = 0;
            Previous_Track = Current_Track;
        }
    }
    //======================================================================
    else if((OTG_status == 0)&&(DispLoadVal > sys.para.zload_mask)) //&&(track_change_tout == 0)
    {
        switch(load_ann_timer_case)
        {
            case 0:
            {
                load_ann_tout = sys.para.load_announce_timer*1000;
                load_ann_timer_case = 1;
                track_change_tout = DELAY3_SENSE_DEBAUNCE;
                if(por_mp3_flag == 1)
                {
                    por_mp3_flag = 0;
                    Previous_Track = Current_Track;
                }
                break;
            }
            case 1:
            {
                if(load_ann_tout == 0)
                {
                    if(load_once_flag == 0)
                    {
                        otg_once_flag = 0;
                        height_once_flag = 0;
                        load_once_flag = 1;
                        load_ann_timer_case = 0;
                        Current_Track = 3;
                        if(sys.para.voice_of_language == 1)
                        {
                            Current_Track += 4;
                        }
                    }
                }                
                break;
            }
        }
    }
    else if(track_change_tout == 0)       //Recycle condition
    {
        _3TimeFlag = 0;
        _3TimeValue = 0;
        Current_Track = 0;
        Track_Counter = 0;
        load_ann_timer_case = 0;
        otg_once_flag = 0;
        height_once_flag = 0;
        load_once_flag = 0;
//        UART_Send_String(UART_MODULE1,"track_change_tout over...!!\r\n");
    }
    
    if((Previous_Track != Current_Track)&&(track_change_tout == 0))
    {
        _3TimeValue = 0;
        _3TimeFlag = 0;
        Track_Counter = 0;
        Previous_Track = Current_Track;
//        UART_Send_String(UART_MODULE1,"Track changed...!!\r\n");
//        sprintf(wbuf,"Previous_Track=%d Current_Track=%d\r\n",Previous_Track,Current_Track);
//        UART_Send_String(UART_MODULE1,wbuf);
    }
    
    Play_track_Logic();
}
    

/*******************************************************************************/
void Telematics_DataBuffer(void)
{
//    uint16_t NoOfDatabytes_2=31;
//    
//	TxdBuff[0] = '$';
//	TxdBuff[1] = (NoOfDatabytes_2 & 0xff00)>>8;
//	TxdBuff[2] = NoOfDatabytes_2 & 0x00ff;
//
//	TxdBuff[3] = 0x00;  
//	TxdBuff[4] = sys.para.duty;
//	
//	TempDispBoomAngle = (bm_angle/10);
//	TxdBuff[5] = (TempDispBoomAngle & 0xff00)>>8;
//	TxdBuff[6] = TempDispBoomAngle & 0x00ff;
//				
//	TxdBuff[7] = (Radius1 & 0xff00)>>8;
//	TxdBuff[8] = Radius1 & 0x00ff;
//					
//	TxdBuff[9] = (TotalBmLength & 0xff00)>>8;
//	TxdBuff[10] = TotalBmLength & 0x00ff;
//			
//	TxdBuff[11] = (DispLoadVal & 0xff00)>>8;
//	TxdBuff[12] = DispLoadVal & 0x00ff;
//					
//    TxdBuff[13] = (Cap1 & 0xff00)>>8;
//	TxdBuff[14] = Cap1 & 0x00ff;
//					
//	TxdBuff[15] = (condition & 0xff00)>>8;
//	TxdBuff[16] = condition & 0x00ff;
//    
//    TxdBuff[31]=    OTG_status  ;
//    TxdBuff[32]=    art_ip_bit  ;
 
}