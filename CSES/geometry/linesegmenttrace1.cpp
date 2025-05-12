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

const ll oo = 1e18;
struct Line {
    ll m, b; // mx + b
    Line(ll m = oo, ll b = oo) : m(m), b(b) {}
    ll operator()(ll x) {
        if(m == oo) return -oo;
        return m * x + b;
    }
};

struct Node {
    int lo, hi;
    Line best;
    Node *l = 0, *r = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {}
    void add(Line cur, int L, int R){
        if (hi <= L || R <= lo) return;
        if (L <= lo && hi <= R) {
            add(cur);
        } else push(), l->add(cur, L, R), r->add(cur, L, R);
    }
    void add(Line cur) {
        int mid = lo + (hi - lo) / 2;
        if (cur(mid) > best(mid)) swap(best, cur);
        if(lo + 1 == hi) return;
        push();
        if (cur(lo) > best(lo)) l->add(cur);
        else r->add(cur);
    }
    ll query(int x) {
        if (x < lo || hi <= x) return -oo;
        if (!l) return best(x);
        return max({best(x), l->query(x), r->query(x)});
    }
    void push() {
        if(!l) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    Node tree(0, m+1);
    rep(i, 0, n) {
        ll y1, y2; cin >> y1 >> y2;
        ll slope = (y2-y1)/m;
        tree.add(Line(slope, y1));
    }
    rep(i, 0, m+1) {
        cout << tree.query(i) << " ";
    }
    cout << "\n";
    
    return 0;
}
