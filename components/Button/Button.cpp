#include "Button.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#define PULL_DOWN GPIO_PULLDOWN_DISABLE
#define PULL_UP GPIO_PULLUP_ENABLE  // Ändrat till ENABLE så knappen fungerar
#define DEBOUNCE_TIME_MS 10  // 10ms debounce

Button::Button(gpio_num_t P_pin) {
    this->pin = P_pin;
    this->lastState = false;
    this->state = false;
    this->lastDebounceTime = 0;
    this->buttonReleased = true;  // ✅ Viktigt! Sätt till true från början
    this->startTickButton = 0;
    this->timeSincePressed = 0;
    this->onPressed_cb = NULL;
    this->onReleased_cb = NULL;
}
void Button::init() {
    gpio_config_t buttonConfig = {};
    buttonConfig.mode = GPIO_MODE_INPUT;
    buttonConfig.intr_type = GPIO_INTR_DISABLE;
    buttonConfig.pull_down_en = PULL_DOWN;
    buttonConfig.pull_up_en = PULL_UP;
    buttonConfig.pin_bit_mask = 1ULL << pin;

    esp_err_t error = gpio_config(&buttonConfig);
    if (error != ESP_OK) {
        printf("GPIO configuration failed for pin %d with error code: %d\n", pin, error);
    }
}

void Button::update() {
    int gpio_level = gpio_get_level((gpio_num_t)pin); // FIXAT

    TickType_t currentTick = xTaskGetTickCount();

    if (gpio_level == 1 && buttonReleased) {
        buttonReleased = false;
        startTickButton = currentTick;

        if (onPressed_cb) {
            onPressed_cb(pin);
        }
    }

    if (gpio_level == 0 && !buttonReleased) {
        timeSincePressed = currentTick - startTickButton;

        if (timeSincePressed >= pdMS_TO_TICKS(DEBOUNCE_TIME_MS)) {
            if (onReleased_cb) {
                onReleased_cb(pin);
            }

            buttonReleased = true;
            startTickButton = currentTick;
        }
    }
}


void Button::setOnPressed(int (*callback)(int)) {
    onPressed_cb = callback;  // Spara callback
}
void Button::setOnReleased(int (*onReleased)(int pin)) {
    this->onReleased_cb = onReleased;
}
