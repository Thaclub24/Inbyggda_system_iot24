#include <stdio.h>
#include "Binary_led.h"
#include "esp_log.h"

BinaryLed::BinaryLed(gpio_num_t pin){
    this->pin = pin;
    this->ledState = false;
    this->blinking = false;
    this->onTime = 1000;
    this->offTime = 1000;
    this->lastToggleTime = xTaskGetTickCount();
}

void BinaryLed::init(){
    
}