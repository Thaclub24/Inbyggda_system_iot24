#include <stdio.h>
#include "Button.h"
#include "driver/gpio.h"

int onPressed_cb(int i){
 printf("GPIO Funkar\n");
    return 0;
}

extern "C" void app_main(void)
{
   Button knapp1 = Button(GPIO_NUM_12);

    knapp1.init();
    knapp1.setOnPressed(onPressed_cb);
while (1)
{ 
    knapp1.update();
}

};