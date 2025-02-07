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

ll maxN = 2e5 + 100;

vl p42{1};

const ll inf = 1e18;
struct Node
{
    Node *l = 0, *r = 0;
    int lo, hi;
    ll lzadd = 0, mn = inf, mx = -inf, nex = inf, mset = inf;
    void pull() {
        if(!l) return;
        mn = min(l->mn, r->mn);
        mx = max(l->mx, r->mx);
        nex = min(l->nex, r->nex);
    }
    Node(vl &v, int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            pull();
        }
        else
        {
            mn = mx = v[lo];
            nex = *upper_bound(all(p42), v[lo]) - v[lo];
        }
    }
    ll pointquery(int idx)
    {
        if (lo + 1 == hi)
            return mn;
        push();
        int mid = lo + (hi - lo) / 2;
        if(mid <= idx) return r->pointquery(idx);
        return l->pointquery(idx);
    }
    void setv(int L, int R, ll x)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R){
            mset = mx = mn = x, lzadd = 0;
            nex = *lower_bound(all(p42), x) - x;
            add(L, R, 0);
        }
        else
        {
            push(), l->setv(L, R, x), r->setv(L, R, x);
            pull();
        }
    }
    int add(int L, int R, ll x)
    {
        if (R <= lo || hi <= L)
            return 0;
        if (L <= lo && hi <= R && (x < nex || mn == mx))
        {
            if(mset != inf) mset += x;
            else lzadd += x;
            mn += x; mx += x;
            if(x < nex) {
                nex -= x;
                return 0;
            }
            assert(mn == mx);
            int res = nex == x;
            nex = *upper_bound(all(p42), mn) - mn;
            return res;
        }
        else
        {
            push();
            int res = l->add(L, R, x) + r->add(L, R, x);
            pull();
            return res;
        }
    }
    void push()
    {
        if (mset != inf)
            l->setv(lo, hi, mset), r->setv(lo, hi, mset), mset = inf;
        else if (lzadd)
            l->add(lo, hi, lzadd), r->add(lo, hi, lzadd), lzadd = 0;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q;
    cin >> n >> q;
    vl v(n);
    rep(i, 0, n) cin >> v[i];
    while(p42.back() * 42 < 1e17) p42.push_back(p42.back() * 42);

    Node *tree = new Node(v, 0, n);
    rep(i, 0, q)
    {
        int t, a, b, x;
        cin >> t >> a;
        a--;
        if (t == 1)
        {
            cout << tree->pointquery(a) << nL;
        }
        else
        {
            cin >> b >> x;
            if (t == 2)
                tree->setv(a, b, x);
            else {
                int res = tree->add(a, b, x);
                while(res) {
                    res = tree->add(a, b, x);
                }

            }
        }
    }

    return 0;
}
