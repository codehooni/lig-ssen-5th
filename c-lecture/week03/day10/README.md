# Week 3 Day10 — 포인터와 정수 변환, 전처리기

> 2026-11-03 학습 정리

## 함수 주소를 정수로 바꿨다가 다시 호출하기
```c
int func(int a, int b) {
    return a + b;
}

int tmp = (int) func;

printf("%d\n", ((int (*) (int, int))tmp)(1, 200));
```
```
201   (x86 기준)
```
- 함수 이름은 함수의 주소다. 주소도 결국 숫자라서 정수로 바꿔 보관할 수 있다.
- 다시 `int (*)(int, int)` 타입으로 캐스팅하면 함수 포인터로 호출할 수 있다.
- ⚠️ x64에서는 주소가 8바이트라 `int`(4바이트)에 넣으면 위쪽 절반이 잘린다. 직접 돌려 보면 x64에서는 프로그램이 죽는다. 주소를 정수로 담을 때는 `intptr_t`/`uintptr_t`(`<stdint.h>`)를 쓴다.

## 배열 주소를 정수로 계산하기
```c
int a;
int arr[5] = { 1, 2, 3, 4, 5 };

a = (int) arr;
a += 2 * sizeof(int);

printf("%d\n", *(int *) a);
```
```
3   (x86 기준)
```
- 정수로 바꾼 주소에 더하면 1바이트씩 움직인다. 그래서 두 칸 뒤로 가려면 `2 * sizeof(int)` = 8을 더한다.
- 포인터 연산 `arr + 2`는 타입 크기를 알아서 곱해 주므로 `2`만 더하면 된다. 둘의 차이를 기억한다.
- ⚠️ 위 예제와 같은 이유로 x64에서는 동작하지 않는다.

## 정해진 주소를 포인터에 넣기
```c
int (*a)[4];
char* (*b)[2];
int (*c)(void);

a = (int(*)[4])0x1000;
b = (char* (*)[2])0x2000;
c = (int (*)(void))0x3000;

printf("%x %x %x\n", (int)a, (int)b, (int)c);
```
```
1000 2000 3000
```
- 숫자를 포인터에 넣으려면 그 포인터의 타입으로 캐스팅한다. 캐스트 표기는 선언에서 변수 이름만 뺀 모양이다.
  - `int (*a)[4]` → `(int (*)[4])`
  - `char* (*b)[2]` → `(char* (*)[2])`
  - `int (*c)(void)` → `(int (*)(void))`
- 임베디드에서 레지스터 주소를 포인터로 다룰 때 이 방식을 쓴다.
- 주소 값만 출력하므로 x64에서도 결과가 같다. 실제 주소를 출력할 때는 `%p`를 쓴다.

## 함수형 매크로
```c
#define ABS(x) (((x) >= 0) ? (x) : (-(x)));
#define MIN(x, y) (((x) <= (y)) ? (x) : (y));
#define MAX(x, y) (((x) >= (y)) ? (x) : (y));
#define SWAP(x, y) ((x) ^= (y), (y) ^= (x), (x) ^= (y));

int a = 5, b = 10;
printf("%d %d\n", a, b);
SWAP(a, b);
printf("%d %d\n", a, b);
```
```
5 10
10 5
```
- 매크로는 컴파일 전에 글자 그대로 바뀐다. 인자와 전체를 괄호로 감싸야 `ABS(a - b)`, `2 * MAX(a, b)` 같은 식에서 우선순위가 꼬이지 않는다.
- `SWAP`은 XOR 교환을 쉼표 연산자로 한 줄에 이었다. 임시 변수가 필요 없다.
- ⚠️ 매크로 끝에 `;`를 넣으면 `int m = MAX(a, b) + 1;`이나 `if(...) SWAP(a, b); else ...`에서 컴파일 오류가 난다. 매크로 정의에는 `;`를 넣지 않는다.
- ⚠️ `SWAP(a, a)`처럼 같은 변수를 넣으면 값이 0이 된다. 또 `MAX(i++, j)`처럼 쓰면 인자가 두 번 계산된다.

