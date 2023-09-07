
#include "main.h"

extern mID can_tx,can_rx;
//char  sys_sr_no[150];
char sys_buf[150];

void ESP_Delay(uint16_t d)
{
    uint16_t i,j;
    
    for(i=0; i<d; i++)
    {
        for(j=0; j<5; j++){}
    }
}

void ESP32_Handler(void)
{
    char esp_buf[100];
    
//    if(onscreen_data_tout == 0)
//    {
//        if(test_mode == 0)
//        {
//            sprintf(esp_buf,"{,OD,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,}\r\n",sys.para.duty,Cap1,TotalBmLength,bm_angle,Radius1,DispLoadVal,load_stat,sys_err,sys.para.sel_uom,sys.para.Select_System);
//            UART_Send_String(UART_MODULE2,esp_buf);
//        }
//        else if(test_mode == 1) //Testing data
//        {
//            sprintf(esp_buf,"{,TD,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,}\r\n",p1_pressure_cnt,p2_pressure_cnt,len_adc_cnt,ang_adc_cnt,can_p1_cnt,can_p2_cnt,can_p3_cnt,can_p4_cnt,can_loadcell_cnt,len_avg_cnt,a2b_stat,art_ip_bit,spare_in_bit,OTG_status);
//            UART_Send_String(UART_MODULE2,esp_buf);
//        }
//        onscreen_data_tout = 500;
//    }
    
    if(esp_frame_flag)
    {
        ESP_Uart_Handler();
        memset(esp_buf,0,sizeof(esp_buf));
        esp_sbyte = 0;
        esp_index = 0;
        esp_frame_flag = 0;
    }
   
}


