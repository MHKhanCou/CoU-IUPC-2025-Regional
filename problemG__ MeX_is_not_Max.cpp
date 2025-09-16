// https://codeforces.com/gym/106057/problem/G

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        vector<bool> present(N + 1, false);

        for (int i = 0; i < N; ++i) {
            ll x;
            cin >> x;
            if (0 <= x && x <= N) present[x] = true;
        }

        int mex = 0;
        while (mex <= N && present[mex]) ++mex;
        cout << mex << '\n';
    }

    return 0;
}
