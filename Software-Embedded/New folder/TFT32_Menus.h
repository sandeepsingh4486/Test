/* 
 * File:   TFT32_Menus.h
 * Author: Edesign3
 *
 * Created on December 14, 2022, 5:52 PM
 */

#ifndef TFT32_MENUS_H
#define	TFT32_MENUS_H
void Clear_Rows(void);
void Set_Codes_Menu_Outlines(void);
void TFT_Main_Menu_Outlines(void);
void TFTDisplay_Main_Menu(void);
void Highlight_Single_Row(uint8_t sel, uint8_t row);
void Inc_Dec_2Digit_Menu(void);
void Inc_Dec_3Digit_Menu(void);
void Inc_Dec_4Digit_Menu(void);
void Inc_Dec_5Digit_Menu(void);
void Inc_Dec_10Digit_Menu(void);
void TFTShow_Enable_Disable(void);
void TFTShow_Languages(void);
void TFTShow_Load_UOM(void);
void TFTShow_WindSpeed_UOM(void);
void Enable_Disable_Menu(void);
void Inc_Dec_3Digit_1Decimal_Menu(void);
void Inc_Dec_4Digit_1Decimal_Menu(void);
void TFTShow_YESNO_Confirmation(void);
void Inc_Dec_3Digit_1Decimal_WSign_Menu(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TFT32_MENUS_H */

