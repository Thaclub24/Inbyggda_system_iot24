#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "driver/ledc.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class AnalogLed {
public:
    AnalogLed(gpio_num_t pin);  
    void init();               
    void update();              
    void settLed(int value);     
    void useSin(bool enable, uint32_t period = 1000);  

private:
    gpio_num_t pin;
    ledc_channel_config_t ledc_channel;
    int current_duty;
    bool increasing;

    bool useSinWave = false;
    uint32_t period = 1000;
    TickType_t startTime = 0;
};

#endif // ANALOG_LED_H
