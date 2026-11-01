#include "day6_lib.h"

#if 0

int main(void) {

    int score[3][4];

    printf("%d\n", sizeof(score[2]));
    printf("%d\n", sizeof(score[3]));

    
    return 0;
}

#endif

#if 0

int main(void) {

    int * ptr;
    int n[] = {5, 10, 22, 34, 36, 44};
    ptr = n;

    printf("%d ", *ptr++);
    printf("%d\n", *ptr);

    printf("%d ", *ptr + 1);
    printf("%d\n", *ptr);

    printf("%d ", ++*ptr);
    printf("%d\n", *ptr);

    printf("%d ", *(ptr + 1));
    printf("%d\n", *ptr);

    printf("%d ", *ptr += 1);
    printf("%d\n", *ptr);
    
    printf("%d ", *++ptr);
    printf("%d\n", *ptr);

    printf("%d ", (*ptr)++);
    printf("%d\n", *ptr);

    return 0;
}

#endif

#if 0

int main(void) {

    char *ptr[] = {"red", "orange", "pink", "white", "blue", "brown", "black", "gray"};

    printf("%c\n", **ptr);
    printf("%s\n", ptr[1]); 
    printf("%s\n", ptr[1] + 3);
    printf("%c\n", *(*(ptr + 1) + 1));
    printf("%c\n", (*(*(ptr + 2) + 1)));
    printf("%s\n", ptr[3] + 2);


    return 0;
}

#endif

#if 0

int main(void) {

    int a[3][4] = { 100, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    print_ary(&a);

    return 0;
}

#endif

#if 0

int main(void) {

    int a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};   // a의 시작 주소 = 1000
    int (*p)[4] = a + 1; // 1044 - 1016 = 28
    int *q = &a[1][2];
    int (*r)[2] = (int (*)[2])(q - 1);
    // sizeof(int) = 4, 포인터 크기 = 8

    r[q[-5]][(&a[2][3] - *p) % 3 - 1] + *(int*)((char*)&a + sizeof(*p) + sizeof(*r));

    return 0;
}

#endif

#if 0

int main(void) {

    int a = 10, b = 5;
    int *ap = &a, *bp = &b;
    int **app = &ap, **bpp = &bp;

    exchange0(&a, &b);
    printf("%d %d\n", a, b);
    exchange1(&ap, &bp);
    printf("%d %d\n", a, b);
    exchange2(&app, &bpp);
    printf("%d %d\n", a, b);

    printf("before change: %p %p\n", ap, bp);
    exchange3(&ap, &bp);
    printf("after change: %p %p\n", ap, bp);

    printf("before change: %p %p\n", ap, bp);
    exchange4(&app, &bpp);
    printf("after change: %p %p\n", ap, bp);
    
    printf("before change: %p %p\n", app, bpp);
    exchange5(&app, &bpp);
    printf("after change: %p %p\n", app, bpp);

    return 0;
}

#endif

#if 0

void func1(int (*fp)(int, int)) {
    printf("%d\n", fp(10, 20));
}

void func2(int (**fp)(int, int)) {
    printf("answer: %d\n", (********fp)(5, 2));
}

int main(void) {

    int (*p) (int, int) = add;

    int (*pa[5])(int, int) = {add , };

    func2(pa);

    printf("%d\n", p(1, 2));
    printf("%d\n", (**********p)(1, 2));
    printf("%p\n", add);
    printf("%p\n", *****add);
    printf("%d\n", (********add)(1, 3));

    return 0;
}

#endif

#if 0

void print_chars(char ** cp, int n) {
    for(int i = 0; i < n; i ++) {
        printf("%s\n", cp[i]);
    }
}

int main(void) {

    char* ch[5] = {"apple", "banana", "mango", "melon", "watermelon"};

    print_chars(ch, SIZE(ch));

    return 0;
}

#endif

#if 01

void func(int ** ary, int n) {
    int count;

    for(int i = 0; i < n; i++) {

        count = ary[i][0];

        for(int j = 1; j <= count; j++) {
            printf("%d ", ary[i][j]);
        }
        printf("\n");
        
    }
}

int main(void) {

    int a[] = { 3, 1, 2, 3 };
    int b[] = { 5, 10, 20, 30, 40, 50 };
    int c[] = { 4, 5, 6, 7, 8 };

    int * ary[] = { a, b, c };

    func(ary, 3);

    return 0;
}

#endif