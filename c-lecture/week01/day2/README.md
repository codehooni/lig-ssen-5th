# Week 1 Day2 — 비트 연산 확장·제어문

> 2026-10-22 학습 정리

## 여러 비트 한 번에 다루기

Day1의 `setBit`(한 비트)을 **s번부터 n개 비트**로 확장한 것.

```c
unsigned int setBits(unsigned int num, int s, int n) {
	return num | (((1 << n) - 1) << s);
}

unsigned int clearBits(unsigned int num, int s, int n) {
	return num & ~(((1 << n) - 1) << s);
}

unsigned int toggleBits(unsigned int num, int s, int n) {
	return num ^ (((1 << n) - 1) << s);
}
```

### 핵심: `((1 << n) - 1) << s`로 연속 마스크 만들기
`1 << n`에서 1을 빼면 **아래 n비트가 전부 1**이 된다. 이걸 s칸 밀면 원하는 위치의 마스크.

```
n = 3, s = 2
1 << 3        = 0000 1000
(1 << 3) - 1  = 0000 0111   ← 1이 3개
... << 2      = 0001 1100   ← 2번부터 3개
```

켜기(`|`) / 끄기(`& ~`) / 뒤집기(`^`)는 Day1과 똑같고, **마스크만 바뀐다.**

### 비트 읽기
```c
unsigned int isBitSet(unsigned int num, int n) {      // Day1의 getBit
    return (num >> n) & 1;
}

unsigned int isBitSets(unsigned int num, int s, int n) {
    return (num >> s) & ((1 << n) - 1);
}
```
- 읽을 때는 반대로 **num을 오른쪽으로 밀어서** 원하는 비트를 0번 자리로 내린 뒤, 마스크로 나머지를 지운다.
- `& 1`: 맨 아래 1비트만 남김 → 0 또는 1
- `& ((1 << n) - 1)`: 맨 아래 n비트만 남김 → 그 비트들이 나타내는 숫자

### 실행 결과
```c
unsigned int a = 0b11001010;

printBits8(a);                     // 11001010
printBits8(setBits(a, 2, 3));      // 11011110  ← 2~4번 켜짐
printBits8(clearBits(a, 6, 2));    // 00001010  ← 6~7번 꺼짐
printBits8(toggleBits(a, 3, 3));   // 11110010  ← 3~5번 뒤집힘
printf("%u\n", isBitSets(a, 1, 2)); // 1        ← 1~2번 = 01
```

```
isBitSets(a, 1, 2)
a          = 1100 1010
a >> 1     = 0110 0101
& 0000 0011= 0000 0001  → 1
```

⚠️ `1 << n`은 signed int라서 `n = 31`이면 부호 비트까지 밀려 UB. Day1처럼 `1u`를 쓰는 게 안전하다. (단, `n = 32`처럼 타입 비트 수 이상 미는 건 `1u`도 UB)

## 짝수/홀수 판별 — `%` vs `&`
```c
int n;
scanf("%d", &n);

if (n % 2 == 0) {
	printf("Even\n");
} else {
	printf("Odd\n");
}

printf((n & 1) ? "odd" : "even");
```

### `n & 1`로 판별하는 원리
2진수에서 **0번 비트(맨 아래)만 홀수 자리(2⁰ = 1)**, 나머지는 전부 짝수 자리다.
→ 0번 비트가 1이면 홀수, 0이면 짝수.
```
6 = 0000 0110  & 1 → 0  → even
7 = 0000 0111  & 1 → 1  → odd
```
- 음수도 2의 보수라 그대로 맞다: `-3 = 1111 1101` → `& 1` = 1 → odd

| | `n % 2 == 0` | `n & 1` |
|---|---|---|
| 연산 | 나눗셈(나머지) | 비트 AND |
| 속도 | 나눗셈은 느린 연산 | 1클럭 |
| 가독성 | 의도가 바로 보임 | 비트를 알아야 함 |

