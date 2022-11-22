#define __LED_H__ // 今は使われてないライブラリ

#ifndef __LED_H__
#define __LED_H__

/* set led1 value */
void write_led1(uint8_t value_);
/* set led2 value */
void write_led2(uint8_t value_);
/* set full color led value */
void write_rgb(uint8_t rgb_);
/* set led1 and led2 value */
void write_led(uint8_t mask_, uint8_t value_);

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

