#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

char *stradd(char *s1, const char *s2, size_t n);
size_t strnlen(const char *s, size_t maxlen);
void itoa(int64_t num, char *str);