#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x)(int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for(auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g, f));

    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while(x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if( comp[i] < 0) dfs(i, g, f);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    int sum = 0;
    rep(i, 0, n){
        rep(j, 0, n){
            int v; cin >> v;
            if(v) adj[i].push_back(j);
            sum += v;
        }
    }
    vvi sccs;
    auto add = [&](vi v)->void {
        sccs.push_back(v);
    };
    scc(adj, add);
    int s = sz(sccs);
    vvi sadj(s, vi(s));
    vi seen(s), cnt(s);
    rep(i, 0, s){
        for(int u : sccs[i]){
            cnt[comp[u]]++;
            for(int v : adj[u]) sadj[comp[u]][comp[v]] = 1;
        }
    }
    vi topo;
    auto go = [&](int u, auto &&go)->void {
        if(seen[u]) return;
        seen[u] = true;
        rep(v, 0, s){
            if(!sadj[u][v] || u == v) continue;
            go(v, go);
        }
        topo.push_back(u);
    };
    int ans = 0;
    int cur = 0;
    rep(i, 0, s){
        go(i, go);
        // cout << i << " " << cnt[i] << " " << dp[i] << "\n";
    }
    // rep(i, 0, n){
    //     cout << i << " " << comp[i] << "\n";
    // }
    
    rep(i, 0, s){
        // cout << topo[i] << "\n";
        ans += cnt[topo[i]] * (cnt[topo[i]] - 1);
        ans += cur * cnt[topo[i]];
        cur += cnt[topo[i]];
    }
    ans -= sum;
    cout << ans << "\n";
    // rep(i, 0, n){
    //     cout << i << " " << comp[i] << "\n";
    // }
    // cout << sum << "\n";



    return 0;
}