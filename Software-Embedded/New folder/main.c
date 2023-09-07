/*
 * File:   main.c
 * Author: Edesign3
 * Modified by : Santosh Katke 
 * Created on 6 JAN, 2023, 3:31 PM
 */
// DSPIC33EP512GM710 Configuration Bit Settings

// 'C' source line config statements

// FICD
#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGEC2 and PGED2)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config BOREN = ON               // Brown-out Reset (BOR) Detection Enable bit (BOR is enabled)
#pragma config ALTI2C1 = ON             // Alternate I2C1 pins (I2C1 mapped to ASDA1/ASCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (Watchdog timer always enabled)
// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Mode Select bits (XT Crystal Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = OFF            // Peripheral pin select configuration (Allow multiple reconfigurations)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FOSCSEL
#pragma config FNOSC = PRIPLL           // Oscillator Source Selection (Primary Oscillator with PLL module (XT + PLL, HS + PLL, EC + PLL))
#pragma config PWMLOCK = OFF            // PWM Lock Enable bit (PWM registers may be written without key sequence)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "main.h"

uint16_t adc_tout;
 
mID can_tx,can_rx;
SPI_P spis;
TIMER_P tims;
UART_P uarts;
ECAN_P ecan;
OP_HANDLE op;


void Delay_1ms(uint16_t d)
{
    ms_count = d;
    while(ms_count);
}


int main(void)
{
    char mbuf[50];
    
#ifdef DISPLAY_16x2
    System_Initialize();
    
#else
#ifdef DISPLAY_TFT32
    System_Initialize();
    
    Default_Main_Screen_Display();
    
#else
#ifdef DISPLAY_192x64
    System_Initialize();
#endif
#endif
#endif
    //UART_Send_String(UART_MODULE3,"WELCOME");
    Parse_Uart_Data();
    Srdata==0;
    // TESTING 28/04/23    
    
//    while(1)
//    {
//        err_led_status |= ERROR_LED;//OVER_TILT_LED;
//        err_led_status |= OVER_ARTICULATION_LED;
//        err_led_status |= NLZ_STATUS_LED;
//        err_led_status |= A2B_STATUS_LED;
//        
//         Delay_1ms(500);
//        err_led_status &= ~ERROR_LED;//OVER_TILT_LED;
//        err_led_status &= ~OVER_ARTICULATION_LED;
//        err_led_status &= ~NLZ_STATUS_LED;
//        err_led_status &= ~A2B_STATUS_LED;
//        
//        Delay_1ms(500);
//    }
    while(1)
    {
        if(pic25k80_tout == 0)
        {
            memset(mbuf, 0, sizeof(mbuf));
            sprintf(mbuf,"{,OD,%d,0,0,}\r\n",digital_output_status);
            UART_Send_String(UART_MODULE4,mbuf);
            digital_output_status = 0;
            mp3_play_flag = 0;
            pic25k80_tout = 400;
        }
        
        if(test_mode == 0)
        {
            if(disp_error == 0)
            {
                Analog_Data_Read();
                
                Calculate_Len_Radius();
                
                Analog_Data_Process();  //Analog Data Process,CSV Process,Decision making,Action.... 
            }
            
#ifdef DISPLAY_16x2
            Display_Main_Screen();   //Display Main Screen Parameter .....
            
            Gui();                  //User Interface 
#else 
#ifdef DISPLAY_TFT32            
            Display_Main_Screen();
            
            TFT32_Gui();
#else
#ifdef DISPLAY_192x64
            GLCD192x64_Gui();
#endif
#endif
#endif
        }
        else if(test_mode == 1) //V1.17.2
        {
           
            Analog_Data_Read();                
        }
        
        ESP32_Handler();
       // ESP32_data();
//       op.redledaction=OUTPUT_ON;
//       op.greenledaction=OUTPUT_ON;
        Delay_1ms(1000);
         //op.redledaction=OUTPUT_OFF;
      // op.greenledaction=OUTPUT_OFF;
      // Delay_1ms(1000);
//        prv_duty = sys.para.duty;
    }
}


/*============================================================================*/
/*
 * Function      :        Do_Len_MPoint_Sorting.
 * Description   :        Used to sort length multipoint calibration values.
 * Parameters    :        mpoint-number of multipoints.
 * Return        :        None.
*/
/*============================================================================*/
void Do_Len_MPoint_Sorting(uint8_t mpoint)
{
    uint8_t f, g;
    uint16_t swap_val;
    
    for (f = 0; f < mpoint; f++)        //
    {
        for (g = f + 1; g < mpoint; g++)
        {
            if (sys.para.multipt_lcalib[g][0] < sys.para.multipt_lcalib[f][0])  //length value
            {
                swap_val = sys.para.multipt_lcalib[f][0];
                sys.para.multipt_lcalib[f][0] = sys.para.multipt_lcalib[g][0];
                sys.para.multipt_lcalib[g][0] = swap_val;
                
                swap_val = sys.para.multipt_lcalib[f][1];                         //length counts
                sys.para.multipt_lcalib[f][1] = sys.para.multipt_lcalib[g][1];
                sys.para.multipt_lcalib[g][1] = swap_val;
            }
        }
    }
}

