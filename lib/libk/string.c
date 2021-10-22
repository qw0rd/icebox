#include <libk/string.h>
#include <stddef.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    uint8_t* _dest = dest;
    const uint8_t* _src = src;

    while (n--) {
        *_dest++ = *_src++;
    }

    return dest;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;

    return len;
}

