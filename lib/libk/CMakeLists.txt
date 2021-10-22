
set (SRC_FILES
    string.c)

add_library(k STATIC ${SRC_FILES})


target_compile_options(k PRIVATE ${COMPILER_FLAGS})
target_link_options(k PRIVATE ${LINKER_FLAGS})

target_include_directories(k 
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/include)
