#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define TAG "PHOTO"
#define PHOTO_RESISTOR ADC_CHANNEL_3


void check_luminosity()
{
   while (true)
  {
    int luminosity = analogRead(PHOTO_RESISTOR);
    luminosity = luminosity - 2048;
    ESP_LOGI(TAG, "Luminosidade: %.3d ", luminosity);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
