#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

// i, a[i]
struct info {
    ll mxnp{0}, mnnp{0}, mxpp{0}, mnpp{0}, best{0};
    info(ll i, ll a) {
        mxnp = mnnp = -i + a;
        mxpp = mnpp = i + a;
    }
    info() {};
};
info operator+(info a, info b) {
    info res{};
    res.best = max({a.best, b.best, b.mxnp - a.mnnp, -b.mnpp + a.mxpp});
    res.mxnp = max(a.mxnp, b.mxnp);
    res.mnnp = min(a.mnnp, b.mnnp);
    res.mxpp = max(a.mxpp, b.mxpp);
    res.mnpp = min(a.mnpp, b.mnpp);
    return res;
}

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    info val;
	Node(vl& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = l->val + r->val;
		}
		else val = info(lo, v[lo]);
	}
	void set(int idx, ll x) {
        
		if (lo + 1 == hi) {val = info(lo, x); return;}
		int mid = lo + (hi - lo) / 2;
        if(mid <= idx) r->set(idx, x);
        else l->set(idx, x);
        val = l->val + r->val;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, q; cin >> n >> q;
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        Node tree(a, 0, n);
        cout << tree.val.best << "\n";
        rep(v, 0, q){
            int i, x; cin >> i >> x; i--;
            a[i] = x;
            tree.set(i, x);
            cout << tree.val.best << "\n";
        }
    }
    
    return 0;
}
