#ifndef LJUSSENSOR_H
#define LJUSSENSOR_H

#include "esp_adc/adc_oneshot.h"

class LDRSensor {
private:
    adc_oneshot_unit_handle_t adc_handle;
    adc_channel_t channel;  // 🔹 Lägg till denna rad! 

public:
    LDRSensor(adc_unit_t unit, adc_channel_t adcChannel);
    ~LDRSensor();
    int readLightLevel();
};

#endif // LJUSSENSOR_H
