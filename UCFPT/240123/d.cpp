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
	int lo, hi, madd = 0, val = inf;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = min(l->val, r->val);
		}
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, l, k;
    cin >> n >> l >> k; l--;
    int ans = 0;
    vi h(n), c;
    rep(i, 0, n){
        cin >> h[i];
        c.pb(h[i]);
    }
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    rep(i, 0, n){
        h[i] = lower_bound(all(c), h[i]) - c.begin();
    }
    rep(i, 0, l){
        if(h[i] >= h[l]) ans++;
    }
    vector<Node> trees;
    rep(i, 0, k + 1){
        trees.pb(Node(0, n));
    }
    trees[1].set(h[l], h[l] + 1, 0);
    rep(i, l + 1, n){
        // rep(j, 0, k + 1){
        //     cout << i << " " << j << " " << trees[j].val << "\n";
        // }
        for(int j = k; j > 0; j--) {
            trees[j].add(0, h[i], 1);
            int prev = trees[j-1].query(0, h[i]);
            trees[j].set(h[i], h[i] + 1, min(trees[j].query(h[i], h[i] + 1), trees[j-1].query(0, h[i])));
            // cout << i << " " << j << " set " << h[i] << " to " << trees[j].query(h[i], h[i] + 1) << " using " << prev << " " << trees[j-1].val << endl;
        }
    }
    int ans1 = trees[k].query(0, n);
    if(ans1 >= inf){
        cout << -1 << "\n";
        return 0;
    }
    ans += ans1;
    cout << ans << "\n";

    return 0;
}
