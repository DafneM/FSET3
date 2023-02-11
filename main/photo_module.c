#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "json_treatment.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define TAG "PHOTO"
#define PHOTO_RESISTOR ADC_CHANNEL_3


void check_luminosity()
{
   while (true)
  {
    int luminosity = analogRead(PHOTO_RESISTOR);
    int light = 0;
    if(luminosity >= 200){
      light = 1;
    }
    ESP_LOGI(TAG, "Luminosidade: %.3d Estado da luz: %d", luminosity, light);
    send_photo_telemetry(&luminosity, &light);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
