/*

1. 아이디어
- 가로, 세로 대각선 확인

2. 시간복잡도
- O(N^3) < 125

3. 자료구조
- board[5][5] : int
- poses[25]: node

*/

#include <stdio.h>

#define N 5

typedef struct {
    int r;
    int c;
}pos;

pos p[N * N + 1];
int row[N + 1];
int col[N + 1];
int dLeft;
int dRight;
int nums[N * N + 1];
int cnt;

void initData();
int bingo();
int check(int);

int main() {
    
    freopen("datat.txt", "r", stdin);

    initData();

    printf("%d", bingo());

}

void initData() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            int n;
            scanf("%d", &n);
            p[n].r = i;
            p[n].c = j;
        }
    }

    for(int i = 1; i <= N * N; i++) {
        scanf("%d", &nums[i]);
    }
}

int bingo() {
    for(int i = 1; i <= N * N; i++) {
        check(nums[i]);
        if(cnt >= 3) return i;
    }
    return 0;
}

int check(int n) {
    int pr = p[n].r;
    int pc = p[n].c;

    if(++row[pr] == 5) cnt++;
    if(++col[pc] == 5) cnt++;
    if(pr + pc == 6) if(++dRight == 5) cnt++;
    if(pr - pc == 0) if(++dLeft == 5) cnt++;
}