#include "safe_memory.h"

#include <stdlib.h>
#include <string.h>

Safe_mem_err safe_malloc(void **ptr, int32_t size)
{
    if (ptr == NULL || (*ptr != NULL && size <= 0))
    {
        return _err_error;
    }

    *ptr = malloc(size);

    if (*ptr == NULL)
    {
        return _err_error;
    }

    void *buffer = *ptr;
    memset(buffer, 0x00, size);
    return _err_no_error;
}

void safe_free_alloc(void **ptr, int32_t size)
{
    if (ptr != NULL)
    {
        if (*ptr != NULL)
        {
            free(*ptr);
            *ptr = NULL;
        }
    }
}
