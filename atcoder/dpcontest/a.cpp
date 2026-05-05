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
    vl dp(n+5);
    dp[0] = 1;
    rep(i, 1, n+3) {
        dp[i] += dp[i-1];
        if(i >= 2) dp[i] += dp[i-2];
        for(int j = 3; j <= i; j += 1) {
            dp[i] += 2 * dp[i-j];
        }
    }
    cout << dp[n] << "\n";
    
    
    return 0;
}
