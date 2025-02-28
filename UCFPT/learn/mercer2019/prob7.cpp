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

const int mod = 1e4+7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        string target;
        rep(i, 0, k) target += 'L';
        target += 'O';
        rep(i, 0, k) target += 'L';
        vector dp(n+1, vi(sz(target)+1));
        dp[0][0] = 1;
        rep(i, 0, n) {
            rep(j, 0, sz(target)) {
                if(s[i] == target[j]) {
                    (dp[i+1][j+1] += dp[i][j]) %= mod;
                }
                (dp[i+1][j] += dp[i][j]) %= mod;
            }
            (dp[i+1].back() += dp[i].back()) %= mod;
        }
        cout << dp.back().back() << "\n";
    }
    
    return 0;
}
