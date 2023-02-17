#include "LED.h"

uint8_t current_value;
uint8_t current_rgb_value;

void led_init()
{
    current_value = 0b11;
    current_rgb_value = 0b111;
    led_write_led(0b11, 0b11);
    led_write_rgb(0b111);
}

void led_start()
{
    led_write_led(0b11, 0b00);
    led_write_rgb(0b000);
}

void led_stop()
{
    led_write_led(0b11, 0b00);
    led_write_rgb(0b100);
}

uint8_t led_read_current_value()
{
    return current_value;
}

uint8_t led_read_current_rgb_value()
{
    return current_rgb_value;
}

void led_write_led1(uint8_t value_)
{
    uint8_t led1_value, led2_value;
    led1_value = value_ << 1;
    led2_value = current_value & 0b01;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, value_ ? GPIO_PIN_RESET : GPIO_PIN_SET);
    current_value = led1_value | led2_value;
}

void led_write_led2(uint8_t value_)
{
    uint8_t led1_value, led2_value;
    led1_value = current_value & 0b10;
    led2_value = value_ << 0;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, value_ ? GPIO_PIN_RESET : GPIO_PIN_SET);
    current_value = led1_value | led2_value;
}

void led_write_rgb(uint8_t rgb_)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, (rgb_ & 0b100) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// LED_R ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, (rgb_ & 0b010) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// LED_G ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, (rgb_ & 0b001) ? GPIO_PIN_RESET : GPIO_PIN_SET);// LED_B ON
    current_rgb_value = rgb_ & 0b0111;
}

void led_write_led(uint8_t mask_, uint8_t value_)
{
    if(mask_ & 0b10)
    {
        led_write_led1((0b10 & value_) >> 1);
    }
    if(mask_ & 0b01)
    {
        led_write_led2((0b01 & value_) >> 0);
    }
}
