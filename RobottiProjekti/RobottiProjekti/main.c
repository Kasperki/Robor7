//----------------------------------------------------------------------------
// C main line
// Robor7
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include<stdio.h>
#include<stdlib.h>

//Omat lolol
#include "MotorControl.h"


void main(void)
{
	int pulseForward = 25;
	char buffer[20];
	volatile int i = 0;
	int a = 0;
	
	// M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	
	//Init
	LCD_Start();
	
	//PWMSTARTS
	InitPWM();
	
	//MainLoop
	while(1)
	{
		i++;
		
		if (i > 1000)
		{
			i = 0;
			if(pulseForward <= 190)
			{
				pulseForward++;
				
			}
			else 
				a = 1;
			
			if (a == 0)
				MoveForward(pulseForward);
			else 
				PWM8_VASEN_WritePulseWidth(0);
			
			//if(pulseForward > 198) 
				//pulseForward = 20;
		
			itoa(buffer,pulseForward,10);
			
			LCD_Position(0,0);
			LCD_PrString(buffer);
		}
	}

	while (1){}
}
