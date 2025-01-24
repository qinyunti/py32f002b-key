#include <stdio.h>
#include "py32f0xx.h"


void led_init(void){
  GPIO_InitTypeDef  GPIO_InitStruct;

  __HAL_RCC_GPIOC_CLK_ENABLE();                          /* Enable GPIOA clock */

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;            /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);  
}

int main(void){
	  HAL_Init();
	  led_init();
		while (1)
		{
			/* Delay 250ms */
			HAL_Delay(250);

			/* LED flipping */
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
		}
}

uint8_t otp[16]={0xAA,0xD0,0x55,0x2F,0x0B,0x00,0xF4,0xFF,0x00,0x00,0xFF,0xFF,0x3F,0x00,0xC0,0xFF};