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

const ll inf = 1e18;
struct Node
{
    Node *l = 0, *r = 0;
    int lo, hi;
    ll mset = 0, madd = 0, val = -inf, timer = 0;
    ll nex42 = 1;
    Node(vl &v, int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            val = comb(l->val, r->val);
            timer = min(l->timer, r->timer);
        }
        else
        {
            val = v[lo];
            while(nex42 <= val) nex42 *= 42;
            timer = nex42 - val;
        }
    }
    ll comb(ll i1, ll i2)
    {
        if (i1 == i2)
            return i1;
        return 0;
    }
    ll pointquery(int idx)
    {
        int L = idx, R = idx + 1;
        if (R <= lo || hi <= L)
            return 0;
        if (L <= lo && hi <= R)
            return val;
        push();
        return max(l->pointquery(idx), r->pointquery(idx));
    }
    ll minquery(int L, int R) {
    	if (R <= lo || hi <= L) return inf;
    	if (L <= lo && hi <= R && val != 0) return timer;
    	push();
    	return min(l->minquery(L, R), r->minquery(L, R));
    }
    void setv(int L, int R, ll x)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R){
            mset = val = x, madd = 0;
            nex42 = 1;
            while(nex42 <= val) nex42 *= 42;
            timer = nex42 - val;
        }
        else
        {
            push(), l->setv(L, R, x), r->setv(L, R, x);
            val = comb(l->val, r->val);
            timer = min(l->timer, r->timer);
        }
    }
    void varadd(int L, int R, ll x)
    {
        add(L, R, x);
        while(minquery(L, R) == 0){
            add(L, R, x);
        }
    }
    void add(int L, int R, ll x)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R)
        {
            if (mset != 0)
                mset += x;
            else
                madd += x;
            if(val != 0){
                val += x;
                while(nex42 < val) nex42 *= 42;
                timer = nex42 - val;
            }
        }
        else
        {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = comb(l->val, r->val);
            timer = min(l->timer, r->timer);
        }
    }
    void push()
    {
        if (mset != 0)
            l->setv(lo, hi, mset), r->setv(lo, hi, mset), mset = 0;
        else if (madd)
            l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
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
            else
                tree->varadd(a, b, x);
        }
    }

    return 0;
}
