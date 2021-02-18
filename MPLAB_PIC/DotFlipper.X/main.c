/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15355
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

uint8_t lastData = 0b00000000;
uint8_t previousData = 0x00;
uint8_t idleStart = 1;
uint16_t counter = 1;
uint8_t previousState = 0x00;
uint8_t nextState = 0x00;

void setDots(uint8_t newData){
    
    if (newData == previousData) return;
    
    previousState = 0x00;
    nextState = 0x00;
    
    previousState ^= (previousData & 0b01000000) >> 6;
    previousState ^= (previousData & 0b00100000) >> 4;
    previousState ^= (previousData & 0b00010000) >> 2;
    previousState ^= (previousData & 0b00001000);
    previousState ^= (previousData & 0b00000100) << 2;
    previousState ^= (previousData & 0b00000010) << 4;
    previousState ^= (previousData & 0b00000001) << 6;
    
    nextState ^= (newData & 0b01000000) >> 6;
    nextState ^= (newData & 0b00100000) >> 4;
    nextState ^= (newData & 0b00010000) >> 2;
    nextState ^= (newData & 0b00001000);
    nextState ^= (newData & 0b00000100) << 2;
    nextState ^= (newData & 0b00000010) << 4;
    nextState ^= (newData & 0b00000001) << 6;
    
    PORTB = previousState;
    PORTA = ~previousState;
    __delay_ms(1);
    PORTB = 0x00;
    PORTA = 0x00;
    
    __delay_ms(5);
    previousData = newData;
    
    PORTB = nextState;
    PORTA = ~nextState;
    __delay_ms(1);
    PORTB = 0x00;
    PORTA = 0x00;
    
}

void spi1InterruptHandler(void) {
    idleStart = 0;
    lastData = SSP1BUF;
    TMR0L = 0x00;
    PIR3bits.SSP1IF = 0;
}

void eusart1RxDataHandler(void){
    idleStart = 0;
    EUSART1_Write(lastData);
    lastData = RC1REG;
    TMR0L = 0x00;
    PIR3bits.RC1IF = 0;
}

void tmr0InterruptHandler(void) {
    if (idleStart) {
        if (((counter++)>>3) < 0x80)
            setDots( ((counter)>>3)&0x7F );
        else
            setDots(0x7F);
    } else {
        setDots( lastData );
    }
//    PIR0bits.TMR0IF = 0;
}

void main(void) {
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    // initialize the device
    SYSTEM_Initialize();
    
    __delay_ms(100);
    setDots(0x00);
    __delay_ms(100);
    setDots(0xFF);
    __delay_ms(100);
    setDots(0x00);
    __delay_ms(500);
    
    SPI1_SetInterruptHandler(spi1InterruptHandler);
    EUSART1_SetRxInterruptHandler(eusart1RxDataHandler);
    TMR0_SetInterruptHandler(tmr0InterruptHandler);
    SSP1CON3bits.BOEN = 1;
    SSP1CON1bits.SSPEN = 1;
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
//    uint8_t count = 0;
//    uint8_t i = 0;
    
    while (1) {
        __delay_ms(200);
        
//        for(count=0; count<4; count++) {
//            setDots(0xAA);
//            __delay_ms(500);
//            setDots(0x55);
//            __delay_ms(500);
//            
//        }
//        
//        setDots(0x00);
//        __delay_ms(500);
//        
//        for(count=0; count<4; count++) {
//            setDots(0xFF);
//            __delay_ms(100);
//            setDots(0x00);
//            __delay_ms(100);
//            
//        }
//        
//        setDots(0x00);
//        __delay_ms(500);
//        
//        for(count=0; count<4; count++){
//            
//            for(i=0; i<7; i++) {
//                setDots(0x01<<i);
//                __delay_ms(33);
//            }
//            setDots(0x00);
//            __delay_ms(33);
//            for(i=0; i<7; i++) {
//                setDots(0x01<< (6-i) );
//                __delay_ms(33);
//            }
//            setDots(0x00);
//            __delay_ms(33);
//        }
//        
//        setDots(0xFF);
//        __delay_ms(5000);
    }
}
/**
 End of File
*/