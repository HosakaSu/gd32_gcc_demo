#include "led.h"

static uint32_t GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT,
                                   LED4_GPIO_PORT, LED5_GPIO_PORT, LED6_GPIO_PORT,
                                   LED7_GPIO_PORT, LED8_GPIO_PORT, LED9_GPIO_PORT,
                                   LED10_GPIO_PORT, LED11_GPIO_PORT, LED12_GPIO_PORT,
                                   LED13_GPIO_PORT, LED14_GPIO_PORT, LED15_GPIO_PORT,
                                   LED16_GPIO_PORT};

static uint32_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN,
                                  LED7_PIN, LED8_PIN, LED9_PIN, LED10_PIN, LED11_PIN, LED12_PIN,
                                  LED13_PIN, LED14_PIN, LED15_PIN, LED16_PIN};

static rcu_periph_enum GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK, 
                                         LED4_GPIO_CLK, LED5_GPIO_CLK, LED6_GPIO_CLK,
                                         LED7_GPIO_CLK, LED8_GPIO_CLK, LED9_GPIO_CLK,
                                         LED10_GPIO_CLK, LED11_GPIO_CLK, LED12_GPIO_CLK,
                                         LED13_GPIO_CLK, LED14_GPIO_CLK, LED15_GPIO_CLK,
                                         LED16_GPIO_CLK};

/*!
    \brief      configure led GPIO
    \param[in]  lednum: specify the led to be configured
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/
void gpio_led_init(led_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */ 
    gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[lednum]);

    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn on selected led
    \param[in]  lednum: specify the led to be turned on
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/
void gpio_led_on(led_typedef_enum lednum)
{
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn off selected led
    \param[in]  lednum: specify the led to be turned off
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/
void gpio_led_off(led_typedef_enum lednum)
{
    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      toggle selected led
    \param[in]  lednum: specify the led to be toggled
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/
void gpio_led_toggle(led_typedef_enum lednum)
{
    gpio_bit_write(GPIO_PORT[lednum], GPIO_PIN[lednum], 
        (bit_status)(1-gpio_input_bit_get(GPIO_PORT[lednum], GPIO_PIN[lednum])));
}

void gd_led_init(void)
{
	for(int i = 0; i < 16; i ++){
		gpio_led_init(i);
	}
}

void gd_led_alloff(void)
{
	for(int i = 0; i < 16; i ++){
		gpio_led_off(i);
	}
}

void gd_led_all_on(void)
{
  for(int i = 0; i < 16; i ++){
    gpio_led_on(i);
  }
}
