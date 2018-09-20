#ifndef ELF_FILE_H
#define ELF_FILE_H

#ifdef __cplusplus
#include <cstddef>
extern "C" {
#else
#include <stdbool.h>
#include <stddef.h>
#endif

typedef struct ELF_FILE_TAG* ELF_FILE_HANDLE;


extern ELF_FILE_HANDLE load_file(const char* filename);
extern void unload_file(ELF_FILE_HANDLE handle);


#ifdef __cplusplus
}
#endif

#endif  // ELF_FILE_H
