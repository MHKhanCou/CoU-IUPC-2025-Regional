//https://codeforces.com/gym/106057/problem/D

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;
    ll res = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        ll mask = 0;
        for (int j = 0; j < m; j++) {
            ll x;
            cin >> x;
            mask |= x;
        }
        res &= mask;
    }
    cout << (res ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
