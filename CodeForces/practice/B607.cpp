#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vvi dp(n, vi(n));
    rep(r, 0, n) {
        for(int l = r-1; l >= 0; l--) {
            dp[l][r] = 1e9;
            if(a[l] == a[r]) dp[l][r] = min(dp[l][r], dp[l+1][r-1]);
            rep(k, l, r) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r] + 1);
            }
        }
    }
    cout << 1+dp[0][n-1] << "\n";
    
    
    return 0;
}
