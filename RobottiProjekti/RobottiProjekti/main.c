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
	InitPWM();
	
	//Init Servo
	InitUAServo();
		
	//Delay10msTimes(50);
	
	//Testink
	TestLoop();

	//MainLoop**********
	//***********************
	/*while(1)
	{

		
	}*/
}



//Palauttaa eerolle millisekunnit siitä asti ku psoc on käynnistytnyt
//Kutsutaan joka 0.001s = 1ms välein.
void TimerInterrupt(void)
{
  timeT++;
	
  //DO NOT TOUCH
  milliT++;
}



//Counter INTERRUPT
void CounterISR(void)
{
  	ultraData++;
}

// Pin interrupt
void PinInterrupt(void){}



//For Testing
void TestLoop(void)
{
	while(1)
	{	
		sendTrigPulse(&ultraData);
		
		distanceCM = ultraData * 2;		
				
		itoa(buffer,distanceCM,10);
		LCD_Position(0,0);
		LCD_PrCString("     ");
		LCD_Position(0,0);
		LCD_PrString(buffer);
				
	}
}

////OMA Delay function 
//void Delay(int delay)
//{
//	unsigned long int timme = milliT + delay;
//	while (milliT < timme){}
//}
