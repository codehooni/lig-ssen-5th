#include <stdio.h>

#if 0

int func(int a, int b) {
    return a + b;
}

int main(void) {

    int tmp = (int) func;

    printf("%d\n", ((int (*) (int, int))tmp)(1, 200) );

    return 0;
}

#endif

#if 0

int main(void) {

    int a;
    int arr[5] = { 1, 2, 3, 4, 5 };

    a = (int) arr;
    a += 2 *sizeof(int);

    printf("%d\n", *(int *) a);

    return 0;
}

#endif

#if 0

int main(void) {

    int (*a)[4];
    char* (*b)[2];
    int (*c)(void);

    a = (int(*)[4])0x1000;
    b = (char* (*)[2])0x2000;
    c = (int (*)(void))0x3000;

    printf("%x %x %x\n", (int)a, (int)b, (int)c);

    return 0;
}

#endif


#if 0

#define ABS(x) (((x) >= 0) ? (x) : (-(x)));
#define MIN(x, y) (((x) <= (y)) ? (x) : (y));
#define MAX(x, y) (((x) >= (y)) ? (x) : (y));
#define SWAP(x, y) ((x) ^= (y), (y) ^= (x), (x) ^= (y)); 

int main(void) {
    int a = 5, b = 10;
    printf("%d %d\n", a, b);
    SWAP(a, b);
    printf("%d %d\n", a, b);

    return 0;
}

#endif

#if 0

#define SOUND_DEVICE_TYPE 0

int main(void) {

#if !SOUND_DEVICE_TYPE
    printf("사운드 장치를 사용하지 않음\n");
#else
#error CODE 10 : Unknown Device!
#endif

    printf("사운드 모드 = %d\n", SOUND_DEVICE_TYPE);
}

#endif

#if 0

#define Assert(x) { \
    if((x) >=4) printf("Range error : %s, %d\n", __FILE__, __LINE__);\
    }

int main(void) {
    int a[4] = { 10,20,30,40 };
    int i;

    for (i = 0; i <= 4; ++i) {
#line 100
        Assert(i);
        printf("a[%d] = %d\n", i, a[i]);
    }
}

#endif

#if 0

#define print(x) printf(#x " = %d\n", x)

int main(void) {

    int a = 2, b =30;

    print(a + b);

    return 0;
}

#endif

#if 0

#define VAR(n) a##n

int main(void) {

    int a1 = 10, a2 = 40;

    printf("%d %d\n", VAR(1), VAR(2));

    return 0;
}

#endif

#if 0

#define string(x) printf(#x" is %d\n", x)       //문자열화 연산자
#define charr(x) printf("%c is %c\n", *#x, x)   //문자화 연산자 // #@x 가 안 되어서 우회
#define concat(x,i) printf("%s is %d\n", #x#i, x##i)  //결합 연산자

int main(void)
{
    int s = 10, c = 97, ca = 7, cb = 9;
    string(s);
    charr(c);
    concat(c, a);
    concat(c, b);
    return 0;
}

#endif

#if 1

#include <stdio.h>
#include <assert.h>

int main() {
    int x;
    printf("\nEnter an integer value: ");
    (void)scanf("%d", &x);
    assert(x >= 0);
    printf("You entered %d.", x);
    return(0);
}

#endif