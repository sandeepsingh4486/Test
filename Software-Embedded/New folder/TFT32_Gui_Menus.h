
#ifndef TFT32_GUI_MENUS_H
#define TFT32_GUI_MENUS_H

void TFT32_Gui(void);
void Display_Duty_Hint_MainScreen(void);
void change_Mode(void);
void Do_Forklift_Load_MPoint_Sorting(uint8_t mpoint);

void Save_Settings_If_Modified(void);
void Shift_Cursor_Position(uint8_t flag_lr, uint8_t num_of_dig,uint8_t decimal_pos);
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
void TFTOperator_View_CraneDetails(void);
void TFTOperator_View_CraneDimensions(uint8_t cnt);
void TFTOperator_View_OTG_Calibration(void);

void Check_PCB89332(void);
void Check_PCB89333(void);

void Duty_Hint(uint16_t Duty_no);
void TFTSelect_Operator_View_Menu(uint8_t sel);
void TFTOperator_Viewing(void);
void TFTOperator_View_Pres_Len_Ang_Cnts(uint8_t p1_chn, uint8_t p2_chn, uint8_t len_chn, uint8_t mang_chn, uint8_t kang_chn, uint16_t p1_cnt, uint16_t p2_cnt, uint16_t len_cnt, uint16_t mang_cnt, uint16_t kang_cnt, uint8_t Select_screen);
void TFTView_Set_Points(uint8_t M_sp1,uint8_t M_sp2,uint8_t M_sp3,uint8_t M_sp4);
void TFTOperator_View_Tilt_ADC_Cnts(uint8_t sel);
void TFTOperator_View_OTG_ADC_Cnts(uint8_t sel);
void TFTOperator_View_Loadcell_Cnts(uint8_t sel);

void TFTView_Offset(int16_t B_ofst, int16_t B_hofst, int16_t B_tip, int16_t s_ofst, int16_t h_ofst);
void TFTError_Count(uint16_t Low_er_cnt, uint16_t High_er_cnt);
void TFTRelay_Status(uint8_t Relay_1,uint8_t Relay_2,uint8_t Relay_3,uint8_t Buzzer);
void TFTView_Hook_Calibration(uint16_t M_min_val,uint16_t M_min_cnt,uint16_t M_max_val,uint16_t M_max_cnt,uint16_t A_min_val,uint16_t A_min_cnt,uint16_t A_max_val,uint16_t A_max_cnt);
void TFTView_Boom_Luff_Angle_Calibration(uint16_t B_min_val,uint16_t B_min_cnt,uint16_t B_max_val,uint16_t B_max_cnt,uint16_t L_min_val,uint16_t L_min_cnt,uint16_t L_max_val,uint16_t L_max_cnt);
void TFTDisplay_Operator_View_Menu(uint8_t page);
void Operator_Setcode_Page_One(void);
void Operator_Setcode_Page_Two(void);
void TFTOperator_View_Pages(uint8_t page);
void TFTCommon_OperatorVw_Escape_Function(void);
void TFTCommon_OperatorSet_Escape_Function(void);
void TFTOperator_Setcode_Pages(uint8_t page);
void TFTSelect_Operator_Setcode_Menu(uint8_t sel);
void TFTDisplay_Operator_Settings(void);
void TFT_Modify_Operator_Settings(void);
void TFTCommon_Opertr_Escape_Function(void);
void TFTDisplay_Operator_Setcode_Menu(uint8_t page);
void TFT_Choose_Duty(void);
void TFTDuty_Hint(uint16_t Duty_no);
void TFT_Change_Main_Falls(void);
void TFT_Draw_Cursor(uint8_t pos, uint16_t clr_color, uint16_t cursor_color);
void TFT_Draw_Cursor_Dynam_Width(uint8_t pos, uint8_t width, uint16_t clr_color, uint16_t cursor_color);
void Current_Prev_Val_Screen(uint8_t para, uint16_t fg_color, uint16_t bg_color);
void TFTShift_Cursor_Position(uint8_t flag_lr, uint8_t num_of_dig,uint8_t decimal_pos);
void TFT_Set_Load_UOM(void);

