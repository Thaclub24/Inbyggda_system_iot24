#include <stdio.h>
#include "Ljussensor.h"
#include "esp_adc/adc_oneshot.h"

LDRSensor::LDRSensor(adc_unit_t unit, adc_channel_t adcChannel) 
    : channel(adcChannel) {  // 🔹 Initialisera channel här
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = unit,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };
    adc_oneshot_new_unit(&init_config, &adc_handle);

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_0,
        .bitwidth = ADC_BITWIDTH_DEFAULT
    };

    adc_oneshot_config_channel(adc_handle, this->channel, &config); // 🔹 Nu fungerar det!
}

LDRSensor::~LDRSensor(){
    adc_oneshot_del_unit(adc_handle);
}

int LDRSensor::readLightLevel() {
    int raw_value = 0;
    adc_oneshot_read(adc_handle, this->channel, &raw_value);  // 🔹 Nu fungerar det!
    return raw_value;
}
