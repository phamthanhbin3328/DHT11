#include "DHT11.h"
extern TIM_HandleTypeDef htim4;


uint16_t Response = 0;


void MXGPIOin(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}
void MXGPIOout(void){
GPIO_InitTypeDef GPIO_InitStruct= {0};
GPIO_InitStruct.Pin=DHT11_Pin;
GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(DHT11_GPIO_Port,&GPIO_InitStruct);
}

void Delay_Us(TIM_HandleTypeDef htime,uint32_t time){
 HAL_TIM_Base_Start(&htime);
__HAL_TIM_SET_COUNTER(&htime,0);
	while(__HAL_TIM_GET_COUNTER(&htime)<time){}
}
uint16_t DHT_ReadPin(){
	return HAL_GPIO_ReadPin(DHT11_GPIO_Port,DHT11_Pin);
}
uint16_t DHT_Start(void){
	
	MXGPIOout();
	HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,0);
	HAL_Delay(20);
	HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,1);
	MXGPIOin();
	Delay_Us(htim4,40);
	if (!DHT_ReadPin())
	{
		Delay_Us(htim4, 90); 
		if(DHT_ReadPin())
		{
			Response = 1;   
		}
		else 
		{
			Response = 0; 
		}
	}		
	while(DHT_ReadPin());
	return Response;
}
uint16_t DHT_Read()
{
	uint16_t Value = 0;
	MXGPIOin();
	for(int i = 0; i<8; i++)
	{
		while(!DHT_ReadPin());
		Delay_Us(htim4, 40);
		if(!DHT_ReadPin())
		{
			Value &= ~(1<<(7-i));	
		}
		else Value |= 1<<(7-i);
		while(DHT_ReadPin());
	}
	return Value;
}