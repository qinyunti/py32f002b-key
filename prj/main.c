#include <stdio.h>
#include <string.h>

#include "py32f0xx.h"
#include "key.h"
#include "uart.h"

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


uint32_t diff_u32(uint32_t pre, uint32_t cur)
{
	if(cur >= pre){
		return cur - pre;
	}else{
		return (uint32_t)0xFFFFFFFF - cur + pre + 1;
	}
}

#define AT_CONN "AT+CONN=D2BC14D9F46B\r\n"
#define LED_PERIOD 1000
#define KEY_PERIOD 20

static uint8_t s_key_buf[4] = {0xAA,0x55,0xFF,0x00};

int main(void){
		uint32_t led_pre_ts = 0;
		uint32_t led_cur_ts = 0;
		uint32_t key_pre_ts = 0;
		uint32_t key_cur_ts = 0;
	
	  uint8_t key_now;
	
	  HAL_Init();
	  HAL_Delay(1000);
	  led_init();
		key_init();
		uart_init(115200);
	
		uart_send((uint8_t*)AT_CONN,strlen(AT_CONN));
	  HAL_Delay(1000);
	
	  led_pre_ts = HAL_GetTick();
	  key_pre_ts = HAL_GetTick();
	
		while (1){
			
			led_cur_ts = HAL_GetTick();
			key_cur_ts = HAL_GetTick();
			
			if(diff_u32(led_pre_ts, led_cur_ts) >= LED_PERIOD){
				led_pre_ts = led_cur_ts;
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
			}

			if(diff_u32(key_pre_ts, key_cur_ts) >= KEY_PERIOD){
				key_pre_ts = key_cur_ts;
				key_read(&key_now);
				s_key_buf[2] = key_now;
				s_key_buf[3] = ~key_now;
				uart_send(s_key_buf,sizeof(s_key_buf));
			}
		}
}
