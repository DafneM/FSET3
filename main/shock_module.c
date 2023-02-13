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
#include "led_pwm.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

#define SHOCK_SENSOR 16

void readShockSensor(){
    gpio_num_t led = 2;
    configure_led_pwm(led);

    uint32_t count = 1;
    int shockStatus;
    while (true) {
        shockStatus = gpio_get_level(SHOCK_SENSOR);
        printf("Status Sensor Impacto: %d", shockStatus);
        printf("Count: %ld", count);
        count = count + 50;
        if (count < 1020) {
            led_control(count);
        }
        else {
            count = 0;
            led_control(count);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}