#include "strings.h"
#include "memory.h"

size_t strnlen(const char *s, size_t maxlen)
{
  size_t i;
  for (i = 0; i < maxlen; ++i)
    if (s[i] == '\0')
      break;
  return i;
}

char *stradd(char *s1, const char *s2, size_t n)
{
    size_t size = strnlen(s2, n);
    if (size != n) memset(s1 + size, '\0', n - size);
    return memcpy(s1, s2, size);
}

void ltos(char* str, uint32_t val, size_t digits)
{
  size_t i=1u;

  for(; i<=digits; i++)
  {
    str[digits-i] = (char)((val % 10u) + '0');
    val/=10u;
  }

  str[i-1u] = '\0';
}