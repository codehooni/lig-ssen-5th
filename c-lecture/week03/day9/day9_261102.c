#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#if 01

int main(void) {

    int a = 0x12345678;
    char * p = (char *) &a;

    if(*p == 0x78) printf("little-endian\n");
    else printf("big-endian\n");

    return 0;
}
#endif

#if 01
typedef struct _color {
    unsigned int red : 8;
    unsigned int green : 8;
    unsigned int : 0;
    unsigned int blue : 8;
}color_t;

int main(void) {

    color_t myColor = { 0x12, 0x34, 0x56 };
    printf("%d\n", sizeof(myColor));    

    return 0;
}

#endif

#if 0


typedef struct _IP {

    uint16_t version : 4;
    uint16_t HL : 4;
    uint16_t typeOfService : 8; 
    uint16_t totalLength;
    uint16_t identification;
    uint16_t IP_Flags_X : 1;
    uint16_t IP_Flags_D : 1;
    uint16_t IP_Flags_M : 1;
    uint16_t fragmentOffset : 13;
    uint8_t timeToLive;
    uint8_t Protocal;
    uint16_t headerChecksum;
    uint32_t sourceAddress;
    uint32_t destinationAddress;
    uint32_t IP_Option;

}IP_Header;

int main(void) {

    IP_Header ip = {
        .version = 0xA,
        .HL = 0xB,
        .typeOfService = 0x11,
        .totalLength = 0x1234,
        .identification = 0x5678,
        .IP_Flags_X = 1,
        .IP_Flags_D = 0,
        .IP_Flags_M = 1,
        .fragmentOffset = 0x1345,
        .timeToLive = 0x10,
        .Protocal = 0x84,
        .headerChecksum = 0x1234,
        .sourceAddress = 0x12345678,
        .destinationAddress = 0x90ABCDEF,
        .IP_Option = 0x1234ABCD
    };

    printf("%p", ip);

    return 0;
}

#endif

#if 0

typedef struct bit {
    unsigned int a : 3;
    unsigned int b : 3;
    unsigned int c : 3;
}bit_t;

int main(void) {

    bit_t x = { 0 };
    x.a = 1;
    x.b = 2;
    x.c = 3;

    printf("%d %d %d\n", x.a, x.b, x.c);

    return 0;
}

#endif

#if 0
// 성능은 오히려 안 나옴
typedef struct bit {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
}bit_t;

int main(void) {

    bit_t x;
    x.a = 1;
    x.b = 2;
    x.c = 3;

    printf("%d %d %d\n", x.a, x.b, x.c);

    return 0;
}

#endif

#if 0

typedef struct bit {
    uint32_t a : 3;
    uint32_t b : 3;
    uint32_t c : 3;
}bit_t;

union _sample {
    int a;
    int b;
    int c;
};

int main(void) {

    bit_t X = { 1, 2, 3 };

    X = (bit_t) { 4, 5, 6 };

    union _sample Y = { 10 };
    
    printf("%d %d %d\n", X.a, X.b, X.c);

    printf("%d %d %d\n", Y.a, Y.b, Y.c);

    Y.a = 20;
    
    printf("%d %d %d\n", Y.a, Y.b, Y.c);

    return 0;
}

#endif

#if 0

// 유니온을 비트 필드와 함께 사용하면 일부를 수정해 전체를 변경하거나 전체를 수정해 일부를 수정할 수 있다 .

typedef struct trgb 
{
    uint32_t blue : 8;
    uint32_t green : 8;
    uint32_t red : 8;
}tRGB;

typedef union pixelcolor
{
    tRGB rgb;
    uint32_t color;
}tPColor;

int main(void) {

    printf("%d %d\n", sizeof(tRGB), sizeof(tPColor));

    tPColor X = {.color = 0x00123456};

    printf("%X %X %X\n", X.rgb.blue, X.rgb.green, X.rgb.red );

    X.color = 0x007722DD;

    printf("%X %X %X\n", X.rgb.blue, X.rgb.green, X.rgb.red );

    X.rgb.red = 0x99;

    printf("%X %X %X\n", X.rgb.blue, X.rgb.green, X.rgb.red );

    return 0;
}

#endif

#if 0

// day7에서도 기존 문제 변형해서 사용해봄 enum

enum { KOR = 1, ENG, MAT };

int main(void) {

    int scores[4] = { 0, 90, 100, 80 };

    printf("%d %d\n", scores[KOR], scores[ENG]);

    return 0;
}

#endif

#if 0

typedef char (*P10C_t)[10];

int printAry(char (*ary)[10], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%s ", ary[i]);
    }
    printf("\n");
}

int main(void) {
    char fruit[][10] = { "apple", "melon", "cherry" };
    int (*fn) (char (*ary)[10], int size);
    fn = printAry;
    fn(fruit, sizeof(fruit) / sizeof(fruit[0]));
    return 0;
}

#endif

#if 0

typedef char C10[10];
typedef C10 *P10C;
typedef int (*FP) (P10C, int);

int printAry(P10C ary, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%s ", ary[i]);
    }
    printf("\n");
}

int main(void) {
    C10 fruit[] = { "apple", "melon", "cherry" };
    FP fn = printAry;
    fn(fruit, SIZE(fruit));
    return 0;
}

#endif