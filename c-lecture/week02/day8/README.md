# Week 2 Day8 — 동적 메모리와 구조체

> 2026-10-30 학습 정리

## malloc과 realloc
```c
int * arr, n = 10;

arr = (int *)malloc(10 * sizeof(int));

if (arr == NULL) {
    printf("There's no memory.");
    exit(1);
}

for(int i = 0; i < 10; i++) {
    arr[i] = 10 * i;
}

int * temp = (int *) realloc(arr, n * sizeof(int));

if(temp == NULL) return 12;
if(temp != arr) arr = temp;
arr[3] = 1000;

free(arr);
arr = NULL;
```
```
0 10 20 30 40 50 60 70 80 90
0 10 20 1000 40 50 60 70 80 90
```
- `malloc`은 바이트 수를 받아 할당하고 첫 주소를 돌려준다. 실패하면 `NULL`이다.
- `realloc`은 `temp`로 받는다. `arr = realloc(arr, ...)`은 실패할 때 `arr`이 `NULL`로 덮여 원래 주소를 잃어버린다.
- `realloc`은 자리가 모자라면 새 곳으로 옮기고 값을 복사한다. 주소가 바뀔 수 있어서 반환값을 꼭 받아 쓴다.
- `free` 뒤에 `NULL`을 넣어 해제한 주소를 다시 쓰는 실수를 막는다.

## 입력에 따라 메모리 늘리기
```c
int * arr, * temp;
int num;
int size = 10, index;

arr = (int *) malloc(size * sizeof(int));

if(arr == NULL) {
    printf("There's no memory.");
    exit(1);
}

for(index = 0; (num = getInt()) > 0; index++) {

    if(index == size) {
        size += 5;

        temp = (int *) realloc(arr, size * sizeof(int));

        if(temp == NULL) {
            printf("There's no memory.");
            free(arr);
            exit(1);
        }

        arr = temp;
    }

    arr[index] = num;
}

printData(arr, index);

free(arr);
arr = NULL;
```
```
입력: 1 2 3 4 5 6 7 8 9 10 11 12 0
출력: 1 2 3 4 5 6 7 8 9 10 11 12
```
- 입력 개수를 모를 때 10칸으로 시작하고, 찼을 때만 5칸씩 늘린다.
- `index == size`는 모든 칸이 찼다는 뜻이다. 범위를 넘지 않도록 값을 저장하기 전에 확인한다.
- `size`는 할당한 칸 수이고, `index`는 저장한 개수다. 출력에는 `index`를 넘긴다.
- `realloc`이 실패해도 원래 메모리는 남아 있다. 그래서 `free(arr)`로 해제하고 끝낸다.

## calloc으로 문자열 배열 만들기
```c
typedef char (*p21c)[21];
typedef char c21[21];

freopen("data.txt", "r", stdin);

int n;
p21c arr;

scanf("%d", &n);
getchar();

arr = (p21c) calloc(n, sizeof(c21));

for(int i = 0; i < n; i++) {
    gets(arr[i]);
}

for(int i = 0; i < n; i++) {
    printf("%s\n", arr[i]);
}
```
```
apple
banana
kiwi
```
- `char [n][21]`을 동적으로 만든다. 행 수는 실행할 때 정하고, 열은 21로 고정한다.
- `c21`은 `char [21]` 타입이고, `p21c`는 그 배열을 가리키는 `char (*)[21]` 타입이다.
- `calloc`은 요소 개수와 크기를 따로 받고, 0으로 초기화한다.
- `freopen`은 표준 입력을 파일로 바꾼다.
- `getchar()`로 `scanf`가 남긴 줄바꿈을 지운다. 지우지 않으면 첫 `gets`가 빈 줄을 읽는다.
- ⚠️ `gets`는 배열 크기를 확인하지 않아 C11에서 표준에서 제거됐다. `fgets`를 쓴다.