- 최적화를 켜면 컴파일러가 `% 2`도 비트 연산으로 바꿔 준다. 하드웨어 나눗셈기가 없는 MCU(Cortex-M0 등) 코드에서는 `& 1`을 직접 쓰는 경우가 많다.
- 삼항 연산자는 **식**이라 `printf`의 인자로 바로 넣을 수 있다.

## ⭐ else if 대신 return — 조기 반환(early return)
```c
int func(int n) {

	if (n % 2 == 0) return 2;
	if (n % 3 == 0) return 3;
	if (n % 5 == 0) return 5;

	return 0;
}
```
- 조건이 맞으면 **바로 return** → 함수가 끝나므로 아래 `if`는 실행되지 않는다.
- 그래서 `else if`를 쓰지 않아도 `else if`와 **똑같이 동작**한다.
- 예: `n = 6` → 2의 배수에서 바로 `2` 반환. 3 검사까지 가지 않는다.

`else if`로 쓰면 이렇게 된다.
```c
int func(int n) {
	int res;

	if (n % 2 == 0)      res = 2;
	else if (n % 3 == 0) res = 3;
	else if (n % 5 == 0) res = 5;
	else                 res = 0;

	return res;
}
```

| | else if | 조기 반환 |
|---|---|---|
| 구조 | 조건이 늘수록 `else if`가 길게 이어짐 | `if` 한 줄씩 나란히 |
| 결과 변수 | 필요 (`res`) | 필요 없음 |
| 읽는 법 | 앞의 조건을 모두 기억하며 읽어야 함 | 한 줄씩 끊어서 읽으면 됨 |

### 점수 판정 문제도 같은 방식
교재 풀이는 `else if`를 이어 쓴다.
```c
int score = 50;

if (score >= 70) {
	printf("pass\n");
}
else if (score >= 60) {
	printf("try again\n");
}
else {
	printf("fail\n");
}
```
함수로 빼면 `return`으로 `else if`를 없앨 수 있다.
```c
void solution(int score) {
	if (score >= 70) { printf("pass\n");      return; }
	if (score >= 60) { printf("try again\n"); return; }
	printf("fail\n");
}
```
- 반환값이 없는 `void` 함수도 `return;`으로 **중간에 빠져나올 수 있다**.
- `score >= 60`에 도착했다는 건 이미 `score < 70`이라는 뜻 → 범위를 `60 <= score && score < 70`처럼 다시 쓸 필요가 없다.

### 덤: 삼항 연산자 중첩
```c
printf(
	(score >= 70) ? "pass\n" :
	(score >= 60) ? "try again\n" : "fail\n"
);
```
- 삼항 연산자는 결합 방향이 ← 라서 `A ? x : (B ? y : z)`로 묶인다 → `else if`와 같은 순서로 검사.
- 짧을 땐 편하지만, 3단 이상이면 읽기 어려우니 if문을 쓰자.

## switch — `score / 10`이 킥
```c
int score = 89;
char result;

switch (score / 10) {
	case 10:
	case 9:
		result = 'A';
		break;
	case 8:
		result = 'B';
		break;
	case 7:
		result = 'C';
		break;
	case 6:
		result = 'D';
		break;
	default:
		result = 'F';
}

printf("%c", result);   // B
```

### ⭐ 왜 10으로 나누나
- `case` 뒤에는 **정수 상수만** 올 수 있다. `case score >= 90:` 같은 범위 조건은 못 쓴다.
- 정수 / 정수 = 정수(소수점 버림) → `score / 10`은 **10의 자리만 남긴다**.
  ```
  80 ~ 89  → 8
  90 ~ 99  → 9
  100      → 10
  ```
- 범위 10개를 **숫자 하나로 묶어서** case 하나로 처리할 수 있게 된다.

