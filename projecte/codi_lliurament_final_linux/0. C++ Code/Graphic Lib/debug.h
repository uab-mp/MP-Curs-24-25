#pragma once

//! Imprime un mensaje de texto en la consola de debug
#define LOG(...)          { log_msg(__VA_ARGS__) ; }

//! Funci? auxiliar para facilitar el uso de macros con par?etros variables
void log_msg(const char *format_string, ...) ;