void TFTDisplay_Supervisor_Set_Menu(uint8_t page);
void TFTSupervisor_Setcode_Pages(uint8_t page);
void TFTSelect_Supervisor_Setcode_Menu(uint8_t sel);
void TFTDisplay_Supervisor_Settings(void);
void TFT_Modify_Supervisor_Settings(void);
void TFTCommon_Supervisor_Escape_Function(void);
void TFT_Change_Main_Boom_Offset_Value(void);
void TFT_Master_Reset(void);
void TFT_SetPoints(void);
void TFT_Set_Offset(void);
void TFT_Set_Duty_Type(void);
void TFT_Select_Duty_HkLoad_Calib(void);
void TFT_TMC_MinMax_Press_Menu(void);
void TFT_Select_Calib_Length(void);
void TFT_Set_Duty_Type_NumofLength(void);
void TFT_Set_Duty_Type_Length_Val(void);
void TFT_Enable_Disable_Supervisor_Menu(void);
void TFT_Calibrate_LenAngles(void);
void TFT_2PCalibrate_Load(void);
void TFT_Set_3Digit_Supervisor_Menu(void);
void TFT_Set_3Digit1Decimal_Supervisor_Menus(void);
void TFT_Set_4Digit_Supervisor_Menu(void);
void TFT_Set_2Digit_Supervisor_Menus(void);
void TFT_Set_10Digit_Supervisor_Menu(void);

void TFT_Multipoint_Calibration_Menu(void);
void TFT_Forklift_Load_MPoint_Menu(void);
void TFT_Tilt_Calibration_Menu(void);
void TFT_Choose_Language_Supervisor_Menu(void);

void TFTDisplay_Site_Set_Menu(uint8_t page);
void TFTSite_Setcode_Pages(uint8_t page);
void TFTSelect_Site_Setcode_Menu(uint8_t sel);
void TFTDisplay_Site_Settings(void);
void TFT_Modify_Site_Settings(void);
void TFTCommon_Site_Escape_Function(void);
void TFT_Edit_4Digit_Site_Menu(void);
void TFT_Set_Site_Factors_menu(void);
void TFT_Enable_Disable_Site_Menu(void);
void TFT_Total_Falls_Menu(void);
void TFT_Edit_2Digit_Site_Menu(void);
void TFT_Set_2Digit_Site_Menus(void);


void TFTDisplay_Factory_Set_Menu(uint8_t page);
void TFTFactory_Setcode_Pages(uint8_t page);
void TFTSelect_Factory_Setcode_Menu(uint8_t sel);
void TFTDisplay_Factory_Settings(void);
void TFT_Modify_Factory_Settings(void);
void TFTCommon_Factory_Escape_Function(void);
void TFT_Enable_Disable_Factory_Menu(void);
void Upload_CSV_File(void);
void TFT_Set_Install_Date(void);
void TFT_Edit_2Digit_Factory_Menu(void);
void TFT_Edit_3Digit_Factory_Menu(void);
void TFT_Set_SO_Number(void);
void TFT_Select_System(void);
void TFT_Send_Pressure_Curve(void);
void TFT_Edit_3Digit1Decimal_Factory_Menu(void);
void TFT_Set_Crane_Details(void);
void TFT_Set_Calib_Pressure_Values(void);

void Select_Operator_View_Menu(void);
void Operator_Viewing(void);
void Show_Live_ADC_Count(void);
void Choose_Duty(void);
void Choose_UOM(void);
void Choose_UOM_Wspd(void);
void Display_Dummy_Calib_Length_Menu(void);
void Display_Operator_Settings_Values(void);

