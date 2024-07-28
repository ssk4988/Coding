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
	bool operator==(A o) const { return pair<int, B>{x, b} == pair<int, B>{o.x, o.b}; }
	bool operator<(A o) const { return pair<int, B>{x, b} < pair<int, B>{o.x, o.b}; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

// struct HashInterval {
// 	vector<H> ha, pw;
// 	HashInterval(vi& str) : ha(sz(str)+1), pw(ha) {
// 		pw[0] = 1;
// 		rep(i,0,sz(str))
// 			ha[i+1] = ha[i] * C + str[i],
// 			pw[i+1] = pw[i] * C;
// 	}
// 	H hashInterval(int a, int b) { // hash [a, b)
// 		return ha[b] - ha[a] * pw[b - a];
// 	}
// };

// vector<H> getHashes(string& str, int length) {
// 	if (sz(str) < length) return {};
// 	H h = 0, pw = 1;
// 	rep(i,0,length)
// 		h = h * C + str[i], pw = pw * C;
// 	vector<H> ret = {h};
// 	rep(i,length,sz(str)) {
// 		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
// 	}
// 	return ret;
// }
H hashString(vi s){H h{}; for(char c:s) h=h*C+c;return h;}
// H hashString(vi& s){H h{}; for(char c:s) h=h*C+c;return h;}

#include <sys/time.h>

const int N = 10;
int main()
{
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi lp(N+1);
    iota(all(lp), 0);
    rep(i, 2, sz(lp)){
        for(int j = 2; j <= i; j++){
            if(i % j == 0){
                lp[i] = j;
                break;
            }
        }
    }
    int n; cin >> n;
    vi freq(N+1);
    rep(i, 0, n){
        int v; cin >> v;
        freq[v]++;
    }
    vvi suffsum(N+1, vi(N+1)), cursum(N+1, vi(N+1));
    n = 0;
    // vector<HashInterval> ha(2, suffsum[1]);
    map<H, int> rl;
    rl[hashString(suffsum[1])] = n++;
    vector<vector<pair<int, ll>>> adj(1);
    vl subsz(1);
    subsz[0] = freq[0] + freq[1];
    vi par(1);
    vi depth(1);
    rep(i, 2, N+1){
        // cout << i << endl;
        int k = i;
        cursum[i] = cursum[i-1];
        while(k > 1){
            cursum[i][lp[k]]++;
            k /= lp[k];
        }
        suffsum[i] = cursum[i];
        partial_sum(suffsum[i].rbegin(), suffsum[i].rend(), suffsum[i].rbegin());
        // ha.pb(suffsum[i]);
        int len = 0;
        while(suffsum[i][sz(suffsum[i]) - len - 1] == suffsum[i-1][sz(suffsum[i]) - len - 1]){
            len++;
        }
        if(suffsum[i-1][sz(suffsum[i]) - len]) len++;
        H parhsh = hashString(vi(suffsum[i-1].end() - len, suffsum[i-1].end()));
        // H parhsh = ha[i].hashInterval(sz(suffsum[i]) - len, sz(suffsum[i]));
        if(!rl.count(parhsh)){
            rl[parhsh] = n++;
            subsz.pb(0);
            adj.pb({});
            depth.pb(suffsum[i-1][sz(suffsum[i]) - len]);
            
        }
        H curhsh = hashString(suffsum[i]);
        // H curhsh = ha[i].hashInterval(0, sz(suffsum[i]));
        if(!rl.count(curhsh)){
            rl[curhsh] = n++;
            subsz.pb(0);
            adj.pb({});
        }
        subsz[rl[curhsh]] += freq[i];
        ll dif = suffsum[i][0] - suffsum[i-1][sz(suffsum[i]) - len];
        adj[rl[parhsh]].pb({rl[curhsh], dif});
        cout << i << " " << len << " " << rl[curhsh] << " " << rl[parhsh] << " " << (dif) << "\n";
        // for(int j : cursum[i]) {
        //     cout << j << " ";
        // }
        // cout << "\n";
    }
    ll ans = 0;
    auto dfs = [&](int u, ll d, auto &&dfs) ->void {
        ans += subsz[u] * d;
        cout << u << " " << subsz[u] << " " << d << "\n";
        for(auto [v, w] : adj[u]){
            dfs(v, d + w, dfs);
            subsz[u] += subsz[v];
        }
    };
    dfs(0, 0, dfs);
    cout << ans << "\n";
    auto dfs1 = [&](int u, auto &&dfs1) -> void {
        for(auto [v, w] : adj[u]){
            if(2 * subsz[v] > subsz[0]){
                ans -= subsz[v] * w;
                ans += (subsz[0] - subsz[v]) * w;
                dfs1(v, dfs1);
            }
        }
    };
    dfs1(0, dfs1);
    cout << ans << "\n";
    
    return 0;
}
