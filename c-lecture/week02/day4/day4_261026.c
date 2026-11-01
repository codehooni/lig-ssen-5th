#include "day4_lib.h"

#if 01

int main(void) {

    char str[30] = { 0 };

    my_gets(str, SIZE(str));

    printf("%s\n", str);

    printf("%s\n", to_upper(str));

    return 0;
}

#endif

#if 0

int main() {

    char str[10] = "apple";

    char* dessert1 = str;
    dessert1[0] = 'k';
    dessert1 = "banana";
    // dessert1[0] = 'k'; // runtime error

    const char* dessert2 = str;
    // dessert2[0] = 'k'; // compile error
    dessert2 = "banana";

    char* const dessert3 = str;
    dessert3[0] = 'k';
    // dessert3 = "banana"; // compile error

    char const * const dessert4 = str;
    // dessert4[0] = 'k'; // compile error
    // dessert4 = "banana"; // compile error

    char * temp = dessert4;
    temp[0] = 'k'; // Olur

// pc에 들어간 "mango"는 .rodata이기 때문에 수정이 불가능하다.
// 반면 str은 rw가 가능한 배열이기 때문에 수정이 가능하다.

// scanf는 stack에 있는 메모리에 값을 넣는다.
// pointer를 배열을 받지 못 한다.
// Pointer 공간은 
// 0x1000 ~ 0x1004
// 를 가르킨다.
// pointer는 넣을 수 있는 공간이 없다.

// 배열 str[10] 공간은
// 0x1000 ~ 0x100A
// 를 가르킨다.
// 배열은 넣을 수 있는 공간이 있다.
// str에서는 각 char 메모리 마다 값을 입력할 수 있다.
    return 0;
}

#endif

#if 0

#define A 3.14

int main(void) {

    const int a = 3.14;

    int c;

    c = A + a + 5;
    printf("%d\n", c);

    return 0;
}

#endif

#if 0

int main(void) {

    char str[30];
    my_strcpy(str, "Hello, World!");
    printf("%s\n", str);

    return 0;
}

#endif

#if 0

int main(void) {

    increament();
    printf("%d\n", getNum());

    return 0;
}

#endif