# Week 1 Day1 — 자료형·const·연산자·비트 연산

> 2026-10-21 학습 정리

## 자료형 — 정수는 int, 실수는 double
```c
float a = 1.234567890123456789f;
double b = 1.234567890123456789;

printf("%.20f\n", a);   // 1.23456788063049316406
printf("%.20f\n", b);   // 1.23456789012345669043

float c = 3.99999f;
printf("%d", (int)c);   // 3
```

| | float | double |
|---|---|---|
| 크기 | 4바이트 | 8바이트 |
| 정확한 자릿수 | 약 7자리 | 약 15자리 |

- float는 `1.234567`까지만 맞고 뒤는 틀린다. double도 16자리부터 틀린다 → 실수는 **근삿값**으로 저장된다.
- 그래서 실수는 기본적으로 **double**을 쓴다. 실수 리터럴(`1.23`)도 기본이 double이고, float로 쓰려면 `f`를 붙인다.
- `(int)c`: 실수 → 정수 변환은 **반올림이 아니라 소수점 버림** → `3.99999`도 `3`.

## const 키워드
### 포인터로 const를 우회하면 UB
```c
const double a = 1.4;

double* p = &a;   // ⚠️ 경고: const가 사라짐
*p = 1.2;
printf("%f", a);
```
- 컴파일은 되지만(경고만 뜸) 결과는 **정의되지 않은 동작(UB)**.
- 실제로 gcc에서 해보면 최적화에 따라 결과가 다르다.
  - `-O0`: `1.200000` (메모리를 다시 읽음)
  - `-O2`: `1.400000` (컴파일러가 "const니까 안 바뀐다"고 보고 1.4를 그대로 사용)
- 👉 const는 컴파일러가 **직접 수정만 막아 줄 뿐**, 포인터로 우회하는 것까지 막지는 못한다. 우회하지 말자.

### const는 바로 오른쪽에 오는 것을 고정한다
`*`를 기준으로 왼쪽에 있으면 **가리키는 값**, 오른쪽에 있으면 **포인터 자체**를 고정한다.

```c
const char* cp = "rabbit";          // 가리키는 char를 고정
cp = "cat";                         // ✅ 포인터 변경 가능
//cp[0] = 'd';                      // ❌ 값 변경 불가

char* const cp2 = "rabbit";         // 포인터 자체를 고정
//cp2 = "cat";                      // ❌ 포인터 변경 불가
cp2[0] = 'd';                       // ✅ 컴파일은 됨 (아래 주의)

const char* const cp3 = "rabbit";   // 둘 다 고정
//cp3 = "cat";                      // ❌
//cp3[0] = 'd';                     // ❌
```

| 선언 | 포인터 변경 (`cp = ...`) | 값 변경 (`cp[0] = ...`) |
|---|---|---|
| `const char* cp` | ✅ | ❌ |
| `char* const cp2` | ❌ | ✅ |
| `const char* const cp3` | ❌ | ❌ |

⚠️ `cp2[0] = 'd'`는 문법상 허용되지만 `"rabbit"`은 **문자열 리터럴**(읽기 전용 메모리)이라 실행 시 UB → 프로그램이 죽을 수 있다. 수정하려면 배열에 복사해서 쓴다.
```c
char str[] = "rabbit";   // 배열에 복사됨
str[0] = 'd';            // ✅ "dabbit"
```

## myStrlen — 문자열 길이 직접 구하기
```c
int myStrlen(const char* str)
{
	const char* s;

	if (str == 0)
		return 0;
	for (s = str; *s; ++s);
	return s - str;
}
```
```c
int len = myStrlen("Hello");
printf("%d\n", len);   // 5
```

### 한 줄씩 보기
- `const char* str`: 문자열을 읽기만 하므로 `const`. 문자열 리터럴(`"Hello"`)도 그대로 넘길 수 있다.
- `if (str == 0)`: NULL 포인터가 들어오면 `*s`에서 터지므로 먼저 막는다.
- `for (s = str; *s; ++s);`
  - 몸체가 없는 반복문 (끝의 `;`)
  - `*s`가 `'\0'`(= 0)이 되면 거짓 → 멈춤
  - 끝나면 `s`는 `'\0'`의 위치를 가리킨다
- `return s - str;`: **포인터끼리 빼면 사이의 요소 개수**가 나온다. `'\0'`은 세지 않는다.

```
주소   1000 1001 1002 1003 1004 1005
값      H    e    l    l    o   \0
       str                      s     → 1005 - 1000 = 5
```

### 표준 strlen과 차이
- 표준 `strlen`은 `size_t`(부호 없는 정수)를 반환한다.
- 표준 `strlen(NULL)`은 검사해 주지 않는다 → UB. `myStrlen`은 0을 반환하도록 직접 막았다.

