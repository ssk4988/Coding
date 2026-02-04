#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int d, t; cin >> d >> t;
    vi has(367);
    rep(i, 0, d) {
        int x; cin >> x;
        has[x] = 1;
    }
    vii tickets(t);
    rep(i, 0, t) {
        cin >> tickets[i].f >> tickets[i].s;
    }
    vi pref(has);
    rep(i, 0, sz(pref)-1){
        pref[i+1] += pref[i];
    }
    vi dp(367, 1e9);
    dp[0] = 0;
    rep(i, 1, sz(dp)) {
        for(auto [k, c] : tickets) {
            dp[i] = min(dp[i], dp[max(0, i-k)]+c);
        }
        if(!has[i]) dp[i] = min(dp[i], dp[i-1]);
    }
    cout << dp.back() << "\n";
    
    return 0;
}
