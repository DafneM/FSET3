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
#define BOARD_LED 2

void check_heartbeat()
{
   while (true)
  {
    int heartbeat = analogRead(HEARTBEAT_SENSOR);
    int board_led_status = 0;
    if(heartbeat > 1000){
      digitalWrite(BOARD_LED, 0);
      board_led_status = 0;
    }
    else {
      digitalWrite(BOARD_LED, 1);
      board_led_status = 1;
    }
    ESP_LOGI(TAG, "Pulso: %.3d ", heartbeat);
    send_heartbeat_telemetry(&heartbeat);
    send_board_led_attribute(&board_led_status);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
