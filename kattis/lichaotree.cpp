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

const ll inf = 1e18;
struct Func {
    ll m, b;
    Func(ll m = -inf, ll b = -inf) : m(m), b(b) {}
    ll operator()(ll x) {
        if (m == -inf) return -inf;
        return m * x + b;
    }
};

struct Node {
    int lo, hi;
    Node *l = 0, *r = 0;
    Func f;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    void add(Func g) { add(g, lo, hi); }
    void add(Func g, int L, int R) {
        if (R <= lo || hi <= L) return;
        int mid = lo + (hi - lo) / 2;
        if(f(mid) < g(mid)) swap(f, g);
        if(f(lo) > g(lo)) r->add(g);
        else l->add(g);
    }
    ll query(int x) {
        int mid = lo + (hi - lo) / 2;
        return max(f(x), mid <= x ? r->query(x) : l->query(x));
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    
    return 0;
}
