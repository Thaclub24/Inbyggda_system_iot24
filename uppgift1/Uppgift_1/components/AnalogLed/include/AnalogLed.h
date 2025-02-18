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
    void setLed(int value);     
    void sin(uint32_t period);  

private:
    gpio_num_t pin;
    ledc_channel_config_t ledc_channel;
    int current_duty;
    bool increasing;
};

#endif // ANALOG_LED_H
