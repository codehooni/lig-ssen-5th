# Week 3 Day9 — 비트 필드, 공용체, 열거형

> 2026-11-02 학습 정리

## 엔디언 확인하기
```c
int a = 0x12345678;
char * p = (char *) &a;

if(*p == 0x78) printf("little-endian\n");
else printf("big-endian\n");
```
```
little-endian
```
- `char *`로 바꾸면 `int`의 첫 바이트(가장 낮은 주소)만 읽는다.
- 첫 바이트가 가장 아래 자리 `0x78`이면 리틀 엔디언, `0x12`이면 빅 엔디언이다.
- x86/x64 PC는 리틀 엔디언이다. 네트워크로 보내는 데이터는 빅 엔디언(네트워크 바이트 순서)을 쓴다.

## 비트 필드 기본
```c
typedef struct bit {
    unsigned int a : 3;
    unsigned int b : 3;
    unsigned int c : 3;
}bit_t;

bit_t x = { 0 };
x.a = 1;
x.b = 2;
x.c = 3;

printf("%d %d %d\n", x.a, x.b, x.c);
```
```
1 2 3
```
- `: 3`은 멤버가 3비트만 쓴다는 뜻이다. 3비트 `unsigned`는 0~7까지 담는다.
- 9비트가 `unsigned int` 하나(32비트) 안에 들어가서 `sizeof(bit_t)`는 4다.
- 같은 멤버를 비트 필드 없이 `unsigned int` 4개로 만들면 16바이트다.
- 비트 필드는 메모리를 아끼지만, 읽고 쓸 때마다 시프트와 마스크 연산이 붙어 속도는 오히려 느릴 수 있다.
- 비트 필드 멤버는 주소가 없어서 `&x.a`는 쓸 수 없다.

## 크기가 0인 비트 필드
```c
typedef struct _color {
    unsigned int red : 8;
    unsigned int green : 8;
    unsigned int : 0;
    unsigned int blue : 8;
}color_t;

color_t myColor = { 0x12, 0x34, 0x56 };
printf("%d\n", sizeof(myColor));
```
```
8
```
- 이름 없는 `: 0`은 "다음 멤버는 새 저장 단위에서 시작하라"는 표시다.
- `red`, `green`은 첫 `unsigned int`에, `blue`는 두 번째 `unsigned int`에 들어가서 8바이트가 된다.
- `: 0`이 없으면 24비트가 한 단위에 들어가 4바이트다.
- 이름 없는 비트 필드는 초기화 목록에서 건너뛴다. 그래서 `0x56`이 `blue`에 들어간다.
- `sizeof`의 결과는 `size_t`라서 `%zu`로 출력하는 것이 맞다.

## 비트 필드로 IP 헤더 만들기
```c
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

IP_Header ip = {
    .version = 0xA,
    .HL = 0xB,
    .typeOfService = 0x11,
    .totalLength = 0x1234,
    /* ... */
    .IP_Option = 0x1234ABCD
};
```
```
sizeof(IP_Header) = 24
메모리: BA 11 34 12 78 56 2D 9A 10 84 34 12 78 56 34 12 EF CD AB 90 CD AB 34 12
```
- `.멤버 = 값`은 지정 초기화(designated initializer)다. 순서와 관계없이 원하는 멤버만 채운다.
- 프로토콜 헤더처럼 비트 단위로 정해진 형식을 구조체로 옮길 때 비트 필드를 쓴다.
- 첫 바이트가 `BA`다. 비트 필드는 (이 컴파일러에서) 낮은 비트부터 채워서 `version`이 아래 4비트, `HL`이 위 4비트에 들어간다.
- 실제 IP 헤더는 첫 바이트의 위 4비트가 version이다(`0x45`). 리틀 엔디언 PC에서 맞추려면 `HL`을 먼저 선언해야 한다.
- `totalLength` 같은 여러 바이트 값도 `34 12`처럼 뒤집혀 저장된다. 네트워크로 보낼 때는 `htons`/`htonl`로 바꾼다.
- ⚠️ 비트 필드의 배치 순서는 컴파일러마다 다를 수 있다. 이식성이 중요하면 시프트와 마스크로 직접 다룬다.
- ⚠️ `printf("%p", ip)`는 구조체를 통째로 넘겨서 잘못된 호출이다. 주소를 보려면 `&ip`를 넘긴다.

