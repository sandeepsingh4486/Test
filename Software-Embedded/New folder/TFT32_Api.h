/* 
 * File:   TFT_Api.h
 * Author: Edesign3
 *
 * Created on 12 December, 2022, 4:07 PM
 */

#ifndef TFT_API_H
#define	TFT_API_H


void system_initialization(void);
void Main_Welcome_Screen(void);
void Software_Details(char *soft_ver_buf,char *csv_ver_buf,char *csv_name_buf,char *date_buf);
void Crane_Details(char *crane_model_buf,char *crane_make_buf,char *crane_type_buf,char *so_no_buf,char *inst_date_buf);
void System_Setup_Screen(void);
void Initial_SPI_Test_Screen(uint8_t sel, uint8_t flag);
void Default_Main_Screen_PNC(uint8_t sel,uint16_t dty,uint16_t mlen,uint16_t jlen,int16_t mang,int16_t jang,uint16_t rad,uint16_t aload,uint16_t mload,uint16_t swl, uint16_t wind);
void Default_Main_Screen_ForkLift(uint8_t sel, uint8_t dty, uint16_t load, uint16_t capa, uint16_t height);
void Default_Main_Screen_KnuckleBoom(uint8_t sel);
void Default_Main_Screen_TMC(uint8_t sel);
void Default_Main_Screen_PNC_Whiteline(uint8_t sel);
void Default_Main_Screen_PNC_Manbasket(uint8_t sel);
void Default_Main_Screen_PNC_Fork(uint8_t sel);

void Draw_Rectangle_Lable_Outlines(uint16_t x, uint16_t y, char *lable, int16_t val, char unit_char, uint8_t sel, uint8_t clr);
void Draw_Rod_Lable_Outlines(uint16_t x, uint16_t y, char *lable, int16_t val, char unit_char, uint8_t sel, uint8_t clr);

void TFT32_Crane_Image(uint16_t x, uint16_t y, uint16_t height, uint16_t width);

void Default_Main_Screen_Outline(void);
void Default_Main_Screen_PNCBB(uint8_t sel, uint16_t dty, uint16_t len, uint16_t ang, uint16_t rad, uint16_t load, uint16_t swl, uint16_t wind);
void TFT32BB_Crane_Image(uint16_t x, uint16_t y, uint16_t height, uint16_t width);





#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TFT_API_H */

