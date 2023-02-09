#include "driver/gpio.h"

#define BUZZER_GPIO 2

void configure_buzzer(void)
{
    esp_rom_gpio_pad_select_gpio(BUZZER_GPIO);
    gpio_reset_pin(BUZZER_GPIO);
    gpio_set_direction(BUZZER_GPIO, GPIO_MODE_OUTPUT);
}

void change_buzzer_state(int buzzer_state){
    gpio_set_level(BUZZER_GPIO, buzzer_state);
}