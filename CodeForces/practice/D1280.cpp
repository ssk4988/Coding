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

pl operator+(pl &a, pl &b){
    return {a.f + b.f, a.s + b.s};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vl dif(n);
        rep(i, 0, n){
            ll v; cin >> v;
            dif[i] -= v;
        }
        rep(i, 0, n){
            ll v; cin >> v;
            dif[i] += v;
        }
        vvi adj(n);
        rep(i, 0, n - 1){
            int a, b; cin >> a >> b;
            a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vector<vpl> dp(n);
        auto convert = [](pl &a)->pl{
            return {a.f + (a.s > 0), 0};
        };
        auto convolve = [&](vpl &a, vpl &b)->vpl{
            vpl res(sz(a) + sz(b) - 1, {-1, -1});
            rep(i, 0, sz(a)){
                rep(j, 0, sz(b)){
                    res[i + j] = max(res[i + j], a[i] + b[j]);
                }
            }
            return res;
        };
        auto solve = [&](int cur, int p, auto &&solve)->vpl{
            dp[cur].pb({0, 0});
            for(int i : adj[cur]){
                if(i == p) continue;
                solve(i, cur, solve);
                dp[cur] = convolve(dp[cur], dp[i]);
            }
            rep(i, 0, sz(dp[cur])){
                dp[cur][i].s += dif[cur];
            }
            dp[cur].pb({-1, -1});
            for(int i = sz(dp[cur]) - 2; i >= 0; i--){
                if(cur == 0) dp[cur][i + 1] = convert(dp[cur][i]);
                else dp[cur][i + 1] = max(dp[cur][i + 1], convert(dp[cur][i]));
            }
            return dp[cur];
        };
        vpl ans = solve(0, -1, solve);
        cout << ans[m].f << nL;
    }
    
    return 0;
}