## scanf_s — 표준 입력
```c
int a;

scanf_s("%d", &a);
printf("%d", a);
```

### 포인트
- `&a`: scanf는 값을 **변수의 주소에 저장**하므로 주소를 넘긴다. `&`를 빼면 `a`의 쓰레기값을 주소로 착각해 엉뚱한 곳에 쓴다.
- `scanf`는 입력이 버퍼 크기를 넘는지 검사하지 않는다 → 버퍼 오버플로 위험.
- Visual Studio는 `scanf`를 쓰면 **C4996 오류**를 낸다. 해결 방법은 두 가지
  - `scanf_s` 사용 (MS 전용, 다른 컴파일러에선 없을 수 있음)
  - 파일 맨 위에 `#define _CRT_SECURE_NO_WARNINGS` → 그냥 `scanf` 사용 가능

### scanf_s는 문자열에서 차이가 난다
`%d`처럼 숫자는 `scanf`와 똑같이 쓰지만, `%s`, `%c`는 **버퍼 크기를 같이 넘겨야** 한다.
```c
char name[20];
scanf_s("%s", name, (unsigned)sizeof(name));   // 크기 필수
scanf("%19s", name);                            // scanf는 폭 지정으로 막기
```
- 배열 이름 `name`은 이미 주소라서 `&`를 붙이지 않는다.

## 연산자 우선순위 (교재 01-10)

| 우선순위 | 종류 | 연산자 | 결합 방향 |
|---|---|---|---|
| 1 | 1차 (후치) | `()` `[]` `.` `->` `a++` `a--` | → |
| 2 | 단항 (전치) | `++a` `--a` `-` `~` `!` `*` `&` `sizeof` `(type)` | ← |
| 3~4 | 산술 | `*` `/` `%` > `+` `-` | → |
| 5 | 비트 이동 | `<<` `>>` | → |
| 6~7 | 관계, 동등 | `<` `<=` `>` `>=` > `==` `!=` | → |
| 8~10 | 비트 논리 | `&` > `^` > `\|` | → |
| 11~12 | 논리 | `&&` > `\|\|` | → |
| 13 | 조건 | `?:` | ← |
| 14 | 대입 | `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `\|=` `<<=` `>>=` | ← |
| 15 | 콤마 | `,` | → |

### 순서 외우기: 후치 → 전치 → 이항
1. **후치 단항** (`a++`, `a[i]`, `f()`)
2. **전치 단항** (`++a`, `*p`, `&a`, `-a`)
3. **이항 연산자** (산술 → 시프트 → 관계 → 비트 → 논리)
4. 마지막에 조건(`?:`), 대입(`=`), 콤마

```c
*p++   // 후치가 먼저 → *(p++) : p가 가리키던 값을 읽고, p를 다음 칸으로
-a * b // 전치가 이항보다 먼저 → (-a) * b
```

### ⭐ `a++`: ++는 먼저 묶이지만 증가는 가장 나중
- 우선순위가 1등이라 `a++`로 **가장 먼저 묶인다**(읽힌다).
- 하지만 그 자리에 쓰이는 값은 **증가 전의 a**. 실제 +1은 **식 전체가 끝난 뒤**에 반영된다.

```c
int a = 2, b = 2;
int x = (++a) * 3;   // a를 먼저 3으로 → 3 * 3 = 9
int y = (b++) * 3;   // 2 * 3 = 6을 계산한 뒤 → b가 3이 됨
```

```c
func(i++);   // i를 함수에 전달한 뒤, i를 1 증가
func(++i);   // i를 1 증가한 뒤, 함수에 전달
```

⚠️ 한 식 안에서 같은 변수를 두 번 바꾸면 UB → `i = i++;`, `a++ + a++` 금지

### 복합 대입 연산자
`a 연산= b` 는 `a = a 연산 b`와 같다.
- 산술: `+=` `-=` `*=` `/=` `%=`
- 비트: `&=` `^=` `|=` `<<=` `>>=`
- 우선순위 14 → 오른쪽 식을 **전부 계산한 뒤** 대입한다. `a *= b + 1`은 `a = a * (b + 1)`.

### 대입(=)은 식이다 (not 문)
```c
int a = 25, b = 5;

