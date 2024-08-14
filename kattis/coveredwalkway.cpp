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
    ll operator()(ll x) {
        if(m == oo) return -oo;
        return m * x + b;
    }
};
vl x;
struct Node {
    int lo, hi;
    Line best;
    Node *l = 0, *r = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    void add(int L, int R, Line cur){
        if (hi <= L || R <= lo) return;
        int mid = lo + (hi - lo) / 2;
        if (cur(x[mid]) > best(x[mid])) {
            swap(best, cur);
        }
        if (lo + 1 == hi) return;
        if (cur(x[lo]) > best(x[lo])) l->add(L, R, cur);
        else r->add(L, R, cur);
    }
    ll query(int p) {
        if (p < lo || hi <= p) return -oo;
        if (lo + 1 == hi) return best(x[p]);
        return max({best(x[p]), l->query(p), r->query(p)});
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll c; cin >> n >> c;
    x.resize(n);
    rep(i, 0, n){
        cin >> x[i];
    }
    Node tree(0, n);
    ll predp = 0;
    rep(i, 0, n){
        tree.add(0, n, Line(2 * x[i], -(predp + x[i] * x[i])));
        predp = c + x[i] * x[i] - tree.query(i);
    }
    cout << predp << "\n";

    
    return 0;
}
