
#include "main.h"

/*============================================================================*/
/*
 * Function      :        Display_Default_PNC_Image.
 * Description   :        Used to display default PNC crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Default_PNC_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+130-1,y+210-1);
    
    for(sector=0; sector<PNC_IMAGE_TOTAL_SECTORS; sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (PNC_IMAGE_TOTAL_SECTORS-1))            //54600/4096 = 13 sectors
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (PNC_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<DEFAULT_PNC_IMAGE_SIZE%SECTOR_SIZE; i+=2)    //54600%4096 = 1352bytes from 14th sector
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}



/*============================================================================*/
/*
 * Function      :        Display_PNC_Whiteline_Image.
 * Description   :        Used to display Escorts PNC Whiteline crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_PNC_Whiteline_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = 6;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = 6;
    
    Address_set(x,y,x+150-1,y+130-1);
    
    for(sector=PNCWL_IMAGE_SECTOR; sector<(PNCWL_IMAGE_SECTOR+PNCWL_IMAGE_TOTAL_SECTORS); sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (PNCWL_IMAGE_SECTOR+PNCWL_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (PNCWL_IMAGE_SECTOR+PNCWL_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<PNCWL_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}

/*============================================================================*/
/*
 * Function      :        Display_Forklift_Image.
 * Description   :        Used to display Forklift crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Forklift_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+170-1,y+150-1);
    
    for(sector=PNC_FORKLIFT_IMAGE_SECTOR; sector<(PNC_FORKLIFT_IMAGE_SECTOR+FORKLIFT_IMAGE_TOTAL_SECTORS); sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (PNC_FORKLIFT_IMAGE_SECTOR+FORKLIFT_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (PNC_FORKLIFT_IMAGE_SECTOR+FORKLIFT_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<PNC_FORKLIFT_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_TMC_Image.
 * Description   :        Used to display TMC crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_TMC_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+150-1,y+120-1);
    
    for(sector=PNC_TMC_IMAGE_SECTOR; sector<(PNC_TMC_IMAGE_SECTOR+TMC_IMAGE_TOTAL_SECTORS); sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (PNC_TMC_IMAGE_SECTOR+TMC_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (PNC_TMC_IMAGE_SECTOR+TMC_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<PNC_TMC_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_KnuckleBoom_Image.
 * Description   :        Used to display Knuckleboom crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_KnuckleBoom_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+150-1,y+120-1);
    
    for(sector=PNC_KNUCBOOM_IMAGE_SECTOR; sector<(PNC_KNUCBOOM_IMAGE_SECTOR+KNUCBOOM_IMAGE_TOTAL_SECTORS); sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (PNC_KNUCBOOM_IMAGE_SECTOR+KNUCBOOM_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (PNC_KNUCBOOM_IMAGE_SECTOR+KNUCBOOM_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<PNC_KNUCBOOM_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_PNCNXP150_Image.
 * Description   :        Used to display NXP150 crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_PNCNXP150_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+130-1,y+210-1);
    
    for(sector=PNC_NXP150_IMAGE_SECTOR; sector<(PNC_NXP150_IMAGE_SECTOR+NXP150_IMAGE_TOTAL_SECTORS); sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (PNC_NXP150_IMAGE_SECTOR+NXP150_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (PNC_NXP150_IMAGE_SECTOR+NXP150_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<PNC_NXP150_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_PNCFork_Image.
 * Description   :        Used to display PNC Fork crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_PNCFork_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+150-1,y+120-1);
    
    for(sector=PNC_PNCFORK_IMAGE_SECTOR; sector<(PNC_PNCFORK_IMAGE_SECTOR+PNCFORK_IMAGE_TOTAL_SECTORS); sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (PNC_PNCFORK_IMAGE_SECTOR+PNCFORK_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (PNC_PNCFORK_IMAGE_SECTOR+PNCFORK_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<PNC_PNCFORK_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_Crawler_Image.
 * Description   :        Used to display Crawler crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Crawler_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+130-1,y+210-1);
    
    for(sector=CRAWLER_IMAGE_SECTOR; sector<(CRAWLER_IMAGE_SECTOR+CRAWLER_IMAGE_TOTAL_SECTORS); sector++) //142600/4096 = 35 sectors
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (CRAWLER_IMAGE_SECTOR+CRAWLER_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (CRAWLER_IMAGE_SECTOR+CRAWLER_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<CRAWLER_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_Tower_Image.
 * Description   :        Used to display Tower crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Tower_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+150-1,y+170-1);
    
    for(sector=TOWER_IMAGE_SECTOR; sector<(TOWER_IMAGE_SECTOR+TOWER_IMAGE_TOTAL_SECTORS); sector++) //142600/4096 = 35 sectors
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (TOWER_IMAGE_SECTOR+TOWER_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (TOWER_IMAGE_SECTOR+TOWER_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<TOWER_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_Telescopic_Image.
 * Description   :        Used to display Telescopic crane image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_Telescopic_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+130-1,y+210-1);
    
    for(sector=TELESCOPIC_IMAGE_SECTOR; sector<(TELESCOPIC_IMAGE_SECTOR+TELESCOPIC_IMAGE_TOTAL_SECTORS); sector++)
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (TELESCOPIC_IMAGE_SECTOR+TELESCOPIC_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (TELESCOPIC_IMAGE_SECTOR+TELESCOPIC_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<TELESCOPIC_IMAGE_SIZE%SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}


/*============================================================================*/
/*
 * Function      :        Display_KAMPLOGO_Image.
 * Description   :        Used to display KAMPL logo image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_KAMPLOGO_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = CS2_FLASH;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = WP2_FLASH;
    
    Address_set(x,y,x+310-1,y+230-1);
    
    for(sector=KAMPLOGO_IMAGE_SECTOR; sector<(KAMPLOGO_IMAGE_SECTOR+KAMPLOGO_IMAGE_TOTAL_SECTORS); sector++) //142600/4096 = 35 sectors
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (KAMPLOGO_IMAGE_SECTOR+KAMPLOGO_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (KAMPLOGO_IMAGE_SECTOR+KAMPLOGO_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<KAMPLOGO_IMAGE_SIZE%SECTOR_SIZE; i+=2)            //142600%4096 = 3336bytes from 35th sector
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}



/*============================================================================*/
/*
 * Function      :        Display_KAMP_QRCode_Image.
 * Description   :        Used to display KAMPL QR image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/
void Display_KAMP_QRCode_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = 6;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = 6;
    
    Address_set(x,y,x+200-1,y+200-1);
    
    for(sector=KAMP_QR_IMAGE_SECTOR; sector<(KAMP_QR_IMAGE_SECTOR+KAMP_QR_IMAGE_TOTAL_SECTORS); sector++) //142600/4096 = 35 sectors
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (KAMP_QR_IMAGE_SECTOR+KAMP_QR_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (KAMP_QR_IMAGE_SECTOR+KAMP_QR_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<KAMP_QRCODE_IMAGE_SIZE%SECTOR_SIZE; i+=2)            //142600%4096 = 3336bytes from 35th sector
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}

//==================================EOF=========================================

/*============================================================================*/
/*
 * Function      :        Display_EscortsLogo_Image
 * Description   :        Used to display ESCORT image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/

void Display_EscortsLogo_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = 6;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = 6;
    
    Address_set(x,y,x+310-1,y+128-1);
    
    for(sector=ESCORTSLOGO_IMAGE_SECTOR; sector<(ESCORTSLOGO_IMAGE_SECTOR+ESCORTSLOGO_IMAGE_TOTAL_SECTORS); sector++) //142600/4096 = 35 sectors
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (ESCORTSLOGO_IMAGE_SECTOR+ESCORTSLOGO_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (ESCORTSLOGO_IMAGE_SECTOR+ESCORTSLOGO_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<ESORTSLOGO_IMAGE_SIZE%SECTOR_SIZE; i+=2)            //142600%4096 = 3336bytes from 35th sector
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}

/*============================================================================*/
/*
 * Function      :        Display_ACELogo_Image
 * Description   :        Used to display ESCORT image on TFT3.2".
 * Parameters    :        x,y-Co-ordinates.
 * Return        :        None.
*/
/*============================================================================*/

