#include <dwin.h>
#include <stdio.h>

static const char *GetType(dwin_type_t type);

void dwin_PrintField(dwin_field_t *field)
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