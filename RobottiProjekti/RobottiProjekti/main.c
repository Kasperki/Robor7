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
//.... 4m täydellä vauhdilla 3.9s

int timeT = 0;

//Main Method
void main(void)
{
	//Määrittelyt
	int pulseForward = 0;
	char buffer[5];
	volatile int i = 0;
	int a = 0;
	
	//Init**************************
	
	//Enables Global Interrupts
	M8C_EnableGInt; 
	
	//Start LCD
	LCD_Start();
	
	//InitializeTimer
	Timer8_Start();
	Timer8_EnableInt();
	
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
		
			if(pulseForward < 198) 
			{
				pulseForward++;
			}
						
			//Ajaa moottoreita
			if(a == 0)
				MoveForward(199);
			else if (a == 1)
				Stop();

			
			//WRITE TO LCD
			itoa(buffer,pulseForward,10);
			LCD_Position(0,2);
			LCD_PrString(buffer);
		}
		
		
		//1s välein vaihda suuntaa. (10ms * 100 = 1s)
		if (timeT == 1000) //1000 = 10s
		{
			a++;
			timeT = 0;
		}
	}

}

//Kutsutaan joka 0.01s = 10ms välein.
#pragma interrupt_handler TimerInterrupt
void TimerInterrupt()
{
  timeT++;
}

