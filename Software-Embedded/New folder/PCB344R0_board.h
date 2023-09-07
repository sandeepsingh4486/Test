/* 
 * File:   PCB344R0_board.h
 * Author: Edesign3
 *
 * Created on December 14, 2022, 3:50 PM
 */

#ifndef PCB344R0_BOARD_H
#define	PCB344R0_BOARD_H


#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "adc1.h"
#include "Opamp.h"
#include "uart.h"
#include "spi.h"
#include "i2c.h"
#include "tmr1.h"
#include "tmr2.h"
#include "tmr3.h"
#include "tmr4.h"
#include "tmr5.h"
#include "tmr6.h"
#include "tmr7.h"
#include "tmr8.h"
#include "tmr9.h"
#include "rtcc.h"
#include "gpio.h"
#include "ppm_select.h"

//Devices
#include "SPI_Flash.h"
#include "LED_Scanner.h"
#include "mp3.h"
#include "mcp3427.h"

#include "ecan1_config.h"
#include "ecan1drv.h"
#include "ecan_common.h"

#include "Length_Angle_Radius.h"
#include "Modify_Integer.h"
#include "Lib_Interpolation.h"
#include "csv_pickup.h"


#ifdef DISPLAY_16x2
//Display 16x2 specific definitions
#include "System.h"
#include "define.h"
#include "Gui_Menus.h"
#include "Display_16x2.h"
#include "ACE_NX360.h"
#else 
#ifdef DISPLAY_TFT32
//Display TFT32 specific definitions
#include "TFT32_System.h"
#include "TFT32_define.h"
#include "Display_TFT32.h"
#include "TFT32_Api.h"
#include "TFT32_Menus.h"
#include "TFT32_Gui_Menus.h"
#include "Eeprom_24AA1025.h"
#else
#ifdef DISPLAY_192x64
//Display TFT32 specific definitions
#include "GLCD192x64_main.h"
#endif
#endif
#endif



typedef struct UART_P
{
    uint32_t baudrate;
    uint8_t tx_RPn;     //RPn
    uint8_t rx_RPIn;     //RPIn
    uint8_t intr:1;     //Interrup enable=1/disable=0
    uint8_t resrv1:7;
    uint8_t resrv2;
}UART_P;

extern UART_P uarts;

typedef struct SPI_P
{
    uint8_t mosi_pin;       //RPn
    uint8_t miso_pin;         //RPIn
    uint8_t sck_pin;         //RPn 
    uint8_t mode;           //Mode 0/1/2/3
}SPI_P;

extern SPI_P spis;


typedef struct TIMER_P
{
    float msec;     //Milisecond time from 10uSec to 200mSec eg. 10usec = 0.01mSec
}TIMER_P;

extern TIMER_P tims;

typedef struct ECAN_P
{
    uint32_t bitrate;
    uint8_t tx_RPn;     //RPn
    uint8_t rx_RPIn;     //RPIn
    uint8_t resrv1;
    uint8_t resrv2;
}ECAN_P;

extern ECAN_P ecan;
extern mID can_tx,can_rx;


//Keypad Pins
#define KEY_SW1            8    //LATEbits.LATE8
#define KEY_SW2            4    //LATDbits.LATD4
#define KEY_SW3            3    //LATDbits.LATD3
#define KEY_SW4            2    //LATDbits.LATD2
#define KEY_SW5            1    //LATDbits.LATD1
#define KEY_SW6            7    //LATAbits.LATA7



//UART Pins
#define U1_DEBUG_RX_D12             12  //RD12
#define U1_DEBUG_TX_D5              5   //RD5

#define U2_IOT_RX_G9                9   //RG9
#define U2_IOT_TX_G6                6   //RG6

#define U3_TELE_RX_F0               0   //RF0
#define U3_TELE_TX_F1               1   //RF1

#define U4_PIC25K80_RX_B12      12  //RB12(RPI44)
#define U4_PIC25K80_TX_G13      13  //RG13(RP125)


