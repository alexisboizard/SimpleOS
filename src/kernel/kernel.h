#pragma once
#include <stddef.h>
#include <stdint.h>

void term_init(void);
void _print_char(char c);
void _print(const char* str);
void kernel_start(void);