### case 묶기와 break
- `case 10:` 뒤에 아무것도 없고 `break`도 없으면 **아래 `case 9:`로 그대로 넘어간다**(fall-through) → 100점도 `'A'`.
- 나머지 case는 `break`가 없으면 아래 case까지 실행돼서 결과가 덮어써진다. **반드시 `break`.**
- `default`: 어떤 case에도 안 맞을 때 (0~59점 → `'F'`). 필수는 아니다.

## 문자열 테이블 — 메모리를 조금 써서 연산을 없애기
```c
int s = 99;
char* grade = "FFFFFFDCBAA";

printf("%c\n", *(grade + (s / 10)));   // A
```
`s / 10`을 그대로 **문자열의 인덱스**로 쓴다.
```
인덱스  0  1  2  3  4  5  6  7  8  9  10
문자    F  F  F  F  F  F  D  C  B  A  A
```
- `s = 99` → `s / 10 = 9` → `grade[9]` = `'A'`
- `*(grade + 9)`와 `grade[9]`는 같은 뜻. `[]`는 "기준 주소에서 얼마나 이동할지"를 나타낸다.

| | switch | 문자열 테이블 |
|---|---|---|
| 코드 | case 6개 + break | 한 줄 |
| 실행 | case 비교 후 분기 (최적화 시 점프 테이블) | 주소 계산 후 **바로 읽기** (비교 없음) |
| 메모리 | 추가 없음 | 문자열 12바이트 (`'\0'` 포함) |

👉 **메모리를 조금 더 쓰고 연산(비교·분기)을 줄이는 방법** = 룩업 테이블(lookup table). 임베디드에서 sin 값, CRC 같은 계산을 미리 표로 만들어 두고 쓰는 것도 같은 아이디어.

⚠️ 인덱스가 0~10을 벗어나면(`s = 120`, `s = -5`) 문자열 바깥 메모리를 읽는다 → UB. 입력 범위를 먼저 검사해야 한다.

## while vs do-while
| | while | do-while |
|---|---|---|
| 조건 검사 | 먼저 검사 → 실행 | 먼저 실행 → 검사 |
| 최소 실행 횟수 | 0번 | **1번** |
| 끝의 `;` | 없음 | `while (조건);` **세미콜론 필수** |

### 문제 1: 10 이하가 들어올 때까지 다시 입력받기
```c
int n1 = 11;                 // ← 일부러 조건에 맞는 값으로 초기화

while (n1 > 10) {
	printf("number1: ");
	scanf("%d", &n1);
}

int n2;                      // 초기화 필요 없음

do {
	printf("number2: ");
	scanf("%d", &n2);
} while (n2 > 10);
```
- 입력은 **무조건 한 번은 받아야** 한다.
- while은 처음 검사를 통과시키려고 `n1 = 11`처럼 **억지 초기값**이 필요하다. 이 값을 빼먹으면 쓰레기값으로 검사하게 된다.
- do-while은 먼저 입력받고 검사하므로 초기값이 필요 없다.

👉 **"일단 한 번 하고, 조건 보고 반복"이면 do-while이 자연스럽다.**

### 문제 2: 숫자 뒤집어 출력하기
```c
int num = 1300;

do {
	printf("%d", num % 10);   // 1의 자리 출력
	num /= 10;                // 1의 자리 버리기
} while (num > 0);
// 0031
```
- `% 10`으로 맨 끝 자리를 꺼내고, `/ 10`으로 그 자리를 버리는 걸 반복한다.

같은 코드를 while로 쓰면 `num = 0`일 때 차이가 난다.

| 입력 | do-while | while |
|---|---|---|
| 1300 | `0031` | `0031` |
| 1030 | `0301` | `0301` |
| **0** | **`0`** | **(아무것도 안 나옴)** |

- while은 `0 > 0`이 거짓이라 한 번도 실행되지 않는다.
- 0도 "한 자리 숫자"이므로 **최소 한 번은 출력해야** 한다 → do-while이 맞다.

