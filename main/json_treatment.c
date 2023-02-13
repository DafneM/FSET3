#include "cJSON.h"
#include "cJSON.c"
#include "mqtt.h"
#include "esp_log.h"
#include "esp_event.h"

#define TAG "MQTT"

void send_dht_telemetry(void *temperature, void *humidity)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    float tmp = *(float *)temperature;
    float hmd = *(float *)humidity;
    
    cJSON_AddItemToObject(root, "temperatura", cJSON_CreateNumber(tmp));
    cJSON_AddItemToObject(root, "umidade", cJSON_CreateNumber(hmd));
    mqtt_envia_mensagem("v1/devices/me/telemetry", cJSON_Print(root));
}

void send_dht_media_telemetry(void *temperature, void *humidity)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    float tmp = *(float *)temperature;
    float hmd = *(float *)humidity;
    
    cJSON_AddItemToObject(root, "temperatura media", cJSON_CreateNumber(tmp));
    cJSON_AddItemToObject(root, "umidade media", cJSON_CreateNumber(hmd));
    mqtt_envia_mensagem("v1/devices/me/telemetry", cJSON_Print(root));
}

void mqtt_event_data_parser(char *data)
{
    cJSON *json = cJSON_Parse(data);
    if (json == NULL)
        return;
    char *key = cJSON_GetObjectItem(json, "method")->valuestring;
    int value = cJSON_GetObjectItem(json, "params")->valueint;
    // TODO: tratar os valores do JSON 
}

void send_photo_telemetry(int *luminosity, int *light)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    float lmn = *(int *)luminosity;
    float lgt = *(int *)light;
    
    cJSON_AddItemToObject(root, "luminosidade", cJSON_CreateNumber(lmn));
    cJSON_AddItemToObject(root, "estado luz", cJSON_CreateNumber(lgt));
    mqtt_envia_mensagem("v1/devices/me/telemetry", cJSON_Print(root));
}


void send_heartbeat_telemetry(int *heartbeat)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    float htb = *(int *)heartbeat;
    
    cJSON_AddItemToObject(root, "batimentos", cJSON_CreateNumber(htb));
    mqtt_envia_mensagem("v1/devices/me/telemetry", cJSON_Print(root));
}

void send_board_led_attribute(int *led_status)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    float ls = *(int *)led_status;
    
    cJSON_AddItemToObject(root, "led da placa", cJSON_CreateNumber(ls));
    mqtt_envia_mensagem("v1/devices/me/attributes", cJSON_Print(root));
}

void send_board_buzzer_attribute(int *buzzer_status)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    float ls = *(int *)buzzer_status;
    
    cJSON_AddItemToObject(root, "alarme", cJSON_CreateNumber(ls));
    mqtt_envia_mensagem("v1/devices/me/attributes", cJSON_Print(root));
}

void send_shock_attribute(int *shocksensor)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    double shocksensor_toDouble = *(int *)shocksensor;
    
    cJSON_AddItemToObject(root, "sensorImpacto", cJSON_CreateNumber(shocksensor_toDouble));
    mqtt_envia_mensagem("v1/devices/me/attributes", cJSON_Print(root));
}

void send_flame_alert(int *flame)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    double flame_toDouble = *(int *)flame;
    
    cJSON_AddItemToObject(root, "alertaFogo", cJSON_CreateNumber(flame_toDouble));
    mqtt_envia_mensagem("v1/devices/me/attributes", cJSON_Print(root));
}

void send_flame_telemetry(int *flame)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    double flame_toDouble = *(int *)flame;
    
    cJSON_AddItemToObject(root, "sensorChama", cJSON_CreateNumber(flame_toDouble));
    mqtt_envia_mensagem("v1/devices/me/telemetry", cJSON_Print(root));
}