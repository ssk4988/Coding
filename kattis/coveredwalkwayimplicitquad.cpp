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
struct Quad {
    ll m, b; // half-parabola with equation (x - m)^2 + b
    Quad(ll m = oo, ll b = oo) : m(m), b(b) {}
    ll operator()(ll x) { return x < m ? oo : (x - m) * (x - m) + b; }
};

struct Node {
    ll lo, hi;
    Quad best;
    Node *l = 0, *r = 0;
    Node(ll lo, ll hi) : lo(lo), hi(hi) {}
    void add(Quad cur, ll L, ll R){
        if (hi <= L || R <= lo) return;
        if (L <= lo && hi <= R) add(cur);
        else push(), l->add(cur, L, R), r->add(cur, L, R);
    }
    void add(Quad cur) {
        ll mid = lo + (hi - lo) / 2;
        if (cur(mid) < best(mid)) swap(best, cur);
        if(lo + 1 == hi) return;
        push();
        if (cur(lo) < best(lo)) l->add(cur);
        else r->add(cur);
    }
    ll query(ll x) {
        if (x < lo || hi <= x) return oo;
        if (!l) return best(x);
        return min({best(x), l->query(x), r->query(x)});
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
    int n; ll c; cin >> n >> c;
    vl x(n);
    const ll mxX = 1e9+10;
    Node tree(0, mxX);
    ll predp = 0;
    rep(i, 0, n){
        cin >> x[i];
    }
    rep(i, 0, n){
        tree.add(Quad(x[i], c + predp), x[i], mxX);
        predp = tree.query(x[i]);
    }
    cout << predp << "\n";

    
    return 0;
}
