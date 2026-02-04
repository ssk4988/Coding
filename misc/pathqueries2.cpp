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

/*
T is a data type
op(T, T) is associative, non-commutative

want to support values on nodes and values on edges
allow rooting at any node

ok other people can write a dfs i hope

input type (on nodes)
parent array, node value array

input type (on edges)
parent array, parent edge value

also need dfs/bfs order of tree
need depth array as well

jump table [p][u] - path from u of 2^p edges/nodes

on nodes:

jump lower depth guy until same depth as upper
now if same node then add that in
while jump doesnt lead to same node for both, do the jump
if not same, do one jump
then add in last guy

on edges:
jump lower guy until same depth as upper
while jump doesnt lead to same node for both, do the jump
if not same, do one jump

parent links to itself

*/

using T = int;
T unit = INT_MAX;
T op(T a, T b) { return min(a, b); }
struct PathQ {
    vi par, depth;
    bool on_edges;
    vvi jmp;
    vector<vector<T>> up, down;
    PathQ(vector<vector<pair<int, T>>> adj, int r=0, bool on_edges = false): par(sz(adj), r), depth(sz(adj)), on_edges(on_edges) {
        int t = bit_width(size(adj)), n = sz(adj);
        vector<T> v(n, unit);
        up = vector(t, vector<T>(n, unit));
        function<void(int,int)> dfs = [&](int u,int p){
            for(auto [v,w]: adj[u]) if(v!=p){
                par[v] = u; up[0][v]=w; depth[v]=depth[u]+1;
                dfs(v,u);
            }
        };
        dfs(r, r);
        down = up;
        jmp = vector(t, par);
        rep(p, 0, t-1) {
            rep(u, 0, n) {
                jmp[p+1][u] = jmp[p][jmp[p][u]];
                up[p+1][u] = op(up[p][u], up[p][jmp[p][u]]);
                down[p+1][u] = op(down[p][jmp[p][u]], down[p][u]);
            }
        }
    }
    T path(int u, int v) {
        T left = unit, right = unit;
        for(int p = sz(jmp)-1; p >= 0; p--) {
            if(depth[jmp[p][u]] >= depth[v]) left = op(left, up[p][u]), u = jmp[p][u];
            if(depth[jmp[p][v]] >= depth[u]) right = op(down[p][v], right), v = jmp[p][v];
        }
        for(int p = sz(jmp)-1; p >= 0; p--)
            if(jmp[p][u] != jmp[p][v]) left = op(left, up[p][u]), right = op(down[p][v], right), u = jmp[p][u], v = jmp[p][v];
        if(u != v) {
            left = op(left, up[0][u]), right = op(down[0][v], right), u = jmp[0][u], v = jmp[0][v];
        }
        return on_edges ? op(left, right) : op(left, op(up[0][u], right));
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    
    return 0;
}
