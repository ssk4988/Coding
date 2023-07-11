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
using vvl = vector<vl>;

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
    vvl arr(n, vl(n)), pref(n, vl(n));
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> arr[i][j];
            pref[i][j] = arr[i][j];
            if(i > 0) pref[i][j] += pref[i - 1][j];
            if(j > 0) pref[i][j] += pref[i][j - 1];
            if(i > 0 && j > 0) pref[i][j] -= pref[i - 1][j - 1];
        }
    }
    auto rangequery = [&](int r1, int c1, int r2, int c2)->ll{
        r1--, c1--;
        ll v = pref[r2][c2];
        if(r1>=0) v-= pref[r1][c2];
        if(c1>=0) v-= pref[r2][c1];
        if(r1>=0 && c1>=0) v += pref[r1][c1];
        return v;
    };
    vector<vpl> dp(n, vpl(n, {LLONG_MAX, -1}));
    rep(i, 0, n){
        dp[i][i] = {0, i};
    }
    rep(len, 2, n + 1){
        rep(l, 0, n - len + 1){
            int r = l + len - 1;
            rep(mid, l, r + 1){
                int leftlen = mid - l, rightlen = r - mid;
                ll cost = 0;
                // cout << "for range [" << l << "," << r << "]: \n";
                if(leftlen > 0){
                    cost += rangequery(l, 0, mid - 1, n - 1) - rangequery(l, l, mid - 1, mid - 1);
                    cost += dp[l][mid - 1].f;
                    // cout << "adding rect vals " << rangequery(l, 0, mid - 1, n - 1) << " minus " << rangequery(l, l, mid - 1, mid - 1) << "\n";
                }
                if(rightlen > 0){
                    cost += rangequery(mid + 1, 0, r, n - 1) - rangequery(mid + 1, mid + 1, r, r);
                    cost += dp[mid + 1][r].f;
                    // cout << "adding rect vals " << rangequery(mid + 1, 0, r, n - 1) << " minus " << rangequery(mid + 1, mid + 1, r, r) << "\n";
                }
                if(cost < dp[l][r].f){
                    dp[l][r] = {cost, mid};
                }
            }
        }
    }
    // cout << dp[0][n - 1].f << "\n";
    vi ans(n, -1);
    auto dfs = [&](int l, int r, int p, auto &&dfs)->void{
        ans[dp[l][r].s] = p;
        if(dp[l][r].s > l){
            dfs(l, dp[l][r].s - 1, dp[l][r].s, dfs);
        }
        if(dp[l][r].s < r){
            dfs(dp[l][r].s + 1, r, dp[l][r].s, dfs);
        }
    };
    dfs(0, n - 1, -1, dfs);
    rep(i, 0, n){
        cout << (ans[i] + 1) << " ";
    }
    cout << "\n";
    
    return 0;
}