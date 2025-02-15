#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"   
#include "freertos/FreeRTOS.h"  
#include "freertos/projdefs.h"

class Button {
public:
    Button(gpio_num_t pin);
    void init();
    void update();
    bool isPressed();
    void setOnPressed(int (*onPressed)(int pin));
    void setOnReleased(int (*onReleased)(int pin));

    gpio_num_t pin; 
    bool state;
    bool lastState;
    uint64_t lastDebounceTime;
    bool buttonReleased;
    TickType_t startTickButton; 
    int timeSincePressed;

    typedef int (*onPressed_cb1)(int);
    onPressed_cb1 onPressed_cb = NULL;

    typedef int (*onReleased_cb1)(int);
    onReleased_cb1 onReleased_cb = NULL;
};

#endif // BUTTON_H
