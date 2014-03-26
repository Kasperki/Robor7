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
volatile int timeT = 0,timeT2 = 0;
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
	
	Delay(200);
	
	//Testink
	//TestLoop();

	//MainLoop**********
	//***********************
	while(1)
	{
		//Controlls the ultraSonic trigger
		ControlTrigger(&timeUltra);	
			
		//Gets the data
		ultraData = getDataUA();
		
	
	}
}

//Delay function
void Delay(int dealy)
{
	int timme = timeT + dealy;
	while (timeT < timme)
	{}
	
	timeT = 0;
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
		if (timeT < 200)
			ControlServo(8);
		else if(timeT < 400)
			ControlServo(15);
		else if(timeT < 600)
			ControlServo(25);
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

