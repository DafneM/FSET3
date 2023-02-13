#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "json_treatment.h"
#include "mqtt.h"

#include "gpio_setup.h"
#include "adc_module.h"

#define TAG "HEARTBEAT"
#define HEARTBEAT_SENSOR ADC_CHANNEL_0
#define BOARD_LED 2

void check_heartbeat()
{
  vTaskDelay(2000 / portTICK_PERIOD_MS);
   while (true)
  {
    int heartbeat = analogRead(HEARTBEAT_SENSOR);
    int board_led_status = 0;
    if(heartbeat > 800){
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

void set_board_led_state(int value, int topic_id){
    // TODO - escrever na NVS
    printf("VALUE = %d\n", value );

    if(value <= 0){
      digitalWrite(BOARD_LED, 0);
    } else {
      digitalWrite(BOARD_LED, 1);
    }

    char resp_topic[50];
    char resp_msg[50];
	  snprintf(resp_topic, 49, "v1/devices/me/rpc/response/%d", topic_id);
    snprintf(resp_msg, 49, "{\"value\": %d}", value);
	  mqtt_envia_mensagem(resp_topic, resp_msg);
}
