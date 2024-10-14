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

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e)
{
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1)
            ans = ans * b % mod;
    return ans;
}

struct UF
{
    vpi e;
    int c;
    UF(int n) : e(n, {-1, -1}), c(n) {}
    pi find(int x)
    {
        if (e[x].f < 0)
            return {x, 0};
        auto [p, w] = find(e[x].f);
        return {p, w ^ e[x].s};
    }
    int dist(int a, int b)
    {
        int x, y;
        tie(a, x) = find(a), tie(b, y) = find(b);
        return x ^ y;
    }
    bool sameSet(int a, int b)
    {
        int x, y;
        tie(a, x) = find(a), tie(b, y) = find(b);
        return a == b;
    }
    bool join(int a, int b, int w)
    {
        int x, y;
        tie(a, x) = find(a), tie(b, y) = find(b);
        if (a == b)
            return false;
        if (e[a] > e[b])
            swap(a, b);
        e[a].f += e[b].f;
        e[b].f = a;
        e[b].s = w ^ x ^ y;
        c--;
        return true;
    }
};

void solve()
{
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    UF uf(n + m);
    bool works = true;
    rep(i, 0, k)
    {
        int r, c, v;
        cin >> r >> c >> v;
        r--, c--;
        c += n;
        if (uf.sameSet(r, c))
        {
            if (v != uf.dist(r, c))
                works = false;
        }
        else
        {
            uf.join(r, c, v);
        }
    }
    int base = 1 << 30;
    base %= mod;
    if (!works)
    {
        cout << 0 << "\n";
    }
    else
        cout << modpow(base, uf.c - 1) << "\n";
    rep(i, 0, q)
    {
        int r, c, v;
        cin >> r >> c >> v;
        r--, c--;
        c += n;
        if (uf.sameSet(r, c))
        {
            if (v != uf.dist(r, c))
                works = false;
        }
        else
        {
            uf.join(r, c, v);
        }
        if (!works)
        {
            cout << 0 << "\n";
        }
        else
            cout << modpow(base, uf.c - 1) << "\n";
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        solve();
    }

    return 0;
}