## 공용체(union)
```c
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

bit_t X = { 1, 2, 3 };
X = (bit_t) { 4, 5, 6 };

union _sample Y = { 10 };

printf("%d %d %d\n", X.a, X.b, X.c);
printf("%d %d %d\n", Y.a, Y.b, Y.c);

Y.a = 20;
printf("%d %d %d\n", Y.a, Y.b, Y.c);
```
```
4 5 6
10 10 10
20 20 20
```
- `(bit_t) { 4, 5, 6 }`은 복합 리터럴이다. 선언이 끝난 구조체에도 한 번에 값을 넣을 수 있다.
- 공용체는 모든 멤버가 같은 주소에서 시작한다. 크기는 가장 큰 멤버의 크기다.
- `{ 10 }`은 첫 멤버 `a`를 초기화한다. `a`, `b`, `c`가 같은 메모리라서 셋 다 10이다.
- `Y.a`만 바꿔도 `b`, `c`가 같이 20이 된다.

## 공용체 + 비트 필드
```c
typedef struct trgb {
    uint32_t blue : 8;
    uint32_t green : 8;
    uint32_t red : 8;
}tRGB;

typedef union pixelcolor {
    tRGB rgb;
    uint32_t color;
}tPColor;

printf("%d %d\n", sizeof(tRGB), sizeof(tPColor));

tPColor X = {.color = 0x00123456};
printf("%X %X %X\n", X.rgb.blue, X.rgb.green, X.rgb.red);

X.color = 0x007722DD;
printf("%X %X %X\n", X.rgb.blue, X.rgb.green, X.rgb.red);

X.rgb.red = 0x99;
printf("%X %X %X\n", X.rgb.blue, X.rgb.green, X.rgb.red);
```
```
4 4
56 34 12
DD 22 77
DD 22 99
```
- 같은 4바이트를 `color`(전체)와 `rgb`(부분) 두 가지 방식으로 볼 수 있다.
- 전체를 바꾸면 각 색이 바뀌고(`0x007722DD` → `DD 22 77`), 한 색만 바꾸면 전체 값의 일부가 바뀐다.
- `blue`를 먼저 선언해서 가장 낮은 바이트 `0x56`이 `blue`가 된다. 낮은 비트부터 채워지기 때문이다.
- 마지막 출력 뒤 `X.color`는 `0x009922DD`다.
- 레지스터를 "전체 값"과 "비트별 필드"로 동시에 다룰 때 자주 쓰는 패턴이다.

## 열거형(enum)으로 배열 인덱스 이름 붙이기
```c
enum { KOR = 1, ENG, MAT };

int scores[4] = { 0, 90, 100, 80 };

printf("%d %d\n", scores[KOR], scores[ENG]);
```
```
90 100
```
- 첫 값을 1로 주면 다음은 자동으로 1씩 늘어난다. `KOR = 1`, `ENG = 2`, `MAT = 3`이다.
- `scores[1]` 대신 `scores[KOR]`로 쓰면 숫자의 의미가 코드에 드러난다.
- 0번 칸은 쓰지 않으려고 배열을 4칸으로 만들었다.

## 함수 포인터와 typedef
```c
int printAry(char (*ary)[10], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%s ", ary[i]);
    }
    printf("\n");
}

char fruit[][10] = { "apple", "melon", "cherry" };
int (*fn) (char (*ary)[10], int size);
fn = printAry;
fn(fruit, sizeof(fruit) / sizeof(fruit[0]));
```
```c
typedef char C10[10];
typedef C10 *P10C;
typedef int (*FP) (P10C, int);

C10 fruit[] = { "apple", "melon", "cherry" };
FP fn = printAry;
fn(fruit, SIZE(fruit));
```
```
apple melon cherry
```
- `char fruit[][10]`의 이름은 `char (*)[10]`(10칸 `char` 배열을 가리키는 포인터)로 바뀐다. 그래서 매개변수도 같은 타입이다.
- `int (*fn)(char (*)[10], int)`처럼 직접 쓰면 읽기 어렵다. typedef를 단계별로 쌓으면 짧아진다.
  - `C10` = `char [10]`
  - `P10C` = `C10 *` = `char (*)[10]`
  - `FP` = `int (*)(P10C, int)`
- `SIZE(x)`는 `sizeof(x) / sizeof((x)[0])`로 배열 요소 수를 구하는 매크로다. 매개변수로 받은 포인터에는 쓸 수 없다.
- ⚠️ `printAry`는 `int`를 반환한다고 선언했지만 `return`이 없다. 반환값이 필요 없으면 `void`로 선언한다.
