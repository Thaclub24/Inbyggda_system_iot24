#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H 

#include "driver/adc.h"
#include "freertos/FreeRTOS.h"

#define FILTER_SIZE 5


class Potentiometer{
    public:
    Potentiometer(adc1_channel_t adcChannel);
    void init();
    void update();
    int getValue();
    void setOnThreshold ( int threshold, bool risingEdge, void (*onThreshold)(adc1_channel_t pin_adc, int value));

    private:
    adc1_channel_t channel;
    int value;
    int lastValue;
    int threshold;
    bool risingEdge;
    void (*onThresholdCallback)(adc1_channel_t pin_adc, int value);

    int filterArr[FILTER_SIZE];
    int index;

};
#endif //POTENTIOMETER_H