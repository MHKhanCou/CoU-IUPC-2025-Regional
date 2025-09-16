//https://codeforces.com/gym/106057/problem/I

// starting with the name of almighty ALLAH
//  Practice is the only shortcut to improve
#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define rj ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'
#define F first
#define S second
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll my_rand(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<ll> h(26);
    for (int i = 0; i < 26; i++) h[i] = my_rand(1, 1e18);

    vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] ^ h[s[i - 1] - 'a'];
    }

    vector<ll> masks = {0};
    for (int i = 0; i < 26; i++) masks.push_back(h[i]);

    map<ll, pair<ll, ll>> m;
    vector<pair<ll, ll>> dp(n + 1);
    dp[n] = {1, 0};
    m[pre[n]] = {1, 0};

    for (int i = n - 1; i >= 0; i--) {
        for (auto &it : masks) {
            ll nxt = pre[i] ^ it;
            if (m.find(nxt) != m.end()) {
                dp[i].F += m[nxt].F;
                dp[i].S += (m[nxt].S + m[nxt].F) % MOD;
                dp[i].F %= MOD;
                dp[i].S %= MOD;
            }
        }
        m[pre[i]].F += dp[i].F;
        m[pre[i]].S += dp[i].S;
        m[pre[i]].F %= MOD;
        m[pre[i]].S %= MOD;
    }

    cout << dp[0].S << nl;
}

int main() {
    rj
    int t = 1;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        solve();
    }
    return 0;
}
