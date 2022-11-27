#ifndef MATH_STR_UTILS_H
#define MATH_STR_UTILS_H

#ifdef _cplusplus
extern "C"
{
#endif

bool ismathconstant(const char c) {return ((bool) isnumber(c)/* || (c == 'π')*/);}

bool isbaseoperator(const char c) {return ((bool) (c == '/') ||  (c == '*')/* || (c == '÷') || (c == '×') || (c == '•')*/ || (c == '+') || (c == '-'));}

bool isadvancedoperator(const char c) {return ((bool) (c == '^') || (c == '!') || (c == '%'));}

bool isbracket(const char c) {return ((bool) (c == '(') || (c == ')'));}

bool isoperator(const char c) {return ((bool) isbaseoperator(c) || isadvancedoperator(c) || isbracket(c));}

bool isvalidpreobrckt(const char c) {return ((bool) isalphachar(c) || ismathconstant(c) || isbaseoperator(c) || isadvancedoperator(c) || (c == '(') || (c == '=') || (c == '\0'));}

bool isvalidpostobrckt(const char c) {return ((bool) isalphachar(c) || ismathconstant(c) || (c == '!') || (c == '('));}

bool isvalidprecbrckt(const char c) {return ((bool) (isalphachar(c) || ismathconstant(c) || (c == ')')));}

bool isvalidpostcbrckt(const char c) {return ((bool) (isalphachar(c) || ismathconstant(c) || isbaseoperator(c) || (isadvancedoperator(c) && (c != '!')) || (c == '=') || (c == ')') || (c == '\0')));}

bool isvalidbrckt(const char c, const char former, const char latter) {return ((bool) isbracket(c) && ((c == '(') ? (isvalidpreobrckt(former) && isvalidpostobrckt(latter)) : (isvalidprecbrckt(former) && isvalidpostcbrckt(latter))));}

bool isvalidprebaseoperator(const char c) {return ((bool) ismathconstant(c) || isalphachar(c) || (c == ')'));}

bool isvalidpostbaseoperator(const char c) {return ((bool) ismathconstant(c) || isalphachar(c) || (c == '(') || (c == '!'));}

bool isvalidbaseoperator(const char c, const char former, const char latter) {return ((bool) isbaseoperator(c) && isvalidprebaseoperator(former) && isvalidpostbaseoperator(latter));}

bool isvalidadvancedoperator(const char c, const char former, const char latter) {return ((bool) isadvancedoperator(c) && ((c != '!') ? isvalidbaseoperator('*', former, latter) : isvalidbaseoperator('*', former, latter) || isoperator(former) || (former == '=') || (former == '\0')));}

bool isvalidoperator(const char c, const char former, const char latter) {return ((bool) isvalidbrckt(c, former, latter) || isvalidbaseoperator(c, former, latter) || isvalidadvancedoperator(c, former, latter));}

bool isvalidexpsn(const char* str, const size_t length)
{
	bool valid = false;
	int_16 brackets = 0;
	char c = '\0', former = '\0', latter = '\0';
	
	for(size_t i = 0; i < length; i++)
	{
		if(brackets < 0) return false;
		
		if(i != 0) former = c;
		if(i != (length - 1)) latter = *(str + (i + 1));
		else latter = '\0';
		c = *(str + i);
		
		fprintf(stdout, "Pre: %d : c: %d : post: %d\n", (int_32) former, (int_32) c, (int_32) latter);
		
		if(c == '\0') break;
		
		if(isoperator(c))
		{
			fprintf(stdout, "%c is an operator\n", c);
			if(!isvalidoperator(c, former, latter)) return false;
			fprintf(stdout, "%c is a valid operator\n", c);
			
			if(isbracket(c)) 
			{
				if(c == '(') brackets++;
				else brackets--;
			}
			
			continue;
		}
		
		fprintf(stdout, "%c is not an operator\n", c);
	    
	    if(!ismathconstant(c) && !isalphachar(c))
	    {
	    	if(c == '=' && brackets == 0) continue;
	    	return false;
	    }
	}
	
	return true;
}

#ifdef _cplusplus
}
#endif

#endif