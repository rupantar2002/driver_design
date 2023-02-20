#ifndef __UART_INTF_H__
#define __UART_INTF_H__

#include <stdint.h>

typedef int (*uart_intf_callback_fun_t)(uint8_t uart_num, uint8_t *data, uint32_t size);

typedef struct uart_intf_tagConfig *uart_intf_handle_t;

uart_intf_handle_t uart_intf_Init(uint8_t uart_num, uint16_t rx, uint16_t tx, uint32_t baud_rate, uint16_t rx_buffer, uint16_t tx_buffer);

int uart_intf_Destroy(uart_intf_handle_t handle);

int uart_intf_Write(uart_intf_handle_t handle, uint8_t *data, uint32_t size);

int uart_intf_Read(uart_intf_handle_t handle, uint8_t *buff, uint32_t size);

int uart_intf_AddCallback(uart_intf_handle_t handle, uart_intf_callback_fun_t clbk_fun);

#endif