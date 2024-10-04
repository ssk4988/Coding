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
	vi e; vector<array<int, 3>> st;
    vi parity;
    bool bipartite = true;
	RollbackUF(int n) : e(n, -1), parity(n) {}
	int size(int x) { return -e[find(x).f]; }
	pi find(int x) { 
        if(e[x] < 0) return {x, 0};
        auto [p, par] = find(e[x]);
        return {p, par ^ parity[x]}; 
    }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;){
            if(st[i][0] != -1)
			e[st[i][0]] = st[i][1];
            bipartite = st[i][2];
        }
		st.resize(t);
	}
	bool join(int a, int b) {
        int ap, bp;
		tie(a, ap) = find(a), tie(b, bp) = find(b);
		if (a == b) {
            if ((bp ^ ap) == 0 && bipartite) {
                st.push_back({-1, -1, true});
                bipartite = false;
            }
            return false;
        }
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a], bipartite});
		st.push_back({b, e[b], bipartite});
		e[a] += e[b]; e[b] = a;
        parity[b] = ap ^ bp ^ 1;
		return true;
	}
};

RollbackUF uf(1);
using U = pi;
struct QueueUpdates {
    vector<tuple<bool, int, U>> st; // reversed, time before update, update
    void push(U u, bool r = false) {
        int t = uf.time();
        uf.join(u.first, u.second);
        st.emplace_back(r, t, u);
    }

    tuple<bool, int, U> rollback() {
        auto [r, t, u] = st.back();
        st.pop_back();
        uf.rollback(t);
        return {r, t, u};
    }
    
    void pop() {
        assert(sz(st));
        auto [r, t, u] = st.back();
        if (r) return void(rollback());
        array<vector<U>, 2> sq;
        do {
            tie(r, t, u) = rollback();
            sq[r].push_back(u);
        } while (sz(st) && sz(sq[0]) > sz(sq[1]));
        if (sz(st) == 0) {
            for(auto &u : sq[0]) push(u, true); // turn all stack updates into queue updates
            sq[0].clear();
        }
        rep(i, 0, 2)
            while(sz(sq[i])) 
                push(sq[i].back(), i), sq[i].pop_back();
        rollback();
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> n >> m >> q;
    uf = RollbackUF(n);
    vpi rds(m);
    vi precomp(m+1); // for precomp[i] = x, added roads [0, i) and [x, m) is still bipartite
    rep(i, 0, m){
        cin >> rds[i].f >> rds[i].s; rds[i].f--, rds[i].s--;
    }
    int x = 0;
    QueueUpdates qu;
    rep(i, 0, m){
        qu.push(rds[i]);
    }
    rep(i, 0, m+1){
        while(x < m && !uf.bipartite) {
            qu.pop();
            x++;
        }
        if(!uf.bipartite) x++;
        if(i < m) qu.push(rds[i]);
        precomp[i] = x;
    }
    rep(i, 0, q) {
        int l, r; cin >> l >> r; l--;
        cout << (precomp[l] <= r ? "NO" : "YES") << "\n";
    }
    
    return 0;
}
