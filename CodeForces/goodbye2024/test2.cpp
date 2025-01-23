#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

typedef uint64_t ull;
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return pair{x, b} == pair{o.x, o.b}; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
// typedef A<1000000007, A<1000000009, unsigned>> H;
typedef A<1000000009, unsigned> H;
// "typedef uint64_t H;" instead if Thue-Morse does not apply.

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};
string s;
HashInterval ha(s);
bool cmp(pii a, pii b) {
    int common = 0;
    for(int dif = 1 << 20; dif; dif /= 2)
    {
        if(min(a.s - a.f, b.s - b.f) >= common + dif && ha.hashInterval(a.f, a.f + common + dif) == ha.hashInterval(b.f, b.f + common + dif)) common += dif;
    }
    if(common == min(a.s - a.f, b.s - b.f)) {
        if(a.s - a.f < b.s - b.f) return true;
        return false;
    }
    return s[a.f + common] < s[b.f + common];
}

pii mx(pii a, pii b) {
    if(cmp(a, b)) return b;
    // if(b < a) return a;
    return a;
}

struct info {
    pii rng{0, 0}, best{0, 0}, suff{0, 0};
    info operator+(info o) {
        if(rng.s == rng.f) return o;
        if(o.rng.s == o.rng.f) return *this;
        pii sf = mx(pii{suff.f, o.rng.s}, o.suff);
        pii bst = mx(best, mx(sf, o.best));
        return info{{rng.f, o.rng.s}, bst, sf};
    }
};

struct Node {
    int lo, hi;
    Node*l = 0, *r = 0;
    info v;
    Node(int lo, int hi) : lo(lo), hi(hi){
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
            v = l->v + r->v;
        } else v = info{{lo, hi}, {lo, hi}, {lo, hi}};
    }
    info query(int L, int R) {
        if(R <= lo || hi <= L) return info();
        if(L <= lo && hi <= R) return v;
        return l->query(L, R) + r->query(L, R);
    }
};

void solve() {
    cin >> s;
    ha = HashInterval(s);
    int n = sz(s);
    int q; cin >> q;
    Node tree(0, n);
    rep(i, 0, q){
        int L, R; cin >> L >> R; L--;
        info v = tree.query(L, R);
        cout << v.best.f+1 << "\n";
    }
}

#include <sys/time.h>
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);
    // int nc; cin >> nc;
    // rep(cn, 0, nc)
    solve();
    
    return 0;
}

