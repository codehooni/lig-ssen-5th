#include <stdio.h>

// P.140
#if 1

#define size_ary(x) (sizeof(x) / sizeof((x)[0]))

void my_gets(char * str, int n);

int main(void) {

    char str[30] = { 0 };

    my_gets(str, size_ary(str));
    printf("%s\n", str);

    char * cp = str;
    printf("Address of pointer: 0x%p\n", cp);
    printf("Size of pointer: %zu\n", sizeof cp);

    return 0;
}

void my_gets(char * str, int n) {
    int i;

    for(i = 0; i < n - 1; i++) {
        str[i] = getchar();

        if(str[i] == '\n') break;
    }

    str[i] = '\0';
}

#endif