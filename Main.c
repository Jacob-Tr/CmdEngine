#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define __CHAR_PTR_SIZE__ 4
#include "includes/Utils.h"
#define DEBUG
#include "includes/ConsoleGl.h"

#define NULL_T (test_type) {' '}
typedef struct
{
	pixel lol;
} test_type;

int main(void)
{
	test_type* t = NULL;
	*t = NULL_T;


	setPointSize(1);

	INIT_SCREEN;

	vector3l a = {5, 0, 5}, b = {10, 0, 10}, c = {5, 0, 9};

	point pt;
	point pt_two;

	initPoint(&pt, 'y', vector3lToVector3(a));
	initPoint(&pt_two, 'b', vector3lToVector3(b));

	line ln;
	initLine(&ln, pt_two, pt);

	addLineToScrnBuf(main_screen_buf, ln);

	START:
	prtScr();
	goto START;
	return 0;
}
