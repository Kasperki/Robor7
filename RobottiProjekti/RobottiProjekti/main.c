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

volatile int distanceCM = 0;
char buffer[10];

// Linefinder test
volatile int onBlackLine = 0, blackLineCounter = 0;

int lastTurn = 1; // muuttuja jolla pidetään kirjaa viimesimmästä käännöksestä. 1 = oikea ja 2 = vasen.
int vaihe = 0;
int left, right;
int etaisyysSeinasta = 0;
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
		itoa(buffer, vaihe, 10);
		LCD_Position(1,0);
		LCD_PrString(buffer);
		
		itoa(buffer, blackLineCounter, 10);
		LCD_Position(0,0);
		LCD_PrString(buffer);		
		
		
		// Eteenpäin ajo vaihe, ajetaan eteenpäin niin pitkään kunnes ollaan 20cm päästä seinästä.
		if( vaihe == 1 )
		{	
			sendTrigPulse(&ultraData);
			
			distanceCM = ultraData * 2;	

			if (distanceCM >= 60)
			{	
				if (lastTurn == 2)
				{
					CheckRight();				
				}				
				if (lastTurn == 1)
				{
					CheckLeft();
				}
				etaisyysSeinasta = ultraData * 2;
				
				ControlServo(SERVO_MIDDLE);
				Delay10msTimes(50);
				if (etaisyysSeinasta < 10)
				{
					MoveForward2(TURN_SPEED, 1.0f, 0.70f);
					
				}
				else if (etaisyysSeinasta > 30)
				{
					MoveForward2(TURN_SPEED, 0.70f, 1.0f);	
					
				}
				else {
					MoveForward(HALF_SPEED);	
				}
			}
			else if (distanceCM < 60 && distanceCM > 35)
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
					Delay10msTimes(42);		//Voi joutua korjaamaan
					Stop();
					lastTurn = 1;
				}
				else 
				{
					//turnlefti
					TurnLeft(TURN_SPEED);
					Delay10msTimes(42);		//Voi joutua korjaamaan
					Stop();
					lastTurn = 2;
				}
				ControlServo(SERVO_MIDDLE_FROM_RIGHT);
				
				Delay(1000);
				vaihe = 1;
		}
		
		//Mustat miehet
		if (blackLineCounter > 0)
			vaihe = 3;
		
		if (vaihe == 3)
			MoveForward(SLOW_SPEED);
		
		if (blackLineCounter >= 5)
		{
			Stop(); 
			vaihe = 4; 
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
	
	//Linefinder START
	
	if ((LineFinder_Data_ADDR & LineFinder_MASK) && (onBlackLine == 0)) {
		onBlackLine = 1;
		blackLineCounter++;
	} else if (!(LineFinder_Data_ADDR & LineFinder_MASK)) { // tänne vaan jos EI olla mustalla viivalla atm
		onBlackLine = 0;
	}
	//LineFinder STOP
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
		ControlServo(SERVO_LEFT);
		Delay10msTimes(250);
		ControlServo(SERVO_MIDDLE_FROM_LEFT);
		Delay10msTimes(250);
		ControlServo(SERVO_RIGHT);
		Delay10msTimes(250);
		ControlServo(SERVO_MIDDLE_FROM_RIGHT);
		Delay10msTimes(250);		
		
		
		
//		TurnRight(TURN_SPEED);
//		Delay10msTimes(75);
//		
//		Stop();
//		Delay10msTimes(250);
//		
//		TurnLeft(TURN_SPEED);
//		Delay10msTimes(75);
//		
//		Stop();
//		Delay10msTimes(250);
		
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
