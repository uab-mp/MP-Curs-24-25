#include <cstdio>
#include <cstdarg>

#include "debug.h"

// Funci? auxiliar para facilitar el uso de macros con par?etros variables
void log_msg(const char *format_string, ...)
{
  va_list args ;
  va_start(args, format_string) ;
  vprintf(format_string, args) ;
  va_end(args) ;
}
