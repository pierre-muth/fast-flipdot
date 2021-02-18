/**
  SPI1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    spi1.c

  @Summary
    This is the generated driver implementation file for the SPI1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides implementations for driver APIs for SPI1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15355
        Driver Version    :  2.0.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above or later
        MPLAB             :  MPLAB X 5.40
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "spi1.h"
#include <xc.h>

typedef struct { 
    uint8_t con1;
    uint8_t stat;
    uint8_t add;
    uint8_t operation;
} spi1_configuration_t;

//con1 == SSPxCON1, stat == SSPxSTAT, add == SSPxADD, operation == Master/Slave
static const spi1_configuration_t spi1_configuration[] = {   
    { 0x5, 0x40, 0x0, 1 }
};

void SPI1_Initialize(void)
{
    //Setup PPS Pins
    SSP1CLKPPS = 17;
    SSP1DATPPS = 16;
    RC1PPS    = 0;
    RC4PPS    = 22;
    // SPI setup
    SSP1STAT = 0x40;
    SSP1CON1 = 0x05;
    SSP1ADD  = 0x00;
    PIE3bits.SSP1IE = 1;
    SPI1_SetInterruptHandler(SPI1_Isr);
    TRISCbits.TRISC1 = 1;
    SSP1CON1bits.SSPEN = 0;
}

bool SPI1_Open(spi1_modes_t spi1UniqueConfiguration)
{
    if(!SSP1CON1bits.SSPEN)
    {
        SSP1STAT = spi1_configuration[spi1UniqueConfiguration].stat;
        SSP1CON1 = spi1_configuration[spi1UniqueConfiguration].con1;
        SSP1CON2 = 0x00;
        SSP1ADD = spi1_configuration[spi1UniqueConfiguration].add;
        TRISCbits.TRISC1 = spi1_configuration[spi1UniqueConfiguration].operation;
        SSP1CON1bits.SSPEN = 1;
        return true;
    }
    return false;
}

void SPI1_Close(void)
{
    SSP1CON1bits.SSPEN = 0;
}

uint8_t SPI1_ExchangeByte(uint8_t data)
{
    SSP1BUF = data;
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
    return SSP1BUF;
}

void SPI1_ExchangeBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        SSP1BUF = *data;
        while(!PIR3bits.SSP1IF);
        PIR3bits.SSP1IF = 0;
        *data++ = SSP1BUF;
    }
}

// Half Duplex SPI Functions
void SPI1_WriteBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        SPI1_ExchangeByte(*data++);
    }
}

void SPI1_ReadBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data++ = SPI1_ExchangeByte(0);
    }
}

void SPI1_WriteByte(uint8_t byte)
{
    SSP1BUF = byte;
}

uint8_t SPI1_ReadByte(void)
{
    return SSP1BUF;
}

void SPI1_Isr(void)
{
    if(PIR3bits.SSP1IF == 1){
        if(MSSP1_InterruptHandler){
            MSSP1_InterruptHandler();
        }
        PIR3bits.SSP1IF= 0;
    }
}

void SPI1_SetInterruptHandler(spi1InterruptHandler_t handler)
{
    MSSP1_InterruptHandler = handler;
}