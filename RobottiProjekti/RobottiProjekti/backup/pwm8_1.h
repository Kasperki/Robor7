//*****************************************************************************
//*****************************************************************************
//  FILENAME: PWM8_1.h
//   Version: 2.5, Updated on 2013/5/19 at 10:44:6
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: PWM16 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef PWM8_1_INCLUDE
#define PWM8_1_INCLUDE

#include <m8c.h>

#pragma fastcall16 PWM8_1_EnableInt
#pragma fastcall16 PWM8_1_DisableInt
#pragma fastcall16 PWM8_1_Start
#pragma fastcall16 PWM8_1_Stop
#pragma fastcall16 PWM8_1_wReadCounter              // Read  DR0
#pragma fastcall16 PWM8_1_WritePeriod               // Write DR1
#pragma fastcall16 PWM8_1_wReadPulseWidth           // Read  DR2
#pragma fastcall16 PWM8_1_WritePulseWidth           // Write DR2

// The following symbols are deprecated.
// They may be omitted in future releases
//
#pragma fastcall16 wPWM8_1_ReadCounter              // Read  DR0 (Deprecated)
#pragma fastcall16 wPWM8_1_ReadPulseWidth           // Read  DR2 (Deprecated)


//-------------------------------------------------
// Prototypes of the PWM8_1 API.
//-------------------------------------------------

extern void PWM8_1_EnableInt(void);                  // Proxy Class 1
extern void PWM8_1_DisableInt(void);                 // Proxy Class 1
extern void PWM8_1_Start(void);                      // Proxy Class 1
extern void PWM8_1_Stop(void);                       // Proxy Class 1
extern WORD PWM8_1_wReadCounter(void);               // Proxy Class 2
extern void PWM8_1_WritePeriod(WORD wPeriod);        // Proxy Class 1
extern WORD PWM8_1_wReadPulseWidth(void);            // Proxy Class 1
extern void PWM8_1_WritePulseWidth(WORD wPulseWidth);// Proxy Class 1

// The following functions are deprecated.
// They may be omitted in future releases
//
extern WORD wPWM8_1_ReadCounter(void);            // Deprecated
extern WORD wPWM8_1_ReadPulseWidth(void);         // Deprecated


//-------------------------------------------------
// Constants for PWM8_1 API's.
//-------------------------------------------------

#define PWM8_1_CONTROL_REG_START_BIT           ( 0x01 )
#define PWM8_1_INT_REG_ADDR                    ( 0x0e1 )
#define PWM8_1_INT_MASK                        ( 0x10 )


//--------------------------------------------------
// Constants for PWM8_1 user defined values
//--------------------------------------------------

#define PWM8_1_PERIOD                          ( 0x18f )
#define PWM8_1_PULSE_WIDTH                     ( 0x0 )


//-------------------------------------------------
// Register Addresses for PWM8_1
//-------------------------------------------------

#pragma ioport  PWM8_1_COUNTER_LSB_REG: 0x02c              //DR0 Count register LSB
BYTE            PWM8_1_COUNTER_LSB_REG;
#pragma ioport  PWM8_1_COUNTER_MSB_REG: 0x030              //DR0 Count register MSB
BYTE            PWM8_1_COUNTER_MSB_REG;
#pragma ioport  PWM8_1_PERIOD_LSB_REG:  0x02d              //DR1 Period register LSB
BYTE            PWM8_1_PERIOD_LSB_REG;
#pragma ioport  PWM8_1_PERIOD_MSB_REG:  0x031              //DR1 Period register MSB
BYTE            PWM8_1_PERIOD_MSB_REG;
#pragma ioport  PWM8_1_COMPARE_LSB_REG: 0x02e              //DR2 Compare register LSB
BYTE            PWM8_1_COMPARE_LSB_REG;
#pragma ioport  PWM8_1_COMPARE_MSB_REG: 0x032              //DR2 Compare register MSB
BYTE            PWM8_1_COMPARE_MSB_REG;
#pragma ioport  PWM8_1_CONTROL_LSB_REG: 0x02f              //Control register LSB
BYTE            PWM8_1_CONTROL_LSB_REG;
#pragma ioport  PWM8_1_CONTROL_MSB_REG: 0x033              //Control register MSB
BYTE            PWM8_1_CONTROL_MSB_REG;
#pragma ioport  PWM8_1_FUNC_LSB_REG:    0x12c              //Function register LSB
BYTE            PWM8_1_FUNC_LSB_REG;
#pragma ioport  PWM8_1_FUNC_MSB_REG:    0x130              //Function register MSB
BYTE            PWM8_1_FUNC_MSB_REG;
#pragma ioport  PWM8_1_INPUT_LSB_REG:   0x12d              //Input register LSB
BYTE            PWM8_1_INPUT_LSB_REG;
#pragma ioport  PWM8_1_INPUT_MSB_REG:   0x131              //Input register MSB
BYTE            PWM8_1_INPUT_MSB_REG;
#pragma ioport  PWM8_1_OUTPUT_LSB_REG:  0x12e              //Output register LSB
BYTE            PWM8_1_OUTPUT_LSB_REG;
#pragma ioport  PWM8_1_OUTPUT_MSB_REG:  0x132              //Output register MSB
BYTE            PWM8_1_OUTPUT_MSB_REG;
#pragma ioport  PWM8_1_INT_REG:       0x0e1                //Interrupt Mask Register
BYTE            PWM8_1_INT_REG;


//-------------------------------------------------
// PWM8_1 Macro 'Functions'
//-------------------------------------------------

#define PWM8_1_Start_M \
   ( PWM8_1_CONTROL_LSB_REG |=  PWM8_1_CONTROL_REG_START_BIT )

#define PWM8_1_Stop_M  \
   ( PWM8_1_CONTROL_LSB_REG &= ~PWM8_1_CONTROL_REG_START_BIT )

#define PWM8_1_EnableInt_M   \
   M8C_EnableIntMask(  PWM8_1_INT_REG, PWM8_1_INT_MASK )

#define PWM8_1_DisableInt_M  \
   M8C_DisableIntMask( PWM8_1_INT_REG, PWM8_1_INT_MASK )

#endif
// end of file PWM8_1.h
