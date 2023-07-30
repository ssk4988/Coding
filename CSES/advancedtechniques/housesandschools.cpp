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

ll dp[3001][3001];
pi res[3001][3001];
ll cost[3001][3001];


struct DP
{ // Modify at w i l l :
    int layer;
    DP(int l) : layer(l){}
    int lo(int ind) { return 0; }
    int hi(int ind) { return layer == 1 ? 1 : ind; }
    ll f(int ind, int k) { return dp[layer - 1][k] + cost[k + 1][ind]; }
    void store(int ind, int k, ll v) { res[layer][ind] = pi(k, v); dp[layer][ind] = v;}
    void rec(int L, int R, int LO, int HI)
    {
        if (L >= R)
            return;
        int mid = (L + R) >> 1;
        pair<ll, int> best(LLONG_MAX, LO);
        rep(k, max(LO, lo(mid)), min(HI, hi(mid)))
            best = min(best, make_pair(f(mid, k), k));
        store(mid, best.second, best.first);
        rec(L, mid, LO, best.second + 1);
        rec(mid + 1, R, best.second, HI);
    }
    void solve(int L, int R) { rec(L, R, INT_MIN, INT_MAX); }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vl c(n + 1);
    rep(i, 1, n + 1){
        cin >> c[i];
    }
    vl prefs(n + 1), suffs(n + 1), pref(n + 1);
    rep(i, 1, n + 1){
        pref[i] = pref[i - 1] + c[i];
        prefs[i] = prefs[i - 1] + i * c[i];
    }
    for(int i = n; i >= 0; i--){
        if(i + 1 <= n) suffs[i] += suffs[i + 1];
        suffs[i] += (n - i) * c[i];
    }
    rep(i, 1, n + 1){
        ll sum = 0;
        ll median = i - 1;
        ll left = 0;
        rep(j, i, n + 1){
            sum += c[j];
            while(left < sum - left){
                median++;
                left += c[median];
            }
            assert(median <= j);
            ll leftside = suffs[i] - (median + 1 <= n ? suffs[median + 1] : 0) - (n - median) * left;
            ll rightside = prefs[j] - (median - 1 >= 0 ? prefs[median - 1] : 0) - median * (sum - left + c[median]);
            cost[i][j] = leftside + rightside;
            // cout << "cost[" << i << "][" << j << "]=" << cost[i][j] << nL;
        }
    }
    vector<DP> d;
    rep(i, 0, k + 1){
        d.pb(DP(i));
        if(i) d.back().solve(1, n + 1);
        // rep(j, 0, n + 1){
        //     cout << "dp[" << i << "][" << j << "]=" << dp[i][j] << nL;
        // }
    }
    cout << dp[k][n] << nL;

    return 0;
}