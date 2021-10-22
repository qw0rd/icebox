#include <stdint.h>
#include <icebox/kprint.h>
#include <icebox/dtb.h>
#include <icebox/drivers/uart.h>
#include <libsbi/sbi.h>


[[gnu::naked]] void init_boot()
{
    asm(R"(
        # load the stack pointer
        la sp, _stack_top
        mv fp, sp

        # pass in dtb addr to `early_kmain`
        mv a0, a1

        call early_kmain
     )");
}

struct boot_info {
    // the address of dtb.
    uintptr_t dtb;
};

[[gnu::noreturn]] void kmain(struct boot_info info);

struct boot_info early_kmain(uintptr_t dtb)
{
    struct boot_info info;
    info.dtb = dtb;

    kmain(info);

}

__attribute__((noreturn)) void kmain(struct boot_info info)
{
    init_uart();

    kput_str("Hello, world\n");

    kprint("My age is %d. The hex number is %x\n. Will it print zero: %x\n", 20, 0xdead, 0);
    kprint("Pretty good at negative i see. It is %dC out there lmao.\n", -69);

    kprint("2**32 is %d\n", 2147483648);
    kprint("2**32 is %ld\n", 4294967296);

    kprint("The number 4 in binary is: %lb\n", 4);

    kprint("The 2**64 is %lx\n", 18446744073709551615lu);

    struct fdt_header hdr = get_header_from_addr(info.dtb);
    print_dtb_header_info(hdr);

    struct sbiret version = sbi_get_spec_version();
    uint64_t val = version.value;

    int major = val >> 24;
    int minor = val & 0xffffff;

    kprint("SBI version: %d.%d\n", major, minor);
    struct sbiret id = sbi_get_sbi_impl_id();

    switch (id.value) {
        case OPEN_SBI:
            kprint("SBI Impl: OpenSBI");
            break;
    }

    while (1) {
        asm("li t0, 0xdeadbeef");
    }
}

