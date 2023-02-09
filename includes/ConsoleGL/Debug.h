#if !defined DEBUG_H && defined DEBUG
#define DEBUG_H

#ifndef STR_UTILS_H
    #include "iincludes/Utils/StringUtils.h"
#endif

#include "includes/ConsoleGL/DebugData/PrimitiveData.h"

#ifdef _cplusplis
extern "C" 
{
#endif

#define DEF 0x00000001
#define ARGS 0x00000010
#define DESCRIPTION 0x00000100
#define TYPES 0x00001000
#define STRUCTS 0x00010000
#define MACROS 0x00100000
#define ALL (DEF & DESCRIPTION & TYPES & STRUCTS & MACROS)

enum headers
{
	PRIMITIVES,
	OBJECTS,
	SCREENBUFFERS,
	SCREENDRAWING
};

#define HEADERS 4
char* headers[HEADERS] =
{
	"Primitives\0",
	"Objects\0",
	"ScreenBuffers\0",
	"ScreenDrawing\0"
};

bool getFlags(const char* str, size_t* flags, const size_t length)
{
	size_t dest_size = (sizeof(char) * 32), index = 0;
	char* dest = (char*) malloc(dest_size);
	
    while(index < length)
	{
		if(!strtoken(dest, str, ' ', &index, dest_size)) break;
		size_t dest_len = strlen(dest);
		
		if(strMatch(dest, "all", dest_len))
		{
			flags = ALL;
			break;
		}
		
		if(strMatch(dest, "defs", dest_len))
		{
			*flags ^= DEF;
			continue;
		}
		
		if(strMatch(dest, "description", dest_len))
		{
			*flags ^= DESCRIPTION;
			continue;
		}
		
		if(strMatch(dest, "types", dest_len))
		{
			*flags ^= TYPES;
			continue;
		}
		
		if(strMatch(dest, "structs", dest_len))
		{
			*flags ^= STRUCTS;
			continue;
		}
		
		if(strMatch(dest, "macros", dest_len))
		{
			*flags ^= MACROS;
			continue;
		}
		
		free(dest);
		return false;
	}
	
	free(dest);
	return true;
}

bool findFuncID(const char* func_name, size_t* id, const size_t header_id, const size_t length)
{
	switch(header_id)
	{
		case PRIMITIVES: return findPrimFuncID(func_name, id, length);
	}
	
	return false;
}

void printFuncHelp(const size_t header_id, const size_t func_id, const size_t flags)
{
	const size_t dest_size = (sizeof(char) * 32);
	size_t index = 0;
	char* dest = (char*) malloc(dest_size), *out = (char*) malloc(dest_size);
	
	snprintf(dest, dest_size, "%s", primitive_func_details[func_id]);
	
	if(flags & ARGS || flags & DEF)
	{
		if(flags & ARGS) strtoken(out, dest, ' ', &index, strlen(dest));
		if(flags & DEF) snprintf(out, dest_size, "%s %s", out,  primitive_functions[func_id]);
		if(flags & ARGS)
		{
			strtoken(dest, dest, ' ', &index, strlen(dest));
			snprintf(out, dest_size, "%s%s", out, dest);
		}
	}
	
	fprintf(stdout, "%s\n", out);
	
	free(dest);
	free(out);
	return;
}

void printHelp(const size_t header_id, const size_t flags)
{
	size_t out_size = (sizeof(char) * 32), index = 0;
	
	switch(header_id)
	{
		case PRIMITIVES:
		{
			for(size_t i = 0; i < PRIMITIVE_FUNCS; i++) printFuncHelp(header_id, i, flags);
			break;
		}
		default:
		{
			fprintf(stderr, "Error: Invalid header ID in function 'printHelp'. [%zu]\n", header_id);
			
			return;
		}
	}
}

void help(const char* str, const size_t length)
{
	if(strMatch(str, "help", length))
	{
		fprintf(stdout, "(Required) [Header Name or Function Name] (Optional) [def] [description] [types] [structs] [macros] [all]\n");
		return;
	}
	
	size_t dest_size = (sizeof(char) * 32), index = 0, flags = 0x0, header_id = HEADERS;
	char* dest = (char*) malloc(dest_size);
	
	if(!strtoken(dest, str, ' ', &index, dest_size))
	{
		fprintf(stderr, "Error: Invalid string supplied to function help: \"%s\".", str);
		
		free(dest);
		return;
	}
	    
	for(size_t i = 0; i < HEADERS; i++)
	{
		char* header = headers[i];
		
	    if(strMatch(dest, header, strlen(dest))) 
	    {
	    	header_id = i;
	    	break;
	    }
	}
	
	if(header_id == HEADERS)
	{
		fprintf(stderr, "Error: Function help recieved invalid arguments: \"%s\".", str);
		
		free(dest);
		return;
	}
	
	substring(dest, dest, index, strlen(dest), dest_size);
	
	size_t func_id = 0;
	char* func_name = (char*) malloc(dest_size);
	
	if(!getFlags(dest, &flags, strlen(dest)))
	{
		if(!strtoken(func_name, dest, ' ', &index, strlen(dest)) || !findFuncID(func_name, &func_id, header_id, strlen(func_name)) || !substring(dest, dest, index, strlen(dest), dest_size))
		{
		    fprintf(stderr, "Error: Function help recieved invalid parameters: \"%s\".", dest);
		
		    free(dest);
		    free(func_name);
		    return;
		}
		
		getFlags(dest, &flags, strlen(dest));
	}
	
	printHelp(header_id, flags);
	
	free(dest);
	return;
}

#ifdef _cplusus
}
#endif

#endif