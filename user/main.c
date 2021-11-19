/*!
    \file    main.c
    \brief   led spark with systick, USART print and key example

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "main.h"

/* configure the TIMER peripheral */
void timer_config(void);
/* configure the TIMER1 interrupt */
void nvic_config(void);
/*!
    \brief      toggle the led every 50ms
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_spark(void)
{
    static __IO uint32_t timingdelaylocal = 0U;

    if (timingdelaylocal)
    {

        if (timingdelaylocal < 50U)
        {
            gpio_led_toggle(LED15);
        }
        else
        {
            gpio_led_off(LED15);
        }
        timingdelaylocal--;
    }
    else
    {
        timingdelaylocal = 100U;
    }
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
    uint8_t button_code;
    /* configure systick */
    systick_config();
    /* initilize the LEDs and buttons */

    gd_led_init();
    gd_led_alloff();
    gd_button_init();
    while (1)
    {
        if(led_all_toggle){
            if(cycle_turn == 1){
                gpio_led_toggle(LED1);
                delay_1ms(delay_time);
                gpio_led_toggle(LED2);
                delay_1ms(delay_time);
                gpio_led_toggle(LED9);
                delay_1ms(delay_time);
                gpio_led_toggle(LED10);
                delay_1ms(delay_time);
                gpio_led_toggle(LED3);
                delay_1ms(delay_time);
                gpio_led_toggle(LED4);
                delay_1ms(delay_time);
                gpio_led_toggle(LED11);
                delay_1ms(delay_time);
                gpio_led_toggle(LED12);
                delay_1ms(delay_time);
                gpio_led_toggle(LED5);
                delay_1ms(delay_time);
                gpio_led_toggle(LED6);
                delay_1ms(delay_time);
                gpio_led_toggle(LED13);
                delay_1ms(delay_time);
                gpio_led_toggle(LED14);
                delay_1ms(delay_time);
                gpio_led_toggle(LED7);
                delay_1ms(delay_time);
                gpio_led_toggle(LED8);
                delay_1ms(delay_time);
                gpio_led_toggle(LED16);
                delay_1ms(delay_time);
                gpio_led_toggle(LED15);
                delay_1ms(delay_time);
            }
            else{
                gpio_led_toggle(LED15);
                delay_1ms(delay_time);
                gpio_led_toggle(LED16);
                delay_1ms(delay_time);
                gpio_led_toggle(LED8);
                delay_1ms(delay_time);
                gpio_led_toggle(LED7);
                delay_1ms(delay_time);
                gpio_led_toggle(LED14);
                delay_1ms(delay_time);
                gpio_led_toggle(LED13);
                delay_1ms(delay_time);
                gpio_led_toggle(LED6);
                delay_1ms(delay_time);
                gpio_led_toggle(LED5);
                delay_1ms(delay_time);
                gpio_led_toggle(LED12);
                delay_1ms(delay_time);
                gpio_led_toggle(LED11);
                delay_1ms(delay_time);
                gpio_led_toggle(LED4);
                delay_1ms(delay_time);
                gpio_led_toggle(LED3);
                delay_1ms(delay_time);
                gpio_led_toggle(LED10);
                delay_1ms(delay_time);
                gpio_led_toggle(LED9);
                delay_1ms(delay_time);
                gpio_led_toggle(LED2);
                delay_1ms(delay_time);
                gpio_led_toggle(LED1);
                delay_1ms(delay_time);          
            }
        }   
        else{
                if(led_all_on == 1){
                    gd_led_all_on();
                }
                else{
                    gd_led_alloff();
                }
        }
    }
}

/**
    \brief      configure the TIMER1 interrupt
    \param[in]  none
    \param[out] none
    \retval     none
  */
void nvic_config(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    nvic_irq_enable(TIMER1_IRQn, 1, 1);
}

/**
    \brief      configure the TIMER peripheral
    \param[in]  none
    \param[out] none
    \retval     none
  */
void timer_config(void)
{
    /* ----------------------------------------------------------------------------
    TIMER1 Configuration: 
    TIMER1CLK = SystemCoreClock/3600 = 20KHz.
    TIMER1 configuration is timing mode, and the timing is 0.2s(400/20000 = 0.02s).
    CH0 update rate = TIMER1 counter clock/CH0CV = 20000/400 = 50Hz.
    ---------------------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);

    timer_deinit(TIMER1);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER1 configuration */
    timer_initpara.prescaler = 3599;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 400;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_CMTG);
    timer_init(TIMER1, &timer_initpara);

    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* CH0,CH1 and CH2 configuration in OC timing mode */
    timer_ocinitpara.outputstate = TIMER_CCX_ENABLE;
    timer_ocinitpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER1, TIMER_CH_0, &timer_ocinitpara);

    /* CH0 configuration in OC timing mode */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, 2000);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_0, TIMER_OC_MODE_TIMING);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

    timer_interrupt_enable(TIMER1, TIMER_INT_CH0);
    timer_enable(TIMER1);
}
