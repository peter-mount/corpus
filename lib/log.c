
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <log.h>

void loginfo(const char *fmt, ...) {
    time_t now = time(NULL);
    struct tm tm;
    localtime_r(&now,&tm);
    char buf[20];
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", &tm);

    va_list argp;

    va_start(argp, fmt);
    fputs(buf, stdout);
    fputc(32, stdout);
    vfprintf(stdout, fmt, argp);
    fputc(10, stdout);
    va_end(argp);
}

