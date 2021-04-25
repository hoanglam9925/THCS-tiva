/*
 * ADC.h
 *
 *  Created on: Apr 13, 2021
 *      Author: shoan
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

static void ADC_ISR(void);
void Config_ADC(void);
void Config_ADC_HardwareAverage(void);
static void ADC_ISR_HardwareAverage(void);


#endif /* ADC_ADC_H_ */
