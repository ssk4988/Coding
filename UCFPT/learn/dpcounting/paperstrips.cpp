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

string s;
vi v;
int n;

int cover(int l, int r)
{
    // cover bits from l to r (exclusive-exclusive)
    if (l + 1 >= r)
        return 0;
    int mask = (1 << (r - l - 1)) - 1;
    return mask << (l + 1);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> s;
    string c;
    for (char x : s)
    {
        if (sz(c) == 0 || c.back() != x)
            c.pb(x);
    }
    s = c;
    n = sz(s);
    v.resize(n);
    rep(i, 0, n)
    {
        v[i] = s[i] - 'a';
    }
    vvi inc(n + 1, vi(n + 1, -1)), dec(n + 1, vi(n + 1, -1)), bitonic(n + 1, vi(n + 1));
    vvi mn(n+1, vi(n+1, INT_MAX)), mx(n+1, vi(n+1, INT_MIN)), mxidx(n+1, vi(n+1));
    rep(i, 0, n)
    {
        bool isinc = true, isdec = true;
        rep(j, i, n)
        {
            mn[i][j+1] = min(mn[i][j], v[j]);
            mx[i][j+1] = max(mx[i][j], v[j]);
            if (j != i && v[j] < v[j - 1])
                isinc = false;
            if (j != i && v[j] > v[j - 1])
                isdec = false;
            if(isinc){
                inc[i][j+1] = cover(mn[i][j+1], mx[i][j+1]);
            }
            if(isdec){
                dec[i][j+1] = cover(mn[i][j+1], mx[i][j+1]);
            }
        }
    }
    rep(i, 0, n){
        rep(j, i, n) {
            mxidx[i][j+1] = i;
            rep(k, i, j+1) {
                if(v[k] > v[mxidx[i][j+1]]) mxidx[i][j+1] = k;
            }
            if(inc[i][mxidx[i][j+1]+1] != -1 && dec[mxidx[i][j+1]][j+1] != -1) bitonic[i][j+1] = true;
        }
    }
    vi uppermask(28);
    rep(i, 0, 28){
        rep(j, i+1, 26){
            uppermask[i] |= 1 << j;
        }
    }
    set<tuple<int, int, int>> seen;
    // state: prefix used, inc mask, dec mask = min segments
    queue<tuple<int, int, int, int, int, int, int>> q;
    q.emplace(0, 0, 0, 0, -1, -1, -1);
    int ans = INT_MAX;
    while (!q.empty())
    {
        auto [pref, incmask, decmask, res, ppref, pincmask, pdecmask] = q.front();
        q.pop();
        cout << pref << " " << incmask << " " << decmask << " " << res << " " << ppref << " " << pincmask << " " << pdecmask << endl;
        if (pref == n)
        {
            ans = res - 1;
            break;
        }
        rep(i, pref, n)
        {
            if(inc[pref][i+1] != -1) {
                int mask = inc[pref][i+1] | (1 << mn[pref][i+1]) | (1 << mx[pref][i+1]);
                if ((mask & incmask) == 0)
                {
                    if (!seen.count({i + 1, incmask | inc[pref][i+1], decmask}))
                    {
                        seen.insert({i + 1, incmask | inc[pref][i+1], decmask});
                        q.emplace(i + 1, incmask | inc[pref][i+1], decmask, res + 1, pref, incmask, decmask);
                    }
                }
            }
            if(dec[pref][i+1] != -1) {
                int mask = dec[pref][i+1] | (1 << mn[pref][i+1]) | (1 << mx[pref][i+1]);
                if ((mask & decmask) == 0)
                {
                    if (!seen.count({i + 1, incmask, decmask | dec[pref][i+1]}))
                    {
                        seen.insert({i + 1, incmask, decmask | dec[pref][i+1]});
                        q.emplace(i + 1, incmask, decmask | dec[pref][i+1], res + 1, pref, incmask, decmask);
                    }
                }
            }
            if(bitonic[pref][i+1]) {
                int m = mxidx[pref][i+1];
                int covermask = uppermask[mn[pref][i+1]];
                int mask = covermask | (1 << mn[pref][i+1]);
                if((mask & incmask) == 0 && (mask & decmask) == 0) {
                    if (!seen.count({i + 1, incmask | covermask, decmask | covermask}))
                    {
                        seen.insert({i + 1, incmask | covermask, decmask | covermask});
                        q.emplace(i + 1, incmask | covermask, decmask | covermask, res + 1, pref, incmask, decmask);
                    }
                }
            }
        }
    }
    cout << ans << "\n";
    cout << sz(seen) << "\n";
    return 0;
}

// asapoihegiowbnfmpzysonaisjrignaseifoijhqnasdkjoigd
