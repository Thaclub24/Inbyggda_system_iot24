#include "AnalogLed.h"
#include <cmath> // Behövs för sin()
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define DUTY_STEP 5
#define DUTY_CYCLE_MAX 8191
#define DUTY_CYCLE_MIN 0

AnalogLed::AnalogLed(gpio_num_t pin) : pin(pin), current_duty(0), increasing(true) {}

void AnalogLed::init() {
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE, 
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .gpio_num       = pin,
        .speed_mode     = LEDC_LOW_SPEED_MODE,  
        .channel        = LEDC_CHANNEL_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}

void AnalogLed::update() {
    if(useSinWave){
        TickType_t currentTime = xTaskGetTickCount();
        float timeElapsed = (currentTime - startTime) * portTICK_PERIOD_MS;  
        float angle = (2 * M_PI * timeElapsed) / period;
        current_duty = (std::sin(angle) + 1) * (DUTY_CYCLE_MAX / 2);

        if (timeElapsed >= period) {
            startTime = xTaskGetTickCount();  // Nollställ starttid
        }
    } 
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, current_duty); 
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
    //ESP_LOGI("AnalogLed", "LED PWM Duty Cycle: %d", current_duty);

}

void AnalogLed::settLed(int value) {
    current_duty = value;
    this->useSinWave = false;
    ESP_LOGI("AnalogLed", "Set LED PWM duty Cycle to: %d", value);
}

void AnalogLed::useSin(bool enable,uint32_t period) {
    this->period = period;
    this->useSinWave = true;
    this->startTime = xTaskGetTickCount();
}
