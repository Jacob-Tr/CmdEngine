#ifndef CALCULATE_H
#define CALCULATE_H

#ifndef UTILS_H
    #include "includes/Utils.h"
#endif

#define OPERATORS 6
const char order[] =
{
	'(',
	'!',
	'/',
	'*',
	'-',
	'+'
};

#ifdef _cplusplus
extern "C"
{
#endif

int_32 findBracketMatch(const char* str, const int_32 index, const size_t length)
{
	char c = *(str + index);
	if(c != '(' && c != ')') 
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: findBtcktMatch cannot find matching bracket for index %zu ('%c') in string \"%s\".\n", index, c, str);
		#endif
		return -1;
	}
	
	const bool open = (c == '(');
	int_32 brackets = (open ? 1 : -1);
	
	for(size_t i = (index + 1); i < (open ? length : (index * 2)); i++)
	{
		c = *(str + (open ? i : (index - (i - index))));
		if(isbracket(c)) brackets = (c == '(' ? brackets + 1 : brackets - 1);
		
		if(brackets == 0) return (open ? i : (index - (i - index)));
		else if((!open && i == 0) || (open && i == (length - 1))) break;
	}
	
	return -1;
}

int_32 findNextOperator(const char* str, const size_t index, const size_t length)
{
	if(index >= length) return -1;
	
	for(size_t i = index; i < length; i++) if(isoperator(*(str + i))) return i;
	
	return (((int_32) length) - 1);
}

int_32 findPrevOperator(const char* str, const size_t index, const size_t length)
{
	if(index >= length) return 0;
	int_32 oper = -1;
	
	for(size_t i = 0; i < OPERATORS; i++)
	{
		oper = prevIndexOf(str, index, order[i], length);
		
		if(oper != -1) return oper;
	}
	
	return 0;
}

size_t countOperators(const char* str, const size_t length)
{
	size_t operators = 0;
	int_32 index = 0;
	
    do
    {
    	index = findNextOperator(str, ((size_t) index), length);
    	if(index != -1) operators++;
    } while(index != -1);
    
    return operators;
}

void findNextBrackets(const char* str, int_32* open, int_32* close, const size_t length)
{
	int_32 index = 0;
	
	*open = -1;
	*close = -1;
	
	while(index != -1)
	{
		index = nextIndexOf(str, '(', (index + 1), length);
		
		if(index == -1) return;
		
		*open = index;
		*close = findBracketMatch(str, index, length);
	}
}

int_32 findNextOperatorToSolve(const char* str, const size_t length)
{
	int_32 index = -1, i = 0;
	
	while(index == -1) 
	{
		index = indexOf(str, order[i++], length);
		
		if(*(str + index) == '(')
		{
			index = -1;
			int_32 close = -1;
			
			findNextBrackets(str, &index, &close, length);
			continue;
		}
		if(isnegativesign(str, index, length)) index = -1;
	}
	
	return index;
}

int_32 findInnerExprStart(const char* str, const size_t operator_index, const size_t length)
{
	if(operator_index >= length) return -1;
	char c = *(str + operator_index);
	
	if(operator_index == 0) return 0;
	
	int_32 start = 0;
	
	if(c == '(' || c == '!') start = ((int_32) operator_index);
	else start = findPrevOperator(str, operator_index, length);
	
	if(start != 0 && isnegativesign(str, (start - 1), length)) start -= 1;
	
	return start;
}

int_32 findInnerExprEnd(const char* str, const size_t operator_index, const size_t length)
{
	char c = *(str + operator_index);
	
	if(operator_index >= length) return -1;
	
	fprintf(stdout, "findInnerExpressionEnd passed str: \"%s\" operaotr_index: %zu length: %zu\n", str, operator_index, length);
	
	int_32 end = (((int_32) length) - 1);
	
	if(c == ')') end = ((int_32) operator_index);
	else if(c == '(') return findBracketMatch(str, operator_index, length);
	else
	{
		end = ((int_32) operator_index);
		do
		{
	        end = (findNextOperator(str, (end + 1), length));
		} while(isnegativesign(str, end, length));
	}
	
	return end;
}

