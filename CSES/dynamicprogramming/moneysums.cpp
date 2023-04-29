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
    int LIM = 1e5 + 10;
    vi dp(LIM);
    dp[0] = true;
    rep(i, 0, n){
        int v; cin >> v;
        for(int j = LIM - 1; j - v >= 0; j--){
            dp[j] |= dp[j - v];
        }
    }
    vi ans;
    rep(i, 1, LIM){
        if(dp[i])ans.pb(i);
    }
    cout << sz(ans) << nL;
    for(int i : ans){
        cout << i << " ";
    }
    cout << nL;
    
    return 0;
}