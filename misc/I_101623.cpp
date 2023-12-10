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
    int n, c; cin >> n >> c;
    vector<pair<pi, int>> apps(n);
    rep(i, 0, n){
        cin >> apps[i].f.f >> apps[i].f.s;
        apps[i].s = i;
    }
    sort(all(apps), [](pair<pi, int> a, pair<pi, int> b)->bool{return max(a.f.f, a.f.s) - a.f.s > max(b.f.f, b.f.s) - b.f.s;});
    vector<vector<pair<int, pi>>> dp(n + 1, vector<pair<int, pi>>(c + 1, {-1e5, {-1, -1}}));
    dp[0][0].f = 0;
    rep(i, 0, n){
        for(int j = c; j >= 0; j--){
            if(dp[i][j].f < 0) continue;
            if(j + max(apps[i].f.f, apps[i].f.s) <= c && dp[i+1][j + apps[i].f.s].f < 1 + dp[i][j].f){
                dp[i + 1][j + apps[i].f.s] = {dp[i][j].f + 1, {i, j}};
            }
            if(dp[i + 1][j].f < dp[i][j].f){
                dp[i + 1][j] = {dp[i][j].f, {i, j}};
            }
        }
    }
    pair<int, pi> ans = {0, {-1, -1}};
    rep(i, 0, c + 1) ans = max(ans, dp.back()[i]);
    cout << ans.f << nL;
    vi res;
    while(ans.f){
        // cout << (ans.s.s + 1) << " ";
        // cout << ans.f << " " << ans.s.f << " " << ans.s.s << nL;
        // bool add = false;
        if(dp[ans.s.f][ans.s.s].f + 1 == ans.f) res.pb(apps[ans.s.f].s + 1);
        // add = true;
        ans = dp[ans.s.f][ans.s.s];
        // if(add) 
    }
    reverse(all(res));
    for(int i : res) cout << i << " ";
    cout << nL;
    return 0;
}
