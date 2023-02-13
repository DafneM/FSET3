#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "json_treatment.h"

#include "gpio_setup.h"
#include "adc_module.h"
#include "gpio.h"

#define TAG "MAGNETIC"
#define MAGNETIC 22

void check_magnetic()
{
  int buzzer_status = 0;
  pinMode(22, GPIO_INPUT);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
   while (true)
  {
    int magnetic = digitalRead(MAGNETIC);
    if(magnetic == 1){
      change_buzzer_state(1);
      buzzer_status = 1;
      send_board_buzzer_attribute(&buzzer_status);
    }
    else {
      change_buzzer_state(0);
      buzzer_status = 0;
      send_board_buzzer_attribute(&buzzer_status);
    }
    ESP_LOGI(TAG, "Pulso: %.3d ", magnetic);
    send_board_magnetic_attribute(&magnetic);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
