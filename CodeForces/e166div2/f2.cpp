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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi par(n, -1), paredge(n, 1), bestl(n, -1), bestd(n);
        iota(all(bestl), 0);
        paredge[0] = 0;
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            par[u] = p;
            if(p != -1) adj[u].erase(find(all(adj[u]), p));
            int bestc = -1;
            for(int v : adj[u]){
                dfs(v, u, dfs);
                if(bestd[v] >= bestd[u]) bestl[u] = bestl[v], bestd[u] = bestd[v] + 1, bestc = v;
            }
            if(bestc != -1) adj[u].erase(find(all(adj[u]), bestc));
        };
        dfs(0, -1, dfs);
        priority_queue<pii> pq;
        pq.push({bestd[0], bestl[0]});
        vi ans(2*n);
        int curans = 0;
        rep(i, 0, n){
            if(pq.empty()) break;
            auto [score, cur] = pq.top(); pq.pop();
            curans += score;
            while(paredge[cur]) {
                for(auto x : adj[par[cur]]) pq.push({bestd[x]+1, bestl[x]});
                adj[par[cur]].clear();
                paredge[cur] = false;
                cur = par[cur];
            }
            ans[(i+1)/2] = n-1 - curans;
        }
        rep(i, 0, n-1) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
