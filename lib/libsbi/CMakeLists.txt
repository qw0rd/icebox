

set (FILES
    base.c
    sbi.c)

add_library(sbi STATIC ${FILES})

target_compile_options(sbi PRIVATE ${COMPILER_FLAGS})

target_include_directories(sbi PRIVATE ${PROJECT_SOURCE_DIR}/include)