void Display_Operator_Setcode_Menu(void);
void Operator_Setcode_Menu(void);
void Operator_Shift_Cursor_Position(uint8_t flag_lr);
void Operator_Change_Parameter_Value(uint8_t flag_id);
void Display_Operator_Settings(void);
void Operator_Save_Settings(void);
void Display_Pressure_Curve_Counts(uint8_t flag_id);

void Display_Supervisor_Set_Menu(void);
void Display_Supervisor_Settings_Values(void);
void Display_Ld_Compansation_Menu(void);
void Choose_Yes_No(void);
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

void Display_Select_Calib_Length_Menu(void);
void Select_Calib_Length_Menu(uint8_t flag_id);
void Display_Min_Calib_Angle_Menu(void);
void Calib_Angle_Shift_Cursor(uint8_t flag_lr);
void Calib_Angle_Change_Parameter_Value(uint8_t flag_id);
void Display_Max_Calib_Angle_Menu(void);

void Supervisor_Setcode_Menu(void);
void Supervisor_Set_Cursor_Position(void);
void Supervisor_Change_Parameter_Value(uint8_t flag_id);
void Display_Supervisor_Settings(void);
void Supervisor_Save_Settings(void);
void Supervisor_Shift_Cursor_Position(uint8_t flag_lr);
void TFT_Length_MPoint_Menu(void);

void Display_Site_Set_Menu(void);
void SiteEngg_Setcode_Menu(void);
void Display_SiteEnggr_Settings_Values(void);
void Display_SiteEnggr_Settings(void);
void Site_Shift_Cursor_Position(uint8_t flag_lr);
void Site_Change_Parameter_Value(uint8_t flag_id);
void USB_Mass_Storage_Options();
void Display_Customer_Care_Num(void);

void Display_Length_Count_Menu(void);
void Select_Length_Count_Menu(uint8_t flag_id);
void Change_Length_Count_Value(void);
void Display_Length_Count_Value(void);
void Display_Length_Count_Cursor(void);
void Length_Count_Shift_Cursor(uint8_t flag_lr);
void Length_Change_Value(uint8_t flag_id);
void Get_Radius_Capacity(uint16_t d_table, uint8_t cnt);

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
void Total_Falls_Menu(void);
void Main_Aux_Total_Falls_Menu(void);
void Select_Main_Aux_Falls(void);
void Display_Main_Aux_Falls(void);
void TFT_Set_3Digit1Decimal_Site_Menus(void);
void TFT_Copy_ZLoad_PCurve(void);
void TFT_View_Duty_Tables(void);
void TFT_View_Duty_Table_Menu(void);

void Display_Advanced_Set_Menu(void);
void Factory_Setcode_Menu(void);
void Factory_Set_Cursor_Position(void);
void Factory_Change_Parameter_Value(uint8_t flag_id);
void Factory_Settings(void);
void Factory_Save_Settings(void);
void Factory_Shift_Cursor_Position(uint8_t flag_lr);
void Display_Crane_Details_Menu(void);
void Select_Crane_Details_menu(void);
void Crane_Detail_Shift_Cursor(uint8_t flag_lr);
void Crane_Detail_Parameter_Value(uint8_t flag_id);
void Update_Crane_Details(void);
void Select_Sensor_Type(void);
void Display_Crane_Details_Menu(void);
void Select_Crane_Model(uint8_t flag_id);
uint8_t Display_Crane_Models_Menu(void);
void Select_Sticker_Type(void);
void Display_Factor_Menu(void);
void Factor_Shift_Cursor(void);
void Factor_Change_Parameter_Value(uint8_t flag_id);
void Get_Radius_Capacity(uint16_t d_table, uint8_t cnt);
void TFT_Select_Sensor_Type(void);
void TFT_Select_Cal_Case_Factory_Menu(void);
void TFT_Set_Calib_LenAngle_Values(void);
void TFT_Set_Crane_Model(void);
void TFT_Select_Length_Drum(void);

#endif
