#include <stdio.h>
#include "Potentiometer.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc/adc_oneshot.h"  
#include "esp_log.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#define TAG "POTENTIOMETER"

Potentiometer::Potentiometer(adc_channel_t adcChannel)
    : channel(adcChannel), value(0), lastValue(0), threshold(2000), risingEdge(true),
      onThresholdCallback(NULL), index(0), active(false) {
}

void Potentiometer::init() {
    // Konfigurera ADC Oneshot Mode Driver
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,  // Vi använder ADC_UNIT_1
        // Övriga fält lämnas standard (beroende på ESP-IDF-version)
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_11,       // 0–3.3V mätområde (använd ADC_ATTEN_DB_11 eller DB_12 enligt din applikation)
        .bitwidth = ADC_BITWIDTH_12,    // 12-bitars upplösning
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, channel, &config));

    ESP_LOGI(TAG, "ADC Oneshot Mode initierad för kanal: %d", channel);
}

void Potentiometer::update() {
    if (!active) {
        return;
    }
    
    int newValue;
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, channel, &newValue));

    // Enkel cirkulär filter (kan utökas om nödvändigt)
    if (index >= FILTER_SIZE) {
        index = 0;
    }
    filterArr[index] = newValue;
    index++;

    // Om en callback är satt, kontrollera om vi har passerat tröskeln
    if (onThresholdCallback != NULL) {
        if (risingEdge && lastValue < threshold && newValue >= threshold) {
            onThresholdCallback(channel, newValue);
        } else if (!risingEdge && lastValue > threshold && newValue <= threshold) {
            onThresholdCallback(channel, newValue);
        }
    }

    lastValue = newValue;
    value = newValue;
    
    vTaskDelay(pdMS_TO_TICKS(10));  // Kort delay för att undvika överdriven CPU-belastning
}

int Potentiometer::getValue() {
    return lastValue;
}

void Potentiometer::setOnThreshold(int threshold, bool risingEdge, onThreshold_t onThresholdFunc) {
    this->threshold = threshold;
    this->risingEdge = risingEdge;
    this->onThresholdCallback = onThresholdFunc;
}

void Potentiometer::setActive(bool value) {
    active = value;
}
