#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mem_map_file.h"

typedef struct MEM_MAP_TAG
{
    void* mapped_file;
    off_t file_size;
    char* data_mapped;

} MEM_MAP;

MEM_MAP_HANDLE mem_map_create(const char* filename)
{
    MEM_MAP* result;
    if (filename == NULL)
    {
        result = NULL;
    }
    else if (result = (MEM_MAP*)malloc(sizeof(MEM_MAP)))
    {
    }
    else
    {
        int file_desc;
        struct stat file_stat;
        memset(result, 0, sizeof(MEM_MAP));

        // Load the file 
        if ((file_desc = open(filename, O_RDONLY)) == -1)
        {
            printf("Unable to open file: %s", filename);
            free(result);
            result = NULL;
        }
        else
        {
            if (fstat(file_desc, &file_stat) == -1)
            {
                printf("Unable to get file info: %s", filename);
                free(result);
                result = NULL;
            }
            else if (!S_ISREG(file_stat.st_mode))
            {
                printf("Invalid elf file: %s", filename);
                free(result);
                result = NULL;
            }
            else if ((result->mapped_file = mmap(0, file_stat.st_size, PROT_READ, MAP_SHARED, file_desc, 0)) == MAP_FAILED)
            {
                printf("Invalid elf file: %s", filename);
                free(result);
                result = NULL;
            }
            else
            {
                result->file_size = file_stat.st_size;
            }
            close(file_desc);
        }
    }
    return result;
}

void mem_map_destroy(MEM_MAP_HANDLE handle)
{
    if (handle != NULL)
    {
        munmap(handle->mapped_file, handle->file_size);
        free(handle);
    }
}

size_t mem_map_initial_bytes(MEM_MAP_HANDLE handle, const unsigned char* data, size_t size_request)
{
    size_t result;
    if (handle == NULL || data == NULL || size_request == 0)
    {
        result = 0;
    }
    else 
    {
        if (size_request > handle->file_size)
        {
            result = handle->file_size;
        }
        else
        {
            result = size_request;
        }
        data = handle->mapped_file;
    }
    return result;
}