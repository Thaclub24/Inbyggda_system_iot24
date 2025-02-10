#include "Button.h"
#include "driver/gpio.h"

#define PULL_DOWN (gpio_pulldown_t) 0
#define PULL_UP (gpio_pullup_t) 0

void init(){
    gpio_config_t buttonConfig;
    buttonConfig.mode = GPIO_MODE_INPUT;
    buttonConfig.intr_type = GPIO_INTR_DISABLE;
    buttonConfig.pull_down_en = PULL_DOWN;
    buttonConfig.pull_up_en = PULL_UP;
    buttonConfig.pin_bit_mask = 1ULL << GPIO_NUM_12;
    esp_err_t error = gpio_config(&buttonConfig);
};

void update(){

};
