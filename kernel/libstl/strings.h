#pragma once
#include <stddef.h>
#include <stdint.h>

char *stradd(char *s1, const char *s2, size_t n);
size_t strnlen(const char *s, size_t maxlen);
void ltos(char* str, uint32_t val, size_t digits);