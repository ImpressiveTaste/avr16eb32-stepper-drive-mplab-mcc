/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

static void (*IO_PC2_InterruptHandler)(void);
static void (*IO_PA7_InterruptHandler)(void);
static void (*WEX0_WO0_InterruptHandler)(void);
static void (*WEX0_WO1_InterruptHandler)(void);
static void (*WEX0_WO2_InterruptHandler)(void);
static void (*WEX0_WO3_InterruptHandler)(void);
static void (*WEX0_WO4_InterruptHandler)(void);
static void (*WEX0_WO5_InterruptHandler)(void);
static void (*WEX0_WO6_InterruptHandler)(void);
static void (*WEX0_WO7_InterruptHandler)(void);
static void (*IO_PF2_InterruptHandler)(void);
static void (*IO_PC3_InterruptHandler)(void);
static void (*IO_PA5_InterruptHandler)(void);
static void (*IO_PA4_InterruptHandler)(void);
static void (*STEP_InterruptHandler)(void);
static void (*DIR_InterruptHandler)(void);
static void (*DEBUGSW_InterruptHandler)(void);
static void (*RESETSW_InterruptHandler)(void);
static void (*DEBUGLED_InterruptHandler)(void);
static void (*HRTLED_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{

  /* OUT Registers Initialization */
    PORTA.OUT = 0x10;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x0;
    PORTF.OUT = 0x0;

  /* DIR Registers Initialization */
    PORTA.DIR = 0x10;
    PORTC.DIR = 0x0;
    PORTD.DIR = 0xFF;
    PORTF.DIR = 0x30;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x4;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x4;
    PORTC.PIN3CTRL = 0x4;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x4;
    PORTD.PIN6CTRL = 0x4;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x8;
    PORTF.PIN1CTRL = 0x8;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x8;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x8;
    PORTF.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.ACROUTEA = 0x0;
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TCEROUTEA = 0x3;
    PORTMUX.TCFROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x1;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    IO_PC2_SetInterruptHandler(IO_PC2_DefaultInterruptHandler);
    IO_PA7_SetInterruptHandler(IO_PA7_DefaultInterruptHandler);
    WEX0_WO0_SetInterruptHandler(WEX0_WO0_DefaultInterruptHandler);
    WEX0_WO1_SetInterruptHandler(WEX0_WO1_DefaultInterruptHandler);
    WEX0_WO2_SetInterruptHandler(WEX0_WO2_DefaultInterruptHandler);
    WEX0_WO3_SetInterruptHandler(WEX0_WO3_DefaultInterruptHandler);
    WEX0_WO4_SetInterruptHandler(WEX0_WO4_DefaultInterruptHandler);
    WEX0_WO5_SetInterruptHandler(WEX0_WO5_DefaultInterruptHandler);
    WEX0_WO6_SetInterruptHandler(WEX0_WO6_DefaultInterruptHandler);
    WEX0_WO7_SetInterruptHandler(WEX0_WO7_DefaultInterruptHandler);
    IO_PF2_SetInterruptHandler(IO_PF2_DefaultInterruptHandler);
    IO_PC3_SetInterruptHandler(IO_PC3_DefaultInterruptHandler);
    IO_PA5_SetInterruptHandler(IO_PA5_DefaultInterruptHandler);
    IO_PA4_SetInterruptHandler(IO_PA4_DefaultInterruptHandler);
    STEP_SetInterruptHandler(STEP_DefaultInterruptHandler);
    DIR_SetInterruptHandler(DIR_DefaultInterruptHandler);
    DEBUGSW_SetInterruptHandler(DEBUGSW_DefaultInterruptHandler);
    RESETSW_SetInterruptHandler(RESETSW_DefaultInterruptHandler);
    DEBUGLED_SetInterruptHandler(DEBUGLED_DefaultInterruptHandler);
    HRTLED_SetInterruptHandler(HRTLED_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for IO_PC2 at application runtime
*/
void IO_PC2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC2_InterruptHandler = interruptHandler;
}

void IO_PC2_DefaultInterruptHandler(void)
{
    // add your IO_PC2 interrupt custom code
    // or set custom function using IO_PC2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA7 at application runtime
*/
void IO_PA7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA7_InterruptHandler = interruptHandler;
}

void IO_PA7_DefaultInterruptHandler(void)
{
    // add your IO_PA7 interrupt custom code
    // or set custom function using IO_PA7_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO0 at application runtime
*/
void WEX0_WO0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO0_InterruptHandler = interruptHandler;
}

void WEX0_WO0_DefaultInterruptHandler(void)
{
    // add your WEX0_WO0 interrupt custom code
    // or set custom function using WEX0_WO0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO1 at application runtime
*/
void WEX0_WO1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO1_InterruptHandler = interruptHandler;
}

void WEX0_WO1_DefaultInterruptHandler(void)
{
    // add your WEX0_WO1 interrupt custom code
    // or set custom function using WEX0_WO1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO2 at application runtime
*/
void WEX0_WO2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO2_InterruptHandler = interruptHandler;
}

void WEX0_WO2_DefaultInterruptHandler(void)
{
    // add your WEX0_WO2 interrupt custom code
    // or set custom function using WEX0_WO2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO3 at application runtime
*/
void WEX0_WO3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO3_InterruptHandler = interruptHandler;
}

void WEX0_WO3_DefaultInterruptHandler(void)
{
    // add your WEX0_WO3 interrupt custom code
    // or set custom function using WEX0_WO3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO4 at application runtime
*/
void WEX0_WO4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO4_InterruptHandler = interruptHandler;
}

void WEX0_WO4_DefaultInterruptHandler(void)
{
    // add your WEX0_WO4 interrupt custom code
    // or set custom function using WEX0_WO4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO5 at application runtime
*/
void WEX0_WO5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO5_InterruptHandler = interruptHandler;
}

void WEX0_WO5_DefaultInterruptHandler(void)
{
    // add your WEX0_WO5 interrupt custom code
    // or set custom function using WEX0_WO5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO6 at application runtime
*/
void WEX0_WO6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO6_InterruptHandler = interruptHandler;
}

void WEX0_WO6_DefaultInterruptHandler(void)
{
    // add your WEX0_WO6 interrupt custom code
    // or set custom function using WEX0_WO6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO7 at application runtime
*/
void WEX0_WO7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO7_InterruptHandler = interruptHandler;
}

void WEX0_WO7_DefaultInterruptHandler(void)
{
    // add your WEX0_WO7 interrupt custom code
    // or set custom function using WEX0_WO7_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF2 at application runtime
*/
void IO_PF2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF2_InterruptHandler = interruptHandler;
}

void IO_PF2_DefaultInterruptHandler(void)
{
    // add your IO_PF2 interrupt custom code
    // or set custom function using IO_PF2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC3 at application runtime
*/
void IO_PC3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC3_InterruptHandler = interruptHandler;
}

void IO_PC3_DefaultInterruptHandler(void)
{
    // add your IO_PC3 interrupt custom code
    // or set custom function using IO_PC3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA5 at application runtime
*/
void IO_PA5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA5_InterruptHandler = interruptHandler;
}

void IO_PA5_DefaultInterruptHandler(void)
{
    // add your IO_PA5 interrupt custom code
    // or set custom function using IO_PA5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA4 at application runtime
*/
void IO_PA4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA4_InterruptHandler = interruptHandler;
}

void IO_PA4_DefaultInterruptHandler(void)
{
    // add your IO_PA4 interrupt custom code
    // or set custom function using IO_PA4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for STEP at application runtime
*/
void STEP_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    STEP_InterruptHandler = interruptHandler;
}

void STEP_DefaultInterruptHandler(void)
{
    // add your STEP interrupt custom code
    // or set custom function using STEP_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DIR at application runtime
*/
void DIR_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DIR_InterruptHandler = interruptHandler;
}

void DIR_DefaultInterruptHandler(void)
{
    // add your DIR interrupt custom code
    // or set custom function using DIR_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DEBUGSW at application runtime
*/
void DEBUGSW_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DEBUGSW_InterruptHandler = interruptHandler;
}

void DEBUGSW_DefaultInterruptHandler(void)
{
    // add your DEBUGSW interrupt custom code
    // or set custom function using DEBUGSW_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for RESETSW at application runtime
*/
void RESETSW_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    RESETSW_InterruptHandler = interruptHandler;
}

void RESETSW_DefaultInterruptHandler(void)
{
    // add your RESETSW interrupt custom code
    // or set custom function using RESETSW_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DEBUGLED at application runtime
*/
void DEBUGLED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DEBUGLED_InterruptHandler = interruptHandler;
}

void DEBUGLED_DefaultInterruptHandler(void)
{
    // add your DEBUGLED interrupt custom code
    // or set custom function using DEBUGLED_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for HRTLED at application runtime
*/
void HRTLED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    HRTLED_InterruptHandler = interruptHandler;
}

void HRTLED_DefaultInterruptHandler(void)
{
    // add your HRTLED interrupt custom code
    // or set custom function using HRTLED_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT7_bm)
    {
       IO_PA7_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       IO_PA5_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       IO_PA4_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT2_bm)
    {
       IO_PC2_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       IO_PC3_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT0_bm)
    {
       WEX0_WO0_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT1_bm)
    {
       WEX0_WO1_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT2_bm)
    {
       WEX0_WO2_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT3_bm)
    {
       WEX0_WO3_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       WEX0_WO4_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       WEX0_WO5_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       WEX0_WO6_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       WEX0_WO7_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       IO_PF2_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT0_bm)
    {
       STEP_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT1_bm)
    {
       DIR_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT3_bm)
    {
       DEBUGSW_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT6_bm)
    {
       RESETSW_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       DEBUGLED_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       HRTLED_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/