#include "main.h"



/*============================================================================*/
/*
 * Function      :        map.
 * Description   :        Used to map a value between two range.
 * Parameters    :        x-actual value to map, in_min/in_max-input range and out_min/out_max-required output range.
 * Return        :        Mapped value in float.
*/
/*============================================================================*/
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


/*============================================================================*/
/*
 * Function      : Update_System_Parameters.
 * Description   : Used to update the csv values to local system parameters.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Update_System_Parameters(void)
{
    sys.para.falls_cnt              = lc_max_falls;
    sys.para.cal_len_min            = lc_bm_length_min;
    sys.para.cal_len_max            = lc_bm_length_max;
    sys.para.bm_length_min          = lc_bm_length_min;
    sys.para.bm_length_max          = lc_bm_length_max;
    sys.para.default_duty           = lc_default_duty;
    sys.para.vertical_offset        = lc_vert_offset;
    sys.para.horizontal_offset      = lc_horiz_offset;
    sys.para.rampivot_offset        = lc_rampivo_offset;
    sys.para.bm_cntr_line_offset    = lc_bmcntrline_offset;
    sys.para.rod_diameter           = lc_rod_diameter;
    sys.para.piston_diameter        = lc_piston_diameter;
    sys.para.bm_offset              = lc_bm_offset;
    sys.para.boom_parts             = lc_num_of_bm_part;
    temp_bm_offset                  = sys.para.bm_offset;
}

/*============================================================================*/
/*
 * Function      : Calculate_CRC.
 * Description   : Used to calculate 16bit crc.
 * Parameters    : None.
 * Return        : crc- calculated crc value.
*/
/*============================================================================*/
uint16_t Calculate_CRC(char *data)
{
	uint8_t k,j,len;
    uint16_t crc=0xffff;
	
    len = strlen(data);
    
    for(j=0; j<len; j++)
    {
        crc = crc ^ data[j];
        
        for(k=0; k<8; k++)
        {
            if(crc & 0x0001)
            {
                crc = ((crc) >> 1) ^ 0xA001;
            }
            else
            {
                (crc) >>= 1;
            }
        }
    }
    
    return crc;
}

/*============================================================================*/
/*
 * Function      : CAN_Receive.
 * Description   : Handles CAN data @500Kbps.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void CAN_Receive(void)
{
    uint16_t can_adc_t = 0;
    
    if(C1RXFUL1bits.RXFUL1 == 1)
    {
        can_rx.buffer = 1;
        C1RXFUL1bits.RXFUL1 = 0;
        
        RxECAN1(&can_rx);
        
        switch(can_rx.id)
        {
            case CAN_LENGTH_ANGLE_A2B:
            {
                if(sys.para.Select_System == ACE_NX360)
                {
                    can_adc_t   = (can_rx.data[0]*256)+can_rx.data[1];
                    if(can_adc_t != 0)
                        BLCount_CAN	 = can_adc_t;

                    can_adc_t   = (can_rx.data[2]*256)+can_rx.data[3];
                    if(can_adc_t != 0)
                        BACount_CAN	 = can_adc_t;

                    A2B_CAN	 	 =  can_rx.data[4];
                    len_adc_cnt = BLCount_CAN;                                      //for TMC manbasket2
                    ang_adc_cnt = BACount_CAN;
                    digital_input_status = 0;
                }
                can_len_angle_tout = 5000;
                break;
            }
            case CAN_P1_P2_SLEW:
            {
                if(sys.para.Select_System == ACE_NX360)
                {
                    P1Count_CAN	 = (can_rx.data[0]*256)+can_rx.data[1];            //P1 Pressure + P2 Pressure + Slew Signal
                    P2Count_CAN	 = (can_rx.data[2]*256)+can_rx.data[3];
                    Slew_CAN	 =  can_rx.data[4];
                    if(Slew_CAN == 0)   art_ip_bit = 0;
                    else                art_ip_bit = 1;
                    p1_pressure_cnt = P1Count_CAN;
                    p2_pressure_cnt = P2Count_CAN;
                    if(p1_pressure_cnt < sys.para.calib_P1LowAdcCount)
                    {
                        p1_pressure_avg = sys.para.calib_P1LowAdcCount;
                    }
                    else
                    {
                        p1_pressure_avg = p1_pressure_cnt;
                    }
                    if(p2_pressure_cnt < sys.para.calib_P2LowAdcCount)
                    {
                        p2_pressure_avg = sys.para.calib_P2LowAdcCount;
                    }
                    else
                    {
                        p2_pressure_avg = p2_pressure_cnt;
                    }
                    digital_input_status = 0;
                }
                can_p1p2_tout = 5000;
                break;
            }
            case CAN_P1P2P3P4_TILT:
            {
                if(sys.para.Select_System == TMC_MANBASKET)
                {
                    if(can_rx.data[0] == 1)
                    {
                        can_adc_t     = (can_rx.data[1]*256)+can_rx.data[2];
                        if(can_adc_t != 0)
                            can_p1_cnt   = can_adc_t;
                        can_adc_t     = (can_rx.data[3]*256)+can_rx.data[4];
                        if(can_adc_t != 0)
                            can_p2_cnt   = can_adc_t;
                        can_adc_t     = (can_rx.data[5]*256)+can_rx.data[6];
                        if(can_adc_t != 0)
                            can_p3_cnt   = can_adc_t;
                    }
                    else if(can_rx.data[0] == 2)
                    {
                        can_adc_t     = (can_rx.data[1]*256)+can_rx.data[2];
                        if(can_adc_t != 0)
                            can_p4_cnt   = can_adc_t;

                        can_adc_t   = (can_rx.data[3]*256)+can_rx.data[4];
                        if(can_adc_t != 0)
                            Tilt_1_X_cnt   = can_adc_t;

                        can_adc_t   = (can_rx.data[5]*256)+can_rx.data[6];
                        if(can_adc_t != 0)
                            Tilt_1_Y_cnt   = can_adc_t;
                    }
                }
                can_175_tout = 5000;
                break;
            }
            case CAN_LOADCELL_ANG_LEN:
            {
                if(can_rx.data[0] == 2)
                {
                    can_adc_t         = (can_rx.data[2]*256)+can_rx.data[3]; 
                    if(can_adc_t != 0)
                        ang_adc_cnt   = can_adc_t;
                    
                    can_adc_t         = (can_rx.data[4]*256)+can_rx.data[5];
                    if(can_adc_t != 0)
                        len_adc_cnt   = can_adc_t;
                }
                can_352_tout = 5000;
                break;
            }
            case CAN_KOPs_SLAVE:
            {
                if(sys.para.Select_System == TMC_MANBASKET)
                {
                    can_loadcell_cnt    = (can_rx.data[1]*256)+can_rx.data[2];
                    can_bpk_state       = can_rx.data[7];
                }
                can_180_tout = 5000;
                break;
            }
            case CAN_MAIN_LOADCELL:
            {
                can_loadcell_cnt    = (can_rx.data[0]*256)+can_rx.data[1];
                can_201_tout = 5000;
                break;
            }
            case CAN_MAIN_ANGLE:
            {
                if(can_rx.data[0] == 3)     //0 to 90 Degree main angle can_adc_t
                {
                    can_adc_t    = (can_rx.data[1]*256)+can_rx.data[2];
                    
                    if(can_adc_t <= 4095)
                        Main_ang_adc_cnt = can_adc_t;
                }
                can_357_tout = 5000;
                break;
            }
            case CAN_MAIN_TILT_ANGLE:
            {
                if(can_rx.data[0] == 1)     //+/- 10 Degree front tilt
                {
                    Tilt_1_X_cnt = (can_rx.data[1]*256)+can_rx.data[2];
                    Tilt_1_Y_cnt = (can_rx.data[3]*256)+can_rx.data[4];
                }
                can_357_tout = 5000;
                break;
            }
            case CAN_AUX_TILT_ANGLE:
            {
                if(can_rx.data[0] == 1)     //+/- 10 Degree front tilt
                {
                    Tilt_2_X_cnt = (can_rx.data[1]*256)+can_rx.data[2];
                    Tilt_2_Y_cnt = (can_rx.data[3]*256)+can_rx.data[4];
                }
                can_358_tout = 5000;
                break;
            }
        }     
    }
}

/*============================================================================*/
/*
 * Function      : CAN_Handler.
 * Description   : Handles CAN data @500Kbps.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void CAN_Handler(void)
{
    if(tower_lamp_can_tout == 0)
    {
        if(sys.para.slave_enable_bit)
        {
            can_frame_cnt++;
        }
        else
        {
            can_frame_cnt = 1;
            can_180_tout = 5000;        //To neglect slave
        }
        
        if(can_frame_cnt == 1)
        {
            can_tx.buffer = 0;
            can_tx.data_length = 8;
            can_tx.frame_type = 0;
            can_tx.id = 400;
            can_tx.message_type = NO_RTR;
            can_tx.data[0] = tower_lamp_out;
            can_tx.data[1] = 0;
            can_tx.data[2] = 0;
            can_tx.data[3] = 0;
            can_tx.data[4] = 0;
            can_tx.data[5] = 0;
            can_tx.data[6] = angleX_per;
            can_tx.data[7] = angleY_per;
            Ecan1WriteMessage(&can_tx);
            C1TR01CONbits.TXREQ0 = 1;
        }
        else if(can_frame_cnt == 2)
        {
            can_tx.buffer = 0;
            can_tx.data_length = 8;
            can_tx.frame_type = 0;
            can_tx.id = 401;
            can_tx.message_type = NO_RTR;
            can_tx.data[0] = 1;
            can_tx.data[1] = sys.para.duty%256;
            can_tx.data[2] = Radius1/256;
            can_tx.data[3] = Radius1%256;
            can_tx.data[4] = DispLoadVal/256;
            can_tx.data[5] = DispLoadVal%256;
            can_tx.data[6] = TempDispBoomAngle;
            can_tx.data[7] = PercLoad%256;
            Ecan1WriteMessage(&can_tx);
            C1TR01CONbits.TXREQ0 = 1;
        }
        else if(can_frame_cnt == 3)
        {
            can_frame_cnt = 0;
            can_tx.buffer = 0;
            can_tx.data_length = 8;
            can_tx.frame_type = 0;
            can_tx.id = 401;
            can_tx.message_type = NO_RTR;
            can_tx.data[0] = 2;
            can_tx.data[1] = TotalBmLength/256;
            can_tx.data[2] = TotalBmLength%256;
            can_tx.data[3] = Cap1/256;
            can_tx.data[4] = Cap1%256;
            can_tx.data[5] = HookHight/256;
            can_tx.data[6] = HookHight%256;
            can_tx.data[7] = (sys.para.sel_uom << 6) + (can_buzz_stat << 4) + err_led_status;
            Ecan1WriteMessage(&can_tx);
            C1TR01CONbits.TXREQ0 = 1;
        }
        tower_lamp_can_tout = 50;
    }
}

/*==============================================================================*/
/*
 * Function     : Bypasskey_Action.
 * Description  : Used to bypass the cutoff condition by using bypass key.
 * Parameters   : None.
 * Return       : None.
*/
/*==============================================================================*/
void Bypasskey_Action(void)
{
    if(((key.bpk_ftp == 1)||(can_bpk_state == 1))&&(sys.para.bpk_enable_bit == 1))
    {
        if(sys.para.fail_safe_stat_bit == 0) 
        {
            if(sys.para.bmdwn_rly_stat_bit == 1) op.relay1action = OUTPUT_OFF;
        }
        else 
        {   
            if(sys.para.bmdwn_rly_stat_bit == 1) op.relay1action = OUTPUT_ON;
        }
        
//        if((sys.para.Select_System != ACE_NX360)&&(sys.para.Select_System != TMC_MANBASKET))
//        {
//            if(sys.para.fail_safe_stat_bit == 0) 
//            {
//                if(sys.para.bmup_rly_stat_bit == 1) op.relay2action = OUTPUT_OFF;
//            }
//            else
//            {
//                if(sys.para.bmup_rly_stat_bit == 1) op.relay2action = OUTPUT_ON;
//            }
//        }
        
        if(sys.para.hootr_rly_stat_bit == 1) op.hooteraction = OUTPUT_OFF;
//        Delay_1ms(100);
    }
    else
    {
        if(sys.para.fail_safe_stat_bit == 0) 
        {
            if(sys.para.bmdwn_rly_stat_bit == 1) op.relay1action = OUTPUT_ON;
        }
        else 
        {
            if(sys.para.bmdwn_rly_stat_bit == 1) op.relay1action = OUTPUT_OFF;
        }
//        if((sys.para.Select_System != ACE_NX360)&&(sys.para.Select_System != TMC_MANBASKET)&&(condition != 4))  //condition = 4: A2B condition shouldn't be there
//        {
//            if(sys.para.fail_safe_stat_bit == 0) 
//            {
//                if(sys.para.bmup_rly_stat_bit == 1) op.relay2action = OUTPUT_ON;
//            }
//            else
//            {
//                if(sys.para.bmup_rly_stat_bit == 1) op.relay2action = OUTPUT_OFF;
//            }
//        }
        
        if(sys.para.hootr_rly_stat_bit == 1) op.hooteraction = OUTPUT_ON;
    }    
}

