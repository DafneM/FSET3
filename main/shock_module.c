#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#include "wifi.h"
#include "mqtt.h"
#include "json_treatment.h"

#define SHOCK_SENSOR 16

void readShockSensor(){
    int shockStatus;
    while (true) {
        shockStatus = gpio_get_level(SHOCK_SENSOR);
        printf("Status Sensor Impacto: %d", shockStatus);
        //send_shock_attribute(&shockStatus);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}