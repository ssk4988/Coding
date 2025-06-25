#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n) {
        int k; cin >> k;
        rep(_, 0, k) {
            int j; cin >> j; j--;
            adj[i].push_back(j);
            if(i == j){
                cout << "-1\n";
                exit(0);
            }
        }
    }
    vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
    vi used(n);
    vvi grid(n, vi(n, -1));
    auto dfs = [&](int r, int c, int v, int d, auto &&dfs) -> void {
        if(used[v]) return;
        used[v] = 1;
        grid[r][c] = v;
        if(sz(adj[v]) == 2) (d += 1) %= 4;
        for(int j : adj[v]) {
            if(used[j]) continue;
            if(sz(adj[j]) == 4) continue;
            int r1 = r + dr[d], c1 = c + dc[d];
            if(min(r1, c1) < 0) continue;
            dfs(r1, c1, j, d, dfs);
        }
    };
    int two = -1;
    rep(i, 0, n) if(sz(adj[i]) == 2) two = i;
    if(two == -1) {
        cout << "-1\n";
        return 0;
    }
    used[two] = 1;
    grid[0][0] = two;
    for(int t : adj[two]) {
        dfs(1, 0, t, 0, dfs);
        break;
    }
    int rb = -1, cb = -1;
    rep(i, 0, n){
        rep(j, 0, n) {
            if(grid[i][j] != -1) rb = max(rb, i+1), cb = max(cb, j+1);
        }
    }
    // cerr << "rb: " << rb << " cb: " << cb << endl;
    // rep(i, 0, rb) {
    //     rep(j, 0, cb){
    //         cerr << grid[i][j]+1 << " ";
    //     }
    //     cerr << endl;
    // }
    if(rb * cb != n) {
        cout << "-1\n";
        return 0;
    }
    vi relax(n);
    // rep(i, 0, n) cerr << i+1 << " " << used[i] << endl;
    auto dfs2 = [&](int r, int c, int v, auto &&dfs2) -> void {
        if(relax[v]) return;
        // cerr << "relax " << r << " " << c << " " << v << endl;
        used[v] = 1;
        grid[r][c] = v;
        vi left;
        for(int j : adj[v]) if(!used[j]) left.push_back(j);
        // cerr << "leftsz: " << sz(left) << endl;
        if(sz(left) != 1) return;
        int j = left[0];
        relax[v] = 1;
        // cerr << "relax spot " << r << " " << c <<  " " << v << endl;
        rep(k, 0, 4) {
            int r1 = r + dr[k], c1 = c + dc[k];
            if(min(r1, c1) < 0 || r1 >= rb || c1 >= cb) continue;
            if(grid[r1][c1] != -1) continue;
            dfs2(r1, c1, j, dfs2);
            break;
        }
        rep(k, 0, 4) {
            int r1 = r + dr[k], c1 = c + dc[k];
            if(min(r1, c1) < 0 || r1 >= rb || c1 >= cb) continue;
            if(grid[r1][c1] == -1) continue;
            dfs2(r1, c1, grid[r1][c1], dfs2);
            break;
        }
    };
    rep(u, 0, n) {
        if(used[u] && !relax[u]) {
            rep(i, 0, rb) {
                rep(j, 0, cb) if(grid[i][j] == u) dfs2(i, j, u, dfs2);
            }
        }
    }
    set<int> seen;
    rep(i, 0, rb) rep(j, 0, cb) seen.insert(grid[i][j]);
    if(seen.count(-1) || sz(seen) != n) cout << "-1\n";
    else {
        bool works = true;
        rep(i, 0, rb) {
            rep(j, 0, cb) {
                if(i+1 < rb) {
                    works = works && find(all(adj[grid[i][j]]), grid[i+1][j]) != end(adj[grid[i][j]]);
                    works = works && find(all(adj[grid[i+1][j]]), grid[i][j]) != end(adj[grid[i+1][j]]);
                }
                if(j+1 < cb) {
                    works = works && find(all(adj[grid[i][j]]), grid[i][j+1]) != end(adj[grid[i][j]]);
                    works = works && find(all(adj[grid[i][j+1]]), grid[i][j]) != end(adj[grid[i][j+1]]);
                }
            }
        }
        if(!works) {
            cout << "-1\n";
            return 0;
        }
        cout << rb << " " << cb << "\n";
        rep(i, 0, rb) {
            rep(j, 0, cb) {
                cout << grid[i][j]+1 << " ";
            }
            cout << "\n";
        }
    }


    return 0;
}