## char **로 문자열 배열 만들기
```c
typedef char ** s_arr_t;
typedef char * str_t;

freopen("data.txt", "r", stdin);

int n, len = 21;
str_t str;
s_arr_t arr;

scanf("%d", &n);
getchar();

arr = (s_arr_t) calloc(n, sizeof(str));

if(arr == NULL) exit(1);

for(int i = 0; i < n; i++) {
    str = (str_t) calloc(len, sizeof(char));

    if(arr == NULL) exit(1);

    gets(str);
    arr[i] = str;
}

for(int i = 0; i < n; i++) {
    printf("%s\n", arr[i]);
}
```
- 먼저 포인터 `n`개짜리 배열을 만들고, 문자열마다 21바이트를 따로 할당해 그 주소를 `arr[i]`에 넣는다.
- ⚠️ `str`을 할당한 뒤 `arr`을 확인하고 있다. `if(str == NULL)`이어야 한다.

| | `char (*)[21]` | `char **` |
|---|---|---|
| 할당 횟수 | 1번 | `n + 1`번 |
| 문자열 위치 | 한 줄로 이어짐 | 따로따로 떨어짐 |
| `arr[i]` | 21바이트씩 이동한 행 | 포인터 칸에 저장된 주소 |
| 해제 | `free` 1번 | 문자열마다 `free`, 마지막에 `arr`도 `free` |

## 문자열 길이만큼만 할당하기
```c
typedef char ** s_arr_t;
typedef char str_t[21];

freopen("data.txt", "r", stdin);

int n;
str_t str;
s_arr_t arr;

scanf("%d", &n);
getchar();

arr = (s_arr_t) calloc(n, sizeof(char *));

if(arr == NULL) exit(1);

for(int i = 0; i < n; i++) {
    gets(str);

    arr[i] = (char *) malloc((strlen(str) + 1) * sizeof(char));

    if(arr[i] == NULL) exit(1);

    strcpy(arr[i], str);
}

for(int i = 0; i < n; i++) {
    printf("%s\n", arr[i]);
}

freeDoubleMem((void ***) &arr, n);
```
- 21바이트 임시 버퍼로 읽은 뒤, 실제 길이만큼만 할당해서 복사한다. `kiwi`는 21바이트 대신 5바이트만 쓴다.
- `strlen`은 `'\0'`을 세지 않아서 `+ 1`이 필요하다.
- `arr[i] = str`로 넣으면 모든 칸이 같은 버퍼를 가리킨다. 그래서 `strcpy`로 복사한다.

### 이중 포인터 메모리 해제
```c
void freeDoubleMem(void *** p, int n) {
    if(p == NULL) return;

    for(int i = 0; i < n; i++) {
        free((*p)[i]);
        (*p)[i] = NULL;
    }

    free(*p);
    *p = NULL;
}
```
- 문자열들을 먼저 해제하고 `arr`을 마지막에 해제한다. `arr`부터 해제하면 문자열 주소를 읽을 수 없다.
- `main`의 `arr` 자체를 `NULL`로 바꾸려고 `&arr`을 넘긴다. 그래서 `void ***`다.
- ⚠️ `char ***`를 `void ***`로 바꿔 접근하는 것은 표준으로 엄밀히 따지면 UB다. 실제로는 대부분 잘 동작한다.

## 할당을 함수로 분리하기
```c
char ** getData(int n) {
    str_t str;
    s_arr_t arr;

    arr = (s_arr_t) calloc(n, sizeof(char *));

    if(arr == NULL) exit(1);

    for(int i = 0; i < n; i++) {
        gets(str);

        arr[i] = (char *) malloc((strlen(str) + 1) * sizeof(char));

        if(arr[i] == NULL) exit(1);

        strcpy(arr[i], str);
    }

    return arr;
}
```
```c
arr = getData(n);

for(int i = 0; i < n; i++) {
    printf("%s\n", arr[i]);
}

freeDoubleMem((void ***) &arr, n);
```

| 메모리 | 저장 위치 | `getData`가 끝난 뒤 |
|---|---|---|
| `str`, `arr` 변수 | 스택 (지역) | 사라짐 |
| `calloc`, `malloc`으로 받은 메모리 | 힙 | `free`할 때까지 남음 |

