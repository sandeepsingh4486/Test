/*******************************************************************************
  ECAN buffer and filter configuration source file

  Company:
    Microchip Technology Inc.

  File Name:
    ecan1drv.c

  Summary:
    Configures the message acceptance filters and the data buffers.

  Description:
    This source file sets the mask for the acceptance filters for the incoming
    data and also configures the data buffers by specifying identifiers for them.
*******************************************************************************/
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "main.h"
//#include "ecan1_config.h"
//#include "ecan_common.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
// Define ECAN Message Buffers
__eds__ ECAN1MSGBUF ecan1msgBuf __attribute__( (space(eds), aligned(ECAN1_MSG_BUF_LENGTH * 16)) );
//__eds__ ECAN2MSGBUF ecan2msgBuf __attribute__( (space(eds), aligned(ECAN2_MSG_BUF_LENGTH * 16)) );


/******************************************************************************
 * Function:        void Ecan1WriteMessage(mID *message)
 *
 * PreCondition:    None
 *
 * Input:           *message: a pointer to the message structure in RAM
 *                  that need to send the message.
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is used to write the ECAN1 buffer with the
 *                  identifiers and the data. Writes the message to be
 *                  transmitted.
 *****************************************************************************/
void Ecan1WriteMessage(mID *message)
{
    /* Writing the message for Transmission
Ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit);
Ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4);

buf -> Transmit Buffer number

txIdentifier -> SID<10:0> : EID<17:0>

ide = 0 -> Message will transmit standard identifier
ide = 1 -> Message will transmit extended identifier

remoteTransmit = 0 -> Normal message
remoteTransmit = 1 -> Message will request remote transmission

dataLength -> Data length can be from 0 to 8 bytes

data1, data2, data3, data4 -> Data words (2 bytes) each

*/
    Ecan1WriteTxMsgBufId( message->buffer, message->id, message->frame_type, message->message_type ); 
    Ecan1WriteTxMsgBufData( message->buffer, message->data_length, ((uint16_t)message->data[1]<<8)|message->data[0], ((uint16_t)message->data[3]<<8)|message->data[2], ((uint16_t)message->data[5]<<8)|message->data[4], ((uint16_t)message->data[7]<<8)|message->data[6] );
}

/******************************************************************************
 * Function:        void RxECAN1(mID *message)
 *
 * PreCondition:    None
 *
 * Input:          *message: a pointer to the message structure in RAM
 *                  that will store the message.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Moves the message from the DMA memory to RAM.
 *****************************************************************************/
void RxECAN1(mID *message)
{
    unsigned int    ide = 0;
    unsigned int    srr = 0;
    unsigned long   id = 0;

    /*
    Standard Message Format: 
    Word0 : 0bUUUx xxxx xxxx xxxx
                 |____________|||
                     SID10:0   SRR IDE(bit 0)     
    Word1 : 0bUUUU xxxx xxxx xxxx
                      |____________|
                        EID17:6
    Word2 : 0bxxxx xxx0 UUU0 xxxx
              |_____||         |__|
              EID5:0 RTR         DLC
    word3-word6: data bytes
    word7: filter hit code bits
    
    Substitute Remote Request Bit
    SRR->    "0"     Normal Message 
            "1"  Message will request remote transmission
    
    Extended  Identifier Bit            
    IDE->     "0"  Message will transmit standard identifier
               "1"  Message will transmit extended identifier
    
    Remote Transmission Request Bit
    RTR->     "0"  Message transmitted is a normal message
            "1"  Message transmitted is a remote message
    */
    /* read word 0 to see the message type */
    ide = ecan1msgBuf[message->buffer][0] & 0x0001;
    srr = ecan1msgBuf[message->buffer][0] & 0x0002;

    /* check to see what type of message it is */
    /* message is standard identifier */
    if( ide == 0 )
    {
        message->id = ( ecan1msgBuf[message->buffer][0] & 0x1FFC ) >> 2;
        message->frame_type = CAN_FRAME_STD;
    }

    /* mesage is extended identifier */
    else
    {
        id = ecan1msgBuf[message->buffer][0] & 0x1FFC;
        message->id = id << 16;
        id = ecan1msgBuf[message->buffer][1] & 0x0FFF;
        message->id = message->id + ( id << 6 );
        id = ( ecan1msgBuf[message->buffer][2] & 0xFC00 ) >> 10;
        message->id = message->id + id;
        message->frame_type = CAN_FRAME_EXT;
    }

    /* check to see what type of message it is */
    /* RTR message */
    if( srr == 1 )
    {
        message->message_type = CAN_MSG_RTR;
    }

    /* normal message */
    else
    {
        message->message_type = CAN_MSG_DATA;
        message->data[0] = ( unsigned char ) ecan1msgBuf[message->buffer][3];
        message->data[1] = ( unsigned char ) ( (ecan1msgBuf[message->buffer][3] & 0xFF00) >> 8 );
        message->data[2] = ( unsigned char ) ecan1msgBuf[message->buffer][4];
        message->data[3] = ( unsigned char ) ( (ecan1msgBuf[message->buffer][4] & 0xFF00) >> 8 );
        message->data[4] = ( unsigned char ) ecan1msgBuf[message->buffer][5];
        message->data[5] = ( unsigned char ) ( (ecan1msgBuf[message->buffer][5] & 0xFF00) >> 8 );
        message->data[6] = ( unsigned char ) ecan1msgBuf[message->buffer][6];
        message->data[7] = ( unsigned char ) ( (ecan1msgBuf[message->buffer][6] & 0xFF00) >> 8 );
        message->data_length = ( unsigned char ) ( ecan1msgBuf[message->buffer][2] & 0x000F );
    }
#ifdef TEST_MODE
    if(( message->data[0] == 0xAA)  &&
      ( message->data[1] == 0xAA)  &&
      ( message->data[2] == 0xBB)  &&
      ( message->data[3] == 0xBB)  &&
      ( message->data[4] == 0xCC)  &&
      ( message->data[5] == 0xCC)  &&
      ( message->data[6] == 0xDD)  &&
      ( message->data[7] == 0xDD))
        test_flag1=1;
    else
        test_flag1=0;

#endif

}