void Display_ACELogo_Image(uint16_t x, uint16_t y)
{
    uint16_t sector;
    uint16_t i;
    
    sflash.spi_module = SPI_MODULE3;
    sflash.cs_port = GPIO_PORTC;
    sflash.cs_pin = 6;
    sflash.wp_port = GPIO_PORTD;
    sflash.wp_pin = 6;
    
    Address_set(x,y,x+310-1,y+128-1);
    
    for(sector=ACELOGO_IMAGE_SECTOR; sector<(ACELOGO_IMAGE_SECTOR+ACELOGO_IMAGE_TOTAL_SECTORS); sector++) //142600/4096 = 35 sectors
    {
        SPIFlash_Read_Sector(sector);
        
        if(sector < (ACELOGO_IMAGE_SECTOR+ACELOGO_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<SECTOR_SIZE; i+=2)
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
        else if(sector == (ACELOGO_IMAGE_SECTOR+ACELOGO_IMAGE_TOTAL_SECTORS-1))
        {
            for(i=0; i<ACELOGO_IMAGE_SIZE%SECTOR_SIZE; i+=2)            //142600%4096 = 3336bytes from 35th sector
            {
                TFT32_Write_Data16((((uint16_t)flash.buf[i+1])*256)+flash.buf[i]);
            }
        }
    }
    
    sflash.spi_module = SPI_MODULE2;
    sflash.cs_port = GPIO_PORTB;
    sflash.cs_pin = CS_FLASH;
    sflash.wp_port = GPIO_PORTE;
    sflash.wp_pin = WP_FLASH;
}



