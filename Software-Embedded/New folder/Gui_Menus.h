
#ifndef GUI_MENUS_H
#define GUI_MENUS_H

void Shift_Cursor_Position(uint8_t flag_lr, uint8_t num_of_dig,uint8_t decimal_pos);
void Gui(void);
void TFT32_Gui(void);
void Modify_System_Parameter(uint8_t digits, uint8_t action, uint8_t cur_pos, uint32_t *para);
void Display_Main_Menu(void);
void Main_Menus(void);
void Select_Main_Menu(void);
void Login_Menu(void);
void Move_Cursor_Left(uint8_t pos);
void Move_Cursor_Right(uint8_t pos);
void Show_Enable_Disable_Stat(uint8_t curr);
void Show_Case_Stat(uint8_t curr);
void Show_Enable_Disable_String(uint8_t curr);
void Show_Yes_No_Stat(uint8_t curr);

void Display_Operator_View_Menu(void);
void Select_Operator_View_Menu(void);
void Operator_Viewing(void);
void Show_Live_ADC_Count(void);
void Choose_Duty(void);
void Choose_UOM(void);
void Display_Dummy_Calib_Length_Menu(void);
void Display_MinMax_Option_Menu(void);
void Display_Fork_MinMax_Press_View(uint8_t pindex, uint8_t minmax);

void Display_Operator_Set_Menu(void);
void Select_Operator_Set_Menu(void);
void Operator_Set_Cursor_Position(void);
void Operator_Change_Parameter_Value(uint8_t flag_id);
void Operator_Setting(void);
void Duty_Hint(uint16_t Duty_no);
void Operator_Save_Settings(void);
void Display_Pressure_Curve_Counts(uint8_t flag_id);

void Display_Supervisor_Set_Menu(void);
void Display_Duty_Type_Menu(void);
void Duty_Type_Cursor_Position(void);
void Duty_Type_Shift_Cursor(uint8_t flag_lr);
void Duty_Type_Change_Parameter_Value(uint8_t flag_id);
void Display_Length_Calib_Menu(void);
void Length_Calib_Cursor_Position(void);
void Length_Calib_Shift_Cursor(uint8_t flag_lr);
void Length_Calib_Change_Parameter_Value(uint8_t flag_id);
void Display_Calib_Hook_Load_Menu(void);
void Calib_Hook_Load_Cursor_Position(void);
void Calib_Hook_Load_Shift_Cursor(uint8_t flag_lr);
void Calib_Hook_Load_Change_Parameter_Value(uint8_t flag_id);
void Display_Calib_Length_Angle(void);
void Supervisor_Show_Live_Adc(void);
void Choose_Yes_No(void);

void Display_Select_Calib_Length_Menu(void);
void Select_Calib_Length_Menu(uint8_t flag_id);
void Display_Min_Calib_Angle_Menu(void);
void Calib_Angle_Shift_Cursor(uint8_t flag_lr);
void Calib_Angle_Change_Parameter_Value(uint8_t flag_id);
void Display_Max_Calib_Angle_Menu(void);

void Supervisor_Setcode_Menu(void);
void Supervisor_Change_Parameter_Value(uint8_t flag_id);
void Supervisor_Setting(void);
void Supervisor_Save_Settings(void);
void Supervisor_Shift_Cursor(uint8_t flag_lr);
void Supervisor_Parametere_Value(void);

void Display_ArtDerate_Menu(void);
void ArtDerate_Cursor_Position(void);

void Display_Fork_MinMax_Press_Menu(uint8_t pindex, uint8_t minmax);        //0=min and 1=max
void Display_Fork_MinMax_Press_Menu_Cursor(void);
void Display_TMC_MinMax_Press_Menu(void);

void Display_Site_Set_Menu(void);
void Select_Site_Set_Menu(void);
void Site_Set_Cursor_Position(void);
void Site_Change_Parameter_Value(uint8_t flag_id);
void USB_Mass_Storage_Options();
void Display_Customer_Care_Num(void);
void Get_Radius_Capacity(uint16_t d_table, uint8_t cnt);

void Display_Length_Count_Menu(void);
void Select_Length_Count_Menu(uint8_t flag_id);
void Change_Length_Count_Value(void);
void Display_Length_Count_Value(void);
void Display_Length_Count_Cursor(void);
void Length_Count_Shift_Cursor(uint8_t flag_lr);
void Length_Change_Value(uint8_t flag_id);

void Site_Setting(void);
void Site_Save_Settings(void);
void Site_Shift_Cursor(uint8_t flag_lr);
void Select_USB_Options(uint8_t flag_id);
void Select_USB_Mass_Storage_Options(void);
void Display_Move_Option(void);
void Display_Length_Factor_Value(void);
void Display_Pressure_Factor_Value(void);
void Select_Length_Factor_Menu(uint8_t flag_id);
void Display_Length_Factor_Cursor(void);
void Display_Length_Factor_Cursor(void);
void Site_Parametere_Value(void);

void Display_Factory_Set_Menu(void);
void Select_Factory_Set_Menu(void);
void Factory_Set_Cursor_Position(void);
void Factory_Change_Parameter_Value(uint8_t flag_id);
void Factory_Setting(void);
void Factory_Save_Settings(void);
void Factory_Shift_Cursor(uint8_t flag_lr);
void Display_Crane_Details_Menu(void);
void Select_Crane_Details_menu(void);
void Crane_Detail_Shift_Cursor(uint8_t flag_lr);
void Crane_Detail_Parameter_Value(uint8_t flag_id);
void Update_Crane_Details(void);
void Select_Sensor_Type(void);
void Display_Crane_Details_Menu(void);
void Select_Crane_Model(uint8_t flag_id);
void Select_Sticker_Type(void);
void Display_Factor_Menu(void);
void Factor_Shift_Cursor(void);
void Factor_Change_Parameter_Value(uint8_t flag_id);
void Factory_Parametere_Value(void);
void Display_Crane_Models_Menu(void);
void Display_Crane_Models_Menu(void);
void Display_Min_Max_PCurve_Menu(void);
void Select_Min_Max_PCurve_Menu(void);
void Display_Known_Load_Value(void);

#endif
