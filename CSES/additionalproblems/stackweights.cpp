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
	int lo, hi, madd = 0;
    pi info = {0, 0}; // min, max
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			comb();
		}
	}
    pi combine(pi l, pi r){
        return {min(l.f, r.f), max(l.s, r.s)};
    }
    void comb(){
        info = combine(l->info, r->info);
    }
	pi query(int L, int R) {
		if (R <= lo || hi <= L) return {inf, -inf};
		if (L <= lo && hi <= R) return info;
		push();
		return combine(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			info.f += x;
            info.s += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			comb();
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
    int n; cin >> n;
    Node tree(0, n);
    rep(i, 0, n){
        int v, t; cin >> v >> t;
        v--;
        tree.add(0, v + 1, t == 1 ? -1 : 1);
        pi info = tree.query(0, n);
        if(info.f >= 0) cout << "<";
        else if(info.s <= 0) cout << ">";
        else cout << "?";
        cout << nL;
    }
    return 0;
}
