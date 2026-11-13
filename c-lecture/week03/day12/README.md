# Week 3 Day12 — 재귀

> 2026-11-05 학습 정리

코드: [recurtion.c](recurtion/recurtion.c), [lib.c](recurtion/lib.c)

## 재귀 호출 전후의 출력 순서
```c
void test01(int n) {
    if(n > 5) return ;
    test01(n + 1);
    printf("%d ", n);
}

void test02(int n) {
    if(n > 5) return ;
    printf("%d ", n);
    test02(n + 1);
    printf("%d ", n);
}

void test03(int n) {
    if(n > 5) return ;

    if(n & 1) printf("%d ", n);
    test03(n + 1);
    if(!(n & 1)) printf("%d ", n);
}

void test04(int n) {
    if(n > 5) return ;
    for(int i = 1; i <= n; i++) printf("%d ", i);
    printf("\n");
    test04(n + 1);
}
```
```
test01(1): 5 4 3 2 1
test02(1): 1 2 3 4 5 5 4 3 2 1
test03(1): 1 3 5 4 2
test04(1):
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
```
- 재귀 함수는 **종료 조건**을 맨 앞에 둔다. `n > 5`면 더 들어가지 않고 돌아간다.
- **호출 전**에 한 일은 들어가는 순서(1 → 5)로, **호출 후**에 한 일은 돌아오는 순서(5 → 1)로 실행된다.
- `test01`은 다 들어간 뒤 돌아오면서 출력해서 거꾸로 나온다.
- `test02`는 들어갈 때 한 번, 나올 때 한 번 출력한다.
- `test03`은 홀수는 들어갈 때, 짝수는 나올 때 출력한다. `n & 1`은 홀수 판별이다.
- `test04`처럼 호출이 함수의 맨 마지막에 있으면(꼬리 재귀) 반복문으로 바꾸기 쉽다.

## 메모이제이션으로 팩토리얼
```c
int factorial(int n) {
    static int sol[100] = { 0 };

    if(n == 1) return 1;

    if(sol[n] != 0) return sol[n];

    sol[n] = n * factorial(n - 1);

    return sol[n];
}
```
```
factorial(5) = 120
```
- 한 번 계산한 값을 `sol[n]`에 저장해 두고, 다음에 같은 `n`이 오면 바로 돌려준다.
- `static` 지역 배열은 함수가 끝나도 값이 남는다. 다른 함수에서는 보이지 않아 전역 `sol`과 이름이 겹쳐도 괜찮다.
- 0이면 "아직 계산 안 함"으로 본다. 결과가 0이 될 수 없는 문제에서만 쓸 수 있는 방법이다.
- ⚠️ `int`는 `13!`부터 넘친다. 큰 값은 `long long`을 쓴다.

## 경우의 수 만들기 (백트래킹 기본형)
세 함수 모두 같은 틀이다.
1. **매개변수 `L`**: 지금 채울 자리(1번째, 2번째, ...)
2. **종료**: `L > N`이면 다 채운 것이니 출력하고 돌아간다.
3. **선택**: `for`로 이 자리에 넣을 값을 하나씩 골라 `sol[L]`에 넣고 다음 자리로 간다.

```c
int N = 3;
int sol[100];

void printList(int * arr, int n) {
    for(int i = 1; i <= n; i++) {
        printf("%d ", sol[i]);
    }
    printf("\n");
}
```

### 중복 순열 — 같은 값을 여러 번 써도 됨
```c
void test07(int L) {
    if(L > N) {
        printList(sol, N);
        return;
    }

    for(int i = 0; i < 3; i++) {
        sol[L] = i;
        test07(L + 1);
    }
}
```
```
0 0 0
0 0 1
0 0 2
0 1 0
...
2 2 2      (총 3³ = 27개)
```
- 각 자리마다 0, 1, 2를 모두 넣어 본다. `N`중 `for`문을 재귀로 만든 것이다.
- 반복문으로는 자리 수만큼 `for`를 써야 하지만, 재귀는 `N`만 바꾸면 된다.

### 조합 — 순서 없이 뽑기 (nCr)
```c
void test08(int L, int start) {
    if(L > N) {
        printList(sol, N);
        return;
    }

    for(int i = start; i <= 6; i++) {
        sol[L] = i;
        test08(L + 1, i + 1);
    }
}
```
```
1 2 3
1 2 4
1 2 5
...
4 5 6      (총 6C3 = 20개)
```
- 1~6 중 3개를 고른다. `start`는 "이 자리에 넣을 수 있는 가장 작은 값"이다.
- 다음 자리는 `i + 1`부터 고르므로 항상 오름차순이 된다. 그래서 `1 2 3`과 `3 2 1` 같은 중복이 생기지 않는다.

### 순열 — 같은 값을 한 번만 쓰기
```c
void test09(void) {
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            for(int k = 1; k <= 3; k++)
                if(i != j && j != k && k != i)
                    printf("%d %d %d\n", i, j, k);
}
```
```c
int bitMask = 0;

void test10(int L) {
    if(L > N) {
        printList(sol, N);
        return;
    }

    for(int i = 1; i <= N; i++) {
        if((bitMask >> i) & 1u) continue;

        sol[L] = i;
        bitMask |= (1 << i);
        test10(L + 1);
        bitMask &= ~(1 << i);
    }
}
```
```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1      (총 3! = 6개)
```
- `test09`는 3중 `for`로 만든 순열이다. 개수가 바뀌면 코드를 고쳐야 한다.
- `test10`은 재귀로 만든 순열이다. 이미 쓴 숫자를 **비트마스크**로 기록한다.
  - `(bitMask >> i) & 1u`: `i`번 비트가 1이면 이미 쓴 숫자라 건너뛴다.
  - `bitMask |= (1 << i)`: 쓰기 전에 표시한다.
  - `bitMask &= ~(1 << i)`: 돌아온 뒤 표시를 지운다(**원상 복구**). 그래야 다른 경우에서 다시 쓸 수 있다.
- `int` 비트마스크는 숫자 31개까지 표시할 수 있다. 더 많으면 `visited[]` 배열을 쓴다.

## 분할 컴파일과 extern
```c
// recurtion.c
extern int N;
extern int sol[10];
extern int bitMask;
void printList(int * arr, int n);
```
```c
// lib.c
int N = 3;
int sol[100];
int bitMask = 0;
```
- 전역 변수는 `lib.c`에 정의하고, `recurtion.c`에서는 `extern`으로 "다른 파일에 있다"고 선언만 한다.
- 빌드: `gcc recurtion.c lib.c -o recurtion`
- ⚠️ `extern int sol[10]`과 정의 `int sol[100]`의 크기가 다르다. 링커는 이름만 맞추기 때문에 오류가 안 나지만, 선언과 정의는 같은 타입으로 맞춘다. 헤더 파일에 `extern` 선언을 모아 두면 이런 실수를 막을 수 있다.
- `printList`가 매개변수 `arr` 대신 전역 `sol`을 출력한다. 지금은 같은 배열을 넘겨서 결과가 같지만 `arr[i]`로 쓰는 것이 맞다.
