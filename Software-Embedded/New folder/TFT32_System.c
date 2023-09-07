/*
        Created by                     :        Santosh Katke
        Date                           :        07 July T21.
        Software Version               :        v1.0
        Note                           :        This is the source file for Pick and carry System.
        MicroController                :        dsPIC33EP512GM710
        Operation Frequency (Crystal)  :        XT oscillator (8MHz) with PLL-140MHz
        Interface                      :        NA.
        Software IDE                   :        MicroC Pro for dsPIC IDE
        Software IDE Version           :        v7.1.0
           Compiler                    :        MPLAB XC16
           Compiler Version            :        v1.41

Description:
  Task to handle System functions.

//============================================================================

Version 1.0 is used as a major milestone, indicating that the software is "complete",
that it has all major features, and is considered reliable enough for general release.

Any minor change in code , increment right side number after decimal point.

Any major change in code , increment Left side number before decimal point.

//============================================================================
Special Notes if any:


Pin details: NA

//============================================================================
Version History
//============================================================================
S.Ver: 01.00        Date: 100220
//============================================================================
Functions effected                        :
Problem description                        :

Current Status                                 :
Keyword to search                         :
//============================================================================
List of Functions used :
   System_Initialize()
   Status_LED_Output_Action()
   Display_Main_Screen()
   Bar_Graph_Disp()
   Marching_Mode()
   Power_ON_Display()
   Calc_CranePara()
   Calc_Parameter_Factors()
   Read_Startup_SPIFlash()
   Read_System_Parameters()
   Factory_Default_Reset()
   
//============================================================================
Naming Procedure:

All variables to be defined as [ "datatype"_Variable name] in lowercase
For Function naming First Character of each word to be in Capital [ Transmit_Data]
For Macros naming All Character of each word to be in Capital [ TRANSMIT_DATA]

==============================================================================
*/
#include "main.h"



/*============================================================================*/
/*
 * Function      :  Init_Keypad.
 * Description   :  Used to init individual keys.
 * Parameters    :  None.
 * Return        :  None.
*/
/*============================================================================*/
void Init_Keypad(void)
{
    GPIO_Function(GPIO_PORTE,KEY_SW1,GPIO_INPUT,0,0);
    GPIO_Function(GPIO_PORTD,KEY_SW2,GPIO_INPUT,0,0);
    GPIO_Function(GPIO_PORTD,KEY_SW3,GPIO_INPUT,0,0);
    GPIO_Function(GPIO_PORTD,KEY_SW4,GPIO_INPUT,0,0);
    GPIO_Function(GPIO_PORTD,KEY_SW5,GPIO_INPUT,0,0);
    GPIO_Function(GPIO_PORTA,KEY_SW6,GPIO_INPUT,0,0);
}


/*============================================================================*/
/*
 * Function      :  Keypad_Scan.
 * Description   :  Used to scan individual keys.
 * Parameters    :  None.
 * Return        :  None.
*/
/*============================================================================*/
void Keypad_Scan(void)
{
    if(PORTEbits.RE8 == 0)
    {
        if(key.duty_ftp == 0)
        {
            key.duty_ftp = 1;
            key.duty = 1;
        }
    }
    else
    {
        key.duty_ftp = 0;
    }
    if(PORTDbits.RD4 == 0)
    {
        if(key.func_ftp == 0)
        {
            key.func_ftp = 1;
            key.function = 1;
        }
    }
    else
    {
        key.func_ftp = 0;
    }
    if(PORTDbits.RD3 == 0)
    {
        if(key.inc_ftp == 0)
        {
            key.inc_ftp = 1;
            key.increment = 1;
        }
    }
    else
    {
        key.inc_ftp = 0;
    }
    if(PORTDbits.RD2 == 0)
    {
        if(key.dec_ftp == 0)
        {
            key.dec_ftp = 1;
            key.decrement = 1;
        }
    }
    else
    {
        key.dec_ftp = 0;
    }
    if(PORTDbits.RD1 == 0)
    {
        if(key.entr_ftp == 0)
        {
            key.entr_ftp = 1;
            key.enter = 1;
        }
    }
    else
    {
        key.entr_ftp = 0;
    }
    if(PORTAbits.RA7 == 0)
    {
        if(key.bpk_ftp == 0)
        {
            key.bpk_ftp = 1;
            key.bypass = 1;
        }
    }
    else
    {
        key.bpk_ftp = 0;
    }
}


