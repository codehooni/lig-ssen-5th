# Week 3 Day13 — 백트래킹 (해밀턴 순환 회로, N-Queen)

> 2026-11-06 학습 정리

Day12의 재귀 틀(매개변수 → 종료 조건 → 선택·표시·재귀·해제)을 실제 문제에 적용한다. 조건에 맞지 않는 길은 더 들어가지 않고 되돌아가는 것이 **백트래킹**이다.

## 해밀턴 순환 회로 — 모든 지점을 한 번씩 돌고 돌아오는 최소 비용
코드: [hamilton.c](hamilton/hamilton.c)

1번 지점에서 출발해 모든 지점을 한 번씩 방문하고 1번으로 돌아오는 최소 비용을 구한다. `MAP[a][b]`는 a → b 비용이고, 0이면 갈 수 없다.

```c
/*
1. Parameter: 현 위치, 재귀 깊이, 현재 위치까지 전체 비용
2. 종료: 모든 지점을 방문 했을 때 처음으로 돌아갈 수 있으면 현재 비용이 최솟값보다 작으면 최솟값을 갱신 후 리턴
3. 행동 선택:
    1. 방문 가능 여부 및 이전 방문 여부 확인
    2. 방문 비용을 현재 비용과 합쳐서 다음 지점 방문
    3. 방문 기록 해제
*/

int N;
int MAP[MAX_N][MAX_N];
int bitMask;
int minCost = 1500;

void dfs(int from, int cnt, int cost) {

    if(cost >= minCost) return;

    if(cnt > N - 1) {
        if(MAP[from][1] == 0) return;
        cost += MAP[from][1];

        if(cost < minCost) minCost = cost;
        return;
    }

    for(int to = 2; to <= N; to++) {
        if((bitMask >> to) & 1u || MAP[from][to] == 0) continue;

        bitMask |= (1 << to);
        dfs(to, cnt + 1, cost + MAP[from][to]);
        bitMask &= ~(1 << to);
    }
}

// main: dfs(1, 1, 0);
```
```
입력                 출력
3                    214
0 86 0
69 0 83
45 97 0

5                    30
0 14 4 10 20
14 0 7 8 7
4 5 0 7 16
11 7 9 0 2
18 7 17 4 0
```
- **매개변수**: 지금 위치 `from`, 지금까지 방문한 지점 수 `cnt`, 지금까지의 비용 `cost`.
- **종료**: `cnt`가 `N`이 되면 다 돈 것이다. 1번으로 돌아가는 길이 있으면 비용을 더해 최솟값을 갱신한다.
- **선택**: 방문하지 않았고 길이 있는 지점만 고른다. 비트마스크로 표시하고, 다녀온 뒤 지운다(Day12 `test10`과 같은 방식).
- 1번은 출발점이라 `to = 2`부터 고른다. 1번은 비트마스크에 표시하지 않고 마지막에만 돌아간다.
- **가지치기**: `cost >= minCost`면 이미 찾은 답보다 비싸니 더 볼 필요가 없다. 맨 앞에서 끊어서 탐색량을 크게 줄인다.
- 3개 예시: 1 → 2(86) → 3(83) → 1(45) = 214. 1 → 3은 길이 없어(0) 이 경로 하나뿐이다.
- `data.txt`에는 예시가 두 개 있지만 코드는 첫 번째만 읽는다.
- ⚠️ `minCost = 1500`은 문제의 최대 비용을 가정한 값이다. 비용이 더 커질 수 있으면 `INT_MAX`로 시작한다.

## N-Queen — 서로 공격하지 않게 퀸 N개 놓기
코드: [n-queen.c](n-queen/n-queen.c)

N×N 판에 퀸 N개를 서로 공격하지 못하게 놓는 방법의 수를 구한다. 퀸은 같은 행·열·대각선을 공격한다.

```c
/*
1. parameter: Queen 행번호
2. 종료: R > N, cnt++
3. 행동: Queen을 놓을 열 위치 선택, col/d_left/d_right 확인 후 선택,
        col/d_left/d_right arr 표시, 다음 행으로 이동, 돌아와서 col/d_left/d_right arr 해제
*/

int N;
int cnt;
int col[MAX_N];          // 같은 열에 Queen의 존재 여부[열번호]
int d_left[MAX_N * 2];   // 좌상향 대각선 d_left[N + 행 - 열]
int d_right[MAX_N * 2];  // 우상향 대각선 d_right[행 + 열]

void nqueen_DFS(int r) {
    if (r > N) { cnt++; return; }

    for(int c = 1; c <= N; c++) {
        if(col[c] == 0 && d_left[N + r - c] == 0 && d_right[r + c] == 0) {
            col[c] = 1; d_left[N + r - c] = 1; d_right[r + c] = 1;
            nqueen_DFS(r + 1);
            col[c] = 0; d_left[N + r - c] = 0; d_right[r + c] = 0;
        }
    }
}
```
```
N = 4  → 2
N = 8  → 92
N = 10 → 724
```
- **한 행에 퀸 하나**만 놓으므로 행은 재귀 깊이 `r`로 처리한다. 행 충돌은 확인할 필요가 없다.
- **열, 대각선 두 방향**은 배열로 표시해서 O(1)에 확인한다. 판 전체를 훑을 필요가 없다.
  - 같은 `↘` 대각선 위의 칸은 `행 - 열`이 같다. 음수가 될 수 있어서 `N`을 더해 `N + r - c`(1 ~ 2N-1)로 쓴다.
  - 같은 `↙` 대각선 위의 칸은 `행 + 열`이 같다(2 ~ 2N).
  - 그래서 대각선 배열은 `MAX_N * 2` 크기다.
- 놓을 때 세 곳에 표시하고, 다음 행을 다 본 뒤 세 곳 모두 지운다.
- 결과만 세면 되므로 종료 조건에서 `cnt++`만 한다. 실제 배치가 필요하면 그때 `arr`를 출력한다.
- ⚠️ `printData`는 안쪽 `for`에서 `j` 대신 `i++`를 증가시켜 무한 반복에 빠진다. 매개변수도 `int *arr[MAX_N]`(포인터 배열)이 아니라 `int (*arr)[MAX_N]`이어야 2차원 배열 `arr`를 받을 수 있다. 지금은 호출하지 않아서 결과에 영향은 없다.
