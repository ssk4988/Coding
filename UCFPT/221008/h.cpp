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

int n = 0;
int pow2 = 0;
int c[2];
vector<pair<pi, bool>> p;
vvi segtree;
// 0 max subarray
// 1 max prefix
// 2 max suffix
// 3 sum

void update(int idx, int val)
{
    idx += pow2;
    rep(i, 0, 4) segtree[idx][i] = val;
    int p, l, r;
    for (; idx > 1; idx >>= 1)
    {
        p = idx >> 1;
        l = (idx & 1) ? idx ^ 1 : idx;
        r = l ^ 1;
        segtree[p][3] = segtree[l][3] + segtree[r][3];
        segtree[p][2] = max(segtree[r][2], segtree[l][2] + segtree[r][3]);
        segtree[p][1] = max(segtree[l][1], segtree[r][1] + segtree[l][3]);
        segtree[p][0] = max(max(segtree[l][0], segtree[r][0]), segtree[l][2] + segtree[r][1]);
    }
}

// int query(int l, int r)
// {
//     int segsz = sz(segtree) / 2;
//     int res = 0;
//     for (l += segsz, r += segsz; l <= r; l >>= 1, r >>= 1)
//     {
//         if (l & 1)
//             res = max(res, segtree[l++]);
//         if (!(r & 1))
//             res = max(res, segtree[r--]);
//     }
//     return res;
// }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    rep(m, 0, 2)
    {
        int l;
        cin >> l;
        n += l;
        rep(i, 0, l)
        {
            int a, b;
            cin >> a >> b;
            p.pb(mp(mp(a, b), m));
        }
    }

    sort(all(p));
    rep(i, 0, 2)
    {
        cin >> c[i];
    }
    c[1] *= -1;
    vector<pair<int, int>> pairs(n);
    for (int i = 0; i < n; ++i)
    {
        pairs[i] = {p[i].f.s, i};
    }
    sort(pairs.begin(), pairs.end());
    int nxt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i > 0 && pairs[i - 1].first != pairs[i].first)
            nxt++;
        p[pairs[i].second].f.s = nxt;
    }
    pow2 = 1;
    while (pow2 < n + 1)
    {
        pow2 <<= 1;
    }
    int ans = 0;
    rep(i, 0, n)
    {
        segtree = vvi(2 * pow2, vi(4, 0));
        rep(j, i, n)
        {
            update(p[j].f.s, c[p[j].s]);
            ans = max(ans, segtree[1][0]);
        }
    }
    cout << ans;

    return 0;
}