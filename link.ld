ENTRY(init_boot)

SECTIONS {
    
    . = 0x80200000;
    PROVIDE(_text_start = .);

    .text : {
        KEEP(*(.text));
        KEEP(*(.text.*));
    }

    . = ALIGN(4096);
    PROVIDE(_data_start = .);
    .data : {
        *(.data)
        *(.data.*)
    }

    . = ALIGN(4096);
    PROVIDE(_ro_data_start = .);
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }

    . = ALIGN(4096);
    PROVIDE(sdata_start = .);
    .sdata : { *(.sdata) }
    .debug : { *(.debug) }

    . = ALIGN(4096);
    PROVIDE(_stack_start = .);
    . += 0x4000;
    PROVIDE(_stack_top = .);

    /* Pages */
    . = ALIGN(4096);
    PROVIDE(pages_bottom = .);
}