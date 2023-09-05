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
        ll w, f; cin >> w >> f;
        int n; cin >> n;
        vi a(n);
        int sum = 0;
        rep(i, 0, n){
            cin >> a[i];
            sum += a[i];
        }
        vi dp(sum + 1);
        dp[0] = true;
        rep(i, 0, n){
            for(int j = sum - a[i]; j >= 0; j--){
                if(dp[j]) dp[j + a[i]] = true;
            }
        }
        ll lo = 0, hi = 1e7;
        while(lo < hi){
            ll mid = lo + (hi - lo) / 2;
            ll ws = w * mid, fs = f * mid;
            bool works = false;
            rep(i, 0, sz(dp)){
                if(dp[i]){
                    if(ws >= i && fs >= sum - i || ws >= sum - i && fs >= i) works = true;
                }
            }
            if(works) hi = mid;
            else lo = mid + 1;
        }
        cout << lo << nL;
    }
    
    return 0;
}
