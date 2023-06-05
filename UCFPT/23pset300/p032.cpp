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
using vvl = vector<vl>;

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

struct Node2 {
	Node2 *l = 0, *r = 0;
	int lo, hi;
    ll val = 0, lzadd = 0;
	Node2(vl &v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node2(v, lo, mid); r = new Node2(v, mid, hi);
		}
        else val = v[lo];
	}
	int query(int i) {
		if (i + 1 <= lo || hi <= i) {assert(false);return 0;}
		if (i == lo && hi == i + 1){
            return val % 256;
        }
		push();
        int mid = lo + (hi - lo) / 2;
        if(mid <= i) return r->query(i);
        else return l->query(i);
	}
	void add(int L, int R, ll v) { 
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R){
            val += v;
            lzadd += v;
        }
		else {
			push(), l->add(L, R, v), r->add(L, R, v);
		}
	}
	void push() {
        if(lzadd == 0) return;
        l->add(lo, hi, lzadd);
        r->add(lo, hi, lzadd);
        lzadd = 0;
	}
};

vector<array<int, 3>> queries;

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    int idx = -1, lzidx = -1, t = -1, lzt = -1, arr = -1, lzarr = -1;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
	}
	void query(int i) {
		if (i + 1 <= lo || hi <= i){ assert(false); return;}
		if (i == lo && hi == i + 1){
            queries.pb({arr, lo - idx, t});
            return;
        }
		push();
        int mid = lo + (hi - lo) / 2;
        if(mid <= i) r->query(i);
        else l->query(i);
	}
	void set(int L, int R, int a, int time) { // a is arr idx, time
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R){
            lzarr = arr = a;
            t = lzt = time;
            lzidx = idx = L;
        }
		else {
			push(), l->set(L, R, a, time), r->set(L, R, a, time);
		}
	}
	void push() {
        if(lzidx == -1) return;
        l->set(lzidx, hi, lzarr, lzt);
        r->set(lzidx, hi, lzarr, lzt);
        lzidx = -1, lzarr = -1, lzt = -1;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> n >> m >> q;
    Node *ch = new Node(0, n);
    vector<vpi> mods(m);
    // vector<PST*> psts(m);
    vector<Node2*> trees(m);
    vi ks(m);
    vvl vs;
    rep(i, 0, m){
        cin >> ks[i];
        vl v(ks[i]);
        rep(j, 0, ks[i]){
            cin >> v[j];
        }
        vs.pb(v);
        trees[i] = new Node2(v, 0, ks[i]);
        // psts[i] = new PST(v, 0, ks[i]);
    }
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int idx, p; cin >> idx >> p;
            idx--, p--;
            // mods[idx].pb({p, p + ks[idx]});
            ch->set(p, p + ks[idx], idx, sz(mods[idx]));
        }
        else if(t == 2){
            int p; cin >> p; p--;
            ch->query(p);
            // cout << ((ch->query(p) % 256 + 256) % 256) << "\n";
        }
        else{
            int idx, l, r; cin >> idx >> l >> r;
            l--,r--,idx--;
            mods[idx].pb({l, r + 1});
            // psts[idx] = psts[idx]->add(l, r + 1, 1);
        }
    }
    vi modt(m, 0);
    for(auto [arr, qidx, t] : queries){
        if(arr == -1) cout << 0 << nL;
        else{
            while(t > modt[arr]){
                // mod seg tree
                trees[arr]->add(mods[arr][modt[arr]].f, mods[arr][modt[arr]].s, 1);
                modt[arr]++;
            }
            cout << trees[arr]->query(qidx) << nL;
            // query seg tree
        }
    }
    
    return 0;
}
