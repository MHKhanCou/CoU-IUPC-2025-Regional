//https://codeforces.com/gym/106057/problem/H

#include <bits/stdc++.h>
#define ll long long
#define nl '\n'
#define rj ios::sync_with_stdio(false); cin.tie(0);
using namespace std;

bool ok(ll s, ll b, ll lm) {
    ll n = s + b - 1;
    ll k = s;
    k = min(k, n - k);
    __int128 an = 1;
    for (ll i = 1; i <= k; i++) {
        an *= (n - i + 1);
        an /= i;

        if (an >= lm) return true;
    }
    return an >= lm;
}

void solve() {
    ll k, m;
    cin >> k >> m;
    if (m == 1) { cout << 0 << nl; return; }
    if (k == 1) { cout << -1 << nl; return; }

    ll lo = 0, hi = 1e18;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (ok(mid, k, m)) hi = mid;
        else lo = mid + 1;
    }
    cout << hi << nl;
}

int main() {
    rj
    int t = 1;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        cout << "Case " << cs << ": ";
        solve();
    }
    return 0;
}
