#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "stdarg.h"

static void printint(int fd, int xx, int base, int sgn)
{
  static char digits[] = "0123456789";
  char buf[16];
  int i;
  uint x;

  if(sgn && xx < 0) {
    x = -xx;
  } else {
    x = xx;
  }

  i = 0;
  do {
    buf[i++] = digits[x % base];
  } while((x /= base) != 0);

  if(sgn && xx < 0) {
    buf[i++] = '-';
  }

  while(--i >= 0) {
    write(fd, &buf[i], 1);
  }
}

void vfprintf(int fd, const char *fmt, va_list ap)
{
  int i;

  for(i = 0; fmt[i]; i++) {
    if(fmt[i] != '%') {
      write(fd, &fmt[i], 1);
      continue;
    }
    if(fmt[++i] == 0) break;
    switch(fmt[i]) {
    case 'd':
      printint(fd, va_arg(ap, int), 10, 1);
      break;
    default:
      write(fd, &fmt[i], 1);
      break;
    }
  }
}

void fprintf(int fd, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(fd, fmt, ap);
  va_end(ap);
}