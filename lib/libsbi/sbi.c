#include <libsbi/sbi.h>


struct sbiret sbi_ecall(int eid, int fid, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5)
{
    struct sbiret ret;
    register int a7 asm("a7") = eid;
    register int a6 asm("a6") = fid;

    register uint64_t a0 asm("a0") = arg0;
    register uint64_t a1 asm("a1") = arg1;
    register uint64_t a2 asm("a2") = arg2;
    register uint64_t a3 asm("a3") = arg3;
    register uint64_t a4 asm("a4") = arg4;
    register uint64_t a5 asm("a5") = arg5;

    asm volatile ("ecall"
        : "+r" (a0), "+r"(a1)
        : "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a6), "r"(a7));

    ret.error = a0;
    ret.value = a1;

    return ret;
}

