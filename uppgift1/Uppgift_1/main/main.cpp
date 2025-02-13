#include <stdio.h>
#include "Button.h"
#include "driver/gpio.h"



extern "C" void app_main(void)
{
   Button knapp1 = Button(GPIO_NUM_12);

    knapp1.init();



};