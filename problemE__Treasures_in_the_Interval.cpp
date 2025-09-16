//https://codeforces.com/gym/106057/problem/E

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q, M;
    cin >> N >> Q >> M;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<ll> diff(N + 1, 0);
    for (int i = 0; i < Q; ++i) {
        int L, R;
        ll d;
        cin >> L >> R >> d;
        diff[L - 1] += d;
        if (R < N) diff[R] -= d;
    }

    ll add = 0;
    for (int i = 0; i < N; ++i) {
        add += diff[i];
        A[i] += add;
    }

    sort(A.rbegin(), A.rend());

    for (int i = 0; i < M; ++i) {
        int K;
        cin >> K;
        cout << A[K - 1] << '\n';
    }

    return 0;
}
