
#include <stdint.h>

uint16_t AI1_Filter(void);
uint16_t AI2_Filter(void);
uint16_t AI3_Filter(void);
uint16_t AI4_Filter(void);

uint16_t AI5_Filter(void);
uint16_t AI6_Filter(void);
uint16_t AI7_Filter(void);
uint16_t AI8_Filter(void);

uint16_t MCP3427_Adc_Filter(uint8_t chan);
uint16_t Read_dsPIC_AnalogIn(uint8_t ai);

void CAN_Handler(void);
void CAN_Receive(void);

void Length_Adc_Fifo(uint16_t adc_cnt);
void Angle_Adc_Fifo(uint16_t adc_cnt);
void Main_Angle_Adc_Fifo(uint16_t adc_cnt);
void P1_Adc_Fifo(uint16_t adc_cnt);
void P2_Adc_Fifo(uint16_t adc_cnt);

void ACE_NX360_Logic_Handler(void);
void Send_Telematics_data(void);
void Analog_Data_Read(void);
void Parse_Uart_Data(void);
void Send_Data_25K80(void);
uint16_t AN28_Adc_Filter(void);
uint16_t AN29_Adc_Filter(void);
uint16_t AN30_Adc_Filter(void);
uint16_t AN31_Adc_Filter(void);
void Analog_Data_Process(void);
void Data_Process(void);
void Calculate_Len_Radius(void);
void Fork_Height(void);
void Ckeck_Load_Value(void);
void BmUp_NLZ_CutOff(void);
void BmDn_NLZ_CutOff(void);
void CalcLengthCalib(void);
void Interpolation(void);
void CheckLoadVal(void);
void CapCalData(void);
void Process_Len_Angle_Data(void);
uint8_t Read_CAN_Adc_Data(void);
void Apply_Load_Corrections(void);
uint8_t Check_Errors_In_AR(void);
void Length_Correction(void);
void Length_Correction_Forklift(void);
void Manbasket_Load_Cal_Func(uint16_t lc_cnt);
void OTG_Tilt_Monitor(void);
void Tilt_Monitor(void);
void Apply_PickNhold_Logic(void);
uint8_t Check_Flags(void);
void Common_Logic_Handler(void);
uint16_t Calculate_CRC(char *data);
float RoundOff(float x);
void Bypasskey_Action(void);
float map(float x, float in_min, float in_max, float out_min, float out_max);

void Do_Len_MPoint_Sorting(uint8_t mpoint);

void Send_Pressure_Curve_Uart(void);









