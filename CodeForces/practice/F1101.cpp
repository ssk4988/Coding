#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;
using vvl = vector<vl>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

ll inf = 1e12;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    vector<array<int, 4>> qs;
    ll ans = 0;
    vvi ts(n + 1);
    rep(i, 0, m){
        int s, f, c, r;
        cin >> s >> f >> c >> r;
        s--, f--;
        qs.pb({s, f, c, r});
        ts[r].pb(i);
    }
    vector<vvl> dp(2, vvl(n, vl(n, inf)));
    rep(l, 0, n){
        rep(r, l, n){
            dp[0][l][r] = a[r] - a[l];
        }
    }
    for(int q : ts[0]){
        auto [s, f, c, r] = qs[q];
        ans = max(ans, ll(c) * dp[0][s][f]);
    }
    rep(i, 1, n + 1){
        rep(l, 0, n){
            int opt = n - 1;
            for(int r = n - 1; r >= l; r--){
                opt = min(r, opt);
                while(opt - 1 >= l && max(dp[0][l][opt], a[r] - a[opt]) >= max(dp[0][l][opt - 1], a[r] - a[opt - 1])) opt--;
                dp[1][l][r] = max(dp[0][l][opt], a[r] - a[opt]);
            }
        }
        for(int q : ts[i]){
            auto [s, f, c, r] = qs[q];
            ans = max(ans, ll(c) * dp[1][s][f]);
        }
        dp[0] = dp[1];
    }
    cout << ans << nL;
    return 0;
}
