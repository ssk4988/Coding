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

struct UF {
	vi e;
    vvi sets;
    UF(){}
	UF(int n) : e(n, -1), sets(n) {
        rep(i, 0, n) sets[i].pb(i);
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
        for(int i : sets[b]) sets[a].pb(i);
        sets[b].clear();
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m, q; cin >> n >> m >> q;
        vi ws;
        vector<vii> adj(n);
        rep(i, 0, m){
            int u, v, w; cin >> u >> v >> w;
            u--, v--;
            adj[u].pb({v, w});
            adj[v].pb({u, w});
            ws.pb(w);
        }
        sort(all(ws));
        ws.erase(unique(all(ws)), end(ws));
        const int inf = 1e9;
        vector<vii> ed(sz(ws));
        rep(i,0, n){
            for(auto &[v, w] : adj[i]){
                int id = lower_bound(all(ws), w) - begin(ws);
                w = id;
                // if(i < v){
                    ed[w].pb({i, v});
                // }
            }
        }
        UF uf(n);
        vi wdids;
        vector<vvi> info(n, vvi(n, vi(n, inf)));
        {
            rep(i, 0, n) {
                queue<pii> q;
                q.push({0, i});
                while(sz(q)) {
                    auto [d, u] = q.front(); q.pop();
                    if(info[i][u][0] != inf) continue;
                    info[i][u][0] = d;
                    for(auto [v, w] : adj[u]){
                        q.push({d+1, v});
                    }
                }
            }
        }
        int used = 0;
        int cnt = 1;
        rep(wid, 0, sz(ws)){
            bool did = false;
            vii dids;
            for(auto [u, v] : ed[wid]) {
                if(uf.join(u, v)) {
                    used++;
                    assert(used <= n);
                    dids.pb({u, v}); 
                    dids.pb({v, u});
                }
            }
            if(sz(dids) == 0) continue;
            wdids.pb(wid);
            rep(i, 0, n){
                rep(j, 0, n){
                    info[i][j][cnt] = info[i][j][cnt-1];
                }
            }
            for(auto [u, v] : dids) {
                rep(i, 0, n){
                    rep(j, 0, n){
                        info[i][j][cnt] = min(info[i][j][cnt], info[i][u][cnt] + info[v][j][cnt]);
                    }
                }
            }
            cnt++;
        }
        rep(i, 0, n){
            rep(j, 0, n) info[i][j].resize(cnt);
        }
        assert(sz(wdids) <= n);
        rep(i, 0, q){
            int a, b, k; cin >> a >> b >> k;
            a--, b--;
            int x = -1;
            for(int dif = 1 << 10; dif; dif /= 2) {
                int cur = x + dif;
                if(cur >= sz(wdids)) continue;
                if(info[a][b][cur] >= k) x = cur;
            }
            // x++;
            cout << ws[wdids[x]] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
