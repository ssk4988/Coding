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

void pointupdate(vi &segtree, int idx, int val)
{
    int segsz = sz(segtree) / 2;
    idx += segsz;
    segtree[idx] = val;
    for (; idx > 1; idx >>= 1)
    {
        segtree[idx >> 1] = (segtree[idx] + segtree[idx ^ 1]);
    }
}

int query(vi &segtree, int l, int r)
{
    int segsz = sz(segtree) / 2;
    int res = 0;
    for (l += segsz, r += segsz; l <= r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res = (res + segtree[l++]);
        if (!(r & 1))
            res = (res + segtree[r--]);
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;
    int gp = 1;
    int n = str.length();
    while (gp < n + 1)
    {
        gp *= 2;
    }
    vvi segtree(64, vi(gp * 2, 0));
    int start = 0;
    pointupdate(segtree[start], 0, 1);
    rep(i, 1, n + 1)
    {
        start ^= 1 << (str[i - 1] - 'a');
        pointupdate(segtree[start], i, 1);
    }
    int q;
    cin >> q;

    rep(i, 0, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            l--;
            ll ans = 0;
            rep(j, 0, 1 << 6)
            {
                ll k = query(segtree[j], l, r);
                ans += k * (k - 1) / 2;
            }
            cout << ans << nL;
        }
        else
        {
            int idx;
            char c;
            cin >> idx >> c;
            int nval[1 << 6];
            int b = 0 ^ (1 << (c - 'a')) ^ (1 << (str[idx - 1] - 'a'));
            rep(j, idx, n + 1)
            {
                rep(k, 0, 1 << 6)
                {
                    nval[k ^ b] = segtree[k][j + gp];
                }
                rep(k, 0, 1 << 6)
                {
                    pointupdate(segtree[k], j, nval[k]);
                }
            }
        }
    }

    return 0;
}