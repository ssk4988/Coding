#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i,a, b) for(int i = a; i <(b); i++)

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using ld = long double;

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vi> hs; vi H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n){}

    void addEdge(int s, int t, ll cap, ll rcap = 0){
        if(s == t) return;
        g[s].push_back({t, sz(g[t]), 0, cap});
        g[t].push_back({s, sz(g[s]) - 1, 0, rcap});
    }
    void addFlow(Edge &e, ll f){
        Edge &back = g[e.dest][e.back];
        if(!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t){
        int v = sz(g); H[s] = v; ec[t] = 1;
        vi co(2 * v); co[0] = v - 1;
        rep(i, 0, v) cur[i] = g[i].data();
        for(Edge &e : g[s]) addFlow(e, e.c);
        for(int hi = 0;;){
            while(hs[hi].empty()) if(!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while(ec[u] > 0){
                if(cur[u] == g[u].data() + sz(g[u])){
                    H[u] = 1e9;
                    for(Edge &e : g[u]) if(e.c && H[u] > H[e.dest] + 1)
                        H[u] = H[e.dest] + 1, cur[u] = &e;
                    if(++co[H[u]], !--co[hi] && hi < v)
                        rep(i, 0, v) if(hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if(cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
            }
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        PushRelabel pr(n + 2);
        vi matt(n), sean(n);
        rep(i, 0, n){
            ld v; cin >> v;
            matt[i] = int(v * 100 + 0.1);
            pr.addEdge(n, i, matt[i]);
        }
        rep(i, 0, n){
            ld v; cin >> v;
            sean[i] = int(v * 100 + 0.1);
            pr.addEdge(i, n + 1, sean[i]);
        }
        vector<vi> adj(n, vi(n));
        rep(i, 0, n){
            rep(j, 0, n){
                ld v; cin >> v;
                int v1 = int(v * 100 + 0.1);
                pr.addEdge(i, j, v1);
                pr.addEdge(j, i, v1);
                adj[i][j] = v1;
            }
        }
        ll mf = pr.calc(n, n + 1);
        vi g1, g2;
        rep(i, 0, n){
            (pr.leftOfMinCut(i) ? g1 : g2).push_back(i);
            // cout << i << " " << (pr.leftOfMinCut(i) ? "matt" : "sean") << "\n";
        }
        ll ans = 0;
        rep(i, 0, sz(g1)){
            ans += matt[g1[i]];
            rep(j, 0, sz(g1)){
                ans += adj[g1[i]][g1[j]];
            }
        }
        rep(i, 0, sz(g2)){
            ans += sean[g2[i]];
            rep(j, 0, sz(g2)){
                ans += adj[g2[i]][g2[j]];
            }
        }
        cout << fixed << setprecision(2) << (ld(ans) / 100) << "\n";

    }
}
