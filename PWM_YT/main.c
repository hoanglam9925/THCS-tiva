

/**
 * main.c
 */
#include "include.h"

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    Config_PWM();
    Config_UART();
	while(1)
	{
	    Process_PWM();

	}
}
