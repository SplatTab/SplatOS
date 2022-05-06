#include <limits.h>
#include "strings.h"
#include "memory.h"
#include "math.h"

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

void itoa(int64_t num, char *str) {
    int i;
    char buf[21] = {0};

    if (!num) {
        return;
    }

    for (i = 19; num; i--) {
        buf[i] = (num % 10) + 0x30;
        num = num / 10;
    }

    i++;
    stradd(str, buf + i, sizeof(str) + sizeof(buf) + i);
}