### 내 풀이: 문자열로 뒤집기
숫자 대신 **문자열로 입력받아** 길이를 구한 뒤 뒤에서부터 출력했다.
```c
int myLen(const char * c) {
    int len = 0;
    while(*(c++)) len++;
    return len;
}

int main(void) {
    char input[9];
    scanf("%8s", input);

    int len = myLen(input);

    for(int i = len-1; i >= 0; i--) {
        printf("%c", input[i]);
    }

    return 0;
}
```
- `while(*(c++)) len++;`: Day1 `myStrlen`과 같은 원리. 후치 `++`라서 **현재 문자를 검사한 뒤** 다음 칸으로 이동한다.
- `char input[9]` + `%8s`: 최대 8글자 + `'\0'` 1칸. 폭을 지정해서 버퍼 오버플로를 막는다.
- 0을 입력해도 `"0"`은 길이 1인 문자열이라 `0`이 정상 출력된다 → while/do-while 고민이 없다.

#### 처음에 했던 실수: `'0'`을 전부 건너뛰기
```c
if(input[i] != '0')
    printf("%c", input[i]);
```
| 입력 | 기대 | 실수 버전 |
|---|---|---|
| 1300 | `0031` | `31` |
| 1030 | `0301` | `31` ← 가운데 0까지 사라짐 |
| 0 | `0` | (아무것도 안 나옴) |

→ `if`를 지워서 숫자 풀이(`0031`)와 결과를 맞췄다.

| | 숫자 풀이 (`% 10`, `/ 10`) | 문자열 풀이 |
|---|---|---|
| 입력 | `int` | `char[]` |
| 길이 | 필요 없음 | `myLen`으로 먼저 구함 |
| 0 처리 | do-while이어야 함 | 자동으로 됨 |
| 범위 | int 범위까지 | 버퍼 크기(8자리)까지 |

## 📌 반복문 활용 — 하드웨어 레지스터 제어 (교재 02-4h, 수업 외)
수업에서는 다루지 않았지만 **임베디드에서 가장 기본이 되는 패턴**이라 정리.
```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// 가상의 하드웨어 레지스터
#define BUTTON_REG (*(volatile uint32_t *)0x40000000)
#define LED_REG    (*(volatile uint32_t *)0x40000004)

// 버튼 상태 읽기 함수
static bool isButtonPressed() {
	return (BUTTON_REG & 0x1) != 0;
}

// LED 상태 설정 함수
static void setLED(bool state) {
	LED_REG = (state) ? 1 : 0;
}

int main(void) {
	while (1) {   // 무한반복
		if (isButtonPressed()) {
			setLED(true);    // 버튼이 눌리면 LED 켜기
			printf("Button pressed, LED ON\n");
		}
		else {
			setLED(false);   // 버튼이 눌리지 않으면 LED 끄기
			printf("Button not pressed, LED OFF\n");
		}

		// 짧은 지연 추가 (디바운싱 등)
		for (volatile int i = 0; i < 100000; i++);
	}
}
```

### 메모리 맵 I/O (Memory-Mapped I/O)
MCU에서는 버튼, LED 같은 장치가 **정해진 메모리 주소**에 연결되어 있다. 그 주소를 읽고 쓰면 하드웨어를 읽고 쓰는 것과 같다.
- `0x40000000`을 읽으면 → 버튼 상태
- `0x40000004`에 쓰면 → LED 켜기/끄기
- 실제 주소는 칩 데이터시트(레퍼런스 매뉴얼)의 **메모리 맵**에 나온다.

### `*(volatile uint32_t *)0x40000000` 뜯어보기
안쪽부터 읽는다.
1. `0x40000000`: 그냥 정수
2. `(volatile uint32_t *)`: 그 정수를 **주소로 형변환** → "이 주소에 32비트 값이 있다"
3. 맨 앞 `*`: 그 주소의 **내용**에 접근 → 변수처럼 읽고 쓸 수 있다

