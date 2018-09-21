#ifndef MEM_MAP_FILE_H
#define MEM_MAP_FILE_H

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
extern "C" {
#else
#include <stddef.h>
#include <stdint.h>
#endif

typedef struct MEM_MAP_TAG* MEM_MAP_HANDLE;

extern MEM_MAP_HANDLE mem_map_create(const char* filename);
extern void mem_map_destroy(MEM_MAP_HANDLE handle);
extern uint64_t mem_map_initial_bytes(MEM_MAP_HANDLE handle, const unsigned char** data, size_t size_request);

#ifdef __cplusplus
}
#endif

#endif  // MEM_MAP_FILE_H
