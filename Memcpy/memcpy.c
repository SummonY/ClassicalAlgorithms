#include <stdio.h>

char* memcpy(char *dst, char *src, size_t len);
int strlen(char *src);

int main()
{
    char src[] = "Hello world!";
    char dst[20];
    int length = strlen(memcpy(dst, src, 7));
    dst[7] = '\0';
    printf("dst = %s, length = %d\n", dst, length);
    return 0;
}

char* memcpy(char *dst, char *src, size_t len)
{
    if (NULL == dst || NULL == src) {
        return NULL;
    }
    char *from = (char *)src;
    char *to = (char *)dst;
    while (len-- > 0) {
        *to++ = *from++;
    }
    return dst;
}

int strlen(char *src)
{
    int len = 0;
    while (*src++ != '\0') {
        ++len;
    }
    return len;
}
