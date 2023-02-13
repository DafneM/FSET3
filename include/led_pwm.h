
#ifndef LED_PWM_H
#define LED_PWM_H

static void configure_led_pwm(gpio_num_t pin);
void led_control(int brightness);

#endif