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

const ll inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	ll lo, hi, mset = 0, madd = 0, sum = 0;
	Node(vl& v, ll lo, ll hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			sum = l->sum + r->sum;
		}
		else sum = v[lo];
	}
	ll query(ll L, ll R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return sum;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void set(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R){
            madd = 0;
            mset = x;
            sum = x * (hi - lo);
        }
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			sum = l->sum + r->sum;
		}
	}
	void add(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != 0) mset += x;
			else madd += x;
			sum += x * (hi - lo);
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			sum = l->sum + r->sum;
		}
	}
	void push() {
		if (mset != 0)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = 0;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    Node* tree = new Node(a, 0, n);
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int a, b, x; cin >> a >> b >> x;
            a--,b--;
            tree->add(a, b + 1, x);
        }
        else if(t == 2){
            int a, b, x; cin >> a >> b >> x;
            a--,b--;
            tree->set(a, b + 1, x);
        }
        else{
            int a, b; cin >> a >> b;
            a--,b--;
            cout << tree->query(a, b + 1) << nL;
        }
    }
    
    return 0;
}