/******************************************************************************
 * Function:     void Ecan1WriteRxAcptFilter(int16_t n, int32_t identifier,
 *               uint16_t exide,uint16_t bufPnt,uint16_t maskSel)
 *
 * PreCondition:  None
 *
 * Input:         n-> Filter number [0-15]
 *                identifier-> Bit ordering is given below
 *                Filter Identifier (29-bits) :
 *                0b000f ffff ffff ffff ffff ffff ffff ffff
 *                     |____________|_____________________|
 *                        SID10:0          EID17:0
 *
 *               Filter Identifier (11-bits) :
 *               0b0000 0000 0000 0000 0000 0fff ffff ffff
 *                                           |___________|
 *                                             SID10:
 *               exide -> "0" for standard identifier
 *                        "1" for Extended identifier
 *               bufPnt -> Message buffer to store filtered message [0-15]
 *               maskSel -> Optinal Masking of identifier bits [0-3]
 *
 * Output:        None
 *
 * Side Effects:  None
 *
 * Overview:      Configures Acceptance filter "n" for ECAN1.
 *****************************************************************************/
void Ecan1WriteRxAcptFilter( int16_t n, int32_t identifier, uint16_t exide, uint16_t bufPnt, uint16_t maskSel )
{
    uint32_t    sid10_0 = 0;

    uint32_t    eid15_0 = 0;

    uint32_t    eid17_16 = 0;
    uint16_t    *sidRegAddr;
    uint16_t    *bufPntRegAddr;
    uint16_t    *maskSelRegAddr;
    uint16_t    *fltEnRegAddr;

    C1CTRL1bits.WIN = 1;

    // Obtain the Address of CiRXFnSID, CiBUFPNTn, CiFMSKSELn and CiFEN register for a given filter number "n"
    sidRegAddr = ( uint16_t * ) ( &C1RXF0SID + (n << 1) );
    bufPntRegAddr = ( uint16_t * ) ( &C1BUFPNT1 + (n >> 2) );
    maskSelRegAddr = ( uint16_t * ) ( &C1FMSKSEL1 + (n >> 3) );
    fltEnRegAddr = ( uint16_t * ) ( &C1FEN1 );

    // Bit-filed manupulation to write to Filter identifier register
    if( exide == 1 )
    {   // Filter Extended Identifier
        eid15_0 = ( identifier & 0xFFFF );
        eid17_16 = ( identifier >> 16 ) & 0x3;
        sid10_0 = ( identifier >> 18 ) & 0x7FF;

        *sidRegAddr = ( ((sid10_0) << 5) + 0x8 ) + eid17_16;    // Write to CiRXFnSID Register
        *( sidRegAddr + 1 ) = eid15_0;  // Write to CiRXFnEID Register
    }
    else
    {   // Filter Standard Identifier
        sid10_0 = ( identifier & 0x7FF );
        *sidRegAddr = ( sid10_0 ) << 5; // Write to CiRXFnSID Register
        *( sidRegAddr + 1 ) = 0;        // Write to CiRXFnEID Register
    }

    *bufPntRegAddr = ( *bufPntRegAddr ) & ( 0xFFFF - (0xF << (4 * (n & 3))) );      // clear nibble
    *bufPntRegAddr = ( (bufPnt << (4 * (n & 3))) | (*bufPntRegAddr) );              // Write to C1BUFPNTn Register
    *maskSelRegAddr = ( *maskSelRegAddr ) & ( 0xFFFF - (0x3 << ((n & 7) * 2)) );    // clear 2 bits
    *maskSelRegAddr = ( (maskSel << (2 * (n & 7))) | (*maskSelRegAddr) );           // Write to C1FMSKSELn Register
    *fltEnRegAddr = ( (0x1 << n) | (*fltEnRegAddr) );   // Write to C1FEN1 Register
    C1CTRL1bits.WIN = 0;
}

