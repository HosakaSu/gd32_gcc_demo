/*!
    \file    gpio.h
    \brief   definitions for gd32f105vct6 manualboard, led, keys and COM ports hardware resources

    \version 2021-10-11, V1.0.0, firmware for GD32F10x
*/
#ifndef LED_H
#define LED_H

#ifdef cplusplus
 extern "C" {
#endif

#include "gd32f10x.h"
// #include "gpio.h"

/* exported types */
typedef enum 
{
    LED1 = 0,
    LED2 = 1,
    LED3 = 2,
    LED4 = 3,
    LED5 = 4,
    LED6 = 5,
    LED7 = 6,
    LED8 = 7,
    LED9 = 8,
    LED10 = 9,
    LED11 = 10,
    LED12 = 11,
    LED13 = 12,
    LED14 = 13,
    LED15 = 14,
    LED16 = 15,
} led_typedef_enum;


#define LEDn                             16U


#define LED1_PIN                         GPIO_PIN_15
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCU_GPIOB

#define LED2_PIN                         GPIO_PIN_14
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCU_GPIOB
  
#define LED3_PIN                         GPIO_PIN_11
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCU_GPIOB
  
#define LED4_PIN                         GPIO_PIN_10
#define LED4_GPIO_PORT                   GPIOB
#define LED4_GPIO_CLK                    RCU_GPIOB
  
#define LED5_PIN                         GPIO_PIN_5
#define LED5_GPIO_PORT                   GPIOE
#define LED5_GPIO_CLK                    RCU_GPIOE

#define LED6_PIN                        GPIO_PIN_4
#define LED6_GPIO_PORT                  GPIOE
#define LED6_GPIO_CLK                   RCU_GPIOE

#define LED7_PIN                        GPIO_PIN_4
#define LED7_GPIO_PORT                  GPIOB
#define LED7_GPIO_CLK                   RCU_GPIOB

#define LED8_PIN                        GPIO_PIN_3
#define LED8_GPIO_PORT                  GPIOB
#define LED8_GPIO_CLK                   RCU_GPIOB

#define LED9_PIN                        GPIO_PIN_13
#define LED9_GPIO_PORT                  GPIOB
#define LED9_GPIO_CLK                   RCU_GPIOB

#define LED10_PIN                        GPIO_PIN_12
#define LED10_GPIO_PORT                  GPIOB
#define LED10_GPIO_CLK                   RCU_GPIOB

#define LED11_PIN                        GPIO_PIN_15
#define LED11_GPIO_PORT                  GPIOE
#define LED11_GPIO_CLK                   RCU_GPIOE

#define LED12_PIN                        GPIO_PIN_14
#define LED12_GPIO_PORT                  GPIOE
#define LED12_GPIO_CLK                   RCU_GPIOE

#define LED13_PIN                        GPIO_PIN_3
#define LED13_GPIO_PORT                  GPIOE
#define LED13_GPIO_CLK                   RCU_GPIOE

#define LED14_PIN                        GPIO_PIN_2
#define LED14_GPIO_PORT                  GPIOE
#define LED14_GPIO_CLK                   RCU_GPIOE

#define LED15_PIN                        GPIO_PIN_6
#define LED15_GPIO_PORT                  GPIOD
#define LED15_GPIO_CLK                   RCU_GPIOD

#define LED16_PIN                        GPIO_PIN_7
#define LED16_GPIO_PORT                  GPIOD
#define LED16_GPIO_CLK                   RCU_GPIOD

/* configure led GPIO */
void gpio_led_init(led_typedef_enum lednum);
/* turn on selected led */
void gpio_led_on(led_typedef_enum lednum);
/* turn off selected led */
void gpio_led_off(led_typedef_enum lednum);
/* toggle the selected led */
void gpio_led_toggle(led_typedef_enum lednum);
/* init all the leds */
void gd_led_init(void);
/* turn off all the leds */
void gd_led_alloff(void);
void gd_led_all_on(void);
#endif /* LED_H */