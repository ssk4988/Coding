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
	int lo, hi;
    bool sw = false;
    pi val = {0, 0};
    pi comb(pi a, pi b){
        return {a.f ^ b.f, a.s ^ b.s};
    }
	Node(vi& v, string &s, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, s, lo, mid); r = new Node(v, s, mid, hi);
			val = comb(l->val, r->val);
		}
		else val = {s[lo] == '0' ? v[lo] : 0, s[lo] == '1'? v[lo] : 0};
	}
	// pi query(int L, int R) {
	// 	if (R <= lo || hi <= L) return {0, 0};
	// 	if (L <= lo && hi <= R) return val;
	// 	push();
	// 	return comb(l->query(L, R), r->query(L, R));
	// }
	void swp(int L, int R) {
        // cout << "swapping " << lo << " " << hi << "\n";
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			swap(val.f, val.s);
            sw = !sw;
		} else {
			push(), l->swp(L, R), r->swp(L, R);
			val = comb(l->val, r->val);
		}
	}
	void push() {
		if (sw && l != NULL)
			l->swp(lo,hi), r->swp(lo,hi), sw = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        string str; cin >> str;
        int q; cin >> q;
        Node tree(a, str, 0, n);
        rep(i, 0, q){
            int t; cin >> t;
            if(t == 1){
                int l, r; cin >> l >> r; l--, r--;
                tree.swp(l, r + 1);
            }
            else{
                int g; cin >> g;
                cout << (g == 0 ? tree.val.f : tree.val.s) << " ";
            }
        }
        cout << nL;
    }
    
    return 0;
}