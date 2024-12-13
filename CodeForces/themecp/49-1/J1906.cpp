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

const ll MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vector<vl> dp(n, vl(n)), pref(n, vl(n));
    vl pw2(n+5);
    pw2[0] = 1;
    rep(i, 1, sz(pw2)){
        pw2[i] = (pw2[i-1] * 2) % MOD;
    }
    for(int i = n-2; i >= 0; i--) {
        dp[n-1][i] = pw2[n-1-i-1];
    }
    for(int i = n-2; i >= 0; i--){
        pref[n-1][i] = (dp[n-1][i] + pref[n-1][i+1]) % MOD;
    }
    for(int i = n-2; i >= 0; i--) {
        for(int j = i-1; j >= 0; j--) {
            if(a[i] < a[i+1]) dp[i][j] = pref[i+1][j] * pw2[i-j-1] % MOD;
            else dp[i][j] = pref[i+1][j+1] * pw2[i-j-1] % MOD;
            pref[i][j] = (dp[i][j] + pref[i][j+1]) % MOD;
        }
    }
    cout << dp[1][0] << "\n";
    
    return 0;
}
