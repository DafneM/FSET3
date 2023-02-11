#include <inttypes.h>
#include "nvs_flash.h"

#ifndef NVS_H
#define NVS_H

esp_err_t save_value(int32_t restart_counter);

int32_t read_value(void);

#endif