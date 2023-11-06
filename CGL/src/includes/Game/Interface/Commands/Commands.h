#ifndef COMMANDS_H
#define COMMANDS_H

#define CMD_QUEUE_SIZE 32

// Macro to create functionality of 'commands'. [CMD(<command>) {<functionality>;}]
#define CMD(cmd) if(cmdcmp(str, (cmd), strlen((cmd)), strlen(str)))
static inline bool cmdcmp(const char* input, const char* cmd, const size_t cmd_len, const size_t length)
{
	if(length != cmd_len) return false;
	
	return !strncmp(input, cmd, length);
}

// For processing commands in syncronously
typedef struct
{
	void** func_ptr;
	void** cmd_args;
	size_t queue_size, queue_entries;
} cmd_queue;

cmd_queue commands;

#define cmd_queue

#ifdef _cplusplus
extern "C"
{
#endif

void destroyCommandQueue(void)
{
	free(commands.func_ptr);
	free(commands.cmd_args);
}

bool initCommandQueue(void)
{
	commands.queue_size = CMD_QUEUE_SIZE;
	commands.queue_entries = 0;

	commands.func_ptr = (void**) malloc(sizeof(void*) * CMD_QUEUE_SIZE);
	commands.cmd_args = (void**) malloc(sizeof(void*) * CMD_QUEUE_SIZE);

	if(commands.func_ptr == NULL || commands.cmd_args == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: Could not initialize command queue.\n");
		#endif
		
		destroyCommandQueue();

		return false;
	}

	return true;
}

void queueCommand(char* cmd_name, const size_t name_len, void* cmd_func, void* cmd_args)
{
	if(commands.queue_entries >= commands.queue_size)
	{
		#ifdef DEBUG
			fprintf(stderr, "Warning: Command queue is full; cannot process command \"%s\".\n", cmd_name);
		#endif

		return;
	}


}

bool processCmd(const char* str, size_t length)
{
	CMD("/exit")
	{
		toggleInput(false);

		print("Exiting...");
		sleep(2);

		exitGame();
		
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

#ifdef _cplusplus
}
#endif

#endif