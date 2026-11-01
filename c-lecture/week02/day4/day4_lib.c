#include "day4_lib.h"

void increament() {
    num++;
}

int getNum() {
    return num;
}

char * my_strcpy(char * to, const char * from) {
    char * save = to;

    for(;(*to = *from); to++, from++);

    return save;
}

// 길이만큼 입력 받고 넘으면 입력버퍼 보장
void my_gets(char * str, int n) {
    int i = 0;
    char c;

    for(i = 0; i < n - 1; i++) {
        str[i] = getchar();

        if(str[i] == '\n') break;
    }

    if(i == n - 1 && (c = getchar()) != '\n') ungetc(c, stdin); // 크게 중요 x

    str[i] = 0;
}

// 포인터로 접근
char * to_upper(char * str) {
    char * new = str;

    while(*str) {
        if ('a' <= *str && *str <= 'z') *str -= 32;
        str++;
    }

    return new;
}

// 배열로 접근
char* to_upper_2(char* str)
{
    int i = 0;
    while (str[i])
    {
        if ('a' <= str[i] && str[i] <= 'z')
        {
            str[i] -= 32;
        }
        i++;
    }

    return str;
}


// 길이만큼 입력 받고 입력 버퍼를 모두 지워주는 함수
void my_gets_1(char* str, int SIZE) {
    int ch;
    int i = 0;

    while ((ch = getchar()) != '\n') {
        if (i < SIZE - 1) {
            str[i] = (char)ch;
            i++;
        }
    }

    str[i] = '\0';
}

// 제대로 입력 안 하면 보장 안 함.
void my_gets_2(char* str, int n)
{
    for(int i = 0; i < n; i++)
    {
        str[i] = getchar();
        if(str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
    }
}

// 포인터로 접근
void my_gets_3(char* p, int n) {
    for (int i = 0; i < n -1; i++) {
        *p = getchar();
        if (*p == '\n') break;
        p++;
        
    }
         *p = '\0';
}