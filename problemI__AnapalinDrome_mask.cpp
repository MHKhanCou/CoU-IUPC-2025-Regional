//https://codeforces.com/gym/106057/problem/I

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007

inline void add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; 
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = s.size();

        vector<int> pref(n + 1);
        for (int i = 0; i < n; i++) {
            int msk = 1 << (s[i] - 'a');
            pref[i + 1] = pref[i] ^ msk;
        }

        map<int, array<int,2>> dp;
        dp[pref[n]] = {0, 1};

        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            int sumWays = 0, cntWays = 0;
            for (int j = 0; j <= 26; j++) {
                int cur = (j == 26 ? 0 : 1 << j);
                int msk = pref[i] ^ cur;
                if (!dp.count(msk)) continue;
                auto [sum, cnt] = dp[msk];
                add(sumWays, sum);
                add(sumWays, cnt);
                add(cntWays, cnt);
            }
            add(dp[pref[i]][0], sumWays);
            add(dp[pref[i]][1], cntWays);
            if (i == 0) ans = sumWays;
        }
        cout << ans << '\n';
    }
    return 0;
}
