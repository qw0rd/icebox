#pragma once

#include <stdint.h>
#include <stdatomic.h>

typedef volatile uint8_t u8_reg;

struct ns16550 {
    // the transmitter and receive buffer register.
    u8_reg tx_rv_reg; 

    // interrupt enable register.
    u8_reg int_en_reg;

    // interrupt ident and FIFO control reg.
    u8_reg int_idt_fifo_ctrl_reg;

    // line ctrl register.
    u8_reg line_ctrl_reg;

    // modem control register.
    u8_reg modem_ctrl_reg;

    // line status register
    u8_reg line_stat_reg;

    // modem status register.
    u8_reg modem_stat_reg;

    // scratch register
    u8_reg scratch_reg;
};


_Static_assert(sizeof(struct ns16550) == 8, "The struct should be 8 bytes");

typedef struct ns16550 ns16550;

void uart_write_u8(uint8_t data);

[[nodiscard]] uint8_t uart_read_u8();


void init_uart();


