

set (SYNC_S_FILES
    spinlock.c)

target_sources(icebox 
    PRIVATE 
    ${SYNC_S_FILES})