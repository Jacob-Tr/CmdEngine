#ifndef COMPATINC_H
#define COMPATINC_H

#ifdef __GNUC__
    #include "includes/Utils/Compat/Linux/IO.h"
#elif defined _WIN32
    #include "includes/Utils/Compat/Windows/IO.h"
#endif

#endif