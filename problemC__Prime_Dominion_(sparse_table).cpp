//https://codeforces.com/gym/106057/problem/C

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
const int K = 25;

int arr[N];
ll LogN[N], table[N][K];
bitset<N> vis;
int n;

ll gcdll(ll a, ll b) { return b ? gcdll(b, a % b) : a; }

void PreLog() {
    LogN[1] = 0;
    for (int i = 2; i < N; i++) LogN[i] = 1 + LogN[i / 2];
}

void SpTable() {
    for (int i = 0; i <= n; i++) table[i][0] = arr[i];
    for (int j = 1; (1 << j) <= n + 1; j++) {
        for (int i = 0; i + (1 << j) - 1 <= n; i++) {
            table[i][j] = gcdll(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }
}

ll RGcdQ(ll l, ll r) {
    ll j = LogN[r - l + 1];
    return gcdll(table[l][j], table[r - (1 << j) + 1][j]);
}

void sieve() {
    vis[0] = vis[1] = true;
    for (int i = 4; i < N; i += 2) vis[i] = true;
    for (int i = 3; i * i < N; i += 2) {
        if (!vis[i]) {
            for (int j = i * i; j < N; j += 2 * i) vis[j] = true;
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    arr[n] = 1;

    SpTable();
    int ans = -1;

    for (int i = 1; i <= n; i++) {
        int lo = i, hi = n + 2, mid;
        while (lo + 1 < hi) {
            mid = (lo + hi) >> 1;
            if (RGcdQ(i - 1, mid - 1) != 1) lo = mid;
            else hi = mid;
        }
        lo = min(lo, n + 1);
        int g = RGcdQ(i - 1, lo - 1);
        if (!vis[g]) ans = max(ans, lo - i + 1);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    PreLog();
    sieve();

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
