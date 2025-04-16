#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const int mod = 1e9+7;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k, s; cin >> n >> k >> s;
    vi dp(n+1);
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    vi pref(a);
    rep(i, 1, n) pref[i] = max(pref[i], pref[i-1]);
    pref.insert(begin(pref), 0);
    dp[0] = 1;
    rep(i, 0, n) {
        int mn = INT_MAX, mx = INT_MIN;
        rep(j, i+1, i+s+1) {
            mn = min(mn, a[j-1]);
            mx = max(mx, a[j-1]);
            if(abs(mx-mn) > k) continue;
            if(pref[i] >= mn) continue;
            (dp[j] += dp[i]) %= mod;
        }
    }
    cout << dp.back() << "\n";

    return 0;
}