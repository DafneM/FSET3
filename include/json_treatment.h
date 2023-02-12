#ifndef JSON_TREATMENT_H
#define JSON_TREATMENT_H

void send_dht_telemetry(void *temperature, void *humidity);

void mqtt_event_data_parser(char *data);

void send_photo_telemetry(int *luminosity, int *light);

void send_heartbeat_telemetry(int *heartbeat);

void send_board_led_attribute(int *led_status);

void send_shock_attribute(int *shocksensor);

#endif