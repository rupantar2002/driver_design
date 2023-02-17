#include <stdio.h>
#include <string.h>

#include <freertos/FreeRtos.h>
#include <freertos/task.h>

#include <esp_timer.h>
#include <esp_err.h>
#include <esp_log.h>

// #define DWIN_RUNTIME_ALLOCATION_STATIC
// #define DWIN_STATIC_BUFFER_SIZE (10)
// #include "dwin.h"

#include "uart_intf.h"

static const char *TAG = "app_main";

// static uint8_t my_buffer1[100];
// static uint8_t my_buffer2[50];

// static const dwin_field_t FIELD1 = {
//     .vp_addr = 0x0010,
//     .type = DWIN_TYPE_INT,
//     .buffer.internal = {0}};

// static const dwin_field_t FIELD2 = {
//     .vp_addr = 0x0001,
//     .type = DWIN_TYPE_TEXT,
//     // .buffer.extrnal.buff_ptr = my_buffer,
//     .buffer.extrnal.buff_alloc_size = sizeof(my_buffer1),
//     // .buffer.external = my_buffer,
// };

// static const dwin_field_t FIELD3 = {
//     .vp_addr = 0x2001,
//     .type = DWIN_TYPE_TEXT,
//     .buffer.extrnal.buff_ptr = my_buffer2,
//     .buffer.extrnal.buff_alloc_size = sizeof(my_buffer2),
//     // .buffer.external = my_buffer,
// };

// static dwin_field_t ARRAY_OF_FIELDS[3] = {
//     FIELD1,
//     FIELD2,
//     FIELD3};

const char *data = "I am sensing data to uart port fmvmv,' f,b ;f,b';f'b.f'b.'f. .fg bn;fg,bn;fbf,'b. ff ";

void app_main(void)
{
    /* creating uart intf handle */
    uart_intf_handle_t uartHdl = uart_intf_Init(1, 18, 19, 115200, 200, 200);
    uart_intf_Write(uartHdl, (uint8_t *)data, strlen(data));

    uint8_t buff[200];

    // uart_intf_Write(uartHdl, (uint8_t *)"vcdcjhbdjcbj", 20);

    /* creating dwin display handle */
    // dwin_handle_t displayHdl = NULL;
    // dwin_Init(displayHdl);

    /* destroying handle after use */
    // dwin_Destroy(displayHdl);
    while (1)
    {
        uart_intf_Read(uartHdl, buff, sizeof(buff));
        printf("received-> %s\n", (const char *)buff);
        uart_intf_Write(uartHdl, buff, strlen((const char *)buff));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    uart_intf_Destroy(uartHdl);
}