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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int m, n, k, s; cin >> m >> n >> k >> s;
    vd a;
    rep(i, 0, m+n){
        ld v; cin >> v;
        a.pb(v);
    }
    sort(all(a));
    vd pref(a);
    vd pref2(a);
    n = n + m;
    rep(i, 0, n){
        pref2[i] *= pref2[i];
    }
    partial_sum(all(pref), pref.begin());
    pref.insert(pref.begin(), 0);
    partial_sum(all(pref2), pref2.begin());
    pref2.insert(pref2.begin(), 0);
    vector<vd> cost(n, vd(n + 1));
    // rep(i, 0, n+1){
    //     cout << i << " " << pref[i] << " " << pref2[i] << "\n";
    // }
    rep(i, 0, n){
        rep(j, i+1, n+1){
            ld opt = (pref[j] - pref[i]) / (j - i);
            cost[i][j] = (j - i) * opt * opt + pref2[j] - pref2[i] - 2 * opt * (pref[j] - pref[i]) + (j - i) * s * s / 4.0;
            // cout << i << "," << j << " " << cost[i][j] << " opt: " << opt << "\n";
        }
    }
    ld inf = 1e18;
    vector<vd> dp(k+1, vd(n+1, inf));
    dp[0][0] = 0;
    rep(u, 0, k){
        rep(i, 0, n+1){
            rep(j, 0, i){
                dp[u+1][i] = min(dp[u+1][i], dp[u][j] + cost[j][i]);
            }
        }
    }
    cout << fixed << setprecision(8) << dp[k][n] << "\n";
    return 0;
}