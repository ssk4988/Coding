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

const ll inf = 1e18;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll b;
    cin >> n >> b;
    vi par(n);
    vvi adj(n);
    vl c(n), d(n);
    rep(i, 0, n){
        cin >> c[i] >> d[i];
        if(i) cin >> par[i];
        par[i]--;
        if(par[i] >= 0) adj[par[i]].pb(i);
    }
    vector<vvl> dp(n, vvl(2));
    vi subsz(n);
    auto convolve = [&](vl &a, vl &b)->vl{
        vl res(sz(a) + sz(b) - 1, inf);
        rep(i, 0, sz(a)){
            rep(j, 0, sz(b)){
                res[i + j] = min(res[i + j], a[i] + b[j]);
            }
        }
        return res;
    };
    auto solve = [&](int cur, auto && solve)->void{
        subsz[cur] = 1;
        for(int i : adj[cur]){
            solve(i, solve);
            subsz[cur] += subsz[i];
        }
        dp[cur][0] = {0, c[cur]};
        for(int i : adj[cur]){
            dp[cur][0] = convolve(dp[i][0], dp[cur][0]);
        }
        dp[cur][1] = {inf, c[cur] - d[cur]};
        for(int i : adj[cur]){
            dp[cur][1] = convolve(dp[i][1], dp[cur][1]);
        }
        rep(i, 0, sz(dp[cur][1])){
            dp[cur][1][i] = min(dp[cur][1][i], dp[cur][0][i]);
        }
    };
    solve(0, solve);
    int ans = 0;
    rep(parity, 0, 2){
        rep(i, 0, sz(dp[0][parity])){
            if(dp[0][parity][i] <= b){
                ans = max(ans, i);
            }
        }
    }
    cout << ans << nL;

    
    return 0;
}
