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
int dp[10009];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    int m = 1e9+7;
    rep(cn, 0, nc){
        int x; cin >> x;
        int n; cin >> n;
        int c[n];
        rep(i, 0, n){
            cin >> c[i];
        }
        
        
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        rep(j, 0, n){
            rep(i, 0, 10000){
                if(c[j] + i <= 10000){
                    dp[c[j] + i] += dp[i];
                    dp[c[j] + i] %= m;
                }
            }
        }
        cout << dp[x] << nL;
    }
    
    return 0;
}