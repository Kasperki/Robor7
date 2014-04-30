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
#include <math.h> 
#include "string.h"

//Omat header filet
#include "MotorControl.h"
#include "UltraControl.h"
//#include "GyroControl.h"

#pragma interrupt_handler PinInterrupt

void Delay(int);
void TestLoop(void);

//Kellot
volatile int timeT = 0;
int timeUltra = 0,timeUltraRead = 0;
volatile unsigned long int milliT = 0;

volatile int distanceCM = 0;
char buffer[10];



//Main Method
void main(void)
{
	//Init**************************
	//UART
	char * strPtr;                        // Parameter pointer
	char uartBuf;
	char x_temp[5];
	char y_temp[5];
	char x[5];
	char y[5];
	float axis_x;
	float axis_y;
    float xAbs,yAbs;
	int apu = 0;

    int Status;
    char* buf;
	
	UART_1_CmdReset();                      // Initialize receiver/cmd // buffer
    //UART_1_IntCntl(UART_1_ENABLE_RX_INT);     // Enable RX interrupts
	UART_1_Start(UART_1_PARITY_NONE); 
	
	//Enables Global Interrupts
	M8C_EnableGInt; 
	M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO);	//VITTU
	
	//Start LCD
	LCD_Start();
	
	//Start Motor PWMs
	InitPWM();
	
	//Init Servo
	InitUAServo();
		
	Delay10msTimes(100);
	
	//Testink
	//TestLoop();

	//MainLoop**********
	//***********************
	while(1)
	{
		//TATTI OHJAUS
		int j = 0; int i = 0;
		for(j = 0; j < 9; j++)
		{
			if (UART_1_cGetChar() == 'A')
			{
				break;
			}
		}
			
		for(i = 0; i < 8; i++)
			strPtr[i] = UART_1_cGetChar();
		
		//Parse X
		for(i = 0; i < 4; i++)
		{
			x_temp[i] = strPtr[i];					
		}			
		//Parse Y
		for(i = 4; i < 8; i++)
		{
			y_temp[i-4] = strPtr[i];	
		}
		
		//1083 -> 0.83f
		if (x_temp[0] == '0')
		{
			x[0] = '-';
			x[1] = x_temp[1];
			x[2] = '.';
			x[3] = x_temp[2];
			x[4] = x_temp[3];
			x[5] = '\0';
			axis_x = (float)atof(x);
		} else if (x_temp[0] == '1')
		{
			x[0] = x_temp[1];
			x[1] = '.';
			x[2] = x_temp[2];
			x[3] = x_temp[3];
			x[4] = '\0';
			axis_x = (float)atof(x);
		}
		//0023 -> -0.23f
		if (y_temp[0] == '0')
		{
			y[0] = '-';
			y[1] = y_temp[1];
			y[2] = '.';
			y[3] = y_temp[2];
			y[4] = y_temp[3];
			y[5] = '\0';
			axis_y = (float)atof(y);
		} else if (y_temp[0] == '1')
		{
			y[0] = y_temp[1];
			y[1] = '.';
			y[2] = y_temp[2];
			y[3] = y_temp[3];
			y[4] = '\0';
			axis_y = (float)atof(y);
		}
		
		if(axis_x < 0) xAbs = axis_x * -1.0f;
		else xAbs = axis_x;
		//xAbs = std::abs(axis_x);
		
		if(axis_y < 0) yAbs = axis_y * -1.0f;
		else yAbs = axis_y;
		//yAbs = std::abs(axis_y);
		
		if(xAbs > yAbs) //Käännytään
		{	
			//if(axis_x > 0.0f)
				TurnRight((int)(FULL_SPEED * xAbs));
			//else			
				//TurnLeft((int)(FULL_SPEED * xAbs));
		
			apu = 1;
		}
		else //Suoraan -> Taakse
		{
			if(axis_y > 0.0f)
			{
				MoveForward2((int)(FULL_SPEED * yAbs),1,1);
				//if(axis_x > 0)
					//MoveForward2((int)(FULL_SPEED * yAbs),1,(int)(FULL_SPEED *  (1 - xAbs)));
				//else
					//MoveForward2((int)(FULL_SPEED * yAbs),(int)(FULL_SPEED *  (1 - xAbs)),1);
			}
			else
			{ 
				MoveBackward((int)(FULL_SPEED * yAbs));
			}
		
			apu = 2;
		}	
		
		
		LCD_Position(0,0);
		//LCD_PrHexByte(uartBuf);
		LCD_PrString(strPtr);
		
		//itoa(buffer,apu,10);
		//LCD_Position(1,1);
		//LCD_PrCString("     ");
		//LCD_PrString(buffer);
		
	

  		
  		buffer = ftoa(axis_x,10);
   		LCD_Position(1,1);
   		LCD_PrString(buffer);
	}
}


// Pin interrupt
void PinInterrupt(void){}


//For Testing
void TestLoop(void)
{
	while(1)
	{	
		/*ControlServo(SERVO_LEFT);
		Delay10msTimes(250);
		ControlServo(SERVO_MIDDLE_FROM_LEFT);
		Delay10msTimes(250);
		ControlServo(SERVO_RIGHT);
		Delay10msTimes(250);
		ControlServo(SERVO_MIDDLE_FROM_RIGHT);
		Delay10msTimes(250);		
			
		itoa(buffer,distanceCM,10);
		LCD_Position(0,0);
		LCD_PrCString("     ");
		LCD_Position(0,0);
		LCD_PrString(buffer);
		*/		
		
				//EZ
//		uartBuf = UART_1_cGetChar();
//		
//		if (uartBuf == 0x31)
//		{
//			MoveForward(FULL_SPEED);
//		}
//		if (uartBuf == 0x32)
//		{
//			TurnRight(FULL_SPEED);
//		}
//		if (uartBuf == 0x33)
//		{
//			MoveBackward(FULL_SPEED);
//		}
//		if (uartBuf == 0x34)
//		{
//			TurnLeft(FULL_SPEED);
//		}
//		if(uartBuf == 0x30)
//			Stop();
		
				
//		LCD_Position(1,0);
//		//LCD_PrHexByte(uartBuf);
//		LCD_PrString(y);
	}
}

////OMA Delay function 
void Delay(int delay)
{
	unsigned long int timme = milliT + delay;
	while (milliT < timme){}
}
