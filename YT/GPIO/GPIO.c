/*
 * GPIO.c
 *
 *  Created on: Apr 12, 2021
 *      Author: shoan
 */
#include "../include.h"
#include "GPIO.h"

static uint32_t status = LED_RED;
static void SWITCH_ISR(void);
void Config_LED(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(LED_PORT, LED_RED);
    GPIOPinWrite(LED_PORT, LED_RED, 0);
    GPIOPinTypeGPIOOutput(LED_PORT, LED_BLUE);
    GPIOPinWrite(LED_PORT, LED_BLUE, 0);
}

void Blink_LED(void)
{
    static uint8_t i=0;
    if(i == 0)
        i = status;
    else
        i = 0;
    GPIOPinWrite(LED_PORT, LED_RED | LED_BLUE, i);
    //SysCtlDelay(SysCtlClockGet()/3); //delay 1s
}

void Config_SW(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(SW_PORT, SW);
    //Strength: cac muc dong dien
    //WPU: Pull up
    GPIOPadConfigSet(SW_PORT, SW, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
    //ham khai bao su kien ngat (PORT, dia chi ham ngat)
    GPIOIntRegister(SW_PORT,&SWITCH_ISR);
    //Cho phep ngat o cap PIN(PORT, chan xay ra ngat (co them INT))
    GPIOIntEnable(SW_PORT, GPIO_INT_PIN_4);
    //Cho phep ngat o PORT
    IntEnable(INT_GPIOF);
    //Cho phep ngat o he thong
    IntMasterEnable();
}

static void SWITCH_ISR(void)
{
    //Kiem tra ngat neu roi thi xoa ngat de thuc hien vong sau
    GPIOIntClear(GPIO_PORTF_BASE, GPIOIntStatus(GPIO_PORTF_BASE, true));
    if(status == LED_RED)
    {
        status = LED_BLUE;
    }
    else
    {
        status = LED_RED;
    }
}

