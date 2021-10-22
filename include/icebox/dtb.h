#pragma once
#include <stdint.h>

//!
//! Very nice structure imo.
//!
struct fdt_header {
    uint32_t magic; /// The dtb magic number. It should contain the value `0xd00dfeed` in big-endian.

    uint32_t totalsize; /// The total size of the blob including the header.

    uint32_t off_dt_struct; /// offset of the dt_struct from the header.

    uint32_t off_dt_strings; /// 
    uint32_t off_mem_rsvmap;

    uint32_t version; /// version of dtb. It should be `17`.
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
};

struct fdt_header get_header_from_addr(uintptr_t addr);

void print_dtb_header_info(struct fdt_header);