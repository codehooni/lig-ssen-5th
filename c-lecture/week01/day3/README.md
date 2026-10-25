# Week 1 Day3 — 분할 컴파일, 배열과 함수, 정렬, 문자열

> 2026-10-23 학습 정리

## 분할 컴파일 — `.h`와 `.c` 나누기
```
day3/
├─ day3_lib.h       ← 함수 선언 (목록표)
├─ day3_lib.c       ← 함수 정의 (실제 코드)
└─ day3_261023.c    ← main (사용하는 쪽)
```
| 파일 | 들어가는 것 | 역할 |
|---|---|---|
| `.h` (헤더) | 함수 **선언**, 매크로, `#include` | "이런 함수가 있다"고 알려 주는 목록 |
| `.c` (소스) | 함수 **정의** | 실제 동작 |

- `main.c`와 `lib.c`가 모두 `#include "day3_lib.h"`를 한다. 그래서 같은 선언을 공유한다.
- `#include "..."`는 **내 프로젝트 파일**, `#include <...>`는 **표준 라이브러리**에 쓴다.

### 빌드: 두 `.c`를 같이 컴파일
```
gcc day3_261023.c day3_lib.c -o day3
```
1. 컴파일: 각 `.c`를 따로 기계어(`.o`)로 만든다. 이때 다른 파일의 함수는 **선언만 보고 넘어간다**.
2. 링크: `.o` 파일들을 합치면서 선언과 실제 정의를 연결한다.
- `day3_lib.c`를 빼먹으면 컴파일은 되지만 **링크 에러**(`undefined reference to 'inputData'`)가 난다.

### 헤더 가드
```c
#ifndef __DAY3_LIB_H__
#define __DAY3_LIB_H__

// 선언들...

#endif
```
- 처음 include될 때는 `__DAY3_LIB_H__`가 정의되지 않았으니 내용이 들어가고, 이때 이름을 정의한다.
- 같은 헤더가 두 번 include되면 이미 정의되어 있으니 **통째로 건너뛴다**. 그래서 중복 정의 에러가 나지 않는다.
- `#pragma once` 한 줄로도 같은 효과를 낼 수 있다(표준은 아니지만 대부분의 컴파일러가 지원).
- 참고: `__`로 시작하는 이름은 원래 컴파일러용으로 예약되어 있다. `DAY3_LIB_H`처럼 쓰는 게 더 안전하다.

### `SIZE` 매크로 — 배열 요소 개수
```c
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

int score[5] = {0};
inputData(score, SIZE(score));   // SIZE(score) = 20 / 4 = 5
```
- 배열 전체 크기 ÷ 요소 하나 크기 = **요소 개수**
- 숫자 `5`를 직접 쓰지 않으니 배열 크기를 바꿔도 코드를 고칠 곳이 한 군데뿐이다.
- `x`와 `(x)[0]`에 괄호를 씌우는 이유: 매크로는 글자를 그대로 바꿔치기한다. 괄호가 없으면 인자로 식이 들어왔을 때 연산 순서가 꼬인다.
- ⚠️ **배열 이름에만** 쓸 수 있다. 함수 안에서 매개변수 `arr`에 쓰면 `arr`은 포인터라서 `sizeof(arr)`가 8(포인터 크기)이 된다. 그래서 함수에는 개수 `n`을 따로 넘긴다.

## ⭐ 배열의 이름은 무엇인가
```c
int a[4] = {10, 20, 30, 40};   // a가 0x1000에서 시작한다고 하자
```
```
주소  0x1000  0x1004  0x1008  0x100C  0x1010
값      10      20      30      40    (끝 다음)
      a[0]    a[1]    a[2]    a[3]
```

### 1. 기본적으로 배열 이름은 포인터: `a == &a[0]`
- 식에 쓰인 `a`는 **첫 요소의 주소**(`int *`)로 바뀐다.
- 그래서 `a + 1`은 int 하나 크기(4바이트)만큼 이동 → `0x1004` = `&a[1]`
- 함수에 `a`를 넘기면 포인터가 넘어가는 것도 이 때문.

### 2. 두 가지 경우만 배열 그대로
| 식 | 의미 | 결과 |
|---|---|---|
| `sizeof(a)` | 배열 **전체** 크기 | `16` (포인터 크기 8이 아님) |
| `&a` | 배열 **전체**의 주소 (`int (*)[4]`) | 값은 `0x1000`으로 `a`와 같지만 **타입이 다르다** |

