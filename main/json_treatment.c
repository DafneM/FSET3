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

void mqtt_event_data_parser(char *data)
{
    cJSON *json = cJSON_Parse(data);
    if (json == NULL)
        return;
    char *key = cJSON_GetObjectItem(json, "method")->valuestring;
    int value = cJSON_GetObjectItem(json, "params")->valueint;
    // TODO: tratar os valores do JSON 
}

void send_photo_telemetry(int *luminosity)
{

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        ESP_LOGE(TAG, "Não foi possível criar o JSON");
        return;
    }

    float lmn = *(int *)luminosity;
    
    cJSON_AddItemToObject(root, "luminosidade", cJSON_CreateNumber(lmn));
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