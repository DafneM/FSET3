
#include <stdio.h>
#include <string.h>
#include "driver/gpio.h"
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

void light_sleep_task() {
    esp_err_t err;
    err = gpio_wakeup_enable(16, GPIO_INTR_HIGH_LEVEL);
    ESP_ERROR_CHECK(err);
    err = esp_sleep_enable_gpio_wakeup();
    ESP_ERROR_CHECK(err);
    mqtt_stop();
    wifi_stop();
    esp_light_sleep_start();

    ESP_LOGI("Awaken", "Sinal na GPIO despertou placa");
    wifi_start();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ESP_LOGI("Awaken", "WiFi e MQTT ligados");
}

void wake_up_with_gpio(gpio_num_t pin) {
    esp_err_t err;
    err = gpio_wakeup_enable(pin, GPIO_INTR_HIGH_LEVEL);
    ESP_ERROR_CHECK(err);
    err = esp_sleep_enable_gpio_wakeup();
    ESP_ERROR_CHECK(err);
}