#include <libsbi/sbi.h>


struct sbiret sbi_get_spec_version()
{
    struct sbiret res = sbi_ecall(0x10, 0x0, 0, 0, 0, 0, 0, 0);
    return res;
}