void findNextExpression(const char* str, int_32* start, int_32* end, const size_t length)
{
	*start = findNextOperatorToSolve(str, length);
	
	*end = findInnerExprEnd(str, ((size_t) * start), length);
	if(*(str + *start) != '(' && *(str + *start) != '!') *start = findInnerExprStart(str, ((size_t) *start), length);
}

int_32 addMulti(const char* str, const size_t index, const size_t length)
{
	if(index >= length) return -1;
	
	char c = *(str + index), former = (index != 0) ? *(str + (index - 1)) : '\0', latter = (index < (length - 1)) ? *(str + (index + 1)) : '\0';
	
	fprintf(stdout, "%zu) C: '%c'[%d] Latter: '%c'[%d] Former: '%c'[%d]\n", index, c, ((int_8) c), latter, ((int_8) latter), former, ((int_8) former));
	
	if((c == '(' && (isalphachar(former) || ismathconstant(former) || former == ')')) || isalphachar(c) && (ismathconstant(former) || former == ')')) return ((int_32) index); 
	if(c == ')' && (isalphachar(latter) || ismathconstant(latter) || latter == '(')) return (((int_32) index) + 1);
	
	return -1;
}

size_t addExtras(char* dest, const char* str, const size_t dest_size, const size_t length)
{
	char c = *str, former = '\0', latter = ((length - 1) > 0) ? *(str + 1) : '\0';
	
	char* temp = (char*) malloc(dest_size);
	snprintf(temp, dest_size, "%s", str);
	
	size_t temp_length = strlen(temp);
	
	int_32 add = -1;
	uint_16 added = 0;
	
	for(size_t i = 0; i < temp_length; i++)
	{
		if(i > 0)
		{
			former = c;
			c = latter;
			if(i < (temp_length - 1)) latter = *(temp + (i + 1));
		}
		
		add = addMulti(temp, i, strlen(temp));
		fprintf(stdout, "Add '*' at %d.\n", add);
		if(add != -1) 
		{
			strAdd(temp, temp, '*', ((size_t) add), dest_size, strlen(temp));
			temp_length = strlen(temp);
			
			added++;
		}
	}
	
	snprintf(dest, dest_size, "%s", temp);
	free(temp);
	
	return ((size_t) added);
}

bool isReducable(const char* str, const size_t length)
{
	size_t operators = countOperators(str, length), checked = 0;
	if(operators == 0) return false;
	
	int_32 index = findNextOperator(str, 0, length);
	
	if(operators == 1)
	{
		char* one = (char*) malloc(sizeof(char) * 32), *two = (char*) malloc(sizeof(char) * 32);
		
		substring(one, str, 0, index, length);
		substring(two, str, (index + 1), length, length);
		
		if(isalphastr(one, strlen(one)) || isalphastr(two, strlen(two)))
		{
			free(one);
			free(two);
			
			return false;
		}
		
		free(one);
		free(two);
		
		return true;
	}
	
	bool reducable = true;
	int_32 start = -1, end = -1;
	
	char* temp = (char*) malloc(sizeof(char) * 64);
	snprintf(temp, 64, "%s", str);
	
	for(size_t checked = 0; checked < operators; checked++)
	{
		index = findNextOperator(str, (index + 1) length);
		
		begin = findInnerExpStart(str, index, length);
		end = findInnerExprEnd(str, index, length);
		
		substring(temp, begin, end, length);
		
		if(isReducable(temp, strlen(temp)) return true;
	}
	
	return false;
}

void solve(char* dest, const char* str, const size_t dest_size, const size_t length)
{
	if(!isvalidexpsn(str, length))
	{
		fprintf(stderr, "Error: solve passed invalid expression \"%s\".\n", str);
		
		return;
	}
	
	int_32 begin = -1, end = -1;
	
	char* expr = (char*) malloc(sizeof(char) * 64), *temp = (char*) malloc(sizeof(char) * 64);
	
	snprintf(expr, 64, "%s", str);
	
	findNextExpression(expr, &begin, &end, strlen(expr));
    substring(temp, expr, begin, end, strlen(expr));
    
    solve(temp, temp, 64, strlen(temp));
    
    strDelMid
}

#ifdef _cplusplus
}
#endif

#endif