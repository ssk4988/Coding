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

struct PST {
	PST *l = 0, *r = 0;
	int lo, hi;
    ll val = 0, lzadd = 0;
	PST(vl& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new PST(v, lo, mid); r = new PST(v, mid, hi);
		}
		else val = v[lo];
	}
    ll query(int L, int R){
        if (R < lo || hi < L) return 0; // idempotent
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
    }
    PST * add(int L, int R, ll v){
        if (R <= lo || hi <= L) return this;
        PST *n = new PST(*this);
        if (L <= lo && hi <= R) {
            n->val += v;
            n->lzadd += v;
        }
        else{
            push();
            n->l = l->add(L, R, v);
            n->r = r->add(L, R, v);
        }
        return n;
    }
    void push(){
        if(lzadd == 0) return;
        l = l->add(lo, hi, lzadd);
        r = r->add(lo, hi, lzadd);
        lzadd = 0;
    }
};
