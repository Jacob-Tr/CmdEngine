#ifndef COMPATINC_H
#define COMPATINC_H

#ifndef _WIN32
    #include "includes/Utils/Compat/Linux/Threads.h"
    #include "includes/Utils/Compat/Linux/IO.h"
#else
    #include "includes/Utils/Compat/Windows/Threads.h"
    #include "includes/Utils/Compat/Windows/IO.h"
#endif

#endif