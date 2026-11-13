#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
1. parameter: Queen 행번호
2. 종료: R > N, cnt++
3. 행동: Queen을 놓을 열 위치 선택, col/d_left/d_right 확인 후 선택, 
        col/d_left/d_right arr 표시, 다음 행으로 이동, 돌아와서 col/d_left/d_right arr 해제
*/

#define MAX_N (13 + 2)

int N;
int cnt; // 결과 저장용
int col[MAX_N]; // 같은 열에 Queen의 존재 여부[열번호]
int d_left[MAX_N * 2]; // 좌상향 대각선에 Queen의 존재 여부 d_left[N + 행 - 열]
int d_right[MAX_N * 2]; // 우상향 대각선에 Queen의 존재 여부 d_right[행 + 열]
int arr[MAX_N][MAX_N]; // NQueen 판

void nqueen_DFS(int);
void printData(int *arr[MAX_N], int n);

int main(void) {

    scanf("%d", &N);

    cnt = 0;

    nqueen_DFS(1);

    printf("%d\n", cnt);

    return 0;
}

void nqueen_DFS(int r) {
    if (r > N) { cnt++; return; }

    for(int c = 1; c <= N; c++) {
        if(col[c] == 0 && d_left[N + r - c] == 0 && d_right[r + c] == 0) {
            col[c] = 1; d_left[N + r - c] = 1; d_right[r + c] = 1; arr[r][c] = 1;
            nqueen_DFS(r + 1);
            col[c] = 0; d_left[N + r - c] = 0; d_right[r + c] = 0; arr[r][c] = 0;
        }
    }
}


void printData(int *arr[MAX_N], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; i++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}