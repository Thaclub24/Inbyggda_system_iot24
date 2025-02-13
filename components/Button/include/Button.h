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
    void setOnPressed(void(*onPressed)(int pin));
    int pin;
    int state;
};

#endif //BUTTON_H

