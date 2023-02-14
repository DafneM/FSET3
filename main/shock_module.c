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
#include "nvs.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

#define SHOCK_SENSOR 16

void readShockSensor(){
    gpio_num_t led = 2;
    configure_led_pwm(led);

    char* var_name = "intensity";
    int shockStatus;
    esp_err_t err;

    int32_t intensity = read_int(var_name);
    while (true) {
        shockStatus = gpio_get_level(SHOCK_SENSOR);
        printf("Status Sensor Impacto: %d", shockStatus);
        printf("Intensidade: %ld", intensity);
        if (shockStatus == 1) {
            intensity = intensity + 20;
        }
        else {
            intensity = intensity - 20;
        }

        if (intensity > 1020) {
            intensity = 1020;
            led_control(intensity);
        } 
        else if (intensity > 0) {
            led_control(intensity);
        }
        else {
            intensity = 0;
            led_control(intensity);
        }
        
        err = save_int(intensity,var_name);
        send_shock_attribute(&shockStatus);
        send_accumulated_heat_attribute(&intensity);
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void readShockSensorBatery(){
    int shockStatus;
    int count = 0;
    while (true) {
        shockStatus = gpio_get_level(SHOCK_SENSOR);
        printf("Status Sensor Impacto: %d", shockStatus);
        send_shock_attribute(&shockStatus);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        if (shockStatus == 0) {
            count++;
        }
        
        if (count > 5) {
            break;
        }
    }
}