// 
// This file contains the driver for NS16550 uart.
// 
// The UART is memory mapped to the address`0x10000000` QEMU-RISCV virt machine.
// Refer: https://www.scs.stanford.edu/10wi-cs140/pintos/specs/pc16550d.pdf

#include <stdint.h>
#include <icebox/drivers/uart.h>
#include <stdbool.h>

#define _UART_ADDR 0x10000000

struct ns16550* const serial = (struct ns16550*)(_UART_ADDR);


// initialize the uart.
void init_uart()
{

}

uint8_t uart_read_u8()
{

}

void uart_write_u8(uint8_t data)
{
    serial->tx_rv_reg = data;
}
