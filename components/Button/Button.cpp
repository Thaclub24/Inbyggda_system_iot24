#include "Button.h"
#include "driver/gpio.h"

#define PULL_DOWN (gpio_pulldown_t) 0
#define PULL_UP (gpio_pullup_t) 0
#define DEBOUNCE_TIME_US 10000  // 10ms debounce

Button::Button(gpio_num_t P_pin){
this->pin = P_pin;
}

void Button::init(){
    gpio_config_t buttonConfig;
    buttonConfig.mode = GPIO_MODE_INPUT;
    buttonConfig.intr_type = GPIO_INTR_DISABLE;
    buttonConfig.pull_down_en = PULL_DOWN;
    buttonConfig.pull_up_en = PULL_UP;
    buttonConfig.pin_bit_mask = 1ULL << pin;
    esp_err_t error = gpio_config(&buttonConfig);

    if (error != ESP_OK) {
        printf("GPIO configuration failed for pin %d with error code: %d\n", GPIO_NUM_12, error);
    }

};

void Button::update(){
/*xxx update (xxx)
Debounce krävs
10 milisekunders period eller snabbare (Gäller alla komponenter)
Får ej använda delay eller fastna här, ingen while loop.
*/
state = false;


};