```c
LED_REG = 1;          // → *(volatile uint32_t *)0x40000004 = 1;
x = BUTTON_REG;       // → x = *(volatile uint32_t *)0x40000000;
```
- `uint32_t`(`stdint.h`): **크기가 정확히 32비트**인 unsigned. 레지스터 크기와 맞아야 해서 `int` 대신 쓴다.
- 매크로 전체를 `( )`로 감싸서 다른 연산자와 섞여도 안전하게 한다.

### ⭐ `volatile`: "이 값은 내가 모르는 사이에 바뀔 수 있다"
최적화된 컴파일러는 이렇게 생각한다.
> "BUTTON_REG를 아까 읽었고 그 사이에 코드에서 바꾼 적이 없으니, 다시 읽지 말고 아까 값을 쓰자."

하지만 버튼 값은 **사람이 누르면 하드웨어가 바꾼다.** 코드에는 안 보인다.
- `volatile`을 붙이면 → **매번 실제 메모리에서 읽고, 매번 실제로 쓴다.** 최적화로 생략하지 않는다.
- 빠뜨리면 → 디버그 빌드에선 되는데 `-O2`에서 버튼을 눌러도 반응이 없는 버그가 생긴다. (Day1 const 우회 실험에서 `-O0`/`-O2` 결과가 달랐던 것과 같은 원리)

| `volatile`이 필요한 곳 | 이유 |
|---|---|
| 하드웨어 레지스터 | 하드웨어가 값을 바꿈 |
| 인터럽트(ISR)와 공유하는 전역 변수 | 인터럽트가 몰래 바꿈 |
| 지연용 빈 루프 변수 | 하는 일이 없어서 루프째 지워짐 |

### 비트 마스크로 읽기
```c
return (BUTTON_REG & 0x1) != 0;
```
- 레지스터 32비트 중 **0번 비트만** 버튼 상태 → `& 0x1`로 나머지를 지운다 (Day2 `isBitSet`과 같은 원리).
- `!= 0`: 결과를 `true`/`false`로 바꿔서 `bool`로 반환한다.

### 무한 루프 + 지연
- `while (1)`: 임베디드 프로그램은 **끝나지 않는다.** 전원이 꺼질 때까지 "읽기 → 판단 → 출력"을 반복한다 (슈퍼 루프).
- `for (volatile int i = 0; i < 100000; i++);`: 아무것도 안 하고 시간만 보내는 **바쁜 대기(busy wait)**.
  - `volatile`이 없으면 컴파일러가 "할 일 없는 루프"로 보고 통째로 지운다.
  - **디바운싱**: 버튼은 누르는 순간 접점이 떨리면서 짧은 시간에 ON/OFF가 여러 번 튄다. 잠깐 기다렸다 다시 읽어서 튀는 값을 무시한다.
  - 실제로는 CPU 클럭에 따라 시간이 달라지므로 **타이머**나 `HAL_Delay()` 같은 함수를 쓴다.

### `static` 함수
- 함수 앞의 `static` → **이 파일 안에서만** 쓸 수 있는 함수. 다른 `.c` 파일과 이름이 겹쳐도 충돌하지 않는다.

### ⚠️ 주의
- PC에서 실행하면 `0x40000000`은 내 프로그램 메모리가 아니라서 **바로 죽는다** (Access violation / Segmentation fault). MCU에서만 의미가 있는 코드.
- `LED_REG = 1`은 레지스터 **32비트 전체를 덮어쓴다.** 실제 레지스터는 한 레지스터에 여러 핀이 있으므로 다른 비트를 건드리지 않게 비트 연산으로 바꾼다.
  ```c
  LED_REG |= (1u << 0);    // 0번 비트만 켜기 (setBit)
  LED_REG &= ~(1u << 0);   // 0번 비트만 끄기 (clearBit)
  ```
  → Day1, Day2에서 연습한 비트 연산이 바로 이렇게 쓰인다.
