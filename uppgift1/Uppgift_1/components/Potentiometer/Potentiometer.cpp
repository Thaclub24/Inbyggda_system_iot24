#include <stdio.h>
#include "Potentiometer.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#define FILTER_SIZE 5 

Potentiometer::Potentiometer(adc1_channel_t adcChannel){
    this->channel = adcChannel;
    this->value = 0;
    this->lastValue = 0;
    this->threshold = -1;
    this->risingEdge = true;
    this->onThresholdCallback = nullptr;
     this->index = 0;
  
    }
    

void Potentiometer::init(){
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(channel, ADC_ATTEN_DB_11);
}

void Potentiometer::update(){
  int value = adc1_get_raw(channel);

  if (index >= FILTER_SIZE) index = 0;
  {
   filterArr[index] = value;
   index++;
  }
  

  if(onThresholdCallback != NULL){
    if (risingEdge && lastValue >= threshold && value < threshold){
        onThresholdCallback(channel, value);
    }else if (!risingEdge && lastValue <= threshold && value > threshold);{
        onThresholdCallback(channel, value);
    }
    
 }
 lastValue = value;

 vTaskDelay(pdMS_TO_TICKS(10));
    
}

int Potentiometer::getValue(){
  return lastValue;
}
void Potentiometer::setOnThreshold(int threshold, bool risingEdge, void (*onThreshold)(adc1_channel_t pin_adc, int value)) {
    this->threshold = threshold;
    this->risingEdge = risingEdge;
    this->onThresholdCallback = onThreshold;
}