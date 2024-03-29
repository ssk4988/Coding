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
	bool operator<(A o) const { return pair<int, B> {x, b} < pair<int, B> {o.x, o.b}; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

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

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}


#include <sys/time.h>
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);


    int n; cin >> n;
    // cout << "n: " << n << endl;
    vector<H> pw;
    pw.pb(1);
    rep(i, 0, n){
        pw.pb(pw.back() * C);
    }
    // cout << "pwsize: " << sz(pw) << endl;
    vi a(n-1);
    H base = 0;
    rep(i, 0, n-1){
        cin >> a[i];
        base = base + pw[a[i]];
    }
    // cout << "got here" << endl;
    set<H> target;
    rep(i, 0, n){
        // cout << "insert " << i << endl;
        target.insert(base + pw[i]);
    }
    vector<H> subhsh(n);
    vvi adj(n);
    vi par(n);
    // cout << "got here" << endl;
    rep(i, 0, n-1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    // cout << "read adjacencies " << endl;
    auto dfs = [&](int u, int p, auto &&dfs)->void {
        par[u] = p;
        // cout << "dfs " << u << " " << p << "\n";
        if(p != -1){
            adj[u].erase(find(all(adj[u]), p));
        }
        subhsh[u] = 1; // 1 of dist 0
        for(int v : adj[u]){
            dfs(v, u, dfs);
            subhsh[u] = subhsh[u] + subhsh[v] * pw[1]; // everything in subtree is 1 away than precalc
        }
    };
    dfs(0, -1, dfs);
    vector<H> reroothsh(n);
    vi good;
    auto reroot = [&](int u, auto &&reroot) -> void {
        if(par[u] == -1){
            reroothsh[u] = subhsh[u];
        }
        else{
            reroothsh[u] = subhsh[u] + ((reroothsh[par[u]] - subhsh[u] * pw[1]) * pw[1]);
        }
        if(target.count(reroothsh[u])){
            good.pb(u);
        }
        for(int v : adj[u]){
            reroot(v, reroot);
        }
    };
    reroot(0, reroot);
    sort(all(good));
    cout << sz(good)<< "\n";
    for(int g : good){
        cout << (g+1) << " ";
    }
    cout << "\n";
    return 0;
}
