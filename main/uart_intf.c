#include "uart_intf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <driver/uart.h>
#include <esp_err.h>

typedef struct uart_intf_tagConfig
{
    uint8_t uart_num;
    uart_intf_callback_fun_t clbk_fun;
    // TODO queue
    QueueHandle_t queue;

} uart_intf_config_t;

uart_intf_handle_t uart_intf_Init(uint8_t uart_num, uint16_t rx, uint16_t tx, uint32_t baud_rate, uint16_t rx_buffer, uint16_t tx_buffer)
{
    uart_intf_handle_t handle = malloc(sizeof(uart_intf_config_t));
    if (!handle)
    {
        printf("faield to init uart\n");
        return 0;
    }
    /* =============================== */

    const uart_config_t cfg = {
        .baud_rate = baud_rate,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
    };

    QueueHandle_t queue;
    ESP_ERROR_CHECK(uart_driver_install(uart_num, rx_buffer, tx_buffer, 10, &queue, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, tx, rx, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    /* =============================== */
    handle->uart_num = uart_num;
    handle->clbk_fun = NULL;
    handle->queue = queue;

    printf("uart_num->%d\n", handle->uart_num);
    printf("rx_buffer->%d\n", rx_buffer);
    printf("tx_buffer->%d\n", tx_buffer);

    return handle;
}

int uart_intf_Destroy(uart_intf_handle_t handle)
{
    if (handle)
    {
        ESP_ERROR_CHECK(uart_driver_delete(handle->uart_num));
        handle->clbk_fun = NULL;
        free(handle);
        return 1;
    }
    return 0;
}

int uart_intf_Write(uart_intf_handle_t handle, uint8_t *data, uint32_t size)
{
    printf("writing uart->%d data->%s size->%d \n", handle->uart_num, (const char *)data, size);
    uart_write_bytes(handle->uart_num, data, size);
    uart_wait_tx_done(handle->uart_num, portMAX_DELAY);
    return 0;
}

int uart_intf_Read(uart_intf_handle_t handle, uint8_t *buff, uint32_t size)
{
    printf("reading");
    uart_read_bytes(handle->uart_num, buff, size, portMAX_DELAY);
    return 0;
}

int uart_intf_AddCallback(uart_intf_handle_t handle, uart_intf_callback_fun_t clbk_fun)
{
    return 0;
}