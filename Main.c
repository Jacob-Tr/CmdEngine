#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define __CHAR_PTR_SIZE__ 4
#include "includes/Utils.h"
#define DEBUG
#include "includes/Calculate.h"
//#include "includes/ConsoleGl.h"

int main(void)
{
    char* expr = "!5+-(-a(6))", oper = '!';
    
    /*fprintf(stdout, "Valid base operator: %s\n", (isvalidbaseoperator(oper, '\0', '\0') ? "true" : "false"));
    fprintf(stdout, "Valid advanced operator: %s\n", (isvalidadvancedoperator(oper, '\0', '\0') ? "true" : "false"));*/
    
    //int_32 open = -1, close = -1;
    
    char* str = (char*) malloc(sizeof(char) * 64);
    solve(str, expr, 64, strlen(str));
    //strAdd(str, expr, '*', 11, 64, strlen(expr));
    
    fprintf(stdout, "%s = %s\n", expr, str);
    //fprintf(stdout, "%d", findBrcktMatch(expr, 11, strlen(expr)));
    //fprintf(stdout, "%s", (isvalidexpsn(expr, strlen(expr)) ? "true" : "false"));
    
	return 0;
}