`&a`는 "int 4개짜리 배열"을 가리키므로 **+1 하면 배열 전체(16바이트)를 건너뛴다.**
```
a + 1   = 0x1000 + 4  × 1 = 0x1004   (int 하나)
&a + 1  = 0x1000 + 16 × 1 = 0x1010   (배열 하나)
```

### 3. 포인터끼리 빼면 바이트 수가 아니라 요소 개수
```
0x1010 - 0x1000 = 16바이트 → int 단위로 나누면 4 (요소의 개수)
```
```c
&a[4] - &a[0]          // 4
(int *)(&a + 1) - a    // 4  ← 배열 끝 - 배열 시작 = 요소 개수
```
- 포인터 뺄셈 결과는 `(주소 차이) / (가리키는 타입 크기)`.
- Day1 `myStrlen`의 `return s - str;`도 같은 원리로 글자 수를 구했다.
- `SIZE(x)`가 `sizeof`로 하는 일을 주소 뺄셈으로도 할 수 있다는 것.

### 4. 포인터 변수 vs 포인터 상수
| | 포인터 변수 | 포인터 상수 |
|---|---|---|
| 예 | `int *p;`의 `p` | `int a[5];`의 `a`, `"apple"` |
| 주소를 저장하는 공간 | 있음 (p 자체가 변수) | 없음 (그 자체가 주소 값) |
| 다른 주소로 바꾸기 | `p = a;` ✅ | `a = p;` ❌ 컴파일 에러 |
| `++` | `p++` ✅ | `a++` ❌ |

```c
int a[5];
int *p = a;    // p: 포인터 변수 → a의 주소를 담는다

p++;           // ✅ 다음 요소를 가리킴
// a++;        // ❌ 배열 이름은 주소 "값"이라 바꿀 수 없다
```
- 정수 변수 `int n`과 정수 상수 `10`의 관계와 같다. `n = 20`은 되지만 `10 = 20`은 안 된다.
- `p[1]`과 `a[1]`처럼 **사용법은 같다.** 차이는 바꿀 수 있느냐.

### 5. 문자열 리터럴 `"apple"`도 포인터 상수
`"apple"`은 메모리 어딘가(읽기 전용 영역 `.rodata`)에 저장된 문자 배열이고, 식에 쓰이면 **첫 글자의 주소**가 된다. 그래서 배열 이름처럼 쓸 수 있다.
```c
printf("%s\n", "apple" + 2);   // "ple"  ← 2칸 뒤 주소부터 출력
printf("%c\n", "banana"[3]);   // 'a'    ← 3번 요소
```
```
"apple"     a  p  p  l  e  \0
            ↑     ↑
          시작   +2 → "ple"
```

배열과 포인터로 문자열을 받을 때의 차이
```c
char str1[10] = "apple";   // 배열에 "apple"을 복사 → 수정 가능
char *p1 = str1;
p1[0] = 'A';               // ✅ str1이 "Apple"이 됨

char *p2 = "banana";       // 리터럴의 주소만 저장 → 원본은 읽기 전용
// p2[0] = 'B';            // ❌ 컴파일은 되지만 실행 중 에러 (.rodata 수정)

// str1 = "banana";        // ❌ 컴파일 에러: str1은 포인터 상수
p2 = "cherry";             // ✅ p2는 포인터 변수라 다른 주소를 담을 수 있다
```
- 배열 `str1`: **내용은 수정 가능**, 이름(주소)은 변경 불가
- 포인터 `p2`: **가리키는 대상은 변경 가능**, 리터럴 내용은 수정 불가
- 그래서 리터럴을 가리킬 때는 `const char *p2 = "banana";`로 써서 수정 시도를 컴파일 단계에서 막는 게 좋다 (Day1 const 참고).

### 6. 함수 이름도 포인터 상수
함수도 메모리(코드 영역)에 저장되고, **함수 이름은 그 함수의 시작 주소**다.
```c
int sumData(int * arr, int n);

printf("%p\n", (void *)sumData);   // 함수의 주소가 출력된다

int (*fp)(int *, int) = sumData;   // fp: 함수 포인터 "변수"
fp(score, 5);                      // sumData(score, 5)와 같다

// sumData = fp;                   // ❌ 함수 이름은 포인터 "상수"라 바꿀 수 없다
```
- `sumData(score, 5)`에서 `( )`는 "이 주소의 함수를 실행하라"는 **호출 연산자**다. `a[1]`에서 `[ ]`가 "이 주소에서 1칸 이동"인 것과 같은 구조.
- 함수 이름이 주소이기 때문에 **호출하기 전에 선언(또는 정의)이 있어야** 컴파일러가 알 수 있다 → 헤더에 함수 선언을 모아 두는 이유.

