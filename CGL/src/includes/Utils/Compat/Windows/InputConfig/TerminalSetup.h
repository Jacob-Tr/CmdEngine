#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef _cplusplus
extern "C"
{
#endif

bool initTerminal(void) 
{
	fprintf(stderr, "Error: initTerminal not yet implemented for Windows.\n");
	
	return true;
}

bool terminalFinalize(int32_t signum) {return false;}

#define STDIN_FILENO _fileno(stdin)
#define STDOUT_FILENO _fileno(stdout)
#define STDERR_FILENO _fileno(stderr)

#ifdef _cplusplus
}
#endif

#endif