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
    int nc;
    cin >> nc;
    rep(cn, 0, nc){
        int e, f;
        cin >> e >> f;
        f -= e;
        int dp[f + 1];
        memset(dp, -1, sizeof dp);
        dp[0] = 0;
        int n, p, w; cin >> n;
        rep(a, 0, n){
            cin >> p >> w;
            for(int i = 0; i <= f - w; i++){
                if(dp[i] != -1)
                    dp[i + w] = min(dp[i + w] == -1 ? INT_MAX : dp[i + w], dp[i] + p);
            }
        }
        if(dp[f] == -1){
            cout << "This is impossible." << nL;
        }
        else{
            cout << "The minimum amount of money in the piggy-bank is " << dp[f] << ".\n";
        }
    }
    
    return 0;
}