//https://codeforces.com/gym/106057/problem/J

// starting with the name of almighty ALLAH
// Practice is the only shortcut to improve
#include <bits/stdc++.h>
#define ll long long
#define F first
#define S second
#define nl '\n'
#define rj ios::sync_with_stdio(false); cin.tie(0);
using namespace std;

const int N = 5e4 + 1, A = 5e4 + 1;
vector<int> uniquePrimes[N];
int v[N];
vector<int> adj[N];

vector<int> getDiv(const vector<int> &x) {
    vector<int> ans;
    int sz = x.size();
    for (int mask = 0; mask < (1 << sz); mask++) {
        ll num = 1;
        for (int j = 0; j < sz; j++) {
            if (mask & (1 << j)) num *= x[j];
        }
        ans.push_back(num);
    }
    return ans;
}

int par[N][16], lvl[N];
int root[N];

namespace PST {
    const int M = 64 * N * 17;
    ll st[M];
    int L[M], R[M], idx = 1;

    int copy(int u) {
        int uu = idx++;
        L[uu] = L[u]; R[uu] = R[u]; st[uu] = st[u];
        return uu;
    }

    int update(int i, int x, int u, int s = 0, int e = A - 1) {
        u = copy(u);
        if (s == e) { st[u] += x; return u; }
        int m = (s + e) >> 1;
        if (i <= m) L[u] = update(i, x, L[u], s, m);
        else R[u] = update(i, x, R[u], m + 1, e);
        st[u] = st[L[u]] + st[R[u]];
        return u;
    }

    ll query(int l, int r, int u, int s = 0, int e = A - 1) {
        if (e < l || r < s) return 0;
        if (l <= s && e <= r) return st[u];
        int m = (s + e) >> 1;
        return query(l, r, L[u], s, m) + query(l, r, R[u], m + 1, e);
    }
}

void pre() {
    for (int i = 2; i < N; i++) {
        if (uniquePrimes[i].empty()) {
            for (int j = i; j < N; j += i) uniquePrimes[j].push_back(i);
        }
    }
}

void dfs(int n = 1, int p = 0) {
    vector<int> dv = getDiv(uniquePrimes[v[n]]);
    for (int x : dv) root[n] = PST::update(x, 1, root[n]);
    par[n][0] = p;
    lvl[n] = lvl[p] + 1;
    for (int i = 1; i < 16; i++) par[n][i] = par[par[n][i - 1]][i - 1];
    for (int it : adj[n]) {
        if (it != p) { root[it] = root[n]; dfs(it, n); }
    }
}

int get_LCA(int p, int q) {
    if (lvl[p] < lvl[q]) swap(p, q);
    int Log = log2(lvl[p]) + 1;
    for (int i = Log; i >= 0; i--) if (lvl[p] - (1 << i) >= lvl[q]) p = par[p][i];
    if (p == q) return p;
    for (int i = Log; i >= 0; i--) if (par[p][i] != par[q][i]) { p = par[p][i]; q = par[q][i]; }
    return par[p][0];
}

vector<int> merge(const vector<int> &x, const vector<int> &y) {
    vector<int> ans;
    int f = 0, s = 0;
    while (f < x.size() && s < y.size()) {
        if (x[f] == y[s]) { ans.push_back(x[f]); f++; s++; }
        else if (x[f] < y[s]) ans.push_back(x[f++]);
        else ans.push_back(y[s++]);
    }
    while (f < x.size()) ans.push_back(x[f++]);
    while (s < y.size()) ans.push_back(y[s++]);
    return ans;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 2; i <= n; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y); adj[y].push_back(x);
    }
    root[0] = 0;
    dfs();
    int q; cin >> q;
    int ans = 0;
    while (q--) {
        int x, y; cin >> x >> y;
        x ^= ans; y ^= ans;
        ans = 0;
        int l = get_LCA(x, y);
        vector<int> pr = merge(uniquePrimes[v[x]], uniquePrimes[v[y]]);
        int sz = pr.size();
        for (int mask = 0; mask < (1 << sz); mask++) {
            ll num = 1; int cnt = 0;
            for (int j = 0; j < sz; j++) if (mask & (1 << j)) { cnt++; num *= pr[j]; if (num >= A) break; }
            if (num < A) {
                int res = PST::query(num, num, root[l]);
                if (cnt & 1) ans -= res;
                else ans += res;
            }
        }
        cout << ans << nl;
    }
}

int main() {
    rj
    pre();
    int t = 1;
    for (int cs = 1; cs <= t; cs++) solve();
    return 0;
}
