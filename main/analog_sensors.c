#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define PHOTO_RESISTOR ADC_CHANNEL_3
#define HEARTBEAT_SENSOR ADC_CHANNEL_0

void setup_analog_sensors()
{
  adc_init(ADC_UNIT_1);
  pinMode(PHOTO_RESISTOR, GPIO_ANALOG);
  pinMode(HEARTBEAT_SENSOR, GPIO_ANALOG);
}