#include <stdio.h>
#include "Button.h"
#include "Potentiometer.h"
#include "Binary_led.h"
//#include "AnalogLed.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN GPIO_NUM_12
#define LED_TIMER LEDC_TIMER_0
#define LED_CHANNEL LEDC_CHANNEL_0

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
void myThresholdCallback(adc1_channel_t pin_adc, int value) {
    printf("Threshold passed! Pin: %d, Value: %d\n", pin_adc, value);
    
}

//För Analog led
/*extern "C" void app_main(void) {
    AnalogLed led(LED_PIN,);
    led.init();

    // Fading effekt, uppdaterar PWM-värdet var 10:e ms
    while (1) {
        led.update();  // Uppdaterar LED:ens ljusstyrka
        vTaskDelay(pdMS_TO_TICKS(50));  // Vänta en liten stund innan nästa uppdatering
    }
}*/

//För binary led
extern "C" void app_main(void){
    BinaryLed led(LED_PIN);
    led.init();

    led.blink(500,500);

    while (1){
        led.update(pdMS_TO_TICKS(10));
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
}

//För potentiometer
/*extern "C" void app_main(void) {
   Potentiometer pot(ADC1_CHANNEL_0);

   pot.init();

   pot.setOnThreshold(2000, true, myThresholdCallback);

   while (1)
   {
    pot.update();
    vTaskDelay(pdMS_TO_TICKS(10));
   }
   
}*/

//För button
/*extern "C" void app_main(void) {
    Button knapp1((gpio_num_t)GPIO_NUM_12);
    knapp1.init();
    
    // Registrera callbacks
    knapp1.setOnPressed(onPressed_cb);
    knapp1.setOnReleased(onReleased_cb);  // (valfritt, men bra att ha)

    while (1) {  
        knapp1.update();
        vTaskDelay(pdMS_TO_TICKS(10));  // Vänta 10 ms för att spara CPU
    }
}*/
