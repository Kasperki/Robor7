//----------------------------------------------------------------------------
// Robotti Projekti
// Robor7 @ 2014
// Kasper Kiiskinen, Henri Sinokki, Eero Holopainen, Mikko Liira, Kari Lampi
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include<stdio.h>
#include<stdlib.h>
#include "delay.h"

//Omat header filet
#include "MotorControl.h"
#include "UltraControl.h"
//#include "GyroControl.h"

#pragma interrupt_handler PinInterrupt

void Delay(int);
void TestLoop(void);
void CounterISR(void);
void CheckLeft(void);
void CheckRight(void);

//Kellot
volatile int timeT = 0;
int timeUltra = 0,timeUltraRead = 0;
volatile unsigned long int milliT = 0;

//Test
volatile int distanceCM = 0;
char buffer[10];

int vaihe = 0;
int left, right;
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
		
	Delay10msTimes(100);
	vaihe = 1;
	
	//Testink
	//TestLoop();

	//MainLoop**********
	//***********************
	while(1)
	{
		// Eteenpäin ajo vaihe, ajetaan eteenpäin niin pitkään kunnes ollaan 20cm päästä seinästä.
		if( vaihe == 1 )
		{	
			sendTrigPulse(&ultraData);
			
			distanceCM = ultraData * 2;	

			if (distanceCM >= 60)
			{	
				MoveForward(HALF_SPEED);
			}
			else if (distanceCM < 60 && distanceCM > 40)
			{
				MoveForward(SLOW_SPEED);
			}				
			else 
			{
				Stop();
				vaihe = 2;
			}
		}
		// Vaiheessa ollaan pysähtyneenä ja katsomme vasemmalle ja oikealle ja teemme päätöksen kumpaan suuntaan käännymme.
		if ( vaihe == 2 )
		{
				CheckLeft();
				left = ultraData * 2;
				CheckRight();
				right = ultraData * 2;
			
				if (right>left)
				{	//turn right
					TurnRight(TURN_SPEED);
					Delay10msTimes(55);
					Stop();
				}
				else 
				{
					TurnLeft(TURN_SPEED);
					Delay10msTimes(55);
					Stop();
					//turnlefti
				}
					
				ControlServo(SERVO_MIDDLE);
				Delay(1000);
				vaihe = 1;
		}

		
	}
}

void CheckLeft(void)
{
	ControlServo(SERVO_LEFT);
	Delay10msTimes(50);
	sendTrigPulse(&ultraData);
}

void CheckRight(void)
{
	ControlServo(SERVO_RIGHT);
	Delay10msTimes(50);
	sendTrigPulse(&ultraData);
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
		TurnRight(TURN_SPEED);
		Delay10msTimes(75);
		
		Stop();
		Delay10msTimes(250);
		
		TurnLeft(TURN_SPEED);
		Delay10msTimes(75);
		
		Stop();
		Delay10msTimes(250);
		
		/*sendTrigPulse(&ultraData);
		
		distanceCM = ultraData * 2;		
	
		itoa(buffer,distanceCM,10);
		LCD_Position(0,0);
		LCD_PrCString("     ");
		LCD_Position(0,0);
		LCD_PrString(buffer);
		*/		
	}
}

////OMA Delay function 
void Delay(int delay)
{
	unsigned long int timme = milliT + delay;
	while (milliT < timme){}
}
