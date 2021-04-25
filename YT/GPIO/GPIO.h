/*
 * GPIO.h
 *
 *  Created on: Apr 12, 2021
 *      Author: shoan
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#define LED_PORT    GPIO_PORTF_BASE
#define LED_RED     GPIO_PIN_1 //LED do onboard
#define LED_BLUE    GPIO_PIN_2
#define SW_PORT     GPIO_PORTF_BASE
#define SW          GPIO_PIN_4

void Blink_LED(void);
void Config_LED(void);

void Config_SW(void);

#endif /* GPIO_GPIO_H_ */
