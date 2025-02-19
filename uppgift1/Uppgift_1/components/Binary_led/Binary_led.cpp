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
    gpio_config_t gpio_conf = {};
    gpio_conf.pin_bit_mask = (1ULL << pin);
    gpio_conf.mode = GPIO_MODE_OUTPUT;
    gpio_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_conf.intr_type = GPIO_INTR_DISABLE;

    esp_err_t err = gpio_config(&gpio_conf);
    ESP_ERROR_CHECK_WITHOUT_ABORT(err);
}

void BinaryLed::update(TickType_t tickInterval){
    if(blinking){
        TickType_t now = xTaskGetTickCount();
        if ((ledState && (now - lastToggleTime) * portTICK_PERIOD_MS >= onTime) || 
            (!ledState && (now - lastToggleTime) * portTICK_PERIOD_MS >= offTime)){
        
            ledState = !ledState;
            lastToggleTime = now;
        }
       
        
    }
    gpio_set_level(pin, ledState);



}

void BinaryLed::setLed(bool value){
    blinking = false;
    ledState = value;
   

}

void BinaryLed::blink(int millieseconds_on, int millieseconds_off){
    onTime = millieseconds_on;
    offTime = millieseconds_off;
    blinking = true;
}