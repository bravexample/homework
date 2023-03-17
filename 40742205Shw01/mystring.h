#include <stddef.h>

char *mystrchr(const char *s, int c) {
    if (!s)
        return NULL;

    for (; *s; s++)
        if (*s == c)
            return (char *)s;
    
    if (!c)
        return (char *)s;
    
    return NULL;
}

char *mystrrchr(const char *s, int c) {
    if (!s)
        return NULL;

    const char *temp = NULL;
    for (; *s; s++)
        if (*s == c)
            temp = s;
    
    if (!c)
        return (char *)s;
    
    if (temp)
        return (char *)temp;
    
    return NULL;
}

size_t mystrspn(const char *s, const char *accept) {
    if (!s || !accept)
        return 0;

    size_t count = 0, i = 0;
    for (; *s; s++, count++) {
        for (i = 0; accept[i]; i++)
            if (*s == accept[i])
                break;
        
        if (!accept[i])
            return count;
    }

    return count;
}

size_t mystrcspn(const char *s, const char *reject) {
    if (!s)
        return 0;

    if (!reject)
        reject = "";

    size_t count = 0, i = 0;
    for (; *s; s++, count++) {
        for (i = 0; reject[i]; i++)
            if (*s == reject[i])
                break;
        
        if (reject[i])
            return count;
    }

    return count;
}

char *mystrpbrk(const char *s, const char *accept) {
    if (!s)
        return NULL;
    
    if (!accept)
        return (char *)s;

    for (; *s; s++)
        for (size_t i = 0; accept[i]; i++)
            if (*s == accept[i])
                return (char *)s;
    
    return NULL;
}

char *mystrstr(const char *haystack , const char *needle) {
    if  (!haystack || !needle)
        return NULL;

    size_t i = 0;
    for (; *haystack; haystack++)
        if (*haystack == *needle) {
            for (i = 0; needle[i]; i++)
                if (haystack[i] != needle[i])
                    break;
            
            if (!needle[i])
                return (char *)haystack;
        }

    return NULL;
}


char *mystrtok_ptr  = NULL;
char *mystrtok_save = NULL;
char *mystrtok(char *str, const char *delim) {
    if (!delim)
        delim = "";

    if (!str) {
        if (!mystrtok_save)
            return NULL;
        
        mystrtok_ptr = mystrtok_save;
    } else
        mystrtok_ptr = str;

    size_t i = 0;
    for (; *mystrtok_ptr; mystrtok_ptr++) {
        for (i = 0; delim[i]; i++)
            if (*mystrtok_ptr == delim[i])
                break;
        
        if (!delim[i])
            break;
    }

    if (!*mystrtok_ptr) {
        mystrtok_save = NULL;
        return NULL;
    }

    size_t j = 0;
    for (i = 0; mystrtok_ptr[i]; i++)
        for (j = 0; delim[j]; j++)
            if (mystrtok_ptr[i] == delim[j]) {
                mystrtok_ptr[i] = '\0';
                mystrtok_save = *(mystrtok_ptr + i + 1) ? mystrtok_ptr + i + 1 : NULL;
                return mystrtok_ptr;
            }

    mystrtok_save = NULL;
    return mystrtok_ptr;
}