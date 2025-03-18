#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "nvs.h"
#include "esp_err.h"

#define MAX_STR_LEN 100

class Configuration {
public:
    Configuration();
    void init();
    
    const char* getDeviceName();
    const char* getSerialNumber();
    
    esp_err_t setDeviceName(const char* newName);
    esp_err_t setSerialNumber(const char* newSerial);

private:
    char deviceName[MAX_STR_LEN];
    char serialNumber[MAX_STR_LEN];

    esp_err_t saveToNVS(const char* key, const char* value);
};

#endif // CONFIGURATION_H
