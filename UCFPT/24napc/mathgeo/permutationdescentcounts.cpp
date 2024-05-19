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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const int N = 105;
int dp[N][N];
const int mod = 1001113;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    dp[1][0] = 1;
    rep(i, 2, N){
        rep(j, 0, i+1){
            dp[i][j] = (dp[i][j] + ll(1 + j) * dp[i-1][j] % mod) % mod;
            if(j) dp[i][j] = (dp[i][j] + ll(dp[i-1][j-1]) * (i - j) % mod) % mod;
            // if(i < 5) cout << i << " " << j << " " << dp[i][j] << "\n";
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int c, n, k; cin >> c >> n >> k;
        cout << c << " " << dp[n][k] << "\n";
    }
    
    return 0;
}
