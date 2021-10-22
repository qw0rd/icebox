
cmake_minimum_required(VERSION 3.21)


OPTION (DEBUG "Debug build with symbols" OFF)

project(Icebox
    DESCRIPTION "RISC-V Operating system"
    VERSION 0.1
    LANGUAGES C CXX ASM)

set (triple riscv64-elf)


set (CMAKE_C_COMPILER ${triple}-gcc)
set (CMAKE_CXX_COMPILER ${triple}-g++)



set (COMPILER_FLAGS
    -Wall
    -Wextra
    -pedantic

    # -Werror

    -march=rv64imad

    -mcmodel=medany

    -ffreestanding

    -std=gnu2x

    -O2
    )

if (DEBUG)
    set(COMPILER_FLAGS ${COMPILER_FLAGS} -g)
endif()

set (LINKER_FLAGS

    -mcmodel=medany

    -ffreestanding
    -nostdlib


    -T ${PROJECT_SOURCE_DIR}/link.ld)

add_subdirectory(lib)
add_subdirectory(kernel)
