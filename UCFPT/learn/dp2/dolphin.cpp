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

void maxupdate(vi& segtree, int idx, int val)
{
    int segsz = sz(segtree) / 2;
    idx += segsz;
    segtree[idx] = val;
    for (; idx > 1; idx >>= 1)
    {
        segtree[idx >> 1] = max(segtree[idx], segtree[idx ^ 1]);
    }
}

int maxquery(vi& segtree, int l, int r)
{
    int segsz = sz(segtree) / 2;
    int res = 0;
    for (l += segsz, r += segsz; l <= r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res = max(res, segtree[l++]);
        if (!(r & 1))
            res = max(res, segtree[r--]);
    }
    return res;
}

void minupdate(vi& segtree, int idx, int val)
{
    int segsz = sz(segtree) / 2;
    idx += segsz;
    segtree[idx] = val;
    for (; idx > 1; idx >>= 1)
    {
        segtree[idx >> 1] = min(segtree[idx], segtree[idx ^ 1]);
    }
}

int minquery(vi& segtree, int l, int r)
{
    int segsz = sz(segtree) / 2;
    int res = 0;
    for (l += segsz, r += segsz; l <= r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res = min(res, segtree[l++]);
        if (!(r & 1))
            res = min(res, segtree[r--]);
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        int inc[n], dec[n], a[n];
        vi incseg(2 * n);
        set<int> aset;
        unordered_map<int, int> m;
        rep(i, 0, n){
            cin >> a[i];
            aset.insert(a[i]);
        }
        int idx = 0;
        for(auto& a1 : aset){
            m[a1] = idx++;
        }
        rep(i, 0, n){
            a[i] = m[a[i]];
        }
        rep(i, 0, n){
            maxupdate(incseg, a[i], 1 + maxquery(incseg, 0, a[i]));
            inc[i] = maxquery(incseg, 0, n - 1);
        }
        fill(all(incseg), 0);
        for(int i = n - 1; i >= 0; i--){
            maxupdate(incseg, a[i], 1 + maxquery(incseg, 0, a[i]));
            dec[i] = maxquery(incseg, 0, n - 1);
        }
        int ans = 0;
        rep(i, 0, n){
            int ans1 = inc[i];
            if(i + 1 < n) ans1 += dec[i + 1];
            ans = max(ans, ans1);
        }
        cout << "Case " << (cn + 1) << ":\n";
        cout << "Dynamo ate " << ans << " food pellet(s)." << nL << nL;
    }
    
    return 0;
}