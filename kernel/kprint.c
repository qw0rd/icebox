#include <stddef.h>
#include <stdarg.h>
#include <icebox/drivers/uart.h>
#include <icebox/sync/spinlock.h>
#include <libk/string.h>
#include <icebox/kprint.h>
#include <stdint.h>
#include <stddef.h>
#include <stdatomic.h>

void kput_char(char c)
{
    uart_write_u8(c);
}


void kput_str(const char* str)
{
    size_t len = strlen(str);
    for (size_t i = 0;i < len;i++) {
        kput_char(str[i]);
    }
}

enum base {
    bin = 2,
    oct = 8,
    dec = 10, 
    hex = 16
};

static char buf[100];

#define len(T)                                      \
    int T##_len(T num, enum base b) {               \
        int len = 0;                                \
        while(num) {                                \
            num /= b;                               \
            len++;                                  \
        }                                           \
        return len;                                 \
    }                                               \


// int length
len(int)

// long length
len(long)

// uint length
len(uint32_t)

// ulong length
len(uint64_t)

const char chars[] = "0123456789abcdef";

#define to_str(T)                                       \
    const char* T##_to_str(T num, enum base b)          \
    {                                                   \
        if (num == 0) {                                 \
            buf[1] = 0;                                 \
            buf[0] = '0';                               \
            return buf;                                 \
        }                                               \
        T len = T##_len(num, b);                        \
        buf[len] = 0;                                   \
        while (num) {                                   \
            char c = chars[num % b];                    \
            buf[--len] = c;                             \
            num /= b;                                   \
        }                                               \
        return buf;                                     \
    }                                                   \

// int_to_str
to_str(int)

// long_to_str
to_str(long)

// uint32_to_str
to_str(uint32_t)

// uint64_to_str
to_str(uint64_t)

const char hex_prefix[2] = {'0', 'x'};

static struct spinlock lock = SPINLOCK_INIT;

void kprint(const char*fmt , ...)
{
    sl_lock(&lock);

    va_list args;
    va_start(args, fmt);
    
    char hex_buf[20];

    while (*fmt) {
        switch (*fmt) {
            case '%' : {
                fmt++;
                switch (*fmt) {
                    case 'l' : {
                        fmt++;
                        switch (*fmt) {
                            case 'b' : {
                                uint64_t b = va_arg(args, uint64_t);
                                kput_str("0b");
                                kput_str(uint64_t_to_str(b, bin));
                                break;
                            }
                            case 'u' : {
                                uint64_t num = va_arg(args, uint64_t);
                                kput_str(uint64_t_to_str(num, dec));
                                break;
                            }
                            case 'd' : {
                                long num = va_arg(args, long);
                                if (num < 0) {
                                    num = (~num) + 1;
                                    kput_char('-');
                                }
                                kput_str(long_to_str(num, dec));
                                break;
                            }
                            case 'x' : {
                                memcpy(hex_buf, hex_prefix, 2);
                                uint64_t num = va_arg(args, uint64_t);
                                const char* str = uint64_t_to_str(num, hex);
                                size_t len = strlen(str);
                                memcpy(&hex_buf[2], str, len);
                                hex_buf[len+2] = 0;
                                kput_str(hex_buf);
                                break;
                            }
                        }
                        break;

                    }
                    case 'd' : {
                        int num = va_arg(args, int);
                        if (num < 0) {
                            num = (~num) + 1;
                            kput_char('-');
                        }
                        kput_str(int_to_str(num, dec));
                        break;
                    }
                    case 'x' : {
                        memcpy(hex_buf, hex_prefix, 2);
                        unsigned int num = va_arg(args, unsigned int);
                        const char* str = uint32_t_to_str(num, hex);
                        size_t len = strlen(str);
                        memcpy(&hex_buf[2], str, len);
                        hex_buf[len+2] = 0;
                        kput_str(hex_buf);
                        break;
                    }
                case 's': {
                    kput_str(va_arg(args, const char*));
                    break;
                }
                }
                break;
            }
            default:
                kput_char(*fmt);
        }
        fmt++;
    }

    sl_release(&lock);
}



