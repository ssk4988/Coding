#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }

};
struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b); 
    }
    bool isect(iterator x, iterator y) {
        if(y == end()) return x->p = inf, 0;
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

struct line {
    ll m, b;
    line(ll m = 0, ll b = LLONG_MAX): m(m), b(b) {}
    ll operator() (ll x) { return m * x + b;}
};

struct node {
    ll lo, md, hi;
    line f;
    node *left=0, *right=0;
    node(ll L, ll R) : lo(L), md((L+R)>>1), hi(R) {
        if(lo == hi) return;
        // left = new node(lo, md);
        // right = new node(md+1, hi);
    }
    void update(line g) {
        if(g(md) < f(md)) swap(f, g);
        if(lo == hi) return;
        push();
        if(f(lo) <= g(lo) && f(hi) <= g(hi)) return;
        if(f(lo) > g(lo)) left->update(g);
        else right->update(g);
    }
    void push() {
        if(lo == hi) return;
        if(!left) {
            left = new node(lo, md);
            right = new node(md+1, hi);
        }
    }
    void update(ll L, ll R, line g) {
        // cerr << "at " << L << " " << R << " " << lo << " " << hi << endl;
        if(hi < L || R < lo) return;
        if(L <= lo && hi <= R) {return update(g);}
        push();
        left->update(L, R, g), right->update(L, R, g);
    }
    ll query(ll x) {
        if(lo == hi) return f(x);
        push();
        return min(f(x), (x <= md ? left : right)->query(x));
    }
};



int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; ll req; cin >> n >> req;
    vl w{0}, d{0};
    rep(i, 0, n) {
        ll a, b; cin >> a >> b;
        d.push_back(d.back() + a);
        w.push_back(w.back() + b);
    }
    node tree(0, d.back()+req);
    tree.update(0, req, line(0, 0));
    rep(i, 1, n+1) {
        ll cur = tree.query(w[i]) + w[i] * w[i];
        cerr << i << " " << cur << endl;
        if(i == n) {
            cout << cur << "\n";
        }
        tree.update(d[i], d[i] + req, line(-2 * w[i], cur + w[i] * w[i]));
    }




    return 0;
}
