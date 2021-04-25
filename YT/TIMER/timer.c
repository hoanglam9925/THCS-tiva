/*
 * timer.c
 *
 *  Created on: Apr 13, 2021
 *      Author: shoan
 */

#include "../include.h"
#include "timer.h"

void Config_Timer(void)
{
    //Cho phep Timer0 hoat dong
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    //Su dung timer tu lap lai (period) va nguyen cay khong chia ra
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    //do su dung full width nen khai bao timer A
    //1s
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()-1);

    TimerIntRegister(TIMER0_BASE, TIMER_A, &Timer_ISR);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

static void Timer_ISR(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    Blink_LED();
}
