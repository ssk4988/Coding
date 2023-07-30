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

struct RollbackUF {
    using a3 = array<int, 3>;
	vi e; vector<a3> st;
    int numcomps;
	RollbackUF(int n) : e(n, -1), numcomps(n) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;){
			e[st[i][0]] = st[i][1];
            numcomps = st[i][2];
        }
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a], numcomps});
		st.push_back({b, e[b], numcomps});
		e[a] += e[b]; e[b] = a;
        numcomps--;
		return true;
	}
};

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    vpi edges;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
	}
	void add(int L, int R, pi edge) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			edges.pb(edge);
		}
		else {
			l->add(L, R, edge), r->add(L, R, edge);
		}
	}
    void dfs(int L, int R, RollbackUF &uf){
        if (R <= lo || hi <= L) return;
        int t = uf.time();
        for(auto &p : edges){
            uf.join(p.f, p.s);
        }
        if(lo + 1 == hi) cout << uf.numcomps << " ";
        else{
            l->dfs(L, R, uf), r->dfs(L, R, uf);
        }
        uf.rollback(t);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    Node tree(0, k + 50);
    map<pi, vi> edges;
    RollbackUF uf(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--,b--;
        if(a > b) swap(a, b);
        edges[{a, b}].pb(0);
    }
    rep(i, 0, k){
        int t, a, b; cin >> t >> a >> b; a--,b--;
        if(a > b) swap(a, b);
        edges[{a, b}].pb(i + 1);
    }
    vpi addend;
    for(auto [key, val] : edges){
        if(sz(val) % 2 == 1) addend.pb(key);
    }
    for(auto p : addend) edges[p].pb(k + 5);
    for(auto [key, val] : edges){
        assert(sz(val) % 2 == 0);
        for(int i = 0; i < sz(val); i += 2){
            tree.add(val[i], val[i + 1], key);
        }
    }
    tree.dfs(0, k + 1, uf);
    cout << nL;
    
    return 0;
}