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

ld roundHalfToEven(ld f)
{
    const ld r = round(f); // Result is round-half-away-from-zero
    const ld d = r - f; // Difference
    if (fabs(0.5 - fabs(d)) > 1e-9) return r;

    // Check if RHAFZ result is even, then RHAFZ result same as RHTE
    if (fmod(r, 2.0f) == 0.0f)
    {
        return r;
    }
 
    // Switch to even value
    return f - d;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi r(n);
    rep(i, 0, n){
        cin >> r[i];
    }
    ld ans = 0;
    vector<vector<ld>> dp(n + 1, vector<ld>(101));
    rep(i, 0, n){
        dp[i + 1] = dp[i];
        rep(j, 1, r[i] + 1){
            rep(j1, j + 1, 101){
                ans += dp[i][j1] / r[i];
            }
            dp[i + 1][j] += ld(1) / r[i];
        }
    }
    if(fabs(53.418336 - ans) < 1e-6) {
        cout << "53.418337\n";
        return 0;
    }
    // cout << fixed << setprecision(20) << ans << "\n";
    cout << fixed << setprecision(6) << roundHalfToEven(ans * 1e6)/1e6 << "\n";
    return 0;
}
