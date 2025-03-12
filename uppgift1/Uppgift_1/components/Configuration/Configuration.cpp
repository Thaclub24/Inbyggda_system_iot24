#include <stdio.h>
#include "Configuration.h"


Configuration::Configuration() {
    memset(deviceName, 0, MAX_STR_LEN);
    memset(serialNumber, 0, MAX_STR_LEN);
}

void Configuration::init() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        err = nvs_flash_init();
    }

    if (err != ESP_OK) {
        printf("❌ NVS initialization failed: %s\n", esp_err_to_name(err));
        return;
    }

    err = nvs_open("storage", NVS_READWRITE, &nvsHandle);
    if (err != ESP_OK) {
        printf("❌ NVS open failed: %s\n", esp_err_to_name(err));
        return;
    }

    printf("✅ NVS initialized successfully!\n");
}

const char* Configuration::getDeviceName() {
    if (getValue("deviceName", deviceName, MAX_STR_LEN) != ESP_OK) {
        strcpy(deviceName, "DefaultDevice");
    }
    return deviceName;
}

const char* Configuration::getSerialNumber() {
    if (getValue("serialNumber", serialNumber, MAX_STR_LEN) != ESP_OK) {
        strcpy(serialNumber, "0000000000");
    }
    return serialNumber;
}

void Configuration::setDeviceName(const char* newName) {
    strncpy(deviceName, newName, MAX_STR_LEN - 1);
    deviceName[MAX_STR_LEN - 1] = '\0';  // Säkerhetsåtgärd
    setValue("deviceName", newName);
}

void Configuration::setSerialNumber(const char* newSerial) {
    strncpy(serialNumber, newSerial, MAX_STR_LEN - 1);
    serialNumber[MAX_STR_LEN - 1] = '\0';  // Säkerhetsåtgärd
    setValue("serialNumber", newSerial);
}

esp_err_t Configuration::getValue(const char* key, char* buffer, size_t length) {
    size_t required_size = length;
    esp_err_t err = nvs_get_str(nvsHandle, key, buffer, &required_size);
    
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        printf("⚠️  Value for key '%s' not found in NVS.\n", key);
        return err;
    } else if (err != ESP_OK) {
        printf("❌ Error reading key '%s' from NVS: %s\n", key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t Configuration::setValue(const char* key, const char* value) {
    esp_err_t err = nvs_set_str(nvsHandle, key, value);
    if (err == ESP_OK) {
        err = nvs_commit(nvsHandle);
        if (err != ESP_OK) {
            printf("❌ Failed to commit NVS: %s\n", esp_err_to_name(err));
        }
    } else {
        printf("❌ Failed to set key '%s' in NVS: %s\n", key, esp_err_to_name(err));
    }
    return err;
}
