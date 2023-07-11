#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;
using vvl = vector<vl>;

vi eulerWalk(vector<vpi> &gr, int nedges, int src = 0){
    int n = sz(gr);
    vi D(n), its(n), eu(nedges), ret, s = {src};
    D[src]++;
    while(!s.empty()){
        int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
        if(it == end){ ret.pb(x); s.pop_back(); continue; }
        tie(y, e) = gr[x][it++];
        if(!eu[e]){
            D[x]--,D[y]++;
            eu[e] = 1; s.pb(y);
        }
    }
    for(int x : D) if(x < 0 || sz(ret) != nedges + 1) return {};
    return {ret.rbegin(), ret.rend()};
}
//  TEST ON TRIANGLE
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vi> adj(n);
    vvpi gr(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
        gr[a].pb({b, i});
        gr[b].pb({a, i});
    }
    int src = 0;
    vi D(n), its(n), eu(m), ret, s = {src};
    D[src]++;
    while(!s.empty()){
        int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
        if(it == end){ ret.pb(x); s.pop_back(); continue; }
        tie(y, e) = gr[x][it++];
        if(!eu[e]){
            D[x]--,D[y]++;
            eu[e] = 1; s.pb(y);
        }
    }
    // for(int x : D) if(x < 0 || sz(ret) != nedges + 1) return {};
    // return {ret.rbegin(), ret.rend()};
    unordered_set<int> ins;
    ins.insert(ret[0]);
    vi path;
    path.pb(ret[0]);
    vi path2;
    rep(i, 1, sz(ret)){
        if(ins.count(ret[i])){
            path2.clear();
            path2.pb(ret[i]);
            while(path.back() != ret[i]){
                path2.pb(path.back());
                ins.erase(path.back());
                path.pop_back();
            }
            ins.erase(path.back());
            path.pop_back();
            for(int j : path2){
                cout << (j + 1) << " ";
            }
            cout << "\n";
        }
        ins.insert(ret[i]);
        path.pb(ret[i]);
        
    }

    

    return 0;
}