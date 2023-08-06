#ifndef THREADING_H
#define THREADING_H

enum thread_enm
{
	THREAD_NETWORK,
	THREAD_INPUT,
	THREAD_AUDIO,
	THREAD_NULL
};

static bool exitThread[THREAD_NULL] = {false, false, false};
static size_t thread_id[THREAD_NULL] = {0, 0, 0};

#include "includes/Engine/Threads/NetworkThread.h"
#include "includes/Engine/Threads/InputThread.h"
#include "includes/Engine/Threads/AudioThread.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool initUtilityThreads(void)
{
	THREAD* network_thread = getNextThreadFromPool(main_pool, &thread_id[THREAD_NETWORK]), *input_thread = getNextThreadFromPool(main_pool, &thread_id[THREAD_INPUT]), *audio_thread = getNextThreadFromPool(main_pool, &thread_id[THREAD_AUDIO]);

	if((network_thread == NULL) || (input_thread == NULL) || (audio_thread == NULL))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not get thread pointer from thread pool.\n");
		#endif
		
		return false;
	}

	char* names[THREAD_NULL];

	for(size_t i = 0; i < THREAD_NULL; i++) names[i] = (char*) malloc(sizeof(char) * MAX_THREAD_NAME);

	memcpy(names[THREAD_NETWORK], "Network Thread", strlen("Network Thread"));
	memcpy(names[THREAD_INPUT], "Input Thread", strlen("Input Thread"));
	memcpy(names[THREAD_AUDIO], "Audio Thread", strlen("Audio Thread"));

	*(names[THREAD_NETWORK] + strlen("Network Thread")) = '\0';
	*(names[THREAD_INPUT] + strlen("Input Thread")) = '\0';
	*(names[THREAD_AUDIO] + strlen("Audio Thread")) = '\0';

	initThread(network_thread, names[THREAD_NETWORK], strlen(names[THREAD_NETWORK]), (void*) networkLoop, NULL, 0);
	initThread(input_thread, names[THREAD_INPUT], strlen(names[THREAD_INPUT]), (void*) inputLoop, NULL, 0);
	initThread(audio_thread, names[THREAD_AUDIO], strlen(names[THREAD_AUDIO]), (void*) audioLoop, NULL, 0);
	
	return true;
}

void getUtilityThreadPtrs(THREAD** input, THREAD** audio, THREAD** network)
{
	*input = getThreadPtrFromPool(*main_pool, thread_id[THREAD_NETWORK]);
	*network = getThreadPtrFromPool(*main_pool, thread_id[THREAD_INPUT]);
	*audio = getThreadPtrFromPool(*main_pool, thread_id[THREAD_AUDIO]);
}

void exitUtilityThread(enum thread_enum t)
{
	THREAD* thread = getThreadPtrFromPool(*main_pool, thread_id[t]);

	exitThread[t] = true;

	SDL_WaitThread(thread->thread, NULL);
}

void exitUtilityThreads(void)
{
	exitUtilityThread(THREAD_NETWORK);
	exitUtilityThread(THREAD_INPUT);
	exitUtilityThread(THREAD_AUDIO);
}

bool startUtilityThreads(void)
{
	THREAD* input, *network, *audio;

	getUtilityThreadPtrs(&input, &audio, &network);

	if(!(startThread(input) && startThread(audio) && startThread(network)))
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: One or more utility threads failed to start.\n");
		#endif

		return false;
	}
    
    return true;
}

#ifdef __cplusplus
}
#endif

#endif