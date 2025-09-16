// starting with the name of almighty ALLAH
// Practice is the only shortcut to improve
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rj ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'

void solve() {
    ll a;
    cin >> a;
    ll an = 1;
    for (ll i = 1; i < a; ++i) an *= i;
    cout << an << nl;
}

int main() {
    rj
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
