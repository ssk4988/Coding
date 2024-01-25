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

const ll inf = 1e18;
struct Flow
{
    ll score, add, sat, out;
    // score - how much wine already
    // add - how much can add by more input
    // sat - how much after add can we add before blocked from output
    // out - how much flowing out now
    Flow(ll a = 0, ll b = 0, ll c = 0)
    {
        ll rem = min(a, b);
        score = rem;
        a -= rem, b -= rem;
        out = min(c, a);
        add = b;
        sat = c - out;
    }
};

Flow operator+(Flow l, Flow r)
{
    Flow res;
    res.score = l.score + r.score;
    ll comb = min(l.out, r.add);
    res.score += comb;
    l.out -= comb;
    r.add -= comb;
    comb = min(l.out, r.sat);
    l.out -= comb;
    r.sat -= comb;
    res.out = min(inf, comb + r.out);
    comb = min(l.sat, r.add);
    res.add = l.add + comb;
    l.sat -= comb;
    r.add -= comb;
    res.sat = min(l.sat, r.sat);
    return res;
}

struct Node
{
    Node *l = 0, *r = 0;
    int lo, hi;
    Flow val;
    Node(int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
            val = l->val + r->val;
        }
    }
    void set(int idx, ll a, ll b, ll c)
    {
        if (idx + 1 <= lo || hi <= idx)
            return;
        if (idx <= lo && hi <= idx + 1)
        {
            val = Flow(a, b, c);
        }
        else
        {
            int mid = lo + (hi - lo) / 2;
            if (mid <= idx)
                r->set(idx, a, b, c);
            else
                l->set(idx, a, b, c);
            // push(), l->set(idx, a, b, c), r->set(idx, a, b, c);
            val = l->val + r->val;
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int nc; cin >> nc;
    // rep(cn, 0, nc){
    int n, q;
    cin >> n >> q;
    vl a(n), b(n), c(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];
    rep(i, 0, n - 1) cin >> c[i];
    Node tree(0, n);
    rep(i, 0, n)
    {
        tree.set(i, a[i], b[i], c[i]);
    }
    rep(i, 0, q)
    {
        ll p, x, y, z;
        cin >> p >> x >> y >> z;
        p--;
        tree.set(p, x, y, z);
        cout << tree.val.score << "\n";
    }
    // }

    return 0;
}
