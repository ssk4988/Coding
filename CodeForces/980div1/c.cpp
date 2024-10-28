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
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() { return x ^ (ull) b << 21; }
    // bool operator==(A o) const { return (ull)*this == (ull)o; }
	bool operator==(A o) const { return pair<int, B>{x, b} == pair<int, B>{o.x, o.b}; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(vi& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
    H leftrot(int r) {
        return hashInterval(r, sz(ha)-1) * pw[r] + hashInterval(0, r);
    }
};

#include <sys/time.h>

int main()
{
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k, m; cin >> n >> k;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        cin >> m;
        vvi g1(n);
        rep(i, 0, m){
            int u, v; cin >> u >> v; u--, v--;
            g1[u].pb(v);
        }
        vi b(n);
        rep(i, 0, n) cin >> b[i];
        cin >> m;
        vvi g2(n);
        rep(i, 0, m){
            int u, v; cin >> u >> v; u--, v--;
            g2[u].pb(v);
        }
        vi col1(n, -1), col2(n, -1);
        auto dfs = [&](vvi &g, vi&col, int u, int c, auto&&dfs) -> void {
            if(col[u] != -1){
                assert(col[u] == c);
                return;
            }
            col[u] = c;
            for(int v : g[u]){
                dfs(g, col, v, (c+1)%k, dfs);
            }
        };
        dfs(g1, col1, 0, 0, dfs);
        dfs(g2, col2, 0, 0, dfs);
        int outs = accumulate(all(a), 0), ins = sz(b) - accumulate(all(b), 0);
        if(ins != outs){
            cout << "NO\n";
            continue;
        }
        if(outs == 0 || outs == n){
            cout << "YES\n";
            continue;
        }
        vi freq11(k), freq12(k), freq21(k), freq22(k);
        rep(i, 0, n){
            if(a[i]) freq11[col1[i]]++;
            else freq12[col1[i]]++;
            if(b[i]) freq21[col2[i]]++;
            else freq22[col2[i]]++;
        }
        HashInterval h11(freq11), h12(freq12), h21(freq21), h22(freq22);
        bool works = false;
        rep(r, 0, k){
            if(h11.leftrot(0) == h22.leftrot((r+1)%k) && h12.leftrot(0) == h21.leftrot((r-1+k)%k)){
                works = true;
            }
        }

        // int rot1 = minRotation(freq1), rot2 = minRotation(freq2);
        // rotate(freq1.begin(), freq1.begin()+rot1, freq1.end());
        // rotate(freq2.begin(), freq2.begin()+rot2, freq2.end());
        cout << (works ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
