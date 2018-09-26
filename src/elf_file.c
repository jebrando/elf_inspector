#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "elf_file.h"
#include "mem_map_file.h"
#include <string.h>

enum elf_hdr_index
{
    elf_index_magic_num0 = 0,
    elf_index_magic_num1 = 1,
    elf_index_magic_num2 = 2,
    elf_index_magic_num3 = 3,
    elf_index_class = 4,
    elf_index_byte_order = 5,
    elf_index_version = 6,
    elf_index_os_abi = 7,
    elf_index_abi_version = 8,
    elf_index_padding = 9,
    elf_index_obj_type = 16
};

static const unsigned char MAGIC_NUM_VALUE[] = { 0x7F, 'E', 'L', 'F' };
# define ELF_DATA2_LSB    1  // Little Endian
# define ELF_CLASS_32     1  // 32-bit Architecture

typedef struct ELF_HEADER_INFO_TAG
{
    bool arch_64bit;
    bool byte_order_little;
    uint32_t version;
    uint32_t abi_os;
    uint16_t object_type;
} ELF_HEADER_INFO;

typedef struct ELF_INFO_TAG
{
    MEM_MAP_HANDLE mem_map;
    ELF_HEADER_INFO hdr_info;
    uint64_t file_len;
} ELF_INFO;

static int parse_elf_header(ELF_INFO* elf_info)
{
    int result;
    const unsigned char* hdr_data;

    elf_info->file_len = mem_map_initial_bytes(elf_info->mem_map, &hdr_data, 10);
    if (elf_info->file_len == 0)
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
            elf_info->hdr_info.arch_64bit = (hdr_data[elf_index_class] != ELF_CLASS_32);
            elf_info->hdr_info.byte_order_little = (hdr_data[elf_index_byte_order] == ELF_DATA2_LSB);
            elf_info->hdr_info.abi_os = hdr_data[elf_index_os_abi];
            elf_info->hdr_info.object_type = hdr_data[elf_index_obj_type];
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
    else if ((result = (ELF_INFO*)malloc(sizeof(ELF_INFO))) == NULL)
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
                mem_map_destroy(result->mem_map);
                free(result);
                result = NULL;
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

ELF_BINARY_TYPE elf_binary_format(ELF_INFO_HANDLE handle)
{
    ELF_BINARY_TYPE bin_type;
    if (handle == NULL)
    {
        bin_type = ELF_BIN_UNKNOWN;
    }
    else if (handle->hdr_info.arch_64bit)
    {
        bin_type = ELF_BIN_64BIT;
    }
    else
    {
        bin_type = ELF_BIN_32BIT;
    }
    return bin_type;
}

bool elf_is_little_endian(ELF_INFO_HANDLE handle)
{
    bool result;
    if (handle != NULL)
    {
        result = handle->hdr_info.byte_order_little;
    }
    else
    {
        result = false;
    }
    return result;
}

ELF_OS_TYPE elf_os_type(ELF_INFO_HANDLE handle)
{
    ELF_OS_TYPE type;
    if (handle == NULL)
    {
        type = ELF_OS_UNKNOWN;
    }
    else
    {
        switch (handle->hdr_info.abi_os)
        {
            case ELF_OS_SYSTEM_V:
            case ELF_OS_HP_UX:
            case ELF_OS_NETBSD:
            case ELF_OS_LINUX:
            case ELF_OS_GNU_Hurd:
            case ELF_OS_SOLARIS:
            case ELF_OS_AIX:
            case ELF_OS_IRIX:
            case ELF_OS_FREEBSD:
            case ELF_OS_TRU64:
            case ELF_OS_NOVELL_MODESTO:
            case ELF_OS_OPENBSD:
            case ELF_OS_OPENVMS:
            case ELF_OS_NONSTOP_KERNEL:
            case ELF_OS_AROS:
            case ELF_OS_FENIX_OS:
            case ELF_OS_CLOUD_ABI:
                type = handle->hdr_info.abi_os;
                break;
            case ELF_OS_UNKNOWN:
            default:
                type = ELF_OS_UNKNOWN;
                break;
        }
    }
    return type;
}

ELF_OBJECT_TYPE elf_object_type(ELF_INFO_HANDLE handle)
{
    ELF_OBJECT_TYPE result;
    if (handle == NULL)
    {
        result = ELF_OBJ_UNKNOWN;
    }
    else
    {
    }
    return result;
}