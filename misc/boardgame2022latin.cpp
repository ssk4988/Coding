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

const ll oo = 1e18;
struct Line {
    ll m, b; // mx + b
    Line(ll m = oo, ll b = oo) : m(m), b(b) {}
    ll operator()(ll x) { return m == oo ? -oo : m * x + b; }
};

struct Node {
    ll lo, hi;
    Line best;
    Node *l = 0, *r = 0;
    Node(ll lo, ll hi) : lo(lo), hi(hi) {}
    Node* add(Line cur) {
        ll mid = lo + (hi - lo) / 2;
        Node *n = new Node(*this);
        if (cur(mid) > n->best(mid)) swap(n->best, cur);
        if(lo + 1 == hi) return n;
        n->push();
        if (cur(lo) > n->best(lo)) n->l = n->l->add(cur);
        else n->r = n->r->add(cur);
        return n;
    }
    ll query(ll x) {
        if (x < lo || hi <= x) return -oo;
        if (!l) return best(x);
        return max({best(x), l->query(x), r->query(x)});
    }
    void push() {
        if(!l) {
            ll mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n;
    vpl chips(n);
    rep(i, 0, n){
        cin >> chips[i].f >> chips[i].s;
    }
    cin >> q;
    vpl lines(q);
    vector<Node*> trees;
    trees.pb(new Node(-1e9-10, 1e9+10));
    rep(i, 0, q) {
        cin >> lines[i].f >> lines[i].s;
        trees.pb(trees.back()->add(Line(lines[i].f, lines[i].s)));
    }
    vi ans(n, -1);
    for(int dif = 1 << 20; dif; dif /= 2) {
        rep(i, 0, n){
            if(ans[i] + dif < sz(trees) && trees[ans[i] + dif]->query(chips[i].f) <= chips[i].s){
                ans[i] += dif;
            }
        }
    }
    vvi res(q);
    rep(i, 0, n){
        // ans[i]++;
        if(ans[i] < q){
            res[ans[i]].pb(i);
        }
    }
    rep(i, 0, q){
        cout << sz(res[i]) << " ";
        for(int j : res[i]) cout << j+1 << " ";
        cout << "\n";
    }
    
    return 0;
}
