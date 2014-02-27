#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"

//----------------------------------------------------
  //PORT0_6 TRIGGER
  //PORT0_7 ECHO
//


//Init PGA AND ADC
void InitUA()
{
	PGA_SetGain(PGA_G1_00);
	PGA_Start(PGA_MEDPOWER);
	
	ADCINC_Start(ADCINC_HIGHPOWER);
	ADCINC_GetSamples(0);
}


//Return data from ADC
int getDataUA()
{
	if(ADCINC_fIsDataAvailable() != 0)
	{
		return ADCINC_iGetData();
	}
	else 
		return 0;
}

void ControlTrigger(int freq)
{

}