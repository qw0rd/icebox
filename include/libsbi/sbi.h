#pragma once
#include <stdint.h>

struct sbiret {
    unsigned long error;
    unsigned long value;
};

enum sbi_error {
    SBI_SUCCESS = 0,
    SBI_ERR_FAILED = -1,
    SBI_ERR_NOT_SUPPORTED = -2,
    SBI_ERR_INVALID_PARAM = -3,
    SBI_ERR_DENIED = -4,
    SBI_ERR_INVALID_ADDRESS = -5,
    SBI_ERR_ALREADY_AVAILABLE = -6,
    SBI_ERR_ALREADY_STARTED = -7,
    SBI_ERR_ALREADY_STOPPED = -8,
};

enum sbi_impl_id {
    BERKELEY_BOOT_LOADER = 0,
    OPEN_SBI,
    XVISOR,
    KVM,
    RUST_SBI,
    DIOSIX
};


/*
    Base extension SBI calls.

 */
struct sbiret sbi_ecall(int eid, int fid, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5);

struct sbiret sbi_get_spec_version();

struct sbiret sbi_get_sbi_impl_id();

struct sbiret sbi_get_sbi_impl_version();

struct sbiret sbi_probe_extension();

struct sbiret get_mvendorid();

struct sbiret get_marchid();

struct sbiret get_get_mimpid();

/*
    Legacy SBI calls.

 */
[[deprecated("This function is deprecated and there is no replacement. Refer the SBI spec.")]] void sbi_console_putchar(int ch);

[[deprecated("This function is deprecated and there is no replacement. Refer the SBI spec.")]] int sbi_console_getchar();

/*
    
    Hart management calls.

 */
enum hart_state {
    STARTED,
    STOPPED,
    START_PENDING,
    STOP_PENDING,
    SUSPENDED,
    SUSPEND_PENDING,
    RESUME_PENDING
};


struct sbiret sbi_hart_start(uint64_t hartid, uint64_t start_addr, uint64_t opaque);

struct sbiret sbi_hart_get_status(unsigned long hartid); 
