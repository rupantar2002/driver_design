#include <dwin.h>
#include <stdio.h>
#include <stdlib.h>

/* ============= DWIN UART PROTOCOL SPECIFIC ============= */
#define FRAME_HEADER_H (0x5A)
#define FRAME_HEADER_L (0xA5)
#define COMMAND_READ (0x83)
#define COMMAND_WRITE (0x83)
/* ======================================================= */
typedef struct dwin_tagConfig
{
    dwin_field_t *fields;
    uint16_t count;
    // TODO should have a uart instance
} dwin_config_t;

// TODO with in debugging tag
static const char *GetType(dwin_type_t type);
static int Write();

// TODO with in callbcak tag
static dwin_field_t *GetField(uint16_t id, dwin_config_t *cfg);

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
        return 0;
    }
    return 1;
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
    return 0;
}
int dwin_Read(dwin_handle_t handle, dwin_field_t const *field, void *data) { return 0; }
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

static int Write()
{

    // uint8_t count = 0, i = 0, byteCount;
    // byteCount = 6 + size;
    // uint8_t cmd[DWIN_DISPLAY_MAX_DATA_LENGTH + 6];

    // cmd[0] = FRAME_HEADER_H;
    // cmd[1] = FRAME_HEADER_L;
    // cmd[2] = (3 + size);
    // cmd[3] = COMMONA_WRITE;
    // cmd[4] = vpH;
    // cmd[5] = vpL;
    // for (i = 6; i < byteCount; i++)
    // {
    //     cmd[i] = data[count];
    //     count++;
    // }
    // port_uart_Write(cmd, byteCount);

    return 0;
}
