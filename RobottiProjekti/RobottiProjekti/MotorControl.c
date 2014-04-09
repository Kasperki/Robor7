#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

#define BACKWARD 	0b00000101; // Molemmat Eteen
#define FORWARD 	0b00001010; //Molemmat Taakse
#define LEFTBRIGHTF 0b00001001; // Vasen Eteen Oikea Taakse
#define LEFTFRIGHTB 0b00000110; // Vasen Taakse Oikea Eteen
#define NOLLAA 		0b11110000;		//Molemmat C/D pinnit 0

//Porttien osoitteet
//Port1_0 LEFTC      C = 1, D = 0 FORWARD
//Port1_1 LEFTD		 C = 0, D = 1 BACKWARD 
//Port1_2 RIGHTC
//Port1_3 RIGHTD

const float OIKEUSKERROIN = 1.0f; //Kerroin vasemalle puolelle jotta robotti kulkisi suoraan

//Käynnistää PWM Moduulit
void InitPWM(void)
{
	PWM8_VASEN_Start();
	PWM8_OIKEA_Start();
	
	//Port1_Data_ADDR = LEFTC_Data_ADDR;
	//Port1_Data_ADDR &= NOLLAA;
}

//Kulkee eteenpäin arvolla..
void MoveForward(int pulse)
{				
	LEFTC_Data_ADDR &= NOLLAA;
	LEFTC_Data_ADDR |= FORWARD;

	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Kulkee taaksepäin arvolla
void MoveBackward(int pulse)
{
	LEFTC_Data_ADDR &= NOLLAA;
	LEFTC_Data_ADDR |= BACKWARD;
	
	PWM8_VASEN_WritePulseWidth((BYTE)(pulse * OIKEUSKERROIN));
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Pysäyttää Moottorit
void Stop(void)
{
	PWM8_OIKEA_WritePulseWidth(0);
	PWM8_VASEN_WritePulseWidth(0);
	
	LEFTC_Data_ADDR &= NOLLAA;
}

//Kääntyy vasemmalle
void TurnLeft(int pulse)
{
	LEFTC_Data_ADDR &= NOLLAA;
	LEFTC_Data_ADDR |= LEFTFRIGHTB
		
	PWM8_VASEN_WritePulseWidth((BYTE)pulse);
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}

//Kääntyy oikealle
void TurnRight(int pulse)
{		
	LEFTC_Data_ADDR &= NOLLAA;
	LEFTC_Data_ADDR |= LEFTBRIGHTF;
	
	PWM8_VASEN_WritePulseWidth((BYTE)pulse);
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}


//TEST LEFTTURN
void TestTurnLeft(int pulse)
{
	LEFTC_Data_ADDR &= NOLLAA;
	LEFTC_Data_ADDR |= 0b00000001;
	
	PWM8_VASEN_WritePulseWidth(0);
	PWM8_OIKEA_WritePulseWidth((BYTE)pulse);
}
