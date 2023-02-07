#ifndef CHATBOX_H
#define CHATBOX_H

#define MAX_USR_INPUT 64

static char* __usr_in__ = NULL;

#define print(str) addChat((str), strlen((str)))

#define printc(c) char* __str = (char*) malloc(sizeof(char)); snprintf(__str, 10, "Char: %c[%d]", (c), ((int_32) (c))); print((__str)); free((__str));
#define CMD_DELIM '/'

static char* chat_text;
static vector2 chat_size = EMPTY_VECT2;
static bool chat_init = false;

#ifdef _cplusplus
extern "C"
{
#endif

void initChatbox(const size_t x, const size_t z)
{
	chat_size.x = x;
	chat_size.z = z;
	
	chat_text = (char*) malloc(sizeof(char) * (x * z));
	__usr_in__ = (char*) calloc(MAX_USR_INPUT, sizeof(char));
	
	for(size_t i = 0; i < ((x * z)); i++)
	{
		char set = ' ';
		
		if(i <= x || i >= ((x * z) - x)) set = '-';
		if((i % chat_size.x) == (x - 1)) set = '|';
		if((i % chat_size.x) == 0) set = '|';
		
		*(chat_text + i) = set;
	}
	
	chat_init = true;
}

void destroyChatbox(void) 
{
	free(chat_text);
	
	chat_text = NULL;
	
	free(__usr_in__);
	
	__usr_in__ = NULL;
}

char* getChatboxCharPtr(const size_t x, const size_t z) {return (chat_init) ? (char*) (chat_text + ((z * chat_size.x) + x)) : (char*) NULL;}

void setChatboxChar(const size_t x, const size_t z, const char c) {*(getChatboxCharPtr(x, z)) = c;}

void printChat(void)
{
	screen_buffer* buf = getMainBuffer();
	
	for(size_t i = 0; i < chat_size.z; i++)
	{
		for(size_t ii = 0; ii < chat_size.x; ii++)
		{
			pixel px;
			initPixel(&px, *(getChatboxCharPtr(ii, i)));
			
			setScreenBufPixel(buf, px, ii, i);
		}
	}
}

void clearLine(const size_t line)
{
	if(line >= chat_size.z || line == 0)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Unable to clear line #%zu which exceeds max Z of chatbox [%zu] or is part of the chatbox boarder.\n", line, chat_size.z);
		#endif
		
		return;
	}
	
	memset(getChatboxCharPtr(1, line), ' ', (chat_size.x - 2));
}

void moveChatUp(const size_t moves)
{
	if(moves == 0) return;
	
	#ifdef DEBUG
	    if(moves > chat_size.z) fprintf(stderr, "Warning: moveChatUp moving %zu lines more then chat size of %zu.\n", (moves - chat_size.z), (chat_size.x * chat_size.z));
	#endif
	
	size_t line_index = 0, next_line_index = 0;
	
	for(size_t i = 1; i < (chat_size.z - 2); i++)
	{
		line_index = ((i * chat_size.x) + 1);
		next_line_index = (((i + 1) * chat_size.x) + 1);
		
		memcpy((chat_text + line_index), (chat_text + next_line_index), (chat_size.x - 2));
		clearLine(i + 1);
	}
	
	if(moves > 0) moveChatUp(moves - 1);
}

void clearChat(void) {moveChatUp((chat_size.z - 1));}

void addChat(const char* str, const size_t length)
{
	if(length == 0) return;
	
	size_t moves = 1;
	moves += (length >= chat_size.x ) ? ((size_t) ceil(((double) length) / ((double) chat_size.x))) : 0;
	moveChatUp(moves);
	
	size_t start = ((chat_size.z - 3) * chat_size.x) + 1;
	
	char c = '\0';
	
	for(size_t i = start; (i - start) < length; i++)
	{
		c = *(str + (i - start));
		
		if(!isnumber(c) && !isalphachar(c) && !isoperator(c)) continue;
		
		i = (i % (chat_size.x) == (chat_size.x - 1)) ? (i + 2) : i;
		*(chat_text + i) = c;
	}
	
	printChat();
}

static inline bool cmdcmp(const char* input, const char* cmd, const size_t cmd_len, const size_t length)
{
	if(length != cmd_len) return false;
	
	return !strncmp(input, cmd, length);
}

#include "includes/Engine/Display/Commands/Commands.h"

#define CMD(cmd) if(cmdcmp(str, (cmd), strlen((cmd)), strlen(str)))

bool processCmd(const char* str, size_t length)
{
	//if(*(str + length) == '\0') length--;
	CMD("/exit")
	{
		print("Exiting...");
		sleep(2);
		exitMainThreadQueue();
		return true;
	}
	
	CMD("/hello")
	{
		print("Hello, world!");
		return true;
	}
	return false;
}

#undef CMD

void clearUserIn(void) {memset(__usr_in__, '\0', MAX_USR_INPUT);}

bool addInput(const char c)
{
	if(!isnumber(c) && !isalphachar(c) && !isoperator(c) && c != '\n' && c != '\r' && c != 127)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attempted to add invalid chatacter '%c'[#%d] to user input buffer.\n", c, ((int_32) c));
		#endif
		
		return false;
	}
	
	size_t length = strlen(__usr_in__);
	
	if(c == '\n' || c == '\r')
	{
		if(*(__usr_in__) == CMD_DELIM)
		{
			if(processCmd(__usr_in__, length))
			{
				clearUserIn();
				return true;
			}
			else print("SERVER: Unknown Command.");
		}
		else print(__usr_in__);
		
		clearUserIn();
	}
	else
	{
	    if(c == 127) 
	    {
	    	if(length > 0) *(__usr_in__ + --length) = '\0';
	    }
	    else if(length >= MAX_USR_INPUT)
	    {
    		#ifdef DEBUG
    		    fprintf(stderr, "Warning: Input has grown too long [\"%s\"[%zu]] - Could not add character %c.\n", __usr_in__, length, c);
    		#endif
		
    		return false;
    	}
    	else *(__usr_in__ + length++) = c;
	}
	
	size_t start = (length >= (chat_size.x - 2)) ? (length - (chat_size.x - 2)) : 0;
	
	memset(getChatboxCharPtr(1, (chat_size.z - 2)), ' ', (chat_size.x - 2));
    if(strlen(__usr_in__) > 0) memcpy(getChatboxCharPtr(1, (chat_size.z - 2)), (__usr_in__ + start), (length - start));
	
    printChat();
	
	return true;
}

#ifdef _cplusus
}
#endif

#endif