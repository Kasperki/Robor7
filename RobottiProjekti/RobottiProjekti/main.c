//----------------------------------------------------------------------------
// Robotti Projekti
// Robor7 @ 2014
// Kasper Kiiskinen, Henri Sinokki, Eero Holopainen, Mikko Litta, Kari Lampinen
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include<stdio.h>
#include<stdlib.h>

//Omat header filet
#include "MotorControl.h"
//#include "UltraControl.h"
//#include "GyroControl.h"
//....

//Main Method
void main(void)
{
	//Määrittelyt
	int pulseForward = 0;
	char buffer[10];
	volatile int i = 0;
	int a = 0;
	
	//Init**************************
	
	// M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	
	//Start LCD
	LCD_Start();
	
	//Start Motor PWMs
	InitPWM();
	
	
	//MainLoop**********
	//***********************
	while(1)
	{
		//TEST CODE AJA MOOTTOREITA ETEEN/TAAKSE
		i++;
		if (i > 1000)
		{
			i = 0;
			pulseForward++;
			
			if(pulseForward > 198) 
			{
				pulseForward = 0;
				
				if(a == 0)
					a = 1;
				else 
					a = 0;
			}
			
			//Ajaa moottoreita
			if(a == 1)
				MoveBackward(pulseForward);
			else 
				MoveForward(pulseForward);
			
			
			//WRITE TO LCD
			itoa(buffer,pulseForward,10);
			LCD_Position(0,2);
			LCD_PrString(buffer);
		}
	}

	while (1){}
}
