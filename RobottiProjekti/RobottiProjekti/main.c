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

#pragma interrupt_handler PinInterrupt

void Delay(int);
void TestLoop(void);
void CounterISR(void);

//Kellot
volatile int timeT = 0;
int timeUltra = 0,timeUltraRead = 0;
volatile unsigned long int milliT = 0;

//Test
volatile int a = 0;
char buffer[10];

int pertti = 0;
int timeForward = 50; //.... 4m täydellä vauhdilla 3.7s
int turnTime = 55; 	   //.... 90 asteen käännökseen meneväaika
int timeRobotWidth = 15; //.... Robotin leveyteen menevä aika ?
int ultraData = 0; //Ultraääni anturrista saatava arvo millisekunteina pitää jakaa jollain että saadaan senttimerejä

//Main Method
void main(void)
{
	//Init**************************
	
	//Enables Global Interrupts
	M8C_EnableGInt; 
	M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO);	//VITTU
	
	//Start LCD
	LCD_Start();
	//InitializeTimer
	Timer8_Start();
	Timer8_EnableInt();
		
	Counter16_1_EnableInt();
	Counter16_1_Start();
	
	//Start Motor PWMs
	//InitPWM();
	
	//Init Servo
	//InitUAServo();
		
	//Delay(500);
	
	//Counter8_Start();
	
	//Testink
	TestLoop();

	//MainLoop**********
	//***********************
	/*while(1)
	{
		//Controlls the ultraSonic trigger
		ControlTrigger(&timeUltra);	
			
		//Gets the data
		//ultraData = getDataUA();
		
	}*/
}

//Delay function
void Delay(int dealy)
{
	unsigned long int timme = milliT + dealy;
	while (milliT < timme){}
}

//Palauttaa eerolle millisekunnit siitä asti ku psoc on käynnistytnyt
//Kutsutaan joka 0.001s = 1ms välein.
void TimerInterrupt(void)
{
  timeT++;
	
  //DO NOT TOUCH
  milliT++;
  timeUltra++;
  timeUltraRead++;
}

//Counter INTERRUPT
void CounterISR(void)
{
  pertti++;
}

void PinInterrupt(void)
{
	static BYTE port0_prevValue;
	static nousevaReuna;
	
	//a++;
	
	//UÅ ECHO 
	/* Check if interrupt because of P0_7 change from read */
	if ((PRT0DR ^ port0_prevValue)==0x80)
	{
	
		if (nousevaReuna == 0)
		{
			timeUltraRead = 0;
			nousevaReuna = 1;
			//Counter8_Start();
			//a = 1;
		}
		else 
		{
			nousevaReuna = 0;
			//ultraData = Counter8_wReadCounter();
			//Counter8_Stop();
			//a = 0;
			//ultraData = timeUltraRead;
		}
	}

	/* Store values of P0_40 for next ISR */
	port0_prevValue = PRT0DR & 0x80;
	
}


//For Testing
void TestLoop(void)
{
	while(1)
	{
		
		UATrig_Data_ADDR |= UATrig_MASK;
		Delay(1);
		pertti = 0;
		UATrig_Data_ADDR &= 0b00000000;	
		Delay(10);
		a = pertti;
		//~UATrig_MASK
		
		itoa(buffer,a,10);
		LCD_Position(0,0);
		LCD_PrCString("     ");
		LCD_Position(0,0);
		LCD_PrString(buffer);
		
//		itoa(buffer,t++,10);
//		LCD_Position(1,0);
//		LCD_PrCString("     ");
//		LCD_Position(1,0);
//		LCD_PrString(buffer);
//		for (j=0;j<9000;j++);
			
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
		/*if (timeT < 2000)
			ControlServo(8);
		else if(timeT < 4000)
			ControlServo(15);
		else if(timeT < 6000)
			ControlServo(25);
		else
			Stop();
		*/	
		//Test 90 degree Turn
		/*	
			if(timeT <= 100) //1.0s
				TurnRight(FULL_SPEED);
			else if(timeT <= 400)
				timeT = 0;
		*/
		
	}
}

