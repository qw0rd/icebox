
set (SRC_FILES
    dtb.c
    kprint.c
    kmain.c)

add_executable(icebox ${SRC_FILES})

set_target_properties(icebox
    PROPERTIES
    SUFFIX .elf
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_subdirectory(drivers)
add_subdirectory(sync)

target_link_libraries(icebox 
    PRIVATE 
    k 
    sbi
    m
    gcc)

target_compile_options(icebox PRIVATE ${COMPILER_FLAGS})
target_link_options(icebox PRIVATE ${LINKER_FLAGS})

target_include_directories(icebox PRIVATE
    ${PROJECT_SOURCE_DIR}/include)