👉 **포인터 상수 3가지 정리**
| 포인터 상수 | 가리키는 것 | 같은 타입의 포인터 변수 |
|---|---|---|
| 배열 이름 `a` (`int a[5]`) | 첫 요소 `a[0]` | `int *p = a;` |
| 문자열 리터럴 `"apple"` | 첫 글자 `'a'` | `const char *p = "apple";` |
| 함수 이름 `sumData` | 함수의 시작 코드 | `int (*fp)(int *, int) = sumData;` |

## 배열을 함수에 넘기기
```c
void inputData(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

void printData(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
```
```c
int score[5] = {0};
inputData(score, SIZE(score));
printData(score, SIZE(score));
```
- 배열 이름 `score`는 **첫 요소의 주소**다. 그래서 받는 쪽은 `int * arr`(포인터)로 받는다. `int arr[]`로 써도 똑같이 포인터다.
- 배열이 복사되는 게 아니라 **주소만 넘어간다** → 함수 안에서 `arr[i]`를 바꾸면 main의 `score`가 바뀐다. `inputData`가 값을 채울 수 있는 이유.
- 포인터만으로는 개수를 알 수 없으니 `n`을 같이 넘긴다.
- `&arr[i]`: i번째 요소의 주소. `arr + i`와 같다.

### 합계와 평균
```c
int sumData(int * arr, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

double avgData(int * arr, int n) {
    return (double) sumData(arr, n) / n;
}
```
- 만들어 둔 `sumData`를 **재사용**한다.
- `(double)`을 붙여야 실수 나눗셈이 된다. 빼면 정수 / 정수 = 정수라서 소수점이 버려진다.
  ```
  합계 156, n = 5
  (double)156 / 5 → 31.20
  156 / 5         → 31
  ```

### 최댓값, 최솟값
```c
int findMaxData(int * arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}
```
- 시작값을 `0`이 아니라 **`arr[0]`**으로 잡는다. `0`으로 시작하면 모든 값이 음수일 때 최댓값이 0으로 나온다.
- `arr[0]`을 이미 썼으니 반복은 `i = 1`부터.
- `findMinData`는 부등호만 반대(`min > arr[i]`).

### swap — 포인터로 두 값 바꾸기
```c
void swap(int * p1, int * p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

swap(&a, &b);
```
- 값을 넘기면(`swap(a, b)`) 함수 안의 **복사본**만 바뀌고 main의 `a`, `b`는 그대로다(call by value).
- **주소를 넘기면** `*p1`, `*p2`로 원래 변수에 직접 접근해서 바꿀 수 있다(call by reference).
- `temp` 없이 `*p1 = *p2;`부터 하면 `*p1`의 원래 값이 사라진다.

### 실행 결과
```
입력: 50 20 45 10 30

50 20 45 10 30
total = 155
average = 31.00
max = 50
min = 10
```

## 선택 정렬
**앞자리부터 하나씩, 남은 것 중 가장 작은 값을 골라 채운다.**
```
[50 20 45 10 30]
i=0: 남은 것 중 최소 10 → 0번 자리로   [10 | 20 45 50 30]
i=1: 남은 것 중 최소 20 → 그대로       [10 20 | 45 50 30]
i=2: 남은 것 중 최소 30 → 2번 자리로   [10 20 30 | 50 45]
i=3: 남은 것 중 최소 45 → 3번 자리로   [10 20 30 45 | 50]
```

### 수업 버전: 더 작은 값을 만날 때마다 바로 교환
```c
void selectionSort(int * arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j])
                swap(arr + i, arr + j);
        }
    }
}
```

