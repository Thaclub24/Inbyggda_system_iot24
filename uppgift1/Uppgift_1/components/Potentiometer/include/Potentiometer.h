#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H 

#include "driver/adc.h"


class Potentiometer{
    public:
    Potentiometer(adc1_channel_t adcChannel);
    void init();
    void update();
    int getValue();
    void setOnThreshold ( int threshold, bool risingEdge, void (*onThreshold)(int pin_adc, int value, void*), void* userData )


};
#endif //POTENTIOMETER_H