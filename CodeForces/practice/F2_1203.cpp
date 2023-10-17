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

bool cmp(pi &a, pi &b){
    if(a.s >= 0 && b.s >= 0){
        return a.f < b.f;
    }
    else if(a.s < 0 && b.s < 0){
        return a.f + a.s > b.f + b.s;
    }
    else {
        return (a.s >= 0) > (b.s >= 0);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, r; cin >> n >> r;
    vpi p(n);
    rep(i, 0, n){
        cin >> p[i].f >> p[i].s;
    }
    sort(all(p), cmp);
    const int maxn = 105;
    const int maxr = r + 300 * maxn + 100;

    vvi dp(maxn, vi(maxr, -1));
    auto solve = [&](int idx, int rating, auto &&solve) -> int {
        if(rating < 0) return -2;
        if(idx == -1){
            return rating == r ? 0 : -2;
        }
        if(dp[idx][rating] != -1) return dp[idx][rating];
        dp[idx][rating] = -2;
        if(solve(idx - 1, rating, solve) != -2) dp[idx][rating] = max(dp[idx][rating], solve(idx - 1, rating, solve));
        if(rating - p[idx].s < maxr && rating - p[idx].s >= p[idx].f && solve(idx - 1, rating - p[idx].s, solve) != -2)
            dp[idx][rating] = max(dp[idx][rating], solve(idx - 1, rating - p[idx].s, solve) + 1);
        // cout << idx << " " << rating << " " << dp[idx][rating] << nL;
        return dp[idx][rating];
    };
    int ans = 0;
    rep(rating, 0, maxr){
        // if(solve(n - 1, rating, solve) > ans){
        //     cout << rating << " " << solve(n - 1, rating, solve) << nL;
        // }
        ans = max(ans, solve(n - 1, rating, solve));
    }
    cout << ans << nL;


    return 0;
}
