# Week 2 Day7 — 함수 포인터 활용과 void 포인터

> 2026-10-29 학습 정리

## 구조체에 함수 포인터 담기
```c
typedef struct func {
    const char * name;
    int (*fp)(int, int);
    int res;
} FUNC;
```
```c
const FUNC funcs[] = {
    {"sum", sum},
    {"sub", sub},
    {"mul", mul},
    {"div2", div2},
    {"mod", mod},
};

FUNC * sp = funcs;

const int N = SIZE(funcs);
int n1 = 25, n2 = 6, total = 0;

for(int i = 0; i < N; i++) {
    sp->res = sp->fp(n1, n2);
    total += sp->res;
    printf("%s = %d\n", sp->name, sp->res);
    sp++;
}

printf("sum = %d\n", total);
```
```
sum = 31
sub = 19
mul = 150
div2 = 4
mod = 1
sum = 205
```
- 이름, 함수, 결과를 구조체 한 칸에 묶는다. 연산을 추가할 때 배열에 한 줄만 넣으면 된다.
- `res`처럼 초기값을 주지 않은 멤버는 0으로 채워진다.
- 마지막 줄의 `sum`은 함수 `sum`의 결과가 아니라 다섯 결과의 합계다.
- ⚠️ `const`인 `funcs`를 `FUNC *`로 받아 `res`를 고치는 것은 UB다. 컴파일러도 경고를 낸다. `funcs`와 `sp`에서 `const`를 빼면 해결된다.

## 메뉴로 함수 고르기
```c
while(1) {
    printf("\nWhich operation do you want to perform?\n");
    for(int i = 0; i < N; i++) {
        printf("%d. %s\n", i, funcs[i].name);
    }
    printf("%d. exit\n", N);
    printf("Select (0-%d): ", N);

    scanf("%d", &menu);

    printf("%s = %d\n", funcs[menu].name, funcs[menu].fp(n1, n2));
}
```
- 입력한 번호를 인덱스로 써서 `if`나 `switch` 없이 함수를 고른다.
- 메뉴 글자도 배열에서 만들어서, 연산을 추가하면 메뉴도 함께 늘어난다.
- ⚠️ `5. exit`를 처리하는 코드가 없다. `5`를 입력하면 범위 밖의 `funcs[5]`를 읽어서 UB이고, 실행해 보니 세그폴트가 났다.

범위를 먼저 확인하면 해결된다.
```c
scanf("%d", &menu);

if(menu == N) break;

if(0 <= menu && menu < N) {
    printf("%s = %d\n", funcs[menu].name, funcs[menu].fp(n1, n2));
}
```

### 0번을 exit로 쓰는 메뉴
```c
typedef struct func {
    const char * name;
    int (*fp)(int, int);
    char oper;
    int res;
} FUNC;

int getMenu(FUNC *funcs, size_t n) {
    int menu;

    printf("\nWhich operation do you want to perform?\n");
    printf("0. exit\n");
    for(int i = 1; i < n; i++) {
        printf("%d. %s\n", i, funcs[i].name);
    }
    printf("Select (0-%d): ", n - 1);

    scanf("%d", &menu);

    return menu;
}

const FUNC funcs[] = {
    {0},
    {"sum", sum, '+'},
    {"sub", sub, '-'},
    {"mul", mul, '*'},
    {"div2", div2, '/'},
    {"mod", mod, '%'},
};

while(menu = getMenu(funcs, N))
    printf("%d %c %d = %d\n", n1, funcs[menu].oper, n2, funcs[menu].fp(n1, n2));
```
```
입력: 1 → 25 + 6 = 31
입력: 4 → 25 / 6 = 4
입력: 5 → 25 % 6 = 1
입력: 0 → 종료
```
- 0번 칸을 `{0}`으로 비워 두고 메뉴 번호와 배열 인덱스를 1부터 맞췄다. 0은 종료다.
- `while(menu = getMenu(...))`는 대입한 값이 0이면 반복이 끝난다. 비교(`==`)가 아니라 대입이다.
- `oper` 멤버를 추가해 `25 + 6 = 31`처럼 연산 기호를 출력한다.
- 메뉴 출력과 입력을 `getMenu`로 분리해서 `main`이 짧아졌다.
- ⚠️ 여전히 `6` 이상이나 음수를 입력하면 범위 밖을 읽는다. `1 <= menu && menu < n`을 확인한다.

