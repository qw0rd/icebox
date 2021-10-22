#include <libsbi/sbi.h>


struct sbiret sbi_get_spec_version()
{
    return sbi_ecall(0x10, 0x0, 0, 0, 0, 0, 0, 0);
}


struct sbiret sbi_get_sbi_impl_id()
{
    return sbi_ecall(0x10, 1, 0, 0, 0, 0, 0, 0);
}


struct sbiret sbi_get_sbi_impl_version()
{
    return sbi_ecall(0x10, 2, 0, 0, 0, 0, 0, 0);
}

struct sbiret sbi_probe_extension()
{
    return sbi_ecall(0x10, 3, 0, 0, 0, 0, 0, 0);
}

struct sbiret get_mvendorid()
{
    return sbi_ecall(0x10, 4, 0, 0, 0, 0, 0, 0);
}

struct sbiret get_marchid()
{
    return sbi_ecall(0x10, 5, 0, 0, 0, 0, 0, 0);
}

struct sbiret get_get_mimpid()
{
    return sbi_ecall(0x10, 6, 0, 0, 0, 0, 0, 0);
}

