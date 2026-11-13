#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 0. 정점의 모양: 좌표(y, x)
// 1. 시작점: sY, sX
// 2. 인접점: 우상좌하 ((0, 1), (-1, 0), (0, -1), (1, 0))
// 3. 끝점: 없음
// 4. 방문표시: 경로에 비용 표시
// 5. BFS 1회 수행
// 6. 큐의 크기: 모든 정점의 수 (MAX_L * MAX_L)

#define MAX_L (100 + 2) // memset으로 후에 인접노드 반복문을 돌 때 비교를 많이 줄일 수 있다.

int R, C;
int sR, sC;
int MAP[MAX_L][MAX_L];
int D[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

typedef struct {
    int r;
    int c;
}node;

typedef struct{
    node q[MAX_L * MAX_L];
    int f;
    int r;
}queue;

void initData();
int bfs();
int countSurvivors();
void printData();

int main(void) {

    freopen("data.txt", "r", stdin);

    initData();
    printf("%d\n", bfs());
    printf("%d\n", countSurvivors());
    // printData();

    return 0;
}

void initData() {
    scanf("%d %d", &C, &R);

    for(int r = 1; r <= R; r++) {
        char str[C + 2];
        scanf("%s", str + 1);

        for(int c = 1; c <= C; c++) {
            MAP[r][c] = str[c] - '0';
        }
    }

    scanf("%d %d", &sC, &sR);
}

int bfs() {
    queue q = { { 0 }, 0, 0 };

    MAP[sR][sC]+=2;
    q.q[q.r++] = (node) {sR, sC};

    node curr;

    while(q.r != q.f) {
        curr = q.q[q.f++];

        for(int i = 0; i < 4; i++) {
            node next = (node) {curr.r + D[i][0], curr.c + D[i][1]};

            if(1 <= next.r && next.r <= R &&
                1 <= next.c && next.c <= C &&
                MAP[next.r][next.c] == 1    
            ) {
                MAP[next.r][next.c] = MAP[curr.r][curr.c] + 1;
                q.q[q.r++] = next;
            }
        }
    }

    return MAP[curr.r][curr.c];
}

int countSurvivors() {
    int answer = 0;
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            if(MAP[r][c] == 1) answer++;
        }
    }
    return answer;
}

void printData() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            printf("%d ", MAP[r][c]);
        }
        printf("\n");
    }
}