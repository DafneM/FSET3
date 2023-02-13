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
#define LED_FLASH 18


void check_flame() {
   vTaskDelay(2000 / portTICK_PERIOD_MS);
   int flame;
   int fireAlert = false;
   while (true) {
    flame = analogRead(FLAME_MOD);
    ESP_LOGI(TAG, "Flame: %d", flame);
    
    if (flame < 300) {
      digitalWrite(LED_FLASH, 1);
      fireAlert = true;
      send_flame_alert(&fireAlert);
    }
    else {
      fireAlert = false;
      send_flame_alert(&fireAlert);
    }
    
    flame = flame/4;
    send_flame_telemetry(&flame);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_FLASH, 0);
  }
}