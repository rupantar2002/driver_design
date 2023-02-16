#include <uart_intf.h>
#include <stdio.h>
#include <stdlib.h>

#include <driver/uart.h>

typedef struct uart_intf_tagConfig
{
    uint8_t uart_num;
    uart_intf_callback_fun_t clbk_fun;
} uart_intf_config_t;

int uart_intf_Init(uart_intf_handle_t handle, uint8_t uart_num, uint16_t rx, uint16_t tx, uint32_t baud_rate)
{
    handle = malloc(sizeof(uart_config_t));
    if (handle == NULL)
    {
        printf("faield to init uart\n");
        return 0;
    }

    handle->uart_num = uart_num;
    handle->clbk_fun = NULL;
    return 1;
}

int uart_intf_Write(uart_intf_handle_t handle, uint8_t *data, uint32_t size)
{

    uart_write_bytes(handle->uart_num, data, size);
    return 0;
}

int uart_intf_Read(uart_intf_handle_t handle, uint8_t *buff, uint32_t size)
{
    uart_read_bytes(handle->uart_num, buff, size, 0);
    return 0;
}

int uart_intf_AddCallback(uart_intf_handle_t handle, uart_intf_callback_fun_t clbk_fun)
{
    return 0;
}