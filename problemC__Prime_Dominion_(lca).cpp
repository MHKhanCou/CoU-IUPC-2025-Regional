//https://codeforces.com/gym/106057/problem/C

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5;
int prime[N + 1];
int son = 0;

void sieve() {
    for (int i = 4; i <= N; i += 2) prime[i] = 1;
    for (int i = 3; i * i <= N; i += 2) {
        if (!prime[i]) {
            for (int j = i * i; j <= N; j += 2 * i) {
                prime[j] = 1;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    son += n;
    vector<int> v(n + 1);
    v[0] = 1;
    for (int i = 1; i <= n; i++) cin >> v[i];

    map<int, int> m;
    m[v[0]] = 0;
    int ans = -1;

    for (int i = 1; i <= n; i++) {
        map<int, int> nw;
        nw[v[i]] = i;
        for (auto &it : m) {
            int g = __gcd(it.first, v[i]);
            if (!nw.count(g)) nw[g] = i;
            nw[g] = min(nw[g], it.second);
        }
        m.swap(nw);

        for (auto &it : m) {
            if (it.first > 1 && !prime[it.first]) {
                ans = max(ans, i - it.second + 1);
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();
    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
