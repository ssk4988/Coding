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

const int LIM = 1e5 + 100;

typedef uint64_t ull;
struct H {
	ull x; H(ull x=0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)
vector<H> pw;


using ph = pair<pair<H, H>, int>;

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mid;
    ph val;
	Node(int lo, int hi) : lo(lo), hi(hi), mid(0){
		if (lo + 1 < hi) {
			mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = comb(l->val, r->val);
		}
		else{
            val = {{lo,lo}, 1};
        }
	}
    ph comb(ph a, ph b){
        return {{a.f.f + pw[a.s] * b.f.f, a.f.s * pw[b.s] + b.f.s}, a.s + b.s};
    }
    void change(int idx, int v){
        if(lo + 1 == hi){
            val = {{v, v}, 1};
            return;
        }
        if(mid <= idx) r->change(idx, v);
        else l->change(idx, v);
        val = comb(l->val, r->val);
    }
    ph query(int L, int R){
        if(hi <= L || R <= lo) return {{0, 0}, 0};
        if(L <= lo && hi <= R){
            return val;
        }
        return comb(l->query(L, R), r->query(L, R));
    }
};

struct UF {
	vi r;
    vvi c;
    Node tree;
	UF(int n) : c(n), r(n), tree(0, n) {
        rep(i, 0, n){ 
            r[i] = i;
            c[i].pb(i);
        }
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return sz(c[find(x)]); }
	int find(int x) { return r[x] == x ? x : r[x] = find(r[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (size(a) < size(b)) swap(a, b);
        for(int i : c[b]){ 
            c[a].pb(i);
            r[i] = a;
            tree.change(i, a);
        }
        c[b].clear();
        
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    pw.pb(1);
    rep(i, 0, LIM){
        pw.pb(pw.back() * C);
    }
    int n, q; cin >> n >> q;
    UF uf(n);
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int l, r; cin >> l >> r;
            l--, r--;
            int len = r - l + 1;
            int s1, s2;
            if(len % 2 == 0){
                s1 = l - 1 + len/2, s2 = r + 1 - len/2;
            }
            else{
                s1 = s2 = l - 1 + (len + 1) / 2;
            }
            while(s2 <= r){
                int lo = -1, hi = r - s2;
                if(!(uf.tree.query(s1, s1 + 1).f.f == uf.tree.query(s2, s2 + 1).f.s)){
                    lo = hi = -1;
                }
                while(lo < hi){
                    int mid = lo + (hi - lo + 1) / 2;
                    ph ls = uf.tree.query(s1 - mid, s1 + 1), rs = uf.tree.query(s2, s2 + mid + 1);
                    if(ls.f.f == rs.f.s){
                        lo = mid;
                    }else hi = mid - 1;
                }
                s2 += lo + 1;
                s1 -= lo + 1;
                if(s2 <= r){
                    uf.join(s1, s2);
                }
                s2++;
                s1--;
            }
            ph res = uf.tree.query(l, r + 1);
            assert(res.f.f == res.f.s);
        }
        else{
            int x, y, l, r; cin >> x >> y >> l >> r;
            x--,y--,l--,r--;
            ph ls = uf.tree.query(x, y + 1), rs = uf.tree.query(l, r + 1);
            if(ls.s == rs.s){
                if(ls.f.f == rs.f.f){
                    cout << "Equal\n";
                } 
                else cout << "Unknown\n";
            }
            else cout << "Not equal\n";
        }
    }

    
    return 0;
}