#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dht11.h"

void app_main(void)
{

    struct dht11_reading temp_sensor_read;
    int temperature, humidity;
    
    // WIFI EAMPLE
    //Initialize NVS
    // esp_err_t ret = nvs_flash_init();
    // if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    //   ESP_ERROR_CHECK(nvs_flash_erase());
    //   ret = nvs_flash_init();
    // }
    // ESP_ERROR_CHECK(ret);

    // ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    // wifi_init_sta();

    DHT11_init(32);

    while(1){
        temp_sensor_read = DHT11_read();
        temperature = temp_sensor_read.temperature;
        humidity = temp_sensor_read.humidity;
        printf("%d\n", temperature);
        printf("%d\n", humidity);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
