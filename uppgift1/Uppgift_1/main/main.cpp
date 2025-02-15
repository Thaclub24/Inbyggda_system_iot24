#include <stdio.h>
#include "Button.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Callback-funktion för när knappen trycks ner
int onPressed_cb(int pin) {
    printf("Knapp tryckt! GPIO: %d\n", pin);
    return 0;
}

// Callback-funktion för när knappen släpps (valfritt)
int onReleased_cb(int pin) {
    printf("Knapp släppt! GPIO: %d\n", pin);
    return 0;
}

extern "C" void app_main(void) {
    Button knapp1((gpio_num_t)GPIO_NUM_12);
    knapp1.init();
    
    // Registrera callbacks
    knapp1.setOnPressed(onPressed_cb);
    knapp1.setOnReleased(onReleased_cb);  // (valfritt, men bra att ha)

    while (1) {  
        knapp1.update();
        vTaskDelay(pdMS_TO_TICKS(10));  // Vänta 10 ms för att spara CPU
    }
}