/*============================================================================*/
/*
 * Function      : Length_Correction.
 * Description   : Used to apply length factor to boom length.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Length_Correction(void)
{
    if((sys.para.sel_len_drum == TWENTY_METER_LENGTH)||(sys.para.sel_len_drum == TFIVE_METER_LENGTH))
    {
        if(bm_length <= (FOUR_METER+sys.para.cal_len_min))
        {
            bm_length += sys.para.bm_length_corr1;
        }
        else if((bm_length > (FOUR_METER+sys.para.cal_len_min))&&(bm_length <= (EIGHT_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr2;
        }
        else if((bm_length > (EIGHT_METER+sys.para.cal_len_min))&&(bm_length <= (TWELVE_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr3;
        }
        else if(bm_length > (TWELVE_METER+sys.para.cal_len_min))
        {
            bm_length += sys.para.bm_length_corr4;
        }
    }
    else if(sys.para.sel_len_drum == THIRTSIX_METER_LENGTH)
    {
        if((bm_length > (TWO_METER+sys.para.cal_len_min))&&(bm_length <= (EIGHT_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr1;
        }
        else if((bm_length > (EIGHT_METER+sys.para.cal_len_min))&&(bm_length <= (SIXTEEN_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr2;
        }
        else if((bm_length > (SIXTEEN_METER+sys.para.cal_len_min))&&(bm_length <= (TWFOUR_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr3;
        }
        else if(bm_length > (TWFOUR_METER+sys.para.cal_len_min))
        {
            bm_length += sys.para.bm_length_corr4;
        }
    }
    else if((sys.para.sel_len_drum == FORTYET_METER_LENGTH)||(sys.para.sel_len_drum == FORTYETM_TEFLON4C_LEN))
    {
        if((bm_length > (TWO_METER+sys.para.cal_len_min))&&(bm_length <= (TEN_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr1;
        }
        else if((bm_length > (TEN_METER+sys.para.cal_len_min))&&(bm_length <= (TWENTY_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr2;
        }
        else if((bm_length > (TWENTY_METER+sys.para.cal_len_min))&&(bm_length <= (THIRTY_METER+sys.para.cal_len_min)))
        {
            bm_length += sys.para.bm_length_corr3;
        }
        else if(bm_length > (THIRTY_METER+sys.para.cal_len_min))
        {
            bm_length += sys.para.bm_length_corr4;
        }
    }
}



/*============================================================================*/
/*
 * Function      : Length_Correction_Forklift.
 * Description   : Used to apply length factor to boom length.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Length_Correction_Forklift(void)
{
    if(bm_length <= (ONE_METER+sys.para.cal_len_min))
    {
        bm_length += sys.para.bm_length_corr1;
    }
    else if((bm_length > (ONE_METER+sys.para.cal_len_min))&&(bm_length <= (TWO_METER+sys.para.cal_len_min)))
    {
        bm_length += sys.para.bm_length_corr2;
    }
    else if((bm_length > (TWO_METER+sys.para.cal_len_min))&&(bm_length <= (THREE_METER+sys.para.cal_len_min)))
    {
        bm_length += sys.para.bm_length_corr3;
    }
    else if(bm_length > (THREE_METER+sys.para.cal_len_min))
    {
        bm_length += sys.para.bm_length_corr4;
    }
}


/*============================================================================*/
/*
 * Function      : Parse_Uart_Data.
 * Description   : Read Analog values from uart.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Parse_Uart_Data(void)
{
    char lbuf[50];    
    char* token,token_buf[10][10];
    uint8_t j,k;
    
    if(u4ready_bit)
    {
        if(memcmp(u4buf+1,",AD,",4) == 0)          //Output data {,,AD,p1_adc_cnt,p2_adc_cnt,len_adc_cnt,ang_adc_cnt,digital_status,}
        {
            token = strtok(u4buf, ",");
            sprintf(lbuf,"%s",token);   //Skip SOF
            token = strtok(NULL,",");
            sprintf(lbuf,"%s",token);   //Skip command
            j=0;
            for(k=0; k<5; k++)
            {
                token = strtok(NULL,",");
                sprintf(token_buf[j],"%s",token);
                j++;
            }
            p1_pressure_cnt  = (uint16_t)(atol(token_buf[0]));
            if(p1_pressure_cnt > 4095)  p1_pressure_cnt = sys.para.calib_P1LowAdcCount;
            
            if(p1_pressure_cnt < sys.para.calib_P1LowAdcCount)
            {
                p1_pressure_avg = sys.para.calib_P1LowAdcCount;
            }
            else
            {
                p1_pressure_avg = p1_pressure_cnt;
            }
            p2_pressure_cnt  = (uint16_t)(atol(token_buf[1]));
            if(p2_pressure_cnt > 4095)  p2_pressure_cnt = sys.para.calib_P2LowAdcCount;
            
            if(p2_pressure_cnt < sys.para.calib_P2LowAdcCount)
            {
                p2_pressure_avg = sys.para.calib_P2LowAdcCount;
            }
            else
            {
                p2_pressure_avg = p2_pressure_cnt;
            }
            len_adc_cnt  = (uint16_t)(atol(token_buf[2]));
            ang_adc_cnt  = (uint16_t)(atol(token_buf[3]));
            digital_input_status  = (uint16_t)(atol(token_buf[4]));
        }
        memset(u4buf, 0, sizeof(u4buf));
        u4indx = 0;
        u4ready_bit = 0;
    }  
}


/*============================================================================*/
/*
 * Function      : Send_Data_25K80.
 * Description   : Send data to 25K80 board.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Send_Data_25K80(void)
{
    char mbuf[50];
    
    if(pic25k80_tout == 0)
    {
        memset(mbuf, 0, sizeof(mbuf));
        sprintf(mbuf,"{,OD,%d,0,0,}\r\n",digital_output_status);
        UART_Send_String(UART_MODULE4,mbuf);
        digital_output_status = 0;
        pic25k80_tout = 200;
    }
}


/*============================================================================*/
/*
 * Function      : RoundOff.
 * Description   : Used to rounding off a value(59.4 ~ 59.0 and 59.5 ~ 60.0)
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
float RoundOff(float x)
{
    float y;
    
    y = (int32_t)(x + 0.5);
    
    return y;
}


/*============================================================================*/
/*
 * Function      : Send_Pressure_Curve_Uart.
 * Description   : Used to send P1P2 pressure curve data to PC by using UART.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Send_Pressure_Curve_Uart(void)
{
    uint8_t loop1,loop3,loop4,byt;
    uint16_t loop2;
    char lbuf[5];
    
    pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + flash_memory_offset;
        
    for(loop1=0; loop1<lc_total_duty; loop1++)              //Loop for Total duties
    {
        for(loop4=0; loop4<5; loop4++)                      //Loop for maximum 5 length calibration points
        {
            for(loop3=0; loop3<2; loop3++)                  //Loop for P1 and P2
            {
                UART_Send_String(UART_MODULE3,"24");
                Delay_1ms(1);
                UART_Send_String(UART_MODULE2,"24");
                Delay_1ms(1);
                for(loop2=0; loop2<256; loop2++)            //Each pressure curve table
                {
                    byt = SPIFlash_Read_Byte(pc_page_addr);
                    
                    sprintf(lbuf,"%02X",byt);
                    UART_Send_String(UART_MODULE3,lbuf);
                    Delay_1ms(1);
                    UART_Send_String(UART_MODULE2,lbuf);
                    Delay_1ms(1);
                    pc_page_addr++;
                }
                UART_Send_String(UART_MODULE3,"23\n");
                Delay_1ms(1);
                UART_Send_String(UART_MODULE2,"23\n");
                Delay_1ms(10);
            }
        }
    }    
}
/*============================================================================*/
/*
 * Function      : Analog_Data_Read.
 * Description   : Used to read analog data.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Analog_Data_Read(void)
{
    uint8_t i;
//    ANGLE_STR ang;
    float Alpha2;
    
//    CAN_Receive();
    
    if((sys.para.Select_System != ACE_NX360)&&(sys.para.Select_System != TMC_MANBASKET)&&
       (sys.para.Select_System != TMC_MANBASKET2))
    {
        Parse_Uart_Data();          //Analog and digitalRead data....
    }
    
    if(sys.para.Select_System != FORK_LIFT)
    {
        if(sys.para.bm_length_min == 0 || sys.para.bm_length_max == 0)
        {
            disp_error |= 0x01;
        }
        else
        {
            disp_error &= ~0x01;
        }
        
        if(len_adc_cnt >= 600)
        {
            if(sys.para.mpoint_len_enable_bit == 0)
            {
                Alpha2 = Flot_Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)+sys.para.bl_adc_cnt[1];
                Alpha2 = RoundOff(Alpha2);
//                bm_length = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)+sys.para.bl_adc_cnt[1];   //sys.para.bl_adc_cnt[1] is the offset length in meter saved in supervisor menu during setting of minimum bm length
                bm_length = (uint16_t)Alpha2;
            }
            else
            {
                Alpha2 = Flot_Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)*100;
                Alpha2 = RoundOff(Alpha2);
                mm_len = (uint16_t)Alpha2;
//                mm_len = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)*100;
                
                for(i=0; i<sys.para.numof_len_cal; i++)
                {
                    if((mm_len >= sys.para.multipt_lcalib[i][1])&&(mm_len <= sys.para.multipt_lcalib[i+1][1]))
                    {
                        Alpha2 = Interpolate_Value(mm_len,sys.para.multipt_lcalib[i][1],sys.para.multipt_lcalib[i+1][1],sys.para.multipt_lcalib[i][0],sys.para.multipt_lcalib[i+1][0]);
//                        bm_length = Interpolate_Value(mm_len,sys.para.multipt_lcalib[i][1],sys.para.multipt_lcalib[i+1][1],sys.para.multipt_lcalib[i][0],sys.para.multipt_lcalib[i+1][0]);
                        
                        break;
                    }
                    else if(mm_len < sys.para.multipt_lcalib[0][1])
                    {
                        Alpha2 = sys.para.bm_length_min;
//                        bm_length = sys.para.bm_length_min;
                        
                        break;
                    }
                    else if(mm_len > sys.para.multipt_lcalib[sys.para.numof_len_cal-1][1])
                    {
                        Alpha2 = Interpolate_Value(mm_len,sys.para.multipt_lcalib[sys.para.numof_len_cal-2][1],sys.para.multipt_lcalib[sys.para.numof_len_cal-1][1],sys.para.multipt_lcalib[sys.para.numof_len_cal-2][0],sys.para.multipt_lcalib[sys.para.numof_len_cal-1][0]);
//                        bm_length = Interpolate_Value(mm_len,sys.para.multipt_lcalib[sys.para.numof_len_cal-2][1],sys.para.multipt_lcalib[sys.para.numof_len_cal-1][1],sys.para.multipt_lcalib[sys.para.numof_len_cal-2][0],sys.para.multipt_lcalib[sys.para.numof_len_cal-1][0]);

                        break;
                    }
                }
                Alpha2 = RoundOff(Alpha2);
                bm_length = (uint16_t)Alpha2;
            }
        }
        else bm_length = sys.para.bm_length_min;
        
//        if(len_adc_cnt > 0)
//            bm_length = Calculate_Boom_Length(sys.para.sel_len_drum,len_adc_cnt)+sys.para.bl_adc_cnt[1];   //sys.para.bl_adc_cnt[1] is the offset length in meter saved in supervisor menu during setting of minimum bm length
        
        Length_Correction();
        
        if(sys.para.Select_System != PNC_FORK)
        {
            if(bm_length > sys.para.bm_length_max)       bm_length = sys.para.bm_length_max;
            else if(bm_length < sys.para.cal_len_min)    bm_length = sys.para.cal_len_min;
        }
        else if(sys.para.Select_System == PNC_FORK)
        {
            if(sys.para.duty != sys.para.fork_duty)
            {
                if(bm_length > sys.para.bm_length_max)       bm_length = sys.para.bm_length_max;
                else if(bm_length < sys.para.cal_len_min)    bm_length = sys.para.cal_len_min;
            }
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            if(bm_length < sys.para.cal_len_min)    bm_length = sys.para.cal_len_min;
        }
    }
    
    if((sys.para.Select_System != PALFINGER_KNUCKLE_BOOM)&&(sys.para.Select_System != FORK_LIFT))
    {
        if(ang_adc_cnt > 0)
        {
            bm_angle = map(ang_adc_cnt,sys.para.cal_angle_min_cnt,sys.para.cal_angle_max_cnt,sys.para.cal_angle_min,sys.para.cal_angle_max);
//            bm_angle = Calculate_Boom_Angle(ang);                   //calculate Main Boom  Angle
        }
    }
    else if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
    {
        if(ang_adc_cnt > 0)
        {
            Knbm_angle = map(ang_adc_cnt,sys.para.cal_angle_min_cnt,sys.para.cal_angle_max_cnt,sys.para.cal_angle_min,sys.para.cal_angle_max);            
//            Knbm_angle = Calculate_Boom_Angle(ang);                 //calculate Knuckle boom Angle comes with length drum
        }
        if(Main_ang_adc_cnt > 0)
        {
            bm_angle = map(Main_ang_adc_cnt,sys.para.cal_mangle_min_cnt,sys.para.cal_mangle_max_cnt,sys.para.cal_mangle_min,sys.para.cal_mangle_max);
            DispBoomAngle1 = bm_angle/10;
//            bm_angle = Calculate_Boom_Angle(ang);               //calculate Main Boom Angle Adc Count  
        }
        
        if(menu_stat == DEFAULT_PAGE)
        {
            if(bm_angle < sys.para.low_cutoff_angl)
            {
                sys.para.rig_duty_bit = 1;
#ifdef DISPLAY_16x2
                Lcd16x2_Out(1,1,"  SLI Inactive  ");
                Lcd16x2_Out(2,1,"  Rigging Duty  ");
#else
#ifdef DISPLAY_TFT32
                if(rig_dty_angl_flag == 0)
                {
                    rig_dty_angl_flag = 1;
                    color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);
                    color_lcd_draw_rectangle(ILI9341_NAVY,6,45,313,195);
                    LCDPutStr("SLI INACTIVE",95,90,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
                    LCDPutStr("RIGGING DUTY",95,150,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
                }
#else
#ifdef DISPLAY_192x64
                
#endif
#endif
#endif
            }
            else if(bm_angle > sys.para.low_cutoff_angl+1)
            {
                sys.para.rig_duty_bit = 0;
                
#ifdef DISPLAY_16x2
                
#else
#ifdef DISPLAY_TFT32
                if(rig_dty_angl_flag)
                {
                    rig_dty_angl_flag = 0;
                    Default_Main_Screen_Display();
                }
#else
#ifdef DISPLAY_192x64
                
#endif
#endif
#endif
            }
        }
    }
}

/*============================================================================*/
/*
 * Function      : Analog_Data_Process.
 * Description   : Used to process analog data.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Analog_Data_Process(void)
{
    uint8_t i;
    
    if(calib_mode == 0)
    {
        if(sys.para.Select_System == FORK_LIFT) Fork_Height();
                
        if((sys.para.Select_System != FORK_LIFT)&&(sys.para.Select_System != TMC_MANBASKET)&&
           (sys.para.Select_System != TMC_MANBASKET2))
        {
            TempDispBoomLength = TotalBmLength;
            
            BoomSection = ((sys.para.duty-1)*5);
            
            if(sys.para.duty_type[sys.para.duty-1] == 1)
            {
                
            }
            else
            {
                if(sys.para.duty_type[sys.para.duty-1] != 0)
                {
                    TempMM1 = (uint8_t)sys.para.duty_type[sys.para.duty-1]-1;

                    for(BmSectCntr=0; BmSectCntr < TempMM1; BmSectCntr++)
                    {
                        TempMM2 = BoomSection+BmSectCntr;
                        
                        if((TempDispBoomLength >= sys.para.length_array[TempMM2]) && (TempDispBoomLength < sys.para.length_array[(TempMM2+1)]))
                        {
                            break;
                        }
                        if((BmSectCntr+1)==TempMM1)
                        {
                            break;
                        }
                    }                    
                    BoomSection = (BoomSection + BmSectCntr);
                    // Problem when the boom length is greater than or equal to Max boom Length .....
                    // that is why introduced this step ................................
                    if(TempDispBoomLength >= sys.para.bm_length_max)
                    {
                        BoomSection = (((sys.para.duty-1)*5) + (sys.para.duty_type[sys.para.duty-1]-2)); //length point
                    }
                }
            }
            
            pd.pc_start_page = lc_press_curve_page_s;
            pd.flash_mem_offst = flash_memory_offset;
            
            pd.bm_section = (uint8_t)BoomSection;
            pd.ramPivot = sys.para.rampivot_offset;
            pd.bmcntrl_offst = sys.para.bm_cntr_line_offset;
            pd.numof_cyl = sys.para.num_of_cylinders;
            pd.cal_case = sys.para.num_cal;
            
            pd.constK = constK_Int;
            pd.cosG = cos_Gamma_Int;
            pd.sinG = sin_Gamma_Int;
            pd.piton_area = PistonArea_Int;
            pd.diffr_area = DiffArea_Int;
            
            pd.duty_type = sys.para.duty_type[sys.para.duty-1];
            pd.len_array_max = sys.para.length_array[pd.bm_section+1];
            pd.len_array_min = sys.para.length_array[pd.bm_section];
            pd.mangle = bm_angle;
            pd.radius = Radius1;
            pd.tlen = TotalBmLength;
            
            pd.p1_cnts = p1_pressure_avg;
            pd.p1_lowcnts = sys.para.calib_P1LowAdcCount;
            pd.p1_highcnts = sys.para.calib_P1HighAdcCount;
            pd.p2_cnts = p2_pressure_avg;
            pd.p2_lowcnts = sys.para.calib_P2LowAdcCount;
            pd.p2_highcnts = sys.para.calib_P2HighAdcCount;
            pd.prchn = PRCHN;
            
            TempDispBoomAngle = (bm_angle/10);
            if((sys.para.duty == sys.para.manbas_duty)&&(sys.para.Select_System == ACE_MANBASKET_HXP))
            {
                Manbasket_Load_Cal_Func(loadcell_cnt);
            }
            else if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
            {
                DispLoadVal = (KnuckleBoom_LoadCalcultaion() + sys.para.hook_load);
            }
            else
            {
                DispLoadVal = (PNC_LoadCalcultaion() + sys.para.hook_load);
            }
            Apply_Load_Corrections();
        }
        else if(sys.para.Select_System == FORK_LIFT)
        {
            if(p1_pressure_cnt > sys.para.forkcalib_press_min[0][1])    //[1]=> 1 means counts and 0 means load value
            {
                if(sys.para.bpk_method_stat_bit)        //For SCA fork lift
                {
                    if(art_ip_bit)
                    {
                        P1Fact = (float)((sys.para.forkcalib_press_max[1][0] - sys.para.forkcalib_press_min[1][0])*1.0)/(sys.para.forkcalib_press_max[1][1] - sys.para.forkcalib_press_min[1][1]);
                        if(p1_pressure_cnt < sys.para.forkcalib_press_min[1][1])
                            CalcLoad = 0;
                        else
                            CalcLoad = (P1Fact*(p1_pressure_cnt-sys.para.forkcalib_press_min[1][1]));
                        DispLoadVal = (uint16_t)CalcLoad;
                        DispLoadVal = (DispLoadVal + sys.para.hook_load);
                    }
                    else
                    {
                        P1Fact = (float)((sys.para.forkcalib_press_max[0][0] - sys.para.forkcalib_press_min[0][0])*1.0)/(sys.para.forkcalib_press_max[0][1] - sys.para.forkcalib_press_min[0][1]);
                        if(p1_pressure_cnt < sys.para.forkcalib_press_min[0][1])
                            CalcLoad = 0;
                        else
                            CalcLoad = (P1Fact*(p1_pressure_cnt-sys.para.forkcalib_press_min[0][1]));
                        DispLoadVal = (uint16_t)CalcLoad;
                        DispLoadVal = (DispLoadVal + sys.para.hook_load);
                    }
                }
                else
                {
                    for(i=0; i<sys.para.numof_calib_fork-1; i++)
                    {
                        if((TotalBmLength >= sys.para.fork_len_region[i])&&(TotalBmLength < sys.para.fork_len_region[i+1]))
                        {
                            P1Fact = (float)((sys.para.forkcalib_press_max[i][0] - sys.para.forkcalib_press_min[i][0])*1.0)/(sys.para.forkcalib_press_max[i][1] - sys.para.forkcalib_press_min[i][1]);
                            if(p1_pressure_cnt < sys.para.forkcalib_press_min[i][1])
                                CalcLoad = 0;
                            else
                                CalcLoad = (P1Fact*(p1_pressure_cnt-sys.para.forkcalib_press_min[i][1]));
                            DispLoadVal = (uint16_t)CalcLoad;
                            DispLoadVal = (DispLoadVal + sys.para.hook_load);
                            break;
                        }
                    }
                    if(TotalBmLength >= sys.para.fork_len_region[sys.para.numof_calib_fork-1])
                    {
                        P1Fact = (float)((sys.para.forkcalib_press_max[sys.para.numof_calib_fork-1][0] - sys.para.forkcalib_press_min[sys.para.numof_calib_fork-1][0])*1.0)/(sys.para.forkcalib_press_max[sys.para.numof_calib_fork-1][1] - sys.para.forkcalib_press_min[sys.para.numof_calib_fork-1][1]);
                        if(p1_pressure_cnt < sys.para.forkcalib_press_min[sys.para.numof_calib_fork-1][1])
                            CalcLoad = 0;
                        else
                            CalcLoad = (P1Fact*(p1_pressure_cnt-sys.para.forkcalib_press_min[sys.para.numof_calib_fork-1][1]));
                        DispLoadVal = (unsigned int)CalcLoad;
                        DispLoadVal = (DispLoadVal + sys.para.hook_load);
                    }
                }
            }
            else
            {
                DispLoadVal = (uint16_t)sys.para.calib_pressure1_min;
                DispLoadVal = (DispLoadVal + sys.para.hook_load);
            }
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            Manbasket_Load_Cal_Func(can_loadcell_cnt);
        }
        
        if(sys.para.rig_duty_bit == 0)
        {
            if(CapCalMethodSwitch == 0)       // CutOff => Radius
            {
                if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
                {
                    if(sys.para.duty <= lc_total_duty)
                    {
                        if(Check_Flags() == 1)
                        {
                            if(sys.para.fail_safe_stat_bit == 0)
                            {
                                op.hooteraction = OUTPUT_ON;
                            }
                            else
                            {
                                op.hooteraction = OUTPUT_OFF;
                            }
                        }
                        else
                        {
                            if(Check_Errors_In_AR() == 0)
                            {
                                CheckLoadVal();
                            }
                            else
                            {
                                CAP=0.0;        Cap1=0;
                                Bypasskey_Action();
                            }
                        }
                    }
                }
                else
                {
                    if(sys.para.duty <= lc_total_duty)
                    {
                        if(Check_Errors_In_AR() == 0)
                        {
                            CheckLoadVal();
                        }
                        else
                        {
                            CAP = 0.0;        Cap1 = 0;
                            Bypasskey_Action();
//                            UART_Send_String(UART_MODULE1,"Bypasskey_Action2\r\n");
                        }
                    }
                }
            }
            else                        // CutOff => Angle
            {
                if(Check_Errors_In_AR() == 0)
                {
                    CheckLoadVal();
                }
                else
                {
//                    op.buzzaction = OUTPUT_ON;
                    CAP = 0.0;        Cap1=0;
                    Bypasskey_Action();
//                    UART_Send_String(UART_MODULE1,"Bypasskey_Action3\r\n");
                }
            }
        }
        else if((sys.para.rig_duty_bit == 1)&&(sys.para.Select_System != PALFINGER_KNUCKLE_BOOM))
        {
            Marching_Mode();//Display enters in Rigging duty...(SLI inactive Mode))
        }
        else
        {
            
        }
        
        switch(sys.para.Select_System)
        {
            case REGULAR_SYSTEM         :                                       break;    //  Regular PNC System

            case WHITELINE_ESCORTS      :    White_line_Logic_Handler();        break;    //  Escort Whiteline series

            case ACE_NX360              :    ACE_NX360_Logic_Handler();         break;    //  ACE NX360 CAN based

            case PALFINGER_KNUCKLE_BOOM :                                       break;       
            
            case ACE_MANBASKET_HXP      :                                       break;   //Man Basket ACE HXP MODEL 
            
            case FORK_LIFT              :                                       break;     //Not required any function
            
            case TMC_MANBASKET          :   OTG_Tilt_Monitor();                 break;
            
            case TMC_MANBASKET2         :if(sys.para.obtilt_enable_bit) Tilt_Monitor();else {tilt1X_ok_flag = 0; tilt1Y_ok_flag = 0;}  break;
            
            case TELESCOPIC_RT40        :if(sys.para.obtilt_enable_bit) Tilt_Monitor();else {tilt1X_ok_flag = 0; tilt1Y_ok_flag = 0;}  break;
        }
        
        Voice_Announcement_Handler();
    }    
}

void Common_Logic_Handler(void)
{
    uint16_t NoOfDatabytes=17;
    
    TxdBuff[0] = '$';
    TxdBuff[1] =(NoOfDatabytes & 0xff00)>>8;
    TxdBuff[2] = NoOfDatabytes & 0x00ff;

    TxdBuff[3] = 0x00;  
    TxdBuff[4] = sys.para.duty;

    TempDispBoomAngle = (bm_angle/10);
    TxdBuff[5] = (TempDispBoomAngle & 0xff00)>>8;
    TxdBuff[6] = TempDispBoomAngle & 0x00ff;

    TxdBuff[7] = (Radius1 & 0xff00)>>8;
    TxdBuff[8] = Radius1 & 0x00ff;

    TxdBuff[9] = (TotalBmLength & 0xff00)>>8;
    TxdBuff[10] = TotalBmLength & 0x00ff;

    TxdBuff[11] = (DispLoadVal & 0xff00)>>8;
    TxdBuff[12] = DispLoadVal & 0x00ff;

    TxdBuff[13] = (Cap1 & 0xff00)>>8;
    TxdBuff[14] = Cap1 & 0x00ff;

    TxdBuff[15] = (condition & 0xff00)>>8;
    TxdBuff[16] = condition & 0x00ff;
    
    TxdBuff[17] = art_ip_bit;
    TxdBuff[18] = '#';
    
    if(Tele_Counter == 0)
    {
//       UART3_Array(TxdBuff,19);
       Tele_Counter = 1000;             //1 sec Count=1000 msec
    }
}


//==============================================================================
void ACE_NX360_Logic_Handler(void)
{
    //Total Relay 3 = Relay --1 -  
    if((SlewMode!=0)&&(Slew_CAN))
    {
        //BM_UP_RLY=0;                        // Slew Dump Valve ON
//        op.relay2action = OUTPUT_OFF ;
        op.redledaction = OUTPUT_OFF;
    }
    else if((SlewMode!=0)&&(!Slew_CAN))
    {
	     //BM_UP_RLY=1;                        // Slew Dump Valve OFF
//         op.relay2action = OUTPUT_ON ;
        op.redledaction = OUTPUT_ON;
    }
	else if((SlewMode==0)&&(Slew_CAN))
    {
	     //BM_UP_RLY=1;                        // Slew Dump Valve OFF
//         op.relay2action = OUTPUT_ON ;
        op.redledaction = OUTPUT_ON;
    }
	else if((SlewMode==0)&&(!Slew_CAN))
    {
	     //BM_UP_RLY=1;                        // Slew Dump Valve OFF 
//         op.relay2action = OUTPUT_ON ;
        op.redledaction = OUTPUT_ON;
    }
    else
    {
        
    }   
//    Send_Telematics_data();
}

//==============================================================================
void Send_Telematics_data(void)
{
    uint16_t NoOfDatabytes=17;
    
    TxdBuff[0] = '$';
    TxdBuff[1] =(NoOfDatabytes & 0xff00)>>8;
    TxdBuff[2] = NoOfDatabytes & 0x00ff;
    
    TxdBuff[3] = 0x00;  
    TxdBuff[4] = sys.para.duty;

    TempDispBoomAngle = (bm_angle/10);
    TxdBuff[5] = (TempDispBoomAngle & 0xff00)>>8;
    TxdBuff[6] = TempDispBoomAngle & 0x00ff;

    TxdBuff[7] = (Radius1 & 0xff00)>>8;
    TxdBuff[8] = Radius1 & 0x00ff;

    TxdBuff[9] = (TotalBmLength & 0xff00)>>8;
    TxdBuff[10] = TotalBmLength & 0x00ff;

    TxdBuff[11] = (DispLoadVal & 0xff00)>>8;
    TxdBuff[12] = DispLoadVal & 0x00ff;

    TxdBuff[13] = (Cap1 & 0xff00)>>8;
    TxdBuff[14] = Cap1 & 0x00ff;

    TxdBuff[15] = (condition & 0xff00)>>8;
    TxdBuff[16] = condition & 0x00ff;
    
    TxdBuff[17] = SlewMode;
    TxdBuff[18] = '#';
    
    if(Tele_Counter==0)
    {
//       UART3_Array(TxdBuff,19);
       Tele_Counter=1000;             //1 sec Count=1000 msec
    }
    else
    {

    }
}
/*============================================================================*/
/*
 * Function      : OTG_Tilt_Monitor.
 * Description   : Used to monitor stabilization of TMC crane.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void OTG_Tilt_Monitor(void)
{
    Tilt_Monitor();
    
    p1_hyst = sys.para.forkcalib_press_max[0][1] - sys.para.forkcalib_press_min[0][1];
    p2_hyst = sys.para.forkcalib_press_max[1][1] - sys.para.forkcalib_press_min[1][1];
    p3_hyst = sys.para.forkcalib_press_max[2][1] - sys.para.forkcalib_press_min[2][1];
    p4_hyst = sys.para.forkcalib_press_max[3][1] - sys.para.forkcalib_press_min[3][1];

    if((can_p1_cnt > sys.para.forkcalib_press_max[0][1]-p1_hyst)&&(can_p2_cnt > sys.para.forkcalib_press_max[1][1]-p2_hyst)&&
       (can_p3_cnt > sys.para.forkcalib_press_max[2][1]-p3_hyst)&&(can_p4_cnt > sys.para.forkcalib_press_max[3][1]-p4_hyst))
    {
        otg_p1_ok_flag = 0;     //One flag is enough to check status
    }
    else
    {
        otg_p1_ok_flag = 1;
    }  
}

void Tilt_Monitor(void)
{
    ANGLE_STR ang;
//    char tbuf[50];
        
    ang.LowBmAngle = TILT_MIN_ANGLE;
    ang.HighBmAngle = TILT_MAX_ANGLE;
    ang.BAHighAdcCount = 4075;
    
    ang.Adccnt = Tilt_1_X_cnt;
    ang.BALowAdcCount = sys.para.Tilt1_X_MinAdc;
    TiltAngle_1_X = Calculate_Boom_Angle(ang);
    prv_X_cnts = Tilt_1_X_cnt;
    
    ang.Adccnt = Tilt_1_Y_cnt;
    ang.BALowAdcCount = sys.para.Tilt1_Y_MinAdc;
    TiltAngle_1_Y = Calculate_Boom_Angle(ang);
    prv_Y_cnts = Tilt_1_Y_cnt;
    
    temp_Tilt1X = abs(TiltAngle_1_X);
    temp_Tilt1Y = abs(TiltAngle_1_Y);
    
    if((temp_Tilt1X <= TILT_MAX_ANGLE)&&(temp_Tilt1Y<= TILT_MAX_ANGLE))
    {
        if((temp_Tilt1X > sys.para.Front_tilt_Cutoff)||(temp_Tilt1Y > sys.para.Front_tilt_Cutoff)) 
        {
            if(temp_Tilt1X >= sys.para.Front_tilt_Cutoff)
            {
                tilt1X_ok_flag = 1;
//                sprintf(tbuf,"TiltAngle_1_X=%d temp_Tilt1X=%d\r\n",TiltAngle_1_X,temp_Tilt1X);
//                UART_Send_String(UART_MODULE1,tbuf);
//                sprintf(tbuf,"Tilt_1_X_cnt=%d Tilt_1_Y_cnt=%d\r\n",Tilt_1_X_cnt,Tilt_1_Y_cnt);
//                UART_Send_String(UART_MODULE1,tbuf);
            }
            else
            {
                tilt1Y_ok_flag = 1;
//                sprintf(tbuf,"TiltAngle_1_Y=%d temp_Tilt1Y=%d\r\n",TiltAngle_1_Y,temp_Tilt1Y);
//                UART_Send_String(UART_MODULE1,tbuf);
//                sprintf(tbuf,"Tilt_1_X_cnt=%d Tilt_1_Y_cnt=%d\r\n",Tilt_1_X_cnt,Tilt_1_Y_cnt);
//                UART_Send_String(UART_MODULE1,tbuf);
            }
        }
        else
        {
            if(temp_Tilt1X < sys.para.Front_tilt_Cutoff)   tilt1X_ok_flag = 0;
            if(temp_Tilt1Y < sys.para.Front_tilt_Cutoff)   tilt1Y_ok_flag = 0;
        }
    }
    if((TiltAngle_1_X >= sys.para.Front_tilt_Cutoff*(-1))&&(TiltAngle_1_X <= sys.para.Front_tilt_Cutoff))
        angleX_per = (int8_t)map(TiltAngle_1_X, sys.para.Front_tilt_Cutoff*(-1), sys.para.Front_tilt_Cutoff, -100.0, 100.0);
    else if(TiltAngle_1_X < sys.para.Front_tilt_Cutoff*(-1))
        angleX_per = -100;
    else if(TiltAngle_1_X > sys.para.Front_tilt_Cutoff)
        angleX_per = 100;

    if((TiltAngle_1_Y >= sys.para.Front_tilt_Cutoff*(-1))&&(TiltAngle_1_Y <= sys.para.Front_tilt_Cutoff))
        angleY_per = (int8_t)map(TiltAngle_1_Y, sys.para.Front_tilt_Cutoff*(-1), sys.para.Front_tilt_Cutoff, -100.0, 100.0);
    else if(TiltAngle_1_Y < sys.para.Front_tilt_Cutoff*(-1))
        angleY_per = -100;
    else if(TiltAngle_1_Y > sys.para.Front_tilt_Cutoff)
        angleY_per = 100;
}
/*============================================================================*/
/*
 * Function      : Fork_Height.
 * Description   : Used to find fork height.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Fork_Height(void)
{
    float Alpha2;
//    char mbuf[10];
    
    if(sys.para.cal_len_max_cnt > sys.para.cal_len_min_cnt)
    {
        if(len_adc_cnt > sys.para.cal_len_min_cnt)
        {
            ht_adc_cnt = len_adc_cnt - sys.para.cal_len_min_cnt;                
        }
        else
        {
            ht_adc_cnt = 0;
        }
        BLFact = (float)((sys.para.cal_len_max - sys.para.cal_len_min)*1.0)/(sys.para.cal_len_max_cnt - sys.para.cal_len_min_cnt);            
    }
    else if(sys.para.cal_len_min_cnt > sys.para.cal_len_max_cnt)
    {
        if(len_adc_cnt < sys.para.cal_len_min_cnt)
        {
            ht_adc_cnt = sys.para.cal_len_min_cnt - len_adc_cnt;
        }
        else
        {
            ht_adc_cnt = 0;
        }
        BLFact = (float)((sys.para.cal_len_max - sys.para.cal_len_min)*1.0)/(sys.para.cal_len_min_cnt - sys.para.cal_len_max_cnt);
    }
    Alpha2 = ((float)sys.para.cal_len_min + (BLFact*(float)ht_adc_cnt));
    
//    sprintf(mbuf,"%.3f",BLFact);
//    LCDPutStr(mbuf,10,80, SMALL,ILI9341_NAVY,ILI9341_WHITE);
//    sprintf(mbuf,"%04d",ht_adc_cnt);
//    LCDPutStr(mbuf,10,90, SMALL,ILI9341_NAVY,ILI9341_WHITE);
//    sprintf(mbuf,"%04d",len_adc_cnt);
//    LCDPutStr(mbuf,10,100, SMALL,ILI9341_NAVY,ILI9341_WHITE);
//    sprintf(mbuf,"%.2f",Alpha2);
//    LCDPutStr(mbuf,10,110, SMALL,ILI9341_NAVY,ILI9341_WHITE);
    
    Alpha2 = RoundOff(Alpha2);
    bm_length = (uint16_t)Alpha2;
//    bm_length = (uint16_t)(sys.para.cal_len_min + (BLFact*(float)len_adc_cnt)); 

    Length_Correction_Forklift();

    TotalBmLength = bm_length;
}

/*============================================================================*/
/*
 * Function      : Check_Errors_In_AR.
 * Description   : Used to find any errors regarding A2B-Angle-Radius.
 * Parameters    : None.
 * Return        : True/False.
*/
/*============================================================================*/
uint8_t Check_Errors_In_AR(void)
{
    uint8_t stat = 0;
    static uint8_t SlewMode_BmAngle=0;
    
    if(CapCalMethodSwitch == 0)
    {
        if(sys.para.Select_System == FORK_LIFT)
        {
            return 0;
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM))
        {
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
            {
                if((Radius1 > (LowNlzRad-1))&&(Radius1 < (HighNlzRad+1)))
                {
                    stat = 0;
                }
                else 
                {
                    stat = 1;                
                    op.nlzledaction = OUTPUT_ON;
                    if((Radius1 < LowNlzRad))
                    {
                        condition = 2;
                        load_stat = LOAD_LOW_NLZ; 
                    }
                    else if((Radius1 > HighNlzRad))
                    {
                        condition = 3;
                        load_stat = LOAD_HIGH_NLZ; 
                    }
                }
            }
            else
            {
                if((Radius1 > (LowNlzRad-1))&&(Radius1 < (HighNlzRad+1))&&(HookHight <= sys.para.Max_BLength))
                {
                    stat = 0;
                }
                else
                {
                    stat = 1;
                    op.nlzledaction = OUTPUT_ON;
                    if((Radius1 < LowNlzRad))
                    {
                        condition = 2;
                        load_stat = LOAD_LOW_NLZ; 
                    }
                    else if((Radius1 > HighNlzRad))
                    {
                        condition = 3;
                        load_stat = LOAD_HIGH_NLZ; 
                    }
                }
            }
            return stat;
        }
        else if(sys.para.Select_System == ACE_NX360)
        {
            // In Slew Mode Boom Angle Should be greater than 5 degree. . . . 
            //Other wise NLZ condition will Activate
            if(((SlewMode==0)&&(!Slew_CAN))||((SlewMode!=0)&&(bm_angle>59)&&(Slew_CAN)))
            {
                SlewMode_BmAngle= 1;  
            }
            else
            {
                SlewMode_BmAngle= 0;  
            }
        }
        else
        {
            SlewMode_BmAngle = 1;  
            
            if((sys.para.obtilt_enable_bit)&&(sys.para.Select_System == TELESCOPIC_RT40))
            {
                if((tilt1X_ok_flag)||(tilt1Y_ok_flag))
                {
                    stat = 1;
                    op.nlzledaction = OUTPUT_ON;
                    return stat;
                }
                else if((art_ip_bit)&&(OTG_status)&&((sys.para.duty == 1)||(sys.para.duty == 2)))
                {
                    stat = 1;
                    return stat;
                }
                else if((art_ip_bit == 0)&&(OTG_status)&&((sys.para.duty == 1)||(sys.para.duty == 2)))
                {
                    stat = 1;
                    return stat;
                }
                else if((art_ip_bit == 0)&&(OTG_status == 0)&&(sys.para.duty == 3))
                {
                    stat = 1;
                    return stat;
                }
            }
        }
        if((Radius1 > (LowNlzRad-1))&&(Radius1 < (HighNlzRad+1))&&(bm_angle > sys.para.low_cutoff_angl)&&(bm_angle < ((int16_t)sys.para.hi_cutoff_angl*10))&&(Radius1 > sys.para.Radius_Cutoff)&&(SlewMode_BmAngle==1))                              
        {
            stat = 0;
        }
        else 
        {
            stat = 1;
            
            if((Radius1 < LowNlzRad))
            {
                condition = 2;
                load_stat = LOAD_LOW_NLZ; 
            }
            else if((Radius1 > HighNlzRad))
            {
                condition = 3;
                load_stat = LOAD_HIGH_NLZ; 
            }
            else if(Radius1 <= sys.para.Radius_Cutoff)
            {
                load_stat = LOAD_RADIUS_CUTOFF;
            }
            else if(bm_angle <= sys.para.low_cutoff_angl)
            {
                load_stat = LOAD_LOANG_CUTOFF;
            }
            else if(bm_angle >= ((int16_t)sys.para.hi_cutoff_angl*10))
            {
                load_stat = LOAD_HIANG_CUTOFF;
            }
            
            if((a2b_stat == 0))  op.nlzledaction = OUTPUT_ON;
        }
    }
    else
    {
        if((bm_angle < (cap_angle +1)) && (bm_angle >= (hi_cap_angle)))
        {
            stat = 0;
        }
        else 
        {
            stat = 1;
            if((a2b_stat == 0))  op.nlzledaction = OUTPUT_ON;
        }
    }
    return stat;
}

