#include "Button.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"


#define PULL_DOWN (gpio_pulldown_t) 0
#define PULL_UP (gpio_pullup_t) 0
#define DEBOUNCE_TIME_US 10000  // 10ms debounce

Button::Button(gpio_num_t P_pin){
this->pin = P_pin;
this->lastState = false;
this->state = false;
this->lastDebounceTime = 0;
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
gpio_num_t GPIO_NUM_12 = (gpio_num_t)this->pin;
int gpio_level = gpio_get_level(GPIO_NUM_12);

if (gpio_level == 1 && buttonRealsed == false)
{
    this->buttonRealsed = true;
    this->startTickButton = xTaskGetTickCount();
    

    this->onPressed_cb(this->pin);
}

if(gpio_level == 0 && buttonRealsed == true){
    TickType_t timeSincePressed = xTaskGetTickCount() - startTickButton;

    if (timeSincePressed >= pdMS_TO_TICKS(DEBOUNCE_TIME_US)) {
        this->onRealsed_cb(this->pin);

        this->buttonRealsed = false;
        this->startTickButton = xTaskGetTickCount();
    };
    
};



state = false;


};

//bool Button::isPressed()
void Button::setOnPressed(int (*)(int)){

};