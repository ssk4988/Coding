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

#pragma GCC optimize("Ofast")



struct datastruct {
    ll sum, pref, suff, ans;
};

datastruct t[800'500];

datastruct combine(datastruct &l, datastruct &r) {
    datastruct res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
}

datastruct make_data(ll val) {
    datastruct res;
    res.sum = val;
    res.pref = res.suff = res.ans = max(0LL, val);
    return res;
}

void build(vl &a, ll v, ll tl, ll tr) {
    if (tl == tr) {
        t[v] = make_data(a[tl]);
    } else {
        ll tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

void update(ll v, ll tl, ll tr, ll pos, ll new_val) {
    if (tl == tr) {
        t[v] = make_data(new_val);
    } else {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

datastruct query(ll v, ll tl, ll tr, ll l, ll r) {
    // cout << tl << " " << tr << " " << l << " " << r << nL;
    if (l > r) 
        return make_data(0);
    if (l == tl && r == tr) 
        return t[v];
    ll tm = (tl + tr) / 2;
    datastruct lv = query(v*2, tl, tm, l, min(r, tm)), rv = query(v*2+1, tm+1, tr, max(l, tm+1), r);
    return combine(lv, rv);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    build(a, 1, 0, n - 1);

    rep(i, 0, m){
        int k, x; cin >> k >> x; k--;
        update(1, 0, n - 1, k, x);
        cout << query(1, 0, n - 1, 0, n - 1).ans << nL;
    }



    
    return 0;
}