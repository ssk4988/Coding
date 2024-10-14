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

struct Node {
	Node *left = 0, *right = 0;
	int lo, hi;
	ll val = 0; // initial value of segment
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 == hi) return;
		int mid = (lo + hi) / 2;
		left = new Node(lo, mid), right = new Node(mid, hi);
	}
	// queries min on [L, R) range
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return LLONG_MAX; // idempotent value
		if (L <= lo && hi <= R) return val;
		return merge(left->query(L, R), right->query(L, R));
	}
	void add(int idx, int v) {
		if (lo + 1 == hi) {
			val += v;
			return;
		}
		int mid = (lo + hi) / 2;
		if (mid <= idx) right->add(idx, v);
		else left->add(idx, v);
		val = merge(left->val, right->val);
	}
	ll merge(ll a, ll b) { return min(a, b); }
};



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vl a(n);
    Node tree(0, n);
    rep(i, 0, n) {
        cin >> a[i];
        tree.add(i, a[i]);
    }
    rep(i, 0, q){
        int t, x, y; cin >> t >> x >> y; x--;
        if(t == 1) {
            tree.add(x, y - a[x]);
            a[x] = y;
        } else cout << tree.query(x, y) << "\n";
    }
    
    return 0;
}
