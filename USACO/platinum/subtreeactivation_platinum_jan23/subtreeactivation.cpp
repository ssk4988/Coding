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
    vi par(n);
    par[0] = -1;
    vvi child(n);
    rep(i, 1, n){
        cin >> par[i];
        par[i]--;
        child[par[i]].pb(i);
    }
    vector<vl> dp(n, vl(2));
    // 0 fully solve subtree 1 solve all except heavy/most beneficial one
    vl subsz(n, 1);
    for(int i = n - 1; i >= 0; i--){
        for(int j : child[i]) subsz[i] += subsz[j];
    }
    for(int i = n - 1; i >= 0; i--){
        ll sumchild0 = 0;
        ll maxchild0 = 0;
        vl mindelta;
        vl child1;
        for(int j : child[i]){
            sumchild0 += dp[j][0];
            maxchild0 = max(maxchild0, dp[j][0]);
            mindelta.pb(dp[j][1] + subsz[i] - subsz[j] - dp[j][0]);
            child1.pb(dp[j][1] - dp[j][0]);
        }
        dp[i][1] = sumchild0 - maxchild0;
        dp[i][0] = 2 * subsz[i] + sumchild0;
        sort(all(mindelta));
        sort(all(child1));
        // reverse(all(child1));
        if(sz(child[i]) >= 1){
            // dp[i][0] = min(dp[i][0], subsz[i] + sumchild0 + mindelta[0]);
            dp[i][0] = min(dp[i][0], 2 * subsz[i] + sumchild0 + child1[0]);
            for(int j : child[i]){
                dp[i][0] = min(dp[i][0], sumchild0 + 2 * (subsz[i] - subsz[j]));
            }
        }
        if(sz(child[i]) >= 2){
            // dp[i][0] = min(dp[i][0], sumchild0 + mindelta[0] + mindelta[1]);
            dp[i][0] = min(dp[i][0], 2 * subsz[i] + sumchild0 + child1[0] + child1[1]);
        }
    }
    cout << dp[0][0] << nL;

    return 0;
}
