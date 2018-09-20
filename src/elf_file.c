#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "elf_file.h"
#include "mem_map_file.h"
#include <string.h>

typedef struct ELF_FILE_TAG
{
    MEM_MAP_HANDLE elf_mem_handle;
} ELF_FILE;

ELF_FILE_HANDLE load_file(const char* filename)
{
    ELF_FILE* result;

    if (filename == NULL)
    {
        result = NULL;
    }
    else if (result = (ELF_FILE*)malloc(sizeof(ELF_FILE)))
    {
    }
    else
    {
        memset(result, 0, sizeof(ELF_FILE));
    }
    return result;
}

void unload_file(ELF_FILE_HANDLE handle)
{
    if (handle != NULL)
    {
        free(handle);
    }
}
