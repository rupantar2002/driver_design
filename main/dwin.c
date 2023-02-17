#include <dwin.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* ============= DWIN UART PROTOCOL SPECIFIC ============= */
#define FRAME_HEADER_H (0x5A)
#define FRAME_HEADER_L (0xA5)
#define COMMAND_READ (0x83)
#define COMMAND_WRITE (0x83)
/* ======================================================= */
typedef struct dwin_tagConfig
{
#ifdef DWIN_REQUIRED_CALLBACK
    dwin_field_t *fields;
    uint16_t count;
#endif
    uart_intf_handle_t uart_handle;
} dwin_config_t;

// TODO with in debugging tag
static const char *GetType(dwin_type_t type);

static int WriteField(dwin_handle_t hdl, uint16_t vp_addr, uint8_t *data, uint32_t size);

// TODO with in callbcak tag

#ifdef DWIN_REQUIRED_CALLBACK
static dwin_field_t *GetField(uint16_t id, dwin_config_t *cfg);
#endif

// struct dwin_tagConfig
// {
//     int x;
//     int y;
// };

// typedef struct uart_intf_tagConfig
// {
//     int cjdj;
//     int djcjd;
// } uart_intf_cnfig_t;

int dwin_Init(dwin_handle_t handle)
{
    handle = malloc(sizeof(dwin_config_t));
    if (handle == NULL)
    {
        printf("failed to init\n");
        return false;
    }
#ifdef DWIN_REQUIRED_CALLBACK
    handle->count = 0;
    handle->fields = NULL;
#endif
    handle->uart_handle = NULL;
    return true;
}

int dwin_SetInterface(dwin_handle_t handle, uart_intf_handle_t intf)
{
    if (handle == NULL)
    {
        printf("invalid handle\n");
        return false;
    }

    if (intf == NULL)
    {
        printf("invalid uart handle\n");
        return false;
    }

    handle->uart_handle = intf;
    return true;
}

#ifdef DWIN_REQUIRED_CALLBACK
int dwin_Register(dwin_handle_t handle, dwin_field_t field[], uint16_t count)
{
    if (handle == NULL)
    {
        printf("invalid handle\n");
        return 0;
    }
    handle->fields = field;
    return 1;
}

int dwin_Write(dwin_handle_t handle, uint16_t id, void *data)
{
    dwin_field_t *pField = GetField(id, handle);

    switch (pField->type)
    {
    case DWIN_TYPE_INT:
        // TODO should be encapsulated in function
        {
            uint32_t val = *((uint32_t *)data);
        }
        break;
    case DWIN_TYPE_LINT:
        break;
    case DWIN_TYPE_VP_H:
        break;
    case DWIN_TYPE_VP_L:
        break;
    case DWIN_TYPE_TEXT:
        break;
    default:
        break;
    }

    return 0;
}

int dwin_Read(dwin_handle_t handle, uint16_t id, void *data) { return 0; }

#else

int dwin_Write(dwin_handle_t handle, dwin_field_t const *field, void *data)
{
    if (handle == NULL)
    {
        printf("invalid handle\n");
        return false;
    }

    if (field == NULL)
    {
        printf("invalid field\n");
        return false;
    }
    // uint8_t _buffer[4] = {0}, temp = false;
    // dwin_display_field_t *pField = dwin_display_GetField(id);
    // if (pField == NULL)
    // {
    //     PORT_LOGE(TAG, "field not found\r\n");
    //     return false;
    // }

    // switch (field->type)
    // {
    // case DWIN_TYPE_LINT:
    // {

    //     int32_t val = *(int32_t *)data;
    //     _buffer[0] = (val >> 24) & 0xff;
    //     _buffer[1] = (val >> 16) & 0xff;
    //     _buffer[2] = (val >> 8) & 0xff;
    //     _buffer[3] = val & 0xff;
    //     memcpy(pField->data, _buffer, sizeof(int32_t));
    //     temp = dwin_display_Write(pField->vpHigh, pField->vpLow, _buffer, sizeof(int32_t));
    // }
    // break;
    // case DWIN_TYPE_INT:
    // {
    //     int16_t val = *(int16_t *)data;
    //     _buffer[0] = (val >> 8) & 0xff;
    //     _buffer[1] = val & 0xff;
    //     memcpy(pField->data, _buffer, sizeof(int16_t));
    //     temp = dwin_display_Write(pField->vpHigh, pField->vpLow, _buffer, sizeof(int16_t));
    // }
    // break;
    // case DWIN_TYPE_TEXT:
    // {
    //     strncpy((char *)pField->data, data, pField->dataLen);
    //     temp = dwin_display_Write(pField->vpHigh, pField->vpLow, data, strlen(data));
    // }
    // break;
    // case DWIN_TYPE_VP_H:
    // {
    //     uint8_t val = *(uint16_t *)data;
    //     _buffer[0] = val;
    //     _buffer[1] = 0x00;
    //     memcpy(pField->data, _buffer, sizeof(uint16_t));
    //     temp = dwin_display_Write(pField->vpHigh, pField->vpLow, _buffer, sizeof(uint16_t));
    // }
    // break;
    // case DWIN_TYPE_VP_L:
    // {
    //     uint8_t val = *(uint16_t *)data;
    //     _buffer[0] = 0x00;
    //     _buffer[1] = val;
    //     memcpy(pField->data, _buffer, sizeof(uint16_t));
    //     temp = dwin_display_Write(pField->vpHigh, pField->vpLow, _buffer, sizeof(uint16_t));
    // }
    // break;
    // default:
    //     break;
    // }
    return 0;
}