### 내 버전: 최솟값 위치를 먼저 찾고, 한 번만 교환
```c
int findMinIndex(int * arr, int start, int n) {
    int minIndex = start;
    for (int i = start + 1; i < n; i++) {
        if (arr[minIndex] > arr[i])
            minIndex = i;
    }
    return minIndex;
}

void selectionSortData(int * arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = findMinIndex(arr, i, n);
        swap(arr + i, arr + minIndex);
    }
}
```
- 비교하는 동안은 **인덱스만 기억**하고, 자리 하나당 swap은 **딱 1번**.
- 최솟값 찾기를 `findMinIndex`로 분리 → `selectionSortData`가 "찾고, 바꾼다" 두 줄로 읽힌다.

| 입력 | 수업 버전 swap 횟수 | 내 버전 swap 횟수 |
|---|---|---|
| `50 20 45 10 30` | 7 | 4 |
| `50 40 30 20 10` (역순) | 10 | 4 |

- 비교 횟수는 둘 다 같다(n(n-1)/2). 차이는 **swap 횟수**. swap은 값 3번 이동이라 비교보다 비싸다.
- 내 버전은 항상 n-1번이라, 이미 정렬된 입력에서도 자기 자신과 4번 swap한다. `if (minIndex != i)`를 붙이면 이것도 없앨 수 있다.

## 📌 더 해본 것: 버블 정렬, 삽입 정렬 (수업 외)

### 버블 정렬 — 이웃끼리 비교해서 큰 값을 뒤로
```c
void bubbleSortData(int * arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr + j, arr + (j + 1));
        }
    }
}
```
- 한 바퀴 돌 때마다 **가장 큰 값이 맨 뒤로** 떠오른다(거품처럼).
- 뒤쪽 `i`개는 이미 자리를 잡았으니 `j < n - 1 - i`까지만 본다.

### 삽입 정렬 — 앞쪽 정렬된 부분에 끼워 넣기
```c
void insertionSortData(int * arr, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] > arr[j + 1])
                swap(arr + j, arr + (j + 1));
            else
                break;
        }
    }
}
```
- 카드 정리하듯이, i번 값을 앞쪽으로 한 칸씩 옮기다가 **자리를 찾으면 `break`**.
- 거의 정렬된 입력이면 바로 `break`해서 매우 빠르다.

### 세 가지 비교
| | 선택 (내 버전) | 버블 | 삽입 |
|---|---|---|---|
| 방식 | 최솟값 골라 앞에 | 이웃 비교, 큰 값을 뒤로 | 앞쪽에 끼워 넣기 |
| swap (`50 20 45 10 30`) | 4 | 7 | 7 |
| swap (이미 정렬됨) | 4 | 0 | 0 |
| 이미 정렬된 입력 | 그래도 끝까지 비교 | 끝까지 비교 | 비교 1번씩 하고 `break` → 빠름 |

- 셋 다 기본 시간 복잡도는 **O(n²)**. 데이터가 많으면 퀵 정렬, 병합 정렬 같은 O(n log n) 정렬을 쓴다.

## 변수의 구성 (교재 06-1)
```c
static const unsigned int * a = 100;
```
| 부분 | 이름 | 역할 |
|---|---|---|
| `static` | storage class specifier (기억 부류) | 변수가 **어디에, 얼마나 오래** 있는지. `static`, `extern`, `auto`, `register` |
| `const` | type qualifier (형 한정자) | `const`: 변수를 상수로 / `volatile`: 최적화 금지 |
| `unsigned int` | type specifier (자료형) | **반드시 하나** 필요. 메모리 크기와 성격 |
| `*` | modifier (수식자) | `*`: 주소화, `[ ]`: 배열화, `( )`: 함수화. 우선순위 **`( )` > `[ ]` > `*`** |
| `a` | identifier (식별자) | 변수 이름 |
| `100` | initializer (초기값) | 전역 변수는 **상수만** 초기값으로 쓸 수 있다 |

- 이 중 **자료형과 이름만 필수**, 나머지는 필요할 때 붙인다.
- modifier 우선순위는 바로 아래 "변수 선언 읽는 법"에서 쓴다.

### storage class: extern, static
| | 의미 |
|---|---|
| `extern` | "이 변수(함수)는 **다른 파일에 정의**되어 있다" — 선언만, 메모리를 만들지 않음 |
| `static` (전역/함수 앞) | **이 파일 안에서만** 쓸 수 있다 (Day2 레지스터 예제의 `static` 함수) |
| `static` (지역 변수 앞) | 함수가 끝나도 **값이 유지**된다 (호출 횟수 세기 등) |

