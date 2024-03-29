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
inline ll mod(ll k){
    return k % MOD;
}

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    ll madd = 0, val = 0;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
            val = mod(l->val + r->val);
		}
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return mod(l->query(L, R) + r->query(L, R));
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd = mod(madd + x);
            val = mod(val + x);
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = mod(l->val + r->val);
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
    int k; cin >> k;
    Node tree(0, k+10);
    tree.add(1, 2, 1);
    rep(i, 1, k){
        ll dp = tree.query(i, i+1);
        tree.add(i+1, i+i+1, dp);
    }
    ll dp = tree.query(k, k+1);
    cout << dp << "\n";
    
    return 0;
}
