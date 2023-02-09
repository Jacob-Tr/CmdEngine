#ifndef IO_H
#define IO_H

#define fopen_s(ptr, name, mode) *(ptr) = fopen((name), (mode))
#define freopen_s(ptr, name, mode) *(ptr) = freopen((name), (mode))

#include "includes/Utils/Compat/Linux/InputConfig/TerminalSetup.h"

#endif