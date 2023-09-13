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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

struct XFT {
	vector<ll> s;
	XFT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] ^= dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res ^= s[pos-1];
		return res;
	}
};
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
struct LCA {
	int T = 0;
	vi time, path, ret, p;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C), -1), p(sz(C), -1), rmq((dostuff(C), ret)){
        
        // rmq(ret);
    }
    void dostuff(vector<vi>& C){
        rep(i, 0, sz(C)){
            if(time[i] == -1){
                dfs(C, i, -1);
            }
        }
    }
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
        p[v] = par == -1 ? v : par;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
        int r = rmq.query(a, b);
		return path[r];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vector<array<int, 3>> qs;
    vi tree(q);
    vvi adj(n);
    UF init(n);
    rep(i, 0, q){
        int a, b, t; cin >> a >> b >> t;
        a--, b--;
        qs.pb({a, b, t});
        if(init.join(a, b)){
            adj[a].pb(b);
            adj[b].pb(a);
            tree[i] = true;
        }
    }
    // vi start(n, -1), end(n, -1), p(n, -1), d;
    // int time = 0;
    // auto dfs = [&](int cur, int par, auto &&dfs)->void{
    //     // dfsorder[time] = cur;
    //     start[cur] = time++;
    //     d.pb(cur);
    //     p[cur] = par == -1 ? cur : par;
    //     for(int nex : adj[cur]){
    //         if(nex == par) continue;
    //         dfs(nex, cur, dfs);
    //     }
    //     end[cur] = time++;
    // };
    // rep(i, 0, n){
    //     if(start[i] == -1) dfs(i, -1, dfs);
    // }
    LCA lc(adj);
    XFT xft(n);
    FT ft(n);


    rep(i, 0, q){
        auto [a, b, t] = qs[i];
        int l = lc.lca(a, b);
        if(tree[i]){
            while(a != l){
                xft.update(a, t);
                a = lc.p[a];
            }
            while(b != l){
                xft.update(b, t);
                b = lc.p[b];
            }
            cout << "YES\n";
            continue;
        }
        int cycles = ft.query(a + 1) + ft.query(b + 1) - 2 * ft.query(l + 1);
        int t1 = xft.query(a + 1) ^ xft.query(b + 1);
        if(cycles > 0 || (t1 ^ t) == 0){
            cout << "NO\n";
            continue;
        }        
        
        // adding cycles
        while(a != l){
            ft.update(a, 1);
            a = lc.p[a];
        }
        while(b != l){
            ft.update(b, 1);
            b = lc.p[b];
        }
        cout << "YES\n";
    }


    
    return 0;
}