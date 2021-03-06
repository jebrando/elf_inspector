#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elf_file.h"

typedef struct CMD_LINE_INFO_TAG
{
    const char* elf_file;
} CMD_LINE_INFO;

typedef struct ELF_INSPECTOR_INFO_TAG
{
    ELF_INFO_HANDLE elf_handle;
} ELF_INSPECTOR_INFO;

typedef enum ARGUEMENT_TYPE_TAG
{
    ARGUEMENT_TYPE_UNKNOWN,
    ARGUEMENT_TYPE_ELF_FILE
} ARGUEMENT_TYPE;

static const char* get_object_type(ELF_OBJECT_TYPE type)
{
    const char* result;
    switch (type)
    {
        case ELF_OBJ_ET_NONE:
            result = "none";
            break;
        case ELF_OBJ_ET_REL:
            result = "";
            break;
        case ELF_OBJ_ET_EXEC:
            result = "";
            break;
        case ELF_OBJ_ET_DYN:
            result = "";
            break;
        case ELF_OBJ_ET_CORE:
            result = "";
            break;
        case ELF_OBJ_ET_LOOS:
            result = "";
            break;
        case ELF_OBJ_ET_HIOS:
            result = "";
            break;
        case ELF_OBJ_ET_LOPROC:
            result = "";
            break;
        case ELF_OBJ_ET_HIPROC:
            result = "";
            break;
        case ELF_OBJ_UNKNOWN:
        default:
            result = "Unknown";
            break;
    }
}

static void show_elf_header(ELF_INSPECTOR_INFO* elf_info)
{
    ELF_BINARY_TYPE type = elf_binary_format(elf_info->elf_handle);
    (void)printf("Architecture:\t%s\r\n", (type == ELF_BIN_64BIT) ? "64-bit" : (type == ELF_BIN_32BIT) ? "32-bit" : "unknown");
    (void)printf("Byte Order:\t%s\r\n", elf_is_little_endian(elf_info->elf_handle) ? "little endian" : "big endian");

}

static int parse_command_line(int argc, char* argv[], CMD_LINE_INFO* cmd_info)
{
    int result = 0;
    ARGUEMENT_TYPE argument_type = ARGUEMENT_TYPE_UNKNOWN;

    for (int index = 0; index < argc; index++)
    {
        if (argument_type == ARGUEMENT_TYPE_UNKNOWN)
        {
            if (argv[index][0] == '-' && (argv[index][1] == 'f' || argv[index][1] == 'F'))
            {
                argument_type = ARGUEMENT_TYPE_ELF_FILE;
            }
        }
        else
        {
            switch (argument_type)
            {
                case ARGUEMENT_TYPE_ELF_FILE:
                    cmd_info->elf_file = argv[index];
                    break;
                case ARGUEMENT_TYPE_UNKNOWN:
                default:
                    result = __LINE__;
                    break;
            }
            argument_type = ARGUEMENT_TYPE_UNKNOWN;
        }
    }

    if (cmd_info->elf_file == NULL)
    {
        result = __LINE__;
    }
    return result;
}

static void process_commands(ELF_INSPECTOR_INFO* elf_info)
{

}

// elf_inspector -c <filename>
int main(int argc, char* argv[])
{
    int result;
    CMD_LINE_INFO cmd_info;
    ELF_INSPECTOR_INFO elf_info;
    memset(&cmd_info, 0, sizeof(CMD_LINE_INFO));
    memset(&elf_info, 0, sizeof(ELF_INSPECTOR_INFO));

    if (parse_command_line(argc, argv, &cmd_info) != 0)
    {
        (void)printf("Failure parsing command line\r\n");
        result = __LINE__;
    }
    else if ((elf_info.elf_handle = elf_load_file(cmd_info.elf_file)) == NULL)
    {
        (void)printf("Failure parsing command line\r\n");
        result = __LINE__;
    }
    else
    {
        show_elf_header(&elf_info);

        process_commands(&elf_info);

        elf_unload_file(elf_info.elf_handle);

        result = 0;
    }
    return result;
}
