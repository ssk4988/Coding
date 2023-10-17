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
    vector<vd> prob(5005);
    // prob[0] = 
    prob[1] = {1};
    prob[2] = {1/ld(2), 0};
    rep(i, 3, sz(prob)){
        prob[i] = vd(i);
        if(i % 2 == 0){
            prob[i][0] = 1;
            int sm = 0, bg = i - 2;
            rep(j, 1, i){

                if(j - 2 < sz(prob[i - 2]) && j - 2 >= 0){
                    prob[i][j] += prob[i - 2][j - 2] * sm;
                    // cout << i << " " << j << " " << sm << " " << prob[i - 2][j - 2] << nL;
                }
                if(j - 1 < sz(prob[i - 2]) && j - 1 >= 0) {
                    prob[i][j] += prob[i - 2][j - 1] * bg;
                    // cout << i << " " << j << " " << bg << " " << prob[i - 2][j] << nL;
                }
                sm++;
                bg--;
            }
        }
        else{
            rep(j, 0, i){
                prob[i][j] = 1;
            }
        }
        // if(i < 8){
        rep(j, 0, i) prob[i][j] /= ld(i);
        // rep(j, 0, i){
        //     cout << i << " " << j << " " << prob[i][j] << nL;
        // }

        // }
        // prob[i] = max(1 / ld(i), ld(i - 2) / ld(i) * prob[i - 2]);
        // if(1 + 1e-12 < ld(i - 2) * prob[i - 2]){
        //     cout << i << " " << 1 / ld(i) << " " << ld(i - 2) / ld(i) * prob[i - 2] << nL;
        //     // break;
        // }
    }
    rep(i, 0, 7){
        
    }
    // rep(i, 1, 15){
    //     cout << fixed << setprecision(8) << prob[i] << nL;
    // }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vd dp(n);
        vvi adj(n);
        rep(i, 0, m){
            int a, b; cin >> a >> b;
            a--, b--;
            adj[a].pb(b);
        }
        dp[n - 1] = 1;
        for(int i = n- 1; i >= 0; i--){
            vd ps;
            for(int j : adj[i]){
                ps.pb(dp[j]);
                // dp[i] += dp[j] * prob[sz(adj[i])];
            }
            sort(all(ps));
            reverse(all(ps));
            rep(j, 0, sz(adj[i])){
                dp[i] += ps[j] * prob[sz(adj[i])][j];
            }
            // cout << i << " " << dp[i] << nL;
        }
        cout << fixed << setprecision(12) << dp[0] << nL;
        
    }
    
    return 0;
}