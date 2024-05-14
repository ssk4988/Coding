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
    vvi elem;
	UF(int n) : e(n, -1), elem(n) {
        rep(i, 0, n) elem[i].pb(i);
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
        for(int v : elem[b]) elem[a].pb(v);
        elem[b].clear();
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vvi adj(n);
    rep(i, 0, n){
        int p; cin >> p;
        if(p == 0) continue;
        p--;
        adj[p].pb(i);
    }

    vpi ps(k);
    vvi cnt(n, vi(2));
    vi nex(n, -1);
    bool bad = false;
    rep(i, 0, k){
        cin >> ps[i].f >> ps[i].s;
        ps[i].f--, ps[i].s--;
        nex[ps[i].f] = ps[i].s;
        cnt[ps[i].f][0]++;
        cnt[ps[i].s][1]++;
    }
    rep(i, 0, n){
        if(*max_element(all(cnt[i])) > 1) bad = true;
    }
    UF uf(n);
    for(auto [a, b] : ps){
        if(!uf.join(a, b)) bad = true;
    }
    if(bad){
        cout << 0 << "\n";
        return 0;
    }
    vi state(n);
    vi top;
    auto dfs = [&](int u, auto &&dfs) -> bool {
        u = uf.find(u);
        if(state[u] == 1) return true;
        if(state[u] == 2) return false;
        state[u] = 1;
        for(int x : uf.elem[u]){
            for(int v : adj[x]){
                if(uf.find(v) == u) continue;
                if(dfs(v, dfs)) return true;
            }
        }
        state[u] = 2;
        top.pb(u);
        return false;
    };
    rep(i, 0, n){
        if(dfs(i, dfs)) bad = true;
    }
    if(bad){
        cout << 0 << "\n";
        return 0;
    }
    reverse(all(top));
    vi ans;
    for(int u : top){
        set<int> ss(all(uf.elem[u]));
        for(int v : uf.elem[u]){
            if(nex[v] != -1) ss.erase(nex[v]);
        }
        int cur = *ss.begin();
        ans.pb(cur);
        while(nex[cur] != -1){
            cur = nex[cur];
            ans.pb(cur);
        }
    }
    vi inv(n);
    rep(i, 0, n){
        inv[ans[i]] = i;
        if(nex[ans[i]] != -1 && (i + 1 >= n || ans[i+1] != nex[ans[i]])) bad = true;
    }
    rep(u, 0, n){
        for(int v : adj[u]){
            if(inv[v] < inv[u]) bad = true;
        }
    }
    if(bad){
        cout << "0\n";
        return 0;
    }
    for(int i : ans) cout << (i+1) << " ";
    cout << "\n";
    
    return 0;
}
