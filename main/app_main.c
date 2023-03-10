#include <stdio.h>
#include <string.h>

#include <freertos/FreeRtos.h>
#include <freertos/task.h>

#include <esp_timer.h>
#include <esp_err.h>
#include <esp_log.h>
#include <dwin.h>

static const char *TAG = "app_main";

static uint8_t my_buffer1[100];
static uint8_t my_buffer2[50];

static const dwin_field_t FIELD1 = {
    .vp_addr = 0x0010,
    .type = DWIN_TYPE_INT,
    .buffer.internal = {0}};

static const dwin_field_t FIELD2 = {
    .vp_addr = 0x0001,
    .type = DWIN_TYPE_TEXT,
    // .buffer.extrnal.buff_ptr = my_buffer,
    .buffer.extrnal.buff_alloc_size = sizeof(my_buffer1),
    // .buffer.external = my_buffer,
};

static const dwin_field_t FIELD3 = {
    .vp_addr = 0x2001,
    .type = DWIN_TYPE_TEXT,
    .buffer.extrnal.buff_ptr = my_buffer2,
    .buffer.extrnal.buff_alloc_size = sizeof(my_buffer2),
    // .buffer.external = my_buffer,
};

static dwin_field_t ARRAY_OF_FIELDS[3] = {
    FIELD1,
    FIELD2,
    FIELD3};

void app_main(void)
{
    ESP_LOGI(TAG, "dwin_field_t->%d bytes", sizeof(dwin_field_t));
    // ESP_LOGI(TAG, "dwin_type_t->%d bytes", sizeof(dwin_type_t));
    ESP_LOGI(TAG, "FIELD1->%d bytes", sizeof(FIELD1));
    ESP_LOGI(TAG, "FIELD2->%d bytes", sizeof(FIELD2));

    dwin_PrintField(&FIELD1);
    dwin_PrintField(&FIELD2);
    dwin_PrintField(&FIELD3);

    strncpy((char *)FIELD3.buffer.extrnal.buff_ptr, "fbvfbvjbfjvbjfbvjbfj", FIELD3.buffer.extrnal.buff_alloc_size);
    printf("conetnt->%s\n", (const char *)FIELD3.buffer.extrnal.buff_ptr);

    static dwin_handle_t handle;
    dwin_Init(handle);

    // xTaskCreate(Task1, "Task1", 2048, NULL, 2, NULL);
    // xTaskCreate(Task2, "Task2", 2048, NULL, 1, NULL);

    // xTaskCreatePinnedToCore(Task1, "Task1", 2048, NULL, 1, NULL,0);
    // xTaskCreatePinnedToCore(Task2, "Task2", 2048, NULL, 1, NULL,1);
}