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
#include "UltraControl.h"
//#include "GyroControl.h"

//Kellot
int timeT = 0,timeT2 = 0;
int timeLCD = 0,timeUltra = 0; 

int timeForward = 50; //.... 4m täydellä vauhdilla 3.7s
int turnTime = 55; 	   //.... 90 asteen käännökseen meneväaika
int timeRobotWidth = 15; //.... Robotin leveyteen menevä aika ?

//Main Method
void main(void)
{
	//Määrittelyt
	char buffer[10];
	volatile int i = 0;
	int turn = 0;
	int ultraData = 0; //Data from ultrasonic sensor
	int kulma = 0;
	
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
	
	//Init PGA and ADCIN for Ultrasonic
	InitUA();
	
	//Testink
	//TestLoop();
	
	i = 100;
	
	//MainLoop**********
	//***********************
	while(1)
	{
		//Controlls the ultraSonic trigger
		ControlTrigger(&timeUltra);	
			
		//Gets the data
		ultraData = getDataUA();
		
		//Spiraali
		if(i < 10)
		{
			if(i < 3)
			{
				if(turn == 0)
					MoveForward(HALF_SPEED);
				else if(turn == 1)
				{
					Stop();
					if(timeT >= 100)
					{
						turn = 2; 
						timeT = 0;
					}
				}
				else 
				{
					if(timeT <= turnTime) //if(gyroKulma < 90)
					{
						TurnLeft(HALF_SPEED);
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
				timeT = 0; 
				timeT2 = 0;
				turn = 0;
				timeForward = 0;
				Stop();
			}
			else if (timeT >= timeForward && turn == 0)
			{
				i++;
				turn = 1;
				timeT = 0;
			}
		}
		//End Spiraali
		
		
		//Scan
		if(i == 100)
		{
			if(kulma < 30000)
			{
				if(ultraData < 300)
				{	
					if(ultraData > 0)
						MoveForward(HALF_SPEED); 
				}
				else if (timeT2 >= 50) //WAIT 500ms
				{
					if (turn == 0)
					{	
						timeT = 0;
						turn = 1;
					}
						
					if(timeT <= 20)
						TurnRight(SLOW_SPEED);
					else
					{
						kulma+=5;
						timeT2 = 0;
						turn = 0;
					}
				}
				else 
					Stop();
			}
			else 
				i = 20;
		}
		
		if(i == 20)
			Stop();
		
		
		//WRITE TO LCD
		if(timeLCD >= 6)
		{
			itoa(buffer,ultraData,10);
			LCD_Position(0,0);
			LCD_PrCString("      ");
			LCD_Position(0,0);
			LCD_PrString(buffer);
					
			//
			LCD_Position(0,5);
			LCD_PrCString("      ");
			itoa(buffer,timeForward,10);
			LCD_Position(0,5);
			LCD_PrString(buffer);
			
			LCD_Position(1,0);
			LCD_PrCString("      ");
			itoa(buffer,kulma,10);
			LCD_Position(1,0);
			LCD_PrString(buffer);
			
			timeLCD = 0;
		}		
	}
}

//Kutsutaan joka 0.01s = 10ms välein.
void TimerInterrupt()
{
  timeT++;
  timeT2++;

  timeLCD++; //Controlls LCD draw cycle
  timeUltra++; //Controlls Ultrasonic sensor trigger time
}

//For Testing
void TestLoop()
{
	while(1)
	{
		
		LCD_Position(1,0);
		LCD_PrCString("PIRI TOIMII");
		
		//Test 4m
		/*
		if (timeT < 250)
			TurnLeft(FULL_SPEED);
		else if (timeT < 500)
			TurnRight(HALF_SPEED);
		else 
			Stop();
		*/
	
		//About 90
		if (timeT < 60)
			TurnLeft(HALF_SPEED);
		else
			Stop();
			
		//Test 90 degree Turn
		/*	
			if(timeT <= 100) //1.0s
				TurnRight(FULL_SPEED);
			else if(timeT <= 400)
				timeT = 0;
		*/
		
	}
}

