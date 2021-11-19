#include "uart.h"

void usart0_init(void){
    /* enable uart0 clock */
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_AF);

    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    gpio_pin_remap_config(GPIO_USART0_REMAP, ENABLE);

    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_bit_reset(GPIOA, GPIO_PIN_8);


	usart_deinit(USART0);
	usart_baudrate_set(USART0, 9600U);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	usart_enable(USART0);

    // usart_deinit(USART0);
    // usart_baudrate_set(USART0, 9600U);
    // usart_word_length_set(USART0, USART_WL_8BIT);
    // usart_stop_bit_set(USART0, USART_STB_1BIT);
    // usart_parity_config(USART0, USART_PM_NONE);
    // usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    // usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    // usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    // usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    // usart_enable(USART0);
}

void usart0_send_data_bit(uint8_t buf)
{
    gpio_bit_set(GPIOA, GPIO_PIN_8);
    usart_data_transmit(USART0, (uint8_t)buf);
        while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    gpio_bit_reset(GPIOA, GPIO_PIN_8);
}

void usart0_send_buf(uint8_t *sendbuf, uint8_t bufcnt)
{
    uint8_t i;
    for(i = 0; i < bufcnt; i++){
        usart0_send_data_bit(sendbuf[i]);
    }
}