### enum으로 메뉴 번호에 이름 붙이기
```c
enum MENU {EXIT, SUM, SUB, MUL, DIV, MOD};

while(menu = getMenu(funcs, N)) {
    switch(menu) {
        case SUM:
            printf("%d %c %d = %d\n", n1, funcs[SUM].oper, n2, funcs[SUM].fp(n1, n2));
            break;
        case SUB:
            printf("%d %c %d = %d\n", n1, funcs[SUB].oper, n2, funcs[SUB].fp(n1, n2));
            break;
        /* MUL, DIV, MOD도 같은 모양 */
    }
}
```
- `EXIT`가 0, `SUM`이 1, ... 순서대로 번호가 붙어서 배열 인덱스와 맞는다.
- `case 1:` 대신 `case SUM:`이라 어떤 메뉴인지 바로 읽힌다.
- 범위 밖 번호는 어떤 `case`에도 걸리지 않아 안전하다.
- 다만 다섯 `case`가 같은 코드라서, 범위만 확인하면 앞의 `funcs[menu].fp(...)` 한 줄로 충분하다. `switch`는 메뉴마다 하는 일이 다를 때 쓴다.

## 함수 포인터로 비교 방법 갈아 끼우기
핵심은 정렬 알고리즘의 종류가 아니라 **함수 포인터**다. 정렬 코드를 고치지 않고, 넘기는 함수만 바꿔서 동작을 바꾼다.

### asc와 desc 번갈아 쓰기
```c
int comp_asc(int a, int b)  { return a > b; }
int comp_desc(int a, int b) { return a < b; }

void bubbleSort(int * arr, int n, int (*comp)(int, int)) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(comp(arr[j], arr[j + 1]))
                swap(arr + j, arr + (j + 1));
        }
    }
}
```
```c
bubbleSort(ary, SIZE(ary), comp_asc);    // 2 3 4 5 6 7 8 9 10 12
bubbleSort(ary, SIZE(ary), comp_desc);   // 12 10 9 8 7 6 5 4 3 2
```
- 정렬 함수는 어떤 기준인지 모르고 `comp`의 결과만 보고 교환한다.
- 그래서 함수 이름만 바꿔 넘기면 오름차순과 내림차순을 번갈아 쓸 수 있다.

### qsort에 내가 원하는 비교 넣기
```c
qsort(배열, 요소 개수, 요소 하나의 크기, 비교 함수);
```
`qsort`도 비교 함수를 함수 포인터로 받는다. 무엇을 기준으로 크고 작은지를 내가 정해서 넣을 수 있다. `const void *`로 받으므로 **요소의 주소 타입**으로 캐스팅해서 쓴다.

| 배열 | `void *`의 실제 타입 | 비교 함수 | 내가 정한 기준 |
|---|---|---|---|
| `int ary[]` | `int *` | `compint` | 값 |
| `double doubleAry[]` | `double *` | `compDouble` | 값 |
| `char * charAry[]` | `char **` | `compChar` | 사전 순 |
| `int A[][3]` | `int (*)[3]` | `compDA` | 각 행의 1번 인덱스 값 |
| `score_t scr[]` | `score_t *` | `compScore` | 수학 점수 |

```c
int compChar(const void * a, const void * b) {
    return strcmp(*(char **) a, *(char **) b);
}

int compDA(const void * a, const void * b) {
    int * ap = *(int (*)[3]) a;
    int * bp = *(int (*)[3]) b;
    return ap[1] - bp[1];
}

int compScore(const void * a, const void * b) {
    score_t scoreA = *(score_t *) a;
    score_t scoreB = *(score_t *) b;
    return scoreA.mat - scoreB.mat;
}
```
```c
qsort(scr, SIZE(scr), sizeof(*scr), compScore);   // 수학 점수 20 50 70 85 100 순서
```
- `compScore`에서 `mat`을 `kor`로 바꾸면 국어 점수 기준이 된다. `qsort`는 고칠 필요가 없다.
- `compChar`: 요소가 `char *`이므로 넘어오는 것은 `char **`다. `*`로 한 번 내려야 문자열이 된다.
- `compDouble`: 반환 타입이 `int`라서 `5.14 - 5.10 = 0.04`가 0으로 잘린다. 그래서 빼지 않고 직접 비교한다.

## 복잡한 선언 해석하기와 typedef
함수 포인터 선언은 복잡해 보이지만 읽는 순서가 정해져 있다. `typedef`로 나누면 같은 선언을 훨씬 명료하게 쓸 수 있다.

