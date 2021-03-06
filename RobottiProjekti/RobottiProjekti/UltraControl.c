#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"
#include<stdio.h>
#include<stdlib.h>
#include "delay.h"

//----------------------------------------------------
  //PORT0_6 TRIGGER
  //PORT0_7 ECHO
//

//PORT0_4 SERVO PWM

float distanceToCm = 0.033f;

//Init PGA AND ADC
void InitUAServo(void)
{

}


//Return distance from Ultrasonic sensor in centimeters 
int getDataUA(void)
{
	/*if(ADCINC_fIsDataAvailable() != 0)
	{		
		return (int)(ADCINC_iGetData() * distanceToCm);
	}
	else 
		return 0;*/
	return 0;
}

//Sends Trigger pulse
void ControlTrigger(int *time)
{		
	//Wait 60ms and send pulse again
	if (*time >= 80)
	{
		*time = 0;
	}
	
	//Send Trigger Pulse every 1ms 
	if (*time <= 1)
	{
		UATrig_Data_ADDR |= UATrig_MASK;
	}
	else 	
		UATrig_Data_ADDR &= ~UATrig_MASK;
	
}

void sendTrigPulse(int *ultraData)
{	
	*ultraData = 0;
	UATrig_Data_ADDR |= UATrig_MASK;	
	Delay50u();
	UATrig_Data_ADDR &= ~UATrig_MASK;
	Delay10msTimes(7);
}	

