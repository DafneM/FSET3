#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#include "wifi.h"
#include "mqtt.h"
#include "dht11.h"
#include "json_treatment.h"
#include "gpio.h"
#include "battery_mode.h"
#include "gpio_wakeup.h"
#include "photo_module.h"
#include "heartbeat_module.h"
#include "analog_sensors.h"
#define ESP_CONFIG_NUMBER CONFIG_ESP_CONFIG_NUMBER

#define TEMP_GPIO 19

#define ESP_MODE CONFIG_ESP_MODE
#define BATTERY_MODE 0
#define ENERGY_MODE 1

SemaphoreHandle_t connectionWifiSemaphore;
SemaphoreHandle_t connectionMQTTSemaphore;
SemaphoreHandle_t reconnectionWifiSemaphore;

void wifi_connected(void * params)
{
  while(true)
  {
    if(xSemaphoreTake(connectionWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}

void handle_server_communication(void * params)
{
  char mensagem[50];
  char jsonAtributos[200];
  if(xSemaphoreTake(connectionMQTTSemaphore, portMAX_DELAY))
  {
    while(true)
    {
       float temp = 20.0 + (float)rand()/(float)(RAND_MAX/10.0);
       
      //  sprintf(mensagem, "{\"temperature\": %f}", temp);
      //  mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

      //  sprintf(jsonAtributos, "{\"quantidade de pinos\": 5, \n\"umidade\": 20}");
      //  mqtt_envia_mensagem("v1/devices/me/attributes", jsonAtributos);

       vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
  }
}

void read_temperature_humidity_sensor(){
    struct dht11_reading temp_sensor_read;
    float temperature, humidity;

    DHT11_init(TEMP_GPIO);

    while(1){
        temp_sensor_read = DHT11_read();
        temperature = temp_sensor_read.temperature;
        humidity = temp_sensor_read.humidity;
        send_dht_telemetry(&temperature, &humidity);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        if((temperature < 20 || temperature > 24) || humidity > 60){
          // change_buzzer_state(1);
        }
    }
}

void app_main(void)
{
    printf("ESP NUMBER %d\n", ESP_CONFIG_NUMBER);
    // configure_buzzer();
    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    connectionWifiSemaphore = xSemaphoreCreateBinary();
    connectionMQTTSemaphore = xSemaphoreCreateBinary();
    reconnectionWifiSemaphore = xSemaphoreCreateBinary();
    wifi_start();
    printf("ESP MODE %d\n", ESP_MODE);

    xTaskCreate(&wifi_connected,  "Conexão ao MQTT", 4096, NULL, 1, NULL);
    xTaskCreate(&handle_server_communication, "Comunicação com Broker", 4096, NULL, 1, NULL);
    if(ESP_CONFIG_NUMBER == 0){
      configure_buzzer();
      xTaskCreate(&read_temperature_humidity_sensor, "Comunicação com Broker", 4096, NULL, 1, NULL);
    } else if(ESP_CONFIG_NUMBER == 1){
      setup_analog_sensors();
      xTaskCreate(&check_luminosity, "Leitura de Luminosidade", 4096, NULL, 1, NULL);
      xTaskCreate(&check_heartbeat, "Leitura de Batimentos", 4096, NULL, 1, NULL);
    } else {
      // Opção com LED e sensor de incêndio
    }

    if(ESP_MODE == BATTERY_MODE) {
      ESP_LOGI("modo da esp", "Selecionou modo de bateria");
      example_register_gpio_wakeup();
      xTaskCreate(light_sleep_task, "light_sleep_task", 4096, NULL, 6, NULL);
    }
    else if(ESP_MODE == ENERGY_MODE) {
      ESP_LOGI("modo da esp", "Selecionou modo de energia");
      // loop no modo energia
    }
}

