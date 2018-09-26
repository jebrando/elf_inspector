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

typedef enum ELF_BINARY_TYPE_TAG
{
    ELF_BIN_64BIT,
    ELF_BIN_32BIT,
    ELF_BIN_UNKNOWN
} ELF_BINARY_TYPE;

typedef enum ELF_OS_TYPE_TAG
{
    ELF_OS_SYSTEM_V = 0x00,
    ELF_OS_HP_UX = 0x01,
    ELF_OS_NETBSD = 0x02,
    ELF_OS_LINUX = 0x03,
    ELF_OS_GNU_Hurd = 0x04,
    ELF_OS_SOLARIS = 0x06,
    ELF_OS_AIX = 0x07,
    ELF_OS_IRIX = 0x08,
    ELF_OS_FREEBSD = 0x09,
    ELF_OS_TRU64 = 0x0A,
    ELF_OS_NOVELL_MODESTO = 0x0B,
    ELF_OS_OPENBSD = 0x0C,
    ELF_OS_OPENVMS = 0x0D,
    ELF_OS_NONSTOP_KERNEL = 0x0E,
    ELF_OS_AROS = 0x0F,
    ELF_OS_FENIX_OS = 0x10,
    ELF_OS_CLOUD_ABI = 0x11,
    ELF_OS_UNKNOWN
} ELF_OS_TYPE;

typedef enum ELF_OBJECT_TYPE_TAG
{
    ELF_OBJ_ET_NONE = 0x00,
    ELF_OBJ_ET_REL = 0x01,
    ELF_OBJ_ET_EXEC = 0x02,
    ELF_OBJ_ET_DYN = 0x03,
    ELF_OBJ_ET_CORE = 0x04,
    ELF_OBJ_ET_LOOS = 0xfe00,
    ELF_OBJ_ET_HIOS = 0xfeff,
    ELF_OBJ_ET_LOPROC = 0xff00,
    ELF_OBJ_ET_HIPROC = 0xffff,
    ELF_OBJ_UNKNOWN
} ELF_OBJECT_TYPE;

extern ELF_INFO_HANDLE elf_load_file(const char* filename);
extern void elf_unload_file(ELF_INFO_HANDLE handle);

extern ELF_BINARY_TYPE elf_binary_format(ELF_INFO_HANDLE handle);
extern bool elf_is_little_endian(ELF_INFO_HANDLE handle);
extern ELF_OS_TYPE elf_os_type(ELF_INFO_HANDLE handle);
extern ELF_OBJECT_TYPE elf_object_type(ELF_INFO_HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif  // ELF_INFO_H
