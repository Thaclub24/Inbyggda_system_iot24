#include <stdio.h>
#include "Button.h"
#include "Potentiometer.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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

extern "C" void app_main(void) {
   Potentiometer pot(ADC1_CHANNEL_0);

   pot.init();

   pot.setOnThreshold(2000, true, myThresholdCallback);

   while (1)
   {
    pot.update();
    vTaskDelay(pdMS_TO_TICKS(10));
   }
   


}
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
