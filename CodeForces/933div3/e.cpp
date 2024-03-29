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
        int n, m, k, d; cin >> n >> m >> k >> d;
        vvi grid(n, vi(m));
        rep(i, 0, n){
            rep(j, 0, m){
                cin >> grid[i][j];
            }
        }
        vl ans(n);
        rep(i, 0, n){
            vl dp(m+1);
            multiset<ll> best;
            dp[0] = 1;
            best.insert(dp[0]);
            rep(j, 1, m){
                dp[j] = *best.begin() + grid[i][j] + 1;
                if(j - d - 1 >= 0) best.erase(best.find(dp[j - d - 1]));
                best.insert(dp[j]);
            }
            ans[i] = dp[m-1];
        }
        vl pref(ans);
        partial_sum(all(pref), pref.begin());
        pref.insert(pref.begin(), 0);
        ll best = 1e18;
        rep(i, 0, sz(pref)){
            if(i - k >= 0) best = min(best, pref[i] - pref[i - k]);
        }
        cout << best << "\n";
    }
    
    return 0;
}