/******************************************************************************
 * Function:     void Ecan1WriteRxAcptMask(int16_t m, int32_t identifier,
 *               uint16_t mide, uint16_t exide)
 *
 * PreCondition:  None
 *
 * Input:        m-> Mask number [0-2]
                 identifier-> Bit ordering is given below n-> Filter number [0-15]
 *                identifier-> Bit ordering is given below
 *                Filter mask Identifier (29-bits) :
 *                0b000f ffff ffff ffff ffff ffff ffff ffff
 *                     |____________|_____________________|
 *                        SID10:0          EID17:0
 *
 *               Filter mask Identifier (11-bits) :
 *               0b0000 0000 0000 0000 0000 0fff ffff ffff
 *                                           |___________|
 *                                             SID10:
 *               mide ->  "0"  Match either standard or extended address message
 *                             if filters match
 *                        "1"  Match only message types that correpond to
 *                             'exide' bit in filter
 *
 * Output:        None
 *
 * Side Effects:  None
 *
 * Overview:      Configures Acceptance filter "n" for ECAN1.
 *****************************************************************************/
void Ecan1WriteRxAcptMask( int16_t m, int32_t identifier, uint16_t mide, uint16_t exide )
{
    uint32_t    sid10_0 = 0;

    uint32_t    eid15_0 = 0;

    uint32_t    eid17_16 = 0;
    uint16_t    *maskRegAddr;

    C1CTRL1bits.WIN = 1;

    // Obtain the Address of CiRXMmSID register for given Mask number "m"
    maskRegAddr = ( uint16_t * ) ( &C1RXM0SID + (m << 1) );

    // Bit-filed manupulation to write to Filter Mask register
    if( exide == 1 )
    {   // Filter Extended Identifier
        eid15_0 = ( identifier & 0xFFFF );
        eid17_16 = ( identifier >> 16 ) & 0x3;
        sid10_0 = ( identifier >> 18 ) & 0x7FF;

        if( mide == 1 )
        {
            *maskRegAddr = ( (sid10_0) << 5 ) + 0x0008 + eid17_16;  // Write to CiRXMnSID Register
        }
        else
        {
            *maskRegAddr = ( (sid10_0) << 5 ) + eid17_16;           // Write to CiRXMnSID Register
        }

        *( maskRegAddr + 1 ) = eid15_0; // Write to CiRXMnEID Register
    }
    else
    {   // Filter Standard Identifier
        sid10_0 = ( identifier & 0x7FF );
        if( mide == 1 )
        {
            *maskRegAddr = ( (sid10_0) << 5 ) + 0x0008; // Write to CiRXMnSID Register
        }
        else
        {
            *maskRegAddr = ( sid10_0 ) << 5;            // Write to CiRXMnSID Register
        }

        *( maskRegAddr + 1 ) = 0;                       // Write to CiRXMnEID Register
    }

    C1CTRL1bits.WIN = 0;
}

/******************************************************************************
 * Function:     void Ecan1WriteTxMsgBufId(uint16_t buf, int32_t txIdentifier, uint16_t ide,
 *               uint16_t remoteTransmit)
 *
 * PreCondition:  None
 *
 * Input:        buf    -> Transmit Buffer Number
 *               txIdentifier ->
 *               Extended Identifier (29-bits):
 *                0b000f ffff ffff ffff ffff ffff ffff ffff
 *                     |____________|_____________________|
 *                        SID10:0          EID17:0
 *
 *               Standard Identifier (11-bits) :
 *               0b0000 0000 0000 0000 0000 0fff ffff ffff
 *                                           |___________|
 *                                             SID10:
 *                 Standard Message Format:
 *                                             Word0 : 0b000f ffff ffff ffff
 *                                                          |____________|||___
 *                                                             SID10:0   SRR   IDE
 *                                             Word1 : 0b0000 0000 0000 0000
 *                                                            |____________|
 *                                                               EID17:6
 *                                             Word2 : 0b0000 00f0 0000 ffff
 *                                                       |_____||           |__|
 *                                                       EID5:0 RTR         DLC
 *                Extended Message Format:
 *                                          Word0 : 0b000f ffff ffff ffff
 *                                                       |____________|||___
 *                                                          SID10:0   SRR   IDE
 *                                          Word1 : 0b0000 ffff ffff ffff
 *                                                         |____________|
 *                                                               EID17:6
 *                                          Word2 : 0bffff fff0 0000 ffff
 *                                                    |_____||           |__|
 *                                                    EID5:0 RTR         DLC
 *             ide -> "0"  Message will transmit standard identifier
 *                    "1"  Message will transmit extended identifier
 *
 *            remoteTransmit -> "0" Message transmitted is a normal message
 *                              "1" Message transmitted is a remote message
 *            Standard Message Format:
 *                                          Word0 : 0b000f ffff ffff ff1f
 *                                                       |____________|||___
 *                                                          SID10:0   SRR   IDE
 *                                          Word1 : 0b0000 0000 0000 0000
 *                                                         |____________|
 *                                                            EID17:6
 *                                          Word2 : 0b0000 0010 0000 ffff
 *                                                  |_____||           |__|
 *                                                  EID5:0 RTR         DLC
 *
 *         Extended Message Format:
 *                                         Word0 : 0b000f ffff ffff ff1f
 *                                                      |____________|||___
 *                                                        SID10:0   SRR   IDE
 *                                         Word1 : 0b0000 ffff ffff ffff
 *                                                        |____________|
 *                                                          EID17:6
 *                                         Word2 : 0bffff ff10 0000 ffff
 *                                                   |_____||           |__|
 *                                                   EID5:0 RTR         DLC
 *
 * Output:        None
 *
 * Side Effects:  None
 *
 * Overview:      This function configures ECAN1 message buffer.
 *****************************************************************************/
