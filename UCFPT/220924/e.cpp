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

struct Node {
	Node *l = 0, *r = 0, *parent = NULL;
	int lo, hi, bit = 0;
    bool changed = true;
    vi val;
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi), val(64, 0) {
		if (lo < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid + 1, hi);
            l->parent = r->parent = this;
			comb();
		}
        else{
            val[v[lo]]++;
        }
	}
    vi combine(vi l, vi r){
        vi res(64);
        rep(i, 0, 64){
            res[i] = l[i] + r[i];
        }
        return res;
    }
    void comb() {
        if(!l) return;
        if(!r) return;
        // if(!l->changed && !r->changed) return;
        rep(i, 0, 64){
            val[i] = l->val[i] + r->val[i];
        }
        changed = true;
    }
	vi query(int L, int R) {
		if (R < lo || hi < L) return vi(64, 0);
		if (L <= lo && hi <= R) return val;
		push();
		return combine(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R < lo || hi < L) return;
		if (L <= lo && hi <= R) {
            upd(x);
        }
		else {
			push();
            l->set(L, R, x), r->set(L, R, x);
            comb();
		}
	}
    void upd(int dif) {
        vi val2(val);
        rep(i, 0, 64){
            val[i ^ dif] = val2[i];
        }
        bit ^= dif;
    }
	void push() {
        if(bit == 0) return;
        changed = true;
        // if(parent) parent->comb();
        if(l) {
            l->upd(bit);
        }
        if(r) {
            r->upd(bit);
        }
        bit = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n = str.length();
    vi bits;
    bits.pb(0);
    rep(i, 0, n){
        int k = str[i] - 'a';
        bits.pb(bits.back() ^ (1 << k));
    }
    Node root(bits, 0, bits.size() - 1);
    int q; cin >> q;
    rep(i, 0, q){
        int a; cin >> a;
        if(a == 1){
            int l, r; cin >> l >> r;
            vi res = root.query(l - 1, r);
            ll ans = 0;
            rep(j, 0, 64){
                if(res[j] > 1) ans += ((ll) res[j]) * (res[j] - 1) / 2;
            }
            cout << ans << nL;
        }
        else{
            int ind;
            string st;
            cin >> ind >> st;
            int k = st[0] - 'a';
            root.set(ind, root.hi, (1 << k) ^ (1 << (str[ind - 1] - 'a')));
            str[ind - 1] = st[0];
            // vi cur(bits.size());
            // rep(j, 0, bits.size()){
            //     vi v = root.query(j, j);
            //     rep(l, 0, 64){
            //         if(v[l] == 1){
            //             cur[j] = l;
            //         }
            //     }
            // }
        }
    }
    
    return 0;
}