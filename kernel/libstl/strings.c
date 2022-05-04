#include "strings.h"
#include "memory.h"
#include "limits.h"

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

int atoi(const char *str)
{
    int sign = 1, base = 0, i = 0;

    while (str[i] == ' ')
    {
        i++;
    }

    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        if (base > INT_MAX / 10
            || (base == INT_MAX / 10
            && str[i] - '0' > 7))
        {
            if (sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
        base = 10 * base + (str[i++] - '0');
    }

    return base * sign;
}