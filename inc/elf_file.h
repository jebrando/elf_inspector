#ifndef ELF_INFO_H
#define ELF_INFO_H

#ifdef __cplusplus
#include <cstddef>
extern "C" {
#else
#include <stdbool.h>
#include <stddef.h>
#endif

typedef struct ELF_INFO_TAG* ELF_INFO_HANDLE;


extern ELF_INFO_HANDLE elf_load_file(const char* filename);
extern void elf_unload_file(ELF_INFO_HANDLE handle);


#ifdef __cplusplus
}
#endif

#endif  // ELF_INFO_H
