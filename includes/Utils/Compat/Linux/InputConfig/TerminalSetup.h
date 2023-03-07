#ifndef TERMINAL_H
#define TERMINAL_H

static FILE* terminal = ((FILE*) NULL);
static int_32 terminal_id = -1;
static struct termios original, settings;

#ifdef _cplusplus
extern "C"
{
#endif

void terminalFinalize(int_32 signum)
{
	if(terminal_id < 0) 
	{
		fprintf(stderr, "Error: Terminal finalize failed.\n");
		return;
	}
	
	tcsetattr(terminal_id, TCSANOW, &original);
}

#define SACTION(action) sigaction((action), act, NULL)
bool initSigAction(struct sigaction* act)
{
	sigemptyset(&(act->sa_mask));
	
	act->sa_handler = &(terminalFinalize);
	
	act->sa_flags = 0;
	
	if(SACTION(SIGHUP) || SACTION(SIGINT) || SACTION(SIGQUIT) || 
#ifdef SIGXCPU
    SACTION(SIGTERM) || 
#endif
#ifdef SIGXFSZ
    SACTION(SIGXFSZ) ||
#endif
#ifdef SIGIO
    SACTION(SIGIO) ||
#endif
    SACTION(SIGPIPE) || SACTION(SIGALRM)) return false;
    
    return true;
}
#undef SACTION

void initTerminalSettings(void)
{
	settings.c_iflag &= ~IGNBRK;
	settings.c_iflag |= BRKINT;
	
	settings.c_iflag |= IGNPAR;
	settings.c_iflag &= ~PARMRK;
	
	settings.c_iflag &= ~ISTRIP;
	
	settings.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	
#ifdef IUCLC
    settings.c_iflag &= IUCLC;
#endif

    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= CS8;
    
    settings.c_cflag |= CREAD;
    
    settings.c_lflag |= ISIG;
    
    settings.c_lflag &= ~ICANON;
    
    settings.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    
    settings.c_lflag &= ~IEXTEN;
    
    settings.c_cc[VTIME] = 0;
    settings.c_cc[VMIN] = 1;
}

bool initTerminal(void)
{
	if(terminal_id != -1) fprintf(stderr, "Warning: Reinitialization of terminal.\n");
	
	terminal_id = (isatty(STDIN_FILENO)) ? STDIN_FILENO : (isatty(STDOUT_FILENO)) ? STDOUT_FILENO : (isatty(STDERR_FILENO)) ? STDERR_FILENO : -1;
	
	if(terminal_id == -1 || (tcgetattr(terminal_id, &settings) || tcgetattr(terminal_id, &original)))
	{
		fprintf(stderr, "Error: Terminal initialization failed: Current terminal must be; 'stdin', 'stdout' or 'stderr'.\n");
		return false;
	}
	
	terminal = (isatty(STDIN_FILENO)) ? stdin : (isatty(STDOUT_FILENO)) ? stdout : (isatty(STDERR_FILENO)) ? stderr : ((FILE*) NULL);
	
	// Disable terminal stream buffering
	setvbuf(terminal, NULL, _IONBF, 0);
	
	struct sigaction act;
	if(!initSigAction(&act))
	{
		fprintf(stderr, "Error: sigaction struct initialization failed.\n");
		return false;
	}
	
	initTerminalSettings();
    
    tcsetattr(terminal_id, TCSANOW, &settings);
    
    return true;
}

#ifdef _cplusplus
}
#endif

#endif