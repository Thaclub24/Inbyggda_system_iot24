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
    if (increasing) {
        current_duty += DUTY_STEP;
        if (current_duty >= DUTY_CYCLE_MAX) {
            current_duty = DUTY_CYCLE_MAX;
            increasing = false;
        }
    } else {
        current_duty -= DUTY_STEP;
        if (current_duty <= DUTY_CYCLE_MIN) {
            current_duty = DUTY_CYCLE_MIN;
            increasing = true;
        }
    }
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, current_duty); 
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
    ESP_LOGI("AnalogLed", "LED PWM Duty Cycle: %d", current_duty);
}

void AnalogLed::setLed(int value) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, value); 
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
    ESP_LOGI("AnalogLed", "Set LED PWM duty Cycle to: %d", value);
}

void AnalogLed::sin(uint32_t period) {
    for (uint32_t t = 0; t < period; ++t) {
        current_duty = (std::sin(t * 2 * M_PI / period) + 1) * DUTY_CYCLE_MAX / 2; // ✅ Fixad
        update();
        vTaskDelay(pdMS_TO_TICKS(10)); 
    }
}
