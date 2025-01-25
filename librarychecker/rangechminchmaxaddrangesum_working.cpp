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
struct Node {
    int lo, hi;
    Node *l=0, *r=0;
    ll sum = 0, mx = -inf, mxfreq = 0, mn = inf, mnfreq = 0, mx2 = -inf, mn2 = inf;
    ll lzmx = 0, lzmn = 0, lzadd = 0;
    // if mx == mn, lzmn = 0
    Node(vl& v, int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid), r = new Node(v, mid, hi); merge();
        } else {
            sum = mx = mn = v[lo];
            mxfreq = mnfreq = 1;
        }
    }
    // change values of v by dv
    void tag(ll v, ll dv) {
        if(!dv) return;
        if(mn == v) {
            if(mn != mx) lzmn += dv, sum += dv * mnfreq;
            mn += dv;
        }
        if(mx == v) mx += dv, lzmx += dv, sum += dv * mxfreq;
        if(mn2 == v) mn2 += dv;
        if(mx2 == v) mx2 += dv;
    }
    void merge() {
        sum = l->sum + r->sum;
        mx = l->mx, mxfreq = l->mxfreq;
        mn = l->mn, mnfreq = l->mnfreq;
        mx2 = -inf, mn2 = inf;
        if(r->mx > mx) {
            mx2 = max(mx2, mx);
            mx = r->mx, mxfreq = r->mxfreq;
        } else if(r->mx == mx) mxfreq += r->mxfreq;
        if(r->mn < mn) {
            mn2 = min(mn2, mn);
            mn = r->mn, mnfreq = r->mnfreq;
        } else if(r->mn == mn) mnfreq += r->mnfreq;
        for(auto p : vector{l, r}) {
            for(auto v : {p->mn, p->mx, p->mn2, p->mx2}) {
                if(abs(v)==inf) continue;
                if(v != mx) mx2 = max(mx2, v);
                if(v != mn) mn2 = min(mn2, v);
            }
        }
    }
    void push() {
        if(!l) return;
        if(lzmx == 0 && lzmn == 0 && lzadd == 0) return;
        if(lzadd != 0) {
            l->add(lo, hi, lzadd), r->add(lo, hi, lzadd), lzadd = 0;
        }
        if(lzmx != 0) {
            l->tag(mx-lzmx, lzmx), r->tag(mx-lzmx, lzmx), lzmx = 0;
        }
        if(lzmn != 0) {
            l->tag(mn-lzmn, lzmn), r->tag(mn-lzmn, lzmn), lzmn = 0;
        }
    }
    ll rangesum(int L, int R) {
        if(R <= lo || hi <= L) return 0;
        if(L <= lo && hi <= R) return sum;
        push();
        return l->rangesum(L, R) + r->rangesum(L, R);
    }
    void chmax(int L, int R, ll x) {
        if(R <= lo || hi <= L || mn >= x) return;
        if(L <= lo && hi <= R && mn2 > x) {
            return tag(mn, x - mn);
        }
        push(), l->chmax(L, R, x), r->chmax(L, R, x); merge();
    }
    void chmin(int L, int R, ll x) {
        if(R <= lo || hi <= L || mx <= x) return;
        if(L <= lo && hi <= R && mx2 < x) {
            return tag(mx, x - mx);
        }
        push(), l->chmin(L, R, x), r->chmin(L, R, x); merge();
    }
    void add(int L, int R, ll x) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            sum += (hi - lo) * x;
            mx += x;
            mn += x;
            if(mn2 != inf) mn2 += x;
            if(mx2 != -inf) mx2 += x;
            lzadd += x;
            return;
        }
        push(), l->add(L, R, x), r->add(L, R, x);
        merge();
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    Node tree(a, 0, n);
    rep(i, 0, q){
        // cerr << "dbg: " << tree.rangesum(0, n) << endl;
        int t, l, r; cin >> t >> l >> r;
        if(t == 3) {
            cout << tree.rangesum(l, r) << "\n";
            continue;
        }
        ll b; cin >> b;
        if(t == 0) tree.chmin(l, r, b);
        else if(t == 1) tree.chmax(l, r, b);
        else tree.add(l, r, b);
    }
    return 0;
}