//Lcd 16x2 module connections. Here we need to mention the exact GPIO number of the Microcontroller for the LCD pins
#define RS_PIN_16x2              7    //LATCbits.LATC7
#define EN_PIN_16x2              6    //LATCbits.LATC6 //LATB5_bit
#define D4_PIN_16x2              6    //LATDbits.LATD6
#define D5_PIN_16x2              9    //LATCbits.LATC9 //LATB1_bit
#define D6_PIN_16x2              6    //LATFbits.LATF6 //LATB2_bit
#define D7_PIN_16x2              7    //LATFbits.LATF7 //LATB3_bit
#define LCD_BL_16x2              13   //LATFbits.LATF13


//3.2" TFT module Connections.
#define TFT32_CS            7   //LATFbits.LATF7        //8    //LATCbits.LATC8 
#define TFT32_CD            6   //LATFbits.LATF6        //5    //LATDbits.LATD5
//#define TFT32_RST           13  //LATBbits.LATB13
//#define TFT32_RST           12  //LATFbits.LATF12
#define TFT32_RST           7  //LATCbits.LATC7


//LED Pins
//LED matrix 5x4. Here we need to mention the exact GPIO number of the Microcontroller for the LED pins
#define LED_COL1            1     //LATEbits.LATE1      //12    //LATFbits.LATF12
#define LED_COL2            15    //LATAbits.LATA15     //12    //LATEbits.LATE12
#define LED_COL3            2     //LATGbits.LATG2      //13    //LATEbits.LATE13 
#define LED_COL4            12    //LATDbits.LATD12     //14    //LATDbits.LATD14 
#define LED_COL5            12    //LATFbits.LATF12     //15    //LATDbits.LATD15  

#define LED_ROW1            3    //LATGbits.LATG3
#define LED_ROW2            4    //LATFbits.LATF4
#define LED_ROW3            5    //LATFbits.LATF5 
#define LED_ROW4            5    //LATDbits.LATD5       //2    //LATGbits.LATG2 

//LED matrix 6x5
#define TFT32LED_COL1            7    //LATCbits.LATC7
#define TFT32LED_COL2            6    //LATCbits.LATC6
#define TFT32LED_COL3            13   //LATFbits.LATF13
#define TFT32LED_COL4            8    //LATGbits.LATG8
#define TFT32LED_COL5            7    //LATGbits.LATG7
#define TFT32LED_COL6            15   //LATAbits.LATA15

#define TFT32LED_ROW1            3    //LATGbits.LATG3
#define TFT32LED_ROW2            4    //LATFbits.LATF4
#define TFT32LED_ROW3            5    //LATFbits.LATF5 
#define TFT32LED_ROW4            5    //LATDbits.LATD5
#define TFT32LED_ROW5            1    //LATEbits.LATE1



//SPI flash IC
//Here we need to mention the exact GPIO number of the Microcontroller for chip select of the SPI flash pin
#define CS_FLASH            10    //LATBbits.LATB10 
#define WP_FLASH            9    //LATEbits.LATE9

#define CS2_FLASH           6    //LATCbits.LATC6 
#define WP2_FLASH           6    //LATDbits.LATD6

#define SPI_MISO_PIN                12


//ADC channels from internal OPAMPs. Here we need to mention the exact analog channel number of the Microcontroller for the ADC input pins
#define CHANNEL_AN9            9        //AI2(Analog input 2)->AN9(RA11)
#define CHANNEL_AN10           10       //AI1(Analog input 1)->AN10(RA12)
#define CHANNEL_AN11           11       //AI3(Analog input 3)->AN11(RC11)
#define CHANNEL_AN22           22       //AI4(Analog input 4)->AN22(RG10)

//ADC channels from external OPAMPs. Here we need to mention the exact analog channel number of the Microcontroller for the ADC input pins
#define CHANNEL_AN28           28       //AI8(Analog input 8)->AN28(RA9)
#define CHANNEL_AN29           29       //AI7(Analog input 7)->AN29(RC3)
#define CHANNEL_AN30           30       //AI6(Analog input 6)->AN30(RC4)
#define CHANNEL_AN31           31       //AI5(Analog input 5)->AN31(RC5)

