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
	int lo, hi, madd = 0, val = 0;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	// Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
	// 	if (lo + 1 < hi) {
	// 		int mid = lo + (hi - lo)/2;
	// 		l = new Node(v, lo, mid); r = new Node(v, mid, hi);
	// 		val = max(l->val, r->val);
	// 	}
	// 	else val = v[lo];
	// }
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	// void set(int L, int R, int x) {
	// 	if (R <= lo || hi <= L) return;
	// 	if (L <= lo && hi <= R) mset = val = x, madd = 0;
	// 	else {
	// 		push(), l->set(L, R, x), r->set(L, R, x);
	// 		val = max(l->val, r->val);
	// 	}
	// }
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};
const bool DEBUG = false;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    using a3 = array<int, 3>;
    vector<a3> pts(n);
    rep(i, 0, n){
        cin >> pts[i][2] >> pts[i][0] >> pts[i][1];
        int x = pts[i][0], y = pts[i][1];
        pts[i][0] = x + y;
        if(DEBUG) pts[i][1] = x - y;
        else pts[i][1] = x - y + 1e6;
    }
    Node tree(0, 2e6 + 10);
    sort(all(pts));
    int remidx = 0;
    int ans = 0;
    rep(i, 0, n){
        while(remidx < n && pts[remidx][0] < pts[i][0] - 2 * k){
            if(DEBUG) cout << max(0, pts[remidx][1] - k) << " to " << min(tree.hi, pts[remidx][1] + k + 1) - 1 << " rem " << pts[i][2] << nL;
            tree.add(max(0, pts[remidx][1] - k), min(tree.hi, pts[remidx][1] + k + 1), -pts[remidx][2]);
            remidx++;
        }
        tree.add(max(0, pts[i][1] - k), min(tree.hi, pts[i][1] + k + 1), pts[i][2]);
        if(DEBUG) cout << max(0, pts[i][1] - k) << " to " << min(tree.hi, pts[i][1] + k + 1) - 1 << " add " << pts[i][2] << nL;
        ans = max(ans, tree.val);
    }
    cout << ans << nL;
    
    return 0;
}
