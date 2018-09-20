#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <Windows.h>

#include "mem_map_file.h"

typedef struct MEM_MAP_TAG
{
    HANDLE file_handle;
    HANDLE mapped_file;
    LPVOID data_mapped;
} MEM_MAP;

#define BUF_SIZE    65536

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
        HANDLE file_handle;
        memset(result, 0, sizeof(MEM_MAP));

        if ((file_handle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
        {
            printf("Unable to open file: %s", filename);
            free(result);
            result = NULL;
        }
        else
        {
            LARGE_INTEGER file_size = { 0 };
            GetFileSizeEx(file_handle, &file_size);
            __int64 cbFile = file_size.QuadPart;

            if ((result->mapped_file = CreateFileMappingA(file_handle, NULL, PAGE_READONLY, 0, 0, NULL)) != NULL)
            {
                printf("unable to map file: %s", filename);
                free(result);
                result = NULL;
            }
            else
            {
                /*for (unsigned long long offset = 0; offset < cbFile; offset += cbView) {
        DWORD high = static_cast<DWORD>((offset >> 32) & 0xFFFFFFFFul);
        DWORD low  = static_cast<DWORD>( offset        & 0xFFFFFFFFul);
        // The last view may be shorter.
        if (offset + cbView > cbFile) {
          cbView = static_cast<int>(cbFile - offset);
        }
        const char *pView = static_cast<const char *>(
            ::MapViewOfFile(hmap, FILE_MAP_READ, high, low, cbView));
        if (pView != NULL) {
          ProcessChunk(pView, cbView);
        }
      }*/
            }
        }
    }
    return result;
}

void mem_map_destroy(MEM_MAP_HANDLE handle)
{
    if (handle != NULL)
    {
        CloseHandle(handle->mapped_file);
        CloseHandle(handle->file_handle);
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
        handle->data_mapped = MapViewOfFile(handle->data_mapped, FILE_MAP_READ, 0, 0, BUF_SIZE);
        if (handle->data_mapped == NULL)
        {
            result = 0;
        }
        else
        {
            result = BUF_SIZE;
        }
    }
    return result;
}