수업에서 `swap`을 만들면서 곁다리로 extern을 써 봤다.
```c
// day3_lib.c
int a = 20;          // 전역 변수 정의 (메모리가 여기 생김)

// day3_261023.c
extern int a;        // "a는 다른 파일에 있다" (선언)

int main(void) {
    int a = 10, b = 20;   // ← 지역 변수 a가 전역 a를 가린다
    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);   // a = 20, b = 10
}
```
- 분할 컴파일에서 다른 파일의 전역 변수를 쓰려면 `extern`으로 선언한다. 함수 선언은 `extern`을 생략해도 기본으로 extern이다 (헤더의 함수 선언들).
- ⚠️ 위 코드는 main 안에 같은 이름 `a`를 또 선언해서 **지역 변수가 전역 변수를 가린다.** 그래서 `swap`은 지역 `a`, `b`를 바꾸고 전역 `a`(20)는 쓰이지 않는다. 전역 `a`를 쓰려면 main의 `int a`를 빼야 한다.

## ⭐ 변수 선언 읽는 법
선언에 붙는 기호의 우선순위는 **`( )` > `[ ]` > `*`**.

**읽는 순서**
1. **변수 이름**에서 시작한다.
2. 오른쪽의 `[ ]`, `( )`를 먼저 읽는다.
3. 왼쪽의 `*`를 읽는다.
4. 괄호로 묶여 있으면 **괄호 안부터** 다 읽고 밖으로 나간다.
5. 마지막에 맨 왼쪽의 자료형을 붙인다.

| 기호 | 읽는 법 |
|---|---|
| `[n]` | array of n (n개짜리 배열) |
| `*` | pointer to (~를 가리키는 포인터) |
| `(…)` | function returning (~를 반환하는 함수) |

### 배열 포인터 vs 포인터 배열
```c
char (*p)[5];   // 배열 포인터
char *p[5];     // 포인터 배열
```
**`char (*p)[5]` — 배열 포인터**
```
p → (*p) 괄호 안 먼저: pointer to
  → [5]                : an array of 5
  → char               : char
= pointer to an array of 5 char  (char 5개짜리 배열을 가리키는 포인터)
```
- 포인터 **1개**(8바이트). `p + 1`은 배열 하나(5바이트)를 건너뛴다.
- `&a`(배열 전체의 주소)의 타입이 바로 이것. `char a[5];`이면 `&a`는 `char (*)[5]`.

**`char *p[5]` — 포인터 배열**
```
p → [5]  ( [ ]가 *보다 먼저): an array of 5
  → *                        : pointer to
  → char                     : char
= an array of 5 pointer to char  (char 포인터 5개짜리 배열)
```
- 포인터가 **5개**(40바이트). 문자열 여러 개를 담을 때 쓴다.
  ```c
  char *fruits[3] = {"apple", "banana", "cherry"};
  ```

👉 괄호 하나 차이로 뜻이 완전히 달라진다. **괄호가 있으면 괄호 안이 먼저.**

### 함수 포인터
```c
int (*fp)(int *, int);
```
```
fp → (*fp)       : pointer to
   → (int *, int): function (int *, int를 받는)
   → int         : returning int
= pointer to function (int *, int) returning int
```
- 함수 이름도 배열 이름처럼 **함수의 주소(포인터 상수)**다. 그래서 `fp = sumData;`로 담을 수 있다.
- `fp(score, 5)`로 호출하면 `sumData(score, 5)`와 같다.
- 괄호를 빼고 `int *fp(int *, int);`로 쓰면 → `( )`가 `*`보다 먼저 → "int *를 반환하는 **함수** fp"의 선언이 된다.

### 응용: 구조체로 함수 포인터 배열 만들기
`sumData`, `findMaxData`, `findMinData`는 모두 `int (int *, int)` 모양이라 **같은 함수 포인터 타입**에 담을 수 있다. 이름 문자열과 함께 구조체로 묶었다.
```c
struct myFunc_t {
    int (*fp) (int*, int);   // 함수 포인터
    char * name;             // 출력용 이름
};

struct myFunc_t myFuncArr[] = {
    {sumData, "sum"},
    {findMaxData, "max"},
    {findMinData, "min"},
};

for (int i = 0; i < 3; i++) {
    printf("%s = %d\n", myFuncArr[i].name, myFuncArr[i].fp(score, SIZE(score)));
}
```
```
입력: 50 20 45 10 30

sum = 155
max = 50
min = 10
```
- 함수 3개를 **반복문 하나로** 호출할 수 있다. 함수가 늘어나도 배열에 한 줄만 추가하면 된다.
- 구조체 없이 함수 포인터만 배열로 만들면 이렇게 된다.
  ```c
  int (*fpArr[3])(int *, int) = {sumData, findMaxData, findMinData};
  ```
  읽기: `fpArr` → `[3]` array of 3 → `*` pointer to → `(int *, int)` function → `int` returning int
  = **array of 3 pointer to function returning int**

