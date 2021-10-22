#include <libsbi/sbi.h>

#define EID 0x48534D

struct sbiret sbi_hart_start(uint64_t hartid, uint64_t start_addr, uint64_t opaque)
{
    return sbi_ecall(EID, 0, hartid, start_addr, opaque, 0, 0, 0);
}

struct sbiret sbi_hart_get_status(unsigned long hartid)
{
    return sbi_ecall(EID, 2, hartid, 0, 0, 0, 0, 0);
}
