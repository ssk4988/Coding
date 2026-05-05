#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct Node {
    Node *l = 0, *r = 0;
    ll g = 0;
    int lo, hi;
    Node(vl &a, int lo, int hi) : lo(lo), hi(hi) {
        if(lo+1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(a, lo, mid), r = new Node(a, mid, hi);
            g = gcd(l->g, r->g);
        } else g = a[lo];
    }
    Node* upd(int i, ll x) {
        Node *n = new Node(*this);
        if(lo + 1 == hi) {
            n->g = x;
            return n;
        }
        int mid = lo + (hi - lo) / 2;
        if(mid <= i) n->r = n->r->upd(i, x);
        else n->l = n->l->upd(i, x);
        n->g = gcd(n->l->g, n->r->g);
        return n;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q, d; cin >> n >> q >> d;
    vl ds(d);
    rep(i, 0, d) cin >> ds[i];
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    vector<Node*> trees;
    trees.push_back(new Node(a, 0, n));
    rep(qid, 0, q) {
        int t, u;
        ll x; cin >> t >> u >> x; u--;
        trees.push_back(trees[t]->upd(u, x));
    }
    for(auto p : trees) {
        ll g = p->g;
        ll ans = 0;
        for(auto x : ds) if(g % x == 0) ans += x;
        cout << ans << "\n";
    }
    
    return 0;
}
