#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int,int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    s = "0" + s;
    int n = sz(s);
    vi dp(n+1, 1e9);
    dp[0] = 0;
    vi a(n);
    vi pref(n+1);
    rep(i, 0, n) a[i] = s[i] - '0', pref[i+1] = a[i] + pref[i];
    rep(i, 0, n) {
        dp[i+1] = min(dp[i+1], dp[i] + a[i]);
        rep(j, i+2, n+1) {
            int cost = a[i]+1 + (10-a[j-1]) + 9 * (j-i-2) - (pref[j-1] - pref[i+1]);
            dp[j] = min(dp[j], dp[i] + cost);
        }
    }
    cout << dp.back() << "\n";

    return 0;
}
