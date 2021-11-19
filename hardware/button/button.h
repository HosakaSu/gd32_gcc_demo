/*!
    \file    button.h
    \brief   definitions for gd32f105vct6 manualboard button ports hardware resources

    \version 2021-10-11, V1.0.0, firmware for GD32F10x
*/
#ifndef BUTTON_H
#define BUTTON_H

#ifdef cplusplus
 extern "C" {
#endif

#include "gd32f10x.h"
#include "led.h"
#define BUTTONn                             4U

#define BUTTON1_PIN                   GPIO_PIN_10
#define BUTTON1_GPIO_PORT             GPIOE
#define BUTTON1_GPIO_CLK              RCU_GPIOE

#define BUTTON2_PIN                   GPIO_PIN_11
#define BUTTON2_GPIO_PORT             GPIOE
#define BUTTON2_GPIO_CLK              RCU_GPIOE

#define BUTTON3_PIN                     GPIO_PIN_12
#define BUTTON3_GPIO_PORT               GPIOE
#define BUTTON3_GPIO_CLK                RCU_GPIOE

#define BUTTON4_PIN                     GPIO_PIN_13
#define BUTTON4_GPIO_PORT               GPIOE
#define BUTTON4_GPIO_CLK                RCU_GPIOE

typedef enum 
{
    button_1 = 0,
    button_2 = 1,
    button_3 = 2,
    button_4 = 3,
} button_typedef_enum;

extern int delay_time;
extern int cycle_turn;
extern int led_all_on;
extern int led_all_toggle;
/* function declarations */
/* init one button gpio */
void gpio_button_init(button_typedef_enum button_num);
/* init all the buttons */
void gd_button_init(void);

void button_scan(void);


#ifdef cplusplus
}
#endif

#endif /* BUTTON_H */
