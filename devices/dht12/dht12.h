#include "configuration.h"

#define DHT12_I2C_ADDR (0x5C)
#define DHT12_I2C_REG_START_ADDR (0x0)
#define DHT12_DATA_SIZE (5)

// humidity max 95%
#define DHT12_MAX_HUMI (950)
// humidity min 20%
#define DHT12_MIN_HUMI (200)
// temperature max 60
#define DHT12_MAX_TEMP (600)
// temperature min -20
#define DHT12_MIN_TEMP (-200)
status_t dht12_get_temp_humi(char * temp_str, char * humi_str);
