#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;


#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)


// Check 1x1, 1xn, nx1, nxm
// check 1 guy with all of these, 2 guys

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    rep(i, 0, n) cin >> grid[i];
    vector<array<int, 4>> rng(26, {-1, -1, -1, -1});
    char target = 'A';
    int tr = -1, tc = -1;
    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] == target){
                tr = i, tc = j;
            }
            else if(grid[i][j] != '.') {
                rng[grid[i][j] - target] = {i, j, i+1, j+1};
            }
        }
    }
    assert(tr != -1);
    // cout << target << " " << tr << " " << tc << "\n";
    vi lowestcol(m, n);
    vector<array<int, 4>> cands;
    // lowest row, lowest col, highest row, highest col inc/exc
    for(int r = n - 1; r >= 0; r--){
        rep(j, 0, m){
            if(grid[r][j] != '.' && grid[r][j] != target) lowestcol[j] = r;
        }
        vii st; // pairs of {r, c}
        st.push_back({r, m});
        for(int c = m-1; c >= -1; c--){
            pii cur = {c == -1 ? r : lowestcol[c], c};
            while(sz(st) && cur <= st.back()){
                auto [r1, c1] = st.back();
                st.pop_back();
                if(sz(st)){
                    auto [r2, c2] = st.back();
                    cands.push_back({r, c+1, r1, c2});
                }
            }
            st.push_back(cur);
        }
    }
    array<int, 4> best = {-1, -1, -1, -1};
    for(auto [r1, c1, r2, c2] : cands){
        // cout << "try: " << r1 << " " << c1 << " " << r2 << " " << c2 << "\n";
        if(r1 <= tr && tr < r2 && c1 <= tc && tc < c2 && (r2 - r1) * (c2 - c1) > (best[2] - best[0]) * (best[3] - best[1])){
            best = {r1, c1, r2, c2};
        }
    }
    auto [r1, c1, r2, c2] = best;
    // cout << target << " " << r1 << " " << c1 << " " << r2 << " " << c2 << "\n";
    assert(best[0] != -1);
    rep(r, r1, r2){
        rep(c, c1, c2){
            if(grid[r][c] == '.') grid[r][c] = tolower(target);
        }
    }
    auto incrow = [&](int t)->bool {
        auto &[r1, c1, r2, c2] = rng[t];
        if(r2 >= n) return false;
        rep(c, c1, c2) if(grid[r2][c] != '.') return false;
        rep(c, c1, c2) grid[r2][c] = tolower(target + t);
        r2++;
        return true;
    };
    auto decrow = [&](int t)->bool {
        auto &[r1, c1, r2, c2] = rng[t];
        if(r1 <= 0) return false;
        rep(c, c1, c2) if(grid[r1-1][c] != '.') return false;
        rep(c, c1, c2) grid[r1-1][c] = tolower(target + t);
        r1--;
        return true;
    };
    auto canincrow = [&](int t)->bool {
        auto &[r1, c1, r2, c2] = rng[t];
        if(r2 >= n) return false;
        rep(c, c1, c2) if(grid[r2][c] != '.') return false;
        return true;
    };
    auto candecrow = [&](int t)->bool {
        auto &[r1, c1, r2, c2] = rng[t];
        if(r1 <= 0) return false;
        rep(c, c1, c2) if(grid[r1-1][c] != '.') return false;
        return true;
    };
    auto inccol = [&](int t)->bool {
        auto &[r1, c1, r2, c2] = rng[t];
        if(c2 >= m) return false;
        rep(r, r1, r2) if(grid[r][c2] != '.') return false;
        rep(r, r1, r2) grid[r][c2] = tolower(target + t);
        c2++;
        return true;
    };
    auto deccol = [&](int t)->bool {
        auto &[r1, c1, r2, c2] = rng[t];
        if(c1 <= 0) return false;
        rep(r, r1, r2) if(grid[r][c1-1] != '.') return false;
        rep(r, r1, r2) grid[r][c1-1] = tolower(target + t);
        c1--;
        return true;
    };
    rep(i, 1, 26){
        if(rng[i][0] == -1) continue;
        while(inccol(i));
        while(deccol(i));
    }
    rep(i, 0, n){
        set<int> c;
        rep(j, 0, m){
            if(grid[i][j] != '.') c.insert(toupper(grid[i][j]) - target);
        }
        if(!c.count(0)){
            while(sz(c)){
                bool can = true;
                for(int x : c) if(!canincrow(x)) can = false;
                if(!can) break;
                for(int x : c) incrow(x);
            }
            while(sz(c)){
                bool can = true;
                for(int x : c) if(!candecrow(x)) can = false;
                if(!can) break;
                for(int x : c) decrow(x);
            }
        } else{
            for(int x : c){
                if(x == 0) continue;
                while(incrow(x));
                while(decrow(x));
            }
        }
    }
    
    rep(i, 0, n){
        // rep(j, 0, m) assert(grid[i][j] != '.');
        cout << grid[i] << "\n";
    }
    return 0;
}
