#ifndef __DWIN_H__
#define __DWIN_H__

#include <stdint.h>
#include <uart_intf.h>

#define DWIN_INTERNAL_BUFFER_SIZE (4)

/* ======================= configaration ======================= */

// #define DWIN_REQUIRED_CALLBACK
#define DWIN_REQUIRED_DEBUGGING

// TODO for statically allocate buffer in runtime
#define DWIN_RUNTIME_ALLOCATION_STATIC
#define DWIN_STATIC_BUFFER_SIZE (10)

#define DWIN_STATIC_BUFFER_MIN (10)

// TODO for runtime static buffer allocation
#if defined DWIN_RUNTIME_ALLOCATION_STATIC

#if !defined DWIN_STATIC_BUFFER_SIZE
#error undeifne DWIN_STATIC_BUFFER_SIZE
#endif

#if defined DWIN_STATIC_BUFFER_SIZE && DWIN_STATIC_BUFFER_SIZE < DWIN_STATIC_BUFFER_MIN
#error DWIN_STATIC_BUFFER_SIZE is to small,less than DWIN_STATIC_BUFFER_MIN
#endif

#endif

/* ============================================================= */

#ifdef DWIN_REQUIRED_CALLBACK
typedef void (*dwin_callback_fun_t)(uint8_t *data, uint32_t size, void const *field_ptr);
#endif

#define DWIN_GET_FIELD_COUNT(array) (sizeof(array) / sizeof(array[0]))

typedef enum dwin_tagType
{
    DWIN_TYPE_NONE = -1,
    DWIN_TYPE_INT = 0,
    DWIN_TYPE_LINT = 1,
    DWIN_TYPE_VP_L = 2,
    DWIN_TYPE_VP_H = 3,
    DWIN_TYPE_TEXT = 4,
    DWIN_TYPE_MAX,
} dwin_type_t;

typedef struct dwin_tagExtBuff
{
    uint8_t *buff_ptr;
    uint16_t buff_alloc_size;
    uint16_t buff_usage_size;
} dwin_extBuff_t;

typedef union dwin_tagBuffer
{
    uint8_t internal[DWIN_INTERNAL_BUFFER_SIZE];
    dwin_extBuff_t extrnal;
} dwin_buffer_t;

typedef struct dwin_tagField
{
    uint16_t vp_addr;
    dwin_type_t type;
    dwin_buffer_t buffer;
#ifdef DWIN_REQUIRED_CALLBACK
    uint16_t field_id;
    dwin_callback_fun_t clbk_fun;
#endif
} dwin_field_t;

// TODO remove this coment
/* this is opaque objct because user don not have any need to modify this object
 * also this objct can contain import instances to serial and field objects
 * it is importe to restrict access this thing from user
 *
 */

// TODO lesson 101 i can only define a pointer to a structure
typedef struct dwin_tagConfig *dwin_handle_t;

// typedef struct uart_intf_tagConfig *uart_intf_config_t;

dwin_handle_t dwin_Init(void);
int dwin_SetInterface(dwin_handle_t handle, uart_intf_handle_t intf);

#ifdef DWIN_REQUIRED_CALLBACK
int dwin_Register(dwin_handle_t handle, dwin_field_t field[], uint16_t count);
int dwin_Write(dwin_handle_t handle, uint16_t id, void *data);
int dwin_Read(dwin_handle_t handle, uint16_t id, void *data);
#else
int dwin_Write(dwin_handle_t handle, dwin_field_t *field, void *ptrToData);
int dwin_Read(dwin_handle_t handle, dwin_field_t const *field, void *data);
#endif

int dwin_Destroy(dwin_handle_t handle);

void dwin_PrintField(dwin_field_t const *field);

#endif
