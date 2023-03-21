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
bool DEBUG = false;

vector<vl> bysize, pref, dp;
struct Line
{
    mutable ll p;
    mutable int siz;
    mutable ll yoffset, xoffset;
    bool operator<(const Line &o) const { return xoffset < o.xoffset; }
    bool operator<(ll x) const { return p < x; }
    ll eval(ll x) const
    {
        ll v = 0;
        if (x - xoffset >= sz(pref[siz]))
        {
            if(DEBUG) 
                cout << "too big, x is " << x << ", xoffset is " << xoffset << ", size is " << sz(pref[siz]) << nL;
            v = sz(pref[siz]) > 0 ? pref[siz].back() : 0;
        }
        else if (x - xoffset >= 0)
        {
            v = pref[siz][x - xoffset];
        }
        else
        {
            if(DEBUG) cout << "too small, out of range" << nL;
            return -5;
        }
        return yoffset + v;
    }
};

struct LineContainer : multiset<Line, less<>>
{
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b)
    { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y)
    {
        if (y == end())
        {
            x->p = inf;
            return 0;
        }
        ll maxv = y->xoffset + sz(pref[y->siz]) - 1;
        ll lo = x->xoffset, hi = maxv;
        while (lo < hi)
        {
            ll mid = lo + (hi - lo + 1) / 2;
            if (x->eval(mid) >= y->eval(mid))
            {
                lo = mid;
            }
            else
            {
                hi = mid - 1;
            }
        }
        x->p = lo;
        // if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        // else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll xoffset, ll yoffset, int siz)
    {
        Line l1;
        l1.xoffset = xoffset, l1.yoffset = yoffset, l1.siz = siz;
        auto z = insert(l1), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x)
    {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.eval(x);
    }
};
int n, k;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k;
    bysize.assign(301, {});
    pref.assign(301, {});
    dp = vector<vl>(301, vl(k + 1));
    rep(i, 0, n)
    {
        int s, v;
        cin >> s >> v;
        bysize[s].pb(v);
    }
    rep(i, 0, sz(bysize))
    {
        sort(all(bysize[i]));
        reverse(all(bysize[i]));
        pref[i] = bysize[i];
        rep(j, 1, sz(pref[i]))
        {
            pref[i][j] += pref[i][j - 1];
        }
    }
    // CHECK IF PREF EMPTY, SKIP AFTER COPY
    rep(i, 1, sz(dp))
    {
        // if(sz(bysize[i]) == 0){
        //     bysize[i].pb(0);
        //     pref[i].pb(0);
        // }
        rep(j, 0, sz(dp[i]))
        {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
        if(sz(pref[i]) == 0) continue;
        rep(modres, 0, i)
        {
            LineContainer lc;
            int j = 0, j1 = modres;
            while (j1 < sz(dp[i]))
            {
                if (j > 0)
                {
                    // update dp?
                    dp[i][j1] = max(dp[i][j1], lc.query(j));
                }
                lc.add(j + 1, dp[i - 1][j1], i);
                j++;
                j1 += i;
            }
        }

        rep(j, 1, sz(dp[i]))
        {
            dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
    }

    rep(i, 1, k + 1)
    {
        cout << dp[300][i] << (i + 1 <= k ? " " : nL);
    }

    return 0;
}
