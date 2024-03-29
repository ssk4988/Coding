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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    vector<vpi> adj(n, vpi(m, {-1, -1}));
    vector<vector<vpi>> radj(n, vector<vpi>(m));
    vvi land(n, vi(m));
    vvi sight(n, vi(m));
    vi dr = {1, 0, -1, 0}, dc = {0, 1, 0, -1};
    rep(i, 0, n){
        cin >> grid[i];
        rep(j, 0, m){
            if(grid[i][j] == '#'){
                sight[i][j] = true;
                land[i][j] = true;
            }
            else if(grid[i][j] == '.') land[i][j] = true;
            else if(grid[i][j] == '<'){
                if(j) adj[i][j] = {i, j-1};
            }
            else if(grid[i][j] == '>'){
                if(j + 1 < m) adj[i][j] = {i, j+1};
            }
            else if(grid[i][j] == '^'){
                if(i) adj[i][j] = {i-1, j};
            }
            else{
                if(i+1 < n) adj[i][j] = {i+1, j};
            }
            if(adj[i][j] != pi{-1, -1}){
                // cout << "reverse edge from " << adj[i][j].f << "," << adj[i][j].s << " to " << i << "," << j << endl;
                radj[adj[i][j].f][adj[i][j].s].pb({i, j});
            }
        }
    }
    vvi vis(n, vi(m));
    vector<vpi> cycles;
    vpi path;
    auto dfs = [&](int r, int c, auto &&dfs) -> void {
        if(r == -1 || c == -1) return;
        if(vis[r][c] == 1){
            cycles.pb({});
            for(int i = sz(path) - 1; i >= 0; i--){
                cycles.back().pb(path[i]);
                if(path[i] == pi{r, c}) break;
            }
            return;
        }
        if(vis[r][c] == 2) return;
        vis[r][c] = 1;
        path.pb({r, c});
        dfs(adj[r][c].f, adj[r][c].s, dfs);
        path.pop_back();
        vis[r][c] = 2;
    };
    rep(i, 0, n){
        rep(j, 0, m){
            dfs(i, j, dfs);
        }
    }
    int ans = 0;
    auto revdfs = [&](int r, int c, map<pi, int> &freq, set<pi> &block, auto &&revdfs) -> void {
        rep(i, 0, 4){
            int r1 = r + dr[i], c1 = c + dc[i];
            if(r1 < 0 || c1 < 0 || r1 >= n || c1 >= m) continue;
            if(sight[r1][c1]) freq[{r1, c1}]++;
        }
        // cout << "at " << r << "," << c << " ans is " << sz(freq) << endl;
        ans = max(ans, sz(freq));
        for(auto [r1, c1] : radj[r][c]){
            if(block.count({r1, c1})) continue;
            revdfs(r1, c1, freq, block, revdfs);
        }
        rep(i, 0, 4){
            int r1 = r + dr[i], c1 = c + dc[i];
            if(r1 < 0 || c1 < 0 || r1 >= n || c1 >= m) continue;
            if(sight[r1][c1]) {
                freq[{r1, c1}]--;
                if(freq[{r1, c1}] == 0) freq.erase({r1, c1});
            }
        }
    };
    for(auto &v : cycles){
        map<pi, int> freq;
        set<pi> block;
        // cout << "cycle: ";
        for(auto [r, c] : v){
            rep(i, 0, 4){
                int r1 = r + dr[i], c1 = c + dc[i];
                if(r1 < 0 || c1 < 0 || r1 >= n || c1 >= m) continue;
                if(sight[r1][c1]) freq[{r1, c1}]++;
            }
            // cout << r << "," << c << "  ";
            block.insert({r, c});
        }
        // cout << endl;
        ans = max(ans, sz(freq));
        for(auto [r, c] : v){
            revdfs(r, c, freq, block, revdfs);
        }
    }
    set<pi> block;
    map<pi, int> freq;
    rep(i, 0, n){
        rep(j, 0, m){
            if(land[i][j]) continue;
            if(adj[i][j] == pi{-1, -1} || land[adj[i][j].f][adj[i][j].s]){
                // cout << "checkout " << i << "," << j << endl;
                revdfs(i, j, freq, block, revdfs);
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
