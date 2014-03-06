#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

//Porttien osoitteet
//Port1_0 LEFTC      C = 1, D = 0 FORWARD
//Port1_1 LEFTD		 C = 0, D = 1 BACKWARD 

//Port1_2 RIGHTC
//Port1_3 RIGHTD

const float OIKEUSKERROIN = 0.8f; //Kerroin vasemalle puolelle jotta robotti kulkisi suoraan

//Käynnistää PWM Moduulit
void InitPWM()
{
	PWM8_VASEN_Start();
	PWM8_OIKEA_Start();
	
	LEFTC_Data_ADDR &= 0x00;
	LEFTD_Data_ADDR &= 0x00;
	RIGHTC_Data_ADDR &= 0x00;
	RIGHTD_Data_ADDR &= 0x00;
}

//Kulkee eteenpäin arvolla..
void MoveForward(int pulse)
{				
	LEFTC_Data_ADDR |= LEFTC_MASK;
	LEFTD_Data_ADDR &= 0x00;
	RIGHTC_Data_ADDR |= RIGHTC_MASK;
	RIGHTD_Data_ADDR &= 0x00;
	
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Kulkee taaksepäin arvolla
void MoveBackward(int pulse)
{
	LEFTC_Data_ADDR &= 0x00;
	LEFTD_Data_ADDR |= LEFTD_MASK;
	RIGHTC_Data_ADDR &= 0x00;
	RIGHTD_Data_ADDR |= RIGHTD_MASK;
	
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Pysäyttää Moottorit
void Stop()
{
	PWM8_OIKEA_WritePulseWidth(0);
	PWM8_VASEN_WritePulseWidth(0);
	
	LEFTC_Data_ADDR &= 0x00;
	LEFTD_Data_ADDR &= 0x00;
	RIGHTC_Data_ADDR &= 0x00;
	RIGHTD_Data_ADDR &= 0x00;
}

//Kääntyy vasemmalle
void TurnLeft(int pulse)
{
	LEFTC_Data_ADDR &= 0x00;
	LEFTD_Data_ADDR |= LEFTD_MASK;
	RIGHTC_Data_ADDR |= RIGHTC_MASK;
	RIGHTD_Data_ADDR &= 0x00;
		
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Kääntyy oikealle
void TurnRight(int pulse)
{		
	LEFTC_Data_ADDR |= LEFTC_MASK;
	LEFTD_Data_ADDR &= 0x00;
	RIGHTC_Data_ADDR &= 0x00;
	RIGHTD_Data_ADDR |= RIGHTD_MASK;
	
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//TEST LEFTTURN
void TestTurnLeft(int pulse)
{
	LEFTC_Data_ADDR &= 0x00;
	LEFTD_Data_ADDR &= 0x00;
	RIGHTC_Data_ADDR &= 0x00;
	RIGHTD_Data_ADDR |= RIGHTD_MASK;
	
	PWM8_VASEN_WritePulseWidth(0);
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}
