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
        int n; cin >> n;
        vi a(n), mn(n, INT_MAX), dp(n);
        rep(i, 0, n){
            cin >> a[i]; a[i]--;
        }
        rep(i, 0, n){
            // if(mx[a[i]] == INT_MIN){
            //     dp[i] = -(i + 1);
            // }
            // else{
            dp[i] = min(mn[a[i]], (i > 0 ? (1 + dp[i - 1]) : (1 + 0)));
            // }
            // if(i > 0){
            //     mx[a[i]] = max(mx[a[i]], dp[i - 1]);
            // }
            // else{
            //     mx[a[i]] = max(mx[a[i]], 0);
            // }
            mn[a[i]] = min(mn[a[i]], (i > 0 ? dp[i - 1] : 0));
        }
        cout << (n - dp[n - 1]) << nL;
    }
    
    return 0;
}
