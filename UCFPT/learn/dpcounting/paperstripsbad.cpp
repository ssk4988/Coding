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
    
    n = sz(s);
    v.resize(n);
    pi mx{-1, -1};
    rep(i, 0, n)
    {
        v[i] = s[i] - 'a';
        mx = max(mx, pi{v[i], i});
    }
    bool bitonic = true;
    rep(i, 0, n-1){
        if(i < mx.s && v[i] > v[i+1]) bitonic = false;
        if(i >= mx.s && v[i] < v[i+1]) bitonic = false;
    }
    if(bitonic){
        cout << 0 << "\n";
        return 0;
    }

    set<tuple<int, int, int>> seen;
    // state: prefix used, inc mask, dec mask = min segments
    queue<tuple<int, int, int, int>> q;
    q.emplace(0, 0, 0, 0);
    int ans = INT_MAX;
    while (!q.empty())
    {
        auto [pref, inc, dec, res] = q.front();
        q.pop();
        cout << pref << " " << inc << " " << dec << " " << res << endl;
        if(pref == n) {
            ans = res - 1;
            break;
        }
        bool isinc = true;
        bool isdec = true;
        int mn = INT_MAX, mx = INT_MIN;
        rep(i, pref, n)
        {
            mn = min(mn, v[i]);
            mx = max(mx, v[i]);
            if (i != pref && v[i] < v[i - 1])
                isinc = false;
            if (i != pref && v[i] > v[i - 1])
                isdec = false;
            if(!isinc && !isdec) break;
            int mask = (1 << mn) | (1 << mx) | cover(mn, mx);
            if ((cover(mn, mx) & inc) == 0 && isinc)
            {
                if (!seen.count({i + 1, inc | mask, dec}))
                {
                    seen.insert({i + 1, inc | mask, dec});
                    q.emplace(i + 1, inc | mask, dec, res + 1);
                }
            }
            if ((cover(mn, mx) & dec) == 0 && isdec)
            {
                if (!seen.count({i+1, inc, dec | mask})){
                    seen.insert({i+1, inc, dec | mask});
                    q.emplace(i + 1, inc, dec | mask, res + 1);
                }
            }
        }
    }
    cout << ans << "\n";
    // cout << sz(seen) << "\n";
    return 0;
}

// asapoihegiowbnfmpzysonaisjrignaseifoijhqnasdkjoigd
