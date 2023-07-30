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

typedef uint64_t ull;
static int C; // initialized below
 
// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return (ull)*this == (ull)o; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;
 
ll MOD = 1e9 + 7;
 
ll mod(ll k){
    return k % MOD;
}
 
vl pows;
using pll = pair<pl, ll>;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mid;
    pll val;
	Node(string& v, int lo, int hi) : lo(lo), hi(hi), mid(0) {
		if (lo + 1 < hi) {
			mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = comb(l->val, r->val);
		}
		else{
            val = {{v[lo] - 'a' + 1, v[lo] - 'a' + 1}, 1};
        }
	}
    pll comb(pll a, pll b){
        return {{mod(a.f.f + mod(pows[a.s] * b.f.f)), mod(mod(a.f.s * pows[b.s]) + b.f.s)}, a.s + b.s};
    }
    void change(int idx, char c){
        if(lo + 1 == hi){
            val = {{c - 'a' + 1, c - 'a' + 1}, 1};
            return;
        }
        if(mid <= idx) r->change(idx, c);
        else l->change(idx, c);
        val = comb(l->val, r->val);
    }
    pll query(int L, int R){
        if(hi <= L || R <= lo) return {{0, 0}, 0};
        if(L <= lo && hi <= R) return val;
        return comb(l->query(L, R), r->query(L, R));
    }
};
#include <sys/time.h>
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);
    pows.pb(1);
    int LIM = 2e5 + 100;
    rep(i, 0, LIM){
        pows.pb(mod(pows.back() * C));
    }
    int n, q; cin >> n >> q;
    string str; cin >> str;
    Node tree(str, 0, sz(str));
    rep(i, 0, q){
        int v; cin >> v;
        if(v == 1){
            int idx; cin >> idx; idx--;
            char c; cin >> c;
            tree.change(idx, c);
        }
        else{
            int l, r; cin >> l >> r; l--, r--;
            pll res = tree.query(l, r + 1);
            cout << (res.f.f == res.f.s ? "YES" : "NO") << nL;
        }
    }
    return 0;
}
