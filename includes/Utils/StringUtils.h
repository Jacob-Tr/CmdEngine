#ifndef STR_UTILS_H
#define STR_UTILS_H

#ifdef __cplusplus 
extern "C"
{
#endif

bool isnumber(const char c) {return (c >= '0' && c <= '9');}

bool isnumeric(const char* str, const size_t length)
{
    for(size_t i = 0; i < length; i++) if(!isnumber(*(str + i))) return false;
    return true;
}

bool isalphachar(const char c) {return ((bool) (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));}

bool ispunctuation(const char c) {return (c == '.' || c == '\'' || c == '"' || c == ':' || c == ';' || c == '!' || c == '?' || c == '(' || c == ')' || c == ',' || c == '/');}

bool isalphastr(const char* str, const size_t length) 
{
	for(size_t i = 0; i < length; i++) if(!isalphachar(*(str + i))) return false;
	return true;
}

bool isalphanumeric(const char* str, const size_t length) 
{
	char c = '\0';
	for(size_t i = 0; i < length; i++)
	{
		c = *(str + i);
		if(c == '\0') 
		{
			if(i == 0) return false;
			break;
		}
		
		if(!isnumber(c) && !isalphachar(c)) return false;
	}
	
	return true;
}

bool substring(char* dest, const char* src, const size_t begin, const size_t end, const size_t dest_size)
{
    size_t end_override = end;
    if(end > strlen(src))
    {
        end_override = strlen(src);
        
        #ifdef DEBUG
            fprintf(stderr, "Warning: substring turnicated specified end [%zu] to string length [%zu] for string \"%s\".\n", end, end_override, src);
        #endif
    }
    
    if(begin >= end_override)
    {
    	#ifdef DEBUG
            fprintf(stderr, "Warning: substring could not derive string %zu to %zu in string \"%s\".\n", begin, end_override, src);
        #endif
        
        snprintf(dest, dest_size, "%s", src);
        return true;
    }
    
    if(dest_size < ((end_override) - begin))
    {
    	#ifdef DEBUG
            fprintf(stderr, "Error: Substring could not extract index range %zu to %zu of string \"%s\" into destination of provided size %zu.\n", begin, end_override, src, dest_size);
        #endif
        
        return false;
    }

    snprintf(dest, ((end_override - begin) + 1), "%s", (src + begin));
    
    return true;
}

int_32 indexOf(const char* string, const char c, const size_t length)
{
    for(size_t i = 0; i < length; i++)
    {
        if(i > INT_MAX)
        {
            fprintf(stderr, "Error: indexOf overflow searching for \'%c\' in \"%s\".", c, string);
            return -1;
        }
        
        if(*(string + i) == c) return ((int_32) i);
    }
    
    return -1;
}

int_32 lastIndexOf(const char* string, const char c, const size_t length)
{
    if(length > INT_MAX)
    {
        fprintf(stderr, "Error: lastIndexOf overflow searching for \'%c\' in \"%s\".", c, string);
        
        return -1;
    }
    
    for(size_t i = (length - 1); i >= 0; i--) if(*(string + i) == c) return ((int_32) i);
    
    return -1;
}

int_32 nextIndexOf(const char* string, const char c, const size_t index, const size_t length)
{
    if(index >= length)
    {
        fprintf(stderr, "Error: nextIndexOf index [%zu] is greater than or matches length %zu.\n", index, length);
        return -1;
    }
    
    const size_t dest_len = (length - index);
    char* temp = (char*) malloc(dest_len * sizeof(char));
    
    substring(temp, string, index, length, dest_len);
    int_32 next_index = indexOf(temp, c, dest_len);
    
    if(next_index != -1) next_index += ((int_32) index);
    
    free(temp);
    return next_index;
}

int_32 prevIndexOf(const char* string, const char c, const size_t index, const size_t length)
{
    if(index >= length)
    {
    	#ifdef DEBUG
            fprintf(stderr, "Error: prevIndexOf index [%zu] is greater than or matches length %zu.\n", index, length);
        #endif
        return -1;
    }
    
    int_32 prev_index = lastIndexOf(string, c, index);
    
    if(prev_index == index) prev_index = lastIndexOf(string, c, (index - 1));
    
    return prev_index;
}

bool strtoken(char* dest, const char* src, const char seperator, size_t* index, const size_t dest_size)
{
    const size_t src_len = strlen(src);
    if(*index >= src_len)
    {
        fprintf(stderr, "Error: Index [%zu] is greater then source length of %zu.\n", *index, src_len);
        return false;
    }
    
    if(*(src + *index) == seperator)
    {
        fprintf(stderr, "Warning: strtoken found seperator [%c] at index [%zu] in string \"%s\".\n", seperator, *index, src);
        
        *index += 1;
        return strtoken(dest, src, seperator, index, dest_size);
    }
    
    char* temp = (char*) malloc(dest_size * sizeof(char));
    
    int_32 end = nextIndexOf(src, seperator, *index, src_len);
    
    if(end == -1) substring(temp, src, *index, src_len, dest_size);
    else substring(temp, src, *index, end, dest_size);
    
    snprintf(dest, dest_size, "%s", temp);
    
    if(end == -1) *index = strlen(src);
    else *index = ++end;
    
    free(temp);
    return true;
}

bool strfind(const char* string, const char* substring, int_32* begin, int_32* end, const size_t sub_len, const size_t length)
{
    if((length < sub_len) || (length == 0))
    {
        *begin = -1;
        *end = -1;
        
        return false;
    }
    
    char current = '\0', sub_cur = *(substring);
    *begin = indexOf(string, sub_cur, length);
    
    for(size_t i = *begin; i < length; i++)
    {
        current = *(string + i);
        
        if(*begin == -1)
        {
            if(*(string + i) == *(substring)) *begin = ((int_32) i);
            continue;
        }
        
        sub_cur = *(substring + (i - *begin));
        
        if(sub_cur != current)
        {
            *begin = -1;
            continue;
        }
        else if((*begin - i) >= sub_len)
        {
            *end = (((int_32) i) + 1);
            break;
        }
    }
    
    return (*begin >= 0 && *end >= 1);
}

bool strDel(char* dest, const char* src, const size_t index, const size_t dest_size, const size_t src_len)
{
    char* temp = (char*) malloc(src_len * sizeof(char));
    
    substring(temp, src, 0, index, src_len);
    substring((temp + index), src, (index + 1), src_len, src_len);
    
    snprintf(dest, (src_len * sizeof(char)), "%s", temp);
    
    free(temp);
    return true;
}

bool strDelMid(char* dest, const char* src, const size_t begin, const size_t end, const size_t length)
{
    if(begin >= end || end > length)
    {
    	#ifdef DEBUG
            fprintf(stderr, "Error: strdel could not remove substring index %zu to %zu from \"%s\".\n", begin, end, src);
        #endif
        
        return false;
    }
    
    char* new_str = (char*) malloc((length - (end - begin)) * sizeof(char));
    
    snprintf(new_str, begin, "%s", src);
    snprintf((new_str + (begin + 1)), length, "%s", (src + end));
    
    snprintf(dest, length, "%s", new_str);
    
    free(new_str);
    
    return true;
}

bool strInsert(char* dest, const char* src_one, const char* src_two, const size_t index, const size_t dest_size, const size_t one_len, const size_t two_len)
{
	if((one_len == 0) || (two_len == 0)) return false;
	
	if((one_len + two_len) > dest_size)
	{
		fprintf(stderr, "Error: strInsert cannot insert string \"%s\" of length %zu into index %zu of string \"%s\" of length %zu and store the result in destination of size %zu.\n", src_one, one_len, index, src_two, two_len, dest_size);
		
		return false;
	}
	
	char* temp = (char*) malloc(sizeof(char) * dest_size);
	
	if(index != 0) substring(temp, src_one, 0, index, one_len);
	substring((temp + index), src_two, 0, two_len, two_len);
	substring((temp + (strlen(src_two) + index)), src_one, index, one_len, (one_len - index));
	
	snprintf(dest, dest_size, "%s", temp);
	free(temp);
	
	return true;
}

bool strContainsChar(const char* string, const char ch, const size_t length) {return (indexOf(string, ch, length) != -1);}

bool strContains(const char* string, const char* string2, const size_t length, const size_t length2)
{
    if(length2 > length) return false;
    
    char ch = *string2;
    int_32 index = (indexOf(string, ch, length) + 1), found = 1;
    
    if(index == 0) return false;
    
    for(size_t i = index; i < length; i++)
    {
        if(found == length2) return true;
        if(i >= (length2 - 1)) return false;
        
        if(*(string + i) != *(string2 + (i - index))) return strContains((string + i), string2, (length - i), length2);
    }
    
    if(found == length2) return true;
    return false;
}

bool strMatch(const char* string, const char* string2, const size_t length) 
{
    return (strncmp(string, string2, length) == 0);
}

size_t countChars(const char* src, const char ch, const size_t length)
{
    size_t ret = 0;
    
    for(size_t i = 0; i < length; i++) if(*(src + i) == ch) ret++;
    
    return ret;
}

bool strAdd(char* dest, const char* src, const char c, const size_t index, const size_t dest_size, const size_t src_len)
{
    if(dest_size < index || index > src_len)
    {
        fprintf(stderr, "Error: strAdd cannot insert character %c into destination string \"%s\" of length %zu at index %zu in destination array of size %zu.\n", c, src, src_len, index, dest_size);
        
        return false;
    }

    char* temp = (char*) malloc(dest_size);
    
    if(index != 0 && !substring(temp, src, 0, (index + 1), src_len))
    {
        fprintf(stderr, "Error: strAdd - substring failed on string \"%s\" of length %zu between index %zu and %zu\n", src, src_len, ((size_t) 0), (index + 1));
        
        free(temp);
        return false;
    }
    *(temp + index) = c;
    if((index > src_len) || !substring(((temp + index) + 1), src, index, src_len, src_len))
    {
        fprintf(stderr, "Error: strAdd - substring failed on string \"%s\" of length %zu between index %zu and %zu\n", src, src_len, index, src_len);
        
        free(temp);
        return false;
    }
    
    snprintf(dest, ((src_len * sizeof(char)) + 2), "%s", temp);
    
    free(temp);
    return true;
}

/*bool escapeStrPrcnts(char* dest, const char* src, const size_t dest_size, const size_t src_len)
{
    const size_t percents = countChars(src, '%', src_len);

    if((dest_size + percents) < src_len)
    {
        fprintf(stderr, "Error: sanitizeStr cannot apply formatted result of sanitized string \"%s\" into destination of size %zu.\n", src, dest_size);
        
        return false;
    }
    size_t index = indexOf(src, '%', src_len);
    
    char* temp = (char*) malloc((src_len + percents) * sizeof(char));
    snprintf(temp, src_len, "%s", src);
    
    while(index != -1)
    {
        if(index != 0 && (*(src + (index - 1)) == '\\' && (index == 1 || *(src + (index - 2)) != '\\'))) 
        {
            ++index;
            continue;
        }
        
        strAdd(temp, temp, index, '\\', (src_len + percents), strlen(temp));
        
        index = nextIndexOf(temp, '%', (index + 1), strlen(temp));
    }
    
    snprintf(dest, strlen(temp), "%s", temp);
    
    free(temp);
    return true;
}

bool isStrCompressed(const char* str, const size_t length)
{
    for(size_t i = 0; i < length; i++) if(*(str + i) < (char) 10 && *(str + i) != '\0') return true;
    return false;
}

typedef char cmp_char;
#define cmp_strlen(string) (compressedStrlen((string), strlen((string))) + 1)

size_t compressedStrlen(const char* string, const size_t length);

bool compressText(cmp_char* dest, const char* src, const size_t dest_size, const size_t src_len)
{
    char* temp = (char*) malloc(dest_size * sizeof(char)), current = '\0';
    size_t i = 0, ii = 0, repeat = 1;
    
    for(i = 0; i < src_len; i++)
    {
        current = *(src + i);
        if(current == '\0') break;
    
        while(current == *(src + (i + repeat)) && (++repeat <= 9)) continue;
        
        if(repeat == 1) 
        {
            *(temp + ii++) = current;
            continue;
        }
        
        *(temp + ii++) = (char) repeat;
        *(temp + ii++) = current;
        
        i += (repeat - 1);
        repeat = 1;
    }
    
    *(temp + (strlen(temp) + 1)) = '\0';
    
    snprintf(dest, strlen(temp), "%s", temp);
    
    free(temp);
    return true;
}

bool expandCompressedText(char* dest, const cmp_char* src, const size_t dest_size, const size_t src_len)
{
    char* temp = (char*) malloc(dest_size * sizeof(char)), current = '\0', repeat = '\0';
    size_t ii = 0;
    
    for(size_t i = 0; i < src_len; i++)
    {
        current = *(src + i);
        if(current == '\0') break;
        
        if(repeat == '\0' && (current > '\0' && current < (char) 10))
        {
            repeat = current;
            continue;
        }
        if(repeat != '\0')
        {
            const size_t base = ii;
            for(ii = ii; ii < (base + (size_t) repeat); ii++) *(temp + ii) = current;
            repeat = '\0';
            continue;
        }
        *(temp + ii++) = current;
    }
    
    snprintf(dest, strlen(temp), "%s", temp);
    
    free(temp);
    return true;
}

size_t compressedStrlen(const cmp_char* str, const size_t length)
{
    if(strlen(str) == 0) return 0;
    
    size_t size = 0;
    char current = *(str);
    
    if(!isStrCompressed(str, length))
    {
        char* temp = (char*) malloc(length * sizeof(char));
        
        compressText(temp, str, length, strlen(str));
        
        size = strlen(temp);
        free(temp);
    }
    else
    {
        for(size_t i = 0; i < length; i++)
        {
            current = *(str + i);
        
            if(current > '\0' && current < (char) 10) {size += ((size_t) current);}
            else if((i == 0 || *(str + (i - 1)) > (char) 9) && current != '\0') {size++;}
        }
    }
    
    return size;
}

static inline void fprintcmp(FILE* file, const char* str)
{
    size_t temp_size = (sizeof(char) * (strlen(str) * 2)), length = strlen(str) + 1;

    char* temp = (char*) malloc(temp_size), c = '\0';
    size_t skip = 0;
    
    snprintf(temp, length, "%s", str);
    
    for(size_t i = 0; i < length; i++)
    {
        fprintf(stdout, "%zu\n", i);
        c = *(str + i);
        if(c < (char) 9 && c != '\0')
        {
            if(!strAdd(temp, temp, '[', i, temp_size, (strlen(temp) + 1)))
            {
                fprintf(stderr, "Warning: fprintcmp failed call to strInsert adding \'%c\'[code: %d] to string \"%s\" at index %zu.\n", '[', '[', temp, i);
            }
            *(temp + (i + 1)) = *(temp + (i + 1)) + '0';
            if(!strAdd(temp, temp, ']', (i + 2), temp_size, (strlen(temp) + 1)))
            {
                fprintf(stderr, "Warning: fprintcmp failed call to strInsert adding \'%c\'[code: %d] to string \"%s\" at index %zu.\n", ']', ']', temp, i);
            }
            
            skip += 2;
        }
        
        length += skip;
        i += skip;
        skip = 0;
    }
    
    *(temp + (strlen(temp) + 1)) = '\0';
    
    fprintf(file, temp);
    free(temp);
}*/

bool strRMChar(char* dest, const char* src, const char c, const size_t dest_size, const size_t src_len)
{
    char* temp = (char*) malloc(src_len * sizeof(char));
    snprintf(temp, (src_len * sizeof(char)), "%s", src);
    
    size_t index = indexOf(temp, c, strlen(temp));
    
    while(index != -1)
    {
        strDel(temp, temp, index, (src_len * sizeof(char)), strlen(temp));
        index = indexOf(temp, c, strlen(temp));
    }
    
    snprintf(dest, (strlen(temp) * sizeof(char)), "%s", temp);
    
    free(temp);
    return true;
}

#define form(num) str_num

void strForm(char* dest, const char* src, const char align, const uint_8 strings, const size_t dest_size, const size_t lengths[])
{
	size_t length = 0, largest = 0;
	int_32* index_arr = (int_32*) alloca(sizeof(size_t) * strings), index = 0, prev_index = 0;
    char** str_arr = (char**) alloca(sizeof(char*) * strings);
	
	for(size_t i = 0; i < strings; i++) length += lengths[i];
		
	for(size_t i = 0; i < strings; i++)
	{
		str_arr[i] = (char*) malloc(sizeof(char) * lengths[i]);
		memset(str_arr[i], '\0', (sizeof(char) * lengths[i]));
		
		substring(str_arr[i], src, index, (index + lengths[i]), (sizeof(char) * lengths[i]));
		
		index = indexOf(str_arr[i], align, lengths[i]);
		
		index_arr[i] = index;
		index = (prev_index + ((int_32) lengths[i]));
		prev_index = index;
		
		if(index_arr[i] > largest && index_arr[i] > 0) largest = index_arr[i];
	}
	
	const size_t add_max = (sizeof(char) * largest);
	
	char* new_str = (char*) alloca(sizeof(char) * (length + (largest * strings))), *add_str = (char*) alloca(add_max);
	
	memset(add_str, '\0', add_max);
	
	size_t add = 0;
	
	for(size_t i = 0; i < strings; i++)
	{
		if(index_arr[i] <= largest) add = (largest - ((size_t) index_arr[i]));
		else add = 0;
		
		memset(add_str, ' ', add);
		
		if(i == 0) snprintf(new_str, ((add_max + lengths[i]) + 1), "%s%s\n", add_str, str_arr[i]);
		else snprintf(new_str, ((add_max + strlen(new_str) + lengths[i]) + 1), "%s%s%s\n", new_str, add_str, str_arr[i]);
		
		free(str_arr[i]);
		
		memset(add_str, '\0', add_max);
	}
	
	snprintf(dest, dest_size, "%s", new_str);
	
	//free(new_str);
}

#ifdef __cplusplus 
}
#endif

#endif