#include <inttypes.h>
#include "nvs_flash.h"

#ifndef NVS_H
#define NVS_H

esp_err_t save_int(int32_t restart_counter);

int32_t read_int(void);

esp_err_t write_str(char* key, char* stringVal);

char* read_str(char* key);

#endif