/*============================================================================*/
/*
 * Function      :        Do_Forklift_Load_MPoint_Sorting.
 * Description   :        Used to sort forklift pressure load multipoint calibration values.
 * Parameters    :        mpoint-number of multipoints.
 * Return        :        None.
*/
/*============================================================================*/
void Do_Forklift_Load_MPoint_Sorting(uint8_t mpoint)
{
    uint8_t f, g;
    uint16_t swap_val;
    
    if(byt1 == 0)
    {
        for (f = 0; f < mpoint; f++)
        {
            for (g = f + 1; g < mpoint; g++)
            {
                if (sys.para.forkcalib_press_min[g][0] < sys.para.forkcalib_press_min[f][0])  //load value
                {
                    swap_val = sys.para.forkcalib_press_min[f][0];
                    sys.para.forkcalib_press_min[f][0] = sys.para.forkcalib_press_min[g][0];
                    sys.para.forkcalib_press_min[g][0] = swap_val;
                    
                    swap_val = sys.para.forkcalib_press_min[f][1];                         //load counts
                    sys.para.forkcalib_press_min[f][1] = sys.para.forkcalib_press_min[g][1];
                    sys.para.forkcalib_press_min[g][1] = swap_val;
                }
            }
        }
    }
    else
    {
        for (f = 0; f < mpoint; f++)
        {
            for (g = f + 1; g < mpoint; g++)
            {
                if (sys.para.forkcalib_press_max[g][0] < sys.para.forkcalib_press_max[f][0])  //load value
                {
                    swap_val = sys.para.forkcalib_press_max[f][0];
                    sys.para.forkcalib_press_max[f][0] = sys.para.forkcalib_press_max[g][0];
                    sys.para.forkcalib_press_max[g][0] = swap_val;

                    swap_val = sys.para.forkcalib_press_max[f][1];                         //load counts
                    sys.para.forkcalib_press_max[f][1] = sys.para.forkcalib_press_max[g][1];
                    sys.para.forkcalib_press_max[g][1] = swap_val;
                }
            }
        }
    }
}


void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    //if(menu_stat == DEFAULT_PAGE)  //change here 27/04/23  v1.16  bar graph  status on in menus also
        LED5x4_Scanner(bargraph_status,err_led_status);
//    else
//        LED5x4_Scanner(0,0);
    
    IFS0bits.T1IF = 0;
}
 
