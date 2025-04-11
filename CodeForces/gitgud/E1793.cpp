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
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    vi ans(n+1);
    rep(i, 0, n) {
        int cont = max(i+1, a[i]);
        int k = n - cont + 1;
        ans[k]++;
    }
    for(int i = n-1; i >= 0; i--) {
        ans[i] += ans[i+1];
    }
    vi dp(n+1);
    rep(i, 1, n+1) {
        if(i-a[i-1] >= 0) dp[i] = 1 + dp[i - a[i-1]];
        if(dp[i]) ans[dp[i] + n-i] = max(ans[dp[i] + n-i], i);
        dp[i] = max(dp[i], dp[i-1]);
    }
    for(int i = n-1; i >= 0; i--) ans[i] = max(ans[i], ans[i+1]);
    int q; cin >> q;
    rep(i, 0, q) {
        int k; cin >> k;
        cout << ans[k] << "\n";
    }

    
    return 0;
}
