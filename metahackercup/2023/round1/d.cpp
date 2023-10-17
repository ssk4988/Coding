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

const ll MOD = 1e9 + 7;
const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    pi mx, mn;
    bool flp = false;
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			mx = max(l->mx, r->mx);
            mn = min(l->mn, r->mn);
		}
		else{
            mn = {v[lo], lo};
            mx = {v[lo], -lo};
        }
	}
	void flip(int L, int R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R){
            swap(mn, mx);
            mn.s *= -1;
            mx.s *= -1;
            mn.f = (mn.f * -1 + 2 * MOD) % MOD;
            mx.f = (mx.f * -1 + 2 * MOD) % MOD;
            flp ^= 1;
        }
		else {
			push(), l->flip(L, R), r->flip(L, R);
			mx = max(l->mx, r->mx);
            mn = min(l->mn, r->mn);
		}
	}
	void push() {
		if (flp)
			l->flip(lo,hi), r->flip(lo,hi), flp = 0;
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
        Node tree(a, 0, n);
        int q; cin >> q;
        ll sum = 0;
        rep(i, 0, q){
            int l, r; cin >> l >> r; l--, r--;
            tree.flip(l, r + 1);
            sum += abs(tree.mx.s) + 1;
        }
        cout << "Case #" << (cn + 1) << ": " << sum << nL;
    }
    
    return 0;
}
