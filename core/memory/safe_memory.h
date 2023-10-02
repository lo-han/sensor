#ifndef __SAFE_MEMORY_H__
#define __SAFE_MEMORY_H__

#include <stdint.h>

/********************************************************************
 * Enumeration errors returned by memory management functions.
 ********************************************************************/
typedef enum mem_err
{
    _err_error = -1,
    _err_no_error
} Safe_mem_err;

/********************************************************************
 * This function is a safety reinforcement for memory allocations in heap,
 * used all across the code and for buffer initialization.
 * 
 * Functionality:
 * - Allocate a given NULL buffer;
 * - Check if the memory manipulation was successful;
 * - Fill the newly allocated buffer with '0'
 *
 * Inputs:
 *  - Pointer to pointer referencing a NULL location (void **ptr)
 *  - Buffer size (int32_t size)
 * Output:
 *  - Memory management error enum
 ********************************************************************/
Safe_mem_err safe_malloc(void **ptr, int32_t size);

/********************************************************************
 * This function is a safety reinforcement for memory deallocations in heap.
 * 
 * Functionality:
 * - Fill the newly allocated buffer with '0';
 * - Dellocate a given non NULL buffer;
 *
 * Inputs:
 *  - Pointer to pointer referencing a non NULL location (void **ptr)
 *  - Buffer size (int32_t size)
 ********************************************************************/
void safe_free_alloc(void **ptr, int32_t size);

#endif
