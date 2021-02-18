 /**
   CLC1 Generated Driver API Header File
 
   @Company
     Microchip Technology Inc. 

   @File Name
    clc1.h

   @Summary
     This is the generated header file for the CLC1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This header file provides APIs for driver for CLC1.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
         Device            :  PIC16F15355
         Driver Version    :  2.11
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

#ifndef CLC1_H
 #define CLC1_H
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: CLC1 APIs
*/

/**
  @Summary
    Initializes the CLC1

  @Description
    This routine configures the CLC1 specific control registers

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment

  @Example
    <code>
    CLC1_Initialize();
    </code>
*/
void CLC1_Initialize(void);

/**
  @Summary
    Returns output pin status of the CLC module.

  @Description
    This routine returns output pin status of the CLC module.

  @Param
    None.

  @Returns
    Output pin status
 
  @Example 
    <code>
    bool outputStatus;
    outputStatus = CLC1_OutputStatusGet();
    </code>
*/

bool CLC1_OutputStatusGet(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // CLC1_H
/**
 End of File
*/

