#include <stdio.h>
#include <string.h>

int my_strcmp(char *str1, char *str2) 
{
    while (*str1 != '\0'&& *str1 == *str2) {
        str1++;
        str2++;
    }
    return (char)*str1 - (char)*str2;
}

int my_strlen(char *str)
{
    int len = 0;
    while (*str != '\0'){
        len++;
        str++;
    }
    return len;
}

char *my_strcat(char *dest, char *src)
{
    char *ptr = NULL;
    ptr = dest + my_strlen(dest);

    while (*src != '\0') {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}

char *my_strcpy(char *dest, char *src)
{
    char *ptr = NULL;
    ptr = dest;

    while (*src != '\0') {
        *ptr = *src++;
        ptr++;
    }
    *ptr = '\0';
    return dest;
}

char *my_strrev(char *str) {
    int len = 0;
    char *start = NULL;
    char *end = NULL;
    char temp = {0};

    len = my_strlen(str);
    start = str;
    end = str + len - 1;

    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    
    return str;
}

int main()
{
    char src[10] = "hello";
    char dest[10] = "world";

    printf("dest is %s \n", my_strrev(src));
    printf("copy str is %s \n", my_strcpy(dest, src));

    return 0;
}