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

/*
if sum < 2 * max, then ans is max
ans is max(ceil(sum/2), max)
*/
const int N = 5002;
const int mod = 998244353;
int dp[N][N][2];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    sort(all(a));
    int s = accumulate(all(a), 0);
    dp[0][0][0] = 1;

    rep(i, 0, n) {
        rep(j, 0, s+1) {
            rep(k, 0, 2) {
                if(dp[i][j][k] == 0 )continue;
                (dp[i+1][j][0] += dp[i][j][k]) %= mod;
                (dp[i+1][j+a[i]][1] += dp[i][j][k]) %= mod;
            }
        }
    }
    ll ans = 0;
    rep(i, 0, n) {
        rep(j, 0, s+1) {
            ll ways = dp[i+1][j][1];
            int score = max(a[i], (j+1)/2);
            (ans += ways * score) %= mod;
        }
    }
    cout << ans << "\n";
    return 0;
}
