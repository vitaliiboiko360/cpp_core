#include <stdarg.h>

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif
static void 
terminate(bool use_exit_3);

static void
output_error(
    int err, 
    const char* format, 
    va_list ap);

void
error_exit_en(int err_num, const char* format, ...);

void
error_exit(const char* format, ...);