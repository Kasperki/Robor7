#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"
#include<stdio.h>
#include<stdlib.h>

//----------------------------------------------------
  //PORT0_6 TRIGGER
  //PORT0_7 ECHO
//
float distanceToCm = 0.033f;

//Init PGA AND ADC
void InitUA()
{
	PGA_SetGain(PGA_G1_00);
	PGA_Start(PGA_MEDPOWER);
	
	ADCINC_Start(ADCINC_HIGHPOWER);
	ADCINC_GetSamples(0);
}


//Return distance from Ultrasonic sensor in centimeters 
int getDataUA()
{
	if(ADCINC_fIsDataAvailable() != 0)
	{		
		return (int)(ADCINC_iGetData() * distanceToCm);
	}
	else 
		return 0;
}

//Sends Trigger pulse
void ControlTrigger(int *time)
{
	//Send Trigger Pulse every 10ms 
	if (*time <= 1)
	{
		UATrig_Data_ADDR |= UATrig_MASK;
	}
	else 	
		UATrig_Data_ADDR &= 0x00;
	
	//Wait 60ms and send pulse again
	if (*time >= 6)
	{
		*time = 0;
	}
}

//Control PWM to move sensor