### Left-Right 법 (교재 06-4)
교재는 **한국어 문장**을 만들기 위해 바깥(자료형)에서 안(이름)으로 읽는다.
1. **자료형(datatype)에서 시작**한다 (기본적으로 왼쪽 → 오른쪽).
2. 왼쪽 속성(`*`)이 없으면 **오른쪽**(`( )`, `[ ]`)을 살핀다.
3. 오른쪽 속성이 없으면 **왼쪽**을 살핀다.
4. **식별자(이름)에서 멈춘다.** `( )`와 `[ ]`의 우선순위가 `*`보다 높다.

영어로 읽을 때는 **반대로 이름에서 시작**해서 바깥으로 나간다. 한국어는 "~하는 ~"로 꾸밈말이 앞에 오고, 영어는 "a pointer to ~"로 뒤에 오기 때문에 순서가 반대일 뿐 같은 규칙이다.

### 치환해서 읽기
복잡한 선언은 **안쪽 덩어리를 이름 하나로 바꿔서** 바깥부터 읽으면 쉽다.

**① `int * (*a[5]) (int *);`**
```
a → [5] → * → (int *) → int *
```
- array of 5 pointer to function (int *) returning pointer to int
- **int \*를 받아 int \*를 리턴하는 함수를 가리키는 포인터 5개짜리 배열** (함수 포인터 배열)

**② `int ( * (*ap) (void) ) (void);`**
```
int ( * (*ap)(void) ) (void);
        ~~~~~~~~~~~ 이 부분을 fp로 바꾸면
int ( * fp ) (void);          ← fp: pointer to function returning int
```
→ `(*ap)(void)`가 **함수 포인터를 리턴한다**는 뜻.
- a pointer to function returning **a pointer to function returning int**
- **int를 반환하는 함수를 가리키는 포인터를 반환하는 함수를 가리키는 포인터 변수 ap**

**③ `char * ( * (*var) (void) ) [10];`**
```
char * ( * (*var)(void) ) [10];
           ~~~~~~~~~~~~ fp로 바꾸면
char * ( * fp ) [10];         ← fp: pointer to array of 10 pointer to char
```
→ `(*var)(void)`가 **배열 포인터를 리턴한다**는 뜻.
- a pointer to function returning **a pointer to an array of 10 pointer to char**
- **char 포인터를 원소로 하는 10개짜리 배열을 가리키는 포인터를 리턴하는 함수를 가리키는 포인터**

> ⚠️ 영어로 옮길 때 자주 하는 실수
> - ②에서 `returning a pointer to int`라고 쓰기 쉽다. `( * fp ) (void)`이므로 int가 아니라 **function**을 가리키는 포인터다.
> - ③에서 `returning an array of ...`라고 쓰기 쉽다. C 함수는 **배열을 리턴할 수 없다.** `( * fp )`의 `*` 때문에 배열을 **가리키는 포인터**를 리턴한다.

### 2차원 배열 `int a[3][4];`
```
a → [3] → [4] → int
= an array of 3 arrays of 4 int  (int 4개짜리 배열을 3개 갖는 배열)
```
| 식 | 타입 | 뜻 |
|---|---|---|
| `a[0]` (요소) | `int [4]` | **int 4개짜리 배열** 하나 |
| `a` (식에서, 첫 요소의 주소) | `int (*)[4]` | 배열 포인터 |
| `a[0][0]` | `int` | 정수 하나 |

- 크기가 3인 배열이고, **각 요소는 `int [4]`**(int 4개짜리 배열)다.
- `int (*)[4]`는 요소의 타입이 아니라, 배열 이름 `a`가 식에서 바뀌는 타입(첫 요소 `a[0]`의 주소)이다. 1차원 `int a[5]`의 `a`가 `int *`로 바뀌는 것과 같은 규칙.
- 그래서 2차원 배열을 받는 포인터는 `int (*p)[4] = a;` (배열 포인터). `p + 1`은 한 행(16바이트)을 건너뛴다.

