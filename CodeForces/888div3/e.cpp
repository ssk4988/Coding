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

const ll BAD = LLONG_MAX;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vl c(n), p(k), dp(n, BAD);
        rep(i, 0, n) cin >> c[i];
        rep(i, 0, k){
            cin >> p[i];
            p[i]--;
            dp[p[i]] = 0;
        }
        vvi recipe(n);
        rep(i, 0, n){
            int m; cin >> m;
            rep(j, 0, m){
                int v; cin >> v; v--;
                recipe[i].pb(v);
            }
        }
        auto solve = [&](int cur, auto &&solve)->ll{
            if(dp[cur] != BAD) return dp[cur];
            dp[cur] = c[cur];
            if(recipe[cur].size()){
                ll cost = 0;
                for(int nex : recipe[cur]) cost += solve(nex, solve);
                dp[cur] = min(dp[cur], cost);
            }
            return dp[cur];
        };
        rep(i, 0, n) cout << solve(i, solve) << " ";
        cout << nL;
    }
    
    return 0;
}