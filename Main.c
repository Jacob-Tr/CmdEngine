#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "includes/SafeTypes.h"
#include "includes/ConsoleGl.h"

int main(void)
{
	INIT_SCREEN;
	
	size_t pt_s = 4;
	
	setPointSize(pt_s);
	
	point pt = newPoint('y');
	addPointToScrnBuf(main_screen_buf, pt, 5, 5);
	
	prtScr();
	return 0;
}
