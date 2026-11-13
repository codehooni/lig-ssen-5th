#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define INF INT_MAX
#define MAX_N (100 + 2)
#define MAX_Q (MAX_N * MAX_N + 1)

typedef struct {
    int r;
    int c;
}node;

typedef struct {
    node q[MAX_Q];
    int f;
    int r;
}queue;

int N;
int gR, gC;
int MAP[MAX_N][MAX_N][2];
queue q;
int IN_QUEUE[MAX_N][MAX_N];
int D[4][2] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };

void initData();
int bfs();
int getCost(node, node);
void printData();

int main(void) {

    freopen("data.txt", "r", stdin);

    initData();

    printf("%d\n", bfs());

    return 0;
}

void initData() {
    scanf("%d", &N);
    scanf("%d %d", &gR, &gC);

    for(int i = 0; i <= N + 1; i++) {
        for(int j = 0; j <= N + 1; j++) {
            MAP[i][j][1] = INF;
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            scanf("%d", &MAP[i][j][0]);
        }
    }
}

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

void printData() {
    printf("-----------\n");
    for(int i = 0; i <= N + 1; i++) {
        for(int j = 0; j <= N + 1; j++) {
            printf("%d ", MAP[i][j][1]);
        }
        printf("\n");
    }
}