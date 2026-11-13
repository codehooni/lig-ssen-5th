# Week 3 Day11 — 알고리즘 문제 풀이 (BFS)

> 2026-11-04 학습 정리

알고리즘 문제 풀이: 토마토, 등산가(등산로 찾기)

코드는 [algorithm/week03](../../../algorithm/week03/README.md)에 있다. BFS 기본 절차와 문제 유형 정리도 그 README에 있다.

## 토마토 — 시작점이 여러 개인 BFS
코드: [04_tomato.c](../../../algorithm/week03/04_tomato/04_tomato.c)

익은 토마토(1)는 하루가 지나면 상하좌우의 안 익은 토마토(0)를 익힌다. `-1`은 빈 칸이다. 모두 익는 최소 일수를 구하고, 다 익을 수 없으면 `-1`, 처음부터 다 익어 있으면 `0`을 출력한다.

```c
void initData() {
    int tomato;

    scanf("%d %d", &C, &R);

    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            scanf("%d", &tomato);
            box[r][c] = tomato;
            if(tomato == 0) unripe++;
            if(tomato == 1) q.q[q.r++] = (node) {r, c};
        }
    }
}

int bfs() {
    if(unripe == 0) return 0;

    ripe = q.r;

    node curr;

    while(q.r != q.f) {
        curr  = q.q[q.f++];
        for(int i = 0; i < 4; i++) {
            node next = {curr.r + D[i][0], curr.c + D[i][1]};

            if(1 <= next.r && next.r <= R &&
                1 <= next.c && next.c <= C &&
                box[next.r][next.c] == 0
            ) {
                box[next.r][next.c] = box[curr.r][curr.c] + 1;
                q.q[q.r++] = next;
            }
        }
    }

    if(unripe == q.r - ripe) return box[curr.r][curr.c] - 1;

    return -1;
}
```
```
입력
6 4
1 -1 0 0 0 0
0 -1 0 0 0 0
0 0 0 0 -1 0
0 0 0 0 -1 1

출력
6
```
- **시작점이 여러 개**다. 입력을 받으면서 익은 토마토를 모두 큐에 넣고 BFS를 한 번만 돌린다. 여러 곳에서 동시에 퍼져 나가는 모양이 된다.
- **방문 표시와 날짜를 한 배열에 둔다.** `box`에 "익은 날 + 1"을 적는다. 0이 아니면 이미 방문한 칸이라 따로 `visited` 배열이 필요 없다.
- **답은 마지막으로 꺼낸 칸의 값이다.** BFS는 가까운 순서로 꺼내므로 마지막 `curr`이 가장 늦게 익은 토마토다. 시작값이 1이라 1을 뺀다.
- **다 익었는지 확인한다.** 새로 큐에 들어간 개수 `q.r - ripe`가 처음 안 익은 개수 `unripe`와 같으면 모두 익은 것이다.
- 큐 크기는 모든 칸이 한 번씩 들어가는 경우인 `MAX_N * MAX_N`이다. 큰 배열이라 전역으로 둔다(지역 변수면 스택이 넘친다).
- `scanf("%d %d", &C, &R)`처럼 입력이 가로(열), 세로(행) 순서라는 점을 주의한다.

## 등산로 찾기 — 비용이 다른 최단 경로
코드: [05_hiking.c](../../../algorithm/week03/05_hiking/05_hiking.c)

산 바깥(높이 0)에서 출발해 정상 `(gR, gC)`까지 가는 최소 힘을 구한다. 오르막은 높이 차의 제곱, 내리막은 높이 차, 평지는 0이 든다.

```c
int bfs() {
    MAP[gR][gC][1] = 0;
    q.q[q.r++] = (node) {gR, gC};
    IN_QUEUE[gR][gC] = 1;

    while(q.f != q.r) {
        node curr = q.q[q.f];
        q.f = (q.f + 1) % MAX_Q;
        IN_QUEUE[curr.r][curr.c] = 0;

        for(int i = 0; i < 4; i++) {
            node next = {curr.r + D[i][0], curr.c + D[i][1]};

            if(0 <= next.r && next.r <= N + 1 &&
                0 <= next.c && next.c <= N + 1
            ) {
                if(next.r == gR && next.c == gC) continue;

                int cost = getCost(next, curr) + MAP[curr.r][curr.c][1];

                if(cost < MAP[next.r][next.c][1]) {
                    MAP[next.r][next.c][1] = cost;

                    if(!IN_QUEUE[next.r][next.c]) {
                        q.q[q.r] = next;
                        q.r = (q.r + 1) % MAX_Q;
                        IN_QUEUE[next.r][next.c] = 1;
                    }
                }
            }
        }
    }

    return MAP[0][0][1];
}

int getCost(node from, node to) {
    int fromV = MAP[from.r][from.c][0], toV = MAP[to.r][to.c][0];

    if(fromV > toV) return fromV - toV;
    if(fromV < toV) return (toV - fromV) * (toV - fromV);
    return 0;
}
```
```
입력
5
3 3
4 4 4 4 4
4 2 2 2 4
4 2 5 2 4
4 2 2 2 4
4 4 4 4 4

출력
27
```
- **비용이 칸마다 달라서 "처음 방문 = 최단"이 아니다.** 그래서 방문 표시 대신 지금까지의 최소 비용 `MAP[r][c][1]`을 두고, 더 싼 비용을 찾으면 갱신하고 다시 큐에 넣는다.
- `MAP[r][c][0]`은 높이, `MAP[r][c][1]`은 그 칸까지의 최소 비용이다. 처음에는 `INF`로 채운다.
- **정상에서 거꾸로 출발한다.** 시작점이 바깥 테두리 전체라서, 도착점(정상)에서 한 번만 BFS를 돌리는 편이 쉽다. 대신 비용은 원래 방향(`next` → `curr`)으로 계산해야 해서 `getCost(next, curr)`로 인자를 뒤집었다.
- **바깥을 한 겹 둘러싼다.** 지도를 `0 ~ N+1`로 쓰고 테두리는 높이 0이다. 바깥끼리는 비용이 0이라 모든 테두리 칸의 값이 같아지고, `MAP[0][0][1]`을 답으로 쓸 수 있다.
- `IN_QUEUE`로 이미 큐에 있는 칸을 다시 넣지 않는다. 같은 칸이 여러 번 들어갈 수 있어서 큐를 `% MAX_Q`로 도는 원형 큐로 만들었다.
- 예시: 바깥(0) → 4는 오르막 16, 4 → 2는 내리막 2, 2 → 5는 오르막 9로 합이 27이다.
