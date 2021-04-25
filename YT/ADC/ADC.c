/*
 * ADC.c
 *
 *  Created on: Apr 13, 2021
 *      Author: shoan
 */

#include "ADC.h"
#include "../include.h"

void Config_ADC(void)
{
    //Kich hoat chuc nang ADC0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    //Do kenh 0 cua ADC la PE3 nen cap xung cho PORTE hoat dong
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    //Config chan PE3 lam ADC
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    //(ADC nao, chon SS, xung Trigger lay mau, Priority)
    //SS0: 8 mau, SS1, SS2: 4 mau, SS3: 1 mau
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    //Lenh tren quet 4 mau thi mau 1 lay o chan nao, mau 2 lay chan nao...
    //(ADC nao, SS nao, mau thu may, kenh nao)
    //channel 0 la PE3 nen tham so cuoi de CH0

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH0);
    //EBD de ket thuc som qua trinh lay mau, o tren lay 4 mau nhung thich lay 3 mau roi dung
    //IE khi lay xong mau thu 3 thi cho phep ngat
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0 | ADC_CTL_END | ADC_CTL_IE);
    //Setup xong phai Enable no moi chay (ADC nao, SS may)
    ADCSequenceEnable(ADC0_BASE, 1);
    //Dang ky ngat
    ADCIntRegister(ADC0_BASE, 1, &ADC_ISR);
    //Cho phep ngat ADC
    ADCIntEnable(ADC0_BASE, 1);
}
static void ADC_ISR(void)
{
    ADCIntClear(ADC0_BASE, 1);
    uint32_t DATA[3];
    //lay data trong bo nho quet ve bien
    ADCSequenceDataGet(ADC0_BASE, 1, (uint32_t *)DATA);
    //Khai bao o ROM, khong bi mat khi mat nguon
    volatile float Voltage;
    //Voltage = (float)((DATA[2] + DATA[1] + DATA[0])/3)*5/4096;
    Voltage = DATA[2];
}
//Lay trung binh cua mau
void Config_ADC_HardwareAverage(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    //64 mau lay trung binh
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    //Do no tu tinh trung binh roi nen chi lay 1 step
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0 | ADC_CTL_END | ADC_CTL_IE);
    ADCSequenceEnable(ADC0_BASE, 1);

    ADCIntRegister(ADC0_BASE, 1, &ADC_ISR_HardwareAverage);
    ADCIntEnable(ADC0_BASE, 1);
}
static void ADC_ISR_HardwareAverage(void)
{
    ADCIntClear(ADC0_BASE, 1);
    uint32_t DATA[1];
    ADCSequenceDataGet(ADC0_BASE, 1, (uint32_t *)DATA);
    volatile float Voltage;
    Voltage = (float)(DATA[0]*3.3/4096);
}
