#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "json_treatment.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define TAG "HEARTBEAT"
#define HEARTBEAT_SENSOR ADC_CHANNEL_0

void check_heartbeat()
{
   while (true)
  {
    int heartbeat = analogRead(HEARTBEAT_SENSOR);
    ESP_LOGI(TAG, "Pulso: %.3d ", heartbeat);
    send_heartbeat_telemetry(&heartbeat);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}