uint8_t Check_Flags(void)
{
    if((tilt1X_ok_flag == 0)&&(tilt1Y_ok_flag == 0)&&(otg_p1_ok_flag == 0))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*============================================================================*/
/*
 * Function      : Calculate_Len_Radius.
 * Description   : Used to calculate length and radius.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Calculate_Len_Radius(void)
{
    DCT dt;
    DT tbl;
    BML bl;
    MOVINGBL mbl;
    DTD dty_dat;
    NLZR rad;
    float Alpha2;
    uint16_t TempoAngle=0;
    int16_t temp_offset=0;
    double Hook_height=0.0;
    double Sin_Angle=0.0,Angle_double=0.0;
    
    if((sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
    {
        if(sys.para.duty == 0 || sys.para.duty > lc_total_duty)
        {
            sys.para.duty = 1;
        }
    }
    
    if(sys.para.Select_System != ACE_NX360)
    {
        dt.dc_page_s = lc_duty_cycle_page_s;
        dt.dty = sys.para.duty;
        dt.mem_offset = flash_memory_offset;
    }
    else if(sys.para.Select_System == ACE_NX360)
    {
        dt.dc_page_s = lc_duty_cycle_page_s;
        
        if(art_ip_bit == 0)
            dt.dty = sys.para.duty;
        else
            dt.dty = sys.para.duty+lc_total_duty;
        dt.mem_offset = flash_memory_offset;
    }
    //Start and end duty table number...
    duty_table      = Duty_Table(DT_START,dt);
    End_duty_table  = Duty_Table(DT_END,dt);
    
//    sprintf(dbuf,"duty_table_1=%d\r\n",duty_table);
//    UART_Send_String(UART_MODULE1,dbuf);
    
    if(sys.para.Select_System == PNC_FORK)
    {
        if(sys.para.duty == sys.para.fork_duty) duty_table = End_duty_table+1;  //This is to skip the change in duty table while calculating TotalBmLength and go for moving hook even if fork duty has single duty table.
        //eg. if duty_table = 10 then make it 11
    }
    
    if(sys.para.Select_System != FORK_LIFT)
    {
        //Duty table data...
        tbl.dt_page_s = lc_duty_table_page_s;
        tbl.startdty_tbl = duty_table;
        tbl.mem_offset = flash_memory_offset;
        dty_dat = Duty_Table_Data(tbl);
        
        JibLength          = dty_dat.jiblen;
        CapCalMethodSwitch = dty_dat.ccm_sw;
        cap_angle          = dty_dat.lo_cap_ang;
        hi_cap_angle       = dty_dat.hi_cap_ang;
        
        if(duty_table == End_duty_table)  //If single table means Fixed HOOK or Extra Jib attached
        {
            bl.dt_page_s = lc_duty_table_page_s;
            bl.startdty_tbl = duty_table;
            bl.d.mem_offset = flash_memory_offset;
            bl.jiblen = JibLength;
            
            TotalBmLength = Fixed_Hook_BMLen(bl);
        }
        else                            //If multiple table means movable hook
        {
            bl.dt_page_s = lc_duty_table_page_s;
            bl.startdty_tbl = duty_table;
            bl.enddty_tbl = End_duty_table;
            bl.d.mem_offset = flash_memory_offset;
            bl.d.dty = sys.para.duty;
            bl.def_dty = sys.para.default_duty;
            bl.lc_nobp = lc_num_of_bm_part;
            bl.bmlen = bm_length;
            bl.bmlenmin = sys.para.bm_length_min;
            bl.jiblen = JibLength;
            
            mbl = Moving_Hook_BMLen(bl);
            duty_table = mbl.startdty_tbl;
            TotalBmLength = mbl.blen;
        }
    }
    
    if(sys.para.Select_System == PNC_FORK) 
    {
        if(sys.para.duty == sys.para.fork_duty)
        {
            if((TotalBmLength >= sys.para.cal_len_min)&&(TotalBmLength <= sys.para.bm_length_max))   
                //eg. Incremented duty_table = 11, decrement to  10 to work in min-max boom length 
                duty_table = End_duty_table;  //Restore duty table to original start duty table of fork duty.
            else  
                //eg. Incremented duty_table = 11, decrement to  9 to work with previous duty table which has more working range of radius
                duty_table = End_duty_table-1;  //If length goes beyond the maximum length then choose duty table just before the actual duty table of fork duty table.
        }
    }
    
    //Read low and high no load zone radiuses
    tbl.dt_page_s    = lc_duty_table_page_s;
    
    if(sys.para.Select_System == ACE_NX360)
    {
        tbl.startdty_tbl = duty_table;
    }
    else
    {
        if((lc_art_table_switch == 1)&&(art_ip_bit == 1))
            tbl.startdty_tbl = lc_art_dty_tbl+duty_table-1;
        else
            tbl.startdty_tbl = duty_table;
    }
    
    tbl.mem_offset   = flash_memory_offset;
    rad = No_Load_Zone_Radius(tbl);
    
    LowNlzRad  = rad.lo_nlzr;
    HighNlzRad = rad.hi_nlzr;
    
    if((sys.para.Select_System != FORK_LIFT)&&(sys.para.Select_System != PALFINGER_KNUCKLE_BOOM))
    {
        if(sys.para.Select_System == ACE_NX360)
        {
            if(SlewMode == 0)
                temp_offset = sys.para.bm_offset;
            else
                temp_offset = sys.para.slew_offset;
        }
        else  temp_offset = sys.para.bm_offset;
        
        if(bm_angle < 900)
            Alpha2 = Flot_Calculate_Boom_Radius(bm_angle,TotalBmLength,temp_offset);                
        Alpha2 = RoundOff(Alpha2);
        Radius1 = (uint16_t)Alpha2;
//        Radius1 = Calculate_Boom_Radius(bm_angle,TotalBmLength,temp_offset);  //Redius calculated here only
    }
    else if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
    {
        RAD = 0.0;
        
        if(Knbm_angle < 900)
            TempoAngle = (abs(Knbm_angle))/10;
        
        if(TempoAngle > 90) TempoAngle = 90;
        
        Radius = (float)(TotalBmLength-JibLength) * cos(((double)TempoAngle*3.14)/180.0);
        Radius += (float)sys.para.bm_head_offset * sin(((double)TempoAngle*3.14)/180.0);

        if(JibLength > 0)
        {
            if(DispBoomAngle1 < 0)          DispBoomAngle1 = 0;
            else if(DispBoomAngle1 > 90)    DispBoomAngle1 = 90;
            Alpha2 = (float)(JibLength) * cos(((double)DispBoomAngle1*3.14)/180.0);
        }
        
        //Round up
        Radius1 = (uint16_t)((Radius + Alpha2)*10 + 0.5)/10 + sys.para.bm_offset;

        if(Radius1 > 999)
        {
            Radius1 = 0;
        }
    }
    else if(sys.para.Select_System == FORK_LIFT)
    {
        Radius1 = TotalBmLength;
    }

    if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2)||(sys.para.Select_System == WHITELINE_ESCORTS))
    {
        if(sys.para.hk_height_stat_bit)
        {
            Angle_double    = (double)(TempDispBoomAngle);
            Sin_Angle       = sin((Angle_double*3.14)/180);    //degree = radian * (180/pi)
            Hook_height     = (TotalBmLength*Sin_Angle);
            HookHight       = (uint16_t)Hook_height;

            HookHight = (HookHight + sys.para.bm_ht_offset);
        }
        else
        {
            HookHight = 0;
        }
    }
}


/*============================================================================*/
/*
 * Function      : CheckLoadVal.
 * Description   : Used to calculate safe working load and apply state machines for load.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void CheckLoadVal(void)
{
    uint16_t TempCAP=0;
    float fiveper=0,fifteenper=0,twentyfiveper=0,Fiftyper=0,seventyfiveper=0;
    SWL wl;
    SNATCHBLK sb;
    
    if(sys.para.Select_System == FORK_LIFT)
    {
        wl.art_tbl_sw       = 0;
        wl.art_ip           = 0;
        wl.d.dc_page_s      = 0;
        wl.d.mem_offset     = flash_memory_offset;
        wl.art_page_s       = 0;
        wl.dt_page_s        = lc_duty_table_page_s;
        wl.startdty_tbl     = duty_table;
        
        if((bm_length > 0)&&(bm_length <= sys.para.cal_len_max))    wl.curr_radius = bm_length;
        else if(bm_length > sys.para.cal_len_max)                   wl.curr_radius = sys.para.cal_len_max;
        else if(bm_length == 0)                                     wl.curr_radius = 1;
        
        wl.curr_ang         = 0;
        wl.ccm_sw           = 0;
        wl.art_derat_perc   = 0;
    }
    else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
    {
        wl.art_tbl_sw       = 0;
        wl.art_ip           = 0;
        wl.d.dc_page_s      = lc_duty_cycle_page_s;
        wl.d.mem_offset     = flash_memory_offset;
        wl.art_page_s       = 0;    
        wl.dt_page_s        = lc_duty_table_page_s;
        wl.startdty_tbl     = duty_table;
        wl.curr_radius      = Radius1;
        wl.curr_ang         = bm_angle;
        wl.ccm_sw           = 0;
        wl.art_derat_perc   = 0;
    }
    else if(sys.para.Select_System == ACE_NX360)
    {
        wl.art_tbl_sw       = 0;
        wl.art_ip           = 0;    //handled this in initial stage were we have taken start and end duty cycles
        wl.d.dc_page_s      = lc_duty_cycle_page_s;
        wl.d.mem_offset     = flash_memory_offset;
        wl.art_page_s       = lc_art_table_page_s;
        wl.dt_page_s        = lc_duty_table_page_s;
        wl.startdty_tbl     = duty_table;
        wl.curr_radius      = Radius1;
        wl.curr_ang         = bm_angle;
        wl.ccm_sw           = CapCalMethodSwitch;
        wl.art_derat_perc   = sys.para.art_derate_perc;
        if(sys.para.art_enable_bit)
        {
            wl.art_derat_perc   = sys.para.indopower_art_derate[sys.para.duty-1];
        }
    }
    else
    {
        wl.art_tbl_sw       = lc_art_table_switch;
        wl.art_ip           = art_ip_bit;
        wl.d.dc_page_s      = lc_duty_cycle_page_s;
        wl.d.mem_offset     = flash_memory_offset;
        wl.art_page_s       = lc_art_table_page_s;
        wl.dt_page_s        = lc_duty_table_page_s;
        wl.startdty_tbl     = duty_table;
        wl.curr_radius      = Radius1;
        wl.curr_ang         = bm_angle;
        wl.ccm_sw           = CapCalMethodSwitch;
        wl.art_derat_perc   = sys.para.art_derate_perc;
        if(sys.para.art_enable_bit)
        {
            wl.art_derat_perc   = sys.para.indopower_art_derate[sys.para.duty-1];
        }
    }
//    sprintf(lbuf,"duty_table=%d art_tab_sw=%d art_ip=%d\r\n",duty_table,lc_art_table_switch,art_ip_bit);
//    UART_Send_String(UART_MODULE1,lbuf);
    
    Cap1 = Safe_Working_Load(wl);
    
    if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
    {
        fiveper         = Cap1*0.05;
        fifteenper      = Cap1*0.15;
        twentyfiveper   = Cap1*0.25;
        Fiftyper        = Cap1*0.5;
        seventyfiveper  = Cap1*0.75;

        if(DispLoadVal > fiveper && DispLoadVal <= fifteenper)              DispLoadVal = DispLoadVal + sys.para.load_corr1;
        else if(DispLoadVal > fifteenper && DispLoadVal <= twentyfiveper)   DispLoadVal = DispLoadVal + sys.para.load_corr2;	
        else if(DispLoadVal > twentyfiveper && DispLoadVal <= Fiftyper)     DispLoadVal = DispLoadVal + sys.para.load_corr3;
        else if(DispLoadVal > Fiftyper && DispLoadVal <= seventyfiveper)    DispLoadVal = DispLoadVal + sys.para.load_corr4;
        else if(DispLoadVal > seventyfiveper)                               DispLoadVal = DispLoadVal + sys.para.load_corr5;

        DispLoadVal = (DispLoadVal + sys.para.hook_load);       
    }    
    
    if((sys.para.Select_System != FORK_LIFT)&&(sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
    {
        if((sys.para.Select_System == ACE_MANBASKET_HXP)&&(sys.para.duty == sys.para.manbas_duty)){}
        else if((sys.para.Select_System == TIL_PIXEF_TELE_PNC)&&(sys.para.duty == 1)){} //Spacial case TIL pixef telescopic PNC crane, in which duty 1 has capacity more than default hook
        else
        {
            sb.dt_page_s    = lc_duty_table_page_s;
            sb.startdty_tbl = duty_table;
            sb.falls_cnt    = sys.para.falls_cnt;
            sb.falls_page_s = lc_falls_page_s;
            sb.capacity     = Cap1;
            sb.mem_offset   = flash_memory_offset;
            TempCAP = SnatchBlock_Dty_Capacity(sb);
            if(TempCAP > 0)
                Cap1 = TempCAP;
        }
    }
        
    SafeLimit        = (float)(Cap1*sys.para.sp1_perc);
    SafeLimit        = (SafeLimit/100.0);
    ApproachLimit    = (float)(Cap1*sys.para.sp2_perc);
    ApproachLimit    = (ApproachLimit/100.0);
    CutoffLimit      = (float)(Cap1*sys.para.sp3_perc);
    CutoffLimit      = (CutoffLimit/100.0);
    OverLoadLimit    = (float)(Cap1*sys.para.sp4_perc);
    OverLoadLimit    = (OverLoadLimit/100.0);
    
    if((DispLoadVal < ApproachLimit))   //Safe condition
    {
        op.nlzledaction = OUTPUT_OFF;
        
        if(sys.para.fail_safe_stat_bit == 0) op.relay1action = OUTPUT_OFF;
        else                                 op.relay1action = OUTPUT_ON;
        
//        if((sys.para.Select_System != ACE_NX360)&&(sys.para.Select_System != TMC_MANBASKET))
//        {
//            if(sys.para.fail_safe_stat_bit == 0) 
//            {
//                op.relay2action = OUTPUT_OFF;
//            }
//            else
//            {
//                op.relay2action = OUTPUT_ON;
//            }
//        }
        
        op.hooteraction = OUTPUT_OFF;
        
//        PercLoad = (uint8_t)map(DispLoadVal,0,ApproachLimit,0,68);
//        Set_Bargraph_Percent(PercLoad);
        
        condition = 0;//Telematics Data on UART
        load_stat = LOAD_SAFE;
        
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            op.artledaction = OUTPUT_OFF;               //Overload led
        op.buzzaction = OUTPUT_OFF;
        can_buzz_stat = OUTPUT_OFF;
        tower_lamp_out |= TL_GREEN_LAMP;
        tower_lamp_out &= ~TL_AMBER_LAMP;
        tower_lamp_out &= ~TL_RED_LAMP;
    }
    else if((DispLoadVal >= ApproachLimit) && (DispLoadVal < CutoffLimit))  //Approach condition
    {
//        op.buzzaction = OUTPUT_ON;
        op.nlzledaction = OUTPUT_OFF;
        
        if(sys.para.fail_safe_stat_bit == 0) op.relay1action = OUTPUT_OFF;
        else                                 op.relay1action = OUTPUT_ON;
        
//        if((sys.para.Select_System != ACE_NX360)&&(sys.para.Select_System != TMC_MANBASKET))
//        {
//            if(sys.para.fail_safe_stat_bit == 0) 
//            {
//                op.relay2action = OUTPUT_OFF;
//            }
//            else
//            {
//                op.relay2action = OUTPUT_ON;
//            }
//        }
        
        op.hooteraction = OUTPUT_OFF;
//        PercLoad = (uint8_t)map(DispLoadVal,ApproachLimit,CutoffLimit,68,81);
//        Set_Bargraph_Percent(PercLoad);
        
        condition = 0;//Telematics Data on UART
        load_stat = LOAD_APPROACH;
        
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            op.artledaction = OUTPUT_OFF;               //Overload led
        op.buzzaction = OUTPUT_BLINK;
        can_buzz_stat = OUTPUT_BLINK;
    }
    else if((DispLoadVal >= CutoffLimit) && (DispLoadVal <= OverLoadLimit))  //Overload with bypass condition
    {
//        op.buzzaction = OUTPUT_ON;
        op.nlzledaction = OUTPUT_OFF;
        
        if(sys.para.hootr_rly_stat_bit == 1) op.hooteraction = OUTPUT_ON;
        
        if(sys.para.Select_System != WHITELINE_ESCORTS)             //V1.17.1
        {
            Bypasskey_Action();
//            UART_Send_String(UART_MODULE1,"Bypasskey_Action4\r\n");
        }
//        else
//        {
//            
//        }
        
//        PercLoad = (uint8_t)map(DispLoadVal,CutoffLimit,OverLoadLimit,81,90);
//        Set_Bargraph_Percent(PercLoad);
        condition = 1;//Telematics Data on UART
        load_stat = LOAD_OVRLOAD_WITH_BP;
        
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            op.artledaction = OUTPUT_ON;               //Overload led
        
        
//        op.buzzaction = OUTPUT_ON;
    }
    if((DispLoadVal > OverLoadLimit))                         //Overload no bypass condition
    {
//        op.buzzaction = OUTPUT_ON;
        op.nlzledaction = OUTPUT_OFF;
        
        if(sys.para.fail_safe_stat_bit == 0) 
        {
            if(sys.para.bmdwn_rly_stat_bit == 1) op.relay1action = OUTPUT_ON;
        }
        else if(sys.para.bmdwn_rly_stat_bit == 1) op.relay1action = OUTPUT_OFF;
        
//        if((sys.para.Select_System != ACE_NX360)&&(sys.para.Select_System != TMC_MANBASKET))
//        {
//            if(sys.para.fail_safe_stat_bit == 0) 
//            {
//                if(sys.para.bmup_rly_stat_bit == 1) op.relay2action = OUTPUT_ON;
//            }
//            else
//            {
//                if(sys.para.bmup_rly_stat_bit == 1) op.relay2action = OUTPUT_OFF;
//            }
//        }
        
        if(sys.para.hootr_rly_stat_bit == 1)      op.hooteraction = OUTPUT_ON; 
        
//        if(DispLoadVal > (OverLoadLimit+2)) PercLoad = 100;
//        else                                PercLoad = (uint8_t)map(DispLoadVal,CutoffLimit,OverLoadLimit,90,100);
//        Set_Bargraph_Percent(PercLoad);
        condition = 1;//Telematics Data on UART
        load_stat = LOAD_OVRLOAD_CUTOFF;
        
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            op.artledaction = OUTPUT_ON;               //Overload led
        op.buzzaction = OUTPUT_ON;
        can_buzz_stat = OUTPUT_ON;
    }
    if((a2b_stat)&&(sys.para.Select_System != FORK_LIFT))
    {
        op.buzzaction = OUTPUT_BLINK;
        condition = 4;
        Bypasskey_Action();
//        UART_Send_String(UART_MODULE1,"Bypasskey_Action5\r\n");
        load_stat = LOAD_A2B_CUTOFF;
    }
    Bar_Graph_Disp();
}


/*============================================================================*/
/*
 * Function      : Manbasket_Load_Cal_Func.
 * Description   : Used to calculate man-basket load.
 * Parameters    : lc_cnt: Loadcell counts.
 * Return        : None.
*/
/*============================================================================*/
void Manbasket_Load_Cal_Func(uint16_t lc_cnt)
{
    float loadcell_fact=0,round;
    
    if(lc_cnt <= sys.para.manbasket_min_cnt+10)       //can_loadcell_cnt
    {
        DispLoadVal = 0;
        peakcnt = 0;
        peakDispLoadVal = 0;
    }
    else
    {
        loadcell_fact = (float)((sys.para.manbasket_max - sys.para.manbasket_min)*1.0)/(sys.para.manbasket_max_cnt - sys.para.manbasket_min_cnt);
        
        CalcLoad = (loadcell_fact*(lc_cnt-sys.para.manbasket_min_cnt));
        
        round = RoundOff(CalcLoad);
        
        DispLoadVal = (uint16_t)round;
        
        if(sys.para.peaknhold_stat_bit)     //Spacial case for Terex FR17 crane
        {
            Apply_PickNhold_Logic();
        }
    }
}


/*============================================================================*/
/*
 * Function      : Apply_PickNhold_Logic.
 * Description   : Used to apply pick and hold logic.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Apply_PickNhold_Logic(void)
{
    if(DispLoadVal > sys.para.load_threshold+2)
    {
        if((peakcnt < 10)&&(load_peak_Tout == 0))
        {
            load_peak_Tout = 500;
            if(peakDispLoadVal < DispLoadVal)
            {
                peakDispLoadVal = DispLoadVal;
                p1peak = p1_pressure_cnt;
                p2peak = p2_pressure_cnt;                    
            }
            peakcnt++;
        }
    }
    if(DispLoadVal <= (1+sys.para.hook_load))
    {
        if((p1_pressure_cnt < p1peak)&&(p2_pressure_cnt < p2peak))
	    {
            peakcnt = 0;
            peakDispLoadVal = 0;
            p1peak = 0;
            p2peak = 0;
            up_dn_dir = 0;
        }
    }
    DispLoadVal = (peakDispLoadVal + sys.para.hook_load);
}

/*============================================================================*/
/*
 * Function      : Apply_Load_Corrections.
 * Description   : Used to apply any correction is applicable to load.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Apply_Load_Corrections(void)
{
    uint16_t tempcntr=0,TempTest;
  
    if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
    {
        if(DispBoomAngle1 >= 5 && DispBoomAngle1 < 30)
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr1);
        }	
        else if(DispBoomAngle1 >= 30 && DispBoomAngle1 < 40)
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr2);
        }			
        else if(DispBoomAngle1 >= 40 && DispBoomAngle1 < 60)  //if(DispLoadVal >= (40) && DispLoadVal < (90))
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr3);
        }	
        else if(DispBoomAngle1 >= 60 && DispBoomAngle1 < 70) //if(DispLoadVal >= (90)&& DispLoadVal < (120))
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr4);
        }
        else if(DispBoomAngle1 >= 70) //if(DispLoadVal >= (120))
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr5);
        }
    }
    else
    {
        if(sys.para.Select_System == TIL_PIXEF_TELE_PNC)
        {
            if(DispLoadVal > (2) && DispLoadVal < (20))
            {
                DispLoadVal = (DispLoadVal + sys.para.load_corr1);
            }
        }
        else
        {
            if(DispLoadVal >= (6) && DispLoadVal < (20))
            {
                DispLoadVal = (DispLoadVal + sys.para.load_corr1);
            }
        }

        if(DispLoadVal >= (20) && DispLoadVal < (40))
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr2);
        }

        if(DispLoadVal >= (40) && DispLoadVal < (90))
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr3);
        }

        if(DispLoadVal >= (90)&& DispLoadVal < (120))
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr4);
        }

        if(DispLoadVal >= (120))
        {
            DispLoadVal = (DispLoadVal + sys.para.load_corr5);
        }
    }

    if(sys.para.perc_fact_stat_bit == 1)
    {
        if(DispLoadVal > sys.para.correction_load)
        {
            if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
            {
                TempDispBoomAngle = (abs(Knbm_angle))/10;
            }
            else
            {
                TempDispBoomAngle = (bm_angle/10);
            }
            //TempTest = (TempDispBoomAngle*((/*Fact/10000.0*/0.0033)*(DispLoadVal)));
            TempTest = (TempDispBoomAngle*((sys.para.fact/10000.0)*(DispLoadVal)));
            DispLoadVal = (DispLoadVal - TempTest);
            //DispLoadVal = (DispLoadVal - (TempDispBoomAngle*((/*Fact/10000.0*/0.0033)*(DispLoadVal/10.0))));
        }
    }

    if((sys.para.load_avg_stat_bit == 1) && (sys.para.load_avg_val == 0))
    {
        sys.para.load_avg_val = 3;
    }

    if(sys.para.load_avg_stat_bit == 1)
    {
        DispLoadArr[SpdCntr] = DispLoadVal;
        DispLoadVal = 0;
        for(tempcntr=0; tempcntr < sys.para.load_avg_val; tempcntr++)
        {
            DispLoadVal = (DispLoadVal + DispLoadArr[tempcntr]);
        }
        DispLoadVal = (DispLoadVal/sys.para.load_avg_val);

        SpdCntr++;
        if(SpdCntr >= sys.para.load_avg_val)
        {
            SpdCntr =0;
        }
    }
    
    if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
    {
        
    }
    else
    {
        if(TempDispBoomAngle == 0)
            DispLoadVal = sys.para.hook_load;
        if(bm_angle < 0)
        {
            DispLoadVal = sys.para.hook_load;
        }
    }
    
    //Below functionality is provided for load, if load gets drastically inc/dec. By enabling freeze load menu and set angle at which load need to be freeze in site engg menu. 
    if(sys.para.frz_load_angl_bit)                                              //V1.17.3 Dt:07/07/23
    {
        if(bm_angle < (sys.para.set_angle_frz_lod*10))
        {
            frz_DispLoadVal = DispLoadVal;
        }
        else if(bm_angle > (sys.para.set_angle_frz_lod*10))
        {
            DispLoadVal = frz_DispLoadVal;
        }
    }
     
    if(sys.para.snatch_block_stat_bit == 1)
    {
        if(sys.para.duty <= lc_total_duty)
        {
            if(DispLoadVal > (sys.para.snatch_block_val+sys.para.hook_load) && SnatchBlockflag == 0)
            {
                SnatchBlockflag = 1;
            }
            if(DispLoadVal < (sys.para.snatch_block_val+sys.para.hook_load) && SnatchBlockflag == 1)
            {
                SnatchBlockflag = 0;
                sys.para.duty = sys.para.default_duty;
#ifdef DISPLAY_16x2
                
#else 
#ifdef DISPLAY_TFT32
                if(menu_stat == DEFAULT_PAGE)
                    Display_Duty_Hint_MainScreen();
#else
#ifdef DISPLAY_192x64
        
#endif
#endif
#endif
            }
        }
    }
}


void Get_Radius_Capacity(uint16_t d_table, uint8_t cnt)
{
    uint16_t R_Offset=40,C_Offset=184;
    
    flash_page_addr = (((uint32_t)lc_duty_table_page_s-1)*256)+(((uint32_t)d_table-1)*256)+flash_memory_offset;
    vrad  = (SPIFlash_Read_Byte(flash_page_addr+R_Offset+(cnt*2))*256) + SPIFlash_Read_Byte(flash_page_addr+R_Offset+(cnt*2)+1);
    vcapa = (SPIFlash_Read_Byte(flash_page_addr+C_Offset+(cnt*2))*256) + SPIFlash_Read_Byte(flash_page_addr+C_Offset+(cnt*2)+1);
}


//==================================EOF=========================================