/*
 * PWM.c
 *
 *  Created on: Apr 18, 2021
 *      Author: shoan
 */

#include"PWM.h"
#include "../include.h"

static uint32_t Period;
void Config_PWM(void)
{
    Period = SysCtlClockGet()/20000;
    //Cap clock cho chan F hoat dong
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    //PWM lay clock he thong qua bo chia
    //o day chia 1 (giu nguyen so xung)
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    /* PWM o PF1 la M1PWM5 (Module1 PWM5), PWM Generator2*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    GPIOPinConfigure(GPIO_PF1_M1PWM5);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    //Tao tan so cho PWM
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, Period);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
}

void Process_PWM(void)
{
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, Period*90/100-1);
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
}

