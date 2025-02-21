#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include"esp_adc/adc_oneshot.h"
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


typedef void (*onThreshold_t)(adc_channel_t pin_adc, int value);

#define FILTER_SIZE 5

class Potentiometer {
public:
    // Konstruktor: tar in en ADC-kanal (adc_channel_t)
    Potentiometer(adc_channel_t adcChannel);

    void init();
    void update();
    int getValue();
    void setOnThreshold(int threshold, bool risingEdge, onThreshold_t onThresholdFunc);
    void setActive(bool value);

private:
    adc_channel_t channel; 
    int value;
    int lastValue;
    int threshold;
    bool risingEdge;
    onThreshold_t onThresholdCallback;

    int filterArr[FILTER_SIZE];
    int index;

    bool active;

    adc_oneshot_unit_handle_t adc_handle;
};


#endif // POTENTIOMETER_H
