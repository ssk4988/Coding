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

int dp[20005];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        memset(dp, 0, sizeof dp);
        int k; cin >> k;
        vi a[k];
        rep(i, 0, k){
            int x, y, z;
            cin >> x >> y >> z;
            a[i].pb(x);
            a[i].pb(y);
            a[i].pb(z);
        }
        sort(a, a + k);
        int cur = 0;
        rep(i, 0, k){
            while(cur <= a[i][0]){
                if(cur > 0){
                    dp[cur] = max(dp[cur], dp[cur - 1]);
                }
                cur++;
            }
            cur--; 
            dp[cur + a[i][2]] = max(dp[cur + a[i][2]], dp[cur] + a[i][1]);
            cur++;
        }
        int ans = 0;
        rep(i, 0, 20005){
            ans = max(ans, dp[i]);
        }
        cout << ans << nL;
    }
    
    return 0;
}