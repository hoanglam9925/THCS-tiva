

/**
 * main.c
 */
#include "include.h"

int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	Config_LED();
	Config_SW();
	Config_ADC();
	Config_Timer();
	IntMasterEnable();
	while(1)
	{
	    //Blink_LED();
	    //ADCProcessorTrigger(ADC0_BASE, 1);
	}
}
