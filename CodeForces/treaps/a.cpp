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
    Node *l = 0, *r = 0;
    int val, y, c = 1;
    Node(int val) : val(val), y(rand()) {}
    void recalc();
};

int cnt(Node *n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

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
        return {pa.first, n};
    }
    else
    {
        auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
        n->r = pa.first;
        n->recalc();
        return {n, pa.second};
    }
}

Node *merge(Node *l, Node *r)
{
    if (!l)
        return r;
    if (!r)
        return l;
    if (l->y > r->y)
    {
        l->r = merge(l->r, r);
        l->recalc();
        return l;
    }
    else
    {
        r->l = merge(l, r->l);
        r->recalc();
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
void move2(Node *&t, int l, int r, int n)
{
    int intervallen = min(n - r, r - l);

    Node *a, *b, *c, *d, *e;
    tie(a, b) = split(t, l);
    tie(b, c) = split(b, intervallen);
    tie(c, d) = split(c, r - (l + intervallen));
    tie(d, e) = split(d, intervallen);
    t = merge(a, merge(d, merge(c, merge(b, e))));
}

void dfs(Node *cur){
    if(cur == NULL) return;
    dfs(cur->l);
    cout << cur->val << " ";
    dfs(cur->r);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    Node *treap;
    rep(i, 1, n + 1){
        treap = merge(treap, new Node(i));
    }
    rep(i, 0, n){
        int a, b; cin >> a >> b;
        a--,b--;
        if(a >= b) continue;
        move2(treap, a, b, n);
    }
    dfs(treap);
    return 0;
}