- 지역 배열의 주소를 반환하면 UB지만, 힙 주소는 함수가 끝나도 유효하다.
- `str`은 사라지지만 내용을 `strcpy`로 힙에 복사해 두어서 문제없다.
- 할당은 `getData`에서, 해제는 `main`에서 한다. 해제할 책임이 호출한 쪽으로 넘어온다.

## 큰 메모리 하나에 주소와 문자열 함께 담기
과제: 큰 메모리를 한 번 할당 받아 주소와 문자를 모두 저장하고, `realloc`으로 불필요한 메모리를 반환한다.

```c
char **arr, **tmp, *last;
int n, size;

arr = malloc(1000);

scanf("%d", &n);

arr[0] = (char *) arr + (n * sizeof(char *));
scanf("%s", arr[0]);

for(int i = 1; i < n; i++) {
    arr[i] = arr[i - 1] + (strlen(arr[i - 1]) + 1);
    scanf("%s", arr[i]);
}

last = arr[n - 1] + (strlen(arr[n - 1]) + 1);

size = last - (char *) arr;

tmp = realloc(arr, size);
if(tmp == NULL) {
    free(arr);
    return EXIT_FAILURE;
}

if(arr != tmp) {
    tmp[0] = (char *) tmp + (n * sizeof(char *));

    for(int i = 1; i < n; i++) {
        tmp[i] = tmp[i - 1] + (strlen(tmp[i - 1]) + 1);
    }

    arr = tmp;
}

for(int i = 0; i < n; i++) {
    printf("%s ", arr[i]);   // apple banana kiwi
}

free(arr);
arr = NULL;
```
```
arr
│
▼
[arr[0]][arr[1]][arr[2]][apple\0][banana\0][kiwi\0]
 8바이트  8바이트  8바이트   6바이트    7바이트   5바이트
└───── 24바이트 ─────┘└────── 18바이트 ──────┘   합계 42바이트 (x64)
```
- 앞쪽은 포인터 자리이고, 문자열은 그 뒤에 이어 붙인다. `(char *)`로 바꿔서 바이트 단위로 계산한다.
- `last - (char *) arr`이 실제로 쓴 크기다. `realloc`으로 1000바이트를 42바이트로 줄인다.
- ⚠️ `realloc`으로 자리가 옮겨지면 `arr[i]`에는 옛 주소가 남는다. 그래서 새 위치 기준으로 다시 계산한다.
- 할당이 한 번뿐이라 `free(arr)` 한 번으로 해제가 끝난다.
- ⚠️ `malloc(1000)`의 `NULL` 확인과, 입력이 1000바이트를 넘는 경우의 처리가 없다.

## 구조체 기초
```c
struct student {
    int num;
    double grade;
    char name[20];
    char * phone;
};

typedef struct student student_t;

void printStudent(student_t a) {
    printf("%d %.1lf %s\n", a.num, a.grade, a.name);
}

void printStudent_p(student_t * p) {
    printf("%d %.1lf %s\n", p -> num, p -> grade, p -> name);
    printf("%d %.1lf %s\n", (*p).num, (*p).grade, (*p).name);
}
```
```c
student_t a = { 1, 4.3, "Tom", "010-0000-0000" };
student_t b;

b = a;
strcpy(b.name, "SOS");

printStudent(a);      // 1 4.3 Tom
printStudent_p(&b);   // 1 4.3 SOS (두 줄)
```

### 구조체 대입은 얕은 복사
| 멤버 | `b = a` 결과 | `b`를 고치면 |
|---|---|---|
| `char name[20]` | 글자 20칸 자체가 복사됨 | `a.name`은 그대로 |
| `char * phone` | 주소만 복사됨 | 두 구조체가 같은 문자열을 가리킴 |

- 배열은 `strcpy`로 내용을 복사한다. `a.name = "SOS"`는 컴파일 에러다.
- 포인터는 `a.phone = "..."`처럼 주소를 대입한다.

### 값으로 넘기기와 주소로 넘기기
- `printStudent(a)`는 구조체 전체를 복사하고, `printStudent_p(&b)`는 주소만 복사한다.
- `p -> num`과 `(*p).num`은 같다. `.`이 `*`보다 먼저 계산되어 괄호가 필요하므로 보통 `->`를 쓴다.

