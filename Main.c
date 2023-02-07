#define __PTR_SIZE__ 4
#define SHORT_TYPE_NAMES
#define DEBUG

#include "includes/Utils.h"
#include "includes/Game.h"

int main(void)
{
	if(!init())
	{
		fprintf(stderr, "Error: Fatal error in engine initialization.\n");
		
		return 1;
	}
	
	start();
	return 0;
}