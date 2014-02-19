#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

//Esim!
//PRT0GS |= 0x01; Connects PORT_0_0 to GlobalOutEven 
//PRT0GS &= ~0x01; Disconnects PORT0_0 from GlobalOutEven

//Porttien osoitteet
const int LEFTFOW = 0x01; //Port0_0 VasenPuoli Eteenpäin
const int LEFTBACK = 0x10; //Port0_4 VasenPuoli Taaksepäin

const int RIGHTFOW = 0x02; //Port0_1 OikeaPuoli Eteenpäin
const int RIGHTBACK = 0x20; //Port0_5 OikeaPuoli Taaksepäin
const float OIKEUSKERROIN = 0.8f; //Kerroin vasemalle puolelle jotta robotti kulkisi suoraan

//Käynnistää PWM Moduulit
void InitPWM()
{
	PWM8_VASEN_Start();
	PWM8_OIKEA_Start();
	
	PRT0GS &= ~LEFTBACK;
	PRT0GS &= ~RIGHTBACK;
	PRT0GS &= ~LEFTFOW;
	PRT0GS &= ~RIGHTFOW;
}

//Kulkee eteenpäin arvolla..
void MoveForward(int pulse)
{			
	PRT0GS |= LEFTFOW;
	PRT0GS |= RIGHTFOW;
	PRT0GS &= ~LEFTBACK;
	PRT0GS &= ~RIGHTBACK;
	
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Kulkee taaksepäin arvolla
void MoveBackward(int pulse)
{
	PRT0GS &= ~LEFTFOW;
	PRT0GS &= ~RIGHTFOW;
	PRT0GS |= LEFTBACK;
	PRT0GS |= RIGHTBACK;
	
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Pysäyttää Moottorit
void Stop()
{
	PWM8_OIKEA_WritePulseWidth(0);
	PWM8_VASEN_WritePulseWidth(0);
	PRT0GS &= ~LEFTBACK;
	PRT0GS &= ~RIGHTBACK;
	PRT0GS &= ~LEFTFOW;
	PRT0GS &= ~RIGHTFOW;
}

//Kääntyy vasemmalle
void TurnLeft(int pulse)
{
	PRT0GS &= ~LEFTBACK;
	PRT0GS |= LEFTFOW;
	PRT0GS &= ~RIGHTFOW;
	PRT0GS |= RIGHTBACK;
		
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Kääntyy oikealle
void TurnRight(int pulse)
{
	PRT0GS |= LEFTBACK;
	PRT0GS &= ~LEFTFOW;
	PRT0GS |= RIGHTFOW;
	PRT0GS &= ~RIGHTBACK;
	
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//TEST RIGHTTURN
void TestTurnRight(int pulse)
{
	PRT0GS &= ~LEFTBACK;
	PRT0GS &= ~LEFTFOW;
	PRT0GS |= RIGHTFOW;
	PRT0GS &= ~RIGHTBACK;
	
	//PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}