## 조건부 컴파일과 #error
```c
#define SOUND_DEVICE_TYPE 0

#if !SOUND_DEVICE_TYPE
    printf("사운드 장치를 사용하지 않음\n");
#else
#error CODE 10 : Unknown Device!
#endif

printf("사운드 모드 = %d\n", SOUND_DEVICE_TYPE);
```
```
사운드 장치를 사용하지 않음
사운드 모드 = 0
```
- `#if`는 컴파일 전에 조건을 보고 코드를 넣거나 뺀다. 수업 코드에서 `#if 0`/`#if 1`로 예제를 켜고 끄는 것도 같은 원리다.
- `SOUND_DEVICE_TYPE`을 0이 아닌 값으로 바꾸면 `#error`가 실행되어 컴파일이 메시지와 함께 멈춘다.
- 지원하지 않는 설정으로 빌드하는 것을 미리 막을 때 쓴다.

## __FILE__, __LINE__과 #line
```c
#define Assert(x) { \
    if((x) >=4) printf("Range error : %s, %d\n", __FILE__, __LINE__);\
    }

int a[4] = { 10,20,30,40 };
int i;

for (i = 0; i <= 4; ++i) {
#line 100
    Assert(i);
    printf("a[%d] = %d\n", i, a[i]);
}
```
```
a[0] = 10
a[1] = 20
a[2] = 30
a[3] = 40
Range error : day10_261103.c, 100
a[4] = (쓰레기 값)
```
- `__FILE__`은 파일 이름, `__LINE__`은 지금 줄 번호로 바뀌는 미리 정의된 매크로다.
- `#line 100`은 다음 줄의 번호를 100으로 바꾼다. 그래서 `Assert(i)`의 줄 번호가 100으로 출력된다.
- 매크로가 여러 줄이면 줄 끝에 `\`를 붙여 이어 쓴다.
- `Assert`는 메시지만 출력하고 멈추지 않는다. 그래서 범위를 넘은 `a[4]`를 그대로 읽는다.
- 여러 문장 매크로는 `do { ... } while(0)`로 감싸는 것이 관례다. `if`/`else` 안에서도 한 문장처럼 동작한다.

## # 연산자(문자열화)와 ## 연산자(결합)
```c
#define print(x) printf(#x " = %d\n", x)

int a = 2, b = 30;
print(a + b);
```
```
a + b = 32
```
```c
#define VAR(n) a##n

int a1 = 10, a2 = 40;
printf("%d %d\n", VAR(1), VAR(2));
```
```
10 40
```
```c
#define string(x) printf(#x" is %d\n", x)
#define charr(x) printf("%c is %c\n", *#x, x)
#define concat(x,i) printf("%s is %d\n", #x#i, x##i)

int s = 10, c = 97, ca = 7, cb = 9;
string(s);
charr(c);
concat(c, a);
concat(c, b);
```
```
s is 10
c is a
ca is 7
cb is 9
```
- `#x`는 인자를 문자열로 바꾼다. `print(a + b)`의 `#x`는 `"a + b"`가 된다.
- 붙어 있는 문자열 리터럴은 하나로 합쳐진다. `"a + b" " = %d\n"` → `"a + b = %d\n"`.
- `a##n`은 두 토큰을 이어 새 이름을 만든다. `VAR(1)`은 `a1`이 된다.
- `#@x`(문자로 바꾸기)는 MSVC 전용이라 GCC에서는 안 된다. `*#x`로 문자열 `"c"`의 첫 글자를 꺼내 대신했다.
- `c`의 값 97을 `%c`로 출력하면 `a`다.
- `#x#i`는 `"c" "a"` → `"ca"`, `x##i`는 변수 `ca`가 된다.

## assert
```c
#include <assert.h>

int x;
printf("\nEnter an integer value: ");
(void)scanf("%d", &x);
assert(x >= 0);
printf("You entered %d.", x);
```
```
입력 5:  You entered 5.
입력 -1: Assertion failed: x >= 0, file day10_261103.c, line 168
```
- `assert(조건)`은 조건이 거짓이면 파일 이름과 줄 번호를 출력하고 프로그램을 멈춘다(`abort`).
- 앞에서 직접 만든 `Assert`와 달리 실제로 멈춘다.
- `#include <assert.h>` 앞에 `#define NDEBUG`가 있으면 모든 `assert`가 사라진다. 디버깅용 검사라서 릴리스 빌드에서는 빼는 것이다.
- 그래서 `assert` 안에 꼭 실행돼야 하는 코드(`assert(scanf(...) == 1)` 같은)를 넣으면 안 된다.
- `(void)scanf(...)`는 반환값을 일부러 버린다는 표시로, 경고를 없앤다.