//Respective GPIOs for ADC. Here we need to mention the exact GPIO number of the Microcontroller for ADC input pins
#define ANALOG_AN9          11        //TRISAbits.TRISA11
#define ANALOG_AN10         12        //TRISAbits.TRISA12
#define ANALOG_AN11         11        //TRISCbits.TRISC11
#define ANALOG_AN22         10        //TRISGbits.TRISG10
#define ANALOG_AN28         9        //TRISAbits.TRISA9
#define ANALOG_AN29         3        //TRISCbits.TRISC3
#define ANALOG_AN30         4        //TRISCbits.TRISC4
#define ANALOG_AN31         5        //TRISCbits.TRISC5

//GPIOs for internal OPAMPs. Here we need to mention the exact GPIO number of the Microcontroller for OPAMPs input/outputs pins
#define OA1OUT_ANN          1        //TRISBbits.TRISB1
#define OA1IN1_ANN          2        //TRISBbits.TRISB2
#define OA1IN2_ANN          3        //TRISBbits.TRISB3
#define OA2OUT_ANN          0        //TRISAbits.TRISA0
#define OA2IN1_ANN          1        //TRISAbits.TRISA1
#define OA2IN2_ANN          0        //TRISBbits.TRISB0
#define OA3OUT_ANN          0        //TRISCbits.TRISC0
#define OA3IN1_ANN          2        //TRISCbits.TRISC2
#define OA3IN2_ANN          1        //TRISCbits.TRISC1
#define OA5OUT_ANN          7        //TRISBbits.TRISB7
#define OA5IN1_ANN          4        //TRISAbits.TRISA4
#define OA5IN2_ANN          9        //TRISBbits.TRISB9


//GPIOs for digital inputs. Here we need to mention the exact GPIO number of the Microcontroller for digital input pins
#define DIGITAL_IN4         10        //PORTAbits.RA10
#define DIGITAL_IN3         13        //PORTBbits.RB13
#define DIGITAL_IN2         12        //PORTBbits.RB12
#define DIGITAL_IN1         13        //PORTGbits.RG13

//GPIOs for digital outputs. Here we need to mention the exact GPIO number of the Microcontroller for digital output pins
//#define RELAY1_OUT          14        //LATAbits.LATA14     //bm_dn_rly_stat
//#define RELAY2_OUT          13        //LATCbits.LATC13     //hooter_rly_stat
#define RELAY2_OUT          14        //LATAbits.LATA14     //bm_dn_rly_stat
#define RELAY1_OUT          13        //LATCbits.LATC13     //hooter_rly_stat
#define RELAY3_OUT          8        //LATBbits.LATB8
#define BUZZER_OUT          11        //LATGbits.LATG11

//LCD16x2 Pins
//Lcd 16x2 module connections. Here we need to mention the exact GPIO number of the Microcontroller for the LCD pins
#define RS_PIN_16x2              7    //LATCbits.LATC7
#define EN_PIN_16x2              6    //LATCbits.LATC6 //LATB5_bit
#define D4_PIN_16x2              6    //LATDbits.LATD6
#define D5_PIN_16x2              9    //LATCbits.LATC9 //LATB1_bit
#define D6_PIN_16x2              6    //LATFbits.LATF6 //LATB2_bit
#define D7_PIN_16x2              7    //LATFbits.LATF7 //LATB3_bit
#define LCD_BL_16x2              13   //LATFbits.LATF13

//EEPROM IC 24AA1025 with PHY address 0xA0
#define EEPROM_DEV_ID_HI       0xA0
#define EEPROM_BLOCK0          0x00
#define EEPROM_BLOCK1          0x08
#define EEPROM_CS              0x00
//#define EEPROM_READ            0x01
//#define EEPROM_WRITE           0x00

//#define EEPROM_ACK             0x01
//#define EEPROM_NOACK           0x00

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PCB344R0_BOARD_H */

