
#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "freertos/semphr.h"

#include "wifi.h"
#include "mqtt.h"

extern SemaphoreHandle_t reconnectionWifiSemaphore;

void light_sleep_task(void *args){

    while(1){
        
        wifi_stop();
        mqtt_stop();
        esp_light_sleep_start();

        printf("acordei\n");

        wifi_start();
        if (xSemaphoreTake(reconnectionWifiSemaphore, portMAX_DELAY)){
            mqtt_start();
        }

        //acorda e volta a fazer o que precisa
    }
}