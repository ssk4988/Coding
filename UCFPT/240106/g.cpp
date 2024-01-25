#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define sz(x) (int)x.size()

const int MOD = 1e9 + 7;
inline int mod(int k)
{
    return k % MOD;
}

inline int mod1(int k)
{
    return (k % MOD + MOD) % MOD;
}

struct Node
{
    shared_ptr<Node> l, r;
    int val, y, m;
    ll c = 1;
    Node(int val) : val(val), y(rand())
    {
        m = mod(val);
    }
    void push();
    void recalc();
};

inline ll cnt(shared_ptr<Node> n) { return n ? abs(n->c) : 0; }
inline int mval(shared_ptr<Node> n) { return n ? n->m : 0; }
shared_ptr<Node> makecopy(shared_ptr<Node> n, bool lazy = true)
{
    if (!n)
        return NULL;
    shared_ptr<Node> res = make_shared<Node>(n->val);
    res->l = n->l;
    res->r = n->r;
    res->recalc();
    if((lazy && res->c >= 0) || (!lazy && res->c < 0)) res->c *= -1;
    return res;
}
void Node::recalc()
{
    c = c / abs(c) * (cnt(l) + cnt(r) + 1);
    m = mod(val + mod(mval(l) + mval(r)));
}
void Node::push()
{
    if (c >= 0)
        return;
    l = makecopy(l);
    r = makecopy(r);
    c *= -1;
}

template <class F>
void each(shared_ptr<Node> n, F f)
{
    if (n)
    {
        n->push();
        each(n->l, f);
        f(n->val);
        each(n->r, f);
    }
}

pair<shared_ptr<Node>, shared_ptr<Node>> split(shared_ptr<Node> n, ll k)
{
    if (!n)
        return {};
    n->push();
    n = makecopy(n, false);
    if (cnt(n->l) >= k)
    {
        auto pa = split(n->l, k);
        n->l = pa.second;
        n->recalc();
        return {pa.first, n};
    }
    else
    {
        auto pa = split(n->r, k - cnt(n->l) - 1);
        n->r = pa.first;
        n->recalc();
        return {n, pa.second};
    }
}

shared_ptr<Node> merge(shared_ptr<Node> l, shared_ptr<Node> r)
{
    if (!l)
        return r;
    if (!r)
        return l;
    l->push();
    r->push();
    l = makecopy(l, false);
    r = makecopy(r, false);
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

shared_ptr<Node> splitcopy(shared_ptr<Node> &t, ll l, ll r)
{
    shared_ptr<Node> a, b, c;
    tie(a, b) = split(t, l);
    tie(b, c) = split(b, r - l);
    shared_ptr<Node> n = makecopy(b);
    t = merge(a, merge(b, c));
    return n;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int m = sz(s);
    shared_ptr<Node> root;
    rep(i, 0, m)
        root = merge(root, make_shared<Node>(s[i]));

    vector<shared_ptr<Node>> strs;
    strs.push_back(root);
    while (--n > 0)
    {
        string type;
        cin >> type;
        if (type == "SUB")
        {
            ll i, L, R;
            cin >> i >> L >> R;
            shared_ptr<Node> cre = splitcopy(strs[i], L, R);
            strs.push_back(cre);
        }
        else
        {
            ll a, b;
            cin >> a >> b;
            // a--, b--;
            shared_ptr<Node> n1 = makecopy(strs[a]), n2 = makecopy(strs[b]);
            n1 = merge(n1, n2);
            strs.push_back(n1);
        }
    }
    if (strs.back())
        cout << strs.back()->m << '\n';
    else
        cout << 0 << "\n";
    return 0;
}
