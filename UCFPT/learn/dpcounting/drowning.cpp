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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k, MOD; cin >> n >> k >> MOD;
    vector dp(n+1, vector(k+1, vector(k+1, vi(n+1, -1))));
    auto go = [&](int unused, int mxrun, int run, int dirleft, auto &&go) -> int {
        if(mxrun > k) return 0;
        // cout << unused << " " << mxrun << " " << run << " " << dirleft << endl;
        auto &ans = dp[unused][mxrun][run][dirleft];
        if(ans != -1) return ans;
        if(unused == 0) return ans = 1;
        if(dirleft == 0) return ans = 0;
        ans = 0;
        // skip
        (ans += go(unused, mxrun, run, dirleft-1, go)) %= MOD;
        // take
        (ans += go(unused-1, max(mxrun, run+1), run+1, dirleft-1, go)) %= MOD;
        // take and switch dirs
        if(run + 1 >= 2) {
            (ans += go(unused-1, max(mxrun, run+1), 1, unused-dirleft, go)) %= MOD;
        }
        return ans;
    };

    // n=1, small n < k?
    cout << go(n, 0, 0, n, go) << "\n";
    return 0;
}
