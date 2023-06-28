#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vector<vector<pair<int, ll>>> adj(n);
    rep(i, 0, n - 1){
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }
    vi marked(n);
    rep(i, 0, k){
        int v; cin >> v;
        v--;
        marked[v] = true;
    }
    vi targets(n);
    vl height(n);
    vector<vpl> hs(n);
    // vector<unordered_map<int, ll>> dep(n);
    rep(i, 0, n) if(marked[i]) targets[i]++;
    ll edgesum = 0;
    auto calctargets = [&](int cur, int par, auto &&calctargets)->void{
        for(auto [nex, w] : adj[cur]){
            if(nex == par) continue;
            calctargets(nex, cur, calctargets);
            targets[cur] += targets[nex];
            if(targets[nex]){
                height[cur] = max(height[cur], w + height[nex]);
                hs[cur].pb({w + height[nex], nex});
                edgesum += w;
            }
        }
    };
    calctargets(0, -1, calctargets);
    vl ans(n);
    auto dfs2 = [&](int cur, int par, ll edgesum, ll bestexc, auto &&dfs2)->void{
        if(par != -1 && targets[par])
        {
            hs[cur].pb({bestexc, par});
        }
        sort(all(hs[cur]));
        reverse(all(hs[cur]));
        ans[cur] = 2 * edgesum;
        if(sz(hs[cur])) ans[cur] -= hs[cur][0].f;
        for(auto [nex, w] : adj[cur]){
            if(nex == par) continue;
            ll newbest = 0;
            if(sz(hs[cur]) && nex != hs[cur][0].s) newbest = hs[cur][0].f + w;
            else if(sz(hs[cur]) > 1) newbest = hs[cur][1].f + w;
            if(targets[nex]) edgesum -= w;
            if(targets[cur] - targets[nex]) edgesum += w;
            int add = targets[cur] - targets[nex];
            targets[nex] += add;
            dfs2(nex, cur, edgesum, newbest, dfs2);
            targets[nex] -= add;
            if(targets[nex]) edgesum += w;
            if(targets[cur] - targets[nex]) edgesum -= w;
        }
    };

    
    dfs2(0, -1, edgesum, 0, dfs2);
    rep(i, 0, n){
        cout << ans[i] << "\n";
    }

}
