#ifndef DMM_MAIN_H
#define DMM_MAIN_H

// REQUIREMENTS: Requires size_t (stddef.h), uint32_t (stdint.h).

#include <stddef.h>
#include <stdint.h>

#define DMM_HEADER_MAGIC 0x99A3E7D6

typedef void *(DMM_MallocFn)(size_t size);
typedef void (DMM_FreeFn)(void *ptr);
typedef void *(DMM_ReallocFn)(void *ptr, size_t size);

typedef struct dmm_malloc_header_s {
    uint32_t magic;
    size_t size;
    size_t used; // A bit space-inefficient, but means we only require one type.
    void *data;
    struct dmm_malloc_header_s *next;
} DMM_MallocHeader;

#define DMM_UNASSIGNED_REGION NULL

typedef struct dmm_memory_manager_functions_s {
    DMM_MallocFn *malloc;
    DMM_FreeFn *free;
    DMM_ReallocFn *realloc;
} DMM_MemoryManagerFunctions;

DMM_MallocHeader *dmm_get_first_free_chunk(size_t size);

#endif