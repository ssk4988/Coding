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
	int lo, hi, mid;
    ll sum = 0;
	PST(vl& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			mid = lo + (hi - lo)/2;
			l = new PST(v, lo, mid); r = new PST(v, mid, hi);
			sum = l->sum + r->sum;
		}
		else sum = v[lo];
	}
    PST(PST *n) : lo(n->lo), hi(n->hi), sum(n->sum), mid(n->mid) {l = n->l; r = n->r;}
	ll query(int R) {
		if (R <= lo || hi <= 0) return 0;
		if (0 <= lo && hi <= R) return sum;
		return l->query(R) + r->query(R);
	}
    PST * add(int idx, int v){
        if (idx + 1 <= lo || hi <= idx) return this;
        PST *n = new PST(this);
        if (idx == lo && hi == idx + 1) {
            n->sum += v;
        }
        else{
            if(mid <= idx) n->r = r->add(idx, v);
            else n->l = l->add(idx, v);
            n->sum += n->l->sum + n->r->sum;
        }
        return n;
    }
};

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, idx = -1;
    PST *p = NULL; 
    int lzstart = -1;
    PST *lzp = NULL;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
	}
	ll query(int i) {
		if (i + 1 <= lo || hi <= i) return 0;
		if (i == lo && hi == i + 1){
            if(idx == -1) return 0;
            return p->query(lo - idx + 1);
        }
		push();
        int mid = lo + (hi - lo) / 2;
        if(mid <= i) return r->query(i);
        else return l->query(i);
	}
	void set(int L, int R, PST *x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R){
            lzp = p = x;
            lzstart = idx = L;
        }
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
		}
	}
	void push() {
        if(lzstart == -1) return;
		l->lzstart = l->idx = lzstart;
        l->lzp = l->p = lzp;
        r->lzstart = r->idx = lzstart;
        r->lzp = r->p = lzp;
        lzstart = -1;
        lzp = NULL;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> n >> m >> q;
    Node *ch = new Node(0, n);
    vector<PST*> psts(m);
    vi ks(m);
    rep(i, 0, m){
        cin >> ks[i];
        vl v(ks[i]);
        rep(j, 0, ks[i]){
            cin >> v[j];
        }
        for(int j = ks[i] - 1; j > 0; j--){
            v[j] -= v[j - 1];
        }
        psts[i] = new PST(v, 0, ks[i]);
    }
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int idx, p; cin >> idx >> p;
            idx--, p--;
            ch->set(p, p + ks[idx], psts[idx]);
        }
        else if(t == 2){
            int p; cin >> p; p--;
            cout << ((ch->query(p) % 256 + 256) % 256) << "\n";
        }
        else{
            int idx, l, r; cin >> idx >> l >> r;
            l--,r--,idx--;
            psts[idx] = psts[idx]->add(l, 1);
            psts[idx] = psts[idx]->add(r + 1, -1);
        }
    }
    
    return 0;
}
