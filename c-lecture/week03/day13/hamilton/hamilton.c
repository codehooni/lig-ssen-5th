#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*
1. Parameter: 현 위치, 재귀 깊이, 현재 위치까지 전체 비용
2. 종료: 모든 지점을 방문 했을 때 처음으로 돌아갈 수 있으면 현재 비용이 최솟값보다 작으면 최솟값을 갱신 후 리턴
3. 행동 선택: 
    1. 방문 가능 여부 및 이전 방문 여부 확인
    2. 방문 비용을 현재 비용과 합쳐서 다음 지점 방문
    3. 방문 기록 해제
*/

#define MAX_N (13 + 2)

int N;
int MAP[MAX_N][MAX_N];
int bitMask;
int path[MAX_N];
int minCost = 1500;

void initData();
void dfs(int, int, int);
void printData();

int main(void) {

    freopen("data.txt", "r", stdin);

    initData();

    dfs(1, 1, 0);

    printf("%d", minCost);

    // printData();

    return 0;
}

void initData() {
    scanf("%d", &N);

    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++)
            scanf("%d", &MAP[r][c]);
}

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

void printData() {
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++)
            printf("%d ", MAP[r][c]);
        printf("\n");
    } 
}