#include <stdio.h>
#include <stdlib.h>

char *strcpy(char *dst, char *src);
int strlen(char *src);

int main()
{
    char src[] = "Hello world!";
    char dst[20];
    int length = strlen(strcpy(dst, src));
    printf("dst = %s, length = %d\n", dst, length);

    return 0;
}

char* strcpy(char *dst, char *src)
{
    if (NULL == dst || NULL == src) {
        return NULL;
    }
    char *dstStr = dst;
    while (*src != '\0') {
        *dst++ = *src++;
    }
    return dstStr;
}

int strlen(char *src)
{
    int len = 0;
    while (*src++ != '\0') {
        ++len;
    }
    return len;
}
