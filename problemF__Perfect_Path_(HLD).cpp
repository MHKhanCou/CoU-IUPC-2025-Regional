//https://codeforces.com/gym/106057/problem/F
// Author: Abdullah500 (https://codeforces.com/profile/Abdullah500)

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5 + 1;
const int LG = 17;

int spf[N], primes[N], psz;
int xr[N];
int a[N], mp[N], z[N], neg[N];
int par[N][LG + 1], dep[N];
vector<int> g[N];

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void sieve() {
    for (int i = 2; i < N; i++) {
        if (!spf[i]) spf[i] = i, primes[psz++] = i;
        for (int j = 0, gun = i * primes[0]; j < psz && gun < N && primes[j] <= spf[i]; j++, gun = i * primes[j]) {
            spf[gun] = primes[j];
        }
    }
}

vector<int> factorize(int n) {
    vector<int> p;
    while (n > 1) {
        int k = spf[n], cnt = 0;
        while (n % k == 0) n /= k, cnt++;
        if (cnt & 1) p.push_back(k);
    }
    return p;
}

void dfs(int u, int p = 0) {
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    neg[u] = neg[p] + (a[u] < 0);
    z[u] = z[p] + (a[u] == 0);

    for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];

    auto f = factorize(abs(a[u]));
    mp[u] = mp[p];
    for (auto &div : f) mp[u] ^= xr[div];

    for (auto &v : g[u]) if (v != p) dfs(v, u);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    sieve();
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= 200000; i++) xr[i] = rng();
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        int lc = lca(u, v);
        int xrrr = mp[u] ^ mp[v] ^ mp[lc] ^ mp[par[lc][0]];
        int ng = neg[u] + neg[v] - 2 * neg[lc] + (a[lc] < 0);
        int zero = z[u] + z[v] - 2 * z[lc] + (a[lc] == 0);

        if ((xrrr == 0 && ng % 2 == 0) || zero) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
