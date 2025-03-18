#ifndef BUZZER_H
#define BUZZER_H

#include "driver/gpio.h"

class Buzzer{
public:
Buzzer(gpio_num_t pin);

void playTone(int frequency);

void stopTone();

private:
gpio_num_t buzzerPin; 

}


#endif // BUZZER_H