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
    int n, q; cin >> n >> q;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vvi dp(n, vi(2));
    rep(i,0, n){
        dp[i][0] = 1;
        rep(j, 0, i){
            if(a[j] < a[i]){
                dp[i][0] = max(dp[i][0], 1 + dp[j][1]);
            }
            else{
                dp[i][1] = max(dp[i][1], max(1 + dp[j][0], dp[j][1]));
            }
        }
        dp[i][1] = max(dp[i][1], dp[i][0]);
    }
    
    return 0;
}
