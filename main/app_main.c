#include <stdio.h>
#include <string.h>

#include <freertos/FreeRtos.h>
#include <freertos/task.h>

#include <esp_timer.h>
#include <esp_err.h>
#include <esp_log.h>

#include "uart_intf.h"

#define DWIN_RUNTIME_ALLOCATION_STATIC
#define DWIN_STATIC_BUFFER_SIZE (10)
#include "dwin.h"

static const char *TAG = "app_main";

static uint8_t my_buffer1[100];
// static uint8_t my_buffer2[50];

static dwin_field_t FIELD1 = {
    .vp_addr = 0x000a,
    .type = DWIN_TYPE_LINT,
    .buffer.internal = {0}};

static dwin_field_t FIELD2 = {
    .vp_addr = 0x001a,
    .type = DWIN_TYPE_LINT,
    .buffer.internal = {0}};

// static const dwin_field_t FIELD2 = {
//     .vp_addr = 0x0001,
//     .type = DWIN_TYPE_TEXT,
//     .buffer.extrnal.buff_ptr = my_buffer,
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

const char *data = "I am sensing data to uart port\r\n";

void app_main(void)
{
    int64_t startMicro;
    int64_t deltaMicro;

    /* creating uart intf handle */
    uart_intf_handle_t uartHdl1 = uart_intf_Init(1, 18, 19, 115200, 200, 200);
    uart_intf_handle_t uartHdl2 = uart_intf_Init(2, 13, 12, 115200, 200, 200);

    // uart_intf_Write(uartHdl1, (uint8_t *)data, strlen(data));
    // uart_intf_Write(uartHdl2, (uint8_t *)data, strlen(data));

    uint8_t buff[200];

    // uart_intf_Write(uartHdl, (uint8_t *)"vcdcjhbdjcbj", 20);

    /* creating dwin display handle */
    dwin_handle_t displayHdl = dwin_Init();
    dwin_SetInterface(displayHdl, uartHdl2);

    int32_t temp = 0xaabbccdd;
    startMicro = esp_timer_get_time();
    dwin_Write(displayHdl, &FIELD1, &temp);
    deltaMicro = esp_timer_get_time() - startMicro;
    printf("deltaTick->%lld\n", deltaMicro);

    temp = 0xfffffff;
    startMicro = esp_timer_get_time();
    dwin_Write(displayHdl, &FIELD2, &temp);
    deltaMicro = esp_timer_get_time() - startMicro;
    printf("deltaTick->%lld\n", deltaMicro);
    /* destroying handle after use */
    dwin_Destroy(displayHdl);

    uart_intf_Destroy(uartHdl1);
    uart_intf_Destroy(uartHdl2);
}