#ifndef FILE_H
#define FILE_H

typedef enum
{
   FILE_DATA,
   FILE_TYPES
} ftype;

typedef struct
{
    char* path;
    size_t path_len;
    ftype type;
    FILE* file;
    bool open;
    size_t length;
} file;
#define invalid_file (file*) NULL
uint_32 files = 0;

char* file_ext[FILE_TYPES] =
{
    (char*) ".ini"
};

#define MAX_DIS_CHARS 9 

char disallowed_chars[] = {':', '*',     '?', '"', '<', '>', '|'}; 

#ifdef _WIN32

#define MAX_DIS_NAMES 24 
char disallowed_names[MAX_DIS_NAMES][4] = 
{     
    "CON", 
    "PRN", 
    "AUX", 
    "NUL", 
    "COM1",     
    "COM2",     
    "COM3", 
    "COM4", 
    "COM5", 
    "COM6", 
    "COM7", 
    "COM8",     
    "COM9",
    "COM0",
    "LPT1",     
    "LPT2", 
    "LPT3", 
    "LPT4", 
    "LPT5", 
    "LPT6",     
    "LPT7",     
    "LPT8", 
    "LPT9", 
    "LPT0" 
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif

bool strContainsChar(const char* str,const char ch, const size_t length);

bool doesStrContainDisallowedChars(const char* string) 
{     
    for(size_t i = 0; i <= MAX_DIS_CHARS; i++) if(strContainsChar(string, disallowed_chars[i], strlen(string))) return true;
    
    return false; 
} 

bool isValidWinFileName(const char* string) 
{
#ifdef _WIN32
    if(doesStrContainDisallowedChars(string)) return false;
    
    for(size_t i = 0; i < MAX_DIS_NAMES; i++) if(strMatch(string, disallowed_names[i], strlen(string))) return false;
#endif
    return true; 
} 

bool isValidWinDir(const char* string)
{
    if(strlen(string) < 3) return false;

    char* disk = (char*) malloc(3 * sizeof(char));
    
    snprintf(disk, 3, "%s", string);
    
    if((*disk > 'Z' || *disk < 'A') || *(disk + 1) != ':' || *(disk + 2) != '/') 
    {
        free(disk);
        return false;
    }
    
    free(disk);
    return true;
}

bool isValidDirectory(const char* string) 
{ 
    if(doesStrContainDisallowedChars(string)) return false; 
    
#ifdef _WIN32
    return isValidWinDir(string);
#endif

    return true; 
}

bool isValidFileName(const char* string, const size_t length)
{
#ifdef _WIN32
    if(!isValidWinFileName(string)) return false;
#endif

    if(doesStrContainDisallowedChars(string)) return false;
    
    if(strContainsChar(string, '/', length) || strContainsChar(string, '\\', length)) return false;
    
    return true;
}

bool isValidFileType(const ftype type) {return (type < 0 || type > FILE_TYPES);}

char* getFileTypeExtension(const ftype type) {
    if(!isValidFileType(type)) return "";
    return file_ext[type];
}

#define File(name, path, type, name_len, path_len) initFile((name), (path), (type), (name_len), (path_len))
file* initFile(const char* path, const char* name, const ftype type, const size_t path_len, const size_t name_len)
{
    if(path_len == 0 || name_len == 0)
    {
        fprintf(stderr, "Error: initFile could initialize file with path length %zu and file name length %zu.\n", path_len, name_len);
        
        return invalid_file;
    }
    
    if(!isValidFileType(type))
    {
        fprintf(stderr, "Error: initFile could initialize file with invalid file type %d.\n", (uint_32) type);
        
        return invalid_file;
    }
    
    if(!isValidDirectory(path))
    {
        fprintf(stderr, "Error: initFile could initialize file with invalid path \"%s\".\n", path);
        
        return invalid_file;
    }
    
    if(!isValidFileName(name, strlen(name)))
    {
        fprintf(stderr, "Error: initFile could initialize file with invalid file name \"%s\".\n", name);
        
        return invalid_file;
    }
    
    char* xtnsn = getFileTypeExtension(type);
    const size_t length = ((path_len + name_len + strlen(xtnsn)) + 1);
    char* f_name = (char*) malloc(length * sizeof(char));
    
    snprintf(f_name, length, "%s/%s%s", path, name, xtnsn);
    
    FILE* f = NULL;
    fopen_s(&f, f_name, "R");
    
    if(f == NULL)
    {
        fprintf(stderr, "Error: initFile could not create a file stream for file \"%s\".\n", f_name);
        
        free(f);
        free(f_name);
        return invalid_file;
    }
    
    file* file_strct = (file*) malloc(sizeof(file));
    
    file_strct->path = f_name;
    file_strct->path_len = length;
    file_strct->file = f;
    file_strct->type = type;
    file_strct->open = false;
    file_strct->length = fseek(file_strct->file, 0, SEEK_END);
    
    fseek(file_strct->file, 0, SEEK_SET);
    fclose(f);
    
    files++;
    
    return file_strct;
}

bool isFileOpen(const file f) {return (f.open);}

char* getFileName(const file f) {return f.path;}

size_t getFileNameLen(const file f) {return f.length;}

ftype getFileType(const file f) {return f.type;}

bool FOpen(file* f, const char* mode) 
{
    if(f == invalid_file)
    {
        fprintf(stderr, "Error: FOpen called on invalid file.\n");
        return false;
    }

    if(isFileOpen(*f))
    {
        fprintf(stderr, "Error: FOpen called on already open file: \"%s\".\n", f->path);
        
        return false;
    }
    
    freopen_s(&f->file, f->path, mode, f->file);
    
    if(f->file == NULL)
    {
        fprintf(stderr, "Error: FOpen has Insufficient permissions to open \"%s\" with filemode \"%s\" or file not found.\n", f->path, mode);
        
        return false;
    }
    
    f->open = true;
    return true;
}

bool FClose(file* f)
{
    if(f == invalid_file)
    {
        fprintf(stderr, "Error: FClose called on invalid file.\n");
        return false;
    }
    
    if(!isFileOpen(*f))
    {
        fprintf(stderr, "Error: FClose cannot close already closed file: \"%s\".\n", f->path);
        return false;
    }
    
    fclose(f->file);
    f->open = false;
    
    return true;
}

size_t FGetSize(file* f)
{
    if(f == invalid_file)
    {
        fprintf(stderr, "Error: FGetSize called on invalid file.\n");
        return 0;
    }
    
    bool close = false;
    if(!isFileOpen(*f))
    {
        if(FOpen(f, "R")) close = true;
        else
        {
            fprintf(stderr, "Error: FGetSize called on closed file: \"%s\" which failed to open.\n", f->path);
        
            return 0;
        }
    }
    
    size_t size = fseek(f->file, 0, SEEK_END);
    fseek(f->file, 0, SEEK_SET);
    
    if(close) FClose(f);
    
    return size;
}


bool FRead(char* dest, const file* f, const size_t dest_size)
{
    if(f == invalid_file)
    {
        fprintf(stderr, "Error: FRead called on invalid file.\n");
        return false;
    }
    
    if(!isFileOpen(*f))
    {
        fprintf(stderr, "Error: FRead called on closed file: \"%s\".\n", f->path);
        return false;
    }
    
    fseek(f->file, 0, SEEK_SET);
    fread(dest, sizeof(char), dest_size, f->file);
    
    return true;
}

bool FWrite(file* f, const char* content, const size_t length)
{
    if(f == invalid_file)
    {
        fprintf(stderr, "Error: FWrite called on invalid file.\n");
        return false;
    }
    
    if(!isFileOpen(*f))
    {
        fprintf(stderr, "Error: FWrite called on closed file: \"%s\".\n", f->path);
        return false;
    }
    
    f->length = fwrite(content, length, sizeof(char), f->file);
    fflush(f->file);
    
    return true;
}

void FDestruct(file* f)
{
    if(f == invalid_file)
    {
        fprintf(stderr, "Error: FDestruct called on invalid file.\n");
        return;
    }
    
    if(isFileOpen(*f)) FClose(f);
    
    free(f->path);
    
    file* temp = f;
    f = invalid_file;
    
    free(temp);
    
    files--;
}

#ifdef __cplusplus
}
#endif

#endif