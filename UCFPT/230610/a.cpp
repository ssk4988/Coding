#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;
using vvl = vector<vl>;

typedef unsigned long long ull;
ull sumsq(ull to) { return to / 2 * ((to-1) | 1); }
ull divsum(ull to, ull c, ull k, ull m) {
    ull res = k / m * sumsq(to) + c / m * to;
    k %= m; c %= m;
    if (!k) return res;
    ull to2 = (to * k + c) / m;
    return res + (to - 1) * to2 - divsum(to2, m-1 - c, m, k);
}
ll modsum(ull to, ll c, ll k, ll m) {
    c = ((c % m) + m) % m;
    k = ((k % m) + m) % m;
    return to * c + k * sumsq(to) - m * divsum(to, c, k, m);
}

struct Node {
	Node *l = 0, *r = 0;
	ll lo, hi;
    ll sum = 0;
    ll a, b, start;
    bool lzon = false;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return sum;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void set(int L, int R, ll a, ll b, ll start) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R){
            this->a = a;
            this->b = b;
            this->start = start;
            sum = modsum(hi - lo, ((lo - start + 1) * a) % b, a, b);
            lzon = true;
        }
		else {
			push(), l->set(L, R, a, b, start), r->set(L, R, a, b, start);
			sum = l->sum + r->sum;
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
        if(lzon){
            l->set(lo, hi, a, b, start);
            r->set(lo, hi, a, b, start);
            lzon = false;
        }
	}
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    Node tree(0, n);
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            ll l, r, a, b; cin >> l >> r >> a >> b;
            l--,r--;
            tree.set(l, r + 1, a, b, l);
        }
        else{
            ll l, r; cin >> l >> r;
            l--,r--;
            cout << tree.query(l, r + 1) << "\n";
        }
    }
    return 0;
}