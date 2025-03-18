#include <stdio.h>
#include "Ljussensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

LDRSensor lightSensor(ADC_UNIT_1, ADC_CHANNEL_0);

extern "C" void app_main(void)
{
    printf("Reading light level...\n");

    while (true) {
        int lightLevel = lightSensor.readLightLevel();
        printf("Light Level: %d\n", lightLevel);
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
 
}