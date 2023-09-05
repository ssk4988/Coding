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

int inited = 0;

struct PST
{
    PST *l = 0, *r = 0;
    int lo, hi;
    int has1 = 0, sum1 = 0;
    PST(int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new PST(lo, mid);
            r = new PST(mid, hi);
        }
        inited++;
    }
    PST(PST *n) : lo(n->lo), hi(n->hi), has1(n->has1), sum1(n->sum1)
    {
        l = n->l;
        r = n->r;
        inited++;
    }
    // int pointquery(int idx) {
    // 	if (idx <= lo && hi <= idx + 1) return val;
    //     int mid = lo + (hi - lo)/2;
    //     if(mid <= idx) return r->pointquery(idx);
    //     else return l->pointquery(idx);
    // }
    // int query(int L, int R)
    // {
    //     if (R < lo || hi < L)
    //         return 0; // idempotent
    //     if (L <= lo && hi <= R)
    //         return val;
    //     return l->query(L, R) + r->query(L, R);
    // }
    PST *add(int L)
    {
        PST *n = new PST(this);
        if (L <= lo && hi <= L + 1)
        {

            n->sum1 += (n->has1 == 0);
            n->has1 += (n->has1 == 0);
        }
        else
        {
            if(lo + (hi - lo) / 2 <= L)n->r = r->add(L);
            else n->l = l->add(L);
            n->sum1 = n->has1 + n->l->sum1 + n->r->sum1;
        }
        return n;
    }
};

struct root
{
    PST *r = NULL;
    root *pre = NULL;
    root(PST *v, root *p = NULL) : r(v), pre(p) {}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q;
    cin >> q;
    vector<root *> roots;

    roots.pb(new root(new PST(0, 1e6 + 1)));
    rep(i, 0, q)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int x;
            cin >> x;
            root *r = new root(roots.back()->r->add(x), roots.back());
            roots.pb(r);
        }
        if (c == '-')
        {
            int k;
            cin >> k;
            root *cur = roots.back();
            rep(j, 0, k) cur = cur->pre;
            roots.pb(cur);
        }
        if (c == '!')
            roots.pop_back();
        if (c == '?')
        {
            cout << roots.back()->r->sum1 << nL;
        }
    }
    // cout << inited << nL;

    return 0;
}
