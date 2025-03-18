#include <stdio.h>
#include <string.h>
#include "Configuration.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"

#define NVS_NAMESPACE "storage"
#define DEVICE_NAME_KEY "device_name"
#define SERIAL_NUMBER_KEY "serial_number"

Configuration::Configuration() {
    memset(deviceName, 0, MAX_STR_LEN);
    memset(serialNumber, 0, MAX_STR_LEN);
}

void Configuration::init() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    nvs_handle_t nvsHandle;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvsHandle) == ESP_OK) {
        size_t required_size = sizeof(deviceName);
        if (nvs_get_str(nvsHandle, DEVICE_NAME_KEY, deviceName, &required_size) != ESP_OK) {
            strcpy(deviceName, "DefaultDevice"); 
        }

        required_size = sizeof(serialNumber);
        if (nvs_get_str(nvsHandle, SERIAL_NUMBER_KEY, serialNumber, &required_size) != ESP_OK) {
            strcpy(serialNumber, "0000000000"); 
        }

        nvs_close(nvsHandle);
    }

    printf("✅ NVS initialized and values loaded into RAM.\n");
}

const char* Configuration::getDeviceName() {
    return deviceName;
}

const char* Configuration::getSerialNumber() {
    return serialNumber;
}

esp_err_t Configuration::setDeviceName(const char* newName) {
    if (!newName) return ESP_ERR_INVALID_ARG;

    strncpy(deviceName, newName, MAX_STR_LEN - 1);
    deviceName[MAX_STR_LEN - 1] = '\0';

    return saveToNVS(DEVICE_NAME_KEY, deviceName);
}

esp_err_t Configuration::setSerialNumber(const char* newSerial) {
    if (!newSerial) return ESP_ERR_INVALID_ARG;

    strncpy(serialNumber, newSerial, MAX_STR_LEN - 1);
    serialNumber[MAX_STR_LEN - 1] = '\0';

    return saveToNVS(SERIAL_NUMBER_KEY, serialNumber);
}

esp_err_t Configuration::saveToNVS(const char* key, const char* value) {
    nvs_handle_t nvsHandle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvsHandle);
    if (err == ESP_OK) {
        err = nvs_set_str(nvsHandle, key, value);
        if (err == ESP_OK) {
            err = nvs_commit(nvsHandle);
        }
        nvs_close(nvsHandle);
    } else {
        printf("❌ Failed to write '%s' to NVS: %s\n", key, esp_err_to_name(err));
    }
    return err;
}
