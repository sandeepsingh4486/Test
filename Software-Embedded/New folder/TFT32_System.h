/* 
 * File:   System.h
 * Author: Edesign3
 *
 * Created on 7 July, 2021, 3:43 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

void Default_Main_Screen_Display(void);
void System_Initialize(void);
void Init_Keypad(void);
void Keypad_Scan(void);

void System_Init(void);
void Bar_Graph_Disp(void);
void Set_Bargraph_Percent(uint8_t per);
void Marching_Mode(void);
void Power_ON_Display(void);
void Get_Len_Angle_Radius(void);
void Calc_CranePara(void);
void Calc_Parameter_Factors(void);
void Read_Startup_SPIFlash(void);
void Update_Memory_Addr(uint16_t addr);
void Read_System_Parameters(void);
void Update_System_Parameters(void);
void Factory_Default_Reset(void);
void Display_Main_Screen(void);
void Uom_Display(void);
void Clear_Variables(void);
void Status_LED_Output_Action(void);
void Monitor_Digital_Input(void);
//void CAN_Handler(void);
//void CAN_Receive(void);
void Digital_Output_Handler(void);


void Clear_System_Flags(void);
void Forklift_Main_Screen(void);
void Display_Duty(void);
void Display_LenAngRad(void);
void Display_PNC_Act_Load(void);
void Display_TMC_Act_Load(void);
void Display_PNC_SWL_Capacity(void);
void Display_TMC_SWL_Capacity(void);
void Validate_Variables(void);
void Check_RST_Password(void);
void Reset_System_Parameters(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

