#ifndef DHT11_H
#define DHT11_H
#include "stm32f1xx_hal.h"
#define DHT11_Pin GPIO_PIN_7
#define DHT11_GPIO_Port GPIOA


uint16_t DHT_Start();
uint16_t DHT_Read();

#endif