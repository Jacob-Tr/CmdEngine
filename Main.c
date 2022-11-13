#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define __CHAR_PTR_SIZE__ 4
#include "includes/Utils.h"
#define DEBUG
#include "includes/ConsoleGl.h"


void testStrUtils(void)
{
	char *c = "My Bag  is lost", *dest = (char *)malloc(sizeof(char) * 32);
	size_t index = 0;

	while (index < strlen(c))
	{
		strtoken(dest, c, ' ', &index, 32);
		fprintf(stdout, "%s\n", dest);
	}
}

int main(void)
{
	setPointSize(1);

	INIT_SCREEN;

	vector3l a = {5, 0, 5}, b = {10, 0, 10}, c = {5, 0, 9};
	vector3 xd = {10, 0, 10};
	vector3l lol = vector3Addl(a, vector3ToVector3l(xd));
	//printf("%lld : %lld : %lld", lol.x, lol.y, lol.z);

	point pt;
	point pt_two;

	initPoint(&pt, 'y', vector3lToVector3(a));
	initPoint(&pt_two, 'b', vector3lToVector3(b));

	line ln;
	initLine(&ln, pt_two, pt);

	addLineToScrnBuf(main_screen_buf, ln);

	// prtScr();
	return 0;
}
