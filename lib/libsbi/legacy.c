#include <libsbi/sbi.h>

void sbi_console_putchar(int ch)
{
    sbi_ecall(0x1, 0, (uint64_t)ch, 0, 0, 0, 0, 0);
}

int sbi_console_getchar()
{
    struct sbiret res = sbi_ecall(0x2, 0, 0, 0, 0, 0, 0, 0);
    return res.value;
}

