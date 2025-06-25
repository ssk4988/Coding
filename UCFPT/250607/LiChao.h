struct line {
    ll m, b;
    line(ll m = 0, ll b = LLONG_MAX): m(m), b(b) {}
    ll operator() (ll x) { return m * x + b;}
};

struct node {
    int lo, md, hi;
    line f;
    node *left, *right;
    node(int L, int R) : lo(L), md((L+R)>>1), hi(R) {
        if(lo == hi) return;
        left = new node(lo, md);
        right = new node(md+1, hi);
    }
    void update(line g) {
        if(g(md) < f(md)) swap(f, g);
        if(lo == hi) return;
        if(f(lo) <= g(lo) && f(hi) <= g(hi)) return;
        if(f(lo) > g(lo)) left->update(g);
        else right->update(g);
    }
    ll query(ll x) {
        if(lo == hi) return f(x);
        return min(f(x), (x <= md ? left : right)->query(x));
    }
};
