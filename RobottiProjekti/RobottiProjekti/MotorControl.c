#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

//
void InitPWM()
{
	PWM8_VASEN_Start();
	PWM8_OIKEA_Start();
}

//
void MoveForward(int pulse)
{		
	//TODO 
	PWM8_VASEN_WritePulseWidth((BYTE)pulse);
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//
void Stop()
{
	PWM8_OIKEA_WritePulseWidth(0);
	PWM8_VASEN_WritePulseWidth(0);
}

//
void TurnLeft(int pulse)
{
	//
	PWM8_VASEN_WritePulseWidth((BYTE)pulse);
}

//
void TurnRight(int pulse)
{
	//
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}