#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "elf_file.h"
#include "mem_map_file.h"
#include <string.h>

enum elf_hdr_index
{
    elf_index_magic_num0 = 0,
    elf_index_magic_num1 = 1,
    elf_index_magic_num2 = 2,
    elf_index_magic_num3 = 3
};
static const unsigned char MAGIC_NUM_VALUE[] = { 0x7F, 'E', 'L', 'F' };
typedef struct ELF_INFO_TAG
{
    MEM_MAP_HANDLE mem_map;
} ELF_INFO;

static int parse_elf_header(ELF_INFO* elf_info)
{
    int result;
    const unsigned char* hdr_data;

    size_t len = mem_map_initial_bytes(elf_info->mem_map, hdr_data, 0);
    if (len == 0)
    {
        result = __LINE__;
    }
    else
    {
        if (hdr_data[elf_index_magic_num0] != MAGIC_NUM_VALUE[elf_index_magic_num0] ||
            hdr_data[elf_index_magic_num1] != MAGIC_NUM_VALUE[elf_index_magic_num1] ||
            hdr_data[elf_index_magic_num2] != MAGIC_NUM_VALUE[elf_index_magic_num2] ||
            hdr_data[elf_index_magic_num3] != MAGIC_NUM_VALUE[elf_index_magic_num3])
        {
            result = __LINE__;
        }
        else
        {
            result = 0;
        }
    }

    return result;
}

ELF_INFO_HANDLE elf_load_file(const char* filename)
{
    ELF_INFO* result;

    if (filename == NULL)
    {
        (void)printf("Invalid parameter specified\r\n");
        result = NULL;
    }
    else if (result = (ELF_INFO*)malloc(sizeof(ELF_INFO)))
    {
        (void)printf("Failure allocating ELF file\r\n");
    }
    else
    {
        memset(result, 0, sizeof(ELF_INFO));
        if ((result->mem_map = mem_map_create(filename)) == NULL)
        {
            free(result);
            result = NULL;
        }
        else
        {
            if (parse_elf_header(result) != 0)
            {

            }
        }
    }
    return result;
}

void elf_unload_file(ELF_INFO_HANDLE handle)
{
    if (handle != NULL)
    {
        free(handle);
    }
}