void Ecan1WriteTxMsgBufId( uint16_t buf, int32_t txIdentifier, uint16_t ide, uint16_t remoteTransmit )
{
    uint32_t    word0 = 0;

    uint32_t    word1 = 0;

    uint32_t    word2 = 0;
    uint32_t    sid10_0 = 0;
    uint32_t    eid5_0 = 0;
    uint32_t    eid17_6 = 0;

    if( ide )
    {
        eid5_0 = ( txIdentifier & 0x3F );
        eid17_6 = ( txIdentifier >> 6 ) & 0xFFF;
        sid10_0 = ( txIdentifier >> 18 ) & 0x7FF;
        word1 = eid17_6;
    }
    else
    {
        sid10_0 = ( txIdentifier & 0x7FF );
    }

    if( remoteTransmit == 1 )
    {   // Transmit Remote Frame
        word0 = ( (sid10_0 << 2) | ide | 0x2 );
        word2 = ( (eid5_0 << 10) | 0x0200 );
    }
    else
    {
        word0 = ( (sid10_0 << 2) | ide );
        word2 = ( eid5_0 << 10 );
    }

    // Obtain the Address of Transmit Buffer in DMA RAM for a given Transmit Buffer number
    if( ide )
    {
        ecan1msgBuf[buf][0] = ( word0 | 0x0002 );
    }
    else
    {
        ecan1msgBuf[buf][0] = word0;
    }

    ecan1msgBuf[buf][1] = word1;
    ecan1msgBuf[buf][2] = word2;
}

/******************************************************************************
 * Function:     void Ecan1WriteTxMsgBufData(uint16_t buf, uint16_t dataLength,
 *    uint16_t data1, uint16_t data2, uint16_t data3, uint16_t data4)
 *
 * PreCondition:  None
 *
 * Input:            buf    -> Transmit Buffer Number
 *              dataLength  -> data length in bytes.
 *    	        actual data -> data1, data2, data3, data4
 *
 * Output:        None
 *
 * Side Effects:  None
 *
 * Overview:      This function transmits ECAN data.
 *****************************************************************************/
void Ecan1WriteTxMsgBufData( uint16_t buf, uint16_t dataLength, uint16_t data1, uint16_t data2, uint16_t data3,
                             uint16_t data4 )
{
    ecan1msgBuf[buf][2] = ( (ecan1msgBuf[buf][2] & 0xFFF0) + dataLength );

    ecan1msgBuf[buf][3] = data1;
    ecan1msgBuf[buf][4] = data2;
    ecan1msgBuf[buf][5] = data3;
    ecan1msgBuf[buf][6] = data4;
}

/******************************************************************************
 * Function:     void Ecan1DisableRXFilter(int16_t n)
 *
 * PreCondition:  None
 *
 * Input:          n -> Filter number [0-15]
 *
 * Output:        None
 *
 * Side Effects:  None
 *
 * Overview:          Disables RX Acceptance Filter.
 *****************************************************************************/
void Ecan1DisableRXFilter( int16_t n )
{
    uint16_t    *fltEnRegAddr;
    C1CTRL1bits.WIN = 1;
    fltEnRegAddr = ( uint16_t * ) ( &C1FEN1 );
    *fltEnRegAddr = ( *fltEnRegAddr ) & ( 0xFFFF - (0x1 << n) );
    C1CTRL1bits.WIN = 0;
}

/*******************************************************************************
 End of File
*/
