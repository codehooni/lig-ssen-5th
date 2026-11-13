#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
0. 정점의 모양: C, R
1. 시작점: 모든 익은 토마토
2. 인접점: 우상좌하 ((0, 1), (-1, 0), (0, -1), (1, 0))
3. 끝점: 모든 노드 탐색
4. 방문 표시: 1
5. bfs 1번 수행
6. 큐의 크기: 모든 정점의 수 [MAX_N * MAX_N]
7. 출력 표시: 처음에 안 익은 토마토 받기 
                if 안 익은 토마토 == 0 : 0
                else 큐 다 돌고 안익은 토마토가 있으면 -1 else 최소 일수 출력
*/

#define MAX_N (1000 + 2)

typedef struct {
    int r;
    int c;
}node;

typedef struct {
    node q[MAX_N * MAX_N];
    int f;
    int r;
}queue;

int R, C;
int box[MAX_N][MAX_N];
int unripe = 0, ripe;
int D[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
queue q = { {0, 0}, 0, 0 };

void initData();
int bfs();
void printData();

int main(void) {

    freopen("data.txt", "r", stdin);

    initData();

    printf("%d\n", bfs());

    return 0;
}

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

    // 토마토 익히기
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

void printData() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            printf("%d ", box[r][c]);
        }
        printf("\n");
    }
}