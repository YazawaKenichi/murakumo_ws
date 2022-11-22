#include "LED.h"

#ifndef __LED_H__

void write_led1(uint8_t value_)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, value_);
}

void write_led2(uint8_t value_)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, value_);
}

void write_rgb(uint8_t rgb_)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, (rgb_ & 0b100) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// LED_R ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, (rgb_ & 0b010) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// LED_G ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, (rgb_ & 0b001) ? GPIO_PIN_RESET : GPIO_PIN_SET);// LED_B ON
}

void write_led(uint8_t mask_, uint8_t value_)
{
    if(mask_ & 0b01)
    {
        write_led1(0b01 & value_ >> 0);
    }
    if(mask_ & 0b10)
    {
        write_led2(0b10 & value_ >> 1);
    }
}

#endif