## 문자열 복사와 입력
### strcpy — 문자 배열에 문자열 넣기
```c
char str1[80] = "cat";
char str2[80];

strcpy(str1, "tiger");   // str1 = "tiger"
strcpy(str2, str1);      // str2 = "tiger"

printf("%s, %s\n", str1, str2);   // tiger, tiger
```
- 배열 이름은 포인터 상수라 `str1 = "tiger";`는 안 된다 → **`strcpy`로 한 글자씩 복사**한다.
- 초기화(`char str1[80] = "cat";`)는 선언할 때만 예외적으로 된다.
- ⚠️ 복사받는 배열이 충분히 커야 한다. 크기 검사를 하지 않는다.

### ⭐ scanf는 공백, gets는 엔터가 기준
| 함수 | 어디까지 읽나 | 끝의 공백/`'\n'` |
|---|---|---|
| `scanf("%s", str)` | 앞쪽 공백은 건너뛰고, **공백·탭·엔터 전까지** | **버퍼에 남는다** |
| `scanf("%c", &c)` | **딱 1글자** (공백, `'\n'`도 한 글자로 읽음) | - |
| `gets(str)` | **엔터 전까지** (중간 공백 포함) | `'\n'`은 버퍼에서 꺼내서 버림, 저장 안 함 |
| `fgets(str, size, stdin)` | 엔터까지, 최대 `size - 1`글자 | `'\n'`까지 **str에 저장** |

```
입력: hello world⏎

scanf("%s", str) → str = "hello"         버퍼에 " world\n" 남음
gets(str)        → str = "hello world"   버퍼 비어 있음
```
👉 **띄어쓰기가 있는 문장을 받으려면 gets(fgets), 단어 하나는 scanf.**

### ⭐ 입력 버퍼에 남은 `'\n'` 문제
키보드로 입력한 글자는 **입력 버퍼**에 쌓이고, scanf는 필요한 만큼만 꺼내 간다. 꺼내지 않은 건 버퍼에 그대로 남아 **다음 입력 함수가 가져간다.**
```c
char c;
scanf("%c", &c);   // 'a' 입력 후 엔터
printf("%c\n", c); // a

scanf("%c", &c);   // ← 입력을 기다리지 않고 바로 넘어간다
printf("%c\n", c); // (줄바꿈) ← 앞에서 남은 '\n'을 읽었다
```
```
입력 버퍼:  [a][\n]
1번째 %c → a 가져감      남은 버퍼: [\n]
2번째 %c → \n 가져감     ← 사용자는 입력한 적이 없는데 바로 끝남
```
- `%s`, `%d`는 앞쪽 공백을 알아서 건너뛰어서 이 문제가 잘 안 보인다. **`%c`와 `gets`/`fgets`만 공백과 `'\n'`도 그대로 읽는다.**
- `scanf("%d")` 다음에 `gets`/`fgets`를 쓰면, 남은 `'\n'`만 읽고 빈 문자열로 끝난다. 같은 문제.

**해결 방법**
```c
scanf(" %c", &c);                     // %c 앞에 공백 → 공백·엔터를 건너뛰고 읽기

while (getchar() != '\n');            // 버퍼에 남은 걸 '\n'까지 비우기
```

### gets 대신 fgets
수업에서는 `gets`를 썼지만 **gets는 C11에서 표준에서 삭제**됐다. 배열 크기를 모르고 입력을 끝까지 넣어서 버퍼 오버플로가 나기 때문. gcc에서도 경고가 나거나 쓸 수 없어서 `fgets`로 대신했다.
```c
char str[80] = {0};

fgets(str, sizeof(str), stdin);   // 최대 79글자 + '\0'
str[strcspn(str, "\n")] = '\0';   // 끝에 붙은 '\n' 제거
```
- `fgets`는 `'\n'`까지 저장하므로 gets와 똑같이 쓰려면 지워야 한다.
- `strcspn(str, "\n")`: `str`에서 `'\n'`이 처음 나오는 위치(인덱스). 그 자리에 `'\0'`을 넣어 문자열을 끝낸다. `'\n'`이 없으면 문자열 끝 위치라 그대로 `'\0'`이 들어가서 안전하다.
- VS에서는 `gets_s(str, sizeof(str))`도 쓸 수 있다.
