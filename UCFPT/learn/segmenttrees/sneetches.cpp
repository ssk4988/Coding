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

const int inf = 1e9;
struct sub
{
    int best, sum, pref, suff;
};

struct Node
{
    Node *l = 0, *r = 0;
    int lo, hi, flip = 0;
    sub s{0, 0, 0, 0}, p{0, 0, 0, 0};
    Node(string &v, int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            s = comb(l->s, r->s), p = comb(l->p, r->p);
        }
        else
        {
            if(v[lo] == 'S') s.best = s.sum = s.pref = s.suff = 1;
            else{
                p.best = p.sum = p.pref = p.suff = 1;
            }
        }
    }
    sub comb(sub a, sub b)
    {
        sub res{max(a.suff + b.pref, max(a.best, b.best)), a.sum + b.sum, a.pref, b.suff};
        if (a.sum == l->hi - l->lo) res.pref = a.sum + b.pref;
        if (b.sum == r->hi - r->lo) res.suff = b.sum + a.suff;
        return res;
    }
    void add(int L, int R)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R)
        {
            flip ^= 1;
            swap(p, s);
        }
        else
        {
            push(), l->add(L, R), r->add(L, R);
            s = comb(l->s, r->s), p = comb(l->p, r->p);
        }
    }
    void push()
    {
        if (flip)
            l->add(lo, hi), r->add(lo, hi), flip = 0;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, q; cin >> n >> q;
        string str; cin >> str;
        Node tree(str, 0, n);
        rep(i, 0, q){
            int a, b; cin >> a >> b; a--, b--;
            tree.add(a, b + 1);
            cout << tree.s.best << " " << tree.p.best << nL;
        }
    }
    return 0;
}
