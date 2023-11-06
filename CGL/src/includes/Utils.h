#ifndef UTILS_H
#define UTILS_H

/*
	Anything which is a base dependancy for the rest of Utils; SDL and standard library headers are included here.
	Some macros and basic settings.
*/
#include "includes/Utils/TopLevelCompat.h"

// Debugging tools.
#include "includes/Utils/Debug.h"

// Handle some cross-platform functionality.
#include "includes/Utils/Compat.h"

// Useful character array functions. 
#include "includes/Utils/StringUtils.h"
#include "includes/Utils/MathStrUtils.h"

#include "includes/Utils/FileHandler.h"

#endif