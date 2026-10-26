#include <iostream>
#include <vector>
using namespace std;

#if 1

int main(void) {

    int N, d, k, c;
    cin >> N >> d >> k >> c;

    vector<int> arr(N);
    for(int i = 0; i < N; i++) cin >> arr[i];

    vector<int> cnt(d + 1, 0);

    for(int i = 0; i < k; i++) cnt[arr[i]]++;
    
    int kinds = 0;
    for(int i = 1; i < d + 1; i++) if(cnt[i] > 0) kinds++;
    int answer = kinds + (cnt[c] == 0) ? 1 : 0;
    
    for(int i = 1; i < N; i++) {
        int out = arr[i - 1];
        kinds -= (cnt[out] == 1) ? 1 : 0;
        cnt[out]--;

        int in = arr[(i + k - 1) % N];
        kinds += (cnt[in] == 0) ? 1 : 0;
        cnt[arr[in]]++;

        answer = max(answer, (cnt[c] == 0) ? kinds + 1 : kinds);
    }    
    
    cout << answer << endl;

    return 0;
}

#endif