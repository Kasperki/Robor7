//----------------------------------------------------------------------------
// Robotti Projekti
// Robor7 @ 2014
// Kasper Kiiskinen, Henri Sinokki, Eero Holopainen, Mikko Liira, Kari Lampi
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include<stdio.h>
#include<stdlib.h>

//Omat header filet
#include "MotorControl.h"
//#include "UltraControl.h"
//#include "GyroControl.h"

int timeT = 0; //kello
int timeForward = 150; //.... 4m täydellä vauhdilla 3.9s
int turnTime = 75; 	   //.... 90 asteen käännökseen meneväaika
int timeRobotWidth = 15; //.... Robotin leveyteen menevä aika ?

//Main Method
void main(void)
{
	//Määrittelyt
	char buffer[5];
	volatile int i = 0;
	int turn = 0;
	
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
	
		//Spiraali
		if(i < 3)
		{
			if(turn == 0)
				MoveForward(FULL_SPEED);
			else 
			{
				if(timeT <= turnTime) //if(gyroKulma < 90)
				{
					TurnLeft(FULL_SPEED);
				}
				else
				{ 
					turn = 0;
					timeT = 0;
				}
			}
		}
		else if(i < 5) 
		{
			i = 0;
			timeForward -= timeRobotWidth;
		}
		
		//Kokokierros on menty
		if(timeForward <= 0)
		{
			i = 10;
			timeForward = 0;
			Stop();
		}
		//End Spiraali
		
		
		//Scan
		/*
			if(i == 10)
			{
				Skannaa keiloja.
				while(kulma >= 360)
				{
					WaitForScan?
					If(output => 0) 
						MoveForward(199);
					else
						TurnLeft(199); kulma += 10;
				}
		
				Jos ei löydy i = 20;
			}
		*/
		
		if (timeT >= timeForward && turn == 0)
		{
			i++;
			turn = 1;
			timeT = 0;
			
			//WRITE TO LCD
			itoa(buffer,timeForward,10);
			LCD_Position(0,5);
			LCD_PrString(buffer);
			
			itoa(buffer,i,10);
			LCD_Position(0,0);
			LCD_PrString(buffer);
		}
	}

}

//Kutsutaan joka 0.01s = 10ms välein.
#pragma interrupt_handler TimerInterrupt
void TimerInterrupt()
{
  timeT++;
}

