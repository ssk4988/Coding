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

struct Node
{
    Node *l = 0, *r = 0, *p = 0;
    int val, y, c = 1;
    ll sum = 0;
    Node(int val) : val(val), y(rand()), sum(val) {}
    void recalc();
};

int cnt(Node *n) { return n ? n->c : 0; }
ll sm(Node *n) { return n ? n->sum : 0; }
void Node::recalc()
{
    c = cnt(l) + cnt(r) + 1;
    if (l)
        l->p = this;
    if (r)
        r->p = this;
    sum = sm(l) + sm(r) + val;
}

template <class F>
void each(Node *n, F f)
{
    if (n)
    {
        each(n->l, f);
        f(n->val);
        each(n->r, f);
    }
}

pair<Node *, Node *> split(Node *n, int k)
{
    if (!n)
        return {};
    if (cnt(n->l) >= k)
    { // "n->val >= k" for lower_bound(k)
        auto pa = split(n->l, k);
        n->l = pa.second;
        n->recalc();
        if (pa.first)
            pa.first->p = NULL;
        if (n)
            n->p = NULL;
        return {pa.first, n};
    }
    else
    {
        auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
        n->r = pa.first;
        n->recalc();
        if (n)
            n->p = NULL;
        if (pa.second)
            pa.second->p = NULL;
        return {n, pa.second};
    }
}

Node *par(Node *n){
    if(!n) return NULL;
    if(n && !n->p) return n;
    return par(n->p);
}

Node *merge(Node *l, Node *r)
{
    if (!l)
    {
        if (r)
            r->p = NULL;
        return r;
    }
    if (!r)
    {
        if (l)
            l->p = NULL;
        return l;
    }
    if (l->y > r->y)
    {
        l->r = merge(l->r, r);
        l->recalc();
        if(l) l->p = NULL;
        return l;
    }
    else
    {
        r->l = merge(l, r->l);
        r->recalc();
        if(r) r->p = NULL;
        r->p = NULL;
        return r;
    }
}

Node *ins(Node *t, Node *n, int pos)
{
    auto pa = split(t, pos);
    return merge(merge(pa.first, n), pa.second);
}

// Example application: move the range [l, r) to index k
void move(Node *&t, int l, int r, int k)
{
    Node *a, *b, *c;
    tie(a, b) = split(t, l);
    tie(b, c) = split(b, r - l);
    if (k <= l)
        t = merge(ins(a, b, k), c);
    else
        t = merge(a, ins(c, b, k - r));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    unordered_map<int, Node*> v;
    int q; cin >> q;
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int y; cin >> y;
            v[i] = new Node(y);
        }
        else if(t == 2){
            int y, z; cin >> y >> z;
            y--,z--;
            Node *yp = par(v[y]), *zp = par(v[z]);
            if(yp == zp) continue;
            merge(yp, zp);
        }
        else if(t == 3){
            int y, z; cin >> y >> z; y--;
            Node *yp = par(v[y]);
            if(cnt(yp) <= z) continue;
            split(yp, z);
        }
        else{
            int y; cin >> y; y--;
            cout << par(v[y])->sum << nL;
        }
    }

    return 0;
}
