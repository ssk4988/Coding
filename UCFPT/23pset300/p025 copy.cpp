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
	int val, y, c = 1, freq;
    vi events;
	PST(int val, int freq) : val(val), y(rand()), freq(freq), c(freq), events(26) { events[val] = 1; }
	void recalc();
};

int cnt(PST* n) { return n ? n->c : 0; }
int frq(PST* n) {return n ? n->freq : 0; }
int distinct(PST *n) {
    if(!n) return 0;
    int v = 0;
    rep(i, 0, 26){
        v += (n->events[i] ? 1 : 0);
    }
    return v;
}
void PST::recalc() { 
    c = cnt(l) + cnt(r) + frq(this); 
    rep(i, 0, 26){
        if((l && l->events[i]) || (r && r->events[i]) || (i == val && freq)) events[i] = 1;
        else events[i] = 0;
    }
}

template<class F> void each(PST* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

PST* merge(PST* l, PST* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->recalc();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->recalc();
		return r;
	}
}
pair<PST*, PST*> split(PST* n, int k) {
	if (!n) return {};
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	} 
    else if(cnt(n->l) + frq(n) >= k){
        PST *lsplit = new PST(n->val, k - cnt(n->l));
        PST *rsplit;
        lsplit = merge(n->l, lsplit);
        if(lsplit) lsplit->recalc();
        if(frq(n) - frq(lsplit) == 0){
            rsplit = n->r;
            if(rsplit)rsplit->recalc();
        }
        else{
            rsplit = new PST(n->val, frq(n) - frq(lsplit));
            rsplit = merge(rsplit, n->r);
            if(rsplit)rsplit->recalc();
        }
        return {lsplit, rsplit};
    }
    else {
		auto pa = split(n->r, k - cnt(n->l) - frq(n)); // and just "k"
		n->r = pa.first;
		n->recalc();
		return {n, pa.second};
	}
}


PST* ins(PST* t, PST* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

// Example application: move the range [l, r) to index k
void move(PST*& t, int l, int r, int k) {
	PST *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    PST *treap = NULL;
    rep(i, 0, q){
        char c; cin >> c;
        if(c == '+'){
            int idx, nbr;
            char ty; cin >> idx >> nbr >> ty;
            int ev = ty - 'a';
            idx--;
            PST *nn = new PST(ev, nbr);
            treap = ins(treap, nn, idx);
        }
        else if(c == '?'){
            int l, r; cin >> l >> r;
            l--, r--;
            r++; // exclusive
            PST *a, *b, *c;
            tie(a,b) = split(treap, l); tie(b,c) = split(b, r - l);
            int ans = distinct(b);
            treap = merge(a, merge(b, c));
            cout << ans << "\n";
        }
        else if(c == '-'){
            int l, r; cin >> l >> r;
            l--, r--;
            r++; // exclusive
            PST *a, *b, *c;
            tie(a,b) = split(treap, l); tie(b,c) = split(b, r - l);
            treap = merge(a, c);
        }
        else {assert(false);}
        // cout << "op\n";
    }
    
    return 0;
}