a %= b -= 1;
printf("%d %d", a, b);   // 1 4
```
1. 대입은 결합 방향이 ← 이므로 `a %= (b -= 1)`로 묶인다.
2. `b -= 1` → b는 4, 그리고 **이 식 자체의 값도 4**
3. `a %= 4` → 25 % 4 = 1

대입식은 대입된 값을 남기기 때문에 이런 코드가 가능하다.
```c
a = b = 0;                          // a = (b = 0)
while ((c = getchar()) != EOF) { }  // 대입하고, 그 값을 바로 비교
```

## 연산 시 주의 사항 (교재 01-10c)
- **정수 / 정수 = 정수** (소수점 버림)
- **정수와 실수의 연산 = 실수**
- **signed와 unsigned의 연산 = unsigned** (int가 unsigned int로 변환되어 연산)

```c
int a = 5;
int b = 2;
int result_i = a / b;              // 2
float result_f = (float)a / b;     // 2.5  ← 하나만 실수로 바꿔도 실수 연산
```
- `(float)(a / b)`라고 쓰면 정수 나눗셈(2)을 먼저 한 뒤 바꾸므로 `2.0`이 된다.

```c
int a = -1;
unsigned int b = 1;
if (a < b) printf("a is less than b\n");
else       printf("a is not less than b\n");   // ← 이게 출력됨
```
- `-1`이 unsigned로 바뀌면 `0xFFFFFFFF` = 4294967295 → `1`보다 크다.
- gcc는 `-Wall`(정확히는 `-Wsign-compare`)로 경고해 준다.

## Short-circuit 원리 (교재 01-10g ~ 10i)
`&&`, `||`는 **왼쪽만으로 결과가 정해지면 오른쪽을 실행하지 않는다.**
- `A && B`: A가 거짓이면 B 안 봄 (어차피 거짓)
- `A || B`: A가 참이면 B 안 봄 (어차피 참)

### 활용: NULL 포인터 역참조 방지
```c
if (ptr != NULL && *ptr == 10) {
	// ptr이 NULL이 아니고 *ptr이 10인 경우 실행
}
```
- `ptr`이 NULL이면 왼쪽에서 바로 거짓 → `*ptr`을 실행하지 않아 안전하다.
- 순서를 바꿔 `*ptr == 10 && ptr != NULL`로 쓰면 NULL일 때 먼저 터진다. **검사가 먼저, 사용이 나중.**
- `myStrlen`의 `if (str == 0) return 0;`도 같은 목적.

## 삼항 연산자 vs if-else
```c
int a = 10, b = 20;
int res;

res = (a > b) ? a : b;   // 삼항 연산자

if (a > b) {             // if-else
	res = a;
}
else {
	res = b;
}
```
- 둘 다 큰 값(20)을 `res`에 넣는다.
- `조건 ? 참일 때 값 : 거짓일 때 값` → 삼항 연산자는 **식**이라 값이 남는다. 그래서 대입문 오른쪽에 바로 쓸 수 있다.

### ⭐ 어셈블리로 비교하기
수업에서는 "삼항 연산자가 어셈블리로 가면 더 길다"고 했다 (VS Debug 기준). 그런데 **내 컴파일러(gcc, 최적화 없음)로 확인하면 반대**였다.

```
	res = (a > b) ? a : b;
  1b:	mov    edx,DWORD PTR [rbp-0xc]     ; edx = b
  1e:	mov    eax,DWORD PTR [rbp-0x8]     ; eax = a
  21:	cmp    edx,eax                     ; b와 a 비교
  23:	cmovge eax,edx                     ; b >= a 이면 eax = b
  26:	mov    DWORD PTR [rbp-0x4],eax     ; res = eax

	if (a > b) {
  29:	mov    eax,DWORD PTR [rbp-0x8]     ; eax = a
  2c:	cmp    eax,DWORD PTR [rbp-0xc]     ; a와 b 비교
  2f:	jle    39 <main+0x39>              ; a <= b 이면 else로 점프
		res = a;
  31:	mov    eax,DWORD PTR [rbp-0x8]
  34:	mov    DWORD PTR [rbp-0x4],eax
  37:	jmp    3f <main+0x3f>              ; else 건너뛰기
	}
	else {
		res = b;
  39:	mov    eax,DWORD PTR [rbp-0xc]
  3c:	mov    DWORD PTR [rbp-0x4],eax
	}
```

| | 삼항 연산자 | if-else |
|---|---|---|
| 명령어 수 | 5줄 | 7줄 |
| 분기(점프) | 없음 (`cmov`) | `jle`, `jmp` 2번 |

- `cmov`(conditional move): 조건이 맞을 때만 값을 옮기는 명령. **점프 없이** 선택을 끝낸다.
- 점프가 있으면 CPU가 분기 예측을 해야 하고, 틀리면 파이프라인을 비우느라 느려진다.
- 수업(VS Debug)에서는 MSVC가 삼항 연산자 결과를 임시 변수에 먼저 저장했다가 `res`로 복사해서 더 길게 나온다.
- 최적화(`-O2`)를 켜면 gcc는 둘 다 같은 코드(`cmov` 4줄)를 만든다.

👉 **같은 C 코드라도 컴파일러와 빌드 설정에 따라 어셈블리가 다르다.** "삼항이 짧다/길다"를 외우지 말고 직접 디스어셈블해서 확인하자.
- VS: 중단점 → 디버그 중 `Ctrl + Alt + D`
- gcc: `gcc -g -c day1.c -o day1.o` (`-g`가 있어야 소스가 같이 나옴) → `objdump -d -M intel -S day1.o`

## 비트 연산 — 특정 비트 켜기/끄기/뒤집기
```c
unsigned int setBit(unsigned int num, int n) {
	return num | (1u << n);
}

