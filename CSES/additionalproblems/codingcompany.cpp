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

const ll MOD = 1e9 + 7;
ll dp[102][102][5001];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    dp[0][0][0] = 1;
    int n, x; cin >> n >> x;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    a.pb(-1);
    sort(all(a));
    rep(i, 0, n){
        int c = a[i + 1] - a[i];
        rep(j, 0, n + 1){
            rep(k, 0, x + 1){
                int k1 = k + j * c;
                if(k1 > x || k1 < 0 || dp[i][j][k] == 0) continue;
                // close some interval
                if(j){
                    dp[i + 1][j - 1][k1] = (dp[i + 1][j - 1][k1] + (j * dp[i][j][k]) % MOD) % MOD;
                }
                // open some interval here
                dp[i + 1][j + 1][k1] = (dp[i + 1][j + 1][k1] + dp[i][j][k]) % MOD;
                // open and close some interval
                dp[i + 1][j][k1] = (dp[i + 1][j][k1] + dp[i][j][k]) % MOD;
                // put it in some interval
                dp[i + 1][j][k1] = (dp[i + 1][j][k1] + (j * dp[i][j][k]) % MOD) % MOD;
            }
        }
    }
    ll ans = 0;
    rep(k, 0, x + 1){
        ans = (ans + dp[n][0][k]) % MOD;
    }
    cout << ans << nL;
    
    return 0;
}
