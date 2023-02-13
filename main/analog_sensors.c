#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define ESP_CONFIG_NUMBER CONFIG_ESP_CONFIG_NUMBER

#define FLAME_SENSOR ADC_CHANNEL_0
#define PHOTO_RESISTOR ADC_CHANNEL_3
#define HEARTBEAT_SENSOR ADC_CHANNEL_0
#define BOARD_LED 2
#define SHOCK_SENSOR 16

void setup_analog_sensors()
{
  adc_init(ADC_UNIT_1);
  
  if (ESP_CONFIG_NUMBER == 1) {
    pinMode(PHOTO_RESISTOR, GPIO_ANALOG);
    pinMode(HEARTBEAT_SENSOR, GPIO_ANALOG);
    pinMode(BOARD_LED, GPIO_OUTPUT);
  }
  
  else if (ESP_CONFIG_NUMBER == 2) {
    pinMode(FLAME_SENSOR, GPIO_ANALOG);
    pinMode(SHOCK_SENSOR, GPIO_INPUT);
  }
}