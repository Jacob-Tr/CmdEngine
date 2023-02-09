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
	if(index >= length) return -1;
	int_32 oper = -1, lowest = -1;
	
	for(size_t i = 0; i < OPERATORS; i++)
	{
		oper = prevIndexOf(str, index, order[i], length);
		
		if(oper >= 0 && lowest < oper) lowest = oper;
	}
	
	return (lowest >= 0) ? lowest : 0;
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
		
		if(*(str + index) == '(') return index;
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
	
	if(isprefixoperator(c)) start = ((int_32) operator_index);
	else start = findPrevOperator(str, operator_index, length);
	
	if(start != 0 && isnegativesign(str, (start - 1), length)) start -= 1;
	
	return start;
}

int_32 findInnerExprEnd(const char* str, const size_t operator_index, const size_t length)
{
	char c = *(str + operator_index);
	
	if(operator_index >= length) return -1;
	
	int_32 end = (((int_32) length) - 1);
	
	if(issuffixoperator(c)) return ((int_32) operator_index);
	else if(isprefixoperator(c)) return findBracketMatch(str, operator_index, length);
	else
	{
		end = ((int_32) operator_index);
		do
		{
	        end = (findNextOperator(str, (end + 1), length));
		} while(isnumericoperator(str, end, length));
	}
	
	return end;
}

void findNextExpression(const char* str, int_32* start, int_32* end, const size_t length)
{
	*start = findNextOperatorToSolve(str, length);
	
	*end = findInnerExprEnd(str, ((size_t) * start), length);
	if(!isprefixoperator(*(str + *start))) *start = findInnerExprStart(str, ((size_t) *start), length);
}

int_32 addMulti(const char* str, const size_t index, const size_t length)
{
	if(index >= length) return -1;
	
	char c = *(str + index), former = (index != 0) ? *(str + (index - 1)) : '\0', latter = (index < (length - 1)) ? *(str + (index + 1)) : '\0';
	
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

static inline bool isReducable(const char* str, const size_t length)
{
	if(isalphanumeric(str, length)) return false;
	
	char c, former = '\0', latter = '\0';
	int_32 index = 0;
	for(index = 0; index < length; index++)
	{
		c = *(str + index);
		if(!isoperator(c) || isnegativesign(str, index, length)) continue;
		
		return true;
	}
	
	return false;
}

static inline void solve(char* dest, const char* src, const size_t dest_size, const size_t length)
{
	snprintf(dest, dest_size, "%s", src);
	addExtras(dest, dest, dest_size, length);
	int_32 begin, end;
	findNextExpression(dest, &begin, &end, strlen(dest));
	
	size_t temp_size = ((end - begin) + 1);
	
	char* temp = (char*) malloc(sizeof(char) * temp_size);
	substring(temp, dest, begin, (end + 1), temp_size);
	
	printf("Reduced to: %s\n", temp);
	
	//begin = 0, end = (strlen(temp) - 1)
	
	char first = *temp, last = *(temp + (strlen(temp) - 1));
	
	if(isbracket(first) && isbracket(last))
	{
	    substring(temp, temp, ((size_t) begin + 1), ((size_t) end), temp_size);
	    
	    if(isReducable(temp, strlen(temp))) solve(temp, temp, temp_size, strlen(temp));
	    
	    strDelMid(dest, dest, begin, (end + 1), strlen(dest));
	    strInsert(dest, dest, temp, ((size_t) begin), dest_size, strlen(dest), strlen(temp));
	    
	    free(temp);
	    return;
	}
	
	fprintf(stdout, "%d - %d\n", begin, end);
}

#ifdef _cplusplus
}
#endif

#endif