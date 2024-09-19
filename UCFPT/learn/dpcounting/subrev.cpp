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
const int N = 51;
int dp[N][N][N+1][N+1][2];

int main()
{
    // freopen("subrev.in", "r", stdin);
    // freopen("subrev.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    memset(dp, -1, sizeof dp);
    rep(i, 0, n) cin >> a[i];
    auto go = [&](int l, int r, int pl, int pr, int adv, auto &&go) -> int {
        if(l > r) return 0;
        int &ans = dp[l][r][pl][pr][adv];
        if(ans != -1) return ans;
        if(l == r) return ans = (pl == N || a[pl] <= a[l]) && (pr == N || a[l] <= a[pr]);
        ans = 0;
        if(adv == 0) {
            ans = max({ans, go(l+1, r, pl, pr, adv, go), go(l, r, pl, pr, 1, go)});
            if((pl == N || a[pl] <= a[l]) && (pr == N || a[l] <= a[pr])) ans = max(ans, 1 + go(l+1, r, l, pr, 0, go));
        }
        else {
            ans = max(ans, go(l, r-1, pl, pr, adv, go));
            if((pl == N || a[pl] <= a[r]) && (pr == N || a[r] <= a[pr])) ans = max(ans, 1 + go(l, r-1, pl, r, 0, go));
            if(a[l] >= a[r] && (pl == N || a[pl] <= a[r]) && (pr == N || a[l] <= a[pr])) ans = max(ans, 2 + go(l+1, r-1, r, l, 0, go));
            if((pl == N || a[pl] <= a[l]) && (pr == N || a[l] <= a[pr])) ans = max(ans, 1 + go(l+1, r-1, pl, l, 0, go));
            if((pl == N || a[pl] <= a[r]) && (pr == N || a[r] <= a[pr])) ans = max(ans, 1 + go(l+1, r-1, r, pr, 0, go));
        }
        // cout << l << " " << r << " " << pl << " " << pr << " " << adv << " = " << ans << endl;
        return ans;
    };
    cout << go(0, n-1, N, N, 0, go) << endl;
    
    return 0;
}
