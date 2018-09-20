#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.11)
project(elf_inspector)

#include("configs/analysisFunctions.cmake")


include(ExternalProject)

include_directories(./inc)

set(elf_inspect_h_files
    ./inc/elf_file.h
    ./inc/mem_map_file.h
)

set(elf_inspect_c_files
    ./main.c
    ./src/elf_file.c
)

if(WIN32)
    set(elf_inspect_c_files
        ${elf_inspect_c_files}
        ./src/mem_map_file_win.c
    )
else()
    set(elf_inspect_c_files
        ${elf_inspect_c_files}
        ./src/mem_map_file_linux.c
    )
endif()

add_executable(elf_inspector ${elf_inspect_c_files} ${elf_inspect_h_files})
