/**
  EUSART1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart1.h

  @Summary
    This is the generated header file for the EUSART1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for EUSART1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15355
        Driver Version    :  2.1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB 	          :  MPLAB X 5.40
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

#ifndef EUSART1_H
#define EUSART1_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


/**
  Section: Macro Declarations
*/

#define EUSART1_DataReady  (EUSART1_is_rx_ready())

/**
  Section: Data Type Definitions
*/

typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}eusart1_status_t;

/**
 Section: Global variables
 */
extern volatile uint8_t eusart1TxBufferRemaining;
extern volatile uint8_t eusart1RxCount;

/**
  Section: EUSART1 APIs
*/
extern void (*EUSART1_RxDefaultInterruptHandler)(void);

/**
  @Summary
    Initialization routine that takes inputs from the EUSART1 GUI.

  @Description
    This routine initializes the EUSART1 driver.
    This routine must be called before any other EUSART1 routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    
*/
void EUSART1_Initialize(void);

/**
  @Summary
    Checks if the EUSART1 transmitter is ready to transmit data

  @Description
    This routine checks if EUSART1 transmitter is ready 
    to accept and transmit data byte

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function.
    EUSART1 transmitter should be enabled before calling 
    this function

  @Param
    None

  @Returns
    Status of EUSART1 transmitter
    TRUE: EUSART1 transmitter is ready
    FALSE: EUSART1 transmitter is not ready
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART1_is_rx_ready())
            {
                rxData = UART1_Read();
                if(EUSART1_is_tx_ready())
                {
                    EUSART1Write(rxData);
                }
            }
        }
    }
    </code>
*/
bool EUSART1_is_tx_ready(void);

/**
  @Summary
    Checks if the EUSART1 receiver ready for reading

  @Description
    This routine checks if EUSART1 receiver has received data 
    and ready to be read

  @Preconditions
    EUSART1_Initialize() function should be called
    before calling this function
    EUSART1 receiver should be enabled before calling this 
    function

  @Param
    None

  @Returns
    Status of EUSART1 receiver
    TRUE: EUSART1 receiver is ready for reading
    FALSE: EUSART1 receiver is not ready for reading
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART1_is_rx_ready())
            {
                rxData = UART1_Read();
                if(EUSART1_is_tx_ready())
                {
                    EUSART1_Write(rxData);
                }
            }
        }
    }
    </code>
*/
bool EUSART1_is_rx_ready(void);

/**
  @Summary
    Checks if EUSART1 data is transmitted

  @Description
    This function return the status of transmit shift register

  @Preconditions
    EUSART1_Initialize() function should be called
    before calling this function
    EUSART1 transmitter should be enabled and EUSART1_Write
    should be called before calling this function

  @Param
    None

  @Returns
    Status of EUSART1 receiver
    TRUE: Data completely shifted out if the USART shift register
    FALSE: Data is not completely shifted out of the shift register
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            if(EUSART1_is_tx_ready())
            {
				LED_0_SetHigh();
                EUSART1Write(rxData);
            }
			if(EUSART1_is_tx_done()
            {
                LED_0_SetLow();
            }
        }
    }
    </code>
*/
bool EUSART1_is_tx_done(void);

/**
  @Summary
    Gets the error status of the last read byte.

  @Description
    This routine gets the error status of the last read byte.

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function. The returned value is only
    updated after a read is called.

  @Param
    None

  @Returns
    the status of the last read byte

  @Example
	<code>
    void main(void)
    {
        volatile uint8_t rxData;
        volatile eusart1_status_t rxStatus;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        // Enable the Global Interrupts
        INTERRUPT_GlobalInterruptEnable();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART1_is_rx_ready())
            {
                rxData = EUSART1_Read();
                rxStatus = EUSART1_get_last_status();
                if(rxStatus.ferr){
                    LED_0_SetHigh();
                }
            }
        }
    }
    </code>
 */
eusart1_status_t EUSART1_get_last_status(void);

/**
  @Summary
    Read a byte of data from the EUSART1.

  @Description
    This routine reads a byte of data from the EUSART1.

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if the receiver is not empty before calling this function.

  @Param
    None

  @Returns
    A data byte received by the driver.
*/
uint8_t EUSART1_Read(void);

 /**
  @Summary
    Writes a byte of data to the EUSART1.

  @Description
    This routine writes a byte of data to the EUSART1.

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the EUSART1

  @Returns
    None
*/
void EUSART1_Write(uint8_t txData);


/**
  @Summary
    Maintains the driver's receiver state machine and implements its ISR

  @Description
    This routine is used to maintain the driver's internal receiver state
    machine.This interrupt service routine is called when the state of the
    receiver needs to be maintained in a non polled manner.

  @Preconditions
    EUSART1_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void EUSART1_Receive_ISR(void);

/**
  @Summary
    Maintains the driver's receiver state machine

  @Description
    This routine is called by the receive state routine and is used to maintain 
    the driver's internal receiver state machine. It should be called by a custom
    ISR to maintain normal behavior

  @Preconditions
    EUSART1_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void EUSART1_RxDataHandler(void);

/**
  @Summary
    Set EUSART1 Framing Error Handler

  @Description
    This API sets the function to be called upon EUSART1 framing error

  @Preconditions
    Initialize  the EUSART1 before calling this API

  @Param
    Address of function to be set as framing error handler

  @Returns
    None
*/
void EUSART1_SetFramingErrorHandler(void (* interruptHandler)(void));

/**
  @Summary
    Set EUSART1 Overrun Error Handler

  @Description
    This API sets the function to be called upon EUSART1 overrun error

  @Preconditions
    Initialize  the EUSART1 module before calling this API

  @Param
    Address of function to be set as overrun error handler

  @Returns
    None
*/
void EUSART1_SetOverrunErrorHandler(void (* interruptHandler)(void));

/**
  @Summary
    Set EUSART1 Error Handler

  @Description
    This API sets the function to be called upon EUSART1 error

  @Preconditions
    Initialize  the EUSART1 module before calling this API

  @Param
    Address of function to be set as error handler

  @Returns
    None
*/
void EUSART1_SetErrorHandler(void (* interruptHandler)(void));


/**
  @Summary
    Sets the receive handler function to be called by the interrupt service

  @Description
    Calling this function will set a new custom function that will be 
    called when the receive interrupt needs servicing.

  @Preconditions
    EUSART1_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    A pointer to the new function

  @Returns
    None
*/
void EUSART1_SetRxInterruptHandler(void (* interruptHandler)(void));

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // EUSART1_H
/**
 End of File
*/
