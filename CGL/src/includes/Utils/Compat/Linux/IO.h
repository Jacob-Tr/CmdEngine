#ifndef IO_H
#define IO_H

#define fopen_s(ptr, name, mode) *(ptr) = fopen((name), (mode))
#define freopen_s(ptr, name, mode, oldstream) *(ptr) = freopen((name), (mode), (oldstream))

#include "includes/Utils/Compat/Linux/InputConfig/TerminalSetup.h"

#endif