#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
using bs = bitset<10>;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vii dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<string> grid(2 * n - 1);
    rep(i, 0, sz(grid)){
        cin >> grid[i];
    }
    // cout << "read stuff" << endl;
    vector cmp(n, vector(n, vi(2, -1)));
    // 0 horizontal 1 vertical
    vector used(n, vi(n));
    vector pos(n, vector<bs>(n));
    rep(i, 0, n){
        rep(j, 0, n){
            rep(k, 0, n){
                pos[i][j][k] = 1;
            }
        }
    }
    rep(i, 0, 2 * n - 1){
        rep(j, 0, 2 * n - 1){
            if((i + j) % 2 == 0) continue;
            int rw = i/2, cl = j/2;
            if(i & 1){
                if(grid[i][j] != '.')
                cmp[rw][cl][1] = grid[i][j] == 'v';
                // cout << rw << " " << cl << " " << 1 << " " << cmp[rw][cl][1] << endl;
            }
            else {
                if(grid[i][j] != '.')
                cmp[rw][cl][0] = grid[i][j] == '>';
                // cout << rw << " " << cl << " " << 0 << " " << cmp[rw][cl][0] << endl;
            }
        }
    }
    vvi res(n, vi(n, -1));
    vector<tuple<int, int, bs>> prv_pos;
    auto clear_range = [&](int i, int j, int l, int r) -> void {
        rep(v, l, r){
            pos[i][j][v] = 0;
        }
    };
    auto upd_adj = [&](int i, int j, int pi, int pj, int val) -> void {
        if(pi == i) {
            if(j > pj) {
                if(cmp[i][pj][0] == 1) clear_range(pi, pj, 0, val);
                else if(cmp[i][pj][0] == 0) clear_range(pi, pj, val, n);
            } else {
                if(cmp[i][j][0] == 1) clear_range(pi, pj, val, n);
                else if(cmp[i][j][0] == 0) clear_range(pi, pj, 0, val);
            }
        } else {
            if(i > pi) {
                if(cmp[pi][j][1] == 1) clear_range(pi, pj, 0, val);
                else if(cmp[pi][j][1] == 0) clear_range(pi, pj, val, n);
            } else {
                if(cmp[i][j][1] == 1) clear_range(pi, pj, val, n);
                else if(cmp[i][j][1] == 0) clear_range(pi, pj, 0, val);
            }
        }
    };
    auto set_val = [&](int i, int j, int val)->int {
        int prv_t = sz(prv_pos);
        rep(k, 0, n){
            if(!used[i][k]){
                prv_pos.emplace_back(i, k, pos[i][k]);
                pos[i][k][val] = 0;
            }
            if(k != i && !used[k][j]){
                prv_pos.emplace_back(k, j, pos[k][j]);
                pos[k][j][val] = 0;
            }
        }
        res[i][j] = val;
        used[i][j] = true;
        for(auto [dr, dc] : dir) {
            int i1 = i + dr, j1 = j + dc;
            if(i1 < 0 || j1 < 0 || i1 >= n || j1 >= n) continue;
            prv_pos.emplace_back(i1, j1, pos[i1][j1]);
            upd_adj(i, j, i1, j1, val);
        }
        return prv_t;
    };
    auto rem_val = [&](int i, int j, int t) -> void {
        used[i][j] = false;
        res[i][j] = -1;
        while(sz(prv_pos) > t){
            auto [row, col, mask] = prv_pos.back();
            prv_pos.pop_back();
            pos[row][col] = mask;
        }
    };
    int depth = 0, mx_depth = 0;
    auto bt = [&](auto &&bt) -> bool {
        if(depth > mx_depth){
            mx_depth = depth;
            // cout << mx_depth << endl;
        }
        array<int, 3> mn = {100, -1, -1};
        rep(i, 0, n){
            rep(j, 0,n){
                if(used[i][j]) continue;
                mn = min(mn, array<int, 3>{(int)pos[i][j].count(), i, j});
            }
        }
        auto [cnt, i, j] = mn;
        // cout << cnt << " " << i << " " << j << " " << pos[i][j] << endl;
        if(mn[0] == 100) return true;
        if(mn[0] == 0){
            // assert(false);
            return false;
        }
        rep(v, 0, n){
            if(pos[i][j][v]){
                int t = set_val(i, j, v);
                depth++;
                if(bt(bt)) return true;
                depth--;
                rem_val(i, j, t);
            }
        }
        return false;
    };
    rep(i, 0, n){
        rep(j, 0, n){
            if(grid[i * 2][j * 2] != '-'){
                int v = grid[i * 2][j * 2] - '0';
                v--;
                // cout << "setting " << i << " " << j << " " << v << endl;
                set_val(i, j, v);
            }
        }
    }
    // cout << pos[4][4] << endl;
    // cout << pos[3][2] << endl;
    // cout << "started stuff" << endl;
    bool works = bt(bt);
    // cout << works << "\n";
    rep(i, 0,n){
        rep(j, 0, n) cout << res[i][j]+1;
        cout << "\n";
    }

    return 0;
}
