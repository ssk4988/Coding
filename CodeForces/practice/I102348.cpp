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

const int MAX_N = 12e5;
struct TwoSat {
	int N;
	vector<vi> gr;
	bitset<MAX_N> values, setv; // 0 = false, 1 = true

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f].push_back(j^1);
		gr[j].push_back(f^1);
	}
    void implies(int f, int j) {
        either(~(f), j);
    }
    void neq(int f, int j){
        implies(f, ~j);
        implies(j, ~f);
    }
	vi val, comp, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		for(int e : gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (!setv[x>>1])
				values[x>>1] = x&1, setv[x>>1] = 1;
		} while (x != i);
		return val[i] = low;
	}

	bool solve() {
		// values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		rep(i,0,2*N) if (!comp[i]) dfs(i);
		rep(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};

// xi or yi
// not (ui and vi) = not ui or not vi
// if li >= rj then not i or not j  i implies not j, j implies not i
// T/F for each i from 0 to n-1
// fake node for each r val from 0 to M-1 - prefix
// r=i represents r <= i
// not r=i implies not r=i-1 
// l=i represents l >= i
// fake node for each l val from 0 to M-1 - suffix
// not l=i implies not l=i+1

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, p, M, m; cin >> n >> p >> M >> m;
    TwoSat ts(p + 2 * M);
    rep(i, 0, n){
        int x, y; cin >> x >> y; x--, y--;
        ts.either(x, y);
    }
    vi ls, rs;
    rep(i, 0, p){
        int l, r; cin >> l >> r; l--, r--;
        if(l) ts.implies(i, p + l);
        if(r + 1 < M) ts.implies(i, p + M + r);
        ls.pb(l);
        rs.pb(r);
    }
    rep(i, 0, M){
        if(i)ts.implies(~(p + M + i), ~(p + M + i - 1)); // !r<=i implies !r<=i-1
        if(i + 1 < M) ts.implies(~(p + i), ~(p + i + 1)); // !l>=i implies !l>=i+1
        if(i) ts.neq(p + i, p + M + i-1); // l>=i != r <= i-1
    }
    rep(i, 0, m){
        int u, v; cin >> u >> v; u--, v--;
        ts.either(~(u), ~(v));
    }
    bool works = ts.solve();
    if(!works){
        cout << "-1\n";
        return 0;
    }
    int l = 0, r = M-1;
    vi res;
    rep(i, 0, p){
        if(ts.values[i]) {
            res.pb(i);
            l = max(l, ls[i]);
            r = min(r, rs[i]);
        }
    }
    assert(l <= r);
    cout << sz(res) << " " << l+1 << endl;
    for(int i : res) cout << i+1 << " ";
    cout << endl;
    
    return 0;
}
