#ifndef COMPATINC_H
#define COMPATINC_H

#ifndef _MSC_VER
    #include "includes/Utils/Compat/Linux/Threads.h"
    #include "includes/Utils/Compat/Linux/TerminalSetup.h"
#else
    #include "includes/Utils/Compat/Windows/Threads.h"
    #include "includes/Utils/Compat/Windows/TerminalSetup.h"
#endif

#endif