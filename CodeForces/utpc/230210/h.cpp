#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;
unordered_map<int, int> rl, ml;
struct Node
{
    int lo, hi;
    Node *l = 0, *r = 0;
    ll val = 0, lzadd = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {}
    ll query(int L, int R)
    {
        if (hi <= L || R <= lo)
            return 0;
        if (L <= lo && hi <= R)
        {
            return val;
        }
        else
        {
            push();
            return l->query(L, R) + r->query(L, R);
        }
    }
    void add(int L, int R, ll x)
    {
        if (hi <= L || R <= lo)
            return;
        if (L <= lo && hi <= R)
        {
            val += (ml[hi] - ml[lo]) * x;
            lzadd += x;
        }
        else
        {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = l->val + r->val;
        }
    }
    void push()
    {
        if (!l && lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
        if (lzadd)
        {
            l->add(lo, hi, lzadd), r->add(lo, hi, lzadd);
            lzadd = 0;
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    set<int> cc;

    vector<array<ll, 4>> rs;
    rep(i, 0, n)
    {
        ll r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        rs.push_back({r1, c1, r2, c2});
        cc.insert(c1);
        cc.insert(c2);
        cc.insert(c2 + 1);
        // tree.add(c1, c2 + 1, (r2 - r1 + 1));
    }
    // cout << ans << "\n";
    vector<ll> ws(m);
    rep(i, 0, m)
    {
        cin >> ws[i];
        cc.insert(ws[i]);
        cc.insert(ws[i] + 1);
        // tree.add(w, w + 1, -tree.query(w, w + 1));
        // ll v = tree.query(w, w + 1);
        // cout << "rem: " << w << " " << v << "\n";
        // ans -= v;
    }
    for (int i : cc)
    {
        rl[i] = sz(rl);
        ml[rl[i]] = i;
    }
    Node tree(0, sz(rl) + 100);
    for (auto [r1, c1, r2, c2] : rs)
    {
        tree.add(rl[c1], rl[c2 + 1], (r2 - r1 + 1));
    }
    ll ans = tree.val;
    for (ll w : ws)
    {
        ll v = tree.query(rl[w], rl[w + 1]);
        // cout << "rem: " << w << " " << v << "\n";
        ans -= v;
    }
    cout << ans << "\n";
}
