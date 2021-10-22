#include <stdint.h>
#include <icebox/dtb.h>
#include <icebox/kprint.h>


struct fdt_header get_header_from_addr(uintptr_t addr)
{
    struct fdt_header hdr = *((struct fdt_header*)addr);


    // reverse the byte order for sanity.
    // fuck the spec for using big endian
    // SMH
    hdr.magic = __builtin_bswap32(hdr.magic);
    hdr.totalsize = __builtin_bswap32(hdr.totalsize);
    hdr.off_dt_struct = __builtin_bswap32(hdr.off_dt_struct);
    hdr.off_dt_strings = __builtin_bswap32(hdr.off_dt_strings);
    hdr.off_mem_rsvmap = __builtin_bswap32(hdr.off_mem_rsvmap);
    hdr.version = __builtin_bswap32(hdr.version);
    hdr.last_comp_version = __builtin_bswap32(hdr.last_comp_version);
    hdr.boot_cpuid_phys = __builtin_bswap32(hdr.boot_cpuid_phys);
    hdr.size_dt_strings = __builtin_bswap32(hdr.size_dt_strings);
    hdr.size_dt_struct = __builtin_bswap32(hdr.size_dt_struct);

    return hdr;
}


void print_dtb_header_info(struct fdt_header hdr)
{
    kprint("------DTB Header-----\n");
    kprint("Magic: %x\n", hdr.magic);
    kprint("Totalsize: %d bytes\n", hdr.totalsize);
    kprint("dt_struct offset: %d\n", hdr.off_dt_struct);
    kprint("dt_strings offset: %d\n", hdr.off_dt_strings);
    kprint("mem_rsvmap offset: %d\n", hdr.off_mem_rsvmap);
    kprint("version: %d\n", hdr.version);
    kprint("last_comp_version: %d\n", hdr.last_comp_version);
    kprint("boot_cpuid_phys: %d\n", hdr.boot_cpuid_phys);
    kprint("dt_strings size: %d bytes\n", hdr.size_dt_strings);
    kprint("dt_struct size: %d bytes\n", hdr.size_dt_struct);
    kprint("------DTB Header-----\n");
}