void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    Keypad_Scan();
    
    CAN_Receive();
    
    if((sys.para.rig_duty_bit == 0)&&(test_mode == 0))
    {
        if(((digital_input_status & 0x01)&&(sys.para.a2b_stat_bit == 1))||(A2B_CAN))
        {
            op.a2bledaction = OUTPUT_ON;
            a2b_stat = 1;
        }
        else
        {
            op.a2bledaction = OUTPUT_OFF;
            a2b_stat = 0;
        }

        if((sys.para.Select_System != PALFINGER_KNUCKLE_BOOM)&&(sys.para.Select_System != TMC_MANBASKET)&&
           (sys.para.Select_System != TMC_MANBASKET2)&&(sys.para.Select_System != ACE_NX360))
        {
            if(digital_input_status & 0x02)
            {
                switch(sys.para.Select_System)
                {
                    case REGULAR_SYSTEM:     op.artledaction = OUTPUT_ON; art_ip_bit = 1;  break;       //Articulation LED ON Here
                    case WHITELINE_ESCORTS:  op.artledaction = OUTPUT_ON; art_ip_bit = 1;  break;
                    case TIL_PIXEF_TELE_PNC: op.artledaction = OUTPUT_ON; art_ip_bit = 1;  break;
                    case FORK_LIFT:          art_ip_bit = 1;  break;
                    case TELESCOPIC_RT40:     op.artledaction = OUTPUT_ON; art_ip_bit = 1;  break;
                }
            }
            else
            {
                if(sys.para.Select_System != FORK_LIFT)
                    op.artledaction = OUTPUT_OFF;
                art_ip_bit = 0;
            }
        }
        else
        {
            op.artledaction = OUTPUT_OFF;
        }

        if(digital_input_status & 0x04)         //OTG1
        {
            OTG_status = 1;
        }
        else
        {
            OTG_status = 0; 
        }
    }
     if(test_mode)
    {
        if(digital_input_status & 0x01)
        {
            a2b_stat = 1;
        }
        else
        {
            a2b_stat = 0;
        }

        if(digital_input_status & 0x02)
        {
            art_ip_bit = 1;
        }
        else
        {
            art_ip_bit = 0;
        }

        if(digital_input_status & 0x04)
        {
            OTG_status = 1;
        }
        else
        {
            OTG_status = 0; 
        }

        if(digital_input_status & 0x08)
        {
            spare_in_bit = 1;
        }
        else
        {
            spare_in_bit = 0;
        }
    }

    if((ui_key == 0) &&(sys.para.rig_duty_bit == 0))Digital_Output_Handler(); //Digital_Output_Handler WORK IF RIGGIG DUTY DISABLE

    if((sys.para.Select_System == ACE_NX360)||(sys.para.Select_System == TMC_MANBASKET)||
       (sys.para.Select_System == TMC_MANBASKET2))
        CAN_Handler();
        
    IFS0bits.T2IF = 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void)
{
    if(ms_count > 0)            ms_count--;
    
    if(disp_refresh_cnt > 0)    disp_refresh_cnt--;
    if(hint_refresh_cnt > 0)    hint_refresh_cnt--;
    if(op.errledtout > 0)       op.errledtout--;
    if(op.a2bledtout > 0)       op.a2bledtout--;
    if(op.artledtout > 0)       op.artledtout--;
    if(op.nlzledtout > 0)       op.nlzledtout--;
    if(op.buzztout > 0)         op.buzztout--;
    if(can_interval_cnt > 0)    can_interval_cnt--;
    if(temp_interval_cnt > 0)   temp_interval_cnt--;

    if(adc_tout > 0)            adc_tout--;
    if(bpk_tout > 0)            bpk_tout--;
    if(common_tout > 0)         common_tout--; 
    if(Tele_Counter>0)          Tele_Counter--;  //Telematics Counter
    if(load_peak_Tout > 0)      load_peak_Tout--;
    if(can_175_tout > 0)        can_175_tout--;
    if(sys.para.slave_enable_bit)   
        if(can_180_tout > 0)        can_180_tout--;
    if(can_201_tout > 0)        can_201_tout--;
    if(can_352_tout > 0)        can_352_tout--;
    if(can_357_tout > 0)        can_357_tout--;
    if(can_358_tout > 0)        can_358_tout--;
    if(test_tout > 0)           test_tout--;
    if(pc_tout > 0)             pc_tout--;
    //===================================================
    if(Track_Counter>0)         Track_Counter--;  //White Line  
    if(track_change_tout > 0)   track_change_tout--;
    if(load_ann_tout > 0)       load_ann_tout--;
    if(direction_tout > 0)      direction_tout--;

    if(can_len_angle_tout > 0)  can_len_angle_tout--;
    if(can_p1p2_tout > 0)       can_p1p2_tout--;

    if(master_can_sync_tout > 0)    master_can_sync_tout--;
    if(tower_lamp_can_tout > 0) tower_lamp_can_tout--;

    //=================ESP32========================
    if(onscreen_data_tout > 0)  onscreen_data_tout--;
    if(esp_bpk_tout_ms > 0)     esp_bpk_tout_ms--;

    if(pic25k80_tout > 0)       pic25k80_tout--;
    
    IFS0bits.T3IF = 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void) //SPI FLASH
{
    IFS0bits.U1RXIF = 0;
}


void __attribute__ ((interrupt, no_auto_psv)) _U2RXInterrupt(void)  //IOT
{    
    IFS1bits.U2RXIF = 0;
}


void __attribute__ ((interrupt, no_auto_psv)) _U3RXInterrupt(void) //Telematics
{
    uint8_t RxdData;
    
    RxdData = U3RXREG;
    
    if((RxStart_flag==0)&&(RxdData == '$'))   //check Start of Frame 
    {
        Rxcount = 0;
        DataRxdOver =0;
        RxStart_flag = 1; //page start flag confirm
    }
    else if(RxStart_flag==1)
    {
        Serial_buff[Rxcount]= RxdData;
        RxdData = 0;
        Rxcount++;                             //Receving 256 Byte 

        if((NewCSVFlag==0)&&(Rxcount>=256))
        {
            Page_done=1;
            Rxcount=0;
            RxStart_flag=0;	
        }	
        else if((NewCSVFlag==1)&&(Rxcount>=3))
        {
            Page_done=1;
            Rxcount=0;
            RxStart_flag=0;	
        }
    }
    else if((RxStart_flag==0)&&(RxdData==0x03))
    {
        DataRxdOver=1;	
    }
    else
    {
        if(RxdData != '\n')
        {
            esp_buf[esp_index++] = RxdData;
        }
        else if(RxdData == '\n')
        {
            esp_buf[esp_index++] = RxdData;
            esp_frame_flag = 1;  
        }
    }
    IFS5bits.U3RXIF = 0;//clear interrupt flag
}


void __attribute__ ((interrupt, no_auto_psv)) _U4RXInterrupt(void) //Speaker /mp3
{
    uint8_t inChar;
    
    inChar = U4RXREG;
    
    if(inChar != '\n')
    {
        u4buf[u4indx] = (char)inChar; // Store it
        u4indx++; // Increment where to write next
    }
    else
    {
        u4buf[u4indx] = (char)inChar; // Store it
        u4indx = 0;
        u4ready_bit = 1;
    }
    IFS5bits.U4RXIF = 0;
}



