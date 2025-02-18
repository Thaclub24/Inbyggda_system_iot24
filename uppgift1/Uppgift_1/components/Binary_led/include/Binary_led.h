#ifndef BINARY_LED_H
#define BINARY_LED_H

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

class BinaryLed{
    public:
    BinaryLed(gpio_num_t pin);

    void init();
    void update(TickType_t tickInterval);
    void steLed(bool value);
    void blink(int milliseconds_on, int milliseconds_off);

    private:
    gpio_num_t pin;
    bool ledState;
    bool blinking;
    int onTime;
    int offTime;
    TickType_t lastToggleTime;


};
#endif //BINARY_LED_H