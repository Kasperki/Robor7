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

int timeT = 0, timeT2 = 0; //kello
int timeForward = 150; //.... 4m täydellä vauhdilla 3.9s
int turnTime = 75; 	   //.... 90 asteen käännökseen meneväaika
int timeRobotWidth = 15; //.... Robotin leveyteen menevä aika ?
int trig = 0;

//Main Method
void main(void)
{
	//Määrittelyt
	char buffer[5];
	volatile int i = 0;
	int turn = 0;
	int ultraData = 0;
	int ammu = 1;
	
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
	
	PGA_SetGain(PGA_G8_00);
	PGA_Start(PGA_MEDPOWER);
	
	ADCINC_1_Start(ADCINC_1_HIGHPOWER);
	ADCINC_1_GetSamples(0);
	
	
	
	//MainLoop**********
	//***********************
	while(1)
	{
		//NEW STUFF
		if (trig == 1)
		{
			UATrig_Data_ADDR |= UATrig_MASK;
		}
		else 	
			UATrig_Data_ADDR &= 0x00;
		
		
		if(ADCINC_1_fIsDataAvailable() != 0)
			ultraData = ADCINC_1_iGetData();
		
		ultraData = ADCINC_1_iClearFlagGetData();
		//END

		
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
		
		/*
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
		}*/
	
		if(timeT > 100)
		{
			itoa(buffer,ultraData,10);
			LCD_Position(0,0);
			LCD_PrString(buffer);
			
			itoa(buffer,timeT,10);
			LCD_Position(1,5);
			LCD_PrString(buffer);
			
			timeT = 0;
		}
		
		
	}

}

//Kutsutaan joka 0.01s = 10ms välein.
#pragma interrupt_handler TimerInterrupt
void TimerInterrupt()
{
  timeT++;
  timeT2++;
}

//NEW STUFF
#pragma iterrupt_handler TimerUAInterrupt
void TimerUAInterrupt()
{
	if(timeT2 > 6)
	{
		timeT2 = 0;
		trig = 1;
	}
	
	if (trig == 1)
	{
		trig = 0;
	}
}
