//https://codeforces.com/gym/106057/problem/B

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1000000007;

struct PT {
    ll x, y;
    PT() : x(0), y(0) {}
    PT(ll _x, ll _y) : x(_x), y(_y) {}
};
istream &operator>>(istream &in, PT &p) { return in >> p.x >> p.y; }

inline ll cross(const PT &a, const PT &b) { return a.x * b.y - a.y * b.x; }

ll area2(const vector<PT> &p) {
    ll ans = 0;
    int n = (int)p.size();
    for (int i = 0; i < n; ++i) ans += cross(p[i], p[(i + 1) % n]);
    ans %= MOD;
    if (ans < 0) ans += MOD; // keep non-negative
    return ans;
}

ll binPow(ll a, ll b) {
    a %= MOD;
    if (a < 0) a += MOD;
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<ll> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];

    vector<ll> ar2(n);
    for (int i = 0; i < n; ++i) {
        int v; cin >> v;
        vector<PT> p(v);
        for (int j = 0; j < v; ++j) cin >> p[j];
        ar2[i] = area2(p);
    }

    vector<array<ll,2>> val(n);
    ll mxnum2 = 0, mxden2 = 1;
    for (int i = 0; i < n; ++i) {
        ll sum2 = 0;
        for (int j = 0; j <= i; ++j) {
            ll cur = ar2[j];
            if (j) cur -= ar2[j - 1];
            sum2 += cur * s[j];
        }
        val[i] = {sum2, ar2[i]};
        if (mxnum2 * ar2[i] <= sum2 * mxden2) {
            mxnum2 = sum2;
            mxden2 = ar2[i];
        }
    }

    ll ans = 0;
    ans = (ans + (mxnum2 % MOD) * binPow(mxden2, MOD - 2) % MOD * (k % MOD)) % MOD;
    ans = (ans + (val[n - 1][0] % MOD) * binPow(val[n - 1][1], MOD - 2) % MOD * ((m - k) % MOD)) % MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    for (int cs = 0; cs < tc; ++cs) solve();
    return 0;
}
