/* 
 * File:   Read_Images.h
 * Author: Edesign3
 *
 * Created on 24 February, 2023, 9:22 AM
 */

#ifndef READ_IMAGES_H
#define	READ_IMAGES_H


#define SECTOR_SIZE                             4096

#define DEFAULT_PNC_IMAGE_SIZE                  54600
#define PNC_FORKLIFT_IMAGE_SIZE                 51000
#define PNC_TMC_IMAGE_SIZE                      36000
#define PNC_KNUCBOOM_IMAGE_SIZE                 36000
#define PNC_NXP150_IMAGE_SIZE                   54600
#define PNC_PNCFORK_IMAGE_SIZE                  36000
#define PNCWL_IMAGE_SIZE                        39000

#define KAMPLOGO_IMAGE_SIZE                     142600
#define CRAWLER_IMAGE_SIZE                      54600
#define TELESCOPIC_IMAGE_SIZE                   54600
#define TOWER_IMAGE_SIZE                        51000
#define KAMP_QRCODE_IMAGE_SIZE                  80000
#define ESORTSLOGO_IMAGE_SIZE                   79360
#define ACELOGO_IMAGE_SIZE                      99820

#define PNC_IMAGE_TOTAL_SECTORS                 14
#define DEFAULT_PNC_IMAGE_SECTOR                0       //14 sectors required(0 to 13)

#define FORKLIFT_IMAGE_TOTAL_SECTORS            13
#define PNC_FORKLIFT_IMAGE_SECTOR               14      //13 sectors required(14 to 26)

#define TMC_IMAGE_TOTAL_SECTORS                 9
#define PNC_TMC_IMAGE_SECTOR                    27      //9 sectors required(27 to 35)

#define KNUCBOOM_IMAGE_TOTAL_SECTORS            9
#define PNC_KNUCBOOM_IMAGE_SECTOR               36      //9 sectors required(36 to 44)

#define NXP150_IMAGE_TOTAL_SECTORS              14
#define PNC_NXP150_IMAGE_SECTOR                 45      //14 sectors required(45 to 58)

#define PNCFORK_IMAGE_TOTAL_SECTORS             9
#define PNC_PNCFORK_IMAGE_SECTOR                59      //9 sectors required(58 to 67)

#define PNCWL_IMAGE_TOTAL_SECTORS               10
#define PNCWL_IMAGE_SECTOR                      68      //10 sectors required(68 to 77)

#define KAMPLOGO_IMAGE_TOTAL_SECTORS            35
#define KAMPLOGO_IMAGE_SECTOR                   250       //35 sectors required(250 to 284)

#define TELESCOPIC_IMAGE_TOTAL_SECTORS          14
#define TELESCOPIC_IMAGE_SECTOR                 285       //14 sectors required(285 to 298)

#define CRAWLER_IMAGE_TOTAL_SECTORS             14
#define CRAWLER_IMAGE_SECTOR                    299       //14 sectors required(299 to 312)

#define TOWER_IMAGE_TOTAL_SECTORS               13
#define TOWER_IMAGE_SECTOR                      313       //13 sectors required(313 to 325)

#define KAMP_QR_IMAGE_TOTAL_SECTORS             20
#define KAMP_QR_IMAGE_SECTOR                    326       //35 sectors required(326 to 345)

#define ESCORTSLOGO_IMAGE_TOTAL_SECTORS         20
#define ESCORTSLOGO_IMAGE_SECTOR                346

#define ACELOGO_IMAGE_TOTAL_SECTORS             25
#define ACELOGO_IMAGE_SECTOR                    367

void Display_Default_PNC_Image(uint16_t x, uint16_t y);
void Display_PNC_Whiteline_Image(uint16_t x, uint16_t y);
void Display_Forklift_Image(uint16_t x, uint16_t y);
void Display_TMC_Image(uint16_t x, uint16_t y);
void Display_KnuckleBoom_Image(uint16_t x, uint16_t y);
void Display_PNCNXP150_Image(uint16_t x, uint16_t y);
void Display_PNCFork_Image(uint16_t x, uint16_t y);
void Display_KAMPLOGO_Image(uint16_t x, uint16_t y);
void Display_Crawler_Image(uint16_t x, uint16_t y);
void Display_Tower_Image(uint16_t x, uint16_t y);
void Display_Telescopic_Image(uint16_t x, uint16_t y);
void Display_KAMP_QRCode_Image(uint16_t x, uint16_t y);
void Display_EscortsLogo_Image(uint16_t x, uint16_t y);
void Display_ACELogo_Image(uint16_t x, uint16_t y);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* READ_IMAGES_H */

