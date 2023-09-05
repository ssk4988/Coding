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
    int n; cin >> n;
    vi par(n, -1);
    vvi child(n);
    vi subsz(n, 1);
    rep(i, 1, n){
        cin >> par[i];
        par[i]--;
        child[par[i]].pb(i);
    }
    for(int i = n-1; i >= 0; i--){
        for(int j : child[i]) subsz[i] += subsz[j];
    }
    ll ans = 0;
    rep(i, 0, n){
        vi c;
        for(int j : child[i]) c.pb(subsz[j]);
        vector<bool> dp(subsz[i]);
        dp[0] = true;
        for(int j : c){
            for(int k = sz(dp) - 1; k >= 0; k--){
                if(j + k < sz(dp) && dp[k]) dp[j + k] = true;
            }
        }
        ll best = 0;
        rep(j, 0, sz(dp)){
            if(dp[j]) best = max(best, ll(j) * (sz(dp) - 1 - j));
        }
        ans += best;
    }
    cout << ans << nL;
    
    return 0;
}
