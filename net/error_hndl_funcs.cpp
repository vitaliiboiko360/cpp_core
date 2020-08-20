#include "error_hndl_funcs.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif
static void 
terminate(bool use_exit_3)
{
    char *s;
    s = getenv("EF_DUMPCORE");
    if (s != NULL && *s != '\0')
        abort();
    else if (use_exit_3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
    // Chapter 25 - difference between exit and _exit  
}

static void
output_error(
    int err, 
    const char* format, 
    va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], user_msg[BUF_SIZE], err_text[BUF_SIZE];
    vsnprintf(user_msg, BUF_SIZE, format, ap);
    snprintf(err_text, BUF_SIZE, " [%s]", strerror(err));
    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", err_text, user_msg);
    fflush(stdout);
    fputs(buf, stderr);
    fflush(stdout);
}

void
error_exit_en(int err_num, const char* format, ...)
{
    va_list arg_list;
    va_start(arg_list, format);
    output_error(err_num, format, arg_list);
    va_end(arg_list);
    terminate(true);
}

void
error_exit(const char* format, ...)
{
    va_list arg_list;
    va_start(arg_list, format);
    output_error(errno, format, arg_list);
    va_end(arg_list);
    terminate(true);
}