### 구조체 크기와 패딩
```
num(4) + 패딩(4) + grade(8) + name(20) + 패딩(4) + phone(8) = 48 (x64)
```
멤버 크기의 합은 40이지만, `double`과 포인터가 8의 배수 주소에 놓이도록 패딩이 들어가 48이 된다.

## 구조체 배열
```c
typedef struct student {
    int num;
    double grade;
    char name[20];
}student_t;

void initStudent(student_t * arr, size_t n) {

    student_t * p;

    for(int i = 0; i < n; i++) {
        p = arr + i;
        scanf("%d %lf %s", &p -> num, &p -> grade, p -> name);
    }

}

void printStudent(student_t * arr, size_t n) {

    student_t * p;

    for(int i = 0; i < n; i++) {
        p = arr + i;
        printf("%d %.1lf %7s\n", p -> num, p -> grade, p -> name);
    }

}
```
```c
freopen("student.txt", "r", stdin);

const int N = 4;
student_t arr[N];

initStudent(arr, N);

printStudent(arr, N);
```
```
1 4.3  Ceyhun
2 3.8     Tom
3 4.2   Jerry
4 3.7   Henry
```
- `arr + i`는 구조체 크기만큼 움직여 i번째 학생을 가리킨다.
- `&p -> num`은 `&(p -> num)`이다. `->`가 `&`보다 먼저 계산된다.
- `p -> name`은 배열이라서 `scanf`에 `&` 없이 넘긴다.
- `%7s`는 7칸에 오른쪽 정렬로 출력한다.

## 중첩 구조체와 멤버 메모리 해제
```c
typedef struct profile {
    int age;
    char * favorateColor[3];
    char name[20];
}profile_t;

typedef struct student {
    int num;
    double grade;
    profile_t profile;
}student_t;

typedef char str_t[20];

void initStudent(student_t * arr, size_t n) {

    str_t buf;

    for(int i = 0; i < n; i++) {
        student_t * sp = arr + i;
        profile_t * pp = &sp -> profile;

        scanf("%d %lf %d", &sp -> num, &sp -> grade,&pp -> age);
        for(int i = 0; i < 3; i++) {
            scanf("%s", buf);
            pp->favorateColor[i] = (char *) malloc(strlen(buf) + 1);
            if(pp == NULL) exit(1);
            strcpy(pp->favorateColor[i], buf);
        }
        scanf("%s", pp -> name);
    }

}

void freeMem3(void * p, size_t n) {

    student_t * s = (student_t *) p;

    student_t * sp;
    profile_t * pp;

    for(int i = 0; i < n; i++) {
        sp = s + i;
        pp = &(s + i) -> profile;
        for(int j = 0; j < 3; j++) {
            freeMem((void**) &pp->favorateColor[j]);
        }
    }
}
```
```c
freopen("student2.txt", "r", stdin);

const int N = 3;
student_t arr[N];

initStudent(arr, N);
printStudent(arr, N);

freeMem3(arr, N);
```
```
1 4.3 20 blue white green Tom
2 3.8 21 yellow pink red John
3 4.2 24 black gray white Jerry
```
- 구조체 안의 구조체는 `pp = &sp -> profile`처럼 포인터로 받아 두면 접근이 짧아진다.
- `favorateColor`는 칸마다 `malloc`하므로 학생 3명 × 색 3개, 총 9번 해제한다.
- `arr` 자체는 지역 배열이라 `free`하지 않는다. 힙에 할당한 멤버만 해제한다.
- `freeMem`이 주소를 받아 `NULL`로 바꿔서, 해제 후 9개 포인터가 모두 `0000000000000000`으로 출력된다.
- ⚠️ `if(pp == NULL)`은 `malloc` 결과를 확인하지 못한다. `if(pp->favorateColor[i] == NULL)`이어야 한다.
- 안쪽 `for`의 `i`가 바깥 `i`를 가린다. 동작은 하지만 `j`처럼 다른 이름을 쓰는 편이 안전하다.
