#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "json_treatment.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define TAG "FLAME"
#define FLAME_MOD ADC_CHANNEL_0


void check_flame()
{
   vTaskDelay(2000 / portTICK_PERIOD_MS);
   while (true)
  {
    int flame = analogRead(FLAME_MOD);
    ESP_LOGI(TAG, "Flame: %d", flame);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}