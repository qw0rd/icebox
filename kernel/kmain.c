#include <stdint.h>
#include <icebox/kprint.h>
#include <icebox/dtb.h>
#include <icebox/drivers/uart.h>
#include <libsbi/sbi.h>
#include <stdatomic.h>

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

[[gnu::noreturn, gnu::naked]] void boot_hart()
{
    asm(R"(
        mv a0, a0
        mv a1, a1
        li sp, 0xbf07d000
        mv fp, sp

        call start

    )");
}

void loop(uint64_t hartid) {
    while (1) {
            kprint("On hart #%d\n", hartid); 
    }
}

void start(uint64_t hartid, uint64_t opaque)
{
    kprint("Here ig");
    loop(hartid);
    while (1) {
        asm("li t1, 0xcafebabe");
    }
}

void print_hart_status(uint64_t value, int id, int* boot_hart_id)
{
    kprint("Hart #%d, ", id);
    switch (value) {
        case STARTED:
            kprint("Status: STARTED\n");
            if (boot_hart_id)
                *boot_hart_id = id;
            break;
        case STOPPED:
            kprint("Status: STOPPED\n");
            break;
        case START_PENDING:
            kprint("Status: START_PENDING\n");
            break;
        case STOP_PENDING:
            kprint("Status: STOP_PENDING\n");
            break;
        case SUSPENDED:
            kprint("Status: SUSPENDED\n");
            break;
        case SUSPEND_PENDING:
            kprint("Status: SUSPEND_PENDING\n");
            break;
        case RESUME_PENDING:
            kprint("Status: RESUME_PENDING\n");
            break;
    }
}

[[gnu::noreturn]] void kmain(struct boot_info info)
{
    init_uart();

    kprint("Dtb at: %lx\n", info.dtb);
    kprint("Getting hart info...\n");
    int hart_count = 0;

    int b_hart_id;
    while (1) {
        struct sbiret res = sbi_hart_get_status(hart_count);
        if (res.error == SBI_ERR_INVALID_PARAM) {
            break;
        }
        print_hart_status(res.value, hart_count, &b_hart_id);
        hart_count++;
    }

    kprint("Booted on hart #%d\n", b_hart_id);

    struct fdt_header hdr = get_header_from_addr(info.dtb);
    print_dtb_header_info(hdr);

    int next_hart_boot = 0;
    while (next_hart_boot == b_hart_id) {
        next_hart_boot++;
    }
    kprint("Will try to boot hart #%d\n", next_hart_boot);
    struct sbiret r = sbi_hart_start(next_hart_boot, (uintptr_t)&boot_hart, 0);
    if (r.error == SBI_SUCCESS) {
        kprint("Started hart: %d\n", next_hart_boot);
    }

    loop(b_hart_id);

    /*
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
    */

    while (1) {
        asm("li t0, 0xdeadbeef");
    }
}

