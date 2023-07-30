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
ll pref[3001];
ll x[3001];

struct DP
{ // Modify at w i l l :
    int layer;
    DP(int l) : layer(l){}
    int lo(int ind) { return 0; }
    int hi(int ind) { return layer == 1 ? 1 : ind; }
    ll f(int ind, int k) { return dp[layer - 1][k] + (pref[ind] - pref[k]) * (pref[ind] - pref[k]); }
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
    rep(i, 1, n + 1){
        cin >> x[i];
        pref[i] = x[i] + pref[i - 1];
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