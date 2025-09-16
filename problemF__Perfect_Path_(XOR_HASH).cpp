//https://codeforces.com/gym/106057/problem/F
/* Author: Mahabub Rahman */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define nl "\n"

const ll N = 2e5 + 5;
const ll MOD = 1e14 + 7;

ll par[N][20], Xor[N], zero[N], neg[N], depth[N], a[N], sp[N], h[N], dp[N];
vector<ll> g[N];

void init_code() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

ll kth_parent(ll u, ll k) {
    for (ll b = 19; b >= 0; b--)
        if ((k >> b) & 1) u = par[u][b];
    return u;
}

ll LCA(ll u, ll v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = kth_parent(u, depth[u] - depth[v]);
    if (u == v) return v;
    for (ll k = 19; k >= 0; k--)
        if (par[u][k] != par[v][k] && par[u][k] != 0) {
            u = par[u][k];
            v = par[v][k];
        }
    return par[v][0];
}

void dfs(ll u, ll p, ll d) {
    par[u][0] = p;
    neg[u] = neg[p];
    zero[u] = zero[p];
    depth[u] = d;

    if (a[u] == 0) zero[u]++;
    if (a[u] < 0) neg[u] ^= 1, a[u] *= -1;

    ll x = a[u], XOR = 0;
    if (dp[x] == -1) {
        while (x > 1) {
            ll p = sp[x], bit = 0;
            while (x % p == 0) bit ^= 1, x /= p;
            if (bit) XOR ^= h[p];
        }
        dp[a[u]] = XOR;
    } else XOR = dp[x];
    Xor[u] = Xor[p] ^ XOR;

    for (auto v : g[u])
        if (v != p) dfs(v, u, d + 1);
}

void pre() {
    for (ll i = 1; i < N; ++i) h[i] = (rand() * 1LL * rand()) % MOD;
    for (int i = 2; i * i < N; i++) {
        if (sp[i]) continue;
        sp[i] = i;
        for (int j = i * i; j < N; j += i)
            if (!sp[j]) sp[j] = i;
    }
    dp[0] = dp[1] = -1;
    for (int i = 2; i < N; ++i) {
        if (!sp[i]) sp[i] = i;
        dp[i] = -1;
    }
}

int main() {
    init_code();
    pre();

    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> a[i];
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 0, 0);

    for (ll k = 1; k < 20; k++)
        for (ll u = 1; u <= n; u++)
            par[u][k] = par[u][k - 1] ? par[par[u][k - 1]][k - 1] : 0;

    ll q;
    cin >> q;
    while (q--) {
        ll u, v;
        cin >> u >> v;
        ll lca = LCA(u, v);

        ll nX = neg[u] ^ neg[par[lca][0]];
        ll z = zero[u] - zero[par[lca][0]];
        ll XOR = Xor[u] ^ Xor[par[lca][0]];

        nX ^= (neg[v] ^ neg[lca]);
        z += (zero[v] - zero[par[lca][0]]);
        XOR ^= (Xor[v] ^ Xor[lca]);

        if (z > 0) cout << "Yes\n";
        else if (nX > 0) cout << "No\n";
        else if (XOR == 0) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
