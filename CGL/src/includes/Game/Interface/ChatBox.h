#ifndef CHATBOX_H
#define CHATBOX_H

#define MAX_USR_INPUT 64

static char* __usr_in__ = NULL;

#define print(str) addChat((str), strlen((str))) 

#define CMD_DELIM '/'

static char* chat_text;
static vector2 chat_size = Vect2(0, 0);

static bool chat_init = false;

#ifdef __cplusplus
extern "C"
{
#endif

void toggleInput(bool value) {get_input = value;}

void __cdecl initChatbox(const vector2 vect)
{
	if(chat_init == true || chat_text != ((char*) NULL) || __usr_in__ != ((char*) NULL))
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: Chatbox re-initialized.\n");
		#endif

		return;
	}

	chat_size.x = vect.x;
	chat_size.z = vect.z;
	
	// Allocate buffers for two global variables
	chat_text = (char*) malloc(sizeof(char) * (vect.x * (vect.z + 1)));
	__usr_in__ = (char*) calloc(MAX_USR_INPUT, sizeof(char));
	
	// Current chatbox boarder character.
	char set;

	for(size_t i = 0; i < (vect.x * vect.z); i++)
	{
		set = ' ';

		if(i <= vect.x || i >= ((vect.x * vect.z) - vect.x)) set = '-';
		if((i % vect.x) == (vect.x - 1)) set = '|';
		if((i % vect.x) == 0) set = '|';
		
		*(chat_text + i) = set;
	}
	
	chat_init = true;
}

void __cdecl destroyChatbox(void) 
{
	free(chat_text);
	chat_text = NULL;
	
	free(__usr_in__);
	__usr_in__ = NULL;
}

// Get the address of the character at (x, z).
char* getChatboxCharPtr(const vector2 vect) {return (chat_init) ? (char*) (chat_text + ((vect.z * chat_size.x) + vect.x)) : (char*) NULL;}

// Set the character value of the chatbox at (x, z).
void setChatboxChar(const vector2 vect, const char c) {*(getChatboxCharPtr(vect)) = c;}

// Print the chatbox to the screen.
void printChat(void)
{
	// Retrieve the next to draw screen buffer.
	/*screen_buffer* buf = getMainBuffer();
	
	for(size_t i = 0; i < chat_size.z; i++)
	{
		for(size_t ii = 0; ii < chat_size.x; ii++)
		{
			pixel px;
			initPixel(&px, ((SDL_Color) COLOR_WHITE), *getChatboxCharPtr((vector2) Vect2(ii, i)));
			
			setScreenBufPixel(buf, px, (vector2) Vect2(ii, i));
		}
	}*/
}

void clearLine(const size_t line)
{
	if(line >= chat_size.z || line == 0)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Unable to clear line #%zu which exceeds max Z of chatbox [%zu] or is part of the chatbox boarder.\n", line, chat_size.z);
		#endif
		
		return;
	}
	
	memset(getChatboxCharPtr((vector2) Vect2(1, line)), ' ', (chat_size.x - 2));
}

void moveChatUp(const size_t moves)
{
	if(moves == 0) return;
	
	#ifdef DEBUG
	    if(moves > chat_size.z) fprintf(stderr, "Warning: moveChatUp moving %zu lines more then chat size of %zu.\n", (moves - chat_size.z), (chat_size.x * chat_size.z));
	#endif
	
	size_t line_index = 0, next_line_index = 0;
	
	// End 2 rows above the bottom (boarder and input); start at index 1 on x axis to avoid left boarder.
	for(size_t i = 1; i < (chat_size.z - 2); i++)
	{
		// Get index 1 of current and following line.
		line_index = ((i * chat_size.x) + 1);
		next_line_index = (((i + 1) * chat_size.x) + 1);
		
		// Copy contents of following line to current line, then clear following line.
		memcpy((chat_text + line_index), (chat_text + next_line_index), (chat_size.x - 2));
		clearLine(i + 1);
	}
	
	// Repeat if necessary.
	if(moves > 0) moveChatUp(moves - 1);
}

void clearChat(void) {moveChatUp((chat_size.z - 1));}

void addChat(const char* str, const size_t length)
{
	if(length == 0) return;
	
	// If there is something to print, moves will be at least 1.
	size_t moves = 1;
	double d_moves = (((double) length) / ((double) chat_size.x)); // How many lines would be needed to fit 'str'.
	moves += (length >= chat_size.x) ? ((size_t) ceil(d_moves)) : 0; // Moves adjusted to upper bound of 'd_moves' if necessary.
	
	if(((d_moves - ((double) moves)) < 0.5) && moves > 1) --moves; // If we rounded up a low half then we overshot, reduce 'moves'.
	moveChatUp(moves);
	
	// Start 2 rows above Z bounds at X index 1.
	size_t start = ((chat_size.z - (2 + moves)) * chat_size.x) + 1;
	
	char c = '\0';
	
	for(size_t i = start; (i - start) < length; i++)
	{
		c = *(str + (i - start)); 
		
		if(!isnumber(c) && !isalphachar(c) && !isoperator(c)) continue;
		
		// Set 'i' to the next line if necessary.
		i = (i % (chat_size.x) == (chat_size.x - 1)) ? (i + 2) : i;

		// Add character to buffer.
		*(chat_text + i) = c;
	}
	
	printChat();
}

#include "includes/Game/Interface/Commands/Commands.h"

void clearUserIn(void) {memset(__usr_in__, '\0', MAX_USR_INPUT);}

bool addInput(const char c)
{
	// Check if character is valid.
	if(!isnumber(c) && !isalphachar(c) && !isoperator(c) && c != '\n' && c != '\r' && c != ' ' && c != 127 && c != 8)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Attempted to add invalid chatacter '%c'[#%d] to user input buffer.\n", c, ((int32_t) c));
		#endif
		
		return false;
	}
	
	size_t length = strlen(__usr_in__);
	
	// Handle 'Enter' press
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
		if(length >= MAX_USR_INPUT) 
	    {
    		#ifdef DEBUG
    		    fprintf(stderr, "Warning: Input has grown too long [\"%s\"[%zu]] - Could not add character %c.\n", __usr_in__, length, c);
    		#endif
		
    		return false;
    	}

		// Handle backspace by replacing the last character with a null char. Otherwise ensure we wont exceed buffer bounds and write char.
	    if(( c == 127 || c == 8) && length > 0) *(__usr_in__ + --length) = '\0';
    	else *(__usr_in__ + length++) = c;
	}
	
	// X bound minus newline and boarder.
	size_t start = (length >= (chat_size.x - 2)) ? (length - (chat_size.x - 2)) : 0;
	
	// Clear the input line and feed the updated final characters of the buffer to the input line.
	clearLine((chat_size.z - 2));
    if(strlen(__usr_in__) > 0) memcpy(getChatboxCharPtr((vector2) Vect2(1, (chat_size.z - 2))), (__usr_in__ + start), (length - start));
	
	// Write the chatbox to the screenbuffer.
    printChat();
	
	return true;
}

#ifdef _cplusus
}
#endif

#endif