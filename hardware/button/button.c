#include "button.h"

static uint32_t BUTTON_PORT[BUTTONn] = {BUTTON1_GPIO_PORT, BUTTON2_GPIO_PORT, BUTTON3_GPIO_PORT, BUTTON4_GPIO_PORT};
static uint32_t BUTTON_PIN[BUTTONn] = {BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN, BUTTON4_PIN};
static rcu_periph_enum BUTTON_CLK[BUTTONn] = {BUTTON1_GPIO_CLK, BUTTON2_GPIO_CLK, BUTTON3_GPIO_CLK, BUTTON4_GPIO_CLK};

int delay_time = 0;
int cycle_turn = 0;
int led_all_on = 0;
int led_all_toggle = 0;

/*!
	\brief      configure button
	\param[in]  key_num: specify the button to be configured
	\param[out] none
	\retval     none
*/
void gpio_button_init(button_typedef_enum button_num)
{
	/* enable the key clock */
	rcu_periph_clock_enable(BUTTON_CLK[button_num]);
	rcu_periph_clock_enable(RCU_AF);

	/* configure button pin as input */
	gpio_init(BUTTON_PORT[button_num], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, BUTTON_PIN[button_num]);
}


/*!
	\brief      return the selected button state
	\param[in]  key: specify the button to be checked
	\param[out] none
	\retval     the button's GPIO pin value
*/
uint8_t gpio_button_state_get(button_typedef_enum button)
{
	if (gpio_input_bit_get(BUTTON_PORT[button], BUTTON_PIN[button]) == 0)
		return 1;
	else
		return 0;
}

/* configure all the buttons */
void gd_button_init(void)
{
	for (int i = 0; i < BUTTONn; i++)
	{
		gpio_button_init(i);
	}
}


void button_scan(void)
{
	uint8_t button1_state, button2_state, button3_state, button4_state;
	button1_state = gpio_button_state_get(button_1);
	button2_state = gpio_button_state_get(button_2);
	button3_state = gpio_button_state_get(button_3);
	button4_state = gpio_button_state_get(button_4);
	if(button1_state == 1){
		// gpio_led_off(LED1);
		delay_time = 100;
	}
	else{
		// gpio_led_on(LED1);
		delay_time = 500;
	}
	if(button2_state == 1){
		cycle_turn = 1;
		// gpio_led_off(LED2);
	}
	else{
		cycle_turn = 0;
		// gpio_led_on(LED2);
	}
	if(button3_state == 1){
		led_all_on = 1;
		// gpio_led_off(LED3);
	}
	else{
		led_all_on = 0;
		// gpio_led_on(LED3);
	}
	if(button4_state == 1){
		led_all_toggle = 1;
		// gpio_led_off(LED4);
	}
	else{
		led_all_toggle = 0;
		// gpio_led_on(LED4);
	}
}