### 읽는 법
이름에서 시작해 안쪽에서 바깥쪽으로 읽는다. 오른쪽의 `()`와 `[]`를 먼저 보고, 그다음 왼쪽의 `*`를 본다.

```c
int (*getFunction(int no)) (int, int)
```
```
getFunction(int no)      int를 받는 함수인데
*                        포인터를 반환하고
(int, int)               그 포인터는 int 2개를 받는 함수를 가리키며
int                      그 함수는 int를 반환한다
```

```c
int (*(* act(int, int (*) (int))) (int, int))(int, int);
```
```
act(int, int (*)(int))   int와 함수 포인터를 받는 함수인데
*                        포인터를 반환하고
(int, int)               그 포인터는 int 2개를 받는 함수를 가리키며
*                        그 함수도 포인터를 반환하고
(int, int)               그 포인터는 int 2개를 받는 함수를 가리키며
int                      그 함수는 int를 반환한다
```

### typedef로 나누기
```c
typedef int (*FP1)(int);
typedef int (*FP2)(int, int);
typedef FP2 (*FP3)(int, int);
```
| `typedef` | 의미 |
|---|---|
| `FP1` | `int` 1개를 받아 `int`를 반환하는 함수의 포인터 |
| `FP2` | `int` 2개를 받아 `int`를 반환하는 함수의 포인터 |
| `FP3` | `int` 2개를 받아 `FP2`를 반환하는 함수의 포인터 |

같은 선언을 `typedef`로 쓰면 무엇을 받고 무엇을 반환하는지 바로 보인다.

| typedef 없이 | typedef로 |
|---|---|
| `int (*(* act(int, int (*) (int))) (int, int))(int, int);` | `FP3 act(int, FP1);` |
| `int (*getFunction(int no)) (int, int)` | `FP2 getFunction(int no)` |
| `int (*fp)(int, int)` | `FP2 fp` |

`*` 없이 만들면 함수 포인터가 아니라 **함수 타입**이 된다. 이 타입으로 함수를 선언할 수 있다.
```c
typedef int FP4(int, FP1);

FP4 compact;   // int compact(int, FP1); 과 같은 선언
```

### 사용 예
```c
int (*getFunction(int no)) (int, int) {
    static int (*fp[])(int, int) = {sum, sub, mul, div2};
    return fp[no];
}
```
```c
int (*fp)(int, int) = getFunction(3);
printf("%d \n", fp(3, 2));   // div2(3, 2) = 1
```

## void 포인터
```c
typedef int (*FP) (int, int);

void * vp;
int a = 65;
double b = 3.14;

vp = &a;
printf("%d\n", *(int*) vp);        // 65

vp = &b;
printf("%.2lf\n", *(double*) vp);  // 3.14
printf("%d\n", *(int*) vp);        // 1374389535

vp = sum;
printf("%d\n", (*******(int(*)(int, int)) vp)(1, 2));   // 3
printf("%d\n", (***************(FP) vp)(1, 2));         // 3
```
- `void *`에는 어떤 타입의 주소든 캐스팅 없이 담을 수 있다.
- 가리키는 대상의 타입을 모르므로 `*vp`는 안 된다. 쓸 때 캐스팅으로 타입을 알려 준다. `qsort` 비교 함수가 캐스팅하는 이유도 같다.
- 타입을 맞추는 것은 프로그래머의 책임이다. `double`을 `(int*)`로 읽으면 엉뚱한 값이 나온다. ⚠️ 표준으로 따지면 UB다.
- `(FP) vp`처럼 `typedef`를 쓰면 캐스팅도 읽기 쉬워진다.
- ⚠️ 표준 C는 함수 포인터를 `void *`에 담는 것을 보장하지 않는다.

### void 포인터로 swap 만들기
```c
void swapVoid(void * a, void * b, size_t size) {
    char * p1 = a;
    char * p2 = b;

    for(size_t i = 0; i < size; i++) {
        char tmp = p1[i];
        p1[i] = p2[i];
        p2[i] = tmp;
    }
}
```
```c
int a = 10, b = 20;

swapVoid(&a, &b, sizeof(int));
printf("%d %d\n", a, b);   // 20 10
```
- `void *`는 타입을 모르므로 크기를 `size`로 따로 받는다.
- `char *`로 바꿔서 1바이트씩 교환한다. 그래서 `int`뿐 아니라 어떤 타입이든 교환할 수 있다.

## 해볼 것
- 활용에 대해서 AI에게 물어보기