void ESP_Uart_Handler(void)
{
    char* token,token_buf[10][10],lbuf[50];
    uint8_t j,k,i;
    uint16_t val=0,l;
    uint32_t jedac=0,chkId=0;
    uint8_t mp3_buf[50];
    uint8_t pbuf[20]={0};

    //UART_Send_String(UART_MODULE2,esp_buf);
   
     memcpy(sys_buf,esp_buf,150);
    //memset(sys_sr_no,0x00,5);
//    memcpy(pbuf,esp_buf+7,12);
//    UART_Send_String(UART_MODULE2,pbuf);
   
//    //sys_sr_no[5]='\0';
//    if(Srdata==0)
//    {
//    for(i=0;i<5;i++)
//     {
//         sys_sr_no[i]=esp_buf[i+7];
//     
//         UART_Send_String(UART_MODULE2,sys_sr_no);
//         Srdata=1;
//     }
//    }
    //=esp_buf;
     //UART_Send_String(UART_MODULE2,"Sr no  = \r\n");
     
    switch(esp_buf[2])
    {
        
        
        
        case 'S':       //Send System settings("SS") need to work on it for sending structure directly
        {
            if(esp_buf[3] == 'S')   //Send system identifier and total size of structure
            {
                flash_page_addr = (lc_duty_hint_page_s-1)*256 + ((sys.para.duty-1)*32) + flash_memory_offset;
                memset(lbuf,0,50);
                
                for(j=0;j<32;j++)
                {
                    lbuf[j] = SPIFlash_Read_Byte(flash_page_addr+j);
                }
//                sprintf(esp_buf,"{,CD,%s,%s,%s,csvVersion,PNC_Crane_v1.9.1,}\r\n",crane_make,crane_type,crane_model);
//                UART_Send_String(UART_MODULE2,esp_buf);
                sp_size = sizeof(sys.buf);
                sprintf(esp_buf,"{,SS,%d,%d,%s,%s,%s,%s,csvVersion,PCB344R1_M512_PNC_v1.12,}\r\n",sys.para.Select_System,sp_size,lbuf,crane_make,crane_type,crane_model);
                UART_Send_String(UART_MODULE3,esp_buf);
//                UART_Send_String(UART_MODULE1,esp_buf);
            }
            else if(esp_buf[3] == 'P')  //Send all parameters
            {
                for(l=0; l<sp_size; l++)
                {
                    UART3_Write(sys.buf[l]);
                    ESP_Delay(1);
                }
            }
            break;
        }
        case 'O':        //Onscreen data
        {
            //for(i=0;i<5;i++)
          // {
                //sys_sr_no[i]=esp_buf[i+5];
              // UART_Send_String(UART_MODULE2,esp_buf); 
          //  }
            sprintf(esp_buf,"{,OD,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,}\r\n",sys.para.duty,Cap1,TotalBmLength,JibLength,bm_angle,Knbm_angle,Radius1,DispLoadVal,(int8_t)TiltAngle_1_X,(int8_t)TiltAngle_1_Y,(int8_t)TiltAngle_2_X,(int8_t)TiltAngle_2_Y,OTG_status,digital_input_status,load_stat,(uint8_t)sys_err,sys.para.sel_uom,sys.para.Select_System);
            UART_Send_String(UART_MODULE3,esp_buf);
            
            break;
        }
        
//        case 'P':
//        {
//            if((sys.para.Select_System == REGULAR_SYSTEM)||(sys.para.Select_System == WHITELINE_ESCORTS)||
//               (sys.para.Select_System == ACE_NX360)||(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)||
//               (sys.para.Select_System == ACE_MANBASKET_HXP))
//                    Send_Pressure_Curve_Uart();
//            else
//               UART2_Write(0x0F);       //Failed as not ack
//            break;
//        }
        case 'C':       //Crane details
        {
//            byt1  = (uint8_t)(sys.para.so_number/100000);
//            byt2  = (uint8_t)((sys.para.so_number%100000)/10000);
//            byt3  = (uint8_t)((sys.para.so_number%10000)/1000);
//            byt4  = (uint8_t)((sys.para.so_number%1000)/100);
//            byt5  = (uint8_t)((sys.para.so_number%100)/10);
//            byt6  = (uint8_t)((sys.para.so_number%10)/1);
//            sprintf(lbuf,"%d%d%d%d%d%d",byt1,byt2,byt3,byt4,byt5,byt6);
//            byt1  = (uint8_t)(sys.para.engine_number/1000000000);
//            byt2  = (uint8_t)((sys.para.engine_number%1000000000)/100000000);
//            byt3  = (uint8_t)((sys.para.engine_number%100000000)/10000000);
//            byt4  = (uint8_t)((sys.para.engine_number%10000000)/1000000);
//            byt5  = (uint8_t)((sys.para.engine_number%1000000)/100000);
//            byt6  = (uint8_t)((sys.para.engine_number%100000)/10000);
//            byt7  = (uint8_t)((sys.para.engine_number%10000)/1000);
//            byt8  = (uint8_t)((sys.para.engine_number%1000)/100);
//            byt9  = (uint8_t)((sys.para.engine_number%100)/10);
//            byt10 = (uint8_t)((sys.para.engine_number%10)/1);
//            sprintf(lbuf1,"%d%d%d%d%d%d%d%d%d%d",byt1,byt2,byt3,byt4,byt5,byt6,byt7,byt8,byt9,byt10);
//            sprintf(esp_buf,"{,CD,%s,%s,%s,csvVersion,PNC_Crane_v1.9.1,}\r\n",crane_make,crane_type,crane_model);
//            UART_Send_String(UART_MODULE2,esp_buf);
            break;
        }
        case 'B':       //Bypass key operation
        {
            if((esp_buf[3] == 'K')&&(condition == 1))
            {
                token = strtok(esp_buf, ",");
                sprintf(lbuf,"%s",token);   //Skip SOF
                token = strtok(NULL,",");
                sprintf(lbuf,"%s",token);   //Skip command
                j=0;
                for(k=0; k<1; k++)
                {
                  token = strtok(NULL,",");
                  sprintf(token_buf[j],"%s",token); 
//                  UART_Send_String(UART_MODULE1,token_buf[j]);
                  j++;
                }
                esp_bpk_tout_min = (uint16_t)(atol(token_buf[0]));
                esp_bpk_tout_ms = esp_bpk_tout_min*60*1000;
            }
            break;
        }
        case 'H':
        {
            if(esp_buf[3] == 'M')
            {
                token = strtok(esp_buf, ",");
                sprintf(lbuf,"%s",token);   //Skip SOF
                token = strtok(NULL,",");
                sprintf(lbuf,"%s",token);   //Skip command
                j=0;
                for(k=0; k<1; k++)
                {
                    token = strtok(NULL,",");
                    sprintf(token_buf[j],"%s",token); 
//                    UART_Send_String(UART_MODULE1,token_buf[j]);
                    j++;
                }
                esp_hooter_mute = (uint8_t)(atol(token_buf[0]));
            }
            break;
        }
        case 'T':
        {
            if(esp_buf[3] == 'M')       //(TME)Test mode Enter=1/Exit=0
            {
                if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                {
                    if(esp_buf[6] == '1')
                    {
                        UART3_Write(0x06);
                        test_mode = 1;
                        color_lcd_draw_rectangle(ILI9341_WHITE,5,5,314,234);    
                        LCDPutStr("SYSTEM UNDER",95,90,XLARGE,ILI9341_NAVY, ILI9341_WHITE );
                        LCDPutStr("TEST MODE!!",95,150,XLARGE,ILI9341_NAVY, ILI9341_WHITE );
                    }
                    else
                    {
                        UART3_Write(0x06);
                        test_mode = 0;
                        Default_Main_Screen_Display();
//                        Lcd16x2_Out(1,1,"H/W TESTING MODE");
//                        Lcd16x2_Out(2,1,"     ENDED      ");
//                        Delay_1ms(2000);
                    }
                    
                    op.buzzaction = OUTPUT_OFF;
                    op.a2bledaction = OUTPUT_OFF;
                    op.artledaction = OUTPUT_OFF;
                    //op.errledaction = OUTPUT_OFF;
                    op.nlzledaction = OUTPUT_OFF;
                    op.relay1action = OUTPUT_OFF;
//                    op.relay2action = OUTPUT_OFF;
                    op.hooteraction = OUTPUT_OFF;
                    op.over_tilt_bit= 0;    //30/06/23 V1.17.2
                    Set_Bargraph_Percent(0);
                    err_led_status = 0x00;  
                    sprintf(lbuf,"test_mode=%d\r\n",test_mode); 
//                    UART_Send_String(UART_MODULE1,lbuf);
                }
            }
            else if(esp_buf[3] == 'B')       //Onboard buzzer
            {
                if((esp_buf[5] == '0')||(esp_buf[5] == '1'))
                {
                    if(esp_buf[5] == '1')   op.buzzaction = OUTPUT_ON;
                    else                    op.buzzaction = OUTPUT_OFF;
                    UART3_Write(0x06);
                }
            }
            else if(esp_buf[3] == 'L')       //Onboard LEDs
            {
                switch(esp_buf[4])
                {
                    case 'E':   //Error LED
                    {
                        if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                        {
//                            if(esp_buf[6] == '1')   op.errledaction = OUTPUT_ON;
//                            else                    op.errledaction = OUTPUT_OFF;
                            if(esp_buf[6] == '1')   op.over_tilt_bit= 1;//V1.17.2
                            else                    op.over_tilt_bit= 0; //V1.17.2
                            UART3_Write(0x06);
                        }
                        break;
                    }
                    case 'A':   //A2B LED
                    {
                        if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                        {
                            if(esp_buf[6] == '1')   op.a2bledaction = OUTPUT_ON;
                            else                    op.a2bledaction = OUTPUT_OFF;
                            UART3_Write(0x06);
                        }
                        break;
                    }
                    case 'N':   //NLZ LED
                    {
                        if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                        {
                            if(esp_buf[6] == '1')   op.nlzledaction = OUTPUT_ON;
                            else                    op.nlzledaction = OUTPUT_OFF;
                            UART3_Write(0x06);
                        }
                        break;
                    }
                    case 'R':   //Articulation LED
                    {
                        if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                        {
                            if(esp_buf[6] == '1')   op.artledaction = OUTPUT_ON;
                            else                    op.artledaction = OUTPUT_OFF;
                            UART3_Write(0x06);
                        }
                        break;
                    }
                    case 'B':   //Bar-graph LEDs
                    {
                        UART3_Write(0x06);
                        token = strtok(esp_buf, ",");
                        sprintf(lbuf,"%s",token);   //Skip SOF
                        token = strtok(NULL,",");
                        sprintf(lbuf,"%s",token);   //Skip command
                        j=0;
                        for(k=0; k<1; k++)
                        {
                          token = strtok(NULL,",");
                          sprintf(token_buf[j],"%s",token); 
//                          UART_Send_String(UART_MODULE1,token_buf[j]);
                          j++;
                        }
                        val = (uint16_t)(atol(token_buf[0]));
                        Set_Bargraph_Percent(0);
                        if(val <= 100)
                        {
                            for(j=1; j<=(val/10); j++)
                            {
                                Set_Bargraph_Percent(j*10);
                                Delay_1ms(200);
                            }
                        }
                        break;
                    }
                     case 'D':   //RED LAMP
                    {
                        if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                        {
                            if(esp_buf[6] == '1')   op.redledaction=OUTPUT_ON;
                            else                    op.redledaction=OUTPUT_OFF;
                            UART3_Write(0x06);
                        }
                        break;
                    }
                      case 'G':   //GREEN LAMP
                    {
                        if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                        {
                            if(esp_buf[6] == '1')   op.greenledaction=OUTPUT_ON;
                            else                    op.greenledaction=OUTPUT_OFF;
                            UART3_Write(0x06);
                        }
                        break;
                    }
                }
            }
            else if(esp_buf[3] == 'K')       //Onboard Keys
            {
                switch(esp_buf[4])
                {
                    case 'H':   //Duty Key
                    {
                        if(key.duty_ftp == 0)   UART3_Write('R');
                        else                    UART3_Write('P');
                        break;
                    }
                    case 'F':   //Function Key
                    {
                        if(key.func_ftp == 0)   UART3_Write('R');
                        else                    UART3_Write('P');
                        break;
                    }
                    case 'I':   //Increment Key
                    {
                        if(key.inc_ftp == 0)   UART3_Write('R');
                        else                   UART3_Write('P');
                        break;
                    }
                    case 'D':   //Decrement Key
                    {
                        if(key.dec_ftp == 0)   UART3_Write('R');
                        else                   UART3_Write('P');
                        break;
                    }
                    case 'E':   //Enter Key
                    {
                        if(key.entr_ftp == 0)   UART3_Write('R');
                        else                    UART3_Write('P');
                        break;
                    }
                    case 'B':   //Bypass Key
                    {
                        if(key.bpk_ftp == 0)   UART3_Write('R');
                        else                   UART3_Write('P');
                        break;
                    }
                }
            }
            else if(esp_buf[3] == 'R')       //Onboard Relays
            {
                if(esp_buf[4] == 'H')   //Hooter
                {
                    if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                    {
                        if(esp_buf[6] == '1')   op.hooteraction = OUTPUT_ON;
                        else                    op.hooteraction = OUTPUT_OFF;
                        UART3_Write(0x06);
                    }
                }
                else if(esp_buf[4] == 'M')   //Main cutoff
                {
                    if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                    {
                        if(esp_buf[6] == '1')   op.relay1action = OUTPUT_ON;
                        else                    op.relay1action = OUTPUT_OFF;
                        UART3_Write(0x06);
                    }
                }
                else if(esp_buf[4] == 'A')   //Aux cutoff
                {
                    if((esp_buf[6] == '0')||(esp_buf[6] == '1'))
                    {
//                        if(esp_buf[6] == '1')   op.relay2action = OUTPUT_ON;
//                        else                    op.relay2action = OUTPUT_OFF;
                        UART3_Write(0x06);
                    }
                }
            }
            else if(esp_buf[3] == 'L')      //LCD
            {
                
            }
            else if(esp_buf[3] == 'C')       //Communications
            {
                if(esp_buf[4] == 'C')   //CAN
                {
                    if(esp_buf[5] == '1')
                    {
                        can_tx.buffer = 0;
                        can_tx.data_length = 8;
                        can_tx.frame_type = 0;
                        can_tx.id = 1023;
                        can_tx.message_type = NO_RTR;
                        can_tx.data[0] = 1;
                        can_tx.data[1] = 2;
                        can_tx.data[2] = 3;
                        can_tx.data[3] = 4;
                        can_tx.data[4] = 5;
                        can_tx.data[5] = 6;
                        can_tx.data[6] = 7;
                        can_tx.data[7] = 8;
                        Ecan1WriteMessage(&can_tx);
                        C1TR01CONbits.TXREQ0 = 1;
                        ms_count = 300;
                        
                        while(ms_count)
                        {
                            if(C1RXFUL1bits.RXFUL1 == 1)
                            {
                                can_rx.buffer = 1;
                                C1RXFUL1bits.RXFUL1 = 0;
                                RxECAN1(&can_rx);
                                
                                if(can_rx.id == 1022)
                                {
                                    if((can_rx.data[0] == 1)&&(can_rx.data[1] == 2)&&(can_rx.data[2] == 3)
                                        &&(can_rx.data[3] == 4)&&(can_rx.data[4] == 5)&&(can_rx.data[5] == 6)
                                        &&(can_rx.data[6] == 7)&&(can_rx.data[7] == 8))
                                    {
                                        UART3_Write(0x06);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else if(esp_buf[5] == '2')//changehere v1.17.4 CAN2 fot testmode app 12-07-23
                    {
                         can_tx.buffer = 0;
                        can_tx.data_length = 8;
                        can_tx.frame_type = 0;
                        can_tx.id = 1023;
                        can_tx.message_type = NO_RTR;
                        can_tx.data[0] = 1;
                        can_tx.data[1] = 2;
                        can_tx.data[2] = 3;
                        can_tx.data[3] = 4;
                        can_tx.data[4] = 5;
                        can_tx.data[5] = 6;
                        can_tx.data[6] = 7;
                        can_tx.data[7] = 8;
                        Ecan1WriteMessage(&can_tx);
                        C1TR01CONbits.TXREQ0 = 1;
                        ms_count = 300;
                        
                        while(ms_count)
                        {
                            if(C1RXFUL1bits.RXFUL1 == 1)
                            {
                                can_rx.buffer = 1;
                                C1RXFUL1bits.RXFUL1 = 0;
                                RxECAN1(&can_rx);
                                
                                if(can_rx.id == 1022)
                                {
                                    if((can_rx.data[0] == 1)&&(can_rx.data[1] == 2)&&(can_rx.data[2] == 3)
                                        &&(can_rx.data[3] == 4)&&(can_rx.data[4] == 5)&&(can_rx.data[5] == 6)
                                        &&(can_rx.data[6] == 7)&&(can_rx.data[7] == 8))
                                    {
                                        UART3_Write(0x06);
                                        break;
                                    }
                                }
                            }
                        }
                        
                        
                        
                    }
                }
                else if(esp_buf[4] == 'T')   //Telematics
                {
                    UART3_Write(0x06);
                    UART_Send_String(UART_MODULE3,"Telematic testing string...!!\r\n");
//                    UART_Send_String(UART_MODULE2,"Telematic testing string...!!\r\n");
                }
                else if(esp_buf[4] == 'S')   //Speaker module
                {
                    UART3_Write(0x06);
                    token = strtok(esp_buf,",");
                    sprintf(lbuf,"%s",token);   //Skip SOF
                    token = strtok(NULL,",");
                    sprintf(lbuf,"%s",token);   //Skip command
                    j=0;
                    for(k=0; k<1; k++)
                    {
                      token = strtok(NULL,",");
                      sprintf(token_buf[j],"%s",token); 
//                      UART_Send_String(UART_MODULE1,token_buf[j]);
                      j++;
                    }
                    val = (uint16_t)(atol(token_buf[0]));
//                    sprintf(lbuf,"Audio Track=%d\r\n",val);//changehere v1,17,2 Audio testing
//                    UART_Send_String(UART_MODULE2,lbuf);
                    Current_Track = val;
//                    Track_Counter = DELAY2_BETWEEN_TWO_TRACKS;
            memset(mp3_buf, 0, sizeof(mp3_buf));//changehere v1.17.2 Audio testing 
            sprintf((char *)mp3_buf,"{,OD,%d,1,%d,}\r\n",digital_output_status,Current_Track);
            UART_Send_String(UART_MODULE4,(char *)mp3_buf);
//                    Play_track_Logic();
                //  Playback_Number(val);     //30/06/23 V1.17.2
                 //   Playback_Number(ESCORTS_WELCOME_HINDI_MP3);
                }
                else if(esp_buf[4] == 'F')   //SPI Flash
                {
                    jedac = Jedec_ID_Read();
                    
                    SPIFlash_Read_Sector(FLASH_TEST_SECTOR);
                    flash.buf[4095] = 'T';
                    Sector_Erase(FLASH_TEST_SECTOR);
                    SPIFlash_Write_Sector(FLASH_TEST_SECTOR);
                    
                    flash.buf[4095] = 0;
                    SPIFlash_Read_Sector(FLASH_TEST_SECTOR);
                    
                    if(((jedac == 0xBF2641)||(jedac == 0x00EF4015))&&(flash.buf[4095] == 'T'))
                    {
                        UART3_Write(0x06);
                    }
                }
                else if(esp_buf[4] == 'G')   // changehere v1.17.4 14/07/23 PI2 Flash
                {
                    jedac = Jedec_ID_Read();
                    
                    SPIFlash_Read_Sector(FLASH_TEST_SECTOR);
                    flash.buf[4095] = 'T';
                    Sector_Erase(FLASH_TEST_SECTOR);
                    SPIFlash_Write_Sector(FLASH_TEST_SECTOR);
                    
                    flash.buf[4095] = 0;
                    SPIFlash_Read_Sector(FLASH_TEST_SECTOR);
                    chkId = Init_SPI_Flash_All();
                    
                    if(((chkId == 0x00BF2641)||(chkId == 0x00EF4015)))
                    {
                        UART3_Write(0x06);
                    }
                }
            }
            else if(esp_buf[3] == 'D')      //Testing data
            {
                CAN_Receive();
                sprintf(esp_buf,"{,TD,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,}\r\n",p1_pressure_cnt,p2_pressure_cnt,len_adc_cnt,ang_adc_cnt,can_p1_cnt,can_p2_cnt,can_p3_cnt,can_p4_cnt,can_loadcell_cnt,len_avg_cnt,a2b_stat,art_ip_bit,spare_in_bit,OTG_status);
                UART_Send_String(UART_MODULE3,esp_buf);
            }            
            break;
        }
    }    
}

void ESP32_data()
{
    char i;
    
    if(esp_buf[2]>0||esp_buf[2]<9)
    {
          
        for(i=0;i<5;i++)
     {
      
       //UART_Send_String(UART_MODULE2,esp_buf);  
      
       sys_sr_no[i]=esp_buf[i];
       UART_Send_String(UART_MODULE2,sys_sr_no);
      }
     
    }
    memset(sys_sr_no,0x00,5);
    memcpy(sys_sr_no,sys_buf+7,5);
    sys_sr_no[5]='\0';
   // UART_Send_String(UART_MODULE2,sys_sr_no);
}




