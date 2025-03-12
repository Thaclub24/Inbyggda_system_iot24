#include <stdio.h>
#include "Button.h"
#include "Potentiometer.h"
#include "Binary_led.h"
#include "AnalogLed.h"
#include "Configuration.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define LED_PIN GPIO_NUM_4
#define LED_TIMER LEDC_TIMER_0
#define LED_CHANNEL LEDC_CHANNEL_0
#define TAG "POTENTIOMETER"

// Callback-funktion för när knappen trycks ner / Button
int onPressed_cb(int pin) {
    printf("Knapp tryckt! GPIO: %d\n", pin);
    return 0;
}

// Callback-funktion för när knappen släpps (valfritt) / Button
int onReleased_cb(int pin) {
    printf("Knapp släppt! GPIO: %d\n", pin);
    return 0;
}

//Detta är för Potentiometer
void myThresholdCallback(adc_channel_t channel, int value) {
    printf("Tröskel passerad på kanal %d med värde %d\n", channel, value);
}

//För configuration
extern "C" void app_main(void){
    Configuration config;
    config.init();
    
    printf("Device Name: %s\n", config.getDeviceName());
    printf("Serial Number: %s\n", config.getSerialNumber());

    config.setDeviceName("ESP32_DevKit");
    config.setSerialNumber("123456789");

    printf("Updated Device Name: %s\n", config.getDeviceName());
    printf("Updated Serial Number: %s\n", config.getSerialNumber());
}
//För Analog led
/*extern "C" void app_main(void) {
    AnalogLed led(LED_PIN);
    led.init();
    led.settLed(500); 
    led.useSin(true, 1500);
   

   
    while (1) {
        led.update();
          // Uppdaterar LED:ens ljusstyrka
        vTaskDelay(pdMS_TO_TICKS(50));  //  Det tar en stund innan nästa uppdatering
    }
}*/

//För binary led
/*extern "C" void app_main(void){
    BinaryLed led(LED_PIN);
    led.init();

    led.blink(100,2000);

    led.steLed(0);

    while (1){
        led.update(pdMS_TO_TICKS(10));
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
}*/


//För potentiometer
/*extern "C" void app_main(void) {
    Potentiometer pot(ADC_CHANNEL_0);
    pot.init();
    pot.setActive(true);
    pot.setOnThreshold(2000, false, myThresholdCallback);

    while (1) {
        pot.update();
       // printf("ADC Värde: %d\n", pot.getValue());
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}*/

//För button
/*extern "C" void app_main(void) {
    Button knapp1((gpio_num_t)GPIO_NUM_4);
    knapp1.init();
    
    // Registrera callbacks
    knapp1.setOnPressed(onPressed_cb);
    knapp1.setOnReleased(onReleased_cb);  // (valfritt, men bra att ha)

    while (1) {  
        knapp1.update();
        vTaskDelay(pdMS_TO_TICKS(10));  // Vänta 10 ms för att spara CPU
    }
}*/
