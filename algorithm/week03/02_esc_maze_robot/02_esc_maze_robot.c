#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 0. 정점의 모양: 1개 정수/문자, 좌표(2, 3차원),...
// 1. 시작점: sR, sC
// 2. 인접점: 상하좌우(-1, 0), (1, 0), (0, 1), (0, -1)
// 3.  방문표시 0:

#define MAX_N (100+2)

int R, C;
int sR, sC, eR, eC;
int maze[MAX_N][MAX_N];
int d[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

typedef struct {
    int r;
    int c;
}node;

typedef struct{
    node q[MAX_N * MAX_N];
    int f;
    int r;
}queue;

void initData();
int bfs(node);
void printMaze(int (*)[MAX_N]);

int main(void) {

    // freopen("02_esc.txt", "r", stdin);

    initData();
    printf("%d\n", bfs((node){sR, sC}));
    // printMaze(maze);

    return 0;
}

void initData() {
    scanf("%d %d", &C, &R);
    scanf("%d %d %d %d", &sC, &sR, &eC, &eR);

    char str[C + 2];
    for(int r = 1; r <= R; r++) {
        scanf("%s", str + 1);
        for(int c = 1; c <= C; c++) {
            maze[r][c] = str[c] - '0';  
        }
    }
}

int bfs(node n) {
    queue q = { { 0 }, 0, 0 };
    
    maze[n.r][n.c] = 1;
    q.q[q.r++] = n;
    
    while(q.f != q.r) {
        node curr = q.q[q.f++];

        if(curr.r == eR && curr.c == eC) 
            return maze[curr.r][curr.c] - 1;
        
        for(int i = 0; i < 4; i++) {
            node next = {curr.r + d[i][0], curr.c + d[i][1]};

            if(1 <= next.r && next.r <= R && 
                1 <= next.c && next.c <= C &&
                !maze[next.r][next.c]
            ) {
                maze[next.r][next.c] = maze[curr.r][curr.c] + 1;
                q.q[q.r++] = next;
            }
        }
    }

    return -1;
}

void printMaze(int (*maze)[MAX_N]) {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            printf("%d ", maze[r][c]);
        }
        printf("\n");
    }
}