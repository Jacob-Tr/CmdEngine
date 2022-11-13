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

bool substring(char* dest, const char* src, const size_t begin, const size_t end, const size_t dest_size)
{
    size_t end_override = end;
    if(end > strlen(src))
    {
        end_override = strlen(src);
        
        fprintf(stderr, "Warning: substring turnicated specified end [%zu] to string length [%zu] for string \"%s\".\n", end, end_override, src);
    }
    
    if(begin >= end_override)
    {
        fprintf(stderr, "Warning: substring could not derive string %zu to %zu in string \"%s\".\n", begin, end_override, src);
        
        snprintf(dest, dest_size, "%s", src);
        return true;
    }
    
    if(dest_size < ((end_override) - begin))
    {
        fprintf(stderr, "Error: Substring could not extract index range %zu to %zu of string \"%s\" into destination of provided size %zu.\n", begin, end_override, src, dest_size);
        
        return false;
    }

    snprintf(dest, ((end_override + 1) - begin), "%s", (src + begin));
    
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
        
        if(*(string + i) == c) return i;
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
    
    for(size_t i = length; i >= 0; i--) if(*(string + i) == c) return i;
    
    return -1;
}

int_32 nextIndexOf(const char* string, const char c, const size_t index, const size_t length)
{
    if(index >= length)
    {
        fprintf(stderr, "Error: nextIndexOf index [%ld] is greater than or matches length %ld.\n", index, length);
        return -1;
    }
    
    const size_t dest_len = (length - index);
    char* temp = (char*) malloc(dest_len * sizeof(char));
    
    substring(temp, string, index, length, dest_len);
    int_32 next_index = indexOf(temp, c, dest_len);
    
    if(next_index != -1) next_index += index;
    
    free(temp);
    return next_index;
}

int_32 prevIndexOf(const char* string, const char c, const size_t index, const size_t length)
{
    if(index >= length)
    {
        fprintf(stderr, "Error: prevIndexOf index [%ld] is greater than or matches length %ld.\n", index, length);
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
            if(*(string + i) == *(substring)) *begin = i;
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
            *end = (i + 1);
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
        fprintf(stderr, "Error: strdel could not remove substring index %ld to %ld from \"%s\".\n", begin, end, src);
        
        return false;
    }
    
    char* new_str = (char*) malloc((length - (end - begin)) * sizeof(char));
    
    snprintf(new_str, (begin + 1), "%s", src);
    snprintf((new_str + (begin)), length, "%s", (src + end));
    
    snprintf(dest, length, "%s", new_str);
    
    free(new_str);
    
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
    if(dest_size < index)
    {
        fprintf(stderr, "Error: strAdd cannot insert character %c into destination string \"%s\" of length %zu at index %zu in destination array of size %zu.\n", c, src, src_len, index, dest_size);
        
        return false;
    }

    char* temp = (char*) malloc(src_len * sizeof(char));
    
    if(!substring(temp, src, 0, index + 1, strlen(src)))
    {
        fprintf(stderr, "Error: strAdd - substring failed on string \"%s\" of length %zu between index %zu and %zu\n", src, src_len, ((size_t) 0), (index + 1));
        
        free(temp);
        return false;
    }
    *(temp + (index + 1)) = c;
    if(!substring(((temp + index) + 2), src, (index + 1), strlen(src), (strlen(src) + 1)))
    {
        fprintf(stderr, "Error: strAdd - substring failed on string \"%s\" of length %zu between index %zu and %zu\n", src, src_len, (index + 1), src_len);
        
        free(temp);
        return false;
    }
    
    snprintf(dest, ((src_len * sizeof(char)) + 1), "%s", temp);
    
    free(temp);
    return true;
}

bool escapeStrPrcnts(char* dest, const char* src, const size_t dest_size, const size_t src_len)
{
    const size_t percents = countChars(src, '\%', src_len);

    if((dest_size + percents) < src_len)
    {
        fprintf(stderr, "Error: sanitizeStr cannot apply formatted result of sanitized string \"%s\" into destination of size %zu.\n", src, dest_size);
        
        return false;
    }
    size_t index = indexOf(src, '\%', src_len);
    
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
        
        index = nextIndexOf(temp, '\%', (index + 1), strlen(temp));
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
}

// NEW ADDITIONS

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


#ifdef __cplusplus 
}
#endif

#endif