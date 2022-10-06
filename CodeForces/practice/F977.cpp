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
#define maxN 200005

int dp[maxN];
int a[maxN];
pi srtd[maxN];

int n;
vi best;

void solve(vi idx)
{
    // rep(i, 0, idx.size()){
    //     cout << idx[i] << " ";
    // }
    // cout << nL;
    if (idx.size() == 0)
        return;
    int base = a[idx[0]];
    vpi dp(sz(idx)); // first is maxlen, second is index of idx that caused it
    vi pr(sz(idx));
    sort(all(idx));
    // for(int i = sz(idx)-1; i >= 0; i--){
    //     idx[i] -= idx[0];
    // }
    // vi segtree(2*sz(idx));

    // rep(i, 0, sz(idx)){
    //     pr[i] = i;
    // }
    //dp[a[idx[0]] - base] = mp(1, 0);
    rep(i, 0, sz(idx))
    {
        if (a[idx[i]] > base && dp[a[idx[i]] - base - 1].f > 0 && dp[a[idx[i]] - base - 1].f + 1 >= dp[a[idx[i]] - base].f)
        {
            pr[i] = dp[a[idx[i]] - base - 1].s;
            dp[a[idx[i]] - base] = mp(dp[a[idx[i]] - base - 1].f + 1, i);
        }
        else
        {
            pr[i] = i;
            dp[a[idx[i]] - base] = mp(1, i);
        }
    }
    int mlen = 0;
    rep(i, 0, sz(idx))
    {
        if (dp[i].f > dp[mlen].f)
            mlen = i;
    }
    if (dp[mlen].f > best.size())
    {
        vi sol;
        int cur = dp[mlen].s;
        while (pr[cur] != cur)
        {
            sol.pb(idx[cur] + 1);
            cur = pr[cur];
        }
        sol.pb(idx[cur] + 1);
        reverse(all(sol));
        best = sol;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // memset(pr, -1, sizeof pr);
    // memset(dp, 1, sizeof dp);
    cin >> n;
    rep(i, 0, n)
    {
        cin >> a[i];
        srtd[i] = mp(a[i], i);
    }
    sort(srtd, srtd + n);
    vi cur;
    rep(i, 0, n)
    {
        if (sz(cur) == 0 || a[cur[sz(cur) - 1]] == srtd[i].f || a[cur[sz(cur) - 1]] + 1 == srtd[i].f)
        {
            cur.pb(srtd[i].s);
        }
        else
        {
            solve(cur);
            cur.clear();
            cur.pb(srtd[i].s);
        }
    }
    solve(cur);
    cout << best.size() << nL;
    rep(i, 0, best.size())
    {
        cout << best[i] << " ";
    }
    cout << nL;
    return 0;
}