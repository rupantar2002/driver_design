#ifndef __DWIN_H__
#define __DWIN_H__

#include <stdint.h>

#define DWIN_INTERNAL_BUFFER_SIZE (4)

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
} dwin_field_t;

/* TODO needs definition */

#endif
