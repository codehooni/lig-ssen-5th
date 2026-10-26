'''
1. 아이디어

2. 시간복잡도
- O(N) 

3. 자료구조
'''

import sys
input = sys.stdin.readline

N, d, k, c = map(int, input().split())

arr = []
for _ in range(N):
    arr.append(int(input()))

cnt = [0] * (d + 1)

for i in range(k):
    cnt[arr[i]] += 1

kinds = sum(1 for x in cnt if x > 0)
answer = kinds + 1 if cnt[c] == 0 else kinds

for i in range(1, N):
    kinds -= 1 if cnt[arr[i - 1]] == 1 else 0
    cnt[arr[i - 1]] -= 1
    kinds += 1 if cnt[arr[(i + k - 1) % N]] == 0 else 0
    cnt[arr[(i + k - 1) % N]] += 1

    answer = max(answer, kinds + 1 if cnt[c] == 0 else kinds)

print(answer)