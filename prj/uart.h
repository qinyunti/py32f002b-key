#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdint.h>

void uart_init(uint32_t baud);
uint32_t uart_send(uint8_t* buffer, uint32_t len);
uint32_t uart_read(uint8_t* buffer, uint32_t len);
void uart_rx_cb(uint8_t* buff, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif


