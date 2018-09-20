#ifndef MEM_MAP_FILE_H
#define MEM_MAP_FILE_H

#ifdef __cplusplus
#include <cstddef>
extern "C" {
#else
#include <stddef.h>
#endif

typedef struct MEM_MAP_TAG* MEM_MAP_HANDLE;


extern MEM_MAP_HANDLE create_mem_map(const char* filename);
extern void destroy_mem_map(MEM_MAP_HANDLE handle);


#ifdef __cplusplus
}
#endif

#endif  // MEM_MAP_FILE_H
