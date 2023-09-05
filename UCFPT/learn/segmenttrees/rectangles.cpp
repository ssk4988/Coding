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

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, flip = 0, val = 0;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void add(int L, int R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			flip ^= 1;
			val = hi - lo - val;
		}
		else {
			push(), l->add(L, R), r->add(L, R);
			val = l->val + r->val;
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (flip)
			l->add(lo,hi), r->add(lo,hi), flip = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    Node tree(0, 1e9);
    int n; cin >> n;
    using a3 = array<int, 3>;
    vector<a3> qs;
    rep(i, 0, n){
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        qs.pb({x1, y1, y2});
        qs.pb({x2, y1, y2});
    }
    sort(all(qs));
    ll ans = 0;
    rep(i, 0, sz(qs)){
        auto [x, y1, y2] = qs[i];
        tree.add(y1, y2);
        if(i + 1 < sz(qs)){
            ans += ll(qs[i + 1][0] - x) * tree.query(0, 1e9);
        }
    }
    cout << ans << nL;
    
    return 0;
}
