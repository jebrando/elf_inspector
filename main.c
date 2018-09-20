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
    return result;
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
        result = 0;
    }
    return result;
}
