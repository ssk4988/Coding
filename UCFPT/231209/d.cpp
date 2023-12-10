#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define pb push_back

using cube = array<int, 6>; // {bot, lef, riback, front, right, top}
cube front(cube &c){
    return {c[3], c[1], c[0], c[5], c[4], c[2]};
}
cube back(cube &c){
    return {c[2], c[1], c[5], c[0], c[4], c[3]};
}
cube left(cube &c) {
    return {c[1], c[5], c[2], c[3], c[0], c[4]};
}
cube right(cube &c) {
    return {c[4], c[0], c[2], c[3], c[5], c[1]};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi grid(n, vi(n));
        rep(i, 0, n){
            rep(j, 0, n){
                cin >> grid[i][j];
            }
        }
        vector<vector<vector<cube>>> cands(n, vector<vector<cube>>(n));
        cands[n-1][n-1].pb({grid[n-1][n-1], -1, -1, -1, -1, -1});
        for(int i = n - 1; i >= 0; i--){
            for(int j = n - 1; j >= 0; j--){
                for(auto &c : cands[i][j]){
                    // left
                    if(j > 0 && (grid[i][j - 1] == c[1] || c[1] == -1)){
                        cands[i][j-1].emplace_back(left(c));
                        cands[i][j-1].back()[0] = grid[i][j-1];
                    }
                    // back
                    if(i > 0 && (grid[i-1][j] == c[2] || c[2] == -1)){
                        cands[i-1][j].emplace_back(back(c));
                        cands[i-1][j].back()[0] = grid[i-1][j];
                    }
                }
            }
        }
        if(sz(cands[0][0]) == 0){
            cout << "No\n";
        }
        else{
            cout << "Yes\n";
            for(auto x : cands[0][0][0]){
                cout << max(x, 0) << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
