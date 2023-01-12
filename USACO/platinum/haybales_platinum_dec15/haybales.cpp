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

const ll inf = 1e18;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, madd = 0;
    vl val;
    // 0 sum 1 min
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi), val(2) {
		if (lo < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid + 1, hi);
			comb();
		}
		else{
            val[0] = val[1] = v[lo];
        }
	}
    vl combine(vl l, vl r){
        return {l[0] + r[0], min(l[1], r[1])};
    }
    void comb(){
        val = combine(l->val, r->val);
    }
	vl query(int L, int R) {
		if (R < lo || hi < L) return {0, inf};
		if (L <= lo && hi <= R) return val;
		push();
		return combine(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, ll x) {
		if (R < lo || hi < L) return;
		if (L <= lo && hi <= R) {
			madd += x;
            val[0] += x * (hi - lo + 1);
            val[1] += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			comb();
		}
	}
	void push() {
		if(!madd) return;
        l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    Node root = Node(a, 0, n - 1);
    rep(i, 0, q){
        char c;
        cin >> c;
        int x, y, z;
        cin >> x >> y;
        x--; y--;
        if(c == 'P'){
            cin >> z;
            root.add(x, y, z);
        }
        else if(c == 'M'){
            cout << root.query(x, y)[1] << nL;
        }
        else{
            cout << root.query(x, y)[0] << nL;
        }
    }


    return 0;
}