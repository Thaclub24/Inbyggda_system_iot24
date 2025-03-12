#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#define MAX_STR_LEN 32

class Configuration{
public:
Configuration();

void init();
const char* getDeviceName();
    const char* getSerialNumber();
    
    void setDeviceName(const char* newName);
    void setSerialNumber(const char* newSerial);

private:
    nvs_handle_t nvsHandle; // NVS-hanterare
    
    char deviceName[MAX_STR_LEN];    // Buffer för enhetsnamn
    char serialNumber[MAX_STR_LEN];  // Buffer för serienummer

    esp_err_t getValue(const char* key, char* buffer, size_t length);
    esp_err_t setValue(const char* key, const char* value);
};

#endif //CONFIGURATION_H