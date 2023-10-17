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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; ll k;
        cin >> n >> m >> k; k *= 2;
        vector<vector<pair<int, ll>>> adj(n);
        ll sumw = 0;
        rep(i, 0, n - 1){
            int a, b; ll w; cin >> a >> b >> w;
            a--, b--;
            w *= 2;
            sumw += w;
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        }
        vi memod(n);
        vector<vl> dp(n);
        auto calc = [&](int cur, int par, auto && calc) -> void {
            if(memod[cur]) return;
            memod[cur] = true;
            dp[cur] = {0, k/2};
            for(auto [nex, w] : adj[cur]){
                if(nex == par) continue;
                calc(nex, cur, calc);
                vl newdp(sz(dp[cur]) + sz(dp[nex]) - 1, LLONG_MAX);
                rep(i, 0, sz(dp[cur])){
                    rep(j, 0, sz(dp[nex])){
                        newdp[i + j] = min(newdp[i + j], dp[cur][i] + dp[nex][j] + (j % 2 == 0) * w);
                    }
                }
                swap(dp[cur], newdp);
            }
        };
        calc(0, -1, calc);
        ll ans = LLONG_MAX;
        rep(i, 0, min(sz(dp[0]), 2 * m + 1)){
            if(i % 2 == 1) continue;
            ans = min(ans, dp[0][i]);
        }
        cout << ((ans + sumw) / 2) << nL;
    }
    
    return 0;
}