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

SemaphoreHandle_t connectionWifiSemaphore;
SemaphoreHandle_t connectionMQTTSemaphore;

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
  // char jsonAtributos[200];
  if(xSemaphoreTake(connectionMQTTSemaphore, portMAX_DELAY))
  {
    while(true)
    {
       float temperatura = 20.0 + (float)rand()/(float)(RAND_MAX/10.0);
       sprintf(mensagem, "temperatura1: %f", temperatura);
       mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

      //  sprintf(jsonAtributos, "{\"quantidade de pinos\": 5, \n\"umidade\": 20}");
      //  mqtt_envia_mensagem("v1/devices/me/attributes", jsonAtributos);

       vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
  }
}

void app_main(void)
{


    // struct dht11_reading temp_sensor_read;
    // int temperature, humidity;

    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    connectionWifiSemaphore = xSemaphoreCreateBinary();
    connectionMQTTSemaphore = xSemaphoreCreateBinary();
    wifi_start();

    xTaskCreate(&wifi_connected,  "Conexão ao MQTT", 4096, NULL, 1, NULL);
    xTaskCreate(&handle_server_communication, "Comunicação com Broker", 4096, NULL, 1, NULL);

    // DHT11_init(32);

    // while(1){
    //     temp_sensor_read = DHT11_read();
    //     temperature = temp_sensor_read.temperature;
    //     humidity = temp_sensor_read.humidity;
    //     printf("%d\n", temperature);
    //     printf("%d\n", humidity);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
}

