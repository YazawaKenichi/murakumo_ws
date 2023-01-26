#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx_hal.h"

void led_init();
void led_start();
void led_stop();
uint8_t led_read_current_value();
uint8_t led_read_current_rgb_value();
void led_write_led1(uint8_t value_);
void led_write_led2(uint8_t value_);
void led_write_rgb(uint8_t rgb_);
void led_write_led(uint8_t, uint8_t);

/* usuage */
/*
    RGB rgb;
    main()
    {
        ...
        write_rgb(0b101);    // Magenda
        ...
        write_led(0b01, 0b01);  // LED2 Set
        ...
        write_led(0b10, 0b00);  // LED1 Reset
        ...
        write_led(0b01, 0b00);  // LED2 Reset
    }
*/
#endif
