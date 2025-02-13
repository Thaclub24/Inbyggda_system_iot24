#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include <portmacro.h>
#include "freertos/projdefs.h"

class Button{

    public:
    Button(gpio_num_t pin);
    void init();
    void update();
    bool isPressed();
    void setOnPressed(int(*onPressed)(int pin));
    int pin;
    bool state;
    bool lastState;
    uint64_t lastDebounceTime;
    int buttonRealsed;
    int startTickButton;
    int timeSincePressed;
    TickType_t startTick;

    typedef int (*onPressed_cb1)(int);
    onPressed_cb1 onPressed_cb = NULL;

    typedef int(*onRealsed_cb1)(int);
    onRealsed_cb1 onRealsed_cb = NULL;


};

#endif //BUTTON_H