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

vi xorv(vi &l, vi &r)
{
    vi res;
    for (int a : l)
    {
        bool contains = false;
        for (int b : r)
        {
            if (a == b)
                contains = true;
        }
        if (!contains)
            res.pb(a);
    }
    for (int b : r)
    {
        bool contains = false;
        for (int a : l)
        {
            if (a == b)
                contains = true;
        }
        if (!contains)
            res.pb(b);
    }
    sort(all(res));
    return res;
}

ll m = 1e9+7;

ll mod(ll k){
    return k % m;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vvi v;
    rep(i, 0, n)
    {
        int l, r, parity;
        cin >> l >> r >> parity;
        int l1 = (i - l + n) % n;
        int r1 = (i + r) % n;
        vi a;
        if (l1 <= r1)
        {
            a.pb(l1);
            a.pb(r1 + 1);
        }
        else
        {
            vi l = {0, r1 + 1};
            vi r = {l1, n};
            a = xorv(l, r);
        }
        if (parity)
        {
            vi lastbit = {n + 1};
            a = xorv(a, lastbit);
        }
        sort(all(a));
        v.pb(a);
    }
    // v.pb({0}); // ??????
    vvi basis(n + 5); // should only need up to size n + 1 but just to be safe
    priority_queue<vi, vvi, greater<vi>> pq;
    for (vi a : v)
    {
        pq.push(a);
    }
    while (!pq.empty())
    {
        vi a = pq.top();
        pq.pop();
        if (a.size() == 0)
            continue;
        if (a.size() == 1 && a[0] == n + 1)
        { // unable to solve
            cout << 0 << nL;
            return 0;
        }

        if (basis[a[0]].size() == 0)
        {
            basis[a[0]] = a;
        }
        else
        {
            vi res = xorv(basis[a[0]], a);
            pq.push(res);
        }
    }

    int basissize = 0;
    ll ans = 1;
    rep(i, 0, n){
        if(basis[i].size() == 0){ // number of non-pivot/independent variables
            basissize++;
            ans = mod(ans * 2);
        }
    }
    cout << ans << nL;
    // cout << basissize << nL;

    return 0;
}