int dwin_Read(dwin_handle_t handle, dwin_field_t const *field, void *data)
{
    if (field->type != DWIN_TYPE_TEXT)
    {
        uart_intf_Read(handle->uart_handle, field->buffer.internal, DWIN_INTERNAL_BUFFER_SIZE);
    }
    return 0;
}
#endif

void dwin_PrintField(dwin_field_t const *field)
{
    // field->vp_addr
    // field->type
    // field->buffer
    printf("\nfield->vp_addr->0X%04x\n", field->vp_addr);
    printf("field->type->%s\n", GetType(field->type));

    if (field->type == DWIN_TYPE_TEXT)
    {
        // field->buffer.extrnal.buff_ptr
        // field->buffer.extrnal.buff_alloc_size
        // field->buffer.extrnal.buff_usage_size
        printf("field->buffer.extrnal.buff_ptr->%p\n", field->buffer.extrnal.buff_ptr);
        printf("field->buffer.extrnal.buff_alloc_size->%d\n", field->buffer.extrnal.buff_alloc_size);
        printf("field->buffer.extrnal.buff_usage_size->%d\n", field->buffer.extrnal.buff_usage_size);
    }
}

const char *GetType(dwin_type_t type)
{
    char *temp = NULL;

    switch (type)
    {
    case DWIN_TYPE_INT:
        temp = "DWIN_TYPE_INT";
        break;
    case DWIN_TYPE_LINT:
        temp = "DWIN_TYPE_LINT";
        break;
    case DWIN_TYPE_VP_H:
        temp = "DWIN_TYPE_VP_H";
        break;
    case DWIN_TYPE_VP_L:
        temp = "DWIN_TYPE_VP_L";
        break;
    case DWIN_TYPE_TEXT:
        temp = "DWIN_TYPE_TEXT";
        break;
    default:
        temp = "undefine type";
        break;
    }
    return (const char *)temp;
}

#ifdef DWIN_REQUIRED_CALLBACK
static dwin_field_t *GetField(uint16_t id, dwin_config_t *cfg)
{
    int i;
    for (i = 0; i < cfg->count; i++)
    {
        if (cfg->fields[i].field_id == id)
        {
            return &(cfg->fields[i]);
        }
    }

    return NULL;
}
#endif

static int WriteField(dwin_handle_t hdl, uint16_t vp_addr, uint8_t *data, uint32_t size)
{
    // TODO both static and dynamic buffer aloocation scheme should be present

    // <FHH> <FHL> <BC> 82 <VP><VP> <VL1><VL1>

#ifdef DWIN_RUNTIME_ALLOCATION_STATIC
    uint8_t _command[DWIN_INTERNAL_BUFFER_SIZE];
#else
    uint8_t *_command = (uint8_t *)malloc(6 + size);
#endif
    uint16_t i, count = 0;

    _command[0] = FRAME_HEADER_H;
    _command[1] = FRAME_HEADER_L;
    _command[2] = (3 + size);
    _command[3] = COMMAND_WRITE;
    _command[4] = ((vp_addr << 8) & 0xff);
    _command[5] = (vp_addr & 0Xff);

    for (i = 6; i < size; i++)
    {
        _command[i] = data[count];
        count++;
    }
    // TODO needs implementation
    uart_intf_Write(hdl->uart_handle, data, size);

#ifndef DWIN_RUNTIME_ALLOCATION_STATIC
    free(_command);
#endif
    return 0;
}
