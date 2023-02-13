#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "json_treatment.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define TAG "MAGNETIC"
#define MAGNETIC 22

void check_magnetic()
{
  pinMode(22, GPIO_INPUT);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
   while (true)
  {
    int magnetic = digitalRead(MAGNETIC);
    int board_led_status = 0;
    if(magnetic == 1){
      board_led_status = 1;
    }
    else {
      board_led_status = 0;
    }
    ESP_LOGI(TAG, "Pulso: %.3d ", magnetic);
    send_board_magnetic_attribute(&magnetic);
    send_board_led_attribute(&board_led_status);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
