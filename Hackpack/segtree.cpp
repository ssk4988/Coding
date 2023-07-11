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
	int lo, hi, val = -inf;
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			comb();
		}
		else val = v[lo];
	}
    int combine(int l, int r){
        return max(l, r);
    }
    void comb(){
        val = combine(l->val, r->val);
    }
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		return combine(l->query(L, R), r->query(L, R));
	}
	void pointupd(int idx, int v){
		if (lo + 1 == hi){
			// do the update
		}
		else {
			int mid = lo + (hi - lo) / 2;
			if(mid <= idx) r->pointupd(idx, v);
			else l->pointupd(idx, v);
			comb();
		}
	}
	int pointquery(int idx){
		if (lo + 1 == hi){
			return val;
		}
		else {
			int mid = lo + (hi - lo) / 2;
			if(mid <= idx) return r->pointquery(idx);
			else l->pointquery(idx);
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    
    return 0;
}
