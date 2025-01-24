#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "fifo.h"
#include <stdio.h>

#include "py32f0xx.h"
#include "py32f002b_ll_usart.h"

#define CriticalAlloc()
#define EnterCritical()                              __disable_irq()
#define ExitCritical()                              __enable_irq()

uint8_t s_uart_rx_buffer[64];

static fifo_st s_uart_fifo_dev=
{
 .in = 0,
 .len = 0,
 .out = 0,
 .buffer = s_uart_rx_buffer,
 .buffer_len = sizeof(s_uart_rx_buffer),
};

void uart_rx_cb(uint8_t* buff, uint32_t len)
{
	fifo_in(&s_uart_fifo_dev, buff, len);
}

void USART1_Handler(void)
{
	uint8_t ch;
	ch = LL_USART_ReceiveData8(USART1);
	uart_rx_cb(&ch, 1);
}


void uart_init(uint32_t baud)
{
	 UART_HandleTypeDef huart;
	
		GPIO_InitTypeDef  GPIO_InitStruct;

		__HAL_RCC_GPIOA_CLK_ENABLE();                          /* Enable GPIOA clock */
	  __HAL_RCC_USART1_CLK_ENABLE();
	
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* Push-pull output */
		GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;          /* GPIO speed */  
	  GPIO_InitStruct.Alternate = GPIO_AF1_USART1;           /* PA6 AF1 USART_TX*/
		/* GPIO initialization */
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  

 
	 //LL_USART_InitTypeDef USART_InitStruct;
	 //USART_InitStruct.BaudRate = baud;
	 //USART_InitStruct.DataWidth = 16;
	 //USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	 //USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_8;
	 //USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	 //USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	 //USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	 //LL_USART_Init(USART1, &USART_InitStruct);
	 //LL_USART_EnableIT_RXNE(USART1);
	 
	 huart.Instance = USART1;
	 huart.Init.BaudRate = baud;
	 huart.Init.WordLength = UART_WORDLENGTH_8B;
	 huart.Init.StopBits = UART_STOPBITS_1;
	 huart.Init.Parity = UART_PARITY_NONE;
	 huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	 huart.Init.Mode = UART_MODE_TX_RX;
	 huart.Init.OverSampling = UART_OVERSAMPLING_8;
	 HAL_UART_Init(&huart);
	 
	 //24000000/115200 = 208.3333
	 //USART1->BRR = (208ul<<4) + 5;
	 __HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
	 HAL_NVIC_SetPriority(USART1_IRQn,1,1);
	 HAL_NVIC_EnableIRQ(USART1_IRQn);
}

uint32_t uart_send(uint8_t* buffer, uint32_t len)
{
    for(uint32_t i=0;i<len;i++)
    {
			while(LL_USART_IsActiveFlag_TXE(USART1) == 0);
			LL_USART_TransmitData8(USART1,buffer[i]);
    }
    return len;
}

uint32_t uart_read(uint8_t* buffer, uint32_t len)
{
    uint32_t rlen;
    CriticalAlloc();
    EnterCritical();
    rlen = fifo_out(&s_uart_fifo_dev, buffer, len);
    ExitCritical();
    return rlen;
}