void System_Initialize(void)
{    
    uint32_t chkId;
//    uint8_t temp[25];
    
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    ANSELD = 0x00;
    ANSELE = 0x00;
    ANSELG = 0x00;

    TRISA = 0;             // Initialize PORTA as output
    TRISB = 0;             // Initialize PORTB as output
    TRISC = 0;             // Initialize PORTC as output
    TRISD = 0;             // Initialize PORTD as output
    TRISF = 0;             // Initialize PORTE as output
    TRISG = 0;             // Initialize PORTG as output

    LATA = 0;
    LATB = 0;              // Set PORTB to zero
    LATC = 0;              // Set PORTC to zero
    LATD = 0;              // Set PORTD to zero
    LATF = 0;              // Set PORTE to zero
    LATG = 0;              // Set PORTG to zero
    
    PLLFBD = 68;             //M=70
    CLKDIV = 0x0000;         // PLL prescaler N1=2, PLL postscaler N2=2
    
    // CF no clock failure; NOSC PRIPLL; LPOSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONH((uint8_t) (0x03));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1); 
    
    ui_key = 1;
    
    //UART1 is mapped with LED matrix so commented
//    GPIO_Function(GPIO_PORTD,U1_DEBUG_RX_D12,GPIO_INPUT,0,DIGITAL_INPUT);
//    GPIO_Function(GPIO_PORTD,U1_DEBUG_TX_D5,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
//    PORTDbits.RD5 = 1;
//    PPS_Mapping(RPI76_MAPPING,PPS_INPUT,UART1Rx);
//    PPS_Mapping(RP69_MAPPING,PPS_OUTPUT,UART1Tx);
//    UART_Initialize(UART_MODULE1,9600UL,0);    
 //   UART_Send_String(UART_MODULE1,"UART1_PERIPHERAL initialised for Debug @9600...!!\r\n");
    
    GPIO_Function(GPIO_PORTG,U2_IOT_RX_G9,GPIO_INPUT,0,DIGITAL_INPUT);
    GPIO_Function(GPIO_PORTG,U2_IOT_TX_G6,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    PORTGbits.RG6 = 1;
    PPS_Mapping(RPI121_MAPPING,PPS_INPUT,UART2Rx);
    PPS_Mapping(RP118_MAPPING,PPS_OUTPUT,UART2Tx);
    UART_Initialize(UART_MODULE2,115200UL,0);
    UART_Send_String(UART_MODULE2,"UART2_PERIPHERAL initialised for Debug @115200...!!\r\n");
        
    GPIO_Function(GPIO_PORTF,U3_TELE_RX_F0,GPIO_INPUT,0,DIGITAL_INPUT);
    GPIO_Function(GPIO_PORTF,U3_TELE_TX_F1,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    PORTFbits.RF1 = 1;
    PPS_Mapping(RPI96_MAPPING,PPS_INPUT,UART3Rx);
    PPS_Mapping(RP97_MAPPING,PPS_OUTPUT,UART3Tx);
    UART_Initialize(UART_MODULE3,38400UL,1);
//    UART_Send_String(UART_MODULE3,"UART3_PERIPHERAL initialised for IOT @38400...!!\r\n");
    
    GPIO_Function(GPIO_PORTB,U4_PIC25K80_RX_B12,GPIO_INPUT,0,DIGITAL_INPUT);
    GPIO_Function(GPIO_PORTG,U4_PIC25K80_TX_G13,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    PORTGbits.RG13 = 1;
    PPS_Mapping(RPI44_MAPPING,PPS_INPUT,UART4Rx);
    PPS_Mapping(RP125_MAPPING,PPS_OUTPUT,UART4Tx);
    UART_Initialize(UART_MODULE4,57600UL,1);
    //UART_Send_String(UART_MODULE1,"UART4_PERIPHERAL initialised for PIC18F25K80 @57600...!!\r\n");
    
    TMR1_Initialize(0.5);
    //UART_Send_String(UART_MODULE1,"TIMER1_PERIPHERAL initialised for 0.5msec...!!\r\n");
    
    TMR2_Initialize(10.0);
    //UART_Send_String(UART_MODULE1,"TIMER2_PERIPHERAL initialised for 10mSec...!!\r\n");
    
    TMR3_Initialize(1.0);
    //UART_Send_String(UART_MODULE1,"TIMER2_PERIPHERAL initialised for 1mSec...!!\r\n");
    
    TRISG |= 0x0003;
    PPS_Mapping(RPI112_MAPPING,PPS_INPUT,ECAN1Rx);
    PPS_Mapping(RP113_MAPPING,PPS_OUTPUT,ECAN1Tx);
    Ecan1Init(500000UL);    
    //UART_Send_String(UART_MODULE1,"ECAN1_PERIPHERAL initialised for 500Kbps...!!\r\n");
    
    Delay_1ms(1000);
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
    
    GPIO_Function(sflash.cs_port,sflash.cs_pin,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    GPIO_Function(sflash.wp_port,sflash.wp_pin,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    //Flash2 for crane images
    GPIO_Function(GPIO_PORTC,CS2_FLASH,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    GPIO_Function(GPIO_PORTD,WP2_FLASH,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    
    CNPDEbits.CNPDE9 = 1;   //Pull down enabled
    CNPUGbits.CNPUG12 = 1;   //Pull up enabled      //SPI2SDI RG12
    GPIO_Function(GPIO_PORTG,12,GPIO_INPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    GPIO_Function(GPIO_PORTG,14,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    GPIO_Function(GPIO_PORTB,11,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    PPS_Mapping(RPI124_MAPPING,PPS_INPUT,SPI2SDI);
    PPS_Mapping(RP126_MAPPING,PPS_OUTPUT,SPI2SDO);
    PPS_Mapping(RP43_MAPPING,PPS_OUTPUT,SPI2SCK);
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR22bits.SCK2R = RP43_MAPPING;                       //Important step in SPI init
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    SPI_Initialize(sflash.spi_module,SPI_MODE0);      //SPI_MODE0
    
    chkId = Init_SPI_Flash_All();
    
    if((chkId == 0x00BF2641)||(chkId == 0x00EF4015)){}
    else
    {
        __asm__ volatile ("reset");//Hardware reset command
    }
    
    Set_Bargraph_Percent(0);
    err_led_status = 0x00;
    
    tft32.spi_module = SPI_MODULE3;
    tft32.cs_port = GPIO_PORTF;
    tft32.cs_pin = TFT32_CS;    
    tft32.cd_port = GPIO_PORTF;
    tft32.cd_pin = TFT32_CD;    
    tft32.rst_port = GPIO_PORTC;
    tft32.rst_pin = TFT32_RST;
    CNPUFbits.CNPUF6 = 1;
    CNPUFbits.CNPUF7 = 1;
//    CNPUBbits.CNPUB13 = 1;
    CNPUFbits.CNPUF12 = 1;
    
    GPIO_Function(tft32.cd_port,tft32.cd_pin,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);      //Data/Command selection pin for 3.2TFT
    GPIO_Function(tft32.cs_port,tft32.cs_pin,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);      //CS pin for 3.2TFT
    GPIO_Function(tft32.rst_port,tft32.rst_pin,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);    //RST pin for 3.2TFT
    
    CNPUCbits.CNPUC9 = 1;   //Pull up enabled
//    CNPUDbits.CNPUD13 = 1;   //Pull up enabled
    CNPUCbits.CNPUC8 = 1;   //Pull up enabled
    CNPUBbits.CNPUB8 = 1;   //Pull up enabled
    GPIO_Function(GPIO_PORTC,9,GPIO_INPUT,GPIO_HIGH,DIGITAL_OUTPUT);
//    GPIO_Function(GPIO_PORTD,13,GPIO_INPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    GPIO_Function(GPIO_PORTC,8,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    GPIO_Function(GPIO_PORTB,8,GPIO_OUTPUT,GPIO_HIGH,DIGITAL_OUTPUT);
    PPS_Mapping(RP57_MAPPING,PPS_INPUT,SPI3SDI);
//    PPS_Mapping(RPI77_MAPPING,PPS_INPUT,SPI3SDI);
    PPS_Mapping(RP56_MAPPING,PPS_OUTPUT,SPI3SDO);
    PPS_Mapping(RP40_MAPPING,PPS_OUTPUT,SPI3SCK);
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    //Important step in SPI init
    RPINR29bits.SCK3R = 0x28;
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS    
    SPI_Initialize(tft32.spi_module,SPI_MODE0);
    
    Delay_1ms(100);
    
    Init_TFT32_ILI9341();
    
    Default_Main_Screen_Outline();
    
//    GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_HIGH);
//    Delay_1ms(1500);
//    GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_LOW);
    
    Init_Keypad();
    
    led.col_port[0] = GPIO_PORTE;
    led.col_pin[0] = LED_COL1;
    led.col_port[1] = GPIO_PORTA;
    led.col_pin[1] = LED_COL2;
    led.col_port[2] = GPIO_PORTG;
    led.col_pin[2] = LED_COL3;
    led.col_port[3] = GPIO_PORTD;
    led.col_pin[3] = LED_COL4;
    led.col_port[4] = GPIO_PORTF;
    led.col_pin[4] = LED_COL5;
    led.row_port[0] = GPIO_PORTG;
    led.row_pin[0] = LED_ROW1;
    led.row_port[1] = GPIO_PORTF;
    led.row_pin[1] = LED_ROW2;
    led.row_port[2] = GPIO_PORTF;
    led.row_pin[2] = LED_ROW3;
    led.row_port[3] = GPIO_PORTD;
    led.row_pin[3] = LED_ROW4;
    Init_LED_Matrix(4);
    
    system_initialization();
    
    Delay_1ms(2000);
    Set_Bargraph_Percent(0);
    err_led_status = 0x00;
    
//    GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_HIGH);
    
                                            //V1.17.1
    
    chkId = Init_SPI_Flash_All();
    
    SPIFlash_Read_Sector(FLASH_TEST_SECTOR);
    flash.buf[4094] = 'K';
    Sector_Erase(FLASH_TEST_SECTOR);
    SPIFlash_Write_Sector(FLASH_TEST_SECTOR);
    
    flash.buf[4094] = 0;
    SPIFlash_Read_Sector(FLASH_TEST_SECTOR);
    
    if(((chkId == 0x00BF2641)||(chkId == 0x00EF4015))&&(flash.buf[4094] == 'K'))
    {
        Initial_SPI_Test_Screen(1,0);
    }
    else
    {
        Initial_SPI_Test_Screen(1,1);
        while(1);
    }
    Delay_1ms(1500);
    GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_LOW);
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    chkId = Init_SPI_Flash_All();

    if(((chkId == 0x00BF2641)||(chkId == 0x00EF4015)))
    {
        Initial_SPI_Test_Screen(2,0);
    }
    else
    {
        Initial_SPI_Test_Screen(2,1);
        while(1);
    }
    Delay_1ms(2000);
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
    
    key.bypass = 0;
    key.duty = 0;
    key.function = 0;
    key.increment = 0;
    key.decrement = 0;
    key.enter = 0;
    
    eep.i2c_module = I2C_MODULE1;
    eep.wp_port = 0;
    eep.wp_pin = 0;
    eep.data = 0;    
    eep.phy_add = EEPROM_DEV_ID_HI|EEPROM_BLOCK0|EEPROM_CS;
    eep.memLoc = 0;
    
    I2C_Master_Initialize(eep.i2c_module);     //ASDA1 and ASCL1
//    //UART_Send_String(UART_MODULE1,"I2C1 initialised for external world...!!\r\n");
    
//    I2C_Master_Initialize(I2C_MODULE2);
//    //UART_Send_String(UART_MODULE1,"I2C1 initialised for MCP3427...!!\r\n");
    
    Read_System_Parameters();
    
    Main_Welcome_Screen();
    
    Power_ON_Display();
    
    if(disp_error == 0)
    {
        Calc_CranePara();
        Calc_Parameter_Factors();
    }
    
    Set_Bargraph_Percent(0);
    err_led_status = 0x00;
    
    Clear_System_Flags();
}



void Clear_System_Flags(void)
{
    menu_stat = DEFAULT_PAGE;
    
    poweron_flag1 = 1;     //for len and angle
    poweron_flag2 = 1;     //for P1 and P2
    poweron_flag3 = 1;     //for len and angle
    poweron_flag4 = 1;     //for P1 and P2
    poweron_flag5 = 1;
    FIFO_Cntr1 = 0;
    FIFO_Cntr2 = 0;
    FIFO_Cntr3 = 0;
    FIFO_Cntr4 = 0;
    FIFO_Cntr5 = 0;
    p1_cumulative = 0;
    p2_cumulative = 0;
    p_sampl_cnt = 0;
    len_cumulative = 0;
    angl_cumulative = 0;
    memset(len_adc_buf,0,sizeof(len_adc_buf));
    memset(ang_adc_buf,0,sizeof(ang_adc_buf));
    memset(knuckl_ang_adc_buf,0,sizeof(knuckl_ang_adc_buf));
    memset(p1_adc_buf,0,sizeof(p1_adc_buf));
    memset(p2_adc_buf,0,sizeof(p2_adc_buf));
    la_sampl_cnt = 0;
    calib_mode = 0;  
    ui_key = 0;
    prv_duty = 0;  
    key.bypass = 0;
    key.duty = 0;
    key.function = 0;
    key.increment = 0;
    key.decrement = 0;
    key.enter = 0;
    Previous_Track = 0;
    Current_Track = 0;
    _3TimeFlag = 0;
    _3TimeValue = 0;
    can_175_tout = 5000;
    can_352_tout = 5000;
    tilt1X_ok_flag = 0;
    tilt1Y_ok_flag = 0;
    tilt2X_ok_flag = 0;
    tilt2Y_ok_flag = 0;
    otg_p1_ok_flag = 0;
    otg_p2_ok_flag = 0;
    otg_p3_ok_flag = 0;
    otg_p4_ok_flag = 0;
    track_change_tout = 5000;
    load_ann_timer_case = 0;
    otg_once_flag = 0;
    height_once_flag = 0;
    load_once_flag = 0;
    can_frame_cnt = 0;
    sys_err = 0;
    load_stat = 0;
//    sys.para.crane_page_index = 1;
}


/*============================================================================*/
/*
 * Function      :        Set_Bargraph_Percent.
 * Description   :        Used to set bargraph percentage(0 to 100%).
 * Parameters    :        per-0 to 100% percent.
 * Return        :        None.
*/
/*============================================================================*/
void Set_Bargraph_Percent(uint8_t per)
{
  uint8_t x,i;                      //Number of leds to be ON
  
  x = (per*16)/100;               //16=LED counts  one LED = 6%
  bargraph_status = 0;
  for(i=0; i<x; i++)
  {
    bargraph_status |= 1 << i;
  }
  if(per == 0) bargraph_status = 0;
}


/*==============================================================================*/
/*
 * Function     : Digital_Output_Handler.
 * Description  : Used to turn ON/OFF/BLINK digital outputs.
 * Parameters   : None.
 * Return       : None.
*/
/*==============================================================================*/
void Digital_Output_Handler(void)
{
    switch(op.relay1action)
    {
     if(sys.para.Select_System != WHITELINE_ESCORTS)
     {        
        case OUTPUT_ON:
        {
            digital_output_status |= (OUTPUT_ON << 0);
            op.relay1action = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            digital_output_status |= (OUTPUT_OFF << 0);
            op.relay1action = 0;
            break;
        }
     }    
    }    
//    switch(op.relay2action)
//    {
//        case OUTPUT_ON:
//        {
//            
//            op.relay2action = 0;
//            break;
//        }
//        case OUTPUT_OFF:
//        {
//            
//            op.relay2action = 0;
//            break;
//        }
//        case OUTPUT_BLINK:
//        {
//            
//            op.relay2action = 0;
//            break;
//        }
//    }    
    switch(op.hooteraction)
    {
        case OUTPUT_ON:
        {
            digital_output_status |= (OUTPUT_ON << 2);
            op.hooteraction = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            digital_output_status |= (OUTPUT_OFF << 2);
            op.hooteraction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            digital_output_status |= (OUTPUT_BLINK << 2);
            op.hooteraction = 0;
            break;
        }
    }     
    switch(op.redledaction)
    {
        case OUTPUT_ON:
        {
            digital_output_status |= (OUTPUT_ON << 4);
            op.redledaction = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            digital_output_status |= (OUTPUT_OFF << 4);
            op.redledaction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            digital_output_status |= (OUTPUT_BLINK << 4);
            op.redledaction = 0;
            break;
        }
    }   
    switch(op.greenledaction)
    {
        case OUTPUT_ON:
        {
            digital_output_status |= (OUTPUT_ON << 6);
            op.greenledaction = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            digital_output_status |= (OUTPUT_OFF << 6);
            op.greenledaction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            digital_output_status |= (OUTPUT_BLINK << 6);
            op.greenledaction = 0;
            break;
        }
    }
    switch(op.artledaction)
    {
        case OUTPUT_ON:
        {
            err_led_status |= OVER_ARTICULATION_LED;
            op.artledaction = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            err_led_status &= ~OVER_ARTICULATION_LED;
            op.artledaction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            if(op.artledtout == 0)
            {
                op.artledtout = 100;
                op.artled_bit = !op.artled_bit;
                if(op.artled_bit)   err_led_status |= OVER_ARTICULATION_LED;
                else                err_led_status &= ~OVER_ARTICULATION_LED;
            }
            break;
        }
    }    
    switch(op.nlzledaction)
    {
        case OUTPUT_ON:
        {
            err_led_status |= NLZ_STATUS_LED;
            op.nlzledaction = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            err_led_status &= ~NLZ_STATUS_LED;
            op.nlzledaction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            if(op.nlzledtout == 0)
            {
                op.nlzledtout = 100;
                op.nlzled_bit = !op.nlzled_bit;
                if(op.nlzled_bit)   err_led_status |= NLZ_STATUS_LED;
                else                err_led_status &= ~NLZ_STATUS_LED;
            }
            break;
        }
    }    
    switch(op.a2bledaction)
    {
        case OUTPUT_ON:
        {
            err_led_status |= A2B_STATUS_LED;
            op.a2bledaction = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            err_led_status &= ~A2B_STATUS_LED;
            op.a2bledaction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            if(op.a2bledtout == 0)
            {
                op.a2bledtout = 100;
                op.a2bled_bit = !op.a2bled_bit;
                if(op.a2bled_bit)   err_led_status |= A2B_STATUS_LED;
                else                err_led_status &= ~A2B_STATUS_LED;
            }
            break;
        }
    }    
    switch(op.errledaction)
    {
        case OUTPUT_ON:
        {
            err_led_status |= ERROR_LED;
            op.errledaction = 0;
            break;
        }
        case OUTPUT_OFF:
        {
            err_led_status &= ~ERROR_LED;
            op.errledaction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            if(op.errledtout == 0)
            {
                op.errledtout = 100;
                op.errled_bit = !op.errled_bit;
                if(op.errled_bit)   err_led_status |= ERROR_LED;
                else                err_led_status &= ~ERROR_LED;
            }
            break;
        }
    }
    switch(op.buzzaction)
    {
        case OUTPUT_ON:
        {
            GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_HIGH);
            op.buzzaction = 0;            
            break;
        }
        case OUTPUT_OFF:
        {
            GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_LOW);
            op.buzzaction = 0;
            break;
        }
        case OUTPUT_BLINK:
        {
            if(op.buzztout == 0)
            {
                op.buzztout = 255;
                op.buzz_bit = !op.buzz_bit;
                if(op.buzz_bit) GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_HIGH);
                else            GPIO_Write(GPIO_PORTG,BUZZER_OUT,GPIO_LOW);
            }
            break;
        }
    }
    switch(op.over_tilt_bit)
    {
        case 1:
        {
            err_led_status |= OVER_TILT_LED;
            break;
        }
        case 0:
        {
            err_led_status &= ~OVER_TILT_LED;
            break;
        }
    }
}
void Display_Duty(void)
{
    char sbuf[20];
    
    sprintf(sbuf,"%02d  ",sys.para.duty);
//    Lcd16x2_Out(1,1,sbuf);
}

void Display_LenAngRad(void)
{
    /*
    if(len_adc_cnt > sys.para.low_err_cnt && len_adc_cnt < sys.para.high_err_cnt)
    {
        LengthErr = 0;
        sys_err &= ~SYS_LEN_LOERR_COUNTS;
        sys_err &= ~SYS_LEN_HIERR_COUNTS;
        if(sys.para.sel_uom == 0)
        {
            if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
            {
                if(TotalBmLength > 999)
                {
                    sprintf(sbuf,"%05.1fM",((float)TotalBmLength)/10.0);
                    Lcd16x2_Out(2,5,sbuf);
                }
                else 
                {
                    sprintf(sbuf," %04.1fM",((float)TotalBmLength)/10.0);
                    Lcd16x2_Out(2,5,sbuf);
                }
            }
            else
            {
                TotalBmLength = (uint16_t)(TotalBmLength*3.28);
                if(TotalBmLength > 999)
                {
                    TotalBmLength = TotalBmLength/10;
                    sprintf(sbuf," %03dF ",TotalBmLength);
                    Lcd16x2_Out(2,5,sbuf);
                }
                else
                {
                    sprintf(sbuf," %04.1fF",((float)TotalBmLength)/10.0);
                    Lcd16x2_Out(2,5,sbuf);
                }
            }            
        }
        else
        {
            if(TotalBmLength > 999)
            {
                sprintf(sbuf,"%05.1fM",((float)TotalBmLength)/10.0);
                Lcd16x2_Out(2,5,sbuf);
            }
            else 
            {
                sprintf(sbuf," %04.1fM",((float)TotalBmLength)/10.0);
                Lcd16x2_Out(2,5,sbuf);
            }
        }
    }
    else
    {
        LengthErr = 1;
        if(len_adc_cnt <= sys.para.low_err_cnt)
        {
            Lcd16x2_Out(2,5," LoErr");
            sys_err |= SYS_LEN_LOERR_COUNTS;
        }
        else if(len_adc_cnt >= sys.para.high_err_cnt)
        {            
            Lcd16x2_Out(2,5," HiErr");
            sys_err |= SYS_LEN_HIERR_COUNTS;
        }
    }
    
    if(ang_adc_cnt > sys.para.low_err_cnt && ang_adc_cnt < sys.para.high_err_cnt)
    {
        AngleErr = 0;
        sys_err &= ~SYS_ANG_LOERR_COUNTS;
        sys_err &= ~SYS_ANG_HIERR_COUNTS;
        TempDispBoomAngle = (bm_angle/10);
        sprintf(sbuf,"%02dß ",TempDispBoomAngle);
        Lcd16x2_Out(2,1,sbuf);
    }
    else
    {
        AngleErr =1;
        if(ang_adc_cnt <= sys.para.low_err_cnt)
        {
          Lcd16x2_Out(2,1,"LoEr");
          sys_err |= SYS_ANG_LOERR_COUNTS;
        }
        else
        {
          if(ang_adc_cnt >= sys.para.high_err_cnt)
          Lcd16x2_Out(2,1,"HiEr");
          sys_err |= SYS_ANG_HIERR_COUNTS;
        }
    }
    
    if(sys.para.sel_uom == 0)
    {
        if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            if(Radius1 > 999)
            {
                sprintf(sbuf,"%05.1fM",((float)Radius1)/10.0);
                Lcd16x2_Out(1,5,sbuf);
            }
            else
            {
                sprintf(sbuf," %04.1fM",((float)Radius1)/10.0);
                Lcd16x2_Out(1,5,sbuf);
            }
        }
        else
        {
            Radius1 = (uint16_t)(Radius1*3.28);
            if(Radius1  > 999)
            {
                Radius1 = Radius1 /10;
                sprintf(sbuf," %03dF ",Radius1);
                Lcd16x2_Out(1,5,sbuf);
            }
            else
            {
                sprintf(sbuf," %04.1fF",((float)Radius1)/10.0);
                Lcd16x2_Out(1,5,sbuf);
            }
        }
    }
    else
    {
        if(Radius1 > 999)
        {
            sprintf(sbuf,"%05.1fM",((float)Radius1)/10.0);
            Lcd16x2_Out(1,5,sbuf);
        }
        else
        {
            sprintf(sbuf," %04.1fM",((float)Radius1)/10.0);
            Lcd16x2_Out(1,5,sbuf);
        }
    }*/
}

void Display_PNC_Act_Load(void)
{
    /*
    if((p1_pressure_cnt > sys.para.low_err_cnt) && (p1_pressure_cnt < sys.para.high_err_cnt) && (p2_pressure_cnt > sys.para.low_err_cnt) && (p2_pressure_cnt < sys.para.high_err_cnt))
    {
        PressErr =0;
        sys_err &= ~SYS_P1_LOERR_COUNTS;
        sys_err &= ~SYS_P2_LOERR_COUNTS;
        sys_err &= ~SYS_P1_HIERR_COUNTS;
        sys_err &= ~SYS_P2_HIERR_COUNTS;
        if(sys.para.sel_uom == 0)
        {
            DispLoadVal = (uint16_t)(DispLoadVal*0.22);
            if(DispLoadVal > 999)
            {
                sprintf(sbuf," %04dK",DispLoadVal);
                Lcd16x2_Out(1,11,sbuf);
            }
            else
            {
                sprintf(sbuf,"  %03dK",DispLoadVal);
                Lcd16x2_Out(1,11,sbuf);
            }
        }
        else
        {
            if((sys.para.duty == sys.para.manbas_duty)&&(sys.para.Select_System == ACE_MANBASKET_HXP))
            {
                if(DispLoadVal > 999)
                {
                    sprintf(sbuf," %04dK",DispLoadVal);
                    Lcd16x2_Out(1,11,sbuf);
                }
                else
                {
                    sprintf(sbuf,"  %03dK",DispLoadVal);
                    Lcd16x2_Out(1,11,sbuf);
                }
            }
            else
            {
                if(DispLoadVal > 999)
                {
                    sprintf(sbuf,"%05.1fT",((float)DispLoadVal)/10.0);
                    Lcd16x2_Out(1,11,sbuf);
                }
                else
                {
                    sprintf(sbuf," %04.1fT",((float)DispLoadVal)/10.0);
                    Lcd16x2_Out(1,11,sbuf);
                }
            }
        }
    }
    else
    {
        PressErr = 1;
        if(p1_pressure_cnt <= sys.para.low_err_cnt || p2_pressure_cnt <= sys.para.low_err_cnt)
        {
            Lcd16x2_Out(1,11," LoErr");
            if(p1_pressure_cnt <= sys.para.low_err_cnt) sys_err |= SYS_P1_LOERR_COUNTS;
            else                                        sys_err |= SYS_P2_LOERR_COUNTS;
        }
        else
        {
            if(p1_pressure_cnt >= sys.para.high_err_cnt || p2_pressure_cnt >= sys.para.high_err_cnt)
            Lcd16x2_Out(1,11," HiErr");
            if(p1_pressure_cnt >= sys.para.high_err_cnt) sys_err |= SYS_P1_HIERR_COUNTS;
            else                                         sys_err |= SYS_P2_HIERR_COUNTS;
        }
    }*/
}

void Display_PNC_SWL_Capacity(void)
{
    /*
    if(sys.para.sel_uom == 0)
    {
        Cap1 = (uint16_t)(Cap1*0.22);
        if(Cap1 > 999)
        {
            sprintf(sbuf," %04d",Cap1);
            Lcd16x2_Out(2,11,sbuf);
        }
        else
        {
            sprintf(sbuf,"  %03d",Cap1);
            Lcd16x2_Out(2,11,sbuf);
        }
    }
    else
    {
        if(Cutt_Off_Flag)//if(DispBoomAngle > (BACutOffLimit*10) || (DispBoomAngle < BALowCutOffLimit*10))
        {
            Cap1 = 0;
        }
        if((sys.para.duty == sys.para.manbas_duty)&&(sys.para.Select_System == ACE_MANBASKET_HXP))
        {
            if(Cap1 > 999)
            {
                sprintf(sbuf," %04dK",Cap1);
                Lcd16x2_Out(2,11,sbuf);
            }
            else
            {
                sprintf(sbuf,"  %03dK",Cap1);
                Lcd16x2_Out(2,11,sbuf);
            }
        }
        else
        {
            if(Cap1 > 999)
            {
                sprintf(sbuf,"%05.1fT",((float)Cap1)/10.0);
                Lcd16x2_Out(2,11,sbuf);
            }
            else
            {
                sprintf(sbuf," %04.1fT",((float)Cap1)/10.0);
                Lcd16x2_Out(2,11,sbuf);
            }
        }
    }*/
}

void Display_TMC_Act_Load(void)
{
    /*
    if(sys.para.sel_uom == 0)
    {
        if(DispLoadVal > 999)
        {
            sprintf(sbuf," %04dK",DispLoadVal);
            Lcd16x2_Out(1,11,sbuf);
        }
        else
        {
            sprintf(sbuf,"  %03dK",DispLoadVal);
            Lcd16x2_Out(1,11,sbuf);
        }
    }
    else
    {
        if(DispLoadVal > 999)
        {
            sprintf(sbuf,"%05.2fT",((float)DispLoadVal)*0.001102);
            Lcd16x2_Out(1,11,sbuf);
        }
        else
        {
            sprintf(sbuf," %04.2fT",((float)DispLoadVal)*0.001102);
            Lcd16x2_Out(1,11,sbuf);
        }
    }*/
}


void Display_TMC_SWL_Capacity(void)
{
    /*
    if(sys.para.sel_uom == 0)
    {
        if(Cap1 > 999)
        {
            sprintf(sbuf," %04dK",Cap1);
            Lcd16x2_Out(2,11,sbuf);
        }
        else
        {
            sprintf(sbuf,"  %03dK",Cap1);
            Lcd16x2_Out(2,11,sbuf);
        }
    }
    else
    {
        if(Cap1 > 999)
        {
            sprintf(sbuf,"%05.2fT",((float)Cap1)*0.001);     //0.001102
            Lcd16x2_Out(2,11,sbuf);
        }
        else
        {
            sprintf(sbuf," %04.2fT",((float)Cap1)*0.001);        //0.001102
            Lcd16x2_Out(2,11,sbuf);
        }
    }*/
}

void Forklift_Main_Screen(void)
{
    
    Display_Duty();
/*
    if((p1_pressure_cnt > sys.para.low_err_cnt) && (p1_pressure_cnt < sys.para.high_err_cnt))
    {
        PressErr = 0;
        if(sys.para.sel_uom == 0)       //Kg
        {
            DispLoadVal = (uint16_t)(DispLoadVal*0.22);
            if(DispLoadVal > 999)
            {
                sprintf(sbuf,"LOAD:%04dK",DispLoadVal);
                Lcd16x2_Out(1,7,sbuf);
            }
            else
            {
                sprintf(sbuf,"LOAD:%03dK ",DispLoadVal);
                Lcd16x2_Out(1,7,sbuf);
            }
        }
        else
        {
            if(DispLoadVal > 999)
            {
                sprintf(sbuf,"LOAD:%.1fT",((float)DispLoadVal)/10.0);
                Lcd16x2_Out(1,6,sbuf);
            }
            else
            {
                sprintf(sbuf," LOAD:%04.1fT",((float)DispLoadVal)/10.0);
                Lcd16x2_Out(1,6,sbuf);
            }
        }
    }
    else
    {
        PressErr = 1;
        if(p1_pressure_cnt <= sys.para.low_err_cnt)         Lcd16x2_Out(1,11,"LoErr");
        else if(p1_pressure_cnt >= sys.para.high_err_cnt)   Lcd16x2_Out(1,11,"HiErr");
    }
    if(sys.para.sel_uom == 0)       //Kg
    {
        Cap1 = (unsigned int)(Cap1*0.22);

        if(Cap1 > 999)
        {
            sprintf(sbuf,"%04.1fM  CAP:%04dK",((float)TotalBmLength)/10.0,Cap1);
            Lcd16x2_Out(2,1,sbuf);
        }
        else
        {
            sprintf(sbuf,"%04.1fM   CAP:%03dK",((float)TotalBmLength)/10.0,Cap1);
            Lcd16x2_Out(2,1,sbuf);
        }
    }
    else
    {
        if(bm_angle > (sys.para.hi_cutoff_angl*10) || (bm_angle < sys.para.low_cutoff_angl*10))
        {
            Cap1 = 0;
        }
        sprintf(sbuf,"%04.1fM  CAP:%04.1fT ",((float)TotalBmLength)/10.0,((float)Cap1)/10.0);
        Lcd16x2_Out(2,1,sbuf);
    }*/
}

/*============================================================================*/
/*
 * Function      : Display_Main_Screen.
 * Description   : Used to display main screen all calculated values.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Display_Main_Screen(void)
{
    // err_led_status |= OVER_TILT_LED;
    if((disp_refresh_cnt == 0)&&(menu_stat == DEFAULT_PAGE)&&(disp_error == 0))
    {
        disp_refresh_cnt = 500;
        
        if(sys.para.Select_System == FORK_LIFT)
        {
            Default_Main_Screen_ForkLift(1,sys.para.duty,DispLoadVal,Cap1,TotalBmLength);
        }
        else if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
        {
            if(rig_dty_angl_flag == 0)
                Default_Main_Screen_KnuckleBoom(1);
        }
        else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
        {
            Default_Main_Screen_TMC(1);
        }
        else if(sys.para.Select_System == WHITELINE_ESCORTS)
        {
            if(sys.para.rig_duty_bit == 0)
                Default_Main_Screen_PNC_Whiteline(1);
        }
        else if(sys.para.Select_System == ACE_MANBASKET_HXP)
        {
            if(sys.para.rig_duty_bit == 0)
                Default_Main_Screen_PNC_Manbasket(1);
        }
        else if(sys.para.Select_System == PNC_FORK)
        {
            if(sys.para.rig_duty_bit == 0)
                Default_Main_Screen_PNC_Fork(1);
        }
        else
        {
            if(sys.para.rig_duty_bit == 0)
                Default_Main_Screen_PNC(1,sys.para.duty,TotalBmLength,0,bm_angle,0,Radius1,0,DispLoadVal,Cap1,0);
        }
        //Debug messages
//        sprintf(lbuf,"%02d %02d",TiltAngle_1_X,TiltAngle_1_Y);
//        LCDPutStr(lbuf,10,190, MEDIUM, ILI9341_NAVY, ILI9341_WHITE);
//        sprintf(lbuf,"%02d %02d",TiltAngle_2_X,TiltAngle_2_Y);
//        LCDPutStr(lbuf,10,210, MEDIUM, ILI9341_NAVY, ILI9341_WHITE);
    } 
}


/*============================================================================*/
/*
 * Function      : Default_Main_Screen_Display.
 * Description   : Used to display main screen.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Default_Main_Screen_Display(void)
{
    if(sys.para.Select_System == FORK_LIFT)
    {
        Default_Main_Screen_ForkLift(0,sys.para.duty,0,0,0);
    }
    else if(sys.para.Select_System == PALFINGER_KNUCKLE_BOOM)
    {
        Default_Main_Screen_KnuckleBoom(0);
        Display_Duty_Hint_MainScreen();
    }
    else if((sys.para.Select_System == TMC_MANBASKET)||(sys.para.Select_System == TMC_MANBASKET2))
    {
        Default_Main_Screen_TMC(0);
        Display_Duty_Hint_MainScreen();
    }
    else if(sys.para.Select_System == WHITELINE_ESCORTS)
    {
        Default_Main_Screen_PNC_Whiteline(0);
        Display_Duty_Hint_MainScreen();
    }
    else if(sys.para.Select_System == ACE_MANBASKET_HXP)
    {
        if(sys.para.rig_duty_bit == 0)
            Default_Main_Screen_PNC_Manbasket(0);
    }
    else if(sys.para.Select_System == PNC_FORK)
    {
        if(sys.para.rig_duty_bit == 0)
            Default_Main_Screen_PNC_Fork(0);
    }
    else
    {
        Default_Main_Screen_PNC(0,sys.para.duty,0,0,0,0,0,0,0,0,0);  
        Display_Duty_Hint_MainScreen();
    }
}

/*============================================================================*/
/*
 * Function      : Bar_Graph_Disp.
 * Description   : Draws bargraph according to load and set points.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Bar_Graph_Disp(void)
{
    uint8_t LEDCount=0,i;
    
    PercLoad = (DispLoadVal/(Cap1*0.01));   
	
	if(PercLoad <= sys.para.sp1_perc)							// 10 => Green LEDs 
	{
		LEDCount = (0) + ((PercLoad - 0)/(((sys.para.sp1_perc-0)*1.0)/(GREENLEDS)));
	}
	
	if((PercLoad > sys.para.sp1_perc)&&(PercLoad <= sys.para.sp2_perc))	// 2 => Yellow LEDs 
	{	
		LEDCount = (10) + ((PercLoad - sys.para.sp1_perc)/(((sys.para.sp2_perc-sys.para.sp1_perc)*1.0)/(YELLOWLEDS)));
	}
	
	if((PercLoad > sys.para.sp2_perc)&&(PercLoad <= sys.para.sp3_perc))	// 4 => Red LEDs 
	{	
		LEDCount = (12) + ((PercLoad - sys.para.sp2_perc)/(((sys.para.sp3_perc-sys.para.sp2_perc)*1.0)/(REDLEDS)));
	}
	
	if((PercLoad > sys.para.sp3_perc))
	{
		LEDCount = 16;
	}
    
    for(i=0; i<LEDCount; i++)
    {
        bargraph_status |= 1 << i;
    }
    if(LEDCount < 16)
    {
        for(i=LEDCount-1; i<16; i++)
        {
            bargraph_status &= ~(1 << i);
        }
    }
}

/*============================================================================*/
/*
 * Function      : Marching_Mode.
 * Description   : This is the marching mode of crane.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Marching_Mode(void)
{
    if(LoopCntr < 5)
    {
        LoopCntr++;
    }
    else
    {
        if(bm_angle >= (sys.para.rig_bm_angl_lmt*10))
        {
            sys.para.duty = sys.para.default_duty;
            sys.para.rig_duty_bit = 0;

            color_lcd_draw_rectangle(ILI9341_NAVY,30,75,295,175);
            LCDPutStr("NOT ALLOWED ",95,90,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr("BM ANGLE > SET LIMIT",50,150,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(2000);
        }
        if(bm_length >= (sys.para.rig_bm_len_lmt))
        {
            sys.para.duty = sys.para.default_duty;
            sys.para.rig_duty_bit = 0;
            color_lcd_draw_rectangle(ILI9341_NAVY,30,75,295,175);
            LCDPutStr("NOT ALLOWED ",95,90,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr(" BM LEN > SET LIMIT ",50,150,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(2000);
        }
        if(DispLoadVal >= (sys.para.rig_load_lmt*10))
        {
            sys.para.duty = sys.para.default_duty;
            sys.para.rig_duty_bit = 0;
            color_lcd_draw_rectangle(ILI9341_NAVY,30,75,295,175);
            LCDPutStr("NOT ALLOWED ",95,90,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            LCDPutStr("HK LOAD > SET LIMIT ",50,150,XLARGE, ILI9341_WHITE, ILI9341_NAVY);
            Delay_1ms(2000);
        }
        if(sys.para.rig_duty_bit == 0)
        {
            SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
            memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

            Sector_Erase(SYSTEM_DEFAULT_SECTOR);
            SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
            
            Default_Main_Screen_Display();
        }
    }
   err_led_status |= OVER_ARTICULATION_LED;
   err_led_status |= NLZ_STATUS_LED;
   err_led_status |= A2B_STATUS_LED;
   err_led_status |= ERROR_LED;//OVER_TILT_LED
   err_led_status |= OVER_TILT_LED;
    Set_Bargraph_Percent(100);

    Delay_1ms(500);
    err_led_status &= ~OVER_ARTICULATION_LED;
    err_led_status &= ~NLZ_STATUS_LED;
    err_led_status &= ~A2B_STATUS_LED;
    err_led_status &= ~ERROR_LED;
    err_led_status &= ~OVER_TILT_LED;
    Set_Bargraph_Percent(0);
    Delay_1ms(500);
}

/*============================================================================*/
/*
 * Function      : Clear_Variables.
 * Description   : Used to clear variables.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Clear_Variables(void)
{
    len_adc_cnt = 0;
    ang_adc_cnt = 0;
    p1_pressure_cnt = 0;
    p2_pressure_cnt = 0;
}


/*============================================================================*/
/*
 * Function      : Power_ON_Display.
 * Description   : Used to display system informations.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Power_ON_Display(void)
{
    char l1buf[20],l2buf[20];
    
    if((memcmp(csv_name,"                                ",32) != 0)&&(lc_csv_id > 0))
    {
        sprintf(l1buf,"%010lu",lc_csv_id);
        
        sprintf(l2buf,"%02d/%02d/%04d",csv_dd,csv_mm,csv_yy);   //,csv_hh,csv_mn
        
        Software_Details("PNC_M512_v1.17.3",l1buf,csv_name,l2buf); //UPDATED VERSION 02/05/23
    }
    else
    {
        Software_Details("PNC_M512_v1.17.3","0000000000","NOT AVAILABLE","NOT AVAILABLE");
    }
    
    Delay_1ms(2000);
    
    sprintf(l1buf,"%02d/%02d/%04d",sys.para.insta_dd,sys.para.insta_mm,sys.para.insta_yy);
    sprintf(l2buf,"%05lu",sys.para.so_number);
    Crane_Details(crane_model,crane_make,crane_type,l2buf,l1buf);
    
    Delay_1ms(2000);
}


/*============================================================================*/
/*
 * Function      : Calc_CranePara.
 * Description   : Used to calculate crane parameters.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Calc_CranePara(void)
{
    /********************************************/
    f1 = ((float)sys.para.vertical_offset*1.0);        // (a) x.xxx
    f1 = (f1/1000.0);

    f2 = ((float)sys.para.horizontal_offset*1.0);        // (b) x.xxx
    f2 = (f2/1000.0);
  //  sprintf(lbuf,"sys.para.vertical_offset=%d sys.para.horizontal_offset=%d\r\n",sys.para.vertical_offset,sys.para.horizontal_offset);
    //UART_Send_String(UART_MODULE1,lbuf);

    f3 = atan(f1/f2);
    Gamma_Int_Rad = (uint16_t)(f3*1000);
  //  sprintf(lbuf,"Gamma_Int_Rad=%d\r\n",Gamma_Int_Rad);
  //  UART_Send_String(UART_MODULE1,lbuf);


    f3 = sin((float)Gamma_Int_Rad/1000.0);
    sin_Gamma_Int = (f3*1000);

    f3 = cos((float)Gamma_Int_Rad/1000.0);
    cos_Gamma_Int = (f3*1000);
  //  sprintf(lbuf,"sin_Gamma_Int=%d cos_Gamma_Int=%d\r\n",sin_Gamma_Int,cos_Gamma_Int);
  //  UART_Send_String(UART_MODULE1,lbuf);

    /********************************************/
    f1 = ((float)sys.para.rampivot_offset*1.0);        // x.xxx
    f1 = (f1/1000.0);                        //

    f2 = ((float)sys.para.vertical_offset*1.0);        // x.xxx
    f2 = (f2/1000.0);           //

    f3 = ((float)sys.para.horizontal_offset*1.0);        // x.xxx
    f3 = (f3/1000.0);           //
  //  sprintf(lbuf,"sys.para.rampivot_offset=%d\r\n",sys.para.rampivot_offset);
    //UART_Send_String(UART_MODULE1,lbuf);

    Den_Float = sqrt((f2*f2)+(f3*f3));

    f2 = (f1)*(1/Den_Float);
    constK_Int = (uint16_t)(f2*1000);
  //  sprintf(lbuf,"constK_Int=%d Den_Float=%.3f\r\n",constK_Int,(double)Den_Float);
  //  UART_Send_String(UART_MODULE1,lbuf);
    /************************************************/

    f1 = ((float)sys.para.piston_diameter*1.0);        // x.xxx
    f1 = (f1/2000.0);
  //  sprintf(lbuf,"sys.para.piston_diameter=%d\r\n",sys.para.piston_diameter);
    //UART_Send_String(UART_MODULE1,lbuf);
    PistonArea_Int = (uint16_t)(PI*f1*f1*100000.0);
  //  sprintf(lbuf,"PistonArea_Int=%d\r\n",PistonArea_Int);
  //  UART_Send_String(UART_MODULE1,lbuf);
    /************************************************/

    f1 = ((float)sys.para.rod_diameter*1.0);        // x.xxx
    f1 = (f1/2000.0);
  //  sprintf(lbuf,"sys.para.rod_diameter=%d\r\n",sys.para.rod_diameter);
    //UART_Send_String(UART_MODULE1,lbuf);
    RodArea_Int = (uint16_t)(PI*f1*f1*100000.0);
  //  sprintf(lbuf,"RodArea_Int=%d\r\n",RodArea_Int);
  //  UART_Send_String(UART_MODULE1,lbuf);
    /************************************************/
    DiffArea_Int = (PistonArea_Int - RodArea_Int);
  //  sprintf(lbuf,"DiffArea_Int=%d\r\n",DiffArea_Int);
  //  UART_Send_String(UART_MODULE1,lbuf);
    /************************************************/
}


/*============================================================================*/
/*
 * Function      : Calc_Parameter_Factors.
 * Description   : Used to calculate factors of parameters.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Calc_Parameter_Factors(void)
{
  //====================================================//
  P1Fact =0;        P2Fact =0;        BLFact =0;        BAFact =0;
  //****************************************************//

  P1Fact = (float)((sys.para.calib_pressure1_max - sys.para.calib_pressure1_min)*1.0)/(sys.para.calib_P1HighAdcCount - sys.para.calib_P1LowAdcCount);
  P2Fact = (float) ((sys.para.calib_pressure2_max - sys.para.calib_pressure2_min)*1.0)/(sys.para.calib_P2HighAdcCount - sys.para.calib_P2LowAdcCount);

  //****************************************************

  if(sys.para.cal_angle_max_cnt > sys.para.cal_angle_min_cnt)
  BAFact = (float) ((sys.para.cal_angle_max - sys.para.cal_angle_min)*1.0)/(sys.para.cal_angle_max_cnt - sys.para.cal_angle_min_cnt);
  else
  BAFact = (float) ((sys.para.cal_angle_max - sys.para.cal_angle_min)*1.0)/(sys.para.cal_angle_min_cnt - sys.para.cal_angle_max_cnt);
}



/*============================================================================*/
/*
 * Function      : Update_Memory_Addr.
 * Description   : Used to update address of SPI flash memory.
 * Parameters    : addr - adress to update.
 * Return        : None.
*/
/*============================================================================*/
void Update_Memory_Addr(uint16_t addr)
{
  addr_low = 0;                 addr_high = 0;
  addr_low_byte1 = 0;        addr_low_byte2 = 0;
  addr_high_byte1 = 0;       addr_high_byte2 = 0;

  addr_low = ((addr)*2);
  addr_low_byte1 = (addr_low & 0x00FF);
  addr_low_byte2 = ((addr_low & 0xFF00)>>8);

  addr_high = (addr_low + 1);
  addr_high_byte1 = (addr_high & 0x00FF);
  addr_high_byte2 = ((addr_high & 0xFF00)>>8);
}

/*============================================================================*/
/*
 * Function      : Read_Startup_SPIFlash.
 * Description   : Used to read csv values(Crane make, Crane name, Crane type etc.) from SPI flash. Need to refer index table from SPI memory usage excel sheet.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Read_Startup_SPIFlash(void)
{
    uint16_t TempCount;
    uint8_t sign;
    uint32_t page_add;
    
    //Offsets required to read csv values
    flash_memory_offset = ONE_SECTOR_SIZE + (SYSTEM_DIRECTORY_SIZE*((uint32_t)sys.para.crane_page_index));
    flash_page_addr = flash_memory_offset;
    
    for(TempCount=0;TempCount<16;TempCount++)
    {
        crane_make[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
        if(crane_make[TempCount]==0x20)
        {    
            crane_make[TempCount]='\0';
        }    
    }
    flash_page_addr += TempCount;
        
    for(TempCount=0;TempCount<16;TempCount++)
    {
        crane_model[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);  //crane name
    }
    flash_page_addr += TempCount;

    for(TempCount=0;TempCount<16;TempCount++)
    {
        crane_type[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
    }
    flash_page_addr += TempCount;
    
    lc_max_capacity = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);    
    flash_page_addr += 2;        //max capacity
    
    //Minimum boom length
    lc_bm_length_min = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //maximum boom length
    lc_bm_length_max = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Default Duty
    lc_default_duty = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Maximum Falls
    lc_max_falls = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Vertical offset[A]
    lc_vert_offset = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Horizontal offset[B]
    lc_horiz_offset = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //RamPivot Offset[C]
    lc_rampivo_offset = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //BmCenter line offset[D]
    lc_bmcntrline_offset = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Dia Rod[E]
    lc_rod_diameter = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Dia Piston[F]
    lc_piston_diameter = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Vert. Dist. [G]
    lc_vertical_dist = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Boom Offset Sign
    sign = SPIFlash_Read_Byte(flash_page_addr);
    flash_page_addr += 1;        //add one byte offset

    //Boom Offset
    lc_bm_offset = SPIFlash_Read_Byte(flash_page_addr);
    if(sign)
    {
      lc_bm_offset *= (-1);
    }
    flash_page_addr += 1;        //add one byte offset

    //Fall?s Data Page
    lc_falls_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Duty Cycle Page
    lc_duty_cycle_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Duty Hint Start Page
    lc_duty_hint_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Duty Hint End Page
    lc_duty_hint_page_e = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Duty Table Start
    lc_duty_table_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Duty Table End
    lc_duty_table_page_e = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Total No. of Duty
    lc_total_duty = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //P. Curve Start
    lc_press_curve_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset
//    if((sys.para.Select_System != FORK_LIFT)&&(sys.para.Select_System != TMC_MANBASKET)&&(sys.para.Select_System != TMC_MANBASKET2))
//        if(lc_press_curve_page_s == 0)          //If pressure curve not present then it causes csv error
//            disp_error |= 0x04;

    //P. Curve End
    lc_press_curve_page_e = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Articulation Table Switch
    lc_art_table_switch = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset
        
    //Articulation Start Table
    lc_art_table_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset
    
    if(lc_art_table_switch)
    {
        page_add = (((uint32_t)lc_duty_cycle_page_s-1)*256)+((lc_art_table_page_s-1)*2)+flash_memory_offset;
        lc_art_dty_tbl = SPIFlash_Read_Byte(page_add)*256 + SPIFlash_Read_Byte(page_add+1);
    }

    //No. of Boom Part
    lc_num_of_bm_part = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Tele Present switch
    lc_tele_present_switch = SPIFlash_Read_Byte(flash_page_addr);
    flash_page_addr += 1;        //add one byte offset
    
    //Pressure Curve Switch
    lc_pressure_curve_switch = SPIFlash_Read_Byte(flash_page_addr);
    flash_page_addr += 1;        //add one byte offset

    //SPI File ID
    lc_spi_file_id = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Duty Group Table Start
    lc_duty_group_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Duty Group Table End
    lc_duty_group_page_e = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Hook Discription Table start
    lc_hk_description_page_s = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    flash_page_addr += 2;        //add two bytes offset

    //Hook Discription Table end
    lc_hk_description_page_e = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
    
    if(((int16_t)lc_bm_length_min == (-1))||((int16_t)lc_bm_length_max == (-1)))
    {
        disp_error |= 0x02;
//        UART_Send_String(UART_MODULE1,"csv value error\r\n");
    }
    
    flash_page_addr = ONE_SECTOR_SIZE + SYSTEM_DIRECTORY_SIZE + (13*16);
    
    lc_csv_id = (((uint32_t)SPIFlash_Read_Byte(flash_page_addr))<<24)+(((uint32_t)SPIFlash_Read_Byte(flash_page_addr+1))<<16)+(SPIFlash_Read_Byte(flash_page_addr+2)<<8)+SPIFlash_Read_Byte(flash_page_addr+3);
//    sprintf(lbuf,"lc_csv_id         =%lu\r\n",lc_csv_id);
//    UART_Send_String(UART_MODULE1,lbuf);
    
    if(lc_csv_id > 0)
    {
        flash_page_addr = flash_page_addr + 4;
        csv_dd = SPIFlash_Read_Byte(flash_page_addr);
        
        flash_page_addr++;
        csv_mm = SPIFlash_Read_Byte(flash_page_addr);
        
        flash_page_addr++;
        csv_yy = SPIFlash_Read_Byte(flash_page_addr)*256 + SPIFlash_Read_Byte(flash_page_addr+1);
        
        flash_page_addr += 2;
        csv_hh = SPIFlash_Read_Byte(flash_page_addr);
        
        flash_page_addr++;
        csv_mn = SPIFlash_Read_Byte(flash_page_addr);
        
        flash_page_addr++;
        csv_ss = SPIFlash_Read_Byte(flash_page_addr);
//        sprintf(lbuf,"csv Date:%02d/%02d/%04d %02d:%02d:%02d\r\n",csv_dd,csv_mm,csv_yy,csv_hh,csv_mn,csv_ss);
//        UART_Send_String(UART_MODULE1,lbuf);
        
        flash_page_addr = ONE_SECTOR_SIZE + SYSTEM_DIRECTORY_SIZE + (14*16);
        memset(csv_name,0,33);
        for(TempCount=0;TempCount<32;TempCount++)
        {
            csv_name[TempCount] = SPIFlash_Read_Byte(flash_page_addr+TempCount);
        }
//        UART_Send_String(UART_MODULE1,csv_name);
//        UART_Send_String(UART_MODULE1,"\r\n");
    }
//    if(disp_error == 0)     //If there is no csv error found then read the length calibration points
//    {
//        //Keep these two for loop here only
//        for(RestoreCntr=0; RestoreCntr<lc_total_duty; RestoreCntr++)
//        {
//            flash_page_addr =(((uint32_t)lc_press_curve_page_s-1)*256)+((RestoreCntr*10)*256)+flash_memory_offset;
//            
//            if(RestoreCntr < 12)
//            {
//                sys.para.duty_type[RestoreCntr] = SPIFlash_Read_Byte(flash_page_addr+4)*256 + SPIFlash_Read_Byte(flash_page_addr+5); //read two byte --> 4+5
//            }
//            else break;
//        }
//        for(RestoreCntr=0; RestoreCntr<(lc_total_duty*5); RestoreCntr++)
//        {
//            flash_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256)+((RestoreCntr*2)*256)+flash_memory_offset;
//            
//            if(RestoreCntr < 60)
//            {
//                sys.para.length_array[RestoreCntr] = SPIFlash_Read_Byte(flash_page_addr+2)*256 + SPIFlash_Read_Byte(flash_page_addr+3);
//            }
//            else break;
//        }
//    }
//  for(RestoreCntr=0; RestoreCntr<lc_total_duty; RestoreCntr++)
//  {
//    sys.para.duty_type[RestoreCntr] = (flash.buf[DN_LEN_CALIB_PTS_START+(RestoreCntr*2)]*256) + flash.buf[DN_LEN_CALIB_PTS_START+(RestoreCntr*2)+1];
//    #ifdef DEBUG_MSG
//    sprintf(lbuf,"sys.para.duty_type[%d]    =%d\r\n",RestoreCntr,sys.para.duty_type[RestoreCntr]);
//    //UART_Send_String(UART_MODULE1,lbuf);
//    #endif
//  }

//  for(RestoreCntr=0; RestoreCntr<(lc_total_duty*5); RestoreCntr++)
//  {
//    sys.para.length_array[RestoreCntr] = flash.buf[DN_LEN_CALIB_ARRAY_START+(RestoreCntr*2)]*256 + flash.buf[DN_LEN_CALIB_ARRAY_START+(RestoreCntr*2)+1];
//
//    #ifdef DEBUG_MSG
//    sprintf(lbuf,"sys.para.length_array[%d]=%d\r\n",RestoreCntr,sys.para.length_array[RestoreCntr]);
//    //UART_Send_String(UART_MODULE1,lbuf);
//    #endif
//  }
  /*
  for(RestoreCntr=1; RestoreCntr<=lc_total_duty; RestoreCntr++)
  {
    for(TempCount=0; TempCount<5; TempCount++)
    {
      pc_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256) + ((RestoreCntr-1)*10*256) + TempCount*512 + flash_memory_offset;
      
      pc_sector_quotient = (uint16_t)(pc_page_addr/4096);    //4096=bytes per sector
      pc_sector_remainder = (uint8_t)((pc_page_addr/256)%16);//256=bytes per page and 16=number of pages per sector

      pc_sector = pc_sector_quotient;
      pc_page = pc_sector_remainder;

      sprintf(lbuf,"  %02d %03d %02d %02d  ",lc_total_duty,lc_press_curve_page_s,RestoreCntr,TempCount);
      Lcd16x2_Out(1,1,lbuf);
      sprintf(lbuf,"Sect-%02d  Page-%02d",pc_sector,pc_page);
      Lcd16x2_Out(2,1,lbuf);
      Delay_ms(1500);
      SPIFlash_Read_Sector(pc_sector);
      for(ang=0; ang<90; ang++)
      {
        flash.sector.page[pc_page][(ang*2)+16] = p/256;
        flash.sector.page[pc_page][(ang*2)+17] = p%256;
      }
      if(pc_page == 15)
      {
        Sector_Erase(pc_sector);
        SPIFlash_Write_Sector(pc_sector);
        pc_sector++;
        SPIFlash_Read_Sector(pc_sector);
        for(ang=0; ang<90; ang++)
        {
          flash.sector.page[0][(ang*2)+16] = p/256;
          flash.sector.page[0][(ang*2)+17] = p%256;
        }
      }
      else
      {
        for(ang=0; ang<90; ang++)
        {
          flash.sector.page[pc_page+1][(ang*2)+16] = p/256;
          flash.sector.page[pc_page+1][(ang*2)+17] = p%256;
        }
      }
      Sector_Erase(pc_sector);
      SPIFlash_Write_Sector(pc_sector);
      p++;
    }
  }*/

//  #ifdef DEBUG_MSG
//  UART_Send_String(UART_MODULE1,crane_make);
//  UART_Send_String(UART_MODULE1,"\r\n");
//  UART_Send_String(UART_MODULE1,crane_model);
//  UART_Send_String(UART_MODULE1,"\r\n");
//  UART_Send_String(UART_MODULE1,crane_type);
//  UART_Send_String(UART_MODULE1,"\r\n");
//  sprintf(lbuf,"lc_bm_length_min         =%d\r\n",lc_bm_length_min);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_bm_length_max         =%d\r\n",lc_bm_length_max);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_default_duty          =%d\r\n",lc_default_duty);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_max_falls             =%d\r\n",lc_max_falls);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_vert_offset           =%d\r\n",lc_vert_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_horiz_offset          =%d\r\n",lc_horiz_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_rampivo_offset        =%d\r\n",lc_rampivo_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_bmcntrline_offset     =%d\r\n",lc_bmcntrline_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_rod_diameter          =%d\r\n",lc_rod_diameter);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_piston_diameter       =%d\r\n",lc_piston_diameter);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_vertical_dist         =%d\r\n",lc_vertical_dist);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sign                     =%d\r\n",sign);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_bm_offset             =%d\r\n",lc_bm_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_falls_page_s          =%d\r\n",lc_falls_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_duty_cycle_page_s     =%d\r\n",lc_duty_cycle_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_duty_hint_page_s      =%d\r\n",lc_duty_hint_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_duty_hint_page_e      =%d\r\n",lc_duty_hint_page_e);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_duty_table_page_s     =%d\r\n",lc_duty_table_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_duty_table_page_e     =%d\r\n",lc_duty_table_page_e);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_total_duty            =%d\r\n",lc_total_duty);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_press_curve_page_s    =%d\r\n",lc_press_curve_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_press_curve_page_e    =%d\r\n",lc_press_curve_page_e);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_art_table_switch      =%d\r\n",lc_art_table_switch);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_art_table_page_s      =%d\r\n",lc_art_table_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_num_of_bm_part        =%d\r\n",lc_num_of_bm_part);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_tele_present_switch   =%d\r\n",lc_tele_present_switch);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_pressure_curve_switch =%d\r\n",lc_pressure_curve_switch);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_spi_file_id           =%d\r\n",lc_spi_file_id);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_duty_group_page_s     =%d\r\n",lc_duty_group_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_duty_group_page_e     =%d\r\n",lc_duty_group_page_e);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_hk_description_page_s =%d\r\n",lc_hk_description_page_s);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_hk_description_page_e =%d\r\n",lc_hk_description_page_e);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"lc_art_dty_tbl          =%d\r\n",lc_art_dty_tbl);
//  UART_Send_String(UART_MODULE1,lbuf);
//  #endif
}

/*============================================================================*/
/*
 * Function      : Read_System_Parameters.
 * Description   : Used to load variables and update if necessary system parameters to SPI flash.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Read_System_Parameters(void)
{
    char lbuf[100];
    uint16_t para_siz,rd_index;
    
    para_siz = sizeof(sys.buf);
    sprintf(lbuf,"Sys parameter structure size=%d\r\n",para_siz);
    //UART_Send_String(UART_MODULE1,lbuf);
    
    for(rd_index=1; rd_index<=para_siz; rd_index++)
    {
        sys.buf[rd_index-1] = SPIFlash_Read_Byte(rd_index);
//        sprintf(lbuf,"%d=%d\r\n",rd_index-1,sys.buf[rd_index-1]);
//        UART_Send_String(UART_MODULE1,lbuf);
    }
    
//    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
//    
//    memcpy(sys.buf, flash.buf+SYS_PARA_MEM_BASE_ADDR, sizeof(sys.buf));
    
    if((sys.para.crane_page_index <= 0)||(sys.para.crane_page_index >= 8000))    //If CSV not available(Total pages=8000 for 2MB size SPI flash))
    {
        disp_error |= 0x02;
        LCDPutStr("CSV FILE NOT AVAILABLE",27,195,XLARGE,ILI9341_WHITE,ILI9341_NAVY);
        Delay_1ms(2000);
        strcpy(crane_make,"NOT AVAILABLE   ");
        strcpy(crane_model,"NOT AVAILABLE   ");
        strcpy(crane_type,"NOT AVAILABLE   ");
        Reset_System_Parameters();
    }
    else
    {
        disp_error &= ~0x02;
        Read_Startup_SPIFlash();
    }
    Validate_Variables();
        
    switch(sys.para.sel_sensor)
    {
        case 1: PRCHN = 1.556224;     //1.279844(PCB332R1) //1.556224(6723) //1.401189(PCB332)
        break;
        case 2: PRCHN = 1.073060;
        break;
        case 3: PRCHN = 1.329486;         //1.44  HYDAC 12v
        
        /* PCB332(3.3V)
         Pressure max counts at 400 bar(20mA) = 3967 Counts
         Pressure min counts at   0 bar( 4mA) =  780 Counts

         Difference counts = 3655 - 744 = 2911 Counts

         Maximum pressure = 400 bar = 4078.864 MT/m2

         Pressure for 1 count = PRCHN = Maximum pressure/Difference counts

         PRCHN = 4078.864/2911

         PRCHN = 1.40118996908278941944 MT/m2.
         
         ======================================================================
         PCB344(5V)
         
         Pressure max counts at 400 bar(20mA) = 3276 Counts
         Pressure min counts at   0 bar( 4mA) =  655 Counts

         Difference counts = 3276 - 655 = 2527 Counts

         Maximum pressure = 400 bar = 4078.864 MT/m2

         Pressure for 1 count = PRCHN = Maximum pressure/Difference counts

         PRCHN = 4078.864/2621

         PRCHN = 1.556224 MT/m2.
         */
        break;
        default: break;
    }
    
//    if(flash.buf[FACTORY_DEFAULT_RESET] == 'X')
//    {
//        //UART_Send_String(UART_MODULE1,"\r\nRead_System_Parameters\r\n");
//        
//        memcpy(sys.buf, flash.buf+SYS_PARA_MEM_BASE_ADDR, sizeof(sys.buf));
//        
////        sprintf(lbuf,"Size Of struct = %d\r\n",sizeof(sys.buf));
////        UART_Send_String(UART_MODULE1,lbuf);
//        
//        switch(sys.para.sel_sensor)
//        {
//            case 1: PRCHN = 1.279844;     //1.556224
//            break;
//            case 2: PRCHN = 1.073060;
//            break;
//            case 3: PRCHN = 1.329486;         //1.44  HYDAC 12v
//            /*
//             Pressure max counts at 400 bar(20mA) = 3967 Counts
//             Pressure min counts at   0 bar( 4mA) =  780 Counts
//             
//             Difference counts = 3967 - 780 = 3187 Counts
//             
//             Maximum pressure = 400 bar = 4078.864 MT/m2
//             
//             Pressure for 1 count = PRCHN = Maximum pressure/Difference counts
//             
//             PRCHN = 4078.864/3187
//             
//             PRCHN = 1.279844 MT/m2.
//             */
//            break;
//            default: break;
//        }
////        sys.para.crane_page_index = 1;
//        Read_Startup_SPIFlash();
//        disp_error &= ~0x02;
//    }
//    else
//    {
//        disp_error |= 0x02;
//        strcpy(crane_make,"NOT AVAILABLE   ");
//        strcpy(crane_model,"NOT AVAILABLE   ");
//        strcpy(crane_type,"NOT AVAILABLE   ");        
//    }

  /*sys.para.vertical_offset =  980;

  sys.para.horizontal_offset = 960;

  sys.para.rampivot_offset = 3750;

  sys.para.bm_cntr_line_offset = 220;

  sys.para.piston_diameter = 138;

  sys.para.rod_diameter = 110; */

  sprintf(lbuf,"Radius_Cutoff           =%d\r\n",sys.para.Radius_Cutoff);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.data_log_cntr           =%d\r\n",sys.para.data_log_cntr);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.main_smpl_cnt           =%d\r\n",sys.para.main_smpl_cnt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.num_of_cylinders        =%d\r\n",sys.para.num_of_cylinders);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_smpl_cnt            =%d\r\n",sys.para.cal_smpl_cnt);
  //UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.falls_cnt               =%d\r\n",sys.para.falls_cnt);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.sel_uom                 =%d\r\n",sys.para.sel_uom);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.sp1_perc                =%d\r\n",sys.para.sp1_perc);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.sp2_perc                =%d\r\n",sys.para.sp2_perc);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.sp3_perc                =%d\r\n",sys.para.sp3_perc);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.sp4_perc                =%d\r\n",sys.para.sp4_perc);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.bm_offset               =%d\r\n",sys.para.bm_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_head_offset          =%d\r\n",sys.para.bm_head_offset);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_tip_offset           =%d\r\n",sys.para.bm_tip_offset);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.baudrate                =%d\r\n",sys.para.baudrate);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.art_derate_perc         =%d\r\n",sys.para.art_derate_perc);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_corr_limit         =%d\r\n",sys.para.load_corr_limit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.sel_sensor              =%d\r\n",sys.para.sel_sensor);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"PRCHN                   =%.06f\r\n",(double)PRCHN);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_pressure1_min     =%d\r\n",sys.para.calib_pressure1_min);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_P1LowAdcCount     =%d\r\n",sys.para.calib_P1LowAdcCount);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_pressure1_max     =%d\r\n",sys.para.calib_pressure1_max);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_P1HighAdcCount    =%d\r\n",sys.para.calib_P1HighAdcCount);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_pressure2_min     =%d\r\n",sys.para.calib_pressure2_min);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_P2LowAdcCount     =%d\r\n",sys.para.calib_P2LowAdcCount);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_pressure2_max     =%d\r\n",sys.para.calib_pressure2_max);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.calib_P2HighAdcCount    =%d\r\n",sys.para.calib_P2HighAdcCount);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_angle_min           =%d\r\n",sys.para.cal_angle_min);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_angle_min_cnt       =%d\r\n",sys.para.cal_angle_min_cnt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_angle_max           =%d\r\n",sys.para.cal_angle_max);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_angle_max_cnt       =%d\r\n",sys.para.cal_angle_max_cnt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_length_min           =%d\r\n",sys.para.bm_length_min);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_length_max           =%d\r\n",sys.para.bm_length_max);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_len_min             =%d\r\n",sys.para.cal_len_min);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bl_adc_cnt[1]           =%d\r\n",sys.para.bl_adc_cnt[1]);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bl_adc_cnt[2]           =%d\r\n",sys.para.bl_adc_cnt[2]);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bl_adc_cnt[3]           =%d\r\n",sys.para.bl_adc_cnt[3]);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bl_adc_cnt[4]           =%d\r\n",sys.para.bl_adc_cnt[4]);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bl_adc_cnt[5]           =%d\r\n",sys.para.bl_adc_cnt[5]);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bl_adc_cnt[6]           =%d\r\n",sys.para.bl_adc_cnt[6]);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_len_max             =%d\r\n",sys.para.cal_len_max);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.cal_len_max_cnt         =%d\r\n",sys.para.cal_len_max_cnt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bpk_enable_bit          =%d\r\n",sys.para.bpk_enable_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.hk_height_stat_bit      =%d\r\n",sys.para.hk_height_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.low_err_cnt             =%d\r\n",sys.para.low_err_cnt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.high_err_cnt            =%d\r\n",sys.para.high_err_cnt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.pressure_p1_chann       =%d\r\n",sys.para.pressure_p1_chann);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.pressure_p2_chann       =%d\r\n",sys.para.pressure_p2_chann);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_length_chann         =%d\r\n",sys.para.bm_length_chann);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_angle_chann          =%d\r\n",sys.para.bm_angle_chann);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.min_angle               =%d\r\n",sys.para.min_angle);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.max_angle               =%d\r\n",sys.para.max_angle);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.default_duty            =%d\r\n",sys.para.default_duty);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.rig_duty_bit            =%d\r\n",sys.para.rig_duty_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.rig_load_lmt            =%d\r\n",sys.para.rig_load_lmt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.rig_bm_len_lmt          =%d\r\n",sys.para.rig_bm_len_lmt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.rig_bm_angl_lmt         =%d\r\n",sys.para.rig_bm_angl_lmt);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.pw_stat_bit             =%d\r\n",sys.para.pw_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bmdwn_rly_stat_bit      =%d\r\n",sys.para.bmdwn_rly_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bmup_rly_stat_bit       =%d\r\n",sys.para.bmup_rly_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.hootr_rly_stat_bit      =%d\r\n",sys.para.hootr_rly_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.a2b_stat_bit            =%d\r\n",sys.para.a2b_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_avg_stat_bit     =%d\r\n",sys.para.load_avg_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_avg_val            =%d\r\n",sys.para.load_avg_val);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.window_sample_size1      =%d\r\n",sys.para.window_sample_size1);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.window_sample_size1     =%d\r\n",sys.para.window_sample_size1);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.hook_load               =%d\r\n",sys.para.hook_load);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.group_duty_s            =%d\r\n",sys.para.group_duty_s);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.group_duty_e            =%d\r\n",sys.para.group_duty_e);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.vertical_offset         =%d\r\n",sys.para.vertical_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.horizontal_offset       =%d\r\n",sys.para.horizontal_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.rampivot_offset         =%d\r\n",sys.para.rampivot_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.bm_cntr_line_offset     =%d\r\n",sys.para.bm_cntr_line_offset);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.piston_diameter         =%d\r\n",sys.para.piston_diameter);
//  UART_Send_String(UART_MODULE1,lbuf);
//  sprintf(lbuf,"sys.para.rod_diameter            =%d\r\n",sys.para.rod_diameter);
//  UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_length_corr1         =%d\r\n",sys.para.bm_length_corr1);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_length_corr2         =%d\r\n",sys.para.bm_length_corr2);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_length_corr3         =%d\r\n",sys.para.bm_length_corr3);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bm_length_corr4         =%d\r\n",sys.para.bm_length_corr4);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.fail_safe_stat_bit      =%d\r\n",sys.para.fail_safe_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.hi_cutoff_angl          =%d\r\n",sys.para.hi_cutoff_angl);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.low_cutoff_angl         =%d\r\n",sys.para.low_cutoff_angl);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.duty_select_stat_bit    =%d\r\n",sys.para.duty_select_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.snatch_block_stat_bit =%d\r\n",sys.para.snatch_block_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.snatch_block_val        =%d\r\n",sys.para.snatch_block_val);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.sticker_type            =%d\r\n",sys.para.sticker_type);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.bpk_method_stat_bit   =%d\r\n",sys.para.bpk_method_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_corr1              =%d\r\n",sys.para.load_corr1);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_corr2              =%d\r\n",sys.para.load_corr2);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_corr3              =%d\r\n",sys.para.load_corr3);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_corr4              =%d\r\n",sys.para.load_corr4);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.load_corr5              =%d\r\n",sys.para.load_corr5);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.fact                    =%d\r\n",sys.para.fact);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.perc_fact_stat_bit  =%d\r\n",sys.para.perc_fact_stat_bit);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.correction_load         =%d\r\n",sys.para.correction_load);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.num_cal                 =%d\r\n",sys.para.num_cal);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"sys.para.duty                   =%d\r\n",sys.para.duty);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"Insta.Date:             =%02d/%02d/%04d\r\n",sys.para.insta_dd,sys.para.insta_mm,sys.para.insta_yy);
  //UART_Send_String(UART_MODULE1,lbuf);
  sprintf(lbuf,"Index start page        =%d\r\n",sys.para.crane_page_index);
//  UART_Send_String(UART_MODULE1,lbuf);
}

