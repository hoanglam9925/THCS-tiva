/*
 * UART.c
 *
 *  Created on: Apr 18, 2021
 *      Author: shoan
 */

#include "UART.h"
#include "../include.h"


static void UART_ISR(void);
void Config_UART(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_PAR_NONE | UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE);
    UARTIntRegister(UART0_BASE, &UART_ISR);
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}
static void UART_ISR(void)
{
    UARTIntClear(UART0_BASE, UARTIntStatus(UART0_BASE, true));
    int32_t k;
    k = UARTCharGet(UART0_BASE);
}

