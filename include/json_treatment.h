#ifndef JSON_TREATMENT_H
#define JSON_TREATMENT_H

void send_dht_telemetry(void *temperature, void *humidity);

void mqtt_event_data_parser(char *data);

#endif