void Reset_System_Parameters(void)
{
    sys.para.Radius_Cutoff = 0;
        
    sys.para.data_log_cntr = 0;

    sys.para.main_smpl_cnt = 20;

    sys.para.num_of_cylinders = 2;

    sys.para.cal_smpl_cnt = 30;

    sys.para.falls_cnt = 4;

    sys.para.sel_uom = 1;

    sys.para.sp1_perc = 93;

    sys.para.sp2_perc = 98;

    sys.para.sp3_perc = 103;

    sys.para.sp4_perc = 110;

    sys.para.bm_offset = -19;

    sys.para.bm_head_offset = 0;

    sys.para.bm_tip_offset = 0;

    sys.para.baudrate = 1;

    sys.para.art_derate_perc = 0;

    sys.para.load_corr_limit = 0;//30

    sys.para.sel_sensor = 1;

    sys.para.calib_pressure1_min = 0;

    if(sys.para.sel_sensor == 1)
    {
      sys.para.calib_P1LowAdcCount = 655;
    }
    else
    {
      sys.para.calib_P1LowAdcCount = 390;
    }

    if(sys.para.sel_sensor == 1)
    {
      sys.para.calib_pressure1_max = 400;
    }
    else
    {
      sys.para.calib_pressure1_max = 344;
    }

    if(sys.para.sel_sensor == 1)
    {
      sys.para.calib_P1HighAdcCount = 3276;
    }
    else
    {
      sys.para.calib_P1HighAdcCount = 3685;
    }

    sys.para.calib_pressure2_min = 0;

    if(sys.para.sel_sensor == 1)
    {
      sys.para.calib_P2LowAdcCount = 655;
    }
    else
    {
      sys.para.calib_P2LowAdcCount = 390;
    }

    if(sys.para.sel_sensor == 1)
    {
      sys.para.calib_pressure2_max = 400;
    }
    else
    {
      sys.para.calib_pressure2_max = 344;
    }
    if(sys.para.sel_sensor == 1)
    {
      sys.para.calib_P2HighAdcCount = 3276;
    }
    else
    {
      sys.para.calib_P2HighAdcCount = 3685;
    }

    sys.para.cal_angle_min = 0;

    sys.para.cal_angle_min_cnt = 3500;

    sys.para.cal_angle_max = 600;

    sys.para.cal_angle_max_cnt = 1300;

    sys.para.bm_length_min = 59;

    sys.para.bm_length_max = 178;

    sys.para.cal_len_min = sys.para.bm_length_min;

    sys.para.bl_adc_cnt[1] = 0;

    sys.para.bl_adc_cnt[2] = 3000;

    sys.para.bl_adc_cnt[3] = 6000;

    sys.para.bl_adc_cnt[4] = 9000;

    sys.para.bl_adc_cnt[5] = 12000;

    sys.para.bl_adc_cnt[6] = 15000;
    
    sys.para.bl_adc_cnt[7] = 18000;

    sys.para.cal_len_max = sys.para.bm_length_max;

    sys.para.cal_len_max_cnt = 1400;

    sys.para.bpk_enable_bit = 1;

    sys.para.hk_height_stat_bit = 0;

    sys.para.low_err_cnt =0;

    sys.para.high_err_cnt = 4095;

    sys.para.pressure_p1_chann = 1;

    sys.para.pressure_p2_chann = 2;

    sys.para.bm_length_chann = 3;

    sys.para.bm_angle_chann = 4;

    sys.para.manbas_chann = 5;

    sys.para.min_angle = 1;

    sys.para.max_angle = 65;

    sys.para.default_duty = 4;

    sys.para.rig_duty_bit = 0;

    sys.para.rig_load_lmt = 10;

    sys.para.rig_bm_len_lmt = 10;

    sys.para.rig_bm_angl_lmt = 5;

    sys.para.pw_stat_bit = 0;

    sys.para.bmdwn_rly_stat_bit = 1;

    sys.para.bmup_rly_stat_bit = 1;

    sys.para.hootr_rly_stat_bit = 1;

    sys.para.a2b_stat_bit = 1;

    sys.para.load_avg_stat_bit = 1;

    sys.para.load_avg_val = 3;

    sys.para.window_sample_size = 4;

    sys.para.window_sample_size1 = 3;

    sys.para.hook_load = 0;

    sys.para.group_duty_s = 1;

    sys.para.group_duty_e = 6;

    sys.para.vertical_offset = 935;

    sys.para.horizontal_offset = 860;

    sys.para.rampivot_offset = 2750;

    sys.para.bm_cntr_line_offset = 200;

    sys.para.piston_diameter = 125;

    sys.para.rod_diameter = 90;

    sys.para.bm_length_corr1 = 0;

    sys.para.bm_length_corr2 = 0;

    sys.para.bm_length_corr3 = 0;

    sys.para.bm_length_corr4 = 0;

    sys.para.fail_safe_stat_bit = 0;

    sys.para.hi_cutoff_angl = 63;

    sys.para.low_cutoff_angl = -30;

    sys.para.duty_select_stat_bit = 1;

    sys.para.snatch_block_stat_bit = 1;

    sys.para.snatch_block_val = 5;

    sys.para.sticker_type = NEW;

    sys.para.bpk_method_stat_bit = 1;

    sys.para.load_corr_factor = 0;

    sys.para.load_corr1 = 0;

    sys.para.load_corr2 = 0;

    sys.para.load_corr3 = 0;

    sys.para.load_corr4 = 0;

    sys.para.load_corr5 = 0;

    sys.para.fact = 33;

    sys.para.perc_fact_stat_bit = 0;

    sys.para.correction_load = 0;

    sys.para.num_cal = 0;

    sys.para.duty = 4;

    sys.para.insta_dd = 1;
    sys.para.insta_mm = 1;
    sys.para.insta_yy = 2021;

    sys.para.engine_number = 0;

    sys.para.so_number = 0;

    sys.para.bl_fact[0] = 127;

    sys.para.bl_fact[1] = 129;

    sys.para.bl_fact[2] = 124;

    sys.para.bl_fact[3] = 120;

    sys.para.bl_fact[4] = 115;

    sys.para.Select_System = 0;

    sys.para.Tilt1_X_MinAdc = 2200;
    sys.para.Tilt1_Y_MinAdc = 2200;
    sys.para.Max_BLength  = 100;
    sys.para.Max_BAngle  = 60;
    sys.para.Front_tilt_Cutoff = 5;
    sys.para.Rear_tilt_Cutoff = 5;
    sys.para.zload_mask = 3;
    sys.para.load_announce_timer = 5;
    sys.para.voice_of_language = 0;

    sys.para.forkcalib_press_min[0][0] = 0;
    sys.para.forkcalib_press_min[0][1] = 750;
    sys.para.forkcalib_press_min[1][0] = 0;
    sys.para.forkcalib_press_min[1][1] = 750;
    sys.para.forkcalib_press_min[2][0] = 0;
    sys.para.forkcalib_press_min[2][1] = 750;
    sys.para.forkcalib_press_min[3][0] = 0;
    sys.para.forkcalib_press_min[3][1] = 750;
    sys.para.forkcalib_press_min[4][0] = 0;
    sys.para.forkcalib_press_min[4][1] = 750;
    sys.para.forkcalib_press_min[5][0] = 0;
    sys.para.forkcalib_press_min[5][1] = 750;
    sys.para.forkcalib_press_min[6][0] = 0;
    sys.para.forkcalib_press_min[6][1] = 750;
    sys.para.forkcalib_press_min[7][0] = 0;
    sys.para.forkcalib_press_min[7][1] = 750;

    sys.para.forkcalib_press_max[0][0] = 0;
    sys.para.forkcalib_press_max[0][1] = 1500;
    sys.para.forkcalib_press_max[1][0] = 0;
    sys.para.forkcalib_press_max[1][1] = 1500;
    sys.para.forkcalib_press_max[2][0] = 0;
    sys.para.forkcalib_press_max[2][1] = 1500;
    sys.para.forkcalib_press_max[3][0] = 0;
    sys.para.forkcalib_press_max[3][1] = 1500;
    sys.para.forkcalib_press_max[4][0] = 0;
    sys.para.forkcalib_press_max[4][1] = 1500;
    sys.para.forkcalib_press_max[5][0] = 0;
    sys.para.forkcalib_press_max[5][1] = 1500;
    sys.para.forkcalib_press_max[6][0] = 0;
    sys.para.forkcalib_press_max[6][1] = 1500;
    sys.para.forkcalib_press_max[7][0] = 0;
    sys.para.forkcalib_press_max[7][1] = 1500;

    sys.para.fork_len_region[0] = 0;
    sys.para.fork_len_region[1] = 20;
    sys.para.fork_len_region[2] = 40;
    sys.para.fork_len_region[3] = 60;
    sys.para.fork_len_region[4] = 80;
    sys.para.fork_len_region[5] = 100;
    sys.para.fork_len_region[6] = 120;
    sys.para.fork_len_region[7] = 140;

    sys.para.numof_calib_fork = 1;

    sys.para.peaknhold_stat_bit = 0;
    sys.para.load_threshold = 2;

    sys.para.loadcell_cnt_offst = 7000;
    sys.para.manbasket_min = 0;
    sys.para.manbasket_max = 200;

    sys.para.manbas_duty = 6;       //Only for ACE NXP150

    sys.para.main_ang_chann = 7;
    sys.para.cal_mangle_min = 0;
    sys.para.cal_mangle_min_cnt = 3500;
    sys.para.cal_mangle_max = 600;
    sys.para.cal_mangle_max_cnt = 1300;

    sys.para.art_enable_bit = 0;
    memset(sys.para.indopower_art_derate,0,12);

    sys.para.sel_len_drum = 0;
    sys.para.slew_offset = -13;
    sys.para.bm_ht_offset = 0;      //TMC crane

    sys.para.fork_duty = 6;         //NXT150 type crane which has a fork instead of hook
    
    sys.para.boom_parts = lc_num_of_bm_part;
    
    sys.para.numof_len_cal = 2;
    sys.para.frz_load_angl_bit = 0;
    sys.para.set_angle_frz_lod = 60;
    
    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));

    Sector_Erase(FACTORY_DEFAULT_RESET);
    SPIFlash_Write_Sector(FACTORY_DEFAULT_RESET);
}


/*============================================================================*/
/*
 * Function      : Validate_Variables.
 * Description   : Used to load variables and update if necessary system parameters to SPI flash.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Validate_Variables(void)
{
//    SPIFlash_Read_Sector(SYSTEM_DEFAULT_SECTOR);
    
    //Operator settings
    if((sys.para.duty == 0)||(sys.para.duty > 999)||(sys.para.duty > lc_total_duty)) sys.para.duty = lc_default_duty;
    
    if((sys.para.falls_cnt == 0)||(sys.para.falls_cnt > 99))
        sys.para.falls_cnt = lc_max_falls;
    
    if(sys.para.sel_uom > 1)
        sys.para.sel_uom = 0;
    
    //Supervisor settings        
    if((sys.para.sp1_perc == 0)||(sys.para.sp1_perc > 999))
        sys.para.sp1_perc = 93;
    
    if((sys.para.sp2_perc == 0)||(sys.para.sp2_perc > 999))
        sys.para.sp2_perc = 98;
    
    if((sys.para.sp3_perc == 0)||(sys.para.sp3_perc > 999))
        sys.para.sp3_perc = 103;
    
    if((sys.para.sp4_perc == 0)||(sys.para.sp4_perc > 999))
        sys.para.sp4_perc = 120;
    
    if(sys.para.bm_offset > 999)
        sys.para.bm_offset = lc_bm_offset;
    
    if(sys.para.bm_head_offset > 999)
        sys.para.bm_head_offset = 0;
    
    if(sys.para.bm_tip_offset > 999)
        sys.para.bm_tip_offset = 0;
    
    if(sys.para.main_smpl_cnt > 99)
        sys.para.main_smpl_cnt = 0;
    
    if(sys.para.hook_load > 999)
        sys.para.hook_load = 0;
    
    if(sys.para.cal_len_min > 999)
    {
        sys.para.cal_len_min = lc_bm_length_min;
        sys.para.cal_len_min_cnt = 800;
    }
    
    if(sys.para.cal_len_max > 999)
    {
        sys.para.cal_len_max = lc_bm_length_max;
        sys.para.cal_len_max_cnt = 3700;
    }
    
    if(sys.para.cal_angle_min > 999)
    {
        sys.para.cal_angle_min = 0;
        sys.para.cal_angle_min_cnt = 800;
    }
    
    if(sys.para.cal_angle_max > 999)
    {
        sys.para.cal_angle_max = 70;
        sys.para.cal_angle_max_cnt = 3200;
    }
    
    if(sys.para.cal_mangle_min > 999)
    {
        sys.para.cal_mangle_min = 0;
        sys.para.cal_mangle_min_cnt = 800;
    }
    
    if(sys.para.cal_mangle_max > 999)
    {
        sys.para.cal_mangle_max = 0;
        sys.para.cal_mangle_max_cnt = 800;
    }
    
    if(sys.para.numof_calib_fork > 99)
        sys.para.numof_calib_fork = 1;
    
    if(sys.para.calib_pressure1_min > 999)
    {
        sys.para.calib_pressure1_min = 0;
        sys.para.calib_P1LowAdcCount = 744;
    }
    
    if(sys.para.calib_pressure1_max > 999)
    {
        sys.para.calib_pressure1_max = 0;
        sys.para.calib_P1HighAdcCount = 3655;
    }
    
    if(sys.para.calib_pressure2_min > 999)
    {
        sys.para.calib_pressure2_min = 0;
        sys.para.calib_P2LowAdcCount = 744;
    }
    
    if(sys.para.calib_pressure2_max > 999)
    {
        sys.para.calib_pressure2_max = 0;
        sys.para.calib_P2HighAdcCount = 3655;
    }
    
    if(sys.para.rig_load_lmt > 999)
        sys.para.rig_load_lmt = 10;
    
    if(sys.para.rig_bm_len_lmt > 999)
        sys.para.rig_bm_len_lmt = 10;
    
    if(sys.para.rig_bm_angl_lmt > 999)
        sys.para.rig_bm_angl_lmt = 5;
        
    if((sys.para.default_duty == 0)||(sys.para.default_duty > lc_total_duty)) sys.para.default_duty = lc_default_duty;
    
    if(sys.para.engine_number > 9999999999)
        sys.para.engine_number = 0;
    
    if(sys.para.art_derate_perc > 9999)
        sys.para.art_derate_perc = 0;
    
    if(sys.para.low_cutoff_angl > 999)
        sys.para.low_cutoff_angl = -30;
    
    if(sys.para.hi_cutoff_angl > 999)
        sys.para.hi_cutoff_angl = 63;
    
    if(sys.para.snatch_block_val > 9999)
        sys.para.snatch_block_val = 5;
    
    if(sys.para.Tilt1_X_MinAdc > 4000)
        sys.para.Tilt1_X_MinAdc = 2200;
    
    if(sys.para.Tilt1_Y_MinAdc > 4000)
        sys.para.Tilt1_Y_MinAdc = 2200;
    
    if(sys.para.Tilt2_X_MinAdc > 4000)
        sys.para.Tilt2_X_MinAdc = 2200;
    
    if(sys.para.Tilt2_Y_MinAdc > 4000)
        sys.para.Tilt2_Y_MinAdc = 2200;
    
    if(sys.para.Front_tilt_Cutoff > 99)
        sys.para.Front_tilt_Cutoff = 5;
    
    if(sys.para.Rear_tilt_Cutoff > 99)
        sys.para.Rear_tilt_Cutoff = 5;
    
    if(sys.para.voice_of_language > 5)
        sys.para.voice_of_language = 0;
    
    if(sys.para.zload_mask > 999)
        sys.para.zload_mask = 0;
    
    if(sys.para.load_announce_timer > 999)
        sys.para.load_announce_timer = 5;
    
    if(sys.para.Max_BLength > 999)
        sys.para.Max_BLength = 100;
    
    if(sys.para.Max_BAngle > 999)
        sys.para.Max_BAngle = 60;
    
    if(sys.para.bm_ht_offset > 999)
        sys.para.bm_ht_offset = 0;
    
    if(sys.para.loadcell_cnt_offst > 32000)
        sys.para.loadcell_cnt_offst = 7000;
    
    if(sys.para.manbasket_min > 999)
    {
        sys.para.manbasket_min = 0;
        sys.para.manbasket_min_cnt = 7000;
    }
    
    if(sys.para.manbasket_max > 999)
    {
        sys.para.manbasket_max = 200;
        sys.para.manbasket_max_cnt = 17000;
    }
    
    if(sys.para.slew_offset > 999)
        sys.para.slew_offset = -13;
    
    //Site Engg settings
    if((sys.para.pressure_p1_chann == 0)||(sys.para.pressure_p1_chann > 9))
        sys.para.pressure_p1_chann = 1;
    
    if((sys.para.pressure_p2_chann == 0)||(sys.para.pressure_p2_chann > 9))
        sys.para.pressure_p2_chann = 2;
    
    if((sys.para.bm_angle_chann == 0)||(sys.para.bm_angle_chann > 9))
        sys.para.bm_angle_chann = 4;
    
    if((sys.para.bm_length_chann == 0)||(sys.para.bm_length_chann > 9))
        sys.para.bm_length_chann = 3;
    
    if((sys.para.main_ang_chann == 0)||(sys.para.main_ang_chann > 9))
        sys.para.main_ang_chann = 7;
    
    if(sys.para.low_err_cnt > 4000)
        sys.para.low_err_cnt = 0;
    
    if(sys.para.high_err_cnt > 4000)
        sys.para.high_err_cnt = 4000;
    
    if(sys.para.load_corr_factor > 999)
        sys.para.load_corr_factor = 0;
    
    if(sys.para.load_corr_limit > 999)
        sys.para.load_corr_limit = 0;
    
    if(sys.para.bm_length_corr1 > 999)
        sys.para.bm_length_corr1 = 0;
    
    if(sys.para.bm_length_corr2 > 999)
        sys.para.bm_length_corr2 = 0;
    
    if(sys.para.bm_length_corr3 > 999)
        sys.para.bm_length_corr3 = 0;
    
    if(sys.para.bm_length_corr4 > 999)
        sys.para.bm_length_corr4 = 0;
    
    if(sys.para.load_corr1 > 999)
        sys.para.load_corr1 = 0;
    
    if(sys.para.load_corr2 > 999)
        sys.para.load_corr2 = 0;
    
    if(sys.para.load_corr3 > 999)
        sys.para.load_corr3 = 0;
    
    if(sys.para.load_corr4 > 999)
        sys.para.load_corr4 = 0;
    
    if(sys.para.load_corr5 > 999)
        sys.para.load_corr5 = 0;
    
    if(sys.para.load_threshold > 999)
        sys.para.load_threshold = 2;
    
    if((sys.para.bm_length_min == 0)||(sys.para.bm_length_min > 999))
        sys.para.bm_length_min = lc_bm_length_min;
    
    if((sys.para.bm_length_max == 0)||(sys.para.bm_length_max > 999))
        sys.para.bm_length_max = lc_bm_length_max;
    
    //Factory settings    
    if(sys.para.window_sample_size > 99)
        sys.para.window_sample_size = 4;
    
    if(sys.para.window_sample_size1 > 99)
        sys.para.window_sample_size1 = 4;
    
    if(sys.para.num_of_cylinders > 99)
        sys.para.num_of_cylinders = 2;
    
    if((sys.para.sel_sensor == 0)||(sys.para.sel_sensor > 5))
        sys.para.sel_sensor = 1;
    
    if(sys.para.correction_load > 999)
        sys.para.correction_load = 0;
    
    if(sys.para.num_cal > 1)
        sys.para.num_cal = 0;
    
    if(sys.para.so_number > 99999)
        sys.para.so_number = 0; 
    
    if(sys.para.Radius_Cutoff > 999)
        sys.para.Radius_Cutoff = 0;
    
    if(sys.para.fork_duty > 99)
        sys.para.fork_duty = 6;
    
    if(sys.para.manbas_duty > 99)
        sys.para.manbas_duty = 6;
    
    if(sys.para.manbas_chann > 99)
        sys.para.manbas_chann = 5;
    
    if(sys.para.sel_len_drum > 9)
        sys.para.sel_len_drum = 0;
    
    if((sys.para.num_of_cylinders == 0)||(sys.para.num_of_cylinders > 2))
        sys.para.num_of_cylinders = 2;
        
    if(sys.para.Select_System > 99)
        sys.para.Select_System = 0;
    
    if(sys.para.insta_dd > 31)
        sys.para.insta_dd = 1;
    
    if(sys.para.insta_mm > 12)
        sys.para.insta_mm = 1;
    
    if((sys.para.insta_yy > 2100)||(sys.para.insta_yy <= 0))
        sys.para.insta_yy = 2000;
    
    if(sys.para.boom_parts > 9)
        sys.para.boom_parts = lc_num_of_bm_part;
    
    if(sys.para.numof_len_cal > 15)
        sys.para.numof_len_cal = 2;
    
    if(sys.para.set_angle_frz_lod > 99)
    {
        sys.para.frz_load_angl_bit = 0;
        sys.para.set_angle_frz_lod = 60;
    }
    
//    memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
//    Sector_Erase(SYSTEM_DEFAULT_SECTOR);
//    SPIFlash_Write_Sector(SYSTEM_DEFAULT_SECTOR);
}

/*============================================================================*/
/*
 * Function      : Factory_Default_Reset.
 * Description   : Used to set system variables to default values.
 * Parameters    : None.
 * Return        : None.
*/
/*============================================================================*/
void Factory_Default_Reset(void)
{
    uint16_t RestoreCntr;
     
        flash.buf[FACTORY_DEFAULT_RESET] = 'X';
        
        sys.para.Radius_Cutoff = 0;
        
        sys.para.data_log_cntr = 0;
        
        sys.para.main_smpl_cnt = 20;
        
        sys.para.num_of_cylinders = 2;
        
        sys.para.cal_smpl_cnt = 30;
        
        sys.para.falls_cnt = lc_max_falls;
        
        sys.para.sel_uom = 1;
        
        sys.para.sp1_perc = 93;
        
        sys.para.sp2_perc = 98;
        
        sys.para.sp3_perc = 103;
        
        sys.para.sp4_perc = 110;
        
        sys.para.bm_offset = lc_bm_offset;
        
        sys.para.bm_head_offset = 0;
        
        sys.para.bm_tip_offset = 0;
        
        sys.para.baudrate = 1;
        
        sys.para.art_derate_perc = 0;
        
        sys.para.load_corr_limit = 0;//30
        
        //Read duty type - Number of length calibration points
        for(RestoreCntr=0; RestoreCntr<lc_total_duty; RestoreCntr++)
        {
          flash_page_addr =(((uint32_t)lc_press_curve_page_s-1)*256)+((RestoreCntr*10)*256)+flash_memory_offset;
          if(RestoreCntr < 20)
          {
            sys.para.duty_type[RestoreCntr] = SPIFlash_Read_Byte(flash_page_addr+4)*256 + SPIFlash_Read_Byte(flash_page_addr+5); //read two byte --> 4+5
            
            if(sys.para.duty_type[RestoreCntr] == 0) sys.para.duty_type[RestoreCntr] = 1;
            #ifdef DEBUG_MSG
            sprintf(lbuf," sys.para.duty_type[%d]=%d\r\n",RestoreCntr,sys.para.duty_type[RestoreCntr]);
            //UART_Send_String(UART_MODULE1,lbuf);
            #endif
          }
          else break;
        }
        
        //Read duty type - length calibration values
     
        for(RestoreCntr=0; RestoreCntr<(lc_total_duty*5); RestoreCntr++)
        {
          flash_page_addr = (((uint32_t)lc_press_curve_page_s-1)*256)+((RestoreCntr*2)*256)+flash_memory_offset;
          
          if(RestoreCntr < 100)
          {
            sys.para.length_array[RestoreCntr] = SPIFlash_Read_Byte(flash_page_addr+2)*256 + SPIFlash_Read_Byte(flash_page_addr+3);
            if(sys.para.length_array[RestoreCntr] == 0) sys.para.length_array[RestoreCntr] = lc_bm_length_min;
            
            #ifdef DEBUG_MSG
            sprintf(lbuf,"sys.para.length_array[%d]=%d\r\n",RestoreCntr,sys.para.length_array[RestoreCntr]);
            //UART_Send_String(UART_MODULE1,lbuf);
            #endif
          }
          else break;
        }
        
        for(RestoreCntr=0;RestoreCntr<6;RestoreCntr++)
        {
          sys.para.ld_corr_bmup[RestoreCntr] = 0;
        }

        sys.para.sel_sensor = 1;
        
        sys.para.calib_pressure1_min = 0;
        
        if(sys.para.sel_sensor == 1)
        {
            sys.para.calib_P1LowAdcCount = 655;
        }
        else
        {
            sys.para.calib_P1LowAdcCount = 390;
        }

        if(sys.para.sel_sensor == 1)
        {
            sys.para.calib_pressure1_max = 400;
        }
        else
        {
            sys.para.calib_pressure1_max = 344;
        }
        
        if(sys.para.sel_sensor == 1)
        {
            sys.para.calib_P1HighAdcCount = 3276;
        }
        else
        {
            sys.para.calib_P1HighAdcCount = 3685;
        }

        sys.para.calib_pressure2_min = 0;
        
        if(sys.para.sel_sensor == 1)
        {
            sys.para.calib_P2LowAdcCount = 655;
        }
        else
        {
            sys.para.calib_P2LowAdcCount = 390;
        }

        if(sys.para.sel_sensor == 1)
        {
            sys.para.calib_pressure2_max = 400;
        }
        else
        {
            sys.para.calib_pressure2_max = 344;
        }
        if(sys.para.sel_sensor == 1)
        {
            sys.para.calib_P2HighAdcCount = 3276;
        }
        else
        {
            sys.para.calib_P2HighAdcCount = 3685;
        }
        
        sys.para.cal_angle_min = 0;        
        sys.para.cal_angle_min_cnt = 3500;
        
        sys.para.cal_angle_max = 600;        
        sys.para.cal_angle_max_cnt = 1300;
        
        sys.para.bm_length_min = lc_bm_length_min;
        sys.para.cal_len_min = sys.para.bm_length_min;
        sys.para.cal_len_min_cnt = 800;
        
        sys.para.bm_length_max = lc_bm_length_max;        
        
        sys.para.bl_adc_cnt[1] = 0;
        
        sys.para.bl_adc_cnt[2] = 3000;
        
        sys.para.bl_adc_cnt[3] = 6000;
        
        sys.para.bl_adc_cnt[4] = 9000;
        
        sys.para.bl_adc_cnt[5] = 12000;
        
        sys.para.bl_adc_cnt[6] = 15000;
        
        sys.para.bl_adc_cnt[7] = 18000;
        
        sys.para.cal_len_max = sys.para.bm_length_max;
        
        sys.para.cal_len_max_cnt = 1400;
        
        sys.para.bpk_enable_bit = 1;
        
        sys.para.hk_height_stat_bit = 0;
        
        sys.para.low_err_cnt =0;
        
        sys.para.high_err_cnt = 4095;
        
        sys.para.pressure_p1_chann = 1;
        
        sys.para.pressure_p2_chann = 2;
        
        sys.para.bm_length_chann = 3;
        
        sys.para.bm_angle_chann = 4;
        
        sys.para.manbas_chann = 5;
        
        sys.para.min_angle = 1;
        
        sys.para.max_angle = 65;
        
        sys.para.default_duty = lc_default_duty;
        
        sys.para.rig_duty_bit = 0;
        
        sys.para.rig_load_lmt = 10;
        
        sys.para.rig_bm_len_lmt = 10;
        
        sys.para.rig_bm_angl_lmt = 5;
        
        sys.para.pw_stat_bit = 0;
        
        sys.para.bmdwn_rly_stat_bit = 1;
        
        sys.para.bmup_rly_stat_bit = 1;
        
        sys.para.hootr_rly_stat_bit = 1;
        
        sys.para.a2b_stat_bit = 1;
        
        sys.para.load_avg_stat_bit = 1;
        
        sys.para.load_avg_val = 3;
        
        sys.para.window_sample_size = 4;
        
        sys.para.window_sample_size1 = 3;
        
        sys.para.hook_load = 0;
        
        sys.para.group_duty_s = 1;
        
        sys.para.group_duty_e = lc_total_duty;
        
        sys.para.vertical_offset = lc_vert_offset;
        
        sys.para.horizontal_offset = lc_horiz_offset;
        
        sys.para.rampivot_offset = lc_rampivo_offset;
        
        sys.para.bm_cntr_line_offset = lc_bmcntrline_offset;
        
        sys.para.piston_diameter = lc_piston_diameter;
        
        sys.para.rod_diameter = lc_rod_diameter;
        
        sys.para.bm_length_corr1 = 0;
        
        sys.para.bm_length_corr2 = 0;
        
        sys.para.bm_length_corr3 = 0;
        
        sys.para.bm_length_corr4 = 0;
        
        sys.para.fail_safe_stat_bit = 0;
        
        sys.para.hi_cutoff_angl = 63;
        
        sys.para.low_cutoff_angl = -30;
        
        sys.para.duty_select_stat_bit = 1;
        
        sys.para.snatch_block_stat_bit = 1;
        
        sys.para.snatch_block_val = 5;
        
        sys.para.sticker_type = NEW;
        
        sys.para.bpk_method_stat_bit = 1;
        
        sys.para.load_corr_factor = 0;
        
        sys.para.load_corr1 = 0;
        
        sys.para.load_corr2 = 0;
        
        sys.para.load_corr3 = 0;
        
        sys.para.load_corr4 = 0;
        
        sys.para.load_corr5 = 0;
        
        sys.para.fact = 33;
        
        sys.para.perc_fact_stat_bit = 0;
        
        sys.para.correction_load = 0;
        
        sys.para.num_cal = 0;
        
        sys.para.duty = lc_default_duty;
        
        sys.para.insta_dd = 1;
        sys.para.insta_mm = 1;
        sys.para.insta_yy = 2021;
        
        sys.para.engine_number = 0;
        
        sys.para.so_number = 0;
        
        sys.para.bl_fact[0] = 127;
        
        sys.para.bl_fact[1] = 129;
        
        sys.para.bl_fact[2] = 124;
        
        sys.para.bl_fact[3] = 120;
        
        sys.para.bl_fact[4] = 115;
        
        sys.para.Select_System = 0;
        
        sys.para.Tilt1_X_MinAdc = 2020;
        sys.para.Tilt1_Y_MinAdc = 2020;
        sys.para.Max_BLength  = 100;
        sys.para.Max_BAngle  = 60;
        sys.para.Front_tilt_Cutoff = 5;
        sys.para.Rear_tilt_Cutoff = 5;
        sys.para.zload_mask = 3;
        sys.para.load_announce_timer = 5;
        sys.para.voice_of_language = 0;
        
        sys.para.forkcalib_press_min[0][0] = 0;
        sys.para.forkcalib_press_min[0][1] = 750;
        sys.para.forkcalib_press_min[1][0] = 0;
        sys.para.forkcalib_press_min[1][1] = 750;
        sys.para.forkcalib_press_min[2][0] = 0;
        sys.para.forkcalib_press_min[2][1] = 750;
        sys.para.forkcalib_press_min[3][0] = 0;
        sys.para.forkcalib_press_min[3][1] = 750;
        sys.para.forkcalib_press_min[4][0] = 0;
        sys.para.forkcalib_press_min[4][1] = 750;
        sys.para.forkcalib_press_min[5][0] = 0;
        sys.para.forkcalib_press_min[5][1] = 750;
        sys.para.forkcalib_press_min[6][0] = 0;
        sys.para.forkcalib_press_min[6][1] = 750;
        sys.para.forkcalib_press_min[7][0] = 0;
        sys.para.forkcalib_press_min[7][1] = 750;
        
        sys.para.forkcalib_press_max[0][0] = 0;
        sys.para.forkcalib_press_max[0][1] = 1500;
        sys.para.forkcalib_press_max[1][0] = 0;
        sys.para.forkcalib_press_max[1][1] = 1500;
        sys.para.forkcalib_press_max[2][0] = 0;
        sys.para.forkcalib_press_max[2][1] = 1500;
        sys.para.forkcalib_press_max[3][0] = 0;
        sys.para.forkcalib_press_max[3][1] = 1500;
        sys.para.forkcalib_press_max[4][0] = 0;
        sys.para.forkcalib_press_max[4][1] = 1500;
        sys.para.forkcalib_press_max[5][0] = 0;
        sys.para.forkcalib_press_max[5][1] = 1500;
        sys.para.forkcalib_press_max[6][0] = 0;
        sys.para.forkcalib_press_max[6][1] = 1500;
        sys.para.forkcalib_press_max[7][0] = 0;
        sys.para.forkcalib_press_max[7][1] = 1500;
        
        sys.para.fork_len_region[0] = 0;
        sys.para.fork_len_region[1] = 20;
        sys.para.fork_len_region[2] = 40;
        sys.para.fork_len_region[3] = 60;
        sys.para.fork_len_region[4] = 80;
        sys.para.fork_len_region[5] = 100;
        sys.para.fork_len_region[6] = 120;
        sys.para.fork_len_region[7] = 140;
        
        sys.para.numof_calib_fork = 1;
        
        sys.para.peaknhold_stat_bit = 0;
        sys.para.load_threshold = 2;
        
        sys.para.loadcell_cnt_offst = 7000;
        sys.para.manbasket_min = 0;
        sys.para.manbasket_min_cnt = 7000;
        sys.para.manbasket_max = 200;
        sys.para.manbasket_max_cnt = 32000;
        
        sys.para.manbas_duty = 6;       //Only for ACE NXP150
        
        sys.para.main_ang_chann = 7;
        sys.para.cal_mangle_min = 0;
        sys.para.cal_mangle_min_cnt = 3500;
        sys.para.cal_mangle_max = 600;
        sys.para.cal_mangle_max_cnt = 1300;
        
        sys.para.art_enable_bit = 0;
        memset(sys.para.indopower_art_derate,0,12);
        
        sys.para.sel_len_drum = 0;
        sys.para.slew_offset = -13;
        sys.para.bm_ht_offset = 0;      //TMC crane
        
        sys.para.fork_duty = 6;         //NXT150 type crane which has a fork instead of hook
        
        sys.para.obtilt_enable_bit = 0;
        sys.para.slave_enable_bit = 0;
        sys.para.mpoint_len_enable_bit = 0;
        
        for(RestoreCntr=0; RestoreCntr<16; RestoreCntr++)
        {
            sys.para.multipt_lcalib[RestoreCntr][0] = 0;
            sys.para.multipt_lcalib[RestoreCntr][1] = 0;
        }
        sys.para.multipt_lcalib[0][0] = sys.para.bm_length_min;
        sys.para.multipt_lcalib[0][1] = 500;

        sys.para.multipt_lcalib[1][0] = sys.para.bm_length_min+10;
        sys.para.multipt_lcalib[1][1] = 1500;
        
        sys.para.boom_parts = lc_num_of_bm_part;
        
        sys.para.numof_len_cal = 2;
        sys.para.frz_load_angl_bit = 0;
        sys.para.set_angle_frz_lod = 60;
        
        memcpy(flash.buf+SYS_PARA_MEM_BASE_ADDR,sys.buf, sizeof(sys.buf));
        
        Sector_Erase(FACTORY_DEFAULT_RESET);
        SPIFlash_Write_Sector(FACTORY_DEFAULT_RESET);
}


//==================================EOF=========================================

