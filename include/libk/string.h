#pragma once
#include <stddef.h>
#include <stdint.h>


//!
//! The  memcpy()  function  copies n bytes from memory area src to memory area dest. The memory areas must not overlap.
//!
void *memcpy(void *restrict dest, const void *restrict src, size_t n);


//!
//! The  memcpy()  function  copies n bytes from memory area src to memory area dest. The memory areas must not overlap.
//!
size_t strlen(const char*);