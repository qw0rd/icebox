
set(DRIVER_SRC
    uart.c)

target_sources(icebox
    PRIVATE 
    ${DRIVER_SRC})
