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
const int dif = 1414214;
int dp[dif+1];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const ll lim = 1e12+10;
    vl tri;
    tri.push_back(0);
    while(tri.back() < lim) {
        ll v = sz(tri);
        tri.push_back(v * (v+1) / 2);
    }
    rep(i, 0, dif+1) dp[i] = 1e9;
    // cout << sz(tri) << "\n";
    // vi dp(dif+1, 1e9);
    dp[0] = 0;
    rep(i, 1, dif+1) {
        int target = 0;
        for(int p = 1 << 20; p; p /= 2) {
            if(target + p >= sz(tri)) continue;
            if(2 * tri[target + p] <= i + 100) target += p;
        }
        rep(j, max(0, target-100), target+1) {
            if(2 * tri[j] > i + 100) break;
            if(i - tri[j] < 0) continue;
            dp[i] = min(dp[i], 1 + dp[i-tri[j]]);
        }
    }
    // return 0;
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        ll n; cin >> n;
        auto it = upper_bound(all(tri), n);
        it--;
        int ans = 1e9;
        int idx = it - begin(tri);
        rep(i, max(0, idx-1000), idx+1) {
            ll left = n - tri[i];
            if(left <= dif) {
                ans = min(ans, 1 + dp[left]);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