unsigned int clearBit(unsigned int num, int n) {
	return num & ~(1u << n);
}

unsigned int toggleBit(unsigned int num, int n) {
	return num ^ (1u << n);
}
```

### 핵심: `1u << n`으로 마스크 만들기
`1`을 왼쪽으로 n칸 밀면 **n번 비트만 1인 값**(마스크)이 된다.
```
1u << 0 = 0000 0001
1u << 3 = 0000 1000
1u << 7 = 1000 0000
```
- `1u`(unsigned)를 쓰는 이유: `1 << 31`처럼 signed int의 부호 비트까지 밀면 UB. unsigned는 안전하다.

| 함수 | 연산 | 원리 |
|---|---|---|
| `setBit` | `num \| 마스크` | OR: 1과 OR하면 무조건 1 → n번 비트 **켜기** |
| `clearBit` | `num & ~마스크` | `~`로 n번만 0인 마스크 → AND하면 n번만 0 → **끄기** |
| `toggleBit` | `num ^ 마스크` | XOR: 1과 XOR하면 반전 → **뒤집기** |

나머지 비트는 OR 0, AND 1, XOR 0이 되어 **그대로 유지**된다.

### 실행 결과
비트 확인용으로 `printBits8`을 직접 만들어 하위 8비트를 출력했다. (`getBit`은 2일차에 정리)
```c
void printBits8(unsigned int num) {
	for (int i = 7; i >= 0; i--) {     // 7번 비트(MSB)부터 출력
		printf("%u", getBit(num, i));
	}
	printf("\n");
}
```
```c
unsigned int a = 0b11001010;

printBits8(a);                // 11001010
printBits8(setBit(a, 0));     // 11001011  ← 0번 켜짐
printBits8(clearBit(a, 7));   // 01001010  ← 7번 꺼짐
printBits8(toggleBit(a, 3));  // 11000010  ← 3번 1→0
printf("%u\n", getBit(a, 1)); // 1
```
- `0b11001010`: 2진수 리터럴. C23부터 표준이고, 그 전에는 gcc/MSVC 확장 기능이다.
- 함수들은 `num`을 **복사해서** 받으므로 `a` 자체는 바뀌지 않는다. 매번 원래 `a`에서 계산된다.

## Integral Promotion (정수의 승격) — 교재 01-03a
```c
unsigned char a = 0xf0;
char b = 0xf0;
unsigned char c = 0x0f;
char d = 0x0f;
printf("%X %X %X %X\n", a, b, c, d);
if (a == ~c) printf("a equal ~c\n");
if (a == ~d) printf("a equal ~d\n");
if (b == ~c) printf("b equal ~c\n");
if (b == ~d) printf("b equal ~d\n");
```
```
F0 FFFFFFF0 F F
b equal ~c
b equal ~d
```
연산 전에 `char`는 전부 **`int`로 승격**된다. 이때 빈 자리를 채우는 방법이 다르다.
- `a`, `c` (unsigned char) → **0으로 채우기**
- `b`, `d` (signed char) → **부호 비트로 채우기**

```
a  = 0xf0 → 00000000 00000000 00000000 11110000   (0x000000F0)
b  = 0xf0 → 11111111 11111111 11111111 11110000   (0xFFFFFFF0, -16)  ← 부호 확장
c  = 0x0f → 00000000 00000000 00000000 00001111
d  = 0x0f → 00000000 00000000 00000000 00001111
~c, ~d    → 11111111 11111111 11111111 11110000   (0xFFFFFFF0)
```
- `b`는 0xf0의 맨 앞 비트가 1이라 음수(-16) → 위쪽 24비트가 1로 채워짐 → `~c`, `~d`와 **같아진다**.
- `a`는 0으로 채워져서 여전히 다르다.
- 승격 후 연산은 모두 **signed int**끼리 한다.

👉 **작은 타입은 연산 전에 int로 승격되고, signed냐 unsigned냐에 따라 채우는 비트가 다르다.**

### 8비트끼리 비교하고 싶다면
뒤집은 뒤 필요한 비트만 남긴다(마스킹).
```c
if (a == (~c & 0xff)) printf("a equal ~c\n");   // 0xf0 == 0xf0 → 출력됨
```
