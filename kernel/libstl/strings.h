#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

char *stradd(char *s1, const char *s2, size_t n);
size_t strnlen(const char *s, size_t maxlen);
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
int atoi(const char *str);
char* itoa(int num, char* str, int base);