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

vl pows;
ll base = 29;
ll MOD = 1e9 + 7;
ll mod(ll k)
{
    return (k % MOD + MOD) % MOD;
}

struct Node
{
    Node *l = 0, *r = 0;
    int val, y, c = 1;
    ll hash, rhash;
    Node(int val) : val(val), y(rand()), hash(val), rhash(val) {}
    void recalc();
};

int cnt(Node *n) { return n ? n->c : 0; }
ll hsh(Node *n) { return n ? n->hash : 0; }
ll rhsh(Node *n) { return n ? n->rhash : 0; }
void Node::recalc()
{
    c = cnt(l) + cnt(r) + 1;
    hash = mod(hsh(l) + mod(mod(pows[cnt(l)] * val) + mod(pows[cnt(l) + 1] * hsh(r))));
    rhash = mod(rhsh(r) + mod(mod(pows[cnt(r)] * val) + mod(pows[cnt(r) + 1] * rhsh(l))));
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
void del(Node *&t, int l, int r)
{
    Node *a, *b, *c;
    tie(a, b) = split(t, l);
    tie(b, c) = split(b, r - l);
    t = merge(a, c);
}

bool pal(Node *&t, int l, int r)
{
    Node *a, *b, *c;
    tie(a, b) = split(t, l);
    tie(b, c) = split(b, r - l);
    bool cond = hsh(b) == rhsh(b);
    t = merge(a, merge(b, c));
    return cond;
}

void dfs(Node *cur)
{
    if (cur == NULL)
        return;
    dfs(cur->l);
    cout << cur->val << " ";
    dfs(cur->r);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int LIM = 3e5 + 100;
    pows.pb(1);
    rep(i, 0, LIM)
    {
        pows.pb(mod(base * pows.back()));
    }
    int n, q;
    cin >> n >> q;
    string str;
    cin >> str;
    Node *treap = NULL;
    rep(i, 0, n)
    {
        treap = merge(treap, new Node(1 + str[i] - 'a'));
    }
    rep(i, 0, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            del(treap, l, r + 1);
        }
        else if (t == 2)
        {
            cin >> str;
            int k;
            cin >> k;
            k--;
            ins(treap, new Node(1 + str[0] - 'a'), k);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            bool cond = pal(treap, l, r + 1);
            cout << (cond ? "yes" : "no") << nL;
        }
    }
    // dfs(treap);
    return 0;
}
