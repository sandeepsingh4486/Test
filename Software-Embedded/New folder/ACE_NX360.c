/*
 * File:   ACE_NX360.c
 * Author: Nitin Shankar k
 *
 * Created on December 25, 2021, 9:46 AM
 */


#include "main.h"



//==============================================================================
void change_Mode(uint8_t Slew_Mode)
{
    if(Slew_Mode == 0)
	{
        Lcd16x2_Out(1,1,"PICK&CARRY MODE ");
	}
	else if(Slew_Mode == 1)
	{
        Lcd16x2_Out(1,1,"SLEW MODE        ");
	}
	else
	{
		Lcd16x2_Out(1,1,"    NO LOAD     ");
        Lcd16x2_Out(2,1,"     ZONE       ");
	}
    Lcd16x2_Out(2,1," Slew Pin:       ");
    
    if(!Slew_CAN)
    {
       Lcd16x2_Out(2,12,"0");
    }
	else
	{
      Lcd16x2_Out(2,12,"1");
    }
    Delay_1